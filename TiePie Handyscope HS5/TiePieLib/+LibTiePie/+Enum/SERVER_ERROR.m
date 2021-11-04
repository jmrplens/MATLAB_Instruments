% MatlabLibTiePie - Matlab bindings for LibTiePie library
%
% Copyright (c) 2012-2021 TiePie engineering
%
% Website: http://www.tiepie.com/LibTiePie

classdef SERVER_ERROR < uint32
    enumeration
        NONE ( 0 )
        UNKNOWN ( 1 )
        CONNECTIONREFUSED ( 2 )
        NETWORKUNREACHABLE ( 3 )
        TIMEDOUT ( 4 )
        HOSTNAMELOOKUPFAILED ( 5 )
    end
end
