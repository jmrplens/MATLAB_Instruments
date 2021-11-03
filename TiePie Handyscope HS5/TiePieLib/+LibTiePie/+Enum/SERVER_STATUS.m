% MatlabLibTiePie - Matlab bindings for LibTiePie library
%
% Copyright (c) 2012-2021 TiePie engineering
%
% Website: http://www.tiepie.com/LibTiePie

classdef SERVER_STATUS < uint32
    enumeration
        DISCONNECTED ( 0 )
        CONNECTING ( 1 )
        CONNECTED ( 2 )
        DISCONNECTING ( 3 )
    end
end
