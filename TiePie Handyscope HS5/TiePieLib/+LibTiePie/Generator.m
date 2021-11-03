% MatlabLibTiePie - Matlab bindings for LibTiePie library
%
% Copyright (c) 2012-2021 TiePie engineering
%
% Website: http://www.tiepie.com/LibTiePie

classdef Generator < LibTiePie.Device
    properties (SetAccess = private)
        ConnectorType;
        IsDifferential;
        Impedance;
        Resolution;
        OutputValueMin;
        OutputValueMax;
        IsControllable;
        IsRunning;
        Status;
        HasOutputInvert;
        SignalTypes;
        HasAmplitude;
        AmplitudeMin;
        AmplitudeMax;
        AmplitudeRanges;
        HasOffset;
        OffsetMin;
        OffsetMax;
        FrequencyModes;
        HasFrequency;
        FrequencyMin;
        FrequencyMax;
        HasPhase;
        PhaseMin;
        PhaseMax;
        HasSymmetry;
        SymmetryMin;
        SymmetryMax;
        HasWidth;
        WidthMin;
        WidthMax;
        HasEdgeTime;
        LeadingEdgeTimeMin;
        LeadingEdgeTimeMax;
        TrailingEdgeTimeMin;
        TrailingEdgeTimeMax;
        HasData;
        DataLengthMin;
        DataLengthMax;
        DataLength;
        Modes;
        ModesNative;
        IsBurstActive;
        BurstCountMin;
        BurstCountMax;
        BurstSampleCountMin;
        BurstSampleCountMax;
        BurstSegmentCountMin;
        BurstSegmentCountMax;
    end
    properties
        OutputOn;
        OutputInvert;
        SignalType;
        Amplitude;
        AmplitudeRange;
        AmplitudeAutoRanging;
        Offset;
        FrequencyMode;
        Frequency;
        Phase;
        Symmetry;
        Width;
        LeadingEdgeTime;
        TrailingEdgeTime;
        Mode;
        BurstCount;
        BurstSampleCount;
        BurstSegmentCount;
    end
    methods
        function obj = Generator(library, handle)
            obj = obj@LibTiePie.Device(library, handle);
        end

        function getOutputValueMinMax(self, min, max)
            calllib(self.m_libraryName, 'GenGetOutputValueMinMax', self.m_handle, min, max);
            self.m_library.checkLastStatus();
        end

        function start(self)
            calllib(self.m_libraryName, 'GenStart', self.m_handle);
            self.m_library.checkLastStatus();
        end

        function stop(self)
            calllib(self.m_libraryName, 'GenStop', self.m_handle);
            self.m_library.checkLastStatus();
        end

        function result = verifyAmplitude(self, amplitude)
            result = calllib(self.m_libraryName, 'GenVerifyAmplitude', self.m_handle, amplitude);
            self.m_library.checkLastStatus();
        end

        function result = verifyOffset(self, offset)
            result = calllib(self.m_libraryName, 'GenVerifyOffset', self.m_handle, offset);
            self.m_library.checkLastStatus();
        end

        function getFrequencyMinMax(self, frequencyMode, min, max)
            calllib(self.m_libraryName, 'GenGetFrequencyMinMax', self.m_handle, frequencyMode, min, max);
            self.m_library.checkLastStatus();
        end

        function result = verifyFrequency(self, frequency)
            result = calllib(self.m_libraryName, 'GenVerifyFrequency', self.m_handle, frequency);
            self.m_library.checkLastStatus();
        end

        function result = verifyPhase(self, phase)
            result = calllib(self.m_libraryName, 'GenVerifyPhase', self.m_handle, phase);
            self.m_library.checkLastStatus();
        end

        function result = verifySymmetry(self, symmetry)
            result = calllib(self.m_libraryName, 'GenVerifySymmetry', self.m_handle, symmetry);
            self.m_library.checkLastStatus();
        end

        function result = verifyWidth(self, width)
            result = calllib(self.m_libraryName, 'GenVerifyWidth', self.m_handle, width);
            self.m_library.checkLastStatus();
        end

        function result = verifyLeadingEdgeTime(self, leadingEdgeTime)
            result = calllib(self.m_libraryName, 'GenVerifyLeadingEdgeTime', self.m_handle, leadingEdgeTime);
            self.m_library.checkLastStatus();
        end

        function result = verifyTrailingEdgeTime(self, trailingEdgeTime)
            result = calllib(self.m_libraryName, 'GenVerifyTrailingEdgeTime', self.m_handle, trailingEdgeTime);
            self.m_library.checkLastStatus();
        end

        function result = verifyDataLength(self, dataLength)
            result = calllib(self.m_libraryName, 'GenVerifyDataLength', self.m_handle, dataLength);
            self.m_library.checkLastStatus();
        end

        function setData(self, data)
            calllib(self.m_libraryName, 'GenSetData', self.m_handle, data, length(data));
            self.m_library.checkLastStatus();
        end

        function result = verifyBurstSegmentCount(self, burstSegmentCount)
            result = calllib(self.m_libraryName, 'GenVerifyBurstSegmentCount', self.m_handle, burstSegmentCount);
            self.m_library.checkLastStatus();
        end
    end
    methods
        function value = get.ConnectorType(self)
            value = calllib(self.m_libraryName, 'GenGetConnectorType', self.m_handle);
            self.m_library.checkLastStatus();
                value = LibTiePie.Enum.CONNECTORTYPE(value);
        end

        function value = get.IsDifferential(self)
            value = calllib(self.m_libraryName, 'GenIsDifferential', self.m_handle);
            self.m_library.checkLastStatus();
        end

        function value = get.Impedance(self)
            value = calllib(self.m_libraryName, 'GenGetImpedance', self.m_handle);
            self.m_library.checkLastStatus();
        end

        function value = get.Resolution(self)
            value = calllib(self.m_libraryName, 'GenGetResolution', self.m_handle);
            self.m_library.checkLastStatus();
        end

        function value = get.OutputValueMin(self)
            value = calllib(self.m_libraryName, 'GenGetOutputValueMin', self.m_handle);
            self.m_library.checkLastStatus();
        end

        function value = get.OutputValueMax(self)
            value = calllib(self.m_libraryName, 'GenGetOutputValueMax', self.m_handle);
            self.m_library.checkLastStatus();
        end

        function value = get.IsControllable(self)
            value = calllib(self.m_libraryName, 'GenIsControllable', self.m_handle);
            self.m_library.checkLastStatus();
        end

        function value = get.IsRunning(self)
            value = calllib(self.m_libraryName, 'GenIsRunning', self.m_handle);
            self.m_library.checkLastStatus();
        end

        function value = get.Status(self)
            value = calllib(self.m_libraryName, 'GenGetStatus', self.m_handle);
            self.m_library.checkLastStatus();
            value = LibTiePie.BitMask2Array(value);
                value = LibTiePie.Enum.GS(value);
        end

        function value = get.OutputOn(self)
            value = calllib(self.m_libraryName, 'GenGetOutputOn', self.m_handle);
            self.m_library.checkLastStatus();
        end

        function set.OutputOn(self, value)
            calllib(self.m_libraryName, 'GenSetOutputOn', self.m_handle, value);
            self.m_library.checkLastStatus();
        end

        function value = get.HasOutputInvert(self)
            value = calllib(self.m_libraryName, 'GenHasOutputInvert', self.m_handle);
            self.m_library.checkLastStatus();
        end

        function value = get.OutputInvert(self)
            value = calllib(self.m_libraryName, 'GenGetOutputInvert', self.m_handle);
            self.m_library.checkLastStatus();
        end

        function set.OutputInvert(self, value)
            calllib(self.m_libraryName, 'GenSetOutputInvert', self.m_handle, value);
            self.m_library.checkLastStatus();
        end

        function value = get.SignalTypes(self)
            value = calllib(self.m_libraryName, 'GenGetSignalTypes', self.m_handle);
            self.m_library.checkLastStatus();
            value = LibTiePie.BitMask2Array(value);
                value = LibTiePie.Enum.ST(value);
        end

        function value = get.SignalType(self)
            value = calllib(self.m_libraryName, 'GenGetSignalType', self.m_handle);
            self.m_library.checkLastStatus();
                value = LibTiePie.Enum.ST(value);
        end

        function set.SignalType(self, value)
            calllib(self.m_libraryName, 'GenSetSignalType', self.m_handle, uint32(value));
            self.m_library.checkLastStatus();
        end

        function value = get.HasAmplitude(self)
            value = calllib(self.m_libraryName, 'GenHasAmplitude', self.m_handle);
            self.m_library.checkLastStatus();
        end

        function value = get.AmplitudeMin(self)
            value = calllib(self.m_libraryName, 'GenGetAmplitudeMin', self.m_handle);
            self.m_library.checkLastStatus();
        end

        function value = get.AmplitudeMax(self)
            value = calllib(self.m_libraryName, 'GenGetAmplitudeMax', self.m_handle);
            self.m_library.checkLastStatus();
        end

        function value = get.Amplitude(self)
            value = calllib(self.m_libraryName, 'GenGetAmplitude', self.m_handle);
            self.m_library.checkLastStatus();
        end

        function set.Amplitude(self, value)
            calllib(self.m_libraryName, 'GenSetAmplitude', self.m_handle, value);
            self.m_library.checkLastStatus();
        end

        function value = get.AmplitudeRanges(self)
            length = calllib(self.m_libraryName, 'GenGetAmplitudeRanges', self.m_handle, [], 0);
            self.m_library.checkLastStatus();
            [~, value] = calllib(self.m_libraryName, 'GenGetAmplitudeRanges', self.m_handle, zeros(length, 1), length);
            self.m_library.checkLastStatus();
        end

        function value = get.AmplitudeRange(self)
            value = calllib(self.m_libraryName, 'GenGetAmplitudeRange', self.m_handle);
            self.m_library.checkLastStatus();
        end

        function set.AmplitudeRange(self, value)
            calllib(self.m_libraryName, 'GenSetAmplitudeRange', self.m_handle, value);
            self.m_library.checkLastStatus();
        end

        function value = get.AmplitudeAutoRanging(self)
            value = calllib(self.m_libraryName, 'GenGetAmplitudeAutoRanging', self.m_handle);
            self.m_library.checkLastStatus();
        end

        function set.AmplitudeAutoRanging(self, value)
            calllib(self.m_libraryName, 'GenSetAmplitudeAutoRanging', self.m_handle, value);
            self.m_library.checkLastStatus();
        end

        function value = get.HasOffset(self)
            value = calllib(self.m_libraryName, 'GenHasOffset', self.m_handle);
            self.m_library.checkLastStatus();
        end

        function value = get.OffsetMin(self)
            value = calllib(self.m_libraryName, 'GenGetOffsetMin', self.m_handle);
            self.m_library.checkLastStatus();
        end

        function value = get.OffsetMax(self)
            value = calllib(self.m_libraryName, 'GenGetOffsetMax', self.m_handle);
            self.m_library.checkLastStatus();
        end

        function value = get.Offset(self)
            value = calllib(self.m_libraryName, 'GenGetOffset', self.m_handle);
            self.m_library.checkLastStatus();
        end

        function set.Offset(self, value)
            calllib(self.m_libraryName, 'GenSetOffset', self.m_handle, value);
            self.m_library.checkLastStatus();
        end

        function value = get.FrequencyModes(self)
            value = calllib(self.m_libraryName, 'GenGetFrequencyModes', self.m_handle);
            self.m_library.checkLastStatus();
            value = LibTiePie.BitMask2Array(value);
                value = LibTiePie.Enum.FM(value);
        end

        function value = get.FrequencyMode(self)
            value = calllib(self.m_libraryName, 'GenGetFrequencyMode', self.m_handle);
            self.m_library.checkLastStatus();
                value = LibTiePie.Enum.FM(value);
        end

        function set.FrequencyMode(self, value)
            calllib(self.m_libraryName, 'GenSetFrequencyMode', self.m_handle, uint32(value));
            self.m_library.checkLastStatus();
        end

        function value = get.HasFrequency(self)
            value = calllib(self.m_libraryName, 'GenHasFrequency', self.m_handle);
            self.m_library.checkLastStatus();
        end

        function value = get.FrequencyMin(self)
            value = calllib(self.m_libraryName, 'GenGetFrequencyMin', self.m_handle);
            self.m_library.checkLastStatus();
        end

        function value = get.FrequencyMax(self)
            value = calllib(self.m_libraryName, 'GenGetFrequencyMax', self.m_handle);
            self.m_library.checkLastStatus();
        end

        function value = get.Frequency(self)
            value = calllib(self.m_libraryName, 'GenGetFrequency', self.m_handle);
            self.m_library.checkLastStatus();
        end

        function set.Frequency(self, value)
            calllib(self.m_libraryName, 'GenSetFrequency', self.m_handle, value);
            self.m_library.checkLastStatus();
        end

        function value = get.HasPhase(self)
            value = calllib(self.m_libraryName, 'GenHasPhase', self.m_handle);
            self.m_library.checkLastStatus();
        end

        function value = get.PhaseMin(self)
            value = calllib(self.m_libraryName, 'GenGetPhaseMin', self.m_handle);
            self.m_library.checkLastStatus();
        end

        function value = get.PhaseMax(self)
            value = calllib(self.m_libraryName, 'GenGetPhaseMax', self.m_handle);
            self.m_library.checkLastStatus();
        end

        function value = get.Phase(self)
            value = calllib(self.m_libraryName, 'GenGetPhase', self.m_handle);
            self.m_library.checkLastStatus();
        end

        function set.Phase(self, value)
            calllib(self.m_libraryName, 'GenSetPhase', self.m_handle, value);
            self.m_library.checkLastStatus();
        end

        function value = get.HasSymmetry(self)
            value = calllib(self.m_libraryName, 'GenHasSymmetry', self.m_handle);
            self.m_library.checkLastStatus();
        end

        function value = get.SymmetryMin(self)
            value = calllib(self.m_libraryName, 'GenGetSymmetryMin', self.m_handle);
            self.m_library.checkLastStatus();
        end

        function value = get.SymmetryMax(self)
            value = calllib(self.m_libraryName, 'GenGetSymmetryMax', self.m_handle);
            self.m_library.checkLastStatus();
        end

        function value = get.Symmetry(self)
            value = calllib(self.m_libraryName, 'GenGetSymmetry', self.m_handle);
            self.m_library.checkLastStatus();
        end

        function set.Symmetry(self, value)
            calllib(self.m_libraryName, 'GenSetSymmetry', self.m_handle, value);
            self.m_library.checkLastStatus();
        end

        function value = get.HasWidth(self)
            value = calllib(self.m_libraryName, 'GenHasWidth', self.m_handle);
            self.m_library.checkLastStatus();
        end

        function value = get.WidthMin(self)
            value = calllib(self.m_libraryName, 'GenGetWidthMin', self.m_handle);
            self.m_library.checkLastStatus();
        end

        function value = get.WidthMax(self)
            value = calllib(self.m_libraryName, 'GenGetWidthMax', self.m_handle);
            self.m_library.checkLastStatus();
        end

        function value = get.Width(self)
            value = calllib(self.m_libraryName, 'GenGetWidth', self.m_handle);
            self.m_library.checkLastStatus();
        end

        function set.Width(self, value)
            calllib(self.m_libraryName, 'GenSetWidth', self.m_handle, value);
            self.m_library.checkLastStatus();
        end

        function value = get.HasEdgeTime(self)
            value = calllib(self.m_libraryName, 'GenHasEdgeTime', self.m_handle);
            self.m_library.checkLastStatus();
        end

        function value = get.LeadingEdgeTimeMin(self)
            value = calllib(self.m_libraryName, 'GenGetLeadingEdgeTimeMin', self.m_handle);
            self.m_library.checkLastStatus();
        end

        function value = get.LeadingEdgeTimeMax(self)
            value = calllib(self.m_libraryName, 'GenGetLeadingEdgeTimeMax', self.m_handle);
            self.m_library.checkLastStatus();
        end

        function value = get.LeadingEdgeTime(self)
            value = calllib(self.m_libraryName, 'GenGetLeadingEdgeTime', self.m_handle);
            self.m_library.checkLastStatus();
        end

        function set.LeadingEdgeTime(self, value)
            calllib(self.m_libraryName, 'GenSetLeadingEdgeTime', self.m_handle, value);
            self.m_library.checkLastStatus();
        end

        function value = get.TrailingEdgeTimeMin(self)
            value = calllib(self.m_libraryName, 'GenGetTrailingEdgeTimeMin', self.m_handle);
            self.m_library.checkLastStatus();
        end

        function value = get.TrailingEdgeTimeMax(self)
            value = calllib(self.m_libraryName, 'GenGetTrailingEdgeTimeMax', self.m_handle);
            self.m_library.checkLastStatus();
        end

        function value = get.TrailingEdgeTime(self)
            value = calllib(self.m_libraryName, 'GenGetTrailingEdgeTime', self.m_handle);
            self.m_library.checkLastStatus();
        end

        function set.TrailingEdgeTime(self, value)
            calllib(self.m_libraryName, 'GenSetTrailingEdgeTime', self.m_handle, value);
            self.m_library.checkLastStatus();
        end

        function value = get.HasData(self)
            value = calllib(self.m_libraryName, 'GenHasData', self.m_handle);
            self.m_library.checkLastStatus();
        end

        function value = get.DataLengthMin(self)
            value = calllib(self.m_libraryName, 'GenGetDataLengthMin', self.m_handle);
            self.m_library.checkLastStatus();
        end

        function value = get.DataLengthMax(self)
            value = calllib(self.m_libraryName, 'GenGetDataLengthMax', self.m_handle);
            self.m_library.checkLastStatus();
        end

        function value = get.DataLength(self)
            value = calllib(self.m_libraryName, 'GenGetDataLength', self.m_handle);
            self.m_library.checkLastStatus();
        end

        function value = get.Modes(self)
            value = calllib(self.m_libraryName, 'GenGetModes', self.m_handle);
            self.m_library.checkLastStatus();
            value = LibTiePie.BitMask2Array(value);
                value = LibTiePie.Enum.GM(value);
        end

        function value = get.ModesNative(self)
            value = calllib(self.m_libraryName, 'GenGetModesNative', self.m_handle);
            self.m_library.checkLastStatus();
            value = LibTiePie.BitMask2Array(value);
                value = LibTiePie.Enum.GM(value);
        end

        function value = get.Mode(self)
            value = calllib(self.m_libraryName, 'GenGetMode', self.m_handle);
            self.m_library.checkLastStatus();
                value = LibTiePie.Enum.GM(value);
        end

        function set.Mode(self, value)
            calllib(self.m_libraryName, 'GenSetMode', self.m_handle, uint64(value));
            self.m_library.checkLastStatus();
        end

        function value = get.IsBurstActive(self)
            value = calllib(self.m_libraryName, 'GenIsBurstActive', self.m_handle);
            self.m_library.checkLastStatus();
        end

        function value = get.BurstCountMin(self)
            value = calllib(self.m_libraryName, 'GenGetBurstCountMin', self.m_handle);
            self.m_library.checkLastStatus();
        end

        function value = get.BurstCountMax(self)
            value = calllib(self.m_libraryName, 'GenGetBurstCountMax', self.m_handle);
            self.m_library.checkLastStatus();
        end

        function value = get.BurstCount(self)
            value = calllib(self.m_libraryName, 'GenGetBurstCount', self.m_handle);
            self.m_library.checkLastStatus();
        end

        function set.BurstCount(self, value)
            calllib(self.m_libraryName, 'GenSetBurstCount', self.m_handle, value);
            self.m_library.checkLastStatus();
        end

        function value = get.BurstSampleCountMin(self)
            value = calllib(self.m_libraryName, 'GenGetBurstSampleCountMin', self.m_handle);
            self.m_library.checkLastStatus();
        end

        function value = get.BurstSampleCountMax(self)
            value = calllib(self.m_libraryName, 'GenGetBurstSampleCountMax', self.m_handle);
            self.m_library.checkLastStatus();
        end

        function value = get.BurstSampleCount(self)
            value = calllib(self.m_libraryName, 'GenGetBurstSampleCount', self.m_handle);
            self.m_library.checkLastStatus();
        end

        function set.BurstSampleCount(self, value)
            calllib(self.m_libraryName, 'GenSetBurstSampleCount', self.m_handle, value);
            self.m_library.checkLastStatus();
        end

        function value = get.BurstSegmentCountMin(self)
            value = calllib(self.m_libraryName, 'GenGetBurstSegmentCountMin', self.m_handle);
            self.m_library.checkLastStatus();
        end

        function value = get.BurstSegmentCountMax(self)
            value = calllib(self.m_libraryName, 'GenGetBurstSegmentCountMax', self.m_handle);
            self.m_library.checkLastStatus();
        end

        function value = get.BurstSegmentCount(self)
            value = calllib(self.m_libraryName, 'GenGetBurstSegmentCount', self.m_handle);
            self.m_library.checkLastStatus();
        end

        function set.BurstSegmentCount(self, value)
            calllib(self.m_libraryName, 'GenSetBurstSegmentCount', self.m_handle, value);
            self.m_library.checkLastStatus();
        end
    end
end
