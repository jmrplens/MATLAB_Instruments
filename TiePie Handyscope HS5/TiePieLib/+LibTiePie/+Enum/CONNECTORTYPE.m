% MatlabLibTiePie - Matlab bindings for LibTiePie library
%
% Copyright (c) 2012-2021 TiePie engineering
%
% Website: http://www.tiepie.com/LibTiePie

classdef CONNECTORTYPE < uint32
    enumeration
        UNKNOWN ( 0 )
        BNC ( 1 )
        BANANA ( 2 )
        POWERPLUG ( 4 )
    end
end
