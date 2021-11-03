% MatlabLibTiePie - Matlab bindings for LibTiePie library
%
% Copyright (c) 2012-2021 TiePie engineering
%
% Website: http://www.tiepie.com/LibTiePie

classdef TH
    properties (Constant)
        ALLPRESAMPLES = intmax('uint64') % Trigger hold off to <b>all presamples valid</b>
    end
    methods (Static)
        function result = toString(value)
            import LibTiePie.Const.TH
            switch value
                case TH.ALLPRESAMPLES
                    result = 'ALLPRESAMPLES';
                otherwise
                    error('Unknown value');
            end
        end
    end
end
