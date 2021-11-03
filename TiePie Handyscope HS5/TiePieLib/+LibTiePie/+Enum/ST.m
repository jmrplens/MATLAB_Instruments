% MatlabLibTiePie - Matlab bindings for LibTiePie library
%
% Copyright (c) 2012-2021 TiePie engineering
%
% Website: http://www.tiepie.com/LibTiePie

classdef ST < uint32
    enumeration
        UNKNOWN ( 0 )
        SINE ( 1 )
        TRIANGLE ( 2 )
        SQUARE ( 4 )
        DC ( 8 )
        NOISE ( 16 )
        ARBITRARY ( 32 )
        PULSE ( 64 )
    end
end
