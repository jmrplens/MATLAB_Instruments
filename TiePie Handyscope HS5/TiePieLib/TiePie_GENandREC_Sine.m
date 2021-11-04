function [signal_rec,t,real_fs] = TiePie_GENandREC_Sine(LIB,f,fs,chan,amp,pulses,RecLength,VRange,ProbeGain)
% TiePie Generation and adquisition (triggered) with sine signal.
%
%   [signal_rec,t,real_fs] = TiePie_GENandREC_Sine(LIB,f,fs,chan,amp,pulses,RecLength,VRange,ProbeGain)
%
% Example:
%   40kHz sine signal with 1MHz sample rate and 2 Volts. Read from channel 1:
%       [signal_rec,t,real_fs] = TiePie_GENandREC_Sine(LIB,40e3,1e6,1,2,50,5000,3,1)
%
% Inputs:
%   LIB         TiePie Library object
%   f           Frequency of sine signal (Hz)
%   fs          Output signal sample rate (Hz)
%   chan        Read channel/s. Available: 1, 2, [1,2], [2,1]
%   amp         Output amplitude (V). Max 12 V
%   pulses      Burst count / repetitions of signal_gen. Default: 1
%   RecLength   Record length in samples
%   VRange      Vertical range for each channel. Array with same length
%               as chan. Default: 80 V
%   ProbeGain   Probe ratio for each channel. Array with same length
%               as chan. Default: 1
%
% Outputs:
%   signal_rec  Signal received array (V). One column for each channel.
%   t           Time array (s)
%   real_fs     Final sample rate acquisition. One positive value
%
% Jose Manuel Requena Plens (2021) [joreple@upv.es]

% Check inputs
arguments
    LIB             (1,1) LibTiePie.Library
    f               (1,1) {mustBePositive}
    fs              (1,1) {mustBePositive}
    chan            (1,:) {mustBeInteger,mustBePositive,mustBeMember(chan,[1,2])}
    amp             (1,1) double
    pulses          (1,1) {mustBeInteger,mustBePositive} = 1
    RecLength       (1,1) {mustBeInteger,mustBePositive} = 10000
    VRange          (1,:) {mustBePositive} = []
    ProbeGain       (1,:) {mustBePositive} = []
end

% Import libraries
import LibTiePie.Const.*
import LibTiePie.Enum.*

%% TiePie
% Enable network search:
LIB.Network.AutoDetectEnabled = true;
% Search for devices:
LIB.DeviceList.update();
% Try to open an oscilloscope with block measurement support and a generator in the same device:
for k = 0 : LIB.DeviceList.Count - 1
    item = LIB.DeviceList.getItemByIndex(k);
    if item.canOpen(DEVICETYPE.OSCILLOSCOPE) && item.canOpen(DEVICETYPE.GENERATOR)
        scp = item.openOscilloscope();
        if ismember(MM.BLOCK, scp.MeasureModes)
            gen = item.openGenerator();
            break;
        else
            clear scp;
        end
    end
end
clear item

%% RUN
if exist('scp', 'var') && exist('gen', 'var')

    %% Input channels settings
    scp.MeasureMode     = MM.BLOCK;     % Set measure mode (BLOCK, STREAM)
    scp.SampleFrequency = fs;           % Set sample frequency
    scp.RecordLength    = RecLength;    % Set record length
    scp.Resolution      = 14;           % Set resolution to 16 bit (available 8, 12, 14 and 16)
    scp.PreSampleRatio  = 0;            % Set pre sample ratio
    % For each channel
    for ii = 1:numel(chan)
        c = chan(ii);
        scp.Channels(c).Enabled    = true;         % Enable channel to measure it
        scp.Channels(c).Coupling   = CK.DCV;       % Set coupling (DCV, ACV)
        if ~isempty(VRange)
            scp.Channels(c).Range  = VRange(ii);   % Set range. Nearest to: (0.2, 0.4, 0.8, 2, 4, 8, 20, 40, 80)
        end
        if ~isempty(ProbeGain)
            scp.Channels(c).ProbeGain  = ProbeGain(ii);% Probe ratio
        end
    end

    %% Trigger settings
    % Set trigger timeout:
    scp.TriggerTimeOut = 1; % 1 s
    % Enable all channel trigger sources:
    for ii = 1:numel(chan)
        c = chan(ii);
        scp.Channels(c).Trigger.Enabled = true;

        % Trigger type (RISINEDGE, FALLINGEDGE, INWINDOW, OUTWINDOW,
        % ANYEDGE, ENTERWINDOW, EXITWINDOW, PULSEWIDTHPOSITIVE)
        scp.Channels(c).Trigger.Kind = TK.RISINGEDGE;

        scp.Channels(c).Trigger.Levels(1) = 0.5; % Trigger level (percentage)
        scp.Channels(c).Trigger.Hystereses(1) = 0.05; % Trigger Hysteresis (percentage)

    end
    % Locate trigger input:
    triggerInput = scp.getTriggerInputById(TIID.GENERATOR_START); % (GENERATOR_NEW_PERIOD, GENERATOR_START, GENERATOR_STOP, EXT1, EXT2
    if triggerInput == false
        clear triggerInput scp gen;
        error('Unknown trigger input!');
    end
    % Enable trigger input:
    triggerInput.Enabled = true;
    % Release reference to trigger input:
    clear triggerInput;

    %% Generator settings:
    gen.SignalType      = ST.SINE;              % Set signal type
    gen.FrequencyMode   = FM.SIGNALFREQUENCY;   % Set frequency mode (SAMPLEFREQUENCY or SIGNALFREQUENCY)
    gen.Frequency       = f;                   % Set sample rate (Hz)
    gen.Amplitude       = amp;                  % Set amplitude (V) (Max 12 V)
    gen.Offset          = 0;                    % Set offset (V) (Max +-12 V)
    % Burst mode
    gen.Mode            = GM.BURST_COUNT;       % Set mode
    gen.BurstCount      = pulses;               % Set burst count / pulses / periods

    gen.OutputOn = true; % Enable output

    %% Information
    % Print oscilloscope info:
    display(scp);
    % Print generator info:
    display(gen);

    %% START
    scp.start(); % Start measurement
    gen.start(); % Start signal generation

    % Wait for measurement to complete:
    while ~scp.IsDataReady
        pause(10e-3) % 10 ms delay, to save CPU time.
    end

    %% STOP
    % Stop generator:
    gen.stop();
    % Disable output:
    gen.OutputOn = false;

    %% Read data
    % Get signals received
    signal_rec = scp.getData();

    % If only one channel, store only data of one channel
    if numel(chan) == 1
        signal_rec = signal_rec(:,1);
    end

    % Real sample frequency
    real_fs = scp.SampleFrequency;
    % Real record length
    real_record_length = scp.RecordLength;
    % Time array
    t = (0:real_record_length-1)/real_fs;

    % Release device
    clear scp gen;
else
    error('No oscilloscope available with block measurement support or generator available in the same unit!');
end