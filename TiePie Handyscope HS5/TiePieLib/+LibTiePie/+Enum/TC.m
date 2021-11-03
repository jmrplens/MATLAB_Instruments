% MatlabLibTiePie - Matlab bindings for LibTiePie library
%
% Copyright (c) 2012-2021 TiePie engineering
%
% Website: http://www.tiepie.com/LibTiePie

classdef TC < uint32
    enumeration
        UNKNOWN ( 0 )
        NONE ( 1 )
        SMALLER ( 2 )
        LARGER ( 4 )
        INSIDE ( 8 )
        OUTSIDE ( 16 )
    end
end
