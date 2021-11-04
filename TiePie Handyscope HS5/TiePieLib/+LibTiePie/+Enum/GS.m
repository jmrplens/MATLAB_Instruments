% MatlabLibTiePie - Matlab bindings for LibTiePie library
%
% Copyright (c) 2012-2021 TiePie engineering
%
% Website: http://www.tiepie.com/LibTiePie

classdef GS < uint32
    enumeration
        STOPPED ( 1 ) % The signal generation is stopped.
        RUNNING ( 2 ) % The signal generation is running.
        BURSTACTIVE ( 4 ) % The generator is operating in burst mode.
        WAITING ( 8 ) % The generator is waiting for a burst to be started.
    end
end
