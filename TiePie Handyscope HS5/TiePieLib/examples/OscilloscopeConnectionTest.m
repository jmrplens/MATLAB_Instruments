% OscilloscopeConnectionTest.m
%
% This example performs a connection test.
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

% Try to open an oscilloscope with connection test support:
clear scp;
for k = 0 : LibTiePie.DeviceList.Count - 1
    item = LibTiePie.DeviceList.getItemByIndex(k);
    if item.canOpen(DEVICETYPE.OSCILLOSCOPE)
        scp = item.openOscilloscope();
        if scp.HasConnectionTest
            break;
        else
            clear scp;
        end
    end
end
clear item

if exist('scp', 'var')
    % Enable all channels that support connection testing:
    for ch = scp.Channels
        ch.Enabled = ch.HasConnectionTest;
    end

    % Print oscilloscope info:
    display(scp);

    % Start connection test:
    scp.startConnectionTest();

    % Wait for connection test to complete:
    while ~scp.IsConnectionTestCompleted
        pause(10e-3); % 10 ms delay, to save CPU time.
    end

    % Print result:
    display('Connection test result:');
    display(scp.getConnectionTestData());

    % Close oscilloscope:
    clear scp;
else
    error('No oscilloscope available with connection test support!');
end
