/**
 * \file libtiepie.h
 * \brief Header for libtiepie
 */

#ifndef _LIBTIEPIE_H_
#define _LIBTIEPIE_H_

// This section tries to define the C99 stdint types by detecting the used compiler/C version:
#if ( defined( __STDC_VERSION__ ) && __STDC_VERSION__ >= 199901L ) || ( defined( __GNUC__ ) && defined( __cplusplus ) )
  #include <stdint.h>
#elif defined( INCLUDED_BY_MATLAB ) // MathWorks Matlab, see libtiepiematlab.h
  #include <tmwtypes.h>

  // Define types:
  typedef INT8_T  int8_t;
  typedef INT16_T int16_t;
  typedef INT32_T int32_t;
  typedef INT64_T int64_t;

  typedef UINT8_T  uint8_t;
  typedef UINT16_T uint16_t;
  typedef UINT32_T uint32_t;
  typedef UINT64_T uint64_t;
#elif defined( _CVI_ ) || defined( LIBTIEPIE_LABVIEW ) // National Instruments LabWindows/CVI/LabView
  #ifdef _CVI_C99_EXTENSIONS_
    #include <stdint.h>
  #else
    // Define types:
    typedef char    int8_t;
    typedef short   int16_t;
    typedef int     int32_t;
    typedef __int64 int64_t;

    typedef unsigned char    uint8_t;
    typedef unsigned short   uint16_t;
    typedef unsigned int     uint32_t;
    typedef unsigned __int64 uint64_t;
  #endif
#elif defined( _MSC_VER )
  #include "stdint.h" // Note: You can find a stdint.h for microsoft compilers at http://msinttypes.googlecode.com/svn/trunk/stdint.h .
#else
  #error "C99 stdint types not defined!"
#endif

// Check whether we are on a Windows NT or Linux based operating system:
#if defined( _WIN32 ) || defined( _WIN64 ) || defined( __WIN32__ ) || defined( __TOS_WIN__ ) || defined( __WINDOWS__ )
  #define LIBTIEPIE_WINDOWS
  #include <windows.h>
#elif defined( __linux__ ) || defined( _NI_linux_ )
  #define LIBTIEPIE_LINUX
#endif

#ifdef __cplusplus
extern "C"
{
#endif

#define LIBTIEPIE_VERSION_MAJOR    0
#define LIBTIEPIE_VERSION_MINOR    9
#define LIBTIEPIE_VERSION_RELEASE  16
#define LIBTIEPIE_VERSION_NUMBER   "0.9.16"
#define LIBTIEPIE_VERSION          "0.9.16"
#define LIBTIEPIE_REVISION         14603

/**
 * \mainpage
 *
 * \section Intro Introduction
 *
 * The LibTiePie library is a library for using TiePie engineering USB instruments through third party software.
 *
 * \subsection instruments Supported instruments
 * - <a class="External" href="https://www.tiepie.com/WS6">WiFiScope WS6</a>
 * - <a class="External" href="https://www.tiepie.com/WS5">WiFiScope WS5</a>
 * - <a class="External" href="https://www.tiepie.com/HS6D">Handyscope HS6 DIFF</a>
 * - <a class="External" href="https://www.tiepie.com/HS5">Handyscope HS5</a>
 * - <a class="External" href="https://www.tiepie.com/HS4">Handyscope HS4</a>
 * - <a class="External" href="https://www.tiepie.com/HS4D">Handyscope HS4 DIFF</a>
 * - <a class="External" href="https://www.tiepie.com/HS3">Handyscope HS3</a>
 * - <a class="External" href="https://www.tiepie-automotive.com/ATS610004D">ATS610004D</a>
 * - <a class="External" href="https://www.tiepie-automotive.com/ATS605004D">ATS605004D</a>
 * - <a class="External" href="https://www.tiepie-automotive.com/ATS5004D">ATS5004D</a>
 * - <a class="External" href="https://www.tiepie.com/HP3">Handyprobe HP3</a>
 * - <a class="External" href="https://www.tiepie.com/TP450">Handyscope TP450</a>
 *
 * \subsection structure Library structure
 *
 * LibTiePie maintains a \ref lst, containing all available supported devices.
 * Possible devices are \ref scp "oscilloscopes", \ref gen "generators" and \ref i2c "I2C hosts".
 * Instruments can contain multiple devices, e.g. the Handyscope HS5 contains an oscilloscope, a generator and an I2C host.
 *
 * Devices can contain sub devices.
 * E.g. devices contain \ref dev_trigger "trigger systems", oscilloscopes contain \ref scp_channels "channels", channels contain \ref scp_ch_tr "channel trigger systems".
 *
 * The LibTiePie library contains functions to control all aspects of the device list and the (sub) devices.
 *
 * \subsubsection prefixes LibTiePie function name prefixes
 *
 * All functions are prefixed, so it is easily determined where the function can be used for.
 *
 * <table>
 *   <tr><th>Prefix</th>     <th>Description</th>                                                      </tr>
 *   <tr><td>\b Lib</td>     <td>Common \ref lib related functions</td>                                </tr>
 *   <tr><td>\b Lst</td>     <td>\ref lst related functions</td>                                       </tr>
 *   <tr><td>\b LstDev</td>  <td>\ref lst_instruments related functions</td>                           </tr>
 *   <tr><td>\b LstCbDev</td><td>\ref lst_combined "Listed combined devices" related functions</td>    </tr>
 *   <tr><td>\b Net</td>     <td>\ref net related functions</td>    </tr>
 *   <tr><td>\b Obj</td>     <td>\ref obj "Common object" related functions</td>                       </tr>
 *   <tr><td>\b Dev</td>     <td>\ref dev "Common device" related functions</td>                       </tr>
 *   <tr><td>\b DevTrIn</td> <td>\ref dev_trigger_input "Device trigger input" related functions</td>  </tr>
 *   <tr><td>\b DevTrOut</td><td>\ref dev_trigger_output "Device trigger output" related functions</td></tr>
 *   <tr><td>\b Scp</td>     <td>\ref scp related functions</td>                                       </tr>
 *   <tr><td>\b ScpCh</td>   <td>\ref scp_channels "Oscilloscope channel" related functions</td>       </tr>
 *   <tr><td>\b ScpChTr</td> <td>\ref scp_ch_tr "Oscilloscope channel trigger" related functions</td>  </tr>
 *   <tr><td>\b Gen</td>     <td>\ref gen related functions</td>                                       </tr>
 *   <tr><td>\b I2C</td>     <td>\ref i2c related functions</td>                                       </tr>
 *   <tr><td>\b Srv</td>     <td>\ref srv related functions</td>                                       </tr>
 *   <tr><td>\b Hlp</td>     <td>\ref hlp for bypassing limitations of some programming languages</td> </tr>
 * </table>
 *
 * \subsection UsingLibTiePie Using LibTiePie
 *
 * When using LibTiePie, to control instruments and perform measurements, the following steps are required:
 *
 * - \ref lib "Initialize" the library
 * - \ref lst "Update" the device list
 * - \ref lst "Open" the required device(s)
 * - Setup the \ref scp
 *   - Setup the \ref scp_channels "oscilloscope channels"
 *   - Setup the \ref scp_timebase "oscilloscope timebase"
 *   - Setup the trigger (\ref scp_ch_tr "channels" and \ref dev_trigger_input "device")
 * - Setup the \ref gen
 * - Start a \ref scp_measurements "measurement"
 * - Wait for the measurement to be \ref scp_measurements_status "ready"
 * - Retrieve the \ref scp_data "measured data"
 * - \ref ObjClose "Close" the device(s)
 * - \ref lib "Exit" the library
 *
 *
 * \subsection errorhandling Error handling
 * On each function call a status flag is set, use LibGetLastStatus() to read the status flag. See also \ref LIBTIEPIESTATUS_ "Status return codes".
 *
 * \page TriggerSystem Trigger system
 *
 * To trigger a device, several trigger sources can be available. These are divided in
 * \subpage triggering_devin sources and
 * \subpage triggering_scpch sources.
 *
 * Use ScpChHasTrigger() to check whether an oscilloscope channel supports trigger.
 *
 * To select a trigger source, enable it. Multiple trigger sources can be used, in that case they will be OR'ed.
 *
 * \subpage triggering_hs5 specific trigger information
 *
 * \subpage triggering_hs6d specific trigger information
 *
 * \subpage triggering_combi specific trigger information
 * \page triggering_devin Device trigger inputs
 *
 * A device can have zero or more device trigger inputs.
 * These can be available as pins on an extension connector on the instrument.
 * Internal signals inside the instrument from e.g. a generator can also be available as device trigger input.
 * Use the function #DevTrGetInputCount to determine the amount of available device trigger inputs.
 * To use a device trigger input as trigger source, use the function #DevTrInSetEnabled to enable it.
 *
 * \section triggering_devin_kind Kind
 *
 * The Kind setting controls how a device trigger input responds to its signal.
 * Use DevTrInGetKinds() to find out which trigger kinds are supported by the device trigger input.
 * Use DevTrInGetKind() and DevTrInSetKind() to access the trigger kind of a trigger input.
 * Available kinds are:
 *
 * \subsection triggering_devin_kind_rising Rising edge (TK_RISINGEDGE)
 *
 * The device trigger responds to a \b rising edge in the input signal.
 *
 *
 * \subsection triggering_devin_kind_falling Falling edge (TK_FALLINGEDGE)
 *
 * The device trigger responds to a \b falling edge in the input signal.
 *
 * Related:
 * - \ref dev_trigger_input_kind "all trigger input kind routines"
 * - \ref dev_trigger_input "trigger inputs".
 * \page triggering_scpch Oscilloscope channel trigger
 *
 * Each oscilloscope channel can be used as trigger source. To use an oscilloscope channel as trigger input, enable it using #ScpChTrSetEnabled.
 *
 * To control how and when the channel trigger responds to the channel input signal, several properties are available:
 * - \ref triggering_scpch_kind "Kind"
 * - \ref triggering_scpch_level "Level"
 * - \ref triggering_scpch_hysteresis "Hysteresis"
 * - \ref triggering_scpch_condition "Condition"
 * - \ref triggering_scpch_time "Time"
 *
 * \section triggering_scpch_kind Kind
 *
 * The kind property is used to control how the channel trigger responds to the channel input signal.
 * The other properties depend on the trigger kind that is selected.
 * Use ScpChTrGetKinds() to find out which trigger kinds are supported by the channel.
 * Available kinds are:
 *
 * \subsection triggering_scpch_kind_risingedge Rising edge (TK_RISINGEDGE)
 *
 * The channel trigger responds to a \b rising edge in the input signal.
 * The trigger uses Level[0] and Hysteresis[0] below the level to determine the rising edge.
 *
 * \subsection triggering_scpch_kind_fallingedge Falling edge (TK_FALLINGEDGE)
 *
 * The channel trigger responds to a \b falling edge in the input signal.
 * The trigger uses Level[0] and Hysteresis[0] above the level to determine the falling edge.
 *
 * \subsection triggering_scpch_kind_anyedge Any edge (TK_ANYEDGE)
 *
 * The channel trigger responds to \b any edge, either rising or falling, in the input signal.
 * The trigger uses Level[0], Hysteresis[0] above the level and Hysteresis[1] below level to determine the edges.
 *
 * \subsection triggering_scpch_kind_inwindow Inside window (TK_INWINDOW)
 *
 * The channel trigger responds when the input signal is \b inside a predefined window.
 * The trigger uses Level[0] and Level[1] to determine the window, there is no restriction to which level must be high and which must be low.
 * The trigger remains active as long as the signal is inside the window.
 *
 * \subsection triggering_scpch_kind_outwindow Outside window (TK_OUTWINDOW)
 *
 * The channel trigger responds when the input signal is \b outside a predefined window.
 * The trigger uses Level[0] and Level[1] to determine the window, there is no restriction to which level must be high and which must be low.
 * The trigger remains active as long as the signal is outside the window.
 *
 * \subsection triggering_scpch_kind_enterwindow Enter window (TK_ENTERWINDOW)
 *
 * The channel trigger responds when the input signal \b enters a predefined window.
 * The trigger uses Level[0] and Hysteresis[0] to define one limit of the window and Level[1] and Hysteresis[1] to determine the other limit of the window,
 * there is no restriction to which level must be high and which must be low. The hysteresis is outside the window defined by the levels.
 *
 * \subsection triggering_scpch_kind_exitwindow Exit window (TK_EXITWINDOW)
 *
 * The channel trigger responds when the input signal \b exits a predefined window.
 * The trigger uses Level[0] and Hysteresis[0] to define one limit of the window and Level[1] and Hysteresis[1] to determine the other limit of the window,
 * there is no restriction to which level must be high and which must be low. The hysteresis is inside the window defined by the levels.
 *
 * \subsection triggering_scpch_kind_pulsewidthpositive Pulse width positive (TK_PULSEWIDTHPOSITIVE)
 *
 * The channel trigger responds when the input signal contains a \b positive \b pulse with a length longer or shorter than a predefined value.
 * The trigger uses Level[0] and Hysteresis[0] to determine the rising and falling edges of the pulse.
 * It also uses Time[0] to define the required length of the pulse and Condition to indicate whether the pulse must be longer or shorter than the defined time.
 *
 * \subsection triggering_scpch_kind_pulsewidthnegative Pulse width negative (TK_PULSEWIDTHNEGATIVE)
 *
 * The channel trigger responds when the input signal contains a \b negative \b pulse with a length longer or shorter than a predefined value.
 * The trigger uses Level[0] and Hysteresis[0] to determine the falling and rising edges of the pulse.
 * It also uses Time[0] to define the required length of the pulse and Condition to indicate whether the pulse must be longer or shorter than the defined time.
 *
 * Read more about the channel trigger kind \ref scp_ch_tr_kind "related functions".
 *
 *
 * \section triggering_scpch_level Level
 *
 * Most trigger kinds use one or more level properties to indicate at which level(s) of the input signal the channel trigger must respond.
 * Use ScpChTrGetLevelCount() to find out how many trigger levels are used by the currently set trigger kind.
 *
 * The trigger level is set as a floating point value between 0 and 1, corresponding to a percentage of the full scale input range:
 * - 0.0 (0%) equals -full scale
 * - 0.5 (50%) equals mid level or 0 Volt
 * - 1.0 (100%) equals full scale.
 *
 * Read more about the trigger level \ref scp_ch_tr_level "related functions".
 *
 *
 * \section triggering_scpch_hysteresis Hysteresis
 *
 * Most trigger kinds use one or more hysteresis properties to indicate the sensitivity of the channel trigger.
 * With a small hysteresis, the trigger system responds to small input signal changes, with a large hysteresis, the input signal change must be large for the channel trigger to respond.
 * Use ScpChTrGetHysteresisCount() to determine the number of trigger hystereses for the currently set trigger kind.
 *
 * The trigger hysteresis is set as a floating point value between 0 and 1, corresponding to a percentage of the full scale input range:
 * - 0.0 (0%) equals 0 Volt (no hysteresis)
 * - 0.5 (50%) equals full scale
 * - 1.0 (100%) equals 2 * full scale.
 *
 * Read more about the trigger hysteresis \ref scp_ch_tr_hysteresis "related functions".
 *
 *
 * \section triggering_scpch_condition Condition
 *
 * Some trigger kinds require an additional condition to indicate how the channel trigger must respond to the input signal.
 *
 * The available trigger conditions depend on the currently set trigger kind.
 * Use ScpChTrGetConditions() to determine the available trigger conditions for the currently selected trigger kind.
 * Available conditions are:
 *
 * \subsection triggering_scpch_condition_larger Larger than (TC_LARGER)
 *
 * This trigger condition is available with pulse width trigger and uses property Time[0].
 * The trigger system responds when a trigger pulse lasts longer than the selected time.
 *
 * \subsection triggering_scpch_condition_smaller Smaller than (TC_SMALLER)
 *
 * This trigger condition is available with pulse width trigger and uses property Time[0].
 * The trigger system responds when a trigger pulse lasts shorter than the selected time.
 *
 * Read more about the trigger condition \ref scp_ch_tr_condition "related functions".
 *
 *
 * \section triggering_scpch_time Time
 *
 * Some trigger kinds and conditions use one or more Time properties to determine how long a specific condition must last for the channel trigger to respond.
 * Use ScpChTrGetTimeCount() to determine the number of trigger time properties for the currently set trigger kind and condition.
 *
 * The Time property is set as a value in seconds.
 *
 * Read more about the trigger time \ref scp_ch_tr_time "related functions".
 *
 * \page triggering_hs5 Handyscope HS5
 *
 * The <a class="External" href="http://www.tiepie.com/HS5">Handyscope HS5</a> consists of an oscilloscope, a generator and an I2C host.
 * Available trigger inputs for these devices are listed below.
 *
 * \section tr_hs5_scp Oscilloscope
 *
 * \subsection tr_hs5_scp_devin Device trigger inputs
 *
 * The Handyscope HS5 oscilloscope supports the following device trigger inputs:
 *
 * - Input[ 0 ]: <b>EXT 1</b> (pin 1 on D-sub connector)
 * - Input[ 1 ]: <b>EXT 2</b> (pin 2 on D-sub connector)
 * - Input[ 2 ]: <b>EXT 3</b> (pin 3 on D-sub connector)
 * - Input[ 3 ]: <b>Generator start</b>
 * - Input[ 4 ]: <b>Generator stop</b>
 * - Input[ 5 ]: <b>Generator new period</b>
 *
 * \subsection  tr_hs5_scp_chin Channel trigger inputs
 *
 * The Handyscope HS5 oscilloscope supports the following channel trigger inputs:
 *
 * - Channel[ 0 ]: <b>CH1</b>
 * - Channel[ 1 ]: <b>CH2</b>
 *
 * \section tr_hs5_gen Generator
 *
 * \subsection tr_hs5_gen_devin Device trigger inputs
 *
 * The Handyscope HS5 generator supports the following device trigger inputs:
 *
 * - Input[ 0 ]: <b>EXT 1</b> (pin 1 on D-sub connector)
 * - Input[ 1 ]: <b>EXT 2</b> (pin 2 on D-sub connector)
 * - Input[ 2 ]: <b>EXT 3</b> (pin 3 on D-sub connector)
 *
 * \page triggering_hs6d Handyscope HS6 DIFF
 *
 * The <a class="External" href="http://www.tiepie.com/HS6D">Handyscope HS6 DIFF</a> has external trigger inputs, listed below.
 *
 * \section tr_hs6d_scp Oscilloscope
 *
 * \subsection tr_hs6d_scp_devin Device trigger inputs
 *
 * The Handyscope HS6 DIFF oscilloscope supports the following device trigger inputs:
 *
 * - Input[ 0 ]: <b>EXT 1</b> (pin 1 on D-sub connector)
 * - Input[ 1 ]: <b>EXT 2</b> (pin 2 on D-sub connector)
 *
 * \subsection  tr_hs6d_scp_chin Channel trigger inputs
 *
 * The Handyscope HS6 DIFF oscilloscope supports the following channel trigger inputs:
 *
 * - Channel[ 0 ]: <b>CH1</b>
 * - Channel[ 1 ]: <b>CH2</b>
 * - Channel[ 2 ]: <b>CH3</b>
 * - Channel[ 3 ]: <b>CH4</b>
 *
 * \page triggering_combi Combined instruments
 *
 * When multiple instruments are combined, lists of trigger inputs are created by combining the trigger inputs of the individual instruments.
 * The lists starts with all trigger inputs of the first instrument in the chain, the instrument at the outside of the chain with the lowest serial number,
 * then subsequently the inputs of the next instrument(s) in the chain are added.
 * The name properties of device trigger inputs with a name will be prefixed with the instrument short name and serial number.
 *
 * The listed available trigger inputs below assume a combined instrument consisting of three Handyscope HS5s, with serial numbers 28000, 28002 and 28001 (connected in that order).
 *
 * \section tr_combi_scp Oscilloscope
 *
 * \subsection tr_combi_scp_devin Device trigger inputs
 *
 * The combined oscilloscope supports the following device trigger inputs:
 *
 * - Input[ 0 ]: <b>HS5(28000).EXT 1</b> (pin 1 on D-sub connector)
 * - Input[ 1 ]: <b>HS5(28000).EXT 2</b> (pin 2 on D-sub connector)
 * - Input[ 2 ]: <b>HS5(28000).EXT 3</b> (pin 3 on D-sub connector)
 * - Input[ 3 ]: <b>HS5(28000).Generator start</b>
 * - Input[ 4 ]: <b>HS5(28000).Generator stop</b>
 * - Input[ 5 ]: <b>HS5(28000).Generator new period</b>
 * - Input[ 6 ]: <b>HS5(28002).EXT 1</b> (pin 1 on D-sub connector)
 * - Input[ 7 ]: <b>HS5(28002).EXT 2</b> (pin 2 on D-sub connector)
 * - Input[ 8 ]: <b>HS5(28002).EXT 3</b> (pin 3 on D-sub connector)
 * - Input[ 9 ]: <b>HS5(28002).Generator start</b>
 * - Input[ 10 ]: <b>HS5(28002).Generator stop</b>
 * - Input[ 11 ]: <b>HS5(28002).Generator new period</b>
 * - Input[ 12 ]: <b>HS5(28001).EXT 1</b> (pin 1 on D-sub connector)
 * - Input[ 13 ]: <b>HS5(28001).EXT 2</b> (pin 2 on D-sub connector)
 * - Input[ 14 ]: <b>HS5(28001).EXT 3</b> (pin 3 on D-sub connector)
 * - Input[ 15 ]: <b>HS5(28001).Generator start</b>
 * - Input[ 16 ]: <b>HS5(28001).Generator stop</b>
 * - Input[ 17 ]: <b>HS5(28001).Generator new period</b>
 *
 * \subsection tr_combi_scp_chin Channel trigger inputs
 *
 * The combined oscilloscope supports the following channel trigger inputs:
 *
 * - Channel[ 0 ]: <b>HS5(28000).CH1</b>
 * - Channel[ 1 ]: <b>HS5(28000).CH2</b>
 * - Channel[ 2 ]: <b>HS5(28002).CH1</b>
 * - Channel[ 3 ]: <b>HS5(28002).CH2</b>
 * - Channel[ 4 ]: <b>HS5(28001).CH1</b>
 * - Channel[ 5 ]: <b>HS5(28001).CH2</b>
 *
 * \defgroup Const Constants
 * \{
 * \defgroup handles Handles
 * \{
 */

#define LIBTIEPIE_HANDLE_INVALID  0
#define TPDEVICEHANDLE_INVALID    LIBTIEPIE_HANDLE_INVALID //!< \deprecated Use: #LIBTIEPIE_HANDLE_INVALID

/**
 * \}
 * \defgroup INTERFACE_ Interfaces
 * \{
 */

#define LIBTIEPIE_INTERFACE_DEVICE        0x0000000000000001
#define LIBTIEPIE_INTERFACE_OSCILLOSCOPE  0x0000000000000002
#define LIBTIEPIE_INTERFACE_GENERATOR     0x0000000000000004
#define LIBTIEPIE_INTERFACE_I2CHOST       0x0000000000000008
#define LIBTIEPIE_INTERFACE_SERVER        0x0000000000000010

/**
 * \}
 * \defgroup DEVICETYPE_ Device type
 * \{
 */

#define DEVICETYPE_OSCILLOSCOPE  0x00000001 //!< Oscilloscope
#define DEVICETYPE_GENERATOR     0x00000002 //!< Generator
#define DEVICETYPE_I2CHOST       0x00000004 //!< I2C Host

#define DEVICETYPE_COUNT  3   //!< Number of device types

/**
 * \}
 * \defgroup IDKIND_ Id kind
 * \{
 */

#define IDKIND_PRODUCTID    0x00000001 //!< dwId parameter is a \ref PID_ "product id".
#define IDKIND_INDEX        0x00000002 //!< dwId parameter is an index.
#define IDKIND_SERIALNUMBER 0x00000004 //!< dwId parameter is a serial number.

#define IDKIND_COUNT  3  //!< Number of id kinds

/**
 * \}
 * \defgroup LIBTIEPIESTATUS_ Status return codes
 *
 *   These codes show the status of the last called LibTiePie function.
 *
 *   0  means ok\n
 *   <0 means error\n
 *   >0 means ok, but with a side effect\n
 * \{
 */

#define LIBTIEPIESTATUS_SUCCESS                                  0 //!< \brief The function executed successfully.
#define LIBTIEPIESTATUS_VALUE_CLIPPED                            1 //!< \brief One of the parameters of the last called function was outside the valid range and clipped to the closest limit.
#define LIBTIEPIESTATUS_VALUE_MODIFIED                           2 //!< \brief One of the parameters of the last called function was within the valid range but not available. The closest valid value is set.
#define LIBTIEPIESTATUS_UNSUCCESSFUL                            -1 //!< \brief An error occurred during execution of the last called function.
#define LIBTIEPIESTATUS_NOT_SUPPORTED                           -2 //!< \brief The requested functionality is not supported by the hardware.
#define LIBTIEPIESTATUS_INVALID_HANDLE                          -3 //!< \brief The handle to the device is invalid.
#define LIBTIEPIESTATUS_INVALID_VALUE                           -4 //!< \brief The requested value is invalid.
#define LIBTIEPIESTATUS_INVALID_CHANNEL                         -5 //!< \brief The requested channel number is invalid.
#define LIBTIEPIESTATUS_INVALID_TRIGGER_SOURCE                  -6 //!< \brief The requested trigger source is invalid.
#define LIBTIEPIESTATUS_INVALID_DEVICE_TYPE                     -7 //!< \brief The device type is invalid.
#define LIBTIEPIESTATUS_INVALID_DEVICE_INDEX                    -8 //!< \brief The device index is invalid, must be < LstGetCount().
#define LIBTIEPIESTATUS_INVALID_PRODUCT_ID                      -9 //!< \brief There is no device with the requested product ID.
#define LIBTIEPIESTATUS_INVALID_DEVICE_SERIALNUMBER            -10 //!< \brief There is no device with the requested serial number.
#define LIBTIEPIESTATUS_OBJECT_GONE                            -11 //!< \brief The object indicated by the handle is no longer available.
#define LIBTIEPIESTATUS_DEVICE_GONE    LIBTIEPIESTATUS_OBJECT_GONE //!< \deprecated Use: #LIBTIEPIESTATUS_OBJECT_GONE
#define LIBTIEPIESTATUS_INTERNAL_ADDRESS                       -12 //!< \brief The requested I<sup>2</sup>C address is an internally used address in the device.
#define LIBTIEPIESTATUS_NOT_CONTROLLABLE                       -13 //!< \brief The generator is currently not controllable, see #GenIsControllable.
#define LIBTIEPIESTATUS_BIT_ERROR                              -14 //!< \brief The requested I<sup>2</sup>C operation generated a bit error.
#define LIBTIEPIESTATUS_NO_ACKNOWLEDGE                         -15 //!< \brief The requested I<sup>2</sup>C operation generated "No acknowledge".
#define LIBTIEPIESTATUS_INVALID_CONTAINED_DEVICE_SERIALNUMBER  -16 //!< \brief A device with the requested serial number is not available in the combined instrument, see #LstDevGetContainedSerialNumbers.
#define LIBTIEPIESTATUS_INVALID_INPUT                          -17 //!< \brief The requested trigger input is invalid.
#define LIBTIEPIESTATUS_INVALID_OUTPUT                         -18 //!< \brief The requested trigger output is invalid.
#define LIBTIEPIESTATUS_INVALID_DRIVER                         -19 //!< \brief The currently installed driver is not supported, see LstDevGetRecommendedDriverVersion(). (Windows only)
#define LIBTIEPIESTATUS_NOT_AVAILABLE                          -20 //!< \brief With the current settings, the requested functionality is not available.
#define LIBTIEPIESTATUS_INVALID_FIRMWARE                       -21 //!< \brief The currently used firmware is not supported \cond EXTENDED_API , see LstDevGetRecommendedFirmwareVersion() \endcond.
#define LIBTIEPIESTATUS_INVALID_INDEX                          -22 //!< \brief The requested index is invalid.
#define LIBTIEPIESTATUS_INVALID_EEPROM                         -23 //!< \brief The instrument's EEPROM content is damaged, please contact TiePie engineering support.
#define LIBTIEPIESTATUS_INITIALIZATION_FAILED                  -24 //!< \brief The instrument's initialization failed, please contact TiePie engineering support.
#define LIBTIEPIESTATUS_LIBRARY_NOT_INITIALIZED                -25 //!< \brief The library is not initialized, see LibInit().
#define LIBTIEPIESTATUS_NO_TRIGGER_ENABLED                     -26 //!< \brief The current setup requires a trigger input to be enabled.

#define LIBTIEPIESTATUS_SYNCHRONIZATION_FAILED                 -29 //!< \brief XXX
#define LIBTIEPIESTATUS_INVALID_HS56_COMBINED_DEVICE           -30 //!< \brief At least one Handyscope HS6 DIFF must be located at the beginning or end of the CMI daisy chain.
#define LIBTIEPIESTATUS_MEASUREMENT_RUNNING                    -31 //!< \brief A measurement is already running.

#define LIBTIEPIESTATUS_INITIALIZATION_ERROR_10001          -10001 //!< \brief The instrument's initialization failed (code: 10001), please contact TiePie engineering support.
#define LIBTIEPIESTATUS_INITIALIZATION_ERROR_10002          -10002 //!< \brief The instrument's initialization failed (code: 10002), please contact TiePie engineering support.
#define LIBTIEPIESTATUS_INITIALIZATION_ERROR_10003          -10003 //!< \brief The instrument's initialization failed (code: 10003), please contact TiePie engineering support.
#define LIBTIEPIESTATUS_INITIALIZATION_ERROR_10004          -10004 //!< \brief The instrument's initialization failed (code: 10004), please contact TiePie engineering support.
#define LIBTIEPIESTATUS_INITIALIZATION_ERROR_10005          -10005 //!< \brief The instrument's initialization failed (code: 10005), please contact TiePie engineering support.
#define LIBTIEPIESTATUS_INITIALIZATION_ERROR_10006          -10006 //!< \brief The instrument's initialization failed (code: 10006), please contact TiePie engineering support.

/**
 * \}
 * \defgroup CONNECTORTYPE_ Connector types
 * \{
 */

#define CONNECTORTYPE_UNKNOWN  0x00000000

#define CONNECTORTYPE_BNC        0x00000001
#define CONNECTORTYPE_BANANA     0x00000002
#define CONNECTORTYPE_POWERPLUG  0x00000004

#define CONNECTORTYPE_COUNT  3  //!< Number of connector types

/**
 * \defgroup CONNECTORTYPE_MASK_ Masks
 * \{
 */

#define CONNECTORTYPE_MASK  ( CONNECTORTYPE_BNC | CONNECTORTYPE_BANANA | CONNECTORTYPE_POWERPLUG )

/**
 * \}
 * \}
 * \defgroup DATARAWTYPE_ Raw data types
 * \{
 */

#define DATARAWTYPE_UNKNOWN  0x00000000

#define DATARAWTYPE_INT8     0x00000001 //!< int8_t
#define DATARAWTYPE_INT16    0x00000002 //!< int16_t
#define DATARAWTYPE_INT32    0x00000004 //!< int32_t
#define DATARAWTYPE_INT64    0x00000008 //!< int64_t

#define DATARAWTYPE_UINT8    0x00000010 //!< uint8_t
#define DATARAWTYPE_UINT16   0x00000020 //!< uint16_t
#define DATARAWTYPE_UINT32   0x00000040 //!< uint32_t
#define DATARAWTYPE_UINT64   0x00000080 //!< uint64_t

#define DATARAWTYPE_FLOAT32  0x00000100 //!< float
#define DATARAWTYPE_FLOAT64  0x00000200 //!< double

#define DATARAWTYPE_COUNT  10  //!< Number of raw data types

/**
 * \defgroup DATARAWTYPE_MASK_ Masks
 * \{
 */

#define DATARAWTYPE_MASK_INT   ( DATARAWTYPE_INT8     | DATARAWTYPE_INT16     | DATARAWTYPE_INT32  | DATARAWTYPE_INT64  )
#define DATARAWTYPE_MASK_UINT  ( DATARAWTYPE_UINT8    | DATARAWTYPE_UINT16    | DATARAWTYPE_UINT32 | DATARAWTYPE_UINT64 )
#define DATARAWTYPE_MASK_FLOAT ( DATARAWTYPE_FLOAT32  | DATARAWTYPE_FLOAT64   )
#define DATARAWTYPE_MASK_FIXED ( DATARAWTYPE_MASK_INT | DATARAWTYPE_MASK_UINT )

/**
 * \}
 * \}
 * \defgroup BOOL8_ bool8_t values
 * \{
 */

#define BOOL8_FALSE 0
#define BOOL8_TRUE  1

/**
 * \}
 * \defgroup LIBTIEPIE_TRISTATE_ LibTiePieTriState_t values
 * \{
 */

#define LIBTIEPIE_TRISTATE_UNDEFINED 0 //!< Undefined
#define LIBTIEPIE_TRISTATE_FALSE     1 //!< False
#define LIBTIEPIE_TRISTATE_TRUE      2 //!< True

/**
 * \}
 * \defgroup LIBTIEPIE_TRIGGERINPUT_INDEX_ Trigger input index values
 * \{
 */

#define LIBTIEPIE_TRIGGERIO_INDEX_INVALID  0xffff

/**
 * \}
 * \defgroup LIBTIEPIE_STRING_LENGTH_ String length values
 * \{
 */

#define LIBTIEPIE_STRING_LENGTH_NULL_TERMINATED  0xffffffff

/**
 * \}
 * \defgroup LIBTIEPIE_SERVER_STATUS_ Server status
 * \{
 */

#define LIBTIEPIE_SERVER_STATUS_DISCONNECTED   0
#define LIBTIEPIE_SERVER_STATUS_CONNECTING     1
#define LIBTIEPIE_SERVER_STATUS_CONNECTED      2
#define LIBTIEPIE_SERVER_STATUS_DISCONNECTING  3

/**
 * \}
 * \defgroup LIBTIEPIE_SERVER_ERROR Server error codes
 * \{
 */

#define LIBTIEPIE_SERVER_ERROR_NONE                  0
#define LIBTIEPIE_SERVER_ERROR_UNKNOWN               1
#define LIBTIEPIE_SERVER_ERROR_CONNECTIONREFUSED     2
#define LIBTIEPIE_SERVER_ERROR_NETWORKUNREACHABLE    3
#define LIBTIEPIE_SERVER_ERROR_TIMEDOUT              4
#define LIBTIEPIE_SERVER_ERROR_HOSTNAMELOOKUPFAILED  5

/**
  *   \}
  */

//! \cond EXTENDED_API

/**
 * \defgroup LIBTIEPIE_RANGEINDEX_ Range index values
 * \{
 */

#define LIBTIEPIE_RANGEINDEX_AUTO  0xffffffff //!< Auto ranging

/**
 * \}
 */

//! \endcond

/**
 * \defgroup LIBTIEPIE_HELPER_FUNNCTION Helper functions values
 * \{
 */

#define LIBTIEPIE_POINTER_ARRAY_MAX_LENGTH 256

/**
 * \}
 * \defgroup AR_ Auto resolution modes
 * \{
 */

#define ARN_COUNT  3 //!< Number of auto resolution modes

/**
 * \defgroup ARB_ Bit numbers
 * \{
 */

#define ARB_DISABLED    0
#define ARB_NATIVEONLY  1
#define ARB_ALL         2

/**
 * \}
 */

#define AR_UNKNOWN     0 //!< Unknown/invalid mode

#define AR_DISABLED    ( 1 << ARB_DISABLED )   //!< Resolution does not automatically change.
#define AR_NATIVEONLY  ( 1 << ARB_NATIVEONLY ) //!< Highest possible native resolution for the current sample frequency is used.
#define AR_ALL         ( 1 << ARB_ALL )        //!< Highest possible native or enhanced resolution for the current sample frequency is used.

/**
 * \defgroup ARM_ Masks
 * \{
 */

#define ARM_NONE    0
#define ARM_ALL     ( ( 1 << ARN_COUNT ) - 1 )
#define ARM_ENABLED ( ARM_ALL & ~AR_DISABLED )

/**
 * \}
 * \}
 * \defgroup CK_ Coupling
 * \{
 */

#define CKN_COUNT  5 //!< Number of couplings

/**
 * \defgroup CKB_ Bit numbers
 * \{
 */

#define CKB_DCV    0  //!< Volt DC
#define CKB_ACV    1  //!< Volt AC
#define CKB_DCA    2  //!< Ampere DC
#define CKB_ACA    3  //!< Ampere AC
#define CKB_OHM    4  //!< Ohm

/**
 * \}
 */

#define CK_UNKNOWN 0                  //!< Unknown/invalid coupling

#define CK_DCV     ( 1 << CKB_DCV )   //!< Volt DC
#define CK_ACV     ( 1 << CKB_ACV )   //!< Volt AC
#define CK_DCA     ( 1 << CKB_DCA )   //!< Ampere DC
#define CK_ACA     ( 1 << CKB_ACA )   //!< Ampere AC
#define CK_OHM     ( 1 << CKB_OHM )   //!< Ohm

/**
 * \defgroup CKM_ Masks
 * \{
 */

#define CKM_NONE  0
#define CKM_V     ( CK_DCV | CK_ACV ) //!< Volt
#define CKM_A     ( CK_DCA | CK_ACA ) //!< Ampere
#define CKM_OHM   ( CK_OHM )          //!< Ohm

#define CKM_ASYMMETRICRANGE ( CKM_OHM )       //!< 0 to +Range
#define CKM_SYMMETRICRANGE  ( CKM_V | CKM_A ) //!< -Range to +Range

/**
 * \}
 * \}
 * \defgroup CO_ Clock output types
 * \{
 */

#define CON_COUNT  3 //!< Number of clock output types

/**
 * \defgroup COB_ Bit numbers
 * \{
 */

#define COB_DISABLED  0 //!< No clock output
#define COB_SAMPLE    1 //!< Sample clock
#define COB_FIXED     2 //!< Fixed clock

/**
 * \}
 */

#define CO_DISABLED  ( 1 << COB_DISABLED ) //!< No clock output
#define CO_SAMPLE    ( 1 << COB_SAMPLE )   //!< Sample clock
#define CO_FIXED     ( 1 << COB_FIXED )    //!< Fixed clock

/**
 * \defgroup COB_ Bit numbers
 * \{
 */

#define COM_NONE       0
#define COM_ALL        ( ( 1 << CON_COUNT ) - 1 )
#define COM_ENABLED    ( COM_ALL & ~CO_DISABLED )
#define COM_FREQUENCY  ( CO_FIXED )

/**
 * \}
 * \}
 * \defgroup CS_ Clock sources
 * \{
 */

#define CSN_COUNT  2 //!< Number of clock sources

/**
 * \defgroup CSB_ Bit numbers
 * \{
 */

#define CSB_EXTERNAL  0 //!< External clock
#define CSB_INTERNAL  1 //!< Internal clock

/**
 * \}
 */

#define CS_EXTERNAL  ( 1 << CSB_EXTERNAL )  //!< External clock
#define CS_INTERNAL  ( 1 << CSB_INTERNAL )  //!< Internal clock

/**
 * \defgroup CSM_ Masks
 * \{
 */

#define CSM_NONE       0
#define CSM_ALL        ( ( 1 << CSN_COUNT ) - 1 )
#define CSM_FREQUENCY  ( CS_EXTERNAL )

/**
 * \}
 * \}
 * \defgroup FM_ Frequency modes
 * \{
 */

#define FMN_COUNT  2 //!< Number of frequency modes

/**
 * \defgroup FMB_ Bit numbers
 * \{
 */

#define FMB_SIGNALFREQUENCY  0
#define FMB_SAMPLEFREQUENCY  1

/**
 * \}
 */

#define FM_UNKNOWN 0x00000000

#define FM_SIGNALFREQUENCY  ( 1 << FMB_SIGNALFREQUENCY )
#define FM_SAMPLEFREQUENCY  ( 1 << FMB_SAMPLEFREQUENCY )

/**
 * \defgroup FMM_ Masks
 * \{
 */

#define FMM_NONE  0x00000000
#define FMM_ALL   ( ( 1 << FMN_COUNT ) - 1 )

/**
 * \}
 * \}
 * \defgroup GM_ Generator modes
 * \{
 */

#define GMN_COUNT  12 //!< Number of generator modes

/**
 * \defgroup GMB_ Bit numbers
 * \{
 */

#define GMB_CONTINUOUS                  0
#define GMB_BURST_COUNT                 1
#define GMB_GATED_PERIODS               2
#define GMB_GATED                       3
#define GMB_GATED_PERIOD_START          4
#define GMB_GATED_PERIOD_FINISH         5
#define GMB_GATED_RUN                   6
#define GMB_GATED_RUN_OUTPUT            7
#define GMB_BURST_SAMPLE_COUNT          8
#define GMB_BURST_SAMPLE_COUNT_OUTPUT   9
#define GMB_BURST_SEGMENT_COUNT         10
#define GMB_BURST_SEGMENT_COUNT_OUTPUT  11

/**
 * \}
 */

#define GM_UNKNOWN  0

#define GM_CONTINUOUS                  ( 1 << GMB_CONTINUOUS )
#define GM_BURST_COUNT                 ( 1 << GMB_BURST_COUNT )
#define GM_GATED_PERIODS               ( 1 << GMB_GATED_PERIODS )
#define GM_GATED                       ( 1 << GMB_GATED )
#define GM_GATED_PERIOD_START          ( 1 << GMB_GATED_PERIOD_START )
#define GM_GATED_PERIOD_FINISH         ( 1 << GMB_GATED_PERIOD_FINISH )
#define GM_GATED_RUN                   ( 1 << GMB_GATED_RUN )
#define GM_GATED_RUN_OUTPUT            ( 1 << GMB_GATED_RUN_OUTPUT )
#define GM_BURST_SAMPLE_COUNT          ( 1 << GMB_BURST_SAMPLE_COUNT )
#define GM_BURST_SAMPLE_COUNT_OUTPUT   ( 1 << GMB_BURST_SAMPLE_COUNT_OUTPUT )
#define GM_BURST_SEGMENT_COUNT         ( 1 << GMB_BURST_SEGMENT_COUNT )
#define GM_BURST_SEGMENT_COUNT_OUTPUT  ( 1 << GMB_BURST_SEGMENT_COUNT_OUTPUT )

/**
 * \defgroup GMM_ Masks
 * \{
 */

#define GMM_NONE                 0
#define GMM_BURST_COUNT          ( GM_BURST_COUNT )
#define GMM_GATED                ( GM_GATED_PERIODS | GM_GATED | GM_GATED_PERIOD_START | GM_GATED_PERIOD_FINISH | GM_GATED_RUN | GM_GATED_RUN_OUTPUT )
#define GMM_BURST_SAMPLE_COUNT   ( GM_BURST_SAMPLE_COUNT | GM_BURST_SAMPLE_COUNT_OUTPUT )
#define GMM_BURST_SEGMENT_COUNT  ( GM_BURST_SEGMENT_COUNT | GM_BURST_SEGMENT_COUNT_OUTPUT )
#define GMM_BURST                ( GMM_BURST_COUNT | GMM_BURST_SAMPLE_COUNT | GMM_BURST_SEGMENT_COUNT )
#define GMM_REQUIRE_TRIGGER      ( GMM_GATED | GMM_BURST_SAMPLE_COUNT | GMM_BURST_SEGMENT_COUNT )  //!< Generator modes that require an enabeld trigger input.
#define GMM_ALL                  ( ( 1ULL << GMN_COUNT ) - 1 )

#define GMM_SIGNALFREQUENCY  ( GMM_ALL & ~GMM_BURST_SAMPLE_COUNT )  //!< Supported generator modes when frequency mode is signal frequency.
#define GMM_SAMPLEFREQUENCY  ( GMM_ALL )                            //!< Supported generator modes when frequency mode is sample frequency.

#define GMM_SINE         ( GMM_SIGNALFREQUENCY )                             //!< Supported generator modes when signal type is sine.
#define GMM_TRIANGLE     ( GMM_SIGNALFREQUENCY )                             //!< Supported generator modes when signal type is triangle.
#define GMM_SQUARE       ( GMM_SIGNALFREQUENCY )                             //!< Supported generator modes when signal type is square.
#define GMM_DC           ( GM_CONTINUOUS )                                   //!< Supported generator modes when signal type is DC.
#define GMM_NOISE        ( GM_CONTINUOUS | GM_GATED )                        //!< Supported generator modes when signal type is noise.
#define GMM_ARBITRARY    ( GMM_SIGNALFREQUENCY | GMM_SAMPLEFREQUENCY )       //!< Supported generator modes when signal type is arbitrary.
#define GMM_PULSE        ( GMM_SIGNALFREQUENCY & ~GMM_BURST_SEGMENT_COUNT )  //!< Supported generator modes when signal type is pulse.

/**
 * \}
 * \}
 * \defgroup GS_ Generator status flags
 * \{
 * \brief Flags to indicate the signal generation status of a generator.
 */

#define GSN_COUNT  4 //!< The number of generator status flags.

/**
 * \defgroup GSB_ Bit numbers
 * \{
 * \brief Bit numbers used to create the signal generation status flags of a generator.
 */

#define GSB_STOPPED      0
#define GSB_RUNNING      1
#define GSB_BURSTACTIVE  2
#define GSB_WAITING      3

/**
 * \}
 */

#define GS_STOPPED      ( 1 << GSB_STOPPED )     //!< The signal generation is stopped.
#define GS_RUNNING      ( 1 << GSB_RUNNING )     //!< The signal generation is running.
#define GS_BURSTACTIVE  ( 1 << GSB_BURSTACTIVE ) //!< The generator is operating in burst mode.
#define GS_WAITING      ( 1 << GSB_WAITING )     //!< The generator is waiting for a burst to be started.

/**
 * \defgroup GSM_ Masks
 * \{
 */

#define GSM_NONE  0
#define GSM_ALL   ( ( 1UL << GSN_COUNT ) - 1 )

/**
 * \}
 * \}
 * \defgroup MM_ Measure modes
 * \{
 */

#define MMN_COUNT  2 //!< Number of measure modes

/**
 * \defgroup MMB_ Bit numbers
 * \{
 */

#define MMB_STREAM 0 //!< Stream mode bit number
#define MMB_BLOCK  1 //!< Block mode bit number

/**
 * \}
 * \defgroup MMM_ Masks
 * \{
 */

#define MMM_NONE 0
#define MMM_ALL  ( ( 1 << MMN_COUNT ) - 1 )

/**
 * \}
 */

#define MM_UNKNOWN 0                   //!< Unknown/invalid mode

#define MM_STREAM  ( 1 << MMB_STREAM ) //!< Stream mode
#define MM_BLOCK   ( 1 << MMB_BLOCK  ) //!< Block mode

/**
 * \}
 * \defgroup ST_ Signal types
 * \{
 */

#define STN_COUNT  7 //!< Number of signal types

/**
 * \defgroup STB_ Bit numbers
 * \{
 */

#define STB_SINE       0
#define STB_TRIANGLE   1
#define STB_SQUARE     2
#define STB_DC         3
#define STB_NOISE      4
#define STB_ARBITRARY  5
#define STB_PULSE      6

/**
 * \}
 */

#define ST_UNKNOWN     0

#define ST_SINE        ( 1 << STB_SINE )
#define ST_TRIANGLE    ( 1 << STB_TRIANGLE )
#define ST_SQUARE      ( 1 << STB_SQUARE )
#define ST_DC          ( 1 << STB_DC )
#define ST_NOISE       ( 1 << STB_NOISE )
#define ST_ARBITRARY   ( 1 << STB_ARBITRARY )
#define ST_PULSE       ( 1 << STB_PULSE )

/**
 * \defgroup STM_ Signal type masks
 * \{
 */

#define STM_NONE       0

#define STM_AMPLITUDE         ( ST_SINE | ST_TRIANGLE | ST_SQUARE         | ST_NOISE | ST_ARBITRARY | ST_PULSE )
#define STM_OFFSET            ( ST_SINE | ST_TRIANGLE | ST_SQUARE | ST_DC | ST_NOISE | ST_ARBITRARY | ST_PULSE )
#define STM_FREQUENCY         ( ST_SINE | ST_TRIANGLE | ST_SQUARE         | ST_NOISE | ST_ARBITRARY | ST_PULSE )
#define STM_PHASE             ( ST_SINE | ST_TRIANGLE | ST_SQUARE                    | ST_ARBITRARY | ST_PULSE )
#define STM_SYMMETRY          ( ST_SINE | ST_TRIANGLE | ST_SQUARE                                              )
#define STM_WIDTH             (                                                                       ST_PULSE )
#define STM_LEADINGEDGETIME   (                                                                       ST_PULSE )
#define STM_TRAILINGEDGETIME  (                                                                       ST_PULSE )
#define STM_DATALENGTH        (                                                        ST_ARBITRARY            )
#define STM_DATA              (                                                        ST_ARBITRARY            )

#define STM_EDGETIME ( STM_LEADINGEDGETIME & STM_TRAILINGEDGETIME )

/**
 * \}
 * \}
 * \defgroup TC_ Trigger conditions
 * \{
 */

#define TCN_COUNT  5 //!< Number of trigger conditions

/**
 * \defgroup TCB_ Bit numbers
 * \{
 */

#define TCB_NONE     0
#define TCB_SMALLER  1
#define TCB_LARGER   2
#define TCB_INSIDE   3
#define TCB_OUTSIDE  4

/**
 * \}
 */

#define TC_UNKNOWN  0

#define TC_NONE     ( 1 << TCB_NONE )
#define TC_SMALLER  ( 1 << TCB_SMALLER )
#define TC_LARGER   ( 1 << TCB_LARGER )
#define TC_INSIDE   ( 1 << TCB_INSIDE )
#define TC_OUTSIDE  ( 1 << TCB_OUTSIDE )

/**
 * \defgroup TCM_ Masks
 * \{
 */

#define TCM_NONE     0 //!< No conditions
#define TCM_ALL      ( ( 1 << TCN_COUNT ) - 1 ) //!< All conditions
#define TCM_ENABLED  ( TCM_ALL & ~TC_NONE ) //!< All conditions except #TC_NONE.

/**
 * \}
 * \}
 * \defgroup TH_ Trigger holdoff
 * \{
 */

#define TH_ALLPRESAMPLES 0xffffffffffffffffULL //!< Trigger hold off to <b>all presamples valid</b>

/**
 * \}
 * \defgroup TIOID_ Trigger input/output ID's
 * \{
 * \defgroup DN_ Device Numbers
 * \{
 */

#define DN_MAIN        0 //!< The device itself.
#define DN_SUB_FIRST   1 //!< First sub device in a combined device.
#define DN_SUB_SECOND  2 //!< Second sub device in a combined device.

/**
 * \}
 * \defgroup PGID_ Port Group ID's
 * \{
 */

#define PGID_OSCILLOSCOPE   1 //!< Oscilloscope
#define PGID_GENERATOR      2 //!< Generator
#define PGID_EXTERNAL_DSUB  3 //!< External D-sub

/**
 * \}
 * \defgroup SGID_ Device Sub Group ID's
 * \{
 * \defgroup SGID_scpgen Oscilloscope or generator
 * \{
 */

#define SGID_MAIN      0 //!< The oscilloscope or function generator itself.
#define SGID_CHANNEL1  1
#define SGID_CHANNEL2  2

/**
 * \}
 * \defgroup SGID_ext External
 * \{
 */

#define SGID_PIN1  1
#define SGID_PIN2  2
#define SGID_PIN3  3

/**
 * \}
 * \}
 * \defgroup FID_ Function ID's
 * \{
 * \defgroup FID_SCP Oscilloscopes and oscilloscope channels
 * \{
 */

#define FID_SCP_TRIGGERED  0

/**
 * \}
 * \defgroup FID_GEN Generators
 * \{
 */

#define FID_GEN_START       0
#define FID_GEN_STOP        1
#define FID_GEN_NEW_PERIOD  2

/**
 * \}
 * \defgroup FID_EXT External
 * \{
 */

#define FID_EXT_TRIGGERED  0

/**
 * \}
 * \}
 * \defgroup TIOID_SC_ Shift constants
 * \{
 */

#define TIOID_SHIFT_PGID  20
#define TIOID_SHIFT_DN    24
#define TIOID_SHIFT_SGID  8
#define TIOID_SHIFT_FID   0

/**
 * \}
 * \defgroup TIID_ Trigger input ID's
 * \{
 */

#define TIID_INVALID              0
#define TIID_EXT1                 TRIGGER_IO_ID( PGID_EXTERNAL_DSUB , SGID_PIN1 , FID_EXT_TRIGGERED  )
#define TIID_EXT2                 TRIGGER_IO_ID( PGID_EXTERNAL_DSUB , SGID_PIN2 , FID_EXT_TRIGGERED  )
#define TIID_EXT3                 TRIGGER_IO_ID( PGID_EXTERNAL_DSUB , SGID_PIN3 , FID_EXT_TRIGGERED  )
#define TIID_GENERATOR_START      TRIGGER_IO_ID( PGID_GENERATOR     , SGID_MAIN , FID_GEN_START      )
#define TIID_GENERATOR_STOP       TRIGGER_IO_ID( PGID_GENERATOR     , SGID_MAIN , FID_GEN_STOP       )
#define TIID_GENERATOR_NEW_PERIOD TRIGGER_IO_ID( PGID_GENERATOR     , SGID_MAIN , FID_GEN_NEW_PERIOD )

/**
 * \}
 * \defgroup TOID_ Trigger output ID's
 * \{
 */

#define TOID_INVALID  0
#define TOID_EXT1     TRIGGER_IO_ID( PGID_EXTERNAL_DSUB , SGID_PIN1 , FID_EXT_TRIGGERED )
#define TOID_EXT2     TRIGGER_IO_ID( PGID_EXTERNAL_DSUB , SGID_PIN2 , FID_EXT_TRIGGERED )
#define TOID_EXT3     TRIGGER_IO_ID( PGID_EXTERNAL_DSUB , SGID_PIN3 , FID_EXT_TRIGGERED )

/**
 * \}
 * \}
 * \defgroup TK_ Trigger kinds
 * \{
 */

#define TKN_COUNT  15 //!< Number of trigger kinds

/**
 * \defgroup TKB_ Bit numbers
 * \{
 */

#define TKB_RISINGEDGE          0
#define TKB_FALLINGEDGE         1
#define TKB_INWINDOW            2
#define TKB_OUTWINDOW           3
#define TKB_ANYEDGE             4
#define TKB_ENTERWINDOW         5
#define TKB_EXITWINDOW          6
#define TKB_PULSEWIDTHPOSITIVE  7
#define TKB_PULSEWIDTHNEGATIVE  8
#define TKB_PULSEWIDTHEITHER    9
#define TKB_RUNTPULSEPOSITIVE  10
#define TKB_RUNTPULSENEGATIVE  11
#define TKB_RUNTPULSEEITHER    12
#define TKB_INTERVALRISING     13
#define TKB_INTERVALFALLING    14

/**
 * \}
 */

#define TK_UNKNOWN            0                                   //!< Unknown/invalid trigger kind
#define TK_RISINGEDGE         ( 1ULL << TKB_RISINGEDGE )          //!< Rising edge
#define TK_FALLINGEDGE        ( 1ULL << TKB_FALLINGEDGE )         //!< Falling edge
#define TK_INWINDOW           ( 1ULL << TKB_INWINDOW )            //!< Inside window
#define TK_OUTWINDOW          ( 1ULL << TKB_OUTWINDOW )           //!< Outside window
#define TK_ANYEDGE            ( 1ULL << TKB_ANYEDGE )             //!< Any edge
#define TK_ENTERWINDOW        ( 1ULL << TKB_ENTERWINDOW )         //!< Enter window
#define TK_EXITWINDOW         ( 1ULL << TKB_EXITWINDOW )          //!< Exit window
#define TK_PULSEWIDTHPOSITIVE ( 1ULL << TKB_PULSEWIDTHPOSITIVE )  //!< Positive pulse width
#define TK_PULSEWIDTHNEGATIVE ( 1ULL << TKB_PULSEWIDTHNEGATIVE )  //!< Negative pulse width
#define TK_PULSEWIDTHEITHER   ( 1ULL << TKB_PULSEWIDTHEITHER )    //!< Positive or negative pulse width
#define TK_RUNTPULSEPOSITIVE  ( 1ULL << TKB_RUNTPULSEPOSITIVE )   //!< Positive runt pulse
#define TK_RUNTPULSENEGATIVE  ( 1ULL << TKB_RUNTPULSENEGATIVE )   //!< Negative runt pulse
#define TK_RUNTPULSEEITHER    ( 1ULL << TKB_RUNTPULSEEITHER )     //!< Positive or negative runt pulse
#define TK_INTERVALRISING     ( 1ULL << TKB_INTERVALRISING )      //!< Interval (rising edge)
#define TK_INTERVALFALLING    ( 1ULL << TKB_INTERVALFALLING )     //!< Interval (falling edge)

/**
 * \defgroup TKM_ Masks
 * \{
 */

#define TKM_NONE             0 //!< No trigger kinds
#define TKM_EDGE             ( TK_RISINGEDGE | TK_FALLINGEDGE | TK_ANYEDGE ) //!< All edge triggers
#define TKM_WINDOW           ( TK_INWINDOW | TK_OUTWINDOW | TK_ENTERWINDOW | TK_EXITWINDOW ) //!< All window triggers
#define TKM_PULSEWIDTH       ( TK_PULSEWIDTHPOSITIVE | TK_PULSEWIDTHNEGATIVE | TK_PULSEWIDTHEITHER ) //!< All pulse width triggers
#define TKM_RUNTPULSE        ( TK_RUNTPULSEPOSITIVE | TK_RUNTPULSENEGATIVE | TK_RUNTPULSEEITHER ) //!< All runt pulse triggers
#define TKM_PULSE            ( TKM_PULSEWIDTH | TKM_RUNTPULSE ) //!< All pulse triggers
#define TKM_INTERVAL         ( TK_INTERVALRISING | TK_INTERVALFALLING ) //!< All interval triggers
#define TKM_TIME             ( TKM_PULSEWIDTH | TKM_WINDOW | TKM_INTERVAL ) //!< All trigger kinds that may have a time property.
#define TKM_ALL              ( ( 1ULL << TKN_COUNT ) - 1 ) //!< All trigger kinds

/**
 * \}
 * \}
 * \defgroup TLM_ Trigger level modes
 * \{
 */

#define TLMN_COUNT  2 //!< Number of trigger level modes

/**
 * \defgroup TLMB_ Bit numbers
 * \{
 */

#define TLMB_RELATIVE  0
#define TLMB_ABSOLUTE  1

/**
 * \}
 */

#define TLM_UNKNOWN  0

#define TLM_RELATIVE  ( 1 << TLMB_RELATIVE )
#define TLM_ABSOLUTE  ( 1 << TLMB_ABSOLUTE )

/**
 * \defgroup TLMM_ Masks
 * \{
 */

#define TLMM_NONE  0
#define TLMM_ALL   ( ( 1 << TLMN_COUNT ) - 1 )

/**
 * \}
 * \}
 * \defgroup TO_ Trigger time outs
 * \{
 */

#define TO_INFINITY -1 //!< No time out

/**
 * \}
 * \defgroup TOE_ Trigger output events
 * \{
 */

#define TOEN_COUNT  6 //!< Number of trigger output events

/**
 * \defgroup TOEB_ Bit numbers
 * \{
 */

#define TOEB_GENERATOR_START         0
#define TOEB_GENERATOR_STOP          1
#define TOEB_GENERATOR_NEWPERIOD     2
#define TOEB_OSCILLOSCOPE_RUNNING    3
#define TOEB_OSCILLOSCOPE_TRIGGERED  4
#define TOEB_MANUAL                  5

/**
 * \}
 */

#define TOE_UNKNOWN                 0
#define TOE_GENERATOR_START         ( 1 << TOEB_GENERATOR_START )
#define TOE_GENERATOR_STOP          ( 1 << TOEB_GENERATOR_STOP )
#define TOE_GENERATOR_NEWPERIOD     ( 1 << TOEB_GENERATOR_NEWPERIOD )
#define TOE_OSCILLOSCOPE_RUNNING    ( 1 << TOEB_OSCILLOSCOPE_RUNNING )
#define TOE_OSCILLOSCOPE_TRIGGERED  ( 1 << TOEB_OSCILLOSCOPE_TRIGGERED )
#define TOE_MANUAL                  ( 1 << TOEB_MANUAL )

/**
 * \defgroup TOEM_ Masks
 * \{
 */

#define TOEM_NONE             0 //!< No trigger output events
#define TOEM_GENERATOR        ( TOE_GENERATOR_START | TOE_GENERATOR_STOP | TOE_GENERATOR_NEWPERIOD ) //!< All generator trigger output events
#define TOEM_OSCILLOSCOPE     ( TOE_OSCILLOSCOPE_RUNNING | TOE_OSCILLOSCOPE_TRIGGERED ) //!< All oscilloscope trigger output events
#define TOEM_ALL              ( ( 1ULL << TOEN_COUNT ) - 1 ) //!< All trigger output events

/**
 * \}
 * \}
 * \defgroup PID_ Product ID's
 * \{
 */

#define PID_NONE        0 //!< Unknown/invalid ID
#define PID_COMBI       2 //!< Combined instrument

#define PID_HS3            13 //!< Handyscope HS3
#define PID_HS4            15 //!< Handyscope HS4
#define PID_HP3            18 //!< Handyprobe HP3
#define PID_TP450          19 //!< TP450
#define PID_HS4D           20 //!< Handyscope HS4-DIFF
#define PID_HS5            22 //!< Handyscope HS5
#define PID_HS6            24 //!< Handyscope HS6
#define PID_HS6D           25 //!< Handyscope HS6 DIFF
#define PID_ATS610004D     31 //!< ATS610004D
#define PID_ATS605004D     32 //!< ATS605004D
#define PID_125020VI       33 //!< Virtual instrument 1250-20
#define PID_WS6            34 //!< WiFiScope WS6
#define PID_WS5            35 //!< WiFiScope WS5
#define PID_WS6D           36 //!< WiFiScope WS6D
#define PID_ATS610004DW    37 //!< ATS610004DW
#define PID_ATS605004DW    38 //!< ATS605004DW
#define PID_WS4D           39 //!< WiFiScope WS4D
#define PID_ATS5004DW      40 //!< ATS5004DW

/**
 * \}
 * \defgroup EVENTID_ Event ID's
 * \{
 * \brief Event IDs for events that can be used by LibTiePie to \ref obj_notifications "notify" the calling application of changes with the instrument.
 *
 *      See also \ref obj_notifications "object notifications".
 */

#define LIBTIEPIE_EVENTID_INVALID                          0 //!< This event ID value should not occur.
#define LIBTIEPIE_EVENTID_OBJ_REMOVED                      1 //!< Event ID for the event indicating that an object was removed.
#define LIBTIEPIE_EVENTID_SCP_DATAREADY                    2 //!< Event ID for the event indicating that the \ref ScpIsDataReady "oscilloscope measurement is ready".
#define LIBTIEPIE_EVENTID_SCP_DATAOVERFLOW                 3 //!< Event ID for the event indicating that the \ref ScpIsDataOverflow "data overflow" occurred during a streaming measurement.
#define LIBTIEPIE_EVENTID_SCP_CONNECTIONTESTCOMPLETED      4 //!< Event ID for the event indicating that the \ref scp_ct "connection test is ready.
#define LIBTIEPIE_EVENTID_SCP_TRIGGERED                    5 //!< Event ID for the event indicating that the oscilloscope has triggered.
#define LIBTIEPIE_EVENTID_GEN_BURSTCOMPLETED               6 //!< Event ID for the event indicating that the generator burst is completed.
#define LIBTIEPIE_EVENTID_GEN_CONTROLLABLECHANGED          7 //!< Event ID for the event indicating that the generator controllable state has changed.
#define LIBTIEPIE_EVENTID_SRV_STATUSCHANGED                8 //!< XXX
#define LIBTIEPIE_EVENTID_SCP_SAFEGROUNDERROR              9 //!< Event ID for the event indicating that the oscilloscope channel \ref scp_ch_safe_ground "SafeGround" was disabled because of a too large ground current. The value parameter of the event contains the channel number (\c 0 to \c ChannelCount-1).
/** \cond EXTENDED_API
 */
#define LIBTIEPIE_EVENTID_SCP_GETDATAASYNCCOMPLETED        10 //!< XXX
/** \endcond.
 */
#define LIBTIEPIE_EVENTID_DEV_BATTERYSTATUSCHANGED         11 //!< XXX

/**
 * \}
 * \}
 * \defgroup types Types
 * \{
 */

typedef int32_t  LibTiePieStatus_t;         //!< LibTiePie status code. \see LIBTIEPIESTATUS_
typedef uint32_t LibTiePieHandle_t;         //!< Generic handle.
typedef LibTiePieHandle_t TpDeviceHandle_t; //!< \deprecated Use: #LibTiePieHandle_t

/**
 * \brief Data type representing a version number.
 *
 * The version number is a packed type containing:
 * - \b Major number in bits 63 to 48, use macro #TPVERSION_MAJOR to extract the major number.
 * - \b Minor number in bits 47 to 32, use macro #TPVERSION_MINOR to extract the minor number.
 * - \b Release number in bits 31 to 16, use macro #TPVERSION_RELEASE to extract the release number.
 * - \b Build number in bits 15 to 0, use macro #TPVERSION_BUILD to extract the build number.
 *
 * \see LibGetVersion()
 * \see LstDevGetDriverVersion()
 * \see LstDevGetRecommendedDriverVersion()
 * \see LstDevGetFirmwareVersion()
 * \cond EXTENDED_API
 * \see LstDevGetRecommendedFirmwareVersion()
 * \endcond
 * \see DevGetDriverVersion()
 * \see DevGetFirmwareVersion()
 * \par Example
 * \code{.c}
 * TpVersion_t Version = LibGetVersion();
 * uint16_t wMajor     = TPVERSION_MAJOR( Version );
 * uint16_t wMinor     = TPVERSION_MINOR( Version );
 * uint16_t wRelease   = TPVERSION_RELEASE( Version );
 * uint16_t wBuild     = TPVERSION_BUILD( Version );
 *
 * printf( "LibGetVersion = %u.%u.%u.%u\n" , wMajor , wMinor , wRelease , wBuild );
 * \endcode
 */
typedef uint64_t TpVersion_t;

/**
 * \brief Data type representing a date.
 *
 * The date is a packed type containing:
 * - \b Year in bits 31 to 16, use macro #TPDATE_YEAR to extract the year
 * - \b Month in bits 15 to 8, use macro #TPDATE_MONTH to extract the month
 * - \b Day in bits 7 to 0, use macro #TPDATE_DAY to extract the day
 *
 * \see LstDevGetCalibrationDate()
 * \see LstCbDevGetCalibrationDate()
 * \see DevGetCalibrationDate()
 * \par Example
 * \code{.c}
 * TpDate_t Date    = DevGetCalibrationDate( hDevice );
 * uint16_t wYear   = TPDATE_YEAR( Date );
 * uint8_t  byMonth = TPDATE_MONTH( Date );
 * uint8_t  byDay   = TPDATE_DAY( Date );
 * \endcode
 */
typedef uint32_t TpDate_t;
typedef uint8_t  bool8_t;                 //!< Boolean value one byte wide. \see BOOL8_
typedef uint8_t  LibTiePieTriState_t;     //!< TriState value one byte wide. \see LIBTIEPIE_TRISTATE_
typedef void**   LibTiePiePointerArray_t; //!< Pointer array \see hlp_ptrar

#ifdef INCLUDED_BY_MATLAB
typedef void* TpCallback_t;
typedef void* TpCallbackDeviceList_t;
typedef void* TpCallbackHandle_t;
typedef void* TpCallbackEvent_t;
#else
typedef void(*TpCallback_t)( void* pData );
typedef void(*TpCallbackDeviceList_t)( void* pData , uint32_t dwDeviceTypes , uint32_t dwSerialNumber );
typedef void(*TpCallbackHandle_t)( void* pData , LibTiePieHandle_t hHandle );
typedef void(*TpCallbackEvent_t)( void* pData , uint32_t dwEvent , uint32_t dwValue );
#endif

/**
 * \}
 * \defgroup macro Macros
 * \{
 */

#define TPVERSION_MAJOR( x )    ( x >> 48 )               //!< Extract the major number from a #TpVersion_t value.
#define TPVERSION_MINOR( x )    ( ( x >> 32 ) & 0xffff )  //!< Extract the minor number from a #TpVersion_t value.
#define TPVERSION_RELEASE( x )  ( ( x >> 16 ) & 0xffff )  //!< Extract the release number from a #TpVersion_t value.
#define TPVERSION_BUILD( x )    ( x & 0xffff )            //!< Extract the build number from a #TpVersion_t value.

#define TPDATE_YEAR( x )  ( x >> 16 )            //!< Extract year from a #TpDate_t value.
#define TPDATE_MONTH( x ) ( ( x >> 8 ) & 0xff )  //!< Extract month from a #TpDate_t value.
#define TPDATE_DAY( x )   ( x & 0xff )           //!< Extract day from a #TpDate_t value.

#define TRIGGER_IO_ID( pgid  , sgid , fid )  ( ( DN_MAIN << TIOID_SHIFT_DN ) | ( ( pgid ) << TIOID_SHIFT_PGID ) | ( ( sgid ) << TIOID_SHIFT_SGID ) | ( ( fid ) << TIOID_SHIFT_FID ) )

#define COMBI_TRIGGER_IO_ID( dn , tiid )  ( ( ( dn ) << TIOID_SHIFT_DN ) | ( ( tiid ) & ( ( 1 << TIOID_SHIFT_DN ) - 1 ) ) )

/**
 * \}
 */

#ifdef LIBTIEPIE_WINDOWS

/**
 * \defgroup messages Messages
 * \{
 */

#define WM_LIBTIEPIE                              ( WM_USER + 1337 ) //!< Message number offset used by LibTiePie.

#define WM_LIBTIEPIE_LST_DEVICEADDED              ( WM_LIBTIEPIE + 2 ) //!< \see LstSetMessageDeviceAdded
#define WM_LIBTIEPIE_LST_DEVICEREMOVED            ( WM_LIBTIEPIE + 3 ) //!< \see LstSetMessageDeviceRemoved
#define WM_LIBTIEPIE_LST_DEVICECANOPENCHANGED     ( WM_LIBTIEPIE + 9 ) //!< \see LstSetMessageDeviceCanOpenChanged

#define WM_LIBTIEPIE_NETSRV_ADDED                 ( WM_LIBTIEPIE + 11 ) //!< \see NetSrvSetMessageAdded

#define WM_LIBTIEPIE_DEV_REMOVED                  ( WM_LIBTIEPIE + 4 ) //!< \deprecated Will be removed in future version, see #ObjSetEventWindowHandle

#define WM_LIBTIEPIE_SCP_DATAREADY                ( WM_LIBTIEPIE + 0 ) //!< \deprecated Will be removed in future version, see #ObjSetEventWindowHandle
#define WM_LIBTIEPIE_SCP_DATAOVERFLOW             ( WM_LIBTIEPIE + 1 ) //!< \deprecated Will be removed in future version, see #ObjSetEventWindowHandle
#define WM_LIBTIEPIE_SCP_CONNECTIONTESTCOMPLETED  ( WM_LIBTIEPIE + 7 ) //!< \deprecated Will be removed in future version, see #ObjSetEventWindowHandle
#define WM_LIBTIEPIE_SCP_TRIGGERED                ( WM_LIBTIEPIE + 8 ) //!< \deprecated Will be removed in future version, see #ObjSetEventWindowHandle

#define WM_LIBTIEPIE_GEN_BURSTCOMPLETED           ( WM_LIBTIEPIE + 5 ) //!< \deprecated Will be removed in future version, see #ObjSetEventWindowHandle
#define WM_LIBTIEPIE_GEN_CONTROLLABLECHANGED      ( WM_LIBTIEPIE + 6 ) //!< \deprecated Will be removed in future version, see #ObjSetEventWindowHandle

#define WM_LIBTIEPIE_EVENT                        ( WM_LIBTIEPIE + 10 ) //!< \see ObjSetEventWindowHandle

/**
 * \}
 */

#endif

/**
 * \defgroup functions Functions
 * \{
 * \defgroup lib Library
 * \{
 * \brief Functions to initialize and exit the library and retrieve information from the library itself.
 *
 *     After loading the library, it must be \ref LibInit "initialized" first, before functions in the library can be used.
 *     Before closing the library, when the application using the library no longer requires it, LibExit() must be called, to clear
 *     and free resources used by the library.
 *
 *     The library has a version number and a configuration number that can be queried.
 *     These can be used when requesting support from TiePie engineering.
 *
 *     On each library function call a status flag is set, indicating how the function was executed.
 *     When a function call behaves different than expected, check the status for possible causes.
 */

// Workaround: Without this line Doxygen adds the documentation below to the group above.

/**
 * \brief Create and initialize internal resources used by the library.
 *
 * This function must be called after loading the library, before non library related functions in the library can be used.
 * Calling non library related functions before the library is initialized will set the status flag to #LIBTIEPIESTATUS_LIBRARY_NOT_INITIALIZED.
 *
 * \remark
 * LibInit can be called multiple times, an internal reference counter is used to keep track of the number of times it is called.
 * LibExit() must then be called equally often.
 * \par Status values
 *   This function does not affect the status flag.
 * \see LibIsInitialized
 * \see LibExit
 * \since 0.5
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef void(*LibTiePieLibInit_t)( void );
#else
void LibInit( void );
#endif

/**
 * \brief Check whether the library's internal resources are initialized.
 *
 * \return #BOOL8_TRUE if initialized, #BOOL8_FALSE otherwise.
 * \par Status values
 *   This function does not affect the status flag.
 * \see LibInit
 * \see LibExit
 * \since 0.5
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef bool8_t(*LibTiePieLibIsInitialized_t)( void );
#else
bool8_t LibIsInitialized( void );
#endif

/**
 * \brief Clear and free internal resources used by the library.
 *
 * This function must be called before closing the library, when the application using the library no longer requires it.
 *
 * \par Status values
 *   This function does not affect the status flag.
 * \see LibInit
 * \see LibIsInitialized
 * \since 0.5
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef void(*LibTiePieLibExit_t)( void );
#else
void LibExit( void );
#endif

/**
 * \brief Get the library version number.
 *
 * \return The library \ref TpVersion_t "version number".
 * \par Status values
 *   This function does not affect the status flag.
 * \par Example
 * \code{.c}
 * TpVersion_t Version = LibGetVersion();
 * uint16_t wMajor     = TPVERSION_MAJOR( Version );
 * uint16_t wMinor     = TPVERSION_MINOR( Version );
 * uint16_t wRelease   = TPVERSION_RELEASE( Version );
 * uint16_t wBuild     = TPVERSION_BUILD( Version );
 *
 * printf( "LibGetVersion = %u.%u.%u.%u\n" , wMajor , wMinor , wRelease , wBuild );
 * \endcode
 * \see LibGetVersionExtra
 *
 * \since 0.4.0
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef TpVersion_t(*LibTiePieLibGetVersion_t)( void );
#else
TpVersion_t LibGetVersion( void );
#endif

/**
 * \brief Get the library version postfix.
 *
 * \return The library version postfix.
 * \par Status values
 *   This function does not affect the status flag.
 * \see LibGetVersion
 *
 * \since 0.5
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef const char*(*LibTiePieLibGetVersionExtra_t)( void );
#else
const char* LibGetVersionExtra( void );
#endif

/**
 * \brief Get the library configuration number.
 *
 * \param[out] pBuffer A pointer to the buffer to write to.
 * \param[in] dwBufferLength The length of the buffer, in bytes.
 * \return The library configuration number length in bytes.
 * \par Status values
 *   This function does not affect the status flag.
 * \par Example
 * \code{.c}
 * uint32_t dwLength = LibGetConfig( NULL , 0 );
 * uint8_t* pBuffer = malloc( sizeof( uint8_t ) * dwLength );
 * dwLength = LibGetConfig( Buffer , dwLength );
 *
 * printf( "LibGetConfig = 0x" );
 * for( i = 0 ; i < dwLength ; i++ )
 *   printf( "%02x" , pBuffer[ i ] );
 * printf( "\n" );
 *
 * free( pBuffer );
 * \endcode
 *
 * \since 0.4.0
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef uint32_t(*LibTiePieLibGetConfig_t)( uint8_t* pBuffer , uint32_t dwBufferLength );
#else
uint32_t LibGetConfig( uint8_t* pBuffer , uint32_t dwBufferLength );
#endif

/**
 * \brief Get the last status value.
 *
 * After each call to a library function, a status flag is set, indicating how the function was executed.
 *
 * \return \ref LIBTIEPIESTATUS_ "Status code".
 * \par Status values
 *   This function does not affect the status flag.
 * \see LibGetLastStatusStr
 *
 * \par Example
 * \code{.c}
 * printf( "LibGetLastStatus = %d\n" , LibGetLastStatus() );
 * \endcode
 *
 * \since 0.4.0
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef LibTiePieStatus_t(*LibTiePieLibGetLastStatus_t)( void );
#else
LibTiePieStatus_t LibGetLastStatus( void );
#endif

/**
 * \brief Get the last status value as text.
 *
 * After each call to a library function, a status flag is set, indicating how the function was executed.
 *
 * \return \ref LIBTIEPIESTATUS_ "Status code" as text.
 * \par Status values
 *   This function does not affect the status flag.
 * \see LibGetLastStatus
 *
 * \par Example
 * \code{.c}
 * printf( "LibGetLastStatusStr = %s\n" , LibGetLastStatusStr() );
 * \endcode
 *
 * \since 0.4.0
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef const char*(*LibTiePieLibGetLastStatusStr_t)( void );
#else
const char* LibGetLastStatusStr( void );
#endif

/**
 * \}
 * \defgroup lst Device list
 * \{
 * \brief Functions to control the device list: open and close devices and retrieve device information.
 *
 * LibTiePie maintains a Device list, containing all available supported devices.
 * Possible devices are oscilloscopes, generators and I2C hosts.
 * Instruments can contain multiple devices, e.g. the Handyscope HS5 contains an oscilloscope, a generator and an I2C host.
 *
 * After starting the application, the device list must be filled with all available devices, using LstUpdate().
 * When the application is running, the device list is automatically maintained.
 * When new compatible devices are connected to the computer, they will be added to the device list automatically.
 * When devices are disconnected from the computer, they are automatically removed from the list.
 *
 * <h3>Getting device information</h3>
 *
 * Before opening a device, information from the \ref lst_instruments "listed devices" can be retrieved.
 * This information can help opening the required device, when multiple devices are available in the list.
 *
 * \anchor OpenDev
 * <h3>Opening a device</h3>
 *
 * Before any device action can be performed a device needs to be opened.
 * When a device in the device list is opened, a unique handle to the device is assigned.
 * This handle is required to access the device.
 *
 * LibTiePie has four functions for opening devices.
 * One function for each \ref DEVICETYPE_ "device type" (\ref LstOpenOscilloscope, \ref LstOpenGenerator and \ref LstOpenI2CHost),
 * and one (\ref LstOpenDevice) to open a device by specifying its \ref DEVICETYPE_ "device type".
 * A device can only be opened once.
 *
 * <h4>Device open methods</h4>
 *
 * LibTiePie supports three different methods for opening devices.
 *
 * - Open by device list index (#IDKIND_INDEX), e.g.:
 * \code{.c}
 * LibTiePieHandle_t hScp = LstOpenDevice( IDKIND_INDEX , 4 , DEVICETYPE_OSCILLOSCOPE ); // Try to open oscilloscope at device list index 4.
 * \endcode
 * - Open by serial number (#IDKIND_SERIALNUMBER), e.g.:
 * \code{.c}
 * LibTiePieHandle_t hGen = LstOpenDevice( IDKIND_SERIALNUMBER , 22110 , DEVICETYPE_GENERATOR ); // Try to open generator with serial number 22110.
 * \endcode
 * - Open by product id (#IDKIND_PRODUCTID), e.g.:
 * \code{.c}
 * LibTiePieHandle_t hI2C = LstOpenDevice( IDKIND_PRODUCTID , PID_HS5 , DEVICETYPE_I2CHOST ); // Try to open a Handyscope HS5 I2C host.
 * \endcode
 *
 * When a device cannot be opened the function to open returns #LIBTIEPIE_HANDLE_INVALID.
 *
 * <h3>Closing a disconnected device</h3>
 *
 * When an open device is disconnected from the computer, the handle to that device will be no longer valid and the device needs to be
 * closed using ObjClose().
 * Calling functions pointing to a disconnected device will set the status flag to \ref LIBTIEPIESTATUS_OBJECT_GONE.
 *
 * \anchor Combining
 * <h3>Combining devices</h3>
 * Several devices support combining, where multiple units can be combined to form a larger device.
 * Two different methods are possible.
 *
 * <h4>Automatic combining</h4>
 *
 * This applies to the Handyscope HS5 and Handyscope HS6 DIFF.
 *
 * Connect the instruments to each other using a special coupling cable and update the device list using LstUpdate().
 * A new combined device with a new (virtual) serial number will be added to the device list, the original devices remain present in the device list but can not be accessed anymore.
 *
 * To undo an automatic combination, remove the coupling cable(s) and update the device list using LstUpdate().
 *
 *
 * <h4>Manual combining</h4>
 *
 * This applies to the Handyscope HS4, Handyscope HS4 DIFF and ATS5004D.
 *
 * Connect the instruments to each other using a special coupling cable and open the individual oscilloscopes to retrieve their handles.
 * Then call a \ref LstCreateCombinedDevice "coupling function", supplying the handles of the devices to combine.
 * A new combined device with a new (virtual) serial number will be added to the device list, the original devices remain present in the device list but their handles become invalid.
 * These should be closed using ObjClose().
 * An <a class="External" href="http://www.tiepie.com/software/LibTiePie/C/Examples/OscilloscopeCombineHS4.c"><b>example</b></a> in C is available on the TiePie engineering website.
 *
 * To undo a manual combination, remove the coupling cable, close the combined device using ObjClose() with the handle of the combined device.
 * Finally remove the combined device from the device list using LstRemoveDevice() with the serial number of the combined device.
 *
 * <h4>Opening a combined device</h4>
 *
 * Opening a combined device can be done in the ways described before, with one restriction.
 * When opening a combined device by product id (#IDKIND_PRODUCTID), the id #PID_COMBI must be used.
 */

// Workaround: Without this line Doxygen adds the documentation below to the group above.

/**
 * \brief Update the device list.
 *
 * This function searches for new instruments and adds these to the device list.
 *
 * \par Status values
 *   <table class="params">
 *   <tr><td>\ref LIBTIEPIESTATUS_LIBRARY_NOT_INITIALIZED "LIBRARY_NOT_INITIALIZED"</td><td>The library is not initialized, see LibInit().</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_SUCCESS "SUCCESS"</td>                <td>The function executed successfully.</td></tr>
 *   </table>
 * \par Example
 * \code{.c}
 * LstUpdate(); // Search for new instruments
 * \endcode
 *
 * \since 0.5
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef void(*LibTiePieLstUpdate_t)( void );
#else
void LstUpdate( void );
#endif

/**
 * \brief Get the number of devices in the device list.
 *
 * \return The number of devices in the device list.
 * \par Status values
 *   <table class="params">
 *   <tr><td>\ref LIBTIEPIESTATUS_LIBRARY_NOT_INITIALIZED "LIBRARY_NOT_INITIALIZED"</td><td>The library is not initialized, see LibInit().</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_SUCCESS "SUCCESS"</td>                <td>The function executed successfully.</td></tr>
 *   </table>
 * \since 0.4.0
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef uint32_t(*LibTiePieLstGetCount_t)( void );
#else
uint32_t LstGetCount( void );
#endif

/**
 * \brief Open a device and get a handle to the device.
 *
 * \param[in] dwIdKind An \ref IDKIND_ "id kind".
 * \param[in] dwId A device index, \ref PID_ "Product ID" or serial number identifying the device to open as specified by \c dwIdKind.
 * \param[in] dwDeviceType A \ref DEVICETYPE_ "device type".
 * \return A device handle, or #LIBTIEPIE_HANDLE_INVALID on error.
 * \par Status values
 *   <table class="params">
 *   <tr><td>\ref LIBTIEPIESTATUS_INITIALIZATION_FAILED "INITIALIZATION_FAILED"</td>      <td>The instrument's initialization failed, please contact TiePie engineering support.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_EEPROM "INVALID_EEPROM"</td>             <td>The instrument's EEPROM content is damaged, please contact TiePie engineering support.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_FIRMWARE "INVALID_FIRMWARE"</td>           <td>The currently used firmware is not supported \cond EXTENDED_API , see LstDevGetRecommendedFirmwareVersion() \endcond.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_DRIVER "INVALID_DRIVER"</td>             <td>The currently installed driver is not supported, see LstDevGetRecommendedDriverVersion(). (Windows only)</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_VALUE "INVALID_VALUE"</td>              <td>The value of dwIdKind or dwDeviceType is invalid.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_DEVICE_INDEX "INVALID_DEVICE_INDEX"</td>       <td>The device index is invalid, must be < LstGetCount().</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_PRODUCT_ID "INVALID_PRODUCT_ID"</td>         <td>There is no device with the requested product ID.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_DEVICE_SERIALNUMBER "INVALID_DEVICE_SERIALNUMBER"</td><td>There is no device with the requested serial number.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_DEVICE_TYPE "INVALID_DEVICE_TYPE"</td>        <td>The device type is invalid.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_DRIVER "INVALID_DRIVER"</td>             <td>The currently installed driver is not supported, see LstDevGetRecommendedDriverVersion(). (Windows only)</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_UNSUCCESSFUL "UNSUCCESSFUL"</td>               <td>The device is already open or an other error occurred.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_LIBRARY_NOT_INITIALIZED "LIBRARY_NOT_INITIALIZED"</td>    <td>The library is not initialized, see LibInit().</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_SUCCESS "SUCCESS"</td>                    <td>The function executed successfully.</td></tr>
 *   </table>
 * \par Examples
 * \code{.c}
 * LibTiePieHandle_t hScp = LstOpenDevice( IDKIND_INDEX , 4 , DEVICETYPE_OSCILLOSCOPE ); // Try to open oscilloscope at device list index 4.
 * \endcode
 * \code{.c}
 * LibTiePieHandle_t hI2C = LstOpenDevice( IDKIND_PRODUCTID , PID_HS5 , DEVICETYPE_I2CHOST ); // Try to open a Handyscope HS5 I2C host.
 * \endcode
 * \code{.c}
 * LibTiePieHandle_t hGen = LstOpenDevice( IDKIND_SERIALNUMBER , 22110 , DEVICETYPE_GENERATOR ); // Try to open generator with serial number 22110.
 * \endcode
 * \see LstOpenOscilloscope
 * \see LstOpenGenerator
 * \see LstOpenI2CHost
 * \see ObjClose
 * \since 0.4.0
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef LibTiePieHandle_t(*LibTiePieLstOpenDevice_t)( uint32_t dwIdKind , uint32_t dwId , uint32_t dwDeviceType );
#else
LibTiePieHandle_t LstOpenDevice( uint32_t dwIdKind , uint32_t dwId , uint32_t dwDeviceType );
#endif

/**
 * \brief Open an oscilloscope and get a handle to the oscilloscope.
 *
 * \param[in] dwIdKind An \ref IDKIND_ "id kind".
 * \param[in] dwId A device index, \ref PID_ "Product ID" or serial number identifying the oscilloscope to open as specified by \c dwIdKind.
 * \return A device handle, or #LIBTIEPIE_HANDLE_INVALID on error.
 * \par Status values
 *   <table class="params">
 *   <tr><td>\ref LIBTIEPIESTATUS_INITIALIZATION_FAILED "INITIALIZATION_FAILED"</td>      <td>The instrument's initialization failed, please contact TiePie engineering support.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_EEPROM "INVALID_EEPROM"</td>             <td>The instrument's EEPROM content is damaged, please contact TiePie engineering support.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_FIRMWARE "INVALID_FIRMWARE"</td>           <td>The currently used firmware is not supported \cond EXTENDED_API , see LstDevGetRecommendedFirmwareVersion() \endcond.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_DRIVER "INVALID_DRIVER"</td>             <td>The currently installed driver is not supported, see LstDevGetRecommendedDriverVersion(). (Windows only)</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_VALUE "INVALID_VALUE"</td>              <td>The value of dwIdKind is invalid.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_DEVICE_INDEX "INVALID_DEVICE_INDEX"</td>       <td>The device index is invalid, must be < LstGetCount().</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_PRODUCT_ID "INVALID_PRODUCT_ID"</td>         <td>There is no device with the requested product ID.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_DEVICE_SERIALNUMBER "INVALID_DEVICE_SERIALNUMBER"</td><td>There is no device with the requested serial number.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_DRIVER "INVALID_DRIVER"</td>             <td>The currently installed driver is not supported, see LstDevGetRecommendedDriverVersion(). (Windows only)</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_UNSUCCESSFUL "UNSUCCESSFUL"</td>               <td>The device is already open or an other error occured.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_LIBRARY_NOT_INITIALIZED "LIBRARY_NOT_INITIALIZED"</td>    <td>The library is not initialized, see LibInit().</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_SUCCESS "SUCCESS"</td>                    <td>The function executed successfully.</td></tr>
 *   </table>
 * \par Examples
 * \code{.c}
 * LibTiePieHandle_t hScp = LstOpenOscilloscope( IDKIND_INDEX , 4 ); // Try to open oscilloscope at device list index 4.
 * \endcode
 * \code{.c}
 * LibTiePieHandle_t hScp = LstOpenOscilloscope( IDKIND_SERIALNUMBER , 27917 ); // Try to open oscilloscope with serial number 27917.
 * \endcode
 * \code{.c}
 * LibTiePieHandle_t hScp = LstOpenOscilloscope( IDKIND_PRODUCTID , PID_HS5 ); // Try to open a Handyscope HS5 oscilloscope.
 * \endcode
 * \see LstOpenDevice
 * \see LstOpenGenerator
 * \see LstOpenI2CHost
 * \see ObjClose
 * \since 0.4.0
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef LibTiePieHandle_t(*LibTiePieLstOpenOscilloscope_t)( uint32_t dwIdKind , uint32_t dwId );
#else
LibTiePieHandle_t LstOpenOscilloscope( uint32_t dwIdKind , uint32_t dwId );
#endif

/**
 * \brief Open a generator and get a handle to the generator.
 *
 * \param[in] dwIdKind An \ref IDKIND_ "id kind".
 * \param[in] dwId Device index, \ref PID_ "Product ID" or serial number identifying the generator to open as specified by \c dwIdKind.
 * \return A device handle, or #LIBTIEPIE_HANDLE_INVALID on error.
 * \par Status values
 *   <table class="params">
 *   <tr><td>\ref LIBTIEPIESTATUS_INITIALIZATION_FAILED "INITIALIZATION_FAILED"</td>      <td>The instrument's initialization failed, please contact TiePie engineering support.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_EEPROM "INVALID_EEPROM"</td>             <td>The instrument's EEPROM content is damaged, please contact TiePie engineering support.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_FIRMWARE "INVALID_FIRMWARE"</td>           <td>The currently used firmware is not supported \cond EXTENDED_API , see LstDevGetRecommendedFirmwareVersion() \endcond.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_DRIVER "INVALID_DRIVER"</td>             <td>The currently installed driver is not supported, see LstDevGetRecommendedDriverVersion(). (Windows only)</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_VALUE "INVALID_VALUE"</td>              <td>The value of dwIdKind is invalid.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_DEVICE_INDEX "INVALID_DEVICE_INDEX"</td>       <td>The device index is invalid, must be < LstGetCount().</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_PRODUCT_ID "INVALID_PRODUCT_ID"</td>         <td>There is no device with the requested product ID.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_DEVICE_SERIALNUMBER "INVALID_DEVICE_SERIALNUMBER"</td><td>There is no device with the requested serial number.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_DRIVER "INVALID_DRIVER"</td>             <td>The currently installed driver is not supported, see LstDevGetRecommendedDriverVersion(). (Windows only)</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_UNSUCCESSFUL "UNSUCCESSFUL"</td>               <td>The device is already open or an other error occured.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_LIBRARY_NOT_INITIALIZED "LIBRARY_NOT_INITIALIZED"</td>    <td>The library is not initialized, see LibInit().</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_SUCCESS "SUCCESS"</td>                    <td>The function executed successfully.</td></tr>
 *   </table>
 * \par Examples
 * \code{.c}
 * LibTiePieHandle_t hGen = LstOpenGenerator( IDKIND_INDEX , 2 ); // Try to open generator at device list index 2.
 * \endcode
 * \code{.c}
 * LibTiePieHandle_t hGen = LstOpenGenerator( IDKIND_SERIALNUMBER , 22110 ); // Try to open generator with serial number 22110.
 * \endcode
 * \code{.c}
 * LibTiePieHandle_t hGen = LstOpenGenerator( IDKIND_PRODUCTID , PID_HS5 ); // Try to open a Handyscope HS5 generator.
 * \endcode
 * \see LstOpenDevice
 * \see LstOpenOscilloscope
 * \see LstOpenI2CHost
 * \see ObjClose
 * \since 0.4.0
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef LibTiePieHandle_t(*LibTiePieLstOpenGenerator_t)( uint32_t dwIdKind , uint32_t dwId );
#else
LibTiePieHandle_t LstOpenGenerator( uint32_t dwIdKind , uint32_t dwId );
#endif

/**
 * \brief Open an I2C host and get a handle to the I2C host.
 *
 * \param[in] dwIdKind An \ref IDKIND_ "id kind".
 * \param[in] dwId A device index, \ref PID_ "Product ID" or serial number identifying the I2C host to open as specified by \c dwIdKind.
 * \return A device handle, or #LIBTIEPIE_HANDLE_INVALID on error.
 * \par Status values
 *   <table class="params">
 *   <tr><td>\ref LIBTIEPIESTATUS_INITIALIZATION_FAILED "INITIALIZATION_FAILED"</td>      <td>The instrument's initialization failed, please contact TiePie engineering support.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_EEPROM "INVALID_EEPROM"</td>             <td>The instrument's EEPROM content is damaged, please contact TiePie engineering support.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_FIRMWARE "INVALID_FIRMWARE"</td>           <td>The currently used firmware is not supported \cond EXTENDED_API , see LstDevGetRecommendedFirmwareVersion() \endcond.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_DRIVER "INVALID_DRIVER"</td>             <td>The currently installed driver is not supported, see LstDevGetRecommendedDriverVersion(). (Windows only)</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_VALUE "INVALID_VALUE"</td>              <td>The value of dwIdKind is invalid.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_DEVICE_INDEX "INVALID_DEVICE_INDEX"</td>       <td>The device index is invalid, must be < LstGetCount().</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_PRODUCT_ID "INVALID_PRODUCT_ID"</td>         <td>There is no device with the requested product ID.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_DEVICE_SERIALNUMBER "INVALID_DEVICE_SERIALNUMBER"</td><td>There is no device with the requested serial number.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_DRIVER "INVALID_DRIVER"</td>             <td>The currently installed driver is not supported, see LstDevGetRecommendedDriverVersion(). (Windows only)</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_UNSUCCESSFUL "UNSUCCESSFUL"</td>               <td>The device is already open or an other error occured.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_LIBRARY_NOT_INITIALIZED "LIBRARY_NOT_INITIALIZED"</td>    <td>The library is not initialized, see LibInit().</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_SUCCESS "SUCCESS"</td>                    <td>The function executed successfully.</td></tr>
 *   </table>
 * \par Examples
 * \code{.c}
 * LibTiePieHandle_t hI2C = LstOpenI2CHost( IDKIND_INDEX , 0 ); // Try to open I2C host at device list index 0.
 * \endcode
 * \code{.c}
 * LibTiePieHandle_t hI2C = LstOpenI2CHost( IDKIND_SERIALNUMBER , 26697 ); // Try to open I2C host with serial number 26697.
 * \endcode
 * \code{.c}
 * LibTiePieHandle_t hI2C = LstOpenI2CHost( IDKIND_PRODUCTID , PID_HS5 ); // Try to open a Handyscope HS5 I2C host.
 * \endcode
 * \see LstOpenDevice
 * \see LstOpenOscilloscope
 * \see LstOpenGenerator
 * \see ObjClose
 * \since 0.4.0
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef LibTiePieHandle_t(*LibTiePieLstOpenI2CHost_t)( uint32_t dwIdKind , uint32_t dwId );
#else
LibTiePieHandle_t LstOpenI2CHost( uint32_t dwIdKind , uint32_t dwId );
#endif

/**
 * \brief Create a combined instrument.
 *
 * This function creates \ref Combining "combined instrument" from the indicated devices.
 *
 * \param[in] pDeviceHandles Pointer to an array of handles of the devices to combine.
 * \param[in] dwCount The number of device handles.
 * \return Serial number of the combined device, or zero on error.
 * \par Status values
 *   <table class="params">
 *   <tr><td>\ref LIBTIEPIESTATUS_NOT_SUPPORTED "NOT_SUPPORTED"</td>          <td>Combining is not supported.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_HANDLE "INVALID_HANDLE"</td>         <td>One or more device handles are invalid or incompatible.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_VALUE "INVALID_VALUE"</td>          <td>pDeviceHandles must be != \c NULL and the number of device handles must be >= 2.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_OBJECT_GONE "OBJECT_GONE"</td>            <td>One or more devices indicated by the device handles is no longer available.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_LIBRARY_NOT_INITIALIZED "LIBRARY_NOT_INITIALIZED"</td><td>The library is not initialized, see LibInit().</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_SUCCESS "SUCCESS"</td>                <td>The function executed successfully.</td></tr>
 *   </table>
 * \see LstCreateAndOpenCombinedDevice
 * \since 0.4.4
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef uint32_t(*LibTiePieLstCreateCombinedDevice_t)( const LibTiePieHandle_t* pDeviceHandles , uint32_t dwCount );
#else
uint32_t LstCreateCombinedDevice( const LibTiePieHandle_t* pDeviceHandles , uint32_t dwCount );
#endif

/**
 * \brief Create and open a combined instrument.
 *
 * This function creates a \ref Combining "combined instrument" from the indicated devices and opens it.
 *
 * \param[in] pDeviceHandles Pointer to an array of handles of the devices to combine.
 * \param[in] dwCount The number of device handles.
 * \return A device handle, or #LIBTIEPIE_HANDLE_INVALID on error.
 * \par Status values
 *   <table class="params">
 *   <tr><td>\ref LIBTIEPIESTATUS_NOT_SUPPORTED "NOT_SUPPORTED"</td>          <td>Combining is not supported.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_HANDLE "INVALID_HANDLE"</td>         <td>One or more device handles are invalid or incompatible.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_VALUE "INVALID_VALUE"</td>          <td>pDeviceHandles must be != \c NULL and the number of device handles must be >= 2.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_OBJECT_GONE "OBJECT_GONE"</td>            <td>One or more devices indicated by the device handles is no longer available.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_UNSUCCESSFUL "UNSUCCESSFUL"</td>           <td>An error occurred during execution of the last called function.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_LIBRARY_NOT_INITIALIZED "LIBRARY_NOT_INITIALIZED"</td><td>The library is not initialized, see LibInit().</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_SUCCESS "SUCCESS"</td>                <td>The function executed successfully.</td></tr>
 *   </table>
 * \see LstCreateCombinedDevice
 * \since 0.4.4
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef LibTiePieHandle_t(*LibTiePieLstCreateAndOpenCombinedDevice_t)( const LibTiePieHandle_t* pDeviceHandles , uint32_t dwCount );
#else
LibTiePieHandle_t LstCreateAndOpenCombinedDevice( const LibTiePieHandle_t* pDeviceHandles , uint32_t dwCount );
#endif

/**
 * \brief Remove an instrument from the device list so it can be used by other applications.
 *
 * \param[in] dwSerialNumber Serial number of the device to remove.
 * \par Status values
 *   <table class="params">
 *   <tr><td>\ref LIBTIEPIESTATUS_UNSUCCESSFUL "UNSUCCESSFUL"</td>               <td>Device is still open?</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_NOT_SUPPORTED "NOT_SUPPORTED"</td>              <td>Device can't be removed from the list. To remove a combined Handyscope HS5, unplug the coupling cable and call LstUpdate().</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_DEVICE_SERIALNUMBER "INVALID_DEVICE_SERIALNUMBER"</td><td>There is no device with the requested serial number.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_LIBRARY_NOT_INITIALIZED "LIBRARY_NOT_INITIALIZED"</td>    <td>The library is not initialized, see LibInit().</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_SUCCESS "SUCCESS"</td>                    <td>The function executed successfully.</td></tr>
 *   </table>
 * \since 0.4.0
 * \see LstRemoveDeviceForce
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef void(*LibTiePieLstRemoveDevice_t)( uint32_t dwSerialNumber );
#else
void LstRemoveDevice( uint32_t dwSerialNumber );
#endif

/**
 * \brief Remove an instrument from the device list even when it is in use so it can be used by other applications.
 *
 * \param[in] dwSerialNumber Serial number of the device to remove.
 * \par Status values
 *   <table class="params">
 *   <tr><td>\ref LIBTIEPIESTATUS_NOT_SUPPORTED "NOT_SUPPORTED"</td>              <td>Device can't be removed from the list. To remove a combined Handyscope HS5, unplug the coupling cable and call LstUpdate().</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_DEVICE_SERIALNUMBER "INVALID_DEVICE_SERIALNUMBER"</td><td>There is no device with the requested serial number.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_LIBRARY_NOT_INITIALIZED "LIBRARY_NOT_INITIALIZED"</td>    <td>The library is not initialized, see LibInit().</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_SUCCESS "SUCCESS"</td>                    <td>The function executed successfully.</td></tr>
 *   </table>
 * \since 0.9.8
 * \see LstRemoveDevice
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef void(*LibTiePieLstRemoveDeviceForce_t)(uint32_t dwSerialNumber);
#else
void LstRemoveDeviceForce(uint32_t dwSerialNumber);
#endif

/**
 * \defgroup lst_instruments Listed devices
 * \{
 * \brief Functions to retrieve information from the listed devices.
 *
 * Before opening a device, device specific information can be retrieved.
 * This information can help opening the required device, when multiple devices are available in the list.
 *
 * <h3>Methods to identify the required device</h3>
 *
 * Three different methods to identify a device are available:
 *
 * - Identify by device list index (#IDKIND_INDEX), e.g.:
 * \code{.c}
 * TpDate_t dwNumber = LstDevGetCalibrationDate( IDKIND_INDEX , 4 ); // Get the calibration date from the device at list index 4.
 * \endcode
 * - Identify by serial number (#IDKIND_SERIALNUMBER), e.g.:
 * \code{.c}
 * TpDate_t dwNumber = LstDevGetCalibrationDate( IDKIND_SERIALNUMBER , 22110 ); // Get the calibration date from the device with serial number 22110.
 * \endcode
 * - Identify by product id (#IDKIND_PRODUCTID), e.g.:
 * \code{.c}
 * TpDate_t dwNumber = LstDevGetCalibrationDate( IDKIND_PRODUCTID , PID_HS5 ); // Get the calibration date from the first Handyscope HS5 in the device list.
 * \endcode
 */

// Workaround: Without this line Doxygen adds the documentation below to the group above.

/**
 * \brief Check whether the listed device can be opened.
 *
 * \param[in] dwIdKind     An \ref IDKIND_ "id kind".
 * \param[in] dwId         A device index, \ref PID_ "Product ID" or serial number identifying the device to check, as specified by \c dwIdKind.
 * \param[in] dwDeviceType A \ref DEVICETYPE_ "device type".
 * \return #BOOL8_TRUE if the device can be opened or #BOOL8_FALSE if not.
 * \par Status values
 *   <table class="params">
 *   <tr><td>\ref LIBTIEPIESTATUS_INITIALIZATION_FAILED "INITIALIZATION_FAILED"</td>      <td>The instrument's initialization failed, please contact TiePie engineering support.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_EEPROM "INVALID_EEPROM"</td>             <td>The instrument's EEPROM content is damaged, please contact TiePie engineering support.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_FIRMWARE "INVALID_FIRMWARE"</td>           <td>The currently used firmware is not supported \cond EXTENDED_API , see LstDevGetRecommendedFirmwareVersion() \endcond.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_DRIVER "INVALID_DRIVER"</td>             <td>The currently installed driver is not supported, see LstDevGetRecommendedDriverVersion(). (Windows only)</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_DEVICE_INDEX "INVALID_DEVICE_INDEX"</td>       <td>The device index is invalid, must be < LstGetCount().</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_DEVICE_SERIALNUMBER "INVALID_DEVICE_SERIALNUMBER"</td><td>There is no device with the requested serial number.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_PRODUCT_ID "INVALID_PRODUCT_ID"</td>         <td>There is no device with the requested product ID.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_DEVICE_TYPE "INVALID_DEVICE_TYPE"</td>        <td>The device type is invalid.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_VALUE "INVALID_VALUE"</td>              <td>The value of dwIdKind is invalid.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_LIBRARY_NOT_INITIALIZED "LIBRARY_NOT_INITIALIZED"</td>    <td>The library is not initialized, see LibInit().</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_SUCCESS "SUCCESS"</td>                    <td>The function executed successfully.</td></tr>
 *   </table>
 * \since 0.5
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef bool8_t(*LibTiePieLstDevCanOpen_t)( uint32_t dwIdKind , uint32_t dwId , uint32_t dwDeviceType );
#else
bool8_t LstDevCanOpen( uint32_t dwIdKind , uint32_t dwId , uint32_t dwDeviceType );
#endif

/**
 * \brief Get the product id of the listed device.
 *
 * \param[in] dwIdKind An \ref IDKIND_ "id kind".
 * \param[in] dwId A device index, \ref PID_ "Product ID" or serial number identifying the device to check, as specified by \c dwIdKind.
 * \return The \ref PID_ "product id" of the listed device.
 * \par Status values
 *   <table class="params">
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_DEVICE_INDEX "INVALID_DEVICE_INDEX"</td>       <td>The device index is invalid, must be < LstGetCount().</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_DEVICE_SERIALNUMBER "INVALID_DEVICE_SERIALNUMBER"</td><td>There is no device with the requested serial number.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_PRODUCT_ID "INVALID_PRODUCT_ID"</td>         <td>There is no device with the requested product ID.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_NOT_SUPPORTED "NOT_SUPPORTED"</td>              <td>The indicated device does not support reading a product id.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_VALUE "INVALID_VALUE"</td>              <td>The value of dwIdKind is invalid.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_LIBRARY_NOT_INITIALIZED "LIBRARY_NOT_INITIALIZED"</td>    <td>The library is not initialized, see LibInit().</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_SUCCESS "SUCCESS"</td>                    <td>The function executed successfully.</td></tr>
 *   </table>
 * \since 0.5
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef uint32_t(*LibTiePieLstDevGetProductId_t)( uint32_t dwIdKind , uint32_t dwId );
#else
uint32_t LstDevGetProductId( uint32_t dwIdKind , uint32_t dwId );
#endif

//! \cond EXTENDED_API

/**
 * \brief Get the vendor id of the listed device.
 *
 * \param[in] dwIdKind An \ref IDKIND_ "id kind".
 * \param[in] dwId A device index, \ref PID_ "Product ID" or serial number identifying the device to check, as specified by \c dwIdKind.
 * \return The vendor id of the listed device.
 * \par Status values
 *   <table class="params">
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_DEVICE_INDEX "INVALID_DEVICE_INDEX"</td>       <td>The device index is invalid, must be < LstGetCount().</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_DEVICE_SERIALNUMBER "INVALID_DEVICE_SERIALNUMBER"</td><td>There is no device with the requested serial number.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_PRODUCT_ID "INVALID_PRODUCT_ID"</td>         <td>There is no device with the requested product ID.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_NOT_SUPPORTED "NOT_SUPPORTED"</td>              <td>The indicated device does not support reading a vendor id.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_VALUE "INVALID_VALUE"</td>              <td>The value of dwIdKind is invalid.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_LIBRARY_NOT_INITIALIZED "LIBRARY_NOT_INITIALIZED"</td>    <td>The library is not initialized, see LibInit().</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_SUCCESS "SUCCESS"</td>                    <td>The function executed successfully.</td></tr>
 *   </table>
 * \since 0.5
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef uint32_t(*LibTiePieLstDevGetVendorId_t)( uint32_t dwIdKind , uint32_t dwId );
#else
uint32_t LstDevGetVendorId( uint32_t dwIdKind , uint32_t dwId );
#endif

//! \endcond

/**
 * \brief Get the full name of the listed device.
 *
 * E.g. <tt>Handyscope HS5-530XMS</tt>
 *
 * \param[in] dwIdKind An \ref IDKIND_ "id kind".
 * \param[in] dwId A device index, \ref PID_ "Product ID" or serial number identifying the device to check, as specified by \c dwIdKind.
 * \param[out] pBuffer A pointer to a buffer for the name.
 * \param[in] dwBufferLength The length of the buffer, in bytes.
 * \return The length of the name in bytes, excluding terminating zero.
 * \par Status values
 *   <table class="params">
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_DEVICE_INDEX "INVALID_DEVICE_INDEX"</td>       <td>The device index is invalid, must be < LstGetCount().</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_DEVICE_SERIALNUMBER "INVALID_DEVICE_SERIALNUMBER"</td><td>There is no device with the requested serial number.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_PRODUCT_ID "INVALID_PRODUCT_ID"</td>         <td>There is no device with the requested product ID.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_NOT_SUPPORTED "NOT_SUPPORTED"</td>              <td>The indicated device does not support reading a name.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_VALUE "INVALID_VALUE"</td>              <td>The value of dwIdKind is invalid.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_LIBRARY_NOT_INITIALIZED "LIBRARY_NOT_INITIALIZED"</td>    <td>The library is not initialized, see LibInit().</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_SUCCESS "SUCCESS"</td>                    <td>The function executed successfully.</td></tr>
 *   </table>
 * \see LstDevGetNameShort
 * \see LstDevGetNameShortest
 *
 * \par Example
 * \code{.c}
 * uint32_t dwLength = LstDevGetName( dwIdKind , dwId , NULL , 0 ) + 1; // Add one for the terminating zero
 * char* sName = malloc( sizeof( char ) * dwLength );
 * dwLength = LstDevGetName( dwIdKind , dwId , sName , dwLength );
 *
 * printf( "LstDevGetName = %s\n" , sName );
 *
 * free( sName );
 * \endcode
 *
 * \since 0.5
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef uint32_t(*LibTiePieLstDevGetName_t)( uint32_t dwIdKind , uint32_t dwId , char* pBuffer , uint32_t dwBufferLength );
#else
uint32_t LstDevGetName( uint32_t dwIdKind , uint32_t dwId , char* pBuffer , uint32_t dwBufferLength );
#endif

/**
 * \brief Get the short name of the listed device.
 *
 * E.g. <tt>HS5-530XMS</tt>
 *
 * \param[in] dwIdKind An \ref IDKIND_ "id kind".
 * \param[in] dwId A device index, \ref PID_ "Product ID" or serial number identifying the device to check, as specified by \c dwIdKind.
 * \param[out] pBuffer A pointer to a buffer for the name.
 * \param[in] dwBufferLength The length of the buffer, in bytes.
 * \return The length of the name in bytes, excluding terminating zero.
 * \par Status values
 *   <table class="params">
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_DEVICE_INDEX "INVALID_DEVICE_INDEX"</td>       <td>The device index is invalid, must be < LstGetCount().</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_DEVICE_SERIALNUMBER "INVALID_DEVICE_SERIALNUMBER"</td><td>There is no device with the requested serial number.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_PRODUCT_ID "INVALID_PRODUCT_ID"</td>         <td>There is no device with the requested product ID.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_NOT_SUPPORTED "NOT_SUPPORTED"</td>              <td>The indicated device does not support reading a name.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_VALUE "INVALID_VALUE"</td>              <td>The value of dwIdKind is invalid.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_LIBRARY_NOT_INITIALIZED "LIBRARY_NOT_INITIALIZED"</td>    <td>The library is not initialized, see LibInit().</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_SUCCESS "SUCCESS"</td>                    <td>The function executed successfully.</td></tr>
 *   </table>
 * \see LstDevGetName
 * \see LstDevGetNameShortest
 *
 * \par Example
 * \code{.c}
 * uint32_t dwLength = LstDevGetNameShort( dwIdKind , dwId , NULL , 0 ) + 1; // Add one for the terminating zero
 * char* sNameShort = malloc( sizeof( char ) * dwLength );
 * dwLength = LstDevGetNameShort( dwIdKind , dwId , sNameShort , dwLength );
 *
 * printf( "LstDevGetNameShort = %s\n" , sNameShort );
 *
 * free( sNameShort );
 * \endcode
 *
 * \since 0.5
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef uint32_t(*LibTiePieLstDevGetNameShort_t)( uint32_t dwIdKind , uint32_t dwId , char* pBuffer , uint32_t dwBufferLength );
#else
uint32_t LstDevGetNameShort( uint32_t dwIdKind , uint32_t dwId , char* pBuffer , uint32_t dwBufferLength );
#endif

/**
 * \brief Get the short name of the listed device wihout model postfix.
 *
 * E.g. <tt>HS5</tt>
 *
 * \param[in] dwIdKind An \ref IDKIND_ "id kind".
 * \param[in] dwId A device index, \ref PID_ "Product ID" or serial number identifying the device to check, as specified by \c dwIdKind.
 * \param[out] pBuffer A pointer to a buffer for the name.
 * \param[in] dwBufferLength The length of the buffer, in bytes.
 * \return The length of the name in bytes, excluding terminating zero.
 * \par Status values
 *   <table class="params">
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_DEVICE_INDEX "INVALID_DEVICE_INDEX"</td>       <td>The device index is invalid, must be < LstGetCount().</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_DEVICE_SERIALNUMBER "INVALID_DEVICE_SERIALNUMBER"</td><td>There is no device with the requested serial number.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_PRODUCT_ID "INVALID_PRODUCT_ID"</td>         <td>There is no device with the requested product ID.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_NOT_SUPPORTED "NOT_SUPPORTED"</td>              <td>The indicated device does not support reading a name.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_VALUE "INVALID_VALUE"</td>              <td>The value of dwIdKind is invalid.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_LIBRARY_NOT_INITIALIZED "LIBRARY_NOT_INITIALIZED"</td>    <td>The library is not initialized, see LibInit().</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_SUCCESS "SUCCESS"</td>                    <td>The function executed successfully.</td></tr>
 *   </table>
 * \see LstDevGetName
 * \see LstDevGetNameShort
 *
 * \par Example
 * \code{.c}
 * uint32_t dwLength = LstDevGetNameShortest( dwIdKind , dwId , NULL , 0 ) + 1; // Add one for the terminating zero
 * char* sNameShortest = malloc( sizeof( char ) * dwLength );
 * dwLength = LstDevGetNameShortest( dwIdKind , dwId , sNameShortest , dwLength );
 *
 * printf( "LstDevGetNameShortest = %s\n" , sNameShortest );
 *
 * free( sNameShortest );
 * \endcode
 *
 * \since 0.4.4
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef uint32_t(*LibTiePieLstDevGetNameShortest_t)( uint32_t dwIdKind , uint32_t dwId , char* pBuffer , uint32_t dwBufferLength );
#else
uint32_t LstDevGetNameShortest( uint32_t dwIdKind , uint32_t dwId , char* pBuffer , uint32_t dwBufferLength );
#endif

/**
 * \brief Get the version number of the driver currently used by the listed device.
 *
 * \param[in] dwIdKind An \ref IDKIND_ "id kind".
 * \param[in] dwId A device index, \ref PID_ "Product ID" or serial number identifying the device to check, as specified by \c dwIdKind.
 * \return The \ref TpVersion_t "version" number of the driver currently used by the listed device, or zero if no driver version is available.
 * \par Status values
 *   <table class="params">
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_DEVICE_INDEX "INVALID_DEVICE_INDEX"</td>       <td>The device index is invalid, must be < LstGetCount().</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_DEVICE_SERIALNUMBER "INVALID_DEVICE_SERIALNUMBER"</td><td>There is no device with the requested serial number.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_PRODUCT_ID "INVALID_PRODUCT_ID"</td>         <td>There is no device with the requested product ID.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_NOT_SUPPORTED "NOT_SUPPORTED"</td>              <td>The indicated device does not support reading a driver version or does not require a driver.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_VALUE "INVALID_VALUE"</td>              <td>The value of dwIdKind is invalid.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_LIBRARY_NOT_INITIALIZED "LIBRARY_NOT_INITIALIZED"</td>    <td>The library is not initialized, see LibInit().</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_SUCCESS "SUCCESS"</td>                    <td>The function executed successfully.</td></tr>
 *   </table>
 * \since 0.4.1
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef TpVersion_t(*LibTiePieLstDevGetDriverVersion_t)( uint32_t dwIdKind , uint32_t dwId );
#else
TpVersion_t LstDevGetDriverVersion( uint32_t dwIdKind , uint32_t dwId );
#endif

/**
 * \brief Get the version number of the recommended driver for the listed device.
 *
 * \param[in] dwIdKind An \ref IDKIND_ "id kind".
 * \param[in] dwId A device index, \ref PID_ "Product ID" or serial number identifying the device to check, as specified by \c dwIdKind.
 * \return The \ref TpVersion_t "version" number of the recommended driver for the listed device, or zero if no driver version is available.
 * \par Status values
 *   <table class="params">
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_DEVICE_INDEX "INVALID_DEVICE_INDEX"</td>       <td>The device index is invalid, must be < LstGetCount().</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_DEVICE_SERIALNUMBER "INVALID_DEVICE_SERIALNUMBER"</td><td>There is no device with the requested serial number.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_PRODUCT_ID "INVALID_PRODUCT_ID"</td>         <td>There is no device with the requested product ID.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_NOT_SUPPORTED "NOT_SUPPORTED"</td>              <td>The indicated device does not support reading a recommended driver version or does not require a driver.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_VALUE "INVALID_VALUE"</td>              <td>The value of dwIdKind is invalid.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_LIBRARY_NOT_INITIALIZED "LIBRARY_NOT_INITIALIZED"</td>    <td>The library is not initialized, see LibInit().</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_SUCCESS "SUCCESS"</td>                    <td>The function executed successfully.</td></tr>
 *   </table>
 * \since 0.4.3
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef TpVersion_t(*LibTiePieLstDevGetRecommendedDriverVersion_t)( uint32_t dwIdKind , uint32_t dwId );
#else
TpVersion_t LstDevGetRecommendedDriverVersion( uint32_t dwIdKind , uint32_t dwId );
#endif

/**
 * \brief Get the version number of the firmware currently used by the listed device.
 *
 * \param[in] dwIdKind An \ref IDKIND_ "id kind".
 * \param[in] dwId A device index, \ref PID_ "Product ID" or serial number identifying the device to check, as specified by \c dwIdKind.
 * \return The \ref TpVersion_t "version" number of the firmware currently used firmware by the listed device, or zero if no firmware version is available.
 * \par Status values
 *   <table class="params">
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_DEVICE_INDEX "INVALID_DEVICE_INDEX"</td>       <td>The device index is invalid, must be < LstGetCount().</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_DEVICE_SERIALNUMBER "INVALID_DEVICE_SERIALNUMBER"</td><td>There is no device with the requested serial number.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_PRODUCT_ID "INVALID_PRODUCT_ID"</td>         <td>There is no device with the requested product ID.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_NOT_SUPPORTED "NOT_SUPPORTED"</td>              <td>The indicated device does not support reading a firmware version or does not require firmware.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_VALUE "INVALID_VALUE"</td>              <td>The value of dwIdKind is invalid.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_LIBRARY_NOT_INITIALIZED "LIBRARY_NOT_INITIALIZED"</td>    <td>The library is not initialized, see LibInit().</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_SUCCESS "SUCCESS"</td>                    <td>The function executed successfully.</td></tr>
 *   </table>
 * \since 0.4.1
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef TpVersion_t(*LibTiePieLstDevGetFirmwareVersion_t)( uint32_t dwIdKind , uint32_t dwId );
#else
TpVersion_t LstDevGetFirmwareVersion( uint32_t dwIdKind , uint32_t dwId );
#endif

//! \cond EXTENDED_API

/**
 * \brief Get the version number of the recommended firmware for the listed device.
 *
 * \param[in] dwIdKind An \ref IDKIND_ "id kind".
 * \param[in] dwId A device index, \ref PID_ "Product ID" or serial number identifying the device to check, as specified by \c dwIdKind.
 * \return The \ref TpVersion_t "version" number of the recommended firmware for the listed device, or zero if no firmware version is available.
 * \par Status values
 *   <table class="params">
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_DEVICE_INDEX "INVALID_DEVICE_INDEX"</td>       <td>The device index is invalid, must be < LstGetCount().</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_DEVICE_SERIALNUMBER "INVALID_DEVICE_SERIALNUMBER"</td><td>There is no device with the requested serial number.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_PRODUCT_ID "INVALID_PRODUCT_ID"</td>         <td>There is no device with the requested product ID.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_NOT_SUPPORTED "NOT_SUPPORTED"</td>              <td>The indicated device does not support reading a recommended firmware version or does not require firmware.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_VALUE "INVALID_VALUE"</td>              <td>The value of dwIdKind is invalid.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_SUCCESS "SUCCESS"</td>                    <td>The function executed successfully.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_LIBRARY_NOT_INITIALIZED "LIBRARY_NOT_INITIALIZED"</td>    <td>The library is not initialized, see LibInit().</td></tr>
 *   </table>
 * \since 0.4.5
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef TpVersion_t(*LibTiePieLstDevGetRecommendedFirmwareVersion_t)( uint32_t dwIdKind , uint32_t dwId );
#else
TpVersion_t LstDevGetRecommendedFirmwareVersion( uint32_t dwIdKind , uint32_t dwId );
#endif

//! \endcond

/**
 * \brief Get the calibration date of the listed device.
 *
 * \param[in] dwIdKind An \ref IDKIND_ "id kind".
 * \param[in] dwId A device index, \ref PID_ "Product ID" or serial number identifying the device to check, as specified by \c dwIdKind.
 * \return The calibration \ref TpDate_t "date" of the listed device, or zero if no calibration date is available.
 * \par Status values
 *   <table class="params">
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_DEVICE_INDEX "INVALID_DEVICE_INDEX"</td>       <td>The device index is invalid, must be < LstGetCount().</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_DEVICE_SERIALNUMBER "INVALID_DEVICE_SERIALNUMBER"</td><td>There is no device with the requested serial number.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_PRODUCT_ID "INVALID_PRODUCT_ID"</td>         <td>There is no device with the requested product ID.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_NOT_SUPPORTED "NOT_SUPPORTED"</td>              <td>The indicated device does not have a calibration date.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_VALUE "INVALID_VALUE"</td>              <td>The value of dwIdKind is invalid.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_LIBRARY_NOT_INITIALIZED "LIBRARY_NOT_INITIALIZED"</td>    <td>The library is not initialized, see LibInit().</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_SUCCESS "SUCCESS"</td>                    <td>The function executed successfully.</td></tr>
 *   </table>
 * \par Example
 * \code{.c}
 * TpDate_t Date    = LstDevGetCalibrationDate( hDevice );
 * uint16_t wYear   = TPDATE_YEAR( Date );
 * uint8_t  byMonth = TPDATE_MONTH( Date );
 * uint8_t  byDay   = TPDATE_DAY( Date );
 *
 * printf( "LstDevGetCalibrationDate = %u-%u-%u\n" , wYear , byMonth , byDay );
 * \endcode
 * \since 0.4.1
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef TpDate_t(*LibTiePieLstDevGetCalibrationDate_t)( uint32_t dwIdKind , uint32_t dwId );
#else
TpDate_t LstDevGetCalibrationDate( uint32_t dwIdKind , uint32_t dwId );
#endif

/**
 * \brief Get the serial number of the listed device.
 *
 * \param[in] dwIdKind An \ref IDKIND_ "id kind".
 * \param[in] dwId A device index, \ref PID_ "Product ID" or serial number identifying the device to check, as specified by \c dwIdKind.
 * \return The serial number of the listed device.
 * \par Status values
 *   <table class="params">
 *   <tr><td>\ref LIBTIEPIESTATUS_INITIALIZATION_FAILED "INITIALIZATION_FAILED"</td>      <td>The instrument's initialization failed, please contact TiePie engineering support.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_EEPROM "INVALID_EEPROM"</td>             <td>The instrument's EEPROM content is damaged, please contact TiePie engineering support.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_FIRMWARE "INVALID_FIRMWARE"</td>           <td>The currently used firmware is not supported \cond EXTENDED_API , see LstDevGetRecommendedFirmwareVersion() \endcond.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_DRIVER "INVALID_DRIVER"</td>             <td>The currently installed driver is not supported, see LstDevGetRecommendedDriverVersion(). (Windows only)</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_DEVICE_INDEX "INVALID_DEVICE_INDEX"</td>       <td>The device index is invalid, must be < LstGetCount().</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_DEVICE_SERIALNUMBER "INVALID_DEVICE_SERIALNUMBER"</td><td>There is no device with the requested serial number.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_PRODUCT_ID "INVALID_PRODUCT_ID"</td>         <td>There is no device with the requested product ID.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_NOT_SUPPORTED "NOT_SUPPORTED"</td>              <td>The indicated device does not support reading a serial number.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_VALUE "INVALID_VALUE"</td>              <td>The value of dwIdKind is invalid.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_LIBRARY_NOT_INITIALIZED "LIBRARY_NOT_INITIALIZED"</td>    <td>The library is not initialized, see LibInit().</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_SUCCESS "SUCCESS"</td>                    <td>The function executed successfully.</td></tr>
 *   </table>
 * \since 0.5
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef uint32_t(*LibTiePieLstDevGetSerialNumber_t)( uint32_t dwIdKind , uint32_t dwId );
#else
uint32_t LstDevGetSerialNumber( uint32_t dwIdKind , uint32_t dwId );
#endif

/**
 * \brief Get the IPv4 address of the listed device.
 *
 * \param[in] dwIdKind An \ref IDKIND_ "id kind".
 * \param[in] dwId A device index, \ref PID_ "Product ID" or serial number identifying the device to check, as specified by \c dwIdKind.
 * \return The IPv4 address of the listed device.
 * \par Status values
 *   <table class="params">
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_DEVICE_INDEX "INVALID_DEVICE_INDEX"</td>       <td>The device index is invalid, must be < LstGetCount().</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_DEVICE_SERIALNUMBER "INVALID_DEVICE_SERIALNUMBER"</td><td>There is no device with the requested serial number.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_PRODUCT_ID "INVALID_PRODUCT_ID"</td>         <td>There is no device with the requested product ID.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_NOT_SUPPORTED "NOT_SUPPORTED"</td>              <td>The indicated device is not a network device.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_VALUE "INVALID_VALUE"</td>              <td>The value of dwIdKind is invalid.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_LIBRARY_NOT_INITIALIZED "LIBRARY_NOT_INITIALIZED"</td>    <td>The library is not initialized, see LibInit().</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_SUCCESS "SUCCESS"</td>                    <td>The function executed successfully.</td></tr>
 *   </table>
 * \since 0.9
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef uint32_t(*LibTiePieLstDevGetIPv4Address_t)( uint32_t dwIdKind , uint32_t dwId );
#else
uint32_t LstDevGetIPv4Address( uint32_t dwIdKind , uint32_t dwId );
#endif

/**
 * \brief Get the IP port number of the listed device.
 *
 * \param[in] dwIdKind An \ref IDKIND_ "id kind".
 * \param[in] dwId A device index, \ref PID_ "Product ID" or serial number identifying the device to check, as specified by \c dwIdKind.
 * \return The IP port number of the listed device.
 * \par Status values
 *   <table class="params">
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_DEVICE_INDEX "INVALID_DEVICE_INDEX"</td>       <td>The device index is invalid, must be < LstGetCount().</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_DEVICE_SERIALNUMBER "INVALID_DEVICE_SERIALNUMBER"</td><td>There is no device with the requested serial number.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_PRODUCT_ID "INVALID_PRODUCT_ID"</td>         <td>There is no device with the requested product ID.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_NOT_SUPPORTED "NOT_SUPPORTED"</td>              <td>The indicated device is not a network device.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_VALUE "INVALID_VALUE"</td>              <td>The value of dwIdKind is invalid.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_LIBRARY_NOT_INITIALIZED "LIBRARY_NOT_INITIALIZED"</td>    <td>The library is not initialized, see LibInit().</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_SUCCESS "SUCCESS"</td>                    <td>The function executed successfully.</td></tr>
 *   </table>
 * \since 0.9
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef uint16_t(*LibTiePieLstDevGetIPPort_t)( uint32_t dwIdKind , uint32_t dwId );
#else
uint16_t LstDevGetIPPort( uint32_t dwIdKind , uint32_t dwId );
#endif

/**
 * \brief Check whether the listed device is connected to a server.
 *
 * \param[in] dwIdKind An \ref IDKIND_ "id kind".
 * \param[in] dwId A device index, \ref PID_ "Product ID" or serial number identifying the device to check, as specified by \c dwIdKind.
 * \return #BOOL8_TRUE if the device isconnected to a server, #BOOL8_FALSE otherwise.
 * \since 0.9
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef bool8_t(*LibTiePieLstDevHasServer_t)( uint32_t dwIdKind , uint32_t dwId );
#else
bool8_t LstDevHasServer( uint32_t dwIdKind , uint32_t dwId );
#endif

/**
 * \brief Get the server handle of the server the listed device is connected to.
 *
 * \param[in] dwIdKind An \ref IDKIND_ "id kind".
 * \param[in] dwId A device index, \ref PID_ "Product ID" or serial number identifying the device to check, as specified by \c dwIdKind.
 * \return A server handle, or #LIBTIEPIE_HANDLE_INVALID on error.
 * \since 0.9
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef LibTiePieHandle_t(*LibTiePieLstDevGetServer_t)( uint32_t dwIdKind , uint32_t dwId );
#else
LibTiePieHandle_t LstDevGetServer( uint32_t dwIdKind , uint32_t dwId );
#endif

/**
 * \brief Get the device types of the listed device.
 *
 * \param[in] dwIdKind An \ref IDKIND_ "id kind".
 * \param[in] dwId A device index, \ref PID_ "Product ID" or serial number identifying the device to check, as specified by \c dwIdKind.
 * \return OR-ed mask of \ref DEVICETYPE_ "device types".
 * \par Status values
 *   <table class="params">
 *   <tr><td>\ref LIBTIEPIESTATUS_INITIALIZATION_FAILED "INITIALIZATION_FAILED"</td>      <td>The instrument's initialization failed, please contact TiePie engineering support.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_EEPROM "INVALID_EEPROM"</td>             <td>The instrument's EEPROM content is damaged, please contact TiePie engineering support.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_FIRMWARE "INVALID_FIRMWARE"</td>           <td>The currently used firmware is not supported \cond EXTENDED_API , see LstDevGetRecommendedFirmwareVersion() \endcond.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_DRIVER "INVALID_DRIVER"</td>             <td>The currently installed driver is not supported, see LstDevGetRecommendedDriverVersion(). (Windows only)</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_DEVICE_INDEX "INVALID_DEVICE_INDEX"</td>       <td>The device index is invalid, must be < LstGetCount().</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_DEVICE_SERIALNUMBER "INVALID_DEVICE_SERIALNUMBER"</td><td>There is no device with the requested serial number.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_PRODUCT_ID "INVALID_PRODUCT_ID"</td>         <td>There is no device with the requested product ID.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_VALUE "INVALID_VALUE"</td>              <td>The value of dwIdKind is invalid.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_DRIVER "INVALID_DRIVER"</td>             <td>The currently installed driver is not supported, see LstDevGetRecommendedDriverVersion(). (Windows only)</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_LIBRARY_NOT_INITIALIZED "LIBRARY_NOT_INITIALIZED"</td>    <td>The library is not initialized, see LibInit().</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_SUCCESS "SUCCESS"</td>                    <td>The function executed successfully.</td></tr>
 *   </table>
 *
 * \par Example
 * \code{.c}
 * uint32_t dwDeviceTypes = LstDevGetTypes( dwIdKind , dwId );
 *
 * // Test all device types:
 * if( dwDeviceTypes & DEVICETYPE_OSCILLOSCOPE )
 *   printf( "DEVICETYPE_OSCILLOSCOPE\n" );
 *
 * if( dwDeviceTypes & DEVICETYPE_GENERATOR )
 *   printf( "DEVICETYPE_GENERATOR\n" );
 *
 * if( dwDeviceTypes & DEVICETYPE_I2CHOST )
 *   printf( "DEVICETYPE_I2CHOST\n" );
 * \endcode
 *
 * \since 0.5
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef uint32_t(*LibTiePieLstDevGetTypes_t)( uint32_t dwIdKind , uint32_t dwId );
#else
uint32_t LstDevGetTypes( uint32_t dwIdKind , uint32_t dwId );
#endif

/**
 * \defgroup lst_combined Combined devices
 * \{
 * \brief Functions to retrieve information from the individual devices in combined devices.
 *
 * <h3>Methods to identify the required contained device in a combined device</h3>
 *
 * To identify a contained device in a combined device, the combined device must be adressed and the also the contained device in it.
 * Three different methods to identify a contained device in a combined are available:
 *
 * - Identify by device list index (#IDKIND_INDEX), e.g.:
 * \code{.c}
 * TpDate_t dwNumber = LstCbDevGetCalibrationDate( IDKIND_INDEX , 4, 27912 ); // Get the calibration date from the continaed device with serial number 27912 in the combined device at list index 4.
 * \endcode
 * - Identify by serial number (#IDKIND_SERIALNUMBER), e.g.:
 * \code{.c}
 * TpDate_t dwNumber = LstCbDevGetCalibrationDate( IDKIND_SERIALNUMBER , 1, 27912 ); // Get the calibration date from the continaed device with serial number 27912 in the combined device with serial number 1.
 * \endcode
 * - Identify by product id (#IDKIND_PRODUCTID), e.g.:
 * \code{.c}
 * TpDate_t dwNumber = LstCbDevGetCalibrationDate( IDKIND_PRODUCTID , PID_COMBI, 27912 ); // Get the calibration date from the continaed device with serial number 27912 in the first combined device in the device list.
 * \endcode
 *
 */

// Workaround: Without this line Doxygen adds the documentation below to the group above.

/**
 * \brief Get the serial numbers of the individual devices contained in a combined device.
 *
 * \param[in] dwIdKind An \ref IDKIND_ "id kind".
 * \param[in] dwId A device index, \ref PID_ "Product ID" or serial number identifying the \b combined device to check, as specified by \c dwIdKind.
 * \param[out] pBuffer A pointer to a buffer for the serial numbers.
 * \param[in] dwBufferLength The length of the buffer, in bytes.
 * \return The number of devices in the combined device, or zero if the device isn't a combined device.
 * \par Status values
 *   <table class="params">
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_VALUE "INVALID_VALUE"</td>              <td>The value of dwIdKind is invalid.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_DEVICE_INDEX "INVALID_DEVICE_INDEX"</td>       <td>The device index is invalid, must be < LstGetCount().</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_PRODUCT_ID "INVALID_PRODUCT_ID"</td>         <td>There is no combined device with the requested product ID.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_DEVICE_SERIALNUMBER "INVALID_DEVICE_SERIALNUMBER"</td><td>There is no combined device with the requested serial number.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_NOT_SUPPORTED "NOT_SUPPORTED"</td>              <td>The indicated device is not a combined device.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_LIBRARY_NOT_INITIALIZED "LIBRARY_NOT_INITIALIZED"</td>    <td>The library is not initialized, see LibInit().</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_SUCCESS "SUCCESS"</td>                    <td>The function executed successfully.</td></tr>
 *   </table>
 *
 * \par Example
 * \code{c}
 * uint32_t dwLength = LstDevGetContainedSerialNumbers( dwIdKind , dwId , NULL , 0 );
 * uint32_t* pSerialNumbers = malloc( sizeof( uint32_t ) * dwLength );
 * dwLength = LstDevGetContainedSerialNumbers( dwIdKind , dwId , pSerialNumbers , dwLength );
 *
 * for( i = 0 ; i < dwLength ; i++ )
 * {
 *   printf( "%u\n" , pSerialNumbers[ i ] );
 * }
 *
 * free( pSerialNumbers );
 * \endcode
 *
 * \since 0.4.1
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef uint32_t(*LibTiePieLstDevGetContainedSerialNumbers_t)( uint32_t dwIdKind , uint32_t dwId , uint32_t* pBuffer , uint32_t dwBufferLength );
#else
uint32_t LstDevGetContainedSerialNumbers( uint32_t dwIdKind , uint32_t dwId , uint32_t* pBuffer , uint32_t dwBufferLength );
#endif

/**
 * \brief Get the product id of a device contained in a combined device.
 *
 * \param[in] dwIdKind An \ref IDKIND_ "id kind".
 * \param[in] dwId A device index, \ref PID_ "Product ID" or serial number identifying the \b combined device to check, as specified by \c dwIdKind.
 * \param[in] dwContainedDeviceSerialNumber The serial number identifying the \b contained device inside the combined device.
 * \return The \ref PID_ "product id" of the contained device.
 * \par Status values
 *   <table class="params">
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_VALUE "INVALID_VALUE"</td>                        <td>The value of dwIdKind is invalid.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_DEVICE_INDEX "INVALID_DEVICE_INDEX"</td>                 <td>The device index is invalid, must be < LstGetCount().</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_PRODUCT_ID "INVALID_PRODUCT_ID"</td>                   <td>There is no combined device with the requested product ID.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_DEVICE_SERIALNUMBER "INVALID_DEVICE_SERIALNUMBER"</td>          <td>There is no combined device with the requested serial number.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_NOT_SUPPORTED "NOT_SUPPORTED"</td>                        <td>The indicated device is not a combined device or the contained device does not support reading a product id.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_CONTAINED_DEVICE_SERIALNUMBER "INVALID_CONTAINED_DEVICE_SERIALNUMBER"</td><td>There is no contained device with the requested serial number in de combined device.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_LIBRARY_NOT_INITIALIZED "LIBRARY_NOT_INITIALIZED"</td>              <td>The library is not initialized, see LibInit().</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_SUCCESS "SUCCESS"</td>                              <td>The function executed successfully.</td></tr>
 *   </table>
 * \since 0.4.1
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef uint32_t(*LibTiePieLstCbDevGetProductId_t)( uint32_t dwIdKind , uint32_t dwId , uint32_t dwContainedDeviceSerialNumber );
#else
uint32_t LstCbDevGetProductId( uint32_t dwIdKind , uint32_t dwId , uint32_t dwContainedDeviceSerialNumber );
#endif

//! \cond EXTENDED_API

/**
 * \brief Get the vendor id of a device contained in a combined device.
 *
 * \param[in] dwIdKind An \ref IDKIND_ "id kind".
 * \param[in] dwId A device index, \ref PID_ "Product ID" or serial number identifying the \b combined device to check, as specified by \c dwIdKind.
 * \param[in] dwContainedDeviceSerialNumber The serial number identifying the \b contained device inside the combined device.
 * \return The vendor id of the contained device.
 * \par Status values
 *   <table class="params">
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_VALUE "INVALID_VALUE"</td>                        <td>The value of dwIdKind is invalid.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_DEVICE_INDEX "INVALID_DEVICE_INDEX"</td>                 <td>The device index is invalid, must be < LstGetCount().</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_PRODUCT_ID "INVALID_PRODUCT_ID"</td>                   <td>There is no combined device with the requested product ID.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_DEVICE_SERIALNUMBER "INVALID_DEVICE_SERIALNUMBER"</td>          <td>There is no combined device with the requested serial number.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_NOT_SUPPORTED "NOT_SUPPORTED"</td>                        <td>The indicated device is not a combined device or the contained device does not support reading a vendor id.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_CONTAINED_DEVICE_SERIALNUMBER "INVALID_CONTAINED_DEVICE_SERIALNUMBER"</td><td>There is no contained device with the requested serial number in de combined device.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_LIBRARY_NOT_INITIALIZED "LIBRARY_NOT_INITIALIZED"</td>              <td>The library is not initialized, see LibInit().</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_SUCCESS "SUCCESS"</td>                              <td>The function executed successfully.</td></tr>
 *   </table>
 * \since 0.4.1
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef uint32_t(*LibTiePieLstCbDevGetVendorId_t)( uint32_t dwIdKind , uint32_t dwId , uint32_t dwContainedDeviceSerialNumber );
#else
uint32_t LstCbDevGetVendorId( uint32_t dwIdKind , uint32_t dwId , uint32_t dwContainedDeviceSerialNumber );
#endif

//! \endcond

/**
 * \brief Get the full name of a device contained in a combined device.
 *
 * E.g. <tt>Handyscope HS5-530XMS</tt>
 *
 * \param[in] dwIdKind An \ref IDKIND_ "id kind".
 * \param[in] dwId A device index, \ref PID_ "Product ID" or serial number identifying the \b combined device to check, as specified by \c dwIdKind.
 * \param[in] dwContainedDeviceSerialNumber The serial number identifying the \b contained device inside the combined device.
 * \param[out] pBuffer A pointer to a buffer for the name.
 * \param[in] dwBufferLength The length of the buffer, in bytes.
 * \return The length of the name in bytes, excluding terminating zero.
 * \par Status values
 *   <table class="params">
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_VALUE "INVALID_VALUE"</td>                        <td>The value of dwIdKind is invalid.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_DEVICE_INDEX "INVALID_DEVICE_INDEX"</td>                 <td>The device index is invalid, must be < LstGetCount().</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_PRODUCT_ID "INVALID_PRODUCT_ID"</td>                   <td>There is no combined device with the requested product ID.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_DEVICE_SERIALNUMBER "INVALID_DEVICE_SERIALNUMBER"</td>          <td>There is no combined device with the requested serial number.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_NOT_SUPPORTED "NOT_SUPPORTED"</td>                        <td>The indicated device is not a combined device or the contained device does not support reading a name.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_CONTAINED_DEVICE_SERIALNUMBER "INVALID_CONTAINED_DEVICE_SERIALNUMBER"</td><td>There is no contained device with the requested serial number in de combined device.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_LIBRARY_NOT_INITIALIZED "LIBRARY_NOT_INITIALIZED"</td>              <td>The library is not initialized, see LibInit().</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_SUCCESS "SUCCESS"</td>                              <td>The function executed successfully.</td></tr>
 *   </table>
 * \since 0.4.1
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef uint32_t(*LibTiePieLstCbDevGetName_t)( uint32_t dwIdKind , uint32_t dwId , uint32_t dwContainedDeviceSerialNumber , char* pBuffer , uint32_t dwBufferLength );
#else
uint32_t LstCbDevGetName( uint32_t dwIdKind , uint32_t dwId , uint32_t dwContainedDeviceSerialNumber , char* pBuffer , uint32_t dwBufferLength );
#endif

/**
 * \brief Get the short name of a device contained in a combined device.
 *
 * E.g. <tt>HS5-530XMS</tt>
 *
 * \param[in] dwIdKind An \ref IDKIND_ "id kind".
 * \param[in] dwId A device index, \ref PID_ "Product ID" or serial number identifying the \b combined device to check, as specified by \c dwIdKind.
 * \param[in] dwContainedDeviceSerialNumber The serial number identifying the \b contained device inside the combined device.
 * \param[out] pBuffer A pointer to a buffer for the name.
 * \param[in] dwBufferLength The length of the buffer, in bytes.
 * \return The length of the name in bytes, excluding terminating zero.
 * \par Status values
 *   <table class="params">
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_VALUE "INVALID_VALUE"</td>                        <td>The value of dwIdKind is invalid.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_DEVICE_INDEX "INVALID_DEVICE_INDEX"</td>                 <td>The device index is invalid, must be < LstGetCount().</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_PRODUCT_ID "INVALID_PRODUCT_ID"</td>                   <td>There is no combined device with the requested product ID.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_DEVICE_SERIALNUMBER "INVALID_DEVICE_SERIALNUMBER"</td>          <td>There is no combined device with the requested serial number.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_NOT_SUPPORTED "NOT_SUPPORTED"</td>                        <td>The indicated device is not a combined device or the contained device does not support reading a name.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_CONTAINED_DEVICE_SERIALNUMBER "INVALID_CONTAINED_DEVICE_SERIALNUMBER"</td><td>There is no contained device with the requested serial number in de combined device.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_LIBRARY_NOT_INITIALIZED "LIBRARY_NOT_INITIALIZED"</td>              <td>The library is not initialized, see LibInit().</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_SUCCESS "SUCCESS"</td>                              <td>The function executed successfully.</td></tr>
 *   </table>
 * \since 0.4.1
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef uint32_t(*LibTiePieLstCbDevGetNameShort_t)( uint32_t dwIdKind , uint32_t dwId , uint32_t dwContainedDeviceSerialNumber , char* pBuffer , uint32_t dwBufferLength );
#else
uint32_t LstCbDevGetNameShort( uint32_t dwIdKind , uint32_t dwId , uint32_t dwContainedDeviceSerialNumber , char* pBuffer , uint32_t dwBufferLength );
#endif

/**
 * \brief Get the short name without model postfix of a device contained in a combined device.
 *
 * E.g. <tt>HS5</tt>
 *
 * \param[in] dwIdKind An \ref IDKIND_ "id kind".
 * \param[in] dwId A device index, \ref PID_ "Product ID" or serial number identifying the \b combined device to check, as specified by \c dwIdKind.
 * \param[in] dwContainedDeviceSerialNumber The serial number identifying the \b contained device inside the combined device.
 * \param[out] pBuffer A pointer to a buffer for the name.
 * \param[in] dwBufferLength The length of the buffer, in bytes.
 * \return The length of the name in bytes, excluding terminating zero.
 * \par Status values
 *   <table class="params">
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_VALUE "INVALID_VALUE"</td>                        <td>The value of dwIdKind is invalid.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_DEVICE_INDEX "INVALID_DEVICE_INDEX"</td>                 <td>The device index is invalid, must be < LstGetCount().</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_PRODUCT_ID "INVALID_PRODUCT_ID"</td>                   <td>There is no combined device with the requested product ID.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_DEVICE_SERIALNUMBER "INVALID_DEVICE_SERIALNUMBER"</td>          <td>There is no combined device with the requested serial number.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_NOT_SUPPORTED "NOT_SUPPORTED"</td>                        <td>The indicated device is not a combined device or the contained device does not support reading a name.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_CONTAINED_DEVICE_SERIALNUMBER "INVALID_CONTAINED_DEVICE_SERIALNUMBER"</td><td>There is no contained device with the requested serial number in de combined device.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_LIBRARY_NOT_INITIALIZED "LIBRARY_NOT_INITIALIZED"</td>              <td>The library is not initialized, see LibInit().</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_SUCCESS "SUCCESS"</td>                              <td>The function executed successfully.</td></tr>
 *   </table>
 * \since 0.4.4
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef uint32_t(*LibTiePieLstCbDevGetNameShortest_t)( uint32_t dwIdKind , uint32_t dwId , uint32_t dwContainedDeviceSerialNumber , char* pBuffer , uint32_t dwBufferLength );
#else
uint32_t LstCbDevGetNameShortest( uint32_t dwIdKind , uint32_t dwId , uint32_t dwContainedDeviceSerialNumber , char* pBuffer , uint32_t dwBufferLength );
#endif

/**
 * \brief Get the driver version of a device contained in a combined device.
 *
 * \param[in] dwIdKind An \ref IDKIND_ "id kind".
 * \param[in] dwId A device index, \ref PID_ "Product ID" or serial number identifying the \b combined device to check, as specified by \c dwIdKind.
 * \param[in] dwContainedDeviceSerialNumber The serial number identifying the \b contained device inside the combined device.
 * \return The driver \ref #TpVersion_t " version" of the contained device, or zero if no driver version is available.
 * \par Status values
 *   <table class="params">
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_VALUE "INVALID_VALUE"</td>                        <td>The value of dwIdKind is invalid.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_DEVICE_INDEX "INVALID_DEVICE_INDEX"</td>                 <td>The device index is invalid, must be < LstGetCount().</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_PRODUCT_ID "INVALID_PRODUCT_ID"</td>                   <td>There is no combined device with the requested product ID.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_DEVICE_SERIALNUMBER "INVALID_DEVICE_SERIALNUMBER"</td>          <td>There is no combined device with the requested serial number.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_NOT_SUPPORTED "NOT_SUPPORTED"</td>                        <td>The indicated device is not a combined device or the contained device does not support reading a driver version or does not require a driver.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_CONTAINED_DEVICE_SERIALNUMBER "INVALID_CONTAINED_DEVICE_SERIALNUMBER"</td><td>There is no contained device with the requested serial number in de combined device.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_LIBRARY_NOT_INITIALIZED "LIBRARY_NOT_INITIALIZED"</td>              <td>The library is not initialized, see LibInit().</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_SUCCESS "SUCCESS"</td>                              <td>The function executed successfully.</td></tr>
 *   </table>
 * \since 0.4.1
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef TpVersion_t(*LibTiePieLstCbDevGetDriverVersion_t)( uint32_t dwIdKind , uint32_t dwId , uint32_t dwContainedDeviceSerialNumber );
#else
TpVersion_t LstCbDevGetDriverVersion( uint32_t dwIdKind , uint32_t dwId , uint32_t dwContainedDeviceSerialNumber );
#endif

/**
 * \brief Get the firmware version of a device contained in a combined device.
 *
 * \param[in] dwIdKind An \ref IDKIND_ "id kind".
 * \param[in] dwId A device index, \ref PID_ "Product ID" or serial number identifying the \b combined device to check, as specified by \c dwIdKind.
 * \param[in] dwContainedDeviceSerialNumber The serial number identifying the \b contained device inside the combined device.
 * \return The firmware \ref #TpVersion_t " version" of the contained device, or zero if no firmware version is available.
 * \par Status values
 *   <table class="params">
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_VALUE "INVALID_VALUE"</td>                        <td>The value of dwIdKind is invalid.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_DEVICE_INDEX "INVALID_DEVICE_INDEX"</td>                 <td>The device index is invalid, must be < LstGetCount().</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_PRODUCT_ID "INVALID_PRODUCT_ID"</td>                   <td>There is no combined device with the requested product ID.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_DEVICE_SERIALNUMBER "INVALID_DEVICE_SERIALNUMBER"</td>          <td>There is no combined device with the requested serial number.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_NOT_SUPPORTED "NOT_SUPPORTED"</td>                        <td>The indicated device is not a combined device or the contained device does not support reading a firmware version or does not require firmware.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_CONTAINED_DEVICE_SERIALNUMBER "INVALID_CONTAINED_DEVICE_SERIALNUMBER"</td><td>There is no contained device with the requested serial number in de combined device.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_LIBRARY_NOT_INITIALIZED "LIBRARY_NOT_INITIALIZED"</td>              <td>The library is not initialized, see LibInit().</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_SUCCESS "SUCCESS"</td>                              <td>The function executed successfully.</td></tr>
 *   </table>
 * \since 0.4.1
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef TpVersion_t(*LibTiePieLstCbDevGetFirmwareVersion_t)( uint32_t dwIdKind , uint32_t dwId , uint32_t dwContainedDeviceSerialNumber );
#else
TpVersion_t LstCbDevGetFirmwareVersion( uint32_t dwIdKind , uint32_t dwId , uint32_t dwContainedDeviceSerialNumber );
#endif

/**
 * \brief Get the calibration date of a device contained in a combined device.
 *
 * \param[in] dwIdKind An \ref IDKIND_ "id kind".
 * \param[in] dwId A device index, \ref PID_ "Product ID" or serial number identifying the \b combined device to check, as specified by \c dwIdKind.
 * \param[in] dwContainedDeviceSerialNumber The serial number identifying the \b contained device inside the combined device.
 * \return The calibration \ref #TpDate_t " date" of the contained device, or zero if no calibration date is available.
 * \par Status values
 *   <table class="params">
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_VALUE "INVALID_VALUE"</td>                        <td>The value of dwIdKind is invalid.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_DEVICE_INDEX "INVALID_DEVICE_INDEX"</td>                 <td>The device index is invalid, must be < LstGetCount().</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_PRODUCT_ID "INVALID_PRODUCT_ID"</td>                   <td>There is no combined device with the requested product ID.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_DEVICE_SERIALNUMBER "INVALID_DEVICE_SERIALNUMBER"</td>          <td>There is no combined device with the requested serial number.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_NOT_SUPPORTED "NOT_SUPPORTED"</td>                        <td>The indicated device is not a combined device or the contained device does not have a calibration date.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_CONTAINED_DEVICE_SERIALNUMBER "INVALID_CONTAINED_DEVICE_SERIALNUMBER"</td><td>There is no contained device with the requested serial number in de combined device.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_LIBRARY_NOT_INITIALIZED "LIBRARY_NOT_INITIALIZED"</td>              <td>The library is not initialized, see LibInit().</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_SUCCESS "SUCCESS"</td>                              <td>The function executed successfully.</td></tr>
 *   </table>
 * \since 0.4.1
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef TpDate_t(*LibTiePieLstCbDevGetCalibrationDate_t)( uint32_t dwIdKind , uint32_t dwId , uint32_t dwContainedDeviceSerialNumber );
#else
TpDate_t LstCbDevGetCalibrationDate( uint32_t dwIdKind , uint32_t dwId , uint32_t dwContainedDeviceSerialNumber );
#endif

/**
 * \brief Get the channel count of an oscilloscope contained in a combined oscilloscope.
 *
 * \param[in] dwIdKind An \ref IDKIND_ "id kind".
 * \param[in] dwId A device index, \ref PID_ "Product ID" or serial number identifying the \b combined oscilloscope to check, as specified by \c dwIdKind.
 * \param[in] dwContainedDeviceSerialNumber The serial number identifying the \b contained oscilloscope inside the combined oscilloscope.
 * \return The channel count of the contained oscilloscope.
 * \par Status values
 *   <table class="params">
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_VALUE "INVALID_VALUE"</td>                        <td>The value of dwIdKind is invalid.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_DEVICE_INDEX "INVALID_DEVICE_INDEX"</td>                 <td>The device index is invalid, must be < LstGetCount().</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_PRODUCT_ID "INVALID_PRODUCT_ID"</td>                   <td>There is no combined oscilloscope with the requested product ID.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_DEVICE_SERIALNUMBER "INVALID_DEVICE_SERIALNUMBER"</td>          <td>There is no combined oscilloscope with the requested serial number.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_NOT_SUPPORTED "NOT_SUPPORTED"</td>                        <td>The indicated device is not a combined oscilloscope.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_CONTAINED_DEVICE_SERIALNUMBER "INVALID_CONTAINED_DEVICE_SERIALNUMBER"</td><td>There is no contained device with the requested serial number in de combined device.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_LIBRARY_NOT_INITIALIZED "LIBRARY_NOT_INITIALIZED"</td>              <td>The library is not initialized, see LibInit().</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_SUCCESS "SUCCESS"</td>                              <td>The function executed successfully.</td></tr>
 *   </table>
 * \since 0.4.1
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef uint16_t(*LibTiePieLstCbScpGetChannelCount_t)( uint32_t dwIdKind , uint32_t dwId , uint32_t dwContainedDeviceSerialNumber );
#else
uint16_t LstCbScpGetChannelCount( uint32_t dwIdKind , uint32_t dwId , uint32_t dwContainedDeviceSerialNumber );
#endif

/**
 * \}
 * \}
 * \defgroup lst_notifications Notifications
 * \{
 * \brief Functions to set notifications that are triggered when the device list is changed.
 *
 * LibTiePie can notify the calling application that the device list is changed in different ways:
 * - by calling callback functions
 * - by setting events
 * - by sending messages (Windows only)
 *
 * \defgroup lst_notifications_deviceadded Device added
 * \{
 * \brief Functions to set notifications that are triggered when a device is added to the list.
 */

// Workaround: Without this line Doxygen adds the documentation below to the group above.

/**
 * \brief Set a callback function which is called when a device is added to the device list.
 *
 * \param[in] pCallback A pointer to the \ref TpCallbackDeviceList_t "callback" function. Use \c NULL to disable.
 * \param[in] pData Optional user data.
 * \par Status values
 *   <table class="params">
 *   <tr><td>\ref LIBTIEPIESTATUS_LIBRARY_NOT_INITIALIZED "LIBRARY_NOT_INITIALIZED"</td><td>The library is not initialized, see LibInit().</td></tr>
 *   <tr><td>#LIBTIEPIESTATUS_SUCCESS                </td><td></td></tr>
 *   </table>
 * \since 0.5
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef void(*LibTiePieLstSetCallbackDeviceAdded_t)( TpCallbackDeviceList_t pCallback , void* pData );
#else
void LstSetCallbackDeviceAdded( TpCallbackDeviceList_t pCallback , void* pData );
#endif

/**
 * \}
 * \defgroup lst_notifications_deviceremoved Device removed
 * \{
 * \brief Functions to set notifications that are triggered when a device is removed from the list.
 */

// Workaround: Without this line Doxygen adds the documentation below to the group above.

/**
 * \brief Set a callback function which is called when a device is removed from the device list.
 *
 * \param[in] pCallback A pointer to the \ref TpCallbackDeviceList_t "callback" function. Use \c NULL to disable.
 * \param[in] pData Optional user data.
 * \par Status values
 *   <table class="params">
 *   <tr><td>\ref LIBTIEPIESTATUS_LIBRARY_NOT_INITIALIZED "LIBRARY_NOT_INITIALIZED"</td><td>The library is not initialized, see LibInit().</td></tr>
 *   <tr><td>#LIBTIEPIESTATUS_SUCCESS                </td><td></td></tr>
 *   </table>
 * \since 0.5
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef void(*LibTiePieLstSetCallbackDeviceRemoved_t)( TpCallbackDeviceList_t pCallback , void* pData );
#else
void LstSetCallbackDeviceRemoved( TpCallbackDeviceList_t pCallback , void* pData );
#endif

/**
 * \}
 * \defgroup lst_notifications_devcanopenchanged Device can open changed
 * \{
 * \brief Functions to set notifications that are triggered when a device is removed from the list.
 */

// Workaround: Without this line Doxygen adds the documentation below to the group above.

/**
 * \brief Set a callback function which is called when the device can open property changes.
 *
 * \param[in] pCallback A pointer to the \ref TpCallbackDeviceList_t "callback" function. Use \c NULL to disable.
 * \param[in] pData Optional user data.
 * \par Status values
 *   <table class="params">
 *   <tr><td>\ref LIBTIEPIESTATUS_LIBRARY_NOT_INITIALIZED "LIBRARY_NOT_INITIALIZED"</td><td>The library is not initialized, see LibInit().</td></tr>
 *   <tr><td>#LIBTIEPIESTATUS_SUCCESS                </td><td></td></tr>
 *   </table>
 * \since 0.6
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef void(*LibTiePieLstSetCallbackDeviceCanOpenChanged_t)( TpCallbackDeviceList_t pCallback , void* pData );
#else
void LstSetCallbackDeviceCanOpenChanged( TpCallbackDeviceList_t pCallback , void* pData );
#endif

/**
 * \}
 */

#ifdef LIBTIEPIE_LINUX

/**
 * \ingroup lst_notifications_deviceadded
 * \brief Set an event file descriptor which is set when a device is added to the device list.
 *
 * \param[in] fdEvent An event file descriptor. Use \c <0 to disable.
 * \note This function is only available on GNU/Linux.
 * \par Status values
 *   <table class="params">
 *   <tr><td>\ref LIBTIEPIESTATUS_LIBRARY_NOT_INITIALIZED "LIBRARY_NOT_INITIALIZED"</td><td>The library is not initialized, see LibInit().</td></tr>
 *   <tr><td>#LIBTIEPIESTATUS_SUCCESS                </td><td></td></tr>
 *   </table>
 * \since 0.4.0
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef void(*LibTiePieLstSetEventDeviceAdded_t)( int fdEvent );
#else
void LstSetEventDeviceAdded( int fdEvent );
#endif

/**
 * \ingroup lst_notifications_deviceremoved
 * \brief Set an event file descriptor which is set when a device is removed from the device list.
 *
 * \param[in] fdEvent an event file descriptor. Use \c <0 to disable.
 * \note This function is only available on GNU/Linux.
 * \par Status values
 *   <table class="params">
 *   <tr><td>\ref LIBTIEPIESTATUS_LIBRARY_NOT_INITIALIZED "LIBRARY_NOT_INITIALIZED"</td><td>The library is not initialized, see LibInit().</td></tr>
 *   <tr><td>#LIBTIEPIESTATUS_SUCCESS                </td><td></td></tr>
 *   </table>
 * \since 0.4.0
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef void(*LibTiePieLstSetEventDeviceRemoved_t)( int fdEvent );
#else
void LstSetEventDeviceRemoved( int fdEvent );
#endif

/**
 * \ingroup lst_notifications_devcanopenchanged
 * \brief Set an event file descriptor which is set when the device can open property changes.
 *
 * \param[in] fdEvent an event file descriptor. Use \c <0 to disable.
 * \note This function is only available on GNU/Linux.
 * \par Status values
 *   <table class="params">
 *   <tr><td>\ref LIBTIEPIESTATUS_LIBRARY_NOT_INITIALIZED "LIBRARY_NOT_INITIALIZED"</td><td>The library is not initialized, see LibInit().</td></tr>
 *   <tr><td>#LIBTIEPIESTATUS_SUCCESS                </td><td></td></tr>
 *   </table>
 * \since 0.6
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef void(*LibTiePieLstSetEventDeviceCanOpenChanged_t)( int fdEvent );
#else
void LstSetEventDeviceCanOpenChanged( int fdEvent );
#endif

#endif

#ifdef LIBTIEPIE_WINDOWS

/**
 * \ingroup lst_notifications_deviceadded
 * \brief Set an event object handle which is set when a device is added to the device list.
 *
 * \param[in] hEvent A handle to the event object. Use \c NULL to disable.
 * \note This function is only available on Windows.
 * \par Status values
 *   <table class="params">
 *   <tr><td>\ref LIBTIEPIESTATUS_LIBRARY_NOT_INITIALIZED "LIBRARY_NOT_INITIALIZED"</td><td>The library is not initialized, see LibInit().</td></tr>
 *   <tr><td>#LIBTIEPIESTATUS_SUCCESS                </td><td></td></tr>
 *   </table>
 * \since 0.4.0
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef void(*LibTiePieLstSetEventDeviceAdded_t)( HANDLE hEvent );
#else
void LstSetEventDeviceAdded( HANDLE hEvent );
#endif

/**
 * \ingroup lst_notifications_deviceremoved
 * \brief Set an event object handle which is set when a device is removed from the device list.
 *
 * \param[in] hEvent A handle to the event object. Use \c NULL to disable.
 * \note This function is only available on Windows.
 * \par Status values
 *   <table class="params">
 *   <tr><td>\ref LIBTIEPIESTATUS_LIBRARY_NOT_INITIALIZED "LIBRARY_NOT_INITIALIZED"</td><td>The library is not initialized, see LibInit().</td></tr>
 *   <tr><td>#LIBTIEPIESTATUS_SUCCESS                </td><td></td></tr>
 *   </table>
 * \since 0.4.0
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef void(*LibTiePieLstSetEventDeviceRemoved_t)( HANDLE hEvent );
#else
void LstSetEventDeviceRemoved( HANDLE hEvent );
#endif

/**
 * \ingroup lst_notifications_devcanopenchanged
 * \brief Set an event object handle which is set when the device can open property changes.
 *
 * \param[in] hEvent A handle to the event object. Use \c NULL to disable.
 * \note This function is only available on Windows.
 * \par Status values
 *   <table class="params">
 *   <tr><td>\ref LIBTIEPIESTATUS_LIBRARY_NOT_INITIALIZED "LIBRARY_NOT_INITIALIZED"</td><td>The library is not initialized, see LibInit().</td></tr>
 *   <tr><td>#LIBTIEPIESTATUS_SUCCESS                </td><td></td></tr>
 *   </table>
 * \since 0.6
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef void(*LibTiePieLstSetEventDeviceCanOpenChanged_t)( HANDLE hEvent );
#else
void LstSetEventDeviceCanOpenChanged( HANDLE hEvent );
#endif

/**
 * \ingroup lst_notifications_deviceadded
 * \brief Set a window handle to which a #WM_LIBTIEPIE_LST_DEVICEADDED message is sent when a device is added to the device list.
 *
 * The parameters of the message contain the following:
 * - \c wParam contains the \ref DEVICETYPE_ "device types".
 * - \c lParam contains the serial number of the added device.
 *
 * \param[in] hWnd A handle to the window whose window procedure is to receive the message. Use \c NULL to disable.
 * \note This function is only available on Windows.
 * \par Status values
 *   <table class="params">
 *   <tr><td>\ref LIBTIEPIESTATUS_LIBRARY_NOT_INITIALIZED "LIBRARY_NOT_INITIALIZED"</td><td>The library is not initialized, see LibInit().</td></tr>
 *   <tr><td>#LIBTIEPIESTATUS_SUCCESS                </td><td></td></tr>
 *   </table>
 * \since 0.4.0
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef void(*LibTiePieLstSetMessageDeviceAdded_t)( HWND hWnd );
#else
void LstSetMessageDeviceAdded( HWND hWnd );
#endif

/**
 * \ingroup lst_notifications_deviceremoved
 * \brief Set a window handle to which a #WM_LIBTIEPIE_LST_DEVICEREMOVED message is sent when a device is removed from the device list.
 *
 * The parameters of the message contain the following:
 * - \c wParam contains the \ref DEVICETYPE_ "device types".
 * - \c lParam contains the serial number of the removed device.
 *
 * \param[in] hWnd A handle to the window whose window procedure is to receive the message. Use \c NULL to disable.
 * \note This function is only available on Windows.
 * \par Status values
 *   <table class="params">
 *   <tr><td>\ref LIBTIEPIESTATUS_LIBRARY_NOT_INITIALIZED "LIBRARY_NOT_INITIALIZED"</td><td>The library is not initialized, see LibInit().</td></tr>
 *   <tr><td>#LIBTIEPIESTATUS_SUCCESS                </td><td></td></tr>
 *   </table>
 * \since 0.4.0
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef void(*LibTiePieLstSetMessageDeviceRemoved_t)( HWND hWnd );
#else
void LstSetMessageDeviceRemoved( HWND hWnd );
#endif

/**
 * \ingroup lst_notifications_devcanopenchanged
 * \brief Set a window handle to which a #WM_LIBTIEPIE_LST_DEVICEREMOVED message is sent when the device can open property changes.
 *
 * The parameters of the message contain the following:
 * - \c wParam contains the \ref DEVICETYPE_ "device type".
 * - \c lParam contains the serial number of the changed device.
 *
 * \param[in] hWnd A handle to the window whose window procedure is to receive the message. Use \c NULL to disable.
 * \note This function is only available on Windows.
 * \par Status values
 *   <table class="params">
 *   <tr><td>\ref LIBTIEPIESTATUS_LIBRARY_NOT_INITIALIZED "LIBRARY_NOT_INITIALIZED"</td><td>The library is not initialized, see LibInit().</td></tr>
 *   <tr><td>#LIBTIEPIESTATUS_SUCCESS                </td><td></td></tr>
 *   </table>
 * \since 0.6
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef void(*LibTiePieLstSetMessageDeviceCanOpenChanged_t)( HWND hWnd );
#else
void LstSetMessageDeviceCanOpenChanged( HWND hWnd );
#endif

#endif

/**
 * \}
 * \}
 * \defgroup net Network
 * \{
 * \brief Network related functions.
 */

// Workaround: Without this line Doxygen adds the documentation below to the group above.

/**
 * \brief Check whether automatically detecting network instruments and instrument servers is enabled.
 *
 * \return #BOOL8_TRUE if enabled, #BOOL8_FALSE otherwise.
 * \since 0.9
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef bool8_t(*LibTiePieNetGetAutoDetectEnabled_t)( void );
#else
bool8_t NetGetAutoDetectEnabled( void );
#endif

/**
 * \brief Enable or disable automatic detection of network instruments and instrument servers.
 *
 * \param[in] bEnable #BOOL8_TRUE or #BOOL8_FALSE.
 * \return #BOOL8_TRUE if enabled, #BOOL8_FALSE otherwise.
 * \since 0.9
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef bool8_t(*LibTiePieNetSetAutoDetectEnabled_t)( bool8_t bEnable );
#else
bool8_t NetSetAutoDetectEnabled( bool8_t bEnable );
#endif

/**
 * \defgroup net_srv Servers
 * \{
 */

// Workaround: Without this line Doxygen adds the documentation below to the group above.

/**
 * \brief Add a server to the list of servers.
 *
 * \param[in] pURL Pointer to URL character buffer.
 * \param[in] dwURLLength Length of URL buffer or #LIBTIEPIE_STRING_LENGTH_NULL_TERMINATED.
 * \param[out] pHandle The handle to the added server or \c NULL.
 * \return #BOOL8_TRUE if added successfully, #BOOL8_FALSE otherwise.
 * \since 0.9
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef bool8_t(*LibTiePieNetSrvAdd_t)( const char* pURL , uint32_t dwURLLength , LibTiePieHandle_t* pHandle );
#else
bool8_t NetSrvAdd( const char* pURL , uint32_t dwURLLength , LibTiePieHandle_t* pHandle );
#endif

/**
 * \brief Remove a server from the list of servers
 *
 * \param[in] pURL Pointer to URL character buffer.
 * \param[in] dwURLLength Length of URL buffer or #LIBTIEPIE_STRING_LENGTH_NULL_TERMINATED.
 * \param[in] bForce If #BOOL8_TRUE all open devices are closed, if #BOOL8_FALSE remove only succeeds if no devices are open.
 * \return #BOOL8_TRUE if removed successfully, #BOOL8_FALSE otherwise.
 * \since 0.9
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef bool8_t(*LibTiePieNetSrvRemove_t)( const char* pURL , uint32_t dwURLLength , bool8_t bForce );
#else
bool8_t NetSrvRemove( const char* pURL , uint32_t dwURLLength , bool8_t bForce );
#endif

/**
 * \brief Get the number of servers available.
 *
 * \return The number of servers available.
 * \since 0.9
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef uint32_t(*LibTiePieNetSrvGetCount_t)( void );
#else
uint32_t NetSrvGetCount( void );
#endif

/**
 * \brief Get the handle of a server, based on its index in the list of servers
 *
 * \param[in] dwIndex A server index, \c 0 .. NetSrvGetCount() - 1.
 * \return The handle to the requested server or \c NULL.
 * \since 0.9
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef LibTiePieHandle_t(*LibTiePieNetSrvGetByIndex_t)( uint32_t dwIndex );
#else
LibTiePieHandle_t NetSrvGetByIndex( uint32_t dwIndex );
#endif

/**
 * \brief Get the handle of a server, based on its URL
 *
 * \param[in] pURL Pointer to URL character buffer.
 * \param[in] dwURLLength Length of URL buffer or #LIBTIEPIE_STRING_LENGTH_NULL_TERMINATED.
 * \return The handle to the requested server or \c NULL.
 * \since 0.9
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef LibTiePieHandle_t(*LibTiePieNetSrvGetByURL_t)( const char* pURL , uint32_t dwURLLength );
#else
LibTiePieHandle_t NetSrvGetByURL( const char* pURL , uint32_t dwURLLength );
#endif

/**
 * \defgroup net_srv_notifications Notifications
 * \{
 * \brief Functions to set notifications that are triggered when the server list is changed.
 *
 * LibTiePie can notify the calling application that the device list is changed in different ways:
 * - by calling callback functions
 * - by setting events
 * - by sending messages (Windows only)
 *
 * \defgroup net_srv_notifications_added Server added
 * \{
 * \brief Functions to set notifications that are triggered when a server is added to the server list.
 */

// Workaround: Without this line Doxygen adds the documentation below to the group above.

/**
 * \brief Set a callback function which is called when a server is added to the server list.
 *
 * \param[in] pCallback A pointer to the \ref TpCallbackHandle_t "callback" function. Use \c NULL to disable.
 * \param[in] pData Optional user data.
 * \par Status values
 *   <table class="params">
 *   <tr><td>\ref LIBTIEPIESTATUS_LIBRARY_NOT_INITIALIZED "LIBRARY_NOT_INITIALIZED"</td><td>The library is not initialized, see LibInit().</td></tr>
 *   <tr><td>#LIBTIEPIESTATUS_SUCCESS                </td><td></td></tr>
 *   </table>
 * \since 0.9
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef void(*LibTiePieNetSrvSetCallbackAdded_t)( TpCallbackHandle_t pCallback , void* pData );
#else
void NetSrvSetCallbackAdded( TpCallbackHandle_t pCallback , void* pData );
#endif

#ifdef LIBTIEPIE_LINUX

/**
 * \brief Set an event file descriptor which is set when a server is added to the server list.
 *
 * \param[in] fdEvent An event file descriptor. Use \c <0 to disable.
 * \note This function is only available on GNU/Linux.
 * \par Status values
 *   <table class="params">
 *   <tr><td>\ref LIBTIEPIESTATUS_LIBRARY_NOT_INITIALIZED "LIBRARY_NOT_INITIALIZED"</td><td>The library is not initialized, see LibInit().</td></tr>
 *   <tr><td>#LIBTIEPIESTATUS_SUCCESS                </td><td></td></tr>
 *   </table>
 * \since 0.9
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef void(*LibTiePieNetSrvSetEventAdded_t)( int fdEvent );
#else
void NetSrvSetEventAdded( int fdEvent );
#endif

#endif

#ifdef LIBTIEPIE_WINDOWS

/**
 * \brief Set an event object handle which is set when a server is added to the server list.
 *
 * \param[in] hEvent A handle to the event object. Use \c NULL to disable.
 * \note This function is only available on Windows.
 * \par Status values
 *   <table class="params">
 *   <tr><td>\ref LIBTIEPIESTATUS_LIBRARY_NOT_INITIALIZED "LIBRARY_NOT_INITIALIZED"</td><td>The library is not initialized, see LibInit().</td></tr>
 *   <tr><td>#LIBTIEPIESTATUS_SUCCESS                </td><td></td></tr>
 *   </table>
 * \since 0.9
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef void(*LibTiePieNetSrvSetEventAdded_t)( HANDLE hEvent );
#else
void NetSrvSetEventAdded( HANDLE hEvent );
#endif

/**
 * \brief Set a window handle to which a #WM_LIBTIEPIE_NETSRV_ADDED message is sent when a server is added to the server list.
 *
 * The parameters of the message contain the following:
 * - \c wParam contains the server handle.
 * - \c lParam is reserved.
 *
 * \param[in] hWnd A handle to the window whose window procedure is to receive the message. Use \c NULL to disable.
 * \note This function is only available on Windows.
 * \par Status values
 *   <table class="params">
 *   <tr><td>\ref LIBTIEPIESTATUS_LIBRARY_NOT_INITIALIZED "LIBRARY_NOT_INITIALIZED"</td><td>The library is not initialized, see LibInit().</td></tr>
 *   <tr><td>#LIBTIEPIESTATUS_SUCCESS                </td><td></td></tr>
 *   </table>
 * \since 0.9
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef void(*LibTiePieNetSrvSetMessageAdded_t)( HWND hWnd );
#else
void NetSrvSetMessageAdded( HWND hWnd );
#endif

#endif

/**
 * \}
 * \}
 * \}
 * \}
 * \defgroup objmain Object
 * \{
 * \brief Functions to control devices.
 *
 *     Before a device can be controlled or information can be retrieved from it, the device must be \ref OpenDev "opened" and a handle to it must be obtained.
 *     This handle is then used in the functions to access the device.
 *
 *     Devices can be \ref scp "oscilloscopes", \ref gen "generators" or \ref i2c "I2C Hosts".
 *     They have device specific functions which are listed in the dedicated sections and \ref dev "common" functions which are available fo all devices.
 *
 * \defgroup obj Common
 * \{
 * \brief Functions common to all objects.
 *
 *       These functions can be called with any handle.
 */

// Workaround: Without this line Doxygen adds the documentation below to the group above.

/**
 * \brief Close a object.
 *
 * When closing a object, its handle becomes invalid and must not be used again.
 *
 * \param[in] hHandle A handle identifying the object.
 * \par Status values
 *   <table class="params">
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_HANDLE "INVALID_HANDLE"</td>         <td>The handle to the device is invalid.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_LIBRARY_NOT_INITIALIZED "LIBRARY_NOT_INITIALIZED"</td><td>The library is not initialized, see LibInit().</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_SUCCESS "SUCCESS"</td>                <td>The function executed successfully.</td></tr>
 *   </table>
 * \see LstOpenDevice
 * \see LstOpenDeviceProtected
 * \see LstOpenOscilloscope
 * \see LstOpenGenerator
 * \see LstOpenI2CHost
 * \see LstDevGetServerHandle
 * \see NetSrvGetByIndex
 * \see NetSrvGetByURL
 * \since 0.6
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef void(*LibTiePieObjClose_t)( LibTiePieHandle_t hHandle );
#else
void ObjClose( LibTiePieHandle_t hHandle );
#endif

/**
 * \brief Check whether an object is removed.
 *
 * \param[in] hHandle A handle identifying the object.
 * \return #BOOL8_TRUE if removed, #BOOL8_FALSE otherwise.
 * \par Status values
 *   <table class="params">
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_HANDLE "INVALID_HANDLE"</td>         <td>The handle to the device is invalid.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_LIBRARY_NOT_INITIALIZED "LIBRARY_NOT_INITIALIZED"</td><td>The library is not initialized, see LibInit().</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_SUCCESS "SUCCESS"</td>                <td>The function executed successfully.</td></tr>
 *   </table>
 * \since 0.6
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef bool8_t(*LibTiePieObjIsRemoved_t)( LibTiePieHandle_t hHandle );
#else
bool8_t ObjIsRemoved( LibTiePieHandle_t hHandle );
#endif

/**
 * \brief Check which interface are supported by the specified object.
 *
 * \param[in] hHandle A handle identifying the object.
 * \return Set of OR-ed, \ref INTERFACE_ "interface flags".
 * \par Status values
 *   <table class="params">
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_HANDLE "INVALID_HANDLE"</td>         <td>The handle to the device is invalid.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_LIBRARY_NOT_INITIALIZED "LIBRARY_NOT_INITIALIZED"</td><td>The library is not initialized, see LibInit().</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_SUCCESS "SUCCESS"</td>                <td>The function executed successfully.</td></tr>
 *   </table>
 * \since 0.6
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef uint64_t(*LibTiePieObjGetInterfaces_t)( LibTiePieHandle_t hHandle );
#else
uint64_t ObjGetInterfaces( LibTiePieHandle_t hHandle );
#endif

/**
 * \}
 * \defgroup obj_notifications Notifications
 * \{
 * \brief Notifications that indicate an object change.
 *
 * LibTiePie can notify the calling application that an object changed in different ways:
 * - by calling a callback function
 * - by setting a events
 * - by sending a message (Windows only)
 */

// Workaround: Without this line Doxygen adds the documentation below to the group above.

/**
 * \brief Set a callback function which is called when an event occurs.
 *
 * \param[in] hHandle A handle identifying the object.
 * \param[in] pCallback A pointer to the \ref TpCallbackEvent_t "callback" function. Use \c NULL to disable.
 * \param[in] pData Optional user data.
 * \since 0.6
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef void(*LibTiePieObjSetEventCallback_t)( LibTiePieHandle_t hHandle , TpCallbackEvent_t pCallback , void* pData );
#else
void ObjSetEventCallback( LibTiePieHandle_t hHandle , TpCallbackEvent_t pCallback , void* pData );
#endif

/**
 * \brief Get an event form the event queue.
 *
 * \param[in] hHandle A handle identifying the object.
 * \param[out] pEvent Pointer to store the event.
 * \param[out] pValue Pointer to store the event value or \c NULL.
 * \return #BOOL8_TRUE if an event is available, #BOOL8_FALSE otherwise.
 * \see ObjSetEventEvent
 * \since 0.6
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef bool8_t(*LibTiePieObjGetEvent_t)( LibTiePieHandle_t hHandle , uint32_t* pEvent , uint32_t* pValue );
#else
bool8_t ObjGetEvent( LibTiePieHandle_t hHandle , uint32_t* pEvent , uint32_t* pValue );
#endif

#ifdef LIBTIEPIE_LINUX

/**
 * \brief Set an event file descriptor which is set when an event occurs.
 *
 * \param[in] hHandle A handle identifying the object.
 * \param[in] fdEvent An event file descriptor. Use <tt><0</tt> to disable.
 * \see ObjGetEvent
 * \since 0.6
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef void(*LibTiePieObjSetEventEvent_t)( LibTiePieHandle_t hHandle , int fdEvent );
#else
void ObjSetEventEvent( LibTiePieHandle_t hHandle , int fdEvent );
#endif

#endif

#ifdef LIBTIEPIE_WINDOWS

/**
 * \brief Set an event object handle which is set when an event occurs.
 *
 * \param[in] hHandle A handle identifying the object.
 * \param[in] hEvent A handle to the event object. Use \c NULL to disable.
 * \see ObjGetEvent
 * \since 0.6
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef void(*LibTiePieObjSetEventEvent_t)( LibTiePieHandle_t hHandle , HANDLE hEvent );
#else
void ObjSetEventEvent( LibTiePieHandle_t hHandle , HANDLE hEvent );
#endif

/**
 * \brief Set a window handle to which a #WM_LIBTIEPIE_EVENT message is sent when an event occurs.
 *
 * The parameters of the message contain the following:
 * - \c wParam contains the \ref EVENTID_ "Event ID".
 * - \c lParam contains the event value (channel number when the Event ID is #LIBTIEPIE_EVENTID_SCP_SAFEGROUNDERROR, else \c 0).
 *
 *
 * \param[in] hHandle A handle identifying the object.
 * \param[in] hWnd A handle to the window whose window procedure is to receive the message. Use \c NULL to disable.
 * \since 0.6
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef void(*LibTiePieObjSetEventWindowHandle_t)( LibTiePieHandle_t hHandle , HWND hWnd );
#else
void ObjSetEventWindowHandle( LibTiePieHandle_t hHandle , HWND hWnd );
#endif

#endif

/**
 * \}
 * \}
 * \defgroup dev Device
 * \{
 * \brief Functions common to all devices, to setup and control devices.
 *
 *       These functions can be called with any device handles.
 */

// Workaround: Without this line Doxygen adds the documentation below to the group above.

/**
 * \deprecated Will be removed in future version, use: ObjClose().
 * \brief Close a device.
 *
 * When closing a device, its handle becomes invalid and must not be used again.
 *
 * \param[in] hDevice A \ref OpenDev "device handle" identifying the device to close.
 * \par Status values
 *   <table class="params">
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_HANDLE "INVALID_HANDLE"</td>         <td>The handle to the device is invalid.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_LIBRARY_NOT_INITIALIZED "LIBRARY_NOT_INITIALIZED"</td><td>The library is not initialized, see LibInit().</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_SUCCESS "SUCCESS"</td>                <td>The function executed successfully.</td></tr>
 *   </table>
 * \see LstOpenDevice
 * \see LstOpenOscilloscope
 * \see LstOpenGenerator
 * \see LstOpenI2CHost
 * \since 0.4.0
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef void(*LibTiePieDevClose_t)( LibTiePieHandle_t hDevice );
#else
void DevClose( LibTiePieHandle_t hDevice );
#endif

/**
 * \defgroup dev_status Status
 * \{
 * \brief Functions to check the status of a device.
 */

// Workaround: Without this line Doxygen adds the documentation below to the group above.

/**
 * \deprecated Will be removed in future version, use: ObjIsRemoved().
 * \brief Check whether a device is removed.
 *
 * \param[in] hDevice A \ref OpenDev "device handle" identifying the device.
 * \return #BOOL8_TRUE if removed, #BOOL8_FALSE otherwise.
 * \par Status values
 *   <table class="params">
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_HANDLE "INVALID_HANDLE"</td>         <td>The handle to the device is invalid.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_LIBRARY_NOT_INITIALIZED "LIBRARY_NOT_INITIALIZED"</td><td>The library is not initialized, see LibInit().</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_SUCCESS "SUCCESS"</td>                <td>The function executed successfully.</td></tr>
 *   </table>
 * \since 0.4.0
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef bool8_t(*LibTiePieDevIsRemoved_t)( LibTiePieHandle_t hDevice );
#else
bool8_t DevIsRemoved( LibTiePieHandle_t hDevice );
#endif

/**
 * \}
 * \defgroup dev_info Info
 * \{
 * \brief Functions to retrieve information from a device.
 */

// Workaround: Without this line Doxygen adds the documentation below to the group above.

/**
 * \brief Get the version number of the driver used by the device.
 *
 * \param[in] hDevice A \ref OpenDev "device handle" identifying the device.
 * \return Driver \ref TpVersion_t "version number", or zero if no version number is available.
 * \par Status values
 *   <table class="params">
 *   <tr><td>\ref LIBTIEPIESTATUS_NOT_SUPPORTED "NOT_SUPPORTED"</td>          <td>The indicated device does not support reading a driver version or does not require a driver.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_HANDLE "INVALID_HANDLE"</td>         <td>The handle to the device is invalid.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_OBJECT_GONE "OBJECT_GONE"</td>            <td>The object indicated by the handle is no longer available.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_LIBRARY_NOT_INITIALIZED "LIBRARY_NOT_INITIALIZED"</td><td>The library is not initialized, see LibInit().</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_SUCCESS "SUCCESS"</td>                <td>The function executed successfully.</td></tr>
 *   </table>
 * \par Example
 * \code{.c}
 * TpVersion_t Version = DevGetDriverVersion( hDevice );
 * uint16_t wMajor     = TPVERSION_MAJOR( Version );
 * uint16_t wMinor     = TPVERSION_MINOR( Version );
 * uint16_t wRelease   = TPVERSION_RELEASE( Version );
 * uint16_t wBuild     = TPVERSION_BUILD( Version );
 *
 * printf( "DevGetDriverVersion = %u.%u.%u.%u\n" , wMajor , wMinor , wRelease , wBuild );
 * \endcode
 *
 * \since 0.4.0
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef TpVersion_t(*LibTiePieDevGetDriverVersion_t)( LibTiePieHandle_t hDevice );
#else
TpVersion_t DevGetDriverVersion( LibTiePieHandle_t hDevice );
#endif

/**
 * \brief Get the version number of the firmware used by the device.
 *
 * \param[in] hDevice A \ref OpenDev "device handle" identifying the device.
 * \return Firmware \ref TpVersion_t "version number", or zero if no version number is available.
 * \par Status values
 *   <table class="params">
 *   <tr><td>\ref LIBTIEPIESTATUS_NOT_SUPPORTED "NOT_SUPPORTED"</td>          <td>The indicated device does not support reading a firmware version or does not require firmware.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_HANDLE "INVALID_HANDLE"</td>         <td>The handle to the device is invalid.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_OBJECT_GONE "OBJECT_GONE"</td>            <td>The object indicated by the handle is no longer available.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_LIBRARY_NOT_INITIALIZED "LIBRARY_NOT_INITIALIZED"</td><td>The library is not initialized, see LibInit().</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_SUCCESS "SUCCESS"</td>                <td>The function executed successfully.</td></tr>
 *   </table>
 * \par Example
 * \code{.c}
 * TpVersion_t Version = DevGetFirmwareVersion( hDevice );
 * uint16_t wMajor     = TPVERSION_MAJOR( Version );
 * uint16_t wMinor     = TPVERSION_MINOR( Version );
 * uint16_t wRelease   = TPVERSION_RELEASE( Version );
 * uint16_t wBuild     = TPVERSION_BUILD( Version );
 *
 * printf( "DevGetFirmwareVersion = %u.%u.%u.%u\n" , wMajor , wMinor , wRelease , wBuild );
 * \endcode
 *
 * \since 0.4.0
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef TpVersion_t(*LibTiePieDevGetFirmwareVersion_t)( LibTiePieHandle_t hDevice );
#else
TpVersion_t DevGetFirmwareVersion( LibTiePieHandle_t hDevice );
#endif

/**
 * \brief Get the calibration date of the device.
 *
 * \param[in] hDevice A \ref OpenDev "device handle" identifying the device.
 * \return The \ref TpDate_t "calibration date" of the device, or zero if no calibration date is available.
 * \par Status values
 *   <table class="params">
 *   <tr><td>\ref LIBTIEPIESTATUS_NOT_SUPPORTED "NOT_SUPPORTED"</td>          <td>The indicated device does not have a calibration date.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_HANDLE "INVALID_HANDLE"</td>         <td>The handle to the device is invalid.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_OBJECT_GONE "OBJECT_GONE"</td>            <td>The object indicated by the handle is no longer available.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_LIBRARY_NOT_INITIALIZED "LIBRARY_NOT_INITIALIZED"</td><td>The library is not initialized, see LibInit().</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_SUCCESS "SUCCESS"</td>                <td>The function executed successfully.</td></tr>
 *   </table>
 * \par Example
 * \code{.c}
 * TpDate_t Date    = DevGetCalibrationDate( hDevice );
 * uint16_t wYear   = TPDATE_YEAR( Date );
 * uint8_t  byMonth = TPDATE_MONTH( Date );
 * uint8_t  byDay   = TPDATE_DAY( Date );
 *
 * printf( "DevGetCalibrationDate = %u-%u-%u\n" , wYear , byMonth , byDay );
 * \endcode
 *
 * \since 0.4.0
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef TpDate_t(*LibTiePieDevGetCalibrationDate_t)( LibTiePieHandle_t hDevice );
#else
TpDate_t DevGetCalibrationDate( LibTiePieHandle_t hDevice );
#endif

//! \cond EXTENDED_API

/**
 * \brief Get the calibration token of the device.
 *
 * \param[in] hDevice A \ref OpenDev "device handle" identifying the device.
 * \param[out] pBuffer A pointer to a buffer for the token.
 * \param[in] dwBufferLength The length of the buffer, in bytes.
 * \return The length of the short name in bytes, excluding terminating zero.
 * \par Status values
 *   <table class="params">
 *   <tr><td>\ref LIBTIEPIESTATUS_NOT_SUPPORTED "NOT_SUPPORTED"</td>          <td>The indicated device does not have a calibration token.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_HANDLE "INVALID_HANDLE"</td>         <td>The handle to the device is invalid.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_OBJECT_GONE "OBJECT_GONE"</td>            <td>The object indicated by the handle is no longer available.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_LIBRARY_NOT_INITIALIZED "LIBRARY_NOT_INITIALIZED"</td><td>The library is not initialized, see LibInit().</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_SUCCESS "SUCCESS"</td>                <td>The function executed successfully.</td></tr>
 *   </table>
 * \par Example
 * \code{.c}
 * uint32_t dwLength = DevGetCalibrationToken( hDevice , NULL , 0 ) + 1; // Add one for the terminating zero
 * char* sCalibrationToken = malloc( sizeof( char ) * dwLength );
 * dwLength = DevGetCalibrationToken( hDevice , sCalibrationToken , dwLength );
 *
 * printf( "DevGetCalibrationToken = %s\n" , sCalibrationToken );
 *
 * free( sCalibrationToken );
 * \endcode
 *
 * \since 0.7.0
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef uint32_t(*LibTiePieDevGetCalibrationToken_t)( LibTiePieHandle_t hDevice , char* pBuffer , uint32_t dwBufferLength );
#else
uint32_t DevGetCalibrationToken( LibTiePieHandle_t hDevice , char* pBuffer , uint32_t dwBufferLength );
#endif

//! \endcond

/**
 * \brief Get the serial number of the device.
 *
 * \param[in] hDevice A \ref OpenDev "device handle" identifying the device.
 * \return The serial number of the device.
 * \par Status values
 *   <table class="params">
 *   <tr><td>\ref LIBTIEPIESTATUS_NOT_SUPPORTED "NOT_SUPPORTED"</td>          <td>The indicated device does not have a serial number.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_HANDLE "INVALID_HANDLE"</td>         <td>The handle to the device is invalid.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_OBJECT_GONE "OBJECT_GONE"</td>            <td>The object indicated by the handle is no longer available.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_LIBRARY_NOT_INITIALIZED "LIBRARY_NOT_INITIALIZED"</td><td>The library is not initialized, see LibInit().</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_SUCCESS "SUCCESS"</td>                <td>The function executed successfully.</td></tr>
 *   </table>
 * \since 0.4.0
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef uint32_t(*LibTiePieDevGetSerialNumber_t)( LibTiePieHandle_t hDevice );
#else
uint32_t DevGetSerialNumber( LibTiePieHandle_t hDevice );
#endif

/**
 * \brief Get the IPv4 address of the device.
 *
 * \param[in] hDevice A \ref OpenDev "device handle" identifying the device.
 * \return The IPv4 address of the device, or zero if no IPv4 address is available.
 * \par Status values
 *   <table class="params">
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_DEVICE_INDEX "INVALID_DEVICE_INDEX"</td>       <td>The device index is invalid, must be < LstGetCount().</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_DEVICE_SERIALNUMBER "INVALID_DEVICE_SERIALNUMBER"</td><td>There is no device with the requested serial number.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_PRODUCT_ID "INVALID_PRODUCT_ID"</td>         <td>There is no device with the requested product ID.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_NOT_SUPPORTED "NOT_SUPPORTED"</td>              <td>The indicated device is not a network device.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_VALUE "INVALID_VALUE"</td>              <td>The value of dwIdKind is invalid.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_LIBRARY_NOT_INITIALIZED "LIBRARY_NOT_INITIALIZED"</td>    <td>The library is not initialized, see LibInit().</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_SUCCESS "SUCCESS"</td>                    <td>The function executed successfully.</td></tr>
 *   </table>
 * \since 0.9
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef uint32_t(*LibTiePieDevGetIPv4Address_t)( LibTiePieHandle_t hDevice );
#else
uint32_t DevGetIPv4Address( LibTiePieHandle_t hDevice );
#endif

/**
 * \brief Get the IP port number of the device.
 *
 * \param[in] hDevice A \ref OpenDev "device handle" identifying the device.
 * \return The IP port number of the device, or zero if no IP port number is available.
 * \par Status values
 *   <table class="params">
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_DEVICE_INDEX "INVALID_DEVICE_INDEX"</td>       <td>The device index is invalid, must be < LstGetCount().</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_DEVICE_SERIALNUMBER "INVALID_DEVICE_SERIALNUMBER"</td><td>There is no device with the requested serial number.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_PRODUCT_ID "INVALID_PRODUCT_ID"</td>         <td>There is no device with the requested product ID.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_NOT_SUPPORTED "NOT_SUPPORTED"</td>              <td>The indicated device is not a network device.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_VALUE "INVALID_VALUE"</td>              <td>The value of dwIdKind is invalid.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_LIBRARY_NOT_INITIALIZED "LIBRARY_NOT_INITIALIZED"</td>    <td>The library is not initialized, see LibInit().</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_SUCCESS "SUCCESS"</td>                    <td>The function executed successfully.</td></tr>
 *   </table>
 * \since 0.9
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef uint16_t(*LibTiePieDevGetIPPort_t)( LibTiePieHandle_t hDevice );
#else
uint16_t DevGetIPPort( LibTiePieHandle_t hDevice );
#endif

/**
 * \brief Get the product id of the device.
 *
 * \param[in] hDevice A \ref OpenDev "device handle" identifying the device.
 * \return The \ref PID_ "product id" of the device.
 * \par Status values
 *   <table class="params">
 *   <tr><td>\ref LIBTIEPIESTATUS_NOT_SUPPORTED "NOT_SUPPORTED"</td>          <td>The indicated device does not support reading a product id.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_HANDLE "INVALID_HANDLE"</td>         <td>The handle to the device is invalid.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_OBJECT_GONE "OBJECT_GONE"</td>            <td>The object indicated by the handle is no longer available.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_LIBRARY_NOT_INITIALIZED "LIBRARY_NOT_INITIALIZED"</td><td>The library is not initialized, see LibInit().</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_SUCCESS "SUCCESS"</td>                <td>The function executed successfully.</td></tr>
 *   </table>
 * \since 0.4.0
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef uint32_t(*LibTiePieDevGetProductId_t)( LibTiePieHandle_t hDevice );
#else
uint32_t DevGetProductId( LibTiePieHandle_t hDevice );
#endif

//! \cond EXTENDED_API

/**
 * \brief Get the vendor id of the device.
 *
 * \param[in] hDevice A \ref OpenDev "device handle" identifying the device.
 * \return The vendor id of the device.
 * \par Status values
 *   <table class="params">
 *   <tr><td>\ref LIBTIEPIESTATUS_NOT_SUPPORTED "NOT_SUPPORTED"</td>          <td>The indicated device does not support reading a vendor id.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_HANDLE "INVALID_HANDLE"</td>         <td>The handle to the device is invalid.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_OBJECT_GONE "OBJECT_GONE"</td>            <td>The object indicated by the handle is no longer available.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_LIBRARY_NOT_INITIALIZED "LIBRARY_NOT_INITIALIZED"</td><td>The library is not initialized, see LibInit().</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_SUCCESS "SUCCESS"</td>                <td>The function executed successfully.</td></tr>
 *   </table>
 * \since 0.4.0
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef uint32_t(*LibTiePieDevGetVendorId_t)( LibTiePieHandle_t hDevice );
#else
uint32_t DevGetVendorId( LibTiePieHandle_t hDevice );
#endif

//! \endcond

/**
 * \brief Get the device type.
 *
 * \param[in] hDevice A \ref OpenDev "device handle" identifying the device.
 * \return The \ref DEVICETYPE_ "device type".
 * \par Status values
 *   <table class="params">
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_HANDLE "INVALID_HANDLE"</td>         <td>The handle to the device is invalid.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_OBJECT_GONE "OBJECT_GONE"</td>            <td>The object indicated by the handle is no longer available.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_UNSUCCESSFUL "UNSUCCESSFUL"</td>           <td>An error occurred during execution of the last called function.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_LIBRARY_NOT_INITIALIZED "LIBRARY_NOT_INITIALIZED"</td><td>The library is not initialized, see LibInit().</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_SUCCESS "SUCCESS"</td>                <td>The function executed successfully.</td></tr>
 *   </table>
 * \since 0.4.0
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef uint32_t(*LibTiePieDevGetType_t)( LibTiePieHandle_t hDevice );
#else
uint32_t DevGetType( LibTiePieHandle_t hDevice );
#endif

/**
 * \brief Get the full name of the device.
 *
 * E.g. <tt>Handyscope HS5-530XMS</tt>
 *
 * \param[in] hDevice A \ref OpenDev "device handle" identifying the device.
 * \param[out] pBuffer A pointer to a buffer for the name.
 * \param[in] dwBufferLength The length of the buffer, in bytes.
 * \return The length of the name in bytes, excluding terminating zero.
 * \par Status values
 *   <table class="params">
 *   <tr><td>\ref LIBTIEPIESTATUS_NOT_SUPPORTED "NOT_SUPPORTED"</td>          <td>The indicated device does not support reading a name.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_HANDLE "INVALID_HANDLE"</td>         <td>The handle to the device is invalid.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_OBJECT_GONE "OBJECT_GONE"</td>            <td>The object indicated by the handle is no longer available.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_LIBRARY_NOT_INITIALIZED "LIBRARY_NOT_INITIALIZED"</td><td>The library is not initialized, see LibInit().</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_SUCCESS "SUCCESS"</td>                <td>The function executed successfully.</td></tr>
 *   </table>
 * \see DevGetNameShort
 * \see DevGetNameShortest
 *
 * \par Example
 * \code{.c}
 * uint32_t dwLength = DevGetName( hDevice , NULL , 0 ) + 1; // Add one for the terminating zero
 * char* sName = malloc( sizeof( char ) * dwLength );
 * dwLength = DevGetName( hDevice , sName , dwLength );
 *
 * printf( "DevGetName = %s\n" , sName );
 *
 * free( sName );
 * \endcode
 *
 * \since 0.4.0
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef uint32_t(*LibTiePieDevGetName_t)( LibTiePieHandle_t hDevice , char* pBuffer , uint32_t dwBufferLength );
#else
uint32_t DevGetName( LibTiePieHandle_t hDevice , char* pBuffer , uint32_t dwBufferLength );
#endif

/**
 * \brief Get the short name of the device.
 *
 * E.g. <tt>HS5-530XMS</tt>
 *
 * \param[in] hDevice A \ref OpenDev "device handle" identifying the device.
 * \param[out] pBuffer A pointer to a buffer for the name.
 * \param[in] dwBufferLength The length of the buffer, in bytes.
 * \return The length of the short name in bytes, excluding terminating zero.
 * \par Status values
 *   <table class="params">
 *   <tr><td>\ref LIBTIEPIESTATUS_NOT_SUPPORTED "NOT_SUPPORTED"</td>          <td>The indicated device does not support reading a name.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_HANDLE "INVALID_HANDLE"</td>         <td>The handle to the device is invalid.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_OBJECT_GONE "OBJECT_GONE"</td>            <td>The object indicated by the handle is no longer available.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_LIBRARY_NOT_INITIALIZED "LIBRARY_NOT_INITIALIZED"</td><td>The library is not initialized, see LibInit().</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_SUCCESS "SUCCESS"</td>                <td>The function executed successfully.</td></tr>
 *   </table>
 * \see DevGetName
 * \see DevGetNameShortest
 *
 * \par Example
 * \code{.c}
 * uint32_t dwLength = DevGetNameShort( hDevice , NULL , 0 ) + 1; // Add one for the terminating zero
 * char* sNameShort = malloc( sizeof( char ) * dwLength );
 * dwLength = DevGetNameShort( hDevice , sNameShort , dwLength );
 *
 * printf( "DevGetNameShort = %s\n" , sNameShort );
 *
 * free( sNameShort );
 * \endcode
 *
 * \since 0.4.0
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef uint32_t(*LibTiePieDevGetNameShort_t)( LibTiePieHandle_t hDevice , char* pBuffer , uint32_t dwBufferLength );
#else
uint32_t DevGetNameShort( LibTiePieHandle_t hDevice , char* pBuffer , uint32_t dwBufferLength );
#endif

/**
 * \brief Get the short name of the device without model postfix.
 *
 * E.g. <tt>HS5</tt>
 *
 * \param[in] hDevice A \ref OpenDev "device handle" identifying the device.
 * \param[out] pBuffer A pointer to a buffer for the name.
 * \param[in] dwBufferLength The length of the buffer, in bytes.
 * \return The length of the short name in bytes, excluding terminating zero.
 * \par Status values
 *   <table class="params">
 *   <tr><td>\ref LIBTIEPIESTATUS_NOT_SUPPORTED "NOT_SUPPORTED"</td>          <td>The indicated device does not support reading a name.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_HANDLE "INVALID_HANDLE"</td>         <td>The handle to the device is invalid.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_OBJECT_GONE "OBJECT_GONE"</td>            <td>The object indicated by the handle is no longer available.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_LIBRARY_NOT_INITIALIZED "LIBRARY_NOT_INITIALIZED"</td><td>The library is not initialized, see LibInit().</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_SUCCESS "SUCCESS"</td>                <td>The function executed successfully.</td></tr>
 *   </table>
 * \see DevGetName
 * \see DevGetNameShort
 *
 * \par Example
 * \code{.c}
 * uint32_t dwLength = DevGetNameShortest( hDevice , NULL , 0 ) + 1; // Add one for the terminating zero
 * char* sNameShortest = malloc( sizeof( char ) * dwLength );
 * dwLength = DevGetNameShortest( hDevice , sNameShortest , dwLength );
 *
 * printf( "DevGetNameShortest = %s\n" , sNameShortest );
 *
 * free( sNameShortest );
 * \endcode
 *
 * \since 0.4.4
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef uint32_t(*LibTiePieDevGetNameShortest_t)( LibTiePieHandle_t hDevice , char* pBuffer , uint32_t dwBufferLength );
#else
uint32_t DevGetNameShortest( LibTiePieHandle_t hDevice , char* pBuffer , uint32_t dwBufferLength );
#endif

/**
 * \}
 * \defgroup dev_battery Battery
 * \{
 * \brief Device battery related functions
 */

// Workaround: Without this line Doxygen adds the documentation below to the group above.

/**
 * \brief Check whether the device has a battery.
 *
 * \param[in] hDevice A \ref OpenDev "device handle" identifying the device.
 * \return  #BOOL8_TRUE if the device has a battery, #BOOL8_FALSE otherwise.
 * \par Status values
 *   <table class="params">
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_HANDLE "INVALID_HANDLE"</td>         <td>The handle to the device is invalid.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_OBJECT_GONE "OBJECT_GONE"</td>            <td>The object indicated by the handle is no longer available.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_LIBRARY_NOT_INITIALIZED "LIBRARY_NOT_INITIALIZED"</td><td>The library is not initialized, see LibInit().</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_SUCCESS "SUCCESS"</td>                <td>The function executed successfully.</td></tr>
 *   </table>
 * \since 0.9
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef bool8_t(*LibTiePieDevHasBattery_t)(LibTiePieHandle_t hDevice);
#else
bool8_t DevHasBattery(LibTiePieHandle_t hDevice);
#endif

/**
 * \brief Get battery charge in percent.
 *
 * \param[in] hDevice A \ref OpenDev "device handle" identifying the device.
 * \return Battery charge in percent if succesful, \c -1 otherwise.
 * \par Status values
 *   <table class="params">
 *   <tr><td>\ref LIBTIEPIESTATUS_NOT_SUPPORTED "NOT_SUPPORTED"</td>          <td>The indicated device does not support reading the battery charge or doesn't have a battery.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_HANDLE "INVALID_HANDLE"</td>         <td>The handle to the device is invalid.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_OBJECT_GONE "OBJECT_GONE"</td>            <td>The object indicated by the handle is no longer available.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_LIBRARY_NOT_INITIALIZED "LIBRARY_NOT_INITIALIZED"</td><td>The library is not initialized, see LibInit().</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_SUCCESS "SUCCESS"</td>                <td>The function executed successfully.</td></tr>
 *   </table>
 * \see DevHasBattery
 * \since 0.9
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef int8_t(*LibTiePieDevGetBatteryCharge_t)(LibTiePieHandle_t hDevice);
#else
int8_t DevGetBatteryCharge(LibTiePieHandle_t hDevice);
#endif

/**
 * \brief Get battery time to empty in minutes.
 *
 * \param[in] hDevice A \ref OpenDev "device handle" identifying the device.
 * \return Battery time to empty in minutes if succesful, \c -1 otherwise.
 * \par Status values
 *   <table class="params">
 *   <tr><td>\ref LIBTIEPIESTATUS_NOT_SUPPORTED "NOT_SUPPORTED"</td>          <td>The indicated device does not support reading the battery time to empty or doesn't have a battery.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_HANDLE "INVALID_HANDLE"</td>         <td>The handle to the device is invalid.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_OBJECT_GONE "OBJECT_GONE"</td>            <td>The object indicated by the handle is no longer available.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_LIBRARY_NOT_INITIALIZED "LIBRARY_NOT_INITIALIZED"</td><td>The library is not initialized, see LibInit().</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_SUCCESS "SUCCESS"</td>                <td>The function executed successfully.</td></tr>
 *   </table>
 * \see DevHasBattery
 * \see DevGetBatteryCharge
 * \since 0.9
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef int32_t(*LibTiePieDevGetBatteryTimeToEmpty_t)(LibTiePieHandle_t hDevice);
#else
int32_t DevGetBatteryTimeToEmpty(LibTiePieHandle_t hDevice);
#endif

/**
 * \brief Get battery time to full in minutes.
 *
 * \param[in] hDevice A \ref OpenDev "device handle" identifying the device.
 * \return Battery time to full in minutes if succesful, \c -1 otherwise.
 * \par Status values
 *   <table class="params">
 *   <tr><td>\ref LIBTIEPIESTATUS_NOT_SUPPORTED "NOT_SUPPORTED"</td>          <td>The indicated device does not support reading the battery time to full or doesn't have a battery.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_HANDLE "INVALID_HANDLE"</td>         <td>The handle to the device is invalid.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_OBJECT_GONE "OBJECT_GONE"</td>            <td>The object indicated by the handle is no longer available.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_LIBRARY_NOT_INITIALIZED "LIBRARY_NOT_INITIALIZED"</td><td>The library is not initialized, see LibInit().</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_SUCCESS "SUCCESS"</td>                <td>The function executed successfully.</td></tr>
 *   </table>
 * \see DevHasBattery
 * \see DevIsBatteryCharging
 * \since 0.9
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef int32_t(*LibTiePieDevGetBatteryTimeToFull_t)(LibTiePieHandle_t hDevice);
#else
int32_t DevGetBatteryTimeToFull(LibTiePieHandle_t hDevice);
#endif

/**
 * \brief Check whether the battery charger is connected.
 *
 * \param[in] hDevice A \ref OpenDev "device handle" identifying the device.
 * \return #BOOL8_TRUE if the battery charger is connected, #BOOL8_FALSE otherwise.
 * \par Status values
 *   <table class="params">
 *   <tr><td>\ref LIBTIEPIESTATUS_NOT_SUPPORTED "NOT_SUPPORTED"</td>          <td>The indicated device does not have a battery.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_HANDLE "INVALID_HANDLE"</td>         <td>The handle to the device is invalid.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_OBJECT_GONE "OBJECT_GONE"</td>            <td>The object indicated by the handle is no longer available.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_LIBRARY_NOT_INITIALIZED "LIBRARY_NOT_INITIALIZED"</td><td>The library is not initialized, see LibInit().</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_SUCCESS "SUCCESS"</td>                <td>The function executed successfully.</td></tr>
 *   </table>
 * \see DevHasBattery
 * \see DevIsBatteryCharging
 * \since 0.9
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef bool8_t(*LibTiePieDevIsBatteryChargerConnected_t)(LibTiePieHandle_t hDevice);
#else
bool8_t DevIsBatteryChargerConnected(LibTiePieHandle_t hDevice);
#endif

/**
 * \brief Check whether the battery is charging.
 *
 * \param[in] hDevice A \ref OpenDev "device handle" identifying the device.
 * \return #BOOL8_TRUE if the battery is charging, #BOOL8_FALSE otherwise.
 * \par Status values
 *   <table class="params">
 *   <tr><td>\ref LIBTIEPIESTATUS_NOT_SUPPORTED "NOT_SUPPORTED"</td>          <td>The indicated device does not have a battery.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_HANDLE "INVALID_HANDLE"</td>         <td>The handle to the device is invalid.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_OBJECT_GONE "OBJECT_GONE"</td>            <td>The object indicated by the handle is no longer available.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_LIBRARY_NOT_INITIALIZED "LIBRARY_NOT_INITIALIZED"</td><td>The library is not initialized, see LibInit().</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_SUCCESS "SUCCESS"</td>                <td>The function executed successfully.</td></tr>
 *   </table>
 * \see DevHasBattery
 * \see DevGetBatteryTimeToEmpty
 * \see DevGetBatteryTimeToFull
 * \since 0.9
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef bool8_t(*LibTiePieDevIsBatteryCharging_t)(LibTiePieHandle_t hDevice);
#else
bool8_t DevIsBatteryCharging(LibTiePieHandle_t hDevice);
#endif

/**
 * \brief Check whether the battery is broken.
 *
 * \param[in] hDevice A \ref OpenDev "device handle" identifying the device.
 * \return #BOOL8_TRUE if the battery is broken, #BOOL8_FALSE otherwise.
 * \par Status values
 *   <table class="params">
 *   <tr><td>\ref LIBTIEPIESTATUS_NOT_SUPPORTED "NOT_SUPPORTED"</td>          <td>The indicated device does not have a battery.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_HANDLE "INVALID_HANDLE"</td>         <td>The handle to the device is invalid.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_OBJECT_GONE "OBJECT_GONE"</td>            <td>The object indicated by the handle is no longer available.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_LIBRARY_NOT_INITIALIZED "LIBRARY_NOT_INITIALIZED"</td><td>The library is not initialized, see LibInit().</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_SUCCESS "SUCCESS"</td>                <td>The function executed successfully.</td></tr>
 *   </table>
 * \see DevHasBattery
 * \since 0.9
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef bool8_t(*LibTiePieDevIsBatteryBroken_t)(LibTiePieHandle_t hDevice);
#else
bool8_t DevIsBatteryBroken(LibTiePieHandle_t hDevice);
#endif

/**
 * \}
 * \defgroup dev_notifications Notifications
 * \{
 *
 * \brief Notifications that indicate a device change.
 *
 * \defgroup dev_notifications_removed Removed
 * \{
 * \brief Notifications indicating a device is removed.
 *
 * LibTiePie can notify the calling application that a device is removed in different ways:
 * - by calling callback functions
 * - by setting events
 * - by sending messages (Windows only)
 */

// Workaround: Without this line Doxygen adds the documentation below to the group above.

/**
 * \deprecated Will be removed in future version, see: ObjSetEventCallback()
 * \brief Set a callback function which is called when the device is removed.
 *
 * \param[in] hDevice A \ref OpenDev "device handle" identifying the device.
 * \param[in] pCallback A pointer to the \ref TpCallback_t "callback" function. Use \c NULL to disable.
 * \param[in] pData Optional user data.
 * \par Status values
 *   <table class="params">
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_HANDLE "INVALID_HANDLE"</td>         <td>The handle to the device is invalid.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_OBJECT_GONE "OBJECT_GONE"</td>            <td>The object indicated by the handle is no longer available.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_LIBRARY_NOT_INITIALIZED "LIBRARY_NOT_INITIALIZED"</td><td>The library is not initialized, see LibInit().</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_SUCCESS "SUCCESS"</td>                <td>The function executed successfully.</td></tr>
 *   </table>
 * \since 0.4.0
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef void(*LibTiePieDevSetCallbackRemoved_t)( LibTiePieHandle_t hDevice , TpCallback_t pCallback , void* pData );
#else
void DevSetCallbackRemoved( LibTiePieHandle_t hDevice , TpCallback_t pCallback , void* pData );
#endif

#ifdef LIBTIEPIE_LINUX

/**
 * \deprecated Will be removed in future version, see: ObjSetEventEvent()
 * \brief Set an event file descriptor which is set when the device is removed.
 *
 * \param[in] hDevice A \ref OpenDev "device handle" identifying the device.
 * \param[in] fdEvent An event file descriptor. Use <tt><0</tt> to disable.
 * \par Status values
 *   <table class="params">
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_HANDLE "INVALID_HANDLE"</td>         <td>The handle to the device is invalid.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_OBJECT_GONE "OBJECT_GONE"</td>            <td>The object indicated by the handle is no longer available.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_LIBRARY_NOT_INITIALIZED "LIBRARY_NOT_INITIALIZED"</td><td>The library is not initialized, see LibInit().</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_SUCCESS "SUCCESS"</td>                <td>The function executed successfully.</td></tr>
 *   </table>
 * \note This function is only available on GNU/Linux.
 * \since 0.4.0
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef void(*LibTiePieDevSetEventRemoved_t)( LibTiePieHandle_t hDevice , int fdEvent );
#else
void DevSetEventRemoved( LibTiePieHandle_t hDevice , int fdEvent );
#endif

#endif

#ifdef LIBTIEPIE_WINDOWS

/**
 * \deprecated Will be removed in future version, see: ObjSetEventEvent()
 * \brief Set an event object handle which is set when the device is removed.
 *
 * \param[in] hDevice A \ref OpenDev "device handle" identifying the device.
 * \param[in] hEvent A handle to the event object. Use \c NULL to disable.
 * \par Status values
 *   <table class="params">
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_HANDLE "INVALID_HANDLE"</td>         <td>The handle to the device is invalid.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_OBJECT_GONE "OBJECT_GONE"</td>            <td>The object indicated by the handle is no longer available.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_LIBRARY_NOT_INITIALIZED "LIBRARY_NOT_INITIALIZED"</td><td>The library is not initialized, see LibInit().</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_SUCCESS "SUCCESS"</td>                <td>The function executed successfully.</td></tr>
 *   </table>
 * \note This function is only available on Windows.
 * \since 0.4.0
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef void(*LibTiePieDevSetEventRemoved_t)( LibTiePieHandle_t hDevice , HANDLE hEvent );
#else
void DevSetEventRemoved( LibTiePieHandle_t hDevice , HANDLE hEvent );
#endif

/**
 * \deprecated Will be removed in future version, see: ObjSetEventWindowHandle()
 * \brief Set a window handle to which a #WM_LIBTIEPIE_DEV_REMOVED message is sent when the device is removed.
 *
 * \param[in] hDevice A \ref OpenDev "device handle" identifying the device.
 * \param[in] hWnd A handle to the window whose window procedure is to receive the message. Use \c NULL to disable.
 * \param[in] wParam Optional user value for the \c wParam parameter of the message.
 * \param[in] lParam Optional user value for the \c lParam parameter of the message.
 * \par Status values
 *   <table class="params">
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_HANDLE "INVALID_HANDLE"</td>         <td>The handle to the device is invalid.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_OBJECT_GONE "OBJECT_GONE"</td>            <td>The object indicated by the handle is no longer available.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_LIBRARY_NOT_INITIALIZED "LIBRARY_NOT_INITIALIZED"</td><td>The library is not initialized, see LibInit().</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_SUCCESS "SUCCESS"</td>                <td>The function executed successfully.</td></tr>
 *   </table>
 * \note This function is only available on Windows.
 * \since 0.4.0
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef void(*LibTiePieDevSetMessageRemoved_t)( LibTiePieHandle_t hDevice , HWND hWnd , WPARAM wParam , LPARAM lParam );
#else
void DevSetMessageRemoved( LibTiePieHandle_t hDevice , HWND hWnd , WPARAM wParam , LPARAM lParam );
#endif

#endif

/**
 * \}
 * \}
 * \defgroup dev_trigger Trigger
 * \{
 * \brief Device trigger related functions.
 *
 * \defgroup dev_trigger_input Input(s)
 * \{
 * \brief A device can have one or more device trigger inputs, usually available as pins on an extension connector on the instrument.
 *
 *           Use the function DevTrGetInputCount() to determine the amount of available device trigger inputs.
 *           To use a device trigger input as trigger source, use the function DevTrInSetEnabled() to enable it.
 */

// Workaround: Without this line Doxygen adds the documentation below to the group above.

/**
 * \brief Get the number of trigger inputs.
 *
 * \param[in] hDevice A \ref OpenDev "device handle" identifying the device.
 * \return The number of trigger inputs.
 * \par Status values
 *   <table class="params">
 *   <tr><td>\ref LIBTIEPIESTATUS_NOT_SUPPORTED "NOT_SUPPORTED"</td>          <td>The device has no trigger inputs.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_HANDLE "INVALID_HANDLE"</td>         <td>The handle to the device is invalid.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_OBJECT_GONE "OBJECT_GONE"</td>            <td>The object indicated by the handle is no longer available.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_LIBRARY_NOT_INITIALIZED "LIBRARY_NOT_INITIALIZED"</td><td>The library is not initialized, see LibInit().</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_SUCCESS "SUCCESS"</td>                <td>The function executed successfully.</td></tr>
 *   </table>
 * \since 0.4.1
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef uint16_t(*LibTiePieDevTrGetInputCount_t)( LibTiePieHandle_t hDevice );
#else
uint16_t DevTrGetInputCount( LibTiePieHandle_t hDevice );
#endif

/**
 * \brief Get the index of a trigger input identified by its ID.
 *
 * The index is used in the other trigger input functions to identify the trigger input.
 *
 * \param[in] hDevice A \ref OpenDev "device handle" identifying the device.
 * \param[in] dwId The trigger input ID, a \ref TIID_ "TIID_*" value, identifying the trigger input.
 * \return The trigger input index or #LIBTIEPIE_TRIGGERIO_INDEX_INVALID.
 * \par Status values
 *   <table class="params">
 *   <tr><td>\ref LIBTIEPIESTATUS_NOT_SUPPORTED "NOT_SUPPORTED"</td>          <td>The device has no trigger inputs.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_VALUE "INVALID_VALUE"</td>          <td>The requested ID is invalid.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_HANDLE "INVALID_HANDLE"</td>         <td>The handle to the device is invalid.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_OBJECT_GONE "OBJECT_GONE"</td>            <td>The object indicated by the handle is no longer available.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_LIBRARY_NOT_INITIALIZED "LIBRARY_NOT_INITIALIZED"</td><td>The library is not initialized, see LibInit().</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_SUCCESS "SUCCESS"</td>                <td>The function executed successfully.</td></tr>
 *   </table>
 * \see DevTrInGetId()
 * \since 0.4.4
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef uint16_t(*LibTiePieDevTrGetInputIndexById_t)( LibTiePieHandle_t hDevice , uint32_t dwId );
#else
uint16_t DevTrGetInputIndexById( LibTiePieHandle_t hDevice , uint32_t dwId );
#endif

/**
 * \defgroup dev_trigger_input_status Status
 * \{
 */

// Workaround: Without this line Doxygen adds the documentation below to the group above.

/**
 * \brief Check whether the trigger input caused a trigger.
 *
 * \param[in] hDevice A \ref OpenDev "device handle" identifying the oscilloscope.
 * \param[in] wInput The trigger input index identifying the trigger input, \c 0 to <tt>DevTrInGetCount() - 1</tt>.
 * \return #BOOL8_TRUE if the trigger input caused a trigger, #BOOL8_FALSE otherwise.
 * \see ScpIsTriggered
 * \see ScpIsTimeOutTriggered
 * \see ScpIsForceTriggered
 * \see ScpChTrIsTriggered
 * \since 0.5
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef bool8_t(*LibTiePieScpTrInIsTriggered_t)( LibTiePieHandle_t hDevice , uint16_t wInput );
#else
bool8_t ScpTrInIsTriggered( LibTiePieHandle_t hDevice , uint16_t wInput );
#endif

/**
 * \}
 * \defgroup dev_trigger_input_enabled Enabled
 * \{
 * \brief The enabled state of a device trigger input determines whether an input is selected as trigger source.
 *
 *             By default, all device trigger inputs are disabled (#BOOL8_FALSE).
 */

// Workaround: Without this line Doxygen adds the documentation below to the group above.

/**
 * \brief Check whether a device trigger input is enabled.
 *
 * \param[in] hDevice A \ref OpenDev "device handle" identifying the device.
 * \param[in] wInput The trigger input index identifying the trigger input, \c 0 to <tt>DevTrInGetCount() - 1</tt>.
 * \return #BOOL8_TRUE if enabled, #BOOL8_FALSE otherwise.
 * \par Status values
 *   <table class="params">
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_INPUT "INVALID_INPUT"</td>          <td>The requested trigger input is invalid.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_NOT_AVAILABLE "NOT_AVAILABLE"</td>          <td>With the current settings, the trigger input is not available.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_NOT_SUPPORTED "NOT_SUPPORTED"</td>          <td>The device has no trigger inputs.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_HANDLE "INVALID_HANDLE"</td>         <td>The handle to the device is invalid.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_OBJECT_GONE "OBJECT_GONE"</td>            <td>The object indicated by the handle is no longer available.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_LIBRARY_NOT_INITIALIZED "LIBRARY_NOT_INITIALIZED"</td><td>The library is not initialized, see LibInit().</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_SUCCESS "SUCCESS"</td>                <td>The function executed successfully.</td></tr>
 *   </table>
 * \see DevTrInSetEnabled
 * \since 0.4.1
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef bool8_t(*LibTiePieDevTrInGetEnabled_t)( LibTiePieHandle_t hDevice , uint16_t wInput );
#else
bool8_t DevTrInGetEnabled( LibTiePieHandle_t hDevice , uint16_t wInput );
#endif

/**
 * \brief To select a device trigger input as trigger source, set trigger input enabled.
 *
 * \param[in] hDevice A \ref OpenDev "device handle" identifying the device.
 * \param[in] wInput The trigger input index identifying the trigger input, \c 0 to <tt>DevTrInGetCount() - 1</tt>.
 * \param[in] bEnable #BOOL8_TRUE or #BOOL8_FALSE.
 * \return #BOOL8_TRUE if enabled, #BOOL8_FALSE otherwise.
 * \par Status values
 *   <table class="params">
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_INPUT "INVALID_INPUT"</td>          <td>The requested trigger input is invalid.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_NOT_AVAILABLE "NOT_AVAILABLE"</td>          <td>With the current settings, the trigger input is not available.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_NOT_SUPPORTED "NOT_SUPPORTED"</td>          <td>The device has no trigger inputs.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_HANDLE "INVALID_HANDLE"</td>         <td>The handle to the device is invalid.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_OBJECT_GONE "OBJECT_GONE"</td>            <td>The object indicated by the handle is no longer available.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_LIBRARY_NOT_INITIALIZED "LIBRARY_NOT_INITIALIZED"</td><td>The library is not initialized, see LibInit().</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_SUCCESS "SUCCESS"</td>                <td>The function executed successfully.</td></tr>
 *   </table>
 * \see DevTrInGetEnabled
 * \since 0.4.1
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef bool8_t(*LibTiePieDevTrInSetEnabled_t)( LibTiePieHandle_t hDevice , uint16_t wInput , bool8_t bEnable );
#else
bool8_t DevTrInSetEnabled( LibTiePieHandle_t hDevice , uint16_t wInput , bool8_t bEnable );
#endif

/**
 * \}
 * \defgroup dev_trigger_input_kind Kind
 * \{
 * \brief The device trigger kind determines how the device trigger responds to the device trigger input signal.
 *
 *             Use DevTrInGetKinds() to find out which trigger kinds are supported by the device trigger input.
 *             Read more on \ref triggering_devin_kind "device trigger kind".
 *
 *             Default value: #TK_RISINGEDGE if supported, else #TK_FALLINGEDGE.
 */

// Workaround: Without this line Doxygen adds the documentation below to the group above.

/**
 * \brief Get the supported trigger kinds for a specified device trigger input.
 *
 * \param[in] hDevice A \ref OpenDev "device handle" identifying the device.
 * \param[in] wInput The trigger input index identifying the trigger input, \c 0 to <tt>DevTrInGetCount() - 1</tt>.
 * \return Supported trigger input kinds, a set of OR-ed \ref TK_ "TK_*" values.
 * \par Status values
 *   <table class="params">
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_INPUT "INVALID_INPUT"</td>          <td>The requested trigger input is invalid.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_NOT_AVAILABLE "NOT_AVAILABLE"</td>          <td>With the current settings, the trigger input is not available.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_NOT_SUPPORTED "NOT_SUPPORTED"</td>          <td>The device has no trigger inputs.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_HANDLE "INVALID_HANDLE"</td>         <td>The handle to the device is invalid.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_OBJECT_GONE "OBJECT_GONE"</td>            <td>The object indicated by the handle is no longer available.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_LIBRARY_NOT_INITIALIZED "LIBRARY_NOT_INITIALIZED"</td><td>The library is not initialized, see LibInit().</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_SUCCESS "SUCCESS"</td>                <td>The function executed successfully.</td></tr>
 *   </table>
 * \see DevTrInGetKind
 * \see DevTrInSetKind
 * \since 0.4.1
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef uint64_t(*LibTiePieDevTrInGetKinds_t)( LibTiePieHandle_t hDevice , uint16_t wInput );
#else
uint64_t DevTrInGetKinds( LibTiePieHandle_t hDevice , uint16_t wInput );
#endif

//! \cond EXTENDED_API

/**
 * \brief Get the supported trigger kinds for a specified oscilloscope trigger input and measure mode.
 *
 * \param[in] hDevice A \ref OpenDev "device handle" identifying the device.
 * \param[in] wInput The trigger input index identifying the trigger input, \c 0 to <tt>DevTrInGetCount() - 1</tt>.
 * \param[in] dwMeasureMode Measure mode, a \ref MM_ "MM_*" value.
 * \return Supported trigger input kinds, a set of OR-ed \ref TK_ "TK_*" values.
 * \par Status values
 *   <table class="params">
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_INPUT "INVALID_INPUT"</td>          <td>The requested trigger input is invalid.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_NOT_AVAILABLE "NOT_AVAILABLE"</td>          <td>With the current settings, the trigger input is not available.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_VALUE "INVALID_VALUE"</td>          <td>The requested measure mode is invalid.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_NOT_SUPPORTED "NOT_SUPPORTED"</td>          <td>The device has no trigger inputs.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_HANDLE "INVALID_HANDLE"</td>         <td>The handle to the device is invalid.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_OBJECT_GONE "OBJECT_GONE"</td>            <td>The object indicated by the handle is no longer available.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_LIBRARY_NOT_INITIALIZED "LIBRARY_NOT_INITIALIZED"</td><td>The library is not initialized, see LibInit().</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_SUCCESS "SUCCESS"</td>                <td>The function executed successfully.</td></tr>
 *   </table>
 * \see DevTrInGetKind
 * \see DevTrInSetKind
 * \since 0.4.4
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef uint64_t(*LibTiePieScpTrInGetKindsEx_t)( LibTiePieHandle_t hDevice , uint16_t wInput , uint32_t dwMeasureMode );
#else
uint64_t ScpTrInGetKindsEx( LibTiePieHandle_t hDevice , uint16_t wInput , uint32_t dwMeasureMode );
#endif

//! \endcond

/**
 * \brief Get the currently selected trigger kind for a specified device trigger input.
 *
 * \param[in] hDevice A \ref OpenDev "device handle" identifying the device.
 * \param[in] wInput The trigger input index identifying the trigger input, \c 0 to <tt>DevTrInGetCount() - 1</tt>.
 * \return The current trigger kind, a \ref TK_ "TK_*" value.
 * \par Status values
 *   <table class="params">
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_INPUT "INVALID_INPUT"</td>          <td>The requested trigger input is invalid.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_NOT_AVAILABLE "NOT_AVAILABLE"</td>          <td>With the current settings, the trigger input is not available.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_NOT_SUPPORTED "NOT_SUPPORTED"</td>          <td>The device has no trigger inputs.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_HANDLE "INVALID_HANDLE"</td>         <td>The handle to the device is invalid.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_OBJECT_GONE "OBJECT_GONE"</td>            <td>The object indicated by the handle is no longer available.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_LIBRARY_NOT_INITIALIZED "LIBRARY_NOT_INITIALIZED"</td><td>The library is not initialized, see LibInit().</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_SUCCESS "SUCCESS"</td>                <td>The function executed successfully.</td></tr>
 *   </table>
 * \see DevTrInGetKinds
 * \see DevTrInSetKind
 * \since 0.4.1
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef uint64_t(*LibTiePieDevTrInGetKind_t)( LibTiePieHandle_t hDevice , uint16_t wInput );
#else
uint64_t DevTrInGetKind( LibTiePieHandle_t hDevice , uint16_t wInput );
#endif

/**
 * \brief Set the required trigger kind for a specified device trigger input.
 *
 * \param[in] hDevice A \ref OpenDev "device handle" identifying the device.
 * \param[in] wInput The trigger input index identifying the trigger input, \c 0 to <tt>DevTrInGetCount() - 1</tt>.
 * \param[in] qwKind The required trigger kind, a \ref TK_ "TK_*" value.
 * \return The actually set trigger kind, a \ref TK_ "TK_*" value.
 * \par Status values
 *   <table class="params">
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_INPUT "INVALID_INPUT"</td>          <td>The requested trigger input is invalid.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_NOT_AVAILABLE "NOT_AVAILABLE"</td>          <td>With the current settings, the trigger input is not available.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_VALUE "INVALID_VALUE"</td>          <td>The requested trigger kind is invalid.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_NOT_SUPPORTED "NOT_SUPPORTED"</td>          <td>The device has no trigger inputs.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_HANDLE "INVALID_HANDLE"</td>         <td>The handle to the device is invalid.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_OBJECT_GONE "OBJECT_GONE"</td>            <td>The object indicated by the handle is no longer available.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_LIBRARY_NOT_INITIALIZED "LIBRARY_NOT_INITIALIZED"</td><td>The library is not initialized, see LibInit().</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_SUCCESS "SUCCESS"</td>                <td>The function executed successfully.</td></tr>
 *   </table>
 * \see DevTrInGetKinds
 * \see DevTrInGetKind
 * \since 0.4.1
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef uint64_t(*LibTiePieDevTrInSetKind_t)( LibTiePieHandle_t hDevice , uint16_t wInput , uint64_t qwKind );
#else
uint64_t DevTrInSetKind( LibTiePieHandle_t hDevice , uint16_t wInput , uint64_t qwKind );
#endif

/**
 * \}
 * \defgroup dev_trigger_input_info Info
 * \{
 * \brief Obtain information of a device trigger input.
 *
 *             The following information of a device trigger input is available:
 *             - \ref DevTrInIsAvailable "Availability"
 *             - \ref DevTrInGetId "ID"
 *             - \ref DevTrInGetName "Name"
 */

// Workaround: Without this line Doxygen adds the documentation below to the group above.

/**
 * \brief Check whether a device trigger input is available.
 *
 * Depending on other settings of a device, a device trigger input may be not available.
 * E.g. when the \ref scp_measurements_mode "measure mode" of an oscilloscope is set to \ref MM_STREAM "streaming",
 * device trigger inputs are not available.
 *
 * \param[in] hDevice A \ref OpenDev "device handle" identifying the device.
 * \param[in] wInput The trigger input index identifying the trigger input, \c 0 to <tt>DevTrInGetCount() - 1</tt>.
 * \return #BOOL8_TRUE if available, #BOOL8_FALSE otherwise.
 * \par Status values
 *   <table class="params">
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_INPUT "INVALID_INPUT"</td>          <td>The requested trigger input is invalid.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_NOT_SUPPORTED "NOT_SUPPORTED"</td>          <td>The device has no trigger inputs.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_HANDLE "INVALID_HANDLE"</td>         <td>The handle to the device is invalid.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_OBJECT_GONE "OBJECT_GONE"</td>            <td>The object indicated by the handle is no longer available.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_LIBRARY_NOT_INITIALIZED "LIBRARY_NOT_INITIALIZED"</td><td>The library is not initialized, see LibInit().</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_SUCCESS "SUCCESS"</td>                <td>The function executed successfully.</td></tr>
 *   </table>
 * \since 0.4.4
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef bool8_t(*LibTiePieDevTrInIsAvailable_t)( LibTiePieHandle_t hDevice , uint16_t wInput );
#else
bool8_t DevTrInIsAvailable( LibTiePieHandle_t hDevice , uint16_t wInput );
#endif

//! \cond EXTENDED_API

/**
 * \brief Check whether a device trigger input is available, for a specific \ref scp_measurements_mode "measure mode".
 *
 * \param[in] hDevice A \ref OpenDev "device handle" identifying the device.
 * \param[in] wInput The trigger input index identifying the trigger input, \c 0 to <tt>DevTrInGetCount() - 1</tt>.
 * \param[in] dwMeasureMode Measure mode, a \ref MM_ "MM_*" value.
 * \return #BOOL8_TRUE if available, #BOOL8_FALSE otherwise.
 * \since 0.4.4
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef bool8_t(*LibTiePieScpTrInIsAvailableEx_t)( LibTiePieHandle_t hDevice , uint16_t wInput , uint32_t dwMeasureMode );
#else
bool8_t ScpTrInIsAvailableEx( LibTiePieHandle_t hDevice , uint16_t wInput , uint32_t dwMeasureMode );
#endif

//! \endcond

/**
 * \brief Get the id of a specified device trigger input.
 *
 * \param[in] hDevice A \ref OpenDev "device handle" identifying the device.
 * \param[in] wInput The trigger input index identifying the trigger input, \c 0 to <tt>DevTrInGetCount() - 1</tt>.
 * \return The trigger input id, a \ref TIID_ "TIID_*" value.
 * \par Status values
 *   <table class="params">
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_INPUT "INVALID_INPUT"</td>          <td>The requested trigger input is invalid.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_NOT_SUPPORTED "NOT_SUPPORTED"</td>          <td>The device has no trigger inputs.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_HANDLE "INVALID_HANDLE"</td>         <td>The handle to the device is invalid.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_OBJECT_GONE "OBJECT_GONE"</td>            <td>The object indicated by the handle is no longer available.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_LIBRARY_NOT_INITIALIZED "LIBRARY_NOT_INITIALIZED"</td><td>The library is not initialized, see LibInit().</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_SUCCESS "SUCCESS"</td>                <td>The function executed successfully.</td></tr>
 *   </table>
 * \see DevTrGetInputIndexById()
 * \since 0.4.4
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef uint32_t(*LibTiePieDevTrInGetId_t)( LibTiePieHandle_t hDevice , uint16_t wInput );
#else
uint32_t DevTrInGetId( LibTiePieHandle_t hDevice , uint16_t wInput );
#endif

/**
 * \brief Get the name of a specified device trigger input.
 *
 * \param[in] hDevice A \ref OpenDev "device handle" identifying the device.
 * \param[in] wInput The trigger input index identifying the trigger input, \c 0 to <tt>DevTrInGetCount() - 1</tt>.
 * \param[out] pBuffer A pointer to a buffer for the name.
 * \param[in] dwBufferLength The length of the buffer, in bytes.
 * \return The length of the name in bytes, excluding terminating zero.
 * \par Status values
 *   <table class="params">
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_INPUT "INVALID_INPUT"</td>          <td>The requested trigger input is invalid.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_NOT_SUPPORTED "NOT_SUPPORTED"</td>          <td>The device has no trigger inputs.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_HANDLE "INVALID_HANDLE"</td>         <td>The handle to the device is invalid.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_OBJECT_GONE "OBJECT_GONE"</td>            <td>The object indicated by the handle is no longer available.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_LIBRARY_NOT_INITIALIZED "LIBRARY_NOT_INITIALIZED"</td><td>The library is not initialized, see LibInit().</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_SUCCESS "SUCCESS"</td>                <td>The function executed successfully.</td></tr>
 *   </table>
 * \since 0.4.1
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef uint32_t(*LibTiePieDevTrInGetName_t)( LibTiePieHandle_t hDevice , uint16_t wInput , char* pBuffer , uint32_t dwBufferLength );
#else
uint32_t DevTrInGetName( LibTiePieHandle_t hDevice , uint16_t wInput , char* pBuffer , uint32_t dwBufferLength );
#endif

/**
 * \}
 * \}
 * \defgroup dev_trigger_output Output(s)
 * \{
 * \brief  A device can have one or more device trigger outputs, usually available as pins on an extension connector on the instrument.
 *
 *           The trigger outputs are controlled by events that occur in the instrument.
 *
 *           Use the function DevTrGetOutputCount() to determine the amount of available device trigger outputs.
 *           To use a device trigger output, use the function DevTrOutSetEnabled() to enable it.
 */

// Workaround: Without this line Doxygen adds the documentation below to the group above.

/**
 * \brief Get the number of trigger outputs.
 *
 * \param[in] hDevice A \ref OpenDev "device handle" identifying the device.
 * \return The number of trigger outputs.
 * \par Status values
 *   <table class="params">
 *   <tr><td>\ref LIBTIEPIESTATUS_NOT_SUPPORTED "NOT_SUPPORTED"</td>          <td>The device has no trigger outputs.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_HANDLE "INVALID_HANDLE"</td>         <td>The handle to the device is invalid.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_OBJECT_GONE "OBJECT_GONE"</td>            <td>The object indicated by the handle is no longer available.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_LIBRARY_NOT_INITIALIZED "LIBRARY_NOT_INITIALIZED"</td><td>The library is not initialized, see LibInit().</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_SUCCESS "SUCCESS"</td>                <td>The function executed successfully.</td></tr>
 *   </table>
 * \since 0.4.1
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef uint16_t(*LibTiePieDevTrGetOutputCount_t)( LibTiePieHandle_t hDevice );
#else
uint16_t DevTrGetOutputCount( LibTiePieHandle_t hDevice );
#endif

/**
 * \brief Get the index of trigger output identified by its ID.
 *
 * \param[in] hDevice A \ref OpenDev "device handle" identifying the device.
 * \param[in] dwId The trigger output ID, a \ref TOID_ "TOID_*" value, identifying the trigger output.
 * \return The trigger output index or #LIBTIEPIE_TRIGGERIO_INDEX_INVALID.
 * \par Status values
 *   <table class="params">
 *   <tr><td>\ref LIBTIEPIESTATUS_NOT_SUPPORTED "NOT_SUPPORTED"</td>          <td>The device has no trigger outputs.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_VALUE "INVALID_VALUE"</td>          <td>The requested ID is invalid.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_HANDLE "INVALID_HANDLE"</td>         <td>The handle to the device is invalid.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_OBJECT_GONE "OBJECT_GONE"</td>            <td>The object indicated by the handle is no longer available.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_LIBRARY_NOT_INITIALIZED "LIBRARY_NOT_INITIALIZED"</td><td>The library is not initialized, see LibInit().</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_SUCCESS "SUCCESS"</td>                <td>The function executed successfully.</td></tr>
 *   </table>
 * \see DevTrOutGetId()
 * \since 0.4.4
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef uint16_t(*LibTiePieDevTrGetOutputIndexById_t)( LibTiePieHandle_t hDevice , uint32_t dwId );
#else
uint16_t DevTrGetOutputIndexById( LibTiePieHandle_t hDevice , uint32_t dwId );
#endif

/**
 * \defgroup dev_trigger_output_enabled Enabled
 * \{
 * \brief The enabled state of a device trigger output determines whether an output is used.
 *
 *             By default, all trigger outputs are disabled (#BOOL8_FALSE).
 */

// Workaround: Without this line Doxygen adds the documentation below to the group above.

/**
 * \brief Check whether a trigger output is enabled.
 *
 * \param[in] hDevice A \ref OpenDev "device handle" identifying the device.
 * \param[in] wOutput The trigger output index identifying the trigger output, \c 0 to <tt>DevTrOutGetCount() - 1</tt>.
 * \return #BOOL8_TRUE if enabled, #BOOL8_FALSE otherwise.
 * \par Status values
 *   <table class="params">
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_OUTPUT "INVALID_OUTPUT"</td>         <td>The requested trigger output is invalid.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_NOT_SUPPORTED "NOT_SUPPORTED"</td>          <td>The device has no trigger outputs.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_HANDLE "INVALID_HANDLE"</td>         <td>The handle to the device is invalid.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_OBJECT_GONE "OBJECT_GONE"</td>            <td>The object indicated by the handle is no longer available.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_LIBRARY_NOT_INITIALIZED "LIBRARY_NOT_INITIALIZED"</td><td>The library is not initialized, see LibInit().</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_SUCCESS "SUCCESS"</td>                <td>The function executed successfully.</td></tr>
 *   </table>
 * \see DevTrOutSetEnabled
 * \since 0.4.1
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef bool8_t(*LibTiePieDevTrOutGetEnabled_t)( LibTiePieHandle_t hDevice , uint16_t wOutput );
#else
bool8_t DevTrOutGetEnabled( LibTiePieHandle_t hDevice , uint16_t wOutput );
#endif

/**
 * \brief Set trigger output enable.
 *
 * \param[in] hDevice A \ref OpenDev "device handle" identifying the device.
 * \param[in] wOutput The trigger output index identifying the trigger output, \c 0 to <tt>DevTrOutGetCount() - 1</tt>.
 * \param[in] bEnable #BOOL8_TRUE or #BOOL8_FALSE.
 * \return #BOOL8_TRUE if enabled, #BOOL8_FALSE otherwise.
 * \par Status values
 *   <table class="params">
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_OUTPUT "INVALID_OUTPUT"</td>         <td>The requested trigger output is invalid.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_NOT_SUPPORTED "NOT_SUPPORTED"</td>          <td>The device has no trigger outputs.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_HANDLE "INVALID_HANDLE"</td>         <td>The handle to the device is invalid.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_OBJECT_GONE "OBJECT_GONE"</td>            <td>The object indicated by the handle is no longer available.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_LIBRARY_NOT_INITIALIZED "LIBRARY_NOT_INITIALIZED"</td><td>The library is not initialized, see LibInit().</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_SUCCESS "SUCCESS"</td>                <td>The function executed successfully.</td></tr>
 *   </table>
 * \see DevTrOutGetEnabled
 * \since 0.4.1
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef bool8_t(*LibTiePieDevTrOutSetEnabled_t)( LibTiePieHandle_t hDevice , uint16_t wOutput , bool8_t bEnable );
#else
bool8_t DevTrOutSetEnabled( LibTiePieHandle_t hDevice , uint16_t wOutput , bool8_t bEnable );
#endif

/**
 * \}
 * \defgroup dev_trigger_output_event Event
 * \{
 * \brief Select the event that controls the trigger output.
 *
 *             Supported events are:
 *             - \ref TOE_GENERATOR_START "Generator start"
 *             - \ref TOE_GENERATOR_STOP "Generator stop"
 *             - \ref TOE_GENERATOR_NEWPERIOD "Generator new period"
 *
 *             Only one event at a time can be set for a trigger output.
 *
 *             By default, the event is set to #TOE_GENERATOR_START.
 */

// Workaround: Without this line Doxygen adds the documentation below to the group above.

/**
 * \brief Get the supported trigger output events for a specified device trigger output.
 *
 * \param[in] hDevice A \ref OpenDev "device handle" identifying the device.
 * \param[in] wOutput The trigger output index identifying the trigger output, \c 0 to <tt>DevTrOutGetCount() - 1</tt>.
 * \return The supported trigger output events, a set of OR-ed \ref TOE_ "TOE_*" values.
 * \par Status values
 *   <table class="params">
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_OUTPUT "INVALID_OUTPUT"</td>         <td>The requested trigger output is invalid.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_NOT_SUPPORTED "NOT_SUPPORTED"</td>          <td>The device has no trigger outputs.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_HANDLE "INVALID_HANDLE"</td>         <td>The handle to the device is invalid.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_OBJECT_GONE "OBJECT_GONE"</td>            <td>The object indicated by the handle is no longer available.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_LIBRARY_NOT_INITIALIZED "LIBRARY_NOT_INITIALIZED"</td><td>The library is not initialized, see LibInit().</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_SUCCESS "SUCCESS"</td>                <td>The function executed successfully.</td></tr>
 *   </table>
 * \see DevTrOutGetEvent
 * \see DevTrOutSetEvent
 * \since 0.4.1
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef uint64_t(*LibTiePieDevTrOutGetEvents_t)( LibTiePieHandle_t hDevice , uint16_t wOutput );
#else
uint64_t DevTrOutGetEvents( LibTiePieHandle_t hDevice , uint16_t wOutput );
#endif

/**
 * \brief Get the currently selected trigger output event for a specified device trigger output.
 *
 * \param[in] hDevice A \ref OpenDev "device handle" identifying the device.
 * \param[in] wOutput The trigger output index identifying the trigger output, \c 0 to <tt>DevTrOutGetCount() - 1</tt>.
 * \return The currently selected trigger output event, a \ref TOE_ "TOE_*" value.
 * \par Status values
 *   <table class="params">
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_OUTPUT "INVALID_OUTPUT"</td>         <td>The requested trigger output is invalid.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_NOT_SUPPORTED "NOT_SUPPORTED"</td>          <td>The device has no trigger outputs.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_HANDLE "INVALID_HANDLE"</td>         <td>The handle to the device is invalid.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_OBJECT_GONE "OBJECT_GONE"</td>            <td>The object indicated by the handle is no longer available.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_LIBRARY_NOT_INITIALIZED "LIBRARY_NOT_INITIALIZED"</td><td>The library is not initialized, see LibInit().</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_SUCCESS "SUCCESS"</td>                <td>The function executed successfully.</td></tr>
 *   </table>
 * \see DevTrOutGetEvents
 * \see DevTrOutSetEvent
 * \since 0.4.1
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef uint64_t(*LibTiePieDevTrOutGetEvent_t)( LibTiePieHandle_t hDevice , uint16_t wOutput );
#else
uint64_t DevTrOutGetEvent( LibTiePieHandle_t hDevice , uint16_t wOutput );
#endif

/**
 * \brief Set the trigger output event for a specified device trigger output.
 *
 * \param[in] hDevice A \ref OpenDev "device handle" identifying the device.
 * \param[in] wOutput The trigger output index identifying the trigger output, \c 0 to <tt>DevTrOutGetCount() - 1</tt>.
 * \param[in] qwEvent Trigger output event, a \ref TOE_ "TOE_*" value.
 * \return Trigger output event, a \ref TOE_ "TOE_*" value.
 * \par Status values
 *   <table class="params">
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_OUTPUT "INVALID_OUTPUT"</td>         <td>The requested trigger output is invalid.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_VALUE "INVALID_VALUE"</td>          <td>The requested event value is invalid.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_NOT_SUPPORTED "NOT_SUPPORTED"</td>          <td>The device has no trigger outputs.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_HANDLE "INVALID_HANDLE"</td>         <td>The handle to the device is invalid.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_OBJECT_GONE "OBJECT_GONE"</td>            <td>The object indicated by the handle is no longer available.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_LIBRARY_NOT_INITIALIZED "LIBRARY_NOT_INITIALIZED"</td><td>The library is not initialized, see LibInit().</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_SUCCESS "SUCCESS"</td>                <td>The function executed successfully.</td></tr>
 *   </table>
 * \see DevTrOutGetEvents
 * \see DevTrOutGetEvent
 * \since 0.4.1
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef uint64_t(*LibTiePieDevTrOutSetEvent_t)( LibTiePieHandle_t hDevice , uint16_t wOutput , uint64_t qwEvent );
#else
uint64_t DevTrOutSetEvent( LibTiePieHandle_t hDevice , uint16_t wOutput , uint64_t qwEvent );
#endif

/**
 * \}
 * \defgroup dev_trigger_output_info Info
 * \{
 * \brief Obtain information of a device trigger output.
 *
 *             The following information of a device trigger output is available:
 *             - \ref DevTrOutGetId "ID"
 *             - \ref DevTrOutGetName "Name"
 */

// Workaround: Without this line Doxygen adds the documentation below to the group above.

/**
 * \brief Get the id of a specified device trigger output.
 *
 * \param[in] hDevice A \ref OpenDev "device handle" identifying the device.
 * \param[in] wOutput The trigger output index identifying the trigger output, \c 0 to <tt>DevTrOutGetCount() - 1</tt>.
 * \return The trigger output id, a \ref TOID_ "TOID_*" value.
 * \par Status values
 *   <table class="params">
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_OUTPUT "INVALID_OUTPUT"</td>         <td>The requested trigger output is invalid.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_NOT_SUPPORTED "NOT_SUPPORTED"</td>          <td>The device has no trigger outputs.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_HANDLE "INVALID_HANDLE"</td>         <td>The handle to the device is invalid.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_OBJECT_GONE "OBJECT_GONE"</td>            <td>The object indicated by the handle is no longer available.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_LIBRARY_NOT_INITIALIZED "LIBRARY_NOT_INITIALIZED"</td><td>The library is not initialized, see LibInit().</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_SUCCESS "SUCCESS"</td>                <td>The function executed successfully.</td></tr>
 *   </table>
 * \see DevTrGetOutputIndexById()
 * \since 0.4.4
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef uint32_t(*LibTiePieDevTrOutGetId_t)( LibTiePieHandle_t hDevice , uint16_t wOutput );
#else
uint32_t DevTrOutGetId( LibTiePieHandle_t hDevice , uint16_t wOutput );
#endif

/**
 * \brief Get the name of a specified device trigger output.
 *
 * \param[in] hDevice A \ref OpenDev "device handle" identifying the device.
 * \param[in] wOutput The trigger output index identifying the trigger output, \c 0 to <tt>DevTrOutGetCount() - 1</tt>.
 * \param[out] pBuffer A pointer to a buffer for the name.
 * \param[in] dwBufferLength The length of the buffer, in bytes.
 * \return The length of the name in bytes, excluding terminating zero.
 * \par Status values
 *   <table class="params">
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_OUTPUT "INVALID_OUTPUT"</td>         <td>The requested trigger output is invalid.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_NOT_SUPPORTED "NOT_SUPPORTED"</td>          <td>The device has no trigger outputs.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_HANDLE "INVALID_HANDLE"</td>         <td>The handle to the device is invalid.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_OBJECT_GONE "OBJECT_GONE"</td>            <td>The object indicated by the handle is no longer available.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_LIBRARY_NOT_INITIALIZED "LIBRARY_NOT_INITIALIZED"</td><td>The library is not initialized, see LibInit().</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_SUCCESS "SUCCESS"</td>                <td>The function executed successfully.</td></tr>
 *   </table>
 * \since 0.4.1
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef uint32_t(*LibTiePieDevTrOutGetName_t)( LibTiePieHandle_t hDevice , uint16_t wOutput , char* pBuffer , uint32_t dwBufferLength );
#else
uint32_t DevTrOutGetName( LibTiePieHandle_t hDevice , uint16_t wOutput , char* pBuffer , uint32_t dwBufferLength );
#endif

/**
 * \brief Trigger the specified device trigger output.
 *
 * \param[in] hDevice A \ref OpenDev "device handle" identifying the device.
 * \param[in] wOutput The trigger output index identifying the trigger output, \c 0 to <tt>DevTrOutGetCount() - 1</tt>.
 * \return #BOOL8_TRUE if successful, #BOOL8_FALSE otherwise.
 * \par Status values
 *   <table class="params">
 *   <tr><td>\ref LIBTIEPIESTATUS_UNSUCCESSFUL "UNSUCCESSFUL"</td>           <td>An error occurred during execution of the last called function.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_OUTPUT "INVALID_OUTPUT"</td>         <td>The requested trigger output is invalid.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_NOT_SUPPORTED "NOT_SUPPORTED"</td>          <td>The device has no trigger outputs or the trigger output doesn't support manual triggering.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_HANDLE "INVALID_HANDLE"</td>         <td>The handle to the device is invalid.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_DEVICE_GONE "DEVICE_GONE"</td>            <td></td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_LIBRARY_NOT_INITIALIZED "LIBRARY_NOT_INITIALIZED"</td><td>The library is not initialized, see LibInit().</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_SUCCESS "SUCCESS"</td>                <td>The function executed successfully.</td></tr>
 *   </table>
 * \since 0.6
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef bool8_t(*LibTiePieDevTrOutTrigger_t)( LibTiePieHandle_t hDevice , uint16_t wOutput );
#else
bool8_t DevTrOutTrigger( LibTiePieHandle_t hDevice , uint16_t wOutput );
#endif

/**
 * \}
 * \}
 * \}
 * \}
 * \defgroup scp Oscilloscope
 * \{
 * \brief Functions to setup and control oscilloscopes.
 *
 *       All oscilloscope related functions require an \ref LibTiePieHandle_t "oscilloscope handle" to identify the oscilloscope,
 *       see \ref OpenDev "opening a device".
 *
 * \defgroup scp_channels Channels
 * \{
 * \brief Functions to setup and control oscilloscope channels.
 *
 *         An oscilloscope will have one or more input channels.
 *         Use ScpGetChannelCount() to determine the amount of available channels.
 *
 *         All oscilloscope channel related functions use a channel number parameter to identify the channel.
 *         Channel numbers start at \c 0 for the first channel.
 *
 */

// Workaround: Without this line Doxygen adds the documentation below to the group above.

/**
 * \brief Get the number of channels.
 *
 * \param[in] hDevice A \ref OpenDev "device handle" identifying the oscilloscope.
 * \return The number of channels.
 * \par Status values
 *   <table class="params">
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_HANDLE "INVALID_HANDLE"</td>         <td>The handle is not a valid oscilloscope handle.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_OBJECT_GONE "OBJECT_GONE"</td>            <td>The object indicated by the handle is no longer available.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_LIBRARY_NOT_INITIALIZED "LIBRARY_NOT_INITIALIZED"</td><td>The library is not initialized, see LibInit().</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_SUCCESS "SUCCESS"</td>                <td>The function executed successfully.</td></tr>
 *   </table>
 * \since 0.4.0
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef uint16_t(*LibTiePieScpGetChannelCount_t)( LibTiePieHandle_t hDevice );
#else
uint16_t ScpGetChannelCount( LibTiePieHandle_t hDevice );
#endif

/**
 * \brief Check whether the channel is available.
 *
 * Depending on other settings, a channel may currently not be available.
 * It can still be \ref ScpChGetEnabled "enabled", but that will affect other settings.
 *
 * \param[in] hDevice A \ref OpenDev "device handle" identifying the oscilloscope.
 * \param[in] wCh The channel number identifying the channel, \c 0 to <tt>ScpGetChannelCount() - 1</tt>.
 * \return #BOOL8_TRUE if available, #BOOL8_FALSE otherwise.
 * \par Status values
 *   <table class="params">
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_CHANNEL "INVALID_CHANNEL"</td>        <td>The requested channel number is invalid.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_HANDLE "INVALID_HANDLE"</td>         <td>The handle is not a valid oscilloscope handle.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_OBJECT_GONE "OBJECT_GONE"</td>            <td>The object indicated by the handle is no longer available.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_LIBRARY_NOT_INITIALIZED "LIBRARY_NOT_INITIALIZED"</td><td>The library is not initialized, see LibInit().</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_SUCCESS "SUCCESS"</td>                <td>The function executed successfully.</td></tr>
 *   </table>
 * \since 0.4.4
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef bool8_t(*LibTiePieScpChIsAvailable_t)( LibTiePieHandle_t hDevice , uint16_t wCh );
#else
bool8_t ScpChIsAvailable( LibTiePieHandle_t hDevice , uint16_t wCh );
#endif

//! \cond EXTENDED_API

/**
 * \brief Check whether the channel is available, for a specific configuration.
 *
 * \param[in] hDevice A \ref OpenDev "device handle" identifying the oscilloscope.
 * \param[in] wCh The channel number identifying the channel, \c 0 to <tt>ScpGetChannelCount() - 1</tt>.
 * \param[in] dwMeasureMode Measure mode, a \ref MM_ "MM_*" value.
 * \param[in] dSampleFrequency SampleFrequency in Hz.
 * \param[in] byResolution Resolution in bits.
 * \param[in] pChannelEnabled Pointer to buffer with channel enables.
 * \param[in] wChannelCount Number of items in \c pChannelEnabled
 * \return #BOOL8_TRUE if available, #BOOL8_FALSE otherwise.
 * \since 0.4.4
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef bool8_t(*LibTiePieScpChIsAvailableEx_t)( LibTiePieHandle_t hDevice , uint16_t wCh , uint32_t dwMeasureMode , double dSampleFrequency , uint8_t byResolution , const bool8_t* pChannelEnabled , uint16_t wChannelCount );
#else
bool8_t ScpChIsAvailableEx( LibTiePieHandle_t hDevice , uint16_t wCh , uint32_t dwMeasureMode , double dSampleFrequency , uint8_t byResolution , const bool8_t* pChannelEnabled , uint16_t wChannelCount );
#endif

//! \endcond

/**
 * \defgroup scp_ch_info Info
 * \{
 * \brief Functions to retrieve information from an oscilloscope channel.
 */

// Workaround: Without this line Doxygen adds the documentation below to the group above.

/**
 * \brief Get the channel \ref CONNECTORTYPE_ "connector type".
 *
 * \param[in] hDevice A \ref OpenDev "device handle" identifying the oscilloscope.
 * \param[in] wCh The channel number identifying the channel, \c 0 to <tt>ScpGetChannelCount() - 1</tt>.
 * \return Channel \ref CONNECTORTYPE_ "connector type".
 * \par Status values
 *   <table class="params">
 *   <tr><td>\ref LIBTIEPIESTATUS_NOT_SUPPORTED "NOT_SUPPORTED"</td>          <td>The channel does not support reading the connector type.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_CHANNEL "INVALID_CHANNEL"</td>        <td>The requested channel number is invalid.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_HANDLE "INVALID_HANDLE"</td>         <td>The handle is not a valid oscilloscope handle.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_OBJECT_GONE "OBJECT_GONE"</td>            <td>The object indicated by the handle is no longer available.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_LIBRARY_NOT_INITIALIZED "LIBRARY_NOT_INITIALIZED"</td><td>The library is not initialized, see LibInit().</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_SUCCESS "SUCCESS"</td>                <td>The function executed successfully.</td></tr>
 *   </table>
 * \since 0.4.0
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef uint32_t(*LibTiePieScpChGetConnectorType_t)( LibTiePieHandle_t hDevice , uint16_t wCh );
#else
uint32_t ScpChGetConnectorType( LibTiePieHandle_t hDevice , uint16_t wCh );
#endif

/**
 * \brief Check whether the channel has a differential input.
 *
 * \param[in] hDevice A \ref OpenDev "device handle" identifying the oscilloscope.
 * \param[in] wCh The channel number identifying the channel, \c 0 to <tt>ScpGetChannelCount() - 1</tt>.
 * \return #BOOL8_TRUE if differential, #BOOL8_FALSE otherwise.
 * \par Status values
 *   <table class="params">
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_CHANNEL "INVALID_CHANNEL"</td>        <td>The requested channel number is invalid.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_HANDLE "INVALID_HANDLE"</td>         <td>The handle is not a valid oscilloscope handle.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_OBJECT_GONE "OBJECT_GONE"</td>            <td>The object indicated by the handle is no longer available.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_LIBRARY_NOT_INITIALIZED "LIBRARY_NOT_INITIALIZED"</td><td>The library is not initialized, see LibInit().</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_SUCCESS "SUCCESS"</td>                <td>The function executed successfully.</td></tr>
 *   </table>
 * \since 0.4.0
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef bool8_t(*LibTiePieScpChIsDifferential_t)( LibTiePieHandle_t hDevice , uint16_t wCh );
#else
bool8_t ScpChIsDifferential( LibTiePieHandle_t hDevice , uint16_t wCh );
#endif

/**
 * \brief Get the channel input impedance.
 *
 * \param[in] hDevice A \ref OpenDev "device handle" identifying the oscilloscope.
 * \param[in] wCh The channel number identifying the channel, \c 0 to <tt>ScpGetChannelCount() - 1</tt>.
 * \return Channel input impedance in Ohm.
 * \par Status values
 *   <table class="params">
 *   <tr><td>\ref LIBTIEPIESTATUS_NOT_SUPPORTED "NOT_SUPPORTED"</td>          <td>The channel does not support reading the input impedance.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_CHANNEL "INVALID_CHANNEL"</td>        <td>The requested channel number is invalid.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_HANDLE "INVALID_HANDLE"</td>         <td>The handle is not a valid oscilloscope handle.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_OBJECT_GONE "OBJECT_GONE"</td>            <td>The object indicated by the handle is no longer available.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_LIBRARY_NOT_INITIALIZED "LIBRARY_NOT_INITIALIZED"</td><td>The library is not initialized, see LibInit().</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_SUCCESS "SUCCESS"</td>                <td>The function executed successfully.</td></tr>
 *   </table>
 * \since 0.4.5
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef double(*LibTiePieScpChGetImpedance_t)( LibTiePieHandle_t hDevice , uint16_t wCh );
#else
double ScpChGetImpedance( LibTiePieHandle_t hDevice , uint16_t wCh );
#endif

/**
 * \}
 * \defgroup scp_ch_bandwidth Bandwidth
 * \{
 * \brief Functions to control the input bandwidth of an oscilloscope channel.
 *
 *           By default the input bandwidth of a channel is set to the highest value available.
 */

// Workaround: Without this line Doxygen adds the documentation below to the group above.

/**
 * \brief Get the supported input bandwidths for a specified channel.
 *
 * \param[in] hDevice A \ref OpenDev "device handle" identifying the oscilloscope.
 * \param[in] wCh The channel number identifying the channel, \c 0 to <tt>ScpGetChannelCount() - 1</tt>.
 * \param[out] pList A pointer to an array for the input bandwidths.
 * \param[in] dwLength The number of elements in the array.
 * \return The total number of bandwidths.
 * \par Status values
 *   <table class="params">
 *   <tr><td>\ref LIBTIEPIESTATUS_UNSUCCESSFUL "UNSUCCESSFUL"</td>           <td>An error occurred during execution of the last called function.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_CHANNEL "INVALID_CHANNEL"</td>        <td>The requested channel number is invalid.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_HANDLE "INVALID_HANDLE"</td>         <td>The handle is not a valid oscilloscope handle.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_OBJECT_GONE "OBJECT_GONE"</td>            <td>The object indicated by the handle is no longer available.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_LIBRARY_NOT_INITIALIZED "LIBRARY_NOT_INITIALIZED"</td><td>The library is not initialized, see LibInit().</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_SUCCESS "SUCCESS"</td>                <td>The function executed successfully.</td></tr>
 *   </table>
 * \see ScpChGetBandwidth
 * \see ScpChSetBandwidth
 * \since 0.6
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef uint32_t(*LibTiePieScpChGetBandwidths_t)( LibTiePieHandle_t hDevice , uint16_t wCh , double* pList , uint32_t dwLength );
#else
uint32_t ScpChGetBandwidths( LibTiePieHandle_t hDevice , uint16_t wCh , double* pList , uint32_t dwLength );
#endif

/**
 * \brief Get the current channel input bandwidth.
 *
 * \param[in] hDevice A \ref OpenDev "device handle" identifying the oscilloscope.
 * \param[in] wCh The channel number identifying the channel, \c 0 to <tt>ScpGetChannelCount() - 1</tt>.
 * \return The current channel input bandwidth in Hz.
 * \par Status values
 *   <table class="params">
 *   <tr><td>\ref LIBTIEPIESTATUS_NOT_SUPPORTED "NOT_SUPPORTED"</td>          <td>The channel does not support reading the input bandwidth.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_CHANNEL "INVALID_CHANNEL"</td>        <td>The requested channel number is invalid.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_HANDLE "INVALID_HANDLE"</td>         <td>The handle is not a valid oscilloscope handle.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_OBJECT_GONE "OBJECT_GONE"</td>            <td>The object indicated by the handle is no longer available.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_LIBRARY_NOT_INITIALIZED "LIBRARY_NOT_INITIALIZED"</td><td>The library is not initialized, see LibInit().</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_SUCCESS "SUCCESS"</td>                <td>The function executed successfully.</td></tr>
 *   </table>
 * \see ScpChGetBandwidths
 * \see ScpChSetBandwidth
 * \since 0.6
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef double(*LibTiePieScpChGetBandwidth_t)( LibTiePieHandle_t hDevice , uint16_t wCh );
#else
double ScpChGetBandwidth( LibTiePieHandle_t hDevice , uint16_t wCh );
#endif

/**
 * \brief Set the channel input bandwidth.
 *
 * \param[in] hDevice A \ref OpenDev "device handle" identifying the oscilloscope.
 * \param[in] wCh The channel number identifying the channel, \c 0 to <tt>ScpGetChannelCount() - 1</tt>.
 * \param[in] dBandwidth The requested input bandwidth in Hz.
 * \return The actually set channel input bandwidth in Hz.
 * \par Status values
 *   <table class="params">
 *   <tr><td>\ref LIBTIEPIESTATUS_NOT_SUPPORTED "NOT_SUPPORTED"</td>          <td>The channel does not support changing the input bandwidth.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_CHANNEL "INVALID_CHANNEL"</td>        <td>The requested channel number is invalid.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_HANDLE "INVALID_HANDLE"</td>         <td>The handle is not a valid oscilloscope handle.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_OBJECT_GONE "OBJECT_GONE"</td>            <td>The object indicated by the handle is no longer available.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_LIBRARY_NOT_INITIALIZED "LIBRARY_NOT_INITIALIZED"</td><td>The library is not initialized, see LibInit().</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_SUCCESS "SUCCESS"</td>                <td>The function executed successfully.</td></tr>
 *   </table>
 * \see ScpChGetBandwidths
 * \see ScpChGetBandwidth
 * \since 0.6
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef double(*LibTiePieScpChSetBandwidth_t)( LibTiePieHandle_t hDevice , uint16_t wCh , double dBandwidth );
#else
double ScpChSetBandwidth( LibTiePieHandle_t hDevice , uint16_t wCh , double dBandwidth );
#endif

/**
 * \}
 * \defgroup scp_ch_coupling Coupling
 * \{
 * \brief Functions to control the input coupling of an oscilloscope channel.
 *
 *           By default the input coupling of a channel is set to: Volt DC (#CK_DCV).
 */

// Workaround: Without this line Doxygen adds the documentation below to the group above.

/**
 * \brief Get the supported coupling kinds of a specified channel.
 *
 * \param[in] hDevice A \ref OpenDev "device handle" identifying the oscilloscope.
 * \param[in] wCh The channel number identifying the channel, \c 0 to <tt>ScpGetChannelCount() - 1</tt>.
 * \return The supported coupling kinds, a set of OR-ed \ref CK_ "CK_*" values.
 * \par Status values
 *   <table class="params">
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_CHANNEL "INVALID_CHANNEL"</td>        <td>The requested channel number is invalid.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_HANDLE "INVALID_HANDLE"</td>         <td>The handle is not a valid oscilloscope handle.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_OBJECT_GONE "OBJECT_GONE"</td>            <td>The object indicated by the handle is no longer available.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_LIBRARY_NOT_INITIALIZED "LIBRARY_NOT_INITIALIZED"</td><td>The library is not initialized, see LibInit().</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_SUCCESS "SUCCESS"</td>                <td>The function executed successfully.</td></tr>
 *   </table>
 * \see ScpChGetCoupling
 * \see ScpChSetCoupling
 * \since 0.4.0
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef uint64_t(*LibTiePieScpChGetCouplings_t)( LibTiePieHandle_t hDevice , uint16_t wCh );
#else
uint64_t ScpChGetCouplings( LibTiePieHandle_t hDevice , uint16_t wCh );
#endif

/**
 * \brief Get the currently set coupling of a specified channel.
 *
 * \param[in] hDevice A \ref OpenDev "device handle" identifying the oscilloscope.
 * \param[in] wCh The channel number identifying the channel, \c 0 to <tt>ScpGetChannelCount() - 1</tt>.
 * \return Coupling, a \ref CK_ "CK_*" value.
 * \par Status values
 *   <table class="params">
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_CHANNEL "INVALID_CHANNEL"</td>        <td>The requested channel number is invalid.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_HANDLE "INVALID_HANDLE"</td>         <td>The handle is not a valid oscilloscope handle.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_OBJECT_GONE "OBJECT_GONE"</td>            <td>The object indicated by the handle is no longer available.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_LIBRARY_NOT_INITIALIZED "LIBRARY_NOT_INITIALIZED"</td><td>The library is not initialized, see LibInit().</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_SUCCESS "SUCCESS"</td>                <td>The function executed successfully.</td></tr>
 *   </table>
 * \see ScpChGetCouplings
 * \see ScpChSetCoupling
 * \since 0.4.0
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef uint64_t(*LibTiePieScpChGetCoupling_t)( LibTiePieHandle_t hDevice , uint16_t wCh );
#else
uint64_t ScpChGetCoupling( LibTiePieHandle_t hDevice , uint16_t wCh );
#endif

/**
 * \brief Set the coupling of a specified channel.
 *
 * \param[in] hDevice A \ref OpenDev "device handle" identifying the oscilloscope.
 * \param[in] wCh The channel number identifying the channel, \c 0 to <tt>ScpGetChannelCount() - 1</tt>.
 * \param[in] qwCoupling The required coupling, a \ref CK_ "CK_*" value.
 * \return The actually set coupling, a \ref CK_ "CK_*" value.
 * \par Status values
 *   <table class="params">
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_VALUE "INVALID_VALUE"</td>          <td>The requested coupling kind is invalid.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_CHANNEL "INVALID_CHANNEL"</td>        <td>The requested channel number is invalid.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_HANDLE "INVALID_HANDLE"</td>         <td>The handle is not a valid oscilloscope handle.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_OBJECT_GONE "OBJECT_GONE"</td>            <td>The object indicated by the handle is no longer available.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_LIBRARY_NOT_INITIALIZED "LIBRARY_NOT_INITIALIZED"</td><td>The library is not initialized, see LibInit().</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_SUCCESS "SUCCESS"</td>                <td>The function executed successfully.</td></tr>
 *   </table>
 * \remark Changing the input coupling can affect the \ref scp_ch_range "input range".
 *
 * \see ScpChGetCouplings
 * \see ScpChGetCoupling
 * \since 0.4.0
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef uint64_t(*LibTiePieScpChSetCoupling_t)( LibTiePieHandle_t hDevice , uint16_t wCh , uint64_t qwCoupling );
#else
uint64_t ScpChSetCoupling( LibTiePieHandle_t hDevice , uint16_t wCh , uint64_t qwCoupling );
#endif

/**
 * \}
 * \defgroup scp_ch_enabled Enabled
 * \{
 * \brief Functions to control the enabled state of an oscilloscope channel.
 *
 *           The enabled state of a channel determines whether the channel is measured.
 *
 *           By default all channels are enabled (#BOOL8_TRUE).
 */

// Workaround: Without this line Doxygen adds the documentation below to the group above.

/**
 * \brief Check whether a specified channel is currently enabled.
 *
 * \param[in] hDevice A \ref OpenDev "device handle" identifying the oscilloscope.
 * \param[in] wCh The channel number identifying the channel, \c 0 to <tt>ScpGetChannelCount() - 1</tt>.
 * \return #BOOL8_TRUE if enabled, #BOOL8_FALSE if disabled.
 * \par Status values
 *   <table class="params">
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_CHANNEL "INVALID_CHANNEL"</td>        <td>The requested channel number is invalid.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_HANDLE "INVALID_HANDLE"</td>         <td>The handle is not a valid oscilloscope handle.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_OBJECT_GONE "OBJECT_GONE"</td>            <td>The object indicated by the handle is no longer available.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_LIBRARY_NOT_INITIALIZED "LIBRARY_NOT_INITIALIZED"</td><td>The library is not initialized, see LibInit().</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_SUCCESS "SUCCESS"</td>                <td>The function executed successfully.</td></tr>
 *   </table>
 * \see ScpChSetEnabled
 * \since 0.4.0
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef bool8_t(*LibTiePieScpChGetEnabled_t)( LibTiePieHandle_t hDevice , uint16_t wCh );
#else
bool8_t ScpChGetEnabled( LibTiePieHandle_t hDevice , uint16_t wCh );
#endif

/**
 * \brief Set channel enable.
 *
 * \param[in] hDevice A \ref OpenDev "device handle" identifying the oscilloscope.
 * \param[in] wCh The channel number identifying the channel, \c 0 to <tt>ScpGetChannelCount() - 1</tt>.
 * \param[in] bEnable #BOOL8_TRUE or #BOOL8_FALSE.
 * \return #BOOL8_TRUE if enabled, #BOOL8_FALSE if disabled.
 * \par Status values
 *   <table class="params">
 *   <tr><td>\ref LIBTIEPIESTATUS_NOT_AVAILABLE "NOT_AVAILABLE"</td>          <td>With the current settings, the requested functionality is not available.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_CHANNEL "INVALID_CHANNEL"</td>        <td>The requested channel number is invalid.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_HANDLE "INVALID_HANDLE"</td>         <td>The handle is not a valid oscilloscope handle.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_OBJECT_GONE "OBJECT_GONE"</td>            <td>The object indicated by the handle is no longer available.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_LIBRARY_NOT_INITIALIZED "LIBRARY_NOT_INITIALIZED"</td><td>The library is not initialized, see LibInit().</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_SUCCESS "SUCCESS"</td>                <td>The function executed successfully.</td></tr>
 *   </table>
 * \remark Changing the channel enable may affect the \ref scp_timebase_sampleFrequency "sample frequency", \ref scp_timebase_recordLength "record length" and/or \ref scp_ch_tr_enabled "channel trigger enabled".
 * \see ScpChGetEnabled
 * \since 0.4.0
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef bool8_t(*LibTiePieScpChSetEnabled_t)( LibTiePieHandle_t hDevice , uint16_t wCh , bool8_t bEnable );
#else
bool8_t ScpChSetEnabled( LibTiePieHandle_t hDevice , uint16_t wCh , bool8_t bEnable );
#endif

/**
 * \}
 * \defgroup scp_ch_probe Probe
 * \{
 * \brief Functions to control the probe settings of an oscilloscope channel.
 *
 *           Probes connected to an input channel usually attenuate the input signal.
 *           Specialized probes or signal converters can also amplify the input signal and/or apply an offset to it.
 *           Probe gain and offset settings are available to compensate the measured values for the gain and offset applied by the
 *           probe or converter.
 *           The channel will then give the original signal values.
 *
 *           When e.g. a X10 attenuating oscilloscope probe is connected, the channel will measure a 10 times smaller value of the input signal.
 *           By setting the probe gain to \c 10, the measured values will be multiplied by 10 to compensate.
 *
 *           By default probe gain is set to \c 1x and probe offset to \c 0.
 */

// Workaround: Without this line Doxygen adds the documentation below to the group above.

/**
 * \brief Get the currently set channel probe gain for a specified channel.
 *
 * \param[in] hDevice A \ref OpenDev "device handle" identifying the oscilloscope.
 * \param[in] wCh The channel number identifying the channel, \c 0 to <tt>ScpGetChannelCount() - 1</tt>.
 * \return The currently set probe gain.
 * \par Status values
 *   <table class="params">
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_CHANNEL "INVALID_CHANNEL"</td>        <td>The requested channel number is invalid.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_HANDLE "INVALID_HANDLE"</td>         <td>The handle is not a valid oscilloscope handle.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_OBJECT_GONE "OBJECT_GONE"</td>            <td>The object indicated by the handle is no longer available.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_LIBRARY_NOT_INITIALIZED "LIBRARY_NOT_INITIALIZED"</td><td>The library is not initialized, see LibInit().</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_SUCCESS "SUCCESS"</td>                <td>The function executed successfully.</td></tr>
 *   </table>
 * \see ScpChSetProbeGain
 * \see ScpChGetDataValueRange
 * \see ScpChGetDataValueMin
 * \see ScpChGetDataValueMax
 * \since 0.4.0
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef double(*LibTiePieScpChGetProbeGain_t)( LibTiePieHandle_t hDevice , uint16_t wCh );
#else
double ScpChGetProbeGain( LibTiePieHandle_t hDevice , uint16_t wCh );
#endif

/**
 * \brief Set the channel probe gain for a specified channel.
 *
 * \param[in] hDevice A \ref OpenDev "device handle" identifying the oscilloscope.
 * \param[in] wCh The channel number identifying the channel, \c 0 to <tt>ScpGetChannelCount() - 1</tt>.
 * \param[in] dProbeGain The required probe gain, <tt>-1e6 <=</tt> gain <tt><= 1e6, != 0</tt>.
 * \return The actually set probe gain.
 * \par Status values
 *   <table class="params">
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_VALUE "INVALID_VALUE"</td>          <td>The requested probe gain value is invalid.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_VALUE_CLIPPED "VALUE_CLIPPED"</td>          <td>The requested probe gain value is outside the valid range and clipped to the closest limit.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_CHANNEL "INVALID_CHANNEL"</td>        <td>The requested channel number is invalid.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_HANDLE "INVALID_HANDLE"</td>         <td>The handle is not a valid oscilloscope handle.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_OBJECT_GONE "OBJECT_GONE"</td>            <td>The object indicated by the handle is no longer available.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_LIBRARY_NOT_INITIALIZED "LIBRARY_NOT_INITIALIZED"</td><td>The library is not initialized, see LibInit().</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_SUCCESS "SUCCESS"</td>                <td>The function executed successfully.</td></tr>
 *   </table>
 * \see ScpChGetProbeGain
 * \see ScpChGetDataValueRange
 * \see ScpChGetDataValueMin
 * \see ScpChGetDataValueMax
 * \since 0.4.0
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef double(*LibTiePieScpChSetProbeGain_t)( LibTiePieHandle_t hDevice , uint16_t wCh , double dProbeGain );
#else
double ScpChSetProbeGain( LibTiePieHandle_t hDevice , uint16_t wCh , double dProbeGain );
#endif

/**
 * \brief Get the currently set channel probe offset for a specified channel.
 *
 * The probe offset value is in Volt, Ampere or Ohm, depending on the \ref scp_ch_coupling "input coupling"
 *
 * \param[in] hDevice A \ref OpenDev "device handle" identifying the oscilloscope.
 * \param[in] wCh The channel number identifying the channel, \c 0 to <tt>ScpGetChannelCount() - 1</tt>.
 * \return The currently set probe offset.
 * \par Status values
 *   <table class="params">
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_CHANNEL "INVALID_CHANNEL"</td>        <td>The requested channel number is invalid.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_HANDLE "INVALID_HANDLE"</td>         <td>The handle is not a valid oscilloscope handle.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_OBJECT_GONE "OBJECT_GONE"</td>            <td>The object indicated by the handle is no longer available.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_LIBRARY_NOT_INITIALIZED "LIBRARY_NOT_INITIALIZED"</td><td>The library is not initialized, see LibInit().</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_SUCCESS "SUCCESS"</td>                <td>The function executed successfully.</td></tr>
 *   </table>
 * \see ScpChSetProbeOffset
 * \see ScpChGetDataValueRange
 * \see ScpChGetDataValueMin
 * \see ScpChGetDataValueMax
 * \since 0.4.4
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef double(*LibTiePieScpChGetProbeOffset_t)( LibTiePieHandle_t hDevice , uint16_t wCh );
#else
double ScpChGetProbeOffset( LibTiePieHandle_t hDevice , uint16_t wCh );
#endif

/**
 * \brief Set the channel probe offset for a specified channel.
 *
 * The probe offset value is in Volt, Ampere or Ohm, depending on the \ref scp_ch_coupling "input coupling"
 *
 * \param[in] hDevice A \ref OpenDev "device handle" identifying the oscilloscope.
 * \param[in] wCh The channel number identifying the channel, \c 0 to <tt>ScpGetChannelCount() - 1</tt>.
 * \param[in] dProbeOffset The required probe offset, <tt>-1e6 <=</tt> offset <tt><= 1e6</tt>.
 * \return The actually set probe offset.
 * \par Status values
 *   <table class="params">
 *   <tr><td>\ref LIBTIEPIESTATUS_VALUE_CLIPPED "VALUE_CLIPPED"</td>          <td>The requested probe offset value is outside the valid range and clipped to the closest limit.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_CHANNEL "INVALID_CHANNEL"</td>        <td>The requested channel number is invalid.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_HANDLE "INVALID_HANDLE"</td>         <td>The handle is not a valid oscilloscope handle.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_OBJECT_GONE "OBJECT_GONE"</td>            <td>The object indicated by the handle is no longer available.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_LIBRARY_NOT_INITIALIZED "LIBRARY_NOT_INITIALIZED"</td><td>The library is not initialized, see LibInit().</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_SUCCESS "SUCCESS"</td>                <td>The function executed successfully.</td></tr>
 *   </table>
 * \see ScpChGetProbeOffset
 * \see ScpChGetDataValueRange
 * \see ScpChGetDataValueMin
 * \see ScpChGetDataValueMax
 * \since 0.4.4
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef double(*LibTiePieScpChSetProbeOffset_t)( LibTiePieHandle_t hDevice , uint16_t wCh , double dProbeOffset );
#else
double ScpChSetProbeOffset( LibTiePieHandle_t hDevice , uint16_t wCh , double dProbeOffset );
#endif

/**
 * \}
 * \defgroup scp_ch_range Range
 * \{
 * \brief Functions to control the input range of an oscilloscope channel
 *
 *           An oscilloscope channel will have one or more different input ranges.
 *           The number of input ranges and which ranges are available depends on the selected \ref ScpChGetCoupling "input coupling".
 *           Use ScpChGetRanges() to determine how many and which ranges are available.
 *           Changing the input couping may change the selected input range.
 *
 *           An input channel supports auto ranging, where a suitable input range is selected based on the measured data of the
 *           last performed measurement with the channel.
 *           Manually setting a range will disable auto ranging.
 *
 *           When auto ranging of a channel is enabled and \ref scp_ch_tr_level_mode "trigger level mode" is set to #TLM_ABSOLUTE,
 *           the input range will not auto range to a range that is smaller than the selected trigger level.
 *
 *           By default the highest available range is selected and auto ranging is enabled.
 */

// Workaround: Without this line Doxygen adds the documentation below to the group above.

/**
 * \brief Check whether auto ranging is enabled for a specified channel.
 *
 * \param[in] hDevice A \ref OpenDev "device handle" identifying the oscilloscope.
 * \param[in] wCh The channel number identifying the channel, \c 0 to <tt>ScpGetChannelCount() - 1</tt>.
 * \return #BOOL8_TRUE if enabled, #BOOL8_FALSE if disabled.
 * \par Status values
 *   <table class="params">
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_CHANNEL "INVALID_CHANNEL"</td>        <td>The requested channel number is invalid.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_HANDLE "INVALID_HANDLE"</td>         <td>The handle is not a valid oscilloscope handle.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_OBJECT_GONE "OBJECT_GONE"</td>            <td>The object indicated by the handle is no longer available.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_LIBRARY_NOT_INITIALIZED "LIBRARY_NOT_INITIALIZED"</td><td>The library is not initialized, see LibInit().</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_SUCCESS "SUCCESS"</td>                <td>The function executed successfully.</td></tr>
 *   </table>
 * \see ScpChSetAutoRanging
 * \since 0.4.0
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef bool8_t(*LibTiePieScpChGetAutoRanging_t)( LibTiePieHandle_t hDevice , uint16_t wCh );
#else
bool8_t ScpChGetAutoRanging( LibTiePieHandle_t hDevice , uint16_t wCh );
#endif

/**
 * \brief Set auto ranging for a specified channel.
 *
 * \param[in] hDevice A \ref OpenDev "device handle" identifying the oscilloscope.
 * \param[in] wCh The channel number identifying the channel, \c 0 to <tt>ScpGetChannelCount() - 1</tt>.
 * \param[in] bEnable #BOOL8_TRUE to enable or #BOOL8_FALSE to disable.
 * \return #BOOL8_TRUE if enabled, #BOOL8_FALSE if disabled.
 * \par Status values
 *   <table class="params">
 *   <tr><td>\ref LIBTIEPIESTATUS_NOT_SUPPORTED "NOT_SUPPORTED"</td>          <td>With the current settings, auto ranging is not available.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_CHANNEL "INVALID_CHANNEL"</td>        <td>The requested channel number is invalid.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_HANDLE "INVALID_HANDLE"</td>         <td>The handle is not a valid oscilloscope handle.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_OBJECT_GONE "OBJECT_GONE"</td>            <td>The object indicated by the handle is no longer available.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_LIBRARY_NOT_INITIALIZED "LIBRARY_NOT_INITIALIZED"</td><td>The library is not initialized, see LibInit().</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_SUCCESS "SUCCESS"</td>                <td>The function executed successfully.</td></tr>
 *   </table>
 * \see ScpChGetAutoRanging
 * \since 0.4.0
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef bool8_t(*LibTiePieScpChSetAutoRanging_t)( LibTiePieHandle_t hDevice , uint16_t wCh , bool8_t bEnable );
#else
bool8_t ScpChSetAutoRanging( LibTiePieHandle_t hDevice , uint16_t wCh , bool8_t bEnable );
#endif

/**
 * \brief Get the supported input ranges for a specified channel, with the currently selected \ref ScpChGetCoupling "coupling".
 *
 * \param[in] hDevice A \ref OpenDev "device handle" identifying the oscilloscope.
 * \param[in] wCh The channel number identifying the channel, \c 0 to <tt>ScpGetChannelCount() - 1</tt>.
 * \param[out] pList A pointer to an array for the input ranges.
 * \param[in] dwLength The number of elements in the array.
 * \return The total number of ranges.
 * \par Status values
 *   <table class="params">
 *   <tr><td>\ref LIBTIEPIESTATUS_UNSUCCESSFUL "UNSUCCESSFUL"</td>           <td>An error occurred during execution of the last called function.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_CHANNEL "INVALID_CHANNEL"</td>        <td>The requested channel number is invalid.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_HANDLE "INVALID_HANDLE"</td>         <td>The handle is not a valid oscilloscope handle.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_OBJECT_GONE "OBJECT_GONE"</td>            <td>The object indicated by the handle is no longer available.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_LIBRARY_NOT_INITIALIZED "LIBRARY_NOT_INITIALIZED"</td><td>The library is not initialized, see LibInit().</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_SUCCESS "SUCCESS"</td>                <td>The function executed successfully.</td></tr>
 *   </table>
 * \cond EXTENDED_API
 * \see ScpChGetRangesEx
 * \endcond
 *
 * \par Example
 * \code{.c}
 * uint32_t dwRangeCount = ScpChGetRanges( hDevice , wCh , NULL , 0 );
 * double* pRanges = malloc( sizeof( double ) * dwRangeCount );
 * dwRangeCount = ScpChGetRanges( hDevice , wCh , pRanges , dwRangeCount );
 *
 * printf( "ScpChGetRanges (Ch%u):\n" , wCh + 1 );
 * for( i = 0 ; i < dwRangeCount ; i++ )
 *   printf( "- %f\n" , pRanges[ i ] );
 *
 * free( pRanges );
 * \endcode
 *
 * \see ScpChGetRange
 * \see ScpChSetRange
 * \since 0.4.0
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef uint32_t(*LibTiePieScpChGetRanges_t)( LibTiePieHandle_t hDevice , uint16_t wCh , double* pList , uint32_t dwLength );
#else
uint32_t ScpChGetRanges( LibTiePieHandle_t hDevice , uint16_t wCh , double* pList , uint32_t dwLength );
#endif

//! \cond EXTENDED_API

/**
 * \brief Get the supported ranges by coupling.
 *
 * \param[in] hDevice A \ref OpenDev "device handle" identifying the oscilloscope.
 * \param[in] wCh The channel number identifying the channel, \c 0 to <tt>ScpGetChannelCount() - 1</tt>.
 * \param[in] qwCoupling Coupling: a \ref CK_ "CK_*" value.
 * \param[out] pList Pointer to array.
 * \param[in] dwLength Number of elements in array.
 * \return Total number of ranges.
 * \see ScpChGetRanges
 * \since 0.4.0
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef uint32_t(*LibTiePieScpChGetRangesEx_t)( LibTiePieHandle_t hDevice , uint16_t wCh , uint64_t qwCoupling , double* pList , uint32_t dwLength );
#else
uint32_t ScpChGetRangesEx( LibTiePieHandle_t hDevice , uint16_t wCh , uint64_t qwCoupling , double* pList , uint32_t dwLength );
#endif

//! \endcond

/**
 * \brief Get the currently selected input range for a specified channel.
 *
 * \param[in] hDevice A \ref OpenDev "device handle" identifying the oscilloscope.
 * \param[in] wCh The channel number identifying the channel, \c 0 to <tt>ScpGetChannelCount() - 1</tt>.
 * \return The currently selected input range.
 * \par Status values
 *   <table class="params">
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_CHANNEL "INVALID_CHANNEL"</td>        <td>The requested channel number is invalid.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_HANDLE "INVALID_HANDLE"</td>         <td>The handle is not a valid oscilloscope handle.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_OBJECT_GONE "OBJECT_GONE"</td>            <td>The object indicated by the handle is no longer available.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_LIBRARY_NOT_INITIALIZED "LIBRARY_NOT_INITIALIZED"</td><td>The library is not initialized, see LibInit().</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_SUCCESS "SUCCESS"</td>                <td>The function executed successfully.</td></tr>
 *   </table>
 * \see ScpChGetRanges
 * \see ScpChSetRange
 * \since 0.4.0
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef double(*LibTiePieScpChGetRange_t)( LibTiePieHandle_t hDevice , uint16_t wCh );
#else
double ScpChGetRange( LibTiePieHandle_t hDevice , uint16_t wCh );
#endif

/**
 * \brief Set the input range for a specified channel.
 *
 * When a non existing input range value is tried to be set, the closest available larger input range is selected.
 *
 * \param[in] hDevice A \ref OpenDev "device handle" identifying the oscilloscope.
 * \param[in] wCh The channel number identifying the channel, \c 0 to <tt>ScpGetChannelCount() - 1</tt>.
 * \param[in] dRange The requested input range, or maximum absolute value that must fit within the range.
 * \return The actually selected input range.
 * \par Status values
 *   <table class="params">
 *   <tr><td>\ref LIBTIEPIESTATUS_VALUE_CLIPPED "VALUE_CLIPPED"</td>          <td>The requested input range is larger than the largest available range and clipped to that range.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_VALUE_MODIFIED "VALUE_MODIFIED"</td>         <td>The requested input range is within the valid range but not available. The closest larger valid value is set.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_VALUE "INVALID_VALUE"</td>          <td>The requested input range is invalid.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_CHANNEL "INVALID_CHANNEL"</td>        <td>The requested channel number is invalid.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_HANDLE "INVALID_HANDLE"</td>         <td>The handle is not a valid oscilloscope handle.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_OBJECT_GONE "OBJECT_GONE"</td>            <td>The object indicated by the handle is no longer available.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_LIBRARY_NOT_INITIALIZED "LIBRARY_NOT_INITIALIZED"</td><td>The library is not initialized, see LibInit().</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_SUCCESS "SUCCESS"</td>                <td>The function executed successfully.</td></tr>
 *   </table>
 * \remark Setting the range will disable auto ranging if enabled.
 * \remark Changing the input range may affect the \ref scp_ch_tr_level "trigger level(s)" if the \ref ScpChTrGetLevelMode "trigger level mode" is #TLM_ABSOLUTE.
 *
 * \par Example
 * \code{.c}
 * double dRange = 10;
 *
 * dRange = ScpChSetRange( hDevice , wCh , dRange );
 *
 * printf( "ScpChSetRange = %f" , dRange );
 * \endcode
 *
 * \see ScpChGetRanges
 * \see ScpChGetRange
 * \since 0.4.0
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef double(*LibTiePieScpChSetRange_t)( LibTiePieHandle_t hDevice , uint16_t wCh , double dRange );
#else
double ScpChSetRange( LibTiePieHandle_t hDevice , uint16_t wCh , double dRange );
#endif

/**
 * \}
 * \defgroup scp_ch_safe_ground SafeGround
 * \{
 * \brief Functions to control the SafeGround feature of an oscilloscope channel.
 *
 *           SafeGround is a system that connects the negative side of an oscilloscope input to the oscilloscope's ground and
 *           real time monitors the ground current of that input.
 *           This turns a differential input into a single ended input.
 *           When the ground current exceeds a selected value, the ground connection of the input is immediately opened,
 *           avoiding that the ground current becomes too large and causes damage.
 *
 *           An event can be generated to inform that the ground was disconnected, #LIBTIEPIE_EVENTID_SCP_SAFEGROUNDERROR.
 *           See also \ref obj_notifications "Notifications".
 *
 *           SafeGround is not available for all instruments.
 *           Use ScpChHasSafeGround() to check whether SafeGround is available for your instrument.
 *
 *           By default SafeGround is disabled and the threshold current is set to 30 mA.
 */

// Workaround: Without this line Doxygen adds the documentation below to the group above.

/**
 * \brief Check whether the specified channel has SafeGround.
 *
 * \param[in] hDevice A \ref OpenDev "device handle" identifying the oscilloscope.
 * \param[in] wCh The channel number identifying the channel, \c 0 to <tt>ScpGetChannelCount() - 1</tt>.
 * \return #BOOL8_TRUE if SafeGround is available, #BOOL8_FALSE otherwise.
 * \par Status values
 *   <table class="params">
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_CHANNEL "INVALID_CHANNEL"</td>        <td>The requested channel number is invalid.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_HANDLE "INVALID_HANDLE"</td>         <td>The handle is not a valid oscilloscope handle.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_OBJECT_GONE "OBJECT_GONE"</td>            <td>The object indicated by the handle is no longer available.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_LIBRARY_NOT_INITIALIZED "LIBRARY_NOT_INITIALIZED"</td><td>The library is not initialized, see LibInit().</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_SUCCESS "SUCCESS"</td>                <td>The function executed successfully.</td></tr>
 *   </table>
 * \since 0.6
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef bool8_t(*LibTiePieScpChHasSafeGround_t)( LibTiePieHandle_t hDevice , uint16_t wCh );
#else
bool8_t ScpChHasSafeGround( LibTiePieHandle_t hDevice , uint16_t wCh );
#endif

/**
 * \brief Check whether SafeGround is enabled for a specified channel.
 *
 * \param[in] hDevice A \ref OpenDev "device handle" identifying the oscilloscope.
 * \param[in] wCh The channel number identifying the channel, \c 0 to <tt>ScpGetChannelCount() - 1</tt>.
 * \return #BOOL8_TRUE if SafeGround is enabled, #BOOL8_FALSE otherwise.
 * \par Status values
 *   <table class="params">
 *   <tr><td>\ref LIBTIEPIESTATUS_NOT_SUPPORTED "NOT_SUPPORTED"</td>          <td>The indicated channel does not have SafeGround.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_CHANNEL "INVALID_CHANNEL"</td>        <td>The requested channel number is invalid.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_HANDLE "INVALID_HANDLE"</td>         <td>The handle is not a valid oscilloscope handle.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_OBJECT_GONE "OBJECT_GONE"</td>            <td>The object indicated by the handle is no longer available.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_LIBRARY_NOT_INITIALIZED "LIBRARY_NOT_INITIALIZED"</td><td>The library is not initialized, see LibInit().</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_SUCCESS "SUCCESS"</td>                <td>The function executed successfully.</td></tr>
 *   </table>
 * \see ScpChHasSafeGround
 * \see ScpChSetSafeGroundEnabled
 * \since 0.6
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef bool8_t(*LibTiePieScpChGetSafeGroundEnabled_t)( LibTiePieHandle_t hDevice , uint16_t wCh );
#else
bool8_t ScpChGetSafeGroundEnabled( LibTiePieHandle_t hDevice , uint16_t wCh );
#endif

/**
 * \brief Enable or disable SafeGround for a specified channel.
 *
 * When a SsfeGround is enabled and a ground current larger than the selected current threahold starts flowing,
 * SafeGround is immediately disabled by the instrument. Remove the (wrong) ground connection before enabling SafeGround.
 *
 * SafeGround can only be enabled or disabled when the scope is not performing a measurement.
 *
 * \param[in] hDevice A \ref OpenDev "device handle" identifying the oscilloscope.
 * \param[in] wCh The channel number identifying the channel, \c 0 to <tt>ScpGetChannelCount() - 1</tt>.
 * \param[in] bEnable #BOOL8_TRUE to enable SafeGround or #BOOL8_FALSE to disable SafeGround.
 * \return #BOOL8_TRUE if SafeGround is enabled, #BOOL8_FALSE otherwise.
 * \par Status values
 *   <table class="params">
 *   <tr><td>\ref LIBTIEPIESTATUS_UNSUCCESSFUL "UNSUCCESSFUL"</td>           <td>A ground current larger than the selected threshold caused SafeGround to be disabled again, or the scope is measuring.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_NOT_SUPPORTED "NOT_SUPPORTED"</td>          <td>The indicated channel does not have SafeGround.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_CHANNEL "INVALID_CHANNEL"</td>        <td>The requested channel number is invalid.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_HANDLE "INVALID_HANDLE"</td>         <td>The handle is not a valid oscilloscope handle.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_OBJECT_GONE "OBJECT_GONE"</td>            <td>The object indicated by the handle is no longer available.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_LIBRARY_NOT_INITIALIZED "LIBRARY_NOT_INITIALIZED"</td><td>The library is not initialized, see LibInit().</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_SUCCESS "SUCCESS"</td>                <td>The function executed successfully.</td></tr>
 *   </table>
 * \see ScpChHasSafeGround
 * \see ScpChGetSafeGroundEnabled
 * \since 0.6
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef bool8_t(*LibTiePieScpChSetSafeGroundEnabled_t)( LibTiePieHandle_t hDevice , uint16_t wCh , bool8_t bEnable );
#else
bool8_t ScpChSetSafeGroundEnabled( LibTiePieHandle_t hDevice , uint16_t wCh , bool8_t bEnable );
#endif

/**
 * \brief Get the minimum SafeGround threshold current for the specified channel.
 *
 * \param[in] hDevice A \ref OpenDev "device handle" identifying the oscilloscope.
 * \param[in] wCh The channel number identifying the channel, \c 0 to <tt>ScpGetChannelCount() - 1</tt>.
 * \return Minimum SafeGround threshold current, in Ampere.
 * \par Status values
 *   <table class="params">
 *   <tr><td>\ref LIBTIEPIESTATUS_NOT_SUPPORTED "NOT_SUPPORTED"</td>          <td>The indicated channel does not have SafeGround.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_CHANNEL "INVALID_CHANNEL"</td>        <td>The requested channel number is invalid.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_HANDLE "INVALID_HANDLE"</td>         <td>The handle is not a valid oscilloscope handle.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_OBJECT_GONE "OBJECT_GONE"</td>            <td>The object indicated by the handle is no longer available.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_LIBRARY_NOT_INITIALIZED "LIBRARY_NOT_INITIALIZED"</td><td>The library is not initialized, see LibInit().</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_SUCCESS "SUCCESS"</td>                <td>The function executed successfully.</td></tr>
 *   </table>
 * \see ScpChHasSafeGround
 * \see ScpChGetSafeGroundThresholdMax
 * \see ScpChGetSafeGroundThreshold
 * \see ScpChSetSafeGroundThreshold
 * \since 0.6
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef double(*LibTiePieScpChGetSafeGroundThresholdMin_t)( LibTiePieHandle_t hDevice , uint16_t wCh );
#else
double ScpChGetSafeGroundThresholdMin( LibTiePieHandle_t hDevice , uint16_t wCh );
#endif

/**
 * \brief Get the maximum SafeGround threshold current for the specified channel.
 *
 * \param[in] hDevice A \ref OpenDev "device handle" identifying the oscilloscope.
 * \param[in] wCh The channel number identifying the channel, \c 0 to <tt>ScpGetChannelCount() - 1</tt>.
 * \return Maximum SafeGround threshold current, in Ampere.
 * \par Status values
 *   <table class="params">
 *   <tr><td>\ref LIBTIEPIESTATUS_NOT_SUPPORTED "NOT_SUPPORTED"</td>          <td>The indicated channel does not have SafeGround.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_CHANNEL "INVALID_CHANNEL"</td>        <td>The requested channel number is invalid.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_HANDLE "INVALID_HANDLE"</td>         <td>The handle is not a valid oscilloscope handle.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_OBJECT_GONE "OBJECT_GONE"</td>            <td>The object indicated by the handle is no longer available.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_LIBRARY_NOT_INITIALIZED "LIBRARY_NOT_INITIALIZED"</td><td>The library is not initialized, see LibInit().</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_SUCCESS "SUCCESS"</td>                <td>The function executed successfully.</td></tr>
 *   </table>
 * \see ScpChHasSafeGround
 * \see ScpChGetSafeGroundThresholdMin
 * \see ScpChGetSafeGroundThreshold
 * \see ScpChSetSafeGroundThreshold
 * \since 0.6
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef double(*LibTiePieScpChGetSafeGroundThresholdMax_t)( LibTiePieHandle_t hDevice , uint16_t wCh );
#else
double ScpChGetSafeGroundThresholdMax( LibTiePieHandle_t hDevice , uint16_t wCh );
#endif

/**
 * \brief Get the actual SafeGround threshold current for the specified channel.
 *
 * \param[in] hDevice A \ref OpenDev "device handle" identifying the oscilloscope.
 * \param[in] wCh The channel number identifying the channel, \c 0 to <tt>ScpGetChannelCount() - 1</tt>.
 * \return The currently set SafeGround threshold current, in Ampere.
 * \par Status values
 *   <table class="params">
 *   <tr><td>\ref LIBTIEPIESTATUS_NOT_SUPPORTED "NOT_SUPPORTED"</td>          <td>The indicated channel does not have SafeGround.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_CHANNEL "INVALID_CHANNEL"</td>        <td>The requested channel number is invalid.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_HANDLE "INVALID_HANDLE"</td>         <td>The handle is not a valid oscilloscope handle.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_OBJECT_GONE "OBJECT_GONE"</td>            <td>The object indicated by the handle is no longer available.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_LIBRARY_NOT_INITIALIZED "LIBRARY_NOT_INITIALIZED"</td><td>The library is not initialized, see LibInit().</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_SUCCESS "SUCCESS"</td>                <td>The function executed successfully.</td></tr>
 *   </table>
 * \see ScpChHasSafeGround
 * \see ScpChGetSafeGroundThresholdMin
 * \see ScpChGetSafeGroundThresholdMax
 * \see ScpChSetSafeGroundThreshold
 * \since 0.6
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef double(*LibTiePieScpChGetSafeGroundThreshold_t)( LibTiePieHandle_t hDevice , uint16_t wCh );
#else
double ScpChGetSafeGroundThreshold( LibTiePieHandle_t hDevice , uint16_t wCh );
#endif

/**
 * \brief Set the SafeGround threshold current for the specified channel.
 *
 * The SafeGround threshold can only be set when the scope is not performing a measurement.
 *
 * \param[in] hDevice A \ref OpenDev "device handle" identifying the oscilloscope.
 * \param[in] wCh The channel number identifying the channel, \c 0 to <tt>ScpGetChannelCount() - 1</tt>.
 * \param[in] dThreshold The required threshold current, in Ampere.
 * \return The actual set SafeGround threshold current, in Ampere.
 * \par Status values
 *   <table class="params">
 *   <tr><td>\ref LIBTIEPIESTATUS_VALUE_MODIFIED "VALUE_MODIFIED"</td>         <td>The requested threshold current is within the valid range, but not available. The closest valid value is set.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_VALUE_CLIPPED "VALUE_CLIPPED"</td>          <td>The requested threshold current is outside the valid range and clipped to the closest limit.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_VALUE "INVALID_VALUE"</td>          <td>The requested value is invalid.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_UNSUCCESSFUL "UNSUCCESSFUL"</td>           <td>The scope is measuring.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_NOT_SUPPORTED "NOT_SUPPORTED"</td>          <td>The indicated channel does not have SafeGround.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_CHANNEL "INVALID_CHANNEL"</td>        <td>The requested channel number is invalid.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_HANDLE "INVALID_HANDLE"</td>         <td>The handle is not a valid oscilloscope handle.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_OBJECT_GONE "OBJECT_GONE"</td>            <td>The object indicated by the handle is no longer available.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_LIBRARY_NOT_INITIALIZED "LIBRARY_NOT_INITIALIZED"</td><td>The library is not initialized, see LibInit().</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_SUCCESS "SUCCESS"</td>                <td>The function executed successfully.</td></tr>
 *   </table>
 * \see ScpChHasSafeGround
 * \see ScpChGetSafeGroundThresholdMin
 * \see ScpChGetSafeGroundThresholdMax
 * \see ScpChGetSafeGroundThreshold
 * \since 0.6
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef double(*LibTiePieScpChSetSafeGroundThreshold_t)( LibTiePieHandle_t hDevice , uint16_t wCh , double dThreshold );
#else
double ScpChSetSafeGroundThreshold( LibTiePieHandle_t hDevice , uint16_t wCh , double dThreshold );
#endif

//! \cond EXTENDED_API

/**
 * \brief Verify if the required threshold current for a specified channel can be set.
 *
 * \param[in] hDevice A \ref OpenDev "device handle" identifying the oscilloscope.
 * \param[in] wCh The channel number identifying the channel, \c 0 to <tt>ScpGetChannelCount() - 1</tt>.
 * \param[in] dThreshold The required threshold current, in Ampere.
 * \return The SafeGround threshold current that would be set.
 * \since 0.6
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef double(*LibTiePieScpChVerifySafeGroundThreshold_t)( LibTiePieHandle_t hDevice , uint16_t wCh , double dThreshold );
#else
double ScpChVerifySafeGroundThreshold( LibTiePieHandle_t hDevice , uint16_t wCh , double dThreshold );
#endif

//! \endcond

/**
 * \}
 * \defgroup scp_ch_tr Trigger
 * \{
 * \brief Functions to control the trigger settings of an input channel.
 *
 *            Depending on the settings of the oscilloscope, a channel trigger may not be supported or temporarily unavailable.
 *            In streaming \ref scp_measurements_mode "measure mode", channel trigger is not supported,
 *            use ScpChHasTrigger() to check if triggering is supported in the currently set measure mode.
 *            When channel trigger is supported, it can be temporarily unavailable due to other settings like e.g. sample frequency,
 *            resolution and/or the number of enabled channels, use ScpChTrIsAvailable() to check if the trigger is available.
 *
 *            To use a channel as trigger source, the channel must be \ref scp_ch_enabled "enabled".
 */

// Workaround: Without this line Doxygen adds the documentation below to the group above.

/**
 * \brief Check whether the specified channel has trigger support with the currently selected \ref scp_measurements_mode "measure mode".
 *
 * \param[in] hDevice A \ref OpenDev "device handle" identifying the oscilloscope.
 * \param[in] wCh The channel number identifying the channel, \c 0 to <tt>ScpGetChannelCount() - 1</tt>.
 * \return #BOOL8_TRUE if the channel has trigger support, #BOOL8_FALSE otherwise.
 * \par Status values
 *   <table class="params">
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_CHANNEL "INVALID_CHANNEL"</td>        <td>The requested channel number is invalid.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_HANDLE "INVALID_HANDLE"</td>         <td>The handle is not a valid oscilloscope handle.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_OBJECT_GONE "OBJECT_GONE"</td>            <td>The object indicated by the handle is no longer available.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_LIBRARY_NOT_INITIALIZED "LIBRARY_NOT_INITIALIZED"</td><td>The library is not initialized, see LibInit().</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_SUCCESS "SUCCESS"</td>                <td>The function executed successfully.</td></tr>
 *   </table>
 * \since 0.4.2
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef bool8_t(*LibTiePieScpChHasTrigger_t)( LibTiePieHandle_t hDevice , uint16_t wCh );
#else
bool8_t ScpChHasTrigger( LibTiePieHandle_t hDevice , uint16_t wCh );
#endif

//! \cond EXTENDED_API

/**
 * \brief Check whether the specified channel has trigger support, for a specific configuration.
 *
 * \param[in] hDevice A \ref OpenDev "device handle" identifying the oscilloscope.
 * \param[in] wCh The channel number identifying the channel, \c 0 to <tt>ScpGetChannelCount() - 1</tt>.
 * \param[in] dwMeasureMode Measure mode, a \ref MM_ "MM_*" value.
 * \return #BOOL8_TRUE if the channel has trigger support, #BOOL8_FALSE otherwise.
 * \par Status values
 *   <table class="params">
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_VALUE "INVALID_VALUE"</td>          <td>The requested value is invalid.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_CHANNEL "INVALID_CHANNEL"</td>        <td>The requested channel number is invalid.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_HANDLE "INVALID_HANDLE"</td>         <td>The handle is not a valid oscilloscope handle.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_OBJECT_GONE "OBJECT_GONE"</td>            <td>The object indicated by the handle is no longer available.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_LIBRARY_NOT_INITIALIZED "LIBRARY_NOT_INITIALIZED"</td><td>The library is not initialized, see LibInit().</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_SUCCESS "SUCCESS"</td>                <td>The function executed successfully.</td></tr>
 *   </table>
 * \since 0.5
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef bool8_t(*LibTiePieScpChHasTriggerEx_t)( LibTiePieHandle_t hDevice , uint16_t wCh , uint32_t dwMeasureMode );
#else
bool8_t ScpChHasTriggerEx( LibTiePieHandle_t hDevice , uint16_t wCh , uint32_t dwMeasureMode );
#endif

//! \endcond

/**
 * \brief Check whether the channel trigger for the specified channel is available, with the current oscilloscope settings.
 *
 * \param[in] hDevice A \ref OpenDev "device handle" identifying the oscilloscope.
 * \param[in] wCh The channel number identifying the channel, \c 0 to <tt>ScpGetChannelCount() - 1</tt>.
 * \return #BOOL8_TRUE if available, #BOOL8_FALSE otherwise.
 * \par Status values
 *   <table class="params">
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_CHANNEL "INVALID_CHANNEL"</td>        <td>The requested channel number is invalid.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_HANDLE "INVALID_HANDLE"</td>         <td>The handle is not a valid oscilloscope handle.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_OBJECT_GONE "OBJECT_GONE"</td>            <td>The object indicated by the handle is no longer available.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_LIBRARY_NOT_INITIALIZED "LIBRARY_NOT_INITIALIZED"</td><td>The library is not initialized, see LibInit().</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_SUCCESS "SUCCESS"</td>                <td>The function executed successfully.</td></tr>
 *   </table>
 * \since 0.4.4
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef bool8_t(*LibTiePieScpChTrIsAvailable_t)( LibTiePieHandle_t hDevice , uint16_t wCh );
#else
bool8_t ScpChTrIsAvailable( LibTiePieHandle_t hDevice , uint16_t wCh );
#endif

//! \cond EXTENDED_API

/**
 * \brief Check whether the channel trigger is available, for a specific configuration.
 *
 * \param[in] hDevice A \ref OpenDev "device handle" identifying the oscilloscope.
 * \param[in] wCh The channel number identifying the channel, \c 0 to <tt>ScpGetChannelCount() - 1</tt>.
 * \param[in] dwMeasureMode Measure mode, a \ref MM_ "MM_*" value.
 * \param[in] dSampleFrequency SampleFrequency in Hz.
 * \param[in] byResolution Resolution in bits.
 * \param[in] pChannelEnabled Pointer to buffer with channel enables.
 * \param[in] pChannelTriggerEnabled  Pointer to buffer with channel trigger enables.
 * \param[in] wChannelCount Number of items in \c pChannelEnabled and \c pChannelTriggerEnabled.
 * \return #BOOL8_TRUE if available, #BOOL8_FALSE otherwise.
 * \since 0.4.4
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef bool8_t(*LibTiePieScpChTrIsAvailableEx_t)( LibTiePieHandle_t hDevice , uint16_t wCh , uint32_t dwMeasureMode , double dSampleFrequency , uint8_t byResolution , const bool8_t* pChannelEnabled , const bool8_t* pChannelTriggerEnabled , uint16_t wChannelCount );
#else
bool8_t ScpChTrIsAvailableEx( LibTiePieHandle_t hDevice , uint16_t wCh , uint32_t dwMeasureMode , double dSampleFrequency , uint8_t byResolution , const bool8_t* pChannelEnabled , const bool8_t* pChannelTriggerEnabled , uint16_t wChannelCount );
#endif

//! \endcond

/**
 * \brief Check whether the channel trigger caused a trigger.
 *
 * \param[in] hDevice A \ref OpenDev "device handle" identifying the oscilloscope.
 * \param[in] wCh The channel number identifying the channel, \c 0 to <tt>ScpGetChannelCount() - 1</tt>.
 * \return #BOOL8_TRUE if the channel trigger caused a trigger, #BOOL8_FALSE otherwise.
 * \see ScpIsTriggered
 * \see ScpIsTimeOutTriggered
 * \see ScpIsForceTriggered
 * \see ScpTrInIsTriggered
 * \since 0.5
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef bool8_t(*LibTiePieScpChTrIsTriggered_t)( LibTiePieHandle_t hDevice , uint16_t wCh );
#else
bool8_t ScpChTrIsTriggered( LibTiePieHandle_t hDevice , uint16_t wCh );
#endif

/**
 * \defgroup scp_ch_tr_enabled Enabled
 * \{
 * \brief The enabled state of a channel trigger determines whether a channel is selected as trigger source.
 *
 *             Channel triggers of multiple channels can be enabled, in that case they will be OR'ed.
 *
 *             The enabled state can be affected by changing the \ref scp_ch_enabled "channel enable", \ref scp_timebase_sampleFrequency "sample frequency" and/or \ref scp_resolution "resolution".
 *
 *             By default channel 1 is enabled, all other channels are disabled.
 */

// Workaround: Without this line Doxygen adds the documentation below to the group above.

/**
 * \brief Check whether channel trigger for a specified channel is enabled.
 *
 * \param[in] hDevice A \ref OpenDev "device handle" identifying the oscilloscope.
 * \param[in] wCh The channel number identifying the channel, \c 0 to <tt>ScpGetChannelCount() - 1</tt>.
 * \return #BOOL8_TRUE if enabled, #BOOL8_FALSE otherwise.
 * \par Status values
 *   <table class="params">
 *   <tr><td>\ref LIBTIEPIESTATUS_NOT_SUPPORTED "NOT_SUPPORTED"</td>          <td>The indicated channel does not support trigger with the current settings.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_CHANNEL "INVALID_CHANNEL"</td>        <td>The requested channel number is invalid.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_HANDLE "INVALID_HANDLE"</td>         <td>The handle is not a valid oscilloscope handle.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_OBJECT_GONE "OBJECT_GONE"</td>            <td>The object indicated by the handle is no longer available.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_LIBRARY_NOT_INITIALIZED "LIBRARY_NOT_INITIALIZED"</td><td>The library is not initialized, see LibInit().</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_SUCCESS "SUCCESS"</td>                <td>The function executed successfully.</td></tr>
 *   </table>
 * \see ScpChTrSetEnabled
 * \since 0.4.2
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef bool8_t(*LibTiePieScpChTrGetEnabled_t)( LibTiePieHandle_t hDevice , uint16_t wCh );
#else
bool8_t ScpChTrGetEnabled( LibTiePieHandle_t hDevice , uint16_t wCh );
#endif

/**
 * \brief To select a channel as trigger source, set channel trigger enable.
 *
 * \param[in] hDevice A \ref OpenDev "device handle" identifying the oscilloscope.
 * \param[in] wCh The channel number identifying the channel, \c 0 to <tt>ScpGetChannelCount() - 1</tt>.
 * \param[in] bEnable #BOOL8_TRUE or #BOOL8_FALSE.
 * \return #BOOL8_TRUE if enabled, #BOOL8_FALSE otherwise.
 * \par Status values
 *   <table class="params">
 *   <tr><td>\ref LIBTIEPIESTATUS_NOT_AVAILABLE "NOT_AVAILABLE"</td>          <td>With the current settings, the requested functionality is not available.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_NOT_SUPPORTED "NOT_SUPPORTED"</td>          <td>The indicated channel does not support trigger with the current settings.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_CHANNEL "INVALID_CHANNEL"</td>        <td>The requested channel number is invalid.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_HANDLE "INVALID_HANDLE"</td>         <td>The handle is not a valid oscilloscope handle.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_OBJECT_GONE "OBJECT_GONE"</td>            <td>The object indicated by the handle is no longer available.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_LIBRARY_NOT_INITIALIZED "LIBRARY_NOT_INITIALIZED"</td><td>The library is not initialized, see LibInit().</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_SUCCESS "SUCCESS"</td>                <td>The function executed successfully.</td></tr>
 *   </table>
 * \remark Enabling the channel trigger may change the \ref scp_ch_range "input range" if \ref ScpChTrGetLevelMode "trigger level mode" is #TLM_ABSOLUTE and \ref ScpChGetAutoRanging "auto ranging" is enabled.
 * \see ScpChTrGetEnabled
 * \since 0.4.2
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef bool8_t(*LibTiePieScpChTrSetEnabled_t)( LibTiePieHandle_t hDevice , uint16_t wCh , bool8_t bEnable );
#else
bool8_t ScpChTrSetEnabled( LibTiePieHandle_t hDevice , uint16_t wCh , bool8_t bEnable );
#endif

/**
 * \}
 * \defgroup scp_ch_tr_kind Kind
 * \{
 * \brief The channel trigger kind property is used to control how the channel trigger responds to the channel input signal.
 *
 *             Use ScpChTrGetKinds() to find out which trigger kinds are supported by the channel.
 *             Depending on the selected trigger kind, other properties like e.g. level(s) and hysteresis are available to configure the
 *             channel trigger. Read more on \ref triggering_scpch_kind "trigger kind".
 *
 *             By default kind is set to rising edge (#TK_RISINGEDGE).
 */

// Workaround: Without this line Doxygen adds the documentation below to the group above.

/**
 * \brief Get the supported channel trigger kinds for a specified channel with the currently selected \ref scp_measurements_mode "measure mode".
 *
 * \param[in] hDevice A \ref OpenDev "device handle" identifying the oscilloscope.
 * \param[in] wCh The channel number identifying the channel, \c 0 to <tt>ScpGetChannelCount() - 1</tt>.
 * \return The supported trigger kinds, a set of OR-ed \ref TK_ "TK_*" values or #TKM_NONE if the channel has no trigger support.
 * \par Status values
 *   <table class="params">
 *   <tr><td>\ref LIBTIEPIESTATUS_NOT_SUPPORTED "NOT_SUPPORTED"</td>          <td>The indicated channel does not support trigger with the current settings.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_CHANNEL "INVALID_CHANNEL"</td>        <td>The requested channel number is invalid.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_HANDLE "INVALID_HANDLE"</td>         <td>The handle is not a valid oscilloscope handle.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_OBJECT_GONE "OBJECT_GONE"</td>            <td>The object indicated by the handle is no longer available.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_LIBRARY_NOT_INITIALIZED "LIBRARY_NOT_INITIALIZED"</td><td>The library is not initialized, see LibInit().</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_SUCCESS "SUCCESS"</td>                <td>The function executed successfully.</td></tr>
 *   </table>
 * \see ScpChTrGetKind
 * \see ScpChTrSetKind
 * \since 0.4.1
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef uint64_t(*LibTiePieScpChTrGetKinds_t)( LibTiePieHandle_t hDevice , uint16_t wCh );
#else
uint64_t ScpChTrGetKinds( LibTiePieHandle_t hDevice , uint16_t wCh );
#endif

//! \cond EXTENDED_API

/**
 * \brief Get the supported channel trigger kinds for a specified channel, for a specific \ref scp_measurements_mode "measure mode".
 *
 * \param[in] hDevice A \ref OpenDev "device handle" identifying the oscilloscope.
 * \param[in] wCh The channel number identifying the channel, \c 0 to <tt>ScpGetChannelCount() - 1</tt>.
 * \param[in] dwMeasureMode Measure mode, a \ref MM_ "MM_*" value.
 * \return Supported trigger kinds, a set of OR-ed \ref TK_ "TK_*" values.
 * \since 0.4.1
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef uint64_t(*LibTiePieScpChTrGetKindsEx_t)( LibTiePieHandle_t hDevice , uint16_t wCh , uint32_t dwMeasureMode );
#else
uint64_t ScpChTrGetKindsEx( LibTiePieHandle_t hDevice , uint16_t wCh , uint32_t dwMeasureMode );
#endif

//! \endcond

/**
 * \brief Get the currently selected channel trigger kind for a specified channel.
 *
 * \param[in] hDevice A \ref OpenDev "device handle" identifying the oscilloscope.
 * \param[in] wCh The channel number identifying the channel, \c 0 to <tt>ScpGetChannelCount() - 1</tt>.
 * \return The current trigger kind, a \ref TK_ "TK_*" value.
 * \par Status values
 *   <table class="params">
 *   <tr><td>\ref LIBTIEPIESTATUS_NOT_SUPPORTED "NOT_SUPPORTED"</td>          <td>The indicated channel does not support trigger with the current settings.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_CHANNEL "INVALID_CHANNEL"</td>        <td>The requested channel number is invalid.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_HANDLE "INVALID_HANDLE"</td>         <td>The handle is not a valid oscilloscope handle.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_OBJECT_GONE "OBJECT_GONE"</td>            <td>The object indicated by the handle is no longer available.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_LIBRARY_NOT_INITIALIZED "LIBRARY_NOT_INITIALIZED"</td><td>The library is not initialized, see LibInit().</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_SUCCESS "SUCCESS"</td>                <td>The function executed successfully.</td></tr>
 *   </table>
 * \see ScpChTrGetKinds
 * \see ScpChTrSetKind
 * \since 0.4.1
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef uint64_t(*LibTiePieScpChTrGetKind_t)( LibTiePieHandle_t hDevice , uint16_t wCh );
#else
uint64_t ScpChTrGetKind( LibTiePieHandle_t hDevice , uint16_t wCh );
#endif

/**
 * \brief Set the channel trigger kind for a specified channel.
 *
 * \param[in] hDevice A \ref OpenDev "device handle" identifying the oscilloscope.
 * \param[in] wCh The channel number identifying the channel, \c 0 to <tt>ScpGetChannelCount() - 1</tt>.
 * \param[in] qwTriggerKind The required trigger kind: a \ref TK_ "TK_*" value.
 * \return The actually set trigger kind, a \ref TK_ "TK_*" value.
 * \par Status values
 *   <table class="params">
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_VALUE "INVALID_VALUE"</td>          <td>The requested trigger kind is invalid.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_NOT_SUPPORTED "NOT_SUPPORTED"</td>          <td>The indicated channel does not support trigger with the current settings.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_CHANNEL "INVALID_CHANNEL"</td>        <td>The requested channel number is invalid.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_HANDLE "INVALID_HANDLE"</td>         <td>The handle is not a valid oscilloscope handle.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_OBJECT_GONE "OBJECT_GONE"</td>            <td>The object indicated by the handle is no longer available.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_LIBRARY_NOT_INITIALIZED "LIBRARY_NOT_INITIALIZED"</td><td>The library is not initialized, see LibInit().</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_SUCCESS "SUCCESS"</td>                <td>The function executed successfully.</td></tr>
 *   </table>
 * \remark Changing the channel trigger kind may change the \ref scp_ch_range "input range" if the \ref ScpChTrGetEnabled "channel trigger" is enabled, \ref ScpChTrGetLevelMode "trigger level mode" is #TLM_ABSOLUTE and \ref ScpChGetAutoRanging "auto ranging" is enabled.
 * \see ScpChTrGetKinds
 * \see ScpChTrGetKind
 * \since 0.4.1
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef uint64_t(*LibTiePieScpChTrSetKind_t)( LibTiePieHandle_t hDevice , uint16_t wCh , uint64_t qwTriggerKind );
#else
uint64_t ScpChTrSetKind( LibTiePieHandle_t hDevice , uint16_t wCh , uint64_t qwTriggerKind );
#endif

/**
 * \}
 * \defgroup scp_ch_tr_level_mode Level mode
 * \{
 * \brief Functions for controlling the trigger level mode.
 *
 *             The trigger level can be set in two different ways, indicated by the trigger level mode:
 *             - #TLM_RELATIVE, the trigger level is set as a floating point value between 0 and 1, corresponding to a percentage of the full scale \ref scp_ch_range "input range".
 *             - #TLM_ABSOLUTE, the trigger level is set as a floating point value, clipped by the full scale \ref scp_ch_range "input range".
 *
 *             When trigger level mode is set to #TLM_RELATIVE and \ref scp_ch_range "auto ranging" of the channel is enabled, the trigger level will remain at the same
 *             percentage when the input range changes, resulting in a different absolute voltage.
 *
 *             When trigger level mode is set to #TLM_ABSOLUTE and auto ranging of the channel is enabled, the trigger level will remain at the same
 *             absolute voltage level when the input range changes. The input range will not auto range to a range that is smaller than the selected
 *             trigger level.
 *
 *             By default the trigger level mode is set to #TLM_RELATIVE.
 */

// Workaround: Without this line Doxygen adds the documentation below to the group above.

/**
 * \brief Get the supported trigger level modes of a specified channel.
 *
 * \param[in] hDevice A \ref OpenDev "device handle" identifying the oscilloscope.
 * \param[in] wCh The channel number identifying the channel, \c 0 to <tt>ScpGetChannelCount() - 1</tt>.
 * \return The supported trigger level modes, a set of OR-ed \ref TLM_ "TLM_*" values or #TLMM_NONE when unsuccessful.
 * \par Status values
 *   <table class="params">
 *   <tr><td>\ref LIBTIEPIESTATUS_NOT_SUPPORTED "NOT_SUPPORTED"</td>          <td>The indicated channel does not support trigger with the current settings.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_CHANNEL "INVALID_CHANNEL"</td>        <td>The requested channel number is invalid.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_HANDLE "INVALID_HANDLE"</td>         <td>The handle is not a valid oscilloscope handle.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_OBJECT_GONE "OBJECT_GONE"</td>            <td>The object indicated by the handle is no longer available.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_LIBRARY_NOT_INITIALIZED "LIBRARY_NOT_INITIALIZED"</td><td>The library is not initialized, see LibInit().</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_SUCCESS "SUCCESS"</td>                <td>The function executed successfully.</td></tr>
 *   </table>
 * \since 0.6
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef uint32_t(*LibTiePieScpChTrGetLevelModes_t)( LibTiePieHandle_t hDevice , uint16_t wCh );
#else
uint32_t ScpChTrGetLevelModes( LibTiePieHandle_t hDevice , uint16_t wCh );
#endif

/**
 * \brief Get the current trigger level mode of a specified channel.
 *
 * \param[in] hDevice A \ref OpenDev "device handle" identifying the oscilloscope.
 * \param[in] wCh The channel number identifying the channel, \c 0 to <tt>ScpGetChannelCount() - 1</tt>.
 * \return The curretly set trigger level mode, a \ref TLM_ "TLM_*" value, or #TLMM_NONE when unsuccessful.
 * \par Status values
 *   <table class="params">
 *   <tr><td>\ref LIBTIEPIESTATUS_NOT_SUPPORTED "NOT_SUPPORTED"</td>          <td>The indicated channel does not support trigger with the current settings.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_CHANNEL "INVALID_CHANNEL"</td>        <td>The requested channel number is invalid.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_HANDLE "INVALID_HANDLE"</td>         <td>The handle is not a valid oscilloscope handle.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_OBJECT_GONE "OBJECT_GONE"</td>            <td>The object indicated by the handle is no longer available.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_LIBRARY_NOT_INITIALIZED "LIBRARY_NOT_INITIALIZED"</td><td>The library is not initialized, see LibInit().</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_SUCCESS "SUCCESS"</td>                <td>The function executed successfully.</td></tr>
 *   </table>
 * \since 0.6
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef uint32_t(*LibTiePieScpChTrGetLevelMode_t)( LibTiePieHandle_t hDevice , uint16_t wCh );
#else
uint32_t ScpChTrGetLevelMode( LibTiePieHandle_t hDevice , uint16_t wCh );
#endif

/**
 * \brief Set the trigger level mode of a specified channel.
 *
 * \param[in] hDevice A \ref OpenDev "device handle" identifying the oscilloscope.
 * \param[in] wCh The channel number identifying the channel, \c 0 to <tt>ScpGetChannelCount() - 1</tt>.
 * \param[in] dwLevelMode The requested trigger level mode, a \ref TLM_ "TLM_*" value.
 * \return The actually set trigger level mode, a \ref TLM_ "TLM_*" value, or #TLMM_NONE when unsuccessful.
 * \par Status values
 *   <table class="params">
 *   <tr><td>\ref LIBTIEPIESTATUS_NOT_SUPPORTED "NOT_SUPPORTED"</td>          <td>The indicated channel does not support trigger with the current settings.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_VALUE "INVALID_VALUE"</td>          <td>The requested trigger level mode is invalid.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_CHANNEL "INVALID_CHANNEL"</td>        <td>The requested channel number is invalid.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_HANDLE "INVALID_HANDLE"</td>         <td>The handle is not a valid oscilloscope handle.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_OBJECT_GONE "OBJECT_GONE"</td>            <td>The object indicated by the handle is no longer available.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_LIBRARY_NOT_INITIALIZED "LIBRARY_NOT_INITIALIZED"</td><td>The library is not initialized, see LibInit().</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_SUCCESS "SUCCESS"</td>                <td>The function executed successfully.</td></tr>
 *   </table>
 * \since 0.6
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef uint32_t(*LibTiePieScpChTrSetLevelMode_t)( LibTiePieHandle_t hDevice , uint16_t wCh , uint32_t dwLevelMode );
#else
uint32_t ScpChTrSetLevelMode( LibTiePieHandle_t hDevice , uint16_t wCh , uint32_t dwLevelMode );
#endif

/**
 * \}
 * \defgroup scp_ch_tr_level Level
 * \{
 * \brief The channel trigger level property is used to control at which level(s) the channel trigger responds to the channel input signal.
 *
 *             The number of available trigger levels depends on the currently set \ref #scp_ch_tr_kind "trigger kind".
 *             Use ScpChTrGetLevelCount() to determine the number of trigger levels for the currently set trigger kind.
 *
 *             If the \ref scp_trigger_level_mode "trigger level mode" is #TLM_RELATIVE, the trigger level is set as a floating point value between 0 and 1, corresponding to a percentage of the full scale \ref scp_ch_range "input range":
 *             - 0.0 (0%) equals -full scale
 *             - 0.5 (50%) equals mid level or 0 Volt
 *             - 1.0 (100%) equals full scale.
 *
 *             If the \ref scp_trigger_level_mode "trigger level mode" is #TLM_ABSOLUTE, the trigger level is set as a floating point value, clipped by the full scale \ref scp_ch_range "input range".
 *
 *             By default the trigger level is set to 0.5 (50%) of the full-scale range.
 */

// Workaround: Without this line Doxygen adds the documentation below to the group above.

/**
 * \brief Get the number of channel trigger levels for a specified channel with the currently selected \ref ScpChTrGetKind "trigger kind".
 *
 * \param[in] hDevice A \ref OpenDev "device handle" identifying the oscilloscope.
 * \param[in] wCh The channel number identifying the channel, \c 0 to <tt>ScpGetChannelCount() - 1</tt>.
 * \return The number of available trigger levels for the currently set trigger kind.
 * \par Status values
 *   <table class="params">
 *   <tr><td>\ref LIBTIEPIESTATUS_NOT_SUPPORTED "NOT_SUPPORTED"</td>          <td>The indicated channel does not support trigger with the current settings.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_CHANNEL "INVALID_CHANNEL"</td>        <td>The requested channel number is invalid.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_HANDLE "INVALID_HANDLE"</td>         <td>The handle is not a valid oscilloscope handle.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_OBJECT_GONE "OBJECT_GONE"</td>            <td>The object indicated by the handle is no longer available.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_LIBRARY_NOT_INITIALIZED "LIBRARY_NOT_INITIALIZED"</td><td>The library is not initialized, see LibInit().</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_SUCCESS "SUCCESS"</td>                <td>The function executed successfully.</td></tr>
 *   </table>
 * \see ScpChTrGetKind
 * \see ScpChTrGetLevel
 * \see ScpChTrSetLevel
 * \since 0.4.1
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef uint32_t(*LibTiePieScpChTrGetLevelCount_t)( LibTiePieHandle_t hDevice , uint16_t wCh );
#else
uint32_t ScpChTrGetLevelCount( LibTiePieHandle_t hDevice , uint16_t wCh );
#endif

/**
 * \brief Get the currently set channel trigger level value for a specified channel and trigger level.
 *
 * \param[in] hDevice A \ref OpenDev "device handle" identifying the oscilloscope.
 * \param[in] wCh The channel number identifying the channel, \c 0 to <tt>ScpGetChannelCount() - 1</tt>.
 * \param[in] dwIndex The trigger level index, \c 0 to <tt>ScpChTrGetLevelCount() - 1</tt>.
 * \return The currently set trigger level value.
 * \par Status values
 *   <table class="params">
 *   <tr><td>\ref LIBTIEPIESTATUS_NOT_SUPPORTED "NOT_SUPPORTED"</td>          <td>The indicated channel does not support trigger (level) with the current settings.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_INDEX "INVALID_INDEX"</td>          <td>The trigger level index is invalid.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_CHANNEL "INVALID_CHANNEL"</td>        <td>The requested channel number is invalid.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_HANDLE "INVALID_HANDLE"</td>         <td>The handle is not a valid oscilloscope handle.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_OBJECT_GONE "OBJECT_GONE"</td>            <td>The object indicated by the handle is no longer available.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_LIBRARY_NOT_INITIALIZED "LIBRARY_NOT_INITIALIZED"</td><td>The library is not initialized, see LibInit().</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_SUCCESS "SUCCESS"</td>                <td>The function executed successfully.</td></tr>
 *   </table>
 * \see ScpChTrGetLevelCount
 * \see ScpChTrSetLevel
 * \since 0.4.1
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef double(*LibTiePieScpChTrGetLevel_t)( LibTiePieHandle_t hDevice , uint16_t wCh , uint32_t dwIndex );
#else
double ScpChTrGetLevel( LibTiePieHandle_t hDevice , uint16_t wCh , uint32_t dwIndex );
#endif

/**
 * \brief Set the channel trigger level value for a specified channel and trigger level.
 *
 * \param[in] hDevice A \ref OpenDev "device handle" identifying the oscilloscope.
 * \param[in] wCh The channel number identifying the channel, \c 0 to <tt>ScpGetChannelCount() - 1</tt>.
 * \param[in] dwIndex The trigger level index, \c 0 to <tt>ScpChTrGetLevelCount() - 1</tt>.
 * \param[in] dLevel The required trigger level.
 * \return The actually set trigger level.
 * \par Status values
 *   <table class="params">
 *   <tr><td>\ref LIBTIEPIESTATUS_VALUE_CLIPPED "VALUE_CLIPPED"</td>          <td>The requested trigger level is outside the valid range and clipped to the closest limit.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_NOT_SUPPORTED "NOT_SUPPORTED"</td>          <td>The indicated channel does not support trigger (level) with the current settings.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_INDEX "INVALID_INDEX"</td>          <td>The trigger level index is invalid.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_CHANNEL "INVALID_CHANNEL"</td>        <td>The requested channel number is invalid.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_HANDLE "INVALID_HANDLE"</td>         <td>The handle is not a valid oscilloscope handle.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_OBJECT_GONE "OBJECT_GONE"</td>            <td>The object indicated by the handle is no longer available.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_LIBRARY_NOT_INITIALIZED "LIBRARY_NOT_INITIALIZED"</td><td>The library is not initialized, see LibInit().</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_SUCCESS "SUCCESS"</td>                <td>The function executed successfully.</td></tr>
 *   </table>
 * \remark Changing the channel trigger level may change the \ref scp_ch_range "input range" if the \ref ScpChTrGetEnabled "channel trigger" is enabled, \ref ScpGetTriggerLevelMode "trigger level mode" is #TLM_ABSOLUTE and \ref ScpChGetAutoRanging "auto ranging" is enabled.
 * \see ScpChTrGetLevelCount
 * \see ScpChTrGetLevel
 * \since 0.4.1
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef double(*LibTiePieScpChTrSetLevel_t)( LibTiePieHandle_t hDevice , uint16_t wCh , uint32_t dwIndex , double dLevel );
#else
double ScpChTrSetLevel( LibTiePieHandle_t hDevice , uint16_t wCh , uint32_t dwIndex , double dLevel );
#endif

/**
 * \}
 * \defgroup scp_ch_tr_hysteresis Hysteresis
 * \{
 * \brief The channel trigger hysteresis property is used to control the sensitivity of the trigger system.
 *
 *             The number of available trigger hystereses depends on the currently set \ref #scp_ch_tr_kind "trigger kind".
 *             Use ScpChTrGetHysteresisCount() to determine the number of trigger hystereses for the currently set trigger kind.
 *
 *             The trigger hysteresis is set as a floating point value between 0 and 1, corresponding to a percentage of the full scale \ref scp_ch_range "input range":
 *             - 0.0 (0%) equals 0 Volt (no hysteresis)
 *             - 0.5 (50%) equals full scale
 *             - 1.0 (100%) equals 2 * full scale.
 *
 *             By default the trigger hysteresis is set to 0.05 (5%) of the full-scale range.
 */

// Workaround: Without this line Doxygen adds the documentation below to the group above.

/**
 * \brief Get the number of trigger hystereses for a specified channel with the currently selected \ref ScpChTrGetKind "trigger kind".
 *
 * \param[in] hDevice A \ref OpenDev "device handle" identifying the oscilloscope.
 * \param[in] wCh The channel number identifying the channel, \c 0 to <tt>ScpGetChannelCount() - 1</tt>.
 * \return The number of available trigger hystereses for the currently set trigger kind.
 * \par Status values
 *   <table class="params">
 *   <tr><td>\ref LIBTIEPIESTATUS_NOT_SUPPORTED "NOT_SUPPORTED"</td>          <td>The indicated channel does not support trigger with the current settings.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_CHANNEL "INVALID_CHANNEL"</td>        <td>The requested channel number is invalid.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_HANDLE "INVALID_HANDLE"</td>         <td>The handle is not a valid oscilloscope handle.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_OBJECT_GONE "OBJECT_GONE"</td>            <td>The object indicated by the handle is no longer available.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_LIBRARY_NOT_INITIALIZED "LIBRARY_NOT_INITIALIZED"</td><td>The library is not initialized, see LibInit().</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_SUCCESS "SUCCESS"</td>                <td>The function executed successfully.</td></tr>
 *   </table>
 * \see ScpChTrGetKind
 * \see ScpChTrGetHysteresis
 * \see ScpChTrSetHysteresis
 * \since 0.4.1
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef uint32_t(*LibTiePieScpChTrGetHysteresisCount_t)( LibTiePieHandle_t hDevice , uint16_t wCh );
#else
uint32_t ScpChTrGetHysteresisCount( LibTiePieHandle_t hDevice , uint16_t wCh );
#endif

/**
 * \brief Get the currently set channel trigger hysteresis value for a specified channel and trigger hysteresis.
 *
 * \param[in] hDevice A \ref OpenDev "device handle" identifying the oscilloscope.
 * \param[in] wCh The channel number identifying the channel, \c 0 to <tt>ScpGetChannelCount() - 1</tt>.
 * \param[in] dwIndex The trigger hysteresis index, \c 0 to <tt>ScpChTrGetHysteresisCount() - 1</tt>.
 * \return The currently set trigger hysteresis value, a number between \c 0 and \c 1.
 * \par Status values
 *   <table class="params">
 *   <tr><td>\ref LIBTIEPIESTATUS_NOT_SUPPORTED "NOT_SUPPORTED"</td>          <td>The indicated channel does not support trigger (hysteresis) with the current settings.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_INDEX "INVALID_INDEX"</td>          <td>The trigger hysteresis index is invalid.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_CHANNEL "INVALID_CHANNEL"</td>        <td>The requested channel number is invalid.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_HANDLE "INVALID_HANDLE"</td>         <td>The handle is not a valid oscilloscope handle.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_OBJECT_GONE "OBJECT_GONE"</td>            <td>The object indicated by the handle is no longer available.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_LIBRARY_NOT_INITIALIZED "LIBRARY_NOT_INITIALIZED"</td><td>The library is not initialized, see LibInit().</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_SUCCESS "SUCCESS"</td>                <td>The function executed successfully.</td></tr>
 *   </table>
 * \see ScpChTrGetHysteresisCount
 * \see ScpChTrSetHysteresis
 * \since 0.4.1
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef double(*LibTiePieScpChTrGetHysteresis_t)( LibTiePieHandle_t hDevice , uint16_t wCh , uint32_t dwIndex );
#else
double ScpChTrGetHysteresis( LibTiePieHandle_t hDevice , uint16_t wCh , uint32_t dwIndex );
#endif

/**
 * \brief Set the channel trigger hysteresis value for a specified channel and trigger hysteresis.
 *
 * \param[in] hDevice A \ref OpenDev "device handle" identifying the oscilloscope.
 * \param[in] wCh The channel number identifying the channel, \c 0 to <tt>ScpGetChannelCount() - 1</tt>.
 * \param[in] dwIndex The trigger hysteresis index, \c 0 to <tt>ScpChTrGetHysteresisCount() - 1</tt>.
 * \param[in] dHysteresis The required trigger hysteresis value, a number between \c 0 and \c 1.
 * \return The actually set trigger hysteresis value, a number between \c 0 and \c 1.
 * \par Status values
 *   <table class="params">
 *   <tr><td>\ref LIBTIEPIESTATUS_VALUE_CLIPPED "VALUE_CLIPPED"</td>          <td>The requested trigger hysteresis is outside the valid range and clipped to the closest limit.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_NOT_SUPPORTED "NOT_SUPPORTED"</td>          <td>The indicated channel does not support trigger (hysteresis) with the current settings.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_INDEX "INVALID_INDEX"</td>          <td>The trigger hysteresis index is invalid.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_CHANNEL "INVALID_CHANNEL"</td>        <td>The requested channel number is invalid.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_HANDLE "INVALID_HANDLE"</td>         <td>The handle is not a valid oscilloscope handle.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_OBJECT_GONE "OBJECT_GONE"</td>            <td>The object indicated by the handle is no longer available.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_LIBRARY_NOT_INITIALIZED "LIBRARY_NOT_INITIALIZED"</td><td>The library is not initialized, see LibInit().</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_SUCCESS "SUCCESS"</td>                <td>The function executed successfully.</td></tr>
 *   </table>
 * \see ScpChTrGetHysteresisCount
 * \see ScpChTrGetHysteresis
 * \since 0.4.1
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef double(*LibTiePieScpChTrSetHysteresis_t)( LibTiePieHandle_t hDevice , uint16_t wCh , uint32_t dwIndex , double dHysteresis );
#else
double ScpChTrSetHysteresis( LibTiePieHandle_t hDevice , uint16_t wCh , uint32_t dwIndex , double dHysteresis );
#endif

/**
 * \}
 * \defgroup scp_ch_tr_condition Condition
 * \{
 * \brief Some trigger kinds require an additional condition to indicate how the channel trigger must respond to the input signal.
 *
 *             The available trigger conditions depend on the currently set trigger kind.
 *             Use ScpChTrGetConditions() to determine the available trigger conditions for the currently selected trigger kind.
 *             Read more on \ref triggering_scpch_condition "trigger condition".
 *
 *             By default the trigger condition is set to: larger than (#TC_LARGER).
 */

// Workaround: Without this line Doxygen adds the documentation below to the group above.

/**
 * \brief Get the supported trigger conditions for a specified channel with the currently selected \ref ScpChTrGetKind "trigger kind".
 *
 * \param[in] hDevice A \ref OpenDev "device handle" identifying the oscilloscope.
 * \param[in] wCh The channel number identifying the channel, \c 0 to <tt>ScpGetChannelCount() - 1</tt>.
 * \return The supported trigger conditions for this channel and trigger kind, a set of OR-ed \ref TC_ "TC_*" values.
 * \par Status values
 *   <table class="params">
 *   <tr><td>\ref LIBTIEPIESTATUS_NOT_SUPPORTED "NOT_SUPPORTED"</td>          <td>The indicated channel does not support trigger with the current settings.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_CHANNEL "INVALID_CHANNEL"</td>        <td>The requested channel number is invalid.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_HANDLE "INVALID_HANDLE"</td>         <td>The handle is not a valid oscilloscope handle.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_OBJECT_GONE "OBJECT_GONE"</td>            <td>The object indicated by the handle is no longer available.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_LIBRARY_NOT_INITIALIZED "LIBRARY_NOT_INITIALIZED"</td><td>The library is not initialized, see LibInit().</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_SUCCESS "SUCCESS"</td>                <td>The function executed successfully.</td></tr>
 *   </table>
 * \see ScpChTrGetKind
 * \see ScpChTrGetCondition
 * \see ScpChTrSetCondition
 * \since 0.4.1
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef uint32_t(*LibTiePieScpChTrGetConditions_t)( LibTiePieHandle_t hDevice , uint16_t wCh );
#else
uint32_t ScpChTrGetConditions( LibTiePieHandle_t hDevice , uint16_t wCh );
#endif

//! \cond EXTENDED_API

/**
 * \brief Get the supported trigger conditions for a specified channel, for a specific \ref scp_measurements_mode "measure mode" and \ref scp_ch_tr_kind "trigger kind".
 *
 * \param[in] hDevice A \ref OpenDev "device handle" identifying the oscilloscope.
 * \param[in] wCh The channel number identifying the channel, \c 0 to <tt>ScpGetChannelCount() - 1</tt>.
 * \param[in] dwMeasureMode Measure mode, a \ref MM_ "MM_*" value.
 * \param[in] qwTriggerKind The required trigger kind: a \ref TK_ "TK_*" value.
 * \return Supported trigger conditions for this channel, measure mode and trigger kind, a set of OR-ed \ref TC_ "TC_*" values.
 * \since 0.4.5
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef uint32_t(*LibTiePieScpChTrGetConditionsEx_t)( LibTiePieHandle_t hDevice , uint16_t wCh , uint32_t dwMeasureMode , uint64_t qwTriggerKind );
#else
uint32_t ScpChTrGetConditionsEx( LibTiePieHandle_t hDevice , uint16_t wCh , uint32_t dwMeasureMode , uint64_t qwTriggerKind );
#endif

//! \endcond

/**
 * \brief Get the current selected trigger condition for a specified channel.
 *
 * \param[in] hDevice A \ref OpenDev "device handle" identifying the oscilloscope.
 * \param[in] wCh The channel number identifying the channel, \c 0 to <tt>ScpGetChannelCount() - 1</tt>.
 * \return The current trigger condition, a \ref TC_ "TC_*" value.
 * \par Status values
 *   <table class="params">
 *   <tr><td>\ref LIBTIEPIESTATUS_NOT_SUPPORTED "NOT_SUPPORTED"</td>          <td>The indicated channel does not support trigger (condition) with the current settings.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_CHANNEL "INVALID_CHANNEL"</td>        <td>The requested channel number is invalid.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_HANDLE "INVALID_HANDLE"</td>         <td>The handle is not a valid oscilloscope handle.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_OBJECT_GONE "OBJECT_GONE"</td>            <td>The object indicated by the handle is no longer available.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_LIBRARY_NOT_INITIALIZED "LIBRARY_NOT_INITIALIZED"</td><td>The library is not initialized, see LibInit().</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_SUCCESS "SUCCESS"</td>                <td>The function executed successfully.</td></tr>
 *   </table>
 * \see ScpChTrGetConditions
 * \see ScpChTrSetCondition
 * \since 0.4.1
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef uint32_t(*LibTiePieScpChTrGetCondition_t)( LibTiePieHandle_t hDevice , uint16_t wCh );
#else
uint32_t ScpChTrGetCondition( LibTiePieHandle_t hDevice , uint16_t wCh );
#endif

/**
 * \brief Set the trigger condition for a specified channel.
 *
 * \param[in] hDevice A \ref OpenDev "device handle" identifying the oscilloscope.
 * \param[in] wCh The channel number identifying the channel, \c 0 to <tt>ScpGetChannelCount() - 1</tt>.
 * \param[in] dwCondition The required trigger condition, a \ref TC_ "TC_*" value.
 * \return The actually set trigger condition, a \ref TC_ "TC_*" value.
 * \par Status values
 *   <table class="params">
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_VALUE "INVALID_VALUE"</td>          <td>The requested trigger condition is invalid.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_NOT_SUPPORTED "NOT_SUPPORTED"</td>          <td>The indicated channel does not support trigger (condition) with the current settings.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_CHANNEL "INVALID_CHANNEL"</td>        <td>The requested channel number is invalid.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_HANDLE "INVALID_HANDLE"</td>         <td>The handle is not a valid oscilloscope handle.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_OBJECT_GONE "OBJECT_GONE"</td>            <td>The object indicated by the handle is no longer available.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_LIBRARY_NOT_INITIALIZED "LIBRARY_NOT_INITIALIZED"</td><td>The library is not initialized, see LibInit().</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_SUCCESS "SUCCESS"</td>                <td>The function executed successfully.</td></tr>
 *   </table>
 * \see ScpChTrGetConditions
 * \see ScpChTrGetCondition
 * \since 0.4.1
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef uint32_t(*LibTiePieScpChTrSetCondition_t)( LibTiePieHandle_t hDevice , uint16_t wCh , uint32_t dwCondition );
#else
uint32_t ScpChTrSetCondition( LibTiePieHandle_t hDevice , uint16_t wCh , uint32_t dwCondition );
#endif

/**
 * \}
 * \defgroup scp_ch_tr_time Time
 * \{
 * \brief The Time property determines how long a specific condition must last for the channel trigger to respond.
 *
 *             The number of time properties depends on the currently selected trigger kind and currently selected trigger condition.
 *             Use ScpChTrGetTimeCount() to determine the number of trigger time properties for the currently set trigger kind and condition.
 *
 *             The trigger time can be affected by changing the \ref scp_timebase_sampleFrequency "sample frequency".
 *
 *             The trigger time is set as a value in seconds.
 *             By default time[0] is set to 1 ms.
 */

// Workaround: Without this line Doxygen adds the documentation below to the group above.

/**
 * \brief Get the number of trigger times for the current \ref ScpChTrGetKind "trigger kind" and \ref ScpChTrGetCondition "trigger condition".
 *
 * \param[in] hDevice A \ref OpenDev "device handle" identifying the oscilloscope.
 * \param[in] wCh The channel number identifying the channel, \c 0 to <tt>ScpGetChannelCount() - 1</tt>.
 * \return The number of available trigger times for the current trigger kind and condition.
 * \par Status values
 *   <table class="params">
 *   <tr><td>\ref LIBTIEPIESTATUS_NOT_SUPPORTED "NOT_SUPPORTED"</td>          <td>The indicated channel does not support trigger with the current settings.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_CHANNEL "INVALID_CHANNEL"</td>        <td>The requested channel number is invalid.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_HANDLE "INVALID_HANDLE"</td>         <td>The handle is not a valid oscilloscope handle.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_OBJECT_GONE "OBJECT_GONE"</td>            <td>The object indicated by the handle is no longer available.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_LIBRARY_NOT_INITIALIZED "LIBRARY_NOT_INITIALIZED"</td><td>The library is not initialized, see LibInit().</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_SUCCESS "SUCCESS"</td>                <td>The function executed successfully.</td></tr>
 *   </table>
 * \see ScpChTrGetKind
 * \see ScpChTrGetCondition
 * \see ScpChTrGetTime
 * \see ScpChTrSetTime
 * \cond EXTENDED_API
 * \see ScpChTrVerifyTime
 * \see ScpChTrVerifyTimeEx2
 * \endcond
 * \since 0.4.1
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef uint32_t(*LibTiePieScpChTrGetTimeCount_t)( LibTiePieHandle_t hDevice , uint16_t wCh );
#else
uint32_t ScpChTrGetTimeCount( LibTiePieHandle_t hDevice , uint16_t wCh );
#endif

/**
 * \brief Get the current trigger time value for a specified channel and trigger type.
 *
 * \param[in] hDevice A \ref OpenDev "device handle" identifying the oscilloscope.
 * \param[in] wCh The channel number identifying the channel, \c 0 to <tt>ScpGetChannelCount() - 1</tt>.
 * \param[in] dwIndex The trigger time index, \c 0 to <tt>ScpChTrGetTimeCount() - 1</tt>.
 * \return The currently set trigger time value, in seconds.
 * \par Status values
 *   <table class="params">
 *   <tr><td>\ref LIBTIEPIESTATUS_NOT_SUPPORTED "NOT_SUPPORTED"</td>          <td>The indicated channel does not support trigger (time) with the current settings.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_INDEX "INVALID_INDEX"</td>          <td>The trigger time index is invalid.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_CHANNEL "INVALID_CHANNEL"</td>        <td>The requested channel number is invalid.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_HANDLE "INVALID_HANDLE"</td>         <td>The handle is not a valid oscilloscope handle.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_OBJECT_GONE "OBJECT_GONE"</td>            <td>The object indicated by the handle is no longer available.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_LIBRARY_NOT_INITIALIZED "LIBRARY_NOT_INITIALIZED"</td><td>The library is not initialized, see LibInit().</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_SUCCESS "SUCCESS"</td>                <td>The function executed successfully.</td></tr>
 *   </table>
 * \see ScpChTrGetTimeCount
 * \see ScpChTrSetTime
 * \cond EXTENDED_API
 * \see ScpChTrVerifyTime
 * \see ScpChTrVerifyTimeEx2
 * \endcond
 * \since 0.4.1
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef double(*LibTiePieScpChTrGetTime_t)( LibTiePieHandle_t hDevice , uint16_t wCh , uint32_t dwIndex );
#else
double ScpChTrGetTime( LibTiePieHandle_t hDevice , uint16_t wCh , uint32_t dwIndex );
#endif

/**
 * \brief Set the required trigger time value for a specified channel and trigger type.
 *
 * \param[in] hDevice A \ref OpenDev "device handle" identifying the oscilloscope.
 * \param[in] wCh The channel number identifying the channel, \c 0 to <tt>ScpGetChannelCount() - 1</tt>.
 * \param[in] dwIndex The trigger time index, \c 0 to <tt>ScpChTrGetTimeCount() - 1</tt>.
 * \param[in] dTime The required trigger time value, in seconds.
 * \return The actually set trigger time value, in seconds.
 * \par Status values
 *   <table class="params">
 *   <tr><td>\ref LIBTIEPIESTATUS_VALUE_MODIFIED "VALUE_MODIFIED"</td>         <td>The requested trigger time is within the valid range, but not available. The closest valid value is set.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_VALUE "INVALID_VALUE"</td>          <td>The requested trigger time is invalid.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_INDEX "INVALID_INDEX"</td>          <td>The trigger time index is invalid.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_NOT_SUPPORTED "NOT_SUPPORTED"</td>          <td>The indicated channel does not support trigger (time) with the current settings.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_CHANNEL "INVALID_CHANNEL"</td>        <td>The requested channel number is invalid.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_HANDLE "INVALID_HANDLE"</td>         <td>The handle is not a valid oscilloscope handle.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_OBJECT_GONE "OBJECT_GONE"</td>            <td>The object indicated by the handle is no longer available.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_LIBRARY_NOT_INITIALIZED "LIBRARY_NOT_INITIALIZED"</td><td>The library is not initialized, see LibInit().</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_SUCCESS "SUCCESS"</td>                <td>The function executed successfully.</td></tr>
 *   </table>
 * \see ScpChTrGetTimeCount
 * \see ScpChTrGetTime
 * \cond EXTENDED_API
 * \see ScpChTrVerifyTime
 * \see ScpChTrVerifyTimeEx2
 * \endcond
 * \since 0.4.1
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef double(*LibTiePieScpChTrSetTime_t)( LibTiePieHandle_t hDevice , uint16_t wCh , uint32_t dwIndex , double dTime );
#else
double ScpChTrSetTime( LibTiePieHandle_t hDevice , uint16_t wCh , uint32_t dwIndex , double dTime );
#endif

//! \cond EXTENDED_API

/**
 * \brief Verify if the required trigger time value for a specified channel and trigger type can be set.
 *
 * \param[in] hDevice A \ref OpenDev "device handle" identifying the oscilloscope.
 * \param[in] wCh The channel number identifying the channel, \c 0 to <tt>ScpGetChannelCount() - 1</tt>.
 * \param[in] dwIndex The trigger time index, \c 0 to <tt>ScpChTrGetTimeCount() - 1</tt>.
 * \param[in] dTime The required trigger time value, in seconds.
 * \return The actually trigger time value that would have been set, in seconds.
 * \see ScpChTrGetTimeCount
 * \see ScpChTrGetTime
 * \see ScpChTrSetTime
 * \see ScpChTrVerifyTimeEx2
 * \since 0.4.2
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef double(*LibTiePieScpChTrVerifyTime_t)( LibTiePieHandle_t hDevice , uint16_t wCh , uint32_t dwIndex , double dTime );
#else
double ScpChTrVerifyTime( LibTiePieHandle_t hDevice , uint16_t wCh , uint32_t dwIndex , double dTime );
#endif

/**
 * \brief Verify if the required trigger time value for a specified channel, measure mode, sample frequency, trigger type and trigger condition can be set.
 *
 * \param[in] hDevice A \ref OpenDev "device handle" identifying the oscilloscope.
 * \param[in] wCh The channel number identifying the channel, \c 0 to <tt>ScpGetChannelCount() - 1</tt>.
 * \param[in] dwIndex The trigger time index, \c 0 to <tt>ScpChTrGetTimeCount() - 1</tt>.
 * \param[in] dTime The required trigger time value, in seconds.
 * \param[in] dwMeasureMode Measure mode, a \ref MM_ "MM_*" value.
 * \param[in] dSampleFrequency Sample frequency in Hz.
 * \param[in] qwTriggerKind The required trigger kind: a \ref TK_ "TK_*" value.
 * \param[in] dwCondition The required trigger condition, a \ref TC_ "TC_*" value.
 * \return The actually trigger time value that would have been set, in seconds.
 * \see ScpChTrGetTimeCount
 * \see ScpChTrGetTime
 * \see ScpChTrSetTime
 * \see ScpChTrVerifyTime
 * \see ScpChTrVerifyTimeEx
 * \since 0.4.5
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef double(*LibTiePieScpChTrVerifyTimeEx2_t)( LibTiePieHandle_t hDevice , uint16_t wCh , uint32_t dwIndex , double dTime , uint32_t dwMeasureMode , double dSampleFrequency , uint64_t qwTriggerKind , uint32_t dwCondition );
#else
double ScpChTrVerifyTimeEx2( LibTiePieHandle_t hDevice , uint16_t wCh , uint32_t dwIndex , double dTime , uint32_t dwMeasureMode , double dSampleFrequency , uint64_t qwTriggerKind , uint32_t dwCondition );
#endif

//! \endcond

/**
 * \}
 * \}
 * \}
 * \defgroup scp_data Data
 * \{
 * \brief Functions to collect the measured data
 *
 * When a measurement is performed, the data is stored inside the instrument.
 * When no \ref scp_timebase_preSamples "pre samples" are selected (pre sample ratio = 0), the trigger point is located at the start of the record and all samples are measured post samples.
 *
 * When pre samples are selected (pre sample ratio > 0), the trigger point is located at position (pre sample ratio * \ref scp_timebase_recordLength "record length"),
 * dividing the record in pre samples and post samples.
 *
 * When after starting the measurement a trigger occurs before all pre samples are measured, not all pre samples will be valid.
 * Invalid pre samples are set to zero.
 * Use #ScpGetValidPreSampleCount to determine the amount of valid pre samples.
 * See \ref scp_trigger_HoldOff "trigger hold off" to force all pre samples to be measured.
 *
 * When retrieving the measured data, the full record can be get, including the invalid presamples.
 * The start index needs to be set to \c 0 then.
 * It is also possible to get only the valid samples.
 * In that case, the start index needs to be set to <tt>( record length - ( number of post samples + number of valid pre samples )</tt>.
 *
 * Example:
 *
 * \code{.c}
 * uint64_t qwPostSamples = llround( ( 1 - ScpGetPreSampleRatio( hScp ) ) * ScpGetRecordLength( hScp ) );
 * uint64_t qwValidSamples = qwPostSamples + ScpGetValidPreSampleCount( hScp );
 * uint64_t qwStart = ScpGetRecordLength( hScp ) - qwValidSamples;
 *
 * uint64_t qwSamplesRead = ScpGetData1Ch( hScp , pDataCh1 , qwStart , qwValidSamples );
 * \endcode
 *
 * The data retrieval functions use buffers to store the measured data in.
 * The caller must assure that enough memory is allocated for the buffer, to contain all data.
 *
 * Several routines are available to get the measured data, one universal applicable routine and a number of dedicated routines,
 * to collect data from specific channels.
 * - #ScpGetData
 * - #ScpGetData1Ch
 * - #ScpGetData2Ch
 * - #ScpGetData3Ch
 * - #ScpGetData4Ch
 * - #ScpGetData5Ch
 * - #ScpGetData6Ch
 * - #ScpGetData7Ch
 * - #ScpGetData8Ch
 *
 * The data is returned directly in Volt, Ampere or Ohm, depending on the \ref scp_ch_coupling "input coupling".
 *
 * Additionally, routines are available to retrieve range information of the measured data.
 * Once a measurement is ready, the input range of a channel can be changed, e.g. by the auto ranging function or by the user.
 * The input range will then no longer match with the range of the measured data.
 * Use these routines to determine the actual range of the measured data.
 * - #ScpChGetDataValueRange
 * - #ScpChGetDataValueMin
 * - #ScpChGetDataValueMax
 *
 * These routines also incorporate the \ref scp_ch_probe "probe" gain and offset that were set during the measurement.
 *
 */

// Workaround: Without this line Doxygen adds the documentation below to the group above.

/**
 * \brief Get the measurement data for specified channels.
 *
 * This routine is used to retrieve measured data from specific channels.
 * It uses an array of pointers to data buffers to indicate from which channels the data must be retrieved.
 * \c NULL pointers can be used to indicate that no data needs to be retrieved for a specific channel.
 *
 * To retrieve data from channels 1 and 2 of the oscilloscope, create a pointer array with two pointers:
 * <tt>{ pDataCh1 , pDataCh2 }</tt> and set wChannelCount to \c 2.
 *
 * To retrieve data from channels 2 and 4 of the oscilloscope, create a pointer array with four pointers:
 * <tt>{ NULL , pDataCh2 , NULL , pDataCh4 }</tt> and set wChannelCount to \c 4.
 *
 * The buffers contain data directly in Volt, Ampere or Ohm, depending on the \ref scp_ch_coupling "input coupling".
 *
 * \param[in] hDevice A \ref OpenDev "device handle" identifying the oscilloscope.
 * \param[out] pBuffers A pointer to a buffer with pointers to buffers for channel data, the pointer buffer may contain \c NULL pointers.
 * \param[in] wChannelCount The number of pointers in the pointer buffer.
 * \param[in] qwStartIndex The position in the record to start reading.
 * \param[in] qwSampleCount The number of samples to read.
 * \return The number of samples actually read.
 * \par Status values
 *   <table class="params">
 *   <tr><td>\ref LIBTIEPIESTATUS_UNSUCCESSFUL "UNSUCCESSFUL"</td>           <td>An error occurred during execution of the last called function.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_VALUE_CLIPPED "VALUE_CLIPPED"</td>          <td>Retrieved less samples than indicated by qwSampleCount.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_HANDLE "INVALID_HANDLE"</td>         <td>The handle is not a valid oscilloscope handle.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_OBJECT_GONE "OBJECT_GONE"</td>            <td>The object indicated by the handle is no longer available.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_LIBRARY_NOT_INITIALIZED "LIBRARY_NOT_INITIALIZED"</td><td>The library is not initialized, see LibInit().</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_SUCCESS "SUCCESS"</td>                <td>The function executed successfully.</td></tr>
 *   </table>
 * \see hlp_ptrar for programming languages that don't support pointers to pointers, e.g. Matlab or Python.
 * \see ScpGetData1Ch, ScpGetData2Ch, ScpGetData3Ch, ScpGetData4Ch, ScpGetData5Ch, ScpGetData6Ch, ScpGetData7Ch, ScpGetData8Ch
 *
 * \par Example
 * \code{.c}
 * uint64_t qwPostSamples = llround( ( 1 - ScpGetPreSampleRatio( hScp ) ) * ScpGetRecordLength( hScp ) );
 * uint64_t qwValidSamples = qwPostSamples + ScpGetValidPreSampleCount( hScp );
 * uint64_t qwStart = ScpGetRecordLength( hScp ) - qwValidSamples;
 *
 * // Allocate memory for active channels:
 * float** ppChannelData = malloc( sizeof( float* ) * wChannelCount );
 * for( wCh = 0 ; wCh < wChannelCount ; wCh++ )
 *   if( ScpChGetEnabled( hScp , wCh ) )
 *     ppChannelData[ wCh ] = malloc( sizeof( float ) * qwValidSamples );
 *   else
 *     ppChannelData[ wCh ] = NULL;
 *
 * // Get data:
 * uint64_t qwSamplesRead = ScpGetData( hScp , ppChannelData , wChannelCount , qwStart , qwValidSamples );
 *
 * // do something with the data.
 *
 * // Free memory:
 * for( wCh = 0 ; wCh < wChannelCount ; wCh++ )
 *   free( ppChannelData[ wCh ] );
 * free( ppChannelData );
 * \endcode
 *
 * \since 0.4.0
 */
#ifdef INCLUDED_BY_MATLAB
#ifdef LIBTIEPIE_DYNAMIC
typedef uint64_t(*LibTiePieScpGetData_t)( LibTiePieHandle_t hDevice , void** pBuffers , uint16_t wChannelCount , uint64_t qwStartIndex , uint64_t qwSampleCount );
#else
uint64_t ScpGetData( LibTiePieHandle_t hDevice , void** pBuffers , uint16_t wChannelCount , uint64_t qwStartIndex , uint64_t qwSampleCount );
#endif
#else
#ifdef LIBTIEPIE_DYNAMIC
typedef uint64_t(*LibTiePieScpGetData_t)( LibTiePieHandle_t hDevice , float** pBuffers , uint16_t wChannelCount , uint64_t qwStartIndex , uint64_t qwSampleCount );
#else
uint64_t ScpGetData( LibTiePieHandle_t hDevice , float** pBuffers , uint16_t wChannelCount , uint64_t qwStartIndex , uint64_t qwSampleCount );
#endif
#endif

/**
 * \brief Get the measurement data for the first channel.
 *
 * The buffers contain data directly in Volt, Ampere or Ohm, depending on the \ref scp_ch_coupling "input coupling".
 *
 * \param[in] hDevice A \ref OpenDev "device handle" identifying the oscilloscope.
 * \param[out] pBufferCh1 A pointer to the buffer for channel 1 data or \c NULL.
 * \param[in] qwStartIndex The psition in the record to start reading.
 * \param[in] qwSampleCount The number of samples to read.
 * \return The number of samples actually read.
 * \par Status values
 *   <table class="params">
 *   <tr><td>\ref LIBTIEPIESTATUS_UNSUCCESSFUL "UNSUCCESSFUL"</td>           <td>An error occurred during execution of the last called function.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_VALUE_CLIPPED "VALUE_CLIPPED"</td>          <td>Retrieved less samples than indicated by qwSampleCount.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_HANDLE "INVALID_HANDLE"</td>         <td>The handle is not a valid oscilloscope handle.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_OBJECT_GONE "OBJECT_GONE"</td>            <td>The object indicated by the handle is no longer available.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_LIBRARY_NOT_INITIALIZED "LIBRARY_NOT_INITIALIZED"</td><td>The library is not initialized, see LibInit().</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_SUCCESS "SUCCESS"</td>                <td>The function executed successfully.</td></tr>
 *   </table>
 * \see ScpGetData
 * \see ScpGetData2Ch, ScpGetData3Ch, ScpGetData4Ch
 * \since 0.4.0
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef uint64_t(*LibTiePieScpGetData1Ch_t)( LibTiePieHandle_t hDevice , float* pBufferCh1 , uint64_t qwStartIndex , uint64_t qwSampleCount );
#else
uint64_t ScpGetData1Ch( LibTiePieHandle_t hDevice , float* pBufferCh1 , uint64_t qwStartIndex , uint64_t qwSampleCount );
#endif

/**
 * \brief Get the measurement data for the first two channels.
 *
 * The buffers contain data directly in Volt, Ampere or Ohm, depending on the \ref scp_ch_coupling "input coupling".
 *
 * \param[in] hDevice A \ref OpenDev "device handle" identifying the oscilloscope.
 * \param[out] pBufferCh1 A pointer to the buffer for channel 1 data or \c NULL.
 * \param[out] pBufferCh2 A pointer to the buffer for channel 2 data or \c NULL.
 * \param[in] qwStartIndex The position in the record to start reading.
 * \param[in] qwSampleCount The number of samples to read.
 * \return The number of samples actually read.
 * \par Status values
 *   <table class="params">
 *   <tr><td>\ref LIBTIEPIESTATUS_UNSUCCESSFUL "UNSUCCESSFUL"</td>           <td>An error occurred during execution of the last called function.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_VALUE_CLIPPED "VALUE_CLIPPED"</td>          <td>Retrieved less samples than indicated by qwSampleCount.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_HANDLE "INVALID_HANDLE"</td>         <td>The handle is not a valid oscilloscope handle.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_OBJECT_GONE "OBJECT_GONE"</td>            <td>The object indicated by the handle is no longer available.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_LIBRARY_NOT_INITIALIZED "LIBRARY_NOT_INITIALIZED"</td><td>The library is not initialized, see LibInit().</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_SUCCESS "SUCCESS"</td>                <td>The function executed successfully.</td></tr>
 *   </table>
 * \see ScpGetData
 * \see ScpGetData1Ch, ScpGetData3Ch, ScpGetData4Ch, ScpGetData5Ch, ScpGetData6Ch, ScpGetData7Ch, ScpGetData8Ch
 * \since 0.4.0
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef uint64_t(*LibTiePieScpGetData2Ch_t)( LibTiePieHandle_t hDevice , float* pBufferCh1 , float* pBufferCh2 , uint64_t qwStartIndex , uint64_t qwSampleCount );
#else
uint64_t ScpGetData2Ch( LibTiePieHandle_t hDevice , float* pBufferCh1 , float* pBufferCh2 , uint64_t qwStartIndex , uint64_t qwSampleCount );
#endif

/**
 * \brief Get the measurement data for the first three channels.
 *
 * The buffers contain data directly in Volt, Ampere or Ohm, depending on the \ref scp_ch_coupling "input coupling".
 *
 * \param[in] hDevice A \ref OpenDev "device handle" identifying the oscilloscope.
 * \param[out] pBufferCh1 A pointer to the buffer for channel 1 data or \c NULL.
 * \param[out] pBufferCh2 A pointer to the buffer for channel 2 data or \c NULL.
 * \param[out] pBufferCh3 A pointer to the buffer for channel 3 data or \c NULL.
 * \param[in] qwStartIndex The position in the record to start reading.
 * \param[in] qwSampleCount The number of samples to read.
 * \return The number of samples actually read.
 * \par Status values
 *   <table class="params">
 *   <tr><td>\ref LIBTIEPIESTATUS_UNSUCCESSFUL "UNSUCCESSFUL"</td>           <td>An error occurred during execution of the last called function.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_VALUE_CLIPPED "VALUE_CLIPPED"</td>          <td>Retrieved less samples than indicated by qwSampleCount.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_HANDLE "INVALID_HANDLE"</td>         <td>The handle is not a valid oscilloscope handle.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_OBJECT_GONE "OBJECT_GONE"</td>            <td>The object indicated by the handle is no longer available.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_LIBRARY_NOT_INITIALIZED "LIBRARY_NOT_INITIALIZED"</td><td>The library is not initialized, see LibInit().</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_SUCCESS "SUCCESS"</td>                <td>The function executed successfully.</td></tr>
 *   </table>
 * \see ScpGetData
 * \see ScpGetData1Ch, ScpGetData2Ch, ScpGetData4Ch, ScpGetData5Ch, ScpGetData6Ch, ScpGetData7Ch, ScpGetData8Ch
 * \since 0.4.0
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef uint64_t(*LibTiePieScpGetData3Ch_t)( LibTiePieHandle_t hDevice , float* pBufferCh1 , float* pBufferCh2 , float* pBufferCh3 , uint64_t qwStartIndex , uint64_t qwSampleCount );
#else
uint64_t ScpGetData3Ch( LibTiePieHandle_t hDevice , float* pBufferCh1 , float* pBufferCh2 , float* pBufferCh3 , uint64_t qwStartIndex , uint64_t qwSampleCount );
#endif

/**
 * \brief Get the measurement data for the first four channels.
 *
 * The buffers contain data directly in Volt, Ampere or Ohm, depending on the \ref scp_ch_coupling "input coupling".
 *
 * \param[in] hDevice A \ref OpenDev "device handle" identifying the oscilloscope.
 * \param[out] pBufferCh1 A pointer to the buffer for channel 1 data or \c NULL.
 * \param[out] pBufferCh2 A pointer to the buffer for channel 2 data or \c NULL.
 * \param[out] pBufferCh3 A pointer to the buffer for channel 3 data or \c NULL.
 * \param[out] pBufferCh4 A pointer to the buffer for channel 4 data or \c NULL.
 * \param[in] qwStartIndex The position in the record to start reading.
 * \param[in] qwSampleCount The number of samples to read.
 * \return The number of samples actually read.
 * \par Status values
 *   <table class="params">
 *   <tr><td>\ref LIBTIEPIESTATUS_UNSUCCESSFUL "UNSUCCESSFUL"</td>           <td>An error occurred during execution of the last called function.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_VALUE_CLIPPED "VALUE_CLIPPED"</td>          <td>Retrieved less samples than indicated by qwSampleCount.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_HANDLE "INVALID_HANDLE"</td>         <td>The handle is not a valid oscilloscope handle.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_OBJECT_GONE "OBJECT_GONE"</td>            <td>The object indicated by the handle is no longer available.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_LIBRARY_NOT_INITIALIZED "LIBRARY_NOT_INITIALIZED"</td><td>The library is not initialized, see LibInit().</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_SUCCESS "SUCCESS"</td>                <td>The function executed successfully.</td></tr>
 *   </table>
 * \see ScpGetData
 * \see ScpGetData1Ch, ScpGetData2Ch, ScpGetData3Ch, ScpGetData5Ch, ScpGetData6Ch, ScpGetData7Ch, ScpGetData8Ch
 * \since 0.4.0
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef uint64_t(*LibTiePieScpGetData4Ch_t)( LibTiePieHandle_t hDevice , float* pBufferCh1 , float* pBufferCh2 , float* pBufferCh3 , float* pBufferCh4 , uint64_t qwStartIndex , uint64_t qwSampleCount );
#else
uint64_t ScpGetData4Ch( LibTiePieHandle_t hDevice , float* pBufferCh1 , float* pBufferCh2 , float* pBufferCh3 , float* pBufferCh4 , uint64_t qwStartIndex , uint64_t qwSampleCount );
#endif

/**
 * \brief Get the measurement data for the first five channels.
 *
 * The buffers contain data directly in Volt, Ampere or Ohm, depending on the \ref scp_ch_coupling "input coupling".
 *
 * \param[in] hDevice A \ref OpenDev "device handle" identifying the oscilloscope.
 * \param[out] pBufferCh1 A pointer to the buffer for channel 1 data or \c NULL.
 * \param[out] pBufferCh2 A pointer to the buffer for channel 2 data or \c NULL.
 * \param[out] pBufferCh3 A pointer to the buffer for channel 3 data or \c NULL.
 * \param[out] pBufferCh4 A pointer to the buffer for channel 4 data or \c NULL.
 * \param[out] pBufferCh5 A pointer to the buffer for channel 5 data or \c NULL.
 * \param[in] qwStartIndex The position in the record to start reading.
 * \param[in] qwSampleCount The number of samples to read.
 * \return The number of samples actually read.
 * \par Status values
 *   <table class="params">
 *   <tr><td>\ref LIBTIEPIESTATUS_UNSUCCESSFUL "UNSUCCESSFUL"</td>           <td>An error occurred during execution of the last called function.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_VALUE_CLIPPED "VALUE_CLIPPED"</td>          <td>Retrieved less samples than indicated by qwSampleCount.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_HANDLE "INVALID_HANDLE"</td>         <td>The handle is not a valid oscilloscope handle.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_OBJECT_GONE "OBJECT_GONE"</td>            <td>The object indicated by the handle is no longer available.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_LIBRARY_NOT_INITIALIZED "LIBRARY_NOT_INITIALIZED"</td><td>The library is not initialized, see LibInit().</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_SUCCESS "SUCCESS"</td>                <td>The function executed successfully.</td></tr>
 *   </table>
 * \see ScpGetData
 * \see ScpGetData1Ch, ScpGetData2Ch, ScpGetData3Ch, ScpGetData4Ch, ScpGetData6Ch, ScpGetData7Ch, ScpGetData8Ch
 * \since 0.9.11
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef uint64_t(*LibTiePieScpGetData5Ch_t)( LibTiePieHandle_t hDevice , float* pBufferCh1 , float* pBufferCh2 , float* pBufferCh3 , float* pBufferCh4 , float* pBufferCh5 , uint64_t qwStartIndex , uint64_t qwSampleCount );
#else
uint64_t ScpGetData5Ch( LibTiePieHandle_t hDevice , float* pBufferCh1 , float* pBufferCh2 , float* pBufferCh3 , float* pBufferCh4 , float* pBufferCh5 , uint64_t qwStartIndex , uint64_t qwSampleCount );
#endif

/**
 * \brief Get the measurement data for the first six channels.
 *
 * The buffers contain data directly in Volt, Ampere or Ohm, depending on the \ref scp_ch_coupling "input coupling".
 *
 * \param[in] hDevice A \ref OpenDev "device handle" identifying the oscilloscope.
 * \param[out] pBufferCh1 A pointer to the buffer for channel 1 data or \c NULL.
 * \param[out] pBufferCh2 A pointer to the buffer for channel 2 data or \c NULL.
 * \param[out] pBufferCh3 A pointer to the buffer for channel 3 data or \c NULL.
 * \param[out] pBufferCh4 A pointer to the buffer for channel 4 data or \c NULL.
 * \param[out] pBufferCh5 A pointer to the buffer for channel 5 data or \c NULL.
 * \param[out] pBufferCh6 A pointer to the buffer for channel 6 data or \c NULL.
 * \param[in] qwStartIndex The position in the record to start reading.
 * \param[in] qwSampleCount The number of samples to read.
 * \return The number of samples actually read.
 * \par Status values
 *   <table class="params">
 *   <tr><td>\ref LIBTIEPIESTATUS_UNSUCCESSFUL "UNSUCCESSFUL"</td>           <td>An error occurred during execution of the last called function.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_VALUE_CLIPPED "VALUE_CLIPPED"</td>          <td>Retrieved less samples than indicated by qwSampleCount.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_HANDLE "INVALID_HANDLE"</td>         <td>The handle is not a valid oscilloscope handle.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_OBJECT_GONE "OBJECT_GONE"</td>            <td>The object indicated by the handle is no longer available.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_LIBRARY_NOT_INITIALIZED "LIBRARY_NOT_INITIALIZED"</td><td>The library is not initialized, see LibInit().</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_SUCCESS "SUCCESS"</td>                <td>The function executed successfully.</td></tr>
 *   </table>
 * \see ScpGetData
 * \see ScpGetData1Ch, ScpGetData2Ch, ScpGetData3Ch, ScpGetData4Ch, ScpGetData5Ch, ScpGetData7Ch, ScpGetData8Ch
 * \since 0.9.11
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef uint64_t(*LibTiePieScpGetData6Ch_t)( LibTiePieHandle_t hDevice , float* pBufferCh1 , float* pBufferCh2 , float* pBufferCh3 , float* pBufferCh4 , float* pBufferCh5 , float* pBufferCh6 , uint64_t qwStartIndex , uint64_t qwSampleCount );
#else
uint64_t ScpGetData6Ch( LibTiePieHandle_t hDevice , float* pBufferCh1 , float* pBufferCh2 , float* pBufferCh3 , float* pBufferCh4 , float* pBufferCh5 , float* pBufferCh6 , uint64_t qwStartIndex , uint64_t qwSampleCount );
#endif

/**
 * \brief Get the measurement data for the first seven channels.
 *
 * The buffers contain data directly in Volt, Ampere or Ohm, depending on the \ref scp_ch_coupling "input coupling".
 *
 * \param[in] hDevice A \ref OpenDev "device handle" identifying the oscilloscope.
 * \param[out] pBufferCh1 A pointer to the buffer for channel 1 data or \c NULL.
 * \param[out] pBufferCh2 A pointer to the buffer for channel 2 data or \c NULL.
 * \param[out] pBufferCh3 A pointer to the buffer for channel 3 data or \c NULL.
 * \param[out] pBufferCh4 A pointer to the buffer for channel 4 data or \c NULL.
 * \param[out] pBufferCh5 A pointer to the buffer for channel 5 data or \c NULL.
 * \param[out] pBufferCh6 A pointer to the buffer for channel 6 data or \c NULL.
 * \param[out] pBufferCh7 A pointer to the buffer for channel 7 data or \c NULL.
 * \param[in] qwStartIndex The position in the record to start reading.
 * \param[in] qwSampleCount The number of samples to read.
 * \return The number of samples actually read.
 * \par Status values
 *   <table class="params">
 *   <tr><td>\ref LIBTIEPIESTATUS_UNSUCCESSFUL "UNSUCCESSFUL"</td>           <td>An error occurred during execution of the last called function.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_VALUE_CLIPPED "VALUE_CLIPPED"</td>          <td>Retrieved less samples than indicated by qwSampleCount.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_HANDLE "INVALID_HANDLE"</td>         <td>The handle is not a valid oscilloscope handle.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_OBJECT_GONE "OBJECT_GONE"</td>            <td>The object indicated by the handle is no longer available.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_LIBRARY_NOT_INITIALIZED "LIBRARY_NOT_INITIALIZED"</td><td>The library is not initialized, see LibInit().</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_SUCCESS "SUCCESS"</td>                <td>The function executed successfully.</td></tr>
 *   </table>
 * \see ScpGetData
 * \see ScpGetData1Ch, ScpGetData2Ch, ScpGetData3Ch, ScpGetData4Ch, ScpGetData5Ch, ScpGetData6Ch, ScpGetData8Ch
 * \since 0.9.11
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef uint64_t(*LibTiePieScpGetData7Ch_t)( LibTiePieHandle_t hDevice , float* pBufferCh1 , float* pBufferCh2 , float* pBufferCh3 , float* pBufferCh4 , float* pBufferCh5 , float* pBufferCh6 , float* pBufferCh7 , uint64_t qwStartIndex , uint64_t qwSampleCount );
#else
uint64_t ScpGetData7Ch( LibTiePieHandle_t hDevice , float* pBufferCh1 , float* pBufferCh2 , float* pBufferCh3 , float* pBufferCh4 , float* pBufferCh5 , float* pBufferCh6 , float* pBufferCh7 , uint64_t qwStartIndex , uint64_t qwSampleCount );
#endif

/**
 * \brief Get the measurement data for the first eight channels.
 *
 * The buffers contain data directly in Volt, Ampere or Ohm, depending on the \ref scp_ch_coupling "input coupling".
 *
 * \param[in] hDevice A \ref OpenDev "device handle" identifying the oscilloscope.
 * \param[out] pBufferCh1 A pointer to the buffer for channel 1 data or \c NULL.
 * \param[out] pBufferCh2 A pointer to the buffer for channel 2 data or \c NULL.
 * \param[out] pBufferCh3 A pointer to the buffer for channel 3 data or \c NULL.
 * \param[out] pBufferCh4 A pointer to the buffer for channel 4 data or \c NULL.
 * \param[out] pBufferCh5 A pointer to the buffer for channel 5 data or \c NULL.
 * \param[out] pBufferCh6 A pointer to the buffer for channel 6 data or \c NULL.
 * \param[out] pBufferCh7 A pointer to the buffer for channel 7 data or \c NULL.
 * \param[out] pBufferCh8 A pointer to the buffer for channel 8 data or \c NULL.
 * \param[in] qwStartIndex The position in the record to start reading.
 * \param[in] qwSampleCount The number of samples to read.
 * \return The number of samples actually read.
 * \par Status values
 *   <table class="params">
 *   <tr><td>\ref LIBTIEPIESTATUS_UNSUCCESSFUL "UNSUCCESSFUL"</td>           <td>An error occurred during execution of the last called function.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_VALUE_CLIPPED "VALUE_CLIPPED"</td>          <td>Retrieved less samples than indicated by qwSampleCount.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_HANDLE "INVALID_HANDLE"</td>         <td>The handle is not a valid oscilloscope handle.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_OBJECT_GONE "OBJECT_GONE"</td>            <td>The object indicated by the handle is no longer available.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_LIBRARY_NOT_INITIALIZED "LIBRARY_NOT_INITIALIZED"</td><td>The library is not initialized, see LibInit().</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_SUCCESS "SUCCESS"</td>                <td>The function executed successfully.</td></tr>
 *   </table>
 * \see ScpGetData
 * \see ScpGetData1Ch, ScpGetData2Ch, ScpGetData3Ch, ScpGetData4Ch, ScpGetData5Ch, ScpGetData6Ch, ScpGetData7Ch
 * \since 0.9.11
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef uint64_t(*LibTiePieScpGetData8Ch_t)( LibTiePieHandle_t hDevice , float* pBufferCh1 , float* pBufferCh2 , float* pBufferCh3 , float* pBufferCh4 , float* pBufferCh5 , float* pBufferCh6 , float* pBufferCh7 , float* pBufferCh8 , uint64_t qwStartIndex , uint64_t qwSampleCount );
#else
uint64_t ScpGetData8Ch( LibTiePieHandle_t hDevice , float* pBufferCh1 , float* pBufferCh2 , float* pBufferCh3 , float* pBufferCh4 , float* pBufferCh5 , float* pBufferCh6 , float* pBufferCh7 , float* pBufferCh8 , uint64_t qwStartIndex , uint64_t qwSampleCount );
#endif

/**
 * \brief Get the number of valid pre samples in the measurement.
 *
 * When pre samples are selected (pre sample ratio > 0), the trigger point is located at position (pre sample ratio * \ref scp_timebase_recordLength "record length"),
 * dividing the record in pre samples and post samples.
 *
 * When after starting the measurement a trigger occurs before all presamples are measured, not all pre samples will be valid.
 *
 * \param[in] hDevice A \ref OpenDev "device handle" identifying the oscilloscope.
 * \return The number of valid pre samples.
 * \par Status values
 *   <table class="params">
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_HANDLE "INVALID_HANDLE"</td>         <td>The handle is not a valid oscilloscope handle.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_OBJECT_GONE "OBJECT_GONE"</td>            <td>The object indicated by the handle is no longer available.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_LIBRARY_NOT_INITIALIZED "LIBRARY_NOT_INITIALIZED"</td><td>The library is not initialized, see LibInit().</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_SUCCESS "SUCCESS"</td>                <td>The function executed successfully.</td></tr>
 *   </table>
 * \since 0.4.0
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef uint64_t(*LibTiePieScpGetValidPreSampleCount_t)( LibTiePieHandle_t hDevice );
#else
uint64_t ScpGetValidPreSampleCount( LibTiePieHandle_t hDevice );
#endif

/**
 * \brief Get the minimum and maximum values of the input range the current data was measured with.
 *
 * The buffers contain the minimum and maximum values of the input range directly in Volt, Ampere or Ohm, depending on the \ref scp_ch_coupling "input coupling".
 *
 * \param[in] hDevice A \ref OpenDev "device handle" identifying the oscilloscope.
 * \param[in] wCh The channel number identifying the channel, \c 0 to <tt>ScpGetChannelCount() - 1</tt>.
 * \param[out] pMin A pointer to a buffer for the minimum value of the range or \c NULL.
 * \param[out] pMax A pointer to a buffer for the maximum value of the range or \c NULL.
 * \par Status values
 *   <table class="params">
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_CHANNEL "INVALID_CHANNEL"</td>        <td>The requested channel number is invalid.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_HANDLE "INVALID_HANDLE"</td>         <td>The handle is not a valid oscilloscope handle.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_OBJECT_GONE "OBJECT_GONE"</td>            <td>The object indicated by the handle is no longer available.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_LIBRARY_NOT_INITIALIZED "LIBRARY_NOT_INITIALIZED"</td><td>The library is not initialized, see LibInit().</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_SUCCESS "SUCCESS"</td>                <td>The function executed successfully.</td></tr>
 *   </table>
 * \see ScpChGetDataValueMin
 * \see ScpChGetDataValueMax
 * \see scp_ch_probe
 * \since 0.4.0
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef void(*LibTiePieScpChGetDataValueRange_t)( LibTiePieHandle_t hDevice , uint16_t wCh , double* pMin , double* pMax );
#else
void ScpChGetDataValueRange( LibTiePieHandle_t hDevice , uint16_t wCh , double* pMin , double* pMax );
#endif

/**
 * \brief Get the minimum value of the input range the current data was measured with.
 *
 * \param[in] hDevice A \ref OpenDev "device handle" identifying the oscilloscope.
 * \param[in] wCh The channel number identifying the channel, \c 0 to <tt>ScpGetChannelCount() - 1</tt>.
 * \return The minimum value of the input range the current data was measured with, in Volt, Ampere or Ohm, depending on the \ref scp_ch_coupling "input coupling".
 * \par Status values
 *   <table class="params">
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_CHANNEL "INVALID_CHANNEL"</td>        <td>The requested channel number is invalid.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_HANDLE "INVALID_HANDLE"</td>         <td>The handle is not a valid oscilloscope handle.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_OBJECT_GONE "OBJECT_GONE"</td>            <td>The object indicated by the handle is no longer available.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_LIBRARY_NOT_INITIALIZED "LIBRARY_NOT_INITIALIZED"</td><td>The library is not initialized, see LibInit().</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_SUCCESS "SUCCESS"</td>                <td>The function executed successfully.</td></tr>
 *   </table>
 * \see ScpChGetDataValueMax
 * \see ScpChGetDataValueRange
 * \see scp_ch_probe
 * \since 0.4.0
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef double(*LibTiePieScpChGetDataValueMin_t)( LibTiePieHandle_t hDevice , uint16_t wCh );
#else
double ScpChGetDataValueMin( LibTiePieHandle_t hDevice , uint16_t wCh );
#endif

/**
 * \brief Get the maximum value of the input range the current data was measured with.
 *
 * \param[in] hDevice A \ref OpenDev "device handle" identifying the oscilloscope.
 * \param[in] wCh The channel number identifying the channel, \c 0 to <tt>ScpGetChannelCount() - 1</tt>.
 * \return The maximum value of the input range the current data was measured with, in Volt, Ampere or Ohm, depending on the \ref scp_ch_coupling "input coupling".
 * \par Status values
 *   <table class="params">
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_CHANNEL "INVALID_CHANNEL"</td>        <td>The requested channel number is invalid.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_HANDLE "INVALID_HANDLE"</td>         <td>The handle is not a valid oscilloscope handle.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_OBJECT_GONE "OBJECT_GONE"</td>            <td>The object indicated by the handle is no longer available.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_LIBRARY_NOT_INITIALIZED "LIBRARY_NOT_INITIALIZED"</td><td>The library is not initialized, see LibInit().</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_SUCCESS "SUCCESS"</td>                <td>The function executed successfully.</td></tr>
 *   </table>
 * \see ScpChGetDataValueMin
 * \see ScpChGetDataValueRange
 * \see scp_ch_probe
 * \since 0.4.0
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef double(*LibTiePieScpChGetDataValueMax_t)( LibTiePieHandle_t hDevice , uint16_t wCh );
#else
double ScpChGetDataValueMax( LibTiePieHandle_t hDevice , uint16_t wCh );
#endif

/**
 * \cond EXTENDED_API
 * \defgroup scp_data_raw Raw
 * \{
 */

// Workaround: Without this line Doxygen adds the documentation below to the group above.

/**
 * \brief Get raw measurement data.
 *
 * \param[in] hDevice A \ref OpenDev "device handle".
 * \param[out] pBuffers Pointer to buffer with pointers to buffer for channel data, pointer buffer may contain \c NULL pointers.
 * \param[in] wChannelCount Number of pointers in pointer buffer.
 * \param[in] qwStartIndex Position in record to start reading.
 * \param[in] qwSampleCount Number of samples to read.
 * \return Number of samples read.
 * \see hlp_ptrar
 * \since 0.4.0
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef uint64_t(*LibTiePieScpGetDataRaw_t)( LibTiePieHandle_t hDevice , void** pBuffers , uint16_t wChannelCount , uint64_t qwStartIndex , uint64_t qwSampleCount );
#else
uint64_t ScpGetDataRaw( LibTiePieHandle_t hDevice , void** pBuffers , uint16_t wChannelCount , uint64_t qwStartIndex , uint64_t qwSampleCount );
#endif

/**
 * \brief Get raw measurement data.
 *
 * \param[in] hDevice A \ref OpenDev "device handle".
 * \param[out] pBufferCh1 Pointer to buffer for channel 1 data or \c NULL.
 * \param[in] qwStartIndex Position in record to start reading.
 * \param[in] qwSampleCount Number of samples to read.
 * \return Number of samples read.
 * \since 0.4.0
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef uint64_t(*LibTiePieScpGetDataRaw1Ch_t)( LibTiePieHandle_t hDevice , void* pBufferCh1 , uint64_t qwStartIndex , uint64_t qwSampleCount );
#else
uint64_t ScpGetDataRaw1Ch( LibTiePieHandle_t hDevice , void* pBufferCh1 , uint64_t qwStartIndex , uint64_t qwSampleCount );
#endif

/**
 * \brief Get raw measurement data.
 *
 * \param[in] hDevice A \ref OpenDev "device handle".
 * \param[out] pBufferCh1 Pointer to buffer for channel 1 data or \c NULL.
 * \param[out] pBufferCh2 Pointer to buffer for channel 2 data or \c NULL.
 * \param[in] qwStartIndex Position in record to start reading.
 * \param[in] qwSampleCount Number of samples to read.
 * \return Number of samples read.
 * \since 0.4.0
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef uint64_t(*LibTiePieScpGetDataRaw2Ch_t)( LibTiePieHandle_t hDevice , void* pBufferCh1 , void* pBufferCh2 , uint64_t qwStartIndex , uint64_t qwSampleCount );
#else
uint64_t ScpGetDataRaw2Ch( LibTiePieHandle_t hDevice , void* pBufferCh1 , void* pBufferCh2 , uint64_t qwStartIndex , uint64_t qwSampleCount );
#endif

/**
 * \brief Get raw measurement data.
 *
 * \param[in] hDevice A \ref OpenDev "device handle".
 * \param[out] pBufferCh1 Pointer to buffer for channel 1 data or \c NULL.
 * \param[out] pBufferCh2 Pointer to buffer for channel 2 data or \c NULL.
 * \param[out] pBufferCh3 Pointer to buffer for channel 3 data or \c NULL.
 * \param[in] qwStartIndex Position in record to start reading.
 * \param[in] qwSampleCount Number of samples to read.
 * \return Number of samples read.
 * \since 0.4.0
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef uint64_t(*LibTiePieScpGetDataRaw3Ch_t)( LibTiePieHandle_t hDevice , void* pBufferCh1 , void* pBufferCh2 , void* pBufferCh3 , uint64_t qwStartIndex , uint64_t qwSampleCount );
#else
uint64_t ScpGetDataRaw3Ch( LibTiePieHandle_t hDevice , void* pBufferCh1 , void* pBufferCh2 , void* pBufferCh3 , uint64_t qwStartIndex , uint64_t qwSampleCount );
#endif

/**
 * \brief Get raw measurement data.
 *
 * \param[in] hDevice A \ref OpenDev "device handle".
 * \param[out] pBufferCh1 Pointer to buffer for channel 1 data or \c NULL.
 * \param[out] pBufferCh2 Pointer to buffer for channel 2 data or \c NULL.
 * \param[out] pBufferCh3 Pointer to buffer for channel 3 data or \c NULL.
 * \param[out] pBufferCh4 Pointer to buffer for channel 4 data or \c NULL.
 * \param[in] qwStartIndex Position in record to start reading.
 * \param[in] qwSampleCount Number of samples to read.
 * \return Number of samples read.
 * \since 0.4.0
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef uint64_t(*LibTiePieScpGetDataRaw4Ch_t)( LibTiePieHandle_t hDevice , void* pBufferCh1 , void* pBufferCh2 , void* pBufferCh3 , void* pBufferCh4 , uint64_t qwStartIndex , uint64_t qwSampleCount );
#else
uint64_t ScpGetDataRaw4Ch( LibTiePieHandle_t hDevice , void* pBufferCh1 , void* pBufferCh2 , void* pBufferCh3 , void* pBufferCh4 , uint64_t qwStartIndex , uint64_t qwSampleCount );
#endif

/**
 * \brief Get raw measurement data.
 *
 * \param[in] hDevice A \ref OpenDev "device handle".
 * \param[out] pBufferCh1 Pointer to buffer for channel 1 data or \c NULL.
 * \param[out] pBufferCh2 Pointer to buffer for channel 2 data or \c NULL.
 * \param[out] pBufferCh3 Pointer to buffer for channel 3 data or \c NULL.
 * \param[out] pBufferCh4 Pointer to buffer for channel 4 data or \c NULL.
 * \param[out] pBufferCh5 Pointer to buffer for channel 5 data or \c NULL.
 * \param[in] qwStartIndex Position in record to start reading.
 * \param[in] qwSampleCount Number of samples to read.
 * \return Number of samples read.
 * \since 0.9.11
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef uint64_t(*LibTiePieScpGetDataRaw5Ch_t)( LibTiePieHandle_t hDevice , void* pBufferCh1 , void* pBufferCh2 , void* pBufferCh3 , void* pBufferCh4 , void* pBufferCh5 , uint64_t qwStartIndex , uint64_t qwSampleCount );
#else
uint64_t ScpGetDataRaw5Ch( LibTiePieHandle_t hDevice , void* pBufferCh1 , void* pBufferCh2 , void* pBufferCh3 , void* pBufferCh4 , void* pBufferCh5 , uint64_t qwStartIndex , uint64_t qwSampleCount );
#endif

/**
 * \brief Get raw measurement data.
 *
 * \param[in] hDevice A \ref OpenDev "device handle".
 * \param[out] pBufferCh1 Pointer to buffer for channel 1 data or \c NULL.
 * \param[out] pBufferCh2 Pointer to buffer for channel 2 data or \c NULL.
 * \param[out] pBufferCh3 Pointer to buffer for channel 3 data or \c NULL.
 * \param[out] pBufferCh4 Pointer to buffer for channel 4 data or \c NULL.
 * \param[out] pBufferCh5 Pointer to buffer for channel 5 data or \c NULL.
 * \param[out] pBufferCh6 Pointer to buffer for channel 6 data or \c NULL.
 * \param[in] qwStartIndex Position in record to start reading.
 * \param[in] qwSampleCount Number of samples to read.
 * \return Number of samples read.
 * \since 0.9.11
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef uint64_t(*LibTiePieScpGetDataRaw6Ch_t)( LibTiePieHandle_t hDevice , void* pBufferCh1 , void* pBufferCh2 , void* pBufferCh3 , void* pBufferCh4 , void* pBufferCh5 , void* pBufferCh6 , uint64_t qwStartIndex , uint64_t qwSampleCount );
#else
uint64_t ScpGetDataRaw6Ch( LibTiePieHandle_t hDevice , void* pBufferCh1 , void* pBufferCh2 , void* pBufferCh3 , void* pBufferCh4 , void* pBufferCh5 , void* pBufferCh6 , uint64_t qwStartIndex , uint64_t qwSampleCount );
#endif

/**
 * \brief Get raw measurement data.
 *
 * \param[in] hDevice A \ref OpenDev "device handle".
 * \param[out] pBufferCh1 Pointer to buffer for channel 1 data or \c NULL.
 * \param[out] pBufferCh2 Pointer to buffer for channel 2 data or \c NULL.
 * \param[out] pBufferCh3 Pointer to buffer for channel 3 data or \c NULL.
 * \param[out] pBufferCh4 Pointer to buffer for channel 4 data or \c NULL.
 * \param[out] pBufferCh5 Pointer to buffer for channel 5 data or \c NULL.
 * \param[out] pBufferCh6 Pointer to buffer for channel 6 data or \c NULL.
 * \param[out] pBufferCh7 Pointer to buffer for channel 7 data or \c NULL.
 * \param[in] qwStartIndex Position in record to start reading.
 * \param[in] qwSampleCount Number of samples to read.
 * \return Number of samples read.
 * \since 0.9.11
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef uint64_t(*LibTiePieScpGetDataRaw7Ch_t)( LibTiePieHandle_t hDevice , void* pBufferCh1 , void* pBufferCh2 , void* pBufferCh3 , void* pBufferCh4 , void* pBufferCh5 , void* pBufferCh6 , void* pBufferCh7 , uint64_t qwStartIndex , uint64_t qwSampleCount );
#else
uint64_t ScpGetDataRaw7Ch( LibTiePieHandle_t hDevice , void* pBufferCh1 , void* pBufferCh2 , void* pBufferCh3 , void* pBufferCh4 , void* pBufferCh5 , void* pBufferCh6 , void* pBufferCh7 , uint64_t qwStartIndex , uint64_t qwSampleCount );
#endif

/**
 * \brief Get raw measurement data.
 *
 * \param[in] hDevice A \ref OpenDev "device handle".
 * \param[out] pBufferCh1 Pointer to buffer for channel 1 data or \c NULL.
 * \param[out] pBufferCh2 Pointer to buffer for channel 2 data or \c NULL.
 * \param[out] pBufferCh3 Pointer to buffer for channel 3 data or \c NULL.
 * \param[out] pBufferCh4 Pointer to buffer for channel 4 data or \c NULL.
 * \param[out] pBufferCh5 Pointer to buffer for channel 5 data or \c NULL.
 * \param[out] pBufferCh6 Pointer to buffer for channel 6 data or \c NULL.
 * \param[out] pBufferCh7 Pointer to buffer for channel 7 data or \c NULL.
 * \param[out] pBufferCh8 Pointer to buffer for channel 8 data or \c NULL.
 * \param[in] qwStartIndex Position in record to start reading.
 * \param[in] qwSampleCount Number of samples to read.
 * \return Number of samples read.
 * \since 0.9.11
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef uint64_t(*LibTiePieScpGetDataRaw8Ch_t)( LibTiePieHandle_t hDevice , void* pBufferCh1 , void* pBufferCh2 , void* pBufferCh3 , void* pBufferCh4 , void* pBufferCh5 , void* pBufferCh6 , void* pBufferCh7 , void* pBufferCh8 , uint64_t qwStartIndex , uint64_t qwSampleCount );
#else
uint64_t ScpGetDataRaw8Ch( LibTiePieHandle_t hDevice , void* pBufferCh1 , void* pBufferCh2 , void* pBufferCh3 , void* pBufferCh4 , void* pBufferCh5 , void* pBufferCh6 , void* pBufferCh7 , void* pBufferCh8 , uint64_t qwStartIndex , uint64_t qwSampleCount );
#endif

/**
 * \brief Get raw data type.
 *
 * \param[in] hDevice A \ref OpenDev "device handle".
 * \param[in] wCh Channel number, \c 0 to <tt>ScpGetChannelCount() - 1</tt>.
 * \return \ref DATARAWTYPE_ "Raw data type".
 * \since 0.4.0
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef uint32_t(*LibTiePieScpChGetDataRawType_t)( LibTiePieHandle_t hDevice , uint16_t wCh );
#else
uint32_t ScpChGetDataRawType( LibTiePieHandle_t hDevice , uint16_t wCh );
#endif

/**
 * \brief Get possible raw data minimum, equal to zero and maximum values.
 *
 * \param[in] hDevice A \ref OpenDev "device handle".
 * \param[in] wCh Channel number, \c 0 to <tt>ScpGetChannelCount() - 1</tt>.
 * \param[out] pMin Pointer to buffer for possible minimum raw data value, or \c NULL.
 * \param[out] pZero Pointer to buffer for equal to zero raw data value, or \c NULL.
 * \param[out] pMax Pointer to buffer for possible maximum raw data value, or \c NULL.
 * \see ScpChGetDataRawValueMin
 * \see ScpChGetDataRawValueZero
 * \see ScpChGetDataRawValueMax
 * \since 0.4.0
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef void(*LibTiePieScpChGetDataRawValueRange_t)( LibTiePieHandle_t hDevice , uint16_t wCh , int64_t* pMin , int64_t* pZero , int64_t* pMax );
#else
void ScpChGetDataRawValueRange( LibTiePieHandle_t hDevice , uint16_t wCh , int64_t* pMin , int64_t* pZero , int64_t* pMax );
#endif

/**
 * \brief Get possible raw data minimum value.
 *
 * \param[in] hDevice A \ref OpenDev "device handle".
 * \param[in] wCh Channel number, \c 0 to <tt>ScpGetChannelCount() - 1</tt>.
 * \return Possible raw data minimum value.
 * \see ScpChGetDataRawValueZero
 * \see ScpChGetDataRawValueMax
 * \see ScpChGetDataRawValueRange
 * \since 0.4.0
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef int64_t(*LibTiePieScpChGetDataRawValueMin_t)( LibTiePieHandle_t hDevice , uint16_t wCh );
#else
int64_t ScpChGetDataRawValueMin( LibTiePieHandle_t hDevice , uint16_t wCh );
#endif

/**
 * \brief Get raw data value which equals zero.
 *
 * \param[in] hDevice A \ref OpenDev "device handle".
 * \param[in] wCh Channel number, \c 0 to <tt>ScpGetChannelCount() - 1</tt>.
 * \return Raw data value which equals zero.
 * \see ScpChGetDataRawValueMin
 * \see ScpChGetDataRawValueMax
 * \see ScpChGetDataRawValueRange
 * \since 0.4.0
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef int64_t(*LibTiePieScpChGetDataRawValueZero_t)( LibTiePieHandle_t hDevice , uint16_t wCh );
#else
int64_t ScpChGetDataRawValueZero( LibTiePieHandle_t hDevice , uint16_t wCh );
#endif

/**
 * \brief Get possible raw data maximum value.
 *
 * \param[in] hDevice A \ref OpenDev "device handle".
 * \param[in] wCh Channel number, \c 0 to <tt>ScpGetChannelCount() - 1</tt>.
 * \return Possible raw data maximum value.
 * \see ScpChGetDataRawValueMin
 * \see ScpChGetDataRawValueZero
 * \see ScpChGetDataRawValueRange
 * \since 0.4.0
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef int64_t(*LibTiePieScpChGetDataRawValueMax_t)( LibTiePieHandle_t hDevice , uint16_t wCh );
#else
int64_t ScpChGetDataRawValueMax( LibTiePieHandle_t hDevice , uint16_t wCh );
#endif

/**
 * \brief Check whether the ranges maximum is reachable.
 *
 * \param[in] hDevice A \ref OpenDev "device handle".
 * \param[in] wCh Channel number, \c 0 to <tt>ScpGetChannelCount() - 1</tt>.
 * \return #BOOL8_TRUE if reachable, #BOOL8_FALSE otherwise.
 * \since 0.4.0
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef bool8_t(*LibTiePieScpChIsRangeMaxReachable_t)( LibTiePieHandle_t hDevice , uint16_t wCh );
#else
bool8_t ScpChIsRangeMaxReachable( LibTiePieHandle_t hDevice , uint16_t wCh );
#endif

/**
 * \}
 * \defgroup scp_data_async Asynchronous
 * \{
 */

// Workaround: Without this line Doxygen adds the documentation below to the group above.

/**
 * \brief Check whether the data download is completed.
 *
 * \param[in] hDevice A \ref OpenDev "device handle" identifying the oscilloscope.
 * \return #BOOL8_TRUE if completed, #BOOL8_FALSE otherwise.
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef bool8_t(*LibTiePieScpIsGetDataAsyncCompleted_t)( LibTiePieHandle_t hDevice );
#else
bool8_t ScpIsGetDataAsyncCompleted( LibTiePieHandle_t hDevice );
#endif

/**
 * \brief Start the download of measurement data for specified channels.
 *
 * \param[in] hDevice A \ref OpenDev "device handle" identifying the oscilloscope.
 * \param[out] pBuffers A pointer to a buffer with pointers to buffers for channel data, the pointer buffer may contain \c NULL pointers.
 * \param[in] wChannelCount The number of pointers in the pointer buffer.
 * \param[in] qwStartIndex The position in the record to start reading.
 * \param[in] qwSampleCount The number of samples to read.
 * \return #BOOL8_TRUE if successful, #BOOL8_FALSE otherwise.
 * \since 0.6
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef bool8_t(*LibTiePieScpStartGetDataAsync_t)( LibTiePieHandle_t hDevice , float** pBuffers , uint16_t wChannelCount , uint64_t qwStartIndex , uint64_t qwSampleCount );
#else
bool8_t ScpStartGetDataAsync( LibTiePieHandle_t hDevice , float** pBuffers , uint16_t wChannelCount , uint64_t qwStartIndex , uint64_t qwSampleCount );
#endif

/**
 * \brief Start the download of raw measurement data for specified channels.
 *
 * \param[in] hDevice A \ref OpenDev "device handle".
 * \param[out] pBuffers Pointer to buffer with pointers to buffer for channel data, pointer buffer may contain \c NULL pointers.
 * \param[in] wChannelCount Number of pointers in pointer buffer.
 * \param[in] qwStartIndex Position in record to start reading.
 * \param[in] qwSampleCount Number of samples to read.
 * \return #BOOL8_TRUE if successful, #BOOL8_FALSE otherwise.
 * \since 0.6
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef bool8_t(*LibTiePieScpStartGetDataAsyncRaw_t)( LibTiePieHandle_t hDevice , void** pBuffers , uint16_t wChannelCount , uint64_t qwStartIndex , uint64_t qwSampleCount );
#else
bool8_t ScpStartGetDataAsyncRaw( LibTiePieHandle_t hDevice , void** pBuffers , uint16_t wChannelCount , uint64_t qwStartIndex , uint64_t qwSampleCount );
#endif

/**
 * \brief Cancel the download of measurement data.
 *
 * \param[in] hDevice A \ref OpenDev "device handle".
 * \return #BOOL8_TRUE if successful, #BOOL8_FALSE otherwise.
 * \since 0.6
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef bool8_t(*LibTiePieScpCancelGetDataAsync_t)( LibTiePieHandle_t hDevice );
#else
bool8_t ScpCancelGetDataAsync( LibTiePieHandle_t hDevice );
#endif

/**
 * \}
 * \endcond
 * \}
 * \defgroup scp_notifications Notifications
 * \{
 * \brief Functions to set notifications that are triggered when the oscilloscope measurement status is changed.
 *
 * LibTiePie can notify the calling application that the oscilloscope measurement status is changed in different ways:
 * - by calling callback functions
 * - by setting events
 * - by sending messages (Windows only)
 *
 * \defgroup scp_notifications_dataReady Data ready
 * \{
 * \brief Functions to set notifications that are triggered when the oscilloscope has new measurement data ready.
 */

// Workaround: Without this line Doxygen adds the documentation below to the group above.

/**
 * \deprecated Will be removed in future version, see: ObjSetEventCallback()
 * \brief Set a callback function which is called when the oscilloscope has new measurement data ready.
 *
 * \param[in] hDevice A \ref OpenDev "device handle" identifying the oscilloscope.
 * \param[in] pCallback A pointer to the callback function. Use \c NULL to disable.
 * \param[in] pData Optional user data.
 * \par Status values
 *   <table class="params">
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_HANDLE "INVALID_HANDLE"</td>         <td>The handle is not a valid oscilloscope handle.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_OBJECT_GONE "OBJECT_GONE"</td>            <td>The object indicated by the handle is no longer available.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_LIBRARY_NOT_INITIALIZED "LIBRARY_NOT_INITIALIZED"</td><td>The library is not initialized, see LibInit().</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_SUCCESS "SUCCESS"</td>                <td>The function executed successfully.</td></tr>
 *   </table>
 * \see ScpIsDataReady
 * \since 0.4.0
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef void(*LibTiePieScpSetCallbackDataReady_t)( LibTiePieHandle_t hDevice , TpCallback_t pCallback , void* pData );
#else
void ScpSetCallbackDataReady( LibTiePieHandle_t hDevice , TpCallback_t pCallback , void* pData );
#endif

/**
 * \}
 * \defgroup scp_notifications_dataOverflow Data overflow
 * \{
 * \brief Functions to set notifications that are triggered when the oscilloscope streaming measurement caused an data overflow.
 *
 * This occurs when during a streaming measurement new measurement data is available while previous measured data is not collected yet.
 *
 */

// Workaround: Without this line Doxygen adds the documentation below to the group above.

/**
 * \deprecated Will be removed in future version, see: ObjSetEventCallback()
 * \brief Set a callback function which is called when the oscilloscope streaming measurement caused an data overflow.
 *
 * \param[in] hDevice A \ref OpenDev "device handle" identifying the oscilloscope.
 * \param[in] pCallback A pointer to the callback function. Use \c NULL to disable.
 * \param[in] pData Optional user data.
 * \par Status values
 *   <table class="params">
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_HANDLE "INVALID_HANDLE"</td>         <td>The handle is not a valid oscilloscope handle.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_OBJECT_GONE "OBJECT_GONE"</td>            <td>The object indicated by the handle is no longer available.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_LIBRARY_NOT_INITIALIZED "LIBRARY_NOT_INITIALIZED"</td><td>The library is not initialized, see LibInit().</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_SUCCESS "SUCCESS"</td>                <td>The function executed successfully.</td></tr>
 *   </table>
 * \see ScpIsDataOverflow
 * \since 0.4.0
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef void(*LibTiePieScpSetCallbackDataOverflow_t)( LibTiePieHandle_t hDevice , TpCallback_t pCallback , void* pData );
#else
void ScpSetCallbackDataOverflow( LibTiePieHandle_t hDevice , TpCallback_t pCallback , void* pData );
#endif

/**
 * \}
 * \defgroup scp_notifications_connectionTestCompleted Connection test completed
 * \{
 * \brief Functions to set notifications that are triggered when the oscilloscope connection test is completed.
 */

// Workaround: Without this line Doxygen adds the documentation below to the group above.

/**
 * \deprecated Will be removed in future version, see: ObjSetEventCallback()
 * \brief Set a callback function which is called when the oscilloscope connection test is completed.
 *
 * \param[in] hDevice A \ref OpenDev "device handle" identifying the oscilloscope.
 * \param[in] pCallback A pointer to the callback function. Use \c NULL to disable.
 * \param[in] pData Optional user data.
 * \par Status values
 *   <table class="params">
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_HANDLE "INVALID_HANDLE"</td>         <td>The handle is not a valid oscilloscope handle.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_OBJECT_GONE "OBJECT_GONE"</td>            <td>The object indicated by the handle is no longer available.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_LIBRARY_NOT_INITIALIZED "LIBRARY_NOT_INITIALIZED"</td><td>The library is not initialized, see LibInit().</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_SUCCESS "SUCCESS"</td>                <td>The function executed successfully.</td></tr>
 *   </table>
 * \see ScpIsConnectionTestCompleted
 * \since 0.4.0
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef void(*LibTiePieScpSetCallbackConnectionTestCompleted_t)( LibTiePieHandle_t hDevice , TpCallback_t pCallback , void* pData );
#else
void ScpSetCallbackConnectionTestCompleted( LibTiePieHandle_t hDevice , TpCallback_t pCallback , void* pData );
#endif

/**
 * \}
 * \defgroup scp_notifications_triggered Triggered
 * \{
 * \brief Functions to set notifications that are triggered when the oscilloscope is triggered.
 */

// Workaround: Without this line Doxygen adds the documentation below to the group above.

/**
 * \deprecated Will be removed in future version, see: ObjSetEventCallback()
 * \brief Set a callback function which is called when the oscilloscope is triggered.
 *
 * \param[in] hDevice A \ref OpenDev "device handle" identifying the oscilloscope.
 * \param[in] pCallback A pointer to the callback function. Use \c NULL to disable.
 * \param[in] pData Optional user data.
 * \par Status values
 *   <table class="params">
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_HANDLE "INVALID_HANDLE"</td>         <td>The handle is not a valid oscilloscope handle.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_OBJECT_GONE "OBJECT_GONE"</td>            <td>The object indicated by the handle is no longer available.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_LIBRARY_NOT_INITIALIZED "LIBRARY_NOT_INITIALIZED"</td><td>The library is not initialized, see LibInit().</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_SUCCESS "SUCCESS"</td>                <td>The function executed successfully.</td></tr>
 *   </table>
 * \since 0.5
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef void(*LibTiePieScpSetCallbackTriggered_t)( LibTiePieHandle_t hDevice , TpCallback_t pCallback , void* pData );
#else
void ScpSetCallbackTriggered( LibTiePieHandle_t hDevice , TpCallback_t pCallback , void* pData );
#endif

/**
 * \}
 */

#ifdef LIBTIEPIE_LINUX

/**
 * \ingroup scp_notifications_dataReady
 * \deprecated Will be removed in future version, see: ObjSetEventEvent()
 * \brief Set an event file descriptor which is set when the oscilloscope has new measurement data ready.
 *
 * \param[in] hDevice A \ref OpenDev "device handle" identifying the oscilloscope.
 * \param[in] fdEvent An event file descriptor. Use \c &lt;0 to disable.
 * \note This function is only available on GNU/Linux.
 * \par Status values
 *   <table class="params">
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_HANDLE "INVALID_HANDLE"</td>         <td>The handle is not a valid oscilloscope handle.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_OBJECT_GONE "OBJECT_GONE"</td>            <td>The object indicated by the handle is no longer available.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_LIBRARY_NOT_INITIALIZED "LIBRARY_NOT_INITIALIZED"</td><td>The library is not initialized, see LibInit().</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_SUCCESS "SUCCESS"</td>                <td>The function executed successfully.</td></tr>
 *   </table>
 * \see ScpIsDataReady
 * \since 0.4.0
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef void(*LibTiePieScpSetEventDataReady_t)( LibTiePieHandle_t hDevice , int fdEvent );
#else
void ScpSetEventDataReady( LibTiePieHandle_t hDevice , int fdEvent );
#endif

/**
 * \ingroup scp_notifications_dataOverflow
 * \deprecated Will be removed in future version, see: ObjSetEventEvent()
 * \brief Set an event file descriptor which is set when the oscilloscope streaming measurement caused an data overflow.
 *
 * \param[in] hDevice A \ref OpenDev "device handle" identifying the oscilloscope.
 * \param[in] fdEvent An event file descriptor. Use \c &lt;0 to disable.
 * \note This function is only available on GNU/Linux.
 * \par Status values
 *   <table class="params">
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_HANDLE "INVALID_HANDLE"</td>         <td>The handle is not a valid oscilloscope handle.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_OBJECT_GONE "OBJECT_GONE"</td>            <td>The object indicated by the handle is no longer available.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_LIBRARY_NOT_INITIALIZED "LIBRARY_NOT_INITIALIZED"</td><td>The library is not initialized, see LibInit().</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_SUCCESS "SUCCESS"</td>                <td>The function executed successfully.</td></tr>
 *   </table>
 * \see ScpIsDataOverflow
 * \since 0.4.0
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef void(*LibTiePieScpSetEventDataOverflow_t)( LibTiePieHandle_t hDevice , int fdEvent );
#else
void ScpSetEventDataOverflow( LibTiePieHandle_t hDevice , int fdEvent );
#endif

/**
 * \ingroup scp_notifications_connectionTestCompleted
 * \deprecated Will be removed in future version, see: ObjSetEventEvent()
 * \brief Set an event file descriptor which is set when the oscilloscope connection test is completed.
 *
 * \param[in] hDevice A \ref OpenDev "device handle" identifying the oscilloscope.
 * \param[in] fdEvent An event file descriptor. Use \c &lt;0 to disable.
 * \note This function is only available on GNU/Linux.
 * \par Status values
 *   <table class="params">
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_HANDLE "INVALID_HANDLE"</td>         <td>The handle is not a valid oscilloscope handle.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_OBJECT_GONE "OBJECT_GONE"</td>            <td>The object indicated by the handle is no longer available.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_LIBRARY_NOT_INITIALIZED "LIBRARY_NOT_INITIALIZED"</td><td>The library is not initialized, see LibInit().</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_SUCCESS "SUCCESS"</td>                <td>The function executed successfully.</td></tr>
 *   </table>
 * \see ScpIsConnectionTestCompleted
 * \since 0.4.0
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef void(*LibTiePieScpSetEventConnectionTestCompleted_t)( LibTiePieHandle_t hDevice , int fdEvent );
#else
void ScpSetEventConnectionTestCompleted( LibTiePieHandle_t hDevice , int fdEvent );
#endif

/**
 * \ingroup scp_notifications_triggered
 * \deprecated Will be removed in future version, see: ObjSetEventEvent()
 * \brief Set an event file descriptor which is set when the oscilloscope is triggered.
 *
 * \param[in] hDevice A \ref OpenDev "device handle" identifying the oscilloscope.
 * \param[in] fdEvent An event file descriptor. Use \c &lt;0 to disable.
 * \note This function is only available on GNU/Linux.
 * \par Status values
 *   <table class="params">
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_HANDLE "INVALID_HANDLE"</td>         <td>The handle is not a valid oscilloscope handle.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_OBJECT_GONE "OBJECT_GONE"</td>            <td>The object indicated by the handle is no longer available.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_LIBRARY_NOT_INITIALIZED "LIBRARY_NOT_INITIALIZED"</td><td>The library is not initialized, see LibInit().</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_SUCCESS "SUCCESS"</td>                <td>The function executed successfully.</td></tr>
 *   </table>
 * \since 0.5
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef void(*LibTiePieScpSetEventTriggered_t)( LibTiePieHandle_t hDevice , int fdEvent );
#else
void ScpSetEventTriggered( LibTiePieHandle_t hDevice , int fdEvent );
#endif

#endif

#ifdef LIBTIEPIE_WINDOWS

/**
 * \ingroup scp_notifications_dataReady
 * \deprecated Will be removed in future version, see: ObjSetEventEvent()
 * \brief Set an event object handle which is set when the oscilloscope has new measurement data ready.
 *
 * \param[in] hDevice A \ref OpenDev "device handle" identifying the oscilloscope.
 * \param[in] hEvent A handle to the event object. Use \c NULL to disable.
 * \note This function is only available on Windows.
 * \par Status values
 *   <table class="params">
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_HANDLE "INVALID_HANDLE"</td>         <td>The handle is not a valid oscilloscope handle.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_OBJECT_GONE "OBJECT_GONE"</td>            <td>The object indicated by the handle is no longer available.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_LIBRARY_NOT_INITIALIZED "LIBRARY_NOT_INITIALIZED"</td><td>The library is not initialized, see LibInit().</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_SUCCESS "SUCCESS"</td>                <td>The function executed successfully.</td></tr>
 *   </table>
 * \see ScpIsDataReady
 * \since 0.4.0
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef void(*LibTiePieScpSetEventDataReady_t)( LibTiePieHandle_t hDevice , HANDLE hEvent );
#else
void ScpSetEventDataReady( LibTiePieHandle_t hDevice , HANDLE hEvent );
#endif

/**
 * \ingroup scp_notifications_dataOverflow
 * \deprecated Will be removed in future version, see: ObjSetEventEvent()
 * \brief Set an event object handle which is set when the oscilloscope streaming measurement caused an data overflow.
 *
 * \param[in] hDevice A \ref OpenDev "device handle" identifying the oscilloscope.
 * \param[in] hEvent A handle to the event object. Use \c NULL to disable.
 * \note This function is only available on Windows.
 * \par Status values
 *   <table class="params">
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_HANDLE "INVALID_HANDLE"</td>         <td>The handle is not a valid oscilloscope handle.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_OBJECT_GONE "OBJECT_GONE"</td>            <td>The object indicated by the handle is no longer available.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_LIBRARY_NOT_INITIALIZED "LIBRARY_NOT_INITIALIZED"</td><td>The library is not initialized, see LibInit().</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_SUCCESS "SUCCESS"</td>                <td>The function executed successfully.</td></tr>
 *   </table>
 * \see ScpIsDataOverflow
 * \since 0.4.0
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef void(*LibTiePieScpSetEventDataOverflow_t)( LibTiePieHandle_t hDevice , HANDLE hEvent );
#else
void ScpSetEventDataOverflow( LibTiePieHandle_t hDevice , HANDLE hEvent );
#endif

/**
 * \ingroup scp_notifications_connectionTestCompleted
 * \deprecated Will be removed in future version, see: ObjSetEventEvent()
 * \brief Set an event object handle which is set when the oscilloscope connection test is completed.
 *
 * \param[in] hDevice A \ref OpenDev "device handle" identifying the oscilloscope.
 * \param[in] hEvent A handle to the event object. Use \c NULL to disable.
 * \note This function is only available on Windows.
 * \par Status values
 *   <table class="params">
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_HANDLE "INVALID_HANDLE"</td>         <td>The handle is not a valid oscilloscope handle.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_OBJECT_GONE "OBJECT_GONE"</td>            <td>The object indicated by the handle is no longer available.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_LIBRARY_NOT_INITIALIZED "LIBRARY_NOT_INITIALIZED"</td><td>The library is not initialized, see LibInit().</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_SUCCESS "SUCCESS"</td>                <td>The function executed successfully.</td></tr>
 *   </table>
 * \see ScpIsConnectionTestCompleted
 * \since 0.4.0
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef void(*LibTiePieScpSetEventConnectionTestCompleted_t)( LibTiePieHandle_t hDevice , HANDLE hEvent );
#else
void ScpSetEventConnectionTestCompleted( LibTiePieHandle_t hDevice , HANDLE hEvent );
#endif

/**
 * \ingroup scp_notifications_triggered
 * \deprecated Will be removed in future version, see: ObjSetEventEvent()
 * \brief Set an event object handle which is set when the oscilloscope is triggered.
 *
 * \param[in] hDevice A \ref OpenDev "device handle" identifying the oscilloscope.
 * \param[in] hEvent A handle to the event object. Use \c NULL to disable.
 * \note This function is only available on Windows.
 * \par Status values
 *   <table class="params">
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_HANDLE "INVALID_HANDLE"</td>         <td>The handle is not a valid oscilloscope handle.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_OBJECT_GONE "OBJECT_GONE"</td>            <td>The object indicated by the handle is no longer available.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_LIBRARY_NOT_INITIALIZED "LIBRARY_NOT_INITIALIZED"</td><td>The library is not initialized, see LibInit().</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_SUCCESS "SUCCESS"</td>                <td>The function executed successfully.</td></tr>
 *   </table>
 * \since 0.5
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef void(*LibTiePieScpSetEventTriggered_t)( LibTiePieHandle_t hDevice , HANDLE hEvent );
#else
void ScpSetEventTriggered( LibTiePieHandle_t hDevice , HANDLE hEvent );
#endif

/**
 * \ingroup scp_notifications_dataReady
 * \deprecated Will be removed in future version, see: ObjSetEventWindowHandle()
 * \brief Set a window handle to which a #WM_LIBTIEPIE_SCP_DATAREADY message is sent when the oscilloscope has new measurement data ready.
 *
 * \param[in] hDevice A \ref OpenDev "device handle" identifying the oscilloscope.
 * \param[in] hWnd A handle to the window whose window procedure is to receive the message. Use \c NULL to disable.
 * \param[in] wParam Optional user value for the \c wParam parameter of the message.
 * \param[in] lParam Optional user value for the \c lParam parameter of the message.
 * \note This function is only available on Windows.
 * \par Status values
 *   <table class="params">
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_HANDLE "INVALID_HANDLE"</td>         <td>The handle is not a valid oscilloscope handle.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_OBJECT_GONE "OBJECT_GONE"</td>            <td>The object indicated by the handle is no longer available.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_LIBRARY_NOT_INITIALIZED "LIBRARY_NOT_INITIALIZED"</td><td>The library is not initialized, see LibInit().</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_SUCCESS "SUCCESS"</td>                <td>The function executed successfully.</td></tr>
 *   </table>
 * \see ScpIsDataReady
 * \since 0.4.0
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef void(*LibTiePieScpSetMessageDataReady_t)( LibTiePieHandle_t hDevice , HWND hWnd , WPARAM wParam , LPARAM lParam );
#else
void ScpSetMessageDataReady( LibTiePieHandle_t hDevice , HWND hWnd , WPARAM wParam , LPARAM lParam );
#endif

/**
 * \ingroup scp_notifications_dataOverflow
 * \deprecated Will be removed in future version, see: ObjSetEventWindowHandle()
 * \brief Set a window handle to which a #WM_LIBTIEPIE_SCP_DATAOVERFLOW message is sent when the oscilloscope streaming measurement caused an data overflow.
 *
 * \param[in] hDevice A \ref OpenDev "device handle" identifying the oscilloscope.
 * \param[in] hWnd A handle to the window whose window procedure is to receive the message. Use \c NULL to disable.
 * \param[in] wParam Optional user value for the \c wParam parameter of the message.
 * \param[in] lParam Optional user value for the \c lParam parameter of the message.
 * \note This function is only available on Windows.
 * \par Status values
 *   <table class="params">
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_HANDLE "INVALID_HANDLE"</td>         <td>The handle is not a valid oscilloscope handle.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_OBJECT_GONE "OBJECT_GONE"</td>            <td>The object indicated by the handle is no longer available.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_LIBRARY_NOT_INITIALIZED "LIBRARY_NOT_INITIALIZED"</td><td>The library is not initialized, see LibInit().</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_SUCCESS "SUCCESS"</td>                <td>The function executed successfully.</td></tr>
 *   </table>
 * \see ScpIsDataOverflow
 * \since 0.4.0
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef void(*LibTiePieScpSetMessageDataOverflow_t)( LibTiePieHandle_t hDevice , HWND hWnd , WPARAM wParam , LPARAM lParam );
#else
void ScpSetMessageDataOverflow( LibTiePieHandle_t hDevice , HWND hWnd , WPARAM wParam , LPARAM lParam );
#endif

/**
 * \ingroup scp_notifications_connectionTestCompleted
 * \deprecated Will be removed in future version, see: ObjSetEventWindowHandle()
 * \brief Set a window handle to which a #WM_LIBTIEPIE_SCP_CONNECTIONTESTCOMPLETED message is sent when the oscilloscope connection test is completed.
 *
 * \param[in] hDevice A \ref OpenDev "device handle" identifying the oscilloscope.
 * \param[in] hWnd A handle to the window whose window procedure is to receive the message. Use \c NULL to disable.
 * \param[in] wParam Optional user value for the \c wParam parameter of the message.
 * \param[in] lParam Optional user value for the \c lParam parameter of the message.
 * \note This function is only available on Windows.
 * \par Status values
 *   <table class="params">
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_HANDLE "INVALID_HANDLE"</td>         <td>The handle is not a valid oscilloscope handle.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_OBJECT_GONE "OBJECT_GONE"</td>            <td>The object indicated by the handle is no longer available.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_LIBRARY_NOT_INITIALIZED "LIBRARY_NOT_INITIALIZED"</td><td>The library is not initialized, see LibInit().</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_SUCCESS "SUCCESS"</td>                <td>The function executed successfully.</td></tr>
 *   </table>
 * \see ScpIsConnectionTestCompleted
 * \since 0.4.0
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef void(*LibTiePieScpSetMessageConnectionTestCompleted_t)( LibTiePieHandle_t hDevice , HWND hWnd , WPARAM wParam , LPARAM lParam );
#else
void ScpSetMessageConnectionTestCompleted( LibTiePieHandle_t hDevice , HWND hWnd , WPARAM wParam , LPARAM lParam );
#endif

/**
 * \ingroup scp_notifications_triggered
 * \deprecated Will be removed in future version, see: ObjSetEventWindowHandle()
 * \brief Set a window handle to which a #WM_LIBTIEPIE_SCP_TRIGGERED message is sent when the oscilloscope is triggered.
 *
 * \param[in] hDevice A \ref OpenDev "device handle" identifying the oscilloscope.
 * \param[in] hWnd A handle to the window whose window procedure is to receive the message. Use \c NULL to disable.
 * \param[in] wParam Optional user value for the \c wParam parameter of the message.
 * \param[in] lParam Optional user value for the \c lParam parameter of the message.
 * \note This function is only available on Windows.
 * \par Status values
 *   <table class="params">
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_HANDLE "INVALID_HANDLE"</td>         <td>The handle is not a valid oscilloscope handle.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_OBJECT_GONE "OBJECT_GONE"</td>            <td>The object indicated by the handle is no longer available.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_LIBRARY_NOT_INITIALIZED "LIBRARY_NOT_INITIALIZED"</td><td>The library is not initialized, see LibInit().</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_SUCCESS "SUCCESS"</td>                <td>The function executed successfully.</td></tr>
 *   </table>
 * \since 0.5
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef void(*LibTiePieScpSetMessageTriggered_t)( LibTiePieHandle_t hDevice , HWND hWnd , WPARAM wParam , LPARAM lParam );
#else
void ScpSetMessageTriggered( LibTiePieHandle_t hDevice , HWND hWnd , WPARAM wParam , LPARAM lParam );
#endif

#endif

/**
 * \}
 * \defgroup scp_measurements Measurements
 * \{
 * \brief Functions to perform measurements.
 *
 *         Oscilloscopes can measure in block mode or in streaming mode. This is determined by the \ref scp_measurements_mode "measure mode".
 *
 *         Several \ref scp_measurements_status "polling routines" and \ref scp_notifications "notifications" are available to determine the measurement status.
 */

// Workaround: Without this line Doxygen adds the documentation below to the group above.

/**
 * \brief Start a single measurement.
 *
 * Use the measurement status \ref scp_measurements_status "functions" or \ref scp_notifications "notifications" to determine the status of a running measurement.
 *
 * \param[in] hDevice A \ref OpenDev "device handle" identifying the oscilloscope.
 * \return #BOOL8_TRUE if the measurement is started, #BOOL8_FALSE otherwise.
 * \par Status values
 *   <table class="params">
 *   <tr><td>\ref LIBTIEPIESTATUS_UNSUCCESSFUL "UNSUCCESSFUL"</td>           <td>The measurement could not be started.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_HANDLE "INVALID_HANDLE"</td>         <td>The handle is not a valid oscilloscope handle.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_OBJECT_GONE "OBJECT_GONE"</td>            <td>The object indicated by the handle is no longer available.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_LIBRARY_NOT_INITIALIZED "LIBRARY_NOT_INITIALIZED"</td><td>The library is not initialized, see LibInit().</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_MEASUREMENT_RUNNING "MEASUREMENT_RUNNING"</td>    <td>A measurement is already running.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_SUCCESS "SUCCESS"</td>                <td>The function executed successfully.</td></tr>
 *   </table>
 * \since 0.4.0
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef bool8_t(*LibTiePieScpStart_t)( LibTiePieHandle_t hDevice );
#else
bool8_t ScpStart( LibTiePieHandle_t hDevice );
#endif

/**
 * \brief Stop a running measurement.
 *
 * \param[in] hDevice A \ref OpenDev "device handle" identifying the oscilloscope.
 * \return #BOOL8_TRUE if the measurement is aborted, #BOOL8_FALSE otherwise.
 * \par Status values
 *   <table class="params">
 *   <tr><td>\ref LIBTIEPIESTATUS_UNSUCCESSFUL "UNSUCCESSFUL"</td>           <td>The measurement could not be stopped.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_HANDLE "INVALID_HANDLE"</td>         <td>The handle is not a valid oscilloscope handle.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_OBJECT_GONE "OBJECT_GONE"</td>            <td>The object indicated by the handle is no longer available.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_LIBRARY_NOT_INITIALIZED "LIBRARY_NOT_INITIALIZED"</td><td>The library is not initialized, see LibInit().</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_SUCCESS "SUCCESS"</td>                <td>The function executed successfully.</td></tr>
 *   </table>
 * \since 0.5
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef bool8_t(*LibTiePieScpStop_t)( LibTiePieHandle_t hDevice );
#else
bool8_t ScpStop( LibTiePieHandle_t hDevice );
#endif

/**
 * \brief Force a trigger.
 *
 * If the trigger conditions are set in such a way that the input signal(s) will never meet the trigger settings,
 * the instrument will wait forever.
 * Use this function to force a trigger, independent from the input signal(s).
 *
 * \param[in] hDevice A \ref OpenDev "device handle" identifying the oscilloscope.
 * \return #BOOL8_TRUE if succeeded, #BOOL8_FALSE otherwise.
 * \par Status values
 *   <table class="params">
 *   <tr><td>\ref LIBTIEPIESTATUS_UNSUCCESSFUL "UNSUCCESSFUL"</td>           <td>The trigger could not be forced.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_NOT_SUPPORTED "NOT_SUPPORTED"</td>          <td>The oscilloscope does not support force trigger.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_HANDLE "INVALID_HANDLE"</td>         <td>The handle is not a valid oscilloscope handle.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_OBJECT_GONE "OBJECT_GONE"</td>            <td>The object indicated by the handle is no longer available.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_LIBRARY_NOT_INITIALIZED "LIBRARY_NOT_INITIALIZED"</td><td>The library is not initialized, see LibInit().</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_SUCCESS "SUCCESS"</td>                <td>The function executed successfully.</td></tr>
 *   </table>
 * \return #BOOL8_TRUE if succeeded, #BOOL8_FALSE otherwise.
 * \since 0.5
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef bool8_t(*LibTiePieScpForceTrigger_t)( LibTiePieHandle_t hDevice );
#else
bool8_t ScpForceTrigger( LibTiePieHandle_t hDevice );
#endif

/**
 * \defgroup scp_measurements_mode Mode
 * \{
 * \brief Functions for controlling the measure mode.
 *
 * Oscilloscopes measure in block mode or in streaming mode.
 * This is determined by the \ref scp_measurements_mode "measure mode".
 *
 * \section ScpMeasurementsBlock Block mode
 *
 * When measuring in <b>block mode</b> (#MM_BLOCK), the oscilloscope uses its internal memory to store the measured data.
 * Once the pre defined number of samples is measured, measuring stops and the computer is notified that the measurement is ready.
 * The computer can collect the data and can then start a new measurement. There will be gaps between consecutive measurements.
 *
 * Advantage of block mode: Fast measurements using a high \ref scp_timebase_sampleFrequency "sample frequency" are possible.
 * Disadvantage of block mode: \ref scp_timebase_recordLength "Record length" is limited by the instrument's memory size.
 *
 * \section ScpMeasurementsStreaming Streaming mode
 *
 * When measuring in <b>streaming mode</b> (#MM_STREAM), the measured data is transferred continuously to the computer and collected in a buffer,
 * while the instrument remains measuring.
 * When a pre defined number of samples has been collected in the buffer, LibTiePie will notify the calling application that a new chunk of data
 * is available to be collected.
 * The calling application can then get that chunk of data and add it to previously collected data.
 * This makes it possible to perform long continuous measurements without gaps.
 *
 * Advantage of streaming mode: very long measurements are posible.
 * Disadvantage of streaming mode: the maximum sample frequency is limited by number of \ref scp_ch_enabled "enabled channels",
 * the selected \ref scp_resolution "resolution", the data transfer rate to computer and the computer speed.
 *
 * The size of the chunks is set using ScpSetRecordLength().
 * The combination of chunk size and \ref scp_timebase_sampleFrequency "sample frequency" determines the duration of a chunk and also the rate
 * at wich chunks are measured and need to be transferred.
 * When the computer can not keep up with the chunk rate and chunks are measured faster than the computer can process them,
 * the running measurement will be stopped and ScpIsDataOverflow() will return #BOOL8_TRUE and \ref scp_notifications_dataOverflow "data overflow notifications" will be triggered.
 *
 * By default the measure mode is set to: Block mode (#MM_BLOCK).
 */

// Workaround: Without this line Doxygen adds the documentation below to the group above.

/**
 * \brief Get the supported measure modes for a specified oscilloscope.
 *
 * \param[in] hDevice A \ref OpenDev "device handle" identifying the oscilloscope.
 * \return The supported measure modes, a set of OR-ed \ref MM_ "MM_*" values.
 * \par Status values
 *   <table class="params">
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_HANDLE "INVALID_HANDLE"</td>         <td>The handle is not a valid oscilloscope handle.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_OBJECT_GONE "OBJECT_GONE"</td>            <td>The object indicated by the handle is no longer available.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_LIBRARY_NOT_INITIALIZED "LIBRARY_NOT_INITIALIZED"</td><td>The library is not initialized, see LibInit().</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_SUCCESS "SUCCESS"</td>                <td>The function executed successfully.</td></tr>
 *   </table>
 * \see ScpGetMeasureMode
 * \see ScpSetMeasureMode
 * \since 0.4.0
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef uint32_t(*LibTiePieScpGetMeasureModes_t)( LibTiePieHandle_t hDevice );
#else
uint32_t ScpGetMeasureModes( LibTiePieHandle_t hDevice );
#endif

/**
 * \brief Get the current measure mode.
 *
 * \param[in] hDevice A \ref OpenDev "device handle" identifying the oscilloscope.
 * \return The currently selected measure mode, a \ref MM_ "MM_*" value.
 * \par Status values
 *   <table class="params">
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_HANDLE "INVALID_HANDLE"</td>         <td>The handle is not a valid oscilloscope handle.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_OBJECT_GONE "OBJECT_GONE"</td>            <td>The object indicated by the handle is no longer available.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_LIBRARY_NOT_INITIALIZED "LIBRARY_NOT_INITIALIZED"</td><td>The library is not initialized, see LibInit().</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_SUCCESS "SUCCESS"</td>                <td>The function executed successfully.</td></tr>
 *   </table>
 * \see ScpGetMeasureModes
 * \see ScpSetMeasureMode
 * \since 0.4.0
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef uint32_t(*LibTiePieScpGetMeasureMode_t)( LibTiePieHandle_t hDevice );
#else
uint32_t ScpGetMeasureMode( LibTiePieHandle_t hDevice );
#endif

/**
 * \brief Set the measure mode.
 *
 * \param[in] hDevice A \ref OpenDev "device handle" identifying the oscilloscope.
 * \param[in] dwMeasureMode The required measure mode, a \ref MM_ "MM_*" value.
 * \return The actually set measure mode, a \ref MM_ "MM_*" value.
 * \remark Changing the measure mode may affect the \ref scp_timebase_sampleFrequency "sample frequency" and/or \ref scp_timebase_recordLength "record length".
 * \par Status values
 *   <table class="params">
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_VALUE "INVALID_VALUE"</td>          <td>The requested measure mode is invalid.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_HANDLE "INVALID_HANDLE"</td>         <td>The handle is not a valid oscilloscope handle.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_OBJECT_GONE "OBJECT_GONE"</td>            <td>The object indicated by the handle is no longer available.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_LIBRARY_NOT_INITIALIZED "LIBRARY_NOT_INITIALIZED"</td><td>The library is not initialized, see LibInit().</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_SUCCESS "SUCCESS"</td>                <td>The function executed successfully.</td></tr>
 *   </table>
 * \see ScpGetMeasureModes
 * \see ScpGetMeasureMode
 * \since 0.4.0
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef uint32_t(*LibTiePieScpSetMeasureMode_t)( LibTiePieHandle_t hDevice , uint32_t dwMeasureMode );
#else
uint32_t ScpSetMeasureMode( LibTiePieHandle_t hDevice , uint32_t dwMeasureMode );
#endif

/**
 * \}
 * \defgroup scp_measurements_status Status
 * \{
 * \brief Functions to check the measurement status.
 *
 * These are all functions to poll the measurement status.
 * For some statuses also \ref scp_notifications "notifications" are available.
 */

// Workaround: Without this line Doxygen adds the documentation below to the group above.

/**
 * \brief Check whether the oscilloscope is currently measuring.
 *
 * \param[in] hDevice A \ref OpenDev "device handle" identifying the oscilloscope.
 * \return #BOOL8_TRUE if oscilloscope is measuring, #BOOL8_FALSE otherwise.
 * \par Status values
 *   <table class="params">
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_HANDLE "INVALID_HANDLE"</td>         <td>The handle is not a valid oscilloscope handle.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_OBJECT_GONE "OBJECT_GONE"</td>            <td>The object indicated by the handle is no longer available.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_LIBRARY_NOT_INITIALIZED "LIBRARY_NOT_INITIALIZED"</td><td>The library is not initialized, see LibInit().</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_SUCCESS "SUCCESS"</td>                <td>The function executed successfully.</td></tr>
 *   </table>
 * \since 0.4.0
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef bool8_t(*LibTiePieScpIsRunning_t)( LibTiePieHandle_t hDevice );
#else
bool8_t ScpIsRunning( LibTiePieHandle_t hDevice );
#endif

/**
 * \brief Check whether the oscilloscope has triggered.
 *
 * Once a measurement is ready, the triggered status can be checked to determine whether the oscilloscope was triggered.
 *
 * \param[in] hDevice A \ref OpenDev "device handle" identifying the oscilloscope.
 * \return #BOOL8_TRUE if oscilloscope has triggered, #BOOL8_FALSE otherwise.
 * \par Status values
 *   <table class="params">
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_HANDLE "INVALID_HANDLE"</td>         <td>The handle is not a valid oscilloscope handle.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_OBJECT_GONE "OBJECT_GONE"</td>            <td>The object indicated by the handle is no longer available.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_LIBRARY_NOT_INITIALIZED "LIBRARY_NOT_INITIALIZED"</td><td>The library is not initialized, see LibInit().</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_SUCCESS "SUCCESS"</td>                <td>The function executed successfully.</td></tr>
 *   </table>
 * \see ScpIsTimeOutTriggered
 * \see ScpIsForceTriggered
 * \see ScpChTrIsTriggered
 * \see ScpTrInIsTriggered
 * \since 0.4.0
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef bool8_t(*LibTiePieScpIsTriggered_t)( LibTiePieHandle_t hDevice );
#else
bool8_t ScpIsTriggered( LibTiePieHandle_t hDevice );
#endif

/**
 * \brief  Check whether the trigger was caused by the trigger time out.
 *
 * \param[in] hDevice A \ref OpenDev "device handle" identifying the oscilloscope.
 * \return #BOOL8_TRUE if the trigger was caused by the \ref scp_trigger_time_out "trigger time out", #BOOL8_FALSE otherwise.
 * \par Status values
 *   <table class="params">
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_HANDLE "INVALID_HANDLE"</td>         <td>The handle is not a valid oscilloscope handle.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_OBJECT_GONE "OBJECT_GONE"</td>            <td>The object indicated by the handle is no longer available.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_LIBRARY_NOT_INITIALIZED "LIBRARY_NOT_INITIALIZED"</td><td>The library is not initialized, see LibInit().</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_SUCCESS "SUCCESS"</td>                <td>The function executed successfully.</td></tr>
 *   </table>
 * \see ScpIsTriggered
 * \see ScpIsForceTriggered
 * \see ScpChTrIsTriggered
 * \see ScpTrInIsTriggered
 * \since 0.5
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef bool8_t(*LibTiePieScpIsTimeOutTriggered_t)( LibTiePieHandle_t hDevice );
#else
bool8_t ScpIsTimeOutTriggered( LibTiePieHandle_t hDevice );
#endif

/**
 * \brief Check whether the trigger was caused by ScpForceTrigger.
 *
 * \param[in] hDevice A \ref OpenDev "device handle" identifying the oscilloscope.
 * \return #BOOL8_TRUE if the trigger was caused by ScpForceTrigger, #BOOL8_FALSE otherwise.
 * \par Status values
 *   <table class="params">
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_HANDLE "INVALID_HANDLE"</td>         <td>The handle is not a valid oscilloscope handle.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_OBJECT_GONE "OBJECT_GONE"</td>            <td>The object indicated by the handle is no longer available.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_LIBRARY_NOT_INITIALIZED "LIBRARY_NOT_INITIALIZED"</td><td>The library is not initialized, see LibInit().</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_SUCCESS "SUCCESS"</td>                <td>The function executed successfully.</td></tr>
 *   </table>
 * \see ScpIsTriggered
 * \see ScpIsTimeOutTriggered
 * \see ScpChTrIsTriggered
 * \see ScpTrInIsTriggered
 * \since 0.5
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef bool8_t(*LibTiePieScpIsForceTriggered_t)( LibTiePieHandle_t hDevice );
#else
bool8_t ScpIsForceTriggered( LibTiePieHandle_t hDevice );
#endif

/**
 * \brief Check whether new, unread measured data is available.
 *
 * When measuring in \ref ScpMeasurementsBlock "block mode", the data ready status is set when the measurement is ready and the measured data is
 * available.
 *
 * When measuring in \ref ScpMeasurementsStreaming "streaming mode", the data ready status is set when one or more new chunks of data are available.
 *
 * The status is cleared by getting the data, using one of the \ref scp_data "ScpGetData*" routines.
 * If more than one chunk of unread data is available, multiple calls to ScpGetData* are required to clear the status.
 *
 * \param[in] hDevice A \ref OpenDev "device handle" identifying the oscilloscope.
 * \return #BOOL8_TRUE if new measured data is available, #BOOL8_FALSE otherwise.
 * \par Status values
 *   <table class="params">
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_HANDLE "INVALID_HANDLE"</td>         <td>The handle is not a valid oscilloscope handle.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_OBJECT_GONE "OBJECT_GONE"</td>            <td>The object indicated by the handle is no longer available.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_LIBRARY_NOT_INITIALIZED "LIBRARY_NOT_INITIALIZED"</td><td>The library is not initialized, see LibInit().</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_SUCCESS "SUCCESS"</td>                <td>The function executed successfully.</td></tr>
 *   </table>
 * \see notification scp_notifications_dataReady
 * \since 0.4.0
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef bool8_t(*LibTiePieScpIsDataReady_t)( LibTiePieHandle_t hDevice );
#else
bool8_t ScpIsDataReady( LibTiePieHandle_t hDevice );
#endif

/**
 * \brief Check whether a data overflow has occurred.
 *
 * During measuring in \ref ScpMeasurementsStreaming "streaming mode", new chunks of measured data will become available.
 * When these chunks are not read fast enough, the number of available chunks will increase.
 * When the available buffer space for these chunks is full, the streaming measurement will be aborted and the data overflow status will be set.
 * The chunks of data that were already buffered, remain available to be read.
 *
 * \param[in] hDevice A \ref OpenDev "device handle" identifying the oscilloscope.
 * \return #BOOL8_TRUE if overflow occurred, #BOOL8_FALSE otherwise.
 * \par Status values
 *   <table class="params">
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_HANDLE "INVALID_HANDLE"</td>         <td>The handle is not a valid oscilloscope handle.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_OBJECT_GONE "OBJECT_GONE"</td>            <td>The object indicated by the handle is no longer available.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_LIBRARY_NOT_INITIALIZED "LIBRARY_NOT_INITIALIZED"</td><td>The library is not initialized, see LibInit().</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_SUCCESS "SUCCESS"</td>                <td>The function executed successfully.</td></tr>
 *   </table>
 * \see notification scp_notifications_dataOverflow
 * \since 0.4.0
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef bool8_t(*LibTiePieScpIsDataOverflow_t)( LibTiePieHandle_t hDevice );
#else
bool8_t ScpIsDataOverflow( LibTiePieHandle_t hDevice );
#endif

/**
 * \}
 * \}
 * \defgroup scp_resolution Resolution
 * \{
 * \brief Functions to control the oscilloscope resolution.
 *
 *         The resolution determines how accurate the amplitude of a signal can be measured.
 *         The higher the resolution, the more accurate the input signal can be reconstructed.
 *
 *         Devices can support multiple resolutions, use ScpGetResolutions() to determine the available resolutions for a device.
 *
 *         Besides native hardware resolutions, also enhanced resolutions can be available for a device.
 *         Use ScpIsResolutionEnhanced() to determine whether the current resolution is a native hardware resolution or an enhanced resolution.
 *
 *         The resolution can be set manually, but can also be set automatically, when \ref scp_resolution_mode "auto resolution mode" is enabled.
 *
 * \defgroup scp_resolution_mode Auto resolution mode
 * \{
 * \brief Functions to control the auto resolution mode.
 *
 *           The resolution can be set manually, but can also be set automatically, based on the selected \ref scp_timebase_sampleFrequency
 *           "sample frequency".
 *           Use ScpGetAutoResolutionModes() to determine the available auto resolution modes.
 *           Possible auto resolution modes are:
 *           - #AR_DISABLED : Resolution does not automatically change.
 *           - #AR_NATIVEONLY : Highest possible native resolution for the current sample frequency is used.
 *           - #AR_ALL : Highest possible native or enhanced resolution for the current sample frequency is used.
 *
 *           When auto resolution mode is set to #AR_DISABLED, the selected resolution will determine the maximum available sample frequency
 *           of the oscilloscope.
 *           When auto resolution mode is enabled, the selected sample frequency will determine the resolution of the oscilloscope.
 *
 *           Changing thesample frequency may change the resolution if auto resolution mode is #AR_NATIVEONLY or #AR_ALL.
 *
 *           Manually setting a resolution will set auto resolution mode to #AR_DISABLED.
 *
 *           By default the auto resolution mode is set to #AR_DISABLED for the Handyprobe HP3 and to #AR_NATIVEONLY for all other supported
 *           instruments.
 */

// Workaround: Without this line Doxygen adds the documentation below to the group above.

/**
 * \brief Get the supported auto resolution modes of the specified oscilloscope.
 *
 * \param[in] hDevice A \ref OpenDev "device handle" identifying the oscilloscope.
 * \return The supported auto resolution modes, a set of OR-ed \ref AR_ "AR_*" values, #ARM_NONE when unsuccessful.
 * \par Status values
 *   <table class="params">
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_HANDLE "INVALID_HANDLE"</td>         <td>The handle is not a valid oscilloscope handle.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_OBJECT_GONE "OBJECT_GONE"</td>            <td>The object indicated by the handle is no longer available.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_LIBRARY_NOT_INITIALIZED "LIBRARY_NOT_INITIALIZED"</td><td>The library is not initialized, see LibInit().</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_SUCCESS "SUCCESS"</td>                <td>The function executed successfully.</td></tr>
 *   </table>
 * \see ScpGetAutoResolutionMode
 * \see ScpSetAutoResolutionMode
 * \since 0.4.3
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef uint32_t(*LibTiePieScpGetAutoResolutionModes_t)( LibTiePieHandle_t hDevice );
#else
uint32_t ScpGetAutoResolutionModes( LibTiePieHandle_t hDevice );
#endif

/**
 * \brief Get the current auto resolution mode of the specified oscilloscope.
 *
 * \param[in] hDevice A \ref OpenDev "device handle" identifying the oscilloscope.
 * \return The currently selected auto resolution mode, a \ref AR_ "AR_*" value, #AR_UNKNOWN when unsuccessful.
 * \par Status values
 *   <table class="params">
 *   <tr><td>\ref LIBTIEPIESTATUS_NOT_SUPPORTED "NOT_SUPPORTED"</td>          <td>Auto resolution is not supported by the hardware.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_HANDLE "INVALID_HANDLE"</td>         <td>The handle is not a valid oscilloscope handle.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_OBJECT_GONE "OBJECT_GONE"</td>            <td>The object indicated by the handle is no longer available.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_LIBRARY_NOT_INITIALIZED "LIBRARY_NOT_INITIALIZED"</td><td>The library is not initialized, see LibInit().</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_SUCCESS "SUCCESS"</td>                <td>The function executed successfully.</td></tr>
 *   </table>
 * \see ScpGetAutoResolutionModes
 * \see ScpSetAutoResolutionMode
 * \since 0.4.3
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef uint32_t(*LibTiePieScpGetAutoResolutionMode_t)( LibTiePieHandle_t hDevice );
#else
uint32_t ScpGetAutoResolutionMode( LibTiePieHandle_t hDevice );
#endif

/**
 * \brief Set the auto resolution mode of the specified oscilloscope.
 *
 * \param[in] hDevice A \ref OpenDev "device handle" identifying the oscilloscope.
 * \param[in] dwAutoResolutionMode The required auto resolution mode, a \ref AR_ "AR_*" value.
 * \return The actually set auto resolution mode, a \ref AR_ "AR_*" value, #AR_UNKNOWN when unsuccessful.
 * \par Status values
 *   <table class="params">
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_VALUE "INVALID_VALUE"</td>          <td>The requested value is invalid.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_NOT_SUPPORTED "NOT_SUPPORTED"</td>          <td>Auto resolution is not supported by the hardware.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_HANDLE "INVALID_HANDLE"</td>         <td>The handle is not a valid oscilloscope handle.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_OBJECT_GONE "OBJECT_GONE"</td>            <td>The object indicated by the handle is no longer available.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_LIBRARY_NOT_INITIALIZED "LIBRARY_NOT_INITIALIZED"</td><td>The library is not initialized, see LibInit().</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_SUCCESS "SUCCESS"</td>                <td>The function executed successfully.</td></tr>
 *   </table>
 * \see ScpGetAutoResolutionModes
 * \see ScpGetAutoResolutionMode
 * \since 0.4.3
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef uint32_t(*LibTiePieScpSetAutoResolutionMode_t)( LibTiePieHandle_t hDevice , uint32_t dwAutoResolutionMode );
#else
uint32_t ScpSetAutoResolutionMode( LibTiePieHandle_t hDevice , uint32_t dwAutoResolutionMode );
#endif

/**
 * \}
 * \brief Get an array with the supported resolutions of the specified oscilloscope.
 *
 * The caller must assure that the array is available and that enough memory is allocated.
 *
 * \param[in] hDevice A \ref OpenDev "device handle" identifying the oscilloscope.
 * \param[out] pList A pointer to an array to contain the supported resolutions, or \c NULL.
 * \param[in] dwLength The number of elements in the array.
 * \return Total number of supported resolutions, or \c 0 when unsuccessful.
 * \par Status values
 *   <table class="params">
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_HANDLE "INVALID_HANDLE"</td>         <td>The handle is not a valid oscilloscope handle.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_OBJECT_GONE "OBJECT_GONE"</td>            <td>The object indicated by the handle is no longer available.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_LIBRARY_NOT_INITIALIZED "LIBRARY_NOT_INITIALIZED"</td><td>The library is not initialized, see LibInit().</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_SUCCESS "SUCCESS"</td>                <td>The function executed successfully.</td></tr>
 *   </table>
 *
 * \par Example
 * \code{.c}
 * uint8_t byResolutionCount = ScpGetResolutions( hDevice , NULL , 0 );
 * uint8_t* pResolutions = malloc( sizeof( uint8_t ) * byResolutionCount );
 * byResolutionCount = ScpGetResolutions( hDevice , pResolutions , byResolutionCount );
 *
 * printf( "ScpGetResolutions:\n" );
 * for( i = 0 ; i < byResolutionCount ; i++ )
 *   printf( "- %u bits\n" , pResolutions[ i ] );
 *
 * free( pResolutions );
 * \endcode
 * \see ScpGetResolution
 * \see ScpSetResolution
 *
 * \since 0.4.0
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef uint32_t(*LibTiePieScpGetResolutions_t)( LibTiePieHandle_t hDevice , uint8_t* pList , uint32_t dwLength );
#else
uint32_t ScpGetResolutions( LibTiePieHandle_t hDevice , uint8_t* pList , uint32_t dwLength );
#endif

/**
 * \brief Get the current resolution of the specified oscilloscope.
 *
 * \param[in] hDevice A \ref OpenDev "device handle" identifying the oscilloscope.
 * \return The current resolution in bits, or \c 0 when unsuccessful.
 * \par Status values
 *   <table class="params">
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_HANDLE "INVALID_HANDLE"</td>         <td>The handle is not a valid oscilloscope handle.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_OBJECT_GONE "OBJECT_GONE"</td>            <td>The object indicated by the handle is no longer available.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_LIBRARY_NOT_INITIALIZED "LIBRARY_NOT_INITIALIZED"</td><td>The library is not initialized, see LibInit().</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_SUCCESS "SUCCESS"</td>                <td>The function executed successfully.</td></tr>
 *   </table>
 * \see ScpGetResolutions
 * \see ScpSetResolution
 * \since 0.4.0
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef uint8_t(*LibTiePieScpGetResolution_t)( LibTiePieHandle_t hDevice );
#else
uint8_t ScpGetResolution( LibTiePieHandle_t hDevice );
#endif

/**
 * \brief Set the resolution of the specified oscilloscope.
 *
 * \param[in] hDevice A \ref OpenDev "device handle" identifying the oscilloscope.
 * \param[in] byResolution The required resolution in bits.
 * \return The actually set resolution in bits, or \c 0 when unsuccessful.
 * \remark Changing the resolution may affect the \ref scp_timebase_sampleFrequency "sample frequency", \ref scp_timebase_recordLength "record length" and/or \ref scp_ch_tr_enabled "channel trigger enabled".
 * \remark Setting the resolution will set auto resolution mode to #AR_DISABLED.
 * \par Status values
 *   <table class="params">
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_VALUE "INVALID_VALUE"</td>          <td>The requested value is invalid.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_HANDLE "INVALID_HANDLE"</td>         <td>The handle is not a valid oscilloscope handle.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_OBJECT_GONE "OBJECT_GONE"</td>            <td>The object indicated by the handle is no longer available.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_LIBRARY_NOT_INITIALIZED "LIBRARY_NOT_INITIALIZED"</td><td>The library is not initialized, see LibInit().</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_SUCCESS "SUCCESS"</td>                <td>The function executed successfully.</td></tr>
 *   </table>
 * \see ScpGetResolutions
 * \see ScpGetResolution
 * \since 0.4.0
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef uint8_t(*LibTiePieScpSetResolution_t)( LibTiePieHandle_t hDevice , uint8_t byResolution );
#else
uint8_t ScpSetResolution( LibTiePieHandle_t hDevice , uint8_t byResolution );
#endif

/**
 * \brief Check whether the currently selected resolution is enhanced or a native resolution of the hardware.
 *
 * \param[in] hDevice A \ref OpenDev "device handle" identifying the oscilloscope.
 * \return #BOOL8_TRUE if the current resolution is enhanced, #BOOL8_FALSE otherwise.
 * \par Status values
 *   <table class="params">
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_HANDLE "INVALID_HANDLE"</td>         <td>The handle is not a valid oscilloscope handle.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_OBJECT_GONE "OBJECT_GONE"</td>            <td>The object indicated by the handle is no longer available.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_LIBRARY_NOT_INITIALIZED "LIBRARY_NOT_INITIALIZED"</td><td>The library is not initialized, see LibInit().</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_SUCCESS "SUCCESS"</td>                <td>The function executed successfully.</td></tr>
 *   </table>
 * \since 0.4.0
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef bool8_t(*LibTiePieScpIsResolutionEnhanced_t)( LibTiePieHandle_t hDevice );
#else
bool8_t ScpIsResolutionEnhanced( LibTiePieHandle_t hDevice );
#endif

//! \cond EXTENDED_API

/**
 * \brief Check whether resolution is enhanced.
 *
 * \param[in] hDevice A \ref OpenDev "device handle" identifying the oscilloscope.
 * \param[in] byResolution Resolution in bits.
 * \return #BOOL8_TRUE if resolution is enhanced, #BOOL8_FALSE otherwise.
 * \since 0.4.0
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef bool8_t(*LibTiePieScpIsResolutionEnhancedEx_t)( LibTiePieHandle_t hDevice , uint8_t byResolution );
#else
bool8_t ScpIsResolutionEnhancedEx( LibTiePieHandle_t hDevice , uint8_t byResolution );
#endif

//! \endcond

/**
 * \}
 * \defgroup scp_clock Clock
 * \{
 * \brief Functions to control the clock of the oscilloscope.
 *
 * \defgroup scp_clock_source Source
 * \{
 * \brief Functions to control the clock source of the oscilloscope.
 *
 *           Oscilloscopes can support multiple clock sources, use ScpGetClockSources() to determine the available clock sources
 *           for an oscilloscope.
 *
 *           When an oscilloscope supports selecting an external clock source, refer to the instrument manual for the location of the
 *           external clock input and the specifications of the required external clock signal.
 *
 *           Depending on the instrument, an external clock input can support multiple input frequencies.
 *           Use ScpGetClockSourceFrequencies() to determine which frequencies are supported.
 *
 *           By default the clock source is set to: Internal (#CS_INTERNAL).
 */

// Workaround: Without this line Doxygen adds the documentation below to the group above.

/**
 * \brief Get the supported clock sources of the specified oscilloscope.
 *
 * \param[in] hDevice A \ref OpenDev "device handle" identifying the oscilloscope.
 * \return The supported clock sources, a set of OR-ed \ref CS_ "CS_*" values, or \c 0 when unsuccessful.
 * \par Status values
 *   <table class="params">
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_HANDLE "INVALID_HANDLE"</td>         <td>The handle is not a valid oscilloscope handle.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_OBJECT_GONE "OBJECT_GONE"</td>            <td>The object indicated by the handle is no longer available.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_LIBRARY_NOT_INITIALIZED "LIBRARY_NOT_INITIALIZED"</td><td>The library is not initialized, see LibInit().</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_SUCCESS "SUCCESS"</td>                <td>The function executed successfully.</td></tr>
 *   </table>
 * \see ScpGetClockSource
 * \see ScpSetClockSource
 * \see ScpGetClockSourceFrequencies
 * \see ScpGetClockSourceFrequency
 * \see ScpSetClockSourceFrequency
 * \since 0.4.0
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef uint32_t(*LibTiePieScpGetClockSources_t)( LibTiePieHandle_t hDevice );
#else
uint32_t ScpGetClockSources( LibTiePieHandle_t hDevice );
#endif

/**
 * \brief Get the currently selected clock source of the specified oscilloscope.
 *
 * \param[in] hDevice A \ref OpenDev "device handle" identifying the oscilloscope.
 * \return The current clock source, a \ref CS_ "CS_*" value, or \c 0 when unsuccessful.
 * \par Status values
 *   <table class="params">
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_HANDLE "INVALID_HANDLE"</td>         <td>The handle is not a valid oscilloscope handle.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_OBJECT_GONE "OBJECT_GONE"</td>            <td>The object indicated by the handle is no longer available.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_LIBRARY_NOT_INITIALIZED "LIBRARY_NOT_INITIALIZED"</td><td>The library is not initialized, see LibInit().</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_SUCCESS "SUCCESS"</td>                <td>The function executed successfully.</td></tr>
 *   </table>
 * \see ScpGetClockSources
 * \see ScpSetClockSource
 * \see ScpGetClockSourceFrequencies
 * \see ScpGetClockSourceFrequency
 * \see ScpSetClockSourceFrequency
 * \since 0.4.0
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef uint32_t(*LibTiePieScpGetClockSource_t)( LibTiePieHandle_t hDevice );
#else
uint32_t ScpGetClockSource( LibTiePieHandle_t hDevice );
#endif

/**
 * \brief Set the clock source of the specified oscilloscope.
 *
 * \param[in] hDevice A \ref OpenDev "device handle" identifying the oscilloscope.
 * \param[in] dwClockSource The requested clock source, a \ref CS_ "CS_*" value.
 * \return The actually set clock source, a \ref CS_ "CS_*" value, or \c 0 when unsuccessful.
 * \par Status values
 *   <table class="params">
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_VALUE "INVALID_VALUE"</td>          <td>The requested value is invalid.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_HANDLE "INVALID_HANDLE"</td>         <td>The handle is not a valid oscilloscope handle.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_OBJECT_GONE "OBJECT_GONE"</td>            <td>The object indicated by the handle is no longer available.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_LIBRARY_NOT_INITIALIZED "LIBRARY_NOT_INITIALIZED"</td><td>The library is not initialized, see LibInit().</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_SUCCESS "SUCCESS"</td>                <td>The function executed successfully.</td></tr>
 *   </table>
 * \see ScpGetClockSources
 * \see ScpGetClockSource
 * \see ScpGetClockSourceFrequencies
 * \see ScpGetClockSourceFrequency
 * \see ScpSetClockSourceFrequency
 * \since 0.4.0
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef uint32_t(*LibTiePieScpSetClockSource_t)( LibTiePieHandle_t hDevice , uint32_t dwClockSource );
#else
uint32_t ScpSetClockSource( LibTiePieHandle_t hDevice , uint32_t dwClockSource );
#endif

/**
 * \brief Get an array with the supported clock source frequencies of the specified oscilloscope.
 *
 * The caller must assure that enough memory is allocated.
 * This function is only available when the clock source is set to #CS_EXTERNAL.
 *
 * \param[in] hDevice A \ref OpenDev "device handle" identifying the oscilloscope.
 * \param[out] pList A pointer to an array for the clock source frequencies, or \c NULL.
 * \param[in] dwLength The number of elements in the array.
 * \return Total number of supported clock source frequencies, or \c 0 when unsuccessful.
 * \par Status values
 *   <table class="params">
 *   <tr><td>\ref LIBTIEPIESTATUS_NOT_SUPPORTED "NOT_SUPPORTED"</td>          <td>The oscilloscope does not support external clock or the clock source is not set to #CS_EXTERNAL.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_HANDLE "INVALID_HANDLE"</td>         <td>The handle is not a valid oscilloscope handle.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_OBJECT_GONE "OBJECT_GONE"</td>            <td>The object indicated by the handle is no longer available.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_LIBRARY_NOT_INITIALIZED "LIBRARY_NOT_INITIALIZED"</td><td>The library is not initialized, see LibInit().</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_SUCCESS "SUCCESS"</td>                <td>The function executed successfully.</td></tr>
 *   </table>
 * \par Example
 * \code{c}
 * uint32_t dwLength = ScpGetClockSourceFrequencies( hDevice , NULL , 0 );
 * double* pFrequencies = malloc( sizeof( double ) * dwLength );
 * dwLength = ScpGetClockSourceFrequencies( hDevice , pFrequencies , dwLength );
 *
 * for( i = 0 ; i < dwLength ; i++ )
 * {
 *   printf( "%f\n" , pFrequencies[ i ] );
 * }
 *
 * free( pFrequencies );
 * \endcode
 * \see ScpGetClockSources
 * \see ScpGetClockSource
 * \see ScpSetClockSource
 * \see ScpGetClockSourceFrequency
 * \see ScpSetClockSourceFrequency
 * \since 0.6
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef uint32_t(*LibTiePieScpGetClockSourceFrequencies_t)( LibTiePieHandle_t hDevice , double* pList , uint32_t dwLength );
#else
uint32_t ScpGetClockSourceFrequencies( LibTiePieHandle_t hDevice , double* pList , uint32_t dwLength );
#endif

//! \cond EXTENDED_API

/**
 * \brief Get an array with the supported clock source frequencies of the specified oscilloscope for the specified clock source.
 *
 * The caller must assure that enough memory is allocated.
 * This function is only available when the clock source is set to #CS_EXTERNAL.
 *
 * \param[in] hDevice A \ref OpenDev "device handle" identifying the oscilloscope.
 * \param[in] dwClockSource The requested clock source, a \ref CS_ "CS_*" value.
 * \param[out] pList A pointer to an array for the clock source frequencies, or \c NULL.
 * \param[in] dwLength The number of elements in the array.
 * \return Total number of supported clock source frequencies, or \c 0 when unsuccessful.
 * \par Status values
 *   <table class="params">
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_VALUE "INVALID_VALUE"</td>          <td>The requested clock source is invalid.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_NOT_SUPPORTED "NOT_SUPPORTED"</td>          <td>The oscilloscope does not support external clock or the clock source is not setto #CS_EXTERNAL.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_HANDLE "INVALID_HANDLE"</td>         <td>The handle is not a valid oscilloscope handle.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_OBJECT_GONE "OBJECT_GONE"</td>            <td>The object indicated by the handle is no longer available.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_LIBRARY_NOT_INITIALIZED "LIBRARY_NOT_INITIALIZED"</td><td>The library is not initialized, see LibInit().</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_SUCCESS "SUCCESS"</td>                <td>The function executed successfully.</td></tr>
 *   </table>
 * \see ScpGetClockSources
 * \see ScpGetClockSource
 * \see ScpSetClockSource
 * \see ScpGetClockSourceFrequencies
 * \see ScpGetClockSourceFrequency
 * \see ScpSetClockSourceFrequency
 * \since 0.6
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef uint32_t(*LibTiePieScpGetClockSourceFrequenciesEx_t)( LibTiePieHandle_t hDevice , uint32_t dwClockSource , double* pList , uint32_t dwLength );
#else
uint32_t ScpGetClockSourceFrequenciesEx( LibTiePieHandle_t hDevice , uint32_t dwClockSource , double* pList , uint32_t dwLength );
#endif

//!\endcond

/**
 * \brief Get the current clock source frequency of the specified oscilloscope.
 *
 * This function is only available when the clock source is set to #CS_EXTERNAL.
 *
 * \param[in] hDevice A \ref OpenDev "device handle" identifying the oscilloscope.
 * \return The current clock source frequency in Hz, or \c 0 when unsuccessful.
 * \par Status values
 *   <table class="params">
 *   <tr><td>\ref LIBTIEPIESTATUS_NOT_SUPPORTED "NOT_SUPPORTED"</td>          <td>The oscilloscope does not support external clock or the clock source is not set to #CS_EXTERNAL.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_HANDLE "INVALID_HANDLE"</td>         <td>The handle is not a valid oscilloscope handle.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_OBJECT_GONE "OBJECT_GONE"</td>            <td>The object indicated by the handle is no longer available.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_LIBRARY_NOT_INITIALIZED "LIBRARY_NOT_INITIALIZED"</td><td>The library is not initialized, see LibInit().</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_SUCCESS "SUCCESS"</td>                <td>The function executed successfully.</td></tr>
 *   </table>
 * \see ScpGetClockSources
 * \see ScpGetClockSource
 * \see ScpSetClockSource
 * \see ScpGetClockSourceFrequencies
 * \see ScpSetClockSourceFrequency
 * \since 0.6
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef double(*LibTiePieScpGetClockSourceFrequency_t)( LibTiePieHandle_t hDevice );
#else
double ScpGetClockSourceFrequency( LibTiePieHandle_t hDevice );
#endif

/**
 * \brief Set the clock source frequency of the specified oscilloscope.
 *
 * This function is only available when the clock source is set to #CS_EXTERNAL.
 *
 * \param[in] hDevice A \ref OpenDev "device handle" identifying the oscilloscope.
 * \param[in] dClockSourceFrequency The required clock source frequency in Hz.
 * \return The actually set clock source frequency in Hz, or \c 0 when unsuccessful.
 * \par Status values
 *   <table class="params">
 *   <tr><td>\ref LIBTIEPIESTATUS_VALUE_CLIPPED "VALUE_CLIPPED"</td>          <td>The requested clock source frequency is outside the valid range and clipped to the closest limit.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_VALUE_MODIFIED "VALUE_MODIFIED"</td>         <td>The requested clock source frequency is within the valid range but not available. The closest valid value is set.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_VALUE "INVALID_VALUE"</td>          <td>The requested value is invalid.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_NOT_SUPPORTED "NOT_SUPPORTED"</td>          <td>The oscilloscope does not support external clock or the clock source is not set to #CS_EXTERNAL.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_HANDLE "INVALID_HANDLE"</td>         <td>The handle is not a valid oscilloscope handle.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_OBJECT_GONE "OBJECT_GONE"</td>            <td>The object indicated by the handle is no longer available.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_LIBRARY_NOT_INITIALIZED "LIBRARY_NOT_INITIALIZED"</td><td>The library is not initialized, see LibInit().</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_SUCCESS "SUCCESS"</td>                <td>The function executed successfully.</td></tr>
 *   </table>
 * \see ScpGetClockSources
 * \see ScpGetClockSource
 * \see ScpSetClockSource
 * \see ScpGetClockSourceFrequencies
 * \see ScpGetClockSourceFrequency
 * \since 0.6
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef double(*LibTiePieScpSetClockSourceFrequency_t)( LibTiePieHandle_t hDevice , double dClockSourceFrequency );
#else
double ScpSetClockSourceFrequency( LibTiePieHandle_t hDevice , double dClockSourceFrequency );
#endif

/**
 * \}
 * \defgroup scp_clock_output Output
 * \{
 * \brief Functions to control the clock output type.
 *
 *           Oscilloscopes can support supplying a clock output signal, use ScpGetClockOutputs() to determine the available
 *           clock outputs for an oscilloscope.
 *
 *           When an oscilloscope supports selecting a clock output signal, refer to the instrument manual for the location of the
 *           clock output and the specifications of the clock output signal.
 *
 *           Depending on the instrument, a clock output can support multiple output frequencies.
 *           Use ScpGetClockSourceFrequencies() to determine which frequencies are supported.
 *
 *           By default the clock output is disabled (#CO_DISABLED).
 */

// Workaround: Without this line Doxygen adds the documentation below to the group above.

/**
 * \brief Get the supported clock outputs of the specified oscilloscope.
 *
 * \param[in] hDevice A \ref OpenDev "device handle" identifying the oscilloscope.
 * \return The supported clock outputs, a set of OR-ed \ref CO_ "CO_*" values, or \c 0 when unsuccessful.
 * \par Status values
 *   <table class="params">
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_HANDLE "INVALID_HANDLE"</td>         <td>The handle is not a valid oscilloscope handle.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_OBJECT_GONE "OBJECT_GONE"</td>            <td>The object indicated by the handle is no longer available.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_LIBRARY_NOT_INITIALIZED "LIBRARY_NOT_INITIALIZED"</td><td>The library is not initialized, see LibInit().</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_SUCCESS "SUCCESS"</td>                <td>The function executed successfully.</td></tr>
 *   </table>
 * \see ScpGetClockOutput
 * \see ScpSetClockOutput
 * \see ScpGetClockOutputFrequencies
 * \see ScpGetClockOutputFrequency
 * \see ScpSetClockOutputFrequency
 * \since 0.4.0
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef uint32_t(*LibTiePieScpGetClockOutputs_t)( LibTiePieHandle_t hDevice );
#else
uint32_t ScpGetClockOutputs( LibTiePieHandle_t hDevice );
#endif

/**
 * \brief Get the currently selected clock output of the specified oscilloscope.
 *
 * \param[in] hDevice A \ref OpenDev "device handle" identifying the oscilloscope.
 * \return The current clock output, a \ref CO_ "CO_*" value, or \c 0 when unsuccessful.
 * \par Status values
 *   <table class="params">
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_HANDLE "INVALID_HANDLE"</td>         <td>The handle is not a valid oscilloscope handle.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_OBJECT_GONE "OBJECT_GONE"</td>            <td>The object indicated by the handle is no longer available.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_LIBRARY_NOT_INITIALIZED "LIBRARY_NOT_INITIALIZED"</td><td>The library is not initialized, see LibInit().</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_SUCCESS "SUCCESS"</td>                <td>The function executed successfully.</td></tr>
 *   </table>
 * \see ScpGetClockOutputs
 * \see ScpSetClockOutput
 * \see ScpGetClockOutputFrequencies
 * \see ScpGetClockOutputFrequency
 * \see ScpSetClockOutputFrequency
 * \since 0.4.0
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef uint32_t(*LibTiePieScpGetClockOutput_t)( LibTiePieHandle_t hDevice );
#else
uint32_t ScpGetClockOutput( LibTiePieHandle_t hDevice );
#endif

/**
 * \brief Set the clock output of the specified oscilloscope.
 *
 * \param[in] hDevice A \ref OpenDev "device handle" identifying the oscilloscope.
 * \param[in] dwClockOutput The requested clock output, a \ref CO_ "CO_*" value.
 * \return The actually set clock output, a \ref CO_ "CO_*" value, or \c 0 when unsuccessful.
 * \par Status values
 *   <table class="params">
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_VALUE "INVALID_VALUE"</td>          <td>The requested value is invalid.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_HANDLE "INVALID_HANDLE"</td>         <td>The handle is not a valid oscilloscope handle.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_OBJECT_GONE "OBJECT_GONE"</td>            <td>The object indicated by the handle is no longer available.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_LIBRARY_NOT_INITIALIZED "LIBRARY_NOT_INITIALIZED"</td><td>The library is not initialized, see LibInit().</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_SUCCESS "SUCCESS"</td>                <td>The function executed successfully.</td></tr>
 *   </table>
 * \see ScpGetClockOutputs
 * \see ScpGetClockOutput
 * \see ScpGetClockOutputFrequencies
 * \see ScpGetClockOutputFrequency
 * \see ScpSetClockOutputFrequency
 * \since 0.4.0
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef uint32_t(*LibTiePieScpSetClockOutput_t)( LibTiePieHandle_t hDevice , uint32_t dwClockOutput );
#else
uint32_t ScpSetClockOutput( LibTiePieHandle_t hDevice , uint32_t dwClockOutput );
#endif

/**
 * \brief Get an array with the supported clock output frequencies of the specified oscilloscope.
 *
 * The caller must assure that enough memory is allocated.
 * This function is only available when the clock output is set to #CO_FIXED.
 *
 * \param[in] hDevice A \ref OpenDev "device handle" identifying the oscilloscope.
 * \param[out] pList A pointer to an array for the clock output frequencies, or \c NULL.
 * \param[in] dwLength The number of elements in the array.
 * \return Total number of supported clock output frequencies, or \c 0 when unsuccessful.
 * \par Status values
 *   <table class="params">
 *   <tr><td>\ref LIBTIEPIESTATUS_NOT_SUPPORTED "NOT_SUPPORTED"</td>          <td>The oscilloscope does not support clock output or the clock output is not set to #CO_FIXED.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_HANDLE "INVALID_HANDLE"</td>         <td>The handle is not a valid oscilloscope handle.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_OBJECT_GONE "OBJECT_GONE"</td>            <td>The object indicated by the handle is no longer available.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_LIBRARY_NOT_INITIALIZED "LIBRARY_NOT_INITIALIZED"</td><td>The library is not initialized, see LibInit().</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_SUCCESS "SUCCESS"</td>                <td>The function executed successfully.</td></tr>
 *   </table>
 * \par Example
 * \code{c}
 * uint32_t dwLength = ScpGetClockOutputFrequencies( hDevice , NULL , 0 );
 * double* pFrequencies = malloc( sizeof( double ) * dwLength );
 * dwLength = ScpGetClockOutputFrequencies( hDevice , pFrequencies , dwLength );
 *
 * for( i = 0 ; i < dwLength ; i++ )
 * {
 *   printf( "%f\n" , pFrequencies[ i ] );
 * }
 *
 * free( pFrequencies );
 * \endcode
 * \see ScpGetClockOutputs
 * \see ScpGetClockOutput
 * \see ScpSetClockOutput
 * \see ScpGetClockOutputFrequency
 * \see ScpSetClockOutputFrequency
 * \since 0.6
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef uint32_t(*LibTiePieScpGetClockOutputFrequencies_t)( LibTiePieHandle_t hDevice , double* pList , uint32_t dwLength );
#else
uint32_t ScpGetClockOutputFrequencies( LibTiePieHandle_t hDevice , double* pList , uint32_t dwLength );
#endif

//! \cond EXTENDED_API

/**
 * \brief Get an array with the supported clock output frequencies of the specified oscilloscope for the specified clock output.
 *
 * The caller must assure that enough memory is allocated.
 * This function is only available when the clock output is set to #CO_FIXED.
 *
 * \param[in] hDevice A \ref OpenDev "device handle" identifying the oscilloscope.
 * \param[in] dwClockOutput The requested clock output, a \ref CS_ "CS_*" value.
 * \param[out] pList A pointer to an array for the clock output frequencies, or \c NULL.
 * \param[in] dwLength The number of elements in the array.
 * \return Total number of supported clock output frequencies, or \c 0 when unsuccessful.
 * \par Status values
 *   <table class="params">
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_VALUE "INVALID_VALUE"</td>          <td>The requested clock output is invalid.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_NOT_SUPPORTED "NOT_SUPPORTED"</td>          <td>The oscilloscope does not support clock output or the clock output is not set to #CO_FIXED.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_HANDLE "INVALID_HANDLE"</td>         <td>The handle is not a valid oscilloscope handle.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_OBJECT_GONE "OBJECT_GONE"</td>            <td>The object indicated by the handle is no longer available.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_LIBRARY_NOT_INITIALIZED "LIBRARY_NOT_INITIALIZED"</td><td>The library is not initialized, see LibInit().</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_SUCCESS "SUCCESS"</td>                <td>The function executed successfully.</td></tr>
 *   </table>
 * \see ScpGetClockOutputs
 * \see ScpGetClockOutput
 * \see ScpSetClockOutput
 * \see ScpGetClockOutputFrequencies
 * \see ScpGetClockOutputFrequency
 * \see ScpSetClockOutputFrequency
 * \since 0.6
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef uint32_t(*LibTiePieScpGetClockOutputFrequenciesEx_t)( LibTiePieHandle_t hDevice , uint32_t dwClockOutput , double* pList , uint32_t dwLength );
#else
uint32_t ScpGetClockOutputFrequenciesEx( LibTiePieHandle_t hDevice , uint32_t dwClockOutput , double* pList , uint32_t dwLength );
#endif

//!\endcond

/**
 * \brief Get the current clock output frequency of the specified oscilloscope.
 *
 * This function is only available when the clock output is set to #CO_FIXED.
 *
 * \param[in] hDevice A \ref OpenDev "device handle" identifying the oscilloscope.
 * \return The current clock output frequency in Hz, or \c 0 when unsuccessful.
 * \par Status values
 *   <table class="params">
 *   <tr><td>\ref LIBTIEPIESTATUS_NOT_SUPPORTED "NOT_SUPPORTED"</td>          <td>The oscilloscope does not support clock output or the clock output is not set to #CO_FIXED.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_HANDLE "INVALID_HANDLE"</td>         <td>The handle is not a valid oscilloscope handle.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_OBJECT_GONE "OBJECT_GONE"</td>            <td>The object indicated by the handle is no longer available.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_LIBRARY_NOT_INITIALIZED "LIBRARY_NOT_INITIALIZED"</td><td>The library is not initialized, see LibInit().</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_SUCCESS "SUCCESS"</td>                <td>The function executed successfully.</td></tr>
 *   </table>
 * \see ScpGetClockOutputs
 * \see ScpGetClockOutput
 * \see ScpSetClockOutput
 * \see ScpGetClockOutputFrequencies
 * \see ScpSetClockOutputFrequency
 * \since 0.6
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef double(*LibTiePieScpGetClockOutputFrequency_t)( LibTiePieHandle_t hDevice );
#else
double ScpGetClockOutputFrequency( LibTiePieHandle_t hDevice );
#endif

/**
 * \brief Set the clock output frequency of the specified oscilloscope.
 *
 * This function is only available when the clock output is set to #CO_FIXED.
 *
 * \param[in] hDevice A \ref OpenDev "device handle" identifying the oscilloscope.
 * \param[in] dClockOutputFrequency The required clock output frequency in Hz.
 * \return The actually set clock output frequency in Hz, or \c 0 when unsuccessful.
 * \par Status values
 *   <table class="params">
 *   <tr><td>\ref LIBTIEPIESTATUS_VALUE_CLIPPED "VALUE_CLIPPED"</td>          <td>The requested clock output frequency is outside the valid range and clipped to the closest limit.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_VALUE_MODIFIED "VALUE_MODIFIED"</td>         <td>The requested clock output frequency is within the valid range but not available. The closest valid value is set.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_VALUE "INVALID_VALUE"</td>          <td>The requested value is invalid.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_NOT_SUPPORTED "NOT_SUPPORTED"</td>          <td>The oscilloscope does not support clock output or the clock output is not set to #CO_FIXED.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_HANDLE "INVALID_HANDLE"</td>         <td>The handle is not a valid oscilloscope handle.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_OBJECT_GONE "OBJECT_GONE"</td>            <td>The object indicated by the handle is no longer available.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_LIBRARY_NOT_INITIALIZED "LIBRARY_NOT_INITIALIZED"</td><td>The library is not initialized, see LibInit().</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_SUCCESS "SUCCESS"</td>                <td>The function executed successfully.</td></tr>
 *   </table>
 * \see ScpGetClockOutputs
 * \see ScpGetClockOutput
 * \see ScpSetClockOutput
 * \see ScpGetClockOutputFrequencies
 * \see ScpGetClockOutputFrequency
 * \since 0.6
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef double(*LibTiePieScpSetClockOutputFrequency_t)( LibTiePieHandle_t hDevice , double dClockOutputFrequency );
#else
double ScpSetClockOutputFrequency( LibTiePieHandle_t hDevice , double dClockOutputFrequency );
#endif

/**
 * \}
 * \}
 * \defgroup scp_timebase Timebase
 * \{
 * \brief Functions to control the time base of the oscilloscope.
 *
 * \defgroup scp_timebase_sampleFrequency Sample frequency
 * \{
 * \brief Functions to control the sample frequency of the oscilloscope.
 *
 *           The rate at which samples are taken by the oscilloscope is called the sample frequency, the number of samples per second.
 *           A higher sample frequency corresponds to a shorter interval between the samples.
 *           With a higher sample frequency, the original signal can be reconstructed much better from the measured samples.
 *
 *           The maximum supported sample frequency depends on the used instrument and its configuration.
 *           Use #ScpGetSampleFrequencyMax to determine the maximum supported sample frequency of a oscilloscope.
 *
 *           The sample frequency can be affected by changing the \ref scp_ch_enabled "channel enable", \ref scp_resolution "resolution" and/or \ref scp_measurements_mode "measure mode".
 *
 *           By default the sample frequency is set to the highest value available.
 */

// Workaround: Without this line Doxygen adds the documentation below to the group above.

/**
 * \brief Get the maximum supported sample frequency of a specified oscilloscope.
 *
 * \param[in] hDevice A \ref OpenDev "device handle" identifying the oscilloscope.
 * \return The maximum supported sample frequency in Hz, or \c 0 when unsuccessful.
 * \par Status values
 *   <table class="params">
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_HANDLE "INVALID_HANDLE"</td>         <td>The handle is not a valid oscilloscope handle.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_OBJECT_GONE "OBJECT_GONE"</td>            <td>The object indicated by the handle is no longer available.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_LIBRARY_NOT_INITIALIZED "LIBRARY_NOT_INITIALIZED"</td><td>The library is not initialized, see LibInit().</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_SUCCESS "SUCCESS"</td>                <td>The function executed successfully.</td></tr>
 *   </table>
 * \see ScpGetSampleFrequency
 * \see ScpSetSampleFrequency
 * \since 0.4.0
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef double(*LibTiePieScpGetSampleFrequencyMax_t)( LibTiePieHandle_t hDevice );
#else
double ScpGetSampleFrequencyMax( LibTiePieHandle_t hDevice );
#endif

/**
 * \brief Get the currently selected sample frequency of a specified oscilloscope.
 *
 * \param[in] hDevice A \ref OpenDev "device handle" identifying the oscilloscope.
 * \return The currently selected sample frequency in Hz, or \c 0 when unsuccessful.
 * \par Status values
 *   <table class="params">
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_HANDLE "INVALID_HANDLE"</td>         <td>The handle is not a valid oscilloscope handle.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_OBJECT_GONE "OBJECT_GONE"</td>            <td>The object indicated by the handle is no longer available.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_LIBRARY_NOT_INITIALIZED "LIBRARY_NOT_INITIALIZED"</td><td>The library is not initialized, see LibInit().</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_SUCCESS "SUCCESS"</td>                <td>The function executed successfully.</td></tr>
 *   </table>
 * \see ScpGetSampleFrequencyMax
 * \see ScpSetSampleFrequency
 * \since 0.4.0
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef double(*LibTiePieScpGetSampleFrequency_t)( LibTiePieHandle_t hDevice );
#else
double ScpGetSampleFrequency( LibTiePieHandle_t hDevice );
#endif

/**
 * \brief Set the sample frequency of a specified oscilloscope.
 *
 * \param[in] hDevice A \ref OpenDev "device handle" identifying the oscilloscope.
 * \param[in] dSampleFrequency The required sample frequency in Hz.
 * \return The actually selected sample frequency in Hz, or \c 0 when unsuccessful.
 * \remark Changing the sample frequency may affect the \ref scp_timebase_recordLength "record length", \ref scp_trigger_time_out "trigger time out", \ref scp_trigger_delay "trigger delay", \ref scp_ch_tr_enabled "channel trigger enabled" and/or \ref scp_ch_tr_time "channel trigger time(s)" value(s).
 * \remark Changing the sample frequency may change the \ref scp_resolution "resolution" if auto resolution mode is #AR_NATIVEONLY or #AR_ALL.
 * \par Status values
 *   <table class="params">
 *   <tr><td>\ref LIBTIEPIESTATUS_VALUE_CLIPPED "VALUE_CLIPPED"</td>          <td>The requested sample frequency is outside the valid range and clipped to the closest limit.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_VALUE_MODIFIED "VALUE_MODIFIED"</td>         <td>The requested sample frequency is within the valid range but not available. The closest valid value is set.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_VALUE "INVALID_VALUE"</td>          <td>The requested value is invalid.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_HANDLE "INVALID_HANDLE"</td>         <td>The handle is not a valid oscilloscope handle.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_OBJECT_GONE "OBJECT_GONE"</td>            <td>The object indicated by the handle is no longer available.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_LIBRARY_NOT_INITIALIZED "LIBRARY_NOT_INITIALIZED"</td><td>The library is not initialized, see LibInit().</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_SUCCESS "SUCCESS"</td>                <td>The function executed successfully.</td></tr>
 *   </table>
 * \see ScpGetSampleFrequencyMax
 * \see ScpGetSampleFrequency
 * \since 0.4.0
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef double(*LibTiePieScpSetSampleFrequency_t)( LibTiePieHandle_t hDevice , double dSampleFrequency );
#else
double ScpSetSampleFrequency( LibTiePieHandle_t hDevice , double dSampleFrequency );
#endif

//! \cond EXTENDED_API

/**
 * \brief Verify if a required sample frequency can be set, for the specified device, without actually setting the hardware itself.
 *
 * \param[in] hDevice A \ref OpenDev "device handle" identifying the oscilloscope.
 * \param[in] dSampleFrequency The required sample frequency, in Hz.
 * \return The sample frequency that would have been set, if ScpSetSampleFrequency() was used.
 * \see ScpGetSampleFrequencyMax
 * \see ScpGetSampleFrequency
 * \see ScpSetSampleFrequency
 * \see ScpVerifySampleFrequencyEx
 * \see ScpVerifySampleFrequenciesEx
 * \since 0.4.0
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef double(*LibTiePieScpVerifySampleFrequency_t)( LibTiePieHandle_t hDevice , double dSampleFrequency );
#else
double ScpVerifySampleFrequency( LibTiePieHandle_t hDevice , double dSampleFrequency );
#endif

/**
 * \brief Verify sample frequency by measure mode, resolution and active channels.
 *
 * \param[in] hDevice A \ref OpenDev "device handle" identifying the oscilloscope.
 * \param[in] dSampleFrequency The required sample frequency, in Hz.
 * \param[in] dwMeasureMode Measure mode, a \ref MM_ "MM_*" value.
 * \param[in] byResolution Resolution in bits.
 * \param[in] pChannelEnabled Pointer to buffer with channel enables.
 * \param[in] wChannelCount Number of items in \c pChannelEnabled.
 * \return Sample frequency in Hz when set.
 * \see ScpGetSampleFrequencyMax
 * \see ScpGetSampleFrequency
 * \see ScpSetSampleFrequency
 * \see ScpVerifySampleFrequency
 * \see ScpVerifySampleFrequenciesEx
 * \since 0.5
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef double(*LibTiePieScpVerifySampleFrequencyEx_t)( LibTiePieHandle_t hDevice , double dSampleFrequency , uint32_t dwMeasureMode , uint8_t byResolution , const bool8_t* pChannelEnabled , uint16_t wChannelCount );
#else
double ScpVerifySampleFrequencyEx( LibTiePieHandle_t hDevice , double dSampleFrequency , uint32_t dwMeasureMode , uint8_t byResolution , const bool8_t* pChannelEnabled , uint16_t wChannelCount );
#endif

/**
 * \brief Verify sample frequencies by measure mode, resolution mode, resolution and active channels.
 *
 * \param[in] hDevice A \ref OpenDev "device handle" identifying the oscilloscope.
 * \param[in,out] pSampleFrequencies Pointer to buffer with sample frequencies.
 * \param[in] dwSampleFrequencyCount Number of items in \c pSampleFrequencies.
 * \param[in] dwMeasureMode Measure mode, a \ref MM_ "MM_*" value.
 * \param[in] dwAutoResolutionMode Auto resolution mode, a \ref AR_ "AR_*" value.
 * \param[in] byResolution Resolution in bits.
 * \param[in] pChannelEnabled Pointer to buffer with channel enables.
 * \param[in] wChannelCount Number of items in \c pChannelEnabled.
 * \see ScpGetSampleFrequencyMax
 * \see ScpGetSampleFrequency
 * \see ScpSetSampleFrequency
 * \see ScpVerifySampleFrequency
 * \see ScpVerifySampleFrequencyEx
 * \since 0.4.5
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef void(*LibTiePieScpVerifySampleFrequenciesEx_t)( LibTiePieHandle_t hDevice , double* pSampleFrequencies , uint32_t dwSampleFrequencyCount , uint32_t dwMeasureMode , uint32_t dwAutoResolutionMode , uint8_t byResolution , const bool8_t* pChannelEnabled , uint16_t wChannelCount );
#else
void ScpVerifySampleFrequenciesEx( LibTiePieHandle_t hDevice , double* pSampleFrequencies , uint32_t dwSampleFrequencyCount , uint32_t dwMeasureMode , uint32_t dwAutoResolutionMode , uint8_t byResolution , const bool8_t* pChannelEnabled , uint16_t wChannelCount );
#endif

//! \endcond

/**
 * \}
 * \defgroup scp_timebase_recordLength Record length
 * \{
 * \brief Functions to control the record length of the oscilloscope.
 *
 *           The record length defines the number of samples in a measurement.
 *           With a given \ref scp_timebase_sampleFrequency "sample frequency", the record length determines the duration of the measurement.
 *           Increasing the record length, will increase the total measuring time. The result is that more of the measured signal is visible.
 *
 *           The maximum supported record length depends on the used instrument and its configuration.
 *           Use #ScpGetRecordLengthMax to determine the maximum supported record length of a oscilloscope.
 *
 *           The record length can be affected by changing the \ref scp_ch_enabled "channel enable", \ref scp_resolution "resolution", \ref scp_measurements_mode "measure mode" and/or \ref scp_timebase_sampleFrequency "sample frequency".
 *
 *           By default the record length is set to: 5000 samples.
 */

// Workaround: Without this line Doxygen adds the documentation below to the group above.

/**
 * \brief Get the maximum supported record length of a specified oscilloscope.
 *
 * \param[in] hDevice A \ref OpenDev "device handle" identifying the oscilloscope.
 * \return The maximum supported record length, or \c 0 when unsuccessful.
 * \par Status values
 *   <table class="params">
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_HANDLE "INVALID_HANDLE"</td>         <td>The handle is not a valid oscilloscope handle.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_OBJECT_GONE "OBJECT_GONE"</td>            <td>The object indicated by the handle is no longer available.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_LIBRARY_NOT_INITIALIZED "LIBRARY_NOT_INITIALIZED"</td><td>The library is not initialized, see LibInit().</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_SUCCESS "SUCCESS"</td>                <td>The function executed successfully.</td></tr>
 *   </table>
 * \see ScpGetRecordLength
 * \see ScpSetRecordLength
 * \since 0.4.0
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef uint64_t(*LibTiePieScpGetRecordLengthMax_t)( LibTiePieHandle_t hDevice );
#else
uint64_t ScpGetRecordLengthMax( LibTiePieHandle_t hDevice );
#endif

//! \cond EXTENDED_API

/**
 * \brief Get maximum record length for a specified measure mode and resolution.
 *
 * \param[in] hDevice A \ref OpenDev "device handle" identifying the oscilloscope.
 * \param[in] dwMeasureMode Measure mode, a \ref MM_ "MM_*" value.
 * \param[in] byResolution Resolution in bits.
 * \return Maximum record length.
 * \see ScpGetRecordLengthMax
 * \see ScpGetRecordLength
 * \see ScpSetRecordLength
 * \see ScpVerifyRecordLength
 * \see ScpVerifyRecordLengthex
 * \since 0.4.0
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef uint64_t(*LibTiePieScpGetRecordLengthMaxEx_t)( LibTiePieHandle_t hDevice , uint32_t dwMeasureMode , uint8_t byResolution );
#else
uint64_t ScpGetRecordLengthMaxEx( LibTiePieHandle_t hDevice , uint32_t dwMeasureMode , uint8_t byResolution );
#endif

//! \endcond

/**
 * \brief Get the currently selected record length of a specified oscilloscope.
 *
 * \param[in] hDevice A \ref OpenDev "device handle" identifying the oscilloscope.
 * \return The currently selected record length in samples, or \c 0 when unsuccessful.
 * \par Status values
 *   <table class="params">
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_HANDLE "INVALID_HANDLE"</td>         <td>The handle is not a valid oscilloscope handle.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_OBJECT_GONE "OBJECT_GONE"</td>            <td>The object indicated by the handle is no longer available.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_LIBRARY_NOT_INITIALIZED "LIBRARY_NOT_INITIALIZED"</td><td>The library is not initialized, see LibInit().</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_SUCCESS "SUCCESS"</td>                <td>The function executed successfully.</td></tr>
 *   </table>
 * \see ScpGetRecordLengthMax
 * \see ScpSetRecordLength
 * \since 0.4.0
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef uint64_t(*LibTiePieScpGetRecordLength_t)( LibTiePieHandle_t hDevice );
#else
uint64_t ScpGetRecordLength( LibTiePieHandle_t hDevice );
#endif

/**
 * \brief Set the record length of a specified oscilloscope.
 *
 * \param[in] hDevice A \ref OpenDev "device handle" identifying the oscilloscope.
 * \param[in] qwRecordLength The required record length in samples.
 * \return The actually set record length in samples, or \c 0 when unsuccessful.
 * \remark Changing the record length may affect the \ref scp_timebase_segmentCount "segment count".
 * \par Status values
 *   <table class="params">
 *   <tr><td>\ref LIBTIEPIESTATUS_VALUE_CLIPPED "VALUE_CLIPPED"</td>          <td>The requested record length is outside the valid range and clipped to the closest limit.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_VALUE_MODIFIED "VALUE_MODIFIED"</td>         <td>The requested record length is within the valid range but not available. The closest valid value is set.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_VALUE "INVALID_VALUE"</td>          <td>The requested value is invalid.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_HANDLE "INVALID_HANDLE"</td>         <td>The handle is not a valid oscilloscope handle.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_OBJECT_GONE "OBJECT_GONE"</td>            <td>The object indicated by the handle is no longer available.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_LIBRARY_NOT_INITIALIZED "LIBRARY_NOT_INITIALIZED"</td><td>The library is not initialized, see LibInit().</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_SUCCESS "SUCCESS"</td>                <td>The function executed successfully.</td></tr>
 *   </table>
 * \see ScpGetRecordLengthMax
 * \see ScpGetRecordLength
 * \since 0.4.0
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef uint64_t(*LibTiePieScpSetRecordLength_t)( LibTiePieHandle_t hDevice , uint64_t qwRecordLength );
#else
uint64_t ScpSetRecordLength( LibTiePieHandle_t hDevice , uint64_t qwRecordLength );
#endif

//! \cond EXTENDED_API

/**
 * \brief Verify if a required record length can be set, for the specified oscilloscope, without actually setting the hardware itself.
 *
 * \param[in] hDevice A \ref OpenDev "device handle" identifying the oscilloscope.
 * \param[in] qwRecordLength The required record length, in samples.
 * \return The record length that would have been set, if ScpSetRecordLength() was used.
 * \see ScpGetRecordLengthMax
 * \see ScpGetRecordLengthMaxEx
 * \see ScpGetRecordLength
 * \see ScpSetRecordLength
 * \see ScpVerifyRecordLengthEx
 * \since 0.4.0
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef uint64_t(*LibTiePieScpVerifyRecordLength_t)( LibTiePieHandle_t hDevice , uint64_t qwRecordLength );
#else
uint64_t ScpVerifyRecordLength( LibTiePieHandle_t hDevice , uint64_t qwRecordLength );
#endif

/**
 * \brief Verify record length by measure mode, resolution and active channels.
 *
 * \param[in] hDevice A \ref OpenDev "device handle" identifying the oscilloscope.
 * \param[in] qwRecordLength Record length.
 * \param[in] dwMeasureMode Measure mode, a \ref MM_ "MM_*" value.
 * \param[in] byResolution Resolution in bits.
 * \param[in] pChannelEnabled Pointer to buffer with channel enables.
 * \param[in] wChannelCount Number of items in \c pChannelEnabled.
 * \return Record length.
 * \see ScpGetRecordLengthMax
 * \see ScpGetRecordLengthMaxEx
 * \see ScpGetRecordLength
 * \see ScpSetRecordLength
 * \see ScpVerifyRecordLength
 * \since 0.5
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef uint64_t(*LibTiePieScpVerifyRecordLengthEx_t)( LibTiePieHandle_t hDevice , uint64_t qwRecordLength , uint32_t dwMeasureMode , uint8_t byResolution , const bool8_t* pChannelEnabled , uint16_t wChannelCount );
#else
uint64_t ScpVerifyRecordLengthEx( LibTiePieHandle_t hDevice , uint64_t qwRecordLength , uint32_t dwMeasureMode , uint8_t byResolution , const bool8_t* pChannelEnabled , uint16_t wChannelCount );
#endif

//! \endcond

/**
 * \}
 * \defgroup scp_timebase_preSamples Pre samples
 * \{
 * \brief Functions to control pre samples.
 *
 *           When pre samples are selected (pre sample ratio > 0), the trigger point is located at position
 *           (pre sample ratio * \ref scp_timebase_recordLength "record length"), dividing the record in pre samples and post samples.
 *           This way it is possible to "look back in time" since the pre samples were captured before the trigger moment.
 *
 *           Pre sample ratio is set as a number between 0 and 1, representing the percentage of the total record length:
 *           - 0 equals a trigger point at the start of the record, 0% pre samples and 100% post samples
 *           - 0.5 equals a trigger point half way the record, 50% pre samples and 50% post samples
 *           - 1  equals a trigger point at the end of the record, 100% pre samples and 0% post samples
 *
 *           By default the pre sample ratio is: 0 (no pre samples).
 *
 *           The pre sample buffer is not completely filled by default.
 *           When a trigger occurs before the pre sample buffer is filled, part of the pre samples will be invalid.
 *           Use ScpGetValidPreSampleCount() before collecting the data to determine the amount of valid pre samples.
 *           To ensure the pre samples buffer will be completely filled, set the \ref scp_trigger_HoldOff "trigger hold off" to #TH_ALLPRESAMPLES.
 */

// Workaround: Without this line Doxygen adds the documentation below to the group above.

/**
 * \brief Get the current pre sample ratio of a specified oscilloscope.
 *
 * \param[in] hDevice A \ref OpenDev "device handle" identifying the oscilloscope.
 * \return The currently selected pre sample ratio, a value between \c 0 and \c 1.
 * \par Status values
 *   <table class="params">
 *   <tr><td>\ref LIBTIEPIESTATUS_NOT_SUPPORTED "NOT_SUPPORTED"</td>          <td>The indicated oscilloscope does not support pre samples with the current settings.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_HANDLE "INVALID_HANDLE"</td>         <td>The handle is not a valid oscilloscope handle.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_OBJECT_GONE "OBJECT_GONE"</td>            <td>The object indicated by the handle is no longer available.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_LIBRARY_NOT_INITIALIZED "LIBRARY_NOT_INITIALIZED"</td><td>The library is not initialized, see LibInit().</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_SUCCESS "SUCCESS"</td>                <td>The function executed successfully.</td></tr>
 *   </table>
 * \see ScpSetPreSampleRatio
 * \since 0.4.0
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef double(*LibTiePieScpGetPreSampleRatio_t)( LibTiePieHandle_t hDevice );
#else
double ScpGetPreSampleRatio( LibTiePieHandle_t hDevice );
#endif

/**
 * \brief Set the pre sample ratio of a specified oscilloscope.
 *
 * \param[in] hDevice A \ref OpenDev "device handle" identifying the oscilloscope.
 * \param[in] dPreSampleRatio The required pre sample ratio, a number between \c 0 and \c 1.
 * \return The actually set pre sample ratio, a number between \c 0 and \c 1.
 * \par Status values
 *   <table class="params">
 *   <tr><td>\ref LIBTIEPIESTATUS_NOT_SUPPORTED "NOT_SUPPORTED"</td>          <td>The indicated oscilloscope does not support pre samples with the current settings.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_VALUE "INVALID_VALUE"</td>          <td>The requested value is invalid.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_HANDLE "INVALID_HANDLE"</td>         <td>The handle is not a valid oscilloscope handle.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_OBJECT_GONE "OBJECT_GONE"</td>            <td>The object indicated by the handle is no longer available.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_LIBRARY_NOT_INITIALIZED "LIBRARY_NOT_INITIALIZED"</td><td>The library is not initialized, see LibInit().</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_SUCCESS "SUCCESS"</td>                <td>The function executed successfully.</td></tr>
 *   </table>
 * \see ScpGetPreSampleRatio
 * \see ScpGetValidPreSampleCount
 * \see scp_trigger_HoldOff
 * \since 0.4.0
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef double(*LibTiePieScpSetPreSampleRatio_t)( LibTiePieHandle_t hDevice , double dPreSampleRatio );
#else
double ScpSetPreSampleRatio( LibTiePieHandle_t hDevice , double dPreSampleRatio );
#endif

/**
 * \}
 * \defgroup scp_timebase_segmentCount Segment count
 * \{
 * \brief Functions to control the segment count.
 *
 *           The segment count can be affected by changing the \ref scp_timebase_recordLength "record length".
 */

// Workaround: Without this line Doxygen adds the documentation below to the group above.

/**
 * \brief Get the maximum supported number of segments of a specified oscilloscope.
 *
 * \param[in] hDevice A \ref OpenDev "device handle" identifying the oscilloscope.
 * \return The maximum supported number of segments, or \c 0 when unsuccessful.
 * \par Status values
 *   <table class="params">
 *   <tr><td>\ref LIBTIEPIESTATUS_NOT_SUPPORTED "NOT_SUPPORTED"</td>          <td>Segment count is not supported by the hardware.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_HANDLE "INVALID_HANDLE"</td>         <td>The handle is not a valid oscilloscope handle.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_OBJECT_GONE "OBJECT_GONE"</td>            <td>The object indicated by the handle is no longer available.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_LIBRARY_NOT_INITIALIZED "LIBRARY_NOT_INITIALIZED"</td><td>The library is not initialized, see LibInit().</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_SUCCESS "SUCCESS"</td>                <td>The function executed successfully.</td></tr>
 *   </table>
 * \see ScpGetSegmentCount
 * \see ScpSetSegmentCount
 * \since 0.4.3
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef uint32_t(*LibTiePieScpGetSegmentCountMax_t)( LibTiePieHandle_t hDevice );
#else
uint32_t ScpGetSegmentCountMax( LibTiePieHandle_t hDevice );
#endif

//! \cond EXTENDED_API

/**
 * \brief Get the maximum supported number of segments for a specified measure mode of a specified oscilloscope.
 *
 * \param[in] hDevice A \ref OpenDev "device handle" identifying the oscilloscope.
 * \param[in] dwMeasureMode Measure mode, a \ref MM_ "MM_*" value.
 * \return The maximum supported number of segments, or \c 0 when unsuccessful.
 * \see ScpGetSegmentCountMax
 * \see ScpGetSegmentCount
 * \see ScpSetSegmentCount
 * \see ScpVerifySegmentCount
 * \see ScpVerifySegmentCountEx2
 * \since 0.4.5
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef uint32_t(*LibTiePieScpGetSegmentCountMaxEx_t)( LibTiePieHandle_t hDevice , uint32_t dwMeasureMode );
#else
uint32_t ScpGetSegmentCountMaxEx( LibTiePieHandle_t hDevice , uint32_t dwMeasureMode );
#endif

//! \endcond

/**
 * \brief Get the currently selected number of segments of a specified oscilloscope.
 *
 * \param[in] hDevice A \ref OpenDev "device handle" identifying the oscilloscope.
 * \return The currently selected number of segments, or \c 0 when unsuccessful.
 * \par Status values
 *   <table class="params">
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_VALUE "INVALID_VALUE"</td>          <td>The requested value is invalid.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_NOT_SUPPORTED "NOT_SUPPORTED"</td>          <td>Segment count is not supported by the hardware.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_HANDLE "INVALID_HANDLE"</td>         <td>The handle is not a valid oscilloscope handle.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_OBJECT_GONE "OBJECT_GONE"</td>            <td>The object indicated by the handle is no longer available.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_LIBRARY_NOT_INITIALIZED "LIBRARY_NOT_INITIALIZED"</td><td>The library is not initialized, see LibInit().</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_SUCCESS "SUCCESS"</td>                <td>The function executed successfully.</td></tr>
 *   </table>
 * \see ScpGetSegmentCountMax
 * \see ScpSetSegmentCount
 * \since 0.4.3
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef uint32_t(*LibTiePieScpGetSegmentCount_t)( LibTiePieHandle_t hDevice );
#else
uint32_t ScpGetSegmentCount( LibTiePieHandle_t hDevice );
#endif

/**
 * \brief Set the number of segments of a specified oscilloscope.
 *
 * \param[in] hDevice A \ref OpenDev "device handle" identifying the oscilloscope.
 * \param[in] dwSegmentCount The required number of segments.
 * \return The actually set number of segments, or \c 0 when unsuccessful.
 * \par Status values
 *   <table class="params">
 *   <tr><td>\ref LIBTIEPIESTATUS_VALUE_CLIPPED "VALUE_CLIPPED"</td>          <td>The requested segment count is outside the valid range and clipped to the closest limit.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_VALUE_MODIFIED "VALUE_MODIFIED"</td>         <td>The requested segment count is within the valid range but not available. The closest valid value is set.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_VALUE "INVALID_VALUE"</td>          <td>The requested value is invalid.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_NOT_SUPPORTED "NOT_SUPPORTED"</td>          <td>Segment count is not supported by the hardware.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_HANDLE "INVALID_HANDLE"</td>         <td>The handle is not a valid oscilloscope handle.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_OBJECT_GONE "OBJECT_GONE"</td>            <td>The object indicated by the handle is no longer available.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_LIBRARY_NOT_INITIALIZED "LIBRARY_NOT_INITIALIZED"</td><td>The library is not initialized, see LibInit().</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_SUCCESS "SUCCESS"</td>                <td>The function executed successfully.</td></tr>
 *   </table>
 * \see ScpGetSegmentCountMax
 * \see ScpGetSegmentCount
 * \since 0.4.3
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef uint32_t(*LibTiePieScpSetSegmentCount_t)( LibTiePieHandle_t hDevice , uint32_t dwSegmentCount );
#else
uint32_t ScpSetSegmentCount( LibTiePieHandle_t hDevice , uint32_t dwSegmentCount );
#endif

//! \cond EXTENDED_API

/**
 * \brief Verify if a required number of segments can be set, without actually setting the hardware itself.
 *
 * \param[in] hDevice A \ref OpenDev "device handle" identifying the oscilloscope.
 * \param[in] dwSegmentCount The required number of segments.
 * \return The actually number of segments that would have been set, if ScpSetSegmentCount() was used.
 * \see ScpGetSegmentCountMax
 * \see ScpGetSegmentCountMaxEx
 * \see ScpGetSegmentCount
 * \see ScpSetSegmentCount
 * \see ScpVerifySegmentCountEx2
 * \since 0.4.3
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef uint32_t(*LibTiePieScpVerifySegmentCount_t)( LibTiePieHandle_t hDevice , uint32_t dwSegmentCount );
#else
uint32_t ScpVerifySegmentCount( LibTiePieHandle_t hDevice , uint32_t dwSegmentCount );
#endif

/**
 * \brief Verify number of segments by measure mode, record length and enabled channels.
 *
 * \param[in] hDevice A \ref OpenDev "device handle" identifying the oscilloscope.
 * \param[in] dwSegmentCount The required number of segments.
 * \param[in] dwMeasureMode Measure mode, a \ref MM_ "MM_*" value.
 * \param[in] qwRecordLength Record length in samples.
 * \param[in] pChannelEnabled Pointer to buffer with channel enables.
 * \param[in] wChannelCount Number of items in \c pChannelEnabled.
 * \return The actually number of segments that would have been set.
 * \see ScpGetSegmentCountMax
 * \see ScpGetSegmentCountMaxEx
 * \see ScpGetSegmentCount
 * \see ScpSetSegmentCount
 * \see ScpVerifySegmentCount
 * \since 0.4.5
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef uint32_t(*LibTiePieScpVerifySegmentCountEx2_t)( LibTiePieHandle_t hDevice , uint32_t dwSegmentCount , uint32_t dwMeasureMode , uint64_t qwRecordLength , const bool8_t* pChannelEnabled , uint16_t wChannelCount );
#else
uint32_t ScpVerifySegmentCountEx2( LibTiePieHandle_t hDevice , uint32_t dwSegmentCount , uint32_t dwMeasureMode , uint64_t qwRecordLength , const bool8_t* pChannelEnabled , uint16_t wChannelCount );
#endif

//! \endcond

/**
 * \}
 * \}
 * \defgroup scp_trigger Trigger
 * \{
 * \brief Functions to control the oscilloscope trigger.
 *
 *          See also the \ref TriggerSystem "Trigger system" page.
 */

// Workaround: Without this line Doxygen adds the documentation below to the group above.

/**
 * \brief Check whether the oscilloscope has trigger support with the currently selected \ref scp_measurements_mode "measure mode".
 *
 * \param[in] hDevice A \ref OpenDev "device handle" identifying the oscilloscope.
 * \return #BOOL8_TRUE if the oscilloscope has trigger support, #BOOL8_FALSE otherwise.
 * \par Status values
 *   <table class="params">
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_HANDLE "INVALID_HANDLE"</td>         <td>The handle is not a valid oscilloscope handle.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_OBJECT_GONE "OBJECT_GONE"</td>            <td>The object indicated by the handle is no longer available.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_LIBRARY_NOT_INITIALIZED "LIBRARY_NOT_INITIALIZED"</td><td>The library is not initialized, see LibInit().</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_SUCCESS "SUCCESS"</td>                <td>The function executed successfully.</td></tr>
 *   </table>
 * \since 0.5
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef bool8_t(*LibTiePieScpHasTrigger_t)( LibTiePieHandle_t hDevice );
#else
bool8_t ScpHasTrigger( LibTiePieHandle_t hDevice );
#endif

//! \cond EXTENDED_API

/**
 * \brief Check whether the oscilloscope has trigger support for a specified measure mode.
 *
 * \param[in] hDevice A \ref OpenDev "device handle" identifying the oscilloscope.
 * \param[in] dwMeasureMode Measure mode, a \ref MM_ "MM_*" value.
 * \return #BOOL8_TRUE if the oscilloscope has trigger support, #BOOL8_FALSE otherwise.
 * \par Status values
 *   <table class="params">
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_VALUE "INVALID_VALUE"</td>          <td>The requested value is invalid.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_HANDLE "INVALID_HANDLE"</td>         <td>The handle is not a valid oscilloscope handle.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_OBJECT_GONE "OBJECT_GONE"</td>            <td>The object indicated by the handle is no longer available.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_LIBRARY_NOT_INITIALIZED "LIBRARY_NOT_INITIALIZED"</td><td>The library is not initialized, see LibInit().</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_SUCCESS "SUCCESS"</td>                <td>The function executed successfully.</td></tr>
 *   </table>
 * \see ScpHasTrigger
 * \since 0.5
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef bool8_t(*LibTiePieScpHasTriggerEx_t)( LibTiePieHandle_t hDevice , uint32_t dwMeasureMode );
#else
bool8_t ScpHasTriggerEx( LibTiePieHandle_t hDevice , uint32_t dwMeasureMode );
#endif

//! \endcond

/**
 * \defgroup scp_trigger_time_out Time out
 * \{
 * \brief Functions to control the oscilloscope trigger time out.
 *
 *           Trigger time out defines the time that the system will wait for a trigger before a trigger is forced.
 *
 *           If the trigger conditions are set in such a way that the input signal(s) will never meet the trigger settings,
 *           the instrument will wait forever. When no measurement is performed, no signals will be displayed.
 *           To avoid that the system will wait infinitely, a trigger time out is added to the trigger system.
 *           When after a user defined amount of time after starting the measurement still no trigger has occurred,
 *           the trigger time out will force a trigger.
 *           This will ensure a minimum number of measurements per second.
 *
 *           The trigger time out is entered as a number, representing the delay in seconds.
 *           There are two special values for the trigger time out setting:
 *           - <b>trigger time out = 0</b> Immediately after starting a measurement a trigger is forced. Basically this bypasses the trigger system and the instrument always measures immediately. No pre samples are recorded. The instrument is free-running, just like when no trigger source is selected.
 *           - <b>trigger time out = infinite</b> (#TO_INFINITY) The system will wait infinitely for a trigger. The software will never force a trigger, only when the trigger conditions are met, a trigger will occur and a measurement will take place. This setting is particularly useful for single shot measurements. On conventional desktop oscilloscopes, this is called Trigger mode NORM.
 *
 *           The trigger time out can be affected by changing the \ref scp_timebase_sampleFrequency "sample frequency".
 *
 *           By default the trigger time out is set to: 0.1 s (100 ms).
 */

// Workaround: Without this line Doxygen adds the documentation below to the group above.

/**
 * \brief Get the currently selected trigger time out in seconds, for a specified oscilloscope.
 *
 * \param[in] hDevice A \ref OpenDev "device handle" identifying the oscilloscope.
 * \return Trigger time out in seconds, or #TO_INFINITY.
 * \par Status values
 *   <table class="params">
 *   <tr><td>\ref LIBTIEPIESTATUS_NOT_SUPPORTED "NOT_SUPPORTED"</td>          <td>The oscilloscope does not support trigger.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_HANDLE "INVALID_HANDLE"</td>         <td>The handle is not a valid oscilloscope handle.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_OBJECT_GONE "OBJECT_GONE"</td>            <td>The object indicated by the handle is no longer available.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_LIBRARY_NOT_INITIALIZED "LIBRARY_NOT_INITIALIZED"</td><td>The library is not initialized, see LibInit().</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_SUCCESS "SUCCESS"</td>                <td>The function executed successfully.</td></tr>
 *   </table>
 * \see ScpSetTriggerTimeOut
 * \since 0.4.0
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef double(*LibTiePieScpGetTriggerTimeOut_t)( LibTiePieHandle_t hDevice );
#else
double ScpGetTriggerTimeOut( LibTiePieHandle_t hDevice );
#endif

/**
 * \brief Set the trigger time out in seconds, for a specified oscilloscope.
 *
 * \param[in] hDevice A \ref OpenDev "device handle" identifying the oscilloscope.
 * \param[in] dTimeOut The required trigger time out in seconds, or #TO_INFINITY.
 * \return The actually set trigger time out in seconds, or #TO_INFINITY.
 * \par Status values
 *   <table class="params">
 *   <tr><td>\ref LIBTIEPIESTATUS_VALUE_MODIFIED "VALUE_MODIFIED"</td>         <td>The requested trigger time out is within the valid range but not available. The closest valid value is set.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_VALUE "INVALID_VALUE"</td>          <td>The requested value is invalid.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_NOT_SUPPORTED "NOT_SUPPORTED"</td>          <td>The oscilloscope does not support trigger.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_HANDLE "INVALID_HANDLE"</td>         <td>The handle is not a valid oscilloscope handle.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_OBJECT_GONE "OBJECT_GONE"</td>            <td>The object indicated by the handle is no longer available.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_LIBRARY_NOT_INITIALIZED "LIBRARY_NOT_INITIALIZED"</td><td>The library is not initialized, see LibInit().</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_SUCCESS "SUCCESS"</td>                <td>The function executed successfully.</td></tr>
 *   </table>
 * \see ScpGetTriggerTimeOut
 * \since 0.4.0
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef double(*LibTiePieScpSetTriggerTimeOut_t)( LibTiePieHandle_t hDevice , double dTimeOut );
#else
double ScpSetTriggerTimeOut( LibTiePieHandle_t hDevice , double dTimeOut );
#endif

//! \cond EXTENDED_API

/**
 * \brief Verify if a required trigger time out can be set, for the specified device, without actually setting the hardware itself.
 *
 * \param[in] hDevice A \ref OpenDev "device handle".
 * \param[in] dTimeOut The required trigger time out in seconds, or #TO_INFINITY.
 * \return The trigger time out that would have been set, if ScpSetTriggerTimeOut() was used.
 * \see ScpGetTriggerTimeOut
 * \see ScpSetTriggerTimeOut
 * \see ScpVerifyTriggerTimeOutEx
 * \since 0.4.0
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef double(*LibTiePieScpVerifyTriggerTimeOut_t)( LibTiePieHandle_t hDevice , double dTimeOut );
#else
double ScpVerifyTriggerTimeOut( LibTiePieHandle_t hDevice , double dTimeOut );
#endif

/**
 * \brief Verify if a required trigger time out can be set, for the specified device, without actually setting the hardware itself.
 *
 * \param[in] hDevice A \ref OpenDev "device handle".
 * \param[in] dTimeOut The required trigger time out in seconds, or #TO_INFINITY.
 * \param[in] dwMeasureMode Measure mode, a \ref MM_ "MM_*" value.
 * \param[in] dSampleFrequency Sample frequency in Hz.
 * \return The trigger time out that would have been set, if ScpSetTriggerTimeOut() was used.
 * \see ScpGetTriggerTimeOut
 * \see ScpSetTriggerTimeOut
 * \see ScpVerifyTriggerTimeOut
 * \since 0.4.3
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef double(*LibTiePieScpVerifyTriggerTimeOutEx_t)( LibTiePieHandle_t hDevice , double dTimeOut , uint32_t dwMeasureMode , double dSampleFrequency );
#else
double ScpVerifyTriggerTimeOutEx( LibTiePieHandle_t hDevice , double dTimeOut , uint32_t dwMeasureMode , double dSampleFrequency );
#endif

//! \endcond

/**
 * \}
 * \defgroup scp_trigger_delay Delay
 * \{
 * \brief Functions to control the trigger delay of an oscilloscope.
 *
 *           Trigger delay allows to start measuring a specified time after the trigger occurred.
 *           This allows to capture events that are more than one full record length past the trigger moment.
 *
 *           Trigger delay is not available for all instruments and only available in \ref scp_measurements_mode "measure mode" Block.
 *           Use ScpHasTriggerDelay() to check whether trigger delay is available for your instrument and in the currently set measure mode.
 *
 *           The trigger delay can be affected by changing the \ref scp_timebase_sampleFrequency "sample frequency".
 */

// Workaround: Without this line Doxygen adds the documentation below to the group above.

/**
 * \brief Check whether the oscilloscope has trigger delay support with the currently selected \ref scp_measurements_mode "measure mode".
 *
 * \param[in] hDevice A \ref OpenDev "device handle" identifying the oscilloscope.
 * \return #BOOL8_TRUE if the oscilloscope has trigger delay support, #BOOL8_FALSE otherwise.
 * \par Status values
 *   <table class="params">
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_HANDLE "INVALID_HANDLE"</td>         <td>The handle is not a valid oscilloscope handle.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_OBJECT_GONE "OBJECT_GONE"</td>            <td>The object indicated by the handle is no longer available.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_LIBRARY_NOT_INITIALIZED "LIBRARY_NOT_INITIALIZED"</td><td>The library is not initialized, see LibInit().</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_SUCCESS "SUCCESS"</td>                <td>The function executed successfully.</td></tr>
 *   </table>
 * \since 0.5
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef bool8_t(*LibTiePieScpHasTriggerDelay_t)( LibTiePieHandle_t hDevice );
#else
bool8_t ScpHasTriggerDelay( LibTiePieHandle_t hDevice );
#endif

//! \cond EXTENDED_API

/**
 * \brief Check whether the oscilloscope has trigger delay support for a specified measure mode.
 *
 * \param[in] hDevice A \ref OpenDev "device handle" identifying the oscilloscope.
 * \param[in] dwMeasureMode Measure mode, a \ref MM_ "MM_*" value.
 * \return #BOOL8_TRUE if the oscilloscope has trigger delay support, #BOOL8_FALSE otherwise.
 * \par Status values
 *   <table class="params">
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_VALUE "INVALID_VALUE"</td>          <td>The requested value is invalid.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_HANDLE "INVALID_HANDLE"</td>         <td>The handle is not a valid oscilloscope handle.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_OBJECT_GONE "OBJECT_GONE"</td>            <td>The object indicated by the handle is no longer available.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_LIBRARY_NOT_INITIALIZED "LIBRARY_NOT_INITIALIZED"</td><td>The library is not initialized, see LibInit().</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_SUCCESS "SUCCESS"</td>                <td>The function executed successfully.</td></tr>
 *   </table>
 * \see ScpHasTriggerDelay
 * \since 0.5
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef bool8_t(*LibTiePieScpHasTriggerDelayEx_t)( LibTiePieHandle_t hDevice , uint32_t dwMeasureMode );
#else
bool8_t ScpHasTriggerDelayEx( LibTiePieHandle_t hDevice , uint32_t dwMeasureMode );
#endif

//! \endcond

/**
 * \brief Get the maximum trigger delay in seconds, for the currently selected \ref scp_measurements_mode "measure mode" and \ref scp_timebase_sampleFrequency "sample frequency".
 *
 * \param[in] hDevice A \ref OpenDev "device handle" identifying the oscilloscope.
 * \return The maximum trigger delay in seconds.
 * \par Status values
 *   <table class="params">
 *   <tr><td>\ref LIBTIEPIESTATUS_NOT_SUPPORTED "NOT_SUPPORTED"</td>          <td>The oscilloscope does not support trigger delay.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_HANDLE "INVALID_HANDLE"</td>         <td>The handle is not a valid oscilloscope handle.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_OBJECT_GONE "OBJECT_GONE"</td>            <td>The object indicated by the handle is no longer available.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_LIBRARY_NOT_INITIALIZED "LIBRARY_NOT_INITIALIZED"</td><td>The library is not initialized, see LibInit().</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_SUCCESS "SUCCESS"</td>                <td>The function executed successfully.</td></tr>
 *   </table>
 * \see ScpHasTriggerDelay
 * \see ScpGetTriggerDelay
 * \see ScpSetTriggerDelay
 * \since 0.5
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef double(*LibTiePieScpGetTriggerDelayMax_t)( LibTiePieHandle_t hDevice );
#else
double ScpGetTriggerDelayMax( LibTiePieHandle_t hDevice );
#endif

//! \cond EXTENDED_API

/**
 * \brief  Get the maximum trigger delay in seconds, for a specified measure mode and sample frequency.
 *
 * \param[in] hDevice A \ref OpenDev "device handle" identifying the oscilloscope.
 * \param[in] dwMeasureMode Measure mode, a \ref MM_ "MM_*" value.
 * \param[in] dSampleFrequency Sample frequency in Hz.
 * \return The maximum trigger delay in seconds.
 * \par Status values
 *   <table class="params">
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_VALUE "INVALID_VALUE"</td>          <td>The requested value is invalid.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_HANDLE "INVALID_HANDLE"</td>         <td>The handle is not a valid oscilloscope handle.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_OBJECT_GONE "OBJECT_GONE"</td>            <td>The object indicated by the handle is no longer available.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_LIBRARY_NOT_INITIALIZED "LIBRARY_NOT_INITIALIZED"</td><td>The library is not initialized, see LibInit().</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_SUCCESS "SUCCESS"</td>                <td>The function executed successfully.</td></tr>
 *   </table>
 * \see ScpHasTriggerDelay
 * \see ScpHasTriggerDelayEx
 * \see ScpGetTriggerDelayMax
 * \see ScpGetTriggerDelay
 * \see ScpSetTriggerDelay
 * \see ScpVerifyTriggerDelay
 * \see ScpVerifyTriggerDelayEx
 * \since 0.5
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef double(*LibTiePieScpGetTriggerDelayMaxEx_t)( LibTiePieHandle_t hDevice , uint32_t dwMeasureMode , double dSampleFrequency );
#else
double ScpGetTriggerDelayMaxEx( LibTiePieHandle_t hDevice , uint32_t dwMeasureMode , double dSampleFrequency );
#endif

//! \endcond

/**
 * \brief Get the currently selected trigger delay in seconds, for a specified oscilloscope.
 *
 * \param[in] hDevice A \ref OpenDev "device handle" identifying the oscilloscope.
 * \return The currently set trigger delay in seconds.
 * \par Status values
 *   <table class="params">
 *   <tr><td>\ref LIBTIEPIESTATUS_NOT_SUPPORTED "NOT_SUPPORTED"</td>          <td>The oscilloscope does not support trigger delay.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_HANDLE "INVALID_HANDLE"</td>         <td>The handle is not a valid oscilloscope handle.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_OBJECT_GONE "OBJECT_GONE"</td>            <td>The object indicated by the handle is no longer available.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_LIBRARY_NOT_INITIALIZED "LIBRARY_NOT_INITIALIZED"</td><td>The library is not initialized, see LibInit().</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_SUCCESS "SUCCESS"</td>                <td>The function executed successfully.</td></tr>
 *   </table>
 * \see ScpHasTriggerDelay
 * \see ScpGetTriggerDelayMax
 * \see ScpSetTriggerDelay
 * \since 0.4.3
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef double(*LibTiePieScpGetTriggerDelay_t)( LibTiePieHandle_t hDevice );
#else
double ScpGetTriggerDelay( LibTiePieHandle_t hDevice );
#endif

/**
 * \brief Set trigger delay in seconds, for a specified oscilloscope.
 *
 * \param[in] hDevice A \ref OpenDev "device handle" identifying the oscilloscope.
 * \param[in] dDelay The required trigger delay in seconds.
 * \return The actually set trigger delay in seconds.
 * \par Status values
 *   <table class="params">
 *   <tr><td>\ref LIBTIEPIESTATUS_VALUE_MODIFIED "VALUE_MODIFIED"</td>         <td>The requested trigger delay is within the valid range but not available. The closest valid value is set.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_VALUE "INVALID_VALUE"</td>          <td>The requested value is invalid.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_NOT_SUPPORTED "NOT_SUPPORTED"</td>          <td>The oscilloscope does not support trigger delay.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_HANDLE "INVALID_HANDLE"</td>         <td>The handle is not a valid oscilloscope handle.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_OBJECT_GONE "OBJECT_GONE"</td>            <td>The object indicated by the handle is no longer available.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_LIBRARY_NOT_INITIALIZED "LIBRARY_NOT_INITIALIZED"</td><td>The library is not initialized, see LibInit().</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_SUCCESS "SUCCESS"</td>                <td>The function executed successfully.</td></tr>
 *   </table>
 * \see ScpHasTriggerDelay
 * \see ScpGetTriggerDelayMax
 * \see ScpGetTriggerDelay
 * \since 0.4.3
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef double(*LibTiePieScpSetTriggerDelay_t)( LibTiePieHandle_t hDevice , double dDelay );
#else
double ScpSetTriggerDelay( LibTiePieHandle_t hDevice , double dDelay );
#endif

//! \cond EXTENDED_API

/**
 * \brief Verify if a required trigger delay can be set, for the specified device, without actually setting the hardware itself.
 *
 * \param[in] hDevice A \ref OpenDev "device handle".
 * \param[in] dDelay The required trigger delay in seconds.
 * \return The trigger delay that would have been set, if ScpSetTriggerDelay() was used.
 * \see ScpHasTriggerDelay
 * \see ScpHasTriggerDelayEx
 * \see ScpGetTriggerDelayMax
 * \see ScpGetTriggerDelay
 * \see ScpSetTriggerDelay
 * \see ScpVerifyTriggerDelayEx
 * \since 0.4.3
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef double(*LibTiePieScpVerifyTriggerDelay_t)( LibTiePieHandle_t hDevice , double dDelay );
#else
double ScpVerifyTriggerDelay( LibTiePieHandle_t hDevice , double dDelay );
#endif

/**
 * \brief Verify if a required trigger delay can be set, for the specified device, without actually setting the hardware itself.
 *
 * \param[in] hDevice A \ref OpenDev "device handle".
 * \param[in] dDelay The required trigger delay in seconds.
 * \param[in] dwMeasureMode Measure mode, a \ref MM_ "MM_*" value.
 * \param[in] dSampleFrequency Sample frequency in Hz.
 * \return The trigger delay that would have been set, if ScpSetTriggerDelay() was used.
 * \see ScpHasTriggerDelay
 * \see ScpHasTriggerDelayEx
 * \see ScpGetTriggerDelayMax
 * \see ScpGetTriggerDelay
 * \see ScpSetTriggerDelay
 * \see ScpVerifyTriggerDelay
 * \since 0.4.3
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef double(*LibTiePieScpVerifyTriggerDelayEx_t)( LibTiePieHandle_t hDevice , double dDelay , uint32_t dwMeasureMode , double dSampleFrequency );
#else
double ScpVerifyTriggerDelayEx( LibTiePieHandle_t hDevice , double dDelay , uint32_t dwMeasureMode , double dSampleFrequency );
#endif

//! \endcond

/**
 * \}
 * \defgroup scp_trigger_HoldOff Hold off
 * \{
 * \brief Functions to control the trigger hold off of an oscilloscope.
 *
 *           Trigger hold off defines a period of time after starting a measurement in which the oscilloscope will not respond to triggers.
 *           It is used to get stable triggering on periodical signals that have multiple moments that would otherwise generate a trigger.
 *
 *           When \ref scp_timebase_preSamples "pre samples" are selected, trigger hold off can be used to ensure that all pre samples are
 *           measured before a trigger occurs. Set the trigger hold off to #TH_ALLPRESAMPLES to measure all pre samples and have no invalid pre samples.
 *
 *           Trigger hold off is not available for all instruments and only available in \ref scp_measurements_mode "measure mode" Block.
 *           Use ScpHasTriggerHoldOff() to check whether trigger hold off is available for your instrument and in the currently set measure mode.
 *
 *           Trigger hold off is set in a number of samples.
 *           By default the trigger hold off is set to: 0 samples.
 */

// Workaround: Without this line Doxygen adds the documentation below to the group above.

/**
 * \brief Check whether the oscilloscope has trigger hold off support with the currently selected \ref scp_measurements_mode "measure mode".
 *
 * \param[in] hDevice A \ref OpenDev "device handle" identifying the oscilloscope.
 * \return #BOOL8_TRUE if the oscilloscope has trigger hold off support, #BOOL8_FALSE otherwise.
 * \par Status values
 *   <table class="params">
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_HANDLE "INVALID_HANDLE"</td>         <td>The handle is not a valid oscilloscope handle.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_OBJECT_GONE "OBJECT_GONE"</td>            <td>The object indicated by the handle is no longer available.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_LIBRARY_NOT_INITIALIZED "LIBRARY_NOT_INITIALIZED"</td><td>The library is not initialized, see LibInit().</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_SUCCESS "SUCCESS"</td>                <td>The function executed successfully.</td></tr>
 *   </table>
 * \since 0.5
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef bool8_t(*LibTiePieScpHasTriggerHoldOff_t)( LibTiePieHandle_t hDevice );
#else
bool8_t ScpHasTriggerHoldOff( LibTiePieHandle_t hDevice );
#endif

//! \cond EXTENDED_API

/**
 * \brief Check whether the oscilloscope has trigger hold off support for a specified measure mode.
 *
 * \param[in] hDevice A \ref OpenDev "device handle" identifying the oscilloscope.
 * \param[in] dwMeasureMode Measure mode, a \ref MM_ "MM_*" value.
 * \return #BOOL8_TRUE if the oscilloscope has trigger hold off support, #BOOL8_FALSE otherwise.
 * \par Status values
 *   <table class="params">
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_VALUE "INVALID_VALUE"</td>          <td>The requested value is invalid.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_HANDLE "INVALID_HANDLE"</td>         <td>The handle is not a valid oscilloscope handle.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_OBJECT_GONE "OBJECT_GONE"</td>            <td>The object indicated by the handle is no longer available.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_LIBRARY_NOT_INITIALIZED "LIBRARY_NOT_INITIALIZED"</td><td>The library is not initialized, see LibInit().</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_SUCCESS "SUCCESS"</td>                <td>The function executed successfully.</td></tr>
 *   </table>
 * \see ScpHasTriggerHoldOff
 * \see ScpGetTriggerHoldOffCountMax
 * \see ScpGetTriggerHoldOffCountMaxEx
 * \see ScpGetTriggerHoldOffCount
 * \see ScpSetTriggerHoldOffCount
 * \since 0.5
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef bool8_t(*LibTiePieScpHasTriggerHoldOffEx_t)( LibTiePieHandle_t hDevice , uint32_t dwMeasureMode );
#else
bool8_t ScpHasTriggerHoldOffEx( LibTiePieHandle_t hDevice , uint32_t dwMeasureMode );
#endif

//! \endcond

/**
 * \brief Get the maximum trigger hold off count in samples, for a specified oscilloscope.
 *
 * \param[in] hDevice A \ref OpenDev "device handle" identifying the oscilloscope.
 * \return The maximum trigger hold off count in samples.
 * \par Status values
 *   <table class="params">
 *   <tr><td>\ref LIBTIEPIESTATUS_NOT_SUPPORTED "NOT_SUPPORTED"</td>          <td>The oscilloscope does not support trigger hold off.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_HANDLE "INVALID_HANDLE"</td>         <td>The handle is not a valid oscilloscope handle.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_OBJECT_GONE "OBJECT_GONE"</td>            <td>The object indicated by the handle is no longer available.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_LIBRARY_NOT_INITIALIZED "LIBRARY_NOT_INITIALIZED"</td><td>The library is not initialized, see LibInit().</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_SUCCESS "SUCCESS"</td>                <td>The function executed successfully.</td></tr>
 *   </table>
 * \see ScpHasTriggerHoldOff
 * \see ScpGetTriggerHoldOffCount
 * \see ScpSetTriggerHoldOffCount
 * \since 0.4.0
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef uint64_t(*LibTiePieScpGetTriggerHoldOffCountMax_t)( LibTiePieHandle_t hDevice );
#else
uint64_t ScpGetTriggerHoldOffCountMax( LibTiePieHandle_t hDevice );
#endif

//! \cond EXTENDED_API

/**
 * \brief Get maximum trigger hold off count in samples for a specified measure mode, for a specified oscilloscope.
 *
 * \param[in] hDevice A \ref OpenDev "device handle" identifying the oscilloscope.
 * \param[in] dwMeasureMode Measure mode, a \ref MM_ "MM_*" value.
 * \return Maximum trigger hold off count in samples.
 * \see ScpHasTriggerHoldOff
 * \see ScpHasTriggerHoldOffEx
 * \see ScpGetTriggerHoldOffCountMax
 * \see ScpGetTriggerHoldOffCount
 * \see ScpSetTriggerHoldOffCount
 * \since 0.4.0
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef uint64_t(*LibTiePieScpGetTriggerHoldOffCountMaxEx_t)( LibTiePieHandle_t hDevice , uint32_t dwMeasureMode );
#else
uint64_t ScpGetTriggerHoldOffCountMaxEx( LibTiePieHandle_t hDevice , uint32_t dwMeasureMode );
#endif

//! \endcond

/**
 * \brief Get the trigger hold off count in samples, for a specified oscilloscope.
 *
 * \param[in] hDevice A \ref OpenDev "device handle" identifying the oscilloscope.
 * \return The currently set trigger hold off count in samples.
 * \par Status values
 *   <table class="params">
 *   <tr><td>\ref LIBTIEPIESTATUS_NOT_SUPPORTED "NOT_SUPPORTED"</td>          <td>The oscilloscope does not support trigger hold off.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_HANDLE "INVALID_HANDLE"</td>         <td>The handle is not a valid oscilloscope handle.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_OBJECT_GONE "OBJECT_GONE"</td>            <td>The object indicated by the handle is no longer available.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_LIBRARY_NOT_INITIALIZED "LIBRARY_NOT_INITIALIZED"</td><td>The library is not initialized, see LibInit().</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_SUCCESS "SUCCESS"</td>                <td>The function executed successfully.</td></tr>
 *   </table>
 * \see ScpHasTriggerHoldOff
 * \see ScpGetTriggerHoldOffCountMax
 * \see ScpSetTriggerHoldOffCount
 * \since 0.4.0
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef uint64_t(*LibTiePieScpGetTriggerHoldOffCount_t)( LibTiePieHandle_t hDevice );
#else
uint64_t ScpGetTriggerHoldOffCount( LibTiePieHandle_t hDevice );
#endif

/**
 * \brief Set the trigger hold off count in samples, for a specified oscilloscope.
 *
 * \param[in] hDevice A \ref OpenDev "device handle" identifying the oscilloscope.
 * \param[in] qwTriggerHoldOffCount The required trigger hold off count in samples.
 * \return The actually set trigger hold off count in samples.
 * \par Status values
 *   <table class="params">
 *   <tr><td>\ref LIBTIEPIESTATUS_VALUE_CLIPPED "VALUE_CLIPPED"</td>          <td>The requested trigger hold off count is outside the valid range and clipped to the closest limit.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_NOT_SUPPORTED "NOT_SUPPORTED"</td>          <td>The oscilloscope does not support trigger hold off.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_HANDLE "INVALID_HANDLE"</td>         <td>The handle is not a valid oscilloscope handle.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_OBJECT_GONE "OBJECT_GONE"</td>            <td>The object indicated by the handle is no longer available.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_LIBRARY_NOT_INITIALIZED "LIBRARY_NOT_INITIALIZED"</td><td>The library is not initialized, see LibInit().</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_SUCCESS "SUCCESS"</td>                <td>The function executed successfully.</td></tr>
 *   </table>
 * \see ScpHasTriggerHoldOff
 * \see ScpGetTriggerHoldOffCountMax
 * \see ScpGetTriggerHoldOffCount
 * \since 0.4.0
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef uint64_t(*LibTiePieScpSetTriggerHoldOffCount_t)( LibTiePieHandle_t hDevice , uint64_t qwTriggerHoldOffCount );
#else
uint64_t ScpSetTriggerHoldOffCount( LibTiePieHandle_t hDevice , uint64_t qwTriggerHoldOffCount );
#endif

/**
 * \}
 * \}
 * \defgroup scp_ct Connection test
 * \{
 * \brief Functions to perform a connection test.
 *
 *         To check whether the measurement probe on a channel is electrically connected to the device under test,
 *         a connection test can be performed on instruments with <a class="External"
 *         href="http://www.tiepie.com/Articles/SureConnect">SureConnect</a>.
 *         To find out whether the connection test is ready, ScpIsConnectionTestCompleted() can be polled, or
 *         a \ref scp_notifications_connectionTestCompleted "notification" can be used.
 *         When the connection test is ready, connection test data indicating the connection status of the input(s)
 *         can be collected using ScpGetConnectionTestData().
 *
 *         Connection test is not available for all instruments.
 *         Use ScpHasConnectionTest() to check whether connection test is available for your instrument.
 */

// Workaround: Without this line Doxygen adds the documentation below to the group above.

/**
 * \brief Check whether the specified oscilloscope supports connection testing.
 *
 * \param[in] hDevice A \ref OpenDev "device handle" identifying the oscilloscope.
 * \return #BOOL8_TRUE when at least one channel supports connection testing, #BOOL8_FALSE otherwise.
 * \par Status values
 *   <table class="params">
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_HANDLE "INVALID_HANDLE"</td>         <td>The handle is not a valid oscilloscope handle.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_OBJECT_GONE "OBJECT_GONE"</td>            <td>The object indicated by the handle is no longer available.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_LIBRARY_NOT_INITIALIZED "LIBRARY_NOT_INITIALIZED"</td><td>The library is not initialized, see LibInit().</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_SUCCESS "SUCCESS"</td>                <td>The function executed successfully.</td></tr>
 *   </table>
 * \see ScpChHasConnectionTest
 * \since 0.4.0
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef bool8_t(*LibTiePieScpHasConnectionTest_t)( LibTiePieHandle_t hDevice );
#else
bool8_t ScpHasConnectionTest( LibTiePieHandle_t hDevice );
#endif

/**
 * \brief Check whether a specified channel of a specified oscilloscope supports connection testing.
 *
 * \param[in] hDevice A \ref OpenDev "device handle" identifying the oscilloscope.
 * \param[in] wCh A channel number identifying the channel, \c 0 to <tt>ScpGetChannelCount() - 1</tt>.
 * \return #BOOL8_TRUE if the channel supports connection test, #BOOL8_FALSE otherwise.
 * \par Status values
 *   <table class="params">
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_CHANNEL "INVALID_CHANNEL"</td>        <td>The requested channel number is invalid.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_HANDLE "INVALID_HANDLE"</td>         <td>The handle is not a valid oscilloscope handle.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_OBJECT_GONE "OBJECT_GONE"</td>            <td>The object indicated by the handle is no longer available.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_LIBRARY_NOT_INITIALIZED "LIBRARY_NOT_INITIALIZED"</td><td>The library is not initialized, see LibInit().</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_SUCCESS "SUCCESS"</td>                <td>The function executed successfully.</td></tr>
 *   </table>
 * \see ScpHasConnectionTest
 * \since 0.4.0
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef bool8_t(*LibTiePieScpChHasConnectionTest_t)( LibTiePieHandle_t hDevice , uint16_t wCh );
#else
bool8_t ScpChHasConnectionTest( LibTiePieHandle_t hDevice , uint16_t wCh );
#endif

/**
 * \brief Perform a connection test on all enabled channels of a specified oscilloscope.
 *
 * \param[in] hDevice A \ref OpenDev "device handle" identifying the oscilloscope.
 * \return #BOOL8_TRUE if started successfully, #BOOL8_FALSE otherwise.
 * \par Status values
 *   <table class="params">
 *   <tr><td>\ref LIBTIEPIESTATUS_UNSUCCESSFUL "UNSUCCESSFUL"</td>           <td>No channels are enabled or a measurement is busy.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_NOT_SUPPORTED "NOT_SUPPORTED"</td>          <td>The oscilloscope does not support connection test.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_HANDLE "INVALID_HANDLE"</td>         <td>The handle is not a valid oscilloscope handle.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_OBJECT_GONE "OBJECT_GONE"</td>            <td>The object indicated by the handle is no longer available.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_LIBRARY_NOT_INITIALIZED "LIBRARY_NOT_INITIALIZED"</td><td>The library is not initialized, see LibInit().</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_SUCCESS "SUCCESS"</td>                <td>The function executed successfully.</td></tr>
 *   </table>
 * \see ScpHasConnectionTest
 * \see ScpChHasConnectionTest
 * \see ScpIsConnectionTestCompleted
 * \see ScpGetConnectionTestData
 * \since 0.5
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef bool8_t(*LibTiePieScpStartConnectionTest_t)( LibTiePieHandle_t hDevice );
#else
bool8_t ScpStartConnectionTest( LibTiePieHandle_t hDevice );
#endif

//! \cond EXTENDED_API

/**
 * \brief Perform a connection test on all channels of a specified oscilloscope.
 *
 * The enabled status of the channels on entry is buffered in an array pointed to by \c pChannelEnabled.
 * During the test, all channels will be enabled.
 * On exit, the original enabled status of the channels will be reset.
 *
 * \param[in] hDevice A \ref OpenDev "device handle" identifying the oscilloscope.
 * \param[in] pChannelEnabled A pointer to a buffer with channel enables.
 * \param[in] wChannelCount The number of items in \c pChannelEnabled.
 * \return #BOOL8_TRUE if started successfully, #BOOL8_FALSE otherwise.
 * \par Status values
 *   <table class="params">
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_CHANNEL "INVALID_CHANNEL"</td>        <td>The requested channel number is invalid.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_UNSUCCESSFUL "UNSUCCESSFUL"</td>           <td>No channels are enabled or a measurement is busy.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_NOT_SUPPORTED "NOT_SUPPORTED"</td>          <td>The oscilloscope does not support connection test.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_HANDLE "INVALID_HANDLE"</td>         <td>The handle is not a valid oscilloscope handle.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_OBJECT_GONE "OBJECT_GONE"</td>            <td>The object indicated by the handle is no longer available.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_LIBRARY_NOT_INITIALIZED "LIBRARY_NOT_INITIALIZED"</td><td>The library is not initialized, see LibInit().</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_SUCCESS "SUCCESS"</td>                <td>The function executed successfully.</td></tr>
 *   </table>
 * \see ScpHasConnectionTest
 * \see ScpChHasConnectionTest
 * \see ScpStartConnectionTest
 * \see ScpIsConnectionTestCompleted
 * \see ScpGetConnectionTestData
 * \since 0.4.5
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef bool8_t(*LibTiePieScpStartConnectionTestEx_t)( LibTiePieHandle_t hDevice , const bool8_t* pChannelEnabled , uint16_t wChannelCount );
#else
bool8_t ScpStartConnectionTestEx( LibTiePieHandle_t hDevice , const bool8_t* pChannelEnabled , uint16_t wChannelCount );
#endif

//! \endcond

/**
 * \brief Check whether the connection test on a specified oscilloscope is completed.
 *
 * \param[in] hDevice A \ref OpenDev "device handle" identifying the oscilloscope.
 * \return #BOOL8_TRUE if completed, #BOOL8_FALSE otherwise.
 * \par Status values
 *   <table class="params">
 *   <tr><td>\ref LIBTIEPIESTATUS_NOT_SUPPORTED "NOT_SUPPORTED"</td>          <td>The oscilloscope does not support connection test.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_HANDLE "INVALID_HANDLE"</td>         <td>The handle is not a valid oscilloscope handle.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_OBJECT_GONE "OBJECT_GONE"</td>            <td>The object indicated by the handle is no longer available.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_LIBRARY_NOT_INITIALIZED "LIBRARY_NOT_INITIALIZED"</td><td>The library is not initialized, see LibInit().</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_SUCCESS "SUCCESS"</td>                <td>The function executed successfully.</td></tr>
 *   </table>
 * \see ScpHasConnectionTest
 * \see ScpChHasConnectionTest
 * \see ScpStartConnectionTest
 * \see notification scp_notifications_connectionTestCompleted
 * \see ScpGetConnectionTestData
 * \since 0.4.0
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef bool8_t(*LibTiePieScpIsConnectionTestCompleted_t)( LibTiePieHandle_t hDevice );
#else
bool8_t ScpIsConnectionTestCompleted( LibTiePieHandle_t hDevice );
#endif

/**
 * \brief Get the connection test result data for a specified oscilloscope.
 *
 * The test result data is presented in an array \c pBuffer with an element for each channel.
 * Each element contains the connection test status for a channel:
 * - #LIBTIEPIE_TRISTATE_UNDEFINED this channel is not enabled or does not support connection test.
 * - #LIBTIEPIE_TRISTATE_FALSE this channel has no connection
 * - #LIBTIEPIE_TRISTATE_TRUE this channel has connection
 *
 * \param[in] hDevice A \ref OpenDev "device handle" identifying the oscilloscope.
 * \param[out] pBuffer A pointer to a #LibTiePieTriState_t array.
 * \param[in] wChannelCount The length of the #LibTiePieTriState_t array.
 * \return The number of elements written in the LibTiePieTriState_t array.
 * \par Status values
 *   <table class="params">
 *   <tr><td>\ref LIBTIEPIESTATUS_NOT_SUPPORTED "NOT_SUPPORTED"</td>          <td>The oscilloscope does not support connection test.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_VALUE "INVALID_VALUE"</td>          <td>The pointer \c pBuffer was \c NULL or \c wChannelCount was \c 0.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_UNSUCCESSFUL "UNSUCCESSFUL"</td>           <td>No connection test result data available.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_HANDLE "INVALID_HANDLE"</td>         <td>The handle is not a valid oscilloscope handle.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_OBJECT_GONE "OBJECT_GONE"</td>            <td>The object indicated by the handle is no longer available.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_LIBRARY_NOT_INITIALIZED "LIBRARY_NOT_INITIALIZED"</td><td>The library is not initialized, see LibInit().</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_SUCCESS "SUCCESS"</td>                <td>The function executed successfully.</td></tr>
 *   </table>
 * \par Example
 * \code{.c}
 * uint16_t wChannelCount = ScpGetChannelCount( hDevice );
 * LibTiePieTriState_t* pConnections = malloc( sizeof( LibTiePieTriState_t ) * wChannelCount );
 * ScpGetConnectionTestData( hDevice , pConnections , wChannelCount );
 *
 * printf( "ScpGetConnectionTestData ( ):\n" );
 * for( uint16_t i = 0 ; i < wChannelCount ; i++ )
 *   switch( pConnections )
 *   {
 *     case LIBTIEPIE_TRISTATE_UNDEFINED:
 *       printf( "- Ch%u Undefined\n", i + 1 );
 *       break;
 *
 *     case LIBTIEPIE_TRISTATE_FALSE:
 *       printf( "- Ch%u Not connected\n", i + 1 );
 *       break;
 *
 *     case LIBTIEPIE_TRISTATE_TRUE:
 *       printf( "- Ch%u Connected\n", i + 1 );
 *       break;
 *
 *     default:
 *       printf( "- Ch%u Invalid value\n", i + 1 );
 *       break;
 *   }
 *
 * free( pConnections );
 * \endcode
 * \see ScpHasConnectionTest
 * \see ScpChHasConnectionTest
 * \see ScpStartConnectionTest
 * \see ScpIsConnectionTestCompleted
 * \since 0.4.0
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef uint16_t(*LibTiePieScpGetConnectionTestData_t)( LibTiePieHandle_t hDevice , LibTiePieTriState_t* pBuffer , uint16_t wChannelCount );
#else
uint16_t ScpGetConnectionTestData( LibTiePieHandle_t hDevice , LibTiePieTriState_t* pBuffer , uint16_t wChannelCount );
#endif

/**
 * \}
 * \}
 * \defgroup gen Generator
 * \{
 * \brief Functions to setup and control generators.
 *
 *       All generator related functions require a \ref LibTiePieHandle_t "generator handle" to identify the generator,
 *       see \ref OpenDev "opening a device".
 *
 *       In certain conditions, like when performing a streaming measurement with the oscilloscope, the generator cannot be controlled.
 *       Use GenIsControllable() to check if the generator can be controlled.
 *
 * \defgroup gen_info Info
 * \{
 * \brief Functions that provide information of a generator.
 */

// Workaround: Without this line Doxygen adds the documentation below to the group above.

/**
 * \brief Get the output \ref CONNECTORTYPE_ "connector type" for a specified generator.
 *
 * \param[in] hDevice A \ref OpenDev "device handle" identifying the generator.
 * \return The output \ref CONNECTORTYPE_ "connector type", #CONNECTORTYPE_UNKNOWN when unsuccessful.
 * \par Status values
 *   <table class="params">
 *   <tr><td>\ref LIBTIEPIESTATUS_NOT_SUPPORTED "NOT_SUPPORTED"</td>          <td>The generator does not support getting the connector type.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_HANDLE "INVALID_HANDLE"</td>         <td>The handle is not a valid generator handle.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_OBJECT_GONE "OBJECT_GONE"</td>            <td>The object indicated by the handle is no longer available.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_LIBRARY_NOT_INITIALIZED "LIBRARY_NOT_INITIALIZED"</td><td>The library is not initialized, see LibInit().</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_SUCCESS "SUCCESS"</td>                <td>The function executed successfully.</td></tr>
 *   </table>
 * \since 0.4.0
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef uint32_t(*LibTiePieGenGetConnectorType_t)( LibTiePieHandle_t hDevice );
#else
uint32_t GenGetConnectorType( LibTiePieHandle_t hDevice );
#endif

/**
 * \brief Check whether the output of a specified generator is differential.
 *
 * \param[in] hDevice A \ref OpenDev "device handle" identifying the generator.
 * \return #BOOL8_TRUE when the output is differential, #BOOL8_FALSE otherwise.
 * \par Status values
 *   <table class="params">
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_HANDLE "INVALID_HANDLE"</td>         <td>The handle is not a valid generator handle.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_OBJECT_GONE "OBJECT_GONE"</td>            <td>The object indicated by the handle is no longer available.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_LIBRARY_NOT_INITIALIZED "LIBRARY_NOT_INITIALIZED"</td><td>The library is not initialized, see LibInit().</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_SUCCESS "SUCCESS"</td>                <td>The function executed successfully.</td></tr>
 *   </table>
 * \since 0.4.0
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef bool8_t(*LibTiePieGenIsDifferential_t)( LibTiePieHandle_t hDevice );
#else
bool8_t GenIsDifferential( LibTiePieHandle_t hDevice );
#endif

/**
 * \brief Get the output impedance of a specified generator.
 *
 * \param[in] hDevice A \ref OpenDev "device handle" identifying the generator.
 * \return The output impedance in Ohm.
 * \par Status values
 *   <table class="params">
 *   <tr><td>\ref LIBTIEPIESTATUS_NOT_SUPPORTED "NOT_SUPPORTED"</td>          <td>The generator does not support getting the output impedance.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_HANDLE "INVALID_HANDLE"</td>         <td>The handle is not a valid generator handle.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_OBJECT_GONE "OBJECT_GONE"</td>            <td>The object indicated by the handle is no longer available.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_LIBRARY_NOT_INITIALIZED "LIBRARY_NOT_INITIALIZED"</td><td>The library is not initialized, see LibInit().</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_SUCCESS "SUCCESS"</td>                <td>The function executed successfully.</td></tr>
 *   </table>
 * \since 0.4.0
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef double(*LibTiePieGenGetImpedance_t)( LibTiePieHandle_t hDevice );
#else
double GenGetImpedance( LibTiePieHandle_t hDevice );
#endif

/**
 * \brief Get the DAC resolution of a specified generator.
 *
 * \param[in] hDevice A \ref OpenDev "device handle" identifying the generator.
 * \return The resolution in bits.
 * \par Status values
 *   <table class="params">
 *   <tr><td>\ref LIBTIEPIESTATUS_NOT_SUPPORTED "NOT_SUPPORTED"</td>          <td>The generator does not support getting the resolution.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_HANDLE "INVALID_HANDLE"</td>         <td>The handle is not a valid generator handle.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_OBJECT_GONE "OBJECT_GONE"</td>            <td>The object indicated by the handle is no longer available.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_LIBRARY_NOT_INITIALIZED "LIBRARY_NOT_INITIALIZED"</td><td>The library is not initialized, see LibInit().</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_SUCCESS "SUCCESS"</td>                <td>The function executed successfully.</td></tr>
 *   </table>
 * \since 0.4.1
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef uint8_t(*LibTiePieGenGetResolution_t)( LibTiePieHandle_t hDevice );
#else
uint8_t GenGetResolution( LibTiePieHandle_t hDevice );
#endif

/**
 * \brief Get the minimum output value of a specified generator.
 *
 * \param[in] hDevice A \ref OpenDev "device handle" identifying the generator.
 * \return The minimum output value in Volt.
 * \par Status values
 *   <table class="params">
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_HANDLE "INVALID_HANDLE"</td>         <td>The handle is not a valid generator handle.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_OBJECT_GONE "OBJECT_GONE"</td>            <td>The object indicated by the handle is no longer available.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_LIBRARY_NOT_INITIALIZED "LIBRARY_NOT_INITIALIZED"</td><td>The library is not initialized, see LibInit().</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_SUCCESS "SUCCESS"</td>                <td>The function executed successfully.</td></tr>
 *   </table>
 * \see GenGetOutputValueMax
 * \since 0.4.5
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef double(*LibTiePieGenGetOutputValueMin_t)( LibTiePieHandle_t hDevice );
#else
double GenGetOutputValueMin( LibTiePieHandle_t hDevice );
#endif

/**
 * \brief Get the maximum output value of a specified generator.
 *
 * \param[in] hDevice A \ref OpenDev "device handle" identifying the generator.
 * \return The maximum output value in Volt.
 * \par Status values
 *   <table class="params">
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_HANDLE "INVALID_HANDLE"</td>         <td>The handle is not a valid generator handle.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_OBJECT_GONE "OBJECT_GONE"</td>            <td>The object indicated by the handle is no longer available.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_LIBRARY_NOT_INITIALIZED "LIBRARY_NOT_INITIALIZED"</td><td>The library is not initialized, see LibInit().</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_SUCCESS "SUCCESS"</td>                <td>The function executed successfully.</td></tr>
 *   </table>
 * \see GenGetOutputValueMin
 * \since 0.4.5
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef double(*LibTiePieGenGetOutputValueMax_t)( LibTiePieHandle_t hDevice );
#else
double GenGetOutputValueMax( LibTiePieHandle_t hDevice );
#endif

//! \cond EXTENDED_API

/**
 * \brief Get the minimum and/or maximum output value of a specified generator.
 *
 * \param[in] hDevice A \ref OpenDev "device handle" identifying the generator.
 * \param[out] pMin A pointer to a memory location for the minimum value, or \c NULL.
 * \param[out] pMax A pointer to a memory location for the maximum value, or \c NULL.
 * \par Status values
 *   <table class="params">
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_HANDLE "INVALID_HANDLE"</td>         <td>The handle is not a valid generator handle.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_OBJECT_GONE "OBJECT_GONE"</td>            <td>The object indicated by the handle is no longer available.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_LIBRARY_NOT_INITIALIZED "LIBRARY_NOT_INITIALIZED"</td><td>The library is not initialized, see LibInit().</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_SUCCESS "SUCCESS"</td>                <td>The function executed successfully.</td></tr>
 *   </table>
 * \since 0.4.5
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef void(*LibTiePieGenGetOutputValueMinMax_t)( LibTiePieHandle_t hDevice , double* pMin , double* pMax );
#else
void GenGetOutputValueMinMax( LibTiePieHandle_t hDevice , double* pMin , double* pMax );
#endif

//! \endcond

/**
 * \}
 * \defgroup gen_control Control
 * \{
 * \brief Functions for starting and stopping the generator and checking its status.
 *
 *         In certain conditions, like when performing a streaming measurement with the oscilloscope, the generator cannot be controlled.
 *         Use GenIsControllable() to poll if the generator can be controlled or use a \ref gen_notifications_controllableChanged "notification".
 *
 *         Use GenGetStatus() to check the signal generation status.
 *
 *         Before a generator can be used, the hardware must be switched on (enabled) using GenSetOutputOn().
 *         When enabeld, the generator signal properties can be set.
 *         When the generator hardware is enabled, but the generator is not started, the output will be at the currently set \ref gen_signalOffset.
 *         When the generator hardware is disabled, the hardware is switched off, resulting in the instrument using less power.
 *
 *         Output invert is not available for all instruments.
 *         Use GenHasOutputInvert() to check whether output invert is available for your instrument.
 */

// Workaround: Without this line Doxygen adds the documentation below to the group above.

/**
 * \brief Check whether a specified generator can be controlled.
 *
 * In certain conditions like when performing a streaming measurement with the oscilloscope, the generator cannot be controlled.
 *
 * \param[in] hDevice A \ref OpenDev "device handle" identifying the generator.
 * \return #BOOL8_TRUE if the generator is controllable, #BOOL8_FALSE otherwise.
 * \par Status values
 *   <table class="params">
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_HANDLE "INVALID_HANDLE"</td>         <td>The handle is not a valid generator handle.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_OBJECT_GONE "OBJECT_GONE"</td>            <td>The object indicated by the handle is no longer available.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_LIBRARY_NOT_INITIALIZED "LIBRARY_NOT_INITIALIZED"</td><td>The library is not initialized, see LibInit().</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_SUCCESS "SUCCESS"</td>                <td>The function executed successfully.</td></tr>
 *   </table>
 * \see Notification gen_notifications_controllableChanged.
 * \see \ref scp_measurements_mode "Measure mode".
 * \since 0.4.0
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef bool8_t(*LibTiePieGenIsControllable_t)( LibTiePieHandle_t hDevice );
#else
bool8_t GenIsControllable( LibTiePieHandle_t hDevice );
#endif

/**
 * \brief Check whether the generator is running.
 *
 * \param[in] hDevice A \ref OpenDev "device handle" identifying the generator.
 * \return #BOOL8_TRUE if running, #BOOL8_FALSE otherwise.
 * \since 0.6
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef bool8_t(*LibTiePieGenIsRunning_t)( LibTiePieHandle_t hDevice );
#else
bool8_t GenIsRunning( LibTiePieHandle_t hDevice );
#endif

/**
 * \brief Get the current signal generation status of a specified generator
 *
 * \param[in] hDevice A \ref OpenDev "device handle" identifying the generator.
 * \return The current signal generation status, a \ref GS_ "GS_*" value or #GSM_NONE when unsuccessful.
 * \par Status values
 *   <table class="params">
 *   <tr><td>\ref LIBTIEPIESTATUS_NOT_SUPPORTED "NOT_SUPPORTED"</td>          <td>The generator does not support getting the status.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_NOT_CONTROLLABLE "NOT_CONTROLLABLE"</td>       <td>The generator is currently not controllable, see #GenIsControllable.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_HANDLE "INVALID_HANDLE"</td>         <td>The handle is not a valid generator handle.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_OBJECT_GONE "OBJECT_GONE"</td>            <td>The object indicated by the handle is no longer available.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_LIBRARY_NOT_INITIALIZED "LIBRARY_NOT_INITIALIZED"</td><td>The library is not initialized, see LibInit().</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_SUCCESS "SUCCESS"</td>                <td>The function executed successfully.</td></tr>
 *   </table>
 * \since 0.5
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef uint32_t(*LibTiePieGenGetStatus_t)( LibTiePieHandle_t hDevice );
#else
uint32_t GenGetStatus( LibTiePieHandle_t hDevice );
#endif

/**
 * \brief Check whether a specified generator is enabled
 *
 * \param[in] hDevice A \ref OpenDev "device handle" identifying the generator.
 * \return #BOOL8_TRUE if the generator hardware is currently enabled, #BOOL8_FALSE if the generator hardware is disabled.
 * \par Status values
 *   <table class="params">
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_HANDLE "INVALID_HANDLE"</td>         <td>The handle is not a valid generator handle.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_OBJECT_GONE "OBJECT_GONE"</td>            <td>The object indicated by the handle is no longer available.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_LIBRARY_NOT_INITIALIZED "LIBRARY_NOT_INITIALIZED"</td><td>The library is not initialized, see LibInit().</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_SUCCESS "SUCCESS"</td>                <td>The function executed successfully.</td></tr>
 *   </table>
 * \see GenSetOutputOn
 * \since 0.4.0
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef bool8_t(*LibTiePieGenGetOutputOn_t)( LibTiePieHandle_t hDevice );
#else
bool8_t GenGetOutputOn( LibTiePieHandle_t hDevice );
#endif

/**
 * \brief Enable or disable the hardware of a specified generator.
 *
 * \param[in] hDevice A \ref OpenDev "device handle" identifying the generator.
 * \param[in] bOutputOn The requested hardware state, #BOOL8_TRUE to enable the hardware, #BOOL8_FALSE to disable the hardware.
 * \return The actually set hardware state, #BOOL8_TRUE if the hardware is enabled, #BOOL8_FALSE if the hardware is disabled.
 * \par Status values
 *   <table class="params">
 *   <tr><td>\ref LIBTIEPIESTATUS_NOT_CONTROLLABLE "NOT_CONTROLLABLE"</td>       <td>The generator is currently not controllable, see #GenIsControllable.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_UNSUCCESSFUL "UNSUCCESSFUL"</td>           <td>An error occurred during execution of the last called function.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_HANDLE "INVALID_HANDLE"</td>         <td>The handle is not a valid generator handle.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_OBJECT_GONE "OBJECT_GONE"</td>            <td>The object indicated by the handle is no longer available.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_LIBRARY_NOT_INITIALIZED "LIBRARY_NOT_INITIALIZED"</td><td>The library is not initialized, see LibInit().</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_SUCCESS "SUCCESS"</td>                <td>The function executed successfully.</td></tr>
 *   </table>
 * \see GenGetOutputOn
 * \since 0.4.0
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef bool8_t(*LibTiePieGenSetOutputOn_t)( LibTiePieHandle_t hDevice , bool8_t bOutputOn );
#else
bool8_t GenSetOutputOn( LibTiePieHandle_t hDevice , bool8_t bOutputOn );
#endif

/**
 * \brief Check whether the output of a specified generator can be inverted
 *
 * \param[in] hDevice A \ref OpenDev "device handle" identifying the generator.
 * \return #BOOL8_TRUE if the output can be inverted, #BOOL8_FALSE if not.
 * \par Status values
 *   <table class="params">
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_HANDLE "INVALID_HANDLE"</td>         <td>The handle is not a valid generator handle.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_OBJECT_GONE "OBJECT_GONE"</td>            <td>The object indicated by the handle is no longer available.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_LIBRARY_NOT_INITIALIZED "LIBRARY_NOT_INITIALIZED"</td><td>The library is not initialized, see LibInit().</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_SUCCESS "SUCCESS"</td>                <td>The function executed successfully.</td></tr>
 *   </table>
 * \see GenGetOutputInvert
 * \see GenSetOutputInvert
 * \since 0.6
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef bool8_t(*LibTiePieGenHasOutputInvert_t)( LibTiePieHandle_t hDevice );
#else
bool8_t GenHasOutputInvert( LibTiePieHandle_t hDevice );
#endif

/**
 * \brief Check whether the output of a specified generator is inverted
 *
 * \param[in] hDevice A \ref OpenDev "device handle" identifying the generator.
 * \return #BOOL8_TRUE if the output is currently inverted, #BOOL8_FALSE if the output is normal.
 * \par Status values
 *   <table class="params">
 *   <tr><td>\ref LIBTIEPIESTATUS_NOT_SUPPORTED "NOT_SUPPORTED"</td>          <td>The requested functionality is not supported by the hardware.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_HANDLE "INVALID_HANDLE"</td>         <td>The handle is not a valid generator handle.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_OBJECT_GONE "OBJECT_GONE"</td>            <td>The object indicated by the handle is no longer available.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_LIBRARY_NOT_INITIALIZED "LIBRARY_NOT_INITIALIZED"</td><td>The library is not initialized, see LibInit().</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_SUCCESS "SUCCESS"</td>                <td>The function executed successfully.</td></tr>
 *   </table>
 * \see GenHasOutputInvert
 * \see GenSetOutputInvert
 * \since 0.5
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef bool8_t(*LibTiePieGenGetOutputInvert_t)( LibTiePieHandle_t hDevice );
#else
bool8_t GenGetOutputInvert( LibTiePieHandle_t hDevice );
#endif

/**
 * \brief Enable or disable the output invert of a specified generator.
 *
 * \param[in] hDevice A \ref OpenDev "device handle" identifying the generator.
 * \param[in] bInvert The requested output state, #BOOL8_TRUE to invert the output, #BOOL8_FALSE to disable the output invert.
 * \return The actually set output state, #BOOL8_TRUE if the output is inverted, #BOOL8_FALSE if the output is normal.
 * \par Status values
 *   <table class="params">
 *   <tr><td>\ref LIBTIEPIESTATUS_NOT_CONTROLLABLE "NOT_CONTROLLABLE"</td>       <td>The generator is currently not controllable, see #GenIsControllable.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_UNSUCCESSFUL "UNSUCCESSFUL"</td>           <td>An error occurred during execution of the last called function.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_NOT_SUPPORTED "NOT_SUPPORTED"</td>          <td>The requested functionality is not supported by the hardware.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_HANDLE "INVALID_HANDLE"</td>         <td>The handle is not a valid generator handle.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_OBJECT_GONE "OBJECT_GONE"</td>            <td>The object indicated by the handle is no longer available.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_LIBRARY_NOT_INITIALIZED "LIBRARY_NOT_INITIALIZED"</td><td>The library is not initialized, see LibInit().</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_SUCCESS "SUCCESS"</td>                <td>The function executed successfully.</td></tr>
 *   </table>
 * \see GenHasOutputInvert
 * \see GenGetOutputInvert
 * \since 0.5
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef bool8_t(*LibTiePieGenSetOutputInvert_t)( LibTiePieHandle_t hDevice , bool8_t bInvert );
#else
bool8_t GenSetOutputInvert( LibTiePieHandle_t hDevice , bool8_t bInvert );
#endif

/**
 * \brief Start the signal generation of a specified generator.
 *
 * \param[in] hDevice A \ref OpenDev "device handle" identifying the generator.
 * \return #BOOL8_TRUE if succesful, #BOOL8_FALSE if failed.
 * \par Status values
 *   <table class="params">
 *   <tr><td>\ref LIBTIEPIESTATUS_NO_TRIGGER_ENABLED "NO_TRIGGER_ENABLED"</td>     <td>The current setup requires a trigger input to be enabled.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_NOT_CONTROLLABLE "NOT_CONTROLLABLE"</td>       <td>The generator is currently not controllable, see #GenIsControllable.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_UNSUCCESSFUL "UNSUCCESSFUL"</td>           <td>An error occurred during execution of the last called function.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_HANDLE "INVALID_HANDLE"</td>         <td>The handle is not a valid generator handle.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_OBJECT_GONE "OBJECT_GONE"</td>            <td>The object indicated by the handle is no longer available.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_LIBRARY_NOT_INITIALIZED "LIBRARY_NOT_INITIALIZED"</td><td>The library is not initialized, see LibInit().</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_SUCCESS "SUCCESS"</td>                <td>The function executed successfully.</td></tr>
 *   </table>
 * \see GenStop
 * \since 0.5
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef bool8_t(*LibTiePieGenStart_t)( LibTiePieHandle_t hDevice );
#else
bool8_t GenStart( LibTiePieHandle_t hDevice );
#endif

/**
 * \brief Stop the signal generation of a specified generator.
 *
 * \param[in] hDevice A \ref OpenDev "device handle" identifying the generator.
 * \return #BOOL8_TRUE if succesful, #BOOL8_FALSE if failed.
 * \par Status values
 *   <table class="params">
 *   <tr><td>\ref LIBTIEPIESTATUS_NOT_CONTROLLABLE "NOT_CONTROLLABLE"</td>       <td>The generator is currently not controllable, see #GenIsControllable.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_UNSUCCESSFUL "UNSUCCESSFUL"</td>           <td>An error occurred during execution of the last called function.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_HANDLE "INVALID_HANDLE"</td>         <td>The handle is not a valid generator handle.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_OBJECT_GONE "OBJECT_GONE"</td>            <td>The object indicated by the handle is no longer available.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_LIBRARY_NOT_INITIALIZED "LIBRARY_NOT_INITIALIZED"</td><td>The library is not initialized, see LibInit().</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_SUCCESS "SUCCESS"</td>                <td>The function executed successfully.</td></tr>
 *   </table>
 * \see GenStart
 * \since 0.5
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef bool8_t(*LibTiePieGenStop_t)( LibTiePieHandle_t hDevice );
#else
bool8_t GenStop( LibTiePieHandle_t hDevice );
#endif

/**
 * \}
 * \defgroup gen_signal Signal
 * \{
 * \brief Functions to control the signal properties of a generator.
 *
 *         The generator supports several standard signal types.
 *         Depending on the signal type that is set, other properties of the generator are available:
 *
 *         <table>
 *           <tr>                    <th>\ref gen_signalType</th><th>\ref gen_signalAmplitude</th><th>\ref gen_signalOffset</th><th>\ref gen_signalFrequency</th><th>\ref gen_signalPhase</th><th>\ref gen_signalSymmetry</th><th>\ref gen_signalWidth</th><th>\ref gen_signalEdgeTime</th><th>\ref gen_signalData "Data"</th></tr>
 *           <tr class="SignalTypes"><th>Sine               </th><td>yes                     </td><td>yes                  </td><td>yes                     </td><td>yes                 </td><td>yes                    </td><td>-                   </td><td>-                      </td><td>-                         </td></tr>
 *           <tr class="SignalTypes"><th>Triangle           </th><td>yes                     </td><td>yes                  </td><td>yes                     </td><td>yes                 </td><td>yes                    </td><td>-                   </td><td>-                      </td><td>-                         </td></tr>
 *           <tr class="SignalTypes"><th>Square             </th><td>yes                     </td><td>yes                  </td><td>yes                     </td><td>yes                 </td><td>yes                    </td><td>-                   </td><td>-                      </td><td>-                         </td></tr>
 *           <tr class="SignalTypes"><th>Pulse              </th><td>yes                     </td><td>yes                  </td><td>yes                     </td><td>yes                 </td><td>-                      </td><td>yes                 </td><td>yes                    </td><td>-                         </td></tr>
 *           <tr class="SignalTypes"><th>DC                 </th><td>-                       </td><td>yes                  </td><td>-                       </td><td>-                   </td><td>-                      </td><td>-                   </td><td>-                      </td><td>-                         </td></tr>
 *           <tr class="SignalTypes"><th>Noise              </th><td>yes                     </td><td>yes                  </td><td>yes                     </td><td>-                   </td><td>-                      </td><td>-                   </td><td>-                      </td><td>-                         </td></tr>
 *           <tr class="SignalTypes"><th>Arbitrary          </th><td>yes                     </td><td>yes                  </td><td>yes                     </td><td>yes                 </td><td>-                      </td><td>-                   </td><td>-                      </td><td>yes                       </td></tr>
 *         </table>
 *
 * \defgroup gen_signalType Signal type
 * \{
 * \brief Functions for controlling the signal type of a generator.
 *
 *           The generator supports several standard signal types.
 *           Use GenGetSignalTypes() to find the supported signal types.
 *
 *           By default signal type is set to: Sine (#ST_SINE).
 */

// Workaround: Without this line Doxygen adds the documentation below to the group above.

/**
 * \brief Get the supported signal types of a specified generator.
 *
 * \param[in] hDevice A \ref OpenDev "device handle" identifying the generator.
 * \return The supported signal types, a set of \ref ST_ "ST_*" values, #STM_NONE when unsuccessful.
 * \par Status values
 *   <table class="params">
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_HANDLE "INVALID_HANDLE"</td>         <td>The handle is not a valid generator handle.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_OBJECT_GONE "OBJECT_GONE"</td>            <td>The object indicated by the handle is no longer available.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_LIBRARY_NOT_INITIALIZED "LIBRARY_NOT_INITIALIZED"</td><td>The library is not initialized, see LibInit().</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_SUCCESS "SUCCESS"</td>                <td>The function executed successfully.</td></tr>
 *   </table>
 * \see GenGetSignalType
 * \see GenSetSignalType
 * \since 0.4.0
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef uint32_t(*LibTiePieGenGetSignalTypes_t)( LibTiePieHandle_t hDevice );
#else
uint32_t GenGetSignalTypes( LibTiePieHandle_t hDevice );
#endif

/**
 * \brief Get the currently selected signal type of a specified generator.
 *
 * \param[in] hDevice A \ref OpenDev "device handle" identifying the generator.
 * \return The currently set signal type, a \ref ST_ "ST_*" value, #ST_UNKNOWN when unsuccessful.
 * \par Status values
 *   <table class="params">
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_HANDLE "INVALID_HANDLE"</td>         <td>The handle is not a valid generator handle.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_OBJECT_GONE "OBJECT_GONE"</td>            <td>The object indicated by the handle is no longer available.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_LIBRARY_NOT_INITIALIZED "LIBRARY_NOT_INITIALIZED"</td><td>The library is not initialized, see LibInit().</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_SUCCESS "SUCCESS"</td>                <td>The function executed successfully.</td></tr>
 *   </table>
 * \see GenGetSignalTypes
 * \see GenSetSignalType
 * \since 0.4.0
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef uint32_t(*LibTiePieGenGetSignalType_t)( LibTiePieHandle_t hDevice );
#else
uint32_t GenGetSignalType( LibTiePieHandle_t hDevice );
#endif

/**
 * \brief Set the signal type of a specified generator.
 *
 * \param[in] hDevice A \ref OpenDev "device handle" identifying the generator.
 * \param[in] dwSignalType The requested signal type, a \ref ST_ "ST_*" value.
 * \return The actually set signal type, a \ref ST_ "ST_*" value, #ST_UNKNOWN when unsuccessful.
 * \par Status values
 *   <table class="params">
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_VALUE "INVALID_VALUE"</td>          <td>The requested signal type is invalid.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_NOT_CONTROLLABLE "NOT_CONTROLLABLE"</td>       <td>The generator is currently not controllable, see #GenIsControllable.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_HANDLE "INVALID_HANDLE"</td>         <td>The handle is not a valid generator handle.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_OBJECT_GONE "OBJECT_GONE"</td>            <td>The object indicated by the handle is no longer available.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_LIBRARY_NOT_INITIALIZED "LIBRARY_NOT_INITIALIZED"</td><td>The library is not initialized, see LibInit().</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_SUCCESS "SUCCESS"</td>                <td>The function executed successfully.</td></tr>
 *   </table>
 * \remark When the generator is active, changing the signal type may shortly interrupt the output signal.
 * \remark Changing the signal type can affect the \ref GenSetFrequencyMode "frequency mode", \ref GenSetMode "generator mode" and/or \ref gen_signalOffset "offset".
 * \remark Setting certain signal types will make other generator properties unavailable.
 * \see GenGetSignalTypes
 * \see GenGetSignalType
 * \since 0.4.0
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef uint32_t(*LibTiePieGenSetSignalType_t)( LibTiePieHandle_t hDevice , uint32_t dwSignalType );
#else
uint32_t GenSetSignalType( LibTiePieHandle_t hDevice , uint32_t dwSignalType );
#endif

/**
 * \}
 * \defgroup gen_signalAmplitude Amplitude
 * \{
 * \brief Functions for controlling the amplitude and amplitude range of a generator.
 *
 *           The amplitude of a generator can be set between a minimum and a maximum value.
 *           Use GenGetAmplitudeMin() and GenGetAmplitudeMax() to get the amplitude limits.
 *
 *           Amplitude and \ref gen_signalOffset combined cannot exceed the \ref GenGetOutputValueMin "minimum" and
 * \ref GenGetOutputValueMax "maximum" output value of the generator.
 *           Setting a larger amplitude will clip the amplitude to a valid value.
 *
 *           A generator has one or more output ranges, use GenSetAmplitudeRange() to set the required range or \ref GenSetAmplitudeAutoRanging
 *           to enable amplitude auto ranging.
 *
 *           By default the amplitude is set to: 1 V and auto ranging is enabled (#BOOL8_TRUE).
 *
 *           When \ref gen_signalType "signal type" DC is active, amplitude is not available.
 *           Use GenHasAmplitude() to check whether amplitude is available for the currently set signal type.
 */

// Workaround: Without this line Doxygen adds the documentation below to the group above.

/**
 * \brief Check whether the current signal type of a specified generator supports controlling the signal amplitude.
 *
 * \param[in] hDevice A \ref OpenDev "device handle" identifying the generator.
 * \return #BOOL8_TRUE if supported, #BOOL8_FALSE if not.
 * \par Status values
 *   <table class="params">
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_HANDLE "INVALID_HANDLE"</td>         <td>The handle is not a valid generator handle.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_OBJECT_GONE "OBJECT_GONE"</td>            <td>The object indicated by the handle is no longer available.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_LIBRARY_NOT_INITIALIZED "LIBRARY_NOT_INITIALIZED"</td><td>The library is not initialized, see LibInit().</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_SUCCESS "SUCCESS"</td>                <td>The function executed successfully.</td></tr>
 *   </table>
 * \see GenGetAmplitudeMin
 * \see GenGetAmplitudeMax
 * \see GenGetAmplitude
 * \see GenSetAmplitude
 * \since 0.6
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef bool8_t(*LibTiePieGenHasAmplitude_t)( LibTiePieHandle_t hDevice );
#else
bool8_t GenHasAmplitude( LibTiePieHandle_t hDevice );
#endif

//! \cond EXTENDED_API

/**
 * \brief Check whether the specified generator supports controlling the signal amplitude for a specified signal type.
 *
 * \param[in] hDevice A \ref OpenDev "device handle" identifying the generator.
 * \param[in] dwSignalType The requested signal type, a \ref ST_ "ST_*" value.
 * \return #BOOL8_TRUE if supported, #BOOL8_FALSE if not.
 * \par Status values
 *   <table class="params">
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_VALUE "INVALID_VALUE"</td>          <td>The requested signal type is invalid.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_HANDLE "INVALID_HANDLE"</td>         <td>The handle is not a valid generator handle.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_OBJECT_GONE "OBJECT_GONE"</td>            <td>The object indicated by the handle is no longer available.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_LIBRARY_NOT_INITIALIZED "LIBRARY_NOT_INITIALIZED"</td><td>The library is not initialized, see LibInit().</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_SUCCESS "SUCCESS"</td>                <td>The function executed successfully.</td></tr>
 *   </table>
 * \since 0.6
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef bool8_t(*LibTiePieGenHasAmplitudeEx_t)( LibTiePieHandle_t hDevice , uint32_t dwSignalType );
#else
bool8_t GenHasAmplitudeEx( LibTiePieHandle_t hDevice , uint32_t dwSignalType );
#endif

//! \endcond

/**
 * \brief Get the minimum signal amplitude for the current signal type of a specified generator.
 *
 *  When \ref GenSetAmplitudeAutoRanging "amplitude auto ranging" is enabled, the minimum value of all amplitude ranges is returned.
 *  When amplitude auto ranging is disabled, the minimum value for the currently set amplitude range is returned.
 *
 * \param[in] hDevice A \ref OpenDev "device handle" identifying the generator.
 * \return The minimum signal amplitude in Volt.
 * \par Status values
 *   <table class="params">
 *   <tr><td>\ref LIBTIEPIESTATUS_NOT_SUPPORTED "NOT_SUPPORTED"</td>          <td>The current signal type does not support signal amplitude.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_HANDLE "INVALID_HANDLE"</td>         <td>The handle is not a valid generator handle.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_OBJECT_GONE "OBJECT_GONE"</td>            <td>The object indicated by the handle is no longer available.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_LIBRARY_NOT_INITIALIZED "LIBRARY_NOT_INITIALIZED"</td><td>The library is not initialized, see LibInit().</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_SUCCESS "SUCCESS"</td>                <td>The function executed successfully.</td></tr>
 *   </table>
 * \see GenGetAmplitudeMax
 * \see GenGetAmplitude
 * \see GenSetAmplitude
 * \since 0.4.0
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef double(*LibTiePieGenGetAmplitudeMin_t)( LibTiePieHandle_t hDevice );
#else
double GenGetAmplitudeMin( LibTiePieHandle_t hDevice );
#endif

/**
 * \brief Get the maximum signal amplitude for the current signal type of a specified generator.
 *
 *  When \ref GenSetAmplitudeAutoRanging "amplitude auto ranging" is enabled, the maximum value for the highest amplitude range is returned.
 *  When amplitude auto ranging is disabled, the maximum value for the currently set amplitude range is returned.
 *
 * \param[in] hDevice A \ref OpenDev "device handle" identifying the generator.
 * \return The maximum signal amplitude in Volt.
 * \par Status values
 *   <table class="params">
 *   <tr><td>\ref LIBTIEPIESTATUS_NOT_SUPPORTED "NOT_SUPPORTED"</td>          <td>The current signal type does not support signal amplitude.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_HANDLE "INVALID_HANDLE"</td>         <td>The handle is not a valid generator handle.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_OBJECT_GONE "OBJECT_GONE"</td>            <td>The object indicated by the handle is no longer available.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_LIBRARY_NOT_INITIALIZED "LIBRARY_NOT_INITIALIZED"</td><td>The library is not initialized, see LibInit().</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_SUCCESS "SUCCESS"</td>                <td>The function executed successfully.</td></tr>
 *   </table>
 * \see GenGetAmplitudeMin
 * \see GenGetAmplitude
 * \see GenSetAmplitude
 * \since 0.4.0
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef double(*LibTiePieGenGetAmplitudeMax_t)( LibTiePieHandle_t hDevice );
#else
double GenGetAmplitudeMax( LibTiePieHandle_t hDevice );
#endif

//! \cond EXTENDED_API

/**
 * \brief Get the minimum and/or maximum amplitude for a specified signal type, of a specified generator.
 *
 *  When \ref GenSetAmplitudeAutoRanging "amplitude auto ranging" is enabled, the minimum and maximum values for the highest amplitude range
 *  are returned.
 *  When amplitude auto ranging is disabled, the minimum and maximum values for the currently set amplitude range
 *  are returned.
 *
 * \param[in] hDevice A \ref OpenDev "device handle" identifying the generator.
 * \param[in] dwSignalType The requested signal type, a \ref ST_ "ST_*" value.
 * \param[out] pMin A pointer to a memory location for the minimum amplitude in Volt, or \c NULL.
 * \param[out] pMax A pointer to a memory location for the maximum amplitude in Volt, or \c NULL.
 * \par Status values
 *   <table class="params">
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_VALUE "INVALID_VALUE"</td>          <td>The requested signal type is invalid.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_NOT_SUPPORTED "NOT_SUPPORTED"</td>          <td>The requested signal type does not support signal amplitude.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_HANDLE "INVALID_HANDLE"</td>         <td>The handle is not a valid generator handle.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_OBJECT_GONE "OBJECT_GONE"</td>            <td>The object indicated by the handle is no longer available.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_LIBRARY_NOT_INITIALIZED "LIBRARY_NOT_INITIALIZED"</td><td>The library is not initialized, see LibInit().</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_SUCCESS "SUCCESS"</td>                <td>The function executed successfully.</td></tr>
 *   </table>
 * \see GenGetAmplitudeMax
 * \see GenGetAmplitude
 * \see GenSetAmplitude
 * \since 0.4.3
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef void(*LibTiePieGenGetAmplitudeMinMaxEx_t)( LibTiePieHandle_t hDevice , uint32_t dwSignalType , double* pMin , double* pMax );
#else
void GenGetAmplitudeMinMaxEx( LibTiePieHandle_t hDevice , uint32_t dwSignalType , double* pMin , double* pMax );
#endif

//! \endcond

/**
 * \brief Get the currently set signal amplitude of a specified generator.
 *
 * \param[in] hDevice A \ref OpenDev "device handle" identifying the generator.
 * \return The currently set signal amplitude in Volt.
 * \par Status values
 *   <table class="params">
 *   <tr><td>\ref LIBTIEPIESTATUS_NOT_SUPPORTED "NOT_SUPPORTED"</td>          <td>The current signal type does not support signal amplitude.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_HANDLE "INVALID_HANDLE"</td>         <td>The handle is not a valid generator handle.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_OBJECT_GONE "OBJECT_GONE"</td>            <td>The object indicated by the handle is no longer available.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_LIBRARY_NOT_INITIALIZED "LIBRARY_NOT_INITIALIZED"</td><td>The library is not initialized, see LibInit().</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_SUCCESS "SUCCESS"</td>                <td>The function executed successfully.</td></tr>
 *   </table>
 * \see GenGetAmplitudeMin
 * \see GenGetAmplitudeMax
 * \see GenSetAmplitude
 * \since 0.4.0
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef double(*LibTiePieGenGetAmplitude_t)( LibTiePieHandle_t hDevice );
#else
double GenGetAmplitude( LibTiePieHandle_t hDevice );
#endif

/**
 * \brief Set the signal amplitude of a specified generator.
 *
 * \param[in] hDevice A \ref OpenDev "device handle" identifying the generator.
 * \param[in] dAmplitude The requested signal amplitude.
 * \return The actually set signal amplitude.
 * \par Status values
 *   <table class="params">
 *   <tr><td>\ref LIBTIEPIESTATUS_VALUE_CLIPPED "VALUE_CLIPPED"</td>          <td>The requested amplitude is outside the valid range and clipped to the closest limit.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_VALUE_MODIFIED "VALUE_MODIFIED"</td>         <td>The requested amplitude is within the valid range but not available. The closest valid value is set.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_VALUE "INVALID_VALUE"</td>          <td>The requested amplitude is &lt; \c 0.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_NOT_SUPPORTED "NOT_SUPPORTED"</td>          <td>The current signal type does not support signal amplitude.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_NOT_CONTROLLABLE "NOT_CONTROLLABLE"</td>       <td>The generator is currently not controllable, see #GenIsControllable.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_HANDLE "INVALID_HANDLE"</td>         <td>The handle is not a valid generator handle.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_OBJECT_GONE "OBJECT_GONE"</td>            <td>The object indicated by the handle is no longer available.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_LIBRARY_NOT_INITIALIZED "LIBRARY_NOT_INITIALIZED"</td><td>The library is not initialized, see LibInit().</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_SUCCESS "SUCCESS"</td>                <td>The function executed successfully.</td></tr>
 *   </table>
 * \remark Setting the amplitude may change the amplitude range when \ref GenSetAmplitudeAutoRanging "amplitude auto ranging" is enabled.
 * \remark Setting the amplitude may cause a new waveform pattern to be uploaded when \ref gen_signalType "signal type" Square wave is active, shortly interrupting the output signal.
 * \see GenGetAmplitudeMin
 * \see GenGetAmplitudeMax
 * \see GenGetAmplitude
 * \since 0.4.0
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef double(*LibTiePieGenSetAmplitude_t)( LibTiePieHandle_t hDevice , double dAmplitude );
#else
double GenSetAmplitude( LibTiePieHandle_t hDevice , double dAmplitude );
#endif

//! \cond EXTENDED_API

/**
 * \brief Verify if a signal amplitude can be set, of a specified generator, without actually setting the hardware itself.
 *
 * \param[in] hDevice A \ref OpenDev "device handle" identifying the generator.
 * \param[in] dAmplitude The requested signal amplitude.
 * \return The signal amplitude that would have been set, in Volt.
 * \par Status values
 *   <table class="params">
 *   <tr><td>\ref LIBTIEPIESTATUS_VALUE_CLIPPED "VALUE_CLIPPED"</td>          <td>The requested amplitude is outside the valid range and clipped to the closest limit.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_VALUE_MODIFIED "VALUE_MODIFIED"</td>         <td>The requested amplitude is within the valid range but not available. The closest valid value is set.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_VALUE "INVALID_VALUE"</td>          <td>The requested amplitude is &lt; \c 0.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_NOT_SUPPORTED "NOT_SUPPORTED"</td>          <td>The current signal type does not support signal amplitude.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_NOT_CONTROLLABLE "NOT_CONTROLLABLE"</td>       <td>The generator is currently not controllable, see #GenIsControllable.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_HANDLE "INVALID_HANDLE"</td>         <td>The handle is not a valid generator handle.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_OBJECT_GONE "OBJECT_GONE"</td>            <td>The object indicated by the handle is no longer available.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_LIBRARY_NOT_INITIALIZED "LIBRARY_NOT_INITIALIZED"</td><td>The library is not initialized, see LibInit().</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_SUCCESS "SUCCESS"</td>                <td>The function executed successfully.</td></tr>
 *   </table>
 * \see GenGetAmplitudeMin
 * \see GenGetAmplitudeMax
 * \see GenGetAmplitudeMinMaxEx
 * \see GenGetAmplitude
 * \see GenSetAmplitude
 * \see GenVerifyAmplitudeEx
 * \since 0.4.0
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef double(*LibTiePieGenVerifyAmplitude_t)( LibTiePieHandle_t hDevice , double dAmplitude );
#else
double GenVerifyAmplitude( LibTiePieHandle_t hDevice , double dAmplitude );
#endif

/**
 * \brief Verify if a signal amplitude can be set for a specified signal type, amplitude range and offset, of a specified generator, without actually setting the hardware itself.
 *
 * \param[in] hDevice A \ref OpenDev "device handle" identifying the generator.
 * \param[in] dAmplitude The requested signal amplitude.
 * \param[in] dwSignalType The requested signal type, a \ref ST_ "ST_*" value.
 * \param[in] dwAmplitudeRangeIndex The requested output range index or \ref LIBTIEPIE_RANGEINDEX_AUTO.
 * \param[in] dOffset The requested signal offset.
 * \return The signal amplitude that would have been set, in Volt.
 * \par Status values
 *   <table class="params">
 *   <tr><td>\ref LIBTIEPIESTATUS_VALUE_CLIPPED "VALUE_CLIPPED"</td>          <td>The requested amplitude is outside the valid range and clipped to the closest limit.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_VALUE_MODIFIED "VALUE_MODIFIED"</td>         <td>The requested amplitude is within the valid range but not available. The closest valid value is set.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_VALUE "INVALID_VALUE"</td>          <td>The requested amplitude is &lt; \c 0.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_NOT_SUPPORTED "NOT_SUPPORTED"</td>          <td>The current signal type does not support signal amplitude.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_HANDLE "INVALID_HANDLE"</td>         <td>The handle is not a valid generator handle.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_OBJECT_GONE "OBJECT_GONE"</td>            <td>The object indicated by the handle is no longer available.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_LIBRARY_NOT_INITIALIZED "LIBRARY_NOT_INITIALIZED"</td><td>The library is not initialized, see LibInit().</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_SUCCESS "SUCCESS"</td>                <td>The function executed successfully.</td></tr>
 *   </table>
 * \see GenGetAmplitudeMin
 * \see GenGetAmplitudeMax
 * \see GenGetAmplitudeMinMaxEx
 * \see GenGetAmplitude
 * \see GenSetAmplitude
 * \see GenVerifyAmplitude
 * \since 0.4.3
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef double(*LibTiePieGenVerifyAmplitudeEx_t)( LibTiePieHandle_t hDevice , double dAmplitude , uint32_t dwSignalType , uint32_t dwAmplitudeRangeIndex , double dOffset );
#else
double GenVerifyAmplitudeEx( LibTiePieHandle_t hDevice , double dAmplitude , uint32_t dwSignalType , uint32_t dwAmplitudeRangeIndex , double dOffset );
#endif

//! \endcond

/**
 * \defgroup gen_signalAmplitudeRange Amplitude range
 * \{
 * \brief Functions for controlling the amplitude range of a generator.
 *
 *           A generator has one or more output ranges, use GenGetAmplitudeRanges() to get the available ranges.
 *           Within each range, the amplitude can be set in a fixed number of steps.
 *           When \ref GenSetAmplitudeAutoRanging "amplitude auto ranging" is disabled, the amplitude can only be set within the selected amplitude range.
 *           When amplitude auto ranging is enabled, selecting a certain amplitude may change the amplitude range to the most appropriate value.
 *
 *           By default the amplitude auto ranging is enabled (#BOOL8_TRUE).
 */

// Workaround: Without this line Doxygen adds the documentation below to the group above.

/**
 * \brief Get the supported amplitude ranges for a specified generator.
 *
 * \param[in] hDevice A \ref OpenDev "device handle" identifying the generator.
 * \param[out] pList A pointer to an array to hold the amplitude range values.
 * \param[in] dwLength The number of elements in the array.
 * \return The number of amplitude ranges.
 * \par Status values
 *   <table class="params">
 *   <tr><td>\ref LIBTIEPIESTATUS_NOT_SUPPORTED "NOT_SUPPORTED"</td>          <td>The current signal type does not support signal amplitude (range).</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_HANDLE "INVALID_HANDLE"</td>         <td>The handle is not a valid generator handle.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_OBJECT_GONE "OBJECT_GONE"</td>            <td>The object indicated by the handle is no longer available.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_LIBRARY_NOT_INITIALIZED "LIBRARY_NOT_INITIALIZED"</td><td>The library is not initialized, see LibInit().</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_SUCCESS "SUCCESS"</td>                <td>The function executed successfully.</td></tr>
 *   </table>
 * \par Example
 * \code{.c}
 * uint32_t dwRangeCount = GenGetAmplitudeRanges( hDevice , NULL , 0 );
 * double* pRanges = malloc( sizeof( double ) * dwRangeCount );
 * dwRangeCount = GenGetAmplitudeRanges( hDevice , pRanges , dwRangeCount );
 *
 * printf( "GenGetAmplitudeRanges:\n" );
 *
 * for( uint32_t i = 0 ; i < dwRangeCount ; i++ )
 *   printf( "- %f\n" , pRanges[ i ] );
 *
 * free( pRanges );
 * \endcode
 *
 * \see GenGetAmplitudeRange
 * \see GenSetAmplitudeRange
 * \see GenGetAmplitudeAutoRanging
 * \see GenSetAmplitudeAutoRanging
 * \since 0.4.1
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef uint32_t(*LibTiePieGenGetAmplitudeRanges_t)( LibTiePieHandle_t hDevice , double* pList , uint32_t dwLength );
#else
uint32_t GenGetAmplitudeRanges( LibTiePieHandle_t hDevice , double* pList , uint32_t dwLength );
#endif

/**
 * \brief Get the currently set amplitude range for a specified generator.
 *
 * \param[in] hDevice A \ref OpenDev "device handle" identifying the generator.
 * \return The currently set amplitude range.
 * \par Status values
 *   <table class="params">
 *   <tr><td>\ref LIBTIEPIESTATUS_NOT_SUPPORTED "NOT_SUPPORTED"</td>          <td>The current signal type does not support signal amplitude (range).</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_HANDLE "INVALID_HANDLE"</td>         <td>The handle is not a valid generator handle.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_OBJECT_GONE "OBJECT_GONE"</td>            <td>The object indicated by the handle is no longer available.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_LIBRARY_NOT_INITIALIZED "LIBRARY_NOT_INITIALIZED"</td><td>The library is not initialized, see LibInit().</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_SUCCESS "SUCCESS"</td>                <td>The function executed successfully.</td></tr>
 *   </table>
 * \see GenGetAmplitudeRanges
 * \see GenSetAmplitudeRange
 * \see GenGetAmplitudeAutoRanging
 * \see GenSetAmplitudeAutoRanging
 * \since 0.4.1
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef double(*LibTiePieGenGetAmplitudeRange_t)( LibTiePieHandle_t hDevice );
#else
double GenGetAmplitudeRange( LibTiePieHandle_t hDevice );
#endif

/**
 * \brief Set the amplitude range for a specified generator.
 *
 * \param[in] hDevice A \ref OpenDev "device handle" identifying the generator.
 * \param[in] dRange The maximum value that must fit within the requested amplitude range.
 * \return The actually set amplitude range.
 * \par Status values
 *   <table class="params">
 *   <tr><td>\ref LIBTIEPIESTATUS_VALUE_CLIPPED "VALUE_CLIPPED"</td>          <td>The requested amplitude range is outside the valid range and clipped to the closest limit.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_VALUE_MODIFIED "VALUE_MODIFIED"</td>         <td>The requested amplitude range is within the valid range but not available. The closest valid value is set.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_VALUE "INVALID_VALUE"</td>          <td>The requested amplitude range is &lt; \c 0.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_NOT_CONTROLLABLE "NOT_CONTROLLABLE"</td>       <td>The generator is currently not controllable, see #GenIsControllable.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_NOT_SUPPORTED "NOT_SUPPORTED"</td>          <td>The current signal type does not support signal amplitude (range).</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_HANDLE "INVALID_HANDLE"</td>         <td>The handle is not a valid generator handle.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_OBJECT_GONE "OBJECT_GONE"</td>            <td>The object indicated by the handle is no longer available.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_LIBRARY_NOT_INITIALIZED "LIBRARY_NOT_INITIALIZED"</td><td>The library is not initialized, see LibInit().</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_SUCCESS "SUCCESS"</td>                <td>The function executed successfully.</td></tr>
 *   </table>
 * \remark Setting the amplitude range will disable \ref GenSetAmplitudeAutoRanging "amplitude auto ranging" when enabled.
 * \remark Setting the amplitude range may affect the amplitude.
 *
 * \par Example
 * \code{.c}
 * double dRange = 10;
 *
 * dRange = GenSetAmplitudeRange( hDevice , dRange );
 *
 * printf( "GenSetAmplitudeRange = %f" , dRange );
 * \endcode
 *
 * \see GenGetAmplitudeRanges
 * \see GenGetAmplitudeRange
 * \see GenGetAmplitudeAutoRanging
 * \see GenSetAmplitudeAutoRanging
 * \since 0.4.1
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef double(*LibTiePieGenSetAmplitudeRange_t)( LibTiePieHandle_t hDevice , double dRange );
#else
double GenSetAmplitudeRange( LibTiePieHandle_t hDevice , double dRange );
#endif

/**
 * \brief Get the amplitude auto ranging setting for a specified generator.
 *
 * \param[in] hDevice A \ref OpenDev "device handle" identifying the generator.
 * \return The currently set amplitude auto ranging setting: #BOOL8_TRUE if enabled, #BOOL8_FALSE if disabled.
 * \par Status values
 *   <table class="params">
 *   <tr><td>\ref LIBTIEPIESTATUS_NOT_SUPPORTED "NOT_SUPPORTED"</td>          <td>The current signal type does not support signal amplitude (range).</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_HANDLE "INVALID_HANDLE"</td>         <td>The handle is not a valid generator handle.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_OBJECT_GONE "OBJECT_GONE"</td>            <td>The object indicated by the handle is no longer available.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_LIBRARY_NOT_INITIALIZED "LIBRARY_NOT_INITIALIZED"</td><td>The library is not initialized, see LibInit().</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_SUCCESS "SUCCESS"</td>                <td>The function executed successfully.</td></tr>
 *   </table>
 * \see GenGetAmplitudeRanges
 * \see GenGetAmplitudeRange
 * \see GenSetAmplitudeRange
 * \see GenSetAmplitudeAutoRanging
 * \since 0.4.1
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef bool8_t(*LibTiePieGenGetAmplitudeAutoRanging_t)( LibTiePieHandle_t hDevice );
#else
bool8_t GenGetAmplitudeAutoRanging( LibTiePieHandle_t hDevice );
#endif

/**
 * \brief Set the amplitude auto ranging setting for a specified generator.
 *
 * \param[in] hDevice A \ref OpenDev "device handle" identifying the generator.
 * \param[in] bEnable The required amplitude auto ranging setting: #BOOL8_TRUE to enable or #BOOL8_FALSE to disable.
 * \return The actually set amplitude auto ranging setting: #BOOL8_TRUE if enabled, #BOOL8_FALSE if disabled.
 * \par Status values
 *   <table class="params">
 *   <tr><td>\ref LIBTIEPIESTATUS_NOT_CONTROLLABLE "NOT_CONTROLLABLE"</td>       <td>The generator is currently not controllable, see #GenIsControllable.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_NOT_SUPPORTED "NOT_SUPPORTED"</td>          <td>The current signal type does not support signal amplitude (range).</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_HANDLE "INVALID_HANDLE"</td>         <td>The handle is not a valid generator handle.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_OBJECT_GONE "OBJECT_GONE"</td>            <td>The object indicated by the handle is no longer available.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_LIBRARY_NOT_INITIALIZED "LIBRARY_NOT_INITIALIZED"</td><td>The library is not initialized, see LibInit().</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_SUCCESS "SUCCESS"</td>                <td>The function executed successfully.</td></tr>
 *   </table>
 * \remark Setting amplitude auto ranging may affect the amplitude range.
 * \see GenGetAmplitudeRanges
 * \see GenGetAmplitudeRange
 * \see GenSetAmplitudeRange
 * \see GenGetAmplitudeAutoRanging
 * \since 0.4.1
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef bool8_t(*LibTiePieGenSetAmplitudeAutoRanging_t)( LibTiePieHandle_t hDevice , bool8_t bEnable );
#else
bool8_t GenSetAmplitudeAutoRanging( LibTiePieHandle_t hDevice , bool8_t bEnable );
#endif

/**
 * \}
 * \}
 * \defgroup gen_signalOffset Offset
 * \{
 * \brief Functions for controlling the offset of a generator.
 *
 *           The offset of a generator can be set between a minimum and a maximum value.
 *           Use GenGetOffsetMin() and GenGetOffsetMax() to get the offset limits.
 *
 * \ref gen_signalAmplitude and Offset combined cannot exceed the \ref GenGetOutputValueMin "minimum" and
 * \ref GenGetOutputValueMax "maximum" output value of the generator.
 *           Setting a larger offset will clip the offset to a valid value.
 *
 *           When the \ref GenGetOutputOn "generator ouput" is switched on but signal generation is \ref GenStop "stopped",
 *           the generator output will be at the currently set offset level.
 *
 *           By default the offset is set to: 0 V.
 */

// Workaround: Without this line Doxygen adds the documentation below to the group above.

/**
 * \brief Check whether the current signal type of a specified generator supports controlling the signal offset.
 *
 * \param[in] hDevice A \ref OpenDev "device handle" identifying the generator.
 * \return #BOOL8_TRUE if supported, #BOOL8_FALSE if not.
 * \par Status values
 *   <table class="params">
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_HANDLE "INVALID_HANDLE"</td>         <td>The handle is not a valid generator handle.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_OBJECT_GONE "OBJECT_GONE"</td>            <td>The object indicated by the handle is no longer available.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_LIBRARY_NOT_INITIALIZED "LIBRARY_NOT_INITIALIZED"</td><td>The library is not initialized, see LibInit().</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_SUCCESS "SUCCESS"</td>                <td>The function executed successfully.</td></tr>
 *   </table>
 * \see GenGetOffsetMin
 * \see GenGetOffsetMax
 * \see GenGetOffset
 * \see GenSetOffset
 * \since 0.6
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef bool8_t(*LibTiePieGenHasOffset_t)( LibTiePieHandle_t hDevice );
#else
bool8_t GenHasOffset( LibTiePieHandle_t hDevice );
#endif

//! \cond EXTENDED_API

/**
 * \brief Check whether the specified generator supports controlling the signal offset for a specified signal type.
 *
 * \param[in] hDevice A \ref OpenDev "device handle" identifying the generator.
 * \param[in] dwSignalType The requested signal type, a \ref ST_ "ST_*" value.
 * \return #BOOL8_TRUE if supported, #BOOL8_FALSE if not.
 * \par Status values
 *   <table class="params">
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_VALUE "INVALID_VALUE"</td>          <td>The requested signal type is invalid.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_HANDLE "INVALID_HANDLE"</td>         <td>The handle is not a valid generator handle.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_OBJECT_GONE "OBJECT_GONE"</td>            <td>The object indicated by the handle is no longer available.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_LIBRARY_NOT_INITIALIZED "LIBRARY_NOT_INITIALIZED"</td><td>The library is not initialized, see LibInit().</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_SUCCESS "SUCCESS"</td>                <td>The function executed successfully.</td></tr>
 *   </table>
 * \since 0.6
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef bool8_t(*LibTiePieGenHasOffsetEx_t)( LibTiePieHandle_t hDevice , uint32_t dwSignalType );
#else
bool8_t GenHasOffsetEx( LibTiePieHandle_t hDevice , uint32_t dwSignalType );
#endif

//! \endcond

/**
 * \brief Get the minimum offset for the current signal type, of a specified generator.
 *
 * \param[in] hDevice A \ref OpenDev "device handle" identifying the generator.
 * \return The minimum signal offset in Volt.
 * \par Status values
 *   <table class="params">
 *   <tr><td>\ref LIBTIEPIESTATUS_NOT_SUPPORTED "NOT_SUPPORTED"</td>          <td>The requested signal type does not support signal offset.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_HANDLE "INVALID_HANDLE"</td>         <td>The handle is not a valid generator handle.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_OBJECT_GONE "OBJECT_GONE"</td>            <td>The object indicated by the handle is no longer available.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_LIBRARY_NOT_INITIALIZED "LIBRARY_NOT_INITIALIZED"</td><td>The library is not initialized, see LibInit().</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_SUCCESS "SUCCESS"</td>                <td>The function executed successfully.</td></tr>
 *   </table>
 * \see GenGetOffsetMax
 * \see GenGetOffset
 * \see GenSetOffset
 * \since 0.4.0
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef double(*LibTiePieGenGetOffsetMin_t)( LibTiePieHandle_t hDevice );
#else
double GenGetOffsetMin( LibTiePieHandle_t hDevice );
#endif

/**
 * \brief Get the maximum offset for the current signal type, of a specified generator.
 *
 * \param[in] hDevice A \ref OpenDev "device handle" identifying the generator.
 * \return The maximum signal offset in Volt.
 * \par Status values
 *   <table class="params">
 *   <tr><td>\ref LIBTIEPIESTATUS_NOT_SUPPORTED "NOT_SUPPORTED"</td>          <td>The requested signal type does not support signal offset.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_HANDLE "INVALID_HANDLE"</td>         <td>The handle is not a valid generator handle.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_OBJECT_GONE "OBJECT_GONE"</td>            <td>The object indicated by the handle is no longer available.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_LIBRARY_NOT_INITIALIZED "LIBRARY_NOT_INITIALIZED"</td><td>The library is not initialized, see LibInit().</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_SUCCESS "SUCCESS"</td>                <td>The function executed successfully.</td></tr>
 *   </table>
 * \see GenGetOffsetMin
 * \see GenGetOffset
 * \see GenSetOffset
 * \since 0.4.0
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef double(*LibTiePieGenGetOffsetMax_t)( LibTiePieHandle_t hDevice );
#else
double GenGetOffsetMax( LibTiePieHandle_t hDevice );
#endif

//! \cond EXTENDED_API

/**
 * \brief Get the minimum and maximum offset for a specified signal type, of a specified generator.
 *
 * \param[in] hDevice A \ref OpenDev "device handle" identifying the generator.
 * \param[in] dwSignalType The requested signal type, a \ref ST_ "ST_*" value.
 * \param[out] pMin A pointer to a memory location for the minimum offset in Volt, or \c NULL.
 * \param[out] pMax A pointer to a memory location for the maximum offset in Volt, or \c NULL.
 * \par Status values
 *   <table class="params">
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_VALUE "INVALID_VALUE"</td>          <td>The requested signal type is invalid.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_NOT_SUPPORTED "NOT_SUPPORTED"</td>          <td>The requested signal type does not support signal offset.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_HANDLE "INVALID_HANDLE"</td>         <td>The handle is not a valid generator handle.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_OBJECT_GONE "OBJECT_GONE"</td>            <td>The object indicated by the handle is no longer available.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_LIBRARY_NOT_INITIALIZED "LIBRARY_NOT_INITIALIZED"</td><td>The library is not initialized, see LibInit().</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_SUCCESS "SUCCESS"</td>                <td>The function executed successfully.</td></tr>
 *   </table>
 * \see GenGetOffsetMin
 * \see GenGetOffsetMax
 * \see GenGetOffset
 * \see GenSetOffset
 * \see GenVerifyOffset
 * \see GenVerifyOffsetEx
 * \since 0.4.3
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef void(*LibTiePieGenGetOffsetMinMaxEx_t)( LibTiePieHandle_t hDevice , uint32_t dwSignalType , double* pMin , double* pMax );
#else
void GenGetOffsetMinMaxEx( LibTiePieHandle_t hDevice , uint32_t dwSignalType , double* pMin , double* pMax );
#endif

//! \endcond

/**
 * \brief Get the current signal offset of a specified generator.
 *
 * \param[in] hDevice A \ref OpenDev "device handle" identifying the generator.
 * \return The currently set signal offset in Volt.
 * \par Status values
 *   <table class="params">
 *   <tr><td>\ref LIBTIEPIESTATUS_NOT_SUPPORTED "NOT_SUPPORTED"</td>          <td>The requested signal type does not support signal offset.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_HANDLE "INVALID_HANDLE"</td>         <td>The handle is not a valid generator handle.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_OBJECT_GONE "OBJECT_GONE"</td>            <td>The object indicated by the handle is no longer available.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_LIBRARY_NOT_INITIALIZED "LIBRARY_NOT_INITIALIZED"</td><td>The library is not initialized, see LibInit().</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_SUCCESS "SUCCESS"</td>                <td>The function executed successfully.</td></tr>
 *   </table>
 * \see GenGetOffsetMin
 * \see GenGetOffsetMax
 * \see GenSetOffset
 * \since 0.4.0
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef double(*LibTiePieGenGetOffset_t)( LibTiePieHandle_t hDevice );
#else
double GenGetOffset( LibTiePieHandle_t hDevice );
#endif

/**
 * \brief Set the signal offset of a specified generator.
 *
 * \param[in] hDevice A \ref OpenDev "device handle" identifying the generator.
 * \param[in] dOffset The requested signal offset in Volt.
 * \return The actually set signal offset in Volt.
 * \par Status values
 *   <table class="params">
 *   <tr><td>\ref LIBTIEPIESTATUS_VALUE_CLIPPED "VALUE_CLIPPED"</td>          <td>The requested offset is outside the valid range and clipped to the closest limit.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_VALUE_MODIFIED "VALUE_MODIFIED"</td>         <td>The requested offset is within the valid range but not available. The closest valid value is set.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_NOT_SUPPORTED "NOT_SUPPORTED"</td>          <td>The current signal type does not support signal offset.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_NOT_CONTROLLABLE "NOT_CONTROLLABLE"</td>       <td>The generator is currently not controllable, see #GenIsControllable.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_HANDLE "INVALID_HANDLE"</td>         <td>The handle is not a valid generator handle.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_OBJECT_GONE "OBJECT_GONE"</td>            <td>The object indicated by the handle is no longer available.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_LIBRARY_NOT_INITIALIZED "LIBRARY_NOT_INITIALIZED"</td><td>The library is not initialized, see LibInit().</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_SUCCESS "SUCCESS"</td>                <td>The function executed successfully.</td></tr>
 *   </table>
 * \see GenGetOffsetMin
 * \see GenGetOffsetMax
 * \see GenGetOffset
 * \since 0.4.0
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef double(*LibTiePieGenSetOffset_t)( LibTiePieHandle_t hDevice , double dOffset );
#else
double GenSetOffset( LibTiePieHandle_t hDevice , double dOffset );
#endif

//! \cond EXTENDED_API

/**
 * \brief Verify if a signal offset can be set, of a specified generator, without actually setting the hardware itself.
 *
 * \param[in] hDevice A \ref OpenDev "device handle" identifying the generator.
 * \param[in] dOffset The requested signal offset, in Volt.
 * \return The signal offset that would have been set, in Volt.
 * \par Status values
 *   <table class="params">
 *   <tr><td>\ref LIBTIEPIESTATUS_VALUE_CLIPPED "VALUE_CLIPPED"</td>          <td>The requested offset is outside the valid range and clipped to the closest limit.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_VALUE_MODIFIED "VALUE_MODIFIED"</td>         <td>The requested offset is within the valid range but not available. The closest valid value is set.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_NOT_SUPPORTED "NOT_SUPPORTED"</td>          <td>The current signal type does not support signal offset.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_HANDLE "INVALID_HANDLE"</td>         <td>The handle is not a valid generator handle.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_OBJECT_GONE "OBJECT_GONE"</td>            <td>The object indicated by the handle is no longer available.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_LIBRARY_NOT_INITIALIZED "LIBRARY_NOT_INITIALIZED"</td><td>The library is not initialized, see LibInit().</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_SUCCESS "SUCCESS"</td>                <td>The function executed successfully.</td></tr>
 *   </table>
 * \see GenGetOffsetMin
 * \see GenGetOffsetMax
 * \see GenGetOffsetMinMaxEx
 * \see GenGetOffset
 * \see GenSetOffset
 * \see GenVerifyOffsetEx
 * \since 0.4.0
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef double(*LibTiePieGenVerifyOffset_t)( LibTiePieHandle_t hDevice , double dOffset );
#else
double GenVerifyOffset( LibTiePieHandle_t hDevice , double dOffset );
#endif

/**
 * \brief Verify if a signal offset can be set for a specified signal type and amplitude, of a specified generator, without actually setting the hardware itself.
 *
 * \param[in] hDevice A \ref OpenDev "device handle" identifying the generator.
 * \param[in] dOffset The requested signal offset.
 * \param[in] dwSignalType The requested signal type, a \ref ST_ "ST_*" value.
 * \param[in] dAmplitude The requested signal amplitude, ignored for #ST_DC.
 * \return The signal offset that would have been set, in Volt.
 * \par Status values
 *   <table class="params">
 *   <tr><td>\ref LIBTIEPIESTATUS_VALUE_CLIPPED "VALUE_CLIPPED"</td>          <td>The requested offset is outside the valid range and clipped to the closest limit.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_VALUE_MODIFIED "VALUE_MODIFIED"</td>         <td>The requested offset is within the valid range but not available. The closest valid value is set.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_VALUE "INVALID_VALUE"</td>          <td>The requested signal type is invalid.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_NOT_SUPPORTED "NOT_SUPPORTED"</td>          <td>The current signal type does not support signal offset.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_HANDLE "INVALID_HANDLE"</td>         <td>The handle is not a valid generator handle.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_OBJECT_GONE "OBJECT_GONE"</td>            <td>The object indicated by the handle is no longer available.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_LIBRARY_NOT_INITIALIZED "LIBRARY_NOT_INITIALIZED"</td><td>The library is not initialized, see LibInit().</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_SUCCESS "SUCCESS"</td>                <td>The function executed successfully.</td></tr>
 *   </table>
 * \see GenGetOffsetMin
 * \see GenGetOffsetMax
 * \see GenGetOffsetMinMaxEx
 * \see GenGetOffset
 * \see GenSetOffset
 * \see GenVerifyOffset
 * \since 0.4.3
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef double(*LibTiePieGenVerifyOffsetEx_t)( LibTiePieHandle_t hDevice , double dOffset , uint32_t dwSignalType , double dAmplitude );
#else
double GenVerifyOffsetEx( LibTiePieHandle_t hDevice , double dOffset , uint32_t dwSignalType , double dAmplitude );
#endif

//! \endcond

/**
 * \}
 * \defgroup gen_signalFrequency Frequency
 * \{
 * \brief Functions for controlling signal frequency, sample frequency and frequency mode of a generator.
 *
 *           The frequency of a generator can be set between a minimum and a maximum value.
 *           Use GenGetFrequencyMin() and GenGetFrequencyMax() to get the frequency limits.
 *
 *           The frequency setting can either set the signal frequency or the sample frequency of the generator,
 *           depending on the selected \ref gen_signalFrequencyMode.
 *
 *           When \ref gen_signalType "signal type" DC is active, frequency is not available.
 *           Use GenHasFrequency() to check whether frequency is available for the currently set signal type.
 *
 *           By default the frequency mode is set to signal frequency (#FM_SIGNALFREQUENCY) and the frequency is set to 1 kHz.
 *
 * \defgroup gen_signalFrequencyMode Frequency mode
 * \{
 * \brief Functions to control the generator frequency mode.
 *
 *             When signal type arbitrary is selected, the frequency mode of the Arbitrary waveform generator can be set.
 *             The following frequency modes are supported:
 *             - <b>Signal frequency</b> : the \ref GenSetFrequency "frequency property" sets the signal frequency, the frequency at which the selected signal will be repeated.
 *             - <b>Sample frequency</b> : The \ref GenSetFrequency "frequency property" sets the sample frequency at which the individual samples of the selected signal will be generated.
 *
 *             With signal types sine, triangle, square and DC, the frequency mode is fixed to signal frequency.
 *             With signal type noise the frequency mode is fixed to sample frequency.
 *
 *             The frequency mode can be affected by changing the \ref gen_signalType "signal type".
 *
 *             By default the frequency mode is set to signal frequency (#FM_SIGNALFREQUENCY)
 */

// Workaround: Without this line Doxygen adds the documentation below to the group above.

/**
 * \brief Get the supported generator frequency modes of a specified generator.
 *
 * \param[in] hDevice A \ref OpenDev "device handle" identifying the generator.
 * \return The supported generator frequency modes, a set of OR-ed \ref FM_ "FM_*" values, or #FMM_NONE.
 * \par Status values
 *   <table class="params">
 *   <tr><td>\ref LIBTIEPIESTATUS_NOT_SUPPORTED "NOT_SUPPORTED"</td>          <td>The generator does not support frequency mode.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_HANDLE "INVALID_HANDLE"</td>         <td>The handle is not a valid generator handle.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_OBJECT_GONE "OBJECT_GONE"</td>            <td>The object indicated by the handle is no longer available.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_LIBRARY_NOT_INITIALIZED "LIBRARY_NOT_INITIALIZED"</td><td>The library is not initialized, see LibInit().</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_SUCCESS "SUCCESS"</td>                <td>The function executed successfully.</td></tr>
 *   </table>
 * \see GenGetFrequencyMode
 * \see GenSetFrequencyMode
 * \since 0.4.1
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef uint32_t(*LibTiePieGenGetFrequencyModes_t)( LibTiePieHandle_t hDevice );
#else
uint32_t GenGetFrequencyModes( LibTiePieHandle_t hDevice );
#endif

//! \cond EXTENDED_API

/**
 * \brief Get the supported generator frequency modes for a specified signal type, of a specified generator.
 *
 * \param[in] hDevice A \ref OpenDev "device handle" identifying the generator.
 * \param[in] dwSignalType The requested signal type, a \ref ST_ "ST_*" value.
 * \return The supported generator frequency modes for th especified signal type, a set of OR-ed \ref FM_ "FM_*" values, or #FMM_NONE.
 * \par Status values
 *   <table class="params">
 *   <tr><td>\ref LIBTIEPIESTATUS_NOT_SUPPORTED "NOT_SUPPORTED"</td>          <td>The generator does not support frequency mode.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_VALUE "INVALID_VALUE"</td>          <td>The requested signal type is invalid.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_HANDLE "INVALID_HANDLE"</td>         <td>The handle is not a valid generator handle.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_OBJECT_GONE "OBJECT_GONE"</td>            <td>The object indicated by the handle is no longer available.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_LIBRARY_NOT_INITIALIZED "LIBRARY_NOT_INITIALIZED"</td><td>The library is not initialized, see LibInit().</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_SUCCESS "SUCCESS"</td>                <td>The function executed successfully.</td></tr>
 *   </table>
 * \see GenGetFrequencyModes
 * \see GenGetFrequencyMode
 * \see GenSetFrequencyMode
 * \since 0.4.1
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef uint32_t(*LibTiePieGenGetFrequencyModesEx_t)( LibTiePieHandle_t hDevice , uint32_t dwSignalType );
#else
uint32_t GenGetFrequencyModesEx( LibTiePieHandle_t hDevice , uint32_t dwSignalType );
#endif

//! \endcond

/**
 * \brief Get the current generator frequency mode of a specified generator
 *
 * \param[in] hDevice A \ref OpenDev "device handle" identifying the generator.
 * \return The currently set generator frequency mode, a \ref FM_ "FM_*" value, #FM_UNKNOWN when unsuccessful.
 * \par Status values
 *   <table class="params">
 *   <tr><td>\ref LIBTIEPIESTATUS_NOT_SUPPORTED "NOT_SUPPORTED"</td>          <td>The generator does not support frequency mode.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_HANDLE "INVALID_HANDLE"</td>         <td>The handle is not a valid generator handle.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_OBJECT_GONE "OBJECT_GONE"</td>            <td>The object indicated by the handle is no longer available.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_LIBRARY_NOT_INITIALIZED "LIBRARY_NOT_INITIALIZED"</td><td>The library is not initialized, see LibInit().</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_SUCCESS "SUCCESS"</td>                <td>The function executed successfully.</td></tr>
 *   </table>
 * \see GenGetFrequencyModes
 * \see GenSetFrequencyMode
 * \since 0.4.1
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef uint32_t(*LibTiePieGenGetFrequencyMode_t)( LibTiePieHandle_t hDevice );
#else
uint32_t GenGetFrequencyMode( LibTiePieHandle_t hDevice );
#endif

/**
 * \brief Set the generator frequency mode of a specified generator.
 *
 * \param[in] hDevice A \ref OpenDev "device handle" identifying the generator.
 * \param[in] dwFrequencyMode The requested generator frequency mode, a \ref FM_ "FM_*" value.
 * \return The actually set generator frequency mode, a \ref FM_ "FM_*" value, #FM_UNKNOWN when unsuccessful.
 * \par Status values
 *   <table class="params">
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_VALUE "INVALID_VALUE"</td>          <td>The requested frequency mode is invalid.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_NOT_SUPPORTED "NOT_SUPPORTED"</td>          <td>The generator does not support generator mode.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_NOT_CONTROLLABLE "NOT_CONTROLLABLE"</td>       <td>The generator is currently not controllable, see #GenIsControllable.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_HANDLE "INVALID_HANDLE"</td>         <td>The handle is not a valid generator handle.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_OBJECT_GONE "OBJECT_GONE"</td>            <td>The object indicated by the handle is no longer available.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_LIBRARY_NOT_INITIALIZED "LIBRARY_NOT_INITIALIZED"</td><td>The library is not initialized, see LibInit().</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_SUCCESS "SUCCESS"</td>                <td>The function executed successfully.</td></tr>
 *   </table>
 * \remark Setting frequency mode is only available when \ref gen_signalType "signal type" Arbitrary is active.
 * \remark When \ref gen_signalType "signal type" Sine, Triangle or Square is active, frequency mode is fixed at signal frequency.
 * \remark When \ref gen_signalType "signal type" Noise is active, frequency mode is fixed at sample frequency.
 * \remark Changing the frequency mode can affect the \ref GenSetMode "generator mode".
 * \see GenGetFrequencyModes
 * \see GenGetFrequencyMode
 * \since 0.4.1
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef uint32_t(*LibTiePieGenSetFrequencyMode_t)( LibTiePieHandle_t hDevice , uint32_t dwFrequencyMode );
#else
uint32_t GenSetFrequencyMode( LibTiePieHandle_t hDevice , uint32_t dwFrequencyMode );
#endif

/**
 * \}
 */

// Workaround: Without this line Doxygen adds the documentation below to the group above.

/**
 * \brief Check whether the current signal type and frequency mode of a specified generator support controlling the signal/sample frequency.
 *
 * \param[in] hDevice A \ref OpenDev "device handle" identifying the generator.
 * \return #BOOL8_TRUE if supported, #BOOL8_FALSE if not.
 * \par Status values
 *   <table class="params">
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_HANDLE "INVALID_HANDLE"</td>         <td>The handle is not a valid generator handle.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_OBJECT_GONE "OBJECT_GONE"</td>            <td>The object indicated by the handle is no longer available.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_LIBRARY_NOT_INITIALIZED "LIBRARY_NOT_INITIALIZED"</td><td>The library is not initialized, see LibInit().</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_SUCCESS "SUCCESS"</td>                <td>The function executed successfully.</td></tr>
 *   </table>
 * \see GenGetFrequencyMin
 * \see GenGetFrequencyMax
 * \see GenGetFrequency
 * \see GenSetFrequency
 * \since 0.6
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef bool8_t(*LibTiePieGenHasFrequency_t)( LibTiePieHandle_t hDevice );
#else
bool8_t GenHasFrequency( LibTiePieHandle_t hDevice );
#endif

//! \cond EXTENDED_API

/**
 * \brief Check whether the specified generator supports controlling the signal/sample frequency for the specified frequency mode and signal type.
 *
 * \param[in] hDevice A \ref OpenDev "device handle" identifying the generator.
 * \param[in] dwFrequencyMode The requested generator frequency mode, a \ref FM_ "FM_*" value.
 * \param[in] dwSignalType The requested signal type, a \ref ST_ "ST_*" value.
 * \return #BOOL8_TRUE if supported, #BOOL8_FALSE if not.
 * \par Status values
 *   <table class="params">
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_VALUE "INVALID_VALUE"</td>          <td>The requested signal type is invalid.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_HANDLE "INVALID_HANDLE"</td>         <td>The handle is not a valid generator handle.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_OBJECT_GONE "OBJECT_GONE"</td>            <td>The object indicated by the handle is no longer available.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_LIBRARY_NOT_INITIALIZED "LIBRARY_NOT_INITIALIZED"</td><td>The library is not initialized, see LibInit().</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_SUCCESS "SUCCESS"</td>                <td>The function executed successfully.</td></tr>
 *   </table>
 * \since 0.6
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef bool8_t(*LibTiePieGenHasFrequencyEx_t)( LibTiePieHandle_t hDevice , uint32_t dwFrequencyMode , uint32_t dwSignalType );
#else
bool8_t GenHasFrequencyEx( LibTiePieHandle_t hDevice , uint32_t dwFrequencyMode , uint32_t dwSignalType );
#endif

//! \endcond

/**
 * \brief Get the minimum signal/sample frequency with the current frequency mode, of a specified generator.
 *
 * \param[in] hDevice A \ref OpenDev "device handle" identifying the generator.
 * \return The minimum signal/sample frequency, in Hz.
 * \par Status values
 *   <table class="params">
 *   <tr><td>\ref LIBTIEPIESTATUS_NOT_SUPPORTED "NOT_SUPPORTED"</td>          <td>The generator does not support frequency for the current signal type.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_HANDLE "INVALID_HANDLE"</td>         <td>The handle is not a valid generator handle.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_OBJECT_GONE "OBJECT_GONE"</td>            <td>The object indicated by the handle is no longer available.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_LIBRARY_NOT_INITIALIZED "LIBRARY_NOT_INITIALIZED"</td><td>The library is not initialized, see LibInit().</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_SUCCESS "SUCCESS"</td>                <td>The function executed successfully.</td></tr>
 *   </table>
 * \see GenGetFrequencyMax
 * \see GenGetFrequency
 * \see GenSetFrequency
 * \since 0.4.0
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef double(*LibTiePieGenGetFrequencyMin_t)( LibTiePieHandle_t hDevice );
#else
double GenGetFrequencyMin( LibTiePieHandle_t hDevice );
#endif

/**
 * \brief Get the maximum signal/sample frequency with the current frequency mode and signal type, of a specified generator.
 *
 * \param[in] hDevice A \ref OpenDev "device handle" identifying the generator.
 * \return The maximum signal/sample frequency, in Hz.
 * \par Status values
 *   <table class="params">
 *   <tr><td>\ref LIBTIEPIESTATUS_NOT_SUPPORTED "NOT_SUPPORTED"</td>          <td>The generator does not support frequency for the current signal type.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_HANDLE "INVALID_HANDLE"</td>         <td>The handle is not a valid generator handle.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_OBJECT_GONE "OBJECT_GONE"</td>            <td>The object indicated by the handle is no longer available.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_LIBRARY_NOT_INITIALIZED "LIBRARY_NOT_INITIALIZED"</td><td>The library is not initialized, see LibInit().</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_SUCCESS "SUCCESS"</td>                <td>The function executed successfully.</td></tr>
 *   </table>
 * \see GenGetFrequencyMin
 * \see GenGetFrequency
 * \see GenSetFrequency
 * \since 0.4.0
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef double(*LibTiePieGenGetFrequencyMax_t)( LibTiePieHandle_t hDevice );
#else
double GenGetFrequencyMax( LibTiePieHandle_t hDevice );
#endif

//! \cond EXTENDED_API

/**
 * \brief Get the minimum and maximum signal/sample frequency for a specified frequency mode and the current signal type, of a specified generator.
 *
 * \param[in] hDevice A \ref OpenDev "device handle" identifying the generator.
 * \param[in] dwFrequencyMode The requested generator frequency mode, a \ref FM_ "FM_*" value.
 * \param[out] pMin A pointer to a memory location for the minimum frequency, or \c NULL.
 * \param[out] pMax A pointer to a memory location for the maximum frequency, or \c NULL.
 * \par Status values
 *   <table class="params">
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_VALUE "INVALID_VALUE"</td>          <td>The requested frequency mode is invalid.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_NOT_SUPPORTED "NOT_SUPPORTED"</td>          <td>The generator does not support frequency for the current signal type.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_HANDLE "INVALID_HANDLE"</td>         <td>The handle is not a valid generator handle.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_OBJECT_GONE "OBJECT_GONE"</td>            <td>The object indicated by the handle is no longer available.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_LIBRARY_NOT_INITIALIZED "LIBRARY_NOT_INITIALIZED"</td><td>The library is not initialized, see LibInit().</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_SUCCESS "SUCCESS"</td>                <td>The function executed successfully.</td></tr>
 *   </table>
 * \see GenGetFrequencyMin
 * \see GenGetFrequencyMax
 * \see GenGetFrequencyMinMaxEx
 * \see GenGetFrequency
 * \see GenSetFrequency
 * \see GenVerifyFrequency
 * \see GenVerifyFrequencyEx2
 * \since 0.4.0
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef void(*LibTiePieGenGetFrequencyMinMax_t)( LibTiePieHandle_t hDevice , uint32_t dwFrequencyMode , double* pMin , double* pMax );
#else
void GenGetFrequencyMinMax( LibTiePieHandle_t hDevice , uint32_t dwFrequencyMode , double* pMin , double* pMax );
#endif

/**
 * \brief Get the minimum and maximum signal/sample frequency for a specified frequency mode and signal type, of a specified generator.
 *
 * \param[in] hDevice A \ref OpenDev "device handle" identifying the generator.
 * \param[in] dwFrequencyMode The requested generator frequency mode, a \ref FM_ "FM_*" value.
 * \param[in] dwSignalType The requested signal type, a \ref ST_ "ST_*" value.
 * \param[out] pMin A pointer to a memory location for the minimum frequency, or \c NULL.
 * \param[out] pMax A pointer to a memory location for the maximum frequency, or \c NULL.
 * \par Status values
 *   <table class="params">
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_VALUE "INVALID_VALUE"</td>          <td>The requested frequency mode and/or signal type is invalid.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_NOT_SUPPORTED "NOT_SUPPORTED"</td>          <td>The generator does not support frequency for the current signal type.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_HANDLE "INVALID_HANDLE"</td>         <td>The handle is not a valid generator handle.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_OBJECT_GONE "OBJECT_GONE"</td>            <td>The object indicated by the handle is no longer available.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_LIBRARY_NOT_INITIALIZED "LIBRARY_NOT_INITIALIZED"</td><td>The library is not initialized, see LibInit().</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_SUCCESS "SUCCESS"</td>                <td>The function executed successfully.</td></tr>
 *   </table>
 * \see GenGetFrequencyMin
 * \see GenGetFrequencyMax
 * \see GenGetFrequencyMinMax
 * \see GenGetFrequency
 * \see GenSetFrequency
 * \see GenVerifyFrequency
 * \see GenVerifyFrequencyEx2
 * \since 0.4.3
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef void(*LibTiePieGenGetFrequencyMinMaxEx_t)( LibTiePieHandle_t hDevice , uint32_t dwFrequencyMode , uint32_t dwSignalType , double* pMin , double* pMax );
#else
void GenGetFrequencyMinMaxEx( LibTiePieHandle_t hDevice , uint32_t dwFrequencyMode , uint32_t dwSignalType , double* pMin , double* pMax );
#endif

//! \endcond

/**
 * \brief Get the current signal/sample frequency, of a specified generator.
 *
 * \param[in] hDevice A \ref OpenDev "device handle" identifying the generator.
 * \return The currently set signal/sample frequency, in Hz.
 * \par Status values
 *   <table class="params">
 *   <tr><td>\ref LIBTIEPIESTATUS_NOT_SUPPORTED "NOT_SUPPORTED"</td>          <td>The generator does not support frequency for the current signal type.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_HANDLE "INVALID_HANDLE"</td>         <td>The handle is not a valid generator handle.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_OBJECT_GONE "OBJECT_GONE"</td>            <td>The object indicated by the handle is no longer available.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_LIBRARY_NOT_INITIALIZED "LIBRARY_NOT_INITIALIZED"</td><td>The library is not initialized, see LibInit().</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_SUCCESS "SUCCESS"</td>                <td>The function executed successfully.</td></tr>
 *   </table>
 * \see GenGetFrequencyMin
 * \see GenGetFrequencyMax
 * \see GenSetFrequency
 * \since 0.4.0
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef double(*LibTiePieGenGetFrequency_t)( LibTiePieHandle_t hDevice );
#else
double GenGetFrequency( LibTiePieHandle_t hDevice );
#endif

/**
 * \brief Set signal/sample frequency, of a specified generator.
 *
 * \param[in] hDevice A \ref OpenDev "device handle" identifying the generator.
 * \param[in] dFrequency The requested signal/sample frequency, in Hz.
 * \return The actually set signal/sample frequency, in Hz.
 * \remark When the generator is active, changing the signal/sample frequency will shortly interrupt the output signal.
 * \remark When \ref gen_signalType "signal type" DC is active, setting signal/sample frequency is not available.
 * \remark Changing the frequency may affect the \ref gen_signalWidth "pulse width" and/or \ref gen_signalEdgeTime "leading and trailing edge time" value(s) when signal type \ref ST_PULSE "pulse" is active.
 * \par Status values
 *   <table class="params">
 *   <tr><td>\ref LIBTIEPIESTATUS_VALUE_CLIPPED "VALUE_CLIPPED"</td>          <td>The requested frequency is outside the valid range and clipped to the closest limit.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_VALUE_MODIFIED "VALUE_MODIFIED"</td>         <td>The requested frequency is within the valid range but not available. The closest valid value is set.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_NOT_SUPPORTED "NOT_SUPPORTED"</td>          <td>The generator does not support frequency for the current signal type.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_NOT_CONTROLLABLE "NOT_CONTROLLABLE"</td>       <td>The generator is currently not controllable, see #GenIsControllable.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_HANDLE "INVALID_HANDLE"</td>         <td>The handle is not a valid generator handle.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_OBJECT_GONE "OBJECT_GONE"</td>            <td>The object indicated by the handle is no longer available.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_LIBRARY_NOT_INITIALIZED "LIBRARY_NOT_INITIALIZED"</td><td>The library is not initialized, see LibInit().</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_SUCCESS "SUCCESS"</td>                <td>The function executed successfully.</td></tr>
 *   </table>
 * \see GenGetFrequencyMin
 * \see GenGetFrequencyMax
 * \see GenGetFrequency
 * \since 0.4.0
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef double(*LibTiePieGenSetFrequency_t)( LibTiePieHandle_t hDevice , double dFrequency );
#else
double GenSetFrequency( LibTiePieHandle_t hDevice , double dFrequency );
#endif

//! \cond EXTENDED_API

/**
 * \brief Verify if a signal/sample frequency can be set, of a specified generator, without actually setting the hardware itself.
 *
 * \param[in] hDevice A \ref OpenDev "device handle" identifying the generator.
 * \param[in] dFrequency The requested signal/sample frequency, in Hz.
 * \return The signal/sample frequency that would have been set, in Hz.
 * \par Status values
 *   <table class="params">
 *   <tr><td>\ref LIBTIEPIESTATUS_VALUE_CLIPPED "VALUE_CLIPPED"</td>          <td>The requested frequency is outside the valid range and clipped to the closest limit.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_VALUE_MODIFIED "VALUE_MODIFIED"</td>         <td>The requested frequency is within the valid range but not available. The closest valid value is set.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_NOT_SUPPORTED "NOT_SUPPORTED"</td>          <td>The generator does not support frequency for the current signal type.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_HANDLE "INVALID_HANDLE"</td>         <td>The handle is not a valid generator handle.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_OBJECT_GONE "OBJECT_GONE"</td>            <td>The object indicated by the handle is no longer available.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_LIBRARY_NOT_INITIALIZED "LIBRARY_NOT_INITIALIZED"</td><td>The library is not initialized, see LibInit().</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_SUCCESS "SUCCESS"</td>                <td>The function executed successfully.</td></tr>
 *   </table>
 * \see GenGetFrequencyMin
 * \see GenGetFrequencyMax
 * \see GenGetFrequencyMinMax
 * \see GenGetFrequencyMinMaxEx
 * \see GenGetFrequency
 * \see GenVerifyFrequencyEx2
 * \since 0.4.0
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef double(*LibTiePieGenVerifyFrequency_t)( LibTiePieHandle_t hDevice , double dFrequency );
#else
double GenVerifyFrequency( LibTiePieHandle_t hDevice , double dFrequency );
#endif

/**
 * \brief  Verify if a signal/sample frequency can be set for a specified frequency mode, signal type and arbitrary waveform pattern length, of a specified generator, without actually setting the hardware itself.
 *
 * \param[in] hDevice A \ref OpenDev "device handle" identifying the generator.
 * \param[in] dFrequency The requested signal/sample frequency, in Hz.
 * \param[in] dwFrequencyMode The requested generator frequency mode, a \ref FM_ "FM_*" value.
 * \param[in] dwSignalType The requested signal type, a \ref ST_ "ST_*" value.
 * \param[in] qwDataLength The requested Arbitrary waveform pattern length.
 * \param[in] dWidth Pulse width in seconds, only for #ST_PULSE.
 * \return The signal/sample frequency that would have been set, in Hz.
 * \par Status values
 *   <table class="params">
 *   <tr><td>\ref LIBTIEPIESTATUS_VALUE_CLIPPED "VALUE_CLIPPED"</td>          <td>The requested frequency is outside the valid range and clipped to the closest limit.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_VALUE_MODIFIED "VALUE_MODIFIED"</td>         <td>The requested frequency is within the valid range but not available. The closest valid value is set.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_VALUE "INVALID_VALUE"</td>          <td>The requested frequency mode, signal type, pattern length and/or width is invalid.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_NOT_SUPPORTED "NOT_SUPPORTED"</td>          <td>The generator does not support frequency for the current signal type.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_HANDLE "INVALID_HANDLE"</td>         <td>The handle is not a valid generator handle.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_OBJECT_GONE "OBJECT_GONE"</td>            <td>The object indicated by the handle is no longer available.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_LIBRARY_NOT_INITIALIZED "LIBRARY_NOT_INITIALIZED"</td><td>The library is not initialized, see LibInit().</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_SUCCESS "SUCCESS"</td>                <td>The function executed successfully.</td></tr>
 *   </table>
 * \see GenGetFrequencyMin
 * \see GenGetFrequencyMax
 * \see GenGetFrequencyMinMax
 * \see GenGetFrequencyMinMaxEx
 * \see GenGetFrequency
 * \see GenVerifyFrequency
 * \since 0.5
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef double(*LibTiePieGenVerifyFrequencyEx2_t)( LibTiePieHandle_t hDevice , double dFrequency , uint32_t dwFrequencyMode , uint32_t dwSignalType , uint64_t qwDataLength , double dWidth );
#else
double GenVerifyFrequencyEx2( LibTiePieHandle_t hDevice , double dFrequency , uint32_t dwFrequencyMode , uint32_t dwSignalType , uint64_t qwDataLength , double dWidth );
#endif

//! \endcond

/**
 * \}
 * \defgroup gen_signalPhase Phase
 * \{
 * \brief Functions for controlling the phase of a generator.
 *
 *           The phase defines the starting point in the period of the signal that is generated, as well as the ending point.
 *           The phase of a generator can be set between a minimum and a maximum value.
 *           Use GenGetPhaseMin() and GenGetPhaseMax() to get the phase limits.
 *
 *           The phase is defined as a number between \c 0 and \c 1, where \c 0 defines the beginning of the period (\c 0&deg;)
 *           and \c 1 defines the end of the period (\c 360&deg;).
 *
 *           Phase is not available on all instruments and all signal types.
 *           Use GenHasPhase() to check whether phase is available for your instrument and for the currently set signal type.
 *
 *           By default the phase is set to: \c 0.
 */

// Workaround: Without this line Doxygen adds the documentation below to the group above.

/**
 * \brief Check whether the specified generator and the current signal type of the specified generator support controlling the signal phase.
 *
 * \param[in] hDevice A \ref OpenDev "device handle" identifying the generator.
 * \return #BOOL8_TRUE if supported, #BOOL8_FALSE if not.
 * \par Status values
 *   <table class="params">
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_HANDLE "INVALID_HANDLE"</td>         <td>The handle is not a valid generator handle.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_OBJECT_GONE "OBJECT_GONE"</td>            <td>The object indicated by the handle is no longer available.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_LIBRARY_NOT_INITIALIZED "LIBRARY_NOT_INITIALIZED"</td><td>The library is not initialized, see LibInit().</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_SUCCESS "SUCCESS"</td>                <td>The function executed successfully.</td></tr>
 *   </table>
 * \see GenGetPhaseMin
 * \see GenGetPhaseMax
 * \see GenGetPhase
 * \see GenSetPhase
 * \since 0.6
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef bool8_t(*LibTiePieGenHasPhase_t)( LibTiePieHandle_t hDevice );
#else
bool8_t GenHasPhase( LibTiePieHandle_t hDevice );
#endif

//! \cond EXTENDED_API

/**
 * \brief Check whether the specified generator supports controlling the signal phase for a specified signal type.
 *
 * \param[in] hDevice A \ref OpenDev "device handle" identifying the generator.
 * \param[in] dwSignalType The requested signal type, a \ref ST_ "ST_*" value.
 * \return #BOOL8_TRUE if supported, #BOOL8_FALSE if not.
 * \par Status values
 *   <table class="params">
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_VALUE "INVALID_VALUE"</td>          <td>The requested signal type is invalid.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_HANDLE "INVALID_HANDLE"</td>         <td>The handle is not a valid generator handle.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_OBJECT_GONE "OBJECT_GONE"</td>            <td>The object indicated by the handle is no longer available.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_LIBRARY_NOT_INITIALIZED "LIBRARY_NOT_INITIALIZED"</td><td>The library is not initialized, see LibInit().</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_SUCCESS "SUCCESS"</td>                <td>The function executed successfully.</td></tr>
 *   </table>
 * \since 0.6
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef bool8_t(*LibTiePieGenHasPhaseEx_t)( LibTiePieHandle_t hDevice , uint32_t dwSignalType );
#else
bool8_t GenHasPhaseEx( LibTiePieHandle_t hDevice , uint32_t dwSignalType );
#endif

//! \endcond

/**
 * \brief Get the minimum signal phase of a specified generator.
 *
 * \param[in] hDevice A \ref OpenDev "device handle" identifying the generator.
 * \return The minimum signal phase, a number between \c 0 and \c 1.
 * \par Status values
 *   <table class="params">
 *   <tr><td>\ref LIBTIEPIESTATUS_NOT_SUPPORTED "NOT_SUPPORTED"</td>          <td>The generator does not support phase for the current signal type.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_HANDLE "INVALID_HANDLE"</td>         <td>The handle is not a valid generator handle.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_OBJECT_GONE "OBJECT_GONE"</td>            <td>The object indicated by the handle is no longer available.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_LIBRARY_NOT_INITIALIZED "LIBRARY_NOT_INITIALIZED"</td><td>The library is not initialized, see LibInit().</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_SUCCESS "SUCCESS"</td>                <td>The function executed successfully.</td></tr>
 *   </table>
 * \see GenHasPhase
 * \see GenGetPhaseMax
 * \see GenGetPhase
 * \see GenSetPhase
 * \since 0.4.3
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef double(*LibTiePieGenGetPhaseMin_t)( LibTiePieHandle_t hDevice );
#else
double GenGetPhaseMin( LibTiePieHandle_t hDevice );
#endif

/**
 * \brief Get the maximum signal phase of a specified generator.
 *
 * \param[in] hDevice A \ref OpenDev "device handle" identifying the generator.
 * \return The maximum signal phase, a number between \c 0 and \c 1.
 * \par Status values
 *   <table class="params">
 *   <tr><td>\ref LIBTIEPIESTATUS_NOT_SUPPORTED "NOT_SUPPORTED"</td>          <td>The generator does not support phase for the current signal type.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_HANDLE "INVALID_HANDLE"</td>         <td>The handle is not a valid generator handle.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_OBJECT_GONE "OBJECT_GONE"</td>            <td>The object indicated by the handle is no longer available.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_LIBRARY_NOT_INITIALIZED "LIBRARY_NOT_INITIALIZED"</td><td>The library is not initialized, see LibInit().</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_SUCCESS "SUCCESS"</td>                <td>The function executed successfully.</td></tr>
 *   </table>
 * \see GenHasPhase
 * \see GenGetPhaseMin
 * \see GenGetPhase
 * \see GenSetPhase
 * \since 0.4.3
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef double(*LibTiePieGenGetPhaseMax_t)( LibTiePieHandle_t hDevice );
#else
double GenGetPhaseMax( LibTiePieHandle_t hDevice );
#endif

//! \cond EXTENDED_API

/**
 * \brief Get the minimum and maximum phase for a specified signal type, of a specified generator.
 *
 * \param[in] hDevice A \ref OpenDev "device handle" identifying the generator.
 * \param[in] dwSignalType The requested signal type, a \ref ST_ "ST_*" value.
 * \param[out] pMin A pointer to a memory location for the minimum phase, or \c NULL.
 * \param[out] pMax A pointer to a memory location for the maximum phase, or \c NULL.
 * \par Status values
 *   <table class="params">
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_VALUE "INVALID_VALUE"</td>          <td>The requested signal type is invalid.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_NOT_SUPPORTED "NOT_SUPPORTED"</td>          <td>The generator does not support phase for the current signal type.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_HANDLE "INVALID_HANDLE"</td>         <td>The handle is not a valid generator handle.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_OBJECT_GONE "OBJECT_GONE"</td>            <td>The object indicated by the handle is no longer available.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_LIBRARY_NOT_INITIALIZED "LIBRARY_NOT_INITIALIZED"</td><td>The library is not initialized, see LibInit().</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_SUCCESS "SUCCESS"</td>                <td>The function executed successfully.</td></tr>
 *   </table>
 * \see GenGetPhaseMin
 * \see GenGetPhaseMax
 * \see GenGetPhase
 * \see GenSetPhase
 * \see GenVerifyPhase
 * \see GenVerifyPhaseEx
 * \since 0.4.3
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef void(*LibTiePieGenGetPhaseMinMaxEx_t)( LibTiePieHandle_t hDevice , uint32_t dwSignalType , double* pMin , double* pMax );
#else
void GenGetPhaseMinMaxEx( LibTiePieHandle_t hDevice , uint32_t dwSignalType , double* pMin , double* pMax );
#endif

//! \endcond

/**
 * \brief Get the current signal phase of a specified generator.
 *
 * \param[in] hDevice A \ref OpenDev "device handle" identifying the generator.
 * \return The currently set signal phase, a number between \c 0 and \c 1.
 * \par Status values
 *   <table class="params">
 *   <tr><td>\ref LIBTIEPIESTATUS_NOT_SUPPORTED "NOT_SUPPORTED"</td>          <td>The generator does not support phase for the current signal type.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_HANDLE "INVALID_HANDLE"</td>         <td>The handle is not a valid generator handle.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_OBJECT_GONE "OBJECT_GONE"</td>            <td>The object indicated by the handle is no longer available.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_LIBRARY_NOT_INITIALIZED "LIBRARY_NOT_INITIALIZED"</td><td>The library is not initialized, see LibInit().</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_SUCCESS "SUCCESS"</td>                <td>The function executed successfully.</td></tr>
 *   </table>
 * \see GenHasPhase
 * \see GenGetPhaseMin
 * \see GenGetPhaseMax
 * \see GenSetPhase
 * \since 0.4.0
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef double(*LibTiePieGenGetPhase_t)( LibTiePieHandle_t hDevice );
#else
double GenGetPhase( LibTiePieHandle_t hDevice );
#endif

/**
 * \brief Set the signal phase of a specified generator.
 *
 * \param[in] hDevice A \ref OpenDev "device handle" identifying the generator.
 * \param[in] dPhase The requested signal phase, a number between \c 0 and \c 1.
 * \return The actually set signal phase, a number between \c 0 and \c 1.
 * \par Status values
 *   <table class="params">
 *   <tr><td>\ref LIBTIEPIESTATUS_VALUE_CLIPPED "VALUE_CLIPPED"</td>          <td>The requested phase is outside the valid range and clipped to the closest limit.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_VALUE_MODIFIED "VALUE_MODIFIED"</td>         <td>The requested phase is within the valid range but not available. The closest valid value is set.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_NOT_SUPPORTED "NOT_SUPPORTED"</td>          <td>The generator does not support phase for the current signal type.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_NOT_CONTROLLABLE "NOT_CONTROLLABLE"</td>       <td>The generator is currently not controllable, see #GenIsControllable.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_HANDLE "INVALID_HANDLE"</td>         <td>The handle is not a valid generator handle.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_OBJECT_GONE "OBJECT_GONE"</td>            <td>The object indicated by the handle is no longer available.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_LIBRARY_NOT_INITIALIZED "LIBRARY_NOT_INITIALIZED"</td><td>The library is not initialized, see LibInit().</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_SUCCESS "SUCCESS"</td>                <td>The function executed successfully.</td></tr>
 *   </table>
 * \remark When the generator is active, changing the phase will shortly interrupt the output signal.
 * \remark When \ref gen_signalType "signal type" DC or Noise is active, setting phase is not available.
 * \see GenHasPhase
 * \see GenGetPhaseMin
 * \see GenGetPhaseMax
 * \see GenGetPhase
 * \since 0.4.0
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef double(*LibTiePieGenSetPhase_t)( LibTiePieHandle_t hDevice , double dPhase );
#else
double GenSetPhase( LibTiePieHandle_t hDevice , double dPhase );
#endif

//! \cond EXTENDED_API

/**
 * \brief Verify if a phase can be set, of a specified generator, without actually setting the hardware itself.
 *
 * \param[in] hDevice A \ref OpenDev "device handle" identifying the generator.
 * \param[in] dPhase The requested signal phase, a number between \c 0 and \c 1.
 * \return The signal phase that would have been set, a number between \c 0 and \c 1.
 * \par Status values
 *   <table class="params">
 *   <tr><td>\ref LIBTIEPIESTATUS_VALUE_CLIPPED "VALUE_CLIPPED"</td>          <td>The requested phase is outside the valid range and clipped to the closest limit.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_VALUE_MODIFIED "VALUE_MODIFIED"</td>         <td>The requested phase is within the valid range but not available. The closest valid value is set.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_NOT_SUPPORTED "NOT_SUPPORTED"</td>          <td>The generator does not support phase for the current signal type.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_HANDLE "INVALID_HANDLE"</td>         <td>The handle is not a valid generator handle.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_OBJECT_GONE "OBJECT_GONE"</td>            <td>The object indicated by the handle is no longer available.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_LIBRARY_NOT_INITIALIZED "LIBRARY_NOT_INITIALIZED"</td><td>The library is not initialized, see LibInit().</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_SUCCESS "SUCCESS"</td>                <td>The function executed successfully.</td></tr>
 *   </table>
 * \see GenGetPhaseMin
 * \see GenGetPhaseMax
 * \see GenGetPhaseMinMaxEx
 * \see GenGetPhase
 * \see GenSetPhase
 * \see GenVerifyPhaseEx
 * \since 0.4.0
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef double(*LibTiePieGenVerifyPhase_t)( LibTiePieHandle_t hDevice , double dPhase );
#else
double GenVerifyPhase( LibTiePieHandle_t hDevice , double dPhase );
#endif

/**
 * \brief Verify if a phase can be set for a specific signal type, of a specified generator, without actually setting the hardware itself.
 *
 * \param[in] hDevice A \ref OpenDev "device handle" identifying the generator.
 * \param[in] dPhase The requested signal phase, a number between \c 0 and \c 1.
 * \param[in] dwSignalType The requested signal type, a \ref ST_ "ST_*" value.
 * \return The signal phase that would have been set, a number between \c 0 and \c 1.
 * \par Status values
 *   <table class="params">
 *   <tr><td>\ref LIBTIEPIESTATUS_VALUE_CLIPPED "VALUE_CLIPPED"</td>          <td>The requested phase is outside the valid range and clipped to the closest limit.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_VALUE_MODIFIED "VALUE_MODIFIED"</td>         <td>The requested phase is within the valid range but not available. The closest valid value is set.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_VALUE "INVALID_VALUE"</td>          <td>The requested signal type is invalid.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_NOT_SUPPORTED "NOT_SUPPORTED"</td>          <td>The generator does not support phase for the current signal type.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_HANDLE "INVALID_HANDLE"</td>         <td>The handle is not a valid generator handle.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_OBJECT_GONE "OBJECT_GONE"</td>            <td>The object indicated by the handle is no longer available.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_LIBRARY_NOT_INITIALIZED "LIBRARY_NOT_INITIALIZED"</td><td>The library is not initialized, see LibInit().</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_SUCCESS "SUCCESS"</td>                <td>The function executed successfully.</td></tr>
 *   </table>
 * \see GenGetPhaseMin
 * \see GenGetPhaseMax
 * \see GenGetPhaseMinMaxEx
 * \see GenGetPhase
 * \see GenSetPhase
 * \see GenVerifyPhase
 * \since 0.4.3
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef double(*LibTiePieGenVerifyPhaseEx_t)( LibTiePieHandle_t hDevice , double dPhase , uint32_t dwSignalType );
#else
double GenVerifyPhaseEx( LibTiePieHandle_t hDevice , double dPhase , uint32_t dwSignalType );
#endif

//! \endcond

/**
 * \}
 * \defgroup gen_signalSymmetry Symmetry
 * \{
 * \brief Functions for controlling the signal symmetry of a generator.
 *
 *           The symmetry of a signal defines the ratio between the length of positive part of a period and the length of the negative part
 *           of a period of the generated signal.
 *           The symmetry of a generator can be set between a minimum and a maximum value.
 *           Use GenGetSymmetryMin() and GenGetSymmetryMax() to get the symmetry limits.
 *
 *           The symmetry is defined as a number between \c 0 and \c 1, where \c 0 defines a symmetry of 0% (no positive part)
 *           and \c 1 defines a symmetry of 100% (no negative part).
 *
 *           When \ref gen_signalType "signal type" Pulse, DC, Noise or Arbitrary is active, setting symmetry is not available.
 *           Use GenHasSymmetry() to check whether symmetry is available for the currently set signal type.
 *
 *           By default the symmetry is set to: 0.5 (50%).
 */

// Workaround: Without this line Doxygen adds the documentation below to the group above.

/**
 * \brief Check whether the current signal type of a specified generator supports controlling the signal symmetry.
 *
 * \param[in] hDevice A \ref OpenDev "device handle" identifying the generator.
 * \return #BOOL8_TRUE if supported, #BOOL8_FALSE if not.
 * \par Status values
 *   <table class="params">
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_HANDLE "INVALID_HANDLE"</td>         <td>The handle is not a valid generator handle.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_OBJECT_GONE "OBJECT_GONE"</td>            <td>The object indicated by the handle is no longer available.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_LIBRARY_NOT_INITIALIZED "LIBRARY_NOT_INITIALIZED"</td><td>The library is not initialized, see LibInit().</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_SUCCESS "SUCCESS"</td>                <td>The function executed successfully.</td></tr>
 *   </table>
 * \see GenGetSymmetryMin
 * \see GenGetSymmetryMax
 * \see GenGetSymmetry
 * \see GenSetSymmetry
 * \since 0.6
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef bool8_t(*LibTiePieGenHasSymmetry_t)( LibTiePieHandle_t hDevice );
#else
bool8_t GenHasSymmetry( LibTiePieHandle_t hDevice );
#endif

//! \cond EXTENDED_API

/**
 * \brief Check whether the specified generator supports controlling the signal symmetry for a specified signal type.
 *
 * \param[in] hDevice A \ref OpenDev "device handle" identifying the generator.
 * \param[in] dwSignalType The requested signal type, a \ref ST_ "ST_*" value.
 * \return #BOOL8_TRUE if supported, #BOOL8_FALSE if not.
 * \par Status values
 *   <table class="params">
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_VALUE "INVALID_VALUE"</td>          <td>The requested signal type is invalid.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_HANDLE "INVALID_HANDLE"</td>         <td>The handle is not a valid generator handle.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_OBJECT_GONE "OBJECT_GONE"</td>            <td>The object indicated by the handle is no longer available.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_LIBRARY_NOT_INITIALIZED "LIBRARY_NOT_INITIALIZED"</td><td>The library is not initialized, see LibInit().</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_SUCCESS "SUCCESS"</td>                <td>The function executed successfully.</td></tr>
 *   </table>
 * \since 0.6
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef bool8_t(*LibTiePieGenHasSymmetryEx_t)( LibTiePieHandle_t hDevice , uint32_t dwSignalType );
#else
bool8_t GenHasSymmetryEx( LibTiePieHandle_t hDevice , uint32_t dwSignalType );
#endif

//! \endcond

/**
 * \brief Get the minimum signal symmetry of a specified generator.
 *
 * \param[in] hDevice A \ref OpenDev "device handle" identifying the generator.
 * \return The minimum signal symmetry, a number between \c 0 and \c 1.
 * \par Status values
 *   <table class="params">
 *   <tr><td>\ref LIBTIEPIESTATUS_NOT_SUPPORTED "NOT_SUPPORTED"</td>          <td>The generator does not support symmetry for the current signal type.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_HANDLE "INVALID_HANDLE"</td>         <td>The handle is not a valid generator handle.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_OBJECT_GONE "OBJECT_GONE"</td>            <td>The object indicated by the handle is no longer available.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_LIBRARY_NOT_INITIALIZED "LIBRARY_NOT_INITIALIZED"</td><td>The library is not initialized, see LibInit().</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_SUCCESS "SUCCESS"</td>                <td>The function executed successfully.</td></tr>
 *   </table>
 * \see GenGetSymmetryMax
 * \see GenGetSymmetry
 * \see GenSetSymmetry
 * \since 0.4.3
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef double(*LibTiePieGenGetSymmetryMin_t)( LibTiePieHandle_t hDevice );
#else
double GenGetSymmetryMin( LibTiePieHandle_t hDevice );
#endif

/**
 * \brief Get the maximum signal symmetry of a specified generator.
 *
 * \param[in] hDevice A \ref OpenDev "device handle" identifying the generator.
 * \return The maximum signal symmetry, a number between \c 0 and \c 1.
 * \par Status values
 *   <table class="params">
 *   <tr><td>\ref LIBTIEPIESTATUS_NOT_SUPPORTED "NOT_SUPPORTED"</td>          <td>The generator does not support symmetry for the current signal type.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_HANDLE "INVALID_HANDLE"</td>         <td>The handle is not a valid generator handle.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_OBJECT_GONE "OBJECT_GONE"</td>            <td>The object indicated by the handle is no longer available.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_LIBRARY_NOT_INITIALIZED "LIBRARY_NOT_INITIALIZED"</td><td>The library is not initialized, see LibInit().</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_SUCCESS "SUCCESS"</td>                <td>The function executed successfully.</td></tr>
 *   </table>
 * \see GenGetSymmetryMin
 * \see GenGetSymmetry
 * \see GenSetSymmetry
 * \since 0.4.3
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef double(*LibTiePieGenGetSymmetryMax_t)( LibTiePieHandle_t hDevice );
#else
double GenGetSymmetryMax( LibTiePieHandle_t hDevice );
#endif

//! \cond EXTENDED_API

/**
 * \brief Get the minimum and maximum symmetry for a specified signal type, of a specified generator.
 *
 * \param[in] hDevice A \ref OpenDev "device handle" identifying the generator.
 * \param[in] dwSignalType The requested signal type, a \ref ST_ "ST_*" value.
 * \param[out] pMin A pointer to a memory location for the minimum symmetry, or \c NULL.
 * \param[out] pMax A pointer to a memory location for the maximum symmetry, or \c NULL.
 * \par Status values
 *   <table class="params">
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_VALUE "INVALID_VALUE"</td>          <td>The requested signal type is invalid.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_NOT_SUPPORTED "NOT_SUPPORTED"</td>          <td>The generator does not support symmetry for the current signal type.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_HANDLE "INVALID_HANDLE"</td>         <td>The handle is not a valid generator handle.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_OBJECT_GONE "OBJECT_GONE"</td>            <td>The object indicated by the handle is no longer available.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_LIBRARY_NOT_INITIALIZED "LIBRARY_NOT_INITIALIZED"</td><td>The library is not initialized, see LibInit().</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_SUCCESS "SUCCESS"</td>                <td>The function executed successfully.</td></tr>
 *   </table>
 * \see GenGetSymmetryMin
 * \see GenGetSymmetryMax
 * \see GenGetSymmetry
 * \see GenSetSymmetry
 * \see GenVerifySymmetry
 * \see GenVerifySymmetryEx
 * \since 0.4.3
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef void(*LibTiePieGenGetSymmetryMinMaxEx_t)( LibTiePieHandle_t hDevice , uint32_t dwSignalType , double* pMin , double* pMax );
#else
void GenGetSymmetryMinMaxEx( LibTiePieHandle_t hDevice , uint32_t dwSignalType , double* pMin , double* pMax );
#endif

//! \endcond

/**
 * \brief Get the current signal symmetry of a specified generator.
 *
 * \param[in] hDevice A \ref OpenDev "device handle" identifying the generator.
 * \return The currently set signal symmetry, a number between \c 0 and \c 1.
 * \par Status values
 *   <table class="params">
 *   <tr><td>\ref LIBTIEPIESTATUS_NOT_SUPPORTED "NOT_SUPPORTED"</td>          <td>The generator does not support symmetry for the current signal type.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_HANDLE "INVALID_HANDLE"</td>         <td>The handle is not a valid generator handle.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_OBJECT_GONE "OBJECT_GONE"</td>            <td>The object indicated by the handle is no longer available.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_LIBRARY_NOT_INITIALIZED "LIBRARY_NOT_INITIALIZED"</td><td>The library is not initialized, see LibInit().</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_SUCCESS "SUCCESS"</td>                <td>The function executed successfully.</td></tr>
 *   </table>
 * \see GenGetSymmetryMin
 * \see GenGetSymmetryMax
 * \see GenSetSymmetry
 * \since 0.4.0
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef double(*LibTiePieGenGetSymmetry_t)( LibTiePieHandle_t hDevice );
#else
double GenGetSymmetry( LibTiePieHandle_t hDevice );
#endif

/**
 * \brief Set the signal symmetry of a specified generator.
 *
 * \param[in] hDevice A \ref OpenDev "device handle" identifying the generator.
 * \param[in] dSymmetry The requested signal symmetry, a number between \c 0 and \c 1.
 * \par Status values
 *   <table class="params">
 *   <tr><td>\ref LIBTIEPIESTATUS_VALUE_CLIPPED "VALUE_CLIPPED"</td>          <td>The requested symmetry is outside the valid range and clipped to the closest limit.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_VALUE_MODIFIED "VALUE_MODIFIED"</td>         <td>The requested symmetry is within the valid range but not available. The closest valid value is set.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_NOT_SUPPORTED "NOT_SUPPORTED"</td>          <td>The generator does not support symmetry for the current signal type.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_NOT_CONTROLLABLE "NOT_CONTROLLABLE"</td>       <td>The generator is currently not controllable, see #GenIsControllable.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_HANDLE "INVALID_HANDLE"</td>         <td>The handle is not a valid generator handle.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_OBJECT_GONE "OBJECT_GONE"</td>            <td>The object indicated by the handle is no longer available.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_LIBRARY_NOT_INITIALIZED "LIBRARY_NOT_INITIALIZED"</td><td>The library is not initialized, see LibInit().</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_SUCCESS "SUCCESS"</td>                <td>The function executed successfully.</td></tr>
 *   </table>
 * \return The actually set signal symmetry, a number between \c 0 and \c 1.
 * \remark When the generator is active, changing the symmetry will shortly interrupt the output signal.
 * \see GenGetSymmetryMin
 * \see GenGetSymmetryMax
 * \see GenGetSymmetry
 * \since 0.4.0
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef double(*LibTiePieGenSetSymmetry_t)( LibTiePieHandle_t hDevice , double dSymmetry );
#else
double GenSetSymmetry( LibTiePieHandle_t hDevice , double dSymmetry );
#endif

//! \cond EXTENDED_API

/**
 * \brief Verify if a symmetry can be set, of a specified generator, without actually setting the hardware itself.
 *
 * \param[in] hDevice A \ref OpenDev "device handle" identifying the generator.
 * \param[in] dSymmetry The requested signal symmetry, a number between \c 0 and \c 1.
 * \return The signal symmetry that would have been set, a number between \c 0 and \c 1.
 * \par Status values
 *   <table class="params">
 *   <tr><td>\ref LIBTIEPIESTATUS_VALUE_CLIPPED "VALUE_CLIPPED"</td>          <td>The requested symmetry is outside the valid range and clipped to the closest limit.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_VALUE_MODIFIED "VALUE_MODIFIED"</td>         <td>The requested symmetry is within the valid range but not available. The closest valid value is set.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_NOT_SUPPORTED "NOT_SUPPORTED"</td>          <td>The generator does not support symmetry for the current signal type.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_HANDLE "INVALID_HANDLE"</td>         <td>The handle is not a valid generator handle.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_OBJECT_GONE "OBJECT_GONE"</td>            <td>The object indicated by the handle is no longer available.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_LIBRARY_NOT_INITIALIZED "LIBRARY_NOT_INITIALIZED"</td><td>The library is not initialized, see LibInit().</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_SUCCESS "SUCCESS"</td>                <td>The function executed successfully.</td></tr>
 *   </table>
 * \see GenGetSymmetryMin
 * \see GenGetSymmetryMax
 * \see GenGetSymmetryMinMaxEx
 * \see GenGetSymmetry
 * \see GenSetSymmetry
 * \see GenVerifySymmetryEx
 * \since 0.4.0
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef double(*LibTiePieGenVerifySymmetry_t)( LibTiePieHandle_t hDevice , double dSymmetry );
#else
double GenVerifySymmetry( LibTiePieHandle_t hDevice , double dSymmetry );
#endif

/**
 * \brief Verify if a symmetry can be set for a specific signal type, of a specified generator, without actually setting the hardware itself.
 *
 * \param[in] hDevice A \ref OpenDev "device handle" identifying the generator.
 * \param[in] dSymmetry The requested signal symmetry, a number between \c 0 and \c 1.
 * \param[in] dwSignalType The requested signal type, a \ref ST_ "ST_*" value.
 * \return The signal symmetry that would have been set, a number between \c 0 and \c 1.
 * \par Status values
 *   <table class="params">
 *   <tr><td>\ref LIBTIEPIESTATUS_VALUE_CLIPPED "VALUE_CLIPPED"</td>          <td>The requested symmetry is outside the valid range and clipped to the closest limit.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_VALUE_MODIFIED "VALUE_MODIFIED"</td>         <td>The requested symmetry is within the valid range but not available. The closest valid value is set.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_VALUE "INVALID_VALUE"</td>          <td>The requested signal type is invalid.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_NOT_SUPPORTED "NOT_SUPPORTED"</td>          <td>The generator does not support symmetry for the current signal type.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_HANDLE "INVALID_HANDLE"</td>         <td>The handle is not a valid generator handle.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_OBJECT_GONE "OBJECT_GONE"</td>            <td>The object indicated by the handle is no longer available.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_LIBRARY_NOT_INITIALIZED "LIBRARY_NOT_INITIALIZED"</td><td>The library is not initialized, see LibInit().</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_SUCCESS "SUCCESS"</td>                <td>The function executed successfully.</td></tr>
 *   </table>
 * \see GenGetSymmetryMin
 * \see GenGetSymmetryMax
 * \see GenGetSymmetryMinMaxEx
 * \see GenGetSymmetry
 * \see GenSetSymmetry
 * \see GenVerifySymmetry
 * \since 0.4.3
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef double(*LibTiePieGenVerifySymmetryEx_t)( LibTiePieHandle_t hDevice , double dSymmetry , uint32_t dwSignalType );
#else
double GenVerifySymmetryEx( LibTiePieHandle_t hDevice , double dSymmetry , uint32_t dwSignalType );
#endif

//! \endcond

/**
 * \}
 * \defgroup gen_signalWidth Pulse width
 * \{
 * \brief Functions for controlling the pulse width of a generator.
 *
 *           The pulse width defines the width of the pulse when \ref gen_signalType "signal type" is set to #ST_PULSE, without affecting the
 * \ref gen_signalFrequency "signal frequency".
 * \image html PulseDefinition.png
 *           The pulse width is defined as the time between 50% of the leading edge of the pulse and 50% of the trailing edge of the pulse,
 *           in seconds. See also \ref gen_signalEdgeTime "pulse edge times".
 *
 *           The pulse width of a generator can be set between a minimum and a maximum value.
 *           Use GenGetWidthMin() and GenGetWidthMax() to get the pulse width limits.
 *
 *           The pulse width can be affected by changing the \ref gen_signalFrequency "signal frequency".
 *
 *           The pulse width is not available on all instruments and only available for \ref gen_signalType "signal type" Pulse.
 *           Use GenHasWidth() to check whether pulse width is available for your instrument and the currently set signal type.
 *
 *           By default the pulse width is set to: 1 us.
 */

// Workaround: Without this line Doxygen adds the documentation below to the group above.

/**
 * \brief Check whether the current signal type of a specified generator supports controlling the signal pulse width.
 *
 * \param[in] hDevice A \ref OpenDev "device handle" identifying the generator.
 * \return #BOOL8_TRUE if supported, #BOOL8_FALSE if not.
 * \par Status values
 *   <table class="params">
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_HANDLE "INVALID_HANDLE"</td>         <td>The handle is not a valid generator handle.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_OBJECT_GONE "OBJECT_GONE"</td>            <td>The object indicated by the handle is no longer available.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_LIBRARY_NOT_INITIALIZED "LIBRARY_NOT_INITIALIZED"</td><td>The library is not initialized, see LibInit().</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_SUCCESS "SUCCESS"</td>                <td>The function executed successfully.</td></tr>
 *   </table>
 * \see GenGetWidthMin
 * \see GenGetWidthMax
 * \see GenGetWidth
 * \see GenSetWidth
 * \since 0.6
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef bool8_t(*LibTiePieGenHasWidth_t)( LibTiePieHandle_t hDevice );
#else
bool8_t GenHasWidth( LibTiePieHandle_t hDevice );
#endif

//! \cond EXTENDED_API

/**
 * \brief Check whether the specified generator supports controlling the signal pulse width for a specified signal type.
 *
 * \param[in] hDevice A \ref OpenDev "device handle" identifying the generator.
 * \param[in] dwSignalType The requested signal type, a \ref ST_ "ST_*" value.
 * \return #BOOL8_TRUE if supported, #BOOL8_FALSE if not.
 * \par Status values
 *   <table class="params">
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_VALUE "INVALID_VALUE"</td>          <td>The requested signal type is invalid.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_HANDLE "INVALID_HANDLE"</td>         <td>The handle is not a valid generator handle.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_OBJECT_GONE "OBJECT_GONE"</td>            <td>The object indicated by the handle is no longer available.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_LIBRARY_NOT_INITIALIZED "LIBRARY_NOT_INITIALIZED"</td><td>The library is not initialized, see LibInit().</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_SUCCESS "SUCCESS"</td>                <td>The function executed successfully.</td></tr>
 *   </table>
 * \since 0.6
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef bool8_t(*LibTiePieGenHasWidthEx_t)( LibTiePieHandle_t hDevice , uint32_t dwSignalType );
#else
bool8_t GenHasWidthEx( LibTiePieHandle_t hDevice , uint32_t dwSignalType );
#endif

//! \endcond

/**
 * \brief Get the minimum pulse width with the current signal frequency, of a specified generator.
 *
 * \param[in] hDevice A \ref OpenDev "device handle" identifying the generator.
 * \return The minimum pulse width in seconds.
 * \par Status values
 *   <table class="params">
 *   <tr><td>\ref LIBTIEPIESTATUS_NOT_SUPPORTED "NOT_SUPPORTED"</td>          <td>The generator does not support pulse width for the current signal type.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_HANDLE "INVALID_HANDLE"</td>         <td>The handle is not a valid generator handle.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_OBJECT_GONE "OBJECT_GONE"</td>            <td>The object indicated by the handle is no longer available.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_LIBRARY_NOT_INITIALIZED "LIBRARY_NOT_INITIALIZED"</td><td>The library is not initialized, see LibInit().</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_SUCCESS "SUCCESS"</td>                <td>The function executed successfully.</td></tr>
 *   </table>
 * \see GenGetWidthMax
 * \see GenGetWidth
 * \see GenSetWidth
 * \since 0.5
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef double(*LibTiePieGenGetWidthMin_t)( LibTiePieHandle_t hDevice );
#else
double GenGetWidthMin( LibTiePieHandle_t hDevice );
#endif

/**
 * \brief Get the maximum pulse width with the current signal frequency, of a specified generator.
 *
 * \param[in] hDevice A \ref OpenDev "device handle" identifying the generator.
 * \return The maximum pulse width in seconds.
 * \par Status values
 *   <table class="params">
 *   <tr><td>\ref LIBTIEPIESTATUS_NOT_SUPPORTED "NOT_SUPPORTED"</td>          <td>The generator does not support pulse width for the current signal type.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_HANDLE "INVALID_HANDLE"</td>         <td>The handle is not a valid generator handle.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_OBJECT_GONE "OBJECT_GONE"</td>            <td>The object indicated by the handle is no longer available.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_LIBRARY_NOT_INITIALIZED "LIBRARY_NOT_INITIALIZED"</td><td>The library is not initialized, see LibInit().</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_SUCCESS "SUCCESS"</td>                <td>The function executed successfully.</td></tr>
 *   </table>
 * \see GenGetWidthMin
 * \see GenGetWidth
 * \see GenSetWidth
 * \since 0.5
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef double(*LibTiePieGenGetWidthMax_t)( LibTiePieHandle_t hDevice );
#else
double GenGetWidthMax( LibTiePieHandle_t hDevice );
#endif

//! \cond EXTENDED_API

/**
 * \brief Get the minimum and maximum pulse width for a specified signal type and signal frequency, of a specified generator.
 *
 * \param[in] hDevice A \ref OpenDev "device handle" identifying the generator.
 * \param[in] dwSignalType The requested signal type, a \ref ST_ "ST_*" value.
 * \param[in] dSignalFrequency The requested signal frequency in Hz.
 * \param[out] pMin A pointer to a memory location for the minimum pulse width, or \c NULL.
 * \param[out] pMax A pointer to a memory location for the maximum pulse width, or \c NULL.
 * \par Status values
 *   <table class="params">
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_VALUE "INVALID_VALUE"</td>          <td>The requested signal type and/or signal frequency is invalid.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_NOT_SUPPORTED "NOT_SUPPORTED"</td>          <td>The generator does not support pulse width for the current signal type.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_HANDLE "INVALID_HANDLE"</td>         <td>The handle is not a valid generator handle.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_OBJECT_GONE "OBJECT_GONE"</td>            <td>The object indicated by the handle is no longer available.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_LIBRARY_NOT_INITIALIZED "LIBRARY_NOT_INITIALIZED"</td><td>The library is not initialized, see LibInit().</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_SUCCESS "SUCCESS"</td>                <td>The function executed successfully.</td></tr>
 *   </table>
 * \see GenGetWidthMin
 * \see GenGetWidthMax
 * \see GenGetWidth
 * \see GenSetWidth
 * \see GenVerifyWidth
 * \see GenVerifyWidthEx
 * \since 0.5
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef void(*LibTiePieGenGetWidthMinMaxEx_t)( LibTiePieHandle_t hDevice , uint32_t dwSignalType , double dSignalFrequency , double* pMin , double* pMax );
#else
void GenGetWidthMinMaxEx( LibTiePieHandle_t hDevice , uint32_t dwSignalType , double dSignalFrequency , double* pMin , double* pMax );
#endif

//! \endcond

/**
 * \brief Get the current pulse width, of a specified generator.
 *
 * \param[in] hDevice A \ref OpenDev "device handle" identifying the generator.
 * \return The currently set pulse width in seconds.
 * \par Status values
 *   <table class="params">
 *   <tr><td>\ref LIBTIEPIESTATUS_NOT_SUPPORTED "NOT_SUPPORTED"</td>          <td>The generator does not support pulse width for the current signal type.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_HANDLE "INVALID_HANDLE"</td>         <td>The handle is not a valid generator handle.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_OBJECT_GONE "OBJECT_GONE"</td>            <td>The object indicated by the handle is no longer available.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_LIBRARY_NOT_INITIALIZED "LIBRARY_NOT_INITIALIZED"</td><td>The library is not initialized, see LibInit().</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_SUCCESS "SUCCESS"</td>                <td>The function executed successfully.</td></tr>
 *   </table>
 * \see GenGetWidthMin
 * \see GenGetWidthMax
 * \see GenSetWidth
 * \since 0.5
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef double(*LibTiePieGenGetWidth_t)( LibTiePieHandle_t hDevice );
#else
double GenGetWidth( LibTiePieHandle_t hDevice );
#endif

/**
 * \brief Set the pulse width, of a specified generator.
 *
 * \param[in] hDevice A \ref OpenDev "device handle" identifying the generator.
 * \param[in] dWidth The requested pulse width in seconds.
 * \return The actually set pulse width in seconds
 * \remark When the generator is active, changing the pulse width will shortly interrupt the output signal.
 * \remark Changing the pulse width may affect the \ref gen_signalEdgeTime "leading and trailing edge time" value(s).
 * \par Status values
 *   <table class="params">
 *   <tr><td>\ref LIBTIEPIESTATUS_VALUE_CLIPPED "VALUE_CLIPPED"</td>          <td>The requested pulse width is outside the valid range and clipped to the closest limit.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_VALUE_MODIFIED "VALUE_MODIFIED"</td>         <td>The requested pulse width is within the valid range but not available. The closest valid value is set.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_NOT_SUPPORTED "NOT_SUPPORTED"</td>          <td>The generator does not support pulse width for the current signal type.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_NOT_CONTROLLABLE "NOT_CONTROLLABLE"</td>       <td>The generator is currently not controllable, see #GenIsControllable.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_HANDLE "INVALID_HANDLE"</td>         <td>The handle is not a valid generator handle.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_OBJECT_GONE "OBJECT_GONE"</td>            <td>The object indicated by the handle is no longer available.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_LIBRARY_NOT_INITIALIZED "LIBRARY_NOT_INITIALIZED"</td><td>The library is not initialized, see LibInit().</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_SUCCESS "SUCCESS"</td>                <td>The function executed successfully.</td></tr>
 *   </table>
 * \see GenGetWidthMin
 * \see GenGetWidthMax
 * \see GenGetWidth
 * \since 0.5
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef double(*LibTiePieGenSetWidth_t)( LibTiePieHandle_t hDevice , double dWidth );
#else
double GenSetWidth( LibTiePieHandle_t hDevice , double dWidth );
#endif

//! \cond EXTENDED_API

/**
 * \brief Verify if a pulse width can be set, of a specified generator, without actually setting the hardware itself.
 *
 * \param[in] hDevice A \ref OpenDev "device handle" identifying the generator.
 * \param[in] dWidth The requested pulse width in seconds.
 * \return The pulse width that would have been set, in seconds.
 * \par Status values
 *   <table class="params">
 *   <tr><td>\ref LIBTIEPIESTATUS_VALUE_CLIPPED "VALUE_CLIPPED"</td>          <td>The requested pulse width is outside the valid range and clipped to the closest limit.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_VALUE_MODIFIED "VALUE_MODIFIED"</td>         <td>The requested pulse width is within the valid range but not available. The closest valid value is set.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_NOT_SUPPORTED "NOT_SUPPORTED"</td>          <td>The generator does not support pulse width for the current signal type.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_HANDLE "INVALID_HANDLE"</td>         <td>The handle is not a valid generator handle.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_OBJECT_GONE "OBJECT_GONE"</td>            <td>The object indicated by the handle is no longer available.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_LIBRARY_NOT_INITIALIZED "LIBRARY_NOT_INITIALIZED"</td><td>The library is not initialized, see LibInit().</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_SUCCESS "SUCCESS"</td>                <td>The function executed successfully.</td></tr>
 *   </table>
 * \see GenGetWidthMin
 * \see GenGetWidthMax
 * \see GenGetWidthMinMaxEx
 * \see GenGetWidth
 * \see GenSetWidth
 * \see GenVerifyWidthEx
 * \since 0.5
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef double(*LibTiePieGenVerifyWidth_t)( LibTiePieHandle_t hDevice , double dWidth );
#else
double GenVerifyWidth( LibTiePieHandle_t hDevice , double dWidth );
#endif

/**
 * \brief Verify if a pulse width can be set for a specific signal type and signal frequency, of a specified generator, without actually setting the hardware itself.
 *
 * \param[in] hDevice A \ref OpenDev "device handle" identifying the generator.
 * \param[in] dWidth The requested pulse width in seconds.
 * \param[in] dwSignalType The requested signal type, a \ref ST_ "ST_*" value.
 * \param[in] dSignalFrequency The requested signal frequency in Hz.
 * \return pulse width in seconds.
 * \par Status values
 *   <table class="params">
 *   <tr><td>\ref LIBTIEPIESTATUS_VALUE_CLIPPED "VALUE_CLIPPED"</td>          <td>The requested pulse width is outside the valid range and clipped to the closest limit.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_VALUE_MODIFIED "VALUE_MODIFIED"</td>         <td>The requested pulse width is within the valid range but not available. The closest valid value is set.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_VALUE "INVALID_VALUE"</td>          <td>The requested signal type and/or signal frequency is invalid.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_NOT_SUPPORTED "NOT_SUPPORTED"</td>          <td>The generator does not support pulse width for the current signal type.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_HANDLE "INVALID_HANDLE"</td>         <td>The handle is not a valid generator handle.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_OBJECT_GONE "OBJECT_GONE"</td>            <td>The object indicated by the handle is no longer available.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_LIBRARY_NOT_INITIALIZED "LIBRARY_NOT_INITIALIZED"</td><td>The library is not initialized, see LibInit().</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_SUCCESS "SUCCESS"</td>                <td>The function executed successfully.</td></tr>
 *   </table>
 * \see GenGetWidthMin
 * \see GenGetWidthMax
 * \see GenGetWidthMinMaxEx
 * \see GenGetWidth
 * \see GenSetWidth
 * \see GenVerifyWidth
 * \since 0.5
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef double(*LibTiePieGenVerifyWidthEx_t)( LibTiePieHandle_t hDevice , double dWidth , uint32_t dwSignalType , double dSignalFrequency );
#else
double GenVerifyWidthEx( LibTiePieHandle_t hDevice , double dWidth , uint32_t dwSignalType , double dSignalFrequency );
#endif

//! \endcond

/**
 * \}
 * \defgroup gen_signalEdgeTime Pulse edge time
 * \{
 * \brief Functions for controlling the signal edge times of a generator.
 *
 *           A pulse signal has a leading edge and a trailing edge.
 *           The duration of these edges can be set individually between a minimum and a maximum value.
 * \image html PulseDefinition.png
 *           For a positive pulse, the leading edge time is defined as the time it takes for the signal to go from 10% of the pulse height
 *           to 90% of the pulse height.
 *           And the trailing edge time is defined as the time it takes for the signal to go from 90% of the pulse height
 *           to 10% of the pulse height.
 *
 *           For a negative pulse, the leading edge time is defined as the time it takes for the signal to go from 90% of the pulse height
 *           to 10% of the pulse height.
 *           And the trailing edge time is defined as the time it takes for the signal to go from 10% of the pulse height
 *           to 90% of the pulse height.
 *
 *           Controlling the edge times is not available on all instruments and only available for \ref gen_signalType "signal type" Pulse.
 *           Use GenHasEdgeTime() to check whether your instrument and the current signal type of a specified generator support controlling the edge times.
 *           Use GenGetLeadingEdgeTimeMin(), GenGetLeadingEdgeTimeMax(), GenGetTrailingEdgeTimeMin() and GenGetTrailingEdgeTimeMax() to get the edge time limits.
 *           The minimum and maximum edge times depend on the currently set \ref gen_signalWidth "pulse width" and \ref gen_signalFrequency "signal frequency" (period).
 *
 *           The edge times are defined in seconds.
 *
 *           The leading edge time and trailing edge time can be affected by changing the \ref gen_signalFrequency "signal frequency" or \ref gen_signalWidth "pulse width".
 *
 *           By default the edge times are set to: 8 ns.
 */

// Workaround: Without this line Doxygen adds the documentation below to the group above.

/**
 * \brief Check whether the current signal type of a specified generator supports controlling the edge times.
 *
 * \param[in] hDevice A \ref OpenDev "device handle" identifying the generator.
 * \return #BOOL8_TRUE if supported, #BOOL8_FALSE if not.
 * \par Status values
 *   <table class="params">
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_HANDLE "INVALID_HANDLE"</td>         <td>The handle is not a valid generator handle.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_OBJECT_GONE "OBJECT_GONE"</td>            <td>The object indicated by the handle is no longer available.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_LIBRARY_NOT_INITIALIZED "LIBRARY_NOT_INITIALIZED"</td><td>The library is not initialized, see LibInit().</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_SUCCESS "SUCCESS"</td>                <td>The function executed successfully.</td></tr>
 *   </table>
 * \see GenGetLeadingEdgeTimeMin
 * \see GenGetLeadingEdgeTimeMax
 * \see GenGetLeadingEdgeTime
 * \see GenSetLeadingEdgeTime
 * \see GenGetTrailingEdgeTimeMin
 * \see GenGetTrailingEdgeTimeMax
 * \see GenGetTrailingEdgeTime
 * \see GenSetTrailingEdgeTime
 * \since 0.6
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef bool8_t(*LibTiePieGenHasEdgeTime_t)( LibTiePieHandle_t hDevice );
#else
bool8_t GenHasEdgeTime( LibTiePieHandle_t hDevice );
#endif

//! \cond EXTENDED_API

/**
 * \brief Check whether the specified generator supports controlling the edge times for a specified signal type.
 *
 * \param[in] hDevice A \ref OpenDev "device handle" identifying the generator.
 * \param[in] dwSignalType The requested signal type, a \ref ST_ "ST_*" value.
 * \return #BOOL8_TRUE if supported, #BOOL8_FALSE if not.
 * \par Status values
 *   <table class="params">
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_VALUE "INVALID_VALUE"</td>          <td>The requested signal type is invalid.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_HANDLE "INVALID_HANDLE"</td>         <td>The handle is not a valid generator handle.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_OBJECT_GONE "OBJECT_GONE"</td>            <td>The object indicated by the handle is no longer available.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_LIBRARY_NOT_INITIALIZED "LIBRARY_NOT_INITIALIZED"</td><td>The library is not initialized, see LibInit().</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_SUCCESS "SUCCESS"</td>                <td>The function executed successfully.</td></tr>
 *   </table>
 * \see GenHasEdgeTime
 * \see GenGetLeadingEdgeTimeMin
 * \see GenGetLeadingEdgeTimeMax
 * \see GenGetLeadingEdgeTimeMinMaxEx
 * \see GenGetLeadingEdgeTime
 * \see GenSetLeadingEdgeTime
 * \see GenVerifyLeadingEdgeTime
 * \see GenVerifyLeadingEdgeTimeEx
 * \see GenGetTrailingEdgeTimeMin
 * \see GenGetTrailingEdgeTimeMax
 * \see GenGetTrailingEdgeTimeMinMaxEx
 * \see GenGetTrailingEdgeTime
 * \see GenSetTrailingEdgeTime
 * \see GenVerifyTrailingEdgeTime
 * \see GenVerifyTrailingEdgeTimeEx
 * \since 0.6
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef bool8_t(*LibTiePieGenHasEdgeTimeEx_t)( LibTiePieHandle_t hDevice , uint32_t dwSignalType );
#else
bool8_t GenHasEdgeTimeEx( LibTiePieHandle_t hDevice , uint32_t dwSignalType );
#endif

//! \endcond

/**
 * \brief Get the minimum leading edge time with the current pulse width and signal frequency, of a specified generator.
 *
 * \param[in] hDevice A \ref OpenDev "device handle" identifying the generator.
 * \return The minimum leading edge time in seconds.
 * \par Status values
 *   <table class="params">
 *   <tr><td>\ref LIBTIEPIESTATUS_NOT_SUPPORTED "NOT_SUPPORTED"</td>          <td>The generator does not support edge times for the current signal type.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_HANDLE "INVALID_HANDLE"</td>         <td>The handle is not a valid generator handle.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_OBJECT_GONE "OBJECT_GONE"</td>            <td>The object indicated by the handle is no longer available.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_LIBRARY_NOT_INITIALIZED "LIBRARY_NOT_INITIALIZED"</td><td>The library is not initialized, see LibInit().</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_SUCCESS "SUCCESS"</td>                <td>The function executed successfully.</td></tr>
 *   </table>
 * \see GenHasEdgeTime
 * \see GenGetLeadingEdgeTimeMax
 * \see GenGetLeadingEdgeTime
 * \see GenSetLeadingEdgeTime
 * \see GenGetTrailingEdgeTimeMin
 * \see GenGetTrailingEdgeTimeMax
 * \see GenGetTrailingEdgeTime
 * \see GenSetTrailingEdgeTime
 * \since 0.6
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef double(*LibTiePieGenGetLeadingEdgeTimeMin_t)( LibTiePieHandle_t hDevice );
#else
double GenGetLeadingEdgeTimeMin( LibTiePieHandle_t hDevice );
#endif

/**
 * \brief Get the maximum leading edge time with the current pulse width and signal frequency, of a specified generator.
 *
 * \param[in] hDevice A \ref OpenDev "device handle" identifying the generator.
 * \return The maximum leading edge time in seconds.
 * \par Status values
 *   <table class="params">
 *   <tr><td>\ref LIBTIEPIESTATUS_NOT_SUPPORTED "NOT_SUPPORTED"</td>          <td>The generator does not support edge times for the current signal type.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_HANDLE "INVALID_HANDLE"</td>         <td>The handle is not a valid generator handle.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_OBJECT_GONE "OBJECT_GONE"</td>            <td>The object indicated by the handle is no longer available.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_LIBRARY_NOT_INITIALIZED "LIBRARY_NOT_INITIALIZED"</td><td>The library is not initialized, see LibInit().</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_SUCCESS "SUCCESS"</td>                <td>The function executed successfully.</td></tr>
 *   </table>
 * \see GenHasEdgeTime
 * \see GenGetLeadingEdgeTimeMin
 * \see GenGetLeadingEdgeTime
 * \see GenSetLeadingEdgeTime
 * \see GenGetTrailingEdgeTimeMin
 * \see GenGetTrailingEdgeTimeMax
 * \see GenGetTrailingEdgeTime
 * \see GenSetTrailingEdgeTime
 * \since 0.6
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef double(*LibTiePieGenGetLeadingEdgeTimeMax_t)( LibTiePieHandle_t hDevice );
#else
double GenGetLeadingEdgeTimeMax( LibTiePieHandle_t hDevice );
#endif

//! \cond EXTENDED_API

/**
 * \brief Get the minimum and maximum leading edge time of a specified generator with the requested signal type, frequency, symmetry, pulse width and trailing edge time.
 *
 * \param[in] hDevice A \ref OpenDev "device handle" identifying the generator.
 * \param[in] dwSignalType The requested signal type, a \ref ST_ "ST_*" value.
 * \param[in] dSignalFrequency The requested signal frequency in Hz.
 * \param[in] dSymmetry The requested signal symmetry, a number between \c 0 and \c 1.
 * \param[in] dWidth The requested pulse width in seconds.
 * \param[in] dTrailingEdgeTime The requested trailing edge time in seconds.
 * \param[out] pMin A pointer to a memory location for the minimum leading edge time, or \c NULL.
 * \param[out] pMax A pointer to a memory location for the maximum leading edge time, or \c NULL.
 * \par Status values
 *   <table class="params">
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_VALUE "INVALID_VALUE"</td>          <td>The requested signal type frequency, symmetry, pulse width and/or trailing edge time is invalid.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_HANDLE "INVALID_HANDLE"</td>         <td>The handle is not a valid generator handle.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_OBJECT_GONE "OBJECT_GONE"</td>            <td>The object indicated by the handle is no longer available.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_LIBRARY_NOT_INITIALIZED "LIBRARY_NOT_INITIALIZED"</td><td>The library is not initialized, see LibInit().</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_SUCCESS "SUCCESS"</td>                <td>The function executed successfully.</td></tr>
 *   </table>
 * \see GenHasEdgeTime
 * \see GenHasEdgeTimeEx
 * \see GenGetLeadingEdgeTimeMin
 * \see GenGetLeadingEdgeTimeMax
 * \see GenGetLeadingEdgeTime
 * \see GenSetLeadingEdgeTime
 * \see GenVerifyLeadingEdgeTime
 * \see GenVerifyLeadingEdgeTimeEx
 * \see GenGetTrailingEdgeTimeMin
 * \see GenGetTrailingEdgeTimeMax
 * \see GenGetTrailingEdgeTimeMinMaxEx
 * \see GenGetTrailingEdgeTime
 * \see GenSetTrailingEdgeTime
 * \see GenVerifyTrailingEdgeTime
 * \see GenVerifyTrailingEdgeTimeEx
 * \since 0.6
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef void(*LibTiePieGenGetLeadingEdgeTimeMinMaxEx_t)( LibTiePieHandle_t hDevice , uint32_t dwSignalType , double dSignalFrequency , double dSymmetry , double dWidth , double dTrailingEdgeTime , double* pMin , double* pMax );
#else
void GenGetLeadingEdgeTimeMinMaxEx( LibTiePieHandle_t hDevice , uint32_t dwSignalType , double dSignalFrequency , double dSymmetry , double dWidth , double dTrailingEdgeTime , double* pMin , double* pMax );
#endif

//! \endcond

/**
 * \brief Get the current leading edge time with the current pulse width and signal frequency, of a specified generator.
 *
 * \param[in] hDevice A \ref OpenDev "device handle" identifying the generator.
 * \return The currently set leading edge time in seconds.
 * \par Status values
 *   <table class="params">
 *   <tr><td>\ref LIBTIEPIESTATUS_NOT_SUPPORTED "NOT_SUPPORTED"</td>          <td>The generator does not support edge times for the current signal type.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_HANDLE "INVALID_HANDLE"</td>         <td>The handle is not a valid generator handle.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_OBJECT_GONE "OBJECT_GONE"</td>            <td>The object indicated by the handle is no longer available.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_LIBRARY_NOT_INITIALIZED "LIBRARY_NOT_INITIALIZED"</td><td>The library is not initialized, see LibInit().</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_SUCCESS "SUCCESS"</td>                <td>The function executed successfully.</td></tr>
 *   </table>
 * \see GenHasEdgeTime
 * \see GenGetLeadingEdgeTimeMin
 * \see GenGetLeadingEdgeTimeMax
 * \see GenSetLeadingEdgeTime
 * \see GenGetTrailingEdgeTimeMin
 * \see GenGetTrailingEdgeTimeMax
 * \see GenGetTrailingEdgeTime
 * \see GenSetTrailingEdgeTime
 * \since 0.6
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef double(*LibTiePieGenGetLeadingEdgeTime_t)( LibTiePieHandle_t hDevice );
#else
double GenGetLeadingEdgeTime( LibTiePieHandle_t hDevice );
#endif

/**
 * \brief Set the leading edge time, of a specified generator.
 *
 * \param[in] hDevice A \ref OpenDev "device handle" identifying the generator.
 * \param[in] dLeadingEdgeTime The requested leading edge time in seconds.
 * \return The actually set leading edge time in seconds.
 * \remark When the generator is active, changing the leading edge time will shortly interrupt the output signal.
 * \par Status values
 *   <table class="params">
 *   <tr><td>\ref LIBTIEPIESTATUS_VALUE_CLIPPED "VALUE_CLIPPED"</td>          <td>The requested edge time is outside the valid range and clipped to the closest limit.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_VALUE_MODIFIED "VALUE_MODIFIED"</td>         <td>The requested edge time is within the valid range but not available. The closest valid value is set.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_NOT_SUPPORTED "NOT_SUPPORTED"</td>          <td>The generator does not support edge times for the current signal type.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_NOT_CONTROLLABLE "NOT_CONTROLLABLE"</td>       <td>The generator is currently not controllable, see #GenIsControllable.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_HANDLE "INVALID_HANDLE"</td>         <td>The handle is not a valid generator handle.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_OBJECT_GONE "OBJECT_GONE"</td>            <td>The object indicated by the handle is no longer available.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_LIBRARY_NOT_INITIALIZED "LIBRARY_NOT_INITIALIZED"</td><td>The library is not initialized, see LibInit().</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_SUCCESS "SUCCESS"</td>                <td>The function executed successfully.</td></tr>
 *   </table>
 * \see GenHasEdgeTime
 * \see GenGetLeadingEdgeTimeMin
 * \see GenGetLeadingEdgeTimeMax
 * \see GenGetLeadingEdgeTime
 * \see GenGetTrailingEdgeTimeMin
 * \see GenGetTrailingEdgeTimeMax
 * \see GenGetTrailingEdgeTime
 * \see GenSetTrailingEdgeTime
 * \since 0.6
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef double(*LibTiePieGenSetLeadingEdgeTime_t)( LibTiePieHandle_t hDevice , double dLeadingEdgeTime );
#else
double GenSetLeadingEdgeTime( LibTiePieHandle_t hDevice , double dLeadingEdgeTime );
#endif

//! \cond EXTENDED_API

/**
 * \brief Verify if a leading edge time can be set for the current signal type and signal frequency, of a specified generator, without actually setting the hardware itself.
 *
 * \param[in] hDevice A \ref OpenDev "device handle" identifying the generator.
 * \param[in] dLeadingEdgeTime The requested leading edge time in seconds.
 * \return The leading edge time that would have been set, in seconds.
 * \par Status values
 *   <table class="params">
 *   <tr><td>\ref LIBTIEPIESTATUS_VALUE_CLIPPED "VALUE_CLIPPED"</td>          <td>The requested edge time is outside the valid range and clipped to the closest limit.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_VALUE_MODIFIED "VALUE_MODIFIED"</td>         <td>The requested edge time is within the valid range but not available. The closest valid value is set.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_NOT_SUPPORTED "NOT_SUPPORTED"</td>          <td>The generator does not support edge times for the current signal type.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_HANDLE "INVALID_HANDLE"</td>         <td>The handle is not a valid generator handle.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_OBJECT_GONE "OBJECT_GONE"</td>            <td>The object indicated by the handle is no longer available.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_LIBRARY_NOT_INITIALIZED "LIBRARY_NOT_INITIALIZED"</td><td>The library is not initialized, see LibInit().</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_SUCCESS "SUCCESS"</td>                <td>The function executed successfully.</td></tr>
 *   </table>
 * \see GenHasEdgeTime
 * \see GenHasEdgeTimeEx
 * \see GenGetLeadingEdgeTimeMin
 * \see GenGetLeadingEdgeTimeMax
 * \see GenGetLeadingEdgeTimeMinMaxEx
 * \see GenGetLeadingEdgeTime
 * \see GenSetLeadingEdgeTime
 * \see GenVerifyLeadingEdgeTimeEx
 * \see GenGetTrailingEdgeTimeMin
 * \see GenGetTrailingEdgeTimeMax
 * \see GenGetTrailingEdgeTimeMinMaxEx
 * \see GenGetTrailingEdgeTime
 * \see GenSetTrailingEdgeTime
 * \see GenVerifyTrailingEdgeTime
 * \see GenVerifyTrailingEdgeTimeEx
 * \since 0.6
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef double(*LibTiePieGenVerifyLeadingEdgeTime_t)( LibTiePieHandle_t hDevice , double dLeadingEdgeTime );
#else
double GenVerifyLeadingEdgeTime( LibTiePieHandle_t hDevice , double dLeadingEdgeTime );
#endif

/**
 * \brief Verify if a leading edge time can be set for a specified generator, with the specified signal type, frequency, symmetrym pulse width and trailing edge time, without actually setting the hardware itself.
 *
 * \param[in] hDevice A \ref OpenDev "device handle" identifying the generator.
 * \param[in] dLeadingEdgeTime The requested leading edge time in seconds.
 * \param[in] dwSignalType The requested signal type, a \ref ST_ "ST_*" value.
 * \param[in] dSignalFrequency The requested signal frequency in Hz.
 * \param[in] dSymmetry The requested signal symmetry, a number between \c 0 and \c 1.
 * \param[in] dWidth The requested pulse width in seconds.
 * \param[in] dTrailingEdgeTime The requested trailing edge time in seconds.
 * \return The leading edge time that would have been set, in seconds.
 * \par Status values
 *   <table class="params">
 *   <tr><td>\ref LIBTIEPIESTATUS_VALUE_CLIPPED "VALUE_CLIPPED"</td>          <td>The requested edge time is outside the valid range and clipped to the closest limit.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_VALUE_MODIFIED "VALUE_MODIFIED"</td>         <td>The requested edge time is within the valid range but not available. The closest valid value is set.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_NOT_SUPPORTED "NOT_SUPPORTED"</td>          <td>The generator does not support edge times for the requested signal type.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_HANDLE "INVALID_HANDLE"</td>         <td>The handle is not a valid generator handle.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_OBJECT_GONE "OBJECT_GONE"</td>            <td>The object indicated by the handle is no longer available.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_LIBRARY_NOT_INITIALIZED "LIBRARY_NOT_INITIALIZED"</td><td>The library is not initialized, see LibInit().</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_SUCCESS "SUCCESS"</td>                <td>The function executed successfully.</td></tr>
 *   </table>
 * \see GenHasEdgeTime
 * \see GenHasEdgeTimeEx
 * \see GenGetLeadingEdgeTimeMin
 * \see GenGetLeadingEdgeTimeMax
 * \see GenGetLeadingEdgeTimeMinMaxEx
 * \see GenGetLeadingEdgeTime
 * \see GenSetLeadingEdgeTime
 * \see GenVerifyLeadingEdgeTime
 * \see GenGetTrailingEdgeTimeMin
 * \see GenGetTrailingEdgeTimeMax
 * \see GenGetTrailingEdgeTimeMinMaxEx
 * \see GenGetTrailingEdgeTime
 * \see GenSetTrailingEdgeTime
 * \see GenVerifyTrailingEdgeTime
 * \see GenVerifyTrailingEdgeTimeEx
 * \since 0.6
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef double(*LibTiePieGenVerifyLeadingEdgeTimeEx_t)( LibTiePieHandle_t hDevice , double dLeadingEdgeTime , uint32_t dwSignalType , double dSignalFrequency , double dSymmetry , double dWidth , double dTrailingEdgeTime );
#else
double GenVerifyLeadingEdgeTimeEx( LibTiePieHandle_t hDevice , double dLeadingEdgeTime , uint32_t dwSignalType , double dSignalFrequency , double dSymmetry , double dWidth , double dTrailingEdgeTime );
#endif

//! \endcond

/**
 * \brief Get the minimum trailing edge time with the current pulse width and signal frequency, of a specified generator.
 *
 * \param[in] hDevice A \ref OpenDev "device handle" identifying the generator.
 * \return The minimum trailing edge time in seconds.
 * \par Status values
 *   <table class="params">
 *   <tr><td>\ref LIBTIEPIESTATUS_NOT_SUPPORTED "NOT_SUPPORTED"</td>          <td>The generator does not support edge times for the current signal type.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_HANDLE "INVALID_HANDLE"</td>         <td>The handle is not a valid generator handle.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_OBJECT_GONE "OBJECT_GONE"</td>            <td>The object indicated by the handle is no longer available.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_LIBRARY_NOT_INITIALIZED "LIBRARY_NOT_INITIALIZED"</td><td>The library is not initialized, see LibInit().</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_SUCCESS "SUCCESS"</td>                <td>The function executed successfully.</td></tr>
 *   </table>
 * \see GenHasEdgeTime
 * \see GenGetLeadingEdgeTimeMin
 * \see GenGetLeadingEdgeTimeMax
 * \see GenGetLeadingEdgeTime
 * \see GenSetLeadingEdgeTime
 * \see GenGetTrailingEdgeTimeMax
 * \see GenGetTrailingEdgeTime
 * \see GenSetTrailingEdgeTime
 * \since 0.6
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef double(*LibTiePieGenGetTrailingEdgeTimeMin_t)( LibTiePieHandle_t hDevice );
#else
double GenGetTrailingEdgeTimeMin( LibTiePieHandle_t hDevice );
#endif

/**
 * \brief Get the maximum trailing edge time with the current pulse width and signal frequency, of a specified generator.
 *
 * \param[in] hDevice A \ref OpenDev "device handle" identifying the generator.
 * \return The maximum trailing edge time in seconds.
 * \par Status values
 *   <table class="params">
 *   <tr><td>\ref LIBTIEPIESTATUS_NOT_SUPPORTED "NOT_SUPPORTED"</td>          <td>The generator does not support edge times for the current signal type.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_HANDLE "INVALID_HANDLE"</td>         <td>The handle is not a valid generator handle.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_OBJECT_GONE "OBJECT_GONE"</td>            <td>The object indicated by the handle is no longer available.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_LIBRARY_NOT_INITIALIZED "LIBRARY_NOT_INITIALIZED"</td><td>The library is not initialized, see LibInit().</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_SUCCESS "SUCCESS"</td>                <td>The function executed successfully.</td></tr>
 *   </table>
 * \see GenHasEdgeTime
 * \see GenGetLeadingEdgeTimeMin
 * \see GenGetLeadingEdgeTimeMax
 * \see GenGetLeadingEdgeTime
 * \see GenSetLeadingEdgeTime
 * \see GenGetTrailingEdgeTimeMin
 * \see GenGetTrailingEdgeTime
 * \see GenSetTrailingEdgeTime
 * \since 0.6
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef double(*LibTiePieGenGetTrailingEdgeTimeMax_t)( LibTiePieHandle_t hDevice );
#else
double GenGetTrailingEdgeTimeMax( LibTiePieHandle_t hDevice );
#endif

//! \cond EXTENDED_API

/**
 * \brief Get the minimum and maximum trailing edge time of a specified generator with the requested signal type, frequency, symmetry, pulse width and leading edge time.
 *
 * \param[in] hDevice A \ref OpenDev "device handle" identifying the generator.
 * \param[in] dwSignalType The requested signal type, a \ref ST_ "ST_*" value.
 * \param[in] dSignalFrequency The requested signal frequency in Hz.
 * \param[in] dSymmetry The requested signal symmetry, a number between \c 0 and \c 1.
 * \param[in] dWidth The requested pulse width in seconds.
 * \param[in] dLeadingEdgeTime The requested trailing edge time in seconds.
 * \param[out] pMin A pointer to a memory location for the minimum trailing edge time, or \c NULL.
 * \param[out] pMax A pointer to a memory location for the maximum trailing edge time, or \c NULL.
 * \par Status values
 *   <table class="params">
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_VALUE "INVALID_VALUE"</td>          <td>The requested signal type frequency, symmetry, pulse width and/or leading edge time is invalid.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_HANDLE "INVALID_HANDLE"</td>         <td>The handle is not a valid generator handle.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_HANDLE "INVALID_HANDLE"</td>         <td>The handle is not a valid generator handle.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_OBJECT_GONE "OBJECT_GONE"</td>            <td>The object indicated by the handle is no longer available.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_LIBRARY_NOT_INITIALIZED "LIBRARY_NOT_INITIALIZED"</td><td>The library is not initialized, see LibInit().</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_SUCCESS "SUCCESS"</td>                <td>The function executed successfully.</td></tr>
 *   </table>
 * \see GenHasEdgeTime
 * \see GenHasEdgeTimeEx
 * \see GenGetLeadingEdgeTimeMin
 * \see GenGetLeadingEdgeTimeMax
 * \see GenGetLeadingEdgeTimeMinMaxEx
 * \see GenGetLeadingEdgeTime
 * \see GenSetLeadingEdgeTime
 * \see GenVerifyLeadingEdgeTime
 * \see GenVerifyLeadingEdgeTimeEx
 * \see GenGetTrailingEdgeTimeMin
 * \see GenGetTrailingEdgeTimeMax
 * \see GenGetTrailingEdgeTime
 * \see GenSetTrailingEdgeTime
 * \see GenVerifyTrailingEdgeTime
 * \see GenVerifyTrailingEdgeTimeEx
 * \since 0.6
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef void(*LibTiePieGenGetTrailingEdgeTimeMinMaxEx_t)( LibTiePieHandle_t hDevice , uint32_t dwSignalType , double dSignalFrequency , double dSymmetry , double dWidth , double dLeadingEdgeTime , double* pMin , double* pMax );
#else
void GenGetTrailingEdgeTimeMinMaxEx( LibTiePieHandle_t hDevice , uint32_t dwSignalType , double dSignalFrequency , double dSymmetry , double dWidth , double dLeadingEdgeTime , double* pMin , double* pMax );
#endif

//! \endcond

/**
 * \brief Get the current trailing edge time with the current pulse width and signal frequency, of a specified generator.
 *
 * \param[in] hDevice A \ref OpenDev "device handle" identifying the generator.
 * \return The currently set trailing edge time in seconds.
 * \par Status values
 *   <table class="params">
 *   <tr><td>\ref LIBTIEPIESTATUS_NOT_SUPPORTED "NOT_SUPPORTED"</td>          <td>The generator does not support edge times for the current signal type.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_HANDLE "INVALID_HANDLE"</td>         <td>The handle is not a valid generator handle.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_OBJECT_GONE "OBJECT_GONE"</td>            <td>The object indicated by the handle is no longer available.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_LIBRARY_NOT_INITIALIZED "LIBRARY_NOT_INITIALIZED"</td><td>The library is not initialized, see LibInit().</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_SUCCESS "SUCCESS"</td>                <td>The function executed successfully.</td></tr>
 *   </table>
 * \see GenHasEdgeTime
 * \see GenGetLeadingEdgeTimeMin
 * \see GenGetLeadingEdgeTimeMax
 * \see GenGetLeadingEdgeTime
 * \see GenSetLeadingEdgeTime
 * \see GenGetTrailingEdgeTimeMin
 * \see GenGetTrailingEdgeTimeMax
 * \see GenSetTrailingEdgeTime
 * \since 0.6
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef double(*LibTiePieGenGetTrailingEdgeTime_t)( LibTiePieHandle_t hDevice );
#else
double GenGetTrailingEdgeTime( LibTiePieHandle_t hDevice );
#endif

/**
 * \brief Set the trailing edge time, of a specified generator.
 *
 * \param[in] hDevice A \ref OpenDev "device handle" identifying the generator.
 * \param[in] dTrailingEdgeTime The requested trailing edge time in seconds.
 * \return The actually set trailing edge time in seconds.
 * \remark When the generator is active, changing the trailing edge time will shortly interrupt the output signal.
 * \par Status values
 *   <table class="params">
 *   <tr><td>\ref LIBTIEPIESTATUS_VALUE_CLIPPED "VALUE_CLIPPED"</td>          <td>The requested edge time is outside the valid range and clipped to the closest limit.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_VALUE_MODIFIED "VALUE_MODIFIED"</td>         <td>The requested edge time is within the valid range but not available. The closest valid value is set.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_NOT_SUPPORTED "NOT_SUPPORTED"</td>          <td>The generator does not support edge times for the current signal type.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_NOT_CONTROLLABLE "NOT_CONTROLLABLE"</td>       <td>The generator is currently not controllable, see #GenIsControllable.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_HANDLE "INVALID_HANDLE"</td>         <td>The handle is not a valid generator handle.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_OBJECT_GONE "OBJECT_GONE"</td>            <td>The object indicated by the handle is no longer available.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_LIBRARY_NOT_INITIALIZED "LIBRARY_NOT_INITIALIZED"</td><td>The library is not initialized, see LibInit().</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_SUCCESS "SUCCESS"</td>                <td>The function executed successfully.</td></tr>
 *   </table>
 * \see GenHasEdgeTime
 * \see GenGetLeadingEdgeTimeMin
 * \see GenGetLeadingEdgeTimeMax
 * \see GenGetLeadingEdgeTime
 * \see GenSetLeadingEdgeTime
 * \see GenGetTrailingEdgeTimeMin
 * \see GenGetTrailingEdgeTimeMax
 * \see GenGetTrailingEdgeTime
 * \since 0.6
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef double(*LibTiePieGenSetTrailingEdgeTime_t)( LibTiePieHandle_t hDevice , double dTrailingEdgeTime );
#else
double GenSetTrailingEdgeTime( LibTiePieHandle_t hDevice , double dTrailingEdgeTime );
#endif

//! \cond EXTENDED_API

/**
 * \brief Verify if a trailing edge time can be set for the current signal type and signal frequency, of a specified generator, without actually setting the hardware itself.
 *
 * \param[in] hDevice A \ref OpenDev "device handle" identifying the generator.
 * \param[in] dTrailingEdgeTime The requested trailing edge time in seconds.
 * \return The trailing edge time that would have been set, in seconds.
 * \par Status values
 *   <table class="params">
 *   <tr><td>\ref LIBTIEPIESTATUS_VALUE_CLIPPED "VALUE_CLIPPED"</td>          <td>The requested edge time is outside the valid range and clipped to the closest limit.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_VALUE_MODIFIED "VALUE_MODIFIED"</td>         <td>The requested edge time is within the valid range but not available. The closest valid value is set.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_NOT_SUPPORTED "NOT_SUPPORTED"</td>          <td>The generator does not support edge times for the current signal type.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_HANDLE "INVALID_HANDLE"</td>         <td>The handle is not a valid generator handle.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_OBJECT_GONE "OBJECT_GONE"</td>            <td>The object indicated by the handle is no longer available.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_LIBRARY_NOT_INITIALIZED "LIBRARY_NOT_INITIALIZED"</td><td>The library is not initialized, see LibInit().</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_SUCCESS "SUCCESS"</td>                <td>The function executed successfully.</td></tr>
 *   </table>
 * \see GenHasEdgeTime
 * \see GenHasEdgeTimeEx
 * \see GenGetLeadingEdgeTimeMin
 * \see GenGetLeadingEdgeTimeMax
 * \see GenGetLeadingEdgeTimeMinMaxEx
 * \see GenGetLeadingEdgeTime
 * \see GenSetLeadingEdgeTime
 * \see GenVerifyLeadingEdgeTime
 * \see GenVerifyLeadingEdgeTimeEx
 * \see GenGetTrailingEdgeTimeMin
 * \see GenGetTrailingEdgeTimeMax
 * \see GenGetTrailingEdgeTime
 * \see GenSetTrailingEdgeTime
 * \see GenVerifyTrailingEdgeTimeEx
 * \since 0.6
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef double(*LibTiePieGenVerifyTrailingEdgeTime_t)( LibTiePieHandle_t hDevice , double dTrailingEdgeTime );
#else
double GenVerifyTrailingEdgeTime( LibTiePieHandle_t hDevice , double dTrailingEdgeTime );
#endif

/**
 * \brief Verify if a trailing edge time can be set for a specified generator, with the specified signal type, frequency, symmetrym pulse width and trailing edge time, without actually setting the hardware itself.
 *
 * \param[in] hDevice A \ref OpenDev "device handle" identifying the generator.
 * \param[in] dTrailingEdgeTime The requested trailing edge time in seconds.
 * \param[in] dwSignalType The requested signal type, a \ref ST_ "ST_*" value.
 * \param[in] dSignalFrequency The requested signal frequency in Hz.
 * \param[in] dSymmetry The requested signal symmetry, a number between \c 0 and \c 1.
 * \param[in] dWidth The requested pulse width in seconds.
 * \param[in] dLeadingEdgeTime The requested leading edge time in seconds.
 * \return The trailing edge time that would have been set, in seconds.
 * \par Status values
 *   <table class="params">
 *   <tr><td>\ref LIBTIEPIESTATUS_VALUE_CLIPPED "VALUE_CLIPPED"</td>          <td>The requested edge time is outside the valid range and clipped to the closest limit.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_VALUE_MODIFIED "VALUE_MODIFIED"</td>         <td>The requested edge time is within the valid range but not available. The closest valid value is set.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_NOT_SUPPORTED "NOT_SUPPORTED"</td>          <td>The generator does not support edge times for the requested signal type.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_HANDLE "INVALID_HANDLE"</td>         <td>The handle is not a valid generator handle.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_OBJECT_GONE "OBJECT_GONE"</td>            <td>The object indicated by the handle is no longer available.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_LIBRARY_NOT_INITIALIZED "LIBRARY_NOT_INITIALIZED"</td><td>The library is not initialized, see LibInit().</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_SUCCESS "SUCCESS"</td>                <td>The function executed successfully.</td></tr>
 *   </table>
 * \see GenHasEdgeTime
 * \see GenHasEdgeTimeEx
 * \see GenGetLeadingEdgeTimeMin
 * \see GenGetLeadingEdgeTimeMax
 * \see GenGetLeadingEdgeTimeMinMaxEx
 * \see GenGetLeadingEdgeTime
 * \see GenSetLeadingEdgeTime
 * \see GenVerifyLeadingEdgeTime
 * \see GenVerifyLeadingEdgeTimeEx
 * \see GenGetTrailingEdgeTimeMin
 * \see GenGetTrailingEdgeTimeMax
 * \see GenGetTrailingEdgeTime
 * \see GenSetTrailingEdgeTime
 * \see GenVerifyTrailingEdgeTime
 * \since 0.6
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef double(*LibTiePieGenVerifyTrailingEdgeTimeEx_t)( LibTiePieHandle_t hDevice , double dTrailingEdgeTime , uint32_t dwSignalType , double dSignalFrequency , double dSymmetry , double dWidth , double dLeadingEdgeTime );
#else
double GenVerifyTrailingEdgeTimeEx( LibTiePieHandle_t hDevice , double dTrailingEdgeTime , uint32_t dwSignalType , double dSignalFrequency , double dSymmetry , double dWidth , double dLeadingEdgeTime );
#endif

//! \endcond

/**
 * \}
 * \defgroup gen_signalData Arbitrary waveform buffer
 * \{
 * \brief Functions for controlling the arbitrary waveform buffer of a generator.
 *
 *           A generator has a buffer in which arbitrary waveform patterns can be loaded, after which the loaded pattern can be generated,
 *           when the \ref gen_signalType "signal type" is set to #ST_ARBITRARY.
 *           Waveform patterns must have a length in samples between a minimum and maximum value.
 *           Use GenGetDataLengthMin() and GenGetDataLengthMax() to get the buffer length limits in samples.
 *
 *           When the \ref gen_signalFrequencyMode "frequency mode" is set to "signal frequency", the loaded pattern is treated as one period
 *           of the signal to generate.
 *           When the \ref gen_signalFrequencyMode "frequency mode" is set to "sample frequency", the samples of the loaded pattern are generated
 *           at the set sample frequency.
 *
 *           The samples in the waveform pattern buffer represent the voltage values of the signal to generate.
 *           These sample values are unitless floating point values.
 *           Positive values represent the positive part of the signal.
 *           Negative values represent the negative part of the signal.
 *           When loading the buffer, the values in the buffer are normalized:
 *           - a value \c 0 (zero) will equal the set \ref gen_signalOffset "offset" value.
 *           - the highest absolute value will equal the set \ref gen_signalAmplitude "amplitude" value.
 *
 *           <b>Example pattern:</b>
 *
 *           <table>
 *             <tr>                    <th>Sample number</th><th>Buffer value</th><th>Generated voltage<br><small>Amplitude = 7 V<br>Offset = 0 V</small></th><th>Generated voltage<br><small>Amplitude = 4V<br>Offset = -1 V</small></th></tr>
 *             <tr class="SignalTypes"><td>            0</td><td> 0.0        </td><td> 0.0 V                                                             </td><td>-1.0 V           </td></tr>
 *             <tr class="SignalTypes"><td>            1</td><td> 0.5        </td><td> 3.5 V                                                             </td><td> 1.0 V           </td></tr>
 *             <tr class="SignalTypes"><td>            2</td><td> 1.0        </td><td> 7.0 V                                                             </td><td> 3.0 V           </td></tr>
 *             <tr class="SignalTypes"><td>            3</td><td> 0.5        </td><td> 3.5 V                                                             </td><td> 1.0 V           </td></tr>
 *             <tr class="SignalTypes"><td>            4</td><td> 0.0        </td><td> 0.0 V                                                             </td><td>-1.0 V           </td></tr>
 *             <tr class="SignalTypes"><td>            5</td><td>-0.5        </td><td>-3.5 V                                                             </td><td>-3.0 V           </td></tr>
 *             <tr class="SignalTypes"><td>            6</td><td>-1.0        </td><td>-7.0 V                                                             </td><td>-5.0 V           </td></tr>
 *             <tr class="SignalTypes"><td>            7</td><td>-0.5        </td><td>-3.5 V                                                             </td><td>-3.0 V           </td></tr>
 *           </table>
 *
 * There are a few limitations with the arbitrary waveform pattern length:
 *
 * <b>Handyscope HS5</b>: for pattern lengths larger than 128 KiSamples (131072 samples),
 * the pattern length must be a multiple of 4 samples. When the length is not a multiple of 4, the data will be resampled to the
 * closest smaller multiple of 4 samples.
 * For pattern lengths smaller than 128 KiSamples, there are no length limitations.
 *
 * <b>Handyscope HS3</b>: patterns must have a length that is a "power of 2" samples long, e.g. 1024, 2048, 4096,  etc..
 * When the length is not a power of 2, the data will be resampled to the closest larger power of 2 samples.
 *
 * When uploading patterns that get resampled, GenSetData() will set status #LIBTIEPIESTATUS_VALUE_MODIFIED.
 * Use GenGetDataLength() to determine the actually used length.
 */

// Workaround: Without this line Doxygen adds the documentation below to the group above.

/**
 * \brief Check whether the current signal type of a specified generator supports controlling the Arbitrary waveform buffer.
 *
 * \param[in] hDevice A \ref OpenDev "device handle" identifying the generator.
 * \return #BOOL8_TRUE if supported, #BOOL8_FALSE if not.
 * \par Status values
 *   <table class="params">
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_HANDLE "INVALID_HANDLE"</td>         <td>The handle is not a valid generator handle.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_OBJECT_GONE "OBJECT_GONE"</td>            <td>The object indicated by the handle is no longer available.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_LIBRARY_NOT_INITIALIZED "LIBRARY_NOT_INITIALIZED"</td><td>The library is not initialized, see LibInit().</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_SUCCESS "SUCCESS"</td>                <td>The function executed successfully.</td></tr>
 *   </table>
 * \see GenSetData
 * \since 0.6
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef bool8_t(*LibTiePieGenHasData_t)( LibTiePieHandle_t hDevice );
#else
bool8_t GenHasData( LibTiePieHandle_t hDevice );
#endif

//! \cond EXTENDED_API

/**
 * \brief Check whether the specified generator supports controlling the Arbitrary waveform buffer for a specified signal type.
 *
 * \param[in] hDevice A \ref OpenDev "device handle" identifying the generator.
 * \param[in] dwSignalType The requested signal type, a \ref ST_ "ST_*" value.
 * \return #BOOL8_TRUE if supported, #BOOL8_FALSE if not.
 * \par Status values
 *   <table class="params">
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_VALUE "INVALID_VALUE"</td>          <td>The requested signal type is invalid.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_HANDLE "INVALID_HANDLE"</td>         <td>The handle is not a valid generator handle.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_OBJECT_GONE "OBJECT_GONE"</td>            <td>The object indicated by the handle is no longer available.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_LIBRARY_NOT_INITIALIZED "LIBRARY_NOT_INITIALIZED"</td><td>The library is not initialized, see LibInit().</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_SUCCESS "SUCCESS"</td>                <td>The function executed successfully.</td></tr>
 *   </table>
 * \since 0.6
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef bool8_t(*LibTiePieGenHasDataEx_t)( LibTiePieHandle_t hDevice , uint32_t dwSignalType );
#else
bool8_t GenHasDataEx( LibTiePieHandle_t hDevice , uint32_t dwSignalType );
#endif

//! \endcond

/**
 * \brief Get the minimum length of the waveform buffer of a specified generator.
 *
 * \param[in] hDevice A \ref OpenDev "device handle" identifying the generator.
 * \return The minimum waveform buffer length in samples.
 * \par Status values
 *   <table class="params">
 *   <tr><td>\ref LIBTIEPIESTATUS_NOT_SUPPORTED "NOT_SUPPORTED"</td>          <td>The generator does not support getting the data length for the current signal type.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_HANDLE "INVALID_HANDLE"</td>         <td>The handle is not a valid generator handle.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_OBJECT_GONE "OBJECT_GONE"</td>            <td>The object indicated by the handle is no longer available.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_LIBRARY_NOT_INITIALIZED "LIBRARY_NOT_INITIALIZED"</td><td>The library is not initialized, see LibInit().</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_SUCCESS "SUCCESS"</td>                <td>The function executed successfully.</td></tr>
 *   </table>
 * \see GenGetDataLengthMax
 * \see GenGetDataLength
 * \since 0.4.2
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef uint64_t(*LibTiePieGenGetDataLengthMin_t)( LibTiePieHandle_t hDevice );
#else
uint64_t GenGetDataLengthMin( LibTiePieHandle_t hDevice );
#endif

/**
 * \brief Get the maximum length of the waveform buffer of a specified generator.
 *
 * \param[in] hDevice A \ref OpenDev "device handle" identifying the generator.
 * \return The maximum waveform buffer length in samples.
 * \par Status values
 *   <table class="params">
 *   <tr><td>\ref LIBTIEPIESTATUS_NOT_SUPPORTED "NOT_SUPPORTED"</td>          <td>The generator does not support getting the data length for the current signal type.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_HANDLE "INVALID_HANDLE"</td>         <td>The handle is not a valid generator handle.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_OBJECT_GONE "OBJECT_GONE"</td>            <td>The object indicated by the handle is no longer available.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_LIBRARY_NOT_INITIALIZED "LIBRARY_NOT_INITIALIZED"</td><td>The library is not initialized, see LibInit().</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_SUCCESS "SUCCESS"</td>                <td>The function executed successfully.</td></tr>
 *   </table>
 * \see GenGetDataLengthMin
 * \see GenGetDataLength
 * \since 0.4.0
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef uint64_t(*LibTiePieGenGetDataLengthMax_t)( LibTiePieHandle_t hDevice );
#else
uint64_t GenGetDataLengthMax( LibTiePieHandle_t hDevice );
#endif

//! \cond EXTENDED_API

/**
 * \brief Get the minimum and maximum length of the waveform buffer for a specified signal type, of a specified generator.
 *
 * \param[in] hDevice A \ref OpenDev "device handle" identifying the generator.
 * \param[in] dwSignalType The requested signal type, a \ref ST_ "ST_*" value.
 * \param[out] pMin A pointer to a memory location for the minimum data length, or \c NULL.
 * \param[out] pMax A pointer to a memory location for the maximum data length, or \c NULL.
 * \par Status values
 *   <table class="params">
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_VALUE "INVALID_VALUE"</td>          <td>The requested signal type is invalid.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_NOT_SUPPORTED "NOT_SUPPORTED"</td>          <td>The generator does not support getting the data length for the current signal type.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_HANDLE "INVALID_HANDLE"</td>         <td>The handle is not a valid generator handle.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_OBJECT_GONE "OBJECT_GONE"</td>            <td>The object indicated by the handle is no longer available.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_LIBRARY_NOT_INITIALIZED "LIBRARY_NOT_INITIALIZED"</td><td>The library is not initialized, see LibInit().</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_SUCCESS "SUCCESS"</td>                <td>The function executed successfully.</td></tr>
 *   </table>
 * \see GenGetDataLengthMin
 * \see GenGetDataLengthMax
 * \see GenGetDataLength
 * \see GenVerifyDataLength
 * \see GenVerifyDataLengthEx
 * \since 0.4.3
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef void(*LibTiePieGenGetDataLengthMinMaxEx_t)( LibTiePieHandle_t hDevice , uint32_t dwSignalType , uint64_t* pMin , uint64_t* pMax );
#else
void GenGetDataLengthMinMaxEx( LibTiePieHandle_t hDevice , uint32_t dwSignalType , uint64_t* pMin , uint64_t* pMax );
#endif

//! \endcond

/**
 * \brief Get the length of the currently loaded waveform pattern of a specified generator.
 *
 * \param[in] hDevice A \ref OpenDev "device handle" identifying the generator.
 * \return The currently set waveform pattern length in samples.
 * \par Status values
 *   <table class="params">
 *   <tr><td>\ref LIBTIEPIESTATUS_NOT_SUPPORTED "NOT_SUPPORTED"</td>          <td>The generator does not support getting the data length for the current signal type.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_HANDLE "INVALID_HANDLE"</td>         <td>The handle is not a valid generator handle.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_OBJECT_GONE "OBJECT_GONE"</td>            <td>The object indicated by the handle is no longer available.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_LIBRARY_NOT_INITIALIZED "LIBRARY_NOT_INITIALIZED"</td><td>The library is not initialized, see LibInit().</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_SUCCESS "SUCCESS"</td>                <td>The function executed successfully.</td></tr>
 *   </table>
 * \see GenGetDataLengthMin
 * \see GenGetDataLengthMax
 * \since 0.4.0
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef uint64_t(*LibTiePieGenGetDataLength_t)( LibTiePieHandle_t hDevice );
#else
uint64_t GenGetDataLength( LibTiePieHandle_t hDevice );
#endif

//! \cond EXTENDED_API

/**
 * \brief Verify if a specified length of the waveform buffer for the current signal type of a specified generator can be set, without actually setting the hardware itself.
 *
 * \param[in] hDevice A \ref OpenDev "device handle" identifying the generator.
 * \param[in] qwDataLength The requested waveform buffer length in samples.
 * \return The waveform buffer length that would have been set, in samples.
 * \par Status values
 *   <table class="params">
 *   <tr><td>\ref LIBTIEPIESTATUS_VALUE_CLIPPED "VALUE_CLIPPED"</td>          <td>The requested buffer length is outside the valid range and clipped to the closest limit.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_VALUE_MODIFIED "VALUE_MODIFIED"</td>         <td>The requested buffer length is within the valid range but not available. The closest valid value is set.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_VALUE "INVALID_VALUE"</td>          <td>The requested waveform pattern length is \c 0.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_NOT_SUPPORTED "NOT_SUPPORTED"</td>          <td>The generator does not support verifying the data length for the current signal type.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_HANDLE "INVALID_HANDLE"</td>         <td>The handle is not a valid generator handle.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_OBJECT_GONE "OBJECT_GONE"</td>            <td>The object indicated by the handle is no longer available.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_LIBRARY_NOT_INITIALIZED "LIBRARY_NOT_INITIALIZED"</td><td>The library is not initialized, see LibInit().</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_SUCCESS "SUCCESS"</td>                <td>The function executed successfully.</td></tr>
 *   </table>
 * \see GenGetDataLengthMin
 * \see GenGetDataLengthMax
 * \see GenGetDataLengthMinMaxEx
 * \see GenGetDataLength
 * \see GenVerifyDataLengthEx
 * \since 0.4.0
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef uint64_t(*LibTiePieGenVerifyDataLength_t)( LibTiePieHandle_t hDevice , uint64_t qwDataLength );
#else
uint64_t GenVerifyDataLength( LibTiePieHandle_t hDevice , uint64_t qwDataLength );
#endif

/**
 * \brief Verify if a specified length of the waveform buffer for a specified signal type of a specified generator can be set, without actually setting the hardware itself.
 *
 * \param[in] hDevice A \ref OpenDev "device handle" identifying the generator.
 * \param[in] qwDataLength The requested waveform buffer length in samples.
 * \param[in] dwSignalType The requested signal type, a \ref ST_ "ST_*" value.
 * \return Waveform buffer length in samples.
 * \par Status values
 *   <table class="params">
 *   <tr><td>\ref LIBTIEPIESTATUS_VALUE_CLIPPED "VALUE_CLIPPED"</td>          <td>The requested buffer length is outside the valid range and clipped to the closest limit.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_VALUE_MODIFIED "VALUE_MODIFIED"</td>         <td>The requested buffer length is within the valid range but not available. The closest valid value is set.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_VALUE "INVALID_VALUE"</td>          <td>The requested signal type is invalid or the requested waveform pattern length is \c 0.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_NOT_SUPPORTED "NOT_SUPPORTED"</td>          <td>The generator does not support verifying the data length for the requested signal type.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_HANDLE "INVALID_HANDLE"</td>         <td>The handle is not a valid generator handle.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_OBJECT_GONE "OBJECT_GONE"</td>            <td>The object indicated by the handle is no longer available.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_LIBRARY_NOT_INITIALIZED "LIBRARY_NOT_INITIALIZED"</td><td>The library is not initialized, see LibInit().</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_SUCCESS "SUCCESS"</td>                <td>The function executed successfully.</td></tr>
 *   </table>
 * \see GenGetDataLengthMin
 * \see GenGetDataLengthMax
 * \see GenGetDataLengthMinMaxEx
 * \see GenGetDataLength
 * \see GenVerifyDataLength
 * \since 0.4.3
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef uint64_t(*LibTiePieGenVerifyDataLengthEx_t)( LibTiePieHandle_t hDevice , uint64_t qwDataLength , uint32_t dwSignalType );
#else
uint64_t GenVerifyDataLengthEx( LibTiePieHandle_t hDevice , uint64_t qwDataLength , uint32_t dwSignalType );
#endif

//! \endcond

/**
 * \brief Load a waveform pattern into the waveform buffer of a specified generator.
 *
 * \param[in] hDevice A \ref OpenDev "device handle" identifying the generator.
 * \param[in] pBuffer A pointer to a buffer with the waveform data.
 * \param[in] qwSampleCount The number of samples in the pattern.
 * \par Status values
 *   <table class="params">
 *   <tr><td>\ref LIBTIEPIESTATUS_VALUE_MODIFIED "VALUE_MODIFIED"</td>         <td>The requested data length is not available. The data is resampled to the closest valid length.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_VALUE "INVALID_VALUE"</td>          <td>The buffer pointer is \c NULL \b or the requested waveform pattern length is \c 0.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_NOT_SUPPORTED "NOT_SUPPORTED"</td>          <td>The generator does not support uploading pattern data for the current signal type.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_UNSUCCESSFUL "UNSUCCESSFUL"</td>           <td>An error occurred during execution of the last called function.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_NOT_CONTROLLABLE "NOT_CONTROLLABLE"</td>       <td>The generator is currently not controllable, see #GenIsControllable.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_HANDLE "INVALID_HANDLE"</td>         <td>The handle is not a valid generator handle.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_OBJECT_GONE "OBJECT_GONE"</td>            <td>The object indicated by the handle is no longer available.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_LIBRARY_NOT_INITIALIZED "LIBRARY_NOT_INITIALIZED"</td><td>The library is not initialized, see LibInit().</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_SUCCESS "SUCCESS"</td>                <td>The function executed successfully.</td></tr>
 *   </table>
 * \remark \ref gen_signalType "Signal type" must be set to arbitrary mode to load a waveform pattern into the waveform buffer.
 * \remark To clear and reset the waveform buffer, call GenSetData with pBuffer = \c NULL \b and qwSampleCount = \c 0.
 * \remark When the generator is active, uploading new a waveform pattern will shortly interrupt the output signal.
 * \remark Changing the data may change the \ref GenSetBurstSegmentCount "burst segment count" if generator mode is #GM_BURST_SEGMENT_COUNT or #GM_BURST_SEGMENT_COUNT_OUTPUT.
 * \see GenGetDataLengthMin
 * \see GenGetDataLengthMax
 * \see GenGetDataLength
 * \since 0.4.0
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef void(*LibTiePieGenSetData_t)( LibTiePieHandle_t hDevice , const float* pBuffer , uint64_t qwSampleCount );
#else
void GenSetData( LibTiePieHandle_t hDevice , const float* pBuffer , uint64_t qwSampleCount );
#endif

//! \cond EXTENDED_API

/**
 * \brief Load a waveform pattern for a specified signal type into the waveform buffer of a specified generator.
 *
 * \param[in] hDevice A \ref OpenDev "device handle" identifying the generator.
 * \param[in] pBuffer A pointer to a buffer with waveform data.
 * \param[in] dwSignalType The requested signal type, a \ref ST_ "ST_*" value.
 * \param[in] dwReserved Must be set to zero.
 * \param[in] qwSampleCount The number of samples in the buffer.
 * \par Status values
 *   <table class="params">
 *   <tr><td>\ref LIBTIEPIESTATUS_VALUE_MODIFIED "VALUE_MODIFIED"</td>         <td>The requested data length is not available. The data is resampled to the closest valid length.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_NOT_SUPPORTED "NOT_SUPPORTED"</td>          <td>The generator does not support uploading pattern data for the requested signal type.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_VALUE "INVALID_VALUE"</td>          <td>The requested signal type is invalid or the requested waveform pattern length is \c 0.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_UNSUCCESSFUL "UNSUCCESSFUL"</td>           <td>An error occurred during execution of the last called function.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_NOT_CONTROLLABLE "NOT_CONTROLLABLE"</td>       <td>The generator is currently not controllable, see #GenIsControllable.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_HANDLE "INVALID_HANDLE"</td>         <td>The handle is not a valid generator handle.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_OBJECT_GONE "OBJECT_GONE"</td>            <td>The object indicated by the handle is no longer available.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_LIBRARY_NOT_INITIALIZED "LIBRARY_NOT_INITIALIZED"</td><td>The library is not initialized, see LibInit().</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_SUCCESS "SUCCESS"</td>                <td>The function executed successfully.</td></tr>
 *   </table>
 * \remark Changing the data may change the \ref GenSetBurstSegmentCount "burst segment count" if generator mode is #GM_BURST_SEGMENT_COUNT or #GM_BURST_SEGMENT_COUNT_OUTPUT.
 * \see GenGetDataLengthMin
 * \see GenGetDataLengthMax
 * \see GenGetDataLength
 * \since 0.4.3
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef void(*LibTiePieGenSetDataEx_t)( LibTiePieHandle_t hDevice , const float* pBuffer , uint64_t qwSampleCount , uint32_t dwSignalType , uint32_t dwReserved );
#else
void GenSetDataEx( LibTiePieHandle_t hDevice , const float* pBuffer , uint64_t qwSampleCount , uint32_t dwSignalType , uint32_t dwReserved );
#endif

/**
 * \defgroup gen_signalDataRaw Raw data
 * \{
 * \brief Functions for raw data.
 */

// Workaround: Without this line Doxygen adds the documentation below to the group above.

/**
 * \brief Get the raw data type of a specified generator.
 *
 * \param[in] hDevice A \ref OpenDev "device handle" identifying the generator.
 * \return The supported raw data type, a \ref DATARAWTYPE_ "DATARAWTYPE_*" value.
 * \see GenSetDataRaw
 * \since 0.4.0
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef uint32_t(*LibTiePieGenGetDataRawType_t)( LibTiePieHandle_t hDevice );
#else
uint32_t GenGetDataRawType( LibTiePieHandle_t hDevice );
#endif

/**
 * \brief Get raw data minimum, equal to zero and maximum values.
 *
 * \param[in] hDevice A \ref OpenDev "device handle" identifying the generator.
 * \param[out] pMin Pointer to buffer for possible minimum raw data value, or \c NULL.
 * \param[out] pZero Pointer to buffer for equal to zero raw data value, or \c NULL.
 * \param[out] pMax Pointer to buffer for possible maximum raw data value, or \c NULL.
 * \since 0.5
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef void(*LibTiePieGenGetDataRawValueRange_t)( LibTiePieHandle_t hDevice , int64_t* pMin , int64_t* pZero , int64_t* pMax );
#else
void GenGetDataRawValueRange( LibTiePieHandle_t hDevice , int64_t* pMin , int64_t* pZero , int64_t* pMax );
#endif

/**
 * \brief Get maximum raw data value.
 *
 * \param[in] hDevice A \ref OpenDev "device handle" identifying the generator.
 * \return Raw data value that equals \ref gen_signalOffset "offset" - \ref gen_signalAmplitude "amplitude".
 * \since 0.5
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef int64_t(*LibTiePieGenGetDataRawValueMin_t)( LibTiePieHandle_t hDevice );
#else
int64_t GenGetDataRawValueMin( LibTiePieHandle_t hDevice );
#endif

/**
 * \brief Get raw data value that equals zero.
 *
 * \param[in] hDevice A \ref OpenDev "device handle" identifying the generator.
 * \return Raw data value that equals \ref gen_signalOffset "offset".
 * \since 0.5
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef int64_t(*LibTiePieGenGetDataRawValueZero_t)( LibTiePieHandle_t hDevice );
#else
int64_t GenGetDataRawValueZero( LibTiePieHandle_t hDevice );
#endif

/**
 * \brief Get minimum raw data value.
 *
 * \param[in] hDevice A \ref OpenDev "device handle" identifying the generator.
 * \return Raw data value that equals \ref gen_signalOffset "offset" + \ref gen_signalAmplitude "amplitude".
 * \since 0.5
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef int64_t(*LibTiePieGenGetDataRawValueMax_t)( LibTiePieHandle_t hDevice );
#else
int64_t GenGetDataRawValueMax( LibTiePieHandle_t hDevice );
#endif

/**
 * \brief Load a waveform pattern into the waveform buffer of a specified generator.
 *
 * \param[in] hDevice A \ref OpenDev "device handle" identifying the generator.
 * \param[in] pBuffer Pointer to buffer with waveform data.
 * \param[in] qwSampleCount Number of samples in buffer.
 * \remark Changing the data may change the \ref GenSetBurstSegmentCount "burst segment count" if generator mode is #GM_BURST_SEGMENT_COUNT or #GM_BURST_SEGMENT_COUNT_OUTPUT.
 * \see GenGetDataRawType
 * \since 0.4.0
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef void(*LibTiePieGenSetDataRaw_t)( LibTiePieHandle_t hDevice , const void* pBuffer , uint64_t qwSampleCount );
#else
void GenSetDataRaw( LibTiePieHandle_t hDevice , const void* pBuffer , uint64_t qwSampleCount );
#endif

/**
 * \brief Load a waveform pattern into the waveform buffer of a specified generator.
 *
 * \param[in] hDevice A \ref OpenDev "device handle" identifying the generator.
 * \param[in] pBuffer Pointer to buffer with waveform data.
 * \param[in] qwSampleCount Number of samples in buffer.
 * \param[in] dwSignalType Signal type, a \ref ST_ "ST_*" value.
 * \param[in] dwReserved Must be set to zero.
 * \remark Changing the data may change the \ref GenSetBurstSegmentCount "burst segment count" if generator mode is #GM_BURST_SEGMENT_COUNT or #GM_BURST_SEGMENT_COUNT_OUTPUT.
 * \see GenGetDataRawType
 * \since 0.4.3
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef void(*LibTiePieGenSetDataRawEx_t)( LibTiePieHandle_t hDevice , const void* pBuffer , uint64_t qwSampleCount , uint32_t dwSignalType , uint32_t dwReserved );
#else
void GenSetDataRawEx( LibTiePieHandle_t hDevice , const void* pBuffer , uint64_t qwSampleCount , uint32_t dwSignalType , uint32_t dwReserved );
#endif

/**
 * \}
 */

//! \endcond

/**
 * \}
 *
 * \}
 * \defgroup gen_mode Mode
 * \{
 * \brief Functions for controlling the generator mode.
 *
 * A generator can operate in various different modes: \ref gen_continuous, \ref gen_burst or \ref gen_gated.
 * In \ref gen_continuous mode, the generator continuously generates the selected signal, until the generator is \ref GenStop "stopped".
 * In \ref gen_burst mode, the generator generates a specified number of periods of the selected signal or a specified number of
 * samples from the waveform buffer and then stops automatically.
 * In \ref gen_gated mode, the generator generates (a part of) the selected signal based on a the precence of an external signal on
 * a selected external input of the generator.
 *
 * Which generator modes are available, depends on the selected \ref gen_signalType "signal type" and \ref GenSetFrequencyMode "frequency mode".
 * Use GenGetModes() to find out which generator modes are supported for the current settings.
 * Use GenGetModesNative() to find out which generator modes are supported, regardless of the current settings.
 *
 * By default generator mode is set to continuous (#GM_CONTINUOUS).
 */

// Workaround: Without this line Doxygen adds the documentation below to the group above.

/**
 * \brief Get the supported generator modes for the current signal type and frequency mode of a specified generator.
 *
 * \param[in] hDevice A \ref OpenDev "device handle" identifying the generator.
 * \return The supported generator modes, a set of OR-ed \ref GM_ "GM_*" values or #GMM_NONE when unsuccessful.
 * \par Status values
 *   <table class="params">
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_HANDLE "INVALID_HANDLE"</td>         <td>The handle is not a valid generator handle.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_OBJECT_GONE "OBJECT_GONE"</td>            <td>The object indicated by the handle is no longer available.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_LIBRARY_NOT_INITIALIZED "LIBRARY_NOT_INITIALIZED"</td><td>The library is not initialized, see LibInit().</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_SUCCESS "SUCCESS"</td>                <td>The function executed successfully.</td></tr>
 *   </table>
 * \see GenGetModesNative
 * \see GenGetMode
 * \see GenSetMode
 * \since 0.5
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef uint64_t(*LibTiePieGenGetModes_t)( LibTiePieHandle_t hDevice );
#else
uint64_t GenGetModes( LibTiePieHandle_t hDevice );
#endif

//! \cond EXTENDED_API

/**
 * \brief Get the supported generator modes for a specified \ref gen_signalType "signal type" and \ref GenSetFrequencyMode "frequency mode" of a specified generator.
 *
 * \param[in] hDevice A \ref OpenDev "device handle" identifying the generator.
 * \param[in] dwSignalType The requested signal type, a \ref ST_ "ST_*" value.
 * \param[in] dwFrequencyMode The requested generator frequency mode, a \ref FM_ "FM_*" value. (Ignored for #ST_DC)
 * \return The supported generator modes, a set of OR-ed \ref GM_ "GM_*" values or #GMM_NONE when unsuccessful.
 * \par Status values
 *   <table class="params">
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_VALUE "INVALID_VALUE"</td>          <td>The requested signal type or frequency mode is invalid.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_HANDLE "INVALID_HANDLE"</td>         <td>The handle is not a valid generator handle.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_OBJECT_GONE "OBJECT_GONE"</td>            <td>The object indicated by the handle is no longer available.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_LIBRARY_NOT_INITIALIZED "LIBRARY_NOT_INITIALIZED"</td><td>The library is not initialized, see LibInit().</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_SUCCESS "SUCCESS"</td>                <td>The function executed successfully.</td></tr>
 *   </table>
 * \since 0.5
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef uint64_t(*LibTiePieGenGetModesEx_t)( LibTiePieHandle_t hDevice , uint32_t dwSignalType , uint32_t dwFrequencyMode );
#else
uint64_t GenGetModesEx( LibTiePieHandle_t hDevice , uint32_t dwSignalType , uint32_t dwFrequencyMode );
#endif

//! \endcond

/**
 * \brief Get all supported generator modes of a specified generator, regardless of the signal type and frequency mode.
 *
 * \param[in] hDevice A \ref OpenDev "device handle" identifying the generator.
 * \return The supported generator modes, a set of OR-ed \ref GM_ "GM_*" values or #GMM_NONE when unsuccessful.
 * \par Status values
 *   <table class="params">
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_HANDLE "INVALID_HANDLE"</td>         <td>The handle is not a valid generator handle.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_OBJECT_GONE "OBJECT_GONE"</td>            <td>The object indicated by the handle is no longer available.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_LIBRARY_NOT_INITIALIZED "LIBRARY_NOT_INITIALIZED"</td><td>The library is not initialized, see LibInit().</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_SUCCESS "SUCCESS"</td>                <td>The function executed successfully.</td></tr>
 *   </table>
 * \see GenGetModes
 * \see GenGetMode
 * \see GenSetMode
 * \since 0.5
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef uint64_t(*LibTiePieGenGetModesNative_t)( LibTiePieHandle_t hDevice );
#else
uint64_t GenGetModesNative( LibTiePieHandle_t hDevice );
#endif

/**
 * \brief Get the current generator mode of a specified generator.
 *
 * \param[in] hDevice A \ref OpenDev "device handle" identifying the generator.
 * \return The currently set generator mode, a \ref GM_ "GM_*" value, or #GMM_NONE when unsuccessful.
 * \par Status values
 *   <table class="params">
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_HANDLE "INVALID_HANDLE"</td>         <td>The handle is not a valid generator handle.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_OBJECT_GONE "OBJECT_GONE"</td>            <td>The object indicated by the handle is no longer available.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_LIBRARY_NOT_INITIALIZED "LIBRARY_NOT_INITIALIZED"</td><td>The library is not initialized, see LibInit().</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_SUCCESS "SUCCESS"</td>                <td>The function executed successfully.</td></tr>
 *   </table>
 * \see GenGetModes
 * \see GenGetModesNative
 * \see GenSetMode
 * \since 0.5
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef uint64_t(*LibTiePieGenGetMode_t)( LibTiePieHandle_t hDevice );
#else
uint64_t GenGetMode( LibTiePieHandle_t hDevice );
#endif

/**
 * \brief Set the generator mode of a specified generator.
 *
 * \param[in] hDevice A \ref OpenDev "device handle" identifying the generator.
 * \param[in] qwGeneratorMode The requested generator mode, a \ref GM_ "GM_*" value.
 * \return The actually set generator mode, a \ref GM_ "GM_*" value, or #GMM_NONE when unsuccessful.
 * \par Status values
 *   <table class="params">
 *   <tr><td>\ref LIBTIEPIESTATUS_NOT_SUPPORTED "NOT_SUPPORTED"</td>          <td>The generator does not support setting the generator mode.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_VALUE "INVALID_VALUE"</td>          <td>The requested generator mode is invalid.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_HANDLE "INVALID_HANDLE"</td>         <td>The handle is not a valid generator handle.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_OBJECT_GONE "OBJECT_GONE"</td>            <td>The object indicated by the handle is no longer available.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_LIBRARY_NOT_INITIALIZED "LIBRARY_NOT_INITIALIZED"</td><td>The library is not initialized, see LibInit().</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_SUCCESS "SUCCESS"</td>                <td>The function executed successfully.</td></tr>
 *   </table>
 * \remark The new value becomes active after a call to GenStart().
 * \see GenGetModes
 * \see GenGetModesNative
 * \see GenGetMode
 * \since 0.5
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef uint64_t(*LibTiePieGenSetMode_t)( LibTiePieHandle_t hDevice , uint64_t qwGeneratorMode );
#else
uint64_t GenSetMode( LibTiePieHandle_t hDevice , uint64_t qwGeneratorMode );
#endif

/**
 * \defgroup gen_continuous Continuous
 * \{
 * \brief Information on continuous mode.
 *
 * In continuous mode, the generator continuously generates the selected signal until the generator is stopped.
 *
 * Starting the generator is done using GenStart() or via an external trigger signal on a selected generator
 * \ref dev_trigger_input "trigger input".
 *
 * Stopping the generator is done using GenStop().
 * The current period of the signal that is being generated is not finished,
 * the output will go immediately to the selected \ref gen_signalOffset.
 *
 * \}
 * \defgroup gen_burst Burst
 * \{
 * \brief Functions for controlling burst mode.
 *
 * In burst mode, the generator generates a specified number of periods of the selected signal,
 * a specified number of samples from the waveform buffer or a segement from the waveform buffer and then stops automatically.
 *
 * Starting the generator is done using GenStart() and via an external trigger signal on a selected generator
 * \ref dev_trigger_input "trigger input".
 * For all burst modes except #GM_BURST_COUNT a generator \ref dev_trigger_input "trigger input" must be enabled.
 *
 * The following burst modes are supported:
 *
 * - #GM_BURST_COUNT :
 *   When the generator is started, or when an external trigger is enabled and the external signal becomes active, the generator generates a
 *   specified number of periods of the selected signal.
 *   When the required number of periods is reached, the generator stops automatically and the output will go to the selected \ref gen_signalOffset.
 *   When the burst is started again, the requested amount of periods is generated again.
 * - #GM_BURST_SAMPLE_COUNT :
 *   When the generator is started and the external signal becomes active, the generator generates a specified number of samples from the
 *   waveform buffer.
 *   When the required number of samples is reached, the generator automatically stops and the output will go to the selected \ref gen_signalOffset.
 *   When the burst is started again, the next requested amount of samples from the waveform buffer are generated.
 * - #GM_BURST_SAMPLE_COUNT_OUTPUT :
 *   When the generator is started and the external signal becomes active, the generator generates a specified number of samples from the
 *   waveform buffer.
 *   When the required number of samples is reached, the generator automatically stops and the output will remain at the level of the last generated sample.
 *   When the burst is started again, the next requested amount of samples from the waveform buffer are generated.
 * - #GM_BURST_SEGMENT_COUNT :
 *   The signal pattern buffer is divided in a specified number of segments.
 *   When the generator is started, each time the external signal becomes active, the generator generates the next segment,
 *   after which the generator automatically stops and the output will go to the selected \ref gen_signalOffset.
 *   When all sements have been generated, the generator will start on the first segment again, on the next activation of the external signal.
 * - #GM_BURST_SEGMENT_COUNT_OUTPUT :
 *   When the generator is started, each time the external signal becomes active, the generator generates the next segment,
 *   after which the generator automatically stops and the output will remain at the level of the last generated sample.
 *   When all sements have been generated, the generator will start on the first segment again, on the next activation of the external signal.
 *
 * By default burst count, burst sample count and burst segment count are set to their minimum values.
 */

// Workaround: Without this line Doxygen adds the documentation below to the group above.

/**
 * \brief Check whether a burst is active, of a specified generator.
 *
 * \param[in] hDevice A \ref OpenDev "device handle" identifying the generator.
 * \return #BOOL8_TRUE if a burst is active, #BOOL8_FALSE otherwise.
 * \par Status values
 *   <table class="params">
 *   <tr><td>\ref LIBTIEPIESTATUS_NOT_SUPPORTED "NOT_SUPPORTED"</td>          <td>The current generator mode does not support getting the burst status.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_HANDLE "INVALID_HANDLE"</td>         <td>The handle is not a valid generator handle.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_OBJECT_GONE "OBJECT_GONE"</td>            <td>The object indicated by the handle is no longer available.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_LIBRARY_NOT_INITIALIZED "LIBRARY_NOT_INITIALIZED"</td><td>The library is not initialized, see LibInit().</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_SUCCESS "SUCCESS"</td>                <td>The function executed successfully.</td></tr>
 *   </table>
 * \see Notification gen_notifications_burstCompleted.
 * \since 0.4.0
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef bool8_t(*LibTiePieGenIsBurstActive_t)( LibTiePieHandle_t hDevice );
#else
bool8_t GenIsBurstActive( LibTiePieHandle_t hDevice );
#endif

/**
 * \brief Get the minimum burst count for the current generator mode of a specified generator.
 *
 * \param[in] hDevice A \ref OpenDev "device handle" identifying the generator.
 * \return The minimum burst count.
 * \par Status values
 *   <table class="params">
 *   <tr><td>\ref LIBTIEPIESTATUS_NOT_SUPPORTED "NOT_SUPPORTED"</td>          <td>The generator does not support burst count in the current generator mode.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_HANDLE "INVALID_HANDLE"</td>         <td>The handle is not a valid generator handle.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_OBJECT_GONE "OBJECT_GONE"</td>            <td>The object indicated by the handle is no longer available.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_LIBRARY_NOT_INITIALIZED "LIBRARY_NOT_INITIALIZED"</td><td>The library is not initialized, see LibInit().</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_SUCCESS "SUCCESS"</td>                <td>The function executed successfully.</td></tr>
 *   </table>
 * \see GenGetBurstCountMax
 * \see GenGetBurstCount
 * \see GenSetBurstCount
 * \since 0.5
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef uint64_t(*LibTiePieGenGetBurstCountMin_t)( LibTiePieHandle_t hDevice );
#else
uint64_t GenGetBurstCountMin( LibTiePieHandle_t hDevice );
#endif

/**
 * \brief Get the maximum burst count for the current generator mode of a specified generator.
 *
 * \param[in] hDevice A \ref OpenDev "device handle" identifying the generator.
 * \return The maximum burst count.
 * \par Status values
 *   <table class="params">
 *   <tr><td>\ref LIBTIEPIESTATUS_NOT_SUPPORTED "NOT_SUPPORTED"</td>          <td>The generator does not support burst count in the current generator mode.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_HANDLE "INVALID_HANDLE"</td>         <td>The handle is not a valid generator handle.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_OBJECT_GONE "OBJECT_GONE"</td>            <td>The object indicated by the handle is no longer available.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_LIBRARY_NOT_INITIALIZED "LIBRARY_NOT_INITIALIZED"</td><td>The library is not initialized, see LibInit().</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_SUCCESS "SUCCESS"</td>                <td>The function executed successfully.</td></tr>
 *   </table>
 * \see GenGetBurstCountMin
 * \see GenGetBurstCount
 * \see GenSetBurstCount
 * \since 0.4.0
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef uint64_t(*LibTiePieGenGetBurstCountMax_t)( LibTiePieHandle_t hDevice );
#else
uint64_t GenGetBurstCountMax( LibTiePieHandle_t hDevice );
#endif

//! \cond EXTENDED_API

/**
 * \brief Get the minimum and maximum burst count for a specified generator mode, of a specified generator.
 *
 * \param[in] hDevice A \ref OpenDev "device handle" identifying the generator.
 * \param[in] qwGeneratorMode The requested generator mode, a \ref GM_ "GM_*" value.
 * \param[out] pMin A pointer to a memory location for the minimum or \c NULL.
 * \param[out] pMax A pointer to a memory location for the maximum or \c NULL.
 * \par Status values
 *   <table class="params">
 *   <tr><td>\ref LIBTIEPIESTATUS_NOT_SUPPORTED "NOT_SUPPORTED"</td>          <td>The generator does not support burst count in the requested generator mode.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_VALUE "INVALID_VALUE"</td>          <td>The requested generator mode is invalid.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_HANDLE "INVALID_HANDLE"</td>         <td>The handle is not a valid generator handle.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_OBJECT_GONE "OBJECT_GONE"</td>            <td>The object indicated by the handle is no longer available.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_LIBRARY_NOT_INITIALIZED "LIBRARY_NOT_INITIALIZED"</td><td>The library is not initialized, see LibInit().</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_SUCCESS "SUCCESS"</td>                <td>The function executed successfully.</td></tr>
 *   </table>
 * \see GenGetBurstCountMax
 * \see GenGetBurstCountMin
 * \see GenGetBurstCount
 * \see GenSetBurstCount
 * \since 0.5
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef void(*LibTiePieGenGetBurstCountMinMaxEx_t)( LibTiePieHandle_t hDevice , uint64_t qwGeneratorMode , uint64_t* pMin , uint64_t* pMax );
#else
void GenGetBurstCountMinMaxEx( LibTiePieHandle_t hDevice , uint64_t qwGeneratorMode , uint64_t* pMin , uint64_t* pMax );
#endif

//! \endcond

/**
 * \brief Get the current burst count for the current generator mode of a specified generator.
 *
 * \param[in] hDevice A \ref OpenDev "device handle" identifying the generator.
 * \return The currently set burst count.
 * \par Status values
 *   <table class="params">
 *   <tr><td>\ref LIBTIEPIESTATUS_NOT_SUPPORTED "NOT_SUPPORTED"</td>          <td>The generator does not support burst count in the current generator mode.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_HANDLE "INVALID_HANDLE"</td>         <td>The handle is not a valid generator handle.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_OBJECT_GONE "OBJECT_GONE"</td>            <td>The object indicated by the handle is no longer available.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_LIBRARY_NOT_INITIALIZED "LIBRARY_NOT_INITIALIZED"</td><td>The library is not initialized, see LibInit().</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_SUCCESS "SUCCESS"</td>                <td>The function executed successfully.</td></tr>
 *   </table>
 * \see GenGetBurstCountMax
 * \see GenGetBurstCountMin
 * \see GenSetBurstCount
 * \since 0.4.0
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef uint64_t(*LibTiePieGenGetBurstCount_t)( LibTiePieHandle_t hDevice );
#else
uint64_t GenGetBurstCount( LibTiePieHandle_t hDevice );
#endif

/**
 * \brief Set the burst count for the current generator mode of a specified generator.
 *
 * \param[in] hDevice A \ref OpenDev "device handle" identifying the generator.
 * \param[in] qwBurstCount The requested burst count, <tt>GenGetBurstCountMin()</tt> to <tt>GenGetBurstCountMax()</tt>.
 * \return The actually set burst count.
 * \remark The new value becomes active after a call to GenStart().
 * \par Status values
 *   <table class="params">
 *   <tr><td>\ref LIBTIEPIESTATUS_VALUE_CLIPPED "VALUE_CLIPPED"</td>          <td>The requested burst count is outside the valid range and clipped to that range.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_VALUE "INVALID_VALUE"</td>          <td>The requested burst count is invalid.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_NOT_SUPPORTED "NOT_SUPPORTED"</td>          <td>The generator does not support burst count in the current generator mode.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_HANDLE "INVALID_HANDLE"</td>         <td>The handle is not a valid generator handle.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_OBJECT_GONE "OBJECT_GONE"</td>            <td>The object indicated by the handle is no longer available.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_LIBRARY_NOT_INITIALIZED "LIBRARY_NOT_INITIALIZED"</td><td>The library is not initialized, see LibInit().</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_SUCCESS "SUCCESS"</td>                <td>The function executed successfully.</td></tr>
 *   </table>
 * \see GenGetBurstCountMax
 * \see GenGetBurstCountMin
 * \see GenGetBurstCount
 * \since 0.4.0
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef uint64_t(*LibTiePieGenSetBurstCount_t)( LibTiePieHandle_t hDevice , uint64_t qwBurstCount );
#else
uint64_t GenSetBurstCount( LibTiePieHandle_t hDevice , uint64_t qwBurstCount );
#endif

/**
 * \brief Get the minimum burst sample count for the current generator mode of a specified generator.
 *
 * \param[in] hDevice A \ref OpenDev "device handle" identifying the generator.
 * \return The minimum burst sample count.
 * \par Status values
 *   <table class="params">
 *   <tr><td>\ref LIBTIEPIESTATUS_NOT_SUPPORTED "NOT_SUPPORTED"</td>          <td>The generator does not support burst sample count in the current generator mode.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_HANDLE "INVALID_HANDLE"</td>         <td>The handle is not a valid generator handle.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_OBJECT_GONE "OBJECT_GONE"</td>            <td>The object indicated by the handle is no longer available.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_LIBRARY_NOT_INITIALIZED "LIBRARY_NOT_INITIALIZED"</td><td>The library is not initialized, see LibInit().</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_SUCCESS "SUCCESS"</td>                <td>The function executed successfully.</td></tr>
 *   </table>
 * \see GenGetBurstSampleCountMax
 * \see GenGetBurstSampleCount
 * \see GenSetBurstSampleCount
 * \since 0.5
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef uint64_t(*LibTiePieGenGetBurstSampleCountMin_t)( LibTiePieHandle_t hDevice );
#else
uint64_t GenGetBurstSampleCountMin( LibTiePieHandle_t hDevice );
#endif

/**
 * \brief Get the maximum burst sample count for the current generator mode of a specified generator.
 *
 * \param[in] hDevice A \ref OpenDev "device handle" identifying the generator.
 * \return The maximum burst sample count.
 * \par Status values
 *   <table class="params">
 *   <tr><td>\ref LIBTIEPIESTATUS_NOT_SUPPORTED "NOT_SUPPORTED"</td>          <td>The generator does not support burst sample count in the current generator mode.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_HANDLE "INVALID_HANDLE"</td>         <td>The handle is not a valid generator handle.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_OBJECT_GONE "OBJECT_GONE"</td>            <td>The object indicated by the handle is no longer available.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_LIBRARY_NOT_INITIALIZED "LIBRARY_NOT_INITIALIZED"</td><td>The library is not initialized, see LibInit().</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_SUCCESS "SUCCESS"</td>                <td>The function executed successfully.</td></tr>
 *   </table>
 * \see GenGetBurstSampleCountMin
 * \see GenGetBurstSampleCount
 * \see GenSetBurstSampleCount
 * \since 0.5
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef uint64_t(*LibTiePieGenGetBurstSampleCountMax_t)( LibTiePieHandle_t hDevice );
#else
uint64_t GenGetBurstSampleCountMax( LibTiePieHandle_t hDevice );
#endif

//! \cond EXTENDED_API

/**
 * \brief Get the minimum and maximum burst sample count for a specified generator mode, of a specified generator.
 *
 * \param[in] hDevice A \ref OpenDev "device handle" identifying the generator.
 * \param[in] qwGeneratorMode The requested generator mode, a \ref GM_ "GM_*" value.
 * \param[out] pMin A pointer to a memory location for the minimum or \c NULL.
 * \param[out] pMax A pointer to a memory location for the maximum or \c NULL.
 * \par Status values
 *   <table class="params">
 *   <tr><td>\ref LIBTIEPIESTATUS_NOT_SUPPORTED "NOT_SUPPORTED"</td>          <td>The generator does not support burst sample count in the specified generator mode.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_VALUE "INVALID_VALUE"</td>          <td>The requested generator mode is invalid.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_HANDLE "INVALID_HANDLE"</td>         <td>The handle is not a valid generator handle.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_OBJECT_GONE "OBJECT_GONE"</td>            <td>The object indicated by the handle is no longer available.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_LIBRARY_NOT_INITIALIZED "LIBRARY_NOT_INITIALIZED"</td><td>The library is not initialized, see LibInit().</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_SUCCESS "SUCCESS"</td>                <td>The function executed successfully.</td></tr>
 *   </table>
 * \see GenGetBurstSampleCountMin
 * \see GenGetBurstSampleCountMax
 * \see GenGetBurstSampleCount
 * \see GenSetBurstSampleCount
 * \since 0.5
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef void(*LibTiePieGenGetBurstSampleCountMinMaxEx_t)( LibTiePieHandle_t hDevice , uint64_t qwGeneratorMode , uint64_t* pMin , uint64_t* pMax );
#else
void GenGetBurstSampleCountMinMaxEx( LibTiePieHandle_t hDevice , uint64_t qwGeneratorMode , uint64_t* pMin , uint64_t* pMax );
#endif

//! \endcond

/**
 * \brief Get the current burst sample count for the current generator mode of a specified generator.
 *
 * \param[in] hDevice A \ref OpenDev "device handle" identifying the generator.
 * \return The currently set burst sample count.
 * \par Status values
 *   <table class="params">
 *   <tr><td>\ref LIBTIEPIESTATUS_NOT_SUPPORTED "NOT_SUPPORTED"</td>          <td>The generator does not support burst sample count in the current generator mode.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_HANDLE "INVALID_HANDLE"</td>         <td>The handle is not a valid generator handle.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_OBJECT_GONE "OBJECT_GONE"</td>            <td>The object indicated by the handle is no longer available.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_LIBRARY_NOT_INITIALIZED "LIBRARY_NOT_INITIALIZED"</td><td>The library is not initialized, see LibInit().</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_SUCCESS "SUCCESS"</td>                <td>The function executed successfully.</td></tr>
 *   </table>
 * \see GenGetBurstSampleCountMin
 * \see GenGetBurstSampleCountMax
 * \see GenSetBurstSampleCount
 * \since 0.5
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef uint64_t(*LibTiePieGenGetBurstSampleCount_t)( LibTiePieHandle_t hDevice );
#else
uint64_t GenGetBurstSampleCount( LibTiePieHandle_t hDevice );
#endif

/**
 * \brief Set the burst sample count for the current generator mode of a specified generator.
 *
 * \param[in] hDevice A \ref OpenDev "device handle" identifying the generator.
 * \param[in] qwBurstSampleCount The requested burst sample count, <tt>GenGetBurstSampleCountMin()</tt> to <tt>GenGetBurstSampleCountMax()</tt>.
 * \return The actually set burst sample count.
 * \remark The new value becomes active after a call to GenStart().
 * \par Status values
 *   <table class="params">
 *   <tr><td>\ref LIBTIEPIESTATUS_VALUE_CLIPPED "VALUE_CLIPPED"</td>          <td>The requested burst sample count is outside the valid range and clipped to that range.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_VALUE "INVALID_VALUE"</td>          <td>The requested burst sample count is invalid.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_NOT_SUPPORTED "NOT_SUPPORTED"</td>          <td>The generator does not support burst sample count in the current generator mode.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_HANDLE "INVALID_HANDLE"</td>         <td>The handle is not a valid generator handle.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_OBJECT_GONE "OBJECT_GONE"</td>            <td>The object indicated by the handle is no longer available.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_LIBRARY_NOT_INITIALIZED "LIBRARY_NOT_INITIALIZED"</td><td>The library is not initialized, see LibInit().</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_SUCCESS "SUCCESS"</td>                <td>The function executed successfully.</td></tr>
 *   </table>
 * \see GenGetBurstSampleCountMin
 * \see GenGetBurstSampleCountMax
 * \see GenGetBurstSampleCount
 * \since 0.5
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef uint64_t(*LibTiePieGenSetBurstSampleCount_t)( LibTiePieHandle_t hDevice , uint64_t qwBurstSampleCount );
#else
uint64_t GenSetBurstSampleCount( LibTiePieHandle_t hDevice , uint64_t qwBurstSampleCount );
#endif

/**
 * \brief Get the minimum burst segment count for the current settings of a specified generator.
 *
 * \param[in] hDevice A \ref OpenDev "device handle" identifying the generator.
 * \return The minimum burst segment count.
 * \par Status values
 *   <table class="params">
 *   <tr><td>\ref LIBTIEPIESTATUS_NOT_SUPPORTED "NOT_SUPPORTED"</td>          <td>The generator does not support burst segment count in the current generator mode.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_HANDLE "INVALID_HANDLE"</td>         <td>The handle is not a valid generator handle.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_OBJECT_GONE "OBJECT_GONE"</td>            <td>The object indicated by the handle is no longer available.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_LIBRARY_NOT_INITIALIZED "LIBRARY_NOT_INITIALIZED"</td><td>The library is not initialized, see LibInit().</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_SUCCESS "SUCCESS"</td>                <td>The function executed successfully.</td></tr>
 *   </table>
 * \see GenGetBurstSegmentCountMax
 * \see GenGetBurstSegmentCount
 * \see GenSetBurstSegmentCount
 * \since 0.5
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef uint64_t(*LibTiePieGenGetBurstSegmentCountMin_t)( LibTiePieHandle_t hDevice );
#else
uint64_t GenGetBurstSegmentCountMin( LibTiePieHandle_t hDevice );
#endif

/**
 * \brief Get the maximum burst segment count for the current settings of a specified generator.
 *
 * \param[in] hDevice A \ref OpenDev "device handle" identifying the generator.
 * \return The maximum burst segment count.
 * \par Status values
 *   <table class="params">
 *   <tr><td>\ref LIBTIEPIESTATUS_NOT_SUPPORTED "NOT_SUPPORTED"</td>          <td>The generator does not support burst segment count in the current generator mode.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_HANDLE "INVALID_HANDLE"</td>         <td>The handle is not a valid generator handle.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_OBJECT_GONE "OBJECT_GONE"</td>            <td>The object indicated by the handle is no longer available.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_LIBRARY_NOT_INITIALIZED "LIBRARY_NOT_INITIALIZED"</td><td>The library is not initialized, see LibInit().</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_SUCCESS "SUCCESS"</td>                <td>The function executed successfully.</td></tr>
 *   </table>
 * \see GenGetBurstSegmentCountMin
 * \see GenGetBurstSegmentCount
 * \see GenSetBurstSegmentCount
 * \since 0.5
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef uint64_t(*LibTiePieGenGetBurstSegmentCountMax_t)( LibTiePieHandle_t hDevice );
#else
uint64_t GenGetBurstSegmentCountMax( LibTiePieHandle_t hDevice );
#endif

//! \cond EXTENDED_API

/**
 * \brief Get the minimum and maximum burst segment count for a specified generator mode, signal type, frequency mode, frequency and data length, of a specified generator.
 *
 * \param[in] hDevice A \ref OpenDev "device handle" identifying the generator.
 * \param[in] qwGeneratorMode The requested generator mode, a \ref GM_ "GM_*" value.
 * \param[in] dwSignalType The requested signal type, a \ref ST_ "ST_*" value.
 * \param[in] dwFrequencyMode The requested frequency mode, a \ref FM_ "FM_*" value. (Ignored for #ST_DC)
 * \param[in] dFrequency The requested frequency in Hz.
 * \param[in] qwDataLength The requested data length in samples, only for #ST_ARBITRARY.
 * \param[out] pMin A pointer to a memory location for the minimum or \c NULL.
 * \param[out] pMax A pointer to a memory location for the maximum or \c NULL.
 * \par Status values
 *   <table class="params">
 *   <tr><td>\ref LIBTIEPIESTATUS_NOT_SUPPORTED "NOT_SUPPORTED"</td>          <td>The generator does not support burst segment count in the current generator mode.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_VALUE "INVALID_VALUE"</td>          <td>The requested generator mode, signal type, frequency mode, frequency or data length is invalid.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_HANDLE "INVALID_HANDLE"</td>         <td>The handle is not a valid generator handle.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_OBJECT_GONE "OBJECT_GONE"</td>            <td>The object indicated by the handle is no longer available.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_LIBRARY_NOT_INITIALIZED "LIBRARY_NOT_INITIALIZED"</td><td>The library is not initialized, see LibInit().</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_SUCCESS "SUCCESS"</td>                <td>The function executed successfully.</td></tr>
 *   </table>
 * \see GenGetBurstSegmentCountMin
 * \see GenGetBurstSegmentCountMax
 * \see GenGetBurstSegmentCount
 * \see GenSetBurstSegmentCount
 * \since 0.5
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef void(*LibTiePieGenGetBurstSegmentCountMinMaxEx_t)( LibTiePieHandle_t hDevice , uint64_t qwGeneratorMode , uint32_t dwSignalType , uint32_t dwFrequencyMode , double dFrequency , uint64_t qwDataLength , uint64_t* pMin , uint64_t* pMax );
#else
void GenGetBurstSegmentCountMinMaxEx( LibTiePieHandle_t hDevice , uint64_t qwGeneratorMode , uint32_t dwSignalType , uint32_t dwFrequencyMode , double dFrequency , uint64_t qwDataLength , uint64_t* pMin , uint64_t* pMax );
#endif

//! \endcond

/**
 * \brief Get the current burst segment count of a specified generator.
 *
 * \param[in] hDevice A \ref OpenDev "device handle" identifying the generator.
 * \return The currently set burst segment count.
 * \par Status values
 *   <table class="params">
 *   <tr><td>\ref LIBTIEPIESTATUS_NOT_SUPPORTED "NOT_SUPPORTED"</td>          <td>The generator does not support burst segment count in the current generator mode.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_HANDLE "INVALID_HANDLE"</td>         <td>The handle is not a valid generator handle.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_OBJECT_GONE "OBJECT_GONE"</td>            <td>The object indicated by the handle is no longer available.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_LIBRARY_NOT_INITIALIZED "LIBRARY_NOT_INITIALIZED"</td><td>The library is not initialized, see LibInit().</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_SUCCESS "SUCCESS"</td>                <td>The function executed successfully.</td></tr>
 *   </table>
 * \see GenGetBurstSegmentCountMin
 * \see GenGetBurstSegmentCountMax
 * \see GenSetBurstSegmentCount
 * \since 0.5
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef uint64_t(*LibTiePieGenGetBurstSegmentCount_t)( LibTiePieHandle_t hDevice );
#else
uint64_t GenGetBurstSegmentCount( LibTiePieHandle_t hDevice );
#endif

/**
 * \brief Set the burst segment count of a specified generator.
 *
 * \param[in] hDevice A \ref OpenDev "device handle" identifying the generator.
 * \param[in] qwBurstSegmentCount The requested burst segment count, <tt>GenGetBurstSegmentCountMin()</tt> to <tt>GenGetBurstSegmentCountMax()</tt>.
 * \return The actually set burst segment count.
 * \par Status values
 *   <table class="params">
 *   <tr><td>\ref LIBTIEPIESTATUS_VALUE_CLIPPED "VALUE_CLIPPED"</td>          <td>The requested burst segment count is outside the valid range and clipped to that range.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_VALUE_MODIFIED "VALUE_MODIFIED"</td>         <td>The requested burst sample count is inside the valid range but not available. The closest valid value is set.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_VALUE "INVALID_VALUE"</td>          <td>The requested burst segment count is invalid.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_NOT_SUPPORTED "NOT_SUPPORTED"</td>          <td>The generator does not support burst segment count in the current generator mode.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_HANDLE "INVALID_HANDLE"</td>         <td>The handle is not a valid generator handle.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_OBJECT_GONE "OBJECT_GONE"</td>            <td>The object indicated by the handle is no longer available.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_LIBRARY_NOT_INITIALIZED "LIBRARY_NOT_INITIALIZED"</td><td>The library is not initialized, see LibInit().</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_SUCCESS "SUCCESS"</td>                <td>The function executed successfully.</td></tr>
 *   </table>
 * \see GenGetBurstSegmentCountMin
 * \see GenGetBurstSegmentCountMax
 * \see GenGetBurstSegmentCount
 * \since 0.5
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef uint64_t(*LibTiePieGenSetBurstSegmentCount_t)( LibTiePieHandle_t hDevice , uint64_t qwBurstSegmentCount );
#else
uint64_t GenSetBurstSegmentCount( LibTiePieHandle_t hDevice , uint64_t qwBurstSegmentCount );
#endif

//! \cond EXTENDED_API

/**
 * \brief Verify if a burst segment count of a specified generator can be set, without actually setting the hardware itself.
 *
 * \param[in] hDevice A \ref OpenDev "device handle" identifying the generator.
 * \param[in] qwBurstSegmentCount The requested burst segment count.
 * \return The burst segment count that would have been set.
 * \par Status values
 *   <table class="params">
 *   <tr><td>\ref LIBTIEPIESTATUS_VALUE_CLIPPED "VALUE_CLIPPED"</td>          <td>The requested burst segment count is outside the valid range and clipped to that range.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_VALUE_MODIFIED "VALUE_MODIFIED"</td>         <td>The requested burst sample count is inside the valid range but not available. The closest valid value is set.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_NOT_SUPPORTED "NOT_SUPPORTED"</td>          <td>The generator does not support burst segment count in the current generator mode.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_HANDLE "INVALID_HANDLE"</td>         <td>The handle is not a valid generator handle.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_OBJECT_GONE "OBJECT_GONE"</td>            <td>The object indicated by the handle is no longer available.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_LIBRARY_NOT_INITIALIZED "LIBRARY_NOT_INITIALIZED"</td><td>The library is not initialized, see LibInit().</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_SUCCESS "SUCCESS"</td>                <td>The function executed successfully.</td></tr>
 *   </table>
 * \see GenGetBurstSegmentCountMin
 * \see GenGetBurstSegmentCountMax
 * \see GenGetBurstSegmentCount
 * \see GenSetBurstSegmentCount
 * \see GenVerifyBurstSegmentCountEx
 * \since 0.5
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef uint64_t(*LibTiePieGenVerifyBurstSegmentCount_t)( LibTiePieHandle_t hDevice , uint64_t qwBurstSegmentCount );
#else
uint64_t GenVerifyBurstSegmentCount( LibTiePieHandle_t hDevice , uint64_t qwBurstSegmentCount );
#endif

/**
 * \brief Verify if a burst segment count for the specified generator mode, signal type, frequency mode, frequency and data length of a specified generator can be set, without actually setting the hardware.
 *
 * \param[in] hDevice A \ref OpenDev "device handle" identifying the generator.
 * \param[in] qwBurstSegmentCount The requested burst segment count.
 * \param[in] qwGeneratorMode The requested generator mode, a \ref GM_ "GM_*" value.
 * \param[in] dwSignalType The requested signal type, a \ref ST_ "ST_*" value.
 * \param[in] dwFrequencyMode The requested frequency mode, a \ref FM_ "FM_*" value. (Ignored for #ST_DC)
 * \param[in] dFrequency The requested frequency in Hz.
 * \param[in] qwDataLength The requested data length in samples, only for #ST_ARBITRARY.
 * \return The burst segment count that would have been set.
 * \par Status values
 *   <table class="params">
 *   <tr><td>\ref LIBTIEPIESTATUS_VALUE_CLIPPED "VALUE_CLIPPED"</td>          <td>The requested burst segment count is outside the valid range and clipped to that range.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_VALUE_MODIFIED "VALUE_MODIFIED"</td>         <td>The requested burst sample count is inside the valid range but not available. The closest valid value is set.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_VALUE "INVALID_VALUE"</td>          <td>The requested burst segment count, generator mode, signal type, frequency mode, frequency or data length is invalid.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_NOT_SUPPORTED "NOT_SUPPORTED"</td>          <td>The generator does not support burst segment count in the current generator mode.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_HANDLE "INVALID_HANDLE"</td>         <td>The handle is not a valid generator handle.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_OBJECT_GONE "OBJECT_GONE"</td>            <td>The object indicated by the handle is no longer available.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_LIBRARY_NOT_INITIALIZED "LIBRARY_NOT_INITIALIZED"</td><td>The library is not initialized, see LibInit().</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_SUCCESS "SUCCESS"</td>                <td>The function executed successfully.</td></tr>
 *   </table>
 * \see GenGetBurstSegmentCountMin
 * \see GenGetBurstSegmentCountMax
 * \see GenGetBurstSegmentCount
 * \see GenSetBurstSegmentCount
 * \see GenVerifyBurstSegmentCount
 * \since 0.5
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef uint64_t(*LibTiePieGenVerifyBurstSegmentCountEx_t)( LibTiePieHandle_t hDevice , uint64_t qwBurstSegmentCount , uint64_t qwGeneratorMode , uint32_t dwSignalType , uint32_t dwFrequencyMode , double dFrequency , uint64_t qwDataLength );
#else
uint64_t GenVerifyBurstSegmentCountEx( LibTiePieHandle_t hDevice , uint64_t qwBurstSegmentCount , uint64_t qwGeneratorMode , uint32_t dwSignalType , uint32_t dwFrequencyMode , double dFrequency , uint64_t qwDataLength );
#endif

//! \endcond

/**
 * \}
 * \defgroup gen_gated Gated
 * \{
 * \brief Information on gated mode.
 *
 *  In gated mode, the generator generates (a part of) the selected signal based on the presence of an external signal on a selected
 * \ref dev_trigger_input "trigger input" of the generator.
 *
 * Starting the generator is done using GenStart().

 * A generator \ref dev_trigger_input "trigger input" must be enabled.
 *
 * The following gated modes are supported:
 *
 * - #GM_GATED :
 *   When the generator is started, signal generation is started, but the output remains at the selected
 * \ref gen_signalOffset "offset level" until the selected external input signal becomes active.
 *   When the external input signal becomes inactive again, the output goes to the selected offset level again.
 * - #GM_GATED_PERIODS :
 *   After the generator is started, signal generation is started at a new period when the selected external input signal becomes active.
 *   When the external input signal becomes inactive again, the current period is finalized, signal generation stops and the output goes to the
 *   selected \ref gen_signalOffset.
 * - #GM_GATED_PERIOD_START :
 *   After  the generator is started, signal generation is started at a new period when selected external input signal becomes active.
 *   When the external input signal becomes inactive again, signal generation immediately stops and the output goes to the selected \ref gen_signalOffset.
 * - #GM_GATED_PERIOD_FINISH :
 *   When the generator is started, signal generation is started, but the output remains at the selected
 * \ref gen_signalOffset "offset level" until the selected external input signal becomes active.
 *   When the external input signal becomes inactive again, the current period is finalized and then the generator stops and the output goes to the
 *   selected \ref gen_signalOffset.
 * - #GM_GATED_RUN :
 *   After the generator is started, signal generation is started at a new period when the selected external input signal becomes active.
 *   When the external input signal becomes inactive again, signal generation is paused and the output goes to the selected \ref gen_signalOffset.
 * - #GM_GATED_RUN_OUTPUT :
 *   After the generator is started, signal generation is started at a new period when the selected external input signal becomes active.
 *   When the external input signal becomes inactive again, signal generation is paused and the output will remain at the level of the last generated sample.
 *
 * \}
 * \}
 * \defgroup gen_notifications Notifications
 * \{
 * \brief Functions to set notifications that are triggered when the generator status is changed.
 *
 * \defgroup gen_notifications_burstCompleted Burst completed
 * \{
 * \brief Functions to set notifications that are triggered when a generator burst is completed.
 */

// Workaround: Without this line Doxygen adds the documentation below to the group above.

/**
 * \deprecated Will be removed in future version, see: ObjSetEventCallback()
 * \brief Set a callback function which is called when the generator burst is completed.
 *
 * \param[in] hDevice A \ref OpenDev "device handle" identifying the generator.
 * \param[in] pCallback A pointer to the callback function. Use \c NULL to disable.
 * \param[in] pData Optional user data.
 * \par Status values
 *   <table class="params">
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_HANDLE "INVALID_HANDLE"</td>         <td>The handle is not a valid generator handle.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_OBJECT_GONE "OBJECT_GONE"</td>            <td>The object indicated by the handle is no longer available.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_LIBRARY_NOT_INITIALIZED "LIBRARY_NOT_INITIALIZED"</td><td>The library is not initialized, see LibInit().</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_SUCCESS "SUCCESS"</td>                <td>The function executed successfully.</td></tr>
 *   </table>
 * \see GenIsBurstActive
 * \since 0.4.0
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef void(*LibTiePieGenSetCallbackBurstCompleted_t)( LibTiePieHandle_t hDevice , TpCallback_t pCallback , void* pData );
#else
void GenSetCallbackBurstCompleted( LibTiePieHandle_t hDevice , TpCallback_t pCallback , void* pData );
#endif

#ifdef LIBTIEPIE_LINUX

/**
 * \deprecated Will be removed in future version, see: ObjSetEventEvent()
 * \brief Set an event file descriptor which is set when the generator burst is completed.
 *
 * \param[in] hDevice A \ref OpenDev "device handle" identifying the generator.
 * \param[in] fdEvent An event file descriptor. Use \c <0 to disable.
 * \note This function is only available on GNU/Linux.
 * \par Status values
 *   <table class="params">
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_HANDLE "INVALID_HANDLE"</td>         <td>The handle is not a valid generator handle.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_OBJECT_GONE "OBJECT_GONE"</td>            <td>The object indicated by the handle is no longer available.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_LIBRARY_NOT_INITIALIZED "LIBRARY_NOT_INITIALIZED"</td><td>The library is not initialized, see LibInit().</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_SUCCESS "SUCCESS"</td>                <td>The function executed successfully.</td></tr>
 *   </table>
 * \see GenIsBurstActive
 * \since 0.4.0
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef void(*LibTiePieGenSetEventBurstCompleted_t)( LibTiePieHandle_t hDevice , int fdEvent );
#else
void GenSetEventBurstCompleted( LibTiePieHandle_t hDevice , int fdEvent );
#endif

#endif

#ifdef LIBTIEPIE_WINDOWS

/**
 * \deprecated Will be removed in future version, see: ObjSetEventEvent()
 * \brief Set an event object handle which is set when the generator burst is completed.
 *
 * \param[in] hDevice A \ref OpenDev "device handle" identifying the generator.
 * \param[in] hEvent A handle to the event object. Use \c NULL to disable.
 * \note This function is only available on Windows.
 * \par Status values
 *   <table class="params">
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_HANDLE "INVALID_HANDLE"</td>         <td>The handle is not a valid generator handle.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_OBJECT_GONE "OBJECT_GONE"</td>            <td>The object indicated by the handle is no longer available.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_LIBRARY_NOT_INITIALIZED "LIBRARY_NOT_INITIALIZED"</td><td>The library is not initialized, see LibInit().</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_SUCCESS "SUCCESS"</td>                <td>The function executed successfully.</td></tr>
 *   </table>
 * \see GenIsBurstActive
 * \since 0.4.0
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef void(*LibTiePieGenSetEventBurstCompleted_t)( LibTiePieHandle_t hDevice , HANDLE hEvent );
#else
void GenSetEventBurstCompleted( LibTiePieHandle_t hDevice , HANDLE hEvent );
#endif

/**
 * \deprecated Will be removed in future version, see: ObjSetEventWindowHandle()
 * \brief Set a window handle to which a #WM_LIBTIEPIE_GEN_BURSTCOMPLETED message is sent when the generator burst is completed.
 *
 * \param[in] hDevice A \ref OpenDev "device handle" identifying the generator.
 * \param[in] hWnd A handle to the window whose window procedure is to receive the message. Use \c NULL to disable.
 * \param[in] wParam Optional user value for the \c wParam parameter of the message.
 * \param[in] lParam Optional user value for the \c lParam parameter of the message.
 * \note This function is only available on Windows.
 * \par Status values
 *   <table class="params">
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_HANDLE "INVALID_HANDLE"</td>         <td>The handle is not a valid generator handle.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_OBJECT_GONE "OBJECT_GONE"</td>            <td>The object indicated by the handle is no longer available.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_LIBRARY_NOT_INITIALIZED "LIBRARY_NOT_INITIALIZED"</td><td>The library is not initialized, see LibInit().</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_SUCCESS "SUCCESS"</td>                <td>The function executed successfully.</td></tr>
 *   </table>
 * \see GenIsBurstActive
 * \since 0.4.0
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef void(*LibTiePieGenSetMessageBurstCompleted_t)( LibTiePieHandle_t hDevice , HWND hWnd , WPARAM wParam , LPARAM lParam );
#else
void GenSetMessageBurstCompleted( LibTiePieHandle_t hDevice , HWND hWnd , WPARAM wParam , LPARAM lParam );
#endif

#endif

/**
 * \}
 * \defgroup gen_notifications_controllableChanged Controllable changed
 * \{
 * \brief Functions to set notifications that are triggered when the generator controllable state has changed.
 *
 * In certain conditions like when performing a streaming measurement with the oscilloscope, the generator cannot be controlled.
 */

// Workaround: Without this line Doxygen adds the documentation below to the group above.

/**
 * \deprecated Will be removed in future version, see: ObjSetEventCallback()
 * \brief Set a callback function which is called when the generator controllable property changes.
 *
 * \param[in] hDevice A \ref OpenDev "device handle" identifying the generator.
 * \param[in] pCallback A pointer to the callback function. Use \c NULL to disable.
 * \param[in] pData Optional user data.
 * \par Status values
 *   <table class="params">
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_HANDLE "INVALID_HANDLE"</td>         <td>The handle is not a valid generator handle.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_OBJECT_GONE "OBJECT_GONE"</td>            <td>The object indicated by the handle is no longer available.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_LIBRARY_NOT_INITIALIZED "LIBRARY_NOT_INITIALIZED"</td><td>The library is not initialized, see LibInit().</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_SUCCESS "SUCCESS"</td>                <td>The function executed successfully.</td></tr>
 *   </table>
 * \see GenIsControllable
 * \since 0.4.0
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef void(*LibTiePieGenSetCallbackControllableChanged_t)( LibTiePieHandle_t hDevice , TpCallback_t pCallback , void* pData );
#else
void GenSetCallbackControllableChanged( LibTiePieHandle_t hDevice , TpCallback_t pCallback , void* pData );
#endif

#ifdef LIBTIEPIE_LINUX

/**
 * \deprecated Will be removed in future version, see: ObjSetEventEvent()
 * \brief Set an event file descriptor which is set when the generator controllable property changes.
 *
 * \param[in] hDevice A \ref OpenDev "device handle" identifying the generator.
 * \param[in] fdEvent An event file descriptor. Use \c <0 to disable.
 * \note This function is only available on GNU/Linux.
 * \par Status values
 *   <table class="params">
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_HANDLE "INVALID_HANDLE"</td>         <td>The handle is not a valid generator handle.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_OBJECT_GONE "OBJECT_GONE"</td>            <td>The object indicated by the handle is no longer available.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_LIBRARY_NOT_INITIALIZED "LIBRARY_NOT_INITIALIZED"</td><td>The library is not initialized, see LibInit().</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_SUCCESS "SUCCESS"</td>                <td>The function executed successfully.</td></tr>
 *   </table>
 * \see GenIsControllable
 * \since 0.4.0
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef void(*LibTiePieGenSetEventControllableChanged_t)( LibTiePieHandle_t hDevice , int fdEvent );
#else
void GenSetEventControllableChanged( LibTiePieHandle_t hDevice , int fdEvent );
#endif

#endif

#ifdef LIBTIEPIE_WINDOWS

/**
 * \deprecated Will be removed in future version, see: ObjSetEventEvent()
 * \brief Set event object handle which is set when the generator controllable property changes.
 *
 * \param[in] hDevice A \ref OpenDev "device handle" identifying the generator.
 * \param[in] hEvent A handle to the event object. Use \c NULL to disable.
 * \note This function is only available on Windows.
 * \par Status values
 *   <table class="params">
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_HANDLE "INVALID_HANDLE"</td>         <td>The handle is not a valid generator handle.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_OBJECT_GONE "OBJECT_GONE"</td>            <td>The object indicated by the handle is no longer available.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_LIBRARY_NOT_INITIALIZED "LIBRARY_NOT_INITIALIZED"</td><td>The library is not initialized, see LibInit().</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_SUCCESS "SUCCESS"</td>                <td>The function executed successfully.</td></tr>
 *   </table>
 * \see GenIsControllable
 * \since 0.4.0
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef void(*LibTiePieGenSetEventControllableChanged_t)( LibTiePieHandle_t hDevice , HANDLE hEvent );
#else
void GenSetEventControllableChanged( LibTiePieHandle_t hDevice , HANDLE hEvent );
#endif

/**
 * \deprecated Will be removed in future version, see: ObjSetEventWindowHandle()
 * \brief Set window handle to which a #WM_LIBTIEPIE_GEN_CONTROLLABLECHANGED message is sent when the generator controllable property changes.
 *
 * \param[in] hDevice A \ref OpenDev "device handle" identifying the generator.
 * \param[in] hWnd A handle to the window whose window procedure is to receive the message. Use \c NULL to disable.
 * \param[in] wParam Optional user value for the \c wParam parameter of the message.
 * \param[in] lParam Optional user value for the \c lParam parameter of the message.
 * \note This function is only available on Windows.
 * \par Status values
 *   <table class="params">
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_HANDLE "INVALID_HANDLE"</td>         <td>The handle is not a valid generator handle.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_OBJECT_GONE "OBJECT_GONE"</td>            <td>The object indicated by the handle is no longer available.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_LIBRARY_NOT_INITIALIZED "LIBRARY_NOT_INITIALIZED"</td><td>The library is not initialized, see LibInit().</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_SUCCESS "SUCCESS"</td>                <td>The function executed successfully.</td></tr>
 *   </table>
 * \see GenIsControllable
 * \since 0.4.0
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef void(*LibTiePieGenSetMessageControllableChanged_t)( LibTiePieHandle_t hDevice , HWND hWnd , WPARAM wParam , LPARAM lParam );
#else
void GenSetMessageControllableChanged( LibTiePieHandle_t hDevice , HWND hWnd , WPARAM wParam , LPARAM lParam );
#endif

#endif

/**
 * \}
 * \}
 * \}
 * \defgroup i2c I2C Host
 * \{
 * \brief Functions to setup and control I<sup>2</sup>C hosts.
 *
 *       All I<sup>2</sup>C host related functions require an \ref LibTiePieHandle_t "I2C host handle" to identify the I<sup>2</sup>C host,
 *       see \ref OpenDev "opening a device".
 *
 *       Some I<sup>2</sup>C addresses may be reserved for internal use in the instrument, these addresses can not be controlled via
 *       the I<sup>2</sup>C host routines.
 *       Use I2CIsInternalAddress() to check whether an address is used internally.
 *
 */

// Workaround: Without this line Doxygen adds the documentation below to the group above.

/**
 * \brief Check whether an address is used internally.
 *
 * \param[in] hDevice A \ref OpenDev "device handle" identifying the I<sup>2</sup>C host.
 * \param[in] wAddress An I<sup>2</sup>C device address.
 * \return #BOOL8_TRUE if the address is used internally, #BOOL8_FALSE otherwise.
 * \par Status values
 *   <table class="params">
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_HANDLE "INVALID_HANDLE"</td>         <td>The handle is not a valid I<sup>2</sup>C host handle.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_OBJECT_GONE "OBJECT_GONE"</td>            <td>The object indicated by the handle is no longer available.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_LIBRARY_NOT_INITIALIZED "LIBRARY_NOT_INITIALIZED"</td><td>The library is not initialized, see LibInit().</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_SUCCESS "SUCCESS"</td>                <td>The function executed successfully.</td></tr>
 *   </table>
 * \see I2CGetInternalAddresses
 * \since 0.4.0
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef bool8_t(*LibTiePieI2CIsInternalAddress_t)( LibTiePieHandle_t hDevice , uint16_t wAddress );
#else
bool8_t I2CIsInternalAddress( LibTiePieHandle_t hDevice , uint16_t wAddress );
#endif

/**
 * \brief Get all addresses which are used internally.
 *
 * \param[in] hDevice A \ref OpenDev "device handle" identifying the I<sup>2</sup>C host.
 * \param[out] pAddresses  A pointer to an array for the addresses.
 * \param[in] dwLength The number of elements in the array.
 * \return The total number of addresses.
 * \par Status values
 *   <table class="params">
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_HANDLE "INVALID_HANDLE"</td>         <td>The handle is not a valid I<sup>2</sup>C host handle.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_OBJECT_GONE "OBJECT_GONE"</td>            <td>The object indicated by the handle is no longer available.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_LIBRARY_NOT_INITIALIZED "LIBRARY_NOT_INITIALIZED"</td><td>The library is not initialized, see LibInit().</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_SUCCESS "SUCCESS"</td>                <td>The function executed successfully.</td></tr>
 *   </table>
 *
 * \par Example
 * \code{.c}
 * uint32_t dwLength = I2CGetInternalAddresses( hDevice , NULL , 0 );
 * uint16_t* pAddresses = malloc( sizeof( uint16_t ) * dwLength );
 * dwLength = I2CGetInternalAddresses( hDevice , pAddresses , dwLength );
 *
 * printf( "I2CGetInternalAddresses:\n" );
 * for( i = 0 ; i < dwLength ; i++ )
 *   printf( "- 0x%x (%u)\n" , pAddresses[ i ] , pAddresses[ i ] );
 *
 * free( pAddresses );
 * \endcode
 *
 * \see I2CIsInternalAddress
 * \since 0.6
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef uint32_t(*LibTiePieI2CGetInternalAddresses_t)( LibTiePieHandle_t hDevice , uint16_t* pAddresses , uint32_t dwLength );
#else
uint32_t I2CGetInternalAddresses( LibTiePieHandle_t hDevice , uint16_t* pAddresses , uint32_t dwLength );
#endif

/**
 * \defgroup i2c_read Reading data
 * \{
 * \brief Functions to read data from an I<sup>2</sup>C device.
 */

// Workaround: Without this line Doxygen adds the documentation below to the group above.

/**
 * \brief Read data from a specified address on the I<sup>2</sup>C bus, using a specified I<sup>2</sup>C host.
 *
 * \param[in] hDevice A \ref OpenDev "device handle" identifying the I<sup>2</sup>C host.
 * \param[in] wAddress The I<sup>2</sup>C address to read from.
 * \param[out] pBuffer A pointer to the read buffer.
 * \param[in] dwSize The number of bytes to read.
 * \param[in] bStop Indicates whether an I<sup>2</sup>C stop is generated after the transaction, when #BOOL8_TRUE, an I<sup>2</sup>C stop is generated, when #BOOL8_FALSE not.
 * \return #BOOL8_TRUE if successful, #BOOL8_FALSE otherwise.
 * \par Status values
 *   <table class="params">
 *   <tr><td>\ref LIBTIEPIESTATUS_INTERNAL_ADDRESS "INTERNAL_ADDRESS"</td>       <td>The requested I<sup>2</sup>C address is an internally used address in the device.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_BIT_ERROR "BIT_ERROR"</td>              <td>The requested I<sup>2</sup>C operation generated a bit error.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_NO_ACKNOWLEDGE "NO_ACKNOWLEDGE"</td>         <td>The requested I<sup>2</sup>C operation generated "No acknowledge".</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_HANDLE "INVALID_HANDLE"</td>         <td>The handle is not a valid I<sup>2</sup>C host handle.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_OBJECT_GONE "OBJECT_GONE"</td>            <td>The object indicated by the handle is no longer available.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_LIBRARY_NOT_INITIALIZED "LIBRARY_NOT_INITIALIZED"</td><td>The library is not initialized, see LibInit().</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_SUCCESS "SUCCESS"</td>                <td>The function executed successfully.</td></tr>
 *   </table>
 * \see I2CReadByte
 * \see I2CReadWord
 * \since 0.4.0
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef bool8_t(*LibTiePieI2CRead_t)( LibTiePieHandle_t hDevice , uint16_t wAddress , void* pBuffer , uint32_t dwSize , bool8_t bStop );
#else
bool8_t I2CRead( LibTiePieHandle_t hDevice , uint16_t wAddress , void* pBuffer , uint32_t dwSize , bool8_t bStop );
#endif

/**
 * \brief Read one byte from a specified address on the I<sup>2</sup>C bus, using a specified I<sup>2</sup>C host.
 *
 * An I<sup>2</sup>C stop is generated after the transaction.
 *
 * \param[in] hDevice A \ref OpenDev "device handle" identifying the I<sup>2</sup>C host.
 * \param[in] wAddress The I<sup>2</sup>C address to read from.
 * \param[out] pValue A pointer to the read buffer.
 * \return #BOOL8_TRUE if successful, #BOOL8_FALSE otherwise.
 * \par Status values
 *   <table class="params">
 *   <tr><td>\ref LIBTIEPIESTATUS_INTERNAL_ADDRESS "INTERNAL_ADDRESS"</td>       <td>The requested I<sup>2</sup>C address is an internally used address in the device.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_BIT_ERROR "BIT_ERROR"</td>              <td>The requested I<sup>2</sup>C operation generated a bit error.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_NO_ACKNOWLEDGE "NO_ACKNOWLEDGE"</td>         <td>The requested I<sup>2</sup>C operation generated "No acknowledge".</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_HANDLE "INVALID_HANDLE"</td>         <td>The handle is not a valid I<sup>2</sup>C host handle.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_OBJECT_GONE "OBJECT_GONE"</td>            <td>The object indicated by the handle is no longer available.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_LIBRARY_NOT_INITIALIZED "LIBRARY_NOT_INITIALIZED"</td><td>The library is not initialized, see LibInit().</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_SUCCESS "SUCCESS"</td>                <td>The function executed successfully.</td></tr>
 *   </table>
 * \see I2CRead
 * \see I2CReadWord
 * \since 0.4.0
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef bool8_t(*LibTiePieI2CReadByte_t)( LibTiePieHandle_t hDevice , uint16_t wAddress , uint8_t* pValue );
#else
bool8_t I2CReadByte( LibTiePieHandle_t hDevice , uint16_t wAddress , uint8_t* pValue );
#endif

/**
 * \brief Read one word from a specified address on the I<sup>2</sup>C bus, using a specified I<sup>2</sup>C host.
 *
 * An I<sup>2</sup>C stop is generated after the transaction.
 *
 * \param[in] hDevice A \ref OpenDev "device handle" identifying the I<sup>2</sup>C host.
 * \param[in] wAddress The I<sup>2</sup>C address to read from.
 * \param[out] pValue A pointer to the read buffer.
 * \return #BOOL8_TRUE if successful, #BOOL8_FALSE otherwise.
 * \note Bus data is regarded big endian and converted to host endianess.
 * \par Status values
 *   <table class="params">
 *   <tr><td>\ref LIBTIEPIESTATUS_INTERNAL_ADDRESS "INTERNAL_ADDRESS"</td>       <td>The requested I<sup>2</sup>C address is an internally used address in the device.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_BIT_ERROR "BIT_ERROR"</td>              <td>The requested I<sup>2</sup>C operation generated a bit error.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_NO_ACKNOWLEDGE "NO_ACKNOWLEDGE"</td>         <td>The requested I<sup>2</sup>C operation generated "No acknowledge".</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_HANDLE "INVALID_HANDLE"</td>         <td>The handle is not a valid I<sup>2</sup>C host handle.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_OBJECT_GONE "OBJECT_GONE"</td>            <td>The object indicated by the handle is no longer available.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_LIBRARY_NOT_INITIALIZED "LIBRARY_NOT_INITIALIZED"</td><td>The library is not initialized, see LibInit().</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_SUCCESS "SUCCESS"</td>                <td>The function executed successfully.</td></tr>
 *   </table>
 * \see I2CRead
 * \see I2CReadByte
 * \since 0.4.0
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef bool8_t(*LibTiePieI2CReadWord_t)( LibTiePieHandle_t hDevice , uint16_t wAddress , uint16_t* pValue );
#else
bool8_t I2CReadWord( LibTiePieHandle_t hDevice , uint16_t wAddress , uint16_t* pValue );
#endif

/**
 * \}
 * \defgroup i2c_write Writing data
 * \{
 * \brief Functions to write data to an I<sup>2</sup>C device.
 */

// Workaround: Without this line Doxygen adds the documentation below to the group above.

/**
 * \brief Write data to a specified address on the I<sup>2</sup>C bus, using a specified I<sup>2</sup>C host.
 *
 * \param[in] hDevice A \ref OpenDev "device handle" identifying the I<sup>2</sup>C host.
 * \param[in] wAddress The I<sup>2</sup>C address to write to.
 * \param[in] pBuffer A pointer to the write buffer.
 * \param[in] dwSize The number of bytes to write.
 * \param[in] bStop Indicates whether an I<sup>2</sup>C stop is generated after the transaction, when #BOOL8_TRUE, an I<sup>2</sup>C stop is generated, when #BOOL8_FALSE not.
 * \return #BOOL8_TRUE if successful, #BOOL8_FALSE otherwise.
 * \par Status values
 *   <table class="params">
 *   <tr><td>\ref LIBTIEPIESTATUS_INTERNAL_ADDRESS "INTERNAL_ADDRESS"</td>       <td>The requested I<sup>2</sup>C address is an internally used address in the device.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_BIT_ERROR "BIT_ERROR"</td>              <td>The requested I<sup>2</sup>C operation generated a bit error.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_NO_ACKNOWLEDGE "NO_ACKNOWLEDGE"</td>         <td>The requested I<sup>2</sup>C operation generated "No acknowledge".</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_HANDLE "INVALID_HANDLE"</td>         <td>The handle is not a valid I<sup>2</sup>C host handle.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_OBJECT_GONE "OBJECT_GONE"</td>            <td>The object indicated by the handle is no longer available.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_LIBRARY_NOT_INITIALIZED "LIBRARY_NOT_INITIALIZED"</td><td>The library is not initialized, see LibInit().</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_SUCCESS "SUCCESS"</td>                <td>The function executed successfully.</td></tr>
 *   </table>
 * \see I2CWriteByte
 * \see I2CWriteByteByte
 * \see I2CWriteByteWord
 * \see I2CWriteWord
 * \since 0.4.0
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef bool8_t(*LibTiePieI2CWrite_t)( LibTiePieHandle_t hDevice , uint16_t wAddress , const void* pBuffer , uint32_t dwSize , bool8_t bStop );
#else
bool8_t I2CWrite( LibTiePieHandle_t hDevice , uint16_t wAddress , const void* pBuffer , uint32_t dwSize , bool8_t bStop );
#endif

/**
 * \brief Write one byte to a specified address on the I<sup>2</sup>C bus, using a specified I<sup>2</sup>C host.
 *
 * An I<sup>2</sup>C stop is generated after the transaction.
 *
 * \param[in] hDevice A \ref OpenDev "device handle" identifying the I<sup>2</sup>C host.
 * \param[in] wAddress The I<sup>2</sup>C address to write to.
 * \param[in] byValue The byte value to write.
 * \return #BOOL8_TRUE if successful, #BOOL8_FALSE otherwise.
 * \par Status values
 *   <table class="params">
 *   <tr><td>\ref LIBTIEPIESTATUS_INTERNAL_ADDRESS "INTERNAL_ADDRESS"</td>       <td>The requested I<sup>2</sup>C address is an internally used address in the device.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_BIT_ERROR "BIT_ERROR"</td>              <td>The requested I<sup>2</sup>C operation generated a bit error.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_NO_ACKNOWLEDGE "NO_ACKNOWLEDGE"</td>         <td>The requested I<sup>2</sup>C operation generated "No acknowledge".</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_HANDLE "INVALID_HANDLE"</td>         <td>The handle is not a valid I<sup>2</sup>C host handle.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_OBJECT_GONE "OBJECT_GONE"</td>            <td>The object indicated by the handle is no longer available.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_LIBRARY_NOT_INITIALIZED "LIBRARY_NOT_INITIALIZED"</td><td>The library is not initialized, see LibInit().</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_SUCCESS "SUCCESS"</td>                <td>The function executed successfully.</td></tr>
 *   </table>
 * \see I2CWrite
 * \see I2CWriteByteByte
 * \see I2CWriteByteWord
 * \see I2CWriteWord
 * \since 0.4.0
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef bool8_t(*LibTiePieI2CWriteByte_t)( LibTiePieHandle_t hDevice , uint16_t wAddress , uint8_t byValue );
#else
bool8_t I2CWriteByte( LibTiePieHandle_t hDevice , uint16_t wAddress , uint8_t byValue );
#endif

/**
 * \brief Write two bytes to a specified address on the I<sup>2</sup>C bus, using a specified I<sup>2</sup>C host.
 *
 * An I<sup>2</sup>C stop is generated after the transaction.
 *
 * \param[in] hDevice A \ref OpenDev "device handle" identifying the I<sup>2</sup>C host.
 * \param[in] wAddress The I<sup>2</sup>C address to write to.
 * \param[in] byValue1 The first byte value to write.
 * \param[in] byValue2 The second byte value to write.
 * \return #BOOL8_TRUE if successful, #BOOL8_FALSE otherwise.
 * \par Status values
 *   <table class="params">
 *   <tr><td>\ref LIBTIEPIESTATUS_INTERNAL_ADDRESS "INTERNAL_ADDRESS"</td>       <td>The requested I<sup>2</sup>C address is an internally used address in the device.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_BIT_ERROR "BIT_ERROR"</td>              <td>The requested I<sup>2</sup>C operation generated a bit error.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_NO_ACKNOWLEDGE "NO_ACKNOWLEDGE"</td>         <td>The requested I<sup>2</sup>C operation generated "No acknowledge".</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_HANDLE "INVALID_HANDLE"</td>         <td>The handle is not a valid I<sup>2</sup>C host handle.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_OBJECT_GONE "OBJECT_GONE"</td>            <td>The object indicated by the handle is no longer available.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_LIBRARY_NOT_INITIALIZED "LIBRARY_NOT_INITIALIZED"</td><td>The library is not initialized, see LibInit().</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_SUCCESS "SUCCESS"</td>                <td>The function executed successfully.</td></tr>
 *   </table>
 * \see I2CWrite
 * \see I2CWriteByte
 * \see I2CWriteByteWord
 * \see I2CWriteWord
 * \since 0.4.0
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef bool8_t(*LibTiePieI2CWriteByteByte_t)( LibTiePieHandle_t hDevice , uint16_t wAddress , uint8_t byValue1 , uint8_t byValue2 );
#else
bool8_t I2CWriteByteByte( LibTiePieHandle_t hDevice , uint16_t wAddress , uint8_t byValue1 , uint8_t byValue2 );
#endif

/**
 * \brief Write one byte and one word to a specified address on the I<sup>2</sup>C bus, using a specified I<sup>2</sup>C host.
 *
 * An I<sup>2</sup>C stop is generated after the transaction.
 *
 * \param[in] hDevice A \ref OpenDev "device handle" identifying the I<sup>2</sup>C host.
 * \param[in] wAddress The I<sup>2</sup>C address to write to.
 * \param[in] byValue1 The byte value to write.
 * \param[in] wValue2 The word value to write.
 * \return #BOOL8_TRUE if successful, #BOOL8_FALSE otherwise.
 * \note Bus data is regarded big endian, host endian data will be converted to big endian.
 * \par Status values
 *   <table class="params">
 *   <tr><td>\ref LIBTIEPIESTATUS_INTERNAL_ADDRESS "INTERNAL_ADDRESS"</td>       <td>The requested I<sup>2</sup>C address is an internally used address in the device.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_BIT_ERROR "BIT_ERROR"</td>              <td>The requested I<sup>2</sup>C operation generated a bit error.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_NO_ACKNOWLEDGE "NO_ACKNOWLEDGE"</td>         <td>The requested I<sup>2</sup>C operation generated "No acknowledge".</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_HANDLE "INVALID_HANDLE"</td>         <td>The handle is not a valid I<sup>2</sup>C host handle.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_OBJECT_GONE "OBJECT_GONE"</td>            <td>The object indicated by the handle is no longer available.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_LIBRARY_NOT_INITIALIZED "LIBRARY_NOT_INITIALIZED"</td><td>The library is not initialized, see LibInit().</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_SUCCESS "SUCCESS"</td>                <td>The function executed successfully.</td></tr>
 *   </table>
 * \see I2CWrite
 * \see I2CWriteByte
 * \see I2CWriteByteByte
 * \see I2CWriteWord
 * \since 0.4.0
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef bool8_t(*LibTiePieI2CWriteByteWord_t)( LibTiePieHandle_t hDevice , uint16_t wAddress , uint8_t byValue1 , uint16_t wValue2 );
#else
bool8_t I2CWriteByteWord( LibTiePieHandle_t hDevice , uint16_t wAddress , uint8_t byValue1 , uint16_t wValue2 );
#endif

/**
 * \brief Write one word to a specified address on the I<sup>2</sup>C bus, using a specified I<sup>2</sup>C host.
 *
 * An I<sup>2</sup>C stop is generated after the transaction.
 *
 * \param[in] hDevice A \ref OpenDev "device handle" identifying the I<sup>2</sup>C host.
 * \param[in] wAddress The I<sup>2</sup>C address to write to.
 * \param[in] wValue The word value to write.
 * \return #BOOL8_TRUE if successful, #BOOL8_FALSE otherwise.
 * \note Bus data is regarded big endian, host endian data will be converted to big endian.
 * \par Status values
 *   <table class="params">
 *   <tr><td>\ref LIBTIEPIESTATUS_INTERNAL_ADDRESS "INTERNAL_ADDRESS"</td>       <td>The requested I<sup>2</sup>C address is an internally used address in the device.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_BIT_ERROR "BIT_ERROR"</td>              <td>The requested I<sup>2</sup>C operation generated a bit error.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_NO_ACKNOWLEDGE "NO_ACKNOWLEDGE"</td>         <td>The requested I<sup>2</sup>C operation generated "No acknowledge".</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_HANDLE "INVALID_HANDLE"</td>         <td>The handle is not a valid I<sup>2</sup>C host handle.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_OBJECT_GONE "OBJECT_GONE"</td>            <td>The object indicated by the handle is no longer available.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_LIBRARY_NOT_INITIALIZED "LIBRARY_NOT_INITIALIZED"</td><td>The library is not initialized, see LibInit().</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_SUCCESS "SUCCESS"</td>                <td>The function executed successfully.</td></tr>
 *   </table>
 * \see I2CWrite
 * \see I2CWriteByte
 * \see I2CWriteByteByte
 * \see I2CWriteByteWord
 * \since 0.4.0
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef bool8_t(*LibTiePieI2CWriteWord_t)( LibTiePieHandle_t hDevice , uint16_t wAddress , uint16_t wValue );
#else
bool8_t I2CWriteWord( LibTiePieHandle_t hDevice , uint16_t wAddress , uint16_t wValue );
#endif

/**
 * \}
 * \defgroup i2c_write_read Writing/reading data
 * \{
 * \brief Functions to write and read data to/from an I<sup>2</sup>C device.
 */

// Workaround: Without this line Doxygen adds the documentation below to the group above.

/**
 * \brief Write and read data to/from to a specified address on the I<sup>2</sup>C bus, using a specified I<sup>2</sup>C host.
 *
 * Equivalent:
 * \code
 * I2CWrite( hDevice , wAddress , pWriteBuffer , dwWriteSize , BOOL8_FALSE ) &&
 * I2CRead( hDevice , wAddress , pReadBuffer , dwReadSize , BOOL8_TRUE );
 * \endcode
 *
 * \param[in] hDevice A \ref OpenDev "device handle" identifying the I<sup>2</sup>C host.
 * \param[in] wAddress The I<sup>2</sup>C address to write to.
 * \param[in] pWriteBuffer A pointer to the write buffer.
 * \param[in] dwWriteSize The number of bytes to write.
 * \param[out] pReadBuffer A pointer to the read buffer.
 * \param[in] dwReadSize The number of bytes to read.
 * \return #BOOL8_TRUE if successful, #BOOL8_FALSE otherwise.
 * \par Status values
 *   <table class="params">
 *   <tr><td>\ref LIBTIEPIESTATUS_INTERNAL_ADDRESS "INTERNAL_ADDRESS"</td>       <td>The requested I<sup>2</sup>C address is an internally used address in the device.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_BIT_ERROR "BIT_ERROR"</td>              <td>The requested I<sup>2</sup>C operation generated a bit error.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_NO_ACKNOWLEDGE "NO_ACKNOWLEDGE"</td>         <td>The requested I<sup>2</sup>C operation generated "No acknowledge".</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_HANDLE "INVALID_HANDLE"</td>         <td>The handle is not a valid I<sup>2</sup>C host handle.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_OBJECT_GONE "OBJECT_GONE"</td>            <td>The object indicated by the handle is no longer available.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_LIBRARY_NOT_INITIALIZED "LIBRARY_NOT_INITIALIZED"</td><td>The library is not initialized, see LibInit().</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_SUCCESS "SUCCESS"</td>                <td>The function executed successfully.</td></tr>
 *   </table>
 * \since 0.6
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef bool8_t(*LibTiePieI2CWriteRead_t)( LibTiePieHandle_t hDevice , uint16_t wAddress , const void* pWriteBuffer , uint32_t dwWriteSize , void* pReadBuffer , uint32_t dwReadSize );
#else
bool8_t I2CWriteRead( LibTiePieHandle_t hDevice , uint16_t wAddress , const void* pWriteBuffer , uint32_t dwWriteSize , void* pReadBuffer , uint32_t dwReadSize );
#endif

/**
 * \}
 * \defgroup i2c_speed Speed
 * \{
 * \brief Functions to control the I<sup>2</sup>C clock speed.
 */

// Workaround: Without this line Doxygen adds the documentation below to the group above.

/**
 * \brief Get the maximum clock speed on the I<sup>2</sup>C bus controlled by a specified I<sup>2</sup>C host.
 *
 * \param[in] hDevice A \ref OpenDev "device handle" identifying the I<sup>2</sup>C host.
 * \return The maximum I<sup>2</sup>C clock speed in Hz.
 * \par Status values
 *   <table class="params">
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_HANDLE "INVALID_HANDLE"</td>         <td>The handle is not a valid I<sup>2</sup>C host handle.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_OBJECT_GONE "OBJECT_GONE"</td>            <td>The object indicated by the handle is no longer available.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_LIBRARY_NOT_INITIALIZED "LIBRARY_NOT_INITIALIZED"</td><td>The library is not initialized, see LibInit().</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_SUCCESS "SUCCESS"</td>                <td>The function executed successfully.</td></tr>
 *   </table>
 * \see I2CGetSpeed
 * \see I2CSetSpeed
 * \since 0.4.0
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef double(*LibTiePieI2CGetSpeedMax_t)( LibTiePieHandle_t hDevice );
#else
double I2CGetSpeedMax( LibTiePieHandle_t hDevice );
#endif

/**
 * \brief Get the current clock speed on the I<sup>2</sup>C bus controlled by a specified I<sup>2</sup>C host.
 *
 * \param[in] hDevice A \ref OpenDev "device handle" identifying the I<sup>2</sup>C host.
 * \return The currently set I<sup>2</sup>C clock speed in Hz.
 * \par Status values
 *   <table class="params">
 *   <tr><td>\ref LIBTIEPIESTATUS_UNSUCCESSFUL "UNSUCCESSFUL"</td>           <td>An error occurred during execution of the last called function.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_HANDLE "INVALID_HANDLE"</td>         <td>The handle is not a valid I<sup>2</sup>C host handle.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_OBJECT_GONE "OBJECT_GONE"</td>            <td>The object indicated by the handle is no longer available.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_LIBRARY_NOT_INITIALIZED "LIBRARY_NOT_INITIALIZED"</td><td>The library is not initialized, see LibInit().</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_SUCCESS "SUCCESS"</td>                <td>The function executed successfully.</td></tr>
 *   </table>
 * \see I2CGetSpeedMax
 * \see I2CSetSpeed
 * \since 0.4.0
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef double(*LibTiePieI2CGetSpeed_t)( LibTiePieHandle_t hDevice );
#else
double I2CGetSpeed( LibTiePieHandle_t hDevice );
#endif

/**
 * \brief Set the clock speed on the I<sup>2</sup>C bus controlled by a specified I<sup>2</sup>C host.
 *
 * \param[in] hDevice A \ref OpenDev "device handle" identifying the I<sup>2</sup>C host.
 * \param[in] dSpeed The requested I<sup>2</sup>C clock speed in Hz.
 * \return The actually set I<sup>2</sup>C clock speed in Hz.
 * \par Status values
 *   <table class="params">
 *   <tr><td>\ref LIBTIEPIESTATUS_VALUE_CLIPPED "VALUE_CLIPPED"</td>          <td>The requested I<sup>2</sup>C clock speed is outside the valid range and clipped to that range.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_VALUE_MODIFIED "VALUE_MODIFIED"</td>         <td>The requested  I<sup>2</sup>C clock speed is inside the valid range but not available. The closest valid value is set.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_HANDLE "INVALID_HANDLE"</td>         <td>The handle is not a valid I<sup>2</sup>C host handle.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_OBJECT_GONE "OBJECT_GONE"</td>            <td>The object indicated by the handle is no longer available.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_LIBRARY_NOT_INITIALIZED "LIBRARY_NOT_INITIALIZED"</td><td>The library is not initialized, see LibInit().</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_SUCCESS "SUCCESS"</td>                <td>The function executed successfully.</td></tr>
 *   </table>
 * \see I2CGetSpeedMax
 * \see I2CGetSpeed
 * \since 0.4.0
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef double(*LibTiePieI2CSetSpeed_t)( LibTiePieHandle_t hDevice , double dSpeed );
#else
double I2CSetSpeed( LibTiePieHandle_t hDevice , double dSpeed );
#endif

//! \cond EXTENDED_API

/**
 * \brief Verify if a clock speed on the I<sup>2</sup>C bus controlled by a specified I<sup>2</sup>C host can be set, without actually setting the hardware.
 *
 * \param[in] hDevice A \ref OpenDev "device handle" identifying the I<sup>2</sup>C host.
 * \param[in] dSpeed The requested I<sup>2</sup>C clock speed in Hz.
 * \return The I<sup>2</sup>C clock speed that would have been set, in Hz.
 * \par Status values
 *   <table class="params">
 *   <tr><td>\ref LIBTIEPIESTATUS_VALUE_CLIPPED "VALUE_CLIPPED"</td>          <td>The requested I<sup>2</sup>C clock speed is outside the valid range and clipped to that range.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_VALUE_MODIFIED "VALUE_MODIFIED"</td>         <td>The requested  I<sup>2</sup>C clock speed is inside the valid range but not available. The closest valid value is set.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_HANDLE "INVALID_HANDLE"</td>         <td>The handle is not a valid I<sup>2</sup>C host handle.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_OBJECT_GONE "OBJECT_GONE"</td>            <td>The object indicated by the handle is no longer available.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_LIBRARY_NOT_INITIALIZED "LIBRARY_NOT_INITIALIZED"</td><td>The library is not initialized, see LibInit().</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_SUCCESS "SUCCESS"</td>                <td>The function executed successfully.</td></tr>
 *   </table>
 * \see I2CGetSpeedMax
 * \see I2CGetSpeed
 * \see I2CSetSpeed
 * \since 0.4.0
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef double(*LibTiePieI2CVerifySpeed_t)( LibTiePieHandle_t hDevice , double dSpeed );
#else
double I2CVerifySpeed( LibTiePieHandle_t hDevice , double dSpeed );
#endif

//! \endcond

/**
 * \}
 * \}
 * \defgroup srv Server
 * \{
 * \brief Functions to communicate with network instruments and instrument servers
 */

// Workaround: Without this line Doxygen adds the documentation below to the group above.

/**
 * \brief Connect to a specified network instrument or instrument server.
 *        This gives access to the network instrument or instruments connected to the instrument server.
 *
 * \param[in] hServer A server handle identifying the server.
 * \param[in] bAsync Connect asynchronously
 * \return #BOOL8_TRUE if successful, #BOOL8_FALSE otherwise.
 * \since 0.9
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef bool8_t(*LibTiePieSrvConnect_t)( LibTiePieHandle_t hServer , bool8_t bAsync );
#else
bool8_t SrvConnect( LibTiePieHandle_t hServer , bool8_t bAsync );
#endif

/**
 * \brief Disconnect from a specified network instrument or instrument server.
 *        This will close all opened instrument(s).
 *
 * \param[in] hServer A server handle identifying the server.
 * \param[in] bForce If #BOOL8_TRUE all open devices are closed, if #BOOL8_FALSE remove only succeeds if no devices are open.
 * \return #BOOL8_TRUE if successful, #BOOL8_FALSE otherwise.
 * \since 0.9
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef bool8_t(*LibTiePieSrvDisconnect_t)( LibTiePieHandle_t hServer , bool8_t bForce );
#else
bool8_t SrvDisconnect( LibTiePieHandle_t hServer , bool8_t bForce );
#endif

/**
 * \brief Remove a specified specified network instrument or instrument server from the list of servers.
 *
 * \param[in] hServer A server handle identifying the server.
 * \param[in] bForce If #BOOL8_TRUE all open devices are closed, if #BOOL8_FALSE remove only succeeds if no devices are open.
 * \return #BOOL8_TRUE if successful, #BOOL8_FALSE otherwise.
 * \since 0.9
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef bool8_t(*LibTiePieSrvRemove_t)( LibTiePieHandle_t hServer , bool8_t bForce );
#else
bool8_t SrvRemove( LibTiePieHandle_t hServer , bool8_t bForce );
#endif

/**
 * \brief Retrieve the status of a specified network instrument or instrument server.
 *
 * \param[in] hServer A server handle identifying the server.
 * \return The status of the specified network instrument or instrument server, see LIBTIEPIE_SERVER_STATUS
 * \since 0.9
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef uint32_t(*LibTiePieSrvGetStatus_t)( LibTiePieHandle_t hServer );
#else
uint32_t SrvGetStatus( LibTiePieHandle_t hServer );
#endif

/**
 * \brief Get the last error from a specified network instrument or instrument server.
 *
 * \param[in] hServer A server handle identifying the server.
 * \return The last error given by the specified network instrument or instrument server, see LIBTIEPIE_SERVER_ERROR
 * \since 0.9
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef uint32_t(*LibTiePieSrvGetLastError_t)( LibTiePieHandle_t hServer );
#else
uint32_t SrvGetLastError( LibTiePieHandle_t hServer );
#endif

/**
 * \brief Get the URL of the specified network instrument or instrument server.
 *
 * \param[in] hServer A server handle identifying the server.
 * \param[out] pBuffer A pointer to a buffer for the URL.
 * \param[in] dwBufferLength The length of the buffer, in bytes.
 * \return The length of the URL in bytes, excluding terminating zero.
 * \since 0.9
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef uint32_t(*LibTiePieSrvGetURL_t)( LibTiePieHandle_t hServer , char* pBuffer , uint32_t dwBufferLength );
#else
uint32_t SrvGetURL( LibTiePieHandle_t hServer , char* pBuffer , uint32_t dwBufferLength );
#endif

/**
 * \brief Get the id of the specified network instrument or instrument server.
 *
 * \param[in] hServer A server handle identifying the server.
 * \param[out] pBuffer A pointer to a buffer for the id.
 * \param[in] dwBufferLength The length of the buffer, in bytes.
 * \return The length of the id in bytes, excluding terminating zero.
 * \since 0.9
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef uint32_t(*LibTiePieSrvGetID_t)( LibTiePieHandle_t hServer , char* pBuffer , uint32_t dwBufferLength );
#else
uint32_t SrvGetID( LibTiePieHandle_t hServer , char* pBuffer , uint32_t dwBufferLength );
#endif

/**
 * \brief Get the IPv4 address of the specified network instrument or instrument server.
 *
 * \param[in] hServer A server handle identifying the server.
 * \return The IPv4 address of the device, or zero if no IPv4 address is available.
 * \since 0.9
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef uint32_t(*LibTiePieSrvGetIPv4Address_t)( LibTiePieHandle_t hServer );
#else
uint32_t SrvGetIPv4Address( LibTiePieHandle_t hServer );
#endif

/**
 * \brief Get the IP port number of the specified network instrument or instrument server.
 *
 * \param[in] hServer A server handle identifying the server.
 * \return The IP port number of the device, or zero if no IP port number is available.
 * \since 0.9
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef uint16_t(*LibTiePieSrvGetIPPort_t)( LibTiePieHandle_t hServer );
#else
uint16_t SrvGetIPPort( LibTiePieHandle_t hServer );
#endif

/**
 * \brief Get the name of the specified network instrument or instrument server.
 *
 * \param[in] hServer A server handle identifying the server.
 * \param[out] pBuffer A pointer to a buffer for the name.
 * \param[in] dwBufferLength The length of the buffer, in bytes.
 * \return The length of the name in bytes, excluding terminating zero.
 * \since 0.9
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef uint32_t(*LibTiePieSrvGetName_t)( LibTiePieHandle_t hServer , char* pBuffer , uint32_t dwBufferLength );
#else
uint32_t SrvGetName( LibTiePieHandle_t hServer , char* pBuffer , uint32_t dwBufferLength );
#endif

/**
 * \brief Get the description of the specified network instrument or instrument server.
 *
 * \param[in] hServer A server handle identifying the server.
 * \param[out] pBuffer A pointer to a buffer for the description.
 * \param[in] dwBufferLength The length of the buffer, in bytes.
 * \return The length of the description in bytes, excluding terminating zero.
 * \since 0.9
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef uint32_t(*LibTiePieSrvGetDescription_t)( LibTiePieHandle_t hServer , char* pBuffer , uint32_t dwBufferLength );
#else
uint32_t SrvGetDescription( LibTiePieHandle_t hServer , char* pBuffer , uint32_t dwBufferLength );
#endif

/**
 * \brief Get the software version number of the specified network instrument or instrument server.
 *
 * \param[in] hServer A server handle identifying the server.
 * \return The software \ref TpVersion_t "version" number of the server, or zero if no software version is available.
 * \since 0.9
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef TpVersion_t(*LibTiePieSrvGetVersion_t)( LibTiePieHandle_t hServer );
#else
TpVersion_t SrvGetVersion( LibTiePieHandle_t hServer );
#endif

/**
 * \brief Get the software version postfix of the specified network instrument or instrument server.
 *
 * \param[in] hServer A server handle identifying the server.
 * \param[out] pBuffer A pointer to a buffer for the software version postfix.
 * \param[in] dwBufferLength The length of the buffer, in bytes.
 * \return The length of the software version postfix in bytes, excluding terminating zero.
 * \since 0.9
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef uint32_t(*LibTiePieSrvGetVersionExtra_t)( LibTiePieHandle_t hServer , char* pBuffer , uint32_t dwBufferLength );
#else
uint32_t SrvGetVersionExtra( LibTiePieHandle_t hServer , char* pBuffer , uint32_t dwBufferLength );
#endif

/**
 * \}
 * \}
 * \}
 * \defgroup hlp Helper functions
 * \{
 * \brief Functions to bypass certain limitations of programming/scripting languages.
 *
 * \defgroup hlp_ptrar Pointer array
 * \{
 * \brief Functions for handling arrays of pointers.
 *
 *       The function ScpGetData() uses a pointer to a buffer with pointers to buffers for the channel data.
 *       Not all programming/scripting languages can handle pointers to pointers properly.
 *       These functions can then be used to work around that issue.
 *
 * \par Example
 *       In pseudocode:
 * \code
 *       buffers = empty list/array
 *       pointerArray = HlpPointerArrayNew( channelCount )
 *
 *       for i = 0 to channelCount - 1
 *         if ScpChGetEnabled( handle , i )
 *           buffers[ i ] = allocate buffer/array
 *           HlpPointerArraySet( pointerArray , i , pointer of buffers[ i ] )
 *         end
 *       end
 *
 *       ScpGetData( handle , pointerArray , channelCount , ... )
 *
 *       HlpPointerArrayDelete( pointerArray )
 * \endcode
 *       The data is now available in \c buffers.
 *
 * \see ScpGetData
 */

// Workaround: Without this line Doxygen adds the documentation below to the group above.

/**
 * \brief Create a new pointer array.
 *
 * The pointer array is initialized with \c NULL pointers.
 *
 * \param[in] dwLength The requested length of the pointer array, \c 1 .. \c #LIBTIEPIE_POINTER_ARRAY_MAX_LENGTH.
 * \return A pointer to the pointer array.
 * \par Status values
 *   <table class="params">
 *   <tr><td>\ref LIBTIEPIESTATUS_INVALID_VALUE "INVALID_VALUE"</td><td>The requested length is invalid.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_UNSUCCESSFUL "UNSUCCESSFUL"</td> <td>An error occurred during execution of the last called function.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_SUCCESS "SUCCESS"</td>      <td>The function executed successfully.</td></tr>
 *   </table>
 * \since 0.4.1
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef LibTiePiePointerArray_t(*LibTiePieHlpPointerArrayNew_t)( uint32_t dwLength );
#else
LibTiePiePointerArray_t HlpPointerArrayNew( uint32_t dwLength );
#endif

/**
 * \brief Set a pointer at a specified index in a specified pointer array.
 *
 * \param[in] pArray A pointer identifying the pointer array.
 * \param[in] dwIndex The requested array index.
 * \param[in] pPointer The pointer value to set.
 * \par Status values
 *   <table class="params">
 *   <tr><td>\ref LIBTIEPIESTATUS_UNSUCCESSFUL "UNSUCCESSFUL"</td><td>The pointer to the array is invalid.</td></tr>
 *   <tr><td>\ref LIBTIEPIESTATUS_SUCCESS "SUCCESS"</td>     <td>The function executed successfully.</td></tr>
 *   </table>
 * \since 0.4.1
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef void(*LibTiePieHlpPointerArraySet_t)( LibTiePiePointerArray_t pArray , uint32_t dwIndex , void* pPointer );
#else
void HlpPointerArraySet( LibTiePiePointerArray_t pArray , uint32_t dwIndex , void* pPointer );
#endif

/**
 * \brief Delete an existing pointer array.
 *
 * \param[in] pArray A pointer identifying the pointer array.
 * \par Status values
 *   <table class="params">
 *   <tr><td>\ref LIBTIEPIESTATUS_SUCCESS "SUCCESS"</td><td>The function executed successfully.</td></tr>
 *   </table>
 * \since 0.4.1
 */
#ifdef LIBTIEPIE_DYNAMIC
typedef void(*LibTiePieHlpPointerArrayDelete_t)( LibTiePiePointerArray_t pArray );
#else
void HlpPointerArrayDelete( LibTiePiePointerArray_t pArray );
#endif

/**
 * \}
 * \}
 * \}
 */

#ifdef __cplusplus
}
#endif

#endif
