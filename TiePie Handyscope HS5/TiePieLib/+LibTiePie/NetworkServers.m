% MatlabLibTiePie - Matlab bindings for LibTiePie library
%
% Copyright (c) 2012-2021 TiePie engineering
%
% Website: http://www.tiepie.com/LibTiePie

classdef NetworkServers < handle
    properties (GetAccess = protected, SetAccess = private)
        m_library;
        m_libraryName;
    end
    properties (SetAccess = private)
        Count;
    end
    methods
        function obj = NetworkServers(library)
            obj.m_library = library;
            obj.m_libraryName = library.Name;
        end

        function server = add(self, url)
            [~, handle] = calllib(self.m_libraryName, 'NetSrvAdd', url, strlength(url), 0);
            self.m_library.checkLastStatus();
            if handle ~= 0
                server = LibTiePie.Server(self.m_library, handle);
            else
                server = false;
            end
        end

        function result = remove(self, url, force)
            result = calllib(self.m_libraryName, 'NetSrvRemove', url, strlength(url), force);
            self.m_library.checkLastStatus();
        end

        function result = getByIndex(self, index)
            result = calllib(self.m_libraryName, 'NetSrvGetByIndex', index);
            self.m_library.checkLastStatus();
        end

        function result = getByURL(self, uRL, uRLLength)
            result = calllib(self.m_libraryName, 'NetSrvGetByURL', uRL, uRLLength);
            self.m_library.checkLastStatus();
        end
    end
    methods
        function value = get.Count(self)
            value = calllib(self.m_libraryName, 'NetSrvGetCount');
            self.m_library.checkLastStatus();
        end
    end
end
