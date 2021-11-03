% GeneratorTriggeredBurst.m
%
% This example generates a 100 kHz square waveform, 25% duty cycle, 0..5 V, 20 periods, this waveform is triggered by the external trigger.
% Connect the external trigger to GND to trigger the burst.
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

% Update device list:
LibTiePie.DeviceList.update();

% Try to open a generator with triggered burst support:
clear gen;
for k = 0 : LibTiePie.DeviceList.Count - 1
    item = LibTiePie.DeviceList.getItemByIndex(k);
    if item.canOpen(DEVICETYPE.GENERATOR)
        gen = item.openGenerator();
        if ismember(GM.BURST_COUNT, gen.ModesNative) && ~isempty(gen.TriggerInputs)
            break;
        else
            clear gen;
        end
    end
end
clear item

if exist('gen', 'var')
    % Set signal type:
    gen.SignalType = ST.SQUARE;

    % Set frequency:
    gen.Frequency = 100e3; % 100 kHz

    % Set symmetry (duty cycle):
    gen.Symmetry = 0.25; % 25 %

    % Set amplitude:
    gen.Amplitude = 5; % 5 V

    % Set offset:
    gen.Offset = 0; % 0 V

    % Set mode:
    gen.Mode = GM.BURST_COUNT;

    % Set burst count:
    gen.BurstCount = 20; % 20 periods

    % Locate trigger input:
    triggerInput = gen.getTriggerInputById(TIID.EXT1); % EXT 1

    if triggerInput == false
        triggerInput = gen.getTriggerInputById(TIID.EXT2); % EXT 2
    end

    if triggerInput == false
        clear triggerInput;
        clear gen;
        error('Unknown trigger input!');
    end

    % Enable trigger input:
    triggerInput.Enabled = true;

    % Set trigger input kind:
    triggerInput.Kind = TK.FALLINGEDGE;

    % Release reference to trigger input:
    clear triggerInput;

    % Enable output:
    gen.OutputOn = true;

    % Print generator info:
    display(gen)

    % Start triggered burst:
    gen.start();

    % Wait for keystroke:
    display('Press any key to stop signal generation...');
    waitforbuttonpress;

    % Stop generator:
    gen.stop();

    % Disable output:
    gen.OutputOn = false;

    % Close generator:
    clear gen;
else
    error('No generator available with triggered burst support!');
end
