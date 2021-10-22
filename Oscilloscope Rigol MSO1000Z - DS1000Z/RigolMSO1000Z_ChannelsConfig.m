function RigolMSO1000Z_ChannelsConfig(serialNum,Channels,VScale,VOffset,ProbeRatio,HScale,HOffset)
% Channels settings. Rigol Oscilloscope MSO 1000 Z.
%
% Examples: 
%   Full config for channels 3 and 4:
%       RigolMSO1000Z_ChannelsConfig('DS1ZD181600446',[3,4],[1,0.125],[0,0],[10,1],0.02,0);
%   Only vertical settings for channels 1,3,4:
%       RigolMSO1000Z_ChannelsConfig('DS1ZD181600446',[1,3,4],[1,0.125,0.5],[0,0,0],[10,1,10]);
%   Only horizontal setting:
%       RigolMSO1000Z_ChannelsConfig('DS1ZD181600446',1,[],[],[],0.02,0);
%
% Input:
%   serialNum:   Serial number (char or string), e.g. 'DS1ZD181600446'
%   Channels:    Channel or channels number to be configured. Array with
%                one element for each channel, e.g. [1] or [2,3] or [1,2,3,4].
%   VScale:      Vertical scale for each channel. Array with same length
%                as ReadChannels.
%   VOffset:     Vertical offset for each channel. Array with same length
%                as ReadChannels.
%   ProbeRatio:  Probe ratio for each channel. Array with same length
%                as ReadChannels.
%   HScale:      Horizontal scale. Only one element/value.
%   HOffset:     Horizontal offset. Only one element/value.
%
% Jose Manuel Requena Plens (2021) [joreple@upv.es]

% Check inputs
arguments 
    serialNum   (1,1) string 
    Channels    (1,:) {mustBeInteger,mustBePositive,mustBeMember(Channels,[1,2,3,4])}
    VScale      (1,:)  = [] 
    VOffset     (1,:)  = [] 
    ProbeRatio  (1,:)  = [] 
    HScale      {mustBeScalarOrEmpty} = [] 
    HOffset     {mustBeScalarOrEmpty} = [] 
end

%% Load instrument
devlist     = visadevlist();                            % Get all VISA resources availables
[~,idxdev]  = ismember(serialNum,devlist.SerialNumber); % Search the serial number
deviceNr    = devlist.ResourceName{idxdev(1)};          % Get resource name
MSO         = visadev(deviceNr);                        % Create VISA Object

%% Enable channels
% Enable only selected read channels
for c = 1:4
    if any(Channels==c)
        % Enable
        writeline(MSO, sprintf(':CHANnel%d:DISPlay ON',c))
    else
        % Disable
        writeline(MSO, sprintf(':CHANnel%d:DISPlay OFF',c))
    end
end

%% Vertical scale

% Set probe ratio
if ~isempty(ProbeRatio)
    for c = 1:length(Channels)
        % Set ratio to available nearest value
        ratioAvail = [0.01,0.02,0.05,0.1,0.2,0.5,1,2,5,10,20,50,100,200,500,1000];
        [~,idx] = min(abs(ratioAvail-ProbeRatio(c)));
        Pratio(c) = ratioAvail(idx); %#ok<*AGROW>

        % Set
        writeline(MSO, sprintf(':CHANnel%d:PROBe %f',Channels(c),Pratio(c)))
    end
end

% Vertical scale (amplitude)
for c = 1:length(Channels)

    % Vertical scale
    if ~isempty(VScale)
        % Set to available nearest value
        Pratio = str2double(writeread(MSO, sprintf(':CHANnel%d:PROBe?',Channels(c))));
        if Pratio <= 1
            Vavail = repmat([1,2,5],4,1).*[1e-3; 1e-2; 1e-1; 1];
            Vavail = [Vavail(:);10];
        else
            Vavail = repmat([1,2,5],4,1).*[1e-2; 1e-1; 1; 1e1];
            Vavail = [Vavail(:);100];
        end
        [~,idx] = min(abs(Vavail-VScale(c)));
        VSca(c) = Vavail(idx);

        % Set
        writeline(MSO, sprintf(':CHANnel%d:SCALe %f',Channels(c),VSca(c)));     
    end

    % Vertical offset
    if ~isempty(VOffset)
        writeline(MSO, sprintf(':CHANnel%d:OFFSet %f',Channels(c),VOffset(c))); 
    end
end

%% Horizontal scale (time)

% Horizontal scale
if ~isempty(HScale)
    % Set to available nearest value
    Tavail = repmat([5,10,20],10,1).*[1e-9;1e-8;1e-7;1e-6;1e-5;1e-4;1e-3;1e-2;1e-1;1];
    Tavail = [Tavail(:);50];
    [~,idx] = min(abs(Tavail-HScale));
    HSca = Tavail(idx);
    % Set
    writeline(MSO, sprintf(':TIMebase:MAIN:SCALe %f',HSca));
end

% Horizontal offset
if ~isempty(HOffset)
    % Limits: -Screen/2 to 1s or -Screen/2 to 5000s
    if HOffset<(-6*HSca); HOffset = -6*HSca; end
    writeline(MSO, sprintf(':TIMebase:MAIN:OFFSet %f',HOffset));
end

% Clear VISA Object
clear MSO
