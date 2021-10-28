function [Data,t,fs] = RigolMSO1000Z_Read_RunStop(serialNum,Channels,frames)
% Read from Rigol Oscilloscope MSO 1000 Z with run/stop capture.
%
% Example: RigolMSO1000Z_Read_RunStop('DS1ZD181600446',[3,4],4);
%
% Input:
%   serialNum:  Serial number (char or string), e.g. 'DS1ZD181600446'
%   Channels:   One-dimension array with channel or channels to read: [1],[2,4],...
%   frames:     Number of frames to be read from internal memory.
%
% Output
%   Data:   Array with as many columns as channels received and 249988 samples.
%   t:      Time array
%   fs:     Sample rate
%
% Jose Manuel Requena Plens (2021)

% Check inputs
arguments
    serialNum   (1,1) string
    Channels    (1,:) {mustBeInteger,mustBePositive,mustBeMember(Channels,[1,2,3,4])}
    frames      {mustBeInteger,mustBeScalarOrEmpty,mustBePositive} = 2
end

%% Load instrument
devlist     = visadevlist();                            % Get all VISA resources availables
[~,idxdev]  = ismember(serialNum,devlist.SerialNumber); % Search the serial number
deviceNr    = devlist.ResourceName{idxdev(1)};          % Get resource name
MSO         = visadev(deviceNr);                        % Create VISA Object

%% Signal data format
writeline(MSO, ':WAVeform:MODE RAW' );
writeline(MSO, ':WAVeform:FORMat BYTE')

% Flush data
flush(MSO); pause(0.1) % Wait 100ms

%% Measure
writeline(MSO, ':RUN');
HScale = str2double(writeread(MSO, ':TIMebase:MAIN:SCALe?'));
pause(HScale*12*4*2+0.1) % Wait for load signal in oscilloscope
writeline(MSO, ':STOP');

% Flush data
flush(MSO); pause(0.1) % Wait 100ms

%% Read data

% Data available
% RAW: 250000 (uint8), WORD: 125000 (uint16), ASCII: 15625 (CSV)
frameSize   = 250000;
HScale      = str2double(writeread(MSO, ':TIMebase:MAIN:SCALe?'));
wavelen     = HScale * 12; % Scale*div
sampleRate  = str2double(writeread(MSO, ':ACQuire:SRATe?'));
totalSize   = floor(wavelen*sampleRate); % Memory Depth = Sample Rate × Waveform Length
totalFrames = min(ceil(totalSize/frameSize),frames);

% Initialize
cellFrames = cell(1,totalFrames);
RAWData    = zeros((frameSize-12)*totalFrames,length(Channels));
YScale     = zeros(1,length(Channels));
refY       = zeros(1,length(Channels));
oriY       = zeros(1,length(Channels));
exit       = false;

% Read
for c = 1:length(Channels) % Each channel

    % Try attempts
    maxatt = 10;
    for att = 1:maxatt
        try
            % Select channel
            writeline(MSO, sprintf(':WAVeform:SOURce CHANnel%d',Channels(c)) );
            % Flush data
            flush(MSO); pause(0.1) % Wait 100ms

            % Read the waveform data (frames)
            frame = 1;
            for point = 0:frameSize:totalSize

                % If all the frames have been received, the loop ends
                if frame>totalFrames; break; end

                % Initial point for frame N
                writeline(MSO, sprintf(':WAVeform:STARt %d',point+13));

                % Final point for frame N
                if (point+frameSize)<=totalSize
                    writeline(MSO, sprintf(':WAVeform:STOP %d',point+frameSize))
                    frameSizeAux = frameSize;
                else
                    % If almost all the memory has been read, the last
                    % points are received
                    writeline(MSO, sprintf(':WAVeform:STOP %d',totalSize))
                    frameSizeAux = totalSize-point;
                    addZeros = frameSize-frameSizeAux;
                    exit = true;
                end

                % Receive data
                writeline(MSO, ':WAVeform:DATA?');   % Request data
                data = read(MSO, frameSizeAux, 'uint8'); % Read data

                % Fill with zeros if the last frame
                if exit; data = [data(1:end-1),zeros(1,addZeros+1)]; end

                % Remove Data Header (11) and end newline character (1) and store
                cellFrames{frame} = data(12:end-1); % Store frames

                if exit; break; end
                frame = frame + 1;
            end

            % Store data without Data Header (11) and end newline character (1)
            data = [cellFrames{:}];
            RAWData(:,c) = data(:);

            % Flush data and reload channel
            flush(MSO); pause(0.1) % Wait 100ms
            writeline(MSO, sprintf(':WAVeform:SOURce CHANnel%d',Channels(c)) );

            % Get Y-axis information
            YScale(c) = str2double(writeread(MSO, ':WAVeform:YINCrement?'));
            % Reference and origin values to centering data
            refY(c)   = str2double(writeread(MSO, ':WAVeform:YREFerence?'));
            oriY(c)   = str2double(writeread(MSO, ':WAVeform:YORigin?'));

            % Reinitialize
            exit = false;
            cellFrames = cell(1,totalFrames);

            % Exit the attempts loop
            break;

        catch
            fprintf('Retrying. Attempt %d with channel %d\r\n',att,Channels(c))
            flush(MSO); pause(0.1) % Wait 100ms
            clear MSO
            MSO = visadev(deviceNr); % Create VISA Object
            if att == maxatt
                YScale(c) = nan;
                refY(c) = nan;
                oriY(c) = nan;
                fprintf('Empty values with channel %d\r\n',Channels(c))
                break;
            end
        end

    end
end

% Flush data
flush(MSO); pause(0.1) % Wait 100ms

% Samplerate
incX = str2double(writeread(MSO, ':WAVeform:XINCrement?')); % delta T (secs)
fs =  str2double(writeread(MSO, ':ACQuire:SRATe?')); % Sa/s

% Scale data (convert 0-255 values to Measure Units and centering in x-axis)
Data = (RAWData - (refY+oriY) ).*YScale; % Scale and centering

% Time array (seconds)
t = 0:incX:incX*(size(Data,1)-1);

% Clear VISA Object
clear MSO