% OscilloscopeCombineHS3HS4.m
%
% This example demonstrates how to create and open a combined instrument of all found Handyscope HS3, Handyscope HS4 and/or Handyscope HS4 DIFF's.
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

% Update device list:
LibTiePie.DeviceList.update();

% Try to open all HS3/HS4(D) oscilloscopes:
allowedProductIDs = [PID.HS3, PID.HS4, PID.HS4D];
import LibTiePie.Oscilloscope;
scps = Oscilloscope.empty;

for k = 0 : LibTiePie.DeviceList.Count - 1
    item = LibTiePie.DeviceList.getItemByIndex(k);
    if ismember(item.ProductId, allowedProductIDs) && item.canOpen(DEVICETYPE.OSCILLOSCOPE)
        scps(end + 1) = item.openOscilloscope();
        fprintf('Found: %s, s/n: %u\n', item.Name, item.SerialNumber);
    end
end
clear item

if length(scps) > 1
    % Create and open combined instrument:
    scp = LibTiePie.DeviceList.createAndOpenCombinedDevice(scps);

    % Remove HS3/HS4(D) objects, not required anymore:
    clear scps;

    % Print combined oscilloscope info:
    display(scp);

    % Get serial number, required for removing:
    serialNumber = scp.SerialNumber;

    % Close combined oscilloscope:
    clear scp;

    % Remove combined oscilloscope from the device list:
    LibTiePie.DeviceList.removeDevice(serialNumber);
else
    clear scps;
    error('Not enough HS3/HS4(D)''s found, at least two required!');
end
