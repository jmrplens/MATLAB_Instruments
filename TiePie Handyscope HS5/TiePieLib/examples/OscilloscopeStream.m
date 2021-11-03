% OscilloscopeStream.m
%
% This example performs a stream mode measurement and writes the data to OscilloscopeStream.csv.
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

% Try to open an oscilloscope with stream measurement support:
clear scp;
for k = 0 : LibTiePie.DeviceList.Count - 1
    item = LibTiePie.DeviceList.getItemByIndex(k);
    if item.canOpen(DEVICETYPE.OSCILLOSCOPE)
        scp = item.openOscilloscope();
        if ismember(MM.STREAM, scp.MeasureModes)
            break;
        else
            clear scp;
        end
    end
end

if exist('scp', 'var')
    % Set measure mode:
    scp.MeasureMode = MM.STREAM;

    % Set sample frequency:
    scp.SampleFrequency = 1e3; % 1 kHz

    % Set record length:
    scp.RecordLength = 1000; % 1 kS

    % For all channels:
    for ch = scp.Channels
        % Enable channel to measure it:
        ch.Enabled = true;

        % Set range:
        ch.Range = 8; % 8 V

        % Set coupling:
        ch.Coupling = CK.DCV; % DC Volt

        clear ch;
    end

    % Print oscilloscope info:
    display(scp);

    % Prepeare CSV writing:
    filename = 'OscilloscopeStream.csv';
    if exist(filename, 'file')
        delete(filename)
    end
    data = [];

    % Start measurement:
    scp.start();

    % Measure 10 chunks:
    for k = 1 : 10
        % Display a message, to inform the user that we still do something:
        fprintf('Data chunk %u\n', k);

        % Wait for measurement to complete:
        while ~(scp.IsDataReady || scp.IsDataOverflow)
            pause(10e-3) % 10 ms delay, to save CPU time.
        end

        if scp.IsDataOverflow
            error('Data overflow!')
        end

        % Get data:
        newData = scp.getData();

        % Apped new data to plot:
        data = [data ; newData];
        figure(123);
        plot(data);

        % Append new data to CSV file:
        dlmwrite(filename, newData, '-append');
    end

    fprintf('Data written to: %s\n', filename);

    % Stop stream:
    scp.stop();

    % Close oscilloscope:
    clear scp;
else
    error('No oscilloscope available with stream measurement support!');
end
