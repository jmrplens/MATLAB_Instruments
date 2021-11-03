% MatlabLibTiePie - Matlab bindings for LibTiePie library
%
% Copyright (c) 2012-2021 TiePie engineering
%
% Website: http://www.tiepie.com/LibTiePie

classdef Object < handle
    properties (GetAccess = protected, SetAccess = private)
        m_library;
        m_libraryName;
        m_handle;
    end
    properties (SetAccess = private)
        IsRemoved;
        Interfaces;
    end
    methods
        function obj = Object(library, handle)
            obj.m_library = library;
            obj.m_libraryName = library.Name;
            obj.m_handle = handle;
          end

        function delete(self)
            calllib(self.m_libraryName, 'ObjClose', self.m_handle);
            self.m_library = 0; % Release reference.
        end

        function result = getEvent(self, event, value)
            result = calllib(self.m_libraryName, 'ObjGetEvent', self.m_handle, event, value);
            self.m_library.checkLastStatus();
        end
    end
    methods
        function value = get.IsRemoved(self)
            value = calllib(self.m_libraryName, 'ObjIsRemoved', self.m_handle);
            self.m_library.checkLastStatus();
        end

        function value = get.Interfaces(self)
            value = calllib(self.m_libraryName, 'ObjGetInterfaces', self.m_handle);
            self.m_library.checkLastStatus();
        end
    end
end
