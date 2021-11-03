% GeneratorArbitrary.m
%
% This example generates an arbitrary waveform.
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
        if ismember(ST.ARBITRARY, gen.SignalTypes)
            break;
        else
            clear gen;
        end
    end
end
clear item

if exist('gen', 'var')
    % Set signal type:
    gen.SignalType = ST.ARBITRARY;

    % Set frequency mode:
    gen.FrequencyMode = FM.SAMPLEFREQUENCY;

    % Set frequency:
    gen.Frequency = 100e3; % 100 kHz

    % Set amplitude:
    gen.Amplitude = 2; % 2 V

    % Set offset:
    gen.Offset = 0; % 0 V

    % Enable output:
    gen.OutputOn = true;

    % Create arbitrary signal:
    x = 1:8192;
    data = sin(x / 100) .* (1 - (x / 8192));
    clear x;

    % Load the signal into the generator:
    gen.setData(data);

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
    error('No generator available with arbitrary support!');
end
