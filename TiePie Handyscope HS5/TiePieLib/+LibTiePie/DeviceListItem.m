% MatlabLibTiePie - Matlab bindings for LibTiePie library
%
% Copyright (c) 2012-2021 TiePie engineering
%
% Website: http://www.tiepie.com/LibTiePie

classdef DeviceListItem < handle
    properties (GetAccess = protected, SetAccess = private)
        m_library;
        m_libraryName;
        m_serialNumber;
    end
    properties (SetAccess = private)
        ProductId;
        VendorId;
        Name;
        NameShort;
        NameShortest;
        DriverVersion;
        DriverVersionString;
        RecommendedDriverVersion;
        RecommendedDriverVersionString;
        FirmwareVersion;
        FirmwareVersionString;
        RecommendedFirmwareVersion;
        RecommendedFirmwareVersionString;
        CalibrationDate;
        SerialNumber;
        IPv4Address;
        IPPort;
        HasServer;
        Server;
        Types;
        ContainedSerialNumbers;
    end
    methods
        function obj = DeviceListItem(library, serialNumber)
            obj.m_library = library;
            obj.m_libraryName = library.Name;
            obj.m_serialNumber = serialNumber;
        end

        function result = openDevice(self, deviceType)
            switch deviceType
                case LibTiePie.Enum.DEVICETYPE.OSCILLOSCOPE
                    result = self.openOscilloscope();
                case LibTiePie.Enum.DEVICETYPE.GENERATOR
                    result = self.openGenerator();
                case LibTiePie.Enum.DEVICETYPE.I2CHOST
                    result = self.openI2CHost();
                otherwise
                    error('Unsupported device type.');
            end
        end

        function result = openOscilloscope(self)
            handle = calllib(self.m_libraryName, 'LstOpenOscilloscope', uint32(LibTiePie.Enum.IDKIND.SERIALNUMBER), self.m_serialNumber);
            self.m_library.checkLastStatus();
            result = LibTiePie.Oscilloscope(self.m_library, handle);
        end

        function result = openGenerator(self)
            handle = calllib(self.m_libraryName, 'LstOpenGenerator', uint32(LibTiePie.Enum.IDKIND.SERIALNUMBER), self.m_serialNumber);
            self.m_library.checkLastStatus();
            result = LibTiePie.Generator(self.m_library, handle);
        end

        function result = openI2CHost(self)
            handle = calllib(self.m_libraryName, 'LstOpenI2CHost', uint32(LibTiePie.Enum.IDKIND.SERIALNUMBER), self.m_serialNumber);
            self.m_library.checkLastStatus();
            result = LibTiePie.I2CHost(self.m_library, handle);
        end

        function result = canOpen(self, deviceType)
            result = calllib(self.m_libraryName, 'LstDevCanOpen', uint32(LibTiePie.Enum.IDKIND.SERIALNUMBER), self.m_serialNumber, uint32(deviceType));
            self.m_library.checkLastStatus();
        end
    end
    methods
        function value = get.ProductId(self)
            value = calllib(self.m_libraryName, 'LstDevGetProductId', uint32(LibTiePie.Enum.IDKIND.SERIALNUMBER), self.m_serialNumber);
            self.m_library.checkLastStatus();
        end

        function value = get.VendorId(self)
            value = calllib(self.m_libraryName, 'LstDevGetVendorId', uint32(LibTiePie.Enum.IDKIND.SERIALNUMBER), self.m_serialNumber);
            self.m_library.checkLastStatus();
        end

        function value = get.Name(self)
            length = calllib(self.m_libraryName, 'LstDevGetName', uint32(LibTiePie.Enum.IDKIND.SERIALNUMBER), self.m_serialNumber, [], 0);
            self.m_library.checkLastStatus();
            [~, value] = calllib(self.m_libraryName, 'LstDevGetName', uint32(LibTiePie.Enum.IDKIND.SERIALNUMBER), self.m_serialNumber, blanks(length), length);
            self.m_library.checkLastStatus();
            value = native2unicode(uint8(value), 'UTF-8');
        end

        function value = get.NameShort(self)
            length = calllib(self.m_libraryName, 'LstDevGetNameShort', uint32(LibTiePie.Enum.IDKIND.SERIALNUMBER), self.m_serialNumber, [], 0);
            self.m_library.checkLastStatus();
            [~, value] = calllib(self.m_libraryName, 'LstDevGetNameShort', uint32(LibTiePie.Enum.IDKIND.SERIALNUMBER), self.m_serialNumber, blanks(length), length);
            self.m_library.checkLastStatus();
            value = native2unicode(uint8(value), 'UTF-8');
        end

        function value = get.NameShortest(self)
            length = calllib(self.m_libraryName, 'LstDevGetNameShortest', uint32(LibTiePie.Enum.IDKIND.SERIALNUMBER), self.m_serialNumber, [], 0);
            self.m_library.checkLastStatus();
            [~, value] = calllib(self.m_libraryName, 'LstDevGetNameShortest', uint32(LibTiePie.Enum.IDKIND.SERIALNUMBER), self.m_serialNumber, blanks(length), length);
            self.m_library.checkLastStatus();
            value = native2unicode(uint8(value), 'UTF-8');
        end

        function value = get.DriverVersion(self)
            value = calllib(self.m_libraryName, 'LstDevGetDriverVersion', uint32(LibTiePie.Enum.IDKIND.SERIALNUMBER), self.m_serialNumber);
            self.m_library.checkLastStatus();
        end

        function value = get.DriverVersionString(self)
            value = LibTiePie.VersionNumber2String(self.DriverVersion);
        end

        function value = get.RecommendedDriverVersion(self)
            value = calllib(self.m_libraryName, 'LstDevGetRecommendedDriverVersion', uint32(LibTiePie.Enum.IDKIND.SERIALNUMBER), self.m_serialNumber);
            self.m_library.checkLastStatus();
        end

        function value = get.RecommendedDriverVersionString(self)
            value = LibTiePie.VersionNumber2String(self.RecommendedDriverVersion);
        end

        function value = get.FirmwareVersion(self)
            value = calllib(self.m_libraryName, 'LstDevGetFirmwareVersion', uint32(LibTiePie.Enum.IDKIND.SERIALNUMBER), self.m_serialNumber);
            self.m_library.checkLastStatus();
        end

        function value = get.FirmwareVersionString(self)
            value = LibTiePie.VersionNumber2String(self.FirmwareVersion);
        end

        function value = get.RecommendedFirmwareVersion(self)
            value = calllib(self.m_libraryName, 'LstDevGetRecommendedFirmwareVersion', uint32(LibTiePie.Enum.IDKIND.SERIALNUMBER), self.m_serialNumber);
            self.m_library.checkLastStatus();
        end

        function value = get.RecommendedFirmwareVersionString(self)
            value = LibTiePie.VersionNumber2String(self.RecommendedFirmwareVersion);
        end

        function value = get.CalibrationDate(self)
            value = calllib(self.m_libraryName, 'LstDevGetCalibrationDate', uint32(LibTiePie.Enum.IDKIND.SERIALNUMBER), self.m_serialNumber);
            self.m_library.checkLastStatus();
        end

        function value = get.SerialNumber(self)
            value = calllib(self.m_libraryName, 'LstDevGetSerialNumber', uint32(LibTiePie.Enum.IDKIND.SERIALNUMBER), self.m_serialNumber);
            self.m_library.checkLastStatus();
        end

        function value = get.IPv4Address(self)
            value = calllib(self.m_libraryName, 'LstDevGetIPv4Address', uint32(LibTiePie.Enum.IDKIND.SERIALNUMBER), self.m_serialNumber);
            self.m_library.checkLastStatus();
        end

        function value = get.IPPort(self)
            value = calllib(self.m_libraryName, 'LstDevGetIPPort', uint32(LibTiePie.Enum.IDKIND.SERIALNUMBER), self.m_serialNumber);
            self.m_library.checkLastStatus();
        end

        function value = get.HasServer(self)
            value = calllib(self.m_libraryName, 'LstDevHasServer', uint32(LibTiePie.Enum.IDKIND.SERIALNUMBER), self.m_serialNumber);
            self.m_library.checkLastStatus();
        end

        function value = get.Server(self)
            handle = calllib(self.m_libraryName, 'LstDevGetServer', uint32(LibTiePie.Enum.IDKIND.SERIALNUMBER), self.m_serialNumber);
            self.m_library.checkLastStatus();
            value = LibTiePie.Server(self.m_library, handle);
        end

        function value = get.Types(self)
            value = calllib(self.m_libraryName, 'LstDevGetTypes', uint32(LibTiePie.Enum.IDKIND.SERIALNUMBER), self.m_serialNumber);
            self.m_library.checkLastStatus();
            value = LibTiePie.BitMask2Array(value);
                value = LibTiePie.Enum.DEVICETYPE(value);
        end

        function value = get.ContainedSerialNumbers(self)
            length = calllib(self.m_libraryName, 'LstDevGetContainedSerialNumbers', uint32(LibTiePie.Enum.IDKIND.SERIALNUMBER), self.m_serialNumber, [], 0);
            self.m_library.checkLastStatus();
            [~, value] = calllib(self.m_libraryName, 'LstDevGetContainedSerialNumbers', uint32(LibTiePie.Enum.IDKIND.SERIALNUMBER), self.m_serialNumber, zeros(length, 1), length);
            self.m_library.checkLastStatus();
        end
    end
end
