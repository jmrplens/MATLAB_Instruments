% MatlabLibTiePie - Matlab bindings for LibTiePie library
%
% Copyright (c) 2012-2021 TiePie engineering
%
% Website: http://www.tiepie.com/LibTiePie

classdef Oscilloscope < LibTiePie.Device
    properties (GetAccess = protected, SetAccess = private)
        m_measureMode;
        m_recordLength;
        m_preSampleRatio;
    end
    properties (SetAccess = private)
        Channels = LibTiePie.OscilloscopeChannel.empty;
        ValidPreSampleCount;
        MeasureModes;
        IsRunning;
        IsTriggered;
        IsTimeOutTriggered;
        IsForceTriggered;
        IsDataReady;
        IsDataOverflow;
        AutoResolutionModes;
        Resolutions;
        IsResolutionEnhanced;
        ClockSources;
        ClockSourceFrequencies;
        ClockOutputs;
        ClockOutputFrequencies;
        SampleFrequencyMax;
        RecordLengthMax;
        SegmentCountMax;
        HasTrigger;
        HasTriggerDelay;
        TriggerDelayMax;
        HasTriggerHoldOff;
        TriggerHoldOffCountMax;
        HasConnectionTest;
        IsConnectionTestCompleted;
    end
    properties
        MeasureMode;
        AutoResolutionMode;
        Resolution;
        ClockSource;
        ClockSourceFrequency;
        ClockOutput;
        ClockOutputFrequency;
        SampleFrequency;
        RecordLength;
        PreSampleRatio;
        SegmentCount;
        TriggerTimeOut;
        TriggerDelay;
        TriggerHoldOffCount;
    end
    methods
        function obj = Oscilloscope(library, handle)
            obj = obj@LibTiePie.Device(library, handle);
            for k = 1 : calllib(obj.m_libraryName, 'ScpGetChannelCount', handle)
                obj.Channels(k) = LibTiePie.OscilloscopeChannel(library, handle, k - 1);
            end
        end

        function result = getData(self)
            if ~self.IsDataReady
                error('Data is not ready. Perform a measurement and wait until IsDataReady.');
            end

            channelCount = length(self.Channels);

            % Calculate valid data start/length:
            if self.m_measureMode == LibTiePie.Enum.MM.BLOCK
                dataLength = self.m_recordLength - round(self.m_preSampleRatio * self.m_recordLength) + self.ValidPreSampleCount;
                start = self.m_recordLength - dataLength;
            else
                dataLength = self.m_recordLength;
                start = 0;
            end

            result = zeros(dataLength, channelCount, 'single');
            data = calllib(self.m_libraryName, 'HlpPointerArrayNew', channelCount);
            self.m_library.checkLastStatus();
            c = onCleanup(@()calllib(self.m_libraryName, 'HlpPointerArrayDelete', data)); % Make sure pointer array is deleted.

            dataPtr = libpointer('singlePtr', result);
            for k = 0:channelCount - 1;
                chDataPtr = dataPtr + k * dataLength;
                calllib(self.m_libraryName, 'HlpPointerArraySet', data, k, chDataPtr);
                self.m_library.checkLastStatus();
            end

            calllib(self.m_libraryName, 'ScpGetData', self.m_handle, data, channelCount, start, dataLength);
            self.m_library.checkLastStatus();

            % Copy the gotten data from the libpointer to the data matrix:
            result = dataPtr.Value;
        end

        function result = getDataAsyncCompleted(self)
            result = calllib(self.m_libraryName, 'ScpIsGetDataAsyncCompleted', self.m_handle);
            self.m_library.checkLastStatus();
        end

        function startGetDataAsync(self, buffers, channelCount, startIndex, sampleCount)
            calllib(self.m_libraryName, 'ScpStartGetDataAsync', self.m_handle, buffers, channelCount, startIndex, sampleCount);
            self.m_library.checkLastStatus();
        end

        function result = cancelGetDataAsync(self)
            result = calllib(self.m_libraryName, 'ScpCancelGetDataAsync', self.m_handle);
            self.m_library.checkLastStatus();
        end

        function result = getDataRaw(self)
            if ~self.IsDataReady
                error('Data is not ready. Perform a measurement and wait until IsDataReady.');
            end

            channelCount = length(self.Channels);

            % Calculate valid data start/length:
            if self.m_measureMode == LibTiePie.Enum.MM.BLOCK
                dataLength = self.m_recordLength - round(self.m_preSampleRatio * self.m_recordLength) + self.ValidPreSampleCount;
                start = self.m_recordLength - dataLength;
            else
                dataLength = self.m_recordLength;
                start = 0;
            end

            rawType = LibTiePie.Const.DataRawType.UNKNOWN;
            for k = 0:channelCount - 1;
                if calllib(self.m_libraryName, 'ScpChGetEnabled', self.m_handle, k)
                    chRawType = calllib(self.m_libraryName, 'ScpChGetDataRawType', self.m_handle, k);
                    if rawType == LibTiePie.Const.DataRawType.UNKNOWN
                        rawType = chRawType;
                    elseif rawType ~= chRawType
                        error('GetDataRaw() requires all channel to use the same raw type, use GetData() instead.');
                    end
                end
            end

            switch rawType
                case LibTiePie.Const.DataRawType.INT8
                    result = zeros(dataLength, channelCount, 'int8');
                    dataPtr = libpointer('int8Ptr', result);
                case LibTiePie.Const.DataRawType.INT16
                    result = zeros(dataLength, channelCount, 'int16');
                    dataPtr = libpointer('int16Ptr', result);
                case LibTiePie.Const.DataRawType.INT32
                    result = zeros(dataLength, channelCount, 'int32');
                    dataPtr = libpointer('int32Ptr', result);
                case LibTiePie.Const.DataRawType.INT64
                    result = zeros(dataLength, channelCount, 'int64');
                    dataPtr = libpointer('int64Ptr', result);
                case LibTiePie.Const.DataRawType.UINT8
                    result = zeros(dataLength, channelCount, 'uint8');
                    dataPtr = libpointer('uint8Ptr', result);
                case LibTiePie.Const.DataRawType.UINT16
                    result = zeros(dataLength, channelCount, 'uint16');
                    dataPtr = libpointer('uint16Ptr', result);
                case LibTiePie.Const.DataRawType.UINT32
                    result = zeros(dataLength, channelCount, 'uint32');
                    dataPtr = libpointer('uint32Ptr', result);
                case LibTiePie.Const.DataRawType.UINT64
                    result = zeros(dataLength, channelCount, 'uint64');
                    dataPtr = libpointer('uint64Ptr', result);
                case LibTiePie.Const.DataRawType.FLOAT32
                    result = zeros(dataLength, channelCount, 'single');
                    dataPtr = libpointer('singlePtr', result);
                case LibTiePie.Const.DataRawType.FLOAT64
                    result = zeros(dataLength, channelCount, 'double');
                    dataPtr = libpointer('doublePtr', result);
                otherwise
                    error('Unsupported raw data type.');
            end

            data = calllib(self.m_libraryName, 'HlpPointerArrayNew', channelCount);
            self.m_library.checkLastStatus();
            c = onCleanup(@()calllib(self.m_libraryName, 'HlpPointerArrayDelete', data)); % Make sure pointer array is deleted.

            for k = 0:channelCount - 1;
                chDataPtr = dataPtr + k * dataLength;
                calllib(self.m_libraryName, 'HlpPointerArraySet', data, k, chDataPtr);
                self.m_library.checkLastStatus();
            end

            calllib(self.m_libraryName, 'ScpGetDataRaw', self.m_handle, data, channelCount, start, dataLength);
            self.m_library.checkLastStatus();

            % Copy the gotten data from the libpointer to the data matrix:
            result = dataPtr.Value;
        end

        function start(self)
            if self.IsRunning
                error('Can not start a measurement, measurement in progress.');
            end

            % Cache some values, needed for getting data:
            self.m_measureMode = uint32(self.MeasureMode);
            self.m_recordLength = self.RecordLength;
            if self.m_measureMode == LibTiePie.Enum.MM.BLOCK
                self.m_preSampleRatio = self.PreSampleRatio;
            end

            calllib(self.m_libraryName, 'ScpStart', self.m_handle);
            self.m_library.checkLastStatus();
        end

        function stop(self)
            calllib(self.m_libraryName, 'ScpStop', self.m_handle);
            self.m_library.checkLastStatus();
        end

        function forceTrigger(self)
            calllib(self.m_libraryName, 'ScpForceTrigger', self.m_handle);
            self.m_library.checkLastStatus();
        end

        function result = verifySampleFrequency(self, sampleFrequency)
            result = calllib(self.m_libraryName, 'ScpVerifySampleFrequency', self.m_handle, sampleFrequency);
            self.m_library.checkLastStatus();
        end

        function result = verifyRecordLength(self, recordLength)
            result = calllib(self.m_libraryName, 'ScpVerifyRecordLength', self.m_handle, recordLength);
            self.m_library.checkLastStatus();
        end

        function result = verifySegmentCount(self, segmentCount)
            result = calllib(self.m_libraryName, 'ScpVerifySegmentCount', self.m_handle, segmentCount);
            self.m_library.checkLastStatus();
        end

        function result = verifyTriggerTimeOut(self, timeOut)
            result = calllib(self.m_libraryName, 'ScpVerifyTriggerTimeOut', self.m_handle, timeOut);
            self.m_library.checkLastStatus();
        end

        function result = verifyTriggerDelay(self, delay)
            result = calllib(self.m_libraryName, 'ScpVerifyTriggerDelay', self.m_handle, delay);
            self.m_library.checkLastStatus();
        end

        function startConnectionTest(self)
            calllib(self.m_libraryName, 'ScpStartConnectionTest', self.m_handle);
            self.m_library.checkLastStatus();
        end

        function result = getConnectionTestData(self)
            if ~self.IsConnectionTestCompleted
                error('ConnectionTestData is not ready. Perform a measurement and wait until IsConnectionTestCompleted.');
            end

            channelCount = length(self.Channels);

            result = zeros(1, channelCount, 'uint8');
            [ ~, result ] = calllib(self.m_libraryName, 'ScpGetConnectionTestData', self.m_handle, result, channelCount);
            self.m_library.checkLastStatus();

            result = LibTiePie.Enum.TRISTATE(result);
        end
    end
    methods
        function value = get.ValidPreSampleCount(self)
            value = calllib(self.m_libraryName, 'ScpGetValidPreSampleCount', self.m_handle);
            self.m_library.checkLastStatus();
        end

        function value = get.MeasureModes(self)
            value = calllib(self.m_libraryName, 'ScpGetMeasureModes', self.m_handle);
            self.m_library.checkLastStatus();
            value = LibTiePie.BitMask2Array(value);
                value = LibTiePie.Enum.MM(value);
        end

        function value = get.MeasureMode(self)
            value = calllib(self.m_libraryName, 'ScpGetMeasureMode', self.m_handle);
            self.m_library.checkLastStatus();
                value = LibTiePie.Enum.MM(value);
        end

        function set.MeasureMode(self, value)
            calllib(self.m_libraryName, 'ScpSetMeasureMode', self.m_handle, uint32(value));
            self.m_library.checkLastStatus();
        end

        function value = get.IsRunning(self)
            value = calllib(self.m_libraryName, 'ScpIsRunning', self.m_handle);
            self.m_library.checkLastStatus();
        end

        function value = get.IsTriggered(self)
            value = calllib(self.m_libraryName, 'ScpIsTriggered', self.m_handle);
            self.m_library.checkLastStatus();
        end

        function value = get.IsTimeOutTriggered(self)
            value = calllib(self.m_libraryName, 'ScpIsTimeOutTriggered', self.m_handle);
            self.m_library.checkLastStatus();
        end

        function value = get.IsForceTriggered(self)
            value = calllib(self.m_libraryName, 'ScpIsForceTriggered', self.m_handle);
            self.m_library.checkLastStatus();
        end

        function value = get.IsDataReady(self)
            value = calllib(self.m_libraryName, 'ScpIsDataReady', self.m_handle);
            self.m_library.checkLastStatus();
        end

        function value = get.IsDataOverflow(self)
            value = calllib(self.m_libraryName, 'ScpIsDataOverflow', self.m_handle);
            self.m_library.checkLastStatus();
        end

        function value = get.AutoResolutionModes(self)
            value = calllib(self.m_libraryName, 'ScpGetAutoResolutionModes', self.m_handle);
            self.m_library.checkLastStatus();
            value = LibTiePie.BitMask2Array(value);
                value = LibTiePie.Enum.AR(value);
        end

        function value = get.AutoResolutionMode(self)
            value = calllib(self.m_libraryName, 'ScpGetAutoResolutionMode', self.m_handle);
            self.m_library.checkLastStatus();
                value = LibTiePie.Enum.AR(value);
        end

        function set.AutoResolutionMode(self, value)
            calllib(self.m_libraryName, 'ScpSetAutoResolutionMode', self.m_handle, uint32(value));
            self.m_library.checkLastStatus();
        end

        function value = get.Resolutions(self)
            length = calllib(self.m_libraryName, 'ScpGetResolutions', self.m_handle, [], 0);
            self.m_library.checkLastStatus();
            [~, value] = calllib(self.m_libraryName, 'ScpGetResolutions', self.m_handle, zeros(length, 1), length);
            self.m_library.checkLastStatus();
        end

        function value = get.Resolution(self)
            value = calllib(self.m_libraryName, 'ScpGetResolution', self.m_handle);
            self.m_library.checkLastStatus();
        end

        function set.Resolution(self, value)
            calllib(self.m_libraryName, 'ScpSetResolution', self.m_handle, value);
            self.m_library.checkLastStatus();
        end

        function value = get.IsResolutionEnhanced(self)
            value = calllib(self.m_libraryName, 'ScpIsResolutionEnhanced', self.m_handle);
            self.m_library.checkLastStatus();
        end

        function value = get.ClockSources(self)
            value = calllib(self.m_libraryName, 'ScpGetClockSources', self.m_handle);
            self.m_library.checkLastStatus();
            value = LibTiePie.BitMask2Array(value);
                value = LibTiePie.Enum.CS(value);
        end

        function value = get.ClockSource(self)
            value = calllib(self.m_libraryName, 'ScpGetClockSource', self.m_handle);
            self.m_library.checkLastStatus();
                value = LibTiePie.Enum.CS(value);
        end

        function set.ClockSource(self, value)
            calllib(self.m_libraryName, 'ScpSetClockSource', self.m_handle, uint32(value));
            self.m_library.checkLastStatus();
        end

        function value = get.ClockSourceFrequencies(self)
            length = calllib(self.m_libraryName, 'ScpGetClockSourceFrequencies', self.m_handle, [], 0);
            self.m_library.checkLastStatus();
            [~, value] = calllib(self.m_libraryName, 'ScpGetClockSourceFrequencies', self.m_handle, zeros(length, 1), length);
            self.m_library.checkLastStatus();
        end

        function value = get.ClockSourceFrequency(self)
            value = calllib(self.m_libraryName, 'ScpGetClockSourceFrequency', self.m_handle);
            self.m_library.checkLastStatus();
        end

        function set.ClockSourceFrequency(self, value)
            calllib(self.m_libraryName, 'ScpSetClockSourceFrequency', self.m_handle, value);
            self.m_library.checkLastStatus();
        end

        function value = get.ClockOutputs(self)
            value = calllib(self.m_libraryName, 'ScpGetClockOutputs', self.m_handle);
            self.m_library.checkLastStatus();
            value = LibTiePie.BitMask2Array(value);
                value = LibTiePie.Enum.CO(value);
        end

        function value = get.ClockOutput(self)
            value = calllib(self.m_libraryName, 'ScpGetClockOutput', self.m_handle);
            self.m_library.checkLastStatus();
                value = LibTiePie.Enum.CO(value);
        end

        function set.ClockOutput(self, value)
            calllib(self.m_libraryName, 'ScpSetClockOutput', self.m_handle, uint32(value));
            self.m_library.checkLastStatus();
        end

        function value = get.ClockOutputFrequencies(self)
            length = calllib(self.m_libraryName, 'ScpGetClockOutputFrequencies', self.m_handle, [], 0);
            self.m_library.checkLastStatus();
            [~, value] = calllib(self.m_libraryName, 'ScpGetClockOutputFrequencies', self.m_handle, zeros(length, 1), length);
            self.m_library.checkLastStatus();
        end

        function value = get.ClockOutputFrequency(self)
            value = calllib(self.m_libraryName, 'ScpGetClockOutputFrequency', self.m_handle);
            self.m_library.checkLastStatus();
        end

        function set.ClockOutputFrequency(self, value)
            calllib(self.m_libraryName, 'ScpSetClockOutputFrequency', self.m_handle, value);
            self.m_library.checkLastStatus();
        end

        function value = get.SampleFrequencyMax(self)
            value = calllib(self.m_libraryName, 'ScpGetSampleFrequencyMax', self.m_handle);
            self.m_library.checkLastStatus();
        end

        function value = get.SampleFrequency(self)
            value = calllib(self.m_libraryName, 'ScpGetSampleFrequency', self.m_handle);
            self.m_library.checkLastStatus();
        end

        function set.SampleFrequency(self, value)
            calllib(self.m_libraryName, 'ScpSetSampleFrequency', self.m_handle, value);
            self.m_library.checkLastStatus();
        end

        function value = get.RecordLengthMax(self)
            value = calllib(self.m_libraryName, 'ScpGetRecordLengthMax', self.m_handle);
            self.m_library.checkLastStatus();
        end

        function value = get.RecordLength(self)
            value = calllib(self.m_libraryName, 'ScpGetRecordLength', self.m_handle);
            self.m_library.checkLastStatus();
        end

        function set.RecordLength(self, value)
            calllib(self.m_libraryName, 'ScpSetRecordLength', self.m_handle, value);
            self.m_library.checkLastStatus();
        end

        function value = get.PreSampleRatio(self)
            value = calllib(self.m_libraryName, 'ScpGetPreSampleRatio', self.m_handle);
            self.m_library.checkLastStatus();
        end

        function set.PreSampleRatio(self, value)
            calllib(self.m_libraryName, 'ScpSetPreSampleRatio', self.m_handle, value);
            self.m_library.checkLastStatus();
        end

        function value = get.SegmentCountMax(self)
            value = calllib(self.m_libraryName, 'ScpGetSegmentCountMax', self.m_handle);
            self.m_library.checkLastStatus();
        end

        function value = get.SegmentCount(self)
            value = calllib(self.m_libraryName, 'ScpGetSegmentCount', self.m_handle);
            self.m_library.checkLastStatus();
        end

        function set.SegmentCount(self, value)
            calllib(self.m_libraryName, 'ScpSetSegmentCount', self.m_handle, value);
            self.m_library.checkLastStatus();
        end

        function value = get.HasTrigger(self)
            value = calllib(self.m_libraryName, 'ScpHasTrigger', self.m_handle);
            self.m_library.checkLastStatus();
        end

        function value = get.TriggerTimeOut(self)
            value = calllib(self.m_libraryName, 'ScpGetTriggerTimeOut', self.m_handle);
            self.m_library.checkLastStatus();
        end

        function set.TriggerTimeOut(self, value)
            calllib(self.m_libraryName, 'ScpSetTriggerTimeOut', self.m_handle, value);
            self.m_library.checkLastStatus();
        end

        function value = get.HasTriggerDelay(self)
            value = calllib(self.m_libraryName, 'ScpHasTriggerDelay', self.m_handle);
            self.m_library.checkLastStatus();
        end

        function value = get.TriggerDelayMax(self)
            value = calllib(self.m_libraryName, 'ScpGetTriggerDelayMax', self.m_handle);
            self.m_library.checkLastStatus();
        end

        function value = get.TriggerDelay(self)
            value = calllib(self.m_libraryName, 'ScpGetTriggerDelay', self.m_handle);
            self.m_library.checkLastStatus();
        end

        function set.TriggerDelay(self, value)
            calllib(self.m_libraryName, 'ScpSetTriggerDelay', self.m_handle, value);
            self.m_library.checkLastStatus();
        end

        function value = get.HasTriggerHoldOff(self)
            value = calllib(self.m_libraryName, 'ScpHasTriggerHoldOff', self.m_handle);
            self.m_library.checkLastStatus();
        end

        function value = get.TriggerHoldOffCountMax(self)
            value = calllib(self.m_libraryName, 'ScpGetTriggerHoldOffCountMax', self.m_handle);
            self.m_library.checkLastStatus();
        end

        function value = get.TriggerHoldOffCount(self)
            value = calllib(self.m_libraryName, 'ScpGetTriggerHoldOffCount', self.m_handle);
            self.m_library.checkLastStatus();
        end

        function set.TriggerHoldOffCount(self, value)
            calllib(self.m_libraryName, 'ScpSetTriggerHoldOffCount', self.m_handle, value);
            self.m_library.checkLastStatus();
        end

        function value = get.HasConnectionTest(self)
            value = calllib(self.m_libraryName, 'ScpHasConnectionTest', self.m_handle);
            self.m_library.checkLastStatus();
        end

        function value = get.IsConnectionTestCompleted(self)
            value = calllib(self.m_libraryName, 'ScpIsConnectionTestCompleted', self.m_handle);
            self.m_library.checkLastStatus();
        end
    end
end
