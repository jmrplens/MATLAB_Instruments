% MatlabLibTiePie - Matlab bindings for LibTiePie library
%
% Copyright (c) 2012-2021 TiePie engineering
%
% Website: http://www.tiepie.com/LibTiePie

classdef MM < uint32
    enumeration
        UNKNOWN ( 0 ) % Unknown/invalid mode
        STREAM ( 1 ) % Stream mode
        BLOCK ( 2 ) % Block mode
    end
end
