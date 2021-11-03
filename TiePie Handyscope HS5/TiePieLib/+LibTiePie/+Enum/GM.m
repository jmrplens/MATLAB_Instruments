% MatlabLibTiePie - Matlab bindings for LibTiePie library
%
% Copyright (c) 2012-2021 TiePie engineering
%
% Website: http://www.tiepie.com/LibTiePie

classdef GM < uint64
    enumeration
        UNKNOWN ( 0 )
        CONTINUOUS ( 1 )
        BURST_COUNT ( 2 )
        GATED_PERIODS ( 4 )
        GATED ( 8 )
        GATED_PERIOD_START ( 16 )
        GATED_PERIOD_FINISH ( 32 )
        GATED_RUN ( 64 )
        GATED_RUN_OUTPUT ( 128 )
        BURST_SAMPLE_COUNT ( 256 )
        BURST_SAMPLE_COUNT_OUTPUT ( 512 )
        BURST_SEGMENT_COUNT ( 1024 )
        BURST_SEGMENT_COUNT_OUTPUT ( 2048 )
    end
end
