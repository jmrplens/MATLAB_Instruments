% MatlabLibTiePie - Matlab bindings for LibTiePie library
%
% Copyright (c) 2012-2021 TiePie engineering
%
% Website: http://www.tiepie.com/LibTiePie

classdef I2CHost < LibTiePie.Device
    properties (SetAccess = private)
        InternalAddresses;
        SpeedMax;
    end
    properties
        Speed;
    end
    methods
        function obj = I2CHost(library, handle)
            obj = obj@LibTiePie.Device(library, handle);
        end

        function result = isInternalAddress(self, address)
            result = calllib(self.m_libraryName, 'I2CIsInternalAddress', self.m_handle, address);
            self.m_library.checkLastStatus();
        end

        function read(self, address, buffer, size, stop)
            calllib(self.m_libraryName, 'I2CRead', self.m_handle, address, buffer, size, stop);
            self.m_library.checkLastStatus();
        end

        function value = readByte(self, address)
            [~, value] = calllib(self.m_libraryName, 'I2CReadByte', self.m_handle, address, 0);
            self.m_library.checkLastStatus();
        end

        function value = readWord(self, address)
            [~, value] = calllib(self.m_libraryName, 'I2CReadWord', self.m_handle, address, 0);
            self.m_library.checkLastStatus();
        end

        function write(self, address, buffer, size, stop)
            calllib(self.m_libraryName, 'I2CWrite', self.m_handle, address, buffer, size, stop);
            self.m_library.checkLastStatus();
        end

        function writeByte(self, address, value)
            calllib(self.m_libraryName, 'I2CWriteByte', self.m_handle, address, value);
            self.m_library.checkLastStatus();
        end

        function writeByteByte(self, address, value1, value2)
            calllib(self.m_libraryName, 'I2CWriteByteByte', self.m_handle, address, value1, value2);
            self.m_library.checkLastStatus();
        end

        function writeByteWord(self, address, value1, value2)
            calllib(self.m_libraryName, 'I2CWriteByteWord', self.m_handle, address, value1, value2);
            self.m_library.checkLastStatus();
        end

        function writeWord(self, address, value)
            calllib(self.m_libraryName, 'I2CWriteWord', self.m_handle, address, value);
            self.m_library.checkLastStatus();
        end

        function writeRead(self, address, writeBuffer, writeSize, readBuffer, readSize)
            calllib(self.m_libraryName, 'I2CWriteRead', self.m_handle, address, writeBuffer, writeSize, readBuffer, readSize);
            self.m_library.checkLastStatus();
        end

        function result = verifySpeed(self, speed)
            result = calllib(self.m_libraryName, 'I2CVerifySpeed', self.m_handle, speed);
            self.m_library.checkLastStatus();
        end
    end
    methods
        function value = get.InternalAddresses(self)
            length = calllib(self.m_libraryName, 'I2CGetInternalAddresses', self.m_handle, [], 0);
            self.m_library.checkLastStatus();
            [~, value] = calllib(self.m_libraryName, 'I2CGetInternalAddresses', self.m_handle, zeros(length, 1), length);
            self.m_library.checkLastStatus();
        end

        function value = get.SpeedMax(self)
            value = calllib(self.m_libraryName, 'I2CGetSpeedMax', self.m_handle);
            self.m_library.checkLastStatus();
        end

        function value = get.Speed(self)
            value = calllib(self.m_libraryName, 'I2CGetSpeed', self.m_handle);
            self.m_library.checkLastStatus();
        end

        function set.Speed(self, value)
            calllib(self.m_libraryName, 'I2CSetSpeed', self.m_handle, value);
            self.m_library.checkLastStatus();
        end
    end
end
