function RigolMSO1000Z_WaitForTrigger(serialNum,TriggerChannel,TriggerLevel)
% Set trigger of Rigol Oscilloscope MSO 1000 Z.
%
% Example: 
%   RigolMSO1104Z_WaitForTrigger('DS1ZD181600446',3,-0.02);
%
% Input:
%   serialNum:      Serial number (char or string), e.g. 'DS1ZD181600446'
%   TriggerChannel: Channel of trigger source.
%   TriggerLevel:   Trigger voltage level.
%
% Jose Manuel Requena Plens (2021) [joreple@upv.es]

% Check inputs
arguments
    serialNum       (1,1) string 
    TriggerChannel  (1,1) {mustBeInteger,mustBeMember(TriggerChannel,[1,2,3,4])}
    TriggerLevel    {mustBeScalarOrEmpty,mustBeReal} = -0.02
end

%% Load instrument
devlist     = visadevlist();                            % Get all VISA resources availables
[~,idxdev]  = ismember(serialNum,devlist.SerialNumber); % Search the serial number
deviceNr    = devlist.ResourceName{idxdev(1)};          % Get resource name
MSO         = visadev(deviceNr);                        % Create VISA Object

% Flush data
flush(MSO); pause(0.1) % Wait 100ms

%% Acquire settings
writeline(MSO, ':ACQuire:MDEPth AUTO' );
writeline(MSO, ':WAVeform:MODE RAW' );
writeline(MSO, ':WAVeform:MODE RAW' );

%% Trigger setup
writeline(MSO, ':TRIGger:MODE EDGE' );
writeline(MSO, ':TRIGger:COUPling DC')
writeline(MSO, ':TRIGger:SWEep SINGle' );
writeline(MSO, ':TRIGger:HOLDoff 0.0000002');
writeline(MSO, ':TRIGger:NREJect 1' );
writeline(MSO, sprintf(':TRIGger:EDGe:SOURce CHANnel%d',TriggerChannel));
writeline(MSO, ':TRIGger:EDGe:SLOPe POSitive' );

% Level
% Limits: (± 5 × VerticalScale from the screen center) - OFFSet
offset = str2double(writeread(MSO, sprintf(':CHANnel%d:OFFSet?',TriggerChannel)));
scale = str2double(writeread(MSO, sprintf(':CHANnel%d:SCALe?',TriggerChannel)));
if TriggerLevel > (5*scale-offset);  TriggerLevel =  5*scale-offset; end
if TriggerLevel < (-5*scale-offset); TriggerLevel = -5*scale-offset; end
% Set level
writeline(MSO, sprintf(':TRIGger:EDGe:LEVel %f',TriggerLevel));

% Flush data
flush(MSO); pause(0.1) % Wait 100ms

% Check trigger (if enabled and wait/run, break)
while 1
    writeline(MSO, ':SINGle')
    % Flush data
    flush(MSO); pause(0.2) % Wait 200ms
    status = writeread(MSO, ':TRIGger:STATus?' );
    if strcmp(status,'WAIT') || strcmp(status,'RUN')
        break;
    end
    pause(0.5)
end

% Clear VISA Object
clear MSO