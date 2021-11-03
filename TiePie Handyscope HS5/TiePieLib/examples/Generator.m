% Generator.m
%
% This example generates a 100 kHz triangle waveform, 4 Vpp.
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

% Try to open a generator:
clear gen;
for k = 0 : LibTiePie.DeviceList.Count - 1
    item = LibTiePie.DeviceList.getItemByIndex(k);
    if item.canOpen(DEVICETYPE.GENERATOR)
        gen = item.openGenerator();
        break;
    end
end
clear item

if exist('gen', 'var')
    % Set signal type:
    gen.SignalType = ST.TRIANGLE;

    % Set frequency:
    gen.Frequency = 100e3; % 100 kHz

    % Set amplitude:
    gen.Amplitude = 2; % 2 V

    % Set offset:
    gen.Offset = 0; % 0 V

    % Enable output:
    gen.OutputOn = true;

    % Print generator info:
    display(gen);

    % Start signal generation:
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
    error('No generator available!');
end
