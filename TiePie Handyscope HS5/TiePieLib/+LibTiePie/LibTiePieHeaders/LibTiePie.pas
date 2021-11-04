// LibTiePie.pas - Unit for using LibTiePie with Pascal.
//
// (c) TiePie engineering 2021
//
// For API documentation see: http://api.tiepie.com/libtiepie
//
// Website: http://www.tiepie.com

unit LibTiePie;

{$ifdef FPC}
  {$MODE DELPHI}
{$endif FPC}

interface

uses
  {$ifdef MSWINDOWS}
  Windows,
  Messages,
  {$endif MSWINDOWS}
  Types;

const
  LIBTIEPIE_VERSION_MAJOR = 0;
  LIBTIEPIE_VERSION_MINOR = 9;
  LIBTIEPIE_VERSION_RELEASE = 16;
  LIBTIEPIE_VERSION_NUMBER = '0.9.16';

  LIBTIEPIE_VERSION = '0.9.16';
  LIBTIEPIE_REVISION = 14603;

  LIBTIEPIE_HANDLE_INVALID = 0;

  TPDEVICEHANDLE_INVALID = LIBTIEPIE_HANDLE_INVALID deprecated; // Use: #LIBTIEPIE_HANDLE_INVALID

  LIBTIEPIE_INTERFACE_DEVICE = $0000000000000001;
  LIBTIEPIE_INTERFACE_OSCILLOSCOPE = $0000000000000002;
  LIBTIEPIE_INTERFACE_GENERATOR = $0000000000000004;
  LIBTIEPIE_INTERFACE_I2CHOST = $0000000000000008;
  LIBTIEPIE_INTERFACE_SERVER = $0000000000000010;

  DEVICETYPE_OSCILLOSCOPE = $00000001; // Oscilloscope
  DEVICETYPE_GENERATOR = $00000002; // Generator
  DEVICETYPE_I2CHOST = $00000004; // I2C Host
  DEVICETYPE_COUNT = 3; // Number of device types

  IDKIND_PRODUCTID = $00000001; // dwId parameter is a product id.
  IDKIND_INDEX = $00000002; // dwId parameter is an index.
  IDKIND_SERIALNUMBER = $00000004; // dwId parameter is a serial number.
  IDKIND_COUNT = 3; // Number of id kinds

  LIBTIEPIESTATUS_SUCCESS = 0; // The function executed successfully.
  LIBTIEPIESTATUS_VALUE_CLIPPED = 1; // One of the parameters of the last called function was outside the valid range and clipped to the closest limit.
  LIBTIEPIESTATUS_VALUE_MODIFIED = 2; // One of the parameters of the last called function was within the valid range but not available. The closest valid value is set.
  LIBTIEPIESTATUS_UNSUCCESSFUL = -1; // An error occurred during execution of the last called function.
  LIBTIEPIESTATUS_NOT_SUPPORTED = -2; // The requested functionality is not supported by the hardware.
  LIBTIEPIESTATUS_INVALID_HANDLE = -3; // The handle to the device is invalid.
  LIBTIEPIESTATUS_INVALID_VALUE = -4; // The requested value is invalid.
  LIBTIEPIESTATUS_INVALID_CHANNEL = -5; // The requested channel number is invalid.
  LIBTIEPIESTATUS_INVALID_TRIGGER_SOURCE = -6; // The requested trigger source is invalid.
  LIBTIEPIESTATUS_INVALID_DEVICE_TYPE = -7; // The device type is invalid.
  LIBTIEPIESTATUS_INVALID_DEVICE_INDEX = -8; // The device index is invalid, must be < LstGetCount().
  LIBTIEPIESTATUS_INVALID_PRODUCT_ID = -9; // There is no device with the requested product ID.
  LIBTIEPIESTATUS_INVALID_DEVICE_SERIALNUMBER = -10; // There is no device with the requested serial number.
  LIBTIEPIESTATUS_OBJECT_GONE = -11; // The object indicated by the handle is no longer available.
  LIBTIEPIESTATUS_DEVICE_GONE = LIBTIEPIESTATUS_OBJECT_GONE deprecated; // Use: #LIBTIEPIESTATUS_OBJECT_GONE
  LIBTIEPIESTATUS_INTERNAL_ADDRESS = -12; // The requested I2C address is an internally used address in the device.
  LIBTIEPIESTATUS_NOT_CONTROLLABLE = -13; // The generator is currently not controllable, see #GenIsControllable.
  LIBTIEPIESTATUS_BIT_ERROR = -14; // The requested I2C operation generated a bit error.
  LIBTIEPIESTATUS_NO_ACKNOWLEDGE = -15; // The requested I2C operation generated "No acknowledge".
  LIBTIEPIESTATUS_INVALID_CONTAINED_DEVICE_SERIALNUMBER = -16; // A device with the requested serial number is not available in the combined instrument, see #LstDevGetContainedSerialNumbers.
  LIBTIEPIESTATUS_INVALID_INPUT = -17; // The requested trigger input is invalid.
  LIBTIEPIESTATUS_INVALID_OUTPUT = -18; // The requested trigger output is invalid.
  LIBTIEPIESTATUS_INVALID_DRIVER = -19; // The currently installed driver is not supported, see LstDevGetRecommendedDriverVersion(). (Windows only)
  LIBTIEPIESTATUS_NOT_AVAILABLE = -20; // With the current settings, the requested functionality is not available.
  LIBTIEPIESTATUS_INVALID_FIRMWARE = -21; // The currently used firmware is not supported \cond EXTENDED_API , see LstDevGetRecommendedFirmwareVersion() \endcond.
  LIBTIEPIESTATUS_INVALID_INDEX = -22; // The requested index is invalid.
  LIBTIEPIESTATUS_INVALID_EEPROM = -23; // The instrument's EEPROM content is damaged, please contact TiePie engineering support.
  LIBTIEPIESTATUS_INITIALIZATION_FAILED = -24; // The instrument's initialization failed, please contact TiePie engineering support.
  LIBTIEPIESTATUS_LIBRARY_NOT_INITIALIZED = -25; // The library is not initialized, see LibInit().
  LIBTIEPIESTATUS_NO_TRIGGER_ENABLED = -26; // The current setup requires a trigger input to be enabled.
  LIBTIEPIESTATUS_SYNCHRONIZATION_FAILED = -29; // XXX
  LIBTIEPIESTATUS_INVALID_HS56_COMBINED_DEVICE = -30; // At least one Handyscope HS6 DIFF must be located at the beginning or end of the CMI daisy chain.
  LIBTIEPIESTATUS_MEASUREMENT_RUNNING = -31; // A measurement is already running.
  LIBTIEPIESTATUS_INITIALIZATION_ERROR_10001 = -10001; // The instrument's initialization failed (code: 10001), please contact TiePie engineering support.
  LIBTIEPIESTATUS_INITIALIZATION_ERROR_10002 = -10002; // The instrument's initialization failed (code: 10002), please contact TiePie engineering support.
  LIBTIEPIESTATUS_INITIALIZATION_ERROR_10003 = -10003; // The instrument's initialization failed (code: 10003), please contact TiePie engineering support.
  LIBTIEPIESTATUS_INITIALIZATION_ERROR_10004 = -10004; // The instrument's initialization failed (code: 10004), please contact TiePie engineering support.
  LIBTIEPIESTATUS_INITIALIZATION_ERROR_10005 = -10005; // The instrument's initialization failed (code: 10005), please contact TiePie engineering support.
  LIBTIEPIESTATUS_INITIALIZATION_ERROR_10006 = -10006; // The instrument's initialization failed (code: 10006), please contact TiePie engineering support.

  CONNECTORTYPE_UNKNOWN = $00000000;
  CONNECTORTYPE_BNC = $00000001;
  CONNECTORTYPE_BANANA = $00000002;
  CONNECTORTYPE_POWERPLUG = $00000004;
  CONNECTORTYPE_COUNT = 3; // Number of connector types
  CONNECTORTYPE_MASK = ( CONNECTORTYPE_BNC or CONNECTORTYPE_BANANA or CONNECTORTYPE_POWERPLUG );

  DATARAWTYPE_UNKNOWN = $00000000;
  DATARAWTYPE_INT8 = $00000001; // int8_t
  DATARAWTYPE_INT16 = $00000002; // int16_t
  DATARAWTYPE_INT32 = $00000004; // int32_t
  DATARAWTYPE_INT64 = $00000008; // int64_t
  DATARAWTYPE_UINT8 = $00000010; // uint8_t
  DATARAWTYPE_UINT16 = $00000020; // uint16_t
  DATARAWTYPE_UINT32 = $00000040; // uint32_t
  DATARAWTYPE_UINT64 = $00000080; // uint64_t
  DATARAWTYPE_FLOAT32 = $00000100; // float
  DATARAWTYPE_FLOAT64 = $00000200; // double
  DATARAWTYPE_COUNT = 10; // Number of raw data types
  DATARAWTYPE_MASK_INT = ( DATARAWTYPE_INT8 or DATARAWTYPE_INT16 or DATARAWTYPE_INT32 or DATARAWTYPE_INT64 );
  DATARAWTYPE_MASK_UINT = ( DATARAWTYPE_UINT8 or DATARAWTYPE_UINT16 or DATARAWTYPE_UINT32 or DATARAWTYPE_UINT64 );
  DATARAWTYPE_MASK_FLOAT = ( DATARAWTYPE_FLOAT32 or DATARAWTYPE_FLOAT64 );
  DATARAWTYPE_MASK_FIXED = ( DATARAWTYPE_MASK_INT or DATARAWTYPE_MASK_UINT );

  BOOL8_FALSE = 0;
  BOOL8_TRUE = 1;

  LIBTIEPIE_TRISTATE_UNDEFINED = 0; // Undefined
  LIBTIEPIE_TRISTATE_FALSE = 1; // False
  LIBTIEPIE_TRISTATE_TRUE = 2; // True

  LIBTIEPIE_TRIGGERIO_INDEX_INVALID = $FFFF;

  LIBTIEPIE_STRING_LENGTH_NULL_TERMINATED = $FFFFFFFF;

  LIBTIEPIE_SERVER_STATUS_DISCONNECTED = 0;
  LIBTIEPIE_SERVER_STATUS_CONNECTING = 1;
  LIBTIEPIE_SERVER_STATUS_CONNECTED = 2;
  LIBTIEPIE_SERVER_STATUS_DISCONNECTING = 3;
  LIBTIEPIE_SERVER_ERROR_NONE = 0;
  LIBTIEPIE_SERVER_ERROR_UNKNOWN = 1;
  LIBTIEPIE_SERVER_ERROR_CONNECTIONREFUSED = 2;
  LIBTIEPIE_SERVER_ERROR_NETWORKUNREACHABLE = 3;
  LIBTIEPIE_SERVER_ERROR_TIMEDOUT = 4;
  LIBTIEPIE_SERVER_ERROR_HOSTNAMELOOKUPFAILED = 5;

  LIBTIEPIE_RANGEINDEX_AUTO = $FFFFFFFF; // Auto ranging

  LIBTIEPIE_POINTER_ARRAY_MAX_LENGTH = 256;

  ARN_COUNT = 3; // Number of auto resolution modes

  ARB_DISABLED = 0;
  ARB_NATIVEONLY = 1;
  ARB_ALL = 2;

  AR_UNKNOWN = 0; // Unknown/invalid mode
  AR_DISABLED = ( 1 shl ARB_DISABLED ); // Resolution does not automatically change.
  AR_NATIVEONLY = ( 1 shl ARB_NATIVEONLY ); // Highest possible native resolution for the current sample frequency is used.
  AR_ALL = ( 1 shl ARB_ALL ); // Highest possible native or enhanced resolution for the current sample frequency is used.

  ARM_NONE = 0;
  ARM_ALL = ( ( 1 shl ARN_COUNT ) - 1 );
  ARM_ENABLED = ( ARM_ALL and not AR_DISABLED );

  CKN_COUNT = 5; // Number of couplings

  CKB_DCV = 0; // Volt DC
  CKB_ACV = 1; // Volt AC
  CKB_DCA = 2; // Ampere DC
  CKB_ACA = 3; // Ampere AC
  CKB_OHM = 4; // Ohm

  CK_UNKNOWN = 0; // Unknown/invalid coupling
  CK_DCV = ( 1 shl CKB_DCV ); // Volt DC
  CK_ACV = ( 1 shl CKB_ACV ); // Volt AC
  CK_DCA = ( 1 shl CKB_DCA ); // Ampere DC
  CK_ACA = ( 1 shl CKB_ACA ); // Ampere AC
  CK_OHM = ( 1 shl CKB_OHM ); // Ohm

  CKM_NONE = 0;
  CKM_V = ( CK_DCV or CK_ACV ); // Volt
  CKM_A = ( CK_DCA or CK_ACA ); // Ampere
  CKM_OHM = ( CK_OHM ); // Ohm
  CKM_ASYMMETRICRANGE = ( CKM_OHM ); // 0 to +Range
  CKM_SYMMETRICRANGE = ( CKM_V or CKM_A ); // -Range to +Range

  CON_COUNT = 3; // Number of clock output types

  COB_DISABLED = 0; // No clock output
  COB_SAMPLE = 1; // Sample clock
  COB_FIXED = 2; // Fixed clock

  CO_DISABLED = ( 1 shl COB_DISABLED ); // No clock output
  CO_SAMPLE = ( 1 shl COB_SAMPLE ); // Sample clock
  CO_FIXED = ( 1 shl COB_FIXED ); // Fixed clock

  COM_NONE = 0;
  COM_ALL = ( ( 1 shl CON_COUNT ) - 1 );
  COM_ENABLED = ( COM_ALL and not CO_DISABLED );
  COM_FREQUENCY = ( CO_FIXED );

  CSN_COUNT = 2; // Number of clock sources

  CSB_EXTERNAL = 0; // External clock
  CSB_INTERNAL = 1; // Internal clock

  CS_EXTERNAL = ( 1 shl CSB_EXTERNAL ); // External clock
  CS_INTERNAL = ( 1 shl CSB_INTERNAL ); // Internal clock

  CSM_NONE = 0;
  CSM_ALL = ( ( 1 shl CSN_COUNT ) - 1 );
  CSM_FREQUENCY = ( CS_EXTERNAL );

  FMN_COUNT = 2; // Number of frequency modes

  FMB_SIGNALFREQUENCY = 0;
  FMB_SAMPLEFREQUENCY = 1;

  FM_UNKNOWN = $00000000;
  FM_SIGNALFREQUENCY = ( 1 shl FMB_SIGNALFREQUENCY );
  FM_SAMPLEFREQUENCY = ( 1 shl FMB_SAMPLEFREQUENCY );

  FMM_NONE = $00000000;
  FMM_ALL = ( ( 1 shl FMN_COUNT ) - 1 );

  GMN_COUNT = 12; // Number of generator modes

  GMB_CONTINUOUS = 0;
  GMB_BURST_COUNT = 1;
  GMB_GATED_PERIODS = 2;
  GMB_GATED = 3;
  GMB_GATED_PERIOD_START = 4;
  GMB_GATED_PERIOD_FINISH = 5;
  GMB_GATED_RUN = 6;
  GMB_GATED_RUN_OUTPUT = 7;
  GMB_BURST_SAMPLE_COUNT = 8;
  GMB_BURST_SAMPLE_COUNT_OUTPUT = 9;
  GMB_BURST_SEGMENT_COUNT = 10;
  GMB_BURST_SEGMENT_COUNT_OUTPUT = 11;

  GM_UNKNOWN = 0;
  GM_CONTINUOUS = ( 1 shl GMB_CONTINUOUS );
  GM_BURST_COUNT = ( 1 shl GMB_BURST_COUNT );
  GM_GATED_PERIODS = ( 1 shl GMB_GATED_PERIODS );
  GM_GATED = ( 1 shl GMB_GATED );
  GM_GATED_PERIOD_START = ( 1 shl GMB_GATED_PERIOD_START );
  GM_GATED_PERIOD_FINISH = ( 1 shl GMB_GATED_PERIOD_FINISH );
  GM_GATED_RUN = ( 1 shl GMB_GATED_RUN );
  GM_GATED_RUN_OUTPUT = ( 1 shl GMB_GATED_RUN_OUTPUT );
  GM_BURST_SAMPLE_COUNT = ( 1 shl GMB_BURST_SAMPLE_COUNT );
  GM_BURST_SAMPLE_COUNT_OUTPUT = ( 1 shl GMB_BURST_SAMPLE_COUNT_OUTPUT );
  GM_BURST_SEGMENT_COUNT = ( 1 shl GMB_BURST_SEGMENT_COUNT );
  GM_BURST_SEGMENT_COUNT_OUTPUT = ( 1 shl GMB_BURST_SEGMENT_COUNT_OUTPUT );

  GMM_NONE = 0;
  GMM_BURST_COUNT = ( GM_BURST_COUNT );
  GMM_GATED = ( GM_GATED_PERIODS or GM_GATED or GM_GATED_PERIOD_START or GM_GATED_PERIOD_FINISH or GM_GATED_RUN or GM_GATED_RUN_OUTPUT );
  GMM_BURST_SAMPLE_COUNT = ( GM_BURST_SAMPLE_COUNT or GM_BURST_SAMPLE_COUNT_OUTPUT );
  GMM_BURST_SEGMENT_COUNT = ( GM_BURST_SEGMENT_COUNT or GM_BURST_SEGMENT_COUNT_OUTPUT );
  GMM_BURST = ( GMM_BURST_COUNT or GMM_BURST_SAMPLE_COUNT or GMM_BURST_SEGMENT_COUNT );
  GMM_REQUIRE_TRIGGER = ( GMM_GATED or GMM_BURST_SAMPLE_COUNT or GMM_BURST_SEGMENT_COUNT ); // Generator modes that require an enabeld trigger input.
  GMM_ALL = ( ( 1 shl GMN_COUNT ) - 1 );
  GMM_SIGNALFREQUENCY = ( GMM_ALL and not GMM_BURST_SAMPLE_COUNT ); // Supported generator modes when frequency mode is signal frequency.
  GMM_SAMPLEFREQUENCY = ( GMM_ALL ); // Supported generator modes when frequency mode is sample frequency.
  GMM_SINE = ( GMM_SIGNALFREQUENCY ); // Supported generator modes when signal type is sine.
  GMM_TRIANGLE = ( GMM_SIGNALFREQUENCY ); // Supported generator modes when signal type is triangle.
  GMM_SQUARE = ( GMM_SIGNALFREQUENCY ); // Supported generator modes when signal type is square.
  GMM_DC = ( GM_CONTINUOUS ); // Supported generator modes when signal type is DC.
  GMM_NOISE = ( GM_CONTINUOUS or GM_GATED ); // Supported generator modes when signal type is noise.
  GMM_ARBITRARY = ( GMM_SIGNALFREQUENCY or GMM_SAMPLEFREQUENCY ); // Supported generator modes when signal type is arbitrary.
  GMM_PULSE = ( GMM_SIGNALFREQUENCY and not GMM_BURST_SEGMENT_COUNT ); // Supported generator modes when signal type is pulse.

  GSN_COUNT = 4; // The number of generator status flags.

  GSB_STOPPED = 0;
  GSB_RUNNING = 1;
  GSB_BURSTACTIVE = 2;
  GSB_WAITING = 3;

  GS_STOPPED = ( 1 shl GSB_STOPPED ); // The signal generation is stopped.
  GS_RUNNING = ( 1 shl GSB_RUNNING ); // The signal generation is running.
  GS_BURSTACTIVE = ( 1 shl GSB_BURSTACTIVE ); // The generator is operating in burst mode.
  GS_WAITING = ( 1 shl GSB_WAITING ); // The generator is waiting for a burst to be started.

  GSM_NONE = 0;
  GSM_ALL = ( ( 1 shl GSN_COUNT ) - 1 );

  MMN_COUNT = 2; // Number of measure modes

  MMB_STREAM = 0; // Stream mode bit number
  MMB_BLOCK = 1; // Block mode bit number

  MMM_NONE = 0;
  MMM_ALL = ( ( 1 shl MMN_COUNT ) - 1 );

  MM_UNKNOWN = 0; // Unknown/invalid mode
  MM_STREAM = ( 1 shl MMB_STREAM ); // Stream mode
  MM_BLOCK = ( 1 shl MMB_BLOCK ); // Block mode

  STN_COUNT = 7; // Number of signal types

  STB_SINE = 0;
  STB_TRIANGLE = 1;
  STB_SQUARE = 2;
  STB_DC = 3;
  STB_NOISE = 4;
  STB_ARBITRARY = 5;
  STB_PULSE = 6;

  ST_UNKNOWN = 0;
  ST_SINE = ( 1 shl STB_SINE );
  ST_TRIANGLE = ( 1 shl STB_TRIANGLE );
  ST_SQUARE = ( 1 shl STB_SQUARE );
  ST_DC = ( 1 shl STB_DC );
  ST_NOISE = ( 1 shl STB_NOISE );
  ST_ARBITRARY = ( 1 shl STB_ARBITRARY );
  ST_PULSE = ( 1 shl STB_PULSE );

  STM_NONE = 0;
  STM_AMPLITUDE = ( ST_SINE or ST_TRIANGLE or ST_SQUARE or ST_NOISE or ST_ARBITRARY or ST_PULSE );
  STM_OFFSET = ( ST_SINE or ST_TRIANGLE or ST_SQUARE or ST_DC or ST_NOISE or ST_ARBITRARY or ST_PULSE );
  STM_FREQUENCY = ( ST_SINE or ST_TRIANGLE or ST_SQUARE or ST_NOISE or ST_ARBITRARY or ST_PULSE );
  STM_PHASE = ( ST_SINE or ST_TRIANGLE or ST_SQUARE or ST_ARBITRARY or ST_PULSE );
  STM_SYMMETRY = ( ST_SINE or ST_TRIANGLE or ST_SQUARE );
  STM_WIDTH = ( ST_PULSE );
  STM_LEADINGEDGETIME = ( ST_PULSE );
  STM_TRAILINGEDGETIME = ( ST_PULSE );
  STM_DATALENGTH = ( ST_ARBITRARY );
  STM_DATA = ( ST_ARBITRARY );
  STM_EDGETIME = ( STM_LEADINGEDGETIME and STM_TRAILINGEDGETIME );

  TCN_COUNT = 5; // Number of trigger conditions

  TCB_NONE = 0;
  TCB_SMALLER = 1;
  TCB_LARGER = 2;
  TCB_INSIDE = 3;
  TCB_OUTSIDE = 4;

  TC_UNKNOWN = 0;
  TC_NONE = ( 1 shl TCB_NONE );
  TC_SMALLER = ( 1 shl TCB_SMALLER );
  TC_LARGER = ( 1 shl TCB_LARGER );
  TC_INSIDE = ( 1 shl TCB_INSIDE );
  TC_OUTSIDE = ( 1 shl TCB_OUTSIDE );

  TCM_NONE = 0; // No conditions
  TCM_ALL = ( ( 1 shl TCN_COUNT ) - 1 ); // All conditions
  TCM_ENABLED = ( TCM_ALL and not TC_NONE ); // All conditions except #TC_NONE.

  TH_ALLPRESAMPLES = $FFFFFFFFFFFFFFFF; // Trigger hold off to all presamples valid

  DN_MAIN = 0; // The device itself.
  DN_SUB_FIRST = 1; // First sub device in a combined device.
  DN_SUB_SECOND = 2; // Second sub device in a combined device.

  PGID_OSCILLOSCOPE = 1; // Oscilloscope
  PGID_GENERATOR = 2; // Generator
  PGID_EXTERNAL_DSUB = 3; // External D-sub

  SGID_MAIN = 0; // The oscilloscope or function generator itself.
  SGID_CHANNEL1 = 1;
  SGID_CHANNEL2 = 2;
  SGID_PIN1 = 1;
  SGID_PIN2 = 2;
  SGID_PIN3 = 3;

  FID_SCP_TRIGGERED = 0;
  FID_GEN_START = 0;
  FID_GEN_STOP = 1;
  FID_GEN_NEW_PERIOD = 2;
  FID_EXT_TRIGGERED = 0;

  TIOID_SHIFT_PGID = 20;
  TIOID_SHIFT_DN = 24;
  TIOID_SHIFT_SGID = 8;
  TIOID_SHIFT_FID = 0;

  TIID_INVALID = 0;
  TIID_EXT1 = ( ( DN_MAIN shl TIOID_SHIFT_DN ) or ( ( PGID_EXTERNAL_DSUB ) shl TIOID_SHIFT_PGID ) or ( ( SGID_PIN1 ) shl TIOID_SHIFT_SGID ) or ( ( FID_EXT_TRIGGERED ) shl TIOID_SHIFT_FID ) );
  TIID_EXT2 = ( ( DN_MAIN shl TIOID_SHIFT_DN ) or ( ( PGID_EXTERNAL_DSUB ) shl TIOID_SHIFT_PGID ) or ( ( SGID_PIN2 ) shl TIOID_SHIFT_SGID ) or ( ( FID_EXT_TRIGGERED ) shl TIOID_SHIFT_FID ) );
  TIID_EXT3 = ( ( DN_MAIN shl TIOID_SHIFT_DN ) or ( ( PGID_EXTERNAL_DSUB ) shl TIOID_SHIFT_PGID ) or ( ( SGID_PIN3 ) shl TIOID_SHIFT_SGID ) or ( ( FID_EXT_TRIGGERED ) shl TIOID_SHIFT_FID ) );
  TIID_GENERATOR_START = ( ( DN_MAIN shl TIOID_SHIFT_DN ) or ( ( PGID_GENERATOR ) shl TIOID_SHIFT_PGID ) or ( ( SGID_MAIN ) shl TIOID_SHIFT_SGID ) or ( ( FID_GEN_START ) shl TIOID_SHIFT_FID ) );
  TIID_GENERATOR_STOP = ( ( DN_MAIN shl TIOID_SHIFT_DN ) or ( ( PGID_GENERATOR ) shl TIOID_SHIFT_PGID ) or ( ( SGID_MAIN ) shl TIOID_SHIFT_SGID ) or ( ( FID_GEN_STOP ) shl TIOID_SHIFT_FID ) );
  TIID_GENERATOR_NEW_PERIOD = ( ( DN_MAIN shl TIOID_SHIFT_DN ) or ( ( PGID_GENERATOR ) shl TIOID_SHIFT_PGID ) or ( ( SGID_MAIN ) shl TIOID_SHIFT_SGID ) or ( ( FID_GEN_NEW_PERIOD ) shl TIOID_SHIFT_FID ) );

  TOID_INVALID = 0;
  TOID_EXT1 = ( ( DN_MAIN shl TIOID_SHIFT_DN ) or ( ( PGID_EXTERNAL_DSUB ) shl TIOID_SHIFT_PGID ) or ( ( SGID_PIN1 ) shl TIOID_SHIFT_SGID ) or ( ( FID_EXT_TRIGGERED ) shl TIOID_SHIFT_FID ) );
  TOID_EXT2 = ( ( DN_MAIN shl TIOID_SHIFT_DN ) or ( ( PGID_EXTERNAL_DSUB ) shl TIOID_SHIFT_PGID ) or ( ( SGID_PIN2 ) shl TIOID_SHIFT_SGID ) or ( ( FID_EXT_TRIGGERED ) shl TIOID_SHIFT_FID ) );
  TOID_EXT3 = ( ( DN_MAIN shl TIOID_SHIFT_DN ) or ( ( PGID_EXTERNAL_DSUB ) shl TIOID_SHIFT_PGID ) or ( ( SGID_PIN3 ) shl TIOID_SHIFT_SGID ) or ( ( FID_EXT_TRIGGERED ) shl TIOID_SHIFT_FID ) );

  TKN_COUNT = 15; // Number of trigger kinds

  TKB_RISINGEDGE = 0;
  TKB_FALLINGEDGE = 1;
  TKB_INWINDOW = 2;
  TKB_OUTWINDOW = 3;
  TKB_ANYEDGE = 4;
  TKB_ENTERWINDOW = 5;
  TKB_EXITWINDOW = 6;
  TKB_PULSEWIDTHPOSITIVE = 7;
  TKB_PULSEWIDTHNEGATIVE = 8;
  TKB_PULSEWIDTHEITHER = 9;
  TKB_RUNTPULSEPOSITIVE = 10;
  TKB_RUNTPULSENEGATIVE = 11;
  TKB_RUNTPULSEEITHER = 12;
  TKB_INTERVALRISING = 13;
  TKB_INTERVALFALLING = 14;

  TK_UNKNOWN = 0; // Unknown/invalid trigger kind
  TK_RISINGEDGE = ( 1 shl TKB_RISINGEDGE ); // Rising edge
  TK_FALLINGEDGE = ( 1 shl TKB_FALLINGEDGE ); // Falling edge
  TK_INWINDOW = ( 1 shl TKB_INWINDOW ); // Inside window
  TK_OUTWINDOW = ( 1 shl TKB_OUTWINDOW ); // Outside window
  TK_ANYEDGE = ( 1 shl TKB_ANYEDGE ); // Any edge
  TK_ENTERWINDOW = ( 1 shl TKB_ENTERWINDOW ); // Enter window
  TK_EXITWINDOW = ( 1 shl TKB_EXITWINDOW ); // Exit window
  TK_PULSEWIDTHPOSITIVE = ( 1 shl TKB_PULSEWIDTHPOSITIVE ); // Positive pulse width
  TK_PULSEWIDTHNEGATIVE = ( 1 shl TKB_PULSEWIDTHNEGATIVE ); // Negative pulse width
  TK_PULSEWIDTHEITHER = ( 1 shl TKB_PULSEWIDTHEITHER ); // Positive or negative pulse width
  TK_RUNTPULSEPOSITIVE = ( 1 shl TKB_RUNTPULSEPOSITIVE ); // Positive runt pulse
  TK_RUNTPULSENEGATIVE = ( 1 shl TKB_RUNTPULSENEGATIVE ); // Negative runt pulse
  TK_RUNTPULSEEITHER = ( 1 shl TKB_RUNTPULSEEITHER ); // Positive or negative runt pulse
  TK_INTERVALRISING = ( 1 shl TKB_INTERVALRISING ); // Interval (rising edge)
  TK_INTERVALFALLING = ( 1 shl TKB_INTERVALFALLING ); // Interval (falling edge)

  TKM_NONE = 0; // No trigger kinds
  TKM_EDGE = ( TK_RISINGEDGE or TK_FALLINGEDGE or TK_ANYEDGE ); // All edge triggers
  TKM_WINDOW = ( TK_INWINDOW or TK_OUTWINDOW or TK_ENTERWINDOW or TK_EXITWINDOW ); // All window triggers
  TKM_PULSEWIDTH = ( TK_PULSEWIDTHPOSITIVE or TK_PULSEWIDTHNEGATIVE or TK_PULSEWIDTHEITHER ); // All pulse width triggers
  TKM_RUNTPULSE = ( TK_RUNTPULSEPOSITIVE or TK_RUNTPULSENEGATIVE or TK_RUNTPULSEEITHER ); // All runt pulse triggers
  TKM_PULSE = ( TKM_PULSEWIDTH or TKM_RUNTPULSE ); // All pulse triggers
  TKM_INTERVAL = ( TK_INTERVALRISING or TK_INTERVALFALLING ); // All interval triggers
  TKM_TIME = ( TKM_PULSEWIDTH or TKM_WINDOW or TKM_INTERVAL ); // All trigger kinds that may have a time property.
  TKM_ALL = ( ( 1 shl TKN_COUNT ) - 1 ); // All trigger kinds

  TLMN_COUNT = 2; // Number of trigger level modes

  TLMB_RELATIVE = 0;
  TLMB_ABSOLUTE = 1;

  TLM_UNKNOWN = 0;
  TLM_RELATIVE = ( 1 shl TLMB_RELATIVE );
  TLM_ABSOLUTE = ( 1 shl TLMB_ABSOLUTE );

  TLMM_NONE = 0;
  TLMM_ALL = ( ( 1 shl TLMN_COUNT ) - 1 );

  TO_INFINITY = -1; // No time out

  TOEN_COUNT = 6; // Number of trigger output events

  TOEB_GENERATOR_START = 0;
  TOEB_GENERATOR_STOP = 1;
  TOEB_GENERATOR_NEWPERIOD = 2;
  TOEB_OSCILLOSCOPE_RUNNING = 3;
  TOEB_OSCILLOSCOPE_TRIGGERED = 4;
  TOEB_MANUAL = 5;

  TOE_UNKNOWN = 0;
  TOE_GENERATOR_START = ( 1 shl TOEB_GENERATOR_START );
  TOE_GENERATOR_STOP = ( 1 shl TOEB_GENERATOR_STOP );
  TOE_GENERATOR_NEWPERIOD = ( 1 shl TOEB_GENERATOR_NEWPERIOD );
  TOE_OSCILLOSCOPE_RUNNING = ( 1 shl TOEB_OSCILLOSCOPE_RUNNING );
  TOE_OSCILLOSCOPE_TRIGGERED = ( 1 shl TOEB_OSCILLOSCOPE_TRIGGERED );
  TOE_MANUAL = ( 1 shl TOEB_MANUAL );

  TOEM_NONE = 0; // No trigger output events
  TOEM_GENERATOR = ( TOE_GENERATOR_START or TOE_GENERATOR_STOP or TOE_GENERATOR_NEWPERIOD ); // All generator trigger output events
  TOEM_OSCILLOSCOPE = ( TOE_OSCILLOSCOPE_RUNNING or TOE_OSCILLOSCOPE_TRIGGERED ); // All oscilloscope trigger output events
  TOEM_ALL = ( ( 1 shl TOEN_COUNT ) - 1 ); // All trigger output events

  PID_NONE = 0; // Unknown/invalid ID
  PID_COMBI = 2; // Combined instrument
  PID_HS3 = 13; // Handyscope HS3
  PID_HS4 = 15; // Handyscope HS4
  PID_HP3 = 18; // Handyprobe HP3
  PID_TP450 = 19; // TP450
  PID_HS4D = 20; // Handyscope HS4-DIFF
  PID_HS5 = 22; // Handyscope HS5
  PID_HS6 = 24; // Handyscope HS6
  PID_HS6D = 25; // Handyscope HS6 DIFF
  PID_ATS610004D = 31; // ATS610004D
  PID_ATS605004D = 32; // ATS605004D
  PID_WS6 = 34; // WiFiScope WS6
  PID_WS5 = 35; // WiFiScope WS5
  PID_WS6D = 36; // WiFiScope WS6D
  PID_ATS610004DW = 37; // ATS610004DW
  PID_ATS605004DW = 38; // ATS605004DW
  PID_WS4D = 39; // WiFiScope WS4D
  PID_ATS5004DW = 40; // ATS5004DW

  LIBTIEPIE_EVENTID_INVALID = 0; // This event ID value should not occur.
  LIBTIEPIE_EVENTID_OBJ_REMOVED = 1; // Event ID for the event indicating that an object was removed.
  LIBTIEPIE_EVENTID_SCP_DATAREADY = 2; // Event ID for the event indicating that the oscilloscope measurement is ready.
  LIBTIEPIE_EVENTID_SCP_DATAOVERFLOW = 3; // Event ID for the event indicating that the data overflow occurred during a streaming measurement.
  LIBTIEPIE_EVENTID_SCP_CONNECTIONTESTCOMPLETED = 4; // Event ID for the event indicating that the \ref scp_ct "connection test is ready.
  LIBTIEPIE_EVENTID_SCP_TRIGGERED = 5; // Event ID for the event indicating that the oscilloscope has triggered.
  LIBTIEPIE_EVENTID_GEN_BURSTCOMPLETED = 6; // Event ID for the event indicating that the generator burst is completed.
  LIBTIEPIE_EVENTID_GEN_CONTROLLABLECHANGED = 7; // Event ID for the event indicating that the generator controllable state has changed.
  LIBTIEPIE_EVENTID_SRV_STATUSCHANGED = 8; // XXX
  LIBTIEPIE_EVENTID_SCP_SAFEGROUNDERROR = 9; // Event ID for the event indicating that the oscilloscope channel SafeGround was disabled because of a too large ground current. The value parameter of the event contains the channel number (\c 0 to \c ChannelCount-1).
  LIBTIEPIE_EVENTID_SCP_GETDATAASYNCCOMPLETED = 10; // XXX
  LIBTIEPIE_EVENTID_DEV_BATTERYSTATUSCHANGED = 11; // XXX

  {$ifdef MSWINDOWS}
  WM_LIBTIEPIE = ( WM_USER + 1337 ); // Message number offset used by LibTiePie.
  WM_LIBTIEPIE_LST_DEVICEADDED = ( WM_LIBTIEPIE + 2 ); // See: LstSetMessageDeviceAdded
  WM_LIBTIEPIE_LST_DEVICEREMOVED = ( WM_LIBTIEPIE + 3 ); // See: LstSetMessageDeviceRemoved
  WM_LIBTIEPIE_LST_DEVICECANOPENCHANGED = ( WM_LIBTIEPIE + 9 ); // See: LstSetMessageDeviceCanOpenChanged
  WM_LIBTIEPIE_NETSRV_ADDED = ( WM_LIBTIEPIE + 11 ); // See: NetSrvSetMessageAdded
  WM_LIBTIEPIE_DEV_REMOVED = ( WM_LIBTIEPIE + 4 ) deprecated; // Will be removed in future version, see #ObjSetEventWindowHandle
  WM_LIBTIEPIE_SCP_DATAREADY = ( WM_LIBTIEPIE + 0 ) deprecated; // Will be removed in future version, see #ObjSetEventWindowHandle
  WM_LIBTIEPIE_SCP_DATAOVERFLOW = ( WM_LIBTIEPIE + 1 ) deprecated; // Will be removed in future version, see #ObjSetEventWindowHandle
  WM_LIBTIEPIE_SCP_CONNECTIONTESTCOMPLETED = ( WM_LIBTIEPIE + 7 ) deprecated; // Will be removed in future version, see #ObjSetEventWindowHandle
  WM_LIBTIEPIE_SCP_TRIGGERED = ( WM_LIBTIEPIE + 8 ) deprecated; // Will be removed in future version, see #ObjSetEventWindowHandle
  WM_LIBTIEPIE_GEN_BURSTCOMPLETED = ( WM_LIBTIEPIE + 5 ) deprecated; // Will be removed in future version, see #ObjSetEventWindowHandle
  WM_LIBTIEPIE_GEN_CONTROLLABLECHANGED = ( WM_LIBTIEPIE + 6 ) deprecated; // Will be removed in future version, see #ObjSetEventWindowHandle
  WM_LIBTIEPIE_EVENT = ( WM_LIBTIEPIE + 10 ); // See: ObjSetEventWindowHandle
  {$endif MSWINDOWS}

  {$if defined( LINUX )}
  sLibTiePieFileNameDefault = 'libtiepie.so.0.9.16';
  {$elseif defined( MACOS )}
  sLibTiePieFileNameDefault = 'libtiepie.dylib';
  {$else}
  sLibTiePieFileNameDefault = 'libtiepie';
  {$ifend}

type
  TLibTiePieStatus = LongInt; // LibTiePie status code. See: LIBTIEPIESTATUS_
  TLibTiePieHandle = LongWord; // Generic handle.
  TTpDeviceHandle = TLibTiePieHandle deprecated; // Use: #LibTiePieHandle_t
  TTpVersion = UInt64;
  TTpDate = LongWord;
  TLibTiePieTriState = Byte; // TriState value one byte wide. See: LIBTIEPIE_TRISTATE_
  TLibTiePiePointerArray = PPointer; // Pointer array See: hlp_ptrar
  TTpCallback = procedure( pData : Pointer ); cdecl;
  TTpCallbackMethod = procedure of object; cdecl;
  TTpCallbackDeviceList = procedure( pData : Pointer ; dwDeviceTypes : LongWord ; dwSerialNumber : LongWord ); cdecl;
  TTpCallbackDeviceListMethod = procedure( dwDeviceTypes : LongWord ; dwSerialNumber : LongWord ) of object; cdecl;
  TTpCallbackHandle = procedure( pData : Pointer ; hHandle : TLibTiePieHandle ); cdecl;
  TTpCallbackHandleMethod = procedure( hHandle : TLibTiePieHandle ) of object; cdecl;
  TTpCallbackEvent = procedure( pData : Pointer ; dwEvent : LongWord ; dwValue : LongWord ); cdecl;
  TTpCallbackEventMethod = procedure( dwEvent : LongWord ; dwValue : LongWord ) of object; cdecl;
  PLibTiePieHandle = ^TLibTiePieHandle;
  PByteBool = ^ByteBool;
  PPSingle = ^PSingle;
  PLibTiePieTriState = ^TLibTiePieTriState;
  PUInt64 = ^UInt64;

{$ifdef LIBTIEPIE_DYNAMIC}
type
  TLibInit = procedure; cdecl;
  TLibIsInitialized = function : ByteBool; cdecl;
  TLibExit = procedure; cdecl;
  TLibGetVersion = function : TTpVersion; cdecl;
  TLibGetVersionExtra = function : PAnsiChar; cdecl;
  TLibGetConfig = function( pBuffer : PByte ; dwBufferLength : LongWord ) : LongWord; cdecl;
  TLibGetLastStatus = function : TLibTiePieStatus; cdecl;
  TLibGetLastStatusStr = function : PAnsiChar; cdecl;
  TLstUpdate = procedure; cdecl;
  TLstGetCount = function : LongWord; cdecl;
  TLstOpenDevice = function( dwIdKind : LongWord ; dwId : LongWord ; dwDeviceType : LongWord ) : TLibTiePieHandle; cdecl;
  TLstOpenOscilloscope = function( dwIdKind : LongWord ; dwId : LongWord ) : TLibTiePieHandle; cdecl;
  TLstOpenGenerator = function( dwIdKind : LongWord ; dwId : LongWord ) : TLibTiePieHandle; cdecl;
  TLstOpenI2CHost = function( dwIdKind : LongWord ; dwId : LongWord ) : TLibTiePieHandle; cdecl;
  TLstCreateCombinedDevice = function( pDeviceHandles : PLibTiePieHandle ; dwCount : LongWord ) : LongWord; cdecl;
  TLstCreateAndOpenCombinedDevice = function( pDeviceHandles : PLibTiePieHandle ; dwCount : LongWord ) : TLibTiePieHandle; cdecl;
  TLstRemoveDevice = procedure( dwSerialNumber : LongWord ); cdecl;
  TLstRemoveDeviceForce = procedure( dwSerialNumber : LongWord ); cdecl;
  TLstDevCanOpen = function( dwIdKind : LongWord ; dwId : LongWord ; dwDeviceType : LongWord ) : ByteBool; cdecl;
  TLstDevGetProductId = function( dwIdKind : LongWord ; dwId : LongWord ) : LongWord; cdecl;
  TLstDevGetVendorId = function( dwIdKind : LongWord ; dwId : LongWord ) : LongWord; cdecl;
  TLstDevGetName = function( dwIdKind : LongWord ; dwId : LongWord ; pBuffer : PAnsiChar ; dwBufferLength : LongWord ) : LongWord; cdecl;
  TLstDevGetNameShort = function( dwIdKind : LongWord ; dwId : LongWord ; pBuffer : PAnsiChar ; dwBufferLength : LongWord ) : LongWord; cdecl;
  TLstDevGetNameShortest = function( dwIdKind : LongWord ; dwId : LongWord ; pBuffer : PAnsiChar ; dwBufferLength : LongWord ) : LongWord; cdecl;
  TLstDevGetDriverVersion = function( dwIdKind : LongWord ; dwId : LongWord ) : TTpVersion; cdecl;
  TLstDevGetRecommendedDriverVersion = function( dwIdKind : LongWord ; dwId : LongWord ) : TTpVersion; cdecl;
  TLstDevGetFirmwareVersion = function( dwIdKind : LongWord ; dwId : LongWord ) : TTpVersion; cdecl;
  TLstDevGetRecommendedFirmwareVersion = function( dwIdKind : LongWord ; dwId : LongWord ) : TTpVersion; cdecl;
  TLstDevGetCalibrationDate = function( dwIdKind : LongWord ; dwId : LongWord ) : TTpDate; cdecl;
  TLstDevGetSerialNumber = function( dwIdKind : LongWord ; dwId : LongWord ) : LongWord; cdecl;
  TLstDevGetIPv4Address = function( dwIdKind : LongWord ; dwId : LongWord ) : LongWord; cdecl;
  TLstDevGetIPPort = function( dwIdKind : LongWord ; dwId : LongWord ) : Word; cdecl;
  TLstDevHasServer = function( dwIdKind : LongWord ; dwId : LongWord ) : ByteBool; cdecl;
  TLstDevGetServer = function( dwIdKind : LongWord ; dwId : LongWord ) : TLibTiePieHandle; cdecl;
  TLstDevGetTypes = function( dwIdKind : LongWord ; dwId : LongWord ) : LongWord; cdecl;
  TLstDevGetContainedSerialNumbers = function( dwIdKind : LongWord ; dwId : LongWord ; pBuffer : PLongWord ; dwBufferLength : LongWord ) : LongWord; cdecl;
  TLstCbDevGetProductId = function( dwIdKind : LongWord ; dwId : LongWord ; dwContainedDeviceSerialNumber : LongWord ) : LongWord; cdecl;
  TLstCbDevGetVendorId = function( dwIdKind : LongWord ; dwId : LongWord ; dwContainedDeviceSerialNumber : LongWord ) : LongWord; cdecl;
  TLstCbDevGetName = function( dwIdKind : LongWord ; dwId : LongWord ; dwContainedDeviceSerialNumber : LongWord ; pBuffer : PAnsiChar ; dwBufferLength : LongWord ) : LongWord; cdecl;
  TLstCbDevGetNameShort = function( dwIdKind : LongWord ; dwId : LongWord ; dwContainedDeviceSerialNumber : LongWord ; pBuffer : PAnsiChar ; dwBufferLength : LongWord ) : LongWord; cdecl;
  TLstCbDevGetNameShortest = function( dwIdKind : LongWord ; dwId : LongWord ; dwContainedDeviceSerialNumber : LongWord ; pBuffer : PAnsiChar ; dwBufferLength : LongWord ) : LongWord; cdecl;
  TLstCbDevGetDriverVersion = function( dwIdKind : LongWord ; dwId : LongWord ; dwContainedDeviceSerialNumber : LongWord ) : TTpVersion; cdecl;
  TLstCbDevGetFirmwareVersion = function( dwIdKind : LongWord ; dwId : LongWord ; dwContainedDeviceSerialNumber : LongWord ) : TTpVersion; cdecl;
  TLstCbDevGetCalibrationDate = function( dwIdKind : LongWord ; dwId : LongWord ; dwContainedDeviceSerialNumber : LongWord ) : TTpDate; cdecl;
  TLstCbScpGetChannelCount = function( dwIdKind : LongWord ; dwId : LongWord ; dwContainedDeviceSerialNumber : LongWord ) : Word; cdecl;
  TLstSetCallbackDeviceAdded = procedure( pCallback : TTpCallbackDeviceList ; pData : Pointer ); cdecl;
  TLstSetCallbackDeviceRemoved = procedure( pCallback : TTpCallbackDeviceList ; pData : Pointer ); cdecl;
  TLstSetCallbackDeviceCanOpenChanged = procedure( pCallback : TTpCallbackDeviceList ; pData : Pointer ); cdecl;
  {$ifdef LINUX}
  TLstSetEventDeviceAdded = procedure( fdEvent : Integer ); cdecl;
  TLstSetEventDeviceRemoved = procedure( fdEvent : Integer ); cdecl;
  TLstSetEventDeviceCanOpenChanged = procedure( fdEvent : Integer ); cdecl;
  {$endif LINUX}
  {$ifdef MSWINDOWS}
  TLstSetEventDeviceAdded = procedure( hEvent : THandle ); cdecl;
  TLstSetEventDeviceRemoved = procedure( hEvent : THandle ); cdecl;
  TLstSetEventDeviceCanOpenChanged = procedure( hEvent : THandle ); cdecl;
  TLstSetMessageDeviceAdded = procedure( hWnd : HWND ); cdecl;
  TLstSetMessageDeviceRemoved = procedure( hWnd : HWND ); cdecl;
  TLstSetMessageDeviceCanOpenChanged = procedure( hWnd : HWND ); cdecl;
  {$endif MSWINDOWS}
  TNetGetAutoDetectEnabled = function : ByteBool; cdecl;
  TNetSetAutoDetectEnabled = function( bEnable : ByteBool ) : ByteBool; cdecl;
  TNetSrvAdd = function( pURL : PAnsiChar ; dwURLLength : LongWord ; pHandle : PLibTiePieHandle ) : ByteBool; cdecl;
  TNetSrvRemove = function( pURL : PAnsiChar ; dwURLLength : LongWord ; bForce : ByteBool ) : ByteBool; cdecl;
  TNetSrvGetCount = function : LongWord; cdecl;
  TNetSrvGetByIndex = function( dwIndex : LongWord ) : TLibTiePieHandle; cdecl;
  TNetSrvGetByURL = function( pURL : PAnsiChar ; dwURLLength : LongWord ) : TLibTiePieHandle; cdecl;
  TNetSrvSetCallbackAdded = procedure( pCallback : TTpCallbackHandle ; pData : Pointer ); cdecl;
  {$ifdef LINUX}
  TNetSrvSetEventAdded = procedure( fdEvent : Integer ); cdecl;
  {$endif LINUX}
  {$ifdef MSWINDOWS}
  TNetSrvSetEventAdded = procedure( hEvent : THandle ); cdecl;
  TNetSrvSetMessageAdded = procedure( hWnd : HWND ); cdecl;
  {$endif MSWINDOWS}
  TObjClose = procedure( hHandle : TLibTiePieHandle ); cdecl;
  TObjIsRemoved = function( hHandle : TLibTiePieHandle ) : ByteBool; cdecl;
  TObjGetInterfaces = function( hHandle : TLibTiePieHandle ) : UInt64; cdecl;
  TObjSetEventCallback = procedure( hHandle : TLibTiePieHandle ; pCallback : TTpCallbackEvent ; pData : Pointer ); cdecl;
  TObjGetEvent = function( hHandle : TLibTiePieHandle ; pEvent : PLongWord ; pValue : PLongWord ) : ByteBool; cdecl;
  {$ifdef LINUX}
  TObjSetEventEvent = procedure( hHandle : TLibTiePieHandle ; fdEvent : Integer ); cdecl;
  {$endif LINUX}
  {$ifdef MSWINDOWS}
  TObjSetEventEvent = procedure( hHandle : TLibTiePieHandle ; hEvent : THandle ); cdecl;
  TObjSetEventWindowHandle = procedure( hHandle : TLibTiePieHandle ; hWnd : HWND ); cdecl;
  {$endif MSWINDOWS}
  TDevClose = procedure( hDevice : TLibTiePieHandle ); cdecl;
  TDevIsRemoved = function( hDevice : TLibTiePieHandle ) : ByteBool; cdecl;
  TDevGetDriverVersion = function( hDevice : TLibTiePieHandle ) : TTpVersion; cdecl;
  TDevGetFirmwareVersion = function( hDevice : TLibTiePieHandle ) : TTpVersion; cdecl;
  TDevGetCalibrationDate = function( hDevice : TLibTiePieHandle ) : TTpDate; cdecl;
  TDevGetCalibrationToken = function( hDevice : TLibTiePieHandle ; pBuffer : PAnsiChar ; dwBufferLength : LongWord ) : LongWord; cdecl;
  TDevGetSerialNumber = function( hDevice : TLibTiePieHandle ) : LongWord; cdecl;
  TDevGetIPv4Address = function( hDevice : TLibTiePieHandle ) : LongWord; cdecl;
  TDevGetIPPort = function( hDevice : TLibTiePieHandle ) : Word; cdecl;
  TDevGetProductId = function( hDevice : TLibTiePieHandle ) : LongWord; cdecl;
  TDevGetVendorId = function( hDevice : TLibTiePieHandle ) : LongWord; cdecl;
  TDevGetType = function( hDevice : TLibTiePieHandle ) : LongWord; cdecl;
  TDevGetName = function( hDevice : TLibTiePieHandle ; pBuffer : PAnsiChar ; dwBufferLength : LongWord ) : LongWord; cdecl;
  TDevGetNameShort = function( hDevice : TLibTiePieHandle ; pBuffer : PAnsiChar ; dwBufferLength : LongWord ) : LongWord; cdecl;
  TDevGetNameShortest = function( hDevice : TLibTiePieHandle ; pBuffer : PAnsiChar ; dwBufferLength : LongWord ) : LongWord; cdecl;
  TDevHasBattery = function( hDevice : TLibTiePieHandle ) : ByteBool; cdecl;
  TDevGetBatteryCharge = function( hDevice : TLibTiePieHandle ) : ShortInt; cdecl;
  TDevGetBatteryTimeToEmpty = function( hDevice : TLibTiePieHandle ) : LongInt; cdecl;
  TDevGetBatteryTimeToFull = function( hDevice : TLibTiePieHandle ) : LongInt; cdecl;
  TDevIsBatteryChargerConnected = function( hDevice : TLibTiePieHandle ) : ByteBool; cdecl;
  TDevIsBatteryCharging = function( hDevice : TLibTiePieHandle ) : ByteBool; cdecl;
  TDevIsBatteryBroken = function( hDevice : TLibTiePieHandle ) : ByteBool; cdecl;
  TDevSetCallbackRemoved = procedure( hDevice : TLibTiePieHandle ; pCallback : TTpCallback ; pData : Pointer ); cdecl;
  {$ifdef LINUX}
  TDevSetEventRemoved = procedure( hDevice : TLibTiePieHandle ; fdEvent : Integer ); cdecl;
  {$endif LINUX}
  {$ifdef MSWINDOWS}
  TDevSetEventRemoved = procedure( hDevice : TLibTiePieHandle ; hEvent : THandle ); cdecl;
  TDevSetMessageRemoved = procedure( hDevice : TLibTiePieHandle ; hWnd : HWND ; wParam : WPARAM ; lParam : LPARAM ); cdecl;
  {$endif MSWINDOWS}
  TDevTrGetInputCount = function( hDevice : TLibTiePieHandle ) : Word; cdecl;
  TDevTrGetInputIndexById = function( hDevice : TLibTiePieHandle ; dwId : LongWord ) : Word; cdecl;
  TScpTrInIsTriggered = function( hDevice : TLibTiePieHandle ; wInput : Word ) : ByteBool; cdecl;
  TDevTrInGetEnabled = function( hDevice : TLibTiePieHandle ; wInput : Word ) : ByteBool; cdecl;
  TDevTrInSetEnabled = function( hDevice : TLibTiePieHandle ; wInput : Word ; bEnable : ByteBool ) : ByteBool; cdecl;
  TDevTrInGetKinds = function( hDevice : TLibTiePieHandle ; wInput : Word ) : UInt64; cdecl;
  TScpTrInGetKindsEx = function( hDevice : TLibTiePieHandle ; wInput : Word ; dwMeasureMode : LongWord ) : UInt64; cdecl;
  TDevTrInGetKind = function( hDevice : TLibTiePieHandle ; wInput : Word ) : UInt64; cdecl;
  TDevTrInSetKind = function( hDevice : TLibTiePieHandle ; wInput : Word ; qwKind : UInt64 ) : UInt64; cdecl;
  TDevTrInIsAvailable = function( hDevice : TLibTiePieHandle ; wInput : Word ) : ByteBool; cdecl;
  TScpTrInIsAvailableEx = function( hDevice : TLibTiePieHandle ; wInput : Word ; dwMeasureMode : LongWord ) : ByteBool; cdecl;
  TDevTrInGetId = function( hDevice : TLibTiePieHandle ; wInput : Word ) : LongWord; cdecl;
  TDevTrInGetName = function( hDevice : TLibTiePieHandle ; wInput : Word ; pBuffer : PAnsiChar ; dwBufferLength : LongWord ) : LongWord; cdecl;
  TDevTrGetOutputCount = function( hDevice : TLibTiePieHandle ) : Word; cdecl;
  TDevTrGetOutputIndexById = function( hDevice : TLibTiePieHandle ; dwId : LongWord ) : Word; cdecl;
  TDevTrOutGetEnabled = function( hDevice : TLibTiePieHandle ; wOutput : Word ) : ByteBool; cdecl;
  TDevTrOutSetEnabled = function( hDevice : TLibTiePieHandle ; wOutput : Word ; bEnable : ByteBool ) : ByteBool; cdecl;
  TDevTrOutGetEvents = function( hDevice : TLibTiePieHandle ; wOutput : Word ) : UInt64; cdecl;
  TDevTrOutGetEvent = function( hDevice : TLibTiePieHandle ; wOutput : Word ) : UInt64; cdecl;
  TDevTrOutSetEvent = function( hDevice : TLibTiePieHandle ; wOutput : Word ; qwEvent : UInt64 ) : UInt64; cdecl;
  TDevTrOutGetId = function( hDevice : TLibTiePieHandle ; wOutput : Word ) : LongWord; cdecl;
  TDevTrOutGetName = function( hDevice : TLibTiePieHandle ; wOutput : Word ; pBuffer : PAnsiChar ; dwBufferLength : LongWord ) : LongWord; cdecl;
  TDevTrOutTrigger = function( hDevice : TLibTiePieHandle ; wOutput : Word ) : ByteBool; cdecl;
  TScpGetChannelCount = function( hDevice : TLibTiePieHandle ) : Word; cdecl;
  TScpChIsAvailable = function( hDevice : TLibTiePieHandle ; wCh : Word ) : ByteBool; cdecl;
  TScpChIsAvailableEx = function( hDevice : TLibTiePieHandle ; wCh : Word ; dwMeasureMode : LongWord ; dSampleFrequency : Double ; byResolution : Byte ; pChannelEnabled : PByteBool ; wChannelCount : Word ) : ByteBool; cdecl;
  TScpChGetConnectorType = function( hDevice : TLibTiePieHandle ; wCh : Word ) : LongWord; cdecl;
  TScpChIsDifferential = function( hDevice : TLibTiePieHandle ; wCh : Word ) : ByteBool; cdecl;
  TScpChGetImpedance = function( hDevice : TLibTiePieHandle ; wCh : Word ) : Double; cdecl;
  TScpChGetBandwidths = function( hDevice : TLibTiePieHandle ; wCh : Word ; pList : PDouble ; dwLength : LongWord ) : LongWord; cdecl;
  TScpChGetBandwidth = function( hDevice : TLibTiePieHandle ; wCh : Word ) : Double; cdecl;
  TScpChSetBandwidth = function( hDevice : TLibTiePieHandle ; wCh : Word ; dBandwidth : Double ) : Double; cdecl;
  TScpChGetCouplings = function( hDevice : TLibTiePieHandle ; wCh : Word ) : UInt64; cdecl;
  TScpChGetCoupling = function( hDevice : TLibTiePieHandle ; wCh : Word ) : UInt64; cdecl;
  TScpChSetCoupling = function( hDevice : TLibTiePieHandle ; wCh : Word ; qwCoupling : UInt64 ) : UInt64; cdecl;
  TScpChGetEnabled = function( hDevice : TLibTiePieHandle ; wCh : Word ) : ByteBool; cdecl;
  TScpChSetEnabled = function( hDevice : TLibTiePieHandle ; wCh : Word ; bEnable : ByteBool ) : ByteBool; cdecl;
  TScpChGetProbeGain = function( hDevice : TLibTiePieHandle ; wCh : Word ) : Double; cdecl;
  TScpChSetProbeGain = function( hDevice : TLibTiePieHandle ; wCh : Word ; dProbeGain : Double ) : Double; cdecl;
  TScpChGetProbeOffset = function( hDevice : TLibTiePieHandle ; wCh : Word ) : Double; cdecl;
  TScpChSetProbeOffset = function( hDevice : TLibTiePieHandle ; wCh : Word ; dProbeOffset : Double ) : Double; cdecl;
  TScpChGetAutoRanging = function( hDevice : TLibTiePieHandle ; wCh : Word ) : ByteBool; cdecl;
  TScpChSetAutoRanging = function( hDevice : TLibTiePieHandle ; wCh : Word ; bEnable : ByteBool ) : ByteBool; cdecl;
  TScpChGetRanges = function( hDevice : TLibTiePieHandle ; wCh : Word ; pList : PDouble ; dwLength : LongWord ) : LongWord; cdecl;
  TScpChGetRangesEx = function( hDevice : TLibTiePieHandle ; wCh : Word ; qwCoupling : UInt64 ; pList : PDouble ; dwLength : LongWord ) : LongWord; cdecl;
  TScpChGetRange = function( hDevice : TLibTiePieHandle ; wCh : Word ) : Double; cdecl;
  TScpChSetRange = function( hDevice : TLibTiePieHandle ; wCh : Word ; dRange : Double ) : Double; cdecl;
  TScpChHasSafeGround = function( hDevice : TLibTiePieHandle ; wCh : Word ) : ByteBool; cdecl;
  TScpChGetSafeGroundEnabled = function( hDevice : TLibTiePieHandle ; wCh : Word ) : ByteBool; cdecl;
  TScpChSetSafeGroundEnabled = function( hDevice : TLibTiePieHandle ; wCh : Word ; bEnable : ByteBool ) : ByteBool; cdecl;
  TScpChGetSafeGroundThresholdMin = function( hDevice : TLibTiePieHandle ; wCh : Word ) : Double; cdecl;
  TScpChGetSafeGroundThresholdMax = function( hDevice : TLibTiePieHandle ; wCh : Word ) : Double; cdecl;
  TScpChGetSafeGroundThreshold = function( hDevice : TLibTiePieHandle ; wCh : Word ) : Double; cdecl;
  TScpChSetSafeGroundThreshold = function( hDevice : TLibTiePieHandle ; wCh : Word ; dThreshold : Double ) : Double; cdecl;
  TScpChVerifySafeGroundThreshold = function( hDevice : TLibTiePieHandle ; wCh : Word ; dThreshold : Double ) : Double; cdecl;
  TScpChHasTrigger = function( hDevice : TLibTiePieHandle ; wCh : Word ) : ByteBool; cdecl;
  TScpChHasTriggerEx = function( hDevice : TLibTiePieHandle ; wCh : Word ; dwMeasureMode : LongWord ) : ByteBool; cdecl;
  TScpChTrIsAvailable = function( hDevice : TLibTiePieHandle ; wCh : Word ) : ByteBool; cdecl;
  TScpChTrIsAvailableEx = function( hDevice : TLibTiePieHandle ; wCh : Word ; dwMeasureMode : LongWord ; dSampleFrequency : Double ; byResolution : Byte ; pChannelEnabled : PByteBool ; pChannelTriggerEnabled : PByteBool ; wChannelCount : Word ) : ByteBool; cdecl;
  TScpChTrIsTriggered = function( hDevice : TLibTiePieHandle ; wCh : Word ) : ByteBool; cdecl;
  TScpChTrGetEnabled = function( hDevice : TLibTiePieHandle ; wCh : Word ) : ByteBool; cdecl;
  TScpChTrSetEnabled = function( hDevice : TLibTiePieHandle ; wCh : Word ; bEnable : ByteBool ) : ByteBool; cdecl;
  TScpChTrGetKinds = function( hDevice : TLibTiePieHandle ; wCh : Word ) : UInt64; cdecl;
  TScpChTrGetKindsEx = function( hDevice : TLibTiePieHandle ; wCh : Word ; dwMeasureMode : LongWord ) : UInt64; cdecl;
  TScpChTrGetKind = function( hDevice : TLibTiePieHandle ; wCh : Word ) : UInt64; cdecl;
  TScpChTrSetKind = function( hDevice : TLibTiePieHandle ; wCh : Word ; qwTriggerKind : UInt64 ) : UInt64; cdecl;
  TScpChTrGetLevelModes = function( hDevice : TLibTiePieHandle ; wCh : Word ) : LongWord; cdecl;
  TScpChTrGetLevelMode = function( hDevice : TLibTiePieHandle ; wCh : Word ) : LongWord; cdecl;
  TScpChTrSetLevelMode = function( hDevice : TLibTiePieHandle ; wCh : Word ; dwLevelMode : LongWord ) : LongWord; cdecl;
  TScpChTrGetLevelCount = function( hDevice : TLibTiePieHandle ; wCh : Word ) : LongWord; cdecl;
  TScpChTrGetLevel = function( hDevice : TLibTiePieHandle ; wCh : Word ; dwIndex : LongWord ) : Double; cdecl;
  TScpChTrSetLevel = function( hDevice : TLibTiePieHandle ; wCh : Word ; dwIndex : LongWord ; dLevel : Double ) : Double; cdecl;
  TScpChTrGetHysteresisCount = function( hDevice : TLibTiePieHandle ; wCh : Word ) : LongWord; cdecl;
  TScpChTrGetHysteresis = function( hDevice : TLibTiePieHandle ; wCh : Word ; dwIndex : LongWord ) : Double; cdecl;
  TScpChTrSetHysteresis = function( hDevice : TLibTiePieHandle ; wCh : Word ; dwIndex : LongWord ; dHysteresis : Double ) : Double; cdecl;
  TScpChTrGetConditions = function( hDevice : TLibTiePieHandle ; wCh : Word ) : LongWord; cdecl;
  TScpChTrGetConditionsEx = function( hDevice : TLibTiePieHandle ; wCh : Word ; dwMeasureMode : LongWord ; qwTriggerKind : UInt64 ) : LongWord; cdecl;
  TScpChTrGetCondition = function( hDevice : TLibTiePieHandle ; wCh : Word ) : LongWord; cdecl;
  TScpChTrSetCondition = function( hDevice : TLibTiePieHandle ; wCh : Word ; dwCondition : LongWord ) : LongWord; cdecl;
  TScpChTrGetTimeCount = function( hDevice : TLibTiePieHandle ; wCh : Word ) : LongWord; cdecl;
  TScpChTrGetTime = function( hDevice : TLibTiePieHandle ; wCh : Word ; dwIndex : LongWord ) : Double; cdecl;
  TScpChTrSetTime = function( hDevice : TLibTiePieHandle ; wCh : Word ; dwIndex : LongWord ; dTime : Double ) : Double; cdecl;
  TScpChTrVerifyTime = function( hDevice : TLibTiePieHandle ; wCh : Word ; dwIndex : LongWord ; dTime : Double ) : Double; cdecl;
  TScpChTrVerifyTimeEx2 = function( hDevice : TLibTiePieHandle ; wCh : Word ; dwIndex : LongWord ; dTime : Double ; dwMeasureMode : LongWord ; dSampleFrequency : Double ; qwTriggerKind : UInt64 ; dwCondition : LongWord ) : Double; cdecl;
  TScpGetData = function( hDevice : TLibTiePieHandle ; pBuffers : PPSingle ; wChannelCount : Word ; qwStartIndex : UInt64 ; qwSampleCount : UInt64 ) : UInt64; cdecl;
  TScpGetData1Ch = function( hDevice : TLibTiePieHandle ; pBufferCh1 : PSingle ; qwStartIndex : UInt64 ; qwSampleCount : UInt64 ) : UInt64; cdecl;
  TScpGetData2Ch = function( hDevice : TLibTiePieHandle ; pBufferCh1 : PSingle ; pBufferCh2 : PSingle ; qwStartIndex : UInt64 ; qwSampleCount : UInt64 ) : UInt64; cdecl;
  TScpGetData3Ch = function( hDevice : TLibTiePieHandle ; pBufferCh1 : PSingle ; pBufferCh2 : PSingle ; pBufferCh3 : PSingle ; qwStartIndex : UInt64 ; qwSampleCount : UInt64 ) : UInt64; cdecl;
  TScpGetData4Ch = function( hDevice : TLibTiePieHandle ; pBufferCh1 : PSingle ; pBufferCh2 : PSingle ; pBufferCh3 : PSingle ; pBufferCh4 : PSingle ; qwStartIndex : UInt64 ; qwSampleCount : UInt64 ) : UInt64; cdecl;
  TScpGetData5Ch = function( hDevice : TLibTiePieHandle ; pBufferCh1 : PSingle ; pBufferCh2 : PSingle ; pBufferCh3 : PSingle ; pBufferCh4 : PSingle ; pBufferCh5 : PSingle ; qwStartIndex : UInt64 ; qwSampleCount : UInt64 ) : UInt64; cdecl;
  TScpGetData6Ch = function( hDevice : TLibTiePieHandle ; pBufferCh1 : PSingle ; pBufferCh2 : PSingle ; pBufferCh3 : PSingle ; pBufferCh4 : PSingle ; pBufferCh5 : PSingle ; pBufferCh6 : PSingle ; qwStartIndex : UInt64 ; qwSampleCount : UInt64 ) : UInt64; cdecl;
  TScpGetData7Ch = function( hDevice : TLibTiePieHandle ; pBufferCh1 : PSingle ; pBufferCh2 : PSingle ; pBufferCh3 : PSingle ; pBufferCh4 : PSingle ; pBufferCh5 : PSingle ; pBufferCh6 : PSingle ; pBufferCh7 : PSingle ; qwStartIndex : UInt64 ; qwSampleCount : UInt64 ) : UInt64; cdecl;
  TScpGetData8Ch = function( hDevice : TLibTiePieHandle ; pBufferCh1 : PSingle ; pBufferCh2 : PSingle ; pBufferCh3 : PSingle ; pBufferCh4 : PSingle ; pBufferCh5 : PSingle ; pBufferCh6 : PSingle ; pBufferCh7 : PSingle ; pBufferCh8 : PSingle ; qwStartIndex : UInt64 ; qwSampleCount : UInt64 ) : UInt64; cdecl;
  TScpGetValidPreSampleCount = function( hDevice : TLibTiePieHandle ) : UInt64; cdecl;
  TScpChGetDataValueRange = procedure( hDevice : TLibTiePieHandle ; wCh : Word ; pMin : PDouble ; pMax : PDouble ); cdecl;
  TScpChGetDataValueMin = function( hDevice : TLibTiePieHandle ; wCh : Word ) : Double; cdecl;
  TScpChGetDataValueMax = function( hDevice : TLibTiePieHandle ; wCh : Word ) : Double; cdecl;
  TScpGetDataRaw = function( hDevice : TLibTiePieHandle ; pBuffers : PPointer ; wChannelCount : Word ; qwStartIndex : UInt64 ; qwSampleCount : UInt64 ) : UInt64; cdecl;
  TScpGetDataRaw1Ch = function( hDevice : TLibTiePieHandle ; pBufferCh1 : Pointer ; qwStartIndex : UInt64 ; qwSampleCount : UInt64 ) : UInt64; cdecl;
  TScpGetDataRaw2Ch = function( hDevice : TLibTiePieHandle ; pBufferCh1 : Pointer ; pBufferCh2 : Pointer ; qwStartIndex : UInt64 ; qwSampleCount : UInt64 ) : UInt64; cdecl;
  TScpGetDataRaw3Ch = function( hDevice : TLibTiePieHandle ; pBufferCh1 : Pointer ; pBufferCh2 : Pointer ; pBufferCh3 : Pointer ; qwStartIndex : UInt64 ; qwSampleCount : UInt64 ) : UInt64; cdecl;
  TScpGetDataRaw4Ch = function( hDevice : TLibTiePieHandle ; pBufferCh1 : Pointer ; pBufferCh2 : Pointer ; pBufferCh3 : Pointer ; pBufferCh4 : Pointer ; qwStartIndex : UInt64 ; qwSampleCount : UInt64 ) : UInt64; cdecl;
  TScpGetDataRaw5Ch = function( hDevice : TLibTiePieHandle ; pBufferCh1 : Pointer ; pBufferCh2 : Pointer ; pBufferCh3 : Pointer ; pBufferCh4 : Pointer ; pBufferCh5 : Pointer ; qwStartIndex : UInt64 ; qwSampleCount : UInt64 ) : UInt64; cdecl;
  TScpGetDataRaw6Ch = function( hDevice : TLibTiePieHandle ; pBufferCh1 : Pointer ; pBufferCh2 : Pointer ; pBufferCh3 : Pointer ; pBufferCh4 : Pointer ; pBufferCh5 : Pointer ; pBufferCh6 : Pointer ; qwStartIndex : UInt64 ; qwSampleCount : UInt64 ) : UInt64; cdecl;
  TScpGetDataRaw7Ch = function( hDevice : TLibTiePieHandle ; pBufferCh1 : Pointer ; pBufferCh2 : Pointer ; pBufferCh3 : Pointer ; pBufferCh4 : Pointer ; pBufferCh5 : Pointer ; pBufferCh6 : Pointer ; pBufferCh7 : Pointer ; qwStartIndex : UInt64 ; qwSampleCount : UInt64 ) : UInt64; cdecl;
  TScpGetDataRaw8Ch = function( hDevice : TLibTiePieHandle ; pBufferCh1 : Pointer ; pBufferCh2 : Pointer ; pBufferCh3 : Pointer ; pBufferCh4 : Pointer ; pBufferCh5 : Pointer ; pBufferCh6 : Pointer ; pBufferCh7 : Pointer ; pBufferCh8 : Pointer ; qwStartIndex : UInt64 ; qwSampleCount : UInt64 ) : UInt64; cdecl;
  TScpChGetDataRawType = function( hDevice : TLibTiePieHandle ; wCh : Word ) : LongWord; cdecl;
  TScpChGetDataRawValueRange = procedure( hDevice : TLibTiePieHandle ; wCh : Word ; pMin : PInt64 ; pZero : PInt64 ; pMax : PInt64 ); cdecl;
  TScpChGetDataRawValueMin = function( hDevice : TLibTiePieHandle ; wCh : Word ) : Int64; cdecl;
  TScpChGetDataRawValueZero = function( hDevice : TLibTiePieHandle ; wCh : Word ) : Int64; cdecl;
  TScpChGetDataRawValueMax = function( hDevice : TLibTiePieHandle ; wCh : Word ) : Int64; cdecl;
  TScpChIsRangeMaxReachable = function( hDevice : TLibTiePieHandle ; wCh : Word ) : ByteBool; cdecl;
  TScpIsGetDataAsyncCompleted = function( hDevice : TLibTiePieHandle ) : ByteBool; cdecl;
  TScpStartGetDataAsync = function( hDevice : TLibTiePieHandle ; pBuffers : PPSingle ; wChannelCount : Word ; qwStartIndex : UInt64 ; qwSampleCount : UInt64 ) : ByteBool; cdecl;
  TScpStartGetDataAsyncRaw = function( hDevice : TLibTiePieHandle ; pBuffers : PPointer ; wChannelCount : Word ; qwStartIndex : UInt64 ; qwSampleCount : UInt64 ) : ByteBool; cdecl;
  TScpCancelGetDataAsync = function( hDevice : TLibTiePieHandle ) : ByteBool; cdecl;
  TScpSetCallbackDataReady = procedure( hDevice : TLibTiePieHandle ; pCallback : TTpCallback ; pData : Pointer ); cdecl;
  TScpSetCallbackDataOverflow = procedure( hDevice : TLibTiePieHandle ; pCallback : TTpCallback ; pData : Pointer ); cdecl;
  TScpSetCallbackConnectionTestCompleted = procedure( hDevice : TLibTiePieHandle ; pCallback : TTpCallback ; pData : Pointer ); cdecl;
  TScpSetCallbackTriggered = procedure( hDevice : TLibTiePieHandle ; pCallback : TTpCallback ; pData : Pointer ); cdecl;
  {$ifdef LINUX}
  TScpSetEventDataReady = procedure( hDevice : TLibTiePieHandle ; fdEvent : Integer ); cdecl;
  TScpSetEventDataOverflow = procedure( hDevice : TLibTiePieHandle ; fdEvent : Integer ); cdecl;
  TScpSetEventConnectionTestCompleted = procedure( hDevice : TLibTiePieHandle ; fdEvent : Integer ); cdecl;
  TScpSetEventTriggered = procedure( hDevice : TLibTiePieHandle ; fdEvent : Integer ); cdecl;
  {$endif LINUX}
  {$ifdef MSWINDOWS}
  TScpSetEventDataReady = procedure( hDevice : TLibTiePieHandle ; hEvent : THandle ); cdecl;
  TScpSetEventDataOverflow = procedure( hDevice : TLibTiePieHandle ; hEvent : THandle ); cdecl;
  TScpSetEventConnectionTestCompleted = procedure( hDevice : TLibTiePieHandle ; hEvent : THandle ); cdecl;
  TScpSetEventTriggered = procedure( hDevice : TLibTiePieHandle ; hEvent : THandle ); cdecl;
  TScpSetMessageDataReady = procedure( hDevice : TLibTiePieHandle ; hWnd : HWND ; wParam : WPARAM ; lParam : LPARAM ); cdecl;
  TScpSetMessageDataOverflow = procedure( hDevice : TLibTiePieHandle ; hWnd : HWND ; wParam : WPARAM ; lParam : LPARAM ); cdecl;
  TScpSetMessageConnectionTestCompleted = procedure( hDevice : TLibTiePieHandle ; hWnd : HWND ; wParam : WPARAM ; lParam : LPARAM ); cdecl;
  TScpSetMessageTriggered = procedure( hDevice : TLibTiePieHandle ; hWnd : HWND ; wParam : WPARAM ; lParam : LPARAM ); cdecl;
  {$endif MSWINDOWS}
  TScpStart = function( hDevice : TLibTiePieHandle ) : ByteBool; cdecl;
  TScpStop = function( hDevice : TLibTiePieHandle ) : ByteBool; cdecl;
  TScpForceTrigger = function( hDevice : TLibTiePieHandle ) : ByteBool; cdecl;
  TScpGetMeasureModes = function( hDevice : TLibTiePieHandle ) : LongWord; cdecl;
  TScpGetMeasureMode = function( hDevice : TLibTiePieHandle ) : LongWord; cdecl;
  TScpSetMeasureMode = function( hDevice : TLibTiePieHandle ; dwMeasureMode : LongWord ) : LongWord; cdecl;
  TScpIsRunning = function( hDevice : TLibTiePieHandle ) : ByteBool; cdecl;
  TScpIsTriggered = function( hDevice : TLibTiePieHandle ) : ByteBool; cdecl;
  TScpIsTimeOutTriggered = function( hDevice : TLibTiePieHandle ) : ByteBool; cdecl;
  TScpIsForceTriggered = function( hDevice : TLibTiePieHandle ) : ByteBool; cdecl;
  TScpIsDataReady = function( hDevice : TLibTiePieHandle ) : ByteBool; cdecl;
  TScpIsDataOverflow = function( hDevice : TLibTiePieHandle ) : ByteBool; cdecl;
  TScpGetAutoResolutionModes = function( hDevice : TLibTiePieHandle ) : LongWord; cdecl;
  TScpGetAutoResolutionMode = function( hDevice : TLibTiePieHandle ) : LongWord; cdecl;
  TScpSetAutoResolutionMode = function( hDevice : TLibTiePieHandle ; dwAutoResolutionMode : LongWord ) : LongWord; cdecl;
  TScpGetResolutions = function( hDevice : TLibTiePieHandle ; pList : PByte ; dwLength : LongWord ) : LongWord; cdecl;
  TScpGetResolution = function( hDevice : TLibTiePieHandle ) : Byte; cdecl;
  TScpSetResolution = function( hDevice : TLibTiePieHandle ; byResolution : Byte ) : Byte; cdecl;
  TScpIsResolutionEnhanced = function( hDevice : TLibTiePieHandle ) : ByteBool; cdecl;
  TScpIsResolutionEnhancedEx = function( hDevice : TLibTiePieHandle ; byResolution : Byte ) : ByteBool; cdecl;
  TScpGetClockSources = function( hDevice : TLibTiePieHandle ) : LongWord; cdecl;
  TScpGetClockSource = function( hDevice : TLibTiePieHandle ) : LongWord; cdecl;
  TScpSetClockSource = function( hDevice : TLibTiePieHandle ; dwClockSource : LongWord ) : LongWord; cdecl;
  TScpGetClockSourceFrequencies = function( hDevice : TLibTiePieHandle ; pList : PDouble ; dwLength : LongWord ) : LongWord; cdecl;
  TScpGetClockSourceFrequenciesEx = function( hDevice : TLibTiePieHandle ; dwClockSource : LongWord ; pList : PDouble ; dwLength : LongWord ) : LongWord; cdecl;
  TScpGetClockSourceFrequency = function( hDevice : TLibTiePieHandle ) : Double; cdecl;
  TScpSetClockSourceFrequency = function( hDevice : TLibTiePieHandle ; dClockSourceFrequency : Double ) : Double; cdecl;
  TScpGetClockOutputs = function( hDevice : TLibTiePieHandle ) : LongWord; cdecl;
  TScpGetClockOutput = function( hDevice : TLibTiePieHandle ) : LongWord; cdecl;
  TScpSetClockOutput = function( hDevice : TLibTiePieHandle ; dwClockOutput : LongWord ) : LongWord; cdecl;
  TScpGetClockOutputFrequencies = function( hDevice : TLibTiePieHandle ; pList : PDouble ; dwLength : LongWord ) : LongWord; cdecl;
  TScpGetClockOutputFrequenciesEx = function( hDevice : TLibTiePieHandle ; dwClockOutput : LongWord ; pList : PDouble ; dwLength : LongWord ) : LongWord; cdecl;
  TScpGetClockOutputFrequency = function( hDevice : TLibTiePieHandle ) : Double; cdecl;
  TScpSetClockOutputFrequency = function( hDevice : TLibTiePieHandle ; dClockOutputFrequency : Double ) : Double; cdecl;
  TScpGetSampleFrequencyMax = function( hDevice : TLibTiePieHandle ) : Double; cdecl;
  TScpGetSampleFrequency = function( hDevice : TLibTiePieHandle ) : Double; cdecl;
  TScpSetSampleFrequency = function( hDevice : TLibTiePieHandle ; dSampleFrequency : Double ) : Double; cdecl;
  TScpVerifySampleFrequency = function( hDevice : TLibTiePieHandle ; dSampleFrequency : Double ) : Double; cdecl;
  TScpVerifySampleFrequencyEx = function( hDevice : TLibTiePieHandle ; dSampleFrequency : Double ; dwMeasureMode : LongWord ; byResolution : Byte ; pChannelEnabled : PByteBool ; wChannelCount : Word ) : Double; cdecl;
  TScpVerifySampleFrequenciesEx = procedure( hDevice : TLibTiePieHandle ; pSampleFrequencies : PDouble ; dwSampleFrequencyCount : LongWord ; dwMeasureMode : LongWord ; dwAutoResolutionMode : LongWord ; byResolution : Byte ; pChannelEnabled : PByteBool ; wChannelCount : Word ); cdecl;
  TScpGetRecordLengthMax = function( hDevice : TLibTiePieHandle ) : UInt64; cdecl;
  TScpGetRecordLengthMaxEx = function( hDevice : TLibTiePieHandle ; dwMeasureMode : LongWord ; byResolution : Byte ) : UInt64; cdecl;
  TScpGetRecordLength = function( hDevice : TLibTiePieHandle ) : UInt64; cdecl;
  TScpSetRecordLength = function( hDevice : TLibTiePieHandle ; qwRecordLength : UInt64 ) : UInt64; cdecl;
  TScpVerifyRecordLength = function( hDevice : TLibTiePieHandle ; qwRecordLength : UInt64 ) : UInt64; cdecl;
  TScpVerifyRecordLengthEx = function( hDevice : TLibTiePieHandle ; qwRecordLength : UInt64 ; dwMeasureMode : LongWord ; byResolution : Byte ; pChannelEnabled : PByteBool ; wChannelCount : Word ) : UInt64; cdecl;
  TScpGetPreSampleRatio = function( hDevice : TLibTiePieHandle ) : Double; cdecl;
  TScpSetPreSampleRatio = function( hDevice : TLibTiePieHandle ; dPreSampleRatio : Double ) : Double; cdecl;
  TScpGetSegmentCountMax = function( hDevice : TLibTiePieHandle ) : LongWord; cdecl;
  TScpGetSegmentCountMaxEx = function( hDevice : TLibTiePieHandle ; dwMeasureMode : LongWord ) : LongWord; cdecl;
  TScpGetSegmentCount = function( hDevice : TLibTiePieHandle ) : LongWord; cdecl;
  TScpSetSegmentCount = function( hDevice : TLibTiePieHandle ; dwSegmentCount : LongWord ) : LongWord; cdecl;
  TScpVerifySegmentCount = function( hDevice : TLibTiePieHandle ; dwSegmentCount : LongWord ) : LongWord; cdecl;
  TScpVerifySegmentCountEx2 = function( hDevice : TLibTiePieHandle ; dwSegmentCount : LongWord ; dwMeasureMode : LongWord ; qwRecordLength : UInt64 ; pChannelEnabled : PByteBool ; wChannelCount : Word ) : LongWord; cdecl;
  TScpHasTrigger = function( hDevice : TLibTiePieHandle ) : ByteBool; cdecl;
  TScpHasTriggerEx = function( hDevice : TLibTiePieHandle ; dwMeasureMode : LongWord ) : ByteBool; cdecl;
  TScpGetTriggerTimeOut = function( hDevice : TLibTiePieHandle ) : Double; cdecl;
  TScpSetTriggerTimeOut = function( hDevice : TLibTiePieHandle ; dTimeOut : Double ) : Double; cdecl;
  TScpVerifyTriggerTimeOut = function( hDevice : TLibTiePieHandle ; dTimeOut : Double ) : Double; cdecl;
  TScpVerifyTriggerTimeOutEx = function( hDevice : TLibTiePieHandle ; dTimeOut : Double ; dwMeasureMode : LongWord ; dSampleFrequency : Double ) : Double; cdecl;
  TScpHasTriggerDelay = function( hDevice : TLibTiePieHandle ) : ByteBool; cdecl;
  TScpHasTriggerDelayEx = function( hDevice : TLibTiePieHandle ; dwMeasureMode : LongWord ) : ByteBool; cdecl;
  TScpGetTriggerDelayMax = function( hDevice : TLibTiePieHandle ) : Double; cdecl;
  TScpGetTriggerDelayMaxEx = function( hDevice : TLibTiePieHandle ; dwMeasureMode : LongWord ; dSampleFrequency : Double ) : Double; cdecl;
  TScpGetTriggerDelay = function( hDevice : TLibTiePieHandle ) : Double; cdecl;
  TScpSetTriggerDelay = function( hDevice : TLibTiePieHandle ; dDelay : Double ) : Double; cdecl;
  TScpVerifyTriggerDelay = function( hDevice : TLibTiePieHandle ; dDelay : Double ) : Double; cdecl;
  TScpVerifyTriggerDelayEx = function( hDevice : TLibTiePieHandle ; dDelay : Double ; dwMeasureMode : LongWord ; dSampleFrequency : Double ) : Double; cdecl;
  TScpHasTriggerHoldOff = function( hDevice : TLibTiePieHandle ) : ByteBool; cdecl;
  TScpHasTriggerHoldOffEx = function( hDevice : TLibTiePieHandle ; dwMeasureMode : LongWord ) : ByteBool; cdecl;
  TScpGetTriggerHoldOffCountMax = function( hDevice : TLibTiePieHandle ) : UInt64; cdecl;
  TScpGetTriggerHoldOffCountMaxEx = function( hDevice : TLibTiePieHandle ; dwMeasureMode : LongWord ) : UInt64; cdecl;
  TScpGetTriggerHoldOffCount = function( hDevice : TLibTiePieHandle ) : UInt64; cdecl;
  TScpSetTriggerHoldOffCount = function( hDevice : TLibTiePieHandle ; qwTriggerHoldOffCount : UInt64 ) : UInt64; cdecl;
  TScpHasConnectionTest = function( hDevice : TLibTiePieHandle ) : ByteBool; cdecl;
  TScpChHasConnectionTest = function( hDevice : TLibTiePieHandle ; wCh : Word ) : ByteBool; cdecl;
  TScpStartConnectionTest = function( hDevice : TLibTiePieHandle ) : ByteBool; cdecl;
  TScpStartConnectionTestEx = function( hDevice : TLibTiePieHandle ; pChannelEnabled : PByteBool ; wChannelCount : Word ) : ByteBool; cdecl;
  TScpIsConnectionTestCompleted = function( hDevice : TLibTiePieHandle ) : ByteBool; cdecl;
  TScpGetConnectionTestData = function( hDevice : TLibTiePieHandle ; pBuffer : PLibTiePieTriState ; wChannelCount : Word ) : Word; cdecl;
  TGenGetConnectorType = function( hDevice : TLibTiePieHandle ) : LongWord; cdecl;
  TGenIsDifferential = function( hDevice : TLibTiePieHandle ) : ByteBool; cdecl;
  TGenGetImpedance = function( hDevice : TLibTiePieHandle ) : Double; cdecl;
  TGenGetResolution = function( hDevice : TLibTiePieHandle ) : Byte; cdecl;
  TGenGetOutputValueMin = function( hDevice : TLibTiePieHandle ) : Double; cdecl;
  TGenGetOutputValueMax = function( hDevice : TLibTiePieHandle ) : Double; cdecl;
  TGenGetOutputValueMinMax = procedure( hDevice : TLibTiePieHandle ; pMin : PDouble ; pMax : PDouble ); cdecl;
  TGenIsControllable = function( hDevice : TLibTiePieHandle ) : ByteBool; cdecl;
  TGenIsRunning = function( hDevice : TLibTiePieHandle ) : ByteBool; cdecl;
  TGenGetStatus = function( hDevice : TLibTiePieHandle ) : LongWord; cdecl;
  TGenGetOutputOn = function( hDevice : TLibTiePieHandle ) : ByteBool; cdecl;
  TGenSetOutputOn = function( hDevice : TLibTiePieHandle ; bOutputOn : ByteBool ) : ByteBool; cdecl;
  TGenHasOutputInvert = function( hDevice : TLibTiePieHandle ) : ByteBool; cdecl;
  TGenGetOutputInvert = function( hDevice : TLibTiePieHandle ) : ByteBool; cdecl;
  TGenSetOutputInvert = function( hDevice : TLibTiePieHandle ; bInvert : ByteBool ) : ByteBool; cdecl;
  TGenStart = function( hDevice : TLibTiePieHandle ) : ByteBool; cdecl;
  TGenStop = function( hDevice : TLibTiePieHandle ) : ByteBool; cdecl;
  TGenGetSignalTypes = function( hDevice : TLibTiePieHandle ) : LongWord; cdecl;
  TGenGetSignalType = function( hDevice : TLibTiePieHandle ) : LongWord; cdecl;
  TGenSetSignalType = function( hDevice : TLibTiePieHandle ; dwSignalType : LongWord ) : LongWord; cdecl;
  TGenHasAmplitude = function( hDevice : TLibTiePieHandle ) : ByteBool; cdecl;
  TGenHasAmplitudeEx = function( hDevice : TLibTiePieHandle ; dwSignalType : LongWord ) : ByteBool; cdecl;
  TGenGetAmplitudeMin = function( hDevice : TLibTiePieHandle ) : Double; cdecl;
  TGenGetAmplitudeMax = function( hDevice : TLibTiePieHandle ) : Double; cdecl;
  TGenGetAmplitudeMinMaxEx = procedure( hDevice : TLibTiePieHandle ; dwSignalType : LongWord ; pMin : PDouble ; pMax : PDouble ); cdecl;
  TGenGetAmplitude = function( hDevice : TLibTiePieHandle ) : Double; cdecl;
  TGenSetAmplitude = function( hDevice : TLibTiePieHandle ; dAmplitude : Double ) : Double; cdecl;
  TGenVerifyAmplitude = function( hDevice : TLibTiePieHandle ; dAmplitude : Double ) : Double; cdecl;
  TGenVerifyAmplitudeEx = function( hDevice : TLibTiePieHandle ; dAmplitude : Double ; dwSignalType : LongWord ; dwAmplitudeRangeIndex : LongWord ; dOffset : Double ) : Double; cdecl;
  TGenGetAmplitudeRanges = function( hDevice : TLibTiePieHandle ; pList : PDouble ; dwLength : LongWord ) : LongWord; cdecl;
  TGenGetAmplitudeRange = function( hDevice : TLibTiePieHandle ) : Double; cdecl;
  TGenSetAmplitudeRange = function( hDevice : TLibTiePieHandle ; dRange : Double ) : Double; cdecl;
  TGenGetAmplitudeAutoRanging = function( hDevice : TLibTiePieHandle ) : ByteBool; cdecl;
  TGenSetAmplitudeAutoRanging = function( hDevice : TLibTiePieHandle ; bEnable : ByteBool ) : ByteBool; cdecl;
  TGenHasOffset = function( hDevice : TLibTiePieHandle ) : ByteBool; cdecl;
  TGenHasOffsetEx = function( hDevice : TLibTiePieHandle ; dwSignalType : LongWord ) : ByteBool; cdecl;
  TGenGetOffsetMin = function( hDevice : TLibTiePieHandle ) : Double; cdecl;
  TGenGetOffsetMax = function( hDevice : TLibTiePieHandle ) : Double; cdecl;
  TGenGetOffsetMinMaxEx = procedure( hDevice : TLibTiePieHandle ; dwSignalType : LongWord ; pMin : PDouble ; pMax : PDouble ); cdecl;
  TGenGetOffset = function( hDevice : TLibTiePieHandle ) : Double; cdecl;
  TGenSetOffset = function( hDevice : TLibTiePieHandle ; dOffset : Double ) : Double; cdecl;
  TGenVerifyOffset = function( hDevice : TLibTiePieHandle ; dOffset : Double ) : Double; cdecl;
  TGenVerifyOffsetEx = function( hDevice : TLibTiePieHandle ; dOffset : Double ; dwSignalType : LongWord ; dAmplitude : Double ) : Double; cdecl;
  TGenGetFrequencyModes = function( hDevice : TLibTiePieHandle ) : LongWord; cdecl;
  TGenGetFrequencyModesEx = function( hDevice : TLibTiePieHandle ; dwSignalType : LongWord ) : LongWord; cdecl;
  TGenGetFrequencyMode = function( hDevice : TLibTiePieHandle ) : LongWord; cdecl;
  TGenSetFrequencyMode = function( hDevice : TLibTiePieHandle ; dwFrequencyMode : LongWord ) : LongWord; cdecl;
  TGenHasFrequency = function( hDevice : TLibTiePieHandle ) : ByteBool; cdecl;
  TGenHasFrequencyEx = function( hDevice : TLibTiePieHandle ; dwFrequencyMode : LongWord ; dwSignalType : LongWord ) : ByteBool; cdecl;
  TGenGetFrequencyMin = function( hDevice : TLibTiePieHandle ) : Double; cdecl;
  TGenGetFrequencyMax = function( hDevice : TLibTiePieHandle ) : Double; cdecl;
  TGenGetFrequencyMinMax = procedure( hDevice : TLibTiePieHandle ; dwFrequencyMode : LongWord ; pMin : PDouble ; pMax : PDouble ); cdecl;
  TGenGetFrequencyMinMaxEx = procedure( hDevice : TLibTiePieHandle ; dwFrequencyMode : LongWord ; dwSignalType : LongWord ; pMin : PDouble ; pMax : PDouble ); cdecl;
  TGenGetFrequency = function( hDevice : TLibTiePieHandle ) : Double; cdecl;
  TGenSetFrequency = function( hDevice : TLibTiePieHandle ; dFrequency : Double ) : Double; cdecl;
  TGenVerifyFrequency = function( hDevice : TLibTiePieHandle ; dFrequency : Double ) : Double; cdecl;
  TGenVerifyFrequencyEx2 = function( hDevice : TLibTiePieHandle ; dFrequency : Double ; dwFrequencyMode : LongWord ; dwSignalType : LongWord ; qwDataLength : UInt64 ; dWidth : Double ) : Double; cdecl;
  TGenHasPhase = function( hDevice : TLibTiePieHandle ) : ByteBool; cdecl;
  TGenHasPhaseEx = function( hDevice : TLibTiePieHandle ; dwSignalType : LongWord ) : ByteBool; cdecl;
  TGenGetPhaseMin = function( hDevice : TLibTiePieHandle ) : Double; cdecl;
  TGenGetPhaseMax = function( hDevice : TLibTiePieHandle ) : Double; cdecl;
  TGenGetPhaseMinMaxEx = procedure( hDevice : TLibTiePieHandle ; dwSignalType : LongWord ; pMin : PDouble ; pMax : PDouble ); cdecl;
  TGenGetPhase = function( hDevice : TLibTiePieHandle ) : Double; cdecl;
  TGenSetPhase = function( hDevice : TLibTiePieHandle ; dPhase : Double ) : Double; cdecl;
  TGenVerifyPhase = function( hDevice : TLibTiePieHandle ; dPhase : Double ) : Double; cdecl;
  TGenVerifyPhaseEx = function( hDevice : TLibTiePieHandle ; dPhase : Double ; dwSignalType : LongWord ) : Double; cdecl;
  TGenHasSymmetry = function( hDevice : TLibTiePieHandle ) : ByteBool; cdecl;
  TGenHasSymmetryEx = function( hDevice : TLibTiePieHandle ; dwSignalType : LongWord ) : ByteBool; cdecl;
  TGenGetSymmetryMin = function( hDevice : TLibTiePieHandle ) : Double; cdecl;
  TGenGetSymmetryMax = function( hDevice : TLibTiePieHandle ) : Double; cdecl;
  TGenGetSymmetryMinMaxEx = procedure( hDevice : TLibTiePieHandle ; dwSignalType : LongWord ; pMin : PDouble ; pMax : PDouble ); cdecl;
  TGenGetSymmetry = function( hDevice : TLibTiePieHandle ) : Double; cdecl;
  TGenSetSymmetry = function( hDevice : TLibTiePieHandle ; dSymmetry : Double ) : Double; cdecl;
  TGenVerifySymmetry = function( hDevice : TLibTiePieHandle ; dSymmetry : Double ) : Double; cdecl;
  TGenVerifySymmetryEx = function( hDevice : TLibTiePieHandle ; dSymmetry : Double ; dwSignalType : LongWord ) : Double; cdecl;
  TGenHasWidth = function( hDevice : TLibTiePieHandle ) : ByteBool; cdecl;
  TGenHasWidthEx = function( hDevice : TLibTiePieHandle ; dwSignalType : LongWord ) : ByteBool; cdecl;
  TGenGetWidthMin = function( hDevice : TLibTiePieHandle ) : Double; cdecl;
  TGenGetWidthMax = function( hDevice : TLibTiePieHandle ) : Double; cdecl;
  TGenGetWidthMinMaxEx = procedure( hDevice : TLibTiePieHandle ; dwSignalType : LongWord ; dSignalFrequency : Double ; pMin : PDouble ; pMax : PDouble ); cdecl;
  TGenGetWidth = function( hDevice : TLibTiePieHandle ) : Double; cdecl;
  TGenSetWidth = function( hDevice : TLibTiePieHandle ; dWidth : Double ) : Double; cdecl;
  TGenVerifyWidth = function( hDevice : TLibTiePieHandle ; dWidth : Double ) : Double; cdecl;
  TGenVerifyWidthEx = function( hDevice : TLibTiePieHandle ; dWidth : Double ; dwSignalType : LongWord ; dSignalFrequency : Double ) : Double; cdecl;
  TGenHasEdgeTime = function( hDevice : TLibTiePieHandle ) : ByteBool; cdecl;
  TGenHasEdgeTimeEx = function( hDevice : TLibTiePieHandle ; dwSignalType : LongWord ) : ByteBool; cdecl;
  TGenGetLeadingEdgeTimeMin = function( hDevice : TLibTiePieHandle ) : Double; cdecl;
  TGenGetLeadingEdgeTimeMax = function( hDevice : TLibTiePieHandle ) : Double; cdecl;
  TGenGetLeadingEdgeTimeMinMaxEx = procedure( hDevice : TLibTiePieHandle ; dwSignalType : LongWord ; dSignalFrequency : Double ; dSymmetry : Double ; dWidth : Double ; dTrailingEdgeTime : Double ; pMin : PDouble ; pMax : PDouble ); cdecl;
  TGenGetLeadingEdgeTime = function( hDevice : TLibTiePieHandle ) : Double; cdecl;
  TGenSetLeadingEdgeTime = function( hDevice : TLibTiePieHandle ; dLeadingEdgeTime : Double ) : Double; cdecl;
  TGenVerifyLeadingEdgeTime = function( hDevice : TLibTiePieHandle ; dLeadingEdgeTime : Double ) : Double; cdecl;
  TGenVerifyLeadingEdgeTimeEx = function( hDevice : TLibTiePieHandle ; dLeadingEdgeTime : Double ; dwSignalType : LongWord ; dSignalFrequency : Double ; dSymmetry : Double ; dWidth : Double ; dTrailingEdgeTime : Double ) : Double; cdecl;
  TGenGetTrailingEdgeTimeMin = function( hDevice : TLibTiePieHandle ) : Double; cdecl;
  TGenGetTrailingEdgeTimeMax = function( hDevice : TLibTiePieHandle ) : Double; cdecl;
  TGenGetTrailingEdgeTimeMinMaxEx = procedure( hDevice : TLibTiePieHandle ; dwSignalType : LongWord ; dSignalFrequency : Double ; dSymmetry : Double ; dWidth : Double ; dLeadingEdgeTime : Double ; pMin : PDouble ; pMax : PDouble ); cdecl;
  TGenGetTrailingEdgeTime = function( hDevice : TLibTiePieHandle ) : Double; cdecl;
  TGenSetTrailingEdgeTime = function( hDevice : TLibTiePieHandle ; dTrailingEdgeTime : Double ) : Double; cdecl;
  TGenVerifyTrailingEdgeTime = function( hDevice : TLibTiePieHandle ; dTrailingEdgeTime : Double ) : Double; cdecl;
  TGenVerifyTrailingEdgeTimeEx = function( hDevice : TLibTiePieHandle ; dTrailingEdgeTime : Double ; dwSignalType : LongWord ; dSignalFrequency : Double ; dSymmetry : Double ; dWidth : Double ; dLeadingEdgeTime : Double ) : Double; cdecl;
  TGenHasData = function( hDevice : TLibTiePieHandle ) : ByteBool; cdecl;
  TGenHasDataEx = function( hDevice : TLibTiePieHandle ; dwSignalType : LongWord ) : ByteBool; cdecl;
  TGenGetDataLengthMin = function( hDevice : TLibTiePieHandle ) : UInt64; cdecl;
  TGenGetDataLengthMax = function( hDevice : TLibTiePieHandle ) : UInt64; cdecl;
  TGenGetDataLengthMinMaxEx = procedure( hDevice : TLibTiePieHandle ; dwSignalType : LongWord ; pMin : PUInt64 ; pMax : PUInt64 ); cdecl;
  TGenGetDataLength = function( hDevice : TLibTiePieHandle ) : UInt64; cdecl;
  TGenVerifyDataLength = function( hDevice : TLibTiePieHandle ; qwDataLength : UInt64 ) : UInt64; cdecl;
  TGenVerifyDataLengthEx = function( hDevice : TLibTiePieHandle ; qwDataLength : UInt64 ; dwSignalType : LongWord ) : UInt64; cdecl;
  TGenSetData = procedure( hDevice : TLibTiePieHandle ; pBuffer : PSingle ; qwSampleCount : UInt64 ); cdecl;
  TGenSetDataEx = procedure( hDevice : TLibTiePieHandle ; pBuffer : PSingle ; qwSampleCount : UInt64 ; dwSignalType : LongWord ; dwReserved : LongWord ); cdecl;
  TGenGetDataRawType = function( hDevice : TLibTiePieHandle ) : LongWord; cdecl;
  TGenGetDataRawValueRange = procedure( hDevice : TLibTiePieHandle ; pMin : PInt64 ; pZero : PInt64 ; pMax : PInt64 ); cdecl;
  TGenGetDataRawValueMin = function( hDevice : TLibTiePieHandle ) : Int64; cdecl;
  TGenGetDataRawValueZero = function( hDevice : TLibTiePieHandle ) : Int64; cdecl;
  TGenGetDataRawValueMax = function( hDevice : TLibTiePieHandle ) : Int64; cdecl;
  TGenSetDataRaw = procedure( hDevice : TLibTiePieHandle ; pBuffer : Pointer ; qwSampleCount : UInt64 ); cdecl;
  TGenSetDataRawEx = procedure( hDevice : TLibTiePieHandle ; pBuffer : Pointer ; qwSampleCount : UInt64 ; dwSignalType : LongWord ; dwReserved : LongWord ); cdecl;
  TGenGetModes = function( hDevice : TLibTiePieHandle ) : UInt64; cdecl;
  TGenGetModesEx = function( hDevice : TLibTiePieHandle ; dwSignalType : LongWord ; dwFrequencyMode : LongWord ) : UInt64; cdecl;
  TGenGetModesNative = function( hDevice : TLibTiePieHandle ) : UInt64; cdecl;
  TGenGetMode = function( hDevice : TLibTiePieHandle ) : UInt64; cdecl;
  TGenSetMode = function( hDevice : TLibTiePieHandle ; qwGeneratorMode : UInt64 ) : UInt64; cdecl;
  TGenIsBurstActive = function( hDevice : TLibTiePieHandle ) : ByteBool; cdecl;
  TGenGetBurstCountMin = function( hDevice : TLibTiePieHandle ) : UInt64; cdecl;
  TGenGetBurstCountMax = function( hDevice : TLibTiePieHandle ) : UInt64; cdecl;
  TGenGetBurstCountMinMaxEx = procedure( hDevice : TLibTiePieHandle ; qwGeneratorMode : UInt64 ; pMin : PUInt64 ; pMax : PUInt64 ); cdecl;
  TGenGetBurstCount = function( hDevice : TLibTiePieHandle ) : UInt64; cdecl;
  TGenSetBurstCount = function( hDevice : TLibTiePieHandle ; qwBurstCount : UInt64 ) : UInt64; cdecl;
  TGenGetBurstSampleCountMin = function( hDevice : TLibTiePieHandle ) : UInt64; cdecl;
  TGenGetBurstSampleCountMax = function( hDevice : TLibTiePieHandle ) : UInt64; cdecl;
  TGenGetBurstSampleCountMinMaxEx = procedure( hDevice : TLibTiePieHandle ; qwGeneratorMode : UInt64 ; pMin : PUInt64 ; pMax : PUInt64 ); cdecl;
  TGenGetBurstSampleCount = function( hDevice : TLibTiePieHandle ) : UInt64; cdecl;
  TGenSetBurstSampleCount = function( hDevice : TLibTiePieHandle ; qwBurstSampleCount : UInt64 ) : UInt64; cdecl;
  TGenGetBurstSegmentCountMin = function( hDevice : TLibTiePieHandle ) : UInt64; cdecl;
  TGenGetBurstSegmentCountMax = function( hDevice : TLibTiePieHandle ) : UInt64; cdecl;
  TGenGetBurstSegmentCountMinMaxEx = procedure( hDevice : TLibTiePieHandle ; qwGeneratorMode : UInt64 ; dwSignalType : LongWord ; dwFrequencyMode : LongWord ; dFrequency : Double ; qwDataLength : UInt64 ; pMin : PUInt64 ; pMax : PUInt64 ); cdecl;
  TGenGetBurstSegmentCount = function( hDevice : TLibTiePieHandle ) : UInt64; cdecl;
  TGenSetBurstSegmentCount = function( hDevice : TLibTiePieHandle ; qwBurstSegmentCount : UInt64 ) : UInt64; cdecl;
  TGenVerifyBurstSegmentCount = function( hDevice : TLibTiePieHandle ; qwBurstSegmentCount : UInt64 ) : UInt64; cdecl;
  TGenVerifyBurstSegmentCountEx = function( hDevice : TLibTiePieHandle ; qwBurstSegmentCount : UInt64 ; qwGeneratorMode : UInt64 ; dwSignalType : LongWord ; dwFrequencyMode : LongWord ; dFrequency : Double ; qwDataLength : UInt64 ) : UInt64; cdecl;
  TGenSetCallbackBurstCompleted = procedure( hDevice : TLibTiePieHandle ; pCallback : TTpCallback ; pData : Pointer ); cdecl;
  {$ifdef LINUX}
  TGenSetEventBurstCompleted = procedure( hDevice : TLibTiePieHandle ; fdEvent : Integer ); cdecl;
  {$endif LINUX}
  {$ifdef MSWINDOWS}
  TGenSetEventBurstCompleted = procedure( hDevice : TLibTiePieHandle ; hEvent : THandle ); cdecl;
  TGenSetMessageBurstCompleted = procedure( hDevice : TLibTiePieHandle ; hWnd : HWND ; wParam : WPARAM ; lParam : LPARAM ); cdecl;
  {$endif MSWINDOWS}
  TGenSetCallbackControllableChanged = procedure( hDevice : TLibTiePieHandle ; pCallback : TTpCallback ; pData : Pointer ); cdecl;
  {$ifdef LINUX}
  TGenSetEventControllableChanged = procedure( hDevice : TLibTiePieHandle ; fdEvent : Integer ); cdecl;
  {$endif LINUX}
  {$ifdef MSWINDOWS}
  TGenSetEventControllableChanged = procedure( hDevice : TLibTiePieHandle ; hEvent : THandle ); cdecl;
  TGenSetMessageControllableChanged = procedure( hDevice : TLibTiePieHandle ; hWnd : HWND ; wParam : WPARAM ; lParam : LPARAM ); cdecl;
  {$endif MSWINDOWS}
  TI2CIsInternalAddress = function( hDevice : TLibTiePieHandle ; wAddress : Word ) : ByteBool; cdecl;
  TI2CGetInternalAddresses = function( hDevice : TLibTiePieHandle ; pAddresses : PWord ; dwLength : LongWord ) : LongWord; cdecl;
  TI2CRead = function( hDevice : TLibTiePieHandle ; wAddress : Word ; pBuffer : Pointer ; dwSize : LongWord ; bStop : ByteBool ) : ByteBool; cdecl;
  TI2CReadByte = function( hDevice : TLibTiePieHandle ; wAddress : Word ; pValue : PByte ) : ByteBool; cdecl;
  TI2CReadWord = function( hDevice : TLibTiePieHandle ; wAddress : Word ; pValue : PWord ) : ByteBool; cdecl;
  TI2CWrite = function( hDevice : TLibTiePieHandle ; wAddress : Word ; pBuffer : Pointer ; dwSize : LongWord ; bStop : ByteBool ) : ByteBool; cdecl;
  TI2CWriteByte = function( hDevice : TLibTiePieHandle ; wAddress : Word ; byValue : Byte ) : ByteBool; cdecl;
  TI2CWriteByteByte = function( hDevice : TLibTiePieHandle ; wAddress : Word ; byValue1 : Byte ; byValue2 : Byte ) : ByteBool; cdecl;
  TI2CWriteByteWord = function( hDevice : TLibTiePieHandle ; wAddress : Word ; byValue1 : Byte ; wValue2 : Word ) : ByteBool; cdecl;
  TI2CWriteWord = function( hDevice : TLibTiePieHandle ; wAddress : Word ; wValue : Word ) : ByteBool; cdecl;
  TI2CWriteRead = function( hDevice : TLibTiePieHandle ; wAddress : Word ; pWriteBuffer : Pointer ; dwWriteSize : LongWord ; pReadBuffer : Pointer ; dwReadSize : LongWord ) : ByteBool; cdecl;
  TI2CGetSpeedMax = function( hDevice : TLibTiePieHandle ) : Double; cdecl;
  TI2CGetSpeed = function( hDevice : TLibTiePieHandle ) : Double; cdecl;
  TI2CSetSpeed = function( hDevice : TLibTiePieHandle ; dSpeed : Double ) : Double; cdecl;
  TI2CVerifySpeed = function( hDevice : TLibTiePieHandle ; dSpeed : Double ) : Double; cdecl;
  TSrvConnect = function( hServer : TLibTiePieHandle ; bAsync : ByteBool ) : ByteBool; cdecl;
  TSrvDisconnect = function( hServer : TLibTiePieHandle ; bForce : ByteBool ) : ByteBool; cdecl;
  TSrvRemove = function( hServer : TLibTiePieHandle ; bForce : ByteBool ) : ByteBool; cdecl;
  TSrvGetStatus = function( hServer : TLibTiePieHandle ) : LongWord; cdecl;
  TSrvGetLastError = function( hServer : TLibTiePieHandle ) : LongWord; cdecl;
  TSrvGetURL = function( hServer : TLibTiePieHandle ; pBuffer : PAnsiChar ; dwBufferLength : LongWord ) : LongWord; cdecl;
  TSrvGetID = function( hServer : TLibTiePieHandle ; pBuffer : PAnsiChar ; dwBufferLength : LongWord ) : LongWord; cdecl;
  TSrvGetIPv4Address = function( hServer : TLibTiePieHandle ) : LongWord; cdecl;
  TSrvGetIPPort = function( hServer : TLibTiePieHandle ) : Word; cdecl;
  TSrvGetName = function( hServer : TLibTiePieHandle ; pBuffer : PAnsiChar ; dwBufferLength : LongWord ) : LongWord; cdecl;
  TSrvGetDescription = function( hServer : TLibTiePieHandle ; pBuffer : PAnsiChar ; dwBufferLength : LongWord ) : LongWord; cdecl;
  TSrvGetVersion = function( hServer : TLibTiePieHandle ) : TTpVersion; cdecl;
  TSrvGetVersionExtra = function( hServer : TLibTiePieHandle ; pBuffer : PAnsiChar ; dwBufferLength : LongWord ) : LongWord; cdecl;
  THlpPointerArrayNew = function( dwLength : LongWord ) : TLibTiePiePointerArray; cdecl;
  THlpPointerArraySet = procedure( pArray : TLibTiePiePointerArray ; dwIndex : LongWord ; pPointer : Pointer ); cdecl;
  THlpPointerArrayDelete = procedure( pArray : TLibTiePiePointerArray ); cdecl;

var
  LibInit : TLibInit = nil;
  LibIsInitialized : TLibIsInitialized = nil;
  LibExit : TLibExit = nil;
  LibGetVersion : TLibGetVersion = nil;
  LibGetVersionExtra : TLibGetVersionExtra = nil;
  LibGetConfig : TLibGetConfig = nil;
  LibGetLastStatus : TLibGetLastStatus = nil;
  LibGetLastStatusStr : TLibGetLastStatusStr = nil;
  LstUpdate : TLstUpdate = nil;
  LstGetCount : TLstGetCount = nil;
  LstOpenDevice : TLstOpenDevice = nil;
  LstOpenOscilloscope : TLstOpenOscilloscope = nil;
  LstOpenGenerator : TLstOpenGenerator = nil;
  LstOpenI2CHost : TLstOpenI2CHost = nil;
  LstCreateCombinedDevice : TLstCreateCombinedDevice = nil;
  LstCreateAndOpenCombinedDevice : TLstCreateAndOpenCombinedDevice = nil;
  LstRemoveDevice : TLstRemoveDevice = nil;
  LstRemoveDeviceForce : TLstRemoveDeviceForce = nil;
  LstDevCanOpen : TLstDevCanOpen = nil;
  LstDevGetProductId : TLstDevGetProductId = nil;
  LstDevGetVendorId : TLstDevGetVendorId = nil;
  LstDevGetName : TLstDevGetName = nil;
  LstDevGetNameShort : TLstDevGetNameShort = nil;
  LstDevGetNameShortest : TLstDevGetNameShortest = nil;
  LstDevGetDriverVersion : TLstDevGetDriverVersion = nil;
  LstDevGetRecommendedDriverVersion : TLstDevGetRecommendedDriverVersion = nil;
  LstDevGetFirmwareVersion : TLstDevGetFirmwareVersion = nil;
  LstDevGetRecommendedFirmwareVersion : TLstDevGetRecommendedFirmwareVersion = nil;
  LstDevGetCalibrationDate : TLstDevGetCalibrationDate = nil;
  LstDevGetSerialNumber : TLstDevGetSerialNumber = nil;
  LstDevGetIPv4Address : TLstDevGetIPv4Address = nil;
  LstDevGetIPPort : TLstDevGetIPPort = nil;
  LstDevHasServer : TLstDevHasServer = nil;
  LstDevGetServer : TLstDevGetServer = nil;
  LstDevGetTypes : TLstDevGetTypes = nil;
  LstDevGetContainedSerialNumbers : TLstDevGetContainedSerialNumbers = nil;
  LstCbDevGetProductId : TLstCbDevGetProductId = nil;
  LstCbDevGetVendorId : TLstCbDevGetVendorId = nil;
  LstCbDevGetName : TLstCbDevGetName = nil;
  LstCbDevGetNameShort : TLstCbDevGetNameShort = nil;
  LstCbDevGetNameShortest : TLstCbDevGetNameShortest = nil;
  LstCbDevGetDriverVersion : TLstCbDevGetDriverVersion = nil;
  LstCbDevGetFirmwareVersion : TLstCbDevGetFirmwareVersion = nil;
  LstCbDevGetCalibrationDate : TLstCbDevGetCalibrationDate = nil;
  LstCbScpGetChannelCount : TLstCbScpGetChannelCount = nil;
  LstSetCallbackDeviceAdded : TLstSetCallbackDeviceAdded = nil;
  LstSetCallbackDeviceRemoved : TLstSetCallbackDeviceRemoved = nil;
  LstSetCallbackDeviceCanOpenChanged : TLstSetCallbackDeviceCanOpenChanged = nil;
  {$ifdef LINUX}
  LstSetEventDeviceAdded : TLstSetEventDeviceAdded = nil;
  LstSetEventDeviceRemoved : TLstSetEventDeviceRemoved = nil;
  LstSetEventDeviceCanOpenChanged : TLstSetEventDeviceCanOpenChanged = nil;
  {$endif LINUX}
  {$ifdef MSWINDOWS}
  LstSetEventDeviceAdded : TLstSetEventDeviceAdded = nil;
  LstSetEventDeviceRemoved : TLstSetEventDeviceRemoved = nil;
  LstSetEventDeviceCanOpenChanged : TLstSetEventDeviceCanOpenChanged = nil;
  LstSetMessageDeviceAdded : TLstSetMessageDeviceAdded = nil;
  LstSetMessageDeviceRemoved : TLstSetMessageDeviceRemoved = nil;
  LstSetMessageDeviceCanOpenChanged : TLstSetMessageDeviceCanOpenChanged = nil;
  {$endif MSWINDOWS}
  NetGetAutoDetectEnabled : TNetGetAutoDetectEnabled = nil;
  NetSetAutoDetectEnabled : TNetSetAutoDetectEnabled = nil;
  NetSrvAdd : TNetSrvAdd = nil;
  NetSrvRemove : TNetSrvRemove = nil;
  NetSrvGetCount : TNetSrvGetCount = nil;
  NetSrvGetByIndex : TNetSrvGetByIndex = nil;
  NetSrvGetByURL : TNetSrvGetByURL = nil;
  NetSrvSetCallbackAdded : TNetSrvSetCallbackAdded = nil;
  {$ifdef LINUX}
  NetSrvSetEventAdded : TNetSrvSetEventAdded = nil;
  {$endif LINUX}
  {$ifdef MSWINDOWS}
  NetSrvSetEventAdded : TNetSrvSetEventAdded = nil;
  NetSrvSetMessageAdded : TNetSrvSetMessageAdded = nil;
  {$endif MSWINDOWS}
  ObjClose : TObjClose = nil;
  ObjIsRemoved : TObjIsRemoved = nil;
  ObjGetInterfaces : TObjGetInterfaces = nil;
  ObjSetEventCallback : TObjSetEventCallback = nil;
  ObjGetEvent : TObjGetEvent = nil;
  {$ifdef LINUX}
  ObjSetEventEvent : TObjSetEventEvent = nil;
  {$endif LINUX}
  {$ifdef MSWINDOWS}
  ObjSetEventEvent : TObjSetEventEvent = nil;
  ObjSetEventWindowHandle : TObjSetEventWindowHandle = nil;
  {$endif MSWINDOWS}
  DevClose : TDevClose = nil;
  DevIsRemoved : TDevIsRemoved = nil;
  DevGetDriverVersion : TDevGetDriverVersion = nil;
  DevGetFirmwareVersion : TDevGetFirmwareVersion = nil;
  DevGetCalibrationDate : TDevGetCalibrationDate = nil;
  DevGetCalibrationToken : TDevGetCalibrationToken = nil;
  DevGetSerialNumber : TDevGetSerialNumber = nil;
  DevGetIPv4Address : TDevGetIPv4Address = nil;
  DevGetIPPort : TDevGetIPPort = nil;
  DevGetProductId : TDevGetProductId = nil;
  DevGetVendorId : TDevGetVendorId = nil;
  DevGetType : TDevGetType = nil;
  DevGetName : TDevGetName = nil;
  DevGetNameShort : TDevGetNameShort = nil;
  DevGetNameShortest : TDevGetNameShortest = nil;
  DevHasBattery : TDevHasBattery = nil;
  DevGetBatteryCharge : TDevGetBatteryCharge = nil;
  DevGetBatteryTimeToEmpty : TDevGetBatteryTimeToEmpty = nil;
  DevGetBatteryTimeToFull : TDevGetBatteryTimeToFull = nil;
  DevIsBatteryChargerConnected : TDevIsBatteryChargerConnected = nil;
  DevIsBatteryCharging : TDevIsBatteryCharging = nil;
  DevIsBatteryBroken : TDevIsBatteryBroken = nil;
  DevSetCallbackRemoved : TDevSetCallbackRemoved = nil;
  {$ifdef LINUX}
  DevSetEventRemoved : TDevSetEventRemoved = nil;
  {$endif LINUX}
  {$ifdef MSWINDOWS}
  DevSetEventRemoved : TDevSetEventRemoved = nil;
  DevSetMessageRemoved : TDevSetMessageRemoved = nil;
  {$endif MSWINDOWS}
  DevTrGetInputCount : TDevTrGetInputCount = nil;
  DevTrGetInputIndexById : TDevTrGetInputIndexById = nil;
  ScpTrInIsTriggered : TScpTrInIsTriggered = nil;
  DevTrInGetEnabled : TDevTrInGetEnabled = nil;
  DevTrInSetEnabled : TDevTrInSetEnabled = nil;
  DevTrInGetKinds : TDevTrInGetKinds = nil;
  ScpTrInGetKindsEx : TScpTrInGetKindsEx = nil;
  DevTrInGetKind : TDevTrInGetKind = nil;
  DevTrInSetKind : TDevTrInSetKind = nil;
  DevTrInIsAvailable : TDevTrInIsAvailable = nil;
  ScpTrInIsAvailableEx : TScpTrInIsAvailableEx = nil;
  DevTrInGetId : TDevTrInGetId = nil;
  DevTrInGetName : TDevTrInGetName = nil;
  DevTrGetOutputCount : TDevTrGetOutputCount = nil;
  DevTrGetOutputIndexById : TDevTrGetOutputIndexById = nil;
  DevTrOutGetEnabled : TDevTrOutGetEnabled = nil;
  DevTrOutSetEnabled : TDevTrOutSetEnabled = nil;
  DevTrOutGetEvents : TDevTrOutGetEvents = nil;
  DevTrOutGetEvent : TDevTrOutGetEvent = nil;
  DevTrOutSetEvent : TDevTrOutSetEvent = nil;
  DevTrOutGetId : TDevTrOutGetId = nil;
  DevTrOutGetName : TDevTrOutGetName = nil;
  DevTrOutTrigger : TDevTrOutTrigger = nil;
  ScpGetChannelCount : TScpGetChannelCount = nil;
  ScpChIsAvailable : TScpChIsAvailable = nil;
  ScpChIsAvailableEx : TScpChIsAvailableEx = nil;
  ScpChGetConnectorType : TScpChGetConnectorType = nil;
  ScpChIsDifferential : TScpChIsDifferential = nil;
  ScpChGetImpedance : TScpChGetImpedance = nil;
  ScpChGetBandwidths : TScpChGetBandwidths = nil;
  ScpChGetBandwidth : TScpChGetBandwidth = nil;
  ScpChSetBandwidth : TScpChSetBandwidth = nil;
  ScpChGetCouplings : TScpChGetCouplings = nil;
  ScpChGetCoupling : TScpChGetCoupling = nil;
  ScpChSetCoupling : TScpChSetCoupling = nil;
  ScpChGetEnabled : TScpChGetEnabled = nil;
  ScpChSetEnabled : TScpChSetEnabled = nil;
  ScpChGetProbeGain : TScpChGetProbeGain = nil;
  ScpChSetProbeGain : TScpChSetProbeGain = nil;
  ScpChGetProbeOffset : TScpChGetProbeOffset = nil;
  ScpChSetProbeOffset : TScpChSetProbeOffset = nil;
  ScpChGetAutoRanging : TScpChGetAutoRanging = nil;
  ScpChSetAutoRanging : TScpChSetAutoRanging = nil;
  ScpChGetRanges : TScpChGetRanges = nil;
  ScpChGetRangesEx : TScpChGetRangesEx = nil;
  ScpChGetRange : TScpChGetRange = nil;
  ScpChSetRange : TScpChSetRange = nil;
  ScpChHasSafeGround : TScpChHasSafeGround = nil;
  ScpChGetSafeGroundEnabled : TScpChGetSafeGroundEnabled = nil;
  ScpChSetSafeGroundEnabled : TScpChSetSafeGroundEnabled = nil;
  ScpChGetSafeGroundThresholdMin : TScpChGetSafeGroundThresholdMin = nil;
  ScpChGetSafeGroundThresholdMax : TScpChGetSafeGroundThresholdMax = nil;
  ScpChGetSafeGroundThreshold : TScpChGetSafeGroundThreshold = nil;
  ScpChSetSafeGroundThreshold : TScpChSetSafeGroundThreshold = nil;
  ScpChVerifySafeGroundThreshold : TScpChVerifySafeGroundThreshold = nil;
  ScpChHasTrigger : TScpChHasTrigger = nil;
  ScpChHasTriggerEx : TScpChHasTriggerEx = nil;
  ScpChTrIsAvailable : TScpChTrIsAvailable = nil;
  ScpChTrIsAvailableEx : TScpChTrIsAvailableEx = nil;
  ScpChTrIsTriggered : TScpChTrIsTriggered = nil;
  ScpChTrGetEnabled : TScpChTrGetEnabled = nil;
  ScpChTrSetEnabled : TScpChTrSetEnabled = nil;
  ScpChTrGetKinds : TScpChTrGetKinds = nil;
  ScpChTrGetKindsEx : TScpChTrGetKindsEx = nil;
  ScpChTrGetKind : TScpChTrGetKind = nil;
  ScpChTrSetKind : TScpChTrSetKind = nil;
  ScpChTrGetLevelModes : TScpChTrGetLevelModes = nil;
  ScpChTrGetLevelMode : TScpChTrGetLevelMode = nil;
  ScpChTrSetLevelMode : TScpChTrSetLevelMode = nil;
  ScpChTrGetLevelCount : TScpChTrGetLevelCount = nil;
  ScpChTrGetLevel : TScpChTrGetLevel = nil;
  ScpChTrSetLevel : TScpChTrSetLevel = nil;
  ScpChTrGetHysteresisCount : TScpChTrGetHysteresisCount = nil;
  ScpChTrGetHysteresis : TScpChTrGetHysteresis = nil;
  ScpChTrSetHysteresis : TScpChTrSetHysteresis = nil;
  ScpChTrGetConditions : TScpChTrGetConditions = nil;
  ScpChTrGetConditionsEx : TScpChTrGetConditionsEx = nil;
  ScpChTrGetCondition : TScpChTrGetCondition = nil;
  ScpChTrSetCondition : TScpChTrSetCondition = nil;
  ScpChTrGetTimeCount : TScpChTrGetTimeCount = nil;
  ScpChTrGetTime : TScpChTrGetTime = nil;
  ScpChTrSetTime : TScpChTrSetTime = nil;
  ScpChTrVerifyTime : TScpChTrVerifyTime = nil;
  ScpChTrVerifyTimeEx2 : TScpChTrVerifyTimeEx2 = nil;
  ScpGetData : TScpGetData = nil;
  ScpGetData1Ch : TScpGetData1Ch = nil;
  ScpGetData2Ch : TScpGetData2Ch = nil;
  ScpGetData3Ch : TScpGetData3Ch = nil;
  ScpGetData4Ch : TScpGetData4Ch = nil;
  ScpGetData5Ch : TScpGetData5Ch = nil;
  ScpGetData6Ch : TScpGetData6Ch = nil;
  ScpGetData7Ch : TScpGetData7Ch = nil;
  ScpGetData8Ch : TScpGetData8Ch = nil;
  ScpGetValidPreSampleCount : TScpGetValidPreSampleCount = nil;
  ScpChGetDataValueRange : TScpChGetDataValueRange = nil;
  ScpChGetDataValueMin : TScpChGetDataValueMin = nil;
  ScpChGetDataValueMax : TScpChGetDataValueMax = nil;
  ScpGetDataRaw : TScpGetDataRaw = nil;
  ScpGetDataRaw1Ch : TScpGetDataRaw1Ch = nil;
  ScpGetDataRaw2Ch : TScpGetDataRaw2Ch = nil;
  ScpGetDataRaw3Ch : TScpGetDataRaw3Ch = nil;
  ScpGetDataRaw4Ch : TScpGetDataRaw4Ch = nil;
  ScpGetDataRaw5Ch : TScpGetDataRaw5Ch = nil;
  ScpGetDataRaw6Ch : TScpGetDataRaw6Ch = nil;
  ScpGetDataRaw7Ch : TScpGetDataRaw7Ch = nil;
  ScpGetDataRaw8Ch : TScpGetDataRaw8Ch = nil;
  ScpChGetDataRawType : TScpChGetDataRawType = nil;
  ScpChGetDataRawValueRange : TScpChGetDataRawValueRange = nil;
  ScpChGetDataRawValueMin : TScpChGetDataRawValueMin = nil;
  ScpChGetDataRawValueZero : TScpChGetDataRawValueZero = nil;
  ScpChGetDataRawValueMax : TScpChGetDataRawValueMax = nil;
  ScpChIsRangeMaxReachable : TScpChIsRangeMaxReachable = nil;
  ScpIsGetDataAsyncCompleted : TScpIsGetDataAsyncCompleted = nil;
  ScpStartGetDataAsync : TScpStartGetDataAsync = nil;
  ScpStartGetDataAsyncRaw : TScpStartGetDataAsyncRaw = nil;
  ScpCancelGetDataAsync : TScpCancelGetDataAsync = nil;
  ScpSetCallbackDataReady : TScpSetCallbackDataReady = nil;
  ScpSetCallbackDataOverflow : TScpSetCallbackDataOverflow = nil;
  ScpSetCallbackConnectionTestCompleted : TScpSetCallbackConnectionTestCompleted = nil;
  ScpSetCallbackTriggered : TScpSetCallbackTriggered = nil;
  {$ifdef LINUX}
  ScpSetEventDataReady : TScpSetEventDataReady = nil;
  ScpSetEventDataOverflow : TScpSetEventDataOverflow = nil;
  ScpSetEventConnectionTestCompleted : TScpSetEventConnectionTestCompleted = nil;
  ScpSetEventTriggered : TScpSetEventTriggered = nil;
  {$endif LINUX}
  {$ifdef MSWINDOWS}
  ScpSetEventDataReady : TScpSetEventDataReady = nil;
  ScpSetEventDataOverflow : TScpSetEventDataOverflow = nil;
  ScpSetEventConnectionTestCompleted : TScpSetEventConnectionTestCompleted = nil;
  ScpSetEventTriggered : TScpSetEventTriggered = nil;
  ScpSetMessageDataReady : TScpSetMessageDataReady = nil;
  ScpSetMessageDataOverflow : TScpSetMessageDataOverflow = nil;
  ScpSetMessageConnectionTestCompleted : TScpSetMessageConnectionTestCompleted = nil;
  ScpSetMessageTriggered : TScpSetMessageTriggered = nil;
  {$endif MSWINDOWS}
  ScpStart : TScpStart = nil;
  ScpStop : TScpStop = nil;
  ScpForceTrigger : TScpForceTrigger = nil;
  ScpGetMeasureModes : TScpGetMeasureModes = nil;
  ScpGetMeasureMode : TScpGetMeasureMode = nil;
  ScpSetMeasureMode : TScpSetMeasureMode = nil;
  ScpIsRunning : TScpIsRunning = nil;
  ScpIsTriggered : TScpIsTriggered = nil;
  ScpIsTimeOutTriggered : TScpIsTimeOutTriggered = nil;
  ScpIsForceTriggered : TScpIsForceTriggered = nil;
  ScpIsDataReady : TScpIsDataReady = nil;
  ScpIsDataOverflow : TScpIsDataOverflow = nil;
  ScpGetAutoResolutionModes : TScpGetAutoResolutionModes = nil;
  ScpGetAutoResolutionMode : TScpGetAutoResolutionMode = nil;
  ScpSetAutoResolutionMode : TScpSetAutoResolutionMode = nil;
  ScpGetResolutions : TScpGetResolutions = nil;
  ScpGetResolution : TScpGetResolution = nil;
  ScpSetResolution : TScpSetResolution = nil;
  ScpIsResolutionEnhanced : TScpIsResolutionEnhanced = nil;
  ScpIsResolutionEnhancedEx : TScpIsResolutionEnhancedEx = nil;
  ScpGetClockSources : TScpGetClockSources = nil;
  ScpGetClockSource : TScpGetClockSource = nil;
  ScpSetClockSource : TScpSetClockSource = nil;
  ScpGetClockSourceFrequencies : TScpGetClockSourceFrequencies = nil;
  ScpGetClockSourceFrequenciesEx : TScpGetClockSourceFrequenciesEx = nil;
  ScpGetClockSourceFrequency : TScpGetClockSourceFrequency = nil;
  ScpSetClockSourceFrequency : TScpSetClockSourceFrequency = nil;
  ScpGetClockOutputs : TScpGetClockOutputs = nil;
  ScpGetClockOutput : TScpGetClockOutput = nil;
  ScpSetClockOutput : TScpSetClockOutput = nil;
  ScpGetClockOutputFrequencies : TScpGetClockOutputFrequencies = nil;
  ScpGetClockOutputFrequenciesEx : TScpGetClockOutputFrequenciesEx = nil;
  ScpGetClockOutputFrequency : TScpGetClockOutputFrequency = nil;
  ScpSetClockOutputFrequency : TScpSetClockOutputFrequency = nil;
  ScpGetSampleFrequencyMax : TScpGetSampleFrequencyMax = nil;
  ScpGetSampleFrequency : TScpGetSampleFrequency = nil;
  ScpSetSampleFrequency : TScpSetSampleFrequency = nil;
  ScpVerifySampleFrequency : TScpVerifySampleFrequency = nil;
  ScpVerifySampleFrequencyEx : TScpVerifySampleFrequencyEx = nil;
  ScpVerifySampleFrequenciesEx : TScpVerifySampleFrequenciesEx = nil;
  ScpGetRecordLengthMax : TScpGetRecordLengthMax = nil;
  ScpGetRecordLengthMaxEx : TScpGetRecordLengthMaxEx = nil;
  ScpGetRecordLength : TScpGetRecordLength = nil;
  ScpSetRecordLength : TScpSetRecordLength = nil;
  ScpVerifyRecordLength : TScpVerifyRecordLength = nil;
  ScpVerifyRecordLengthEx : TScpVerifyRecordLengthEx = nil;
  ScpGetPreSampleRatio : TScpGetPreSampleRatio = nil;
  ScpSetPreSampleRatio : TScpSetPreSampleRatio = nil;
  ScpGetSegmentCountMax : TScpGetSegmentCountMax = nil;
  ScpGetSegmentCountMaxEx : TScpGetSegmentCountMaxEx = nil;
  ScpGetSegmentCount : TScpGetSegmentCount = nil;
  ScpSetSegmentCount : TScpSetSegmentCount = nil;
  ScpVerifySegmentCount : TScpVerifySegmentCount = nil;
  ScpVerifySegmentCountEx2 : TScpVerifySegmentCountEx2 = nil;
  ScpHasTrigger : TScpHasTrigger = nil;
  ScpHasTriggerEx : TScpHasTriggerEx = nil;
  ScpGetTriggerTimeOut : TScpGetTriggerTimeOut = nil;
  ScpSetTriggerTimeOut : TScpSetTriggerTimeOut = nil;
  ScpVerifyTriggerTimeOut : TScpVerifyTriggerTimeOut = nil;
  ScpVerifyTriggerTimeOutEx : TScpVerifyTriggerTimeOutEx = nil;
  ScpHasTriggerDelay : TScpHasTriggerDelay = nil;
  ScpHasTriggerDelayEx : TScpHasTriggerDelayEx = nil;
  ScpGetTriggerDelayMax : TScpGetTriggerDelayMax = nil;
  ScpGetTriggerDelayMaxEx : TScpGetTriggerDelayMaxEx = nil;
  ScpGetTriggerDelay : TScpGetTriggerDelay = nil;
  ScpSetTriggerDelay : TScpSetTriggerDelay = nil;
  ScpVerifyTriggerDelay : TScpVerifyTriggerDelay = nil;
  ScpVerifyTriggerDelayEx : TScpVerifyTriggerDelayEx = nil;
  ScpHasTriggerHoldOff : TScpHasTriggerHoldOff = nil;
  ScpHasTriggerHoldOffEx : TScpHasTriggerHoldOffEx = nil;
  ScpGetTriggerHoldOffCountMax : TScpGetTriggerHoldOffCountMax = nil;
  ScpGetTriggerHoldOffCountMaxEx : TScpGetTriggerHoldOffCountMaxEx = nil;
  ScpGetTriggerHoldOffCount : TScpGetTriggerHoldOffCount = nil;
  ScpSetTriggerHoldOffCount : TScpSetTriggerHoldOffCount = nil;
  ScpHasConnectionTest : TScpHasConnectionTest = nil;
  ScpChHasConnectionTest : TScpChHasConnectionTest = nil;
  ScpStartConnectionTest : TScpStartConnectionTest = nil;
  ScpStartConnectionTestEx : TScpStartConnectionTestEx = nil;
  ScpIsConnectionTestCompleted : TScpIsConnectionTestCompleted = nil;
  ScpGetConnectionTestData : TScpGetConnectionTestData = nil;
  GenGetConnectorType : TGenGetConnectorType = nil;
  GenIsDifferential : TGenIsDifferential = nil;
  GenGetImpedance : TGenGetImpedance = nil;
  GenGetResolution : TGenGetResolution = nil;
  GenGetOutputValueMin : TGenGetOutputValueMin = nil;
  GenGetOutputValueMax : TGenGetOutputValueMax = nil;
  GenGetOutputValueMinMax : TGenGetOutputValueMinMax = nil;
  GenIsControllable : TGenIsControllable = nil;
  GenIsRunning : TGenIsRunning = nil;
  GenGetStatus : TGenGetStatus = nil;
  GenGetOutputOn : TGenGetOutputOn = nil;
  GenSetOutputOn : TGenSetOutputOn = nil;
  GenHasOutputInvert : TGenHasOutputInvert = nil;
  GenGetOutputInvert : TGenGetOutputInvert = nil;
  GenSetOutputInvert : TGenSetOutputInvert = nil;
  GenStart : TGenStart = nil;
  GenStop : TGenStop = nil;
  GenGetSignalTypes : TGenGetSignalTypes = nil;
  GenGetSignalType : TGenGetSignalType = nil;
  GenSetSignalType : TGenSetSignalType = nil;
  GenHasAmplitude : TGenHasAmplitude = nil;
  GenHasAmplitudeEx : TGenHasAmplitudeEx = nil;
  GenGetAmplitudeMin : TGenGetAmplitudeMin = nil;
  GenGetAmplitudeMax : TGenGetAmplitudeMax = nil;
  GenGetAmplitudeMinMaxEx : TGenGetAmplitudeMinMaxEx = nil;
  GenGetAmplitude : TGenGetAmplitude = nil;
  GenSetAmplitude : TGenSetAmplitude = nil;
  GenVerifyAmplitude : TGenVerifyAmplitude = nil;
  GenVerifyAmplitudeEx : TGenVerifyAmplitudeEx = nil;
  GenGetAmplitudeRanges : TGenGetAmplitudeRanges = nil;
  GenGetAmplitudeRange : TGenGetAmplitudeRange = nil;
  GenSetAmplitudeRange : TGenSetAmplitudeRange = nil;
  GenGetAmplitudeAutoRanging : TGenGetAmplitudeAutoRanging = nil;
  GenSetAmplitudeAutoRanging : TGenSetAmplitudeAutoRanging = nil;
  GenHasOffset : TGenHasOffset = nil;
  GenHasOffsetEx : TGenHasOffsetEx = nil;
  GenGetOffsetMin : TGenGetOffsetMin = nil;
  GenGetOffsetMax : TGenGetOffsetMax = nil;
  GenGetOffsetMinMaxEx : TGenGetOffsetMinMaxEx = nil;
  GenGetOffset : TGenGetOffset = nil;
  GenSetOffset : TGenSetOffset = nil;
  GenVerifyOffset : TGenVerifyOffset = nil;
  GenVerifyOffsetEx : TGenVerifyOffsetEx = nil;
  GenGetFrequencyModes : TGenGetFrequencyModes = nil;
  GenGetFrequencyModesEx : TGenGetFrequencyModesEx = nil;
  GenGetFrequencyMode : TGenGetFrequencyMode = nil;
  GenSetFrequencyMode : TGenSetFrequencyMode = nil;
  GenHasFrequency : TGenHasFrequency = nil;
  GenHasFrequencyEx : TGenHasFrequencyEx = nil;
  GenGetFrequencyMin : TGenGetFrequencyMin = nil;
  GenGetFrequencyMax : TGenGetFrequencyMax = nil;
  GenGetFrequencyMinMax : TGenGetFrequencyMinMax = nil;
  GenGetFrequencyMinMaxEx : TGenGetFrequencyMinMaxEx = nil;
  GenGetFrequency : TGenGetFrequency = nil;
  GenSetFrequency : TGenSetFrequency = nil;
  GenVerifyFrequency : TGenVerifyFrequency = nil;
  GenVerifyFrequencyEx2 : TGenVerifyFrequencyEx2 = nil;
  GenHasPhase : TGenHasPhase = nil;
  GenHasPhaseEx : TGenHasPhaseEx = nil;
  GenGetPhaseMin : TGenGetPhaseMin = nil;
  GenGetPhaseMax : TGenGetPhaseMax = nil;
  GenGetPhaseMinMaxEx : TGenGetPhaseMinMaxEx = nil;
  GenGetPhase : TGenGetPhase = nil;
  GenSetPhase : TGenSetPhase = nil;
  GenVerifyPhase : TGenVerifyPhase = nil;
  GenVerifyPhaseEx : TGenVerifyPhaseEx = nil;
  GenHasSymmetry : TGenHasSymmetry = nil;
  GenHasSymmetryEx : TGenHasSymmetryEx = nil;
  GenGetSymmetryMin : TGenGetSymmetryMin = nil;
  GenGetSymmetryMax : TGenGetSymmetryMax = nil;
  GenGetSymmetryMinMaxEx : TGenGetSymmetryMinMaxEx = nil;
  GenGetSymmetry : TGenGetSymmetry = nil;
  GenSetSymmetry : TGenSetSymmetry = nil;
  GenVerifySymmetry : TGenVerifySymmetry = nil;
  GenVerifySymmetryEx : TGenVerifySymmetryEx = nil;
  GenHasWidth : TGenHasWidth = nil;
  GenHasWidthEx : TGenHasWidthEx = nil;
  GenGetWidthMin : TGenGetWidthMin = nil;
  GenGetWidthMax : TGenGetWidthMax = nil;
  GenGetWidthMinMaxEx : TGenGetWidthMinMaxEx = nil;
  GenGetWidth : TGenGetWidth = nil;
  GenSetWidth : TGenSetWidth = nil;
  GenVerifyWidth : TGenVerifyWidth = nil;
  GenVerifyWidthEx : TGenVerifyWidthEx = nil;
  GenHasEdgeTime : TGenHasEdgeTime = nil;
  GenHasEdgeTimeEx : TGenHasEdgeTimeEx = nil;
  GenGetLeadingEdgeTimeMin : TGenGetLeadingEdgeTimeMin = nil;
  GenGetLeadingEdgeTimeMax : TGenGetLeadingEdgeTimeMax = nil;
  GenGetLeadingEdgeTimeMinMaxEx : TGenGetLeadingEdgeTimeMinMaxEx = nil;
  GenGetLeadingEdgeTime : TGenGetLeadingEdgeTime = nil;
  GenSetLeadingEdgeTime : TGenSetLeadingEdgeTime = nil;
  GenVerifyLeadingEdgeTime : TGenVerifyLeadingEdgeTime = nil;
  GenVerifyLeadingEdgeTimeEx : TGenVerifyLeadingEdgeTimeEx = nil;
  GenGetTrailingEdgeTimeMin : TGenGetTrailingEdgeTimeMin = nil;
  GenGetTrailingEdgeTimeMax : TGenGetTrailingEdgeTimeMax = nil;
  GenGetTrailingEdgeTimeMinMaxEx : TGenGetTrailingEdgeTimeMinMaxEx = nil;
  GenGetTrailingEdgeTime : TGenGetTrailingEdgeTime = nil;
  GenSetTrailingEdgeTime : TGenSetTrailingEdgeTime = nil;
  GenVerifyTrailingEdgeTime : TGenVerifyTrailingEdgeTime = nil;
  GenVerifyTrailingEdgeTimeEx : TGenVerifyTrailingEdgeTimeEx = nil;
  GenHasData : TGenHasData = nil;
  GenHasDataEx : TGenHasDataEx = nil;
  GenGetDataLengthMin : TGenGetDataLengthMin = nil;
  GenGetDataLengthMax : TGenGetDataLengthMax = nil;
  GenGetDataLengthMinMaxEx : TGenGetDataLengthMinMaxEx = nil;
  GenGetDataLength : TGenGetDataLength = nil;
  GenVerifyDataLength : TGenVerifyDataLength = nil;
  GenVerifyDataLengthEx : TGenVerifyDataLengthEx = nil;
  GenSetData : TGenSetData = nil;
  GenSetDataEx : TGenSetDataEx = nil;
  GenGetDataRawType : TGenGetDataRawType = nil;
  GenGetDataRawValueRange : TGenGetDataRawValueRange = nil;
  GenGetDataRawValueMin : TGenGetDataRawValueMin = nil;
  GenGetDataRawValueZero : TGenGetDataRawValueZero = nil;
  GenGetDataRawValueMax : TGenGetDataRawValueMax = nil;
  GenSetDataRaw : TGenSetDataRaw = nil;
  GenSetDataRawEx : TGenSetDataRawEx = nil;
  GenGetModes : TGenGetModes = nil;
  GenGetModesEx : TGenGetModesEx = nil;
  GenGetModesNative : TGenGetModesNative = nil;
  GenGetMode : TGenGetMode = nil;
  GenSetMode : TGenSetMode = nil;
  GenIsBurstActive : TGenIsBurstActive = nil;
  GenGetBurstCountMin : TGenGetBurstCountMin = nil;
  GenGetBurstCountMax : TGenGetBurstCountMax = nil;
  GenGetBurstCountMinMaxEx : TGenGetBurstCountMinMaxEx = nil;
  GenGetBurstCount : TGenGetBurstCount = nil;
  GenSetBurstCount : TGenSetBurstCount = nil;
  GenGetBurstSampleCountMin : TGenGetBurstSampleCountMin = nil;
  GenGetBurstSampleCountMax : TGenGetBurstSampleCountMax = nil;
  GenGetBurstSampleCountMinMaxEx : TGenGetBurstSampleCountMinMaxEx = nil;
  GenGetBurstSampleCount : TGenGetBurstSampleCount = nil;
  GenSetBurstSampleCount : TGenSetBurstSampleCount = nil;
  GenGetBurstSegmentCountMin : TGenGetBurstSegmentCountMin = nil;
  GenGetBurstSegmentCountMax : TGenGetBurstSegmentCountMax = nil;
  GenGetBurstSegmentCountMinMaxEx : TGenGetBurstSegmentCountMinMaxEx = nil;
  GenGetBurstSegmentCount : TGenGetBurstSegmentCount = nil;
  GenSetBurstSegmentCount : TGenSetBurstSegmentCount = nil;
  GenVerifyBurstSegmentCount : TGenVerifyBurstSegmentCount = nil;
  GenVerifyBurstSegmentCountEx : TGenVerifyBurstSegmentCountEx = nil;
  GenSetCallbackBurstCompleted : TGenSetCallbackBurstCompleted = nil;
  {$ifdef LINUX}
  GenSetEventBurstCompleted : TGenSetEventBurstCompleted = nil;
  {$endif LINUX}
  {$ifdef MSWINDOWS}
  GenSetEventBurstCompleted : TGenSetEventBurstCompleted = nil;
  GenSetMessageBurstCompleted : TGenSetMessageBurstCompleted = nil;
  {$endif MSWINDOWS}
  GenSetCallbackControllableChanged : TGenSetCallbackControllableChanged = nil;
  {$ifdef LINUX}
  GenSetEventControllableChanged : TGenSetEventControllableChanged = nil;
  {$endif LINUX}
  {$ifdef MSWINDOWS}
  GenSetEventControllableChanged : TGenSetEventControllableChanged = nil;
  GenSetMessageControllableChanged : TGenSetMessageControllableChanged = nil;
  {$endif MSWINDOWS}
  I2CIsInternalAddress : TI2CIsInternalAddress = nil;
  I2CGetInternalAddresses : TI2CGetInternalAddresses = nil;
  I2CRead : TI2CRead = nil;
  I2CReadByte : TI2CReadByte = nil;
  I2CReadWord : TI2CReadWord = nil;
  I2CWrite : TI2CWrite = nil;
  I2CWriteByte : TI2CWriteByte = nil;
  I2CWriteByteByte : TI2CWriteByteByte = nil;
  I2CWriteByteWord : TI2CWriteByteWord = nil;
  I2CWriteWord : TI2CWriteWord = nil;
  I2CWriteRead : TI2CWriteRead = nil;
  I2CGetSpeedMax : TI2CGetSpeedMax = nil;
  I2CGetSpeed : TI2CGetSpeed = nil;
  I2CSetSpeed : TI2CSetSpeed = nil;
  I2CVerifySpeed : TI2CVerifySpeed = nil;
  SrvConnect : TSrvConnect = nil;
  SrvDisconnect : TSrvDisconnect = nil;
  SrvRemove : TSrvRemove = nil;
  SrvGetStatus : TSrvGetStatus = nil;
  SrvGetLastError : TSrvGetLastError = nil;
  SrvGetURL : TSrvGetURL = nil;
  SrvGetID : TSrvGetID = nil;
  SrvGetIPv4Address : TSrvGetIPv4Address = nil;
  SrvGetIPPort : TSrvGetIPPort = nil;
  SrvGetName : TSrvGetName = nil;
  SrvGetDescription : TSrvGetDescription = nil;
  SrvGetVersion : TSrvGetVersion = nil;
  SrvGetVersionExtra : TSrvGetVersionExtra = nil;
  HlpPointerArrayNew : THlpPointerArrayNew = nil;
  HlpPointerArraySet : THlpPointerArraySet = nil;
  HlpPointerArrayDelete : THlpPointerArrayDelete = nil;

function LibTiePieLoad( const sLibTiePieFileName : string = sLibTiePieFileNameDefault ) : Boolean;
function LibTiePieUnload : Boolean;

{$else} // LIBTIEPIE_STATIC

procedure LibInit; cdecl;
function LibIsInitialized : ByteBool; cdecl;
procedure LibExit; cdecl;
function LibGetVersion : TTpVersion; cdecl;
function LibGetVersionExtra : PAnsiChar; cdecl;
function LibGetConfig( pBuffer : PByte ; dwBufferLength : LongWord ) : LongWord; cdecl;
function LibGetLastStatus : TLibTiePieStatus; cdecl;
function LibGetLastStatusStr : PAnsiChar; cdecl;
procedure LstUpdate; cdecl;
function LstGetCount : LongWord; cdecl;
function LstOpenDevice( dwIdKind , dwId , dwDeviceType : LongWord ) : TLibTiePieHandle; cdecl;
function LstOpenOscilloscope( dwIdKind , dwId : LongWord ) : TLibTiePieHandle; cdecl;
function LstOpenGenerator( dwIdKind , dwId : LongWord ) : TLibTiePieHandle; cdecl;
function LstOpenI2CHost( dwIdKind , dwId : LongWord ) : TLibTiePieHandle; cdecl;
function LstCreateCombinedDevice( pDeviceHandles : PLibTiePieHandle ; dwCount : LongWord ) : LongWord; cdecl;
function LstCreateAndOpenCombinedDevice( pDeviceHandles : PLibTiePieHandle ; dwCount : LongWord ) : TLibTiePieHandle; cdecl;
procedure LstRemoveDevice( dwSerialNumber : LongWord ); cdecl;
procedure LstRemoveDeviceForce( dwSerialNumber : LongWord ); cdecl;
function LstDevCanOpen( dwIdKind , dwId , dwDeviceType : LongWord ) : ByteBool; cdecl;
function LstDevGetProductId( dwIdKind , dwId : LongWord ) : LongWord; cdecl;
function LstDevGetVendorId( dwIdKind , dwId : LongWord ) : LongWord; cdecl;
function LstDevGetName( dwIdKind , dwId : LongWord ; pBuffer : PAnsiChar ; dwBufferLength : LongWord ) : LongWord; cdecl;
function LstDevGetNameShort( dwIdKind , dwId : LongWord ; pBuffer : PAnsiChar ; dwBufferLength : LongWord ) : LongWord; cdecl;
function LstDevGetNameShortest( dwIdKind , dwId : LongWord ; pBuffer : PAnsiChar ; dwBufferLength : LongWord ) : LongWord; cdecl;
function LstDevGetDriverVersion( dwIdKind , dwId : LongWord ) : TTpVersion; cdecl;
function LstDevGetRecommendedDriverVersion( dwIdKind , dwId : LongWord ) : TTpVersion; cdecl;
function LstDevGetFirmwareVersion( dwIdKind , dwId : LongWord ) : TTpVersion; cdecl;
function LstDevGetRecommendedFirmwareVersion( dwIdKind , dwId : LongWord ) : TTpVersion; cdecl;
function LstDevGetCalibrationDate( dwIdKind , dwId : LongWord ) : TTpDate; cdecl;
function LstDevGetSerialNumber( dwIdKind , dwId : LongWord ) : LongWord; cdecl;
function LstDevGetIPv4Address( dwIdKind , dwId : LongWord ) : LongWord; cdecl;
function LstDevGetIPPort( dwIdKind , dwId : LongWord ) : Word; cdecl;
function LstDevHasServer( dwIdKind , dwId : LongWord ) : ByteBool; cdecl;
function LstDevGetServer( dwIdKind , dwId : LongWord ) : TLibTiePieHandle; cdecl;
function LstDevGetTypes( dwIdKind , dwId : LongWord ) : LongWord; cdecl;
function LstDevGetContainedSerialNumbers( dwIdKind , dwId : LongWord ; pBuffer : PLongWord ; dwBufferLength : LongWord ) : LongWord; cdecl;
function LstCbDevGetProductId( dwIdKind , dwId , dwContainedDeviceSerialNumber : LongWord ) : LongWord; cdecl;
function LstCbDevGetVendorId( dwIdKind , dwId , dwContainedDeviceSerialNumber : LongWord ) : LongWord; cdecl;
function LstCbDevGetName( dwIdKind , dwId , dwContainedDeviceSerialNumber : LongWord ; pBuffer : PAnsiChar ; dwBufferLength : LongWord ) : LongWord; cdecl;
function LstCbDevGetNameShort( dwIdKind , dwId , dwContainedDeviceSerialNumber : LongWord ; pBuffer : PAnsiChar ; dwBufferLength : LongWord ) : LongWord; cdecl;
function LstCbDevGetNameShortest( dwIdKind , dwId , dwContainedDeviceSerialNumber : LongWord ; pBuffer : PAnsiChar ; dwBufferLength : LongWord ) : LongWord; cdecl;
function LstCbDevGetDriverVersion( dwIdKind , dwId , dwContainedDeviceSerialNumber : LongWord ) : TTpVersion; cdecl;
function LstCbDevGetFirmwareVersion( dwIdKind , dwId , dwContainedDeviceSerialNumber : LongWord ) : TTpVersion; cdecl;
function LstCbDevGetCalibrationDate( dwIdKind , dwId , dwContainedDeviceSerialNumber : LongWord ) : TTpDate; cdecl;
function LstCbScpGetChannelCount( dwIdKind , dwId , dwContainedDeviceSerialNumber : LongWord ) : Word; cdecl;
procedure LstSetCallbackDeviceAdded( pCallback : TTpCallbackDeviceList ; pData : Pointer ); cdecl;
procedure LstSetCallbackDeviceRemoved( pCallback : TTpCallbackDeviceList ; pData : Pointer ); cdecl;
procedure LstSetCallbackDeviceCanOpenChanged( pCallback : TTpCallbackDeviceList ; pData : Pointer ); cdecl;
{$ifdef LINUX}
procedure LstSetEventDeviceAdded( fdEvent : Integer ); cdecl;
procedure LstSetEventDeviceRemoved( fdEvent : Integer ); cdecl;
procedure LstSetEventDeviceCanOpenChanged( fdEvent : Integer ); cdecl;
{$endif LINUX}
{$ifdef MSWINDOWS}
procedure LstSetEventDeviceAdded( hEvent : THandle ); cdecl;
procedure LstSetEventDeviceRemoved( hEvent : THandle ); cdecl;
procedure LstSetEventDeviceCanOpenChanged( hEvent : THandle ); cdecl;
procedure LstSetMessageDeviceAdded( hWnd : HWND ); cdecl;
procedure LstSetMessageDeviceRemoved( hWnd : HWND ); cdecl;
procedure LstSetMessageDeviceCanOpenChanged( hWnd : HWND ); cdecl;
{$endif MSWINDOWS}
function NetGetAutoDetectEnabled : ByteBool; cdecl;
function NetSetAutoDetectEnabled( bEnable : ByteBool ) : ByteBool; cdecl;
function NetSrvAdd( pURL : PAnsiChar ; dwURLLength : LongWord ; pHandle : PLibTiePieHandle ) : ByteBool; cdecl;
function NetSrvRemove( pURL : PAnsiChar ; dwURLLength : LongWord ; bForce : ByteBool ) : ByteBool; cdecl;
function NetSrvGetCount : LongWord; cdecl;
function NetSrvGetByIndex( dwIndex : LongWord ) : TLibTiePieHandle; cdecl;
function NetSrvGetByURL( pURL : PAnsiChar ; dwURLLength : LongWord ) : TLibTiePieHandle; cdecl;
procedure NetSrvSetCallbackAdded( pCallback : TTpCallbackHandle ; pData : Pointer ); cdecl;
{$ifdef LINUX}
procedure NetSrvSetEventAdded( fdEvent : Integer ); cdecl;
{$endif LINUX}
{$ifdef MSWINDOWS}
procedure NetSrvSetEventAdded( hEvent : THandle ); cdecl;
procedure NetSrvSetMessageAdded( hWnd : HWND ); cdecl;
{$endif MSWINDOWS}
procedure ObjClose( hHandle : TLibTiePieHandle ); cdecl;
function ObjIsRemoved( hHandle : TLibTiePieHandle ) : ByteBool; cdecl;
function ObjGetInterfaces( hHandle : TLibTiePieHandle ) : UInt64; cdecl;
procedure ObjSetEventCallback( hHandle : TLibTiePieHandle ; pCallback : TTpCallbackEvent ; pData : Pointer ); cdecl;
function ObjGetEvent( hHandle : TLibTiePieHandle ; pEvent , pValue : PLongWord ) : ByteBool; cdecl;
{$ifdef LINUX}
procedure ObjSetEventEvent( hHandle : TLibTiePieHandle ; fdEvent : Integer ); cdecl;
{$endif LINUX}
{$ifdef MSWINDOWS}
procedure ObjSetEventEvent( hHandle : TLibTiePieHandle ; hEvent : THandle ); cdecl;
procedure ObjSetEventWindowHandle( hHandle : TLibTiePieHandle ; hWnd : HWND ); cdecl;
{$endif MSWINDOWS}
procedure DevClose( hDevice : TLibTiePieHandle ); cdecl;
function DevIsRemoved( hDevice : TLibTiePieHandle ) : ByteBool; cdecl;
function DevGetDriverVersion( hDevice : TLibTiePieHandle ) : TTpVersion; cdecl;
function DevGetFirmwareVersion( hDevice : TLibTiePieHandle ) : TTpVersion; cdecl;
function DevGetCalibrationDate( hDevice : TLibTiePieHandle ) : TTpDate; cdecl;
function DevGetCalibrationToken( hDevice : TLibTiePieHandle ; pBuffer : PAnsiChar ; dwBufferLength : LongWord ) : LongWord; cdecl;
function DevGetSerialNumber( hDevice : TLibTiePieHandle ) : LongWord; cdecl;
function DevGetIPv4Address( hDevice : TLibTiePieHandle ) : LongWord; cdecl;
function DevGetIPPort( hDevice : TLibTiePieHandle ) : Word; cdecl;
function DevGetProductId( hDevice : TLibTiePieHandle ) : LongWord; cdecl;
function DevGetVendorId( hDevice : TLibTiePieHandle ) : LongWord; cdecl;
function DevGetType( hDevice : TLibTiePieHandle ) : LongWord; cdecl;
function DevGetName( hDevice : TLibTiePieHandle ; pBuffer : PAnsiChar ; dwBufferLength : LongWord ) : LongWord; cdecl;
function DevGetNameShort( hDevice : TLibTiePieHandle ; pBuffer : PAnsiChar ; dwBufferLength : LongWord ) : LongWord; cdecl;
function DevGetNameShortest( hDevice : TLibTiePieHandle ; pBuffer : PAnsiChar ; dwBufferLength : LongWord ) : LongWord; cdecl;
function DevHasBattery( hDevice : TLibTiePieHandle ) : ByteBool; cdecl;
function DevGetBatteryCharge( hDevice : TLibTiePieHandle ) : ShortInt; cdecl;
function DevGetBatteryTimeToEmpty( hDevice : TLibTiePieHandle ) : LongInt; cdecl;
function DevGetBatteryTimeToFull( hDevice : TLibTiePieHandle ) : LongInt; cdecl;
function DevIsBatteryChargerConnected( hDevice : TLibTiePieHandle ) : ByteBool; cdecl;
function DevIsBatteryCharging( hDevice : TLibTiePieHandle ) : ByteBool; cdecl;
function DevIsBatteryBroken( hDevice : TLibTiePieHandle ) : ByteBool; cdecl;
procedure DevSetCallbackRemoved( hDevice : TLibTiePieHandle ; pCallback : TTpCallback ; pData : Pointer ); cdecl;
{$ifdef LINUX}
procedure DevSetEventRemoved( hDevice : TLibTiePieHandle ; fdEvent : Integer ); cdecl; deprecated;
{$endif LINUX}
{$ifdef MSWINDOWS}
procedure DevSetEventRemoved( hDevice : TLibTiePieHandle ; hEvent : THandle ); cdecl; deprecated;
procedure DevSetMessageRemoved( hDevice : TLibTiePieHandle ; hWnd : HWND ; wParam : WPARAM ; lParam : LPARAM ); cdecl; deprecated;
{$endif MSWINDOWS}
function DevTrGetInputCount( hDevice : TLibTiePieHandle ) : Word; cdecl;
function DevTrGetInputIndexById( hDevice : TLibTiePieHandle ; dwId : LongWord ) : Word; cdecl;
function ScpTrInIsTriggered( hDevice : TLibTiePieHandle ; wInput : Word ) : ByteBool; cdecl;
function DevTrInGetEnabled( hDevice : TLibTiePieHandle ; wInput : Word ) : ByteBool; cdecl;
function DevTrInSetEnabled( hDevice : TLibTiePieHandle ; wInput : Word ; bEnable : ByteBool ) : ByteBool; cdecl;
function DevTrInGetKinds( hDevice : TLibTiePieHandle ; wInput : Word ) : UInt64; cdecl;
function ScpTrInGetKindsEx( hDevice : TLibTiePieHandle ; wInput : Word ; dwMeasureMode : LongWord ) : UInt64; cdecl;
function DevTrInGetKind( hDevice : TLibTiePieHandle ; wInput : Word ) : UInt64; cdecl;
function DevTrInSetKind( hDevice : TLibTiePieHandle ; wInput : Word ; qwKind : UInt64 ) : UInt64; cdecl;
function DevTrInIsAvailable( hDevice : TLibTiePieHandle ; wInput : Word ) : ByteBool; cdecl;
function ScpTrInIsAvailableEx( hDevice : TLibTiePieHandle ; wInput : Word ; dwMeasureMode : LongWord ) : ByteBool; cdecl;
function DevTrInGetId( hDevice : TLibTiePieHandle ; wInput : Word ) : LongWord; cdecl;
function DevTrInGetName( hDevice : TLibTiePieHandle ; wInput : Word ; pBuffer : PAnsiChar ; dwBufferLength : LongWord ) : LongWord; cdecl;
function DevTrGetOutputCount( hDevice : TLibTiePieHandle ) : Word; cdecl;
function DevTrGetOutputIndexById( hDevice : TLibTiePieHandle ; dwId : LongWord ) : Word; cdecl;
function DevTrOutGetEnabled( hDevice : TLibTiePieHandle ; wOutput : Word ) : ByteBool; cdecl;
function DevTrOutSetEnabled( hDevice : TLibTiePieHandle ; wOutput : Word ; bEnable : ByteBool ) : ByteBool; cdecl;
function DevTrOutGetEvents( hDevice : TLibTiePieHandle ; wOutput : Word ) : UInt64; cdecl;
function DevTrOutGetEvent( hDevice : TLibTiePieHandle ; wOutput : Word ) : UInt64; cdecl;
function DevTrOutSetEvent( hDevice : TLibTiePieHandle ; wOutput : Word ; qwEvent : UInt64 ) : UInt64; cdecl;
function DevTrOutGetId( hDevice : TLibTiePieHandle ; wOutput : Word ) : LongWord; cdecl;
function DevTrOutGetName( hDevice : TLibTiePieHandle ; wOutput : Word ; pBuffer : PAnsiChar ; dwBufferLength : LongWord ) : LongWord; cdecl;
function DevTrOutTrigger( hDevice : TLibTiePieHandle ; wOutput : Word ) : ByteBool; cdecl;
function ScpGetChannelCount( hDevice : TLibTiePieHandle ) : Word; cdecl;
function ScpChIsAvailable( hDevice : TLibTiePieHandle ; wCh : Word ) : ByteBool; cdecl;
function ScpChIsAvailableEx( hDevice : TLibTiePieHandle ; wCh : Word ; dwMeasureMode : LongWord ; dSampleFrequency : Double ; byResolution : Byte ; pChannelEnabled : PByteBool ; wChannelCount : Word ) : ByteBool; cdecl;
function ScpChGetConnectorType( hDevice : TLibTiePieHandle ; wCh : Word ) : LongWord; cdecl;
function ScpChIsDifferential( hDevice : TLibTiePieHandle ; wCh : Word ) : ByteBool; cdecl;
function ScpChGetImpedance( hDevice : TLibTiePieHandle ; wCh : Word ) : Double; cdecl;
function ScpChGetBandwidths( hDevice : TLibTiePieHandle ; wCh : Word ; pList : PDouble ; dwLength : LongWord ) : LongWord; cdecl;
function ScpChGetBandwidth( hDevice : TLibTiePieHandle ; wCh : Word ) : Double; cdecl;
function ScpChSetBandwidth( hDevice : TLibTiePieHandle ; wCh : Word ; dBandwidth : Double ) : Double; cdecl;
function ScpChGetCouplings( hDevice : TLibTiePieHandle ; wCh : Word ) : UInt64; cdecl;
function ScpChGetCoupling( hDevice : TLibTiePieHandle ; wCh : Word ) : UInt64; cdecl;
function ScpChSetCoupling( hDevice : TLibTiePieHandle ; wCh : Word ; qwCoupling : UInt64 ) : UInt64; cdecl;
function ScpChGetEnabled( hDevice : TLibTiePieHandle ; wCh : Word ) : ByteBool; cdecl;
function ScpChSetEnabled( hDevice : TLibTiePieHandle ; wCh : Word ; bEnable : ByteBool ) : ByteBool; cdecl;
function ScpChGetProbeGain( hDevice : TLibTiePieHandle ; wCh : Word ) : Double; cdecl;
function ScpChSetProbeGain( hDevice : TLibTiePieHandle ; wCh : Word ; dProbeGain : Double ) : Double; cdecl;
function ScpChGetProbeOffset( hDevice : TLibTiePieHandle ; wCh : Word ) : Double; cdecl;
function ScpChSetProbeOffset( hDevice : TLibTiePieHandle ; wCh : Word ; dProbeOffset : Double ) : Double; cdecl;
function ScpChGetAutoRanging( hDevice : TLibTiePieHandle ; wCh : Word ) : ByteBool; cdecl;
function ScpChSetAutoRanging( hDevice : TLibTiePieHandle ; wCh : Word ; bEnable : ByteBool ) : ByteBool; cdecl;
function ScpChGetRanges( hDevice : TLibTiePieHandle ; wCh : Word ; pList : PDouble ; dwLength : LongWord ) : LongWord; cdecl;
function ScpChGetRangesEx( hDevice : TLibTiePieHandle ; wCh : Word ; qwCoupling : UInt64 ; pList : PDouble ; dwLength : LongWord ) : LongWord; cdecl;
function ScpChGetRange( hDevice : TLibTiePieHandle ; wCh : Word ) : Double; cdecl;
function ScpChSetRange( hDevice : TLibTiePieHandle ; wCh : Word ; dRange : Double ) : Double; cdecl;
function ScpChHasSafeGround( hDevice : TLibTiePieHandle ; wCh : Word ) : ByteBool; cdecl;
function ScpChGetSafeGroundEnabled( hDevice : TLibTiePieHandle ; wCh : Word ) : ByteBool; cdecl;
function ScpChSetSafeGroundEnabled( hDevice : TLibTiePieHandle ; wCh : Word ; bEnable : ByteBool ) : ByteBool; cdecl;
function ScpChGetSafeGroundThresholdMin( hDevice : TLibTiePieHandle ; wCh : Word ) : Double; cdecl;
function ScpChGetSafeGroundThresholdMax( hDevice : TLibTiePieHandle ; wCh : Word ) : Double; cdecl;
function ScpChGetSafeGroundThreshold( hDevice : TLibTiePieHandle ; wCh : Word ) : Double; cdecl;
function ScpChSetSafeGroundThreshold( hDevice : TLibTiePieHandle ; wCh : Word ; dThreshold : Double ) : Double; cdecl;
function ScpChVerifySafeGroundThreshold( hDevice : TLibTiePieHandle ; wCh : Word ; dThreshold : Double ) : Double; cdecl;
function ScpChHasTrigger( hDevice : TLibTiePieHandle ; wCh : Word ) : ByteBool; cdecl;
function ScpChHasTriggerEx( hDevice : TLibTiePieHandle ; wCh : Word ; dwMeasureMode : LongWord ) : ByteBool; cdecl;
function ScpChTrIsAvailable( hDevice : TLibTiePieHandle ; wCh : Word ) : ByteBool; cdecl;
function ScpChTrIsAvailableEx( hDevice : TLibTiePieHandle ; wCh : Word ; dwMeasureMode : LongWord ; dSampleFrequency : Double ; byResolution : Byte ; pChannelEnabled , pChannelTriggerEnabled : PByteBool ; wChannelCount : Word ) : ByteBool; cdecl;
function ScpChTrIsTriggered( hDevice : TLibTiePieHandle ; wCh : Word ) : ByteBool; cdecl;
function ScpChTrGetEnabled( hDevice : TLibTiePieHandle ; wCh : Word ) : ByteBool; cdecl;
function ScpChTrSetEnabled( hDevice : TLibTiePieHandle ; wCh : Word ; bEnable : ByteBool ) : ByteBool; cdecl;
function ScpChTrGetKinds( hDevice : TLibTiePieHandle ; wCh : Word ) : UInt64; cdecl;
function ScpChTrGetKindsEx( hDevice : TLibTiePieHandle ; wCh : Word ; dwMeasureMode : LongWord ) : UInt64; cdecl;
function ScpChTrGetKind( hDevice : TLibTiePieHandle ; wCh : Word ) : UInt64; cdecl;
function ScpChTrSetKind( hDevice : TLibTiePieHandle ; wCh : Word ; qwTriggerKind : UInt64 ) : UInt64; cdecl;
function ScpChTrGetLevelModes( hDevice : TLibTiePieHandle ; wCh : Word ) : LongWord; cdecl;
function ScpChTrGetLevelMode( hDevice : TLibTiePieHandle ; wCh : Word ) : LongWord; cdecl;
function ScpChTrSetLevelMode( hDevice : TLibTiePieHandle ; wCh : Word ; dwLevelMode : LongWord ) : LongWord; cdecl;
function ScpChTrGetLevelCount( hDevice : TLibTiePieHandle ; wCh : Word ) : LongWord; cdecl;
function ScpChTrGetLevel( hDevice : TLibTiePieHandle ; wCh : Word ; dwIndex : LongWord ) : Double; cdecl;
function ScpChTrSetLevel( hDevice : TLibTiePieHandle ; wCh : Word ; dwIndex : LongWord ; dLevel : Double ) : Double; cdecl;
function ScpChTrGetHysteresisCount( hDevice : TLibTiePieHandle ; wCh : Word ) : LongWord; cdecl;
function ScpChTrGetHysteresis( hDevice : TLibTiePieHandle ; wCh : Word ; dwIndex : LongWord ) : Double; cdecl;
function ScpChTrSetHysteresis( hDevice : TLibTiePieHandle ; wCh : Word ; dwIndex : LongWord ; dHysteresis : Double ) : Double; cdecl;
function ScpChTrGetConditions( hDevice : TLibTiePieHandle ; wCh : Word ) : LongWord; cdecl;
function ScpChTrGetConditionsEx( hDevice : TLibTiePieHandle ; wCh : Word ; dwMeasureMode : LongWord ; qwTriggerKind : UInt64 ) : LongWord; cdecl;
function ScpChTrGetCondition( hDevice : TLibTiePieHandle ; wCh : Word ) : LongWord; cdecl;
function ScpChTrSetCondition( hDevice : TLibTiePieHandle ; wCh : Word ; dwCondition : LongWord ) : LongWord; cdecl;
function ScpChTrGetTimeCount( hDevice : TLibTiePieHandle ; wCh : Word ) : LongWord; cdecl;
function ScpChTrGetTime( hDevice : TLibTiePieHandle ; wCh : Word ; dwIndex : LongWord ) : Double; cdecl;
function ScpChTrSetTime( hDevice : TLibTiePieHandle ; wCh : Word ; dwIndex : LongWord ; dTime : Double ) : Double; cdecl;
function ScpChTrVerifyTime( hDevice : TLibTiePieHandle ; wCh : Word ; dwIndex : LongWord ; dTime : Double ) : Double; cdecl;
function ScpChTrVerifyTimeEx2( hDevice : TLibTiePieHandle ; wCh : Word ; dwIndex : LongWord ; dTime : Double ; dwMeasureMode : LongWord ; dSampleFrequency : Double ; qwTriggerKind : UInt64 ; dwCondition : LongWord ) : Double; cdecl;
function ScpGetData( hDevice : TLibTiePieHandle ; pBuffers : PPSingle ; wChannelCount : Word ; qwStartIndex , qwSampleCount : UInt64 ) : UInt64; cdecl;
function ScpGetData1Ch( hDevice : TLibTiePieHandle ; pBufferCh1 : PSingle ; qwStartIndex , qwSampleCount : UInt64 ) : UInt64; cdecl;
function ScpGetData2Ch( hDevice : TLibTiePieHandle ; pBufferCh1 , pBufferCh2 : PSingle ; qwStartIndex , qwSampleCount : UInt64 ) : UInt64; cdecl;
function ScpGetData3Ch( hDevice : TLibTiePieHandle ; pBufferCh1 , pBufferCh2 , pBufferCh3 : PSingle ; qwStartIndex , qwSampleCount : UInt64 ) : UInt64; cdecl;
function ScpGetData4Ch( hDevice : TLibTiePieHandle ; pBufferCh1 , pBufferCh2 , pBufferCh3 , pBufferCh4 : PSingle ; qwStartIndex , qwSampleCount : UInt64 ) : UInt64; cdecl;
function ScpGetData5Ch( hDevice : TLibTiePieHandle ; pBufferCh1 , pBufferCh2 , pBufferCh3 , pBufferCh4 , pBufferCh5 : PSingle ; qwStartIndex , qwSampleCount : UInt64 ) : UInt64; cdecl;
function ScpGetData6Ch( hDevice : TLibTiePieHandle ; pBufferCh1 , pBufferCh2 , pBufferCh3 , pBufferCh4 , pBufferCh5 , pBufferCh6 : PSingle ; qwStartIndex , qwSampleCount : UInt64 ) : UInt64; cdecl;
function ScpGetData7Ch( hDevice : TLibTiePieHandle ; pBufferCh1 , pBufferCh2 , pBufferCh3 , pBufferCh4 , pBufferCh5 , pBufferCh6 , pBufferCh7 : PSingle ; qwStartIndex , qwSampleCount : UInt64 ) : UInt64; cdecl;
function ScpGetData8Ch( hDevice : TLibTiePieHandle ; pBufferCh1 , pBufferCh2 , pBufferCh3 , pBufferCh4 , pBufferCh5 , pBufferCh6 , pBufferCh7 , pBufferCh8 : PSingle ; qwStartIndex , qwSampleCount : UInt64 ) : UInt64; cdecl;
function ScpGetValidPreSampleCount( hDevice : TLibTiePieHandle ) : UInt64; cdecl;
procedure ScpChGetDataValueRange( hDevice : TLibTiePieHandle ; wCh : Word ; pMin , pMax : PDouble ); cdecl;
function ScpChGetDataValueMin( hDevice : TLibTiePieHandle ; wCh : Word ) : Double; cdecl;
function ScpChGetDataValueMax( hDevice : TLibTiePieHandle ; wCh : Word ) : Double; cdecl;
function ScpGetDataRaw( hDevice : TLibTiePieHandle ; pBuffers : PPointer ; wChannelCount : Word ; qwStartIndex , qwSampleCount : UInt64 ) : UInt64; cdecl;
function ScpGetDataRaw1Ch( hDevice : TLibTiePieHandle ; pBufferCh1 : Pointer ; qwStartIndex , qwSampleCount : UInt64 ) : UInt64; cdecl;
function ScpGetDataRaw2Ch( hDevice : TLibTiePieHandle ; pBufferCh1 , pBufferCh2 : Pointer ; qwStartIndex , qwSampleCount : UInt64 ) : UInt64; cdecl;
function ScpGetDataRaw3Ch( hDevice : TLibTiePieHandle ; pBufferCh1 , pBufferCh2 , pBufferCh3 : Pointer ; qwStartIndex , qwSampleCount : UInt64 ) : UInt64; cdecl;
function ScpGetDataRaw4Ch( hDevice : TLibTiePieHandle ; pBufferCh1 , pBufferCh2 , pBufferCh3 , pBufferCh4 : Pointer ; qwStartIndex , qwSampleCount : UInt64 ) : UInt64; cdecl;
function ScpGetDataRaw5Ch( hDevice : TLibTiePieHandle ; pBufferCh1 , pBufferCh2 , pBufferCh3 , pBufferCh4 , pBufferCh5 : Pointer ; qwStartIndex , qwSampleCount : UInt64 ) : UInt64; cdecl;
function ScpGetDataRaw6Ch( hDevice : TLibTiePieHandle ; pBufferCh1 , pBufferCh2 , pBufferCh3 , pBufferCh4 , pBufferCh5 , pBufferCh6 : Pointer ; qwStartIndex , qwSampleCount : UInt64 ) : UInt64; cdecl;
function ScpGetDataRaw7Ch( hDevice : TLibTiePieHandle ; pBufferCh1 , pBufferCh2 , pBufferCh3 , pBufferCh4 , pBufferCh5 , pBufferCh6 , pBufferCh7 : Pointer ; qwStartIndex , qwSampleCount : UInt64 ) : UInt64; cdecl;
function ScpGetDataRaw8Ch( hDevice : TLibTiePieHandle ; pBufferCh1 , pBufferCh2 , pBufferCh3 , pBufferCh4 , pBufferCh5 , pBufferCh6 , pBufferCh7 , pBufferCh8 : Pointer ; qwStartIndex , qwSampleCount : UInt64 ) : UInt64; cdecl;
function ScpChGetDataRawType( hDevice : TLibTiePieHandle ; wCh : Word ) : LongWord; cdecl;
procedure ScpChGetDataRawValueRange( hDevice : TLibTiePieHandle ; wCh : Word ; pMin , pZero , pMax : PInt64 ); cdecl;
function ScpChGetDataRawValueMin( hDevice : TLibTiePieHandle ; wCh : Word ) : Int64; cdecl;
function ScpChGetDataRawValueZero( hDevice : TLibTiePieHandle ; wCh : Word ) : Int64; cdecl;
function ScpChGetDataRawValueMax( hDevice : TLibTiePieHandle ; wCh : Word ) : Int64; cdecl;
function ScpChIsRangeMaxReachable( hDevice : TLibTiePieHandle ; wCh : Word ) : ByteBool; cdecl;
function ScpIsGetDataAsyncCompleted( hDevice : TLibTiePieHandle ) : ByteBool; cdecl;
function ScpStartGetDataAsync( hDevice : TLibTiePieHandle ; pBuffers : PPSingle ; wChannelCount : Word ; qwStartIndex , qwSampleCount : UInt64 ) : ByteBool; cdecl;
function ScpStartGetDataAsyncRaw( hDevice : TLibTiePieHandle ; pBuffers : PPointer ; wChannelCount : Word ; qwStartIndex , qwSampleCount : UInt64 ) : ByteBool; cdecl;
function ScpCancelGetDataAsync( hDevice : TLibTiePieHandle ) : ByteBool; cdecl;
procedure ScpSetCallbackDataReady( hDevice : TLibTiePieHandle ; pCallback : TTpCallback ; pData : Pointer ); cdecl;
procedure ScpSetCallbackDataOverflow( hDevice : TLibTiePieHandle ; pCallback : TTpCallback ; pData : Pointer ); cdecl;
procedure ScpSetCallbackConnectionTestCompleted( hDevice : TLibTiePieHandle ; pCallback : TTpCallback ; pData : Pointer ); cdecl;
procedure ScpSetCallbackTriggered( hDevice : TLibTiePieHandle ; pCallback : TTpCallback ; pData : Pointer ); cdecl;
{$ifdef LINUX}
procedure ScpSetEventDataReady( hDevice : TLibTiePieHandle ; fdEvent : Integer ); cdecl; deprecated;
procedure ScpSetEventDataOverflow( hDevice : TLibTiePieHandle ; fdEvent : Integer ); cdecl; deprecated;
procedure ScpSetEventConnectionTestCompleted( hDevice : TLibTiePieHandle ; fdEvent : Integer ); cdecl; deprecated;
procedure ScpSetEventTriggered( hDevice : TLibTiePieHandle ; fdEvent : Integer ); cdecl; deprecated;
{$endif LINUX}
{$ifdef MSWINDOWS}
procedure ScpSetEventDataReady( hDevice : TLibTiePieHandle ; hEvent : THandle ); cdecl; deprecated;
procedure ScpSetEventDataOverflow( hDevice : TLibTiePieHandle ; hEvent : THandle ); cdecl; deprecated;
procedure ScpSetEventConnectionTestCompleted( hDevice : TLibTiePieHandle ; hEvent : THandle ); cdecl; deprecated;
procedure ScpSetEventTriggered( hDevice : TLibTiePieHandle ; hEvent : THandle ); cdecl; deprecated;
procedure ScpSetMessageDataReady( hDevice : TLibTiePieHandle ; hWnd : HWND ; wParam : WPARAM ; lParam : LPARAM ); cdecl; deprecated;
procedure ScpSetMessageDataOverflow( hDevice : TLibTiePieHandle ; hWnd : HWND ; wParam : WPARAM ; lParam : LPARAM ); cdecl; deprecated;
procedure ScpSetMessageConnectionTestCompleted( hDevice : TLibTiePieHandle ; hWnd : HWND ; wParam : WPARAM ; lParam : LPARAM ); cdecl; deprecated;
procedure ScpSetMessageTriggered( hDevice : TLibTiePieHandle ; hWnd : HWND ; wParam : WPARAM ; lParam : LPARAM ); cdecl; deprecated;
{$endif MSWINDOWS}
function ScpStart( hDevice : TLibTiePieHandle ) : ByteBool; cdecl;
function ScpStop( hDevice : TLibTiePieHandle ) : ByteBool; cdecl;
function ScpForceTrigger( hDevice : TLibTiePieHandle ) : ByteBool; cdecl;
function ScpGetMeasureModes( hDevice : TLibTiePieHandle ) : LongWord; cdecl;
function ScpGetMeasureMode( hDevice : TLibTiePieHandle ) : LongWord; cdecl;
function ScpSetMeasureMode( hDevice : TLibTiePieHandle ; dwMeasureMode : LongWord ) : LongWord; cdecl;
function ScpIsRunning( hDevice : TLibTiePieHandle ) : ByteBool; cdecl;
function ScpIsTriggered( hDevice : TLibTiePieHandle ) : ByteBool; cdecl;
function ScpIsTimeOutTriggered( hDevice : TLibTiePieHandle ) : ByteBool; cdecl;
function ScpIsForceTriggered( hDevice : TLibTiePieHandle ) : ByteBool; cdecl;
function ScpIsDataReady( hDevice : TLibTiePieHandle ) : ByteBool; cdecl;
function ScpIsDataOverflow( hDevice : TLibTiePieHandle ) : ByteBool; cdecl;
function ScpGetAutoResolutionModes( hDevice : TLibTiePieHandle ) : LongWord; cdecl;
function ScpGetAutoResolutionMode( hDevice : TLibTiePieHandle ) : LongWord; cdecl;
function ScpSetAutoResolutionMode( hDevice : TLibTiePieHandle ; dwAutoResolutionMode : LongWord ) : LongWord; cdecl;
function ScpGetResolutions( hDevice : TLibTiePieHandle ; pList : PByte ; dwLength : LongWord ) : LongWord; cdecl;
function ScpGetResolution( hDevice : TLibTiePieHandle ) : Byte; cdecl;
function ScpSetResolution( hDevice : TLibTiePieHandle ; byResolution : Byte ) : Byte; cdecl;
function ScpIsResolutionEnhanced( hDevice : TLibTiePieHandle ) : ByteBool; cdecl;
function ScpIsResolutionEnhancedEx( hDevice : TLibTiePieHandle ; byResolution : Byte ) : ByteBool; cdecl;
function ScpGetClockSources( hDevice : TLibTiePieHandle ) : LongWord; cdecl;
function ScpGetClockSource( hDevice : TLibTiePieHandle ) : LongWord; cdecl;
function ScpSetClockSource( hDevice : TLibTiePieHandle ; dwClockSource : LongWord ) : LongWord; cdecl;
function ScpGetClockSourceFrequencies( hDevice : TLibTiePieHandle ; pList : PDouble ; dwLength : LongWord ) : LongWord; cdecl;
function ScpGetClockSourceFrequenciesEx( hDevice : TLibTiePieHandle ; dwClockSource : LongWord ; pList : PDouble ; dwLength : LongWord ) : LongWord; cdecl;
function ScpGetClockSourceFrequency( hDevice : TLibTiePieHandle ) : Double; cdecl;
function ScpSetClockSourceFrequency( hDevice : TLibTiePieHandle ; dClockSourceFrequency : Double ) : Double; cdecl;
function ScpGetClockOutputs( hDevice : TLibTiePieHandle ) : LongWord; cdecl;
function ScpGetClockOutput( hDevice : TLibTiePieHandle ) : LongWord; cdecl;
function ScpSetClockOutput( hDevice : TLibTiePieHandle ; dwClockOutput : LongWord ) : LongWord; cdecl;
function ScpGetClockOutputFrequencies( hDevice : TLibTiePieHandle ; pList : PDouble ; dwLength : LongWord ) : LongWord; cdecl;
function ScpGetClockOutputFrequenciesEx( hDevice : TLibTiePieHandle ; dwClockOutput : LongWord ; pList : PDouble ; dwLength : LongWord ) : LongWord; cdecl;
function ScpGetClockOutputFrequency( hDevice : TLibTiePieHandle ) : Double; cdecl;
function ScpSetClockOutputFrequency( hDevice : TLibTiePieHandle ; dClockOutputFrequency : Double ) : Double; cdecl;
function ScpGetSampleFrequencyMax( hDevice : TLibTiePieHandle ) : Double; cdecl;
function ScpGetSampleFrequency( hDevice : TLibTiePieHandle ) : Double; cdecl;
function ScpSetSampleFrequency( hDevice : TLibTiePieHandle ; dSampleFrequency : Double ) : Double; cdecl;
function ScpVerifySampleFrequency( hDevice : TLibTiePieHandle ; dSampleFrequency : Double ) : Double; cdecl;
function ScpVerifySampleFrequencyEx( hDevice : TLibTiePieHandle ; dSampleFrequency : Double ; dwMeasureMode : LongWord ; byResolution : Byte ; pChannelEnabled : PByteBool ; wChannelCount : Word ) : Double; cdecl;
procedure ScpVerifySampleFrequenciesEx( hDevice : TLibTiePieHandle ; pSampleFrequencies : PDouble ; dwSampleFrequencyCount , dwMeasureMode , dwAutoResolutionMode : LongWord ; byResolution : Byte ; pChannelEnabled : PByteBool ; wChannelCount : Word ); cdecl;
function ScpGetRecordLengthMax( hDevice : TLibTiePieHandle ) : UInt64; cdecl;
function ScpGetRecordLengthMaxEx( hDevice : TLibTiePieHandle ; dwMeasureMode : LongWord ; byResolution : Byte ) : UInt64; cdecl;
function ScpGetRecordLength( hDevice : TLibTiePieHandle ) : UInt64; cdecl;
function ScpSetRecordLength( hDevice : TLibTiePieHandle ; qwRecordLength : UInt64 ) : UInt64; cdecl;
function ScpVerifyRecordLength( hDevice : TLibTiePieHandle ; qwRecordLength : UInt64 ) : UInt64; cdecl;
function ScpVerifyRecordLengthEx( hDevice : TLibTiePieHandle ; qwRecordLength : UInt64 ; dwMeasureMode : LongWord ; byResolution : Byte ; pChannelEnabled : PByteBool ; wChannelCount : Word ) : UInt64; cdecl;
function ScpGetPreSampleRatio( hDevice : TLibTiePieHandle ) : Double; cdecl;
function ScpSetPreSampleRatio( hDevice : TLibTiePieHandle ; dPreSampleRatio : Double ) : Double; cdecl;
function ScpGetSegmentCountMax( hDevice : TLibTiePieHandle ) : LongWord; cdecl;
function ScpGetSegmentCountMaxEx( hDevice : TLibTiePieHandle ; dwMeasureMode : LongWord ) : LongWord; cdecl;
function ScpGetSegmentCount( hDevice : TLibTiePieHandle ) : LongWord; cdecl;
function ScpSetSegmentCount( hDevice : TLibTiePieHandle ; dwSegmentCount : LongWord ) : LongWord; cdecl;
function ScpVerifySegmentCount( hDevice : TLibTiePieHandle ; dwSegmentCount : LongWord ) : LongWord; cdecl;
function ScpVerifySegmentCountEx2( hDevice : TLibTiePieHandle ; dwSegmentCount , dwMeasureMode : LongWord ; qwRecordLength : UInt64 ; pChannelEnabled : PByteBool ; wChannelCount : Word ) : LongWord; cdecl;
function ScpHasTrigger( hDevice : TLibTiePieHandle ) : ByteBool; cdecl;
function ScpHasTriggerEx( hDevice : TLibTiePieHandle ; dwMeasureMode : LongWord ) : ByteBool; cdecl;
function ScpGetTriggerTimeOut( hDevice : TLibTiePieHandle ) : Double; cdecl;
function ScpSetTriggerTimeOut( hDevice : TLibTiePieHandle ; dTimeOut : Double ) : Double; cdecl;
function ScpVerifyTriggerTimeOut( hDevice : TLibTiePieHandle ; dTimeOut : Double ) : Double; cdecl;
function ScpVerifyTriggerTimeOutEx( hDevice : TLibTiePieHandle ; dTimeOut : Double ; dwMeasureMode : LongWord ; dSampleFrequency : Double ) : Double; cdecl;
function ScpHasTriggerDelay( hDevice : TLibTiePieHandle ) : ByteBool; cdecl;
function ScpHasTriggerDelayEx( hDevice : TLibTiePieHandle ; dwMeasureMode : LongWord ) : ByteBool; cdecl;
function ScpGetTriggerDelayMax( hDevice : TLibTiePieHandle ) : Double; cdecl;
function ScpGetTriggerDelayMaxEx( hDevice : TLibTiePieHandle ; dwMeasureMode : LongWord ; dSampleFrequency : Double ) : Double; cdecl;
function ScpGetTriggerDelay( hDevice : TLibTiePieHandle ) : Double; cdecl;
function ScpSetTriggerDelay( hDevice : TLibTiePieHandle ; dDelay : Double ) : Double; cdecl;
function ScpVerifyTriggerDelay( hDevice : TLibTiePieHandle ; dDelay : Double ) : Double; cdecl;
function ScpVerifyTriggerDelayEx( hDevice : TLibTiePieHandle ; dDelay : Double ; dwMeasureMode : LongWord ; dSampleFrequency : Double ) : Double; cdecl;
function ScpHasTriggerHoldOff( hDevice : TLibTiePieHandle ) : ByteBool; cdecl;
function ScpHasTriggerHoldOffEx( hDevice : TLibTiePieHandle ; dwMeasureMode : LongWord ) : ByteBool; cdecl;
function ScpGetTriggerHoldOffCountMax( hDevice : TLibTiePieHandle ) : UInt64; cdecl;
function ScpGetTriggerHoldOffCountMaxEx( hDevice : TLibTiePieHandle ; dwMeasureMode : LongWord ) : UInt64; cdecl;
function ScpGetTriggerHoldOffCount( hDevice : TLibTiePieHandle ) : UInt64; cdecl;
function ScpSetTriggerHoldOffCount( hDevice : TLibTiePieHandle ; qwTriggerHoldOffCount : UInt64 ) : UInt64; cdecl;
function ScpHasConnectionTest( hDevice : TLibTiePieHandle ) : ByteBool; cdecl;
function ScpChHasConnectionTest( hDevice : TLibTiePieHandle ; wCh : Word ) : ByteBool; cdecl;
function ScpStartConnectionTest( hDevice : TLibTiePieHandle ) : ByteBool; cdecl;
function ScpStartConnectionTestEx( hDevice : TLibTiePieHandle ; pChannelEnabled : PByteBool ; wChannelCount : Word ) : ByteBool; cdecl;
function ScpIsConnectionTestCompleted( hDevice : TLibTiePieHandle ) : ByteBool; cdecl;
function ScpGetConnectionTestData( hDevice : TLibTiePieHandle ; pBuffer : PLibTiePieTriState ; wChannelCount : Word ) : Word; cdecl;
function GenGetConnectorType( hDevice : TLibTiePieHandle ) : LongWord; cdecl;
function GenIsDifferential( hDevice : TLibTiePieHandle ) : ByteBool; cdecl;
function GenGetImpedance( hDevice : TLibTiePieHandle ) : Double; cdecl;
function GenGetResolution( hDevice : TLibTiePieHandle ) : Byte; cdecl;
function GenGetOutputValueMin( hDevice : TLibTiePieHandle ) : Double; cdecl;
function GenGetOutputValueMax( hDevice : TLibTiePieHandle ) : Double; cdecl;
procedure GenGetOutputValueMinMax( hDevice : TLibTiePieHandle ; pMin , pMax : PDouble ); cdecl;
function GenIsControllable( hDevice : TLibTiePieHandle ) : ByteBool; cdecl;
function GenIsRunning( hDevice : TLibTiePieHandle ) : ByteBool; cdecl;
function GenGetStatus( hDevice : TLibTiePieHandle ) : LongWord; cdecl;
function GenGetOutputOn( hDevice : TLibTiePieHandle ) : ByteBool; cdecl;
function GenSetOutputOn( hDevice : TLibTiePieHandle ; bOutputOn : ByteBool ) : ByteBool; cdecl;
function GenHasOutputInvert( hDevice : TLibTiePieHandle ) : ByteBool; cdecl;
function GenGetOutputInvert( hDevice : TLibTiePieHandle ) : ByteBool; cdecl;
function GenSetOutputInvert( hDevice : TLibTiePieHandle ; bInvert : ByteBool ) : ByteBool; cdecl;
function GenStart( hDevice : TLibTiePieHandle ) : ByteBool; cdecl;
function GenStop( hDevice : TLibTiePieHandle ) : ByteBool; cdecl;
function GenGetSignalTypes( hDevice : TLibTiePieHandle ) : LongWord; cdecl;
function GenGetSignalType( hDevice : TLibTiePieHandle ) : LongWord; cdecl;
function GenSetSignalType( hDevice : TLibTiePieHandle ; dwSignalType : LongWord ) : LongWord; cdecl;
function GenHasAmplitude( hDevice : TLibTiePieHandle ) : ByteBool; cdecl;
function GenHasAmplitudeEx( hDevice : TLibTiePieHandle ; dwSignalType : LongWord ) : ByteBool; cdecl;
function GenGetAmplitudeMin( hDevice : TLibTiePieHandle ) : Double; cdecl;
function GenGetAmplitudeMax( hDevice : TLibTiePieHandle ) : Double; cdecl;
procedure GenGetAmplitudeMinMaxEx( hDevice : TLibTiePieHandle ; dwSignalType : LongWord ; pMin , pMax : PDouble ); cdecl;
function GenGetAmplitude( hDevice : TLibTiePieHandle ) : Double; cdecl;
function GenSetAmplitude( hDevice : TLibTiePieHandle ; dAmplitude : Double ) : Double; cdecl;
function GenVerifyAmplitude( hDevice : TLibTiePieHandle ; dAmplitude : Double ) : Double; cdecl;
function GenVerifyAmplitudeEx( hDevice : TLibTiePieHandle ; dAmplitude : Double ; dwSignalType , dwAmplitudeRangeIndex : LongWord ; dOffset : Double ) : Double; cdecl;
function GenGetAmplitudeRanges( hDevice : TLibTiePieHandle ; pList : PDouble ; dwLength : LongWord ) : LongWord; cdecl;
function GenGetAmplitudeRange( hDevice : TLibTiePieHandle ) : Double; cdecl;
function GenSetAmplitudeRange( hDevice : TLibTiePieHandle ; dRange : Double ) : Double; cdecl;
function GenGetAmplitudeAutoRanging( hDevice : TLibTiePieHandle ) : ByteBool; cdecl;
function GenSetAmplitudeAutoRanging( hDevice : TLibTiePieHandle ; bEnable : ByteBool ) : ByteBool; cdecl;
function GenHasOffset( hDevice : TLibTiePieHandle ) : ByteBool; cdecl;
function GenHasOffsetEx( hDevice : TLibTiePieHandle ; dwSignalType : LongWord ) : ByteBool; cdecl;
function GenGetOffsetMin( hDevice : TLibTiePieHandle ) : Double; cdecl;
function GenGetOffsetMax( hDevice : TLibTiePieHandle ) : Double; cdecl;
procedure GenGetOffsetMinMaxEx( hDevice : TLibTiePieHandle ; dwSignalType : LongWord ; pMin , pMax : PDouble ); cdecl;
function GenGetOffset( hDevice : TLibTiePieHandle ) : Double; cdecl;
function GenSetOffset( hDevice : TLibTiePieHandle ; dOffset : Double ) : Double; cdecl;
function GenVerifyOffset( hDevice : TLibTiePieHandle ; dOffset : Double ) : Double; cdecl;
function GenVerifyOffsetEx( hDevice : TLibTiePieHandle ; dOffset : Double ; dwSignalType : LongWord ; dAmplitude : Double ) : Double; cdecl;
function GenGetFrequencyModes( hDevice : TLibTiePieHandle ) : LongWord; cdecl;
function GenGetFrequencyModesEx( hDevice : TLibTiePieHandle ; dwSignalType : LongWord ) : LongWord; cdecl;
function GenGetFrequencyMode( hDevice : TLibTiePieHandle ) : LongWord; cdecl;
function GenSetFrequencyMode( hDevice : TLibTiePieHandle ; dwFrequencyMode : LongWord ) : LongWord; cdecl;
function GenHasFrequency( hDevice : TLibTiePieHandle ) : ByteBool; cdecl;
function GenHasFrequencyEx( hDevice : TLibTiePieHandle ; dwFrequencyMode , dwSignalType : LongWord ) : ByteBool; cdecl;
function GenGetFrequencyMin( hDevice : TLibTiePieHandle ) : Double; cdecl;
function GenGetFrequencyMax( hDevice : TLibTiePieHandle ) : Double; cdecl;
procedure GenGetFrequencyMinMax( hDevice : TLibTiePieHandle ; dwFrequencyMode : LongWord ; pMin , pMax : PDouble ); cdecl;
procedure GenGetFrequencyMinMaxEx( hDevice : TLibTiePieHandle ; dwFrequencyMode , dwSignalType : LongWord ; pMin , pMax : PDouble ); cdecl;
function GenGetFrequency( hDevice : TLibTiePieHandle ) : Double; cdecl;
function GenSetFrequency( hDevice : TLibTiePieHandle ; dFrequency : Double ) : Double; cdecl;
function GenVerifyFrequency( hDevice : TLibTiePieHandle ; dFrequency : Double ) : Double; cdecl;
function GenVerifyFrequencyEx2( hDevice : TLibTiePieHandle ; dFrequency : Double ; dwFrequencyMode , dwSignalType : LongWord ; qwDataLength : UInt64 ; dWidth : Double ) : Double; cdecl;
function GenHasPhase( hDevice : TLibTiePieHandle ) : ByteBool; cdecl;
function GenHasPhaseEx( hDevice : TLibTiePieHandle ; dwSignalType : LongWord ) : ByteBool; cdecl;
function GenGetPhaseMin( hDevice : TLibTiePieHandle ) : Double; cdecl;
function GenGetPhaseMax( hDevice : TLibTiePieHandle ) : Double; cdecl;
procedure GenGetPhaseMinMaxEx( hDevice : TLibTiePieHandle ; dwSignalType : LongWord ; pMin , pMax : PDouble ); cdecl;
function GenGetPhase( hDevice : TLibTiePieHandle ) : Double; cdecl;
function GenSetPhase( hDevice : TLibTiePieHandle ; dPhase : Double ) : Double; cdecl;
function GenVerifyPhase( hDevice : TLibTiePieHandle ; dPhase : Double ) : Double; cdecl;
function GenVerifyPhaseEx( hDevice : TLibTiePieHandle ; dPhase : Double ; dwSignalType : LongWord ) : Double; cdecl;
function GenHasSymmetry( hDevice : TLibTiePieHandle ) : ByteBool; cdecl;
function GenHasSymmetryEx( hDevice : TLibTiePieHandle ; dwSignalType : LongWord ) : ByteBool; cdecl;
function GenGetSymmetryMin( hDevice : TLibTiePieHandle ) : Double; cdecl;
function GenGetSymmetryMax( hDevice : TLibTiePieHandle ) : Double; cdecl;
procedure GenGetSymmetryMinMaxEx( hDevice : TLibTiePieHandle ; dwSignalType : LongWord ; pMin , pMax : PDouble ); cdecl;
function GenGetSymmetry( hDevice : TLibTiePieHandle ) : Double; cdecl;
function GenSetSymmetry( hDevice : TLibTiePieHandle ; dSymmetry : Double ) : Double; cdecl;
function GenVerifySymmetry( hDevice : TLibTiePieHandle ; dSymmetry : Double ) : Double; cdecl;
function GenVerifySymmetryEx( hDevice : TLibTiePieHandle ; dSymmetry : Double ; dwSignalType : LongWord ) : Double; cdecl;
function GenHasWidth( hDevice : TLibTiePieHandle ) : ByteBool; cdecl;
function GenHasWidthEx( hDevice : TLibTiePieHandle ; dwSignalType : LongWord ) : ByteBool; cdecl;
function GenGetWidthMin( hDevice : TLibTiePieHandle ) : Double; cdecl;
function GenGetWidthMax( hDevice : TLibTiePieHandle ) : Double; cdecl;
procedure GenGetWidthMinMaxEx( hDevice : TLibTiePieHandle ; dwSignalType : LongWord ; dSignalFrequency : Double ; pMin , pMax : PDouble ); cdecl;
function GenGetWidth( hDevice : TLibTiePieHandle ) : Double; cdecl;
function GenSetWidth( hDevice : TLibTiePieHandle ; dWidth : Double ) : Double; cdecl;
function GenVerifyWidth( hDevice : TLibTiePieHandle ; dWidth : Double ) : Double; cdecl;
function GenVerifyWidthEx( hDevice : TLibTiePieHandle ; dWidth : Double ; dwSignalType : LongWord ; dSignalFrequency : Double ) : Double; cdecl;
function GenHasEdgeTime( hDevice : TLibTiePieHandle ) : ByteBool; cdecl;
function GenHasEdgeTimeEx( hDevice : TLibTiePieHandle ; dwSignalType : LongWord ) : ByteBool; cdecl;
function GenGetLeadingEdgeTimeMin( hDevice : TLibTiePieHandle ) : Double; cdecl;
function GenGetLeadingEdgeTimeMax( hDevice : TLibTiePieHandle ) : Double; cdecl;
procedure GenGetLeadingEdgeTimeMinMaxEx( hDevice : TLibTiePieHandle ; dwSignalType : LongWord ; dSignalFrequency , dSymmetry , dWidth , dTrailingEdgeTime : Double ; pMin , pMax : PDouble ); cdecl;
function GenGetLeadingEdgeTime( hDevice : TLibTiePieHandle ) : Double; cdecl;
function GenSetLeadingEdgeTime( hDevice : TLibTiePieHandle ; dLeadingEdgeTime : Double ) : Double; cdecl;
function GenVerifyLeadingEdgeTime( hDevice : TLibTiePieHandle ; dLeadingEdgeTime : Double ) : Double; cdecl;
function GenVerifyLeadingEdgeTimeEx( hDevice : TLibTiePieHandle ; dLeadingEdgeTime : Double ; dwSignalType : LongWord ; dSignalFrequency , dSymmetry , dWidth , dTrailingEdgeTime : Double ) : Double; cdecl;
function GenGetTrailingEdgeTimeMin( hDevice : TLibTiePieHandle ) : Double; cdecl;
function GenGetTrailingEdgeTimeMax( hDevice : TLibTiePieHandle ) : Double; cdecl;
procedure GenGetTrailingEdgeTimeMinMaxEx( hDevice : TLibTiePieHandle ; dwSignalType : LongWord ; dSignalFrequency , dSymmetry , dWidth , dLeadingEdgeTime : Double ; pMin , pMax : PDouble ); cdecl;
function GenGetTrailingEdgeTime( hDevice : TLibTiePieHandle ) : Double; cdecl;
function GenSetTrailingEdgeTime( hDevice : TLibTiePieHandle ; dTrailingEdgeTime : Double ) : Double; cdecl;
function GenVerifyTrailingEdgeTime( hDevice : TLibTiePieHandle ; dTrailingEdgeTime : Double ) : Double; cdecl;
function GenVerifyTrailingEdgeTimeEx( hDevice : TLibTiePieHandle ; dTrailingEdgeTime : Double ; dwSignalType : LongWord ; dSignalFrequency , dSymmetry , dWidth , dLeadingEdgeTime : Double ) : Double; cdecl;
function GenHasData( hDevice : TLibTiePieHandle ) : ByteBool; cdecl;
function GenHasDataEx( hDevice : TLibTiePieHandle ; dwSignalType : LongWord ) : ByteBool; cdecl;
function GenGetDataLengthMin( hDevice : TLibTiePieHandle ) : UInt64; cdecl;
function GenGetDataLengthMax( hDevice : TLibTiePieHandle ) : UInt64; cdecl;
procedure GenGetDataLengthMinMaxEx( hDevice : TLibTiePieHandle ; dwSignalType : LongWord ; pMin , pMax : PUInt64 ); cdecl;
function GenGetDataLength( hDevice : TLibTiePieHandle ) : UInt64; cdecl;
function GenVerifyDataLength( hDevice : TLibTiePieHandle ; qwDataLength : UInt64 ) : UInt64; cdecl;
function GenVerifyDataLengthEx( hDevice : TLibTiePieHandle ; qwDataLength : UInt64 ; dwSignalType : LongWord ) : UInt64; cdecl;
procedure GenSetData( hDevice : TLibTiePieHandle ; pBuffer : PSingle ; qwSampleCount : UInt64 ); cdecl;
procedure GenSetDataEx( hDevice : TLibTiePieHandle ; pBuffer : PSingle ; qwSampleCount : UInt64 ; dwSignalType , dwReserved : LongWord ); cdecl;
function GenGetDataRawType( hDevice : TLibTiePieHandle ) : LongWord; cdecl;
procedure GenGetDataRawValueRange( hDevice : TLibTiePieHandle ; pMin , pZero , pMax : PInt64 ); cdecl;
function GenGetDataRawValueMin( hDevice : TLibTiePieHandle ) : Int64; cdecl;
function GenGetDataRawValueZero( hDevice : TLibTiePieHandle ) : Int64; cdecl;
function GenGetDataRawValueMax( hDevice : TLibTiePieHandle ) : Int64; cdecl;
procedure GenSetDataRaw( hDevice : TLibTiePieHandle ; pBuffer : Pointer ; qwSampleCount : UInt64 ); cdecl;
procedure GenSetDataRawEx( hDevice : TLibTiePieHandle ; pBuffer : Pointer ; qwSampleCount : UInt64 ; dwSignalType , dwReserved : LongWord ); cdecl;
function GenGetModes( hDevice : TLibTiePieHandle ) : UInt64; cdecl;
function GenGetModesEx( hDevice : TLibTiePieHandle ; dwSignalType , dwFrequencyMode : LongWord ) : UInt64; cdecl;
function GenGetModesNative( hDevice : TLibTiePieHandle ) : UInt64; cdecl;
function GenGetMode( hDevice : TLibTiePieHandle ) : UInt64; cdecl;
function GenSetMode( hDevice : TLibTiePieHandle ; qwGeneratorMode : UInt64 ) : UInt64; cdecl;
function GenIsBurstActive( hDevice : TLibTiePieHandle ) : ByteBool; cdecl;
function GenGetBurstCountMin( hDevice : TLibTiePieHandle ) : UInt64; cdecl;
function GenGetBurstCountMax( hDevice : TLibTiePieHandle ) : UInt64; cdecl;
procedure GenGetBurstCountMinMaxEx( hDevice : TLibTiePieHandle ; qwGeneratorMode : UInt64 ; pMin , pMax : PUInt64 ); cdecl;
function GenGetBurstCount( hDevice : TLibTiePieHandle ) : UInt64; cdecl;
function GenSetBurstCount( hDevice : TLibTiePieHandle ; qwBurstCount : UInt64 ) : UInt64; cdecl;
function GenGetBurstSampleCountMin( hDevice : TLibTiePieHandle ) : UInt64; cdecl;
function GenGetBurstSampleCountMax( hDevice : TLibTiePieHandle ) : UInt64; cdecl;
procedure GenGetBurstSampleCountMinMaxEx( hDevice : TLibTiePieHandle ; qwGeneratorMode : UInt64 ; pMin , pMax : PUInt64 ); cdecl;
function GenGetBurstSampleCount( hDevice : TLibTiePieHandle ) : UInt64; cdecl;
function GenSetBurstSampleCount( hDevice : TLibTiePieHandle ; qwBurstSampleCount : UInt64 ) : UInt64; cdecl;
function GenGetBurstSegmentCountMin( hDevice : TLibTiePieHandle ) : UInt64; cdecl;
function GenGetBurstSegmentCountMax( hDevice : TLibTiePieHandle ) : UInt64; cdecl;
procedure GenGetBurstSegmentCountMinMaxEx( hDevice : TLibTiePieHandle ; qwGeneratorMode : UInt64 ; dwSignalType , dwFrequencyMode : LongWord ; dFrequency : Double ; qwDataLength : UInt64 ; pMin , pMax : PUInt64 ); cdecl;
function GenGetBurstSegmentCount( hDevice : TLibTiePieHandle ) : UInt64; cdecl;
function GenSetBurstSegmentCount( hDevice : TLibTiePieHandle ; qwBurstSegmentCount : UInt64 ) : UInt64; cdecl;
function GenVerifyBurstSegmentCount( hDevice : TLibTiePieHandle ; qwBurstSegmentCount : UInt64 ) : UInt64; cdecl;
function GenVerifyBurstSegmentCountEx( hDevice : TLibTiePieHandle ; qwBurstSegmentCount , qwGeneratorMode : UInt64 ; dwSignalType , dwFrequencyMode : LongWord ; dFrequency : Double ; qwDataLength : UInt64 ) : UInt64; cdecl;
procedure GenSetCallbackBurstCompleted( hDevice : TLibTiePieHandle ; pCallback : TTpCallback ; pData : Pointer ); cdecl;
{$ifdef LINUX}
procedure GenSetEventBurstCompleted( hDevice : TLibTiePieHandle ; fdEvent : Integer ); cdecl; deprecated;
{$endif LINUX}
{$ifdef MSWINDOWS}
procedure GenSetEventBurstCompleted( hDevice : TLibTiePieHandle ; hEvent : THandle ); cdecl; deprecated;
procedure GenSetMessageBurstCompleted( hDevice : TLibTiePieHandle ; hWnd : HWND ; wParam : WPARAM ; lParam : LPARAM ); cdecl; deprecated;
{$endif MSWINDOWS}
procedure GenSetCallbackControllableChanged( hDevice : TLibTiePieHandle ; pCallback : TTpCallback ; pData : Pointer ); cdecl;
{$ifdef LINUX}
procedure GenSetEventControllableChanged( hDevice : TLibTiePieHandle ; fdEvent : Integer ); cdecl; deprecated;
{$endif LINUX}
{$ifdef MSWINDOWS}
procedure GenSetEventControllableChanged( hDevice : TLibTiePieHandle ; hEvent : THandle ); cdecl; deprecated;
procedure GenSetMessageControllableChanged( hDevice : TLibTiePieHandle ; hWnd : HWND ; wParam : WPARAM ; lParam : LPARAM ); cdecl; deprecated;
{$endif MSWINDOWS}
function I2CIsInternalAddress( hDevice : TLibTiePieHandle ; wAddress : Word ) : ByteBool; cdecl;
function I2CGetInternalAddresses( hDevice : TLibTiePieHandle ; pAddresses : PWord ; dwLength : LongWord ) : LongWord; cdecl;
function I2CRead( hDevice : TLibTiePieHandle ; wAddress : Word ; pBuffer : Pointer ; dwSize : LongWord ; bStop : ByteBool ) : ByteBool; cdecl;
function I2CReadByte( hDevice : TLibTiePieHandle ; wAddress : Word ; pValue : PByte ) : ByteBool; cdecl;
function I2CReadWord( hDevice : TLibTiePieHandle ; wAddress : Word ; pValue : PWord ) : ByteBool; cdecl;
function I2CWrite( hDevice : TLibTiePieHandle ; wAddress : Word ; pBuffer : Pointer ; dwSize : LongWord ; bStop : ByteBool ) : ByteBool; cdecl;
function I2CWriteByte( hDevice : TLibTiePieHandle ; wAddress : Word ; byValue : Byte ) : ByteBool; cdecl;
function I2CWriteByteByte( hDevice : TLibTiePieHandle ; wAddress : Word ; byValue1 , byValue2 : Byte ) : ByteBool; cdecl;
function I2CWriteByteWord( hDevice : TLibTiePieHandle ; wAddress : Word ; byValue1 : Byte ; wValue2 : Word ) : ByteBool; cdecl;
function I2CWriteWord( hDevice : TLibTiePieHandle ; wAddress , wValue : Word ) : ByteBool; cdecl;
function I2CWriteRead( hDevice : TLibTiePieHandle ; wAddress : Word ; pWriteBuffer : Pointer ; dwWriteSize : LongWord ; pReadBuffer : Pointer ; dwReadSize : LongWord ) : ByteBool; cdecl;
function I2CGetSpeedMax( hDevice : TLibTiePieHandle ) : Double; cdecl;
function I2CGetSpeed( hDevice : TLibTiePieHandle ) : Double; cdecl;
function I2CSetSpeed( hDevice : TLibTiePieHandle ; dSpeed : Double ) : Double; cdecl;
function I2CVerifySpeed( hDevice : TLibTiePieHandle ; dSpeed : Double ) : Double; cdecl;
function SrvConnect( hServer : TLibTiePieHandle ; bAsync : ByteBool ) : ByteBool; cdecl;
function SrvDisconnect( hServer : TLibTiePieHandle ; bForce : ByteBool ) : ByteBool; cdecl;
function SrvRemove( hServer : TLibTiePieHandle ; bForce : ByteBool ) : ByteBool; cdecl;
function SrvGetStatus( hServer : TLibTiePieHandle ) : LongWord; cdecl;
function SrvGetLastError( hServer : TLibTiePieHandle ) : LongWord; cdecl;
function SrvGetURL( hServer : TLibTiePieHandle ; pBuffer : PAnsiChar ; dwBufferLength : LongWord ) : LongWord; cdecl;
function SrvGetID( hServer : TLibTiePieHandle ; pBuffer : PAnsiChar ; dwBufferLength : LongWord ) : LongWord; cdecl;
function SrvGetIPv4Address( hServer : TLibTiePieHandle ) : LongWord; cdecl;
function SrvGetIPPort( hServer : TLibTiePieHandle ) : Word; cdecl;
function SrvGetName( hServer : TLibTiePieHandle ; pBuffer : PAnsiChar ; dwBufferLength : LongWord ) : LongWord; cdecl;
function SrvGetDescription( hServer : TLibTiePieHandle ; pBuffer : PAnsiChar ; dwBufferLength : LongWord ) : LongWord; cdecl;
function SrvGetVersion( hServer : TLibTiePieHandle ) : TTpVersion; cdecl;
function SrvGetVersionExtra( hServer : TLibTiePieHandle ; pBuffer : PAnsiChar ; dwBufferLength : LongWord ) : LongWord; cdecl;
function HlpPointerArrayNew( dwLength : LongWord ) : TLibTiePiePointerArray; cdecl;
procedure HlpPointerArraySet( pArray : TLibTiePiePointerArray ; dwIndex : LongWord ; pPointer : Pointer ); cdecl;
procedure HlpPointerArrayDelete( pArray : TLibTiePiePointerArray ); cdecl;

{$endif !LIBTIEPIE_DYNAMIC}

// Extra routines:

function TpDateToDateTime( ATpDate : TTpDate ) : TDateTime;
function LibGetConfigDynArray : TByteDynArray;
function LstDevGetNameWS( dwIdKind , dwId : LongWord ) : WideString;
function LstDevGetNameShortWS( dwIdKind , dwId : LongWord ) : WideString;
function LstDevGetNameShortestWS( dwIdKind , dwId : LongWord ) : WideString;
function LstDevGetContainedSerialNumbersDynArray( dwIdKind , dwId : LongWord ) : TLongWordDynArray;
function LstCbDevGetNameWS( dwIdKind , dwId , dwContainedDeviceSerialNumber : LongWord ) : WideString;
function LstCbDevGetNameShortWS( dwIdKind , dwId , dwContainedDeviceSerialNumber : LongWord ) : WideString;
function LstCbDevGetNameShortestWS( dwIdKind , dwId , dwContainedDeviceSerialNumber : LongWord ) : WideString;
procedure LstSetCallbackMethodDeviceAdded( AMethod : TTpCallbackDeviceListMethod );
procedure LstSetCallbackMethodDeviceRemoved( AMethod : TTpCallbackDeviceListMethod );
procedure LstSetCallbackMethodDeviceCanOpenChanged( AMethod : TTpCallbackDeviceListMethod );
procedure NetSrvSetCallbackMethodAdded( AMethod : TTpCallbackHandleMethod );
procedure ObjSetEventCallbackMethod( hHandle : TLibTiePieHandle ; AMethod : TTpCallbackEventMethod );
function DevGetCalibrationTokenWS( hDevice : TLibTiePieHandle ) : WideString;
function DevGetNameWS( hDevice : TLibTiePieHandle ) : WideString;
function DevGetNameShortWS( hDevice : TLibTiePieHandle ) : WideString;
function DevGetNameShortestWS( hDevice : TLibTiePieHandle ) : WideString;
procedure DevSetCallbackMethodRemoved( hDevice : TLibTiePieHandle ; AMethod : TTpCallbackMethod );
function DevTrInGetNameWS( hDevice : TLibTiePieHandle ; wInput : Word ) : WideString;
function DevTrOutGetNameWS( hDevice : TLibTiePieHandle ; wOutput : Word ) : WideString;
function ScpChGetBandwidthsDynArray( hDevice : TLibTiePieHandle ; wCh : Word ) : TDoubleDynArray;
function ScpChGetRangesDynArray( hDevice : TLibTiePieHandle ; wCh : Word ) : TDoubleDynArray;
function ScpChGetRangesExDynArray( hDevice : TLibTiePieHandle ; wCh : Word ; qwCoupling : UInt64 ) : TDoubleDynArray;
procedure ScpSetCallbackMethodDataReady( hDevice : TLibTiePieHandle ; AMethod : TTpCallbackMethod );
procedure ScpSetCallbackMethodDataOverflow( hDevice : TLibTiePieHandle ; AMethod : TTpCallbackMethod );
procedure ScpSetCallbackMethodConnectionTestCompleted( hDevice : TLibTiePieHandle ; AMethod : TTpCallbackMethod );
procedure ScpSetCallbackMethodTriggered( hDevice : TLibTiePieHandle ; AMethod : TTpCallbackMethod );
function ScpGetResolutionsDynArray( hDevice : TLibTiePieHandle ) : TByteDynArray;
function ScpGetClockSourceFrequenciesDynArray( hDevice : TLibTiePieHandle ) : TDoubleDynArray;
function ScpGetClockSourceFrequenciesExDynArray( hDevice : TLibTiePieHandle ; dwClockSource : LongWord ) : TDoubleDynArray;
function ScpGetClockOutputFrequenciesDynArray( hDevice : TLibTiePieHandle ) : TDoubleDynArray;
function ScpGetClockOutputFrequenciesExDynArray( hDevice : TLibTiePieHandle ; dwClockOutput : LongWord ) : TDoubleDynArray;
function GenGetAmplitudeRangesDynArray( hDevice : TLibTiePieHandle ) : TDoubleDynArray;
procedure GenSetCallbackMethodBurstCompleted( hDevice : TLibTiePieHandle ; AMethod : TTpCallbackMethod );
procedure GenSetCallbackMethodControllableChanged( hDevice : TLibTiePieHandle ; AMethod : TTpCallbackMethod );
function I2CGetInternalAddressesDynArray( hDevice : TLibTiePieHandle ) : TWordDynArray;
function SrvGetURLWS( hServer : TLibTiePieHandle ) : WideString;
function SrvGetIDWS( hServer : TLibTiePieHandle ) : WideString;
function SrvGetNameWS( hServer : TLibTiePieHandle ) : WideString;
function SrvGetDescriptionWS( hServer : TLibTiePieHandle ) : WideString;
function SrvGetVersionExtraWS( hServer : TLibTiePieHandle ) : WideString;

{$ifdef LIBTIEPIE_DYNAMIC}
var
  {$ifdef MSWINDOWS}
  hLibTiePie : THandle = 0;
  {$else}
  hLibTiePie : TLibHandle = 0;
  {$endif !MSWINDOWS}
{$endif LIBTIEPIE_DYNAMIC}

implementation

uses
  {$if defined( LIBTIEPIE_DYNAMIC ) and not defined( MSWINDOWS )}
  dynlibs,
  {$ifend}
  SysUtils;

{$ifdef LIBTIEPIE_DYNAMIC}

function LibTiePieLoad( const sLibTiePieFileName : string = sLibTiePieFileNameDefault ) : Boolean;
begin
  if hLibTiePie = 0 then begin
    hLibTiePie := LoadLibrary( PAnsiChar( sLibTiePieFileName ) );

    if hLibTiePie <> 0 then begin
      LibInit := TLibInit( GetProcAddress( hLibTiePie , 'LibInit' ) );
      LibIsInitialized := TLibIsInitialized( GetProcAddress( hLibTiePie , 'LibIsInitialized' ) );
      LibExit := TLibExit( GetProcAddress( hLibTiePie , 'LibExit' ) );
      LibGetVersion := TLibGetVersion( GetProcAddress( hLibTiePie , 'LibGetVersion' ) );
      LibGetVersionExtra := TLibGetVersionExtra( GetProcAddress( hLibTiePie , 'LibGetVersionExtra' ) );
      LibGetConfig := TLibGetConfig( GetProcAddress( hLibTiePie , 'LibGetConfig' ) );
      LibGetLastStatus := TLibGetLastStatus( GetProcAddress( hLibTiePie , 'LibGetLastStatus' ) );
      LibGetLastStatusStr := TLibGetLastStatusStr( GetProcAddress( hLibTiePie , 'LibGetLastStatusStr' ) );
      LstUpdate := TLstUpdate( GetProcAddress( hLibTiePie , 'LstUpdate' ) );
      LstGetCount := TLstGetCount( GetProcAddress( hLibTiePie , 'LstGetCount' ) );
      LstOpenDevice := TLstOpenDevice( GetProcAddress( hLibTiePie , 'LstOpenDevice' ) );
      LstOpenOscilloscope := TLstOpenOscilloscope( GetProcAddress( hLibTiePie , 'LstOpenOscilloscope' ) );
      LstOpenGenerator := TLstOpenGenerator( GetProcAddress( hLibTiePie , 'LstOpenGenerator' ) );
      LstOpenI2CHost := TLstOpenI2CHost( GetProcAddress( hLibTiePie , 'LstOpenI2CHost' ) );
      LstCreateCombinedDevice := TLstCreateCombinedDevice( GetProcAddress( hLibTiePie , 'LstCreateCombinedDevice' ) );
      LstCreateAndOpenCombinedDevice := TLstCreateAndOpenCombinedDevice( GetProcAddress( hLibTiePie , 'LstCreateAndOpenCombinedDevice' ) );
      LstRemoveDevice := TLstRemoveDevice( GetProcAddress( hLibTiePie , 'LstRemoveDevice' ) );
      LstRemoveDeviceForce := TLstRemoveDeviceForce( GetProcAddress( hLibTiePie , 'LstRemoveDeviceForce' ) );
      LstDevCanOpen := TLstDevCanOpen( GetProcAddress( hLibTiePie , 'LstDevCanOpen' ) );
      LstDevGetProductId := TLstDevGetProductId( GetProcAddress( hLibTiePie , 'LstDevGetProductId' ) );
      LstDevGetVendorId := TLstDevGetVendorId( GetProcAddress( hLibTiePie , 'LstDevGetVendorId' ) );
      LstDevGetName := TLstDevGetName( GetProcAddress( hLibTiePie , 'LstDevGetName' ) );
      LstDevGetNameShort := TLstDevGetNameShort( GetProcAddress( hLibTiePie , 'LstDevGetNameShort' ) );
      LstDevGetNameShortest := TLstDevGetNameShortest( GetProcAddress( hLibTiePie , 'LstDevGetNameShortest' ) );
      LstDevGetDriverVersion := TLstDevGetDriverVersion( GetProcAddress( hLibTiePie , 'LstDevGetDriverVersion' ) );
      LstDevGetRecommendedDriverVersion := TLstDevGetRecommendedDriverVersion( GetProcAddress( hLibTiePie , 'LstDevGetRecommendedDriverVersion' ) );
      LstDevGetFirmwareVersion := TLstDevGetFirmwareVersion( GetProcAddress( hLibTiePie , 'LstDevGetFirmwareVersion' ) );
      LstDevGetRecommendedFirmwareVersion := TLstDevGetRecommendedFirmwareVersion( GetProcAddress( hLibTiePie , 'LstDevGetRecommendedFirmwareVersion' ) );
      LstDevGetCalibrationDate := TLstDevGetCalibrationDate( GetProcAddress( hLibTiePie , 'LstDevGetCalibrationDate' ) );
      LstDevGetSerialNumber := TLstDevGetSerialNumber( GetProcAddress( hLibTiePie , 'LstDevGetSerialNumber' ) );
      LstDevGetIPv4Address := TLstDevGetIPv4Address( GetProcAddress( hLibTiePie , 'LstDevGetIPv4Address' ) );
      LstDevGetIPPort := TLstDevGetIPPort( GetProcAddress( hLibTiePie , 'LstDevGetIPPort' ) );
      LstDevHasServer := TLstDevHasServer( GetProcAddress( hLibTiePie , 'LstDevHasServer' ) );
      LstDevGetServer := TLstDevGetServer( GetProcAddress( hLibTiePie , 'LstDevGetServer' ) );
      LstDevGetTypes := TLstDevGetTypes( GetProcAddress( hLibTiePie , 'LstDevGetTypes' ) );
      LstDevGetContainedSerialNumbers := TLstDevGetContainedSerialNumbers( GetProcAddress( hLibTiePie , 'LstDevGetContainedSerialNumbers' ) );
      LstCbDevGetProductId := TLstCbDevGetProductId( GetProcAddress( hLibTiePie , 'LstCbDevGetProductId' ) );
      LstCbDevGetVendorId := TLstCbDevGetVendorId( GetProcAddress( hLibTiePie , 'LstCbDevGetVendorId' ) );
      LstCbDevGetName := TLstCbDevGetName( GetProcAddress( hLibTiePie , 'LstCbDevGetName' ) );
      LstCbDevGetNameShort := TLstCbDevGetNameShort( GetProcAddress( hLibTiePie , 'LstCbDevGetNameShort' ) );
      LstCbDevGetNameShortest := TLstCbDevGetNameShortest( GetProcAddress( hLibTiePie , 'LstCbDevGetNameShortest' ) );
      LstCbDevGetDriverVersion := TLstCbDevGetDriverVersion( GetProcAddress( hLibTiePie , 'LstCbDevGetDriverVersion' ) );
      LstCbDevGetFirmwareVersion := TLstCbDevGetFirmwareVersion( GetProcAddress( hLibTiePie , 'LstCbDevGetFirmwareVersion' ) );
      LstCbDevGetCalibrationDate := TLstCbDevGetCalibrationDate( GetProcAddress( hLibTiePie , 'LstCbDevGetCalibrationDate' ) );
      LstCbScpGetChannelCount := TLstCbScpGetChannelCount( GetProcAddress( hLibTiePie , 'LstCbScpGetChannelCount' ) );
      LstSetCallbackDeviceAdded := TLstSetCallbackDeviceAdded( GetProcAddress( hLibTiePie , 'LstSetCallbackDeviceAdded' ) );
      LstSetCallbackDeviceRemoved := TLstSetCallbackDeviceRemoved( GetProcAddress( hLibTiePie , 'LstSetCallbackDeviceRemoved' ) );
      LstSetCallbackDeviceCanOpenChanged := TLstSetCallbackDeviceCanOpenChanged( GetProcAddress( hLibTiePie , 'LstSetCallbackDeviceCanOpenChanged' ) );
      {$ifdef LINUX}
      LstSetEventDeviceAdded := TLstSetEventDeviceAdded( GetProcAddress( hLibTiePie , 'LstSetEventDeviceAdded' ) );
      LstSetEventDeviceRemoved := TLstSetEventDeviceRemoved( GetProcAddress( hLibTiePie , 'LstSetEventDeviceRemoved' ) );
      LstSetEventDeviceCanOpenChanged := TLstSetEventDeviceCanOpenChanged( GetProcAddress( hLibTiePie , 'LstSetEventDeviceCanOpenChanged' ) );
      {$endif LINUX}
      {$ifdef MSWINDOWS}
      LstSetEventDeviceAdded := TLstSetEventDeviceAdded( GetProcAddress( hLibTiePie , 'LstSetEventDeviceAdded' ) );
      LstSetEventDeviceRemoved := TLstSetEventDeviceRemoved( GetProcAddress( hLibTiePie , 'LstSetEventDeviceRemoved' ) );
      LstSetEventDeviceCanOpenChanged := TLstSetEventDeviceCanOpenChanged( GetProcAddress( hLibTiePie , 'LstSetEventDeviceCanOpenChanged' ) );
      LstSetMessageDeviceAdded := TLstSetMessageDeviceAdded( GetProcAddress( hLibTiePie , 'LstSetMessageDeviceAdded' ) );
      LstSetMessageDeviceRemoved := TLstSetMessageDeviceRemoved( GetProcAddress( hLibTiePie , 'LstSetMessageDeviceRemoved' ) );
      LstSetMessageDeviceCanOpenChanged := TLstSetMessageDeviceCanOpenChanged( GetProcAddress( hLibTiePie , 'LstSetMessageDeviceCanOpenChanged' ) );
      {$endif MSWINDOWS}
      NetGetAutoDetectEnabled := TNetGetAutoDetectEnabled( GetProcAddress( hLibTiePie , 'NetGetAutoDetectEnabled' ) );
      NetSetAutoDetectEnabled := TNetSetAutoDetectEnabled( GetProcAddress( hLibTiePie , 'NetSetAutoDetectEnabled' ) );
      NetSrvAdd := TNetSrvAdd( GetProcAddress( hLibTiePie , 'NetSrvAdd' ) );
      NetSrvRemove := TNetSrvRemove( GetProcAddress( hLibTiePie , 'NetSrvRemove' ) );
      NetSrvGetCount := TNetSrvGetCount( GetProcAddress( hLibTiePie , 'NetSrvGetCount' ) );
      NetSrvGetByIndex := TNetSrvGetByIndex( GetProcAddress( hLibTiePie , 'NetSrvGetByIndex' ) );
      NetSrvGetByURL := TNetSrvGetByURL( GetProcAddress( hLibTiePie , 'NetSrvGetByURL' ) );
      NetSrvSetCallbackAdded := TNetSrvSetCallbackAdded( GetProcAddress( hLibTiePie , 'NetSrvSetCallbackAdded' ) );
      {$ifdef LINUX}
      NetSrvSetEventAdded := TNetSrvSetEventAdded( GetProcAddress( hLibTiePie , 'NetSrvSetEventAdded' ) );
      {$endif LINUX}
      {$ifdef MSWINDOWS}
      NetSrvSetEventAdded := TNetSrvSetEventAdded( GetProcAddress( hLibTiePie , 'NetSrvSetEventAdded' ) );
      NetSrvSetMessageAdded := TNetSrvSetMessageAdded( GetProcAddress( hLibTiePie , 'NetSrvSetMessageAdded' ) );
      {$endif MSWINDOWS}
      ObjClose := TObjClose( GetProcAddress( hLibTiePie , 'ObjClose' ) );
      ObjIsRemoved := TObjIsRemoved( GetProcAddress( hLibTiePie , 'ObjIsRemoved' ) );
      ObjGetInterfaces := TObjGetInterfaces( GetProcAddress( hLibTiePie , 'ObjGetInterfaces' ) );
      ObjSetEventCallback := TObjSetEventCallback( GetProcAddress( hLibTiePie , 'ObjSetEventCallback' ) );
      ObjGetEvent := TObjGetEvent( GetProcAddress( hLibTiePie , 'ObjGetEvent' ) );
      {$ifdef LINUX}
      ObjSetEventEvent := TObjSetEventEvent( GetProcAddress( hLibTiePie , 'ObjSetEventEvent' ) );
      {$endif LINUX}
      {$ifdef MSWINDOWS}
      ObjSetEventEvent := TObjSetEventEvent( GetProcAddress( hLibTiePie , 'ObjSetEventEvent' ) );
      ObjSetEventWindowHandle := TObjSetEventWindowHandle( GetProcAddress( hLibTiePie , 'ObjSetEventWindowHandle' ) );
      {$endif MSWINDOWS}
      DevClose := TDevClose( GetProcAddress( hLibTiePie , 'DevClose' ) );
      DevIsRemoved := TDevIsRemoved( GetProcAddress( hLibTiePie , 'DevIsRemoved' ) );
      DevGetDriverVersion := TDevGetDriverVersion( GetProcAddress( hLibTiePie , 'DevGetDriverVersion' ) );
      DevGetFirmwareVersion := TDevGetFirmwareVersion( GetProcAddress( hLibTiePie , 'DevGetFirmwareVersion' ) );
      DevGetCalibrationDate := TDevGetCalibrationDate( GetProcAddress( hLibTiePie , 'DevGetCalibrationDate' ) );
      DevGetCalibrationToken := TDevGetCalibrationToken( GetProcAddress( hLibTiePie , 'DevGetCalibrationToken' ) );
      DevGetSerialNumber := TDevGetSerialNumber( GetProcAddress( hLibTiePie , 'DevGetSerialNumber' ) );
      DevGetIPv4Address := TDevGetIPv4Address( GetProcAddress( hLibTiePie , 'DevGetIPv4Address' ) );
      DevGetIPPort := TDevGetIPPort( GetProcAddress( hLibTiePie , 'DevGetIPPort' ) );
      DevGetProductId := TDevGetProductId( GetProcAddress( hLibTiePie , 'DevGetProductId' ) );
      DevGetVendorId := TDevGetVendorId( GetProcAddress( hLibTiePie , 'DevGetVendorId' ) );
      DevGetType := TDevGetType( GetProcAddress( hLibTiePie , 'DevGetType' ) );
      DevGetName := TDevGetName( GetProcAddress( hLibTiePie , 'DevGetName' ) );
      DevGetNameShort := TDevGetNameShort( GetProcAddress( hLibTiePie , 'DevGetNameShort' ) );
      DevGetNameShortest := TDevGetNameShortest( GetProcAddress( hLibTiePie , 'DevGetNameShortest' ) );
      DevHasBattery := TDevHasBattery( GetProcAddress( hLibTiePie , 'DevHasBattery' ) );
      DevGetBatteryCharge := TDevGetBatteryCharge( GetProcAddress( hLibTiePie , 'DevGetBatteryCharge' ) );
      DevGetBatteryTimeToEmpty := TDevGetBatteryTimeToEmpty( GetProcAddress( hLibTiePie , 'DevGetBatteryTimeToEmpty' ) );
      DevGetBatteryTimeToFull := TDevGetBatteryTimeToFull( GetProcAddress( hLibTiePie , 'DevGetBatteryTimeToFull' ) );
      DevIsBatteryChargerConnected := TDevIsBatteryChargerConnected( GetProcAddress( hLibTiePie , 'DevIsBatteryChargerConnected' ) );
      DevIsBatteryCharging := TDevIsBatteryCharging( GetProcAddress( hLibTiePie , 'DevIsBatteryCharging' ) );
      DevIsBatteryBroken := TDevIsBatteryBroken( GetProcAddress( hLibTiePie , 'DevIsBatteryBroken' ) );
      DevSetCallbackRemoved := TDevSetCallbackRemoved( GetProcAddress( hLibTiePie , 'DevSetCallbackRemoved' ) );
      {$ifdef LINUX}
      DevSetEventRemoved := TDevSetEventRemoved( GetProcAddress( hLibTiePie , 'DevSetEventRemoved' ) );
      {$endif LINUX}
      {$ifdef MSWINDOWS}
      DevSetEventRemoved := TDevSetEventRemoved( GetProcAddress( hLibTiePie , 'DevSetEventRemoved' ) );
      DevSetMessageRemoved := TDevSetMessageRemoved( GetProcAddress( hLibTiePie , 'DevSetMessageRemoved' ) );
      {$endif MSWINDOWS}
      DevTrGetInputCount := TDevTrGetInputCount( GetProcAddress( hLibTiePie , 'DevTrGetInputCount' ) );
      DevTrGetInputIndexById := TDevTrGetInputIndexById( GetProcAddress( hLibTiePie , 'DevTrGetInputIndexById' ) );
      ScpTrInIsTriggered := TScpTrInIsTriggered( GetProcAddress( hLibTiePie , 'ScpTrInIsTriggered' ) );
      DevTrInGetEnabled := TDevTrInGetEnabled( GetProcAddress( hLibTiePie , 'DevTrInGetEnabled' ) );
      DevTrInSetEnabled := TDevTrInSetEnabled( GetProcAddress( hLibTiePie , 'DevTrInSetEnabled' ) );
      DevTrInGetKinds := TDevTrInGetKinds( GetProcAddress( hLibTiePie , 'DevTrInGetKinds' ) );
      ScpTrInGetKindsEx := TScpTrInGetKindsEx( GetProcAddress( hLibTiePie , 'ScpTrInGetKindsEx' ) );
      DevTrInGetKind := TDevTrInGetKind( GetProcAddress( hLibTiePie , 'DevTrInGetKind' ) );
      DevTrInSetKind := TDevTrInSetKind( GetProcAddress( hLibTiePie , 'DevTrInSetKind' ) );
      DevTrInIsAvailable := TDevTrInIsAvailable( GetProcAddress( hLibTiePie , 'DevTrInIsAvailable' ) );
      ScpTrInIsAvailableEx := TScpTrInIsAvailableEx( GetProcAddress( hLibTiePie , 'ScpTrInIsAvailableEx' ) );
      DevTrInGetId := TDevTrInGetId( GetProcAddress( hLibTiePie , 'DevTrInGetId' ) );
      DevTrInGetName := TDevTrInGetName( GetProcAddress( hLibTiePie , 'DevTrInGetName' ) );
      DevTrGetOutputCount := TDevTrGetOutputCount( GetProcAddress( hLibTiePie , 'DevTrGetOutputCount' ) );
      DevTrGetOutputIndexById := TDevTrGetOutputIndexById( GetProcAddress( hLibTiePie , 'DevTrGetOutputIndexById' ) );
      DevTrOutGetEnabled := TDevTrOutGetEnabled( GetProcAddress( hLibTiePie , 'DevTrOutGetEnabled' ) );
      DevTrOutSetEnabled := TDevTrOutSetEnabled( GetProcAddress( hLibTiePie , 'DevTrOutSetEnabled' ) );
      DevTrOutGetEvents := TDevTrOutGetEvents( GetProcAddress( hLibTiePie , 'DevTrOutGetEvents' ) );
      DevTrOutGetEvent := TDevTrOutGetEvent( GetProcAddress( hLibTiePie , 'DevTrOutGetEvent' ) );
      DevTrOutSetEvent := TDevTrOutSetEvent( GetProcAddress( hLibTiePie , 'DevTrOutSetEvent' ) );
      DevTrOutGetId := TDevTrOutGetId( GetProcAddress( hLibTiePie , 'DevTrOutGetId' ) );
      DevTrOutGetName := TDevTrOutGetName( GetProcAddress( hLibTiePie , 'DevTrOutGetName' ) );
      DevTrOutTrigger := TDevTrOutTrigger( GetProcAddress( hLibTiePie , 'DevTrOutTrigger' ) );
      ScpGetChannelCount := TScpGetChannelCount( GetProcAddress( hLibTiePie , 'ScpGetChannelCount' ) );
      ScpChIsAvailable := TScpChIsAvailable( GetProcAddress( hLibTiePie , 'ScpChIsAvailable' ) );
      ScpChIsAvailableEx := TScpChIsAvailableEx( GetProcAddress( hLibTiePie , 'ScpChIsAvailableEx' ) );
      ScpChGetConnectorType := TScpChGetConnectorType( GetProcAddress( hLibTiePie , 'ScpChGetConnectorType' ) );
      ScpChIsDifferential := TScpChIsDifferential( GetProcAddress( hLibTiePie , 'ScpChIsDifferential' ) );
      ScpChGetImpedance := TScpChGetImpedance( GetProcAddress( hLibTiePie , 'ScpChGetImpedance' ) );
      ScpChGetBandwidths := TScpChGetBandwidths( GetProcAddress( hLibTiePie , 'ScpChGetBandwidths' ) );
      ScpChGetBandwidth := TScpChGetBandwidth( GetProcAddress( hLibTiePie , 'ScpChGetBandwidth' ) );
      ScpChSetBandwidth := TScpChSetBandwidth( GetProcAddress( hLibTiePie , 'ScpChSetBandwidth' ) );
      ScpChGetCouplings := TScpChGetCouplings( GetProcAddress( hLibTiePie , 'ScpChGetCouplings' ) );
      ScpChGetCoupling := TScpChGetCoupling( GetProcAddress( hLibTiePie , 'ScpChGetCoupling' ) );
      ScpChSetCoupling := TScpChSetCoupling( GetProcAddress( hLibTiePie , 'ScpChSetCoupling' ) );
      ScpChGetEnabled := TScpChGetEnabled( GetProcAddress( hLibTiePie , 'ScpChGetEnabled' ) );
      ScpChSetEnabled := TScpChSetEnabled( GetProcAddress( hLibTiePie , 'ScpChSetEnabled' ) );
      ScpChGetProbeGain := TScpChGetProbeGain( GetProcAddress( hLibTiePie , 'ScpChGetProbeGain' ) );
      ScpChSetProbeGain := TScpChSetProbeGain( GetProcAddress( hLibTiePie , 'ScpChSetProbeGain' ) );
      ScpChGetProbeOffset := TScpChGetProbeOffset( GetProcAddress( hLibTiePie , 'ScpChGetProbeOffset' ) );
      ScpChSetProbeOffset := TScpChSetProbeOffset( GetProcAddress( hLibTiePie , 'ScpChSetProbeOffset' ) );
      ScpChGetAutoRanging := TScpChGetAutoRanging( GetProcAddress( hLibTiePie , 'ScpChGetAutoRanging' ) );
      ScpChSetAutoRanging := TScpChSetAutoRanging( GetProcAddress( hLibTiePie , 'ScpChSetAutoRanging' ) );
      ScpChGetRanges := TScpChGetRanges( GetProcAddress( hLibTiePie , 'ScpChGetRanges' ) );
      ScpChGetRangesEx := TScpChGetRangesEx( GetProcAddress( hLibTiePie , 'ScpChGetRangesEx' ) );
      ScpChGetRange := TScpChGetRange( GetProcAddress( hLibTiePie , 'ScpChGetRange' ) );
      ScpChSetRange := TScpChSetRange( GetProcAddress( hLibTiePie , 'ScpChSetRange' ) );
      ScpChHasSafeGround := TScpChHasSafeGround( GetProcAddress( hLibTiePie , 'ScpChHasSafeGround' ) );
      ScpChGetSafeGroundEnabled := TScpChGetSafeGroundEnabled( GetProcAddress( hLibTiePie , 'ScpChGetSafeGroundEnabled' ) );
      ScpChSetSafeGroundEnabled := TScpChSetSafeGroundEnabled( GetProcAddress( hLibTiePie , 'ScpChSetSafeGroundEnabled' ) );
      ScpChGetSafeGroundThresholdMin := TScpChGetSafeGroundThresholdMin( GetProcAddress( hLibTiePie , 'ScpChGetSafeGroundThresholdMin' ) );
      ScpChGetSafeGroundThresholdMax := TScpChGetSafeGroundThresholdMax( GetProcAddress( hLibTiePie , 'ScpChGetSafeGroundThresholdMax' ) );
      ScpChGetSafeGroundThreshold := TScpChGetSafeGroundThreshold( GetProcAddress( hLibTiePie , 'ScpChGetSafeGroundThreshold' ) );
      ScpChSetSafeGroundThreshold := TScpChSetSafeGroundThreshold( GetProcAddress( hLibTiePie , 'ScpChSetSafeGroundThreshold' ) );
      ScpChVerifySafeGroundThreshold := TScpChVerifySafeGroundThreshold( GetProcAddress( hLibTiePie , 'ScpChVerifySafeGroundThreshold' ) );
      ScpChHasTrigger := TScpChHasTrigger( GetProcAddress( hLibTiePie , 'ScpChHasTrigger' ) );
      ScpChHasTriggerEx := TScpChHasTriggerEx( GetProcAddress( hLibTiePie , 'ScpChHasTriggerEx' ) );
      ScpChTrIsAvailable := TScpChTrIsAvailable( GetProcAddress( hLibTiePie , 'ScpChTrIsAvailable' ) );
      ScpChTrIsAvailableEx := TScpChTrIsAvailableEx( GetProcAddress( hLibTiePie , 'ScpChTrIsAvailableEx' ) );
      ScpChTrIsTriggered := TScpChTrIsTriggered( GetProcAddress( hLibTiePie , 'ScpChTrIsTriggered' ) );
      ScpChTrGetEnabled := TScpChTrGetEnabled( GetProcAddress( hLibTiePie , 'ScpChTrGetEnabled' ) );
      ScpChTrSetEnabled := TScpChTrSetEnabled( GetProcAddress( hLibTiePie , 'ScpChTrSetEnabled' ) );
      ScpChTrGetKinds := TScpChTrGetKinds( GetProcAddress( hLibTiePie , 'ScpChTrGetKinds' ) );
      ScpChTrGetKindsEx := TScpChTrGetKindsEx( GetProcAddress( hLibTiePie , 'ScpChTrGetKindsEx' ) );
      ScpChTrGetKind := TScpChTrGetKind( GetProcAddress( hLibTiePie , 'ScpChTrGetKind' ) );
      ScpChTrSetKind := TScpChTrSetKind( GetProcAddress( hLibTiePie , 'ScpChTrSetKind' ) );
      ScpChTrGetLevelModes := TScpChTrGetLevelModes( GetProcAddress( hLibTiePie , 'ScpChTrGetLevelModes' ) );
      ScpChTrGetLevelMode := TScpChTrGetLevelMode( GetProcAddress( hLibTiePie , 'ScpChTrGetLevelMode' ) );
      ScpChTrSetLevelMode := TScpChTrSetLevelMode( GetProcAddress( hLibTiePie , 'ScpChTrSetLevelMode' ) );
      ScpChTrGetLevelCount := TScpChTrGetLevelCount( GetProcAddress( hLibTiePie , 'ScpChTrGetLevelCount' ) );
      ScpChTrGetLevel := TScpChTrGetLevel( GetProcAddress( hLibTiePie , 'ScpChTrGetLevel' ) );
      ScpChTrSetLevel := TScpChTrSetLevel( GetProcAddress( hLibTiePie , 'ScpChTrSetLevel' ) );
      ScpChTrGetHysteresisCount := TScpChTrGetHysteresisCount( GetProcAddress( hLibTiePie , 'ScpChTrGetHysteresisCount' ) );
      ScpChTrGetHysteresis := TScpChTrGetHysteresis( GetProcAddress( hLibTiePie , 'ScpChTrGetHysteresis' ) );
      ScpChTrSetHysteresis := TScpChTrSetHysteresis( GetProcAddress( hLibTiePie , 'ScpChTrSetHysteresis' ) );
      ScpChTrGetConditions := TScpChTrGetConditions( GetProcAddress( hLibTiePie , 'ScpChTrGetConditions' ) );
      ScpChTrGetConditionsEx := TScpChTrGetConditionsEx( GetProcAddress( hLibTiePie , 'ScpChTrGetConditionsEx' ) );
      ScpChTrGetCondition := TScpChTrGetCondition( GetProcAddress( hLibTiePie , 'ScpChTrGetCondition' ) );
      ScpChTrSetCondition := TScpChTrSetCondition( GetProcAddress( hLibTiePie , 'ScpChTrSetCondition' ) );
      ScpChTrGetTimeCount := TScpChTrGetTimeCount( GetProcAddress( hLibTiePie , 'ScpChTrGetTimeCount' ) );
      ScpChTrGetTime := TScpChTrGetTime( GetProcAddress( hLibTiePie , 'ScpChTrGetTime' ) );
      ScpChTrSetTime := TScpChTrSetTime( GetProcAddress( hLibTiePie , 'ScpChTrSetTime' ) );
      ScpChTrVerifyTime := TScpChTrVerifyTime( GetProcAddress( hLibTiePie , 'ScpChTrVerifyTime' ) );
      ScpChTrVerifyTimeEx2 := TScpChTrVerifyTimeEx2( GetProcAddress( hLibTiePie , 'ScpChTrVerifyTimeEx2' ) );
      ScpGetData := TScpGetData( GetProcAddress( hLibTiePie , 'ScpGetData' ) );
      ScpGetData1Ch := TScpGetData1Ch( GetProcAddress( hLibTiePie , 'ScpGetData1Ch' ) );
      ScpGetData2Ch := TScpGetData2Ch( GetProcAddress( hLibTiePie , 'ScpGetData2Ch' ) );
      ScpGetData3Ch := TScpGetData3Ch( GetProcAddress( hLibTiePie , 'ScpGetData3Ch' ) );
      ScpGetData4Ch := TScpGetData4Ch( GetProcAddress( hLibTiePie , 'ScpGetData4Ch' ) );
      ScpGetData5Ch := TScpGetData5Ch( GetProcAddress( hLibTiePie , 'ScpGetData5Ch' ) );
      ScpGetData6Ch := TScpGetData6Ch( GetProcAddress( hLibTiePie , 'ScpGetData6Ch' ) );
      ScpGetData7Ch := TScpGetData7Ch( GetProcAddress( hLibTiePie , 'ScpGetData7Ch' ) );
      ScpGetData8Ch := TScpGetData8Ch( GetProcAddress( hLibTiePie , 'ScpGetData8Ch' ) );
      ScpGetValidPreSampleCount := TScpGetValidPreSampleCount( GetProcAddress( hLibTiePie , 'ScpGetValidPreSampleCount' ) );
      ScpChGetDataValueRange := TScpChGetDataValueRange( GetProcAddress( hLibTiePie , 'ScpChGetDataValueRange' ) );
      ScpChGetDataValueMin := TScpChGetDataValueMin( GetProcAddress( hLibTiePie , 'ScpChGetDataValueMin' ) );
      ScpChGetDataValueMax := TScpChGetDataValueMax( GetProcAddress( hLibTiePie , 'ScpChGetDataValueMax' ) );
      ScpGetDataRaw := TScpGetDataRaw( GetProcAddress( hLibTiePie , 'ScpGetDataRaw' ) );
      ScpGetDataRaw1Ch := TScpGetDataRaw1Ch( GetProcAddress( hLibTiePie , 'ScpGetDataRaw1Ch' ) );
      ScpGetDataRaw2Ch := TScpGetDataRaw2Ch( GetProcAddress( hLibTiePie , 'ScpGetDataRaw2Ch' ) );
      ScpGetDataRaw3Ch := TScpGetDataRaw3Ch( GetProcAddress( hLibTiePie , 'ScpGetDataRaw3Ch' ) );
      ScpGetDataRaw4Ch := TScpGetDataRaw4Ch( GetProcAddress( hLibTiePie , 'ScpGetDataRaw4Ch' ) );
      ScpGetDataRaw5Ch := TScpGetDataRaw5Ch( GetProcAddress( hLibTiePie , 'ScpGetDataRaw5Ch' ) );
      ScpGetDataRaw6Ch := TScpGetDataRaw6Ch( GetProcAddress( hLibTiePie , 'ScpGetDataRaw6Ch' ) );
      ScpGetDataRaw7Ch := TScpGetDataRaw7Ch( GetProcAddress( hLibTiePie , 'ScpGetDataRaw7Ch' ) );
      ScpGetDataRaw8Ch := TScpGetDataRaw8Ch( GetProcAddress( hLibTiePie , 'ScpGetDataRaw8Ch' ) );
      ScpChGetDataRawType := TScpChGetDataRawType( GetProcAddress( hLibTiePie , 'ScpChGetDataRawType' ) );
      ScpChGetDataRawValueRange := TScpChGetDataRawValueRange( GetProcAddress( hLibTiePie , 'ScpChGetDataRawValueRange' ) );
      ScpChGetDataRawValueMin := TScpChGetDataRawValueMin( GetProcAddress( hLibTiePie , 'ScpChGetDataRawValueMin' ) );
      ScpChGetDataRawValueZero := TScpChGetDataRawValueZero( GetProcAddress( hLibTiePie , 'ScpChGetDataRawValueZero' ) );
      ScpChGetDataRawValueMax := TScpChGetDataRawValueMax( GetProcAddress( hLibTiePie , 'ScpChGetDataRawValueMax' ) );
      ScpChIsRangeMaxReachable := TScpChIsRangeMaxReachable( GetProcAddress( hLibTiePie , 'ScpChIsRangeMaxReachable' ) );
      ScpIsGetDataAsyncCompleted := TScpIsGetDataAsyncCompleted( GetProcAddress( hLibTiePie , 'ScpIsGetDataAsyncCompleted' ) );
      ScpStartGetDataAsync := TScpStartGetDataAsync( GetProcAddress( hLibTiePie , 'ScpStartGetDataAsync' ) );
      ScpStartGetDataAsyncRaw := TScpStartGetDataAsyncRaw( GetProcAddress( hLibTiePie , 'ScpStartGetDataAsyncRaw' ) );
      ScpCancelGetDataAsync := TScpCancelGetDataAsync( GetProcAddress( hLibTiePie , 'ScpCancelGetDataAsync' ) );
      ScpSetCallbackDataReady := TScpSetCallbackDataReady( GetProcAddress( hLibTiePie , 'ScpSetCallbackDataReady' ) );
      ScpSetCallbackDataOverflow := TScpSetCallbackDataOverflow( GetProcAddress( hLibTiePie , 'ScpSetCallbackDataOverflow' ) );
      ScpSetCallbackConnectionTestCompleted := TScpSetCallbackConnectionTestCompleted( GetProcAddress( hLibTiePie , 'ScpSetCallbackConnectionTestCompleted' ) );
      ScpSetCallbackTriggered := TScpSetCallbackTriggered( GetProcAddress( hLibTiePie , 'ScpSetCallbackTriggered' ) );
      {$ifdef LINUX}
      ScpSetEventDataReady := TScpSetEventDataReady( GetProcAddress( hLibTiePie , 'ScpSetEventDataReady' ) );
      ScpSetEventDataOverflow := TScpSetEventDataOverflow( GetProcAddress( hLibTiePie , 'ScpSetEventDataOverflow' ) );
      ScpSetEventConnectionTestCompleted := TScpSetEventConnectionTestCompleted( GetProcAddress( hLibTiePie , 'ScpSetEventConnectionTestCompleted' ) );
      ScpSetEventTriggered := TScpSetEventTriggered( GetProcAddress( hLibTiePie , 'ScpSetEventTriggered' ) );
      {$endif LINUX}
      {$ifdef MSWINDOWS}
      ScpSetEventDataReady := TScpSetEventDataReady( GetProcAddress( hLibTiePie , 'ScpSetEventDataReady' ) );
      ScpSetEventDataOverflow := TScpSetEventDataOverflow( GetProcAddress( hLibTiePie , 'ScpSetEventDataOverflow' ) );
      ScpSetEventConnectionTestCompleted := TScpSetEventConnectionTestCompleted( GetProcAddress( hLibTiePie , 'ScpSetEventConnectionTestCompleted' ) );
      ScpSetEventTriggered := TScpSetEventTriggered( GetProcAddress( hLibTiePie , 'ScpSetEventTriggered' ) );
      ScpSetMessageDataReady := TScpSetMessageDataReady( GetProcAddress( hLibTiePie , 'ScpSetMessageDataReady' ) );
      ScpSetMessageDataOverflow := TScpSetMessageDataOverflow( GetProcAddress( hLibTiePie , 'ScpSetMessageDataOverflow' ) );
      ScpSetMessageConnectionTestCompleted := TScpSetMessageConnectionTestCompleted( GetProcAddress( hLibTiePie , 'ScpSetMessageConnectionTestCompleted' ) );
      ScpSetMessageTriggered := TScpSetMessageTriggered( GetProcAddress( hLibTiePie , 'ScpSetMessageTriggered' ) );
      {$endif MSWINDOWS}
      ScpStart := TScpStart( GetProcAddress( hLibTiePie , 'ScpStart' ) );
      ScpStop := TScpStop( GetProcAddress( hLibTiePie , 'ScpStop' ) );
      ScpForceTrigger := TScpForceTrigger( GetProcAddress( hLibTiePie , 'ScpForceTrigger' ) );
      ScpGetMeasureModes := TScpGetMeasureModes( GetProcAddress( hLibTiePie , 'ScpGetMeasureModes' ) );
      ScpGetMeasureMode := TScpGetMeasureMode( GetProcAddress( hLibTiePie , 'ScpGetMeasureMode' ) );
      ScpSetMeasureMode := TScpSetMeasureMode( GetProcAddress( hLibTiePie , 'ScpSetMeasureMode' ) );
      ScpIsRunning := TScpIsRunning( GetProcAddress( hLibTiePie , 'ScpIsRunning' ) );
      ScpIsTriggered := TScpIsTriggered( GetProcAddress( hLibTiePie , 'ScpIsTriggered' ) );
      ScpIsTimeOutTriggered := TScpIsTimeOutTriggered( GetProcAddress( hLibTiePie , 'ScpIsTimeOutTriggered' ) );
      ScpIsForceTriggered := TScpIsForceTriggered( GetProcAddress( hLibTiePie , 'ScpIsForceTriggered' ) );
      ScpIsDataReady := TScpIsDataReady( GetProcAddress( hLibTiePie , 'ScpIsDataReady' ) );
      ScpIsDataOverflow := TScpIsDataOverflow( GetProcAddress( hLibTiePie , 'ScpIsDataOverflow' ) );
      ScpGetAutoResolutionModes := TScpGetAutoResolutionModes( GetProcAddress( hLibTiePie , 'ScpGetAutoResolutionModes' ) );
      ScpGetAutoResolutionMode := TScpGetAutoResolutionMode( GetProcAddress( hLibTiePie , 'ScpGetAutoResolutionMode' ) );
      ScpSetAutoResolutionMode := TScpSetAutoResolutionMode( GetProcAddress( hLibTiePie , 'ScpSetAutoResolutionMode' ) );
      ScpGetResolutions := TScpGetResolutions( GetProcAddress( hLibTiePie , 'ScpGetResolutions' ) );
      ScpGetResolution := TScpGetResolution( GetProcAddress( hLibTiePie , 'ScpGetResolution' ) );
      ScpSetResolution := TScpSetResolution( GetProcAddress( hLibTiePie , 'ScpSetResolution' ) );
      ScpIsResolutionEnhanced := TScpIsResolutionEnhanced( GetProcAddress( hLibTiePie , 'ScpIsResolutionEnhanced' ) );
      ScpIsResolutionEnhancedEx := TScpIsResolutionEnhancedEx( GetProcAddress( hLibTiePie , 'ScpIsResolutionEnhancedEx' ) );
      ScpGetClockSources := TScpGetClockSources( GetProcAddress( hLibTiePie , 'ScpGetClockSources' ) );
      ScpGetClockSource := TScpGetClockSource( GetProcAddress( hLibTiePie , 'ScpGetClockSource' ) );
      ScpSetClockSource := TScpSetClockSource( GetProcAddress( hLibTiePie , 'ScpSetClockSource' ) );
      ScpGetClockSourceFrequencies := TScpGetClockSourceFrequencies( GetProcAddress( hLibTiePie , 'ScpGetClockSourceFrequencies' ) );
      ScpGetClockSourceFrequenciesEx := TScpGetClockSourceFrequenciesEx( GetProcAddress( hLibTiePie , 'ScpGetClockSourceFrequenciesEx' ) );
      ScpGetClockSourceFrequency := TScpGetClockSourceFrequency( GetProcAddress( hLibTiePie , 'ScpGetClockSourceFrequency' ) );
      ScpSetClockSourceFrequency := TScpSetClockSourceFrequency( GetProcAddress( hLibTiePie , 'ScpSetClockSourceFrequency' ) );
      ScpGetClockOutputs := TScpGetClockOutputs( GetProcAddress( hLibTiePie , 'ScpGetClockOutputs' ) );
      ScpGetClockOutput := TScpGetClockOutput( GetProcAddress( hLibTiePie , 'ScpGetClockOutput' ) );
      ScpSetClockOutput := TScpSetClockOutput( GetProcAddress( hLibTiePie , 'ScpSetClockOutput' ) );
      ScpGetClockOutputFrequencies := TScpGetClockOutputFrequencies( GetProcAddress( hLibTiePie , 'ScpGetClockOutputFrequencies' ) );
      ScpGetClockOutputFrequenciesEx := TScpGetClockOutputFrequenciesEx( GetProcAddress( hLibTiePie , 'ScpGetClockOutputFrequenciesEx' ) );
      ScpGetClockOutputFrequency := TScpGetClockOutputFrequency( GetProcAddress( hLibTiePie , 'ScpGetClockOutputFrequency' ) );
      ScpSetClockOutputFrequency := TScpSetClockOutputFrequency( GetProcAddress( hLibTiePie , 'ScpSetClockOutputFrequency' ) );
      ScpGetSampleFrequencyMax := TScpGetSampleFrequencyMax( GetProcAddress( hLibTiePie , 'ScpGetSampleFrequencyMax' ) );
      ScpGetSampleFrequency := TScpGetSampleFrequency( GetProcAddress( hLibTiePie , 'ScpGetSampleFrequency' ) );
      ScpSetSampleFrequency := TScpSetSampleFrequency( GetProcAddress( hLibTiePie , 'ScpSetSampleFrequency' ) );
      ScpVerifySampleFrequency := TScpVerifySampleFrequency( GetProcAddress( hLibTiePie , 'ScpVerifySampleFrequency' ) );
      ScpVerifySampleFrequencyEx := TScpVerifySampleFrequencyEx( GetProcAddress( hLibTiePie , 'ScpVerifySampleFrequencyEx' ) );
      ScpVerifySampleFrequenciesEx := TScpVerifySampleFrequenciesEx( GetProcAddress( hLibTiePie , 'ScpVerifySampleFrequenciesEx' ) );
      ScpGetRecordLengthMax := TScpGetRecordLengthMax( GetProcAddress( hLibTiePie , 'ScpGetRecordLengthMax' ) );
      ScpGetRecordLengthMaxEx := TScpGetRecordLengthMaxEx( GetProcAddress( hLibTiePie , 'ScpGetRecordLengthMaxEx' ) );
      ScpGetRecordLength := TScpGetRecordLength( GetProcAddress( hLibTiePie , 'ScpGetRecordLength' ) );
      ScpSetRecordLength := TScpSetRecordLength( GetProcAddress( hLibTiePie , 'ScpSetRecordLength' ) );
      ScpVerifyRecordLength := TScpVerifyRecordLength( GetProcAddress( hLibTiePie , 'ScpVerifyRecordLength' ) );
      ScpVerifyRecordLengthEx := TScpVerifyRecordLengthEx( GetProcAddress( hLibTiePie , 'ScpVerifyRecordLengthEx' ) );
      ScpGetPreSampleRatio := TScpGetPreSampleRatio( GetProcAddress( hLibTiePie , 'ScpGetPreSampleRatio' ) );
      ScpSetPreSampleRatio := TScpSetPreSampleRatio( GetProcAddress( hLibTiePie , 'ScpSetPreSampleRatio' ) );
      ScpGetSegmentCountMax := TScpGetSegmentCountMax( GetProcAddress( hLibTiePie , 'ScpGetSegmentCountMax' ) );
      ScpGetSegmentCountMaxEx := TScpGetSegmentCountMaxEx( GetProcAddress( hLibTiePie , 'ScpGetSegmentCountMaxEx' ) );
      ScpGetSegmentCount := TScpGetSegmentCount( GetProcAddress( hLibTiePie , 'ScpGetSegmentCount' ) );
      ScpSetSegmentCount := TScpSetSegmentCount( GetProcAddress( hLibTiePie , 'ScpSetSegmentCount' ) );
      ScpVerifySegmentCount := TScpVerifySegmentCount( GetProcAddress( hLibTiePie , 'ScpVerifySegmentCount' ) );
      ScpVerifySegmentCountEx2 := TScpVerifySegmentCountEx2( GetProcAddress( hLibTiePie , 'ScpVerifySegmentCountEx2' ) );
      ScpHasTrigger := TScpHasTrigger( GetProcAddress( hLibTiePie , 'ScpHasTrigger' ) );
      ScpHasTriggerEx := TScpHasTriggerEx( GetProcAddress( hLibTiePie , 'ScpHasTriggerEx' ) );
      ScpGetTriggerTimeOut := TScpGetTriggerTimeOut( GetProcAddress( hLibTiePie , 'ScpGetTriggerTimeOut' ) );
      ScpSetTriggerTimeOut := TScpSetTriggerTimeOut( GetProcAddress( hLibTiePie , 'ScpSetTriggerTimeOut' ) );
      ScpVerifyTriggerTimeOut := TScpVerifyTriggerTimeOut( GetProcAddress( hLibTiePie , 'ScpVerifyTriggerTimeOut' ) );
      ScpVerifyTriggerTimeOutEx := TScpVerifyTriggerTimeOutEx( GetProcAddress( hLibTiePie , 'ScpVerifyTriggerTimeOutEx' ) );
      ScpHasTriggerDelay := TScpHasTriggerDelay( GetProcAddress( hLibTiePie , 'ScpHasTriggerDelay' ) );
      ScpHasTriggerDelayEx := TScpHasTriggerDelayEx( GetProcAddress( hLibTiePie , 'ScpHasTriggerDelayEx' ) );
      ScpGetTriggerDelayMax := TScpGetTriggerDelayMax( GetProcAddress( hLibTiePie , 'ScpGetTriggerDelayMax' ) );
      ScpGetTriggerDelayMaxEx := TScpGetTriggerDelayMaxEx( GetProcAddress( hLibTiePie , 'ScpGetTriggerDelayMaxEx' ) );
      ScpGetTriggerDelay := TScpGetTriggerDelay( GetProcAddress( hLibTiePie , 'ScpGetTriggerDelay' ) );
      ScpSetTriggerDelay := TScpSetTriggerDelay( GetProcAddress( hLibTiePie , 'ScpSetTriggerDelay' ) );
      ScpVerifyTriggerDelay := TScpVerifyTriggerDelay( GetProcAddress( hLibTiePie , 'ScpVerifyTriggerDelay' ) );
      ScpVerifyTriggerDelayEx := TScpVerifyTriggerDelayEx( GetProcAddress( hLibTiePie , 'ScpVerifyTriggerDelayEx' ) );
      ScpHasTriggerHoldOff := TScpHasTriggerHoldOff( GetProcAddress( hLibTiePie , 'ScpHasTriggerHoldOff' ) );
      ScpHasTriggerHoldOffEx := TScpHasTriggerHoldOffEx( GetProcAddress( hLibTiePie , 'ScpHasTriggerHoldOffEx' ) );
      ScpGetTriggerHoldOffCountMax := TScpGetTriggerHoldOffCountMax( GetProcAddress( hLibTiePie , 'ScpGetTriggerHoldOffCountMax' ) );
      ScpGetTriggerHoldOffCountMaxEx := TScpGetTriggerHoldOffCountMaxEx( GetProcAddress( hLibTiePie , 'ScpGetTriggerHoldOffCountMaxEx' ) );
      ScpGetTriggerHoldOffCount := TScpGetTriggerHoldOffCount( GetProcAddress( hLibTiePie , 'ScpGetTriggerHoldOffCount' ) );
      ScpSetTriggerHoldOffCount := TScpSetTriggerHoldOffCount( GetProcAddress( hLibTiePie , 'ScpSetTriggerHoldOffCount' ) );
      ScpHasConnectionTest := TScpHasConnectionTest( GetProcAddress( hLibTiePie , 'ScpHasConnectionTest' ) );
      ScpChHasConnectionTest := TScpChHasConnectionTest( GetProcAddress( hLibTiePie , 'ScpChHasConnectionTest' ) );
      ScpStartConnectionTest := TScpStartConnectionTest( GetProcAddress( hLibTiePie , 'ScpStartConnectionTest' ) );
      ScpStartConnectionTestEx := TScpStartConnectionTestEx( GetProcAddress( hLibTiePie , 'ScpStartConnectionTestEx' ) );
      ScpIsConnectionTestCompleted := TScpIsConnectionTestCompleted( GetProcAddress( hLibTiePie , 'ScpIsConnectionTestCompleted' ) );
      ScpGetConnectionTestData := TScpGetConnectionTestData( GetProcAddress( hLibTiePie , 'ScpGetConnectionTestData' ) );
      GenGetConnectorType := TGenGetConnectorType( GetProcAddress( hLibTiePie , 'GenGetConnectorType' ) );
      GenIsDifferential := TGenIsDifferential( GetProcAddress( hLibTiePie , 'GenIsDifferential' ) );
      GenGetImpedance := TGenGetImpedance( GetProcAddress( hLibTiePie , 'GenGetImpedance' ) );
      GenGetResolution := TGenGetResolution( GetProcAddress( hLibTiePie , 'GenGetResolution' ) );
      GenGetOutputValueMin := TGenGetOutputValueMin( GetProcAddress( hLibTiePie , 'GenGetOutputValueMin' ) );
      GenGetOutputValueMax := TGenGetOutputValueMax( GetProcAddress( hLibTiePie , 'GenGetOutputValueMax' ) );
      GenGetOutputValueMinMax := TGenGetOutputValueMinMax( GetProcAddress( hLibTiePie , 'GenGetOutputValueMinMax' ) );
      GenIsControllable := TGenIsControllable( GetProcAddress( hLibTiePie , 'GenIsControllable' ) );
      GenIsRunning := TGenIsRunning( GetProcAddress( hLibTiePie , 'GenIsRunning' ) );
      GenGetStatus := TGenGetStatus( GetProcAddress( hLibTiePie , 'GenGetStatus' ) );
      GenGetOutputOn := TGenGetOutputOn( GetProcAddress( hLibTiePie , 'GenGetOutputOn' ) );
      GenSetOutputOn := TGenSetOutputOn( GetProcAddress( hLibTiePie , 'GenSetOutputOn' ) );
      GenHasOutputInvert := TGenHasOutputInvert( GetProcAddress( hLibTiePie , 'GenHasOutputInvert' ) );
      GenGetOutputInvert := TGenGetOutputInvert( GetProcAddress( hLibTiePie , 'GenGetOutputInvert' ) );
      GenSetOutputInvert := TGenSetOutputInvert( GetProcAddress( hLibTiePie , 'GenSetOutputInvert' ) );
      GenStart := TGenStart( GetProcAddress( hLibTiePie , 'GenStart' ) );
      GenStop := TGenStop( GetProcAddress( hLibTiePie , 'GenStop' ) );
      GenGetSignalTypes := TGenGetSignalTypes( GetProcAddress( hLibTiePie , 'GenGetSignalTypes' ) );
      GenGetSignalType := TGenGetSignalType( GetProcAddress( hLibTiePie , 'GenGetSignalType' ) );
      GenSetSignalType := TGenSetSignalType( GetProcAddress( hLibTiePie , 'GenSetSignalType' ) );
      GenHasAmplitude := TGenHasAmplitude( GetProcAddress( hLibTiePie , 'GenHasAmplitude' ) );
      GenHasAmplitudeEx := TGenHasAmplitudeEx( GetProcAddress( hLibTiePie , 'GenHasAmplitudeEx' ) );
      GenGetAmplitudeMin := TGenGetAmplitudeMin( GetProcAddress( hLibTiePie , 'GenGetAmplitudeMin' ) );
      GenGetAmplitudeMax := TGenGetAmplitudeMax( GetProcAddress( hLibTiePie , 'GenGetAmplitudeMax' ) );
      GenGetAmplitudeMinMaxEx := TGenGetAmplitudeMinMaxEx( GetProcAddress( hLibTiePie , 'GenGetAmplitudeMinMaxEx' ) );
      GenGetAmplitude := TGenGetAmplitude( GetProcAddress( hLibTiePie , 'GenGetAmplitude' ) );
      GenSetAmplitude := TGenSetAmplitude( GetProcAddress( hLibTiePie , 'GenSetAmplitude' ) );
      GenVerifyAmplitude := TGenVerifyAmplitude( GetProcAddress( hLibTiePie , 'GenVerifyAmplitude' ) );
      GenVerifyAmplitudeEx := TGenVerifyAmplitudeEx( GetProcAddress( hLibTiePie , 'GenVerifyAmplitudeEx' ) );
      GenGetAmplitudeRanges := TGenGetAmplitudeRanges( GetProcAddress( hLibTiePie , 'GenGetAmplitudeRanges' ) );
      GenGetAmplitudeRange := TGenGetAmplitudeRange( GetProcAddress( hLibTiePie , 'GenGetAmplitudeRange' ) );
      GenSetAmplitudeRange := TGenSetAmplitudeRange( GetProcAddress( hLibTiePie , 'GenSetAmplitudeRange' ) );
      GenGetAmplitudeAutoRanging := TGenGetAmplitudeAutoRanging( GetProcAddress( hLibTiePie , 'GenGetAmplitudeAutoRanging' ) );
      GenSetAmplitudeAutoRanging := TGenSetAmplitudeAutoRanging( GetProcAddress( hLibTiePie , 'GenSetAmplitudeAutoRanging' ) );
      GenHasOffset := TGenHasOffset( GetProcAddress( hLibTiePie , 'GenHasOffset' ) );
      GenHasOffsetEx := TGenHasOffsetEx( GetProcAddress( hLibTiePie , 'GenHasOffsetEx' ) );
      GenGetOffsetMin := TGenGetOffsetMin( GetProcAddress( hLibTiePie , 'GenGetOffsetMin' ) );
      GenGetOffsetMax := TGenGetOffsetMax( GetProcAddress( hLibTiePie , 'GenGetOffsetMax' ) );
      GenGetOffsetMinMaxEx := TGenGetOffsetMinMaxEx( GetProcAddress( hLibTiePie , 'GenGetOffsetMinMaxEx' ) );
      GenGetOffset := TGenGetOffset( GetProcAddress( hLibTiePie , 'GenGetOffset' ) );
      GenSetOffset := TGenSetOffset( GetProcAddress( hLibTiePie , 'GenSetOffset' ) );
      GenVerifyOffset := TGenVerifyOffset( GetProcAddress( hLibTiePie , 'GenVerifyOffset' ) );
      GenVerifyOffsetEx := TGenVerifyOffsetEx( GetProcAddress( hLibTiePie , 'GenVerifyOffsetEx' ) );
      GenGetFrequencyModes := TGenGetFrequencyModes( GetProcAddress( hLibTiePie , 'GenGetFrequencyModes' ) );
      GenGetFrequencyModesEx := TGenGetFrequencyModesEx( GetProcAddress( hLibTiePie , 'GenGetFrequencyModesEx' ) );
      GenGetFrequencyMode := TGenGetFrequencyMode( GetProcAddress( hLibTiePie , 'GenGetFrequencyMode' ) );
      GenSetFrequencyMode := TGenSetFrequencyMode( GetProcAddress( hLibTiePie , 'GenSetFrequencyMode' ) );
      GenHasFrequency := TGenHasFrequency( GetProcAddress( hLibTiePie , 'GenHasFrequency' ) );
      GenHasFrequencyEx := TGenHasFrequencyEx( GetProcAddress( hLibTiePie , 'GenHasFrequencyEx' ) );
      GenGetFrequencyMin := TGenGetFrequencyMin( GetProcAddress( hLibTiePie , 'GenGetFrequencyMin' ) );
      GenGetFrequencyMax := TGenGetFrequencyMax( GetProcAddress( hLibTiePie , 'GenGetFrequencyMax' ) );
      GenGetFrequencyMinMax := TGenGetFrequencyMinMax( GetProcAddress( hLibTiePie , 'GenGetFrequencyMinMax' ) );
      GenGetFrequencyMinMaxEx := TGenGetFrequencyMinMaxEx( GetProcAddress( hLibTiePie , 'GenGetFrequencyMinMaxEx' ) );
      GenGetFrequency := TGenGetFrequency( GetProcAddress( hLibTiePie , 'GenGetFrequency' ) );
      GenSetFrequency := TGenSetFrequency( GetProcAddress( hLibTiePie , 'GenSetFrequency' ) );
      GenVerifyFrequency := TGenVerifyFrequency( GetProcAddress( hLibTiePie , 'GenVerifyFrequency' ) );
      GenVerifyFrequencyEx2 := TGenVerifyFrequencyEx2( GetProcAddress( hLibTiePie , 'GenVerifyFrequencyEx2' ) );
      GenHasPhase := TGenHasPhase( GetProcAddress( hLibTiePie , 'GenHasPhase' ) );
      GenHasPhaseEx := TGenHasPhaseEx( GetProcAddress( hLibTiePie , 'GenHasPhaseEx' ) );
      GenGetPhaseMin := TGenGetPhaseMin( GetProcAddress( hLibTiePie , 'GenGetPhaseMin' ) );
      GenGetPhaseMax := TGenGetPhaseMax( GetProcAddress( hLibTiePie , 'GenGetPhaseMax' ) );
      GenGetPhaseMinMaxEx := TGenGetPhaseMinMaxEx( GetProcAddress( hLibTiePie , 'GenGetPhaseMinMaxEx' ) );
      GenGetPhase := TGenGetPhase( GetProcAddress( hLibTiePie , 'GenGetPhase' ) );
      GenSetPhase := TGenSetPhase( GetProcAddress( hLibTiePie , 'GenSetPhase' ) );
      GenVerifyPhase := TGenVerifyPhase( GetProcAddress( hLibTiePie , 'GenVerifyPhase' ) );
      GenVerifyPhaseEx := TGenVerifyPhaseEx( GetProcAddress( hLibTiePie , 'GenVerifyPhaseEx' ) );
      GenHasSymmetry := TGenHasSymmetry( GetProcAddress( hLibTiePie , 'GenHasSymmetry' ) );
      GenHasSymmetryEx := TGenHasSymmetryEx( GetProcAddress( hLibTiePie , 'GenHasSymmetryEx' ) );
      GenGetSymmetryMin := TGenGetSymmetryMin( GetProcAddress( hLibTiePie , 'GenGetSymmetryMin' ) );
      GenGetSymmetryMax := TGenGetSymmetryMax( GetProcAddress( hLibTiePie , 'GenGetSymmetryMax' ) );
      GenGetSymmetryMinMaxEx := TGenGetSymmetryMinMaxEx( GetProcAddress( hLibTiePie , 'GenGetSymmetryMinMaxEx' ) );
      GenGetSymmetry := TGenGetSymmetry( GetProcAddress( hLibTiePie , 'GenGetSymmetry' ) );
      GenSetSymmetry := TGenSetSymmetry( GetProcAddress( hLibTiePie , 'GenSetSymmetry' ) );
      GenVerifySymmetry := TGenVerifySymmetry( GetProcAddress( hLibTiePie , 'GenVerifySymmetry' ) );
      GenVerifySymmetryEx := TGenVerifySymmetryEx( GetProcAddress( hLibTiePie , 'GenVerifySymmetryEx' ) );
      GenHasWidth := TGenHasWidth( GetProcAddress( hLibTiePie , 'GenHasWidth' ) );
      GenHasWidthEx := TGenHasWidthEx( GetProcAddress( hLibTiePie , 'GenHasWidthEx' ) );
      GenGetWidthMin := TGenGetWidthMin( GetProcAddress( hLibTiePie , 'GenGetWidthMin' ) );
      GenGetWidthMax := TGenGetWidthMax( GetProcAddress( hLibTiePie , 'GenGetWidthMax' ) );
      GenGetWidthMinMaxEx := TGenGetWidthMinMaxEx( GetProcAddress( hLibTiePie , 'GenGetWidthMinMaxEx' ) );
      GenGetWidth := TGenGetWidth( GetProcAddress( hLibTiePie , 'GenGetWidth' ) );
      GenSetWidth := TGenSetWidth( GetProcAddress( hLibTiePie , 'GenSetWidth' ) );
      GenVerifyWidth := TGenVerifyWidth( GetProcAddress( hLibTiePie , 'GenVerifyWidth' ) );
      GenVerifyWidthEx := TGenVerifyWidthEx( GetProcAddress( hLibTiePie , 'GenVerifyWidthEx' ) );
      GenHasEdgeTime := TGenHasEdgeTime( GetProcAddress( hLibTiePie , 'GenHasEdgeTime' ) );
      GenHasEdgeTimeEx := TGenHasEdgeTimeEx( GetProcAddress( hLibTiePie , 'GenHasEdgeTimeEx' ) );
      GenGetLeadingEdgeTimeMin := TGenGetLeadingEdgeTimeMin( GetProcAddress( hLibTiePie , 'GenGetLeadingEdgeTimeMin' ) );
      GenGetLeadingEdgeTimeMax := TGenGetLeadingEdgeTimeMax( GetProcAddress( hLibTiePie , 'GenGetLeadingEdgeTimeMax' ) );
      GenGetLeadingEdgeTimeMinMaxEx := TGenGetLeadingEdgeTimeMinMaxEx( GetProcAddress( hLibTiePie , 'GenGetLeadingEdgeTimeMinMaxEx' ) );
      GenGetLeadingEdgeTime := TGenGetLeadingEdgeTime( GetProcAddress( hLibTiePie , 'GenGetLeadingEdgeTime' ) );
      GenSetLeadingEdgeTime := TGenSetLeadingEdgeTime( GetProcAddress( hLibTiePie , 'GenSetLeadingEdgeTime' ) );
      GenVerifyLeadingEdgeTime := TGenVerifyLeadingEdgeTime( GetProcAddress( hLibTiePie , 'GenVerifyLeadingEdgeTime' ) );
      GenVerifyLeadingEdgeTimeEx := TGenVerifyLeadingEdgeTimeEx( GetProcAddress( hLibTiePie , 'GenVerifyLeadingEdgeTimeEx' ) );
      GenGetTrailingEdgeTimeMin := TGenGetTrailingEdgeTimeMin( GetProcAddress( hLibTiePie , 'GenGetTrailingEdgeTimeMin' ) );
      GenGetTrailingEdgeTimeMax := TGenGetTrailingEdgeTimeMax( GetProcAddress( hLibTiePie , 'GenGetTrailingEdgeTimeMax' ) );
      GenGetTrailingEdgeTimeMinMaxEx := TGenGetTrailingEdgeTimeMinMaxEx( GetProcAddress( hLibTiePie , 'GenGetTrailingEdgeTimeMinMaxEx' ) );
      GenGetTrailingEdgeTime := TGenGetTrailingEdgeTime( GetProcAddress( hLibTiePie , 'GenGetTrailingEdgeTime' ) );
      GenSetTrailingEdgeTime := TGenSetTrailingEdgeTime( GetProcAddress( hLibTiePie , 'GenSetTrailingEdgeTime' ) );
      GenVerifyTrailingEdgeTime := TGenVerifyTrailingEdgeTime( GetProcAddress( hLibTiePie , 'GenVerifyTrailingEdgeTime' ) );
      GenVerifyTrailingEdgeTimeEx := TGenVerifyTrailingEdgeTimeEx( GetProcAddress( hLibTiePie , 'GenVerifyTrailingEdgeTimeEx' ) );
      GenHasData := TGenHasData( GetProcAddress( hLibTiePie , 'GenHasData' ) );
      GenHasDataEx := TGenHasDataEx( GetProcAddress( hLibTiePie , 'GenHasDataEx' ) );
      GenGetDataLengthMin := TGenGetDataLengthMin( GetProcAddress( hLibTiePie , 'GenGetDataLengthMin' ) );
      GenGetDataLengthMax := TGenGetDataLengthMax( GetProcAddress( hLibTiePie , 'GenGetDataLengthMax' ) );
      GenGetDataLengthMinMaxEx := TGenGetDataLengthMinMaxEx( GetProcAddress( hLibTiePie , 'GenGetDataLengthMinMaxEx' ) );
      GenGetDataLength := TGenGetDataLength( GetProcAddress( hLibTiePie , 'GenGetDataLength' ) );
      GenVerifyDataLength := TGenVerifyDataLength( GetProcAddress( hLibTiePie , 'GenVerifyDataLength' ) );
      GenVerifyDataLengthEx := TGenVerifyDataLengthEx( GetProcAddress( hLibTiePie , 'GenVerifyDataLengthEx' ) );
      GenSetData := TGenSetData( GetProcAddress( hLibTiePie , 'GenSetData' ) );
      GenSetDataEx := TGenSetDataEx( GetProcAddress( hLibTiePie , 'GenSetDataEx' ) );
      GenGetDataRawType := TGenGetDataRawType( GetProcAddress( hLibTiePie , 'GenGetDataRawType' ) );
      GenGetDataRawValueRange := TGenGetDataRawValueRange( GetProcAddress( hLibTiePie , 'GenGetDataRawValueRange' ) );
      GenGetDataRawValueMin := TGenGetDataRawValueMin( GetProcAddress( hLibTiePie , 'GenGetDataRawValueMin' ) );
      GenGetDataRawValueZero := TGenGetDataRawValueZero( GetProcAddress( hLibTiePie , 'GenGetDataRawValueZero' ) );
      GenGetDataRawValueMax := TGenGetDataRawValueMax( GetProcAddress( hLibTiePie , 'GenGetDataRawValueMax' ) );
      GenSetDataRaw := TGenSetDataRaw( GetProcAddress( hLibTiePie , 'GenSetDataRaw' ) );
      GenSetDataRawEx := TGenSetDataRawEx( GetProcAddress( hLibTiePie , 'GenSetDataRawEx' ) );
      GenGetModes := TGenGetModes( GetProcAddress( hLibTiePie , 'GenGetModes' ) );
      GenGetModesEx := TGenGetModesEx( GetProcAddress( hLibTiePie , 'GenGetModesEx' ) );
      GenGetModesNative := TGenGetModesNative( GetProcAddress( hLibTiePie , 'GenGetModesNative' ) );
      GenGetMode := TGenGetMode( GetProcAddress( hLibTiePie , 'GenGetMode' ) );
      GenSetMode := TGenSetMode( GetProcAddress( hLibTiePie , 'GenSetMode' ) );
      GenIsBurstActive := TGenIsBurstActive( GetProcAddress( hLibTiePie , 'GenIsBurstActive' ) );
      GenGetBurstCountMin := TGenGetBurstCountMin( GetProcAddress( hLibTiePie , 'GenGetBurstCountMin' ) );
      GenGetBurstCountMax := TGenGetBurstCountMax( GetProcAddress( hLibTiePie , 'GenGetBurstCountMax' ) );
      GenGetBurstCountMinMaxEx := TGenGetBurstCountMinMaxEx( GetProcAddress( hLibTiePie , 'GenGetBurstCountMinMaxEx' ) );
      GenGetBurstCount := TGenGetBurstCount( GetProcAddress( hLibTiePie , 'GenGetBurstCount' ) );
      GenSetBurstCount := TGenSetBurstCount( GetProcAddress( hLibTiePie , 'GenSetBurstCount' ) );
      GenGetBurstSampleCountMin := TGenGetBurstSampleCountMin( GetProcAddress( hLibTiePie , 'GenGetBurstSampleCountMin' ) );
      GenGetBurstSampleCountMax := TGenGetBurstSampleCountMax( GetProcAddress( hLibTiePie , 'GenGetBurstSampleCountMax' ) );
      GenGetBurstSampleCountMinMaxEx := TGenGetBurstSampleCountMinMaxEx( GetProcAddress( hLibTiePie , 'GenGetBurstSampleCountMinMaxEx' ) );
      GenGetBurstSampleCount := TGenGetBurstSampleCount( GetProcAddress( hLibTiePie , 'GenGetBurstSampleCount' ) );
      GenSetBurstSampleCount := TGenSetBurstSampleCount( GetProcAddress( hLibTiePie , 'GenSetBurstSampleCount' ) );
      GenGetBurstSegmentCountMin := TGenGetBurstSegmentCountMin( GetProcAddress( hLibTiePie , 'GenGetBurstSegmentCountMin' ) );
      GenGetBurstSegmentCountMax := TGenGetBurstSegmentCountMax( GetProcAddress( hLibTiePie , 'GenGetBurstSegmentCountMax' ) );
      GenGetBurstSegmentCountMinMaxEx := TGenGetBurstSegmentCountMinMaxEx( GetProcAddress( hLibTiePie , 'GenGetBurstSegmentCountMinMaxEx' ) );
      GenGetBurstSegmentCount := TGenGetBurstSegmentCount( GetProcAddress( hLibTiePie , 'GenGetBurstSegmentCount' ) );
      GenSetBurstSegmentCount := TGenSetBurstSegmentCount( GetProcAddress( hLibTiePie , 'GenSetBurstSegmentCount' ) );
      GenVerifyBurstSegmentCount := TGenVerifyBurstSegmentCount( GetProcAddress( hLibTiePie , 'GenVerifyBurstSegmentCount' ) );
      GenVerifyBurstSegmentCountEx := TGenVerifyBurstSegmentCountEx( GetProcAddress( hLibTiePie , 'GenVerifyBurstSegmentCountEx' ) );
      GenSetCallbackBurstCompleted := TGenSetCallbackBurstCompleted( GetProcAddress( hLibTiePie , 'GenSetCallbackBurstCompleted' ) );
      {$ifdef LINUX}
      GenSetEventBurstCompleted := TGenSetEventBurstCompleted( GetProcAddress( hLibTiePie , 'GenSetEventBurstCompleted' ) );
      {$endif LINUX}
      {$ifdef MSWINDOWS}
      GenSetEventBurstCompleted := TGenSetEventBurstCompleted( GetProcAddress( hLibTiePie , 'GenSetEventBurstCompleted' ) );
      GenSetMessageBurstCompleted := TGenSetMessageBurstCompleted( GetProcAddress( hLibTiePie , 'GenSetMessageBurstCompleted' ) );
      {$endif MSWINDOWS}
      GenSetCallbackControllableChanged := TGenSetCallbackControllableChanged( GetProcAddress( hLibTiePie , 'GenSetCallbackControllableChanged' ) );
      {$ifdef LINUX}
      GenSetEventControllableChanged := TGenSetEventControllableChanged( GetProcAddress( hLibTiePie , 'GenSetEventControllableChanged' ) );
      {$endif LINUX}
      {$ifdef MSWINDOWS}
      GenSetEventControllableChanged := TGenSetEventControllableChanged( GetProcAddress( hLibTiePie , 'GenSetEventControllableChanged' ) );
      GenSetMessageControllableChanged := TGenSetMessageControllableChanged( GetProcAddress( hLibTiePie , 'GenSetMessageControllableChanged' ) );
      {$endif MSWINDOWS}
      I2CIsInternalAddress := TI2CIsInternalAddress( GetProcAddress( hLibTiePie , 'I2CIsInternalAddress' ) );
      I2CGetInternalAddresses := TI2CGetInternalAddresses( GetProcAddress( hLibTiePie , 'I2CGetInternalAddresses' ) );
      I2CRead := TI2CRead( GetProcAddress( hLibTiePie , 'I2CRead' ) );
      I2CReadByte := TI2CReadByte( GetProcAddress( hLibTiePie , 'I2CReadByte' ) );
      I2CReadWord := TI2CReadWord( GetProcAddress( hLibTiePie , 'I2CReadWord' ) );
      I2CWrite := TI2CWrite( GetProcAddress( hLibTiePie , 'I2CWrite' ) );
      I2CWriteByte := TI2CWriteByte( GetProcAddress( hLibTiePie , 'I2CWriteByte' ) );
      I2CWriteByteByte := TI2CWriteByteByte( GetProcAddress( hLibTiePie , 'I2CWriteByteByte' ) );
      I2CWriteByteWord := TI2CWriteByteWord( GetProcAddress( hLibTiePie , 'I2CWriteByteWord' ) );
      I2CWriteWord := TI2CWriteWord( GetProcAddress( hLibTiePie , 'I2CWriteWord' ) );
      I2CWriteRead := TI2CWriteRead( GetProcAddress( hLibTiePie , 'I2CWriteRead' ) );
      I2CGetSpeedMax := TI2CGetSpeedMax( GetProcAddress( hLibTiePie , 'I2CGetSpeedMax' ) );
      I2CGetSpeed := TI2CGetSpeed( GetProcAddress( hLibTiePie , 'I2CGetSpeed' ) );
      I2CSetSpeed := TI2CSetSpeed( GetProcAddress( hLibTiePie , 'I2CSetSpeed' ) );
      I2CVerifySpeed := TI2CVerifySpeed( GetProcAddress( hLibTiePie , 'I2CVerifySpeed' ) );
      SrvConnect := TSrvConnect( GetProcAddress( hLibTiePie , 'SrvConnect' ) );
      SrvDisconnect := TSrvDisconnect( GetProcAddress( hLibTiePie , 'SrvDisconnect' ) );
      SrvRemove := TSrvRemove( GetProcAddress( hLibTiePie , 'SrvRemove' ) );
      SrvGetStatus := TSrvGetStatus( GetProcAddress( hLibTiePie , 'SrvGetStatus' ) );
      SrvGetLastError := TSrvGetLastError( GetProcAddress( hLibTiePie , 'SrvGetLastError' ) );
      SrvGetURL := TSrvGetURL( GetProcAddress( hLibTiePie , 'SrvGetURL' ) );
      SrvGetID := TSrvGetID( GetProcAddress( hLibTiePie , 'SrvGetID' ) );
      SrvGetIPv4Address := TSrvGetIPv4Address( GetProcAddress( hLibTiePie , 'SrvGetIPv4Address' ) );
      SrvGetIPPort := TSrvGetIPPort( GetProcAddress( hLibTiePie , 'SrvGetIPPort' ) );
      SrvGetName := TSrvGetName( GetProcAddress( hLibTiePie , 'SrvGetName' ) );
      SrvGetDescription := TSrvGetDescription( GetProcAddress( hLibTiePie , 'SrvGetDescription' ) );
      SrvGetVersion := TSrvGetVersion( GetProcAddress( hLibTiePie , 'SrvGetVersion' ) );
      SrvGetVersionExtra := TSrvGetVersionExtra( GetProcAddress( hLibTiePie , 'SrvGetVersionExtra' ) );
      HlpPointerArrayNew := THlpPointerArrayNew( GetProcAddress( hLibTiePie , 'HlpPointerArrayNew' ) );
      HlpPointerArraySet := THlpPointerArraySet( GetProcAddress( hLibTiePie , 'HlpPointerArraySet' ) );
      HlpPointerArrayDelete := THlpPointerArrayDelete( GetProcAddress( hLibTiePie , 'HlpPointerArrayDelete' ) );

      LibInit();
    end;
  end;
  Result := hLibTiePie <> 0;
end;

function LibTiePieUnload : Boolean;
begin
  if hLibTiePie <> 0 then begin
    LibExit();

    LibInit := nil;
    LibIsInitialized := nil;
    LibExit := nil;
    LibGetVersion := nil;
    LibGetVersionExtra := nil;
    LibGetConfig := nil;
    LibGetLastStatus := nil;
    LibGetLastStatusStr := nil;
    LstUpdate := nil;
    LstGetCount := nil;
    LstOpenDevice := nil;
    LstOpenOscilloscope := nil;
    LstOpenGenerator := nil;
    LstOpenI2CHost := nil;
    LstCreateCombinedDevice := nil;
    LstCreateAndOpenCombinedDevice := nil;
    LstRemoveDevice := nil;
    LstRemoveDeviceForce := nil;
    LstDevCanOpen := nil;
    LstDevGetProductId := nil;
    LstDevGetVendorId := nil;
    LstDevGetName := nil;
    LstDevGetNameShort := nil;
    LstDevGetNameShortest := nil;
    LstDevGetDriverVersion := nil;
    LstDevGetRecommendedDriverVersion := nil;
    LstDevGetFirmwareVersion := nil;
    LstDevGetRecommendedFirmwareVersion := nil;
    LstDevGetCalibrationDate := nil;
    LstDevGetSerialNumber := nil;
    LstDevGetIPv4Address := nil;
    LstDevGetIPPort := nil;
    LstDevHasServer := nil;
    LstDevGetServer := nil;
    LstDevGetTypes := nil;
    LstDevGetContainedSerialNumbers := nil;
    LstCbDevGetProductId := nil;
    LstCbDevGetVendorId := nil;
    LstCbDevGetName := nil;
    LstCbDevGetNameShort := nil;
    LstCbDevGetNameShortest := nil;
    LstCbDevGetDriverVersion := nil;
    LstCbDevGetFirmwareVersion := nil;
    LstCbDevGetCalibrationDate := nil;
    LstCbScpGetChannelCount := nil;
    LstSetCallbackDeviceAdded := nil;
    LstSetCallbackDeviceRemoved := nil;
    LstSetCallbackDeviceCanOpenChanged := nil;
    {$ifdef LINUX}
    LstSetEventDeviceAdded := nil;
    LstSetEventDeviceRemoved := nil;
    LstSetEventDeviceCanOpenChanged := nil;
    {$endif LINUX}
    {$ifdef MSWINDOWS}
    LstSetEventDeviceAdded := nil;
    LstSetEventDeviceRemoved := nil;
    LstSetEventDeviceCanOpenChanged := nil;
    LstSetMessageDeviceAdded := nil;
    LstSetMessageDeviceRemoved := nil;
    LstSetMessageDeviceCanOpenChanged := nil;
    {$endif MSWINDOWS}
    NetGetAutoDetectEnabled := nil;
    NetSetAutoDetectEnabled := nil;
    NetSrvAdd := nil;
    NetSrvRemove := nil;
    NetSrvGetCount := nil;
    NetSrvGetByIndex := nil;
    NetSrvGetByURL := nil;
    NetSrvSetCallbackAdded := nil;
    {$ifdef LINUX}
    NetSrvSetEventAdded := nil;
    {$endif LINUX}
    {$ifdef MSWINDOWS}
    NetSrvSetEventAdded := nil;
    NetSrvSetMessageAdded := nil;
    {$endif MSWINDOWS}
    ObjClose := nil;
    ObjIsRemoved := nil;
    ObjGetInterfaces := nil;
    ObjSetEventCallback := nil;
    ObjGetEvent := nil;
    {$ifdef LINUX}
    ObjSetEventEvent := nil;
    {$endif LINUX}
    {$ifdef MSWINDOWS}
    ObjSetEventEvent := nil;
    ObjSetEventWindowHandle := nil;
    {$endif MSWINDOWS}
    DevClose := nil;
    DevIsRemoved := nil;
    DevGetDriverVersion := nil;
    DevGetFirmwareVersion := nil;
    DevGetCalibrationDate := nil;
    DevGetCalibrationToken := nil;
    DevGetSerialNumber := nil;
    DevGetIPv4Address := nil;
    DevGetIPPort := nil;
    DevGetProductId := nil;
    DevGetVendorId := nil;
    DevGetType := nil;
    DevGetName := nil;
    DevGetNameShort := nil;
    DevGetNameShortest := nil;
    DevHasBattery := nil;
    DevGetBatteryCharge := nil;
    DevGetBatteryTimeToEmpty := nil;
    DevGetBatteryTimeToFull := nil;
    DevIsBatteryChargerConnected := nil;
    DevIsBatteryCharging := nil;
    DevIsBatteryBroken := nil;
    DevSetCallbackRemoved := nil;
    {$ifdef LINUX}
    DevSetEventRemoved := nil;
    {$endif LINUX}
    {$ifdef MSWINDOWS}
    DevSetEventRemoved := nil;
    DevSetMessageRemoved := nil;
    {$endif MSWINDOWS}
    DevTrGetInputCount := nil;
    DevTrGetInputIndexById := nil;
    ScpTrInIsTriggered := nil;
    DevTrInGetEnabled := nil;
    DevTrInSetEnabled := nil;
    DevTrInGetKinds := nil;
    ScpTrInGetKindsEx := nil;
    DevTrInGetKind := nil;
    DevTrInSetKind := nil;
    DevTrInIsAvailable := nil;
    ScpTrInIsAvailableEx := nil;
    DevTrInGetId := nil;
    DevTrInGetName := nil;
    DevTrGetOutputCount := nil;
    DevTrGetOutputIndexById := nil;
    DevTrOutGetEnabled := nil;
    DevTrOutSetEnabled := nil;
    DevTrOutGetEvents := nil;
    DevTrOutGetEvent := nil;
    DevTrOutSetEvent := nil;
    DevTrOutGetId := nil;
    DevTrOutGetName := nil;
    DevTrOutTrigger := nil;
    ScpGetChannelCount := nil;
    ScpChIsAvailable := nil;
    ScpChIsAvailableEx := nil;
    ScpChGetConnectorType := nil;
    ScpChIsDifferential := nil;
    ScpChGetImpedance := nil;
    ScpChGetBandwidths := nil;
    ScpChGetBandwidth := nil;
    ScpChSetBandwidth := nil;
    ScpChGetCouplings := nil;
    ScpChGetCoupling := nil;
    ScpChSetCoupling := nil;
    ScpChGetEnabled := nil;
    ScpChSetEnabled := nil;
    ScpChGetProbeGain := nil;
    ScpChSetProbeGain := nil;
    ScpChGetProbeOffset := nil;
    ScpChSetProbeOffset := nil;
    ScpChGetAutoRanging := nil;
    ScpChSetAutoRanging := nil;
    ScpChGetRanges := nil;
    ScpChGetRangesEx := nil;
    ScpChGetRange := nil;
    ScpChSetRange := nil;
    ScpChHasSafeGround := nil;
    ScpChGetSafeGroundEnabled := nil;
    ScpChSetSafeGroundEnabled := nil;
    ScpChGetSafeGroundThresholdMin := nil;
    ScpChGetSafeGroundThresholdMax := nil;
    ScpChGetSafeGroundThreshold := nil;
    ScpChSetSafeGroundThreshold := nil;
    ScpChVerifySafeGroundThreshold := nil;
    ScpChHasTrigger := nil;
    ScpChHasTriggerEx := nil;
    ScpChTrIsAvailable := nil;
    ScpChTrIsAvailableEx := nil;
    ScpChTrIsTriggered := nil;
    ScpChTrGetEnabled := nil;
    ScpChTrSetEnabled := nil;
    ScpChTrGetKinds := nil;
    ScpChTrGetKindsEx := nil;
    ScpChTrGetKind := nil;
    ScpChTrSetKind := nil;
    ScpChTrGetLevelModes := nil;
    ScpChTrGetLevelMode := nil;
    ScpChTrSetLevelMode := nil;
    ScpChTrGetLevelCount := nil;
    ScpChTrGetLevel := nil;
    ScpChTrSetLevel := nil;
    ScpChTrGetHysteresisCount := nil;
    ScpChTrGetHysteresis := nil;
    ScpChTrSetHysteresis := nil;
    ScpChTrGetConditions := nil;
    ScpChTrGetConditionsEx := nil;
    ScpChTrGetCondition := nil;
    ScpChTrSetCondition := nil;
    ScpChTrGetTimeCount := nil;
    ScpChTrGetTime := nil;
    ScpChTrSetTime := nil;
    ScpChTrVerifyTime := nil;
    ScpChTrVerifyTimeEx2 := nil;
    ScpGetData := nil;
    ScpGetData1Ch := nil;
    ScpGetData2Ch := nil;
    ScpGetData3Ch := nil;
    ScpGetData4Ch := nil;
    ScpGetData5Ch := nil;
    ScpGetData6Ch := nil;
    ScpGetData7Ch := nil;
    ScpGetData8Ch := nil;
    ScpGetValidPreSampleCount := nil;
    ScpChGetDataValueRange := nil;
    ScpChGetDataValueMin := nil;
    ScpChGetDataValueMax := nil;
    ScpGetDataRaw := nil;
    ScpGetDataRaw1Ch := nil;
    ScpGetDataRaw2Ch := nil;
    ScpGetDataRaw3Ch := nil;
    ScpGetDataRaw4Ch := nil;
    ScpGetDataRaw5Ch := nil;
    ScpGetDataRaw6Ch := nil;
    ScpGetDataRaw7Ch := nil;
    ScpGetDataRaw8Ch := nil;
    ScpChGetDataRawType := nil;
    ScpChGetDataRawValueRange := nil;
    ScpChGetDataRawValueMin := nil;
    ScpChGetDataRawValueZero := nil;
    ScpChGetDataRawValueMax := nil;
    ScpChIsRangeMaxReachable := nil;
    ScpIsGetDataAsyncCompleted := nil;
    ScpStartGetDataAsync := nil;
    ScpStartGetDataAsyncRaw := nil;
    ScpCancelGetDataAsync := nil;
    ScpSetCallbackDataReady := nil;
    ScpSetCallbackDataOverflow := nil;
    ScpSetCallbackConnectionTestCompleted := nil;
    ScpSetCallbackTriggered := nil;
    {$ifdef LINUX}
    ScpSetEventDataReady := nil;
    ScpSetEventDataOverflow := nil;
    ScpSetEventConnectionTestCompleted := nil;
    ScpSetEventTriggered := nil;
    {$endif LINUX}
    {$ifdef MSWINDOWS}
    ScpSetEventDataReady := nil;
    ScpSetEventDataOverflow := nil;
    ScpSetEventConnectionTestCompleted := nil;
    ScpSetEventTriggered := nil;
    ScpSetMessageDataReady := nil;
    ScpSetMessageDataOverflow := nil;
    ScpSetMessageConnectionTestCompleted := nil;
    ScpSetMessageTriggered := nil;
    {$endif MSWINDOWS}
    ScpStart := nil;
    ScpStop := nil;
    ScpForceTrigger := nil;
    ScpGetMeasureModes := nil;
    ScpGetMeasureMode := nil;
    ScpSetMeasureMode := nil;
    ScpIsRunning := nil;
    ScpIsTriggered := nil;
    ScpIsTimeOutTriggered := nil;
    ScpIsForceTriggered := nil;
    ScpIsDataReady := nil;
    ScpIsDataOverflow := nil;
    ScpGetAutoResolutionModes := nil;
    ScpGetAutoResolutionMode := nil;
    ScpSetAutoResolutionMode := nil;
    ScpGetResolutions := nil;
    ScpGetResolution := nil;
    ScpSetResolution := nil;
    ScpIsResolutionEnhanced := nil;
    ScpIsResolutionEnhancedEx := nil;
    ScpGetClockSources := nil;
    ScpGetClockSource := nil;
    ScpSetClockSource := nil;
    ScpGetClockSourceFrequencies := nil;
    ScpGetClockSourceFrequenciesEx := nil;
    ScpGetClockSourceFrequency := nil;
    ScpSetClockSourceFrequency := nil;
    ScpGetClockOutputs := nil;
    ScpGetClockOutput := nil;
    ScpSetClockOutput := nil;
    ScpGetClockOutputFrequencies := nil;
    ScpGetClockOutputFrequenciesEx := nil;
    ScpGetClockOutputFrequency := nil;
    ScpSetClockOutputFrequency := nil;
    ScpGetSampleFrequencyMax := nil;
    ScpGetSampleFrequency := nil;
    ScpSetSampleFrequency := nil;
    ScpVerifySampleFrequency := nil;
    ScpVerifySampleFrequencyEx := nil;
    ScpVerifySampleFrequenciesEx := nil;
    ScpGetRecordLengthMax := nil;
    ScpGetRecordLengthMaxEx := nil;
    ScpGetRecordLength := nil;
    ScpSetRecordLength := nil;
    ScpVerifyRecordLength := nil;
    ScpVerifyRecordLengthEx := nil;
    ScpGetPreSampleRatio := nil;
    ScpSetPreSampleRatio := nil;
    ScpGetSegmentCountMax := nil;
    ScpGetSegmentCountMaxEx := nil;
    ScpGetSegmentCount := nil;
    ScpSetSegmentCount := nil;
    ScpVerifySegmentCount := nil;
    ScpVerifySegmentCountEx2 := nil;
    ScpHasTrigger := nil;
    ScpHasTriggerEx := nil;
    ScpGetTriggerTimeOut := nil;
    ScpSetTriggerTimeOut := nil;
    ScpVerifyTriggerTimeOut := nil;
    ScpVerifyTriggerTimeOutEx := nil;
    ScpHasTriggerDelay := nil;
    ScpHasTriggerDelayEx := nil;
    ScpGetTriggerDelayMax := nil;
    ScpGetTriggerDelayMaxEx := nil;
    ScpGetTriggerDelay := nil;
    ScpSetTriggerDelay := nil;
    ScpVerifyTriggerDelay := nil;
    ScpVerifyTriggerDelayEx := nil;
    ScpHasTriggerHoldOff := nil;
    ScpHasTriggerHoldOffEx := nil;
    ScpGetTriggerHoldOffCountMax := nil;
    ScpGetTriggerHoldOffCountMaxEx := nil;
    ScpGetTriggerHoldOffCount := nil;
    ScpSetTriggerHoldOffCount := nil;
    ScpHasConnectionTest := nil;
    ScpChHasConnectionTest := nil;
    ScpStartConnectionTest := nil;
    ScpStartConnectionTestEx := nil;
    ScpIsConnectionTestCompleted := nil;
    ScpGetConnectionTestData := nil;
    GenGetConnectorType := nil;
    GenIsDifferential := nil;
    GenGetImpedance := nil;
    GenGetResolution := nil;
    GenGetOutputValueMin := nil;
    GenGetOutputValueMax := nil;
    GenGetOutputValueMinMax := nil;
    GenIsControllable := nil;
    GenIsRunning := nil;
    GenGetStatus := nil;
    GenGetOutputOn := nil;
    GenSetOutputOn := nil;
    GenHasOutputInvert := nil;
    GenGetOutputInvert := nil;
    GenSetOutputInvert := nil;
    GenStart := nil;
    GenStop := nil;
    GenGetSignalTypes := nil;
    GenGetSignalType := nil;
    GenSetSignalType := nil;
    GenHasAmplitude := nil;
    GenHasAmplitudeEx := nil;
    GenGetAmplitudeMin := nil;
    GenGetAmplitudeMax := nil;
    GenGetAmplitudeMinMaxEx := nil;
    GenGetAmplitude := nil;
    GenSetAmplitude := nil;
    GenVerifyAmplitude := nil;
    GenVerifyAmplitudeEx := nil;
    GenGetAmplitudeRanges := nil;
    GenGetAmplitudeRange := nil;
    GenSetAmplitudeRange := nil;
    GenGetAmplitudeAutoRanging := nil;
    GenSetAmplitudeAutoRanging := nil;
    GenHasOffset := nil;
    GenHasOffsetEx := nil;
    GenGetOffsetMin := nil;
    GenGetOffsetMax := nil;
    GenGetOffsetMinMaxEx := nil;
    GenGetOffset := nil;
    GenSetOffset := nil;
    GenVerifyOffset := nil;
    GenVerifyOffsetEx := nil;
    GenGetFrequencyModes := nil;
    GenGetFrequencyModesEx := nil;
    GenGetFrequencyMode := nil;
    GenSetFrequencyMode := nil;
    GenHasFrequency := nil;
    GenHasFrequencyEx := nil;
    GenGetFrequencyMin := nil;
    GenGetFrequencyMax := nil;
    GenGetFrequencyMinMax := nil;
    GenGetFrequencyMinMaxEx := nil;
    GenGetFrequency := nil;
    GenSetFrequency := nil;
    GenVerifyFrequency := nil;
    GenVerifyFrequencyEx2 := nil;
    GenHasPhase := nil;
    GenHasPhaseEx := nil;
    GenGetPhaseMin := nil;
    GenGetPhaseMax := nil;
    GenGetPhaseMinMaxEx := nil;
    GenGetPhase := nil;
    GenSetPhase := nil;
    GenVerifyPhase := nil;
    GenVerifyPhaseEx := nil;
    GenHasSymmetry := nil;
    GenHasSymmetryEx := nil;
    GenGetSymmetryMin := nil;
    GenGetSymmetryMax := nil;
    GenGetSymmetryMinMaxEx := nil;
    GenGetSymmetry := nil;
    GenSetSymmetry := nil;
    GenVerifySymmetry := nil;
    GenVerifySymmetryEx := nil;
    GenHasWidth := nil;
    GenHasWidthEx := nil;
    GenGetWidthMin := nil;
    GenGetWidthMax := nil;
    GenGetWidthMinMaxEx := nil;
    GenGetWidth := nil;
    GenSetWidth := nil;
    GenVerifyWidth := nil;
    GenVerifyWidthEx := nil;
    GenHasEdgeTime := nil;
    GenHasEdgeTimeEx := nil;
    GenGetLeadingEdgeTimeMin := nil;
    GenGetLeadingEdgeTimeMax := nil;
    GenGetLeadingEdgeTimeMinMaxEx := nil;
    GenGetLeadingEdgeTime := nil;
    GenSetLeadingEdgeTime := nil;
    GenVerifyLeadingEdgeTime := nil;
    GenVerifyLeadingEdgeTimeEx := nil;
    GenGetTrailingEdgeTimeMin := nil;
    GenGetTrailingEdgeTimeMax := nil;
    GenGetTrailingEdgeTimeMinMaxEx := nil;
    GenGetTrailingEdgeTime := nil;
    GenSetTrailingEdgeTime := nil;
    GenVerifyTrailingEdgeTime := nil;
    GenVerifyTrailingEdgeTimeEx := nil;
    GenHasData := nil;
    GenHasDataEx := nil;
    GenGetDataLengthMin := nil;
    GenGetDataLengthMax := nil;
    GenGetDataLengthMinMaxEx := nil;
    GenGetDataLength := nil;
    GenVerifyDataLength := nil;
    GenVerifyDataLengthEx := nil;
    GenSetData := nil;
    GenSetDataEx := nil;
    GenGetDataRawType := nil;
    GenGetDataRawValueRange := nil;
    GenGetDataRawValueMin := nil;
    GenGetDataRawValueZero := nil;
    GenGetDataRawValueMax := nil;
    GenSetDataRaw := nil;
    GenSetDataRawEx := nil;
    GenGetModes := nil;
    GenGetModesEx := nil;
    GenGetModesNative := nil;
    GenGetMode := nil;
    GenSetMode := nil;
    GenIsBurstActive := nil;
    GenGetBurstCountMin := nil;
    GenGetBurstCountMax := nil;
    GenGetBurstCountMinMaxEx := nil;
    GenGetBurstCount := nil;
    GenSetBurstCount := nil;
    GenGetBurstSampleCountMin := nil;
    GenGetBurstSampleCountMax := nil;
    GenGetBurstSampleCountMinMaxEx := nil;
    GenGetBurstSampleCount := nil;
    GenSetBurstSampleCount := nil;
    GenGetBurstSegmentCountMin := nil;
    GenGetBurstSegmentCountMax := nil;
    GenGetBurstSegmentCountMinMaxEx := nil;
    GenGetBurstSegmentCount := nil;
    GenSetBurstSegmentCount := nil;
    GenVerifyBurstSegmentCount := nil;
    GenVerifyBurstSegmentCountEx := nil;
    GenSetCallbackBurstCompleted := nil;
    {$ifdef LINUX}
    GenSetEventBurstCompleted := nil;
    {$endif LINUX}
    {$ifdef MSWINDOWS}
    GenSetEventBurstCompleted := nil;
    GenSetMessageBurstCompleted := nil;
    {$endif MSWINDOWS}
    GenSetCallbackControllableChanged := nil;
    {$ifdef LINUX}
    GenSetEventControllableChanged := nil;
    {$endif LINUX}
    {$ifdef MSWINDOWS}
    GenSetEventControllableChanged := nil;
    GenSetMessageControllableChanged := nil;
    {$endif MSWINDOWS}
    I2CIsInternalAddress := nil;
    I2CGetInternalAddresses := nil;
    I2CRead := nil;
    I2CReadByte := nil;
    I2CReadWord := nil;
    I2CWrite := nil;
    I2CWriteByte := nil;
    I2CWriteByteByte := nil;
    I2CWriteByteWord := nil;
    I2CWriteWord := nil;
    I2CWriteRead := nil;
    I2CGetSpeedMax := nil;
    I2CGetSpeed := nil;
    I2CSetSpeed := nil;
    I2CVerifySpeed := nil;
    SrvConnect := nil;
    SrvDisconnect := nil;
    SrvRemove := nil;
    SrvGetStatus := nil;
    SrvGetLastError := nil;
    SrvGetURL := nil;
    SrvGetID := nil;
    SrvGetIPv4Address := nil;
    SrvGetIPPort := nil;
    SrvGetName := nil;
    SrvGetDescription := nil;
    SrvGetVersion := nil;
    SrvGetVersionExtra := nil;
    HlpPointerArrayNew := nil;
    HlpPointerArraySet := nil;
    HlpPointerArrayDelete := nil;

    FreeLibrary( hLibTiePie );

    hLibTiePie := 0;
  end;
  Result := hLibTiePie = 0;
end;

{$else} // LIBTIEPIE_STATIC

procedure LibInit; cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_LibInit'{$endif};
function LibIsInitialized : ByteBool; cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_LibIsInitialized'{$endif};
procedure LibExit; cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_LibExit'{$endif};
function LibGetVersion : TTpVersion; cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_LibGetVersion'{$endif};
function LibGetVersionExtra : PAnsiChar; cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_LibGetVersionExtra'{$endif};
function LibGetConfig( pBuffer : PByte ; dwBufferLength : LongWord ) : LongWord; cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_LibGetConfig'{$endif};
function LibGetLastStatus : TLibTiePieStatus; cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_LibGetLastStatus'{$endif};
function LibGetLastStatusStr : PAnsiChar; cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_LibGetLastStatusStr'{$endif};
procedure LstUpdate; cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_LstUpdate'{$endif};
function LstGetCount : LongWord; cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_LstGetCount'{$endif};
function LstOpenDevice( dwIdKind , dwId , dwDeviceType : LongWord ) : TLibTiePieHandle; cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_LstOpenDevice'{$endif};
function LstOpenOscilloscope( dwIdKind , dwId : LongWord ) : TLibTiePieHandle; cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_LstOpenOscilloscope'{$endif};
function LstOpenGenerator( dwIdKind , dwId : LongWord ) : TLibTiePieHandle; cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_LstOpenGenerator'{$endif};
function LstOpenI2CHost( dwIdKind , dwId : LongWord ) : TLibTiePieHandle; cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_LstOpenI2CHost'{$endif};
function LstCreateCombinedDevice( pDeviceHandles : PLibTiePieHandle ; dwCount : LongWord ) : LongWord; cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_LstCreateCombinedDevice'{$endif};
function LstCreateAndOpenCombinedDevice( pDeviceHandles : PLibTiePieHandle ; dwCount : LongWord ) : TLibTiePieHandle; cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_LstCreateAndOpenCombinedDevice'{$endif};
procedure LstRemoveDevice( dwSerialNumber : LongWord ); cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_LstRemoveDevice'{$endif};
procedure LstRemoveDeviceForce( dwSerialNumber : LongWord ); cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_LstRemoveDeviceForce'{$endif};
function LstDevCanOpen( dwIdKind , dwId , dwDeviceType : LongWord ) : ByteBool; cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_LstDevCanOpen'{$endif};
function LstDevGetProductId( dwIdKind , dwId : LongWord ) : LongWord; cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_LstDevGetProductId'{$endif};
function LstDevGetVendorId( dwIdKind , dwId : LongWord ) : LongWord; cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_LstDevGetVendorId'{$endif};
function LstDevGetName( dwIdKind , dwId : LongWord ; pBuffer : PAnsiChar ; dwBufferLength : LongWord ) : LongWord; cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_LstDevGetName'{$endif};
function LstDevGetNameShort( dwIdKind , dwId : LongWord ; pBuffer : PAnsiChar ; dwBufferLength : LongWord ) : LongWord; cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_LstDevGetNameShort'{$endif};
function LstDevGetNameShortest( dwIdKind , dwId : LongWord ; pBuffer : PAnsiChar ; dwBufferLength : LongWord ) : LongWord; cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_LstDevGetNameShortest'{$endif};
function LstDevGetDriverVersion( dwIdKind , dwId : LongWord ) : TTpVersion; cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_LstDevGetDriverVersion'{$endif};
function LstDevGetRecommendedDriverVersion( dwIdKind , dwId : LongWord ) : TTpVersion; cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_LstDevGetRecommendedDriverVersion'{$endif};
function LstDevGetFirmwareVersion( dwIdKind , dwId : LongWord ) : TTpVersion; cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_LstDevGetFirmwareVersion'{$endif};
function LstDevGetRecommendedFirmwareVersion( dwIdKind , dwId : LongWord ) : TTpVersion; cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_LstDevGetRecommendedFirmwareVersion'{$endif};
function LstDevGetCalibrationDate( dwIdKind , dwId : LongWord ) : TTpDate; cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_LstDevGetCalibrationDate'{$endif};
function LstDevGetSerialNumber( dwIdKind , dwId : LongWord ) : LongWord; cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_LstDevGetSerialNumber'{$endif};
function LstDevGetIPv4Address( dwIdKind , dwId : LongWord ) : LongWord; cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_LstDevGetIPv4Address'{$endif};
function LstDevGetIPPort( dwIdKind , dwId : LongWord ) : Word; cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_LstDevGetIPPort'{$endif};
function LstDevHasServer( dwIdKind , dwId : LongWord ) : ByteBool; cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_LstDevHasServer'{$endif};
function LstDevGetServer( dwIdKind , dwId : LongWord ) : TLibTiePieHandle; cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_LstDevGetServer'{$endif};
function LstDevGetTypes( dwIdKind , dwId : LongWord ) : LongWord; cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_LstDevGetTypes'{$endif};
function LstDevGetContainedSerialNumbers( dwIdKind , dwId : LongWord ; pBuffer : PLongWord ; dwBufferLength : LongWord ) : LongWord; cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_LstDevGetContainedSerialNumbers'{$endif};
function LstCbDevGetProductId( dwIdKind , dwId , dwContainedDeviceSerialNumber : LongWord ) : LongWord; cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_LstCbDevGetProductId'{$endif};
function LstCbDevGetVendorId( dwIdKind , dwId , dwContainedDeviceSerialNumber : LongWord ) : LongWord; cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_LstCbDevGetVendorId'{$endif};
function LstCbDevGetName( dwIdKind , dwId , dwContainedDeviceSerialNumber : LongWord ; pBuffer : PAnsiChar ; dwBufferLength : LongWord ) : LongWord; cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_LstCbDevGetName'{$endif};
function LstCbDevGetNameShort( dwIdKind , dwId , dwContainedDeviceSerialNumber : LongWord ; pBuffer : PAnsiChar ; dwBufferLength : LongWord ) : LongWord; cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_LstCbDevGetNameShort'{$endif};
function LstCbDevGetNameShortest( dwIdKind , dwId , dwContainedDeviceSerialNumber : LongWord ; pBuffer : PAnsiChar ; dwBufferLength : LongWord ) : LongWord; cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_LstCbDevGetNameShortest'{$endif};
function LstCbDevGetDriverVersion( dwIdKind , dwId , dwContainedDeviceSerialNumber : LongWord ) : TTpVersion; cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_LstCbDevGetDriverVersion'{$endif};
function LstCbDevGetFirmwareVersion( dwIdKind , dwId , dwContainedDeviceSerialNumber : LongWord ) : TTpVersion; cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_LstCbDevGetFirmwareVersion'{$endif};
function LstCbDevGetCalibrationDate( dwIdKind , dwId , dwContainedDeviceSerialNumber : LongWord ) : TTpDate; cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_LstCbDevGetCalibrationDate'{$endif};
function LstCbScpGetChannelCount( dwIdKind , dwId , dwContainedDeviceSerialNumber : LongWord ) : Word; cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_LstCbScpGetChannelCount'{$endif};
procedure LstSetCallbackDeviceAdded( pCallback : TTpCallbackDeviceList ; pData : Pointer ); cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_LstSetCallbackDeviceAdded'{$endif};
procedure LstSetCallbackDeviceRemoved( pCallback : TTpCallbackDeviceList ; pData : Pointer ); cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_LstSetCallbackDeviceRemoved'{$endif};
procedure LstSetCallbackDeviceCanOpenChanged( pCallback : TTpCallbackDeviceList ; pData : Pointer ); cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_LstSetCallbackDeviceCanOpenChanged'{$endif};
{$ifdef LINUX}
procedure LstSetEventDeviceAdded( fdEvent : Integer ); cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_LstSetEventDeviceAdded'{$endif};
procedure LstSetEventDeviceRemoved( fdEvent : Integer ); cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_LstSetEventDeviceRemoved'{$endif};
procedure LstSetEventDeviceCanOpenChanged( fdEvent : Integer ); cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_LstSetEventDeviceCanOpenChanged'{$endif};
{$endif LINUX}
{$ifdef MSWINDOWS}
procedure LstSetEventDeviceAdded( hEvent : THandle ); cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_LstSetEventDeviceAdded'{$endif};
procedure LstSetEventDeviceRemoved( hEvent : THandle ); cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_LstSetEventDeviceRemoved'{$endif};
procedure LstSetEventDeviceCanOpenChanged( hEvent : THandle ); cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_LstSetEventDeviceCanOpenChanged'{$endif};
procedure LstSetMessageDeviceAdded( hWnd : HWND ); cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_LstSetMessageDeviceAdded'{$endif};
procedure LstSetMessageDeviceRemoved( hWnd : HWND ); cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_LstSetMessageDeviceRemoved'{$endif};
procedure LstSetMessageDeviceCanOpenChanged( hWnd : HWND ); cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_LstSetMessageDeviceCanOpenChanged'{$endif};
{$endif MSWINDOWS}
function NetGetAutoDetectEnabled : ByteBool; cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_NetGetAutoDetectEnabled'{$endif};
function NetSetAutoDetectEnabled( bEnable : ByteBool ) : ByteBool; cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_NetSetAutoDetectEnabled'{$endif};
function NetSrvAdd( pURL : PAnsiChar ; dwURLLength : LongWord ; pHandle : PLibTiePieHandle ) : ByteBool; cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_NetSrvAdd'{$endif};
function NetSrvRemove( pURL : PAnsiChar ; dwURLLength : LongWord ; bForce : ByteBool ) : ByteBool; cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_NetSrvRemove'{$endif};
function NetSrvGetCount : LongWord; cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_NetSrvGetCount'{$endif};
function NetSrvGetByIndex( dwIndex : LongWord ) : TLibTiePieHandle; cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_NetSrvGetByIndex'{$endif};
function NetSrvGetByURL( pURL : PAnsiChar ; dwURLLength : LongWord ) : TLibTiePieHandle; cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_NetSrvGetByURL'{$endif};
procedure NetSrvSetCallbackAdded( pCallback : TTpCallbackHandle ; pData : Pointer ); cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_NetSrvSetCallbackAdded'{$endif};
{$ifdef LINUX}
procedure NetSrvSetEventAdded( fdEvent : Integer ); cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_NetSrvSetEventAdded'{$endif};
{$endif LINUX}
{$ifdef MSWINDOWS}
procedure NetSrvSetEventAdded( hEvent : THandle ); cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_NetSrvSetEventAdded'{$endif};
procedure NetSrvSetMessageAdded( hWnd : HWND ); cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_NetSrvSetMessageAdded'{$endif};
{$endif MSWINDOWS}
procedure ObjClose( hHandle : TLibTiePieHandle ); cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_ObjClose'{$endif};
function ObjIsRemoved( hHandle : TLibTiePieHandle ) : ByteBool; cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_ObjIsRemoved'{$endif};
function ObjGetInterfaces( hHandle : TLibTiePieHandle ) : UInt64; cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_ObjGetInterfaces'{$endif};
procedure ObjSetEventCallback( hHandle : TLibTiePieHandle ; pCallback : TTpCallbackEvent ; pData : Pointer ); cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_ObjSetEventCallback'{$endif};
function ObjGetEvent( hHandle : TLibTiePieHandle ; pEvent , pValue : PLongWord ) : ByteBool; cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_ObjGetEvent'{$endif};
{$ifdef LINUX}
procedure ObjSetEventEvent( hHandle : TLibTiePieHandle ; fdEvent : Integer ); cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_ObjSetEventEvent'{$endif};
{$endif LINUX}
{$ifdef MSWINDOWS}
procedure ObjSetEventEvent( hHandle : TLibTiePieHandle ; hEvent : THandle ); cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_ObjSetEventEvent'{$endif};
procedure ObjSetEventWindowHandle( hHandle : TLibTiePieHandle ; hWnd : HWND ); cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_ObjSetEventWindowHandle'{$endif};
{$endif MSWINDOWS}
procedure DevClose( hDevice : TLibTiePieHandle ); cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_DevClose'{$endif};
function DevIsRemoved( hDevice : TLibTiePieHandle ) : ByteBool; cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_DevIsRemoved'{$endif};
function DevGetDriverVersion( hDevice : TLibTiePieHandle ) : TTpVersion; cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_DevGetDriverVersion'{$endif};
function DevGetFirmwareVersion( hDevice : TLibTiePieHandle ) : TTpVersion; cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_DevGetFirmwareVersion'{$endif};
function DevGetCalibrationDate( hDevice : TLibTiePieHandle ) : TTpDate; cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_DevGetCalibrationDate'{$endif};
function DevGetCalibrationToken( hDevice : TLibTiePieHandle ; pBuffer : PAnsiChar ; dwBufferLength : LongWord ) : LongWord; cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_DevGetCalibrationToken'{$endif};
function DevGetSerialNumber( hDevice : TLibTiePieHandle ) : LongWord; cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_DevGetSerialNumber'{$endif};
function DevGetIPv4Address( hDevice : TLibTiePieHandle ) : LongWord; cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_DevGetIPv4Address'{$endif};
function DevGetIPPort( hDevice : TLibTiePieHandle ) : Word; cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_DevGetIPPort'{$endif};
function DevGetProductId( hDevice : TLibTiePieHandle ) : LongWord; cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_DevGetProductId'{$endif};
function DevGetVendorId( hDevice : TLibTiePieHandle ) : LongWord; cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_DevGetVendorId'{$endif};
function DevGetType( hDevice : TLibTiePieHandle ) : LongWord; cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_DevGetType'{$endif};
function DevGetName( hDevice : TLibTiePieHandle ; pBuffer : PAnsiChar ; dwBufferLength : LongWord ) : LongWord; cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_DevGetName'{$endif};
function DevGetNameShort( hDevice : TLibTiePieHandle ; pBuffer : PAnsiChar ; dwBufferLength : LongWord ) : LongWord; cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_DevGetNameShort'{$endif};
function DevGetNameShortest( hDevice : TLibTiePieHandle ; pBuffer : PAnsiChar ; dwBufferLength : LongWord ) : LongWord; cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_DevGetNameShortest'{$endif};
function DevHasBattery( hDevice : TLibTiePieHandle ) : ByteBool; cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_DevHasBattery'{$endif};
function DevGetBatteryCharge( hDevice : TLibTiePieHandle ) : ShortInt; cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_DevGetBatteryCharge'{$endif};
function DevGetBatteryTimeToEmpty( hDevice : TLibTiePieHandle ) : LongInt; cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_DevGetBatteryTimeToEmpty'{$endif};
function DevGetBatteryTimeToFull( hDevice : TLibTiePieHandle ) : LongInt; cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_DevGetBatteryTimeToFull'{$endif};
function DevIsBatteryChargerConnected( hDevice : TLibTiePieHandle ) : ByteBool; cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_DevIsBatteryChargerConnected'{$endif};
function DevIsBatteryCharging( hDevice : TLibTiePieHandle ) : ByteBool; cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_DevIsBatteryCharging'{$endif};
function DevIsBatteryBroken( hDevice : TLibTiePieHandle ) : ByteBool; cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_DevIsBatteryBroken'{$endif};
procedure DevSetCallbackRemoved( hDevice : TLibTiePieHandle ; pCallback : TTpCallback ; pData : Pointer ); cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_DevSetCallbackRemoved'{$endif};
{$ifdef LINUX}
procedure DevSetEventRemoved( hDevice : TLibTiePieHandle ; fdEvent : Integer ); cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_DevSetEventRemoved'{$endif};
{$endif LINUX}
{$ifdef MSWINDOWS}
procedure DevSetEventRemoved( hDevice : TLibTiePieHandle ; hEvent : THandle ); cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_DevSetEventRemoved'{$endif};
procedure DevSetMessageRemoved( hDevice : TLibTiePieHandle ; hWnd : HWND ; wParam : WPARAM ; lParam : LPARAM ); cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_DevSetMessageRemoved'{$endif};
{$endif MSWINDOWS}
function DevTrGetInputCount( hDevice : TLibTiePieHandle ) : Word; cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_DevTrGetInputCount'{$endif};
function DevTrGetInputIndexById( hDevice : TLibTiePieHandle ; dwId : LongWord ) : Word; cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_DevTrGetInputIndexById'{$endif};
function ScpTrInIsTriggered( hDevice : TLibTiePieHandle ; wInput : Word ) : ByteBool; cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_ScpTrInIsTriggered'{$endif};
function DevTrInGetEnabled( hDevice : TLibTiePieHandle ; wInput : Word ) : ByteBool; cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_DevTrInGetEnabled'{$endif};
function DevTrInSetEnabled( hDevice : TLibTiePieHandle ; wInput : Word ; bEnable : ByteBool ) : ByteBool; cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_DevTrInSetEnabled'{$endif};
function DevTrInGetKinds( hDevice : TLibTiePieHandle ; wInput : Word ) : UInt64; cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_DevTrInGetKinds'{$endif};
function ScpTrInGetKindsEx( hDevice : TLibTiePieHandle ; wInput : Word ; dwMeasureMode : LongWord ) : UInt64; cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_ScpTrInGetKindsEx'{$endif};
function DevTrInGetKind( hDevice : TLibTiePieHandle ; wInput : Word ) : UInt64; cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_DevTrInGetKind'{$endif};
function DevTrInSetKind( hDevice : TLibTiePieHandle ; wInput : Word ; qwKind : UInt64 ) : UInt64; cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_DevTrInSetKind'{$endif};
function DevTrInIsAvailable( hDevice : TLibTiePieHandle ; wInput : Word ) : ByteBool; cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_DevTrInIsAvailable'{$endif};
function ScpTrInIsAvailableEx( hDevice : TLibTiePieHandle ; wInput : Word ; dwMeasureMode : LongWord ) : ByteBool; cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_ScpTrInIsAvailableEx'{$endif};
function DevTrInGetId( hDevice : TLibTiePieHandle ; wInput : Word ) : LongWord; cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_DevTrInGetId'{$endif};
function DevTrInGetName( hDevice : TLibTiePieHandle ; wInput : Word ; pBuffer : PAnsiChar ; dwBufferLength : LongWord ) : LongWord; cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_DevTrInGetName'{$endif};
function DevTrGetOutputCount( hDevice : TLibTiePieHandle ) : Word; cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_DevTrGetOutputCount'{$endif};
function DevTrGetOutputIndexById( hDevice : TLibTiePieHandle ; dwId : LongWord ) : Word; cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_DevTrGetOutputIndexById'{$endif};
function DevTrOutGetEnabled( hDevice : TLibTiePieHandle ; wOutput : Word ) : ByteBool; cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_DevTrOutGetEnabled'{$endif};
function DevTrOutSetEnabled( hDevice : TLibTiePieHandle ; wOutput : Word ; bEnable : ByteBool ) : ByteBool; cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_DevTrOutSetEnabled'{$endif};
function DevTrOutGetEvents( hDevice : TLibTiePieHandle ; wOutput : Word ) : UInt64; cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_DevTrOutGetEvents'{$endif};
function DevTrOutGetEvent( hDevice : TLibTiePieHandle ; wOutput : Word ) : UInt64; cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_DevTrOutGetEvent'{$endif};
function DevTrOutSetEvent( hDevice : TLibTiePieHandle ; wOutput : Word ; qwEvent : UInt64 ) : UInt64; cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_DevTrOutSetEvent'{$endif};
function DevTrOutGetId( hDevice : TLibTiePieHandle ; wOutput : Word ) : LongWord; cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_DevTrOutGetId'{$endif};
function DevTrOutGetName( hDevice : TLibTiePieHandle ; wOutput : Word ; pBuffer : PAnsiChar ; dwBufferLength : LongWord ) : LongWord; cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_DevTrOutGetName'{$endif};
function DevTrOutTrigger( hDevice : TLibTiePieHandle ; wOutput : Word ) : ByteBool; cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_DevTrOutTrigger'{$endif};
function ScpGetChannelCount( hDevice : TLibTiePieHandle ) : Word; cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_ScpGetChannelCount'{$endif};
function ScpChIsAvailable( hDevice : TLibTiePieHandle ; wCh : Word ) : ByteBool; cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_ScpChIsAvailable'{$endif};
function ScpChIsAvailableEx( hDevice : TLibTiePieHandle ; wCh : Word ; dwMeasureMode : LongWord ; dSampleFrequency : Double ; byResolution : Byte ; pChannelEnabled : PByteBool ; wChannelCount : Word ) : ByteBool; cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_ScpChIsAvailableEx'{$endif};
function ScpChGetConnectorType( hDevice : TLibTiePieHandle ; wCh : Word ) : LongWord; cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_ScpChGetConnectorType'{$endif};
function ScpChIsDifferential( hDevice : TLibTiePieHandle ; wCh : Word ) : ByteBool; cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_ScpChIsDifferential'{$endif};
function ScpChGetImpedance( hDevice : TLibTiePieHandle ; wCh : Word ) : Double; cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_ScpChGetImpedance'{$endif};
function ScpChGetBandwidths( hDevice : TLibTiePieHandle ; wCh : Word ; pList : PDouble ; dwLength : LongWord ) : LongWord; cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_ScpChGetBandwidths'{$endif};
function ScpChGetBandwidth( hDevice : TLibTiePieHandle ; wCh : Word ) : Double; cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_ScpChGetBandwidth'{$endif};
function ScpChSetBandwidth( hDevice : TLibTiePieHandle ; wCh : Word ; dBandwidth : Double ) : Double; cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_ScpChSetBandwidth'{$endif};
function ScpChGetCouplings( hDevice : TLibTiePieHandle ; wCh : Word ) : UInt64; cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_ScpChGetCouplings'{$endif};
function ScpChGetCoupling( hDevice : TLibTiePieHandle ; wCh : Word ) : UInt64; cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_ScpChGetCoupling'{$endif};
function ScpChSetCoupling( hDevice : TLibTiePieHandle ; wCh : Word ; qwCoupling : UInt64 ) : UInt64; cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_ScpChSetCoupling'{$endif};
function ScpChGetEnabled( hDevice : TLibTiePieHandle ; wCh : Word ) : ByteBool; cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_ScpChGetEnabled'{$endif};
function ScpChSetEnabled( hDevice : TLibTiePieHandle ; wCh : Word ; bEnable : ByteBool ) : ByteBool; cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_ScpChSetEnabled'{$endif};
function ScpChGetProbeGain( hDevice : TLibTiePieHandle ; wCh : Word ) : Double; cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_ScpChGetProbeGain'{$endif};
function ScpChSetProbeGain( hDevice : TLibTiePieHandle ; wCh : Word ; dProbeGain : Double ) : Double; cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_ScpChSetProbeGain'{$endif};
function ScpChGetProbeOffset( hDevice : TLibTiePieHandle ; wCh : Word ) : Double; cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_ScpChGetProbeOffset'{$endif};
function ScpChSetProbeOffset( hDevice : TLibTiePieHandle ; wCh : Word ; dProbeOffset : Double ) : Double; cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_ScpChSetProbeOffset'{$endif};
function ScpChGetAutoRanging( hDevice : TLibTiePieHandle ; wCh : Word ) : ByteBool; cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_ScpChGetAutoRanging'{$endif};
function ScpChSetAutoRanging( hDevice : TLibTiePieHandle ; wCh : Word ; bEnable : ByteBool ) : ByteBool; cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_ScpChSetAutoRanging'{$endif};
function ScpChGetRanges( hDevice : TLibTiePieHandle ; wCh : Word ; pList : PDouble ; dwLength : LongWord ) : LongWord; cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_ScpChGetRanges'{$endif};
function ScpChGetRangesEx( hDevice : TLibTiePieHandle ; wCh : Word ; qwCoupling : UInt64 ; pList : PDouble ; dwLength : LongWord ) : LongWord; cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_ScpChGetRangesEx'{$endif};
function ScpChGetRange( hDevice : TLibTiePieHandle ; wCh : Word ) : Double; cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_ScpChGetRange'{$endif};
function ScpChSetRange( hDevice : TLibTiePieHandle ; wCh : Word ; dRange : Double ) : Double; cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_ScpChSetRange'{$endif};
function ScpChHasSafeGround( hDevice : TLibTiePieHandle ; wCh : Word ) : ByteBool; cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_ScpChHasSafeGround'{$endif};
function ScpChGetSafeGroundEnabled( hDevice : TLibTiePieHandle ; wCh : Word ) : ByteBool; cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_ScpChGetSafeGroundEnabled'{$endif};
function ScpChSetSafeGroundEnabled( hDevice : TLibTiePieHandle ; wCh : Word ; bEnable : ByteBool ) : ByteBool; cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_ScpChSetSafeGroundEnabled'{$endif};
function ScpChGetSafeGroundThresholdMin( hDevice : TLibTiePieHandle ; wCh : Word ) : Double; cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_ScpChGetSafeGroundThresholdMin'{$endif};
function ScpChGetSafeGroundThresholdMax( hDevice : TLibTiePieHandle ; wCh : Word ) : Double; cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_ScpChGetSafeGroundThresholdMax'{$endif};
function ScpChGetSafeGroundThreshold( hDevice : TLibTiePieHandle ; wCh : Word ) : Double; cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_ScpChGetSafeGroundThreshold'{$endif};
function ScpChSetSafeGroundThreshold( hDevice : TLibTiePieHandle ; wCh : Word ; dThreshold : Double ) : Double; cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_ScpChSetSafeGroundThreshold'{$endif};
function ScpChVerifySafeGroundThreshold( hDevice : TLibTiePieHandle ; wCh : Word ; dThreshold : Double ) : Double; cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_ScpChVerifySafeGroundThreshold'{$endif};
function ScpChHasTrigger( hDevice : TLibTiePieHandle ; wCh : Word ) : ByteBool; cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_ScpChHasTrigger'{$endif};
function ScpChHasTriggerEx( hDevice : TLibTiePieHandle ; wCh : Word ; dwMeasureMode : LongWord ) : ByteBool; cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_ScpChHasTriggerEx'{$endif};
function ScpChTrIsAvailable( hDevice : TLibTiePieHandle ; wCh : Word ) : ByteBool; cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_ScpChTrIsAvailable'{$endif};
function ScpChTrIsAvailableEx( hDevice : TLibTiePieHandle ; wCh : Word ; dwMeasureMode : LongWord ; dSampleFrequency : Double ; byResolution : Byte ; pChannelEnabled , pChannelTriggerEnabled : PByteBool ; wChannelCount : Word ) : ByteBool; cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_ScpChTrIsAvailableEx'{$endif};
function ScpChTrIsTriggered( hDevice : TLibTiePieHandle ; wCh : Word ) : ByteBool; cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_ScpChTrIsTriggered'{$endif};
function ScpChTrGetEnabled( hDevice : TLibTiePieHandle ; wCh : Word ) : ByteBool; cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_ScpChTrGetEnabled'{$endif};
function ScpChTrSetEnabled( hDevice : TLibTiePieHandle ; wCh : Word ; bEnable : ByteBool ) : ByteBool; cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_ScpChTrSetEnabled'{$endif};
function ScpChTrGetKinds( hDevice : TLibTiePieHandle ; wCh : Word ) : UInt64; cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_ScpChTrGetKinds'{$endif};
function ScpChTrGetKindsEx( hDevice : TLibTiePieHandle ; wCh : Word ; dwMeasureMode : LongWord ) : UInt64; cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_ScpChTrGetKindsEx'{$endif};
function ScpChTrGetKind( hDevice : TLibTiePieHandle ; wCh : Word ) : UInt64; cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_ScpChTrGetKind'{$endif};
function ScpChTrSetKind( hDevice : TLibTiePieHandle ; wCh : Word ; qwTriggerKind : UInt64 ) : UInt64; cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_ScpChTrSetKind'{$endif};
function ScpChTrGetLevelModes( hDevice : TLibTiePieHandle ; wCh : Word ) : LongWord; cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_ScpChTrGetLevelModes'{$endif};
function ScpChTrGetLevelMode( hDevice : TLibTiePieHandle ; wCh : Word ) : LongWord; cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_ScpChTrGetLevelMode'{$endif};
function ScpChTrSetLevelMode( hDevice : TLibTiePieHandle ; wCh : Word ; dwLevelMode : LongWord ) : LongWord; cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_ScpChTrSetLevelMode'{$endif};
function ScpChTrGetLevelCount( hDevice : TLibTiePieHandle ; wCh : Word ) : LongWord; cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_ScpChTrGetLevelCount'{$endif};
function ScpChTrGetLevel( hDevice : TLibTiePieHandle ; wCh : Word ; dwIndex : LongWord ) : Double; cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_ScpChTrGetLevel'{$endif};
function ScpChTrSetLevel( hDevice : TLibTiePieHandle ; wCh : Word ; dwIndex : LongWord ; dLevel : Double ) : Double; cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_ScpChTrSetLevel'{$endif};
function ScpChTrGetHysteresisCount( hDevice : TLibTiePieHandle ; wCh : Word ) : LongWord; cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_ScpChTrGetHysteresisCount'{$endif};
function ScpChTrGetHysteresis( hDevice : TLibTiePieHandle ; wCh : Word ; dwIndex : LongWord ) : Double; cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_ScpChTrGetHysteresis'{$endif};
function ScpChTrSetHysteresis( hDevice : TLibTiePieHandle ; wCh : Word ; dwIndex : LongWord ; dHysteresis : Double ) : Double; cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_ScpChTrSetHysteresis'{$endif};
function ScpChTrGetConditions( hDevice : TLibTiePieHandle ; wCh : Word ) : LongWord; cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_ScpChTrGetConditions'{$endif};
function ScpChTrGetConditionsEx( hDevice : TLibTiePieHandle ; wCh : Word ; dwMeasureMode : LongWord ; qwTriggerKind : UInt64 ) : LongWord; cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_ScpChTrGetConditionsEx'{$endif};
function ScpChTrGetCondition( hDevice : TLibTiePieHandle ; wCh : Word ) : LongWord; cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_ScpChTrGetCondition'{$endif};
function ScpChTrSetCondition( hDevice : TLibTiePieHandle ; wCh : Word ; dwCondition : LongWord ) : LongWord; cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_ScpChTrSetCondition'{$endif};
function ScpChTrGetTimeCount( hDevice : TLibTiePieHandle ; wCh : Word ) : LongWord; cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_ScpChTrGetTimeCount'{$endif};
function ScpChTrGetTime( hDevice : TLibTiePieHandle ; wCh : Word ; dwIndex : LongWord ) : Double; cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_ScpChTrGetTime'{$endif};
function ScpChTrSetTime( hDevice : TLibTiePieHandle ; wCh : Word ; dwIndex : LongWord ; dTime : Double ) : Double; cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_ScpChTrSetTime'{$endif};
function ScpChTrVerifyTime( hDevice : TLibTiePieHandle ; wCh : Word ; dwIndex : LongWord ; dTime : Double ) : Double; cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_ScpChTrVerifyTime'{$endif};
function ScpChTrVerifyTimeEx2( hDevice : TLibTiePieHandle ; wCh : Word ; dwIndex : LongWord ; dTime : Double ; dwMeasureMode : LongWord ; dSampleFrequency : Double ; qwTriggerKind : UInt64 ; dwCondition : LongWord ) : Double; cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_ScpChTrVerifyTimeEx2'{$endif};
function ScpGetData( hDevice : TLibTiePieHandle ; pBuffers : PPSingle ; wChannelCount : Word ; qwStartIndex , qwSampleCount : UInt64 ) : UInt64; cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_ScpGetData'{$endif};
function ScpGetData1Ch( hDevice : TLibTiePieHandle ; pBufferCh1 : PSingle ; qwStartIndex , qwSampleCount : UInt64 ) : UInt64; cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_ScpGetData1Ch'{$endif};
function ScpGetData2Ch( hDevice : TLibTiePieHandle ; pBufferCh1 , pBufferCh2 : PSingle ; qwStartIndex , qwSampleCount : UInt64 ) : UInt64; cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_ScpGetData2Ch'{$endif};
function ScpGetData3Ch( hDevice : TLibTiePieHandle ; pBufferCh1 , pBufferCh2 , pBufferCh3 : PSingle ; qwStartIndex , qwSampleCount : UInt64 ) : UInt64; cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_ScpGetData3Ch'{$endif};
function ScpGetData4Ch( hDevice : TLibTiePieHandle ; pBufferCh1 , pBufferCh2 , pBufferCh3 , pBufferCh4 : PSingle ; qwStartIndex , qwSampleCount : UInt64 ) : UInt64; cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_ScpGetData4Ch'{$endif};
function ScpGetData5Ch( hDevice : TLibTiePieHandle ; pBufferCh1 , pBufferCh2 , pBufferCh3 , pBufferCh4 , pBufferCh5 : PSingle ; qwStartIndex , qwSampleCount : UInt64 ) : UInt64; cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_ScpGetData5Ch'{$endif};
function ScpGetData6Ch( hDevice : TLibTiePieHandle ; pBufferCh1 , pBufferCh2 , pBufferCh3 , pBufferCh4 , pBufferCh5 , pBufferCh6 : PSingle ; qwStartIndex , qwSampleCount : UInt64 ) : UInt64; cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_ScpGetData6Ch'{$endif};
function ScpGetData7Ch( hDevice : TLibTiePieHandle ; pBufferCh1 , pBufferCh2 , pBufferCh3 , pBufferCh4 , pBufferCh5 , pBufferCh6 , pBufferCh7 : PSingle ; qwStartIndex , qwSampleCount : UInt64 ) : UInt64; cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_ScpGetData7Ch'{$endif};
function ScpGetData8Ch( hDevice : TLibTiePieHandle ; pBufferCh1 , pBufferCh2 , pBufferCh3 , pBufferCh4 , pBufferCh5 , pBufferCh6 , pBufferCh7 , pBufferCh8 : PSingle ; qwStartIndex , qwSampleCount : UInt64 ) : UInt64; cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_ScpGetData8Ch'{$endif};
function ScpGetValidPreSampleCount( hDevice : TLibTiePieHandle ) : UInt64; cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_ScpGetValidPreSampleCount'{$endif};
procedure ScpChGetDataValueRange( hDevice : TLibTiePieHandle ; wCh : Word ; pMin , pMax : PDouble ); cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_ScpChGetDataValueRange'{$endif};
function ScpChGetDataValueMin( hDevice : TLibTiePieHandle ; wCh : Word ) : Double; cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_ScpChGetDataValueMin'{$endif};
function ScpChGetDataValueMax( hDevice : TLibTiePieHandle ; wCh : Word ) : Double; cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_ScpChGetDataValueMax'{$endif};
function ScpGetDataRaw( hDevice : TLibTiePieHandle ; pBuffers : PPointer ; wChannelCount : Word ; qwStartIndex , qwSampleCount : UInt64 ) : UInt64; cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_ScpGetDataRaw'{$endif};
function ScpGetDataRaw1Ch( hDevice : TLibTiePieHandle ; pBufferCh1 : Pointer ; qwStartIndex , qwSampleCount : UInt64 ) : UInt64; cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_ScpGetDataRaw1Ch'{$endif};
function ScpGetDataRaw2Ch( hDevice : TLibTiePieHandle ; pBufferCh1 , pBufferCh2 : Pointer ; qwStartIndex , qwSampleCount : UInt64 ) : UInt64; cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_ScpGetDataRaw2Ch'{$endif};
function ScpGetDataRaw3Ch( hDevice : TLibTiePieHandle ; pBufferCh1 , pBufferCh2 , pBufferCh3 : Pointer ; qwStartIndex , qwSampleCount : UInt64 ) : UInt64; cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_ScpGetDataRaw3Ch'{$endif};
function ScpGetDataRaw4Ch( hDevice : TLibTiePieHandle ; pBufferCh1 , pBufferCh2 , pBufferCh3 , pBufferCh4 : Pointer ; qwStartIndex , qwSampleCount : UInt64 ) : UInt64; cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_ScpGetDataRaw4Ch'{$endif};
function ScpGetDataRaw5Ch( hDevice : TLibTiePieHandle ; pBufferCh1 , pBufferCh2 , pBufferCh3 , pBufferCh4 , pBufferCh5 : Pointer ; qwStartIndex , qwSampleCount : UInt64 ) : UInt64; cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_ScpGetDataRaw5Ch'{$endif};
function ScpGetDataRaw6Ch( hDevice : TLibTiePieHandle ; pBufferCh1 , pBufferCh2 , pBufferCh3 , pBufferCh4 , pBufferCh5 , pBufferCh6 : Pointer ; qwStartIndex , qwSampleCount : UInt64 ) : UInt64; cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_ScpGetDataRaw6Ch'{$endif};
function ScpGetDataRaw7Ch( hDevice : TLibTiePieHandle ; pBufferCh1 , pBufferCh2 , pBufferCh3 , pBufferCh4 , pBufferCh5 , pBufferCh6 , pBufferCh7 : Pointer ; qwStartIndex , qwSampleCount : UInt64 ) : UInt64; cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_ScpGetDataRaw7Ch'{$endif};
function ScpGetDataRaw8Ch( hDevice : TLibTiePieHandle ; pBufferCh1 , pBufferCh2 , pBufferCh3 , pBufferCh4 , pBufferCh5 , pBufferCh6 , pBufferCh7 , pBufferCh8 : Pointer ; qwStartIndex , qwSampleCount : UInt64 ) : UInt64; cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_ScpGetDataRaw8Ch'{$endif};
function ScpChGetDataRawType( hDevice : TLibTiePieHandle ; wCh : Word ) : LongWord; cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_ScpChGetDataRawType'{$endif};
procedure ScpChGetDataRawValueRange( hDevice : TLibTiePieHandle ; wCh : Word ; pMin , pZero , pMax : PInt64 ); cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_ScpChGetDataRawValueRange'{$endif};
function ScpChGetDataRawValueMin( hDevice : TLibTiePieHandle ; wCh : Word ) : Int64; cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_ScpChGetDataRawValueMin'{$endif};
function ScpChGetDataRawValueZero( hDevice : TLibTiePieHandle ; wCh : Word ) : Int64; cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_ScpChGetDataRawValueZero'{$endif};
function ScpChGetDataRawValueMax( hDevice : TLibTiePieHandle ; wCh : Word ) : Int64; cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_ScpChGetDataRawValueMax'{$endif};
function ScpChIsRangeMaxReachable( hDevice : TLibTiePieHandle ; wCh : Word ) : ByteBool; cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_ScpChIsRangeMaxReachable'{$endif};
function ScpIsGetDataAsyncCompleted( hDevice : TLibTiePieHandle ) : ByteBool; cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_ScpIsGetDataAsyncCompleted'{$endif};
function ScpStartGetDataAsync( hDevice : TLibTiePieHandle ; pBuffers : PPSingle ; wChannelCount : Word ; qwStartIndex , qwSampleCount : UInt64 ) : ByteBool; cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_ScpStartGetDataAsync'{$endif};
function ScpStartGetDataAsyncRaw( hDevice : TLibTiePieHandle ; pBuffers : PPointer ; wChannelCount : Word ; qwStartIndex , qwSampleCount : UInt64 ) : ByteBool; cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_ScpStartGetDataAsyncRaw'{$endif};
function ScpCancelGetDataAsync( hDevice : TLibTiePieHandle ) : ByteBool; cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_ScpCancelGetDataAsync'{$endif};
procedure ScpSetCallbackDataReady( hDevice : TLibTiePieHandle ; pCallback : TTpCallback ; pData : Pointer ); cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_ScpSetCallbackDataReady'{$endif};
procedure ScpSetCallbackDataOverflow( hDevice : TLibTiePieHandle ; pCallback : TTpCallback ; pData : Pointer ); cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_ScpSetCallbackDataOverflow'{$endif};
procedure ScpSetCallbackConnectionTestCompleted( hDevice : TLibTiePieHandle ; pCallback : TTpCallback ; pData : Pointer ); cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_ScpSetCallbackConnectionTestCompleted'{$endif};
procedure ScpSetCallbackTriggered( hDevice : TLibTiePieHandle ; pCallback : TTpCallback ; pData : Pointer ); cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_ScpSetCallbackTriggered'{$endif};
{$ifdef LINUX}
procedure ScpSetEventDataReady( hDevice : TLibTiePieHandle ; fdEvent : Integer ); cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_ScpSetEventDataReady'{$endif};
procedure ScpSetEventDataOverflow( hDevice : TLibTiePieHandle ; fdEvent : Integer ); cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_ScpSetEventDataOverflow'{$endif};
procedure ScpSetEventConnectionTestCompleted( hDevice : TLibTiePieHandle ; fdEvent : Integer ); cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_ScpSetEventConnectionTestCompleted'{$endif};
procedure ScpSetEventTriggered( hDevice : TLibTiePieHandle ; fdEvent : Integer ); cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_ScpSetEventTriggered'{$endif};
{$endif LINUX}
{$ifdef MSWINDOWS}
procedure ScpSetEventDataReady( hDevice : TLibTiePieHandle ; hEvent : THandle ); cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_ScpSetEventDataReady'{$endif};
procedure ScpSetEventDataOverflow( hDevice : TLibTiePieHandle ; hEvent : THandle ); cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_ScpSetEventDataOverflow'{$endif};
procedure ScpSetEventConnectionTestCompleted( hDevice : TLibTiePieHandle ; hEvent : THandle ); cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_ScpSetEventConnectionTestCompleted'{$endif};
procedure ScpSetEventTriggered( hDevice : TLibTiePieHandle ; hEvent : THandle ); cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_ScpSetEventTriggered'{$endif};
procedure ScpSetMessageDataReady( hDevice : TLibTiePieHandle ; hWnd : HWND ; wParam : WPARAM ; lParam : LPARAM ); cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_ScpSetMessageDataReady'{$endif};
procedure ScpSetMessageDataOverflow( hDevice : TLibTiePieHandle ; hWnd : HWND ; wParam : WPARAM ; lParam : LPARAM ); cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_ScpSetMessageDataOverflow'{$endif};
procedure ScpSetMessageConnectionTestCompleted( hDevice : TLibTiePieHandle ; hWnd : HWND ; wParam : WPARAM ; lParam : LPARAM ); cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_ScpSetMessageConnectionTestCompleted'{$endif};
procedure ScpSetMessageTriggered( hDevice : TLibTiePieHandle ; hWnd : HWND ; wParam : WPARAM ; lParam : LPARAM ); cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_ScpSetMessageTriggered'{$endif};
{$endif MSWINDOWS}
function ScpStart( hDevice : TLibTiePieHandle ) : ByteBool; cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_ScpStart'{$endif};
function ScpStop( hDevice : TLibTiePieHandle ) : ByteBool; cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_ScpStop'{$endif};
function ScpForceTrigger( hDevice : TLibTiePieHandle ) : ByteBool; cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_ScpForceTrigger'{$endif};
function ScpGetMeasureModes( hDevice : TLibTiePieHandle ) : LongWord; cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_ScpGetMeasureModes'{$endif};
function ScpGetMeasureMode( hDevice : TLibTiePieHandle ) : LongWord; cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_ScpGetMeasureMode'{$endif};
function ScpSetMeasureMode( hDevice : TLibTiePieHandle ; dwMeasureMode : LongWord ) : LongWord; cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_ScpSetMeasureMode'{$endif};
function ScpIsRunning( hDevice : TLibTiePieHandle ) : ByteBool; cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_ScpIsRunning'{$endif};
function ScpIsTriggered( hDevice : TLibTiePieHandle ) : ByteBool; cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_ScpIsTriggered'{$endif};
function ScpIsTimeOutTriggered( hDevice : TLibTiePieHandle ) : ByteBool; cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_ScpIsTimeOutTriggered'{$endif};
function ScpIsForceTriggered( hDevice : TLibTiePieHandle ) : ByteBool; cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_ScpIsForceTriggered'{$endif};
function ScpIsDataReady( hDevice : TLibTiePieHandle ) : ByteBool; cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_ScpIsDataReady'{$endif};
function ScpIsDataOverflow( hDevice : TLibTiePieHandle ) : ByteBool; cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_ScpIsDataOverflow'{$endif};
function ScpGetAutoResolutionModes( hDevice : TLibTiePieHandle ) : LongWord; cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_ScpGetAutoResolutionModes'{$endif};
function ScpGetAutoResolutionMode( hDevice : TLibTiePieHandle ) : LongWord; cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_ScpGetAutoResolutionMode'{$endif};
function ScpSetAutoResolutionMode( hDevice : TLibTiePieHandle ; dwAutoResolutionMode : LongWord ) : LongWord; cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_ScpSetAutoResolutionMode'{$endif};
function ScpGetResolutions( hDevice : TLibTiePieHandle ; pList : PByte ; dwLength : LongWord ) : LongWord; cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_ScpGetResolutions'{$endif};
function ScpGetResolution( hDevice : TLibTiePieHandle ) : Byte; cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_ScpGetResolution'{$endif};
function ScpSetResolution( hDevice : TLibTiePieHandle ; byResolution : Byte ) : Byte; cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_ScpSetResolution'{$endif};
function ScpIsResolutionEnhanced( hDevice : TLibTiePieHandle ) : ByteBool; cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_ScpIsResolutionEnhanced'{$endif};
function ScpIsResolutionEnhancedEx( hDevice : TLibTiePieHandle ; byResolution : Byte ) : ByteBool; cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_ScpIsResolutionEnhancedEx'{$endif};
function ScpGetClockSources( hDevice : TLibTiePieHandle ) : LongWord; cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_ScpGetClockSources'{$endif};
function ScpGetClockSource( hDevice : TLibTiePieHandle ) : LongWord; cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_ScpGetClockSource'{$endif};
function ScpSetClockSource( hDevice : TLibTiePieHandle ; dwClockSource : LongWord ) : LongWord; cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_ScpSetClockSource'{$endif};
function ScpGetClockSourceFrequencies( hDevice : TLibTiePieHandle ; pList : PDouble ; dwLength : LongWord ) : LongWord; cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_ScpGetClockSourceFrequencies'{$endif};
function ScpGetClockSourceFrequenciesEx( hDevice : TLibTiePieHandle ; dwClockSource : LongWord ; pList : PDouble ; dwLength : LongWord ) : LongWord; cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_ScpGetClockSourceFrequenciesEx'{$endif};
function ScpGetClockSourceFrequency( hDevice : TLibTiePieHandle ) : Double; cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_ScpGetClockSourceFrequency'{$endif};
function ScpSetClockSourceFrequency( hDevice : TLibTiePieHandle ; dClockSourceFrequency : Double ) : Double; cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_ScpSetClockSourceFrequency'{$endif};
function ScpGetClockOutputs( hDevice : TLibTiePieHandle ) : LongWord; cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_ScpGetClockOutputs'{$endif};
function ScpGetClockOutput( hDevice : TLibTiePieHandle ) : LongWord; cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_ScpGetClockOutput'{$endif};
function ScpSetClockOutput( hDevice : TLibTiePieHandle ; dwClockOutput : LongWord ) : LongWord; cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_ScpSetClockOutput'{$endif};
function ScpGetClockOutputFrequencies( hDevice : TLibTiePieHandle ; pList : PDouble ; dwLength : LongWord ) : LongWord; cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_ScpGetClockOutputFrequencies'{$endif};
function ScpGetClockOutputFrequenciesEx( hDevice : TLibTiePieHandle ; dwClockOutput : LongWord ; pList : PDouble ; dwLength : LongWord ) : LongWord; cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_ScpGetClockOutputFrequenciesEx'{$endif};
function ScpGetClockOutputFrequency( hDevice : TLibTiePieHandle ) : Double; cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_ScpGetClockOutputFrequency'{$endif};
function ScpSetClockOutputFrequency( hDevice : TLibTiePieHandle ; dClockOutputFrequency : Double ) : Double; cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_ScpSetClockOutputFrequency'{$endif};
function ScpGetSampleFrequencyMax( hDevice : TLibTiePieHandle ) : Double; cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_ScpGetSampleFrequencyMax'{$endif};
function ScpGetSampleFrequency( hDevice : TLibTiePieHandle ) : Double; cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_ScpGetSampleFrequency'{$endif};
function ScpSetSampleFrequency( hDevice : TLibTiePieHandle ; dSampleFrequency : Double ) : Double; cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_ScpSetSampleFrequency'{$endif};
function ScpVerifySampleFrequency( hDevice : TLibTiePieHandle ; dSampleFrequency : Double ) : Double; cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_ScpVerifySampleFrequency'{$endif};
function ScpVerifySampleFrequencyEx( hDevice : TLibTiePieHandle ; dSampleFrequency : Double ; dwMeasureMode : LongWord ; byResolution : Byte ; pChannelEnabled : PByteBool ; wChannelCount : Word ) : Double; cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_ScpVerifySampleFrequencyEx'{$endif};
procedure ScpVerifySampleFrequenciesEx( hDevice : TLibTiePieHandle ; pSampleFrequencies : PDouble ; dwSampleFrequencyCount , dwMeasureMode , dwAutoResolutionMode : LongWord ; byResolution : Byte ; pChannelEnabled : PByteBool ; wChannelCount : Word ); cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_ScpVerifySampleFrequenciesEx'{$endif};
function ScpGetRecordLengthMax( hDevice : TLibTiePieHandle ) : UInt64; cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_ScpGetRecordLengthMax'{$endif};
function ScpGetRecordLengthMaxEx( hDevice : TLibTiePieHandle ; dwMeasureMode : LongWord ; byResolution : Byte ) : UInt64; cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_ScpGetRecordLengthMaxEx'{$endif};
function ScpGetRecordLength( hDevice : TLibTiePieHandle ) : UInt64; cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_ScpGetRecordLength'{$endif};
function ScpSetRecordLength( hDevice : TLibTiePieHandle ; qwRecordLength : UInt64 ) : UInt64; cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_ScpSetRecordLength'{$endif};
function ScpVerifyRecordLength( hDevice : TLibTiePieHandle ; qwRecordLength : UInt64 ) : UInt64; cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_ScpVerifyRecordLength'{$endif};
function ScpVerifyRecordLengthEx( hDevice : TLibTiePieHandle ; qwRecordLength : UInt64 ; dwMeasureMode : LongWord ; byResolution : Byte ; pChannelEnabled : PByteBool ; wChannelCount : Word ) : UInt64; cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_ScpVerifyRecordLengthEx'{$endif};
function ScpGetPreSampleRatio( hDevice : TLibTiePieHandle ) : Double; cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_ScpGetPreSampleRatio'{$endif};
function ScpSetPreSampleRatio( hDevice : TLibTiePieHandle ; dPreSampleRatio : Double ) : Double; cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_ScpSetPreSampleRatio'{$endif};
function ScpGetSegmentCountMax( hDevice : TLibTiePieHandle ) : LongWord; cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_ScpGetSegmentCountMax'{$endif};
function ScpGetSegmentCountMaxEx( hDevice : TLibTiePieHandle ; dwMeasureMode : LongWord ) : LongWord; cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_ScpGetSegmentCountMaxEx'{$endif};
function ScpGetSegmentCount( hDevice : TLibTiePieHandle ) : LongWord; cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_ScpGetSegmentCount'{$endif};
function ScpSetSegmentCount( hDevice : TLibTiePieHandle ; dwSegmentCount : LongWord ) : LongWord; cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_ScpSetSegmentCount'{$endif};
function ScpVerifySegmentCount( hDevice : TLibTiePieHandle ; dwSegmentCount : LongWord ) : LongWord; cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_ScpVerifySegmentCount'{$endif};
function ScpVerifySegmentCountEx2( hDevice : TLibTiePieHandle ; dwSegmentCount , dwMeasureMode : LongWord ; qwRecordLength : UInt64 ; pChannelEnabled : PByteBool ; wChannelCount : Word ) : LongWord; cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_ScpVerifySegmentCountEx2'{$endif};
function ScpHasTrigger( hDevice : TLibTiePieHandle ) : ByteBool; cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_ScpHasTrigger'{$endif};
function ScpHasTriggerEx( hDevice : TLibTiePieHandle ; dwMeasureMode : LongWord ) : ByteBool; cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_ScpHasTriggerEx'{$endif};
function ScpGetTriggerTimeOut( hDevice : TLibTiePieHandle ) : Double; cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_ScpGetTriggerTimeOut'{$endif};
function ScpSetTriggerTimeOut( hDevice : TLibTiePieHandle ; dTimeOut : Double ) : Double; cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_ScpSetTriggerTimeOut'{$endif};
function ScpVerifyTriggerTimeOut( hDevice : TLibTiePieHandle ; dTimeOut : Double ) : Double; cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_ScpVerifyTriggerTimeOut'{$endif};
function ScpVerifyTriggerTimeOutEx( hDevice : TLibTiePieHandle ; dTimeOut : Double ; dwMeasureMode : LongWord ; dSampleFrequency : Double ) : Double; cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_ScpVerifyTriggerTimeOutEx'{$endif};
function ScpHasTriggerDelay( hDevice : TLibTiePieHandle ) : ByteBool; cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_ScpHasTriggerDelay'{$endif};
function ScpHasTriggerDelayEx( hDevice : TLibTiePieHandle ; dwMeasureMode : LongWord ) : ByteBool; cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_ScpHasTriggerDelayEx'{$endif};
function ScpGetTriggerDelayMax( hDevice : TLibTiePieHandle ) : Double; cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_ScpGetTriggerDelayMax'{$endif};
function ScpGetTriggerDelayMaxEx( hDevice : TLibTiePieHandle ; dwMeasureMode : LongWord ; dSampleFrequency : Double ) : Double; cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_ScpGetTriggerDelayMaxEx'{$endif};
function ScpGetTriggerDelay( hDevice : TLibTiePieHandle ) : Double; cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_ScpGetTriggerDelay'{$endif};
function ScpSetTriggerDelay( hDevice : TLibTiePieHandle ; dDelay : Double ) : Double; cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_ScpSetTriggerDelay'{$endif};
function ScpVerifyTriggerDelay( hDevice : TLibTiePieHandle ; dDelay : Double ) : Double; cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_ScpVerifyTriggerDelay'{$endif};
function ScpVerifyTriggerDelayEx( hDevice : TLibTiePieHandle ; dDelay : Double ; dwMeasureMode : LongWord ; dSampleFrequency : Double ) : Double; cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_ScpVerifyTriggerDelayEx'{$endif};
function ScpHasTriggerHoldOff( hDevice : TLibTiePieHandle ) : ByteBool; cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_ScpHasTriggerHoldOff'{$endif};
function ScpHasTriggerHoldOffEx( hDevice : TLibTiePieHandle ; dwMeasureMode : LongWord ) : ByteBool; cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_ScpHasTriggerHoldOffEx'{$endif};
function ScpGetTriggerHoldOffCountMax( hDevice : TLibTiePieHandle ) : UInt64; cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_ScpGetTriggerHoldOffCountMax'{$endif};
function ScpGetTriggerHoldOffCountMaxEx( hDevice : TLibTiePieHandle ; dwMeasureMode : LongWord ) : UInt64; cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_ScpGetTriggerHoldOffCountMaxEx'{$endif};
function ScpGetTriggerHoldOffCount( hDevice : TLibTiePieHandle ) : UInt64; cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_ScpGetTriggerHoldOffCount'{$endif};
function ScpSetTriggerHoldOffCount( hDevice : TLibTiePieHandle ; qwTriggerHoldOffCount : UInt64 ) : UInt64; cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_ScpSetTriggerHoldOffCount'{$endif};
function ScpHasConnectionTest( hDevice : TLibTiePieHandle ) : ByteBool; cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_ScpHasConnectionTest'{$endif};
function ScpChHasConnectionTest( hDevice : TLibTiePieHandle ; wCh : Word ) : ByteBool; cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_ScpChHasConnectionTest'{$endif};
function ScpStartConnectionTest( hDevice : TLibTiePieHandle ) : ByteBool; cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_ScpStartConnectionTest'{$endif};
function ScpStartConnectionTestEx( hDevice : TLibTiePieHandle ; pChannelEnabled : PByteBool ; wChannelCount : Word ) : ByteBool; cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_ScpStartConnectionTestEx'{$endif};
function ScpIsConnectionTestCompleted( hDevice : TLibTiePieHandle ) : ByteBool; cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_ScpIsConnectionTestCompleted'{$endif};
function ScpGetConnectionTestData( hDevice : TLibTiePieHandle ; pBuffer : PLibTiePieTriState ; wChannelCount : Word ) : Word; cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_ScpGetConnectionTestData'{$endif};
function GenGetConnectorType( hDevice : TLibTiePieHandle ) : LongWord; cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_GenGetConnectorType'{$endif};
function GenIsDifferential( hDevice : TLibTiePieHandle ) : ByteBool; cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_GenIsDifferential'{$endif};
function GenGetImpedance( hDevice : TLibTiePieHandle ) : Double; cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_GenGetImpedance'{$endif};
function GenGetResolution( hDevice : TLibTiePieHandle ) : Byte; cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_GenGetResolution'{$endif};
function GenGetOutputValueMin( hDevice : TLibTiePieHandle ) : Double; cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_GenGetOutputValueMin'{$endif};
function GenGetOutputValueMax( hDevice : TLibTiePieHandle ) : Double; cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_GenGetOutputValueMax'{$endif};
procedure GenGetOutputValueMinMax( hDevice : TLibTiePieHandle ; pMin , pMax : PDouble ); cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_GenGetOutputValueMinMax'{$endif};
function GenIsControllable( hDevice : TLibTiePieHandle ) : ByteBool; cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_GenIsControllable'{$endif};
function GenIsRunning( hDevice : TLibTiePieHandle ) : ByteBool; cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_GenIsRunning'{$endif};
function GenGetStatus( hDevice : TLibTiePieHandle ) : LongWord; cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_GenGetStatus'{$endif};
function GenGetOutputOn( hDevice : TLibTiePieHandle ) : ByteBool; cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_GenGetOutputOn'{$endif};
function GenSetOutputOn( hDevice : TLibTiePieHandle ; bOutputOn : ByteBool ) : ByteBool; cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_GenSetOutputOn'{$endif};
function GenHasOutputInvert( hDevice : TLibTiePieHandle ) : ByteBool; cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_GenHasOutputInvert'{$endif};
function GenGetOutputInvert( hDevice : TLibTiePieHandle ) : ByteBool; cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_GenGetOutputInvert'{$endif};
function GenSetOutputInvert( hDevice : TLibTiePieHandle ; bInvert : ByteBool ) : ByteBool; cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_GenSetOutputInvert'{$endif};
function GenStart( hDevice : TLibTiePieHandle ) : ByteBool; cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_GenStart'{$endif};
function GenStop( hDevice : TLibTiePieHandle ) : ByteBool; cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_GenStop'{$endif};
function GenGetSignalTypes( hDevice : TLibTiePieHandle ) : LongWord; cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_GenGetSignalTypes'{$endif};
function GenGetSignalType( hDevice : TLibTiePieHandle ) : LongWord; cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_GenGetSignalType'{$endif};
function GenSetSignalType( hDevice : TLibTiePieHandle ; dwSignalType : LongWord ) : LongWord; cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_GenSetSignalType'{$endif};
function GenHasAmplitude( hDevice : TLibTiePieHandle ) : ByteBool; cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_GenHasAmplitude'{$endif};
function GenHasAmplitudeEx( hDevice : TLibTiePieHandle ; dwSignalType : LongWord ) : ByteBool; cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_GenHasAmplitudeEx'{$endif};
function GenGetAmplitudeMin( hDevice : TLibTiePieHandle ) : Double; cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_GenGetAmplitudeMin'{$endif};
function GenGetAmplitudeMax( hDevice : TLibTiePieHandle ) : Double; cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_GenGetAmplitudeMax'{$endif};
procedure GenGetAmplitudeMinMaxEx( hDevice : TLibTiePieHandle ; dwSignalType : LongWord ; pMin , pMax : PDouble ); cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_GenGetAmplitudeMinMaxEx'{$endif};
function GenGetAmplitude( hDevice : TLibTiePieHandle ) : Double; cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_GenGetAmplitude'{$endif};
function GenSetAmplitude( hDevice : TLibTiePieHandle ; dAmplitude : Double ) : Double; cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_GenSetAmplitude'{$endif};
function GenVerifyAmplitude( hDevice : TLibTiePieHandle ; dAmplitude : Double ) : Double; cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_GenVerifyAmplitude'{$endif};
function GenVerifyAmplitudeEx( hDevice : TLibTiePieHandle ; dAmplitude : Double ; dwSignalType , dwAmplitudeRangeIndex : LongWord ; dOffset : Double ) : Double; cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_GenVerifyAmplitudeEx'{$endif};
function GenGetAmplitudeRanges( hDevice : TLibTiePieHandle ; pList : PDouble ; dwLength : LongWord ) : LongWord; cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_GenGetAmplitudeRanges'{$endif};
function GenGetAmplitudeRange( hDevice : TLibTiePieHandle ) : Double; cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_GenGetAmplitudeRange'{$endif};
function GenSetAmplitudeRange( hDevice : TLibTiePieHandle ; dRange : Double ) : Double; cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_GenSetAmplitudeRange'{$endif};
function GenGetAmplitudeAutoRanging( hDevice : TLibTiePieHandle ) : ByteBool; cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_GenGetAmplitudeAutoRanging'{$endif};
function GenSetAmplitudeAutoRanging( hDevice : TLibTiePieHandle ; bEnable : ByteBool ) : ByteBool; cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_GenSetAmplitudeAutoRanging'{$endif};
function GenHasOffset( hDevice : TLibTiePieHandle ) : ByteBool; cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_GenHasOffset'{$endif};
function GenHasOffsetEx( hDevice : TLibTiePieHandle ; dwSignalType : LongWord ) : ByteBool; cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_GenHasOffsetEx'{$endif};
function GenGetOffsetMin( hDevice : TLibTiePieHandle ) : Double; cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_GenGetOffsetMin'{$endif};
function GenGetOffsetMax( hDevice : TLibTiePieHandle ) : Double; cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_GenGetOffsetMax'{$endif};
procedure GenGetOffsetMinMaxEx( hDevice : TLibTiePieHandle ; dwSignalType : LongWord ; pMin , pMax : PDouble ); cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_GenGetOffsetMinMaxEx'{$endif};
function GenGetOffset( hDevice : TLibTiePieHandle ) : Double; cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_GenGetOffset'{$endif};
function GenSetOffset( hDevice : TLibTiePieHandle ; dOffset : Double ) : Double; cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_GenSetOffset'{$endif};
function GenVerifyOffset( hDevice : TLibTiePieHandle ; dOffset : Double ) : Double; cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_GenVerifyOffset'{$endif};
function GenVerifyOffsetEx( hDevice : TLibTiePieHandle ; dOffset : Double ; dwSignalType : LongWord ; dAmplitude : Double ) : Double; cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_GenVerifyOffsetEx'{$endif};
function GenGetFrequencyModes( hDevice : TLibTiePieHandle ) : LongWord; cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_GenGetFrequencyModes'{$endif};
function GenGetFrequencyModesEx( hDevice : TLibTiePieHandle ; dwSignalType : LongWord ) : LongWord; cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_GenGetFrequencyModesEx'{$endif};
function GenGetFrequencyMode( hDevice : TLibTiePieHandle ) : LongWord; cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_GenGetFrequencyMode'{$endif};
function GenSetFrequencyMode( hDevice : TLibTiePieHandle ; dwFrequencyMode : LongWord ) : LongWord; cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_GenSetFrequencyMode'{$endif};
function GenHasFrequency( hDevice : TLibTiePieHandle ) : ByteBool; cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_GenHasFrequency'{$endif};
function GenHasFrequencyEx( hDevice : TLibTiePieHandle ; dwFrequencyMode , dwSignalType : LongWord ) : ByteBool; cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_GenHasFrequencyEx'{$endif};
function GenGetFrequencyMin( hDevice : TLibTiePieHandle ) : Double; cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_GenGetFrequencyMin'{$endif};
function GenGetFrequencyMax( hDevice : TLibTiePieHandle ) : Double; cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_GenGetFrequencyMax'{$endif};
procedure GenGetFrequencyMinMax( hDevice : TLibTiePieHandle ; dwFrequencyMode : LongWord ; pMin , pMax : PDouble ); cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_GenGetFrequencyMinMax'{$endif};
procedure GenGetFrequencyMinMaxEx( hDevice : TLibTiePieHandle ; dwFrequencyMode , dwSignalType : LongWord ; pMin , pMax : PDouble ); cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_GenGetFrequencyMinMaxEx'{$endif};
function GenGetFrequency( hDevice : TLibTiePieHandle ) : Double; cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_GenGetFrequency'{$endif};
function GenSetFrequency( hDevice : TLibTiePieHandle ; dFrequency : Double ) : Double; cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_GenSetFrequency'{$endif};
function GenVerifyFrequency( hDevice : TLibTiePieHandle ; dFrequency : Double ) : Double; cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_GenVerifyFrequency'{$endif};
function GenVerifyFrequencyEx2( hDevice : TLibTiePieHandle ; dFrequency : Double ; dwFrequencyMode , dwSignalType : LongWord ; qwDataLength : UInt64 ; dWidth : Double ) : Double; cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_GenVerifyFrequencyEx2'{$endif};
function GenHasPhase( hDevice : TLibTiePieHandle ) : ByteBool; cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_GenHasPhase'{$endif};
function GenHasPhaseEx( hDevice : TLibTiePieHandle ; dwSignalType : LongWord ) : ByteBool; cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_GenHasPhaseEx'{$endif};
function GenGetPhaseMin( hDevice : TLibTiePieHandle ) : Double; cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_GenGetPhaseMin'{$endif};
function GenGetPhaseMax( hDevice : TLibTiePieHandle ) : Double; cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_GenGetPhaseMax'{$endif};
procedure GenGetPhaseMinMaxEx( hDevice : TLibTiePieHandle ; dwSignalType : LongWord ; pMin , pMax : PDouble ); cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_GenGetPhaseMinMaxEx'{$endif};
function GenGetPhase( hDevice : TLibTiePieHandle ) : Double; cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_GenGetPhase'{$endif};
function GenSetPhase( hDevice : TLibTiePieHandle ; dPhase : Double ) : Double; cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_GenSetPhase'{$endif};
function GenVerifyPhase( hDevice : TLibTiePieHandle ; dPhase : Double ) : Double; cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_GenVerifyPhase'{$endif};
function GenVerifyPhaseEx( hDevice : TLibTiePieHandle ; dPhase : Double ; dwSignalType : LongWord ) : Double; cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_GenVerifyPhaseEx'{$endif};
function GenHasSymmetry( hDevice : TLibTiePieHandle ) : ByteBool; cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_GenHasSymmetry'{$endif};
function GenHasSymmetryEx( hDevice : TLibTiePieHandle ; dwSignalType : LongWord ) : ByteBool; cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_GenHasSymmetryEx'{$endif};
function GenGetSymmetryMin( hDevice : TLibTiePieHandle ) : Double; cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_GenGetSymmetryMin'{$endif};
function GenGetSymmetryMax( hDevice : TLibTiePieHandle ) : Double; cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_GenGetSymmetryMax'{$endif};
procedure GenGetSymmetryMinMaxEx( hDevice : TLibTiePieHandle ; dwSignalType : LongWord ; pMin , pMax : PDouble ); cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_GenGetSymmetryMinMaxEx'{$endif};
function GenGetSymmetry( hDevice : TLibTiePieHandle ) : Double; cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_GenGetSymmetry'{$endif};
function GenSetSymmetry( hDevice : TLibTiePieHandle ; dSymmetry : Double ) : Double; cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_GenSetSymmetry'{$endif};
function GenVerifySymmetry( hDevice : TLibTiePieHandle ; dSymmetry : Double ) : Double; cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_GenVerifySymmetry'{$endif};
function GenVerifySymmetryEx( hDevice : TLibTiePieHandle ; dSymmetry : Double ; dwSignalType : LongWord ) : Double; cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_GenVerifySymmetryEx'{$endif};
function GenHasWidth( hDevice : TLibTiePieHandle ) : ByteBool; cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_GenHasWidth'{$endif};
function GenHasWidthEx( hDevice : TLibTiePieHandle ; dwSignalType : LongWord ) : ByteBool; cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_GenHasWidthEx'{$endif};
function GenGetWidthMin( hDevice : TLibTiePieHandle ) : Double; cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_GenGetWidthMin'{$endif};
function GenGetWidthMax( hDevice : TLibTiePieHandle ) : Double; cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_GenGetWidthMax'{$endif};
procedure GenGetWidthMinMaxEx( hDevice : TLibTiePieHandle ; dwSignalType : LongWord ; dSignalFrequency : Double ; pMin , pMax : PDouble ); cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_GenGetWidthMinMaxEx'{$endif};
function GenGetWidth( hDevice : TLibTiePieHandle ) : Double; cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_GenGetWidth'{$endif};
function GenSetWidth( hDevice : TLibTiePieHandle ; dWidth : Double ) : Double; cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_GenSetWidth'{$endif};
function GenVerifyWidth( hDevice : TLibTiePieHandle ; dWidth : Double ) : Double; cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_GenVerifyWidth'{$endif};
function GenVerifyWidthEx( hDevice : TLibTiePieHandle ; dWidth : Double ; dwSignalType : LongWord ; dSignalFrequency : Double ) : Double; cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_GenVerifyWidthEx'{$endif};
function GenHasEdgeTime( hDevice : TLibTiePieHandle ) : ByteBool; cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_GenHasEdgeTime'{$endif};
function GenHasEdgeTimeEx( hDevice : TLibTiePieHandle ; dwSignalType : LongWord ) : ByteBool; cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_GenHasEdgeTimeEx'{$endif};
function GenGetLeadingEdgeTimeMin( hDevice : TLibTiePieHandle ) : Double; cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_GenGetLeadingEdgeTimeMin'{$endif};
function GenGetLeadingEdgeTimeMax( hDevice : TLibTiePieHandle ) : Double; cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_GenGetLeadingEdgeTimeMax'{$endif};
procedure GenGetLeadingEdgeTimeMinMaxEx( hDevice : TLibTiePieHandle ; dwSignalType : LongWord ; dSignalFrequency , dSymmetry , dWidth , dTrailingEdgeTime : Double ; pMin , pMax : PDouble ); cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_GenGetLeadingEdgeTimeMinMaxEx'{$endif};
function GenGetLeadingEdgeTime( hDevice : TLibTiePieHandle ) : Double; cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_GenGetLeadingEdgeTime'{$endif};
function GenSetLeadingEdgeTime( hDevice : TLibTiePieHandle ; dLeadingEdgeTime : Double ) : Double; cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_GenSetLeadingEdgeTime'{$endif};
function GenVerifyLeadingEdgeTime( hDevice : TLibTiePieHandle ; dLeadingEdgeTime : Double ) : Double; cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_GenVerifyLeadingEdgeTime'{$endif};
function GenVerifyLeadingEdgeTimeEx( hDevice : TLibTiePieHandle ; dLeadingEdgeTime : Double ; dwSignalType : LongWord ; dSignalFrequency , dSymmetry , dWidth , dTrailingEdgeTime : Double ) : Double; cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_GenVerifyLeadingEdgeTimeEx'{$endif};
function GenGetTrailingEdgeTimeMin( hDevice : TLibTiePieHandle ) : Double; cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_GenGetTrailingEdgeTimeMin'{$endif};
function GenGetTrailingEdgeTimeMax( hDevice : TLibTiePieHandle ) : Double; cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_GenGetTrailingEdgeTimeMax'{$endif};
procedure GenGetTrailingEdgeTimeMinMaxEx( hDevice : TLibTiePieHandle ; dwSignalType : LongWord ; dSignalFrequency , dSymmetry , dWidth , dLeadingEdgeTime : Double ; pMin , pMax : PDouble ); cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_GenGetTrailingEdgeTimeMinMaxEx'{$endif};
function GenGetTrailingEdgeTime( hDevice : TLibTiePieHandle ) : Double; cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_GenGetTrailingEdgeTime'{$endif};
function GenSetTrailingEdgeTime( hDevice : TLibTiePieHandle ; dTrailingEdgeTime : Double ) : Double; cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_GenSetTrailingEdgeTime'{$endif};
function GenVerifyTrailingEdgeTime( hDevice : TLibTiePieHandle ; dTrailingEdgeTime : Double ) : Double; cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_GenVerifyTrailingEdgeTime'{$endif};
function GenVerifyTrailingEdgeTimeEx( hDevice : TLibTiePieHandle ; dTrailingEdgeTime : Double ; dwSignalType : LongWord ; dSignalFrequency , dSymmetry , dWidth , dLeadingEdgeTime : Double ) : Double; cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_GenVerifyTrailingEdgeTimeEx'{$endif};
function GenHasData( hDevice : TLibTiePieHandle ) : ByteBool; cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_GenHasData'{$endif};
function GenHasDataEx( hDevice : TLibTiePieHandle ; dwSignalType : LongWord ) : ByteBool; cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_GenHasDataEx'{$endif};
function GenGetDataLengthMin( hDevice : TLibTiePieHandle ) : UInt64; cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_GenGetDataLengthMin'{$endif};
function GenGetDataLengthMax( hDevice : TLibTiePieHandle ) : UInt64; cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_GenGetDataLengthMax'{$endif};
procedure GenGetDataLengthMinMaxEx( hDevice : TLibTiePieHandle ; dwSignalType : LongWord ; pMin , pMax : PUInt64 ); cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_GenGetDataLengthMinMaxEx'{$endif};
function GenGetDataLength( hDevice : TLibTiePieHandle ) : UInt64; cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_GenGetDataLength'{$endif};
function GenVerifyDataLength( hDevice : TLibTiePieHandle ; qwDataLength : UInt64 ) : UInt64; cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_GenVerifyDataLength'{$endif};
function GenVerifyDataLengthEx( hDevice : TLibTiePieHandle ; qwDataLength : UInt64 ; dwSignalType : LongWord ) : UInt64; cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_GenVerifyDataLengthEx'{$endif};
procedure GenSetData( hDevice : TLibTiePieHandle ; pBuffer : PSingle ; qwSampleCount : UInt64 ); cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_GenSetData'{$endif};
procedure GenSetDataEx( hDevice : TLibTiePieHandle ; pBuffer : PSingle ; qwSampleCount : UInt64 ; dwSignalType , dwReserved : LongWord ); cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_GenSetDataEx'{$endif};
function GenGetDataRawType( hDevice : TLibTiePieHandle ) : LongWord; cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_GenGetDataRawType'{$endif};
procedure GenGetDataRawValueRange( hDevice : TLibTiePieHandle ; pMin , pZero , pMax : PInt64 ); cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_GenGetDataRawValueRange'{$endif};
function GenGetDataRawValueMin( hDevice : TLibTiePieHandle ) : Int64; cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_GenGetDataRawValueMin'{$endif};
function GenGetDataRawValueZero( hDevice : TLibTiePieHandle ) : Int64; cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_GenGetDataRawValueZero'{$endif};
function GenGetDataRawValueMax( hDevice : TLibTiePieHandle ) : Int64; cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_GenGetDataRawValueMax'{$endif};
procedure GenSetDataRaw( hDevice : TLibTiePieHandle ; pBuffer : Pointer ; qwSampleCount : UInt64 ); cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_GenSetDataRaw'{$endif};
procedure GenSetDataRawEx( hDevice : TLibTiePieHandle ; pBuffer : Pointer ; qwSampleCount : UInt64 ; dwSignalType , dwReserved : LongWord ); cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_GenSetDataRawEx'{$endif};
function GenGetModes( hDevice : TLibTiePieHandle ) : UInt64; cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_GenGetModes'{$endif};
function GenGetModesEx( hDevice : TLibTiePieHandle ; dwSignalType , dwFrequencyMode : LongWord ) : UInt64; cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_GenGetModesEx'{$endif};
function GenGetModesNative( hDevice : TLibTiePieHandle ) : UInt64; cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_GenGetModesNative'{$endif};
function GenGetMode( hDevice : TLibTiePieHandle ) : UInt64; cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_GenGetMode'{$endif};
function GenSetMode( hDevice : TLibTiePieHandle ; qwGeneratorMode : UInt64 ) : UInt64; cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_GenSetMode'{$endif};
function GenIsBurstActive( hDevice : TLibTiePieHandle ) : ByteBool; cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_GenIsBurstActive'{$endif};
function GenGetBurstCountMin( hDevice : TLibTiePieHandle ) : UInt64; cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_GenGetBurstCountMin'{$endif};
function GenGetBurstCountMax( hDevice : TLibTiePieHandle ) : UInt64; cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_GenGetBurstCountMax'{$endif};
procedure GenGetBurstCountMinMaxEx( hDevice : TLibTiePieHandle ; qwGeneratorMode : UInt64 ; pMin , pMax : PUInt64 ); cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_GenGetBurstCountMinMaxEx'{$endif};
function GenGetBurstCount( hDevice : TLibTiePieHandle ) : UInt64; cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_GenGetBurstCount'{$endif};
function GenSetBurstCount( hDevice : TLibTiePieHandle ; qwBurstCount : UInt64 ) : UInt64; cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_GenSetBurstCount'{$endif};
function GenGetBurstSampleCountMin( hDevice : TLibTiePieHandle ) : UInt64; cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_GenGetBurstSampleCountMin'{$endif};
function GenGetBurstSampleCountMax( hDevice : TLibTiePieHandle ) : UInt64; cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_GenGetBurstSampleCountMax'{$endif};
procedure GenGetBurstSampleCountMinMaxEx( hDevice : TLibTiePieHandle ; qwGeneratorMode : UInt64 ; pMin , pMax : PUInt64 ); cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_GenGetBurstSampleCountMinMaxEx'{$endif};
function GenGetBurstSampleCount( hDevice : TLibTiePieHandle ) : UInt64; cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_GenGetBurstSampleCount'{$endif};
function GenSetBurstSampleCount( hDevice : TLibTiePieHandle ; qwBurstSampleCount : UInt64 ) : UInt64; cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_GenSetBurstSampleCount'{$endif};
function GenGetBurstSegmentCountMin( hDevice : TLibTiePieHandle ) : UInt64; cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_GenGetBurstSegmentCountMin'{$endif};
function GenGetBurstSegmentCountMax( hDevice : TLibTiePieHandle ) : UInt64; cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_GenGetBurstSegmentCountMax'{$endif};
procedure GenGetBurstSegmentCountMinMaxEx( hDevice : TLibTiePieHandle ; qwGeneratorMode : UInt64 ; dwSignalType , dwFrequencyMode : LongWord ; dFrequency : Double ; qwDataLength : UInt64 ; pMin , pMax : PUInt64 ); cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_GenGetBurstSegmentCountMinMaxEx'{$endif};
function GenGetBurstSegmentCount( hDevice : TLibTiePieHandle ) : UInt64; cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_GenGetBurstSegmentCount'{$endif};
function GenSetBurstSegmentCount( hDevice : TLibTiePieHandle ; qwBurstSegmentCount : UInt64 ) : UInt64; cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_GenSetBurstSegmentCount'{$endif};
function GenVerifyBurstSegmentCount( hDevice : TLibTiePieHandle ; qwBurstSegmentCount : UInt64 ) : UInt64; cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_GenVerifyBurstSegmentCount'{$endif};
function GenVerifyBurstSegmentCountEx( hDevice : TLibTiePieHandle ; qwBurstSegmentCount , qwGeneratorMode : UInt64 ; dwSignalType , dwFrequencyMode : LongWord ; dFrequency : Double ; qwDataLength : UInt64 ) : UInt64; cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_GenVerifyBurstSegmentCountEx'{$endif};
procedure GenSetCallbackBurstCompleted( hDevice : TLibTiePieHandle ; pCallback : TTpCallback ; pData : Pointer ); cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_GenSetCallbackBurstCompleted'{$endif};
{$ifdef LINUX}
procedure GenSetEventBurstCompleted( hDevice : TLibTiePieHandle ; fdEvent : Integer ); cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_GenSetEventBurstCompleted'{$endif};
{$endif LINUX}
{$ifdef MSWINDOWS}
procedure GenSetEventBurstCompleted( hDevice : TLibTiePieHandle ; hEvent : THandle ); cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_GenSetEventBurstCompleted'{$endif};
procedure GenSetMessageBurstCompleted( hDevice : TLibTiePieHandle ; hWnd : HWND ; wParam : WPARAM ; lParam : LPARAM ); cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_GenSetMessageBurstCompleted'{$endif};
{$endif MSWINDOWS}
procedure GenSetCallbackControllableChanged( hDevice : TLibTiePieHandle ; pCallback : TTpCallback ; pData : Pointer ); cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_GenSetCallbackControllableChanged'{$endif};
{$ifdef LINUX}
procedure GenSetEventControllableChanged( hDevice : TLibTiePieHandle ; fdEvent : Integer ); cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_GenSetEventControllableChanged'{$endif};
{$endif LINUX}
{$ifdef MSWINDOWS}
procedure GenSetEventControllableChanged( hDevice : TLibTiePieHandle ; hEvent : THandle ); cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_GenSetEventControllableChanged'{$endif};
procedure GenSetMessageControllableChanged( hDevice : TLibTiePieHandle ; hWnd : HWND ; wParam : WPARAM ; lParam : LPARAM ); cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_GenSetMessageControllableChanged'{$endif};
{$endif MSWINDOWS}
function I2CIsInternalAddress( hDevice : TLibTiePieHandle ; wAddress : Word ) : ByteBool; cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_I2CIsInternalAddress'{$endif};
function I2CGetInternalAddresses( hDevice : TLibTiePieHandle ; pAddresses : PWord ; dwLength : LongWord ) : LongWord; cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_I2CGetInternalAddresses'{$endif};
function I2CRead( hDevice : TLibTiePieHandle ; wAddress : Word ; pBuffer : Pointer ; dwSize : LongWord ; bStop : ByteBool ) : ByteBool; cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_I2CRead'{$endif};
function I2CReadByte( hDevice : TLibTiePieHandle ; wAddress : Word ; pValue : PByte ) : ByteBool; cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_I2CReadByte'{$endif};
function I2CReadWord( hDevice : TLibTiePieHandle ; wAddress : Word ; pValue : PWord ) : ByteBool; cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_I2CReadWord'{$endif};
function I2CWrite( hDevice : TLibTiePieHandle ; wAddress : Word ; pBuffer : Pointer ; dwSize : LongWord ; bStop : ByteBool ) : ByteBool; cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_I2CWrite'{$endif};
function I2CWriteByte( hDevice : TLibTiePieHandle ; wAddress : Word ; byValue : Byte ) : ByteBool; cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_I2CWriteByte'{$endif};
function I2CWriteByteByte( hDevice : TLibTiePieHandle ; wAddress : Word ; byValue1 , byValue2 : Byte ) : ByteBool; cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_I2CWriteByteByte'{$endif};
function I2CWriteByteWord( hDevice : TLibTiePieHandle ; wAddress : Word ; byValue1 : Byte ; wValue2 : Word ) : ByteBool; cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_I2CWriteByteWord'{$endif};
function I2CWriteWord( hDevice : TLibTiePieHandle ; wAddress , wValue : Word ) : ByteBool; cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_I2CWriteWord'{$endif};
function I2CWriteRead( hDevice : TLibTiePieHandle ; wAddress : Word ; pWriteBuffer : Pointer ; dwWriteSize : LongWord ; pReadBuffer : Pointer ; dwReadSize : LongWord ) : ByteBool; cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_I2CWriteRead'{$endif};
function I2CGetSpeedMax( hDevice : TLibTiePieHandle ) : Double; cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_I2CGetSpeedMax'{$endif};
function I2CGetSpeed( hDevice : TLibTiePieHandle ) : Double; cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_I2CGetSpeed'{$endif};
function I2CSetSpeed( hDevice : TLibTiePieHandle ; dSpeed : Double ) : Double; cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_I2CSetSpeed'{$endif};
function I2CVerifySpeed( hDevice : TLibTiePieHandle ; dSpeed : Double ) : Double; cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_I2CVerifySpeed'{$endif};
function SrvConnect( hServer : TLibTiePieHandle ; bAsync : ByteBool ) : ByteBool; cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_SrvConnect'{$endif};
function SrvDisconnect( hServer : TLibTiePieHandle ; bForce : ByteBool ) : ByteBool; cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_SrvDisconnect'{$endif};
function SrvRemove( hServer : TLibTiePieHandle ; bForce : ByteBool ) : ByteBool; cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_SrvRemove'{$endif};
function SrvGetStatus( hServer : TLibTiePieHandle ) : LongWord; cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_SrvGetStatus'{$endif};
function SrvGetLastError( hServer : TLibTiePieHandle ) : LongWord; cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_SrvGetLastError'{$endif};
function SrvGetURL( hServer : TLibTiePieHandle ; pBuffer : PAnsiChar ; dwBufferLength : LongWord ) : LongWord; cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_SrvGetURL'{$endif};
function SrvGetID( hServer : TLibTiePieHandle ; pBuffer : PAnsiChar ; dwBufferLength : LongWord ) : LongWord; cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_SrvGetID'{$endif};
function SrvGetIPv4Address( hServer : TLibTiePieHandle ) : LongWord; cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_SrvGetIPv4Address'{$endif};
function SrvGetIPPort( hServer : TLibTiePieHandle ) : Word; cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_SrvGetIPPort'{$endif};
function SrvGetName( hServer : TLibTiePieHandle ; pBuffer : PAnsiChar ; dwBufferLength : LongWord ) : LongWord; cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_SrvGetName'{$endif};
function SrvGetDescription( hServer : TLibTiePieHandle ; pBuffer : PAnsiChar ; dwBufferLength : LongWord ) : LongWord; cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_SrvGetDescription'{$endif};
function SrvGetVersion( hServer : TLibTiePieHandle ) : TTpVersion; cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_SrvGetVersion'{$endif};
function SrvGetVersionExtra( hServer : TLibTiePieHandle ; pBuffer : PAnsiChar ; dwBufferLength : LongWord ) : LongWord; cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_SrvGetVersionExtra'{$endif};
function HlpPointerArrayNew( dwLength : LongWord ) : TLibTiePiePointerArray; cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_HlpPointerArrayNew'{$endif};
procedure HlpPointerArraySet( pArray : TLibTiePiePointerArray ; dwIndex : LongWord ; pPointer : Pointer ); cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_HlpPointerArraySet'{$endif};
procedure HlpPointerArrayDelete( pArray : TLibTiePiePointerArray ); cdecl; external sLibTiePieFileNameDefault {$ifdef MACOS}name '_HlpPointerArrayDelete'{$endif};

{$endif !LIBTIEPIE_DYNAMIC}

//==============================================================================
// Extra routines

{$IF not Declared( UTF8ToWideString )}
function UTF8ToWideString( const us : UTF8String ) : WideString;
begin
  Result := UTF8Decode( us );
end;
{$IFEND}

function TpDateToDateTime( ATpDate : TTpDate ) : TDateTime;
begin
  if ATpDate <> 0 then
    Result := EncodeDate( ATpDate shr 16 , ( ATpDate shr 8 ) and $FF , ATpDate and $FF )
  else
    Result := 0;
end;

function LibGetConfigDynArray : TByteDynArray;
begin
  SetLength( Result , LibGetConfig( nil , 0 ) );
  if Length( Result ) > 0 then
    LibGetConfig( @Result[ 0 ] , Length( Result ) );
end;

function LstDevGetNameWS( dwIdKind , dwId : LongWord ) : WideString;
var
  usTmp : UTF8String;
  dwLength : LongWord;
begin
  dwLength := LstDevGetName( dwIdKind , dwId , nil , 0 );
  if dwLength > 0 then begin
    SetLength( usTmp , dwLength );
    LstDevGetName( dwIdKind , dwId , @usTmp[ 1 ] , dwLength );
    Result := UTF8ToWideString( usTmp );
  end;
end;

function LstDevGetNameShortWS( dwIdKind , dwId : LongWord ) : WideString;
var
  usTmp : UTF8String;
  dwLength : LongWord;
begin
  dwLength := LstDevGetNameShort( dwIdKind , dwId , nil , 0 );
  if dwLength > 0 then begin
    SetLength( usTmp , dwLength );
    LstDevGetNameShort( dwIdKind , dwId , @usTmp[ 1 ] , dwLength );
    Result := UTF8ToWideString( usTmp );
  end;
end;

function LstDevGetNameShortestWS( dwIdKind , dwId : LongWord ) : WideString;
var
  usTmp : UTF8String;
  dwLength : LongWord;
begin
  dwLength := LstDevGetNameShortest( dwIdKind , dwId , nil , 0 );
  if dwLength > 0 then begin
    SetLength( usTmp , dwLength );
    LstDevGetNameShortest( dwIdKind , dwId , @usTmp[ 1 ] , dwLength );
    Result := UTF8ToWideString( usTmp );
  end;
end;

function LstDevGetCalibrationDateTime( dwIdKind , dwId : LongWord ) : TDateTime;
begin
  Result := TpDateToDateTime( LstDevGetCalibrationDate( dwIdKind , dwId ) );
end;

function LstDevGetContainedSerialNumbersDynArray( dwIdKind , dwId : LongWord ) : TLongWordDynArray;
begin
  SetLength( Result , LstDevGetContainedSerialNumbers( dwIdKind , dwId , nil , 0 ) );
  if Length( Result ) > 0 then
    LstDevGetContainedSerialNumbers( dwIdKind , dwId , @Result[ 0 ] , Length( Result ) );
end;

function LstCbDevGetNameWS( dwIdKind , dwId , dwContainedDeviceSerialNumber : LongWord ) : WideString;
var
  usTmp : UTF8String;
  dwLength : LongWord;
begin
  dwLength := LstCbDevGetName( dwIdKind , dwId , dwContainedDeviceSerialNumber , nil , 0 );
  if dwLength > 0 then begin
    SetLength( usTmp , dwLength );
    LstCbDevGetName( dwIdKind , dwId , dwContainedDeviceSerialNumber , @usTmp[ 1 ] , dwLength );
    Result := UTF8ToWideString( usTmp );
  end;
end;

function LstCbDevGetNameShortWS( dwIdKind , dwId , dwContainedDeviceSerialNumber : LongWord ) : WideString;
var
  usTmp : UTF8String;
  dwLength : LongWord;
begin
  dwLength := LstCbDevGetNameShort( dwIdKind , dwId , dwContainedDeviceSerialNumber , nil , 0 );
  if dwLength > 0 then begin
    SetLength( usTmp , dwLength );
    LstCbDevGetNameShort( dwIdKind , dwId , dwContainedDeviceSerialNumber , @usTmp[ 1 ] , dwLength );
    Result := UTF8ToWideString( usTmp );
  end;
end;

function LstCbDevGetNameShortestWS( dwIdKind , dwId , dwContainedDeviceSerialNumber : LongWord ) : WideString;
var
  usTmp : UTF8String;
  dwLength : LongWord;
begin
  dwLength := LstCbDevGetNameShortest( dwIdKind , dwId , dwContainedDeviceSerialNumber , nil , 0 );
  if dwLength > 0 then begin
    SetLength( usTmp , dwLength );
    LstCbDevGetNameShortest( dwIdKind , dwId , dwContainedDeviceSerialNumber , @usTmp[ 1 ] , dwLength );
    Result := UTF8ToWideString( usTmp );
  end;
end;

function LstCbDevGetCalibrationDateTime( dwIdKind , dwId , dwContainedDeviceSerialNumber : LongWord ) : TDateTime;
begin
  Result := TpDateToDateTime( LstCbDevGetCalibrationDate( dwIdKind , dwId , dwContainedDeviceSerialNumber ) );
end;

procedure LstSetCallbackMethodDeviceAdded( AMethod : TTpCallbackDeviceListMethod );
begin
  LstSetCallbackDeviceAdded( TMethod( AMethod ).Code , TMethod( AMethod ).Data );
end;

procedure LstSetCallbackMethodDeviceRemoved( AMethod : TTpCallbackDeviceListMethod );
begin
  LstSetCallbackDeviceRemoved( TMethod( AMethod ).Code , TMethod( AMethod ).Data );
end;

procedure LstSetCallbackMethodDeviceCanOpenChanged( AMethod : TTpCallbackDeviceListMethod );
begin
  LstSetCallbackDeviceCanOpenChanged( TMethod( AMethod ).Code , TMethod( AMethod ).Data );
end;

procedure NetSrvSetCallbackMethodAdded( AMethod : TTpCallbackHandleMethod );
begin
  NetSrvSetCallbackAdded( TMethod( AMethod ).Code , TMethod( AMethod ).Data );
end;

procedure ObjSetEventCallbackMethod( hHandle : TLibTiePieHandle ; AMethod : TTpCallbackEventMethod );
begin
  ObjSetEventCallback( hHandle , TMethod( AMethod ).Code , TMethod( AMethod ).Data );
end;

function DevGetCalibrationDateTime( hDevice : TLibTiePieHandle ) : TDateTime;
begin
  Result := TpDateToDateTime( DevGetCalibrationDate( hDevice ) );
end;

function DevGetCalibrationTokenWS( hDevice : TLibTiePieHandle ) : WideString;
var
  usTmp : UTF8String;
  dwLength : LongWord;
begin
  dwLength := DevGetCalibrationToken( hDevice , nil , 0 );
  if dwLength > 0 then begin
    SetLength( usTmp , dwLength );
    DevGetCalibrationToken( hDevice , @usTmp[ 1 ] , dwLength );
    Result := UTF8ToWideString( usTmp );
  end;
end;

function DevGetNameWS( hDevice : TLibTiePieHandle ) : WideString;
var
  usTmp : UTF8String;
  dwLength : LongWord;
begin
  dwLength := DevGetName( hDevice , nil , 0 );
  if dwLength > 0 then begin
    SetLength( usTmp , dwLength );
    DevGetName( hDevice , @usTmp[ 1 ] , dwLength );
    Result := UTF8ToWideString( usTmp );
  end;
end;

function DevGetNameShortWS( hDevice : TLibTiePieHandle ) : WideString;
var
  usTmp : UTF8String;
  dwLength : LongWord;
begin
  dwLength := DevGetNameShort( hDevice , nil , 0 );
  if dwLength > 0 then begin
    SetLength( usTmp , dwLength );
    DevGetNameShort( hDevice , @usTmp[ 1 ] , dwLength );
    Result := UTF8ToWideString( usTmp );
  end;
end;

function DevGetNameShortestWS( hDevice : TLibTiePieHandle ) : WideString;
var
  usTmp : UTF8String;
  dwLength : LongWord;
begin
  dwLength := DevGetNameShortest( hDevice , nil , 0 );
  if dwLength > 0 then begin
    SetLength( usTmp , dwLength );
    DevGetNameShortest( hDevice , @usTmp[ 1 ] , dwLength );
    Result := UTF8ToWideString( usTmp );
  end;
end;

procedure DevSetCallbackMethodRemoved( hDevice : TLibTiePieHandle ; AMethod : TTpCallbackMethod );
begin
  DevSetCallbackRemoved( hDevice , TMethod( AMethod ).Code , TMethod( AMethod ).Data );
end;

function DevTrInGetNameWS( hDevice : TLibTiePieHandle ; wInput : Word ) : WideString;
var
  usTmp : UTF8String;
  dwLength : LongWord;
begin
  dwLength := DevTrInGetName( hDevice , wInput , nil , 0 );
  if dwLength > 0 then begin
    SetLength( usTmp , dwLength );
    DevTrInGetName( hDevice , wInput , @usTmp[ 1 ] , dwLength );
    Result := UTF8ToWideString( usTmp );
  end;
end;

function DevTrOutGetNameWS( hDevice : TLibTiePieHandle ; wOutput : Word ) : WideString;
var
  usTmp : UTF8String;
  dwLength : LongWord;
begin
  dwLength := DevTrOutGetName( hDevice , wOutput , nil , 0 );
  if dwLength > 0 then begin
    SetLength( usTmp , dwLength );
    DevTrOutGetName( hDevice , wOutput , @usTmp[ 1 ] , dwLength );
    Result := UTF8ToWideString( usTmp );
  end;
end;

function ScpChGetBandwidthsDynArray( hDevice : TLibTiePieHandle ; wCh : Word ) : TDoubleDynArray;
begin
  SetLength( Result , ScpChGetBandwidths( hDevice , wCh , nil , 0 ) );
  if Length( Result ) > 0 then
    ScpChGetBandwidths( hDevice , wCh , @Result[ 0 ] , Length( Result ) );
end;

function ScpChGetRangesDynArray( hDevice : TLibTiePieHandle ; wCh : Word ) : TDoubleDynArray;
begin
  SetLength( Result , ScpChGetRanges( hDevice , wCh , nil , 0 ) );
  if Length( Result ) > 0 then
    ScpChGetRanges( hDevice , wCh , @Result[ 0 ] , Length( Result ) );
end;

function ScpChGetRangesExDynArray( hDevice : TLibTiePieHandle ; wCh : Word ; qwCoupling : UInt64 ) : TDoubleDynArray;
begin
  SetLength( Result , ScpChGetRangesEx( hDevice , wCh , qwCoupling , nil , 0 ) );
  if Length( Result ) > 0 then
    ScpChGetRangesEx( hDevice , wCh , qwCoupling , @Result[ 0 ] , Length( Result ) );
end;

procedure ScpSetCallbackMethodDataReady( hDevice : TLibTiePieHandle ; AMethod : TTpCallbackMethod );
begin
  ScpSetCallbackDataReady( hDevice , TMethod( AMethod ).Code , TMethod( AMethod ).Data );
end;

procedure ScpSetCallbackMethodDataOverflow( hDevice : TLibTiePieHandle ; AMethod : TTpCallbackMethod );
begin
  ScpSetCallbackDataOverflow( hDevice , TMethod( AMethod ).Code , TMethod( AMethod ).Data );
end;

procedure ScpSetCallbackMethodConnectionTestCompleted( hDevice : TLibTiePieHandle ; AMethod : TTpCallbackMethod );
begin
  ScpSetCallbackConnectionTestCompleted( hDevice , TMethod( AMethod ).Code , TMethod( AMethod ).Data );
end;

procedure ScpSetCallbackMethodTriggered( hDevice : TLibTiePieHandle ; AMethod : TTpCallbackMethod );
begin
  ScpSetCallbackTriggered( hDevice , TMethod( AMethod ).Code , TMethod( AMethod ).Data );
end;

function ScpGetResolutionsDynArray( hDevice : TLibTiePieHandle ) : TByteDynArray;
begin
  SetLength( Result , ScpGetResolutions( hDevice , nil , 0 ) );
  if Length( Result ) > 0 then
    ScpGetResolutions( hDevice , @Result[ 0 ] , Length( Result ) );
end;

function ScpGetClockSourceFrequenciesDynArray( hDevice : TLibTiePieHandle ) : TDoubleDynArray;
begin
  SetLength( Result , ScpGetClockSourceFrequencies( hDevice , nil , 0 ) );
  if Length( Result ) > 0 then
    ScpGetClockSourceFrequencies( hDevice , @Result[ 0 ] , Length( Result ) );
end;

function ScpGetClockSourceFrequenciesExDynArray( hDevice : TLibTiePieHandle ; dwClockSource : LongWord ) : TDoubleDynArray;
begin
  SetLength( Result , ScpGetClockSourceFrequenciesEx( hDevice , dwClockSource , nil , 0 ) );
  if Length( Result ) > 0 then
    ScpGetClockSourceFrequenciesEx( hDevice , dwClockSource , @Result[ 0 ] , Length( Result ) );
end;

function ScpGetClockOutputFrequenciesDynArray( hDevice : TLibTiePieHandle ) : TDoubleDynArray;
begin
  SetLength( Result , ScpGetClockOutputFrequencies( hDevice , nil , 0 ) );
  if Length( Result ) > 0 then
    ScpGetClockOutputFrequencies( hDevice , @Result[ 0 ] , Length( Result ) );
end;

function ScpGetClockOutputFrequenciesExDynArray( hDevice : TLibTiePieHandle ; dwClockOutput : LongWord ) : TDoubleDynArray;
begin
  SetLength( Result , ScpGetClockOutputFrequenciesEx( hDevice , dwClockOutput , nil , 0 ) );
  if Length( Result ) > 0 then
    ScpGetClockOutputFrequenciesEx( hDevice , dwClockOutput , @Result[ 0 ] , Length( Result ) );
end;

function GenGetAmplitudeRangesDynArray( hDevice : TLibTiePieHandle ) : TDoubleDynArray;
begin
  SetLength( Result , GenGetAmplitudeRanges( hDevice , nil , 0 ) );
  if Length( Result ) > 0 then
    GenGetAmplitudeRanges( hDevice , @Result[ 0 ] , Length( Result ) );
end;

procedure GenSetCallbackMethodBurstCompleted( hDevice : TLibTiePieHandle ; AMethod : TTpCallbackMethod );
begin
  GenSetCallbackBurstCompleted( hDevice , TMethod( AMethod ).Code , TMethod( AMethod ).Data );
end;

procedure GenSetCallbackMethodControllableChanged( hDevice : TLibTiePieHandle ; AMethod : TTpCallbackMethod );
begin
  GenSetCallbackControllableChanged( hDevice , TMethod( AMethod ).Code , TMethod( AMethod ).Data );
end;

function I2CGetInternalAddressesDynArray( hDevice : TLibTiePieHandle ) : TWordDynArray;
begin
  SetLength( Result , I2CGetInternalAddresses( hDevice , nil , 0 ) );
  if Length( Result ) > 0 then
    I2CGetInternalAddresses( hDevice , @Result[ 0 ] , Length( Result ) );
end;

function SrvGetURLWS( hServer : TLibTiePieHandle ) : WideString;
var
  usTmp : UTF8String;
  dwLength : LongWord;
begin
  dwLength := SrvGetURL( hServer , nil , 0 );
  if dwLength > 0 then begin
    SetLength( usTmp , dwLength );
    SrvGetURL( hServer , @usTmp[ 1 ] , dwLength );
    Result := UTF8ToWideString( usTmp );
  end;
end;

function SrvGetIDWS( hServer : TLibTiePieHandle ) : WideString;
var
  usTmp : UTF8String;
  dwLength : LongWord;
begin
  dwLength := SrvGetID( hServer , nil , 0 );
  if dwLength > 0 then begin
    SetLength( usTmp , dwLength );
    SrvGetID( hServer , @usTmp[ 1 ] , dwLength );
    Result := UTF8ToWideString( usTmp );
  end;
end;

function SrvGetNameWS( hServer : TLibTiePieHandle ) : WideString;
var
  usTmp : UTF8String;
  dwLength : LongWord;
begin
  dwLength := SrvGetName( hServer , nil , 0 );
  if dwLength > 0 then begin
    SetLength( usTmp , dwLength );
    SrvGetName( hServer , @usTmp[ 1 ] , dwLength );
    Result := UTF8ToWideString( usTmp );
  end;
end;

function SrvGetDescriptionWS( hServer : TLibTiePieHandle ) : WideString;
var
  usTmp : UTF8String;
  dwLength : LongWord;
begin
  dwLength := SrvGetDescription( hServer , nil , 0 );
  if dwLength > 0 then begin
    SetLength( usTmp , dwLength );
    SrvGetDescription( hServer , @usTmp[ 1 ] , dwLength );
    Result := UTF8ToWideString( usTmp );
  end;
end;

function SrvGetVersionExtraWS( hServer : TLibTiePieHandle ) : WideString;
var
  usTmp : UTF8String;
  dwLength : LongWord;
begin
  dwLength := SrvGetVersionExtra( hServer , nil , 0 );
  if dwLength > 0 then begin
    SetLength( usTmp , dwLength );
    SrvGetVersionExtra( hServer , @usTmp[ 1 ] , dwLength );
    Result := UTF8ToWideString( usTmp );
  end;
end;

// END Extra routines
//==============================================================================

{$ifndef LIBTIEPIE_DYNAMIC}
initialization
  LibInit();
finalization
  LibExit();
{$endif !LIBTIEPIE_DYNAMIC}
end.
