% MatlabLibTiePie - Matlab bindings for LibTiePie library
%
% Copyright (c) 2012-2021 TiePie engineering
%
% Website: http://www.tiepie.com/LibTiePie

classdef Network < handle
    properties (GetAccess = protected, SetAccess = private)
        m_library;
        m_libraryName;
    end
    properties (SetAccess = private)
        Servers;
    end
    properties
        AutoDetectEnabled;
    end
    methods
        function obj = Network(library)
            obj.m_library = library;
            obj.m_libraryName = library.Name;
            obj.Servers = LibTiePie.NetworkServers(library);
        end
    end
    methods
        function value = get.AutoDetectEnabled(self)
            value = calllib(self.m_libraryName, 'NetGetAutoDetectEnabled');
            self.m_library.checkLastStatus();
        end

        function set.AutoDetectEnabled(self, value)
            calllib(self.m_libraryName, 'NetSetAutoDetectEnabled', value);
            self.m_library.checkLastStatus();
        end
    end
end
