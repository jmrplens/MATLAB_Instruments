% MatlabLibTiePie - Matlab bindings for LibTiePie library
%
% Copyright (c) 2012-2021 TiePie engineering
%
% Website: http://www.tiepie.com/LibTiePie

classdef TIID
    properties (Constant)
        INVALID = 0
        EXT1 = 3145984
        EXT2 = 3146240
        EXT3 = 3146496
        GENERATOR_START = 2097152
        GENERATOR_STOP = 2097153
        GENERATOR_NEW_PERIOD = 2097154
    end
    methods (Static)
        function result = toString(value)
            import LibTiePie.Const.TIID
            switch value
                case TIID.INVALID
                    result = 'INVALID';
                case TIID.EXT1
                    result = 'EXT1';
                case TIID.EXT2
                    result = 'EXT2';
                case TIID.EXT3
                    result = 'EXT3';
                case TIID.GENERATOR_START
                    result = 'GENERATOR_START';
                case TIID.GENERATOR_STOP
                    result = 'GENERATOR_STOP';
                case TIID.GENERATOR_NEW_PERIOD
                    result = 'GENERATOR_NEW_PERIOD';
                otherwise
                    error('Unknown value');
            end
        end
    end
end
