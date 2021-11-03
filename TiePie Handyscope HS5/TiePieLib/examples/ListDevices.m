% ListDevices.m
%
% This example prints all the available devices to the screen.
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

% Get the number of connected devices:
numDevices = LibTiePie.DeviceList.Count;

if numDevices > 0
    fprintf('Available devices:\n');

    for k = 0 : numDevices - 1
        item = LibTiePie.DeviceList.getItemByIndex(k);

        fprintf('  Name: %s\n', item.Name);
        fprintf('    Serial Number  : %u\n', item.SerialNumber);
        fprintf('    Available types: %s\n', ArrayToString(item.Types));
        if item.HasServer
            server = item.Server
            fprintf('    Server         : %s (%s)', server.URL, server.Name);
            clear server
        end
        clear item;
    end
else
    fprintf('No devices found!\n')
end
