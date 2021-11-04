% MatlabLibTiePie - Matlab bindings for LibTiePie library
%
% Copyright (c) 2012-2021 TiePie engineering
%
% Website: http://www.tiepie.com/LibTiePie

classdef Server < LibTiePie.Object
    properties (SetAccess = private)
        Status;
        LastError;
        URL;
        ID;
        IPv4Address;
        IPPort;
        Name;
        Description;
        Version;
        VersionString;
        VersionExtra;
    end
    methods
        function obj = Server(library, handle)
            obj = obj@LibTiePie.Object(library, handle);
        end

        function result = connect(self, async)
            result = calllib(self.m_libraryName, 'SrvConnect', self.m_handle, async);
            self.m_library.checkLastStatus();
        end

        function result = disconnect(self, force)
            result = calllib(self.m_libraryName, 'SrvDisconnect', self.m_handle, force);
            self.m_library.checkLastStatus();
        end

        function result = remove(self, force)
            result = calllib(self.m_libraryName, 'SrvRemove', self.m_handle, force);
            self.m_library.checkLastStatus();
        end
    end
    methods
        function value = get.Status(self)
            value = calllib(self.m_libraryName, 'SrvGetStatus', self.m_handle);
            self.m_library.checkLastStatus();
            value = LibTiePie.BitMask2Array(value);
                value = LibTiePie.Enum.GS(value);
        end

        function value = get.LastError(self)
            value = calllib(self.m_libraryName, 'SrvGetLastError', self.m_handle);
            self.m_library.checkLastStatus();
        end

        function value = get.URL(self)
            length = calllib(self.m_libraryName, 'SrvGetURL', self.m_handle, [], 0);
            self.m_library.checkLastStatus();
            [~, value] = calllib(self.m_libraryName, 'SrvGetURL', self.m_handle, blanks(length), length);
            self.m_library.checkLastStatus();
            value = native2unicode(uint8(value), 'UTF-8');
        end

        function value = get.ID(self)
            length = calllib(self.m_libraryName, 'SrvGetID', self.m_handle, [], 0);
            self.m_library.checkLastStatus();
            [~, value] = calllib(self.m_libraryName, 'SrvGetID', self.m_handle, blanks(length), length);
            self.m_library.checkLastStatus();
            value = native2unicode(uint8(value), 'UTF-8');
        end

        function value = get.IPv4Address(self)
            value = calllib(self.m_libraryName, 'SrvGetIPv4Address', self.m_handle);
            self.m_library.checkLastStatus();
        end

        function value = get.IPPort(self)
            value = calllib(self.m_libraryName, 'SrvGetIPPort', self.m_handle);
            self.m_library.checkLastStatus();
        end

        function value = get.Name(self)
            length = calllib(self.m_libraryName, 'SrvGetName', self.m_handle, [], 0);
            self.m_library.checkLastStatus();
            [~, value] = calllib(self.m_libraryName, 'SrvGetName', self.m_handle, blanks(length), length);
            self.m_library.checkLastStatus();
            value = native2unicode(uint8(value), 'UTF-8');
        end

        function value = get.Description(self)
            length = calllib(self.m_libraryName, 'SrvGetDescription', self.m_handle, [], 0);
            self.m_library.checkLastStatus();
            [~, value] = calllib(self.m_libraryName, 'SrvGetDescription', self.m_handle, blanks(length), length);
            self.m_library.checkLastStatus();
            value = native2unicode(uint8(value), 'UTF-8');
        end

        function value = get.Version(self)
            value = calllib(self.m_libraryName, 'SrvGetVersion', self.m_handle);
            self.m_library.checkLastStatus();
        end

        function value = get.VersionString(self)
            value = LibTiePie.VersionNumber2String(self.Version);
        end

        function value = get.VersionExtra(self)
            length = calllib(self.m_libraryName, 'SrvGetVersionExtra', self.m_handle, [], 0);
            self.m_library.checkLastStatus();
            [~, value] = calllib(self.m_libraryName, 'SrvGetVersionExtra', self.m_handle, blanks(length), length);
            self.m_library.checkLastStatus();
            value = native2unicode(uint8(value), 'UTF-8');
        end
    end
end
