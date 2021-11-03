% OscilloscopeGeneratorTrigger.m
%
% This example sets up the generator to generate a 1 kHz triangle waveform, 4 Vpp.
% It also sets up the oscilloscope to perform a block mode measurement, triggered on "Generator new period".
% A measurement is performed and the data is plotted.
%
% Find more information on http://www.tiepie.com/LibTiePie .

if verLessThan('matlab', '8')
    error('Matlab 8.0 (R2012b) or higher is required.');
end

% Open LibTiePie and display library info if not yet opened:
import LibTiePie.Const.*
import LibTiePie.Enum.*

if ~exist('LibTiePie', 'var')
    % Open LibTiePie:
    LibTiePie = LibTiePie.Library
end

% Enable network search:       
LibTiePie.Network.AutoDetectEnabled = true;

% Search for devices:
LibTiePie.DeviceList.update();

% Try to open an oscilloscope with block measurement support and a generator in the same device:
clear scp;
clear gen;
for k = 0 : LibTiePie.DeviceList.Count - 1
    item = LibTiePie.DeviceList.getItemByIndex(k);
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

if exist('scp', 'var') && exist('gen', 'var')
    % Oscilloscope settings:

    % Set measure mode:
    scp.MeasureMode = MM.BLOCK;

    % Set sample frequency:
    scp.SampleFrequency = 1e6; % 1 MHz

    % Set record length:
    scp.RecordLength = 10000; % 10000 Samples

    % Set pre sample ratio:
    scp.PreSampleRatio = 0; % 0 %

    % For all channels:
    for ch = scp.Channels
        % Enable channel to measure it:
        ch.Enabled = true;

        % Set range:
        ch.Range = 8; % 8 V

        % Set coupling:
        ch.Coupling = CK.DCV; % DC Volt

        % Release reference:
        clear ch;
    end

    % Set trigger timeout:
    scp.TriggerTimeOut = 1; % 1 s

    % Disable all channel trigger sources:
    for ch = scp.Channels
        ch.Trigger.Enabled = false;
        clear ch;
    end

    % Locate trigger input:
    triggerInput = scp.getTriggerInputById(TIID.GENERATOR_NEW_PERIOD); % or TIID.GENERATOR_START or TIID.GENERATOR_STOP

    if triggerInput == false
        clear triggerInput;
        clear scp;
        clear gen;
        error('Unknown trigger input!');
    end

    % Enable trigger input:
    triggerInput.Enabled = true;

    % Release reference to trigger input:
    clear triggerInput;

    % Generator settings:

    % Set signal type:
    gen.SignalType = ST.TRIANGLE;

    % Set frequency:
    gen.Frequency = 1e3; % 1 kHz

    % Set amplitude:
    gen.Amplitude = 2; % 2 V

    % Set offset:
    gen.Offset = 0; % 0 V

    % Enable output:
    gen.OutputOn = true;

    % Print oscilloscope info:
    display(scp);

    % Print generator info:
    display(gen);

    % Start measurement:
    scp.start();

    % Start signal generation:
    gen.start();

    % Wait for measurement to complete:
    while ~scp.IsDataReady
        pause(10e-3) % 10 ms delay, to save CPU time.
    end

    % Stop generator:
    gen.stop();

    % Disable output:
    gen.OutputOn = false;

    % Get data:
    arData = scp.getData();

    % Get all channel data value ranges (which are compensated for probe gain/offset):
    clear darRangeMin;
    clear darRangeMax;
    for i = 1 : length(scp.Channels)
        [darRangeMin(i), darRangeMax(i)] = scp.Channels(i).getDataValueRange();
    end

    % Plot results:
    figure(500);
    plot((1:scp.RecordLength) / scp.SampleFrequency, arData);
    axis([0 (scp.RecordLength / scp.SampleFrequency) min(darRangeMin) max(darRangeMax)]);
    xlabel('Time [s]');
    ylabel('Amplitude [V]');

    % Close oscilloscope:
    clear scp;

    % Close generator:
    clear gen;
else
    error('No oscilloscope available with block measurement support or generator available in the same unit!');
end
