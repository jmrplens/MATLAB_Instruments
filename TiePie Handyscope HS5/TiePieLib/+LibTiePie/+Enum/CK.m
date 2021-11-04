% MatlabLibTiePie - Matlab bindings for LibTiePie library
%
% Copyright (c) 2012-2021 TiePie engineering
%
% Website: http://www.tiepie.com/LibTiePie

classdef CK < uint64
    enumeration
        UNKNOWN ( 0 ) % Unknown/invalid coupling
        DCV ( 1 ) % Volt DC
        ACV ( 2 ) % Volt AC
        DCA ( 4 ) % Ampere DC
        ACA ( 8 ) % Ampere AC
        OHM ( 16 ) % Ohm
    end
end
