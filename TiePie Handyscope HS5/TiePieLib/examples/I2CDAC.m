% I2CDAC.m
%
% This example demonstrates how to use an I2C host supported by LibTiePie.
% It shows how to control an Analog Devices AD5667 dual 16-bit DAC.
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

% Try to open an I2C host:
clear i2c;
for k = 0 : LibTiePie.DeviceList.Count - 1
    item = LibTiePie.DeviceList.getItemByIndex(k);
    if item.canOpen(DEVICETYPE.I2CHOST)
        i2c = item.openI2CHost();
        break;
    end
end
clear item

if exist('i2c', 'var')
    % Print I2C host info:
    display(i2c);

    % Turn on internal reference:
    i2c.writeByteWord(12, 56, 1);

    % Set DAC to mid level:
    i2c.writeByteWord(12, 24, 32768);

    % Close I2C host:
    clear i2c;
else
    error('No I2C host available!');
end
