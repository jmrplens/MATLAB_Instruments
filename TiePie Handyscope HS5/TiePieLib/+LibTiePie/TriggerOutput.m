% MatlabLibTiePie - Matlab bindings for LibTiePie library
%
% Copyright (c) 2012-2021 TiePie engineering
%
% Website: http://www.tiepie.com/LibTiePie

classdef TriggerOutput < handle
    properties (GetAccess = protected, SetAccess = private)
        m_library;
        m_libraryName;
        m_handle;
        m_index;
    end
    properties (SetAccess = private)
        Events;
        Id;
        Name;
    end
    properties
        Enabled;
        Event;
    end
    methods
        function obj = TriggerOutput(library, handle, index)
            obj.m_library = library;
            obj.m_libraryName = library.Name;
            obj.m_handle = handle;
            obj.m_index = index;
        end

        function result = trigger(self)
            result = calllib(self.m_libraryName, 'DevTrOutTrigger', self.m_handle, self.m_index);
            self.m_library.checkLastStatus();
        end
    end
    methods
        function value = get.Enabled(self)
            value = calllib(self.m_libraryName, 'DevTrOutGetEnabled', self.m_handle, self.m_index);
            self.m_library.checkLastStatus();
        end

        function set.Enabled(self, value)
            calllib(self.m_libraryName, 'DevTrOutSetEnabled', self.m_handle, self.m_index, value);
            self.m_library.checkLastStatus();
        end

        function value = get.Events(self)
            value = calllib(self.m_libraryName, 'DevTrOutGetEvents', self.m_handle, self.m_index);
            self.m_library.checkLastStatus();
            value = LibTiePie.BitMask2Array(value);
                value = LibTiePie.Enum.TOE(value);
        end

        function value = get.Event(self)
            value = calllib(self.m_libraryName, 'DevTrOutGetEvent', self.m_handle, self.m_index);
            self.m_library.checkLastStatus();
                value = LibTiePie.Enum.TOE(value);
        end

        function set.Event(self, value)
            calllib(self.m_libraryName, 'DevTrOutSetEvent', self.m_handle, self.m_index, uint64(value));
            self.m_library.checkLastStatus();
        end

        function value = get.Id(self)
            value = calllib(self.m_libraryName, 'DevTrOutGetId', self.m_handle, self.m_index);
            self.m_library.checkLastStatus();
        end

        function value = get.Name(self)
            length = calllib(self.m_libraryName, 'DevTrOutGetName', self.m_handle, self.m_index, [], 0);
            self.m_library.checkLastStatus();
            [~, value] = calllib(self.m_libraryName, 'DevTrOutGetName', self.m_handle, self.m_index, blanks(length), length);
            self.m_library.checkLastStatus();
            value = native2unicode(uint8(value), 'UTF-8');
        end
    end
end
