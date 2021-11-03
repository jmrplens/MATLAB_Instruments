% MatlabLibTiePie - Matlab bindings for LibTiePie library
%
% Copyright (c) 2012-2021 TiePie engineering
%
% Website: http://www.tiepie.com/LibTiePie


classdef OscilloscopeChannelTriggerLevels < handle
    properties (GetAccess = protected, SetAccess = private)
        m_library;
        m_libraryName;
        m_handle;
        m_ch;
    end
    properties (SetAccess = private)
        Count;
    end
    methods
        function obj = OscilloscopeChannelTriggerLevels(library, handle, ch)
            obj.m_library = library;
            obj.m_libraryName = library.Name;
            obj.m_handle = handle;
            obj.m_ch = ch;
        end

        function value = subsref(self, S)
            switch S(1).type
                case '()'
                    index = S(1).subs{1};
                    value = calllib(self.m_libraryName, 'ScpChTrGetLevel', self.m_handle, self.m_ch, index - 1);
                    self.m_library.checkLastStatus();
                otherwise
                    value = builtin('subsref', self, S);
            end
        end

        function obj = subsasgn(self, S, value)
            switch S(1).type
                case '()'
                    obj = self;
                    index = S(1).subs{1};
                    calllib(self.m_libraryName, 'ScpChTrSetLevel', self.m_handle, self.m_ch, index - 1, value);
                    self.m_library.checkLastStatus();
                otherwise
                    obj = builtin('subsasgn', self, S, value);
            end
        end

    end
    methods
        function value = get.Count(self)
            value = calllib(self.m_libraryName, 'ScpChTrGetLevelCount', self.m_handle, self.m_ch);
            self.m_library.checkLastStatus();
        end
    end
end
