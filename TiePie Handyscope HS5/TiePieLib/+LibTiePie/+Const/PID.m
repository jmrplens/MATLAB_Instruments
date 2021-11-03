% MatlabLibTiePie - Matlab bindings for LibTiePie library
%
% Copyright (c) 2012-2021 TiePie engineering
%
% Website: http://www.tiepie.com/LibTiePie

classdef PID
    properties (Constant)
        NONE = 0 % Unknown/invalid ID
        COMBI = 2 % Combined instrument
        HS3 = 13 % Handyscope HS3
        HS4 = 15 % Handyscope HS4
        HP3 = 18 % Handyprobe HP3
        TP450 = 19 % TP450
        HS4D = 20 % Handyscope HS4-DIFF
        HS5 = 22 % Handyscope HS5
        HS6 = 24 % Handyscope HS6
        HS6D = 25 % Handyscope HS6 DIFF
        ATS610004D = 31 % ATS610004D
        ATS605004D = 32 % ATS605004D
        WS6 = 34 % WiFiScope WS6
        WS5 = 35 % WiFiScope WS5
        WS6D = 36 % WiFiScope WS6D
        ATS610004DW = 37 % ATS610004DW
        ATS605004DW = 38 % ATS605004DW
        WS4D = 39 % WiFiScope WS4D
        ATS5004DW = 40 % ATS5004DW
    end
    methods (Static)
        function result = toString(value)
            import LibTiePie.Const.PID
            switch value
                case PID.NONE
                    result = 'NONE';
                case PID.COMBI
                    result = 'COMBI';
                case PID.HS3
                    result = 'HS3';
                case PID.HS4
                    result = 'HS4';
                case PID.HP3
                    result = 'HP3';
                case PID.TP450
                    result = 'TP450';
                case PID.HS4D
                    result = 'HS4D';
                case PID.HS5
                    result = 'HS5';
                case PID.HS6
                    result = 'HS6';
                case PID.HS6D
                    result = 'HS6D';
                case PID.ATS610004D
                    result = 'ATS610004D';
                case PID.ATS605004D
                    result = 'ATS605004D';
                case PID.WS6
                    result = 'WS6';
                case PID.WS5
                    result = 'WS5';
                case PID.WS6D
                    result = 'WS6D';
                case PID.ATS610004DW
                    result = 'ATS610004DW';
                case PID.ATS605004DW
                    result = 'ATS605004DW';
                case PID.WS4D
                    result = 'WS4D';
                case PID.ATS5004DW
                    result = 'ATS5004DW';
                otherwise
                    error('Unknown value');
            end
        end
    end
end
