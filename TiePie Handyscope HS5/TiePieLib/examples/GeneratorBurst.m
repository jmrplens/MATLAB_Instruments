% GeneratorBurst.m
%
% This example generates a 50 Hz sine waveform, 4 Vpp, 100 periods.
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

% Try to open a generator with arbitrary support:
clear gen;
for k = 0 : LibTiePie.DeviceList.Count - 1
    item = LibTiePie.DeviceList.getItemByIndex(k);
    if item.canOpen(DEVICETYPE.GENERATOR)
        gen = item.openGenerator();
        if ismember(GM.BURST_COUNT, gen.ModesNative)
            break;
        else
            clear Gen;
        end
    end
end
clear item

if exist('gen', 'var')
    % Set signal type:
    gen.SignalType = ST.SINE;

    % Set frequency:
    gen.Frequency = 50; % 50 Hz

    % Set amplitude:
    gen.Amplitude = 2; % 2 V

    % Set offset:
    gen.Offset = 0; % 0 V

    % Set mode:
    gen.Mode = GM.BURST_COUNT;

    % Set burst count:
    gen.BurstCount = 100; % 100 periods

    % Enable output:
    gen.OutputOn = true;

    % Print generator info:
    display(gen);

    % Start signal burst:
    gen.start();

    % Wait for burst to complete:
    while gen.IsBurstActive
        pause(10e-3); % 10 ms delay, to save CPU time.
    end

    % Disable output:
    gen.OutputOn = false;

    % Close generator:
    clear gen;
else
    error('No generator available with burst support!');
end
