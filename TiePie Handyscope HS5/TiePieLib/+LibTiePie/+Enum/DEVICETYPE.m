% MatlabLibTiePie - Matlab bindings for LibTiePie library
%
% Copyright (c) 2012-2021 TiePie engineering
%
% Website: http://www.tiepie.com/LibTiePie

classdef DEVICETYPE < uint32
    enumeration
        OSCILLOSCOPE ( 1 ) % Oscilloscope
        GENERATOR ( 2 ) % Generator
        I2CHOST ( 4 ) % I2C Host
    end
end
