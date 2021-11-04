% MatlabLibTiePie - Matlab bindings for LibTiePie library
%
% Copyright (c) 2012-2021 TiePie engineering
%
% Website: http://www.tiepie.com/LibTiePie

classdef TK < uint64
    enumeration
        UNKNOWN ( 0 ) % Unknown/invalid trigger kind
        RISINGEDGE ( 1 ) % Rising edge
        FALLINGEDGE ( 2 ) % Falling edge
        INWINDOW ( 4 ) % Inside window
        OUTWINDOW ( 8 ) % Outside window
        ANYEDGE ( 16 ) % Any edge
        ENTERWINDOW ( 32 ) % Enter window
        EXITWINDOW ( 64 ) % Exit window
        PULSEWIDTHPOSITIVE ( 128 ) % Positive pulse width
        PULSEWIDTHNEGATIVE ( 256 ) % Negative pulse width
        PULSEWIDTHEITHER ( 512 ) % Positive or negative pulse width
        RUNTPULSEPOSITIVE ( 1024 ) % Positive runt pulse
        RUNTPULSENEGATIVE ( 2048 ) % Negative runt pulse
        RUNTPULSEEITHER ( 4096 ) % Positive or negative runt pulse
        INTERVALRISING ( 8192 ) % Interval (rising edge)
        INTERVALFALLING ( 16384 ) % Interval (falling edge)
    end
end
