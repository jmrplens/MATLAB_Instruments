function [Data,t,fs] = RedPitaya_Pulses_SRCandREC(IP,port,outCH,inCH,type,f,pulses,amp,decimation)
% RED PITAYA STEMlab 125-14 v1.1
% Comands: https://redpitaya.readthedocs.io/en/latest/appsFeatures/remoteControl/remoteControl.html#list-of-supported-scpi-commands
%
% Example: RedPitaya_Pulses_SRCandREC('192.168.1.200',5000,1,1,'sine',40e3,100,0.5,64)
%
% Input:
%   IP:         IP address
%   Port:       Connection port
%   outCH:      Output channel. 1 or 2
%   inCH:       Input channel. 1 or 2
%   type:       Signal type (sine, square, triangle, sawu, sawd, pwm)
%   f:          Signal frequency (Hz)
%   pulses:     Number of pulses. Default: 50
%   amp:        Signal amplitude (V). Default: 1
%   decimation: Decimation value. Sample Rate = 125/decimation. Default: 64
%               Available: 1, 8, 64, 1024, 8192, 65536
%
% Output
%   Data:   Array with as many columns as channels received and 249988 samples.
%   t:      Time array
%   fs:     Sample rate
%
% Jose Manuel Requena Plens (2021) [joreple@upv.es]

% Check inputs
arguments
    IP          (1,1) string 
    port        (1,1) double
    outCH       (1,1) {mustBeInteger,mustBePositive,mustBeMember(outCH,[1,2])}
    inCH        (1,1) {mustBeInteger,mustBePositive,mustBeMember(inCH,[1,2])}
    type        (1,1) string {mustBeMember(type,{'sine','square','triangle','sawu','sawd','pwm'})}
    f           (1,1) {mustBePositive}
    pulses      (1,1) {mustBeInteger,mustBePositive} = 50
    amp         (1,1) {mustBeInRange(amp,-1,1)} = 1
    decimation  (1,1) {mustBeInteger,mustBePositive,mustBeMember(decimation,[1,8,64,1024,8192,65536])} = 64
end

%% CHANNELS
% Output channel
SOURout = ['SOUR',num2str(outCH)];
OUTPUT  = ['OUTPUT',num2str(outCH)];
% Input channel
SOURin  = ['SOUR',num2str(inCH)];

%% SIGNAL
% Type
switch lower(type)
    case 'sine'
        SIGNAL = 'SINE';
    case 'square'
        SIGNAL = 'SQUARE';
    case 'triangle'
        SIGNAL = 'TRIANGLE';
    case 'sawu' % sawtooth up
        SIGNAL = 'SAWU';
    case 'sawd' % sawtooth down
        SIGNAL = 'SAWD';
    case 'pwm'
        SIGNAL = 'PWM'; % Duty cycle set with: 'SOURx:DCYC 0.2'
    otherwise
        error('Type signal error. Available: {sine, square, triangle, sawu, sawd, pwm}.')
end
% Frecuency
FREQUENCY = num2str(f,'%.2f');
% Amplitude (limits -1 to 1 Volt)
if amp > 1; amp = 1; end; if amp < -1; amp = -1; end
AMPLITUDE = num2str(amp);
% Number of pulses
PULSES = num2str(pulses);


%% CONNECTION
tcpIP   = tcpclient(IP, port);              % Create connection
configureTerminator(tcpIP,"LF","CR/LF");    % Set terminator for write and read 
flush(tcpIP);               % Clear write/read buffers

%% RESET HARDWARE
writeline(tcpIP,'GEN:RST'); % Reset generator order
writeline(tcpIP,'ACQ:RST'); % Reset acquisition order

%% GENERATE SIGNAL

% Function of output signal order string 'SOURx:FUNC AAAA'
funct_order = [SOURout,':FUNC ',SIGNAL];
% Frequency of output signal order string 'SOURx:FREQ:FIX xxxx'
f_order     = [SOURout,':FREQ:FIX ',FREQUENCY]; 
% Amplitude of output signal order string 'SOURx:VOLT x'
a_order     = [SOURout,':VOLT ',AMPLITUDE];
% Offset amplitude 'SOURx:VOLT:OFFS xxx'
a_order_off = [SOURout,':VOLT:OFFS ',num2str(0)]; % To 0 volts
% Phase 'SOURx:PHAS xx'
ph_order    = [SOURout,':PHAS ',num2str(0)]; % To 0 
% Pulses of signal order string 'SOURx:BURS:NCYC x'
puls_order  = [SOURout,':BURS:NCYC ',PULSES];
% Pulses of signal order string 'SOURx:BURS:STAT BURST' % {'BURST','CONTINOUS'}
pstat_order = [SOURout,':BURS:STAT ','BURST'];
% Channel on order string 'OUTPUTx:STATE ON'
on_order    = [OUTPUT,':STATE ON'];

% Send orders
writeline(tcpIP,funct_order);  % Set function of output signal 
writeline(tcpIP,f_order);      % Set frequency of output signal
writeline(tcpIP,a_order);      % Set amplitude of output signal
writeline(tcpIP,a_order_off);  % Set offset amplitude of output signal
writeline(tcpIP,ph_order);     % Set phase of output signal
writeline(tcpIP,puls_order);   % Set pulses of sine wave
writeline(tcpIP,pstat_order);  % Set burst mode
writeline(tcpIP,on_order);     % Power on output channel

%% ACQUISITION

% Decimation order string 'ACQ:DEC x'
dec_order    = sprintf('ACQ:DEC %d',decimation);

writeline(tcpIP,dec_order);                 % Decimation of signal received -> Fs = 125/decimation
writeline(tcpIP,'ACQ:TRIG:LEV 0');          % Trigger level to 0. Trigger by software
writeline(tcpIP,'ACQ:TRIG:DLY 8192');       % Trigger delay to 0. +-8192 is available
writeline(tcpIP,'ACQ:AVG ON');              % Enable averaging
writeline(tcpIP,'ACQ:GET:DATA:UNITS RAW');  % Acquired data units {'RAW','VOLTS'}
writeline(tcpIP,'ACQ:GET:DATA:FORMAT ASCII'); % Acquired data format {'BIN','ASCII'}


%% START MEASURE (generation & acquisition)
writeline(tcpIP,'ACQ:START');           % Acquisition
pause(1);                               % Wait for load buffer
writeline(tcpIP,'ACQ:TRIG AWG_PE'); 
writeline(tcpIP,[SOURout,':TRIG:IMM']); % Set generator trigger to immediately

%% Wait for trigger
while 1
    trig_rsp = strtrim(writeread(tcpIP,'ACQ:TRIG:STAT?'));
    if trig_rsp == "TD" % Trigger Disabled
        break
    end
end

%% READ
writeline(tcpIP,['ACQ:',SOURin,':DATA?']);  % Request acquisition data
signal_str = readline(tcpIP);               % Read acquisition data
writeline(tcpIP,'ACQ:STOP');                % Stop acquisition

%% PROCESS DATA
signal_str = erase(signal_str,["{","}"]);           % Clean
Data = str2double(split(signal_str',','));    % To num

% Sample rate and time array
fs = 125/str2double(writeread(tcpIP,'ACQ:DEC?'));
t  = (0:1:length(Data)-1)/fs;

%% Close connection with Red Pitaya
clear('tcpIP')

end