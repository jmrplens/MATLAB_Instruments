% MatlabLibTiePie - Matlab bindings for LibTiePie library
%
% Copyright (c) 2012-2021 TiePie engineering
%
% Website: http://www.tiepie.com/LibTiePie

classdef AR < uint32
    enumeration
        UNKNOWN ( 0 ) % Unknown/invalid mode
        DISABLED ( 1 ) % Resolution does not automatically change.
        NATIVEONLY ( 2 ) % Highest possible native resolution for the current sample frequency is used.
        ALL ( 4 ) % Highest possible native or enhanced resolution for the current sample frequency is used.
    end
end
