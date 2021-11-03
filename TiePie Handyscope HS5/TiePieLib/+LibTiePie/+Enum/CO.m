% MatlabLibTiePie - Matlab bindings for LibTiePie library
%
% Copyright (c) 2012-2021 TiePie engineering
%
% Website: http://www.tiepie.com/LibTiePie

classdef CO < uint32
    enumeration
        DISABLED ( 1 ) % No clock output
        SAMPLE ( 2 ) % Sample clock
        FIXED ( 4 ) % Fixed clock
    end
end
