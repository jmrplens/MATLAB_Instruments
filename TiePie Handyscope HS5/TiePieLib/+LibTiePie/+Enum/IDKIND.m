% MatlabLibTiePie - Matlab bindings for LibTiePie library
%
% Copyright (c) 2012-2021 TiePie engineering
%
% Website: http://www.tiepie.com/LibTiePie

classdef IDKIND < uint32
    enumeration
        PRODUCTID ( 1 ) % dwId parameter is a \ref PID_ "product id".
        INDEX ( 2 ) % dwId parameter is an index.
        SERIALNUMBER ( 4 ) % dwId parameter is a serial number.
    end
end
