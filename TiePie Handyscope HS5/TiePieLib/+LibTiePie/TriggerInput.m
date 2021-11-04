% MatlabLibTiePie - Matlab bindings for LibTiePie library
%
% Copyright (c) 2012-2021 TiePie engineering
%
% Website: http://www.tiepie.com/LibTiePie

classdef TriggerInput < handle
    properties (GetAccess = protected, SetAccess = private)
        m_library;
        m_libraryName;
        m_handle;
        m_index;
    end
    properties (SetAccess = private)
        IsTriggered;
        Kinds;
        IsAvailable;
        Id;
        Name;
    end
    properties
        Enabled;
        Kind;
    end
    methods
        function obj = TriggerInput(library, handle, index)
            obj.m_library = library;
            obj.m_libraryName = library.Name;
            obj.m_handle = handle;
            obj.m_index = index;
          end
    end
    methods
        function value = get.IsTriggered(self)
            value = calllib(self.m_libraryName, 'ScpTrInIsTriggered', self.m_handle, self.m_index);
            self.m_library.checkLastStatus();
        end

        function value = get.Enabled(self)
            value = calllib(self.m_libraryName, 'DevTrInGetEnabled', self.m_handle, self.m_index);
            self.m_library.checkLastStatus();
        end

        function set.Enabled(self, value)
            calllib(self.m_libraryName, 'DevTrInSetEnabled', self.m_handle, self.m_index, value);
            self.m_library.checkLastStatus();
        end

        function value = get.Kinds(self)
            value = calllib(self.m_libraryName, 'DevTrInGetKinds', self.m_handle, self.m_index);
            self.m_library.checkLastStatus();
            value = LibTiePie.BitMask2Array(value);
                value = LibTiePie.Enum.TK(value);
        end

        function value = get.Kind(self)
            value = calllib(self.m_libraryName, 'DevTrInGetKind', self.m_handle, self.m_index);
            self.m_library.checkLastStatus();
                value = LibTiePie.Enum.TK(value);
        end

        function set.Kind(self, value)
            calllib(self.m_libraryName, 'DevTrInSetKind', self.m_handle, self.m_index, uint64(value));
            self.m_library.checkLastStatus();
        end

        function value = get.IsAvailable(self)
            value = calllib(self.m_libraryName, 'DevTrInIsAvailable', self.m_handle, self.m_index);
            self.m_library.checkLastStatus();
        end

        function value = get.Id(self)
            value = calllib(self.m_libraryName, 'DevTrInGetId', self.m_handle, self.m_index);
            self.m_library.checkLastStatus();
        end

        function value = get.Name(self)
            length = calllib(self.m_libraryName, 'DevTrInGetName', self.m_handle, self.m_index, [], 0);
            self.m_library.checkLastStatus();
            [~, value] = calllib(self.m_libraryName, 'DevTrInGetName', self.m_handle, self.m_index, blanks(length), length);
            self.m_library.checkLastStatus();
            value = native2unicode(uint8(value), 'UTF-8');
        end
    end
end
