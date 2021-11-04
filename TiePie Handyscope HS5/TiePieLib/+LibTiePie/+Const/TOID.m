% MatlabLibTiePie - Matlab bindings for LibTiePie library
%
% Copyright (c) 2012-2021 TiePie engineering
%
% Website: http://www.tiepie.com/LibTiePie

classdef TOID
    properties (Constant)
        INVALID = 0
        EXT1 = 3145984
        EXT2 = 3146240
        EXT3 = 3146496
    end
    methods (Static)
        function result = toString(value)
            import LibTiePie.Const.TOID
            switch value
                case TOID.INVALID
                    result = 'INVALID';
                case TOID.EXT1
                    result = 'EXT1';
                case TOID.EXT2
                    result = 'EXT2';
                case TOID.EXT3
                    result = 'EXT3';
                otherwise
                    error('Unknown value');
            end
        end
    end
end
