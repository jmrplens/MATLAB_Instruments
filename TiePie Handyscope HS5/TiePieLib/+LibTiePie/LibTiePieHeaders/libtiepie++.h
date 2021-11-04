/**
 * \file libtiepie++.h
 * \brief C++ header with wrapper classes for libtiepie.
 */

#ifndef _LIBTIEPIE___H_
#define _LIBTIEPIE___H_

#include <vector>
#include <string>
#include <stdexcept>
#include "libtiepie.h"

namespace LibTiePie
{
  typedef TpDeviceHandle_t Handle_t;

  class Exception : public std::runtime_error
  {
    protected:
      const LibTiePieStatus_t m_status;

    public:
      Exception( LibTiePieStatus_t Status , const std::string& sWhat ) :
        std::runtime_error( sWhat ) ,
        m_status( Status )
      {
      }

      LibTiePieStatus_t status() const
      {
        return m_status;
      }
  };

  class UnsuccessfulException : public Exception
  {
    public:
      UnsuccessfulException() :
        Exception( LIBTIEPIESTATUS_UNSUCCESSFUL , "Unsuccessful" )
      {
      }
  };

  class NotSupportedException : public Exception
  {
    public:
      NotSupportedException() :
        Exception( LIBTIEPIESTATUS_NOT_SUPPORTED , "Not supported" )
      {
      }
  };

  class InvalidHandleException : public Exception
  {
    public:
      InvalidHandleException() :
        Exception( LIBTIEPIESTATUS_INVALID_HANDLE , "Invalid handle" )
      {
      }
  };

  class InvalidValueException : public Exception
  {
    public:
      InvalidValueException() :
        Exception( LIBTIEPIESTATUS_INVALID_VALUE , "Invalid value" )
      {
      }
  };

  class InvalidChannelException : public Exception
  {
    public:
      InvalidChannelException() :
        Exception( LIBTIEPIESTATUS_INVALID_CHANNEL , "Invalid channel" )
      {
      }
  };

  class InvalidTriggerSourceException : public Exception
  {
    public:
      InvalidTriggerSourceException() :
        Exception( LIBTIEPIESTATUS_INVALID_TRIGGER_SOURCE , "Invalid trigger source" )
      {
      }
  };

  class InvalidDeviceTypeException : public Exception
  {
    public:
      InvalidDeviceTypeException() :
        Exception( LIBTIEPIESTATUS_INVALID_DEVICE_TYPE , "Invalid device type" )
      {
      }
  };

  class InvalidDeviceIndexException : public Exception
  {
    public:
      InvalidDeviceIndexException() :
        Exception( LIBTIEPIESTATUS_INVALID_DEVICE_INDEX , "Invalid device index" )
      {
      }
  };

  class InvalidProductIdException : public Exception
  {
    public:
      InvalidProductIdException() :
        Exception( LIBTIEPIESTATUS_INVALID_PRODUCT_ID , "Invalid product id" )
      {
      }
  };

  class InvalidDeviceSerialNumberException : public Exception
  {
    public:
      InvalidDeviceSerialNumberException() :
        Exception( LIBTIEPIESTATUS_INVALID_DEVICE_SERIALNUMBER , "Invalid device serialnumber" )
      {
      }
  };

  class ObjectGoneException : public Exception
  {
    public:
      ObjectGoneException() :
        Exception( LIBTIEPIESTATUS_OBJECT_GONE , "Object gone" )
      {
      }
  };

  typedef ObjectGoneException DeviceGoneException;

  class InternalAddressException : public Exception
  {
    public:
      InternalAddressException() :
        Exception( LIBTIEPIESTATUS_INTERNAL_ADDRESS , "Internal address" )
      {
      }
  };

  class NotControllableException : public Exception
  {
    public:
      NotControllableException() :
        Exception( LIBTIEPIESTATUS_NOT_CONTROLLABLE , "Not controllable" )
      {
      }
  };

  class BitErrorException : public Exception
  {
    public:
      BitErrorException() :
        Exception( LIBTIEPIESTATUS_BIT_ERROR , "Bit error" )
      {
      }
  };

  class NoAcknowledgeException : public Exception
  {
    public:
      NoAcknowledgeException() :
        Exception( LIBTIEPIESTATUS_NO_ACKNOWLEDGE , "No acknowledge" )
      {
      }
  };

  class InvalidContainedDeviceSerialNumberException : public Exception
  {
    public:
      InvalidContainedDeviceSerialNumberException() :
        Exception( LIBTIEPIESTATUS_INVALID_CONTAINED_DEVICE_SERIALNUMBER , "Invalid contained device serialnumber" )
      {
      }
  };

  class InvalidInputException : public Exception
  {
    public:
      InvalidInputException() :
        Exception( LIBTIEPIESTATUS_INVALID_INPUT , "Invalid input" )
      {
      }
  };

  class InvalidOutputException : public Exception
  {
    public:
      InvalidOutputException() :
        Exception( LIBTIEPIESTATUS_INVALID_OUTPUT , "Invalid output" )
      {
      }
  };

  class InvalidDriverException : public Exception
  {
    public:
      InvalidDriverException() :
        Exception( LIBTIEPIESTATUS_INVALID_DRIVER , "Invalid driver" )
      {
      }
  };

  class NotAvailableException : public Exception
  {
    public:
      NotAvailableException() :
        Exception( LIBTIEPIESTATUS_NOT_AVAILABLE , "Not available" )
      {
      }
  };

  class InvalidFirmwareException : public Exception
  {
    public:
      InvalidFirmwareException() :
        Exception( LIBTIEPIESTATUS_INVALID_FIRMWARE , "Invalid firmware" )
      {
      }
  };

  class InvalidIndexException : public Exception
  {
    public:
      InvalidIndexException() :
        Exception( LIBTIEPIESTATUS_INVALID_INDEX , "Invalid index" )
      {
      }
  };

  class InvalidEepromException : public Exception
  {
    public:
      InvalidEepromException() :
        Exception( LIBTIEPIESTATUS_INVALID_EEPROM , "Invalid eeprom" )
      {
      }
  };

  class InitializationFailedException : public Exception
  {
    public:
      InitializationFailedException() :
        Exception( LIBTIEPIESTATUS_INITIALIZATION_FAILED , "Initialization failed" )
      {
      }
  };

  class LibraryNotInitializedException : public Exception
  {
    public:
      LibraryNotInitializedException() :
        Exception( LIBTIEPIESTATUS_LIBRARY_NOT_INITIALIZED , "Library not initialized" )
      {
      }
  };

  class NoTriggerEnabledException : public Exception
  {
    public:
      NoTriggerEnabledException() :
        Exception( LIBTIEPIESTATUS_NO_TRIGGER_ENABLED , "No trigger enabled" )
      {
      }
  };

  class SynchronizationFailedException : public Exception
  {
    public:
      SynchronizationFailedException() :
        Exception( LIBTIEPIESTATUS_SYNCHRONIZATION_FAILED , "Synchronization failed" )
      {
      }
  };

  class InvalidHS56CombinedDeviceException : public Exception
  {
    public:
      InvalidHS56CombinedDeviceException() :
        Exception( LIBTIEPIESTATUS_INVALID_HS56_COMBINED_DEVICE , "Invalid hs56 combined device" )
      {
      }
  };

  class MeasurementRunningException : public Exception
  {
    public:
      MeasurementRunningException() :
        Exception( LIBTIEPIESTATUS_MEASUREMENT_RUNNING , "Measurement running" )
      {
      }
  };

  class InitializationError10001Exception : public Exception
  {
    public:
      InitializationError10001Exception() :
        Exception( LIBTIEPIESTATUS_INITIALIZATION_ERROR_10001 , "Initialization error 10001" )
      {
      }
  };

  class InitializationError10002Exception : public Exception
  {
    public:
      InitializationError10002Exception() :
        Exception( LIBTIEPIESTATUS_INITIALIZATION_ERROR_10002 , "Initialization error 10002" )
      {
      }
  };

  class InitializationError10003Exception : public Exception
  {
    public:
      InitializationError10003Exception() :
        Exception( LIBTIEPIESTATUS_INITIALIZATION_ERROR_10003 , "Initialization error 10003" )
      {
      }
  };

  class InitializationError10004Exception : public Exception
  {
    public:
      InitializationError10004Exception() :
        Exception( LIBTIEPIESTATUS_INITIALIZATION_ERROR_10004 , "Initialization error 10004" )
      {
      }
  };

  class InitializationError10005Exception : public Exception
  {
    public:
      InitializationError10005Exception() :
        Exception( LIBTIEPIESTATUS_INITIALIZATION_ERROR_10005 , "Initialization error 10005" )
      {
      }
  };

  class InitializationError10006Exception : public Exception
  {
    public:
      InitializationError10006Exception() :
        Exception( LIBTIEPIESTATUS_INITIALIZATION_ERROR_10006 , "Initialization error 10006" )
      {
      }
  };

  template<typename T> class Buffer
  {
    protected:
      T* m_buffer;

    public:
      Buffer( size_t Length ) :
        m_buffer( Length > 0 ? new T[ Length ] : 0 )
      {
      }

      ~Buffer()
      {
        if( m_buffer )
          delete [] m_buffer;
      }

      const T* operator*() const
      {
        return m_buffer;
      }

      T* operator*()
      {
        return m_buffer;
      }
  };

  template<class T> class ObjectList
  {
    protected:
      std::vector<T*> m_items;

    public:
      typedef typename std::vector<T*>::size_type size_type;

      ObjectList( Handle_t hDevice , size_type Length )
      {
        for( size_type i = 0 ; i < Length ; i++ )
          m_items.push_back( new T( hDevice , i ) );
      }

      ObjectList( Handle_t hDevice , uint16_t wCh , size_type Length )
      {
        for( size_type i = 0 ; i < Length ; i++ )
          m_items.push_back( new T( hDevice , wCh , i ) );
      }

      ~ObjectList()
      {
        for( typename std::vector<T*>::iterator it = m_items.begin() , itEnd = m_items.end() ; it != itEnd ; it++ )
          delete *it;
      }

      size_type count() const
      {
        return m_items.size();
      }

      T& operator[]( size_type Index ) const
      {
        if( Index < count() )
          return *m_items[ Index ];

        throw std::out_of_range( "Index out of range" );
      }
  };

  class Object;

  class Library
  {
    public:
      static void init()
      {
        LibInit();
      }

      static bool isInitialized()
      {
        return ( LibIsInitialized() != BOOL8_FALSE );
      }

      static void exit()
      {
        LibExit();
      }

      static TpVersion_t version()
      {
        return LibGetVersion();
      }

      static std::string versionExtra()
      {
        const char* result = LibGetVersionExtra();
        return result ? std::string( result ) : std::string();
      }

      static const std::vector<uint8_t> config()
      {
        const uint32_t dwBufferLength = LibGetConfig( 0 , 0 );
        Buffer<uint8_t> tmp( dwBufferLength );
        LibGetConfig( *tmp , dwBufferLength );
        return std::vector<uint8_t>( *tmp , *tmp + dwBufferLength );
      }

      static LibTiePieStatus_t lastStatus()
      {
        return LibGetLastStatus();
      }

      static std::string lastStatusStr()
      {
        const char* result = LibGetLastStatusStr();
        return result ? std::string( result ) : std::string();
      }

      static void checkLastStatusAndThrowOnError()
      {
         LibTiePieStatus_t status = Library::lastStatus();

         if( status < 0 ) // Error's only.
           switch( status )
           {
             case LIBTIEPIESTATUS_UNSUCCESSFUL:
               throw UnsuccessfulException();
             case LIBTIEPIESTATUS_NOT_SUPPORTED:
               throw NotSupportedException();
             case LIBTIEPIESTATUS_INVALID_HANDLE:
               throw InvalidHandleException();
             case LIBTIEPIESTATUS_INVALID_VALUE:
               throw InvalidValueException();
             case LIBTIEPIESTATUS_INVALID_CHANNEL:
               throw InvalidChannelException();
             case LIBTIEPIESTATUS_INVALID_TRIGGER_SOURCE:
               throw InvalidTriggerSourceException();
             case LIBTIEPIESTATUS_INVALID_DEVICE_TYPE:
               throw InvalidDeviceTypeException();
             case LIBTIEPIESTATUS_INVALID_DEVICE_INDEX:
               throw InvalidDeviceIndexException();
             case LIBTIEPIESTATUS_INVALID_PRODUCT_ID:
               throw InvalidProductIdException();
             case LIBTIEPIESTATUS_INVALID_DEVICE_SERIALNUMBER:
               throw InvalidDeviceSerialNumberException();
             case LIBTIEPIESTATUS_OBJECT_GONE:
               throw ObjectGoneException();
             case LIBTIEPIESTATUS_INTERNAL_ADDRESS:
               throw InternalAddressException();
             case LIBTIEPIESTATUS_NOT_CONTROLLABLE:
               throw NotControllableException();
             case LIBTIEPIESTATUS_BIT_ERROR:
               throw BitErrorException();
             case LIBTIEPIESTATUS_NO_ACKNOWLEDGE:
               throw NoAcknowledgeException();
             case LIBTIEPIESTATUS_INVALID_CONTAINED_DEVICE_SERIALNUMBER:
               throw InvalidContainedDeviceSerialNumberException();
             case LIBTIEPIESTATUS_INVALID_INPUT:
               throw InvalidInputException();
             case LIBTIEPIESTATUS_INVALID_OUTPUT:
               throw InvalidOutputException();
             case LIBTIEPIESTATUS_INVALID_DRIVER:
               throw InvalidDriverException();
             case LIBTIEPIESTATUS_NOT_AVAILABLE:
               throw NotAvailableException();
             case LIBTIEPIESTATUS_INVALID_FIRMWARE:
               throw InvalidFirmwareException();
             case LIBTIEPIESTATUS_INVALID_INDEX:
               throw InvalidIndexException();
             case LIBTIEPIESTATUS_INVALID_EEPROM:
               throw InvalidEepromException();
             case LIBTIEPIESTATUS_INITIALIZATION_FAILED:
               throw InitializationFailedException();
             case LIBTIEPIESTATUS_LIBRARY_NOT_INITIALIZED:
               throw LibraryNotInitializedException();
             case LIBTIEPIESTATUS_NO_TRIGGER_ENABLED:
               throw NoTriggerEnabledException();
             case LIBTIEPIESTATUS_SYNCHRONIZATION_FAILED:
               throw SynchronizationFailedException();
             case LIBTIEPIESTATUS_INVALID_HS56_COMBINED_DEVICE:
               throw InvalidHS56CombinedDeviceException();
             case LIBTIEPIESTATUS_MEASUREMENT_RUNNING:
               throw MeasurementRunningException();
             case LIBTIEPIESTATUS_INITIALIZATION_ERROR_10001:
               throw InitializationError10001Exception();
             case LIBTIEPIESTATUS_INITIALIZATION_ERROR_10002:
               throw InitializationError10002Exception();
             case LIBTIEPIESTATUS_INITIALIZATION_ERROR_10003:
               throw InitializationError10003Exception();
             case LIBTIEPIESTATUS_INITIALIZATION_ERROR_10004:
               throw InitializationError10004Exception();
             case LIBTIEPIESTATUS_INITIALIZATION_ERROR_10005:
               throw InitializationError10005Exception();
             case LIBTIEPIESTATUS_INITIALIZATION_ERROR_10006:
               throw InitializationError10006Exception();
             default:
               throw Exception( status , Library::lastStatusStr() );
           }
      }

      template<class _result, class _class> static _result* createObject( Handle_t handle )
      {
        return new _class( handle );
      }
  };

  class Object
  {
    protected:
      const Handle_t m_handle;

    public:
      Object( Handle_t hHandle ) :
        m_handle( hHandle )
      {
      }

      virtual ~Object()
      {
        ObjClose( m_handle );
      }

      Handle_t handle() const
      {
        return m_handle;
      }

      bool isRemoved() const
      {
        const bool result = ( ObjIsRemoved( m_handle ) != BOOL8_FALSE );
        Library::checkLastStatusAndThrowOnError();

        return result;
      }

      uint64_t interfaces() const
      {
        const uint64_t result = ObjGetInterfaces( m_handle );
        Library::checkLastStatusAndThrowOnError();

        return result;
      }

      void setEventCallback( TpCallbackEvent_t pCallback , void* pData )
      {
        ObjSetEventCallback( m_handle , pCallback , pData );
        Library::checkLastStatusAndThrowOnError();
      }

      bool getEvent( uint32_t* pEvent , uint32_t* pValue ) const
      {
        const bool result = ( ObjGetEvent( m_handle , pEvent , pValue ) != BOOL8_FALSE );
        Library::checkLastStatusAndThrowOnError();

        return result;
      }

#ifdef LIBTIEPIE_LINUX
      void setEventEvent( int fdEvent )
      {
        ObjSetEventEvent( m_handle , fdEvent );
        Library::checkLastStatusAndThrowOnError();
      }
#endif

#ifdef LIBTIEPIE_WINDOWS
      void setEventEvent( HANDLE hEvent )
      {
        ObjSetEventEvent( m_handle , hEvent );
        Library::checkLastStatusAndThrowOnError();
      }

      void setEventWindowHandle( HWND hWnd )
      {
        ObjSetEventWindowHandle( m_handle , hWnd );
        Library::checkLastStatusAndThrowOnError();
      }
#endif
  };

  class Device;
  class Oscilloscope;
  class Generator;
  class I2CHost;

  class Server : public Object
  {
    public:
      Server( Handle_t hServer ) :
        Object( hServer )
      {
      }

      bool connect( bool bAsync )
      {
        const bool result = ( SrvConnect( m_handle , bAsync ? BOOL8_TRUE : BOOL8_FALSE ) != BOOL8_FALSE );
        Library::checkLastStatusAndThrowOnError();

        return result;
      }

      bool disconnect( bool bForce )
      {
        const bool result = ( SrvDisconnect( m_handle , bForce ? BOOL8_TRUE : BOOL8_FALSE ) != BOOL8_FALSE );
        Library::checkLastStatusAndThrowOnError();

        return result;
      }

      bool remove( bool bForce )
      {
        const bool result = ( SrvRemove( m_handle , bForce ? BOOL8_TRUE : BOOL8_FALSE ) != BOOL8_FALSE );
        Library::checkLastStatusAndThrowOnError();

        return result;
      }

      uint32_t status() const
      {
        const uint32_t result = SrvGetStatus( m_handle );
        Library::checkLastStatusAndThrowOnError();

        return result;
      }

      uint32_t lastError() const
      {
        const uint32_t result = SrvGetLastError( m_handle );
        Library::checkLastStatusAndThrowOnError();

        return result;
      }

      const std::string url() const
      {
        const uint32_t dwLength = SrvGetURL( m_handle , 0 , 0 ) + 1;
        Library::checkLastStatusAndThrowOnError();
        Buffer<char> s( dwLength );
        SrvGetURL( m_handle , *s , dwLength );
        Library::checkLastStatusAndThrowOnError();
        return *s;
      }

      const std::string id() const
      {
        const uint32_t dwLength = SrvGetID( m_handle , 0 , 0 ) + 1;
        Library::checkLastStatusAndThrowOnError();
        Buffer<char> s( dwLength );
        SrvGetID( m_handle , *s , dwLength );
        Library::checkLastStatusAndThrowOnError();
        return *s;
      }

      uint32_t ipv4Address() const
      {
        const uint32_t result = SrvGetIPv4Address( m_handle );
        Library::checkLastStatusAndThrowOnError();

        return result;
      }

      uint16_t ipPort() const
      {
        const uint16_t result = SrvGetIPPort( m_handle );
        Library::checkLastStatusAndThrowOnError();

        return result;
      }

      const std::string name() const
      {
        const uint32_t dwLength = SrvGetName( m_handle , 0 , 0 ) + 1;
        Library::checkLastStatusAndThrowOnError();
        Buffer<char> s( dwLength );
        SrvGetName( m_handle , *s , dwLength );
        Library::checkLastStatusAndThrowOnError();
        return *s;
      }

      const std::string description() const
      {
        const uint32_t dwLength = SrvGetDescription( m_handle , 0 , 0 ) + 1;
        Library::checkLastStatusAndThrowOnError();
        Buffer<char> s( dwLength );
        SrvGetDescription( m_handle , *s , dwLength );
        Library::checkLastStatusAndThrowOnError();
        return *s;
      }

      TpVersion_t version() const
      {
        const TpVersion_t result = SrvGetVersion( m_handle );
        Library::checkLastStatusAndThrowOnError();

        return result;
      }

      const std::string versionExtra() const
      {
        const uint32_t dwLength = SrvGetVersionExtra( m_handle , 0 , 0 ) + 1;
        Library::checkLastStatusAndThrowOnError();
        Buffer<char> s( dwLength );
        SrvGetVersionExtra( m_handle , *s , dwLength );
        Library::checkLastStatusAndThrowOnError();
        return *s;
      }
  };

  class Network
  {
    public:
      class Servers
      {

        static Server* add( const std::string& url )
        {
          Handle_t handle = LIBTIEPIE_HANDLE_INVALID;
          const bool result = NetSrvAdd( url.c_str() , LIBTIEPIE_STRING_LENGTH_NULL_TERMINATED , &handle ) != BOOL8_FALSE;
          Library::checkLastStatusAndThrowOnError();
          return result ? new Server( handle ) : 0;
        }

        static bool remove( const std::string& url , bool bForce )
        {
          const bool result = ( NetSrvRemove( url.c_str() , LIBTIEPIE_STRING_LENGTH_NULL_TERMINATED , bForce ? BOOL8_TRUE : BOOL8_FALSE ) != BOOL8_FALSE );
          Library::checkLastStatusAndThrowOnError();

          return result;
        }

        static uint32_t count()
        {
          const uint32_t result = NetSrvGetCount();
          Library::checkLastStatusAndThrowOnError();

          return result;
        }

        static Server* getByIndex( uint32_t dwIndex )
        {
          const Handle_t result = NetSrvGetByIndex( dwIndex );
          Library::checkLastStatusAndThrowOnError();

          return new Server( result );
        }

        static Server* getByURL( const std::string& url )
        {
          const Handle_t result = NetSrvGetByURL( url.c_str() , LIBTIEPIE_STRING_LENGTH_NULL_TERMINATED );
          Library::checkLastStatusAndThrowOnError();

          return new Server( result );
        }

        static void setCallbackAdded( TpCallbackHandle_t pCallback , void* pData )
        {
          NetSrvSetCallbackAdded( pCallback , pData );
          Library::checkLastStatusAndThrowOnError();
        }

#ifdef LIBTIEPIE_LINUX
        static void setEventAdded( int fdEvent )
        {
          NetSrvSetEventAdded( fdEvent );
          Library::checkLastStatusAndThrowOnError();
        }
#endif

#ifdef LIBTIEPIE_WINDOWS
        static void setEventAdded( HANDLE hEvent )
        {
          NetSrvSetEventAdded( hEvent );
          Library::checkLastStatusAndThrowOnError();
        }

        static void setMessageAdded( HWND hWnd )
        {
          NetSrvSetMessageAdded( hWnd );
          Library::checkLastStatusAndThrowOnError();
        }
#endif
      };

      static bool autoDetectEnabled()
      {
        const bool result = ( NetGetAutoDetectEnabled() != BOOL8_FALSE );
        Library::checkLastStatusAndThrowOnError();

        return result;
      }

      static bool setAutoDetectEnabled( bool bEnable )
      {
        const bool result = ( NetSetAutoDetectEnabled( bEnable ? BOOL8_TRUE : BOOL8_FALSE ) != BOOL8_FALSE );
        Library::checkLastStatusAndThrowOnError();

        return result;
      }
  };

  class TriggerInput;

  class TriggerInputs : public ObjectList<TriggerInput>
  {
    protected:
      const Handle_t m_handle;

    public:
      TriggerInputs( Handle_t hDevice , size_type Length ) :
        ObjectList<TriggerInput>( hDevice , Length ) ,
        m_handle( hDevice )
      {
      }

      TriggerInput* getById( uint32_t dwId ) const
      {
        const uint16_t wIndex = DevTrGetInputIndexById( m_handle , dwId );

        Library::checkLastStatusAndThrowOnError();

        if( wIndex != LIBTIEPIE_TRIGGERIO_INDEX_INVALID )
          return m_items[ wIndex ];
        else
          return 0;
      }
  };

  class TriggerOutput;

  class TriggerOutputs : public ObjectList<TriggerOutput>
  {
    protected:
      const Handle_t m_handle;

    public:
      TriggerOutputs( Handle_t hDevice , size_type Length ) :
        ObjectList<TriggerOutput>( hDevice , Length ) ,
        m_handle( hDevice )
      {
      }

      TriggerOutput* getById( uint32_t dwId ) const
      {
        const uint16_t wIndex = DevTrGetOutputIndexById( m_handle , dwId );

        Library::checkLastStatusAndThrowOnError();

        if( wIndex != LIBTIEPIE_TRIGGERIO_INDEX_INVALID )
          return m_items[ wIndex ];
        else
          return 0;
      }
  };

  class Device : public Object
  {
    public:
      const TriggerInputs triggerInputs;
      const TriggerOutputs triggerOutputs;

      Device( Handle_t hDevice ) :
        Object( hDevice ) ,
        triggerInputs( hDevice , DevTrGetInputCount( hDevice ) ) ,
        triggerOutputs( hDevice , DevTrGetOutputCount( hDevice ) )
      {
      }

      TpVersion_t driverVersion() const
      {
        const TpVersion_t result = DevGetDriverVersion( m_handle );
        Library::checkLastStatusAndThrowOnError();

        return result;
      }

      TpVersion_t firmwareVersion() const
      {
        const TpVersion_t result = DevGetFirmwareVersion( m_handle );
        Library::checkLastStatusAndThrowOnError();

        return result;
      }

      TpDate_t calibrationDate() const
      {
        const TpDate_t result = DevGetCalibrationDate( m_handle );
        Library::checkLastStatusAndThrowOnError();

        return result;
      }

      const std::string calibrationToken() const
      {
        const uint32_t dwLength = DevGetCalibrationToken( m_handle , 0 , 0 ) + 1;
        Library::checkLastStatusAndThrowOnError();
        Buffer<char> s( dwLength );
        DevGetCalibrationToken( m_handle , *s , dwLength );
        Library::checkLastStatusAndThrowOnError();
        return *s;
      }

      uint32_t serialNumber() const
      {
        const uint32_t result = DevGetSerialNumber( m_handle );
        Library::checkLastStatusAndThrowOnError();

        return result;
      }

      uint32_t ipv4Address() const
      {
        const uint32_t result = DevGetIPv4Address( m_handle );
        Library::checkLastStatusAndThrowOnError();

        return result;
      }

      uint16_t ipPort() const
      {
        const uint16_t result = DevGetIPPort( m_handle );
        Library::checkLastStatusAndThrowOnError();

        return result;
      }

      uint32_t productId() const
      {
        const uint32_t result = DevGetProductId( m_handle );
        Library::checkLastStatusAndThrowOnError();

        return result;
      }

      uint32_t vendorId() const
      {
        const uint32_t result = DevGetVendorId( m_handle );
        Library::checkLastStatusAndThrowOnError();

        return result;
      }

      uint32_t type() const
      {
        const uint32_t result = DevGetType( m_handle );
        Library::checkLastStatusAndThrowOnError();

        return result;
      }

      const std::string name() const
      {
        const uint32_t dwLength = DevGetName( m_handle , 0 , 0 ) + 1;
        Library::checkLastStatusAndThrowOnError();
        Buffer<char> s( dwLength );
        DevGetName( m_handle , *s , dwLength );
        Library::checkLastStatusAndThrowOnError();
        return *s;
      }

      const std::string nameShort() const
      {
        const uint32_t dwLength = DevGetNameShort( m_handle , 0 , 0 ) + 1;
        Library::checkLastStatusAndThrowOnError();
        Buffer<char> s( dwLength );
        DevGetNameShort( m_handle , *s , dwLength );
        Library::checkLastStatusAndThrowOnError();
        return *s;
      }

      const std::string nameShortest() const
      {
        const uint32_t dwLength = DevGetNameShortest( m_handle , 0 , 0 ) + 1;
        Library::checkLastStatusAndThrowOnError();
        Buffer<char> s( dwLength );
        DevGetNameShortest( m_handle , *s , dwLength );
        Library::checkLastStatusAndThrowOnError();
        return *s;
      }

      bool hasBattery() const
      {
        const bool result = ( DevHasBattery( m_handle ) != BOOL8_FALSE );
        Library::checkLastStatusAndThrowOnError();

        return result;
      }

      int8_t batteryCharge() const
      {
        const int8_t result = DevGetBatteryCharge( m_handle );
        Library::checkLastStatusAndThrowOnError();

        return result;
      }

      int32_t batteryTimeToEmpty() const
      {
        const int32_t result = DevGetBatteryTimeToEmpty( m_handle );
        Library::checkLastStatusAndThrowOnError();

        return result;
      }

      int32_t batteryTimeToFull() const
      {
        const int32_t result = DevGetBatteryTimeToFull( m_handle );
        Library::checkLastStatusAndThrowOnError();

        return result;
      }

      bool isBatteryChargerConnected() const
      {
        const bool result = ( DevIsBatteryChargerConnected( m_handle ) != BOOL8_FALSE );
        Library::checkLastStatusAndThrowOnError();

        return result;
      }

      bool isBatteryCharging() const
      {
        const bool result = ( DevIsBatteryCharging( m_handle ) != BOOL8_FALSE );
        Library::checkLastStatusAndThrowOnError();

        return result;
      }

      bool isBatteryBroken() const
      {
        const bool result = ( DevIsBatteryBroken( m_handle ) != BOOL8_FALSE );
        Library::checkLastStatusAndThrowOnError();

        return result;
      }

      void setCallbackRemoved( TpCallback_t pCallback , void* pData )
      {
        DevSetCallbackRemoved( m_handle , pCallback , pData );
        Library::checkLastStatusAndThrowOnError();
      }

#ifdef LIBTIEPIE_LINUX
      void setEventRemoved( int fdEvent )
      {
        DevSetEventRemoved( m_handle , fdEvent );
        Library::checkLastStatusAndThrowOnError();
      }
#endif

#ifdef LIBTIEPIE_WINDOWS
      void setEventRemoved( HANDLE hEvent )
      {
        DevSetEventRemoved( m_handle , hEvent );
        Library::checkLastStatusAndThrowOnError();
      }

      void setMessageRemoved( HWND hWnd , WPARAM wParam , LPARAM lParam )
      {
        DevSetMessageRemoved( m_handle , hWnd , wParam , lParam );
        Library::checkLastStatusAndThrowOnError();
      }
#endif
  };

  class TriggerInput
  {
    protected:
      const Handle_t m_handle;
      const uint16_t m_input;

    public:
      TriggerInput( Handle_t hDevice , uint16_t wInput ) :
        m_handle( hDevice ) ,
        m_input( wInput )
      {
      }

      bool isTriggered() const
      {
        const bool result = ( ScpTrInIsTriggered( m_handle , m_input ) != BOOL8_FALSE );
        Library::checkLastStatusAndThrowOnError();

        return result;
      }

      bool enabled() const
      {
        const bool result = ( DevTrInGetEnabled( m_handle , m_input ) != BOOL8_FALSE );
        Library::checkLastStatusAndThrowOnError();

        return result;
      }

      bool setEnabled( bool bEnable )
      {
        const bool result = ( DevTrInSetEnabled( m_handle , m_input , bEnable ? BOOL8_TRUE : BOOL8_FALSE ) != BOOL8_FALSE );
        Library::checkLastStatusAndThrowOnError();

        return result;
      }

      uint64_t kinds() const
      {
        const uint64_t result = DevTrInGetKinds( m_handle , m_input );
        Library::checkLastStatusAndThrowOnError();

        return result;
      }

      uint64_t getKinds( uint32_t dwMeasureMode ) const
      {
        const uint64_t result = ScpTrInGetKindsEx( m_handle , m_input , dwMeasureMode );
        Library::checkLastStatusAndThrowOnError();

        return result;
      }

      uint64_t kind() const
      {
        const uint64_t result = DevTrInGetKind( m_handle , m_input );
        Library::checkLastStatusAndThrowOnError();

        return result;
      }

      uint64_t setKind( uint64_t qwKind )
      {
        const uint64_t result = DevTrInSetKind( m_handle , m_input , qwKind );
        Library::checkLastStatusAndThrowOnError();

        return result;
      }

      bool isAvailable() const
      {
        const bool result = ( DevTrInIsAvailable( m_handle , m_input ) != BOOL8_FALSE );
        Library::checkLastStatusAndThrowOnError();

        return result;
      }

      bool isAvailable( uint32_t dwMeasureMode ) const
      {
        const bool result = ( ScpTrInIsAvailableEx( m_handle , m_input , dwMeasureMode ) != BOOL8_FALSE );
        Library::checkLastStatusAndThrowOnError();

        return result;
      }

      uint32_t id() const
      {
        const uint32_t result = DevTrInGetId( m_handle , m_input );
        Library::checkLastStatusAndThrowOnError();

        return result;
      }

      const std::string name() const
      {
        const uint32_t dwLength = DevTrInGetName( m_handle , m_input , 0 , 0 ) + 1;
        Library::checkLastStatusAndThrowOnError();
        Buffer<char> s( dwLength );
        DevTrInGetName( m_handle , m_input , *s , dwLength );
        Library::checkLastStatusAndThrowOnError();
        return *s;
      }
  };

  class TriggerOutput
  {
    protected:
      const Handle_t m_handle;
      const uint16_t m_output;

    public:
      TriggerOutput( Handle_t hDevice , uint16_t wOutput ) :
        m_handle( hDevice ) ,
        m_output( wOutput )
      {
      }

      bool enabled() const
      {
        const bool result = ( DevTrOutGetEnabled( m_handle , m_output ) != BOOL8_FALSE );
        Library::checkLastStatusAndThrowOnError();

        return result;
      }

      bool setEnabled( bool bEnable )
      {
        const bool result = ( DevTrOutSetEnabled( m_handle , m_output , bEnable ? BOOL8_TRUE : BOOL8_FALSE ) != BOOL8_FALSE );
        Library::checkLastStatusAndThrowOnError();

        return result;
      }

      uint64_t events() const
      {
        const uint64_t result = DevTrOutGetEvents( m_handle , m_output );
        Library::checkLastStatusAndThrowOnError();

        return result;
      }

      uint64_t event() const
      {
        const uint64_t result = DevTrOutGetEvent( m_handle , m_output );
        Library::checkLastStatusAndThrowOnError();

        return result;
      }

      uint64_t setEvent( uint64_t qwEvent )
      {
        const uint64_t result = DevTrOutSetEvent( m_handle , m_output , qwEvent );
        Library::checkLastStatusAndThrowOnError();

        return result;
      }

      uint32_t id() const
      {
        const uint32_t result = DevTrOutGetId( m_handle , m_output );
        Library::checkLastStatusAndThrowOnError();

        return result;
      }

      const std::string name() const
      {
        const uint32_t dwLength = DevTrOutGetName( m_handle , m_output , 0 , 0 ) + 1;
        Library::checkLastStatusAndThrowOnError();
        Buffer<char> s( dwLength );
        DevTrOutGetName( m_handle , m_output , *s , dwLength );
        Library::checkLastStatusAndThrowOnError();
        return *s;
      }

      bool trigger()
      {
        const bool result = ( DevTrOutTrigger( m_handle , m_output ) != BOOL8_FALSE );
        Library::checkLastStatusAndThrowOnError();

        return result;
      }
  };

  class OscilloscopeChannel;

  class Oscilloscope : public Device
  {
    public:
      typedef ObjectList<OscilloscopeChannel> Channels;

      const Channels channels;

      Oscilloscope( Handle_t hDevice ) :
        Device( hDevice ) ,
        channels( hDevice , ScpGetChannelCount( hDevice ) )
      {
      }

      uint64_t getData( float** pBuffers , uint16_t wChannelCount , uint64_t qwStartIndex , uint64_t qwSampleCount )
      {
        const uint64_t result = ScpGetData( m_handle , pBuffers , wChannelCount , qwStartIndex , qwSampleCount );
        Library::checkLastStatusAndThrowOnError();

        return result;
      }

      uint64_t getData1Ch( float* pBufferCh1 , uint64_t qwStartIndex , uint64_t qwSampleCount )
      {
        const uint64_t result = ScpGetData1Ch( m_handle , pBufferCh1 , qwStartIndex , qwSampleCount );
        Library::checkLastStatusAndThrowOnError();

        return result;
      }

      uint64_t getData2Ch( float* pBufferCh1 , float* pBufferCh2 , uint64_t qwStartIndex , uint64_t qwSampleCount )
      {
        const uint64_t result = ScpGetData2Ch( m_handle , pBufferCh1 , pBufferCh2 , qwStartIndex , qwSampleCount );
        Library::checkLastStatusAndThrowOnError();

        return result;
      }

      uint64_t getData3Ch( float* pBufferCh1 , float* pBufferCh2 , float* pBufferCh3 , uint64_t qwStartIndex , uint64_t qwSampleCount )
      {
        const uint64_t result = ScpGetData3Ch( m_handle , pBufferCh1 , pBufferCh2 , pBufferCh3 , qwStartIndex , qwSampleCount );
        Library::checkLastStatusAndThrowOnError();

        return result;
      }

      uint64_t getData4Ch( float* pBufferCh1 , float* pBufferCh2 , float* pBufferCh3 , float* pBufferCh4 , uint64_t qwStartIndex , uint64_t qwSampleCount )
      {
        const uint64_t result = ScpGetData4Ch( m_handle , pBufferCh1 , pBufferCh2 , pBufferCh3 , pBufferCh4 , qwStartIndex , qwSampleCount );
        Library::checkLastStatusAndThrowOnError();

        return result;
      }

      uint64_t getData5Ch( float* pBufferCh1 , float* pBufferCh2 , float* pBufferCh3 , float* pBufferCh4 , float* pBufferCh5 , uint64_t qwStartIndex , uint64_t qwSampleCount )
      {
        const uint64_t result = ScpGetData5Ch( m_handle , pBufferCh1 , pBufferCh2 , pBufferCh3 , pBufferCh4 , pBufferCh5 , qwStartIndex , qwSampleCount );
        Library::checkLastStatusAndThrowOnError();

        return result;
      }

      uint64_t getData6Ch( float* pBufferCh1 , float* pBufferCh2 , float* pBufferCh3 , float* pBufferCh4 , float* pBufferCh5 , float* pBufferCh6 , uint64_t qwStartIndex , uint64_t qwSampleCount )
      {
        const uint64_t result = ScpGetData6Ch( m_handle , pBufferCh1 , pBufferCh2 , pBufferCh3 , pBufferCh4 , pBufferCh5 , pBufferCh6 , qwStartIndex , qwSampleCount );
        Library::checkLastStatusAndThrowOnError();

        return result;
      }

      uint64_t getData7Ch( float* pBufferCh1 , float* pBufferCh2 , float* pBufferCh3 , float* pBufferCh4 , float* pBufferCh5 , float* pBufferCh6 , float* pBufferCh7 , uint64_t qwStartIndex , uint64_t qwSampleCount )
      {
        const uint64_t result = ScpGetData7Ch( m_handle , pBufferCh1 , pBufferCh2 , pBufferCh3 , pBufferCh4 , pBufferCh5 , pBufferCh6 , pBufferCh7 , qwStartIndex , qwSampleCount );
        Library::checkLastStatusAndThrowOnError();

        return result;
      }

      uint64_t getData8Ch( float* pBufferCh1 , float* pBufferCh2 , float* pBufferCh3 , float* pBufferCh4 , float* pBufferCh5 , float* pBufferCh6 , float* pBufferCh7 , float* pBufferCh8 , uint64_t qwStartIndex , uint64_t qwSampleCount )
      {
        const uint64_t result = ScpGetData8Ch( m_handle , pBufferCh1 , pBufferCh2 , pBufferCh3 , pBufferCh4 , pBufferCh5 , pBufferCh6 , pBufferCh7 , pBufferCh8 , qwStartIndex , qwSampleCount );
        Library::checkLastStatusAndThrowOnError();

        return result;
      }

      uint64_t validPreSampleCount() const
      {
        const uint64_t result = ScpGetValidPreSampleCount( m_handle );
        Library::checkLastStatusAndThrowOnError();

        return result;
      }

      uint64_t getDataRaw( void** pBuffers , uint16_t wChannelCount , uint64_t qwStartIndex , uint64_t qwSampleCount )
      {
        const uint64_t result = ScpGetDataRaw( m_handle , pBuffers , wChannelCount , qwStartIndex , qwSampleCount );
        Library::checkLastStatusAndThrowOnError();

        return result;
      }

      uint64_t getDataRaw1Ch( void* pBufferCh1 , uint64_t qwStartIndex , uint64_t qwSampleCount )
      {
        const uint64_t result = ScpGetDataRaw1Ch( m_handle , pBufferCh1 , qwStartIndex , qwSampleCount );
        Library::checkLastStatusAndThrowOnError();

        return result;
      }

      uint64_t getDataRaw2Ch( void* pBufferCh1 , void* pBufferCh2 , uint64_t qwStartIndex , uint64_t qwSampleCount )
      {
        const uint64_t result = ScpGetDataRaw2Ch( m_handle , pBufferCh1 , pBufferCh2 , qwStartIndex , qwSampleCount );
        Library::checkLastStatusAndThrowOnError();

        return result;
      }

      uint64_t getDataRaw3Ch( void* pBufferCh1 , void* pBufferCh2 , void* pBufferCh3 , uint64_t qwStartIndex , uint64_t qwSampleCount )
      {
        const uint64_t result = ScpGetDataRaw3Ch( m_handle , pBufferCh1 , pBufferCh2 , pBufferCh3 , qwStartIndex , qwSampleCount );
        Library::checkLastStatusAndThrowOnError();

        return result;
      }

      uint64_t getDataRaw4Ch( void* pBufferCh1 , void* pBufferCh2 , void* pBufferCh3 , void* pBufferCh4 , uint64_t qwStartIndex , uint64_t qwSampleCount )
      {
        const uint64_t result = ScpGetDataRaw4Ch( m_handle , pBufferCh1 , pBufferCh2 , pBufferCh3 , pBufferCh4 , qwStartIndex , qwSampleCount );
        Library::checkLastStatusAndThrowOnError();

        return result;
      }

      uint64_t getDataRaw5Ch( void* pBufferCh1 , void* pBufferCh2 , void* pBufferCh3 , void* pBufferCh4 , void* pBufferCh5 , uint64_t qwStartIndex , uint64_t qwSampleCount )
      {
        const uint64_t result = ScpGetDataRaw5Ch( m_handle , pBufferCh1 , pBufferCh2 , pBufferCh3 , pBufferCh4 , pBufferCh5 , qwStartIndex , qwSampleCount );
        Library::checkLastStatusAndThrowOnError();

        return result;
      }

      uint64_t getDataRaw6Ch( void* pBufferCh1 , void* pBufferCh2 , void* pBufferCh3 , void* pBufferCh4 , void* pBufferCh5 , void* pBufferCh6 , uint64_t qwStartIndex , uint64_t qwSampleCount )
      {
        const uint64_t result = ScpGetDataRaw6Ch( m_handle , pBufferCh1 , pBufferCh2 , pBufferCh3 , pBufferCh4 , pBufferCh5 , pBufferCh6 , qwStartIndex , qwSampleCount );
        Library::checkLastStatusAndThrowOnError();

        return result;
      }

      uint64_t getDataRaw7Ch( void* pBufferCh1 , void* pBufferCh2 , void* pBufferCh3 , void* pBufferCh4 , void* pBufferCh5 , void* pBufferCh6 , void* pBufferCh7 , uint64_t qwStartIndex , uint64_t qwSampleCount )
      {
        const uint64_t result = ScpGetDataRaw7Ch( m_handle , pBufferCh1 , pBufferCh2 , pBufferCh3 , pBufferCh4 , pBufferCh5 , pBufferCh6 , pBufferCh7 , qwStartIndex , qwSampleCount );
        Library::checkLastStatusAndThrowOnError();

        return result;
      }

      uint64_t getDataRaw8Ch( void* pBufferCh1 , void* pBufferCh2 , void* pBufferCh3 , void* pBufferCh4 , void* pBufferCh5 , void* pBufferCh6 , void* pBufferCh7 , void* pBufferCh8 , uint64_t qwStartIndex , uint64_t qwSampleCount )
      {
        const uint64_t result = ScpGetDataRaw8Ch( m_handle , pBufferCh1 , pBufferCh2 , pBufferCh3 , pBufferCh4 , pBufferCh5 , pBufferCh6 , pBufferCh7 , pBufferCh8 , qwStartIndex , qwSampleCount );
        Library::checkLastStatusAndThrowOnError();

        return result;
      }

      bool getDataAsyncCompleted()
      {
        const bool result = ( ScpIsGetDataAsyncCompleted( m_handle ) != BOOL8_FALSE );
        Library::checkLastStatusAndThrowOnError();

        return result;
      }

      void startGetDataAsync( float** pBuffers , uint16_t wChannelCount , uint64_t qwStartIndex , uint64_t qwSampleCount )
      {
        ScpStartGetDataAsync( m_handle , pBuffers , wChannelCount , qwStartIndex , qwSampleCount );
        Library::checkLastStatusAndThrowOnError();
      }

      void startGetDataAsyncRaw( void** pBuffers , uint16_t wChannelCount , uint64_t qwStartIndex , uint64_t qwSampleCount )
      {
        ScpStartGetDataAsyncRaw( m_handle , pBuffers , wChannelCount , qwStartIndex , qwSampleCount );
        Library::checkLastStatusAndThrowOnError();
      }

      bool cancelGetDataAsync()
      {
        const bool result = ( ScpCancelGetDataAsync( m_handle ) != BOOL8_FALSE );
        Library::checkLastStatusAndThrowOnError();

        return result;
      }

      void setCallbackDataReady( TpCallback_t pCallback , void* pData )
      {
        ScpSetCallbackDataReady( m_handle , pCallback , pData );
        Library::checkLastStatusAndThrowOnError();
      }

      void setCallbackDataOverflow( TpCallback_t pCallback , void* pData )
      {
        ScpSetCallbackDataOverflow( m_handle , pCallback , pData );
        Library::checkLastStatusAndThrowOnError();
      }

      void setCallbackConnectionTestCompleted( TpCallback_t pCallback , void* pData )
      {
        ScpSetCallbackConnectionTestCompleted( m_handle , pCallback , pData );
        Library::checkLastStatusAndThrowOnError();
      }

      void setCallbackTriggered( TpCallback_t pCallback , void* pData )
      {
        ScpSetCallbackTriggered( m_handle , pCallback , pData );
        Library::checkLastStatusAndThrowOnError();
      }

#ifdef LIBTIEPIE_LINUX
      void setEventDataReady( int fdEvent )
      {
        ScpSetEventDataReady( m_handle , fdEvent );
        Library::checkLastStatusAndThrowOnError();
      }

      void setEventDataOverflow( int fdEvent )
      {
        ScpSetEventDataOverflow( m_handle , fdEvent );
        Library::checkLastStatusAndThrowOnError();
      }

      void setEventConnectionTestCompleted( int fdEvent )
      {
        ScpSetEventConnectionTestCompleted( m_handle , fdEvent );
        Library::checkLastStatusAndThrowOnError();
      }

      void setEventTriggered( int fdEvent )
      {
        ScpSetEventTriggered( m_handle , fdEvent );
        Library::checkLastStatusAndThrowOnError();
      }
#endif

#ifdef LIBTIEPIE_WINDOWS
      void setEventDataReady( HANDLE hEvent )
      {
        ScpSetEventDataReady( m_handle , hEvent );
        Library::checkLastStatusAndThrowOnError();
      }

      void setEventDataOverflow( HANDLE hEvent )
      {
        ScpSetEventDataOverflow( m_handle , hEvent );
        Library::checkLastStatusAndThrowOnError();
      }

      void setEventConnectionTestCompleted( HANDLE hEvent )
      {
        ScpSetEventConnectionTestCompleted( m_handle , hEvent );
        Library::checkLastStatusAndThrowOnError();
      }

      void setEventTriggered( HANDLE hEvent )
      {
        ScpSetEventTriggered( m_handle , hEvent );
        Library::checkLastStatusAndThrowOnError();
      }

      void setMessageDataReady( HWND hWnd , WPARAM wParam , LPARAM lParam )
      {
        ScpSetMessageDataReady( m_handle , hWnd , wParam , lParam );
        Library::checkLastStatusAndThrowOnError();
      }

      void setMessageDataOverflow( HWND hWnd , WPARAM wParam , LPARAM lParam )
      {
        ScpSetMessageDataOverflow( m_handle , hWnd , wParam , lParam );
        Library::checkLastStatusAndThrowOnError();
      }

      void setMessageConnectionTestCompleted( HWND hWnd , WPARAM wParam , LPARAM lParam )
      {
        ScpSetMessageConnectionTestCompleted( m_handle , hWnd , wParam , lParam );
        Library::checkLastStatusAndThrowOnError();
      }

      void setMessageTriggered( HWND hWnd , WPARAM wParam , LPARAM lParam )
      {
        ScpSetMessageTriggered( m_handle , hWnd , wParam , lParam );
        Library::checkLastStatusAndThrowOnError();
      }
#endif

      void start()
      {
        ScpStart( m_handle );
        Library::checkLastStatusAndThrowOnError();
      }

      void stop()
      {
        ScpStop( m_handle );
        Library::checkLastStatusAndThrowOnError();
      }

      void forceTrigger()
      {
        ScpForceTrigger( m_handle );
        Library::checkLastStatusAndThrowOnError();
      }

      uint32_t measureModes() const
      {
        const uint32_t result = ScpGetMeasureModes( m_handle );
        Library::checkLastStatusAndThrowOnError();

        return result;
      }

      uint32_t measureMode() const
      {
        const uint32_t result = ScpGetMeasureMode( m_handle );
        Library::checkLastStatusAndThrowOnError();

        return result;
      }

      uint32_t setMeasureMode( uint32_t dwMeasureMode )
      {
        const uint32_t result = ScpSetMeasureMode( m_handle , dwMeasureMode );
        Library::checkLastStatusAndThrowOnError();

        return result;
      }

      bool isRunning() const
      {
        const bool result = ( ScpIsRunning( m_handle ) != BOOL8_FALSE );
        Library::checkLastStatusAndThrowOnError();

        return result;
      }

      bool isTriggered() const
      {
        const bool result = ( ScpIsTriggered( m_handle ) != BOOL8_FALSE );
        Library::checkLastStatusAndThrowOnError();

        return result;
      }

      bool isTimeOutTriggered() const
      {
        const bool result = ( ScpIsTimeOutTriggered( m_handle ) != BOOL8_FALSE );
        Library::checkLastStatusAndThrowOnError();

        return result;
      }

      bool isForceTriggered() const
      {
        const bool result = ( ScpIsForceTriggered( m_handle ) != BOOL8_FALSE );
        Library::checkLastStatusAndThrowOnError();

        return result;
      }

      bool isDataReady() const
      {
        const bool result = ( ScpIsDataReady( m_handle ) != BOOL8_FALSE );
        Library::checkLastStatusAndThrowOnError();

        return result;
      }

      bool isDataOverflow() const
      {
        const bool result = ( ScpIsDataOverflow( m_handle ) != BOOL8_FALSE );
        Library::checkLastStatusAndThrowOnError();

        return result;
      }

      uint32_t autoResolutionModes() const
      {
        const uint32_t result = ScpGetAutoResolutionModes( m_handle );
        Library::checkLastStatusAndThrowOnError();

        return result;
      }

      uint32_t autoResolutionMode() const
      {
        const uint32_t result = ScpGetAutoResolutionMode( m_handle );
        Library::checkLastStatusAndThrowOnError();

        return result;
      }

      uint32_t setAutoResolutionMode( uint32_t dwAutoResolutionMode )
      {
        const uint32_t result = ScpSetAutoResolutionMode( m_handle , dwAutoResolutionMode );
        Library::checkLastStatusAndThrowOnError();

        return result;
      }

      const std::vector<uint8_t> resolutions() const
      {
        const uint32_t dwLength = ScpGetResolutions( m_handle , 0 , 0 );
        Library::checkLastStatusAndThrowOnError();
        Buffer<uint8_t> tmp( dwLength );
        ScpGetResolutions( m_handle , *tmp , dwLength );
        Library::checkLastStatusAndThrowOnError();
        return std::vector<uint8_t>( *tmp , *tmp + dwLength );
      }

      uint8_t resolution() const
      {
        const uint8_t result = ScpGetResolution( m_handle );
        Library::checkLastStatusAndThrowOnError();

        return result;
      }

      uint8_t setResolution( uint8_t byResolution )
      {
        const uint8_t result = ScpSetResolution( m_handle , byResolution );
        Library::checkLastStatusAndThrowOnError();

        return result;
      }

      bool isResolutionEnhanced() const
      {
        const bool result = ( ScpIsResolutionEnhanced( m_handle ) != BOOL8_FALSE );
        Library::checkLastStatusAndThrowOnError();

        return result;
      }

      bool isResolutionEnhanced( uint8_t byResolution ) const
      {
        const bool result = ( ScpIsResolutionEnhancedEx( m_handle , byResolution ) != BOOL8_FALSE );
        Library::checkLastStatusAndThrowOnError();

        return result;
      }

      uint32_t clockSources() const
      {
        const uint32_t result = ScpGetClockSources( m_handle );
        Library::checkLastStatusAndThrowOnError();

        return result;
      }

      uint32_t clockSource() const
      {
        const uint32_t result = ScpGetClockSource( m_handle );
        Library::checkLastStatusAndThrowOnError();

        return result;
      }

      uint32_t setClockSource( uint32_t dwClockSource )
      {
        const uint32_t result = ScpSetClockSource( m_handle , dwClockSource );
        Library::checkLastStatusAndThrowOnError();

        return result;
      }

      const std::vector<double> clockSourceFrequencies() const
      {
        const uint32_t dwLength = ScpGetClockSourceFrequencies( m_handle , 0 , 0 );
        Library::checkLastStatusAndThrowOnError();
        Buffer<double> tmp( dwLength );
        ScpGetClockSourceFrequencies( m_handle , *tmp , dwLength );
        Library::checkLastStatusAndThrowOnError();
        return std::vector<double>( *tmp , *tmp + dwLength );
      }

      const std::vector<double> getClockSourceFrequencies( uint32_t dwClockSource ) const
      {
        const uint32_t dwLength = ScpGetClockSourceFrequenciesEx( m_handle , dwClockSource , 0 , 0 );
        Library::checkLastStatusAndThrowOnError();
        Buffer<double> tmp( dwLength );
        ScpGetClockSourceFrequenciesEx( m_handle , dwClockSource , *tmp , dwLength );
        Library::checkLastStatusAndThrowOnError();
        return std::vector<double>( *tmp , *tmp + dwLength );
      }

      double clockSourceFrequency() const
      {
        const double result = ScpGetClockSourceFrequency( m_handle );
        Library::checkLastStatusAndThrowOnError();

        return result;
      }

      double setClockSourceFrequency( double dClockSourceFrequency )
      {
        const double result = ScpSetClockSourceFrequency( m_handle , dClockSourceFrequency );
        Library::checkLastStatusAndThrowOnError();

        return result;
      }

      uint32_t clockOutputs() const
      {
        const uint32_t result = ScpGetClockOutputs( m_handle );
        Library::checkLastStatusAndThrowOnError();

        return result;
      }

      uint32_t clockOutput() const
      {
        const uint32_t result = ScpGetClockOutput( m_handle );
        Library::checkLastStatusAndThrowOnError();

        return result;
      }

      uint32_t setClockOutput( uint32_t dwClockOutput )
      {
        const uint32_t result = ScpSetClockOutput( m_handle , dwClockOutput );
        Library::checkLastStatusAndThrowOnError();

        return result;
      }

      const std::vector<double> clockOutputFrequencies() const
      {
        const uint32_t dwLength = ScpGetClockOutputFrequencies( m_handle , 0 , 0 );
        Library::checkLastStatusAndThrowOnError();
        Buffer<double> tmp( dwLength );
        ScpGetClockOutputFrequencies( m_handle , *tmp , dwLength );
        Library::checkLastStatusAndThrowOnError();
        return std::vector<double>( *tmp , *tmp + dwLength );
      }

      const std::vector<double> getClockOutputFrequencies( uint32_t dwClockOutput ) const
      {
        const uint32_t dwLength = ScpGetClockOutputFrequenciesEx( m_handle , dwClockOutput , 0 , 0 );
        Library::checkLastStatusAndThrowOnError();
        Buffer<double> tmp( dwLength );
        ScpGetClockOutputFrequenciesEx( m_handle , dwClockOutput , *tmp , dwLength );
        Library::checkLastStatusAndThrowOnError();
        return std::vector<double>( *tmp , *tmp + dwLength );
      }

      double clockOutputFrequency() const
      {
        const double result = ScpGetClockOutputFrequency( m_handle );
        Library::checkLastStatusAndThrowOnError();

        return result;
      }

      double setClockOutputFrequency( double dClockOutputFrequency )
      {
        const double result = ScpSetClockOutputFrequency( m_handle , dClockOutputFrequency );
        Library::checkLastStatusAndThrowOnError();

        return result;
      }

      double sampleFrequencyMax() const
      {
        const double result = ScpGetSampleFrequencyMax( m_handle );
        Library::checkLastStatusAndThrowOnError();

        return result;
      }

      double sampleFrequency() const
      {
        const double result = ScpGetSampleFrequency( m_handle );
        Library::checkLastStatusAndThrowOnError();

        return result;
      }

      double setSampleFrequency( double dSampleFrequency )
      {
        const double result = ScpSetSampleFrequency( m_handle , dSampleFrequency );
        Library::checkLastStatusAndThrowOnError();

        return result;
      }

      double verifySampleFrequency( double dSampleFrequency ) const
      {
        const double result = ScpVerifySampleFrequency( m_handle , dSampleFrequency );
        Library::checkLastStatusAndThrowOnError();

        return result;
      }

      double verifySampleFrequency( double dSampleFrequency , uint32_t dwMeasureMode , uint8_t byResolution , const bool8_t* pChannelEnabled , uint16_t wChannelCount ) const
      {
        const double result = ScpVerifySampleFrequencyEx( m_handle , dSampleFrequency , dwMeasureMode , byResolution , pChannelEnabled , wChannelCount );
        Library::checkLastStatusAndThrowOnError();

        return result;
      }

      void verifySampleFrequencies( double* pSampleFrequencies , uint32_t dwSampleFrequencyCount , uint32_t dwMeasureMode , uint32_t dwAutoResolutionMode , uint8_t byResolution , const bool8_t* pChannelEnabled , uint16_t wChannelCount ) const
      {
        ScpVerifySampleFrequenciesEx( m_handle , pSampleFrequencies , dwSampleFrequencyCount , dwMeasureMode , dwAutoResolutionMode , byResolution , pChannelEnabled , wChannelCount );
        Library::checkLastStatusAndThrowOnError();
      }

      uint64_t recordLengthMax() const
      {
        const uint64_t result = ScpGetRecordLengthMax( m_handle );
        Library::checkLastStatusAndThrowOnError();

        return result;
      }

      uint64_t recordLengthMax( uint32_t dwMeasureMode , uint8_t byResolution ) const
      {
        const uint64_t result = ScpGetRecordLengthMaxEx( m_handle , dwMeasureMode , byResolution );
        Library::checkLastStatusAndThrowOnError();

        return result;
      }

      uint64_t recordLength() const
      {
        const uint64_t result = ScpGetRecordLength( m_handle );
        Library::checkLastStatusAndThrowOnError();

        return result;
      }

      uint64_t setRecordLength( uint64_t qwRecordLength )
      {
        const uint64_t result = ScpSetRecordLength( m_handle , qwRecordLength );
        Library::checkLastStatusAndThrowOnError();

        return result;
      }

      uint64_t verifyRecordLength( uint64_t qwRecordLength ) const
      {
        const uint64_t result = ScpVerifyRecordLength( m_handle , qwRecordLength );
        Library::checkLastStatusAndThrowOnError();

        return result;
      }

      uint64_t verifyRecordLength( uint64_t qwRecordLength , uint32_t dwMeasureMode , uint8_t byResolution , const bool8_t* pChannelEnabled , uint16_t wChannelCount ) const
      {
        const uint64_t result = ScpVerifyRecordLengthEx( m_handle , qwRecordLength , dwMeasureMode , byResolution , pChannelEnabled , wChannelCount );
        Library::checkLastStatusAndThrowOnError();

        return result;
      }

      double preSampleRatio() const
      {
        const double result = ScpGetPreSampleRatio( m_handle );
        Library::checkLastStatusAndThrowOnError();

        return result;
      }

      double setPreSampleRatio( double dPreSampleRatio )
      {
        const double result = ScpSetPreSampleRatio( m_handle , dPreSampleRatio );
        Library::checkLastStatusAndThrowOnError();

        return result;
      }

      uint32_t segmentCountMax() const
      {
        const uint32_t result = ScpGetSegmentCountMax( m_handle );
        Library::checkLastStatusAndThrowOnError();

        return result;
      }

      uint32_t segmentCountMax( uint32_t dwMeasureMode ) const
      {
        const uint32_t result = ScpGetSegmentCountMaxEx( m_handle , dwMeasureMode );
        Library::checkLastStatusAndThrowOnError();

        return result;
      }

      uint32_t segmentCount() const
      {
        const uint32_t result = ScpGetSegmentCount( m_handle );
        Library::checkLastStatusAndThrowOnError();

        return result;
      }

      uint32_t setSegmentCount( uint32_t dwSegmentCount )
      {
        const uint32_t result = ScpSetSegmentCount( m_handle , dwSegmentCount );
        Library::checkLastStatusAndThrowOnError();

        return result;
      }

      uint32_t verifySegmentCount( uint32_t dwSegmentCount ) const
      {
        const uint32_t result = ScpVerifySegmentCount( m_handle , dwSegmentCount );
        Library::checkLastStatusAndThrowOnError();

        return result;
      }

      uint32_t verifySegmentCount( uint32_t dwSegmentCount , uint32_t dwMeasureMode , uint64_t qwRecordLength , const bool8_t* pChannelEnabled , uint16_t wChannelCount ) const
      {
        const uint32_t result = ScpVerifySegmentCountEx2( m_handle , dwSegmentCount , dwMeasureMode , qwRecordLength , pChannelEnabled , wChannelCount );
        Library::checkLastStatusAndThrowOnError();

        return result;
      }

      bool hasTrigger() const
      {
        const bool result = ( ScpHasTrigger( m_handle ) != BOOL8_FALSE );
        Library::checkLastStatusAndThrowOnError();

        return result;
      }

      bool hasTrigger( uint32_t dwMeasureMode ) const
      {
        const bool result = ( ScpHasTriggerEx( m_handle , dwMeasureMode ) != BOOL8_FALSE );
        Library::checkLastStatusAndThrowOnError();

        return result;
      }

      double triggerTimeOut() const
      {
        const double result = ScpGetTriggerTimeOut( m_handle );
        Library::checkLastStatusAndThrowOnError();

        return result;
      }

      double setTriggerTimeOut( double dTimeOut )
      {
        const double result = ScpSetTriggerTimeOut( m_handle , dTimeOut );
        Library::checkLastStatusAndThrowOnError();

        return result;
      }

      double verifyTriggerTimeOut( double dTimeOut ) const
      {
        const double result = ScpVerifyTriggerTimeOut( m_handle , dTimeOut );
        Library::checkLastStatusAndThrowOnError();

        return result;
      }

      double verifyTriggerTimeOut( double dTimeOut , uint32_t dwMeasureMode , double dSampleFrequency ) const
      {
        const double result = ScpVerifyTriggerTimeOutEx( m_handle , dTimeOut , dwMeasureMode , dSampleFrequency );
        Library::checkLastStatusAndThrowOnError();

        return result;
      }

      bool hasTriggerDelay() const
      {
        const bool result = ( ScpHasTriggerDelay( m_handle ) != BOOL8_FALSE );
        Library::checkLastStatusAndThrowOnError();

        return result;
      }

      bool hasTriggerDelay( uint32_t dwMeasureMode ) const
      {
        const bool result = ( ScpHasTriggerDelayEx( m_handle , dwMeasureMode ) != BOOL8_FALSE );
        Library::checkLastStatusAndThrowOnError();

        return result;
      }

      double triggerDelayMax() const
      {
        const double result = ScpGetTriggerDelayMax( m_handle );
        Library::checkLastStatusAndThrowOnError();

        return result;
      }

      double triggerDelayMax( uint32_t dwMeasureMode , double dSampleFrequency ) const
      {
        const double result = ScpGetTriggerDelayMaxEx( m_handle , dwMeasureMode , dSampleFrequency );
        Library::checkLastStatusAndThrowOnError();

        return result;
      }

      double triggerDelay() const
      {
        const double result = ScpGetTriggerDelay( m_handle );
        Library::checkLastStatusAndThrowOnError();

        return result;
      }

      double setTriggerDelay( double dDelay )
      {
        const double result = ScpSetTriggerDelay( m_handle , dDelay );
        Library::checkLastStatusAndThrowOnError();

        return result;
      }

      double verifyTriggerDelay( double dDelay ) const
      {
        const double result = ScpVerifyTriggerDelay( m_handle , dDelay );
        Library::checkLastStatusAndThrowOnError();

        return result;
      }

      double verifyTriggerDelay( double dDelay , uint32_t dwMeasureMode , double dSampleFrequency ) const
      {
        const double result = ScpVerifyTriggerDelayEx( m_handle , dDelay , dwMeasureMode , dSampleFrequency );
        Library::checkLastStatusAndThrowOnError();

        return result;
      }

      bool hasTriggerHoldOff() const
      {
        const bool result = ( ScpHasTriggerHoldOff( m_handle ) != BOOL8_FALSE );
        Library::checkLastStatusAndThrowOnError();

        return result;
      }

      bool hasTriggerHoldOff( uint32_t dwMeasureMode ) const
      {
        const bool result = ( ScpHasTriggerHoldOffEx( m_handle , dwMeasureMode ) != BOOL8_FALSE );
        Library::checkLastStatusAndThrowOnError();

        return result;
      }

      uint64_t triggerHoldOffCountMax() const
      {
        const uint64_t result = ScpGetTriggerHoldOffCountMax( m_handle );
        Library::checkLastStatusAndThrowOnError();

        return result;
      }

      uint64_t triggerHoldOffCountMax( uint32_t dwMeasureMode ) const
      {
        const uint64_t result = ScpGetTriggerHoldOffCountMaxEx( m_handle , dwMeasureMode );
        Library::checkLastStatusAndThrowOnError();

        return result;
      }

      uint64_t triggerHoldOffCount() const
      {
        const uint64_t result = ScpGetTriggerHoldOffCount( m_handle );
        Library::checkLastStatusAndThrowOnError();

        return result;
      }

      uint64_t setTriggerHoldOffCount( uint64_t qwTriggerHoldOffCount )
      {
        const uint64_t result = ScpSetTriggerHoldOffCount( m_handle , qwTriggerHoldOffCount );
        Library::checkLastStatusAndThrowOnError();

        return result;
      }

      bool hasConnectionTest() const
      {
        const bool result = ( ScpHasConnectionTest( m_handle ) != BOOL8_FALSE );
        Library::checkLastStatusAndThrowOnError();

        return result;
      }

      void startConnectionTest()
      {
        ScpStartConnectionTest( m_handle );
        Library::checkLastStatusAndThrowOnError();
      }

      void startConnectionTest( const bool8_t* pChannelEnabled , uint16_t wChannelCount )
      {
        ScpStartConnectionTestEx( m_handle , pChannelEnabled , wChannelCount );
        Library::checkLastStatusAndThrowOnError();
      }

      bool isConnectionTestCompleted() const
      {
        const bool result = ( ScpIsConnectionTestCompleted( m_handle ) != BOOL8_FALSE );
        Library::checkLastStatusAndThrowOnError();

        return result;
      }

      uint16_t connectionTestData( LibTiePieTriState_t* pBuffer , uint16_t wChannelCount ) const
      {
        const uint16_t result = ScpGetConnectionTestData( m_handle , pBuffer , wChannelCount );
        Library::checkLastStatusAndThrowOnError();

        return result;
      }
  };

  class OscilloscopeChannelTriggerLevel
  {
    protected:
      const Handle_t m_handle;
      const uint16_t m_ch;
      const uint32_t m_index;

    public:
      OscilloscopeChannelTriggerLevel( Handle_t handle , uint16_t wCh , uint32_t dwIndex ) :
        m_handle( handle ) ,
        m_ch( wCh ) ,
        m_index( dwIndex )
      {
      }

      operator double() const
      {
        const double result = ScpChTrGetLevel( m_handle , m_ch , m_index );
        Library::checkLastStatusAndThrowOnError();

        return result;
      }

      double operator=( const double& value )
      {
        double tmp = ScpChTrSetLevel( m_handle , m_ch , m_index , value );
        Library::checkLastStatusAndThrowOnError();

        return tmp;
      }
  };

  class OscilloscopeChannelTriggerLevels : public ObjectList<OscilloscopeChannelTriggerLevel>
  {
    protected:
      const Handle_t m_handle;
      const uint16_t m_ch;

    public:
      OscilloscopeChannelTriggerLevels( Handle_t hDevice , uint16_t wCh ) :
        ObjectList<OscilloscopeChannelTriggerLevel>( hDevice , wCh , 2 ) ,
        m_handle( hDevice ) ,
        m_ch( wCh )
      {
      }

      size_type count() const
      {
        const size_type result = ScpChTrGetLevelCount( m_handle , m_ch );
        Library::checkLastStatusAndThrowOnError();

        return result;
      }
  };

  class OscilloscopeChannelTriggerHysteresis
  {
    protected:
      const Handle_t m_handle;
      const uint16_t m_ch;
      const uint32_t m_index;

    public:
      OscilloscopeChannelTriggerHysteresis( Handle_t handle , uint16_t wCh , uint32_t dwIndex ) :
        m_handle( handle ) ,
        m_ch( wCh ) ,
        m_index( dwIndex )
      {
      }

      operator double() const
      {
        const double result = ScpChTrGetHysteresis( m_handle , m_ch , m_index );
        Library::checkLastStatusAndThrowOnError();

        return result;
      }

      double operator=( const double& value )
      {
        double tmp = ScpChTrSetHysteresis( m_handle , m_ch , m_index , value );
        Library::checkLastStatusAndThrowOnError();

        return tmp;
      }
  };

  class OscilloscopeChannelTriggerHystereses : public ObjectList<OscilloscopeChannelTriggerHysteresis>
  {
    protected:
      const Handle_t m_handle;
      const uint16_t m_ch;

    public:
      OscilloscopeChannelTriggerHystereses( Handle_t hDevice , uint16_t wCh ) :
        ObjectList<OscilloscopeChannelTriggerHysteresis>( hDevice , wCh , 2 ) ,
        m_handle( hDevice ) ,
        m_ch( wCh )
      {
      }

      size_type count() const
      {
        const size_type result = ScpChTrGetHysteresisCount( m_handle , m_ch );
        Library::checkLastStatusAndThrowOnError();

        return result;
      }
  };

  class OscilloscopeChannelTriggerTime
  {
    protected:
      const Handle_t m_handle;
      const uint16_t m_ch;
      const uint32_t m_index;

    public:
      OscilloscopeChannelTriggerTime( Handle_t handle , uint16_t wCh , uint32_t dwIndex ) :
        m_handle( handle ) ,
        m_ch( wCh ) ,
        m_index( dwIndex )
      {
      }

      operator double() const
      {
        const double result = ScpChTrGetTime( m_handle , m_ch , m_index );
        Library::checkLastStatusAndThrowOnError();

        return result;
      }

      double operator=( const double& value )
      {
        double tmp = ScpChTrSetTime( m_handle , m_ch , m_index , value );
        Library::checkLastStatusAndThrowOnError();

        return tmp;
      }

      double verify( double value ) const
      {
        const double result = ScpChTrVerifyTime( m_handle , m_ch , m_index , value );
        Library::checkLastStatusAndThrowOnError();

        return result;
      }

      double verify( double dTime , uint32_t dwMeasureMode , double dSampleFrequency , uint64_t qwTriggerKind , uint32_t dwTriggerCondition ) const
      {
        const double result = ScpChTrVerifyTimeEx2( m_handle , m_ch , m_index , dTime , dwMeasureMode , dSampleFrequency , qwTriggerKind , dwTriggerCondition );
        Library::checkLastStatusAndThrowOnError();

        return result;
      }
  };

  class OscilloscopeChannelTriggerTimes : public ObjectList<OscilloscopeChannelTriggerTime>
  {
    protected:
      const Handle_t m_handle;
      const uint16_t m_ch;

    public:
      OscilloscopeChannelTriggerTimes( Handle_t hDevice , uint16_t wCh ) :
        ObjectList<OscilloscopeChannelTriggerTime>( hDevice , wCh , 2 ) ,
        m_handle( hDevice ) ,
        m_ch( wCh )
      {
      }

      size_type count() const
      {
        const size_type result = ScpChTrGetTimeCount( m_handle , m_ch );
        Library::checkLastStatusAndThrowOnError();

        return result;
      }
  };

  class OscilloscopeChannelTrigger
  {
    protected:
      const Handle_t m_handle;
      const uint16_t m_ch;

    public:
      const OscilloscopeChannelTriggerLevels Levels;
      const OscilloscopeChannelTriggerHystereses Hystereses;
      const OscilloscopeChannelTriggerTimes Times;

      OscilloscopeChannelTrigger( Handle_t hDevice , uint16_t wCh ) :
        m_handle( hDevice ) ,
        m_ch( wCh ) ,
        Levels( m_handle , m_ch ) ,
        Hystereses( m_handle , m_ch ) ,
        Times( m_handle , m_ch )
      {
      }

      bool isAvailable() const
      {
        const bool result = ( ScpChTrIsAvailable( m_handle , m_ch ) != BOOL8_FALSE );
        Library::checkLastStatusAndThrowOnError();

        return result;
      }

      bool isAvailable( uint32_t dwMeasureMode , double dSampleFrequency , uint8_t byResolution , const bool8_t* pChannelEnabled , const bool8_t* pChannelTriggerEnabled , uint16_t wChannelCount ) const
      {
        const bool result = ( ScpChTrIsAvailableEx( m_handle , m_ch , dwMeasureMode , dSampleFrequency , byResolution , pChannelEnabled , pChannelTriggerEnabled , wChannelCount ) != BOOL8_FALSE );
        Library::checkLastStatusAndThrowOnError();

        return result;
      }

      bool isTriggered() const
      {
        const bool result = ( ScpChTrIsTriggered( m_handle , m_ch ) != BOOL8_FALSE );
        Library::checkLastStatusAndThrowOnError();

        return result;
      }

      bool enabled() const
      {
        const bool result = ( ScpChTrGetEnabled( m_handle , m_ch ) != BOOL8_FALSE );
        Library::checkLastStatusAndThrowOnError();

        return result;
      }

      bool setEnabled( bool bEnable )
      {
        const bool result = ( ScpChTrSetEnabled( m_handle , m_ch , bEnable ? BOOL8_TRUE : BOOL8_FALSE ) != BOOL8_FALSE );
        Library::checkLastStatusAndThrowOnError();

        return result;
      }

      uint64_t kinds() const
      {
        const uint64_t result = ScpChTrGetKinds( m_handle , m_ch );
        Library::checkLastStatusAndThrowOnError();

        return result;
      }

      uint64_t kinds( uint32_t dwMeasureMode ) const
      {
        const uint64_t result = ScpChTrGetKindsEx( m_handle , m_ch , dwMeasureMode );
        Library::checkLastStatusAndThrowOnError();

        return result;
      }

      uint64_t kind() const
      {
        const uint64_t result = ScpChTrGetKind( m_handle , m_ch );
        Library::checkLastStatusAndThrowOnError();

        return result;
      }

      uint64_t setKind( uint64_t qwTriggerKind )
      {
        const uint64_t result = ScpChTrSetKind( m_handle , m_ch , qwTriggerKind );
        Library::checkLastStatusAndThrowOnError();

        return result;
      }

      uint32_t levelModes() const
      {
        const uint32_t result = ScpChTrGetLevelModes( m_handle , m_ch );
        Library::checkLastStatusAndThrowOnError();

        return result;
      }

      uint32_t levelMode() const
      {
        const uint32_t result = ScpChTrGetLevelMode( m_handle , m_ch );
        Library::checkLastStatusAndThrowOnError();

        return result;
      }

      uint32_t setLevelMode( uint32_t dwLevelMode )
      {
        const uint32_t result = ScpChTrSetLevelMode( m_handle , m_ch , dwLevelMode );
        Library::checkLastStatusAndThrowOnError();

        return result;
      }

      uint32_t conditions() const
      {
        const uint32_t result = ScpChTrGetConditions( m_handle , m_ch );
        Library::checkLastStatusAndThrowOnError();

        return result;
      }

      uint32_t conditions( uint32_t dwMeasureMode , uint64_t qwTriggerKind ) const
      {
        const uint32_t result = ScpChTrGetConditionsEx( m_handle , m_ch , dwMeasureMode , qwTriggerKind );
        Library::checkLastStatusAndThrowOnError();

        return result;
      }

      uint32_t condition() const
      {
        const uint32_t result = ScpChTrGetCondition( m_handle , m_ch );
        Library::checkLastStatusAndThrowOnError();

        return result;
      }

      uint32_t setCondition( uint32_t dwCondition )
      {
        const uint32_t result = ScpChTrSetCondition( m_handle , m_ch , dwCondition );
        Library::checkLastStatusAndThrowOnError();

        return result;
      }
  };

  class OscilloscopeChannel
  {
    protected:
      const Handle_t m_handle;
      const uint16_t m_ch;

    public:
      OscilloscopeChannelTrigger* const trigger;

      OscilloscopeChannel( Handle_t hDevice , uint16_t wCh ) :
        m_handle( hDevice ) ,
        m_ch( wCh ) ,
        trigger( ScpChHasTrigger( hDevice , wCh ) ? new OscilloscopeChannelTrigger( hDevice , wCh ) : 0 )
      {
      }

      ~OscilloscopeChannel()
      {
        if( trigger )
          delete trigger;
      }

      uint32_t number() const
      {
        return m_ch + 1;
      }

      bool isAvailable() const
      {
        const bool result = ( ScpChIsAvailable( m_handle , m_ch ) != BOOL8_FALSE );
        Library::checkLastStatusAndThrowOnError();

        return result;
      }

      bool isAvailable( uint32_t dwMeasureMode , double dSampleFrequency , uint8_t byResolution , const bool8_t* pChannelEnabled , uint16_t wChannelCount ) const
      {
        const bool result = ( ScpChIsAvailableEx( m_handle , m_ch , dwMeasureMode , dSampleFrequency , byResolution , pChannelEnabled , wChannelCount ) != BOOL8_FALSE );
        Library::checkLastStatusAndThrowOnError();

        return result;
      }

      uint32_t connectorType() const
      {
        const uint32_t result = ScpChGetConnectorType( m_handle , m_ch );
        Library::checkLastStatusAndThrowOnError();

        return result;
      }

      bool isDifferential() const
      {
        const bool result = ( ScpChIsDifferential( m_handle , m_ch ) != BOOL8_FALSE );
        Library::checkLastStatusAndThrowOnError();

        return result;
      }

      double impedance() const
      {
        const double result = ScpChGetImpedance( m_handle , m_ch );
        Library::checkLastStatusAndThrowOnError();

        return result;
      }

      const std::vector<double> bandwidths() const
      {
        const uint32_t dwLength = ScpChGetBandwidths( m_handle , m_ch , 0 , 0 );
        Library::checkLastStatusAndThrowOnError();
        Buffer<double> tmp( dwLength );
        ScpChGetBandwidths( m_handle , m_ch , *tmp , dwLength );
        Library::checkLastStatusAndThrowOnError();
        return std::vector<double>( *tmp , *tmp + dwLength );
      }

      double bandwidth() const
      {
        const double result = ScpChGetBandwidth( m_handle , m_ch );
        Library::checkLastStatusAndThrowOnError();

        return result;
      }

      double setBandwidth( double dBandwidth )
      {
        const double result = ScpChSetBandwidth( m_handle , m_ch , dBandwidth );
        Library::checkLastStatusAndThrowOnError();

        return result;
      }

      uint64_t couplings() const
      {
        const uint64_t result = ScpChGetCouplings( m_handle , m_ch );
        Library::checkLastStatusAndThrowOnError();

        return result;
      }

      uint64_t coupling() const
      {
        const uint64_t result = ScpChGetCoupling( m_handle , m_ch );
        Library::checkLastStatusAndThrowOnError();

        return result;
      }

      uint64_t setCoupling( uint64_t qwCoupling )
      {
        const uint64_t result = ScpChSetCoupling( m_handle , m_ch , qwCoupling );
        Library::checkLastStatusAndThrowOnError();

        return result;
      }

      bool enabled() const
      {
        const bool result = ( ScpChGetEnabled( m_handle , m_ch ) != BOOL8_FALSE );
        Library::checkLastStatusAndThrowOnError();

        return result;
      }

      bool setEnabled( bool bEnable )
      {
        const bool result = ( ScpChSetEnabled( m_handle , m_ch , bEnable ? BOOL8_TRUE : BOOL8_FALSE ) != BOOL8_FALSE );
        Library::checkLastStatusAndThrowOnError();

        return result;
      }

      double probeGain() const
      {
        const double result = ScpChGetProbeGain( m_handle , m_ch );
        Library::checkLastStatusAndThrowOnError();

        return result;
      }

      double setProbeGain( double dProbeGain )
      {
        const double result = ScpChSetProbeGain( m_handle , m_ch , dProbeGain );
        Library::checkLastStatusAndThrowOnError();

        return result;
      }

      double probeOffset() const
      {
        const double result = ScpChGetProbeOffset( m_handle , m_ch );
        Library::checkLastStatusAndThrowOnError();

        return result;
      }

      double setProbeOffset( double dProbeOffset )
      {
        const double result = ScpChSetProbeOffset( m_handle , m_ch , dProbeOffset );
        Library::checkLastStatusAndThrowOnError();

        return result;
      }

      bool autoRanging() const
      {
        const bool result = ( ScpChGetAutoRanging( m_handle , m_ch ) != BOOL8_FALSE );
        Library::checkLastStatusAndThrowOnError();

        return result;
      }

      bool setAutoRanging( bool bEnable )
      {
        const bool result = ( ScpChSetAutoRanging( m_handle , m_ch , bEnable ? BOOL8_TRUE : BOOL8_FALSE ) != BOOL8_FALSE );
        Library::checkLastStatusAndThrowOnError();

        return result;
      }

      const std::vector<double> ranges() const
      {
        const uint32_t dwLength = ScpChGetRanges( m_handle , m_ch , 0 , 0 );
        Library::checkLastStatusAndThrowOnError();
        Buffer<double> tmp( dwLength );
        ScpChGetRanges( m_handle , m_ch , *tmp , dwLength );
        Library::checkLastStatusAndThrowOnError();
        return std::vector<double>( *tmp , *tmp + dwLength );
      }

      const std::vector<double> ranges( uint64_t qwCoupling ) const
      {
        const uint32_t dwLength = ScpChGetRangesEx( m_handle , m_ch , qwCoupling , 0 , 0 );
        Library::checkLastStatusAndThrowOnError();
        Buffer<double> tmp( dwLength );
        ScpChGetRangesEx( m_handle , m_ch , qwCoupling , *tmp , dwLength );
        Library::checkLastStatusAndThrowOnError();
        return std::vector<double>( *tmp , *tmp + dwLength );
      }

      double range() const
      {
        const double result = ScpChGetRange( m_handle , m_ch );
        Library::checkLastStatusAndThrowOnError();

        return result;
      }

      double setRange( double dRange )
      {
        const double result = ScpChSetRange( m_handle , m_ch , dRange );
        Library::checkLastStatusAndThrowOnError();

        return result;
      }

      bool hasSafeGround() const
      {
        const bool result = ( ScpChHasSafeGround( m_handle , m_ch ) != BOOL8_FALSE );
        Library::checkLastStatusAndThrowOnError();

        return result;
      }

      bool safeGroundEnabled() const
      {
        const bool result = ( ScpChGetSafeGroundEnabled( m_handle , m_ch ) != BOOL8_FALSE );
        Library::checkLastStatusAndThrowOnError();

        return result;
      }

      bool setSafeGroundEnabled( bool bEnable )
      {
        const bool result = ( ScpChSetSafeGroundEnabled( m_handle , m_ch , bEnable ? BOOL8_TRUE : BOOL8_FALSE ) != BOOL8_FALSE );
        Library::checkLastStatusAndThrowOnError();

        return result;
      }

      double safeGroundThresholdMin() const
      {
        const double result = ScpChGetSafeGroundThresholdMin( m_handle , m_ch );
        Library::checkLastStatusAndThrowOnError();

        return result;
      }

      double safeGroundThresholdMax() const
      {
        const double result = ScpChGetSafeGroundThresholdMax( m_handle , m_ch );
        Library::checkLastStatusAndThrowOnError();

        return result;
      }

      double safeGroundThreshold() const
      {
        const double result = ScpChGetSafeGroundThreshold( m_handle , m_ch );
        Library::checkLastStatusAndThrowOnError();

        return result;
      }

      double setSafeGroundThreshold( double dThreshold )
      {
        const double result = ScpChSetSafeGroundThreshold( m_handle , m_ch , dThreshold );
        Library::checkLastStatusAndThrowOnError();

        return result;
      }

      double verifySafeGroundThreshold( double dThreshold ) const
      {
        const double result = ScpChVerifySafeGroundThreshold( m_handle , m_ch , dThreshold );
        Library::checkLastStatusAndThrowOnError();

        return result;
      }

      bool hasTrigger() const
      {
        const bool result = ( ScpChHasTrigger( m_handle , m_ch ) != BOOL8_FALSE );
        Library::checkLastStatusAndThrowOnError();

        return result;
      }

      bool hasTrigger( uint32_t dwMeasureMode ) const
      {
        const bool result = ( ScpChHasTriggerEx( m_handle , m_ch , dwMeasureMode ) != BOOL8_FALSE );
        Library::checkLastStatusAndThrowOnError();

        return result;
      }

      void getDataValueRange( double* pMin , double* pMax ) const
      {
        ScpChGetDataValueRange( m_handle , m_ch , pMin , pMax );
        Library::checkLastStatusAndThrowOnError();
      }

      double dataValueMin() const
      {
        const double result = ScpChGetDataValueMin( m_handle , m_ch );
        Library::checkLastStatusAndThrowOnError();

        return result;
      }

      double dataValueMax() const
      {
        const double result = ScpChGetDataValueMax( m_handle , m_ch );
        Library::checkLastStatusAndThrowOnError();

        return result;
      }

      uint32_t dataRawType() const
      {
        const uint32_t result = ScpChGetDataRawType( m_handle , m_ch );
        Library::checkLastStatusAndThrowOnError();

        return result;
      }

      void getDataRawValueRange( int64_t* pMin , int64_t* pZero , int64_t* pMax ) const
      {
        ScpChGetDataRawValueRange( m_handle , m_ch , pMin , pZero , pMax );
        Library::checkLastStatusAndThrowOnError();
      }

      int64_t dataRawValueMin() const
      {
        const int64_t result = ScpChGetDataRawValueMin( m_handle , m_ch );
        Library::checkLastStatusAndThrowOnError();

        return result;
      }

      int64_t dataRawValueZero() const
      {
        const int64_t result = ScpChGetDataRawValueZero( m_handle , m_ch );
        Library::checkLastStatusAndThrowOnError();

        return result;
      }

      int64_t dataRawValueMax() const
      {
        const int64_t result = ScpChGetDataRawValueMax( m_handle , m_ch );
        Library::checkLastStatusAndThrowOnError();

        return result;
      }

      bool isRangeMaxReachable() const
      {
        const bool result = ( ScpChIsRangeMaxReachable( m_handle , m_ch ) != BOOL8_FALSE );
        Library::checkLastStatusAndThrowOnError();

        return result;
      }

      bool hasConnectionTest() const
      {
        const bool result = ( ScpChHasConnectionTest( m_handle , m_ch ) != BOOL8_FALSE );
        Library::checkLastStatusAndThrowOnError();

        return result;
      }
  };

  class Generator : public Device
  {
    public:
      Generator( Handle_t hDevice ) :
        Device( hDevice )
      {
      }

      uint32_t connectorType() const
      {
        const uint32_t result = GenGetConnectorType( m_handle );
        Library::checkLastStatusAndThrowOnError();

        return result;
      }

      bool isDifferential() const
      {
        const bool result = ( GenIsDifferential( m_handle ) != BOOL8_FALSE );
        Library::checkLastStatusAndThrowOnError();

        return result;
      }

      double impedance() const
      {
        const double result = GenGetImpedance( m_handle );
        Library::checkLastStatusAndThrowOnError();

        return result;
      }

      uint8_t resolution() const
      {
        const uint8_t result = GenGetResolution( m_handle );
        Library::checkLastStatusAndThrowOnError();

        return result;
      }

      double outputValueMin() const
      {
        const double result = GenGetOutputValueMin( m_handle );
        Library::checkLastStatusAndThrowOnError();

        return result;
      }

      double outputValueMax() const
      {
        const double result = GenGetOutputValueMax( m_handle );
        Library::checkLastStatusAndThrowOnError();

        return result;
      }

      void getOutputValueMinMax( double* pMin , double* pMax ) const
      {
        GenGetOutputValueMinMax( m_handle , pMin , pMax );
        Library::checkLastStatusAndThrowOnError();
      }

      bool isControllable() const
      {
        const bool result = ( GenIsControllable( m_handle ) != BOOL8_FALSE );
        Library::checkLastStatusAndThrowOnError();

        return result;
      }

      bool isRunning() const
      {
        const bool result = ( GenIsRunning( m_handle ) != BOOL8_FALSE );
        Library::checkLastStatusAndThrowOnError();

        return result;
      }

      uint32_t status() const
      {
        const uint32_t result = GenGetStatus( m_handle );
        Library::checkLastStatusAndThrowOnError();

        return result;
      }

      bool outputOn() const
      {
        const bool result = ( GenGetOutputOn( m_handle ) != BOOL8_FALSE );
        Library::checkLastStatusAndThrowOnError();

        return result;
      }

      bool setOutputOn( bool bOutputOn )
      {
        const bool result = ( GenSetOutputOn( m_handle , bOutputOn ? BOOL8_TRUE : BOOL8_FALSE ) != BOOL8_FALSE );
        Library::checkLastStatusAndThrowOnError();

        return result;
      }

      bool hasOutputInvert() const
      {
        const bool result = ( GenHasOutputInvert( m_handle ) != BOOL8_FALSE );
        Library::checkLastStatusAndThrowOnError();

        return result;
      }

      bool outputInvert() const
      {
        const bool result = ( GenGetOutputInvert( m_handle ) != BOOL8_FALSE );
        Library::checkLastStatusAndThrowOnError();

        return result;
      }

      bool setOutputInvert( bool bInvert )
      {
        const bool result = ( GenSetOutputInvert( m_handle , bInvert ? BOOL8_TRUE : BOOL8_FALSE ) != BOOL8_FALSE );
        Library::checkLastStatusAndThrowOnError();

        return result;
      }

      void start()
      {
        GenStart( m_handle );
        Library::checkLastStatusAndThrowOnError();
      }

      void stop()
      {
        GenStop( m_handle );
        Library::checkLastStatusAndThrowOnError();
      }

      uint32_t signalTypes() const
      {
        const uint32_t result = GenGetSignalTypes( m_handle );
        Library::checkLastStatusAndThrowOnError();

        return result;
      }

      uint32_t signalType() const
      {
        const uint32_t result = GenGetSignalType( m_handle );
        Library::checkLastStatusAndThrowOnError();

        return result;
      }

      uint32_t setSignalType( uint32_t dwSignalType )
      {
        const uint32_t result = GenSetSignalType( m_handle , dwSignalType );
        Library::checkLastStatusAndThrowOnError();

        return result;
      }

      bool hasAmplitude() const
      {
        const bool result = ( GenHasAmplitude( m_handle ) != BOOL8_FALSE );
        Library::checkLastStatusAndThrowOnError();

        return result;
      }

      bool hasAmplitude( uint32_t dwSignalType ) const
      {
        const bool result = ( GenHasAmplitudeEx( m_handle , dwSignalType ) != BOOL8_FALSE );
        Library::checkLastStatusAndThrowOnError();

        return result;
      }

      double amplitudeMin() const
      {
        const double result = GenGetAmplitudeMin( m_handle );
        Library::checkLastStatusAndThrowOnError();

        return result;
      }

      double amplitudeMax() const
      {
        const double result = GenGetAmplitudeMax( m_handle );
        Library::checkLastStatusAndThrowOnError();

        return result;
      }

      void getAmplitudeMinMax( uint32_t dwSignalType , double* pMin , double* pMax ) const
      {
        GenGetAmplitudeMinMaxEx( m_handle , dwSignalType , pMin , pMax );
        Library::checkLastStatusAndThrowOnError();
      }

      double amplitude() const
      {
        const double result = GenGetAmplitude( m_handle );
        Library::checkLastStatusAndThrowOnError();

        return result;
      }

      double setAmplitude( double dAmplitude )
      {
        const double result = GenSetAmplitude( m_handle , dAmplitude );
        Library::checkLastStatusAndThrowOnError();

        return result;
      }

      double verifyAmplitude( double dAmplitude ) const
      {
        const double result = GenVerifyAmplitude( m_handle , dAmplitude );
        Library::checkLastStatusAndThrowOnError();

        return result;
      }

      double verifyAmplitude( double dAmplitude , uint32_t dwSignalType , uint32_t dwAmplitudeRangeIndex , double dOffset ) const
      {
        const double result = GenVerifyAmplitudeEx( m_handle , dAmplitude , dwSignalType , dwAmplitudeRangeIndex , dOffset );
        Library::checkLastStatusAndThrowOnError();

        return result;
      }

      const std::vector<double> amplitudeRanges() const
      {
        const uint32_t dwLength = GenGetAmplitudeRanges( m_handle , 0 , 0 );
        Library::checkLastStatusAndThrowOnError();
        Buffer<double> tmp( dwLength );
        GenGetAmplitudeRanges( m_handle , *tmp , dwLength );
        Library::checkLastStatusAndThrowOnError();
        return std::vector<double>( *tmp , *tmp + dwLength );
      }

      double amplitudeRange() const
      {
        const double result = GenGetAmplitudeRange( m_handle );
        Library::checkLastStatusAndThrowOnError();

        return result;
      }

      double setAmplitudeRange( double dRange )
      {
        const double result = GenSetAmplitudeRange( m_handle , dRange );
        Library::checkLastStatusAndThrowOnError();

        return result;
      }

      bool amplitudeAutoRanging() const
      {
        const bool result = ( GenGetAmplitudeAutoRanging( m_handle ) != BOOL8_FALSE );
        Library::checkLastStatusAndThrowOnError();

        return result;
      }

      bool setAmplitudeAutoRanging( bool bEnable )
      {
        const bool result = ( GenSetAmplitudeAutoRanging( m_handle , bEnable ? BOOL8_TRUE : BOOL8_FALSE ) != BOOL8_FALSE );
        Library::checkLastStatusAndThrowOnError();

        return result;
      }

      bool hasOffset() const
      {
        const bool result = ( GenHasOffset( m_handle ) != BOOL8_FALSE );
        Library::checkLastStatusAndThrowOnError();

        return result;
      }

      bool hasOffset( uint32_t dwSignalType ) const
      {
        const bool result = ( GenHasOffsetEx( m_handle , dwSignalType ) != BOOL8_FALSE );
        Library::checkLastStatusAndThrowOnError();

        return result;
      }

      double offsetMin() const
      {
        const double result = GenGetOffsetMin( m_handle );
        Library::checkLastStatusAndThrowOnError();

        return result;
      }

      double offsetMax() const
      {
        const double result = GenGetOffsetMax( m_handle );
        Library::checkLastStatusAndThrowOnError();

        return result;
      }

      void getOffsetMinMax( uint32_t dwSignalType , double* pMin , double* pMax ) const
      {
        GenGetOffsetMinMaxEx( m_handle , dwSignalType , pMin , pMax );
        Library::checkLastStatusAndThrowOnError();
      }

      double offset() const
      {
        const double result = GenGetOffset( m_handle );
        Library::checkLastStatusAndThrowOnError();

        return result;
      }

      double setOffset( double dOffset )
      {
        const double result = GenSetOffset( m_handle , dOffset );
        Library::checkLastStatusAndThrowOnError();

        return result;
      }

      double verifyOffset( double dOffset ) const
      {
        const double result = GenVerifyOffset( m_handle , dOffset );
        Library::checkLastStatusAndThrowOnError();

        return result;
      }

      double verifyOffset( double dOffset , uint32_t dwSignalType , double dAmplitude ) const
      {
        const double result = GenVerifyOffsetEx( m_handle , dOffset , dwSignalType , dAmplitude );
        Library::checkLastStatusAndThrowOnError();

        return result;
      }

      uint32_t frequencyModes() const
      {
        const uint32_t result = GenGetFrequencyModes( m_handle );
        Library::checkLastStatusAndThrowOnError();

        return result;
      }

      uint32_t frequencyModes( uint32_t dwSignalType ) const
      {
        const uint32_t result = GenGetFrequencyModesEx( m_handle , dwSignalType );
        Library::checkLastStatusAndThrowOnError();

        return result;
      }

      uint32_t frequencyMode() const
      {
        const uint32_t result = GenGetFrequencyMode( m_handle );
        Library::checkLastStatusAndThrowOnError();

        return result;
      }

      uint32_t setFrequencyMode( uint32_t dwFrequencyMode )
      {
        const uint32_t result = GenSetFrequencyMode( m_handle , dwFrequencyMode );
        Library::checkLastStatusAndThrowOnError();

        return result;
      }

      bool hasFrequency() const
      {
        const bool result = ( GenHasFrequency( m_handle ) != BOOL8_FALSE );
        Library::checkLastStatusAndThrowOnError();

        return result;
      }

      bool hasFrequency( uint32_t dwFrequencyMode , uint32_t dwSignalType ) const
      {
        const bool result = ( GenHasFrequencyEx( m_handle , dwFrequencyMode , dwSignalType ) != BOOL8_FALSE );
        Library::checkLastStatusAndThrowOnError();

        return result;
      }

      double frequencyMin() const
      {
        const double result = GenGetFrequencyMin( m_handle );
        Library::checkLastStatusAndThrowOnError();

        return result;
      }

      double frequencyMax() const
      {
        const double result = GenGetFrequencyMax( m_handle );
        Library::checkLastStatusAndThrowOnError();

        return result;
      }

      void getFrequencyMinMax( uint32_t dwFrequencyMode , double* pMin , double* pMax ) const
      {
        GenGetFrequencyMinMax( m_handle , dwFrequencyMode , pMin , pMax );
        Library::checkLastStatusAndThrowOnError();
      }

      void getFrequencyMinMax( uint32_t dwFrequencyMode , uint32_t dwSignalType , double* pMin , double* pMax ) const
      {
        GenGetFrequencyMinMaxEx( m_handle , dwFrequencyMode , dwSignalType , pMin , pMax );
        Library::checkLastStatusAndThrowOnError();
      }

      double frequency() const
      {
        const double result = GenGetFrequency( m_handle );
        Library::checkLastStatusAndThrowOnError();

        return result;
      }

      double setFrequency( double dFrequency )
      {
        const double result = GenSetFrequency( m_handle , dFrequency );
        Library::checkLastStatusAndThrowOnError();

        return result;
      }

      double verifyFrequency( double dFrequency ) const
      {
        const double result = GenVerifyFrequency( m_handle , dFrequency );
        Library::checkLastStatusAndThrowOnError();

        return result;
      }

      double verifyFrequency( double dFrequency , uint32_t dwFrequencyMode , uint32_t dwSignalType , uint64_t qwDataLength , double dWidth ) const
      {
        const double result = GenVerifyFrequencyEx2( m_handle , dFrequency , dwFrequencyMode , dwSignalType , qwDataLength , dWidth );
        Library::checkLastStatusAndThrowOnError();

        return result;
      }

      bool hasPhase() const
      {
        const bool result = ( GenHasPhase( m_handle ) != BOOL8_FALSE );
        Library::checkLastStatusAndThrowOnError();

        return result;
      }

      bool hasPhase( uint32_t dwSignalType ) const
      {
        const bool result = ( GenHasPhaseEx( m_handle , dwSignalType ) != BOOL8_FALSE );
        Library::checkLastStatusAndThrowOnError();

        return result;
      }

      double phaseMin() const
      {
        const double result = GenGetPhaseMin( m_handle );
        Library::checkLastStatusAndThrowOnError();

        return result;
      }

      double phaseMax() const
      {
        const double result = GenGetPhaseMax( m_handle );
        Library::checkLastStatusAndThrowOnError();

        return result;
      }

      void getPhaseMinMax( uint32_t dwSignalType , double* pMin , double* pMax ) const
      {
        GenGetPhaseMinMaxEx( m_handle , dwSignalType , pMin , pMax );
        Library::checkLastStatusAndThrowOnError();
      }

      double phase() const
      {
        const double result = GenGetPhase( m_handle );
        Library::checkLastStatusAndThrowOnError();

        return result;
      }

      double setPhase( double dPhase )
      {
        const double result = GenSetPhase( m_handle , dPhase );
        Library::checkLastStatusAndThrowOnError();

        return result;
      }

      double verifyPhase( double dPhase ) const
      {
        const double result = GenVerifyPhase( m_handle , dPhase );
        Library::checkLastStatusAndThrowOnError();

        return result;
      }

      double verifyPhase( double dPhase , uint32_t dwSignalType ) const
      {
        const double result = GenVerifyPhaseEx( m_handle , dPhase , dwSignalType );
        Library::checkLastStatusAndThrowOnError();

        return result;
      }

      bool hasSymmetry() const
      {
        const bool result = ( GenHasSymmetry( m_handle ) != BOOL8_FALSE );
        Library::checkLastStatusAndThrowOnError();

        return result;
      }

      bool hasSymmetry( uint32_t dwSignalType ) const
      {
        const bool result = ( GenHasSymmetryEx( m_handle , dwSignalType ) != BOOL8_FALSE );
        Library::checkLastStatusAndThrowOnError();

        return result;
      }

      double symmetryMin() const
      {
        const double result = GenGetSymmetryMin( m_handle );
        Library::checkLastStatusAndThrowOnError();

        return result;
      }

      double symmetryMax() const
      {
        const double result = GenGetSymmetryMax( m_handle );
        Library::checkLastStatusAndThrowOnError();

        return result;
      }

      void getSymmetryMinMax( uint32_t dwSignalType , double* pMin , double* pMax ) const
      {
        GenGetSymmetryMinMaxEx( m_handle , dwSignalType , pMin , pMax );
        Library::checkLastStatusAndThrowOnError();
      }

      double symmetry() const
      {
        const double result = GenGetSymmetry( m_handle );
        Library::checkLastStatusAndThrowOnError();

        return result;
      }

      double setSymmetry( double dSymmetry )
      {
        const double result = GenSetSymmetry( m_handle , dSymmetry );
        Library::checkLastStatusAndThrowOnError();

        return result;
      }

      double verifySymmetry( double dSymmetry ) const
      {
        const double result = GenVerifySymmetry( m_handle , dSymmetry );
        Library::checkLastStatusAndThrowOnError();

        return result;
      }

      double verifySymmetry( double dSymmetry , uint32_t dwSignalType ) const
      {
        const double result = GenVerifySymmetryEx( m_handle , dSymmetry , dwSignalType );
        Library::checkLastStatusAndThrowOnError();

        return result;
      }

      bool hasWidth() const
      {
        const bool result = ( GenHasWidth( m_handle ) != BOOL8_FALSE );
        Library::checkLastStatusAndThrowOnError();

        return result;
      }

      bool hasWidth( uint32_t dwSignalType ) const
      {
        const bool result = ( GenHasWidthEx( m_handle , dwSignalType ) != BOOL8_FALSE );
        Library::checkLastStatusAndThrowOnError();

        return result;
      }

      double widthMin() const
      {
        const double result = GenGetWidthMin( m_handle );
        Library::checkLastStatusAndThrowOnError();

        return result;
      }

      double widthMax() const
      {
        const double result = GenGetWidthMax( m_handle );
        Library::checkLastStatusAndThrowOnError();

        return result;
      }

      void widthMinMax( uint32_t dwSignalType , double dSignalFrequency , double* pMin , double* pMax ) const
      {
        GenGetWidthMinMaxEx( m_handle , dwSignalType , dSignalFrequency , pMin , pMax );
        Library::checkLastStatusAndThrowOnError();
      }

      double width() const
      {
        const double result = GenGetWidth( m_handle );
        Library::checkLastStatusAndThrowOnError();

        return result;
      }

      double setWidth( double dWidth )
      {
        const double result = GenSetWidth( m_handle , dWidth );
        Library::checkLastStatusAndThrowOnError();

        return result;
      }

      double verifyWidth( double dWidth ) const
      {
        const double result = GenVerifyWidth( m_handle , dWidth );
        Library::checkLastStatusAndThrowOnError();

        return result;
      }

      double verifyWidth( double dWidth , uint32_t dwSignalType , double dSignalFrequency ) const
      {
        const double result = GenVerifyWidthEx( m_handle , dWidth , dwSignalType , dSignalFrequency );
        Library::checkLastStatusAndThrowOnError();

        return result;
      }

      bool hasEdgeTime() const
      {
        const bool result = ( GenHasEdgeTime( m_handle ) != BOOL8_FALSE );
        Library::checkLastStatusAndThrowOnError();

        return result;
      }

      bool hasEdgeTime( uint32_t dwSignalType ) const
      {
        const bool result = ( GenHasEdgeTimeEx( m_handle , dwSignalType ) != BOOL8_FALSE );
        Library::checkLastStatusAndThrowOnError();

        return result;
      }

      double leadingEdgeTimeMin() const
      {
        const double result = GenGetLeadingEdgeTimeMin( m_handle );
        Library::checkLastStatusAndThrowOnError();

        return result;
      }

      double leadingEdgeTimeMax() const
      {
        const double result = GenGetLeadingEdgeTimeMax( m_handle );
        Library::checkLastStatusAndThrowOnError();

        return result;
      }

      void getLeadingEdgeTimeMinMax( uint32_t dwSignalType , double dSignalFrequency , double dSymmetry , double dWidth , double dTrailingEdgeTime , double* pMin , double* pMax ) const
      {
        GenGetLeadingEdgeTimeMinMaxEx( m_handle , dwSignalType , dSignalFrequency , dSymmetry , dWidth , dTrailingEdgeTime , pMin , pMax );
        Library::checkLastStatusAndThrowOnError();
      }

      double leadingEdgeTime() const
      {
        const double result = GenGetLeadingEdgeTime( m_handle );
        Library::checkLastStatusAndThrowOnError();

        return result;
      }

      double setLeadingEdgeTime( double dLeadingEdgeTime )
      {
        const double result = GenSetLeadingEdgeTime( m_handle , dLeadingEdgeTime );
        Library::checkLastStatusAndThrowOnError();

        return result;
      }

      double verifyLeadingEdgeTime( double dLeadingEdgeTime ) const
      {
        const double result = GenVerifyLeadingEdgeTime( m_handle , dLeadingEdgeTime );
        Library::checkLastStatusAndThrowOnError();

        return result;
      }

      double verifyLeadingEdgeTime( double dLeadingEdgeTime , uint32_t dwSignalType , double dSignalFrequency , double dSymmetry , double dWidth , double dTrailingEdgeTime ) const
      {
        const double result = GenVerifyLeadingEdgeTimeEx( m_handle , dLeadingEdgeTime , dwSignalType , dSignalFrequency , dSymmetry , dWidth , dTrailingEdgeTime );
        Library::checkLastStatusAndThrowOnError();

        return result;
      }

      double trailingEdgeTimeMin() const
      {
        const double result = GenGetTrailingEdgeTimeMin( m_handle );
        Library::checkLastStatusAndThrowOnError();

        return result;
      }

      double trailingEdgeTimeMax() const
      {
        const double result = GenGetTrailingEdgeTimeMax( m_handle );
        Library::checkLastStatusAndThrowOnError();

        return result;
      }

      void getTrailingEdgeTimeMinMax( uint32_t dwSignalType , double dSignalFrequency , double dSymmetry , double dWidth , double dLeadingEdgeTime , double* pMin , double* pMax ) const
      {
        GenGetTrailingEdgeTimeMinMaxEx( m_handle , dwSignalType , dSignalFrequency , dSymmetry , dWidth , dLeadingEdgeTime , pMin , pMax );
        Library::checkLastStatusAndThrowOnError();
      }

      double trailingEdgeTime() const
      {
        const double result = GenGetTrailingEdgeTime( m_handle );
        Library::checkLastStatusAndThrowOnError();

        return result;
      }

      double setTrailingEdgeTime( double dTrailingEdgeTime )
      {
        const double result = GenSetTrailingEdgeTime( m_handle , dTrailingEdgeTime );
        Library::checkLastStatusAndThrowOnError();

        return result;
      }

      double verifyTrailingEdgeTime( double dTrailingEdgeTime ) const
      {
        const double result = GenVerifyTrailingEdgeTime( m_handle , dTrailingEdgeTime );
        Library::checkLastStatusAndThrowOnError();

        return result;
      }

      double verifyTrailingEdgeTime( double dTrailingEdgeTime , uint32_t dwSignalType , double dSignalFrequency , double dSymmetry , double dWidth , double dLeadingEdgeTime ) const
      {
        const double result = GenVerifyTrailingEdgeTimeEx( m_handle , dTrailingEdgeTime , dwSignalType , dSignalFrequency , dSymmetry , dWidth , dLeadingEdgeTime );
        Library::checkLastStatusAndThrowOnError();

        return result;
      }

      bool hasData() const
      {
        const bool result = ( GenHasData( m_handle ) != BOOL8_FALSE );
        Library::checkLastStatusAndThrowOnError();

        return result;
      }

      bool hasData( uint32_t dwSignalType ) const
      {
        const bool result = ( GenHasDataEx( m_handle , dwSignalType ) != BOOL8_FALSE );
        Library::checkLastStatusAndThrowOnError();

        return result;
      }

      uint64_t dataLengthMin() const
      {
        const uint64_t result = GenGetDataLengthMin( m_handle );
        Library::checkLastStatusAndThrowOnError();

        return result;
      }

      uint64_t dataLengthMax() const
      {
        const uint64_t result = GenGetDataLengthMax( m_handle );
        Library::checkLastStatusAndThrowOnError();

        return result;
      }

      void getDataLengthMinMax( uint32_t dwSignalType , uint64_t* pMin , uint64_t* pMax ) const
      {
        GenGetDataLengthMinMaxEx( m_handle , dwSignalType , pMin , pMax );
        Library::checkLastStatusAndThrowOnError();
      }

      uint64_t dataLength() const
      {
        const uint64_t result = GenGetDataLength( m_handle );
        Library::checkLastStatusAndThrowOnError();

        return result;
      }

      uint64_t verifyDataLength( uint64_t qwDataLength ) const
      {
        const uint64_t result = GenVerifyDataLength( m_handle , qwDataLength );
        Library::checkLastStatusAndThrowOnError();

        return result;
      }

      uint64_t verifyDataLength( uint64_t qwDataLength , uint32_t dwSignalType ) const
      {
        const uint64_t result = GenVerifyDataLengthEx( m_handle , qwDataLength , dwSignalType );
        Library::checkLastStatusAndThrowOnError();

        return result;
      }

      void setData( const float* pBuffer , uint64_t qwSampleCount )
      {
        GenSetData( m_handle , pBuffer , qwSampleCount );
        Library::checkLastStatusAndThrowOnError();
      }

      void setData( const float* pBuffer , uint64_t qwSampleCount , uint32_t dwSignalType , uint32_t dwReserved )
      {
        GenSetDataEx( m_handle , pBuffer , qwSampleCount , dwSignalType , dwReserved );
        Library::checkLastStatusAndThrowOnError();
      }

      uint32_t dataRawType() const
      {
        const uint32_t result = GenGetDataRawType( m_handle );
        Library::checkLastStatusAndThrowOnError();

        return result;
      }

      void dataRawValueRange( int64_t* pMin , int64_t* pZero , int64_t* pMax ) const
      {
        GenGetDataRawValueRange( m_handle , pMin , pZero , pMax );
        Library::checkLastStatusAndThrowOnError();
      }

      int64_t dataRawValueMin() const
      {
        const int64_t result = GenGetDataRawValueMin( m_handle );
        Library::checkLastStatusAndThrowOnError();

        return result;
      }

      int64_t dataRawValueZero() const
      {
        const int64_t result = GenGetDataRawValueZero( m_handle );
        Library::checkLastStatusAndThrowOnError();

        return result;
      }

      int64_t dataRawValueMax() const
      {
        const int64_t result = GenGetDataRawValueMax( m_handle );
        Library::checkLastStatusAndThrowOnError();

        return result;
      }

      void setDataRaw( const void* pBuffer , uint64_t qwSampleCount )
      {
        GenSetDataRaw( m_handle , pBuffer , qwSampleCount );
        Library::checkLastStatusAndThrowOnError();
      }

      void setDataRaw( const void* pBuffer , uint64_t qwSampleCount , uint32_t dwSignalType , uint32_t dwReserved )
      {
        GenSetDataRawEx( m_handle , pBuffer , qwSampleCount , dwSignalType , dwReserved );
        Library::checkLastStatusAndThrowOnError();
      }

      uint64_t modes() const
      {
        const uint64_t result = GenGetModes( m_handle );
        Library::checkLastStatusAndThrowOnError();

        return result;
      }

      uint64_t modes( uint32_t dwSignalType , uint32_t dwFrequencyMode ) const
      {
        const uint64_t result = GenGetModesEx( m_handle , dwSignalType , dwFrequencyMode );
        Library::checkLastStatusAndThrowOnError();

        return result;
      }

      uint64_t modesNative() const
      {
        const uint64_t result = GenGetModesNative( m_handle );
        Library::checkLastStatusAndThrowOnError();

        return result;
      }

      uint64_t mode() const
      {
        const uint64_t result = GenGetMode( m_handle );
        Library::checkLastStatusAndThrowOnError();

        return result;
      }

      uint64_t setMode( uint64_t qwGeneratorMode )
      {
        const uint64_t result = GenSetMode( m_handle , qwGeneratorMode );
        Library::checkLastStatusAndThrowOnError();

        return result;
      }

      bool isBurstActive() const
      {
        const bool result = ( GenIsBurstActive( m_handle ) != BOOL8_FALSE );
        Library::checkLastStatusAndThrowOnError();

        return result;
      }

      uint64_t burstCountMin() const
      {
        const uint64_t result = GenGetBurstCountMin( m_handle );
        Library::checkLastStatusAndThrowOnError();

        return result;
      }

      uint64_t burstCountMax() const
      {
        const uint64_t result = GenGetBurstCountMax( m_handle );
        Library::checkLastStatusAndThrowOnError();

        return result;
      }

      void burstCountMinMax( uint64_t qwGeneratorMode , uint64_t* pMin , uint64_t* pMax ) const
      {
        GenGetBurstCountMinMaxEx( m_handle , qwGeneratorMode , pMin , pMax );
        Library::checkLastStatusAndThrowOnError();
      }

      uint64_t burstCount() const
      {
        const uint64_t result = GenGetBurstCount( m_handle );
        Library::checkLastStatusAndThrowOnError();

        return result;
      }

      uint64_t setBurstCount( uint64_t qwBurstCount )
      {
        const uint64_t result = GenSetBurstCount( m_handle , qwBurstCount );
        Library::checkLastStatusAndThrowOnError();

        return result;
      }

      uint64_t burstSampleCountMin() const
      {
        const uint64_t result = GenGetBurstSampleCountMin( m_handle );
        Library::checkLastStatusAndThrowOnError();

        return result;
      }

      uint64_t burstSampleCountMax() const
      {
        const uint64_t result = GenGetBurstSampleCountMax( m_handle );
        Library::checkLastStatusAndThrowOnError();

        return result;
      }

      void burstSampleCountMinMax( uint64_t qwGeneratorMode , uint64_t* pMin , uint64_t* pMax ) const
      {
        GenGetBurstSampleCountMinMaxEx( m_handle , qwGeneratorMode , pMin , pMax );
        Library::checkLastStatusAndThrowOnError();
      }

      uint64_t burstSampleCount() const
      {
        const uint64_t result = GenGetBurstSampleCount( m_handle );
        Library::checkLastStatusAndThrowOnError();

        return result;
      }

      uint64_t setBurstSampleCount( uint64_t qwBurstSampleCount )
      {
        const uint64_t result = GenSetBurstSampleCount( m_handle , qwBurstSampleCount );
        Library::checkLastStatusAndThrowOnError();

        return result;
      }

      uint64_t burstSegmentCountMin() const
      {
        const uint64_t result = GenGetBurstSegmentCountMin( m_handle );
        Library::checkLastStatusAndThrowOnError();

        return result;
      }

      uint64_t burstSegmentCountMax() const
      {
        const uint64_t result = GenGetBurstSegmentCountMax( m_handle );
        Library::checkLastStatusAndThrowOnError();

        return result;
      }

      void burstSegmentCountMinMax( uint64_t qwGeneratorMode , uint32_t dwSignalType , uint32_t dwFrequencyMode , double dFrequency , uint64_t qwDataLength , uint64_t* pMin , uint64_t* pMax ) const
      {
        GenGetBurstSegmentCountMinMaxEx( m_handle , qwGeneratorMode , dwSignalType , dwFrequencyMode , dFrequency , qwDataLength , pMin , pMax );
        Library::checkLastStatusAndThrowOnError();
      }

      uint64_t burstSegmentCount() const
      {
        const uint64_t result = GenGetBurstSegmentCount( m_handle );
        Library::checkLastStatusAndThrowOnError();

        return result;
      }

      uint64_t setBurstSegmentCount( uint64_t qwBurstSegmentCount )
      {
        const uint64_t result = GenSetBurstSegmentCount( m_handle , qwBurstSegmentCount );
        Library::checkLastStatusAndThrowOnError();

        return result;
      }

      uint64_t verifyBurstSegmentCount( uint64_t qwBurstSegmentCount ) const
      {
        const uint64_t result = GenVerifyBurstSegmentCount( m_handle , qwBurstSegmentCount );
        Library::checkLastStatusAndThrowOnError();

        return result;
      }

      uint64_t verifyBurstSegmentCount( uint64_t qwBurstSegmentCount , uint64_t qwGeneratorMode , uint32_t dwSignalType , uint32_t dwFrequencyMode , double dFrequency , uint64_t qwDataLength ) const
      {
        const uint64_t result = GenVerifyBurstSegmentCountEx( m_handle , qwBurstSegmentCount , qwGeneratorMode , dwSignalType , dwFrequencyMode , dFrequency , qwDataLength );
        Library::checkLastStatusAndThrowOnError();

        return result;
      }

      void setCallbackBurstCompleted( TpCallback_t pCallback , void* pData )
      {
        GenSetCallbackBurstCompleted( m_handle , pCallback , pData );
        Library::checkLastStatusAndThrowOnError();
      }

#ifdef LIBTIEPIE_LINUX
      void setEventBurstCompleted( int fdEvent )
      {
        GenSetEventBurstCompleted( m_handle , fdEvent );
        Library::checkLastStatusAndThrowOnError();
      }
#endif

#ifdef LIBTIEPIE_WINDOWS
      void setEventBurstCompleted( HANDLE hEvent )
      {
        GenSetEventBurstCompleted( m_handle , hEvent );
        Library::checkLastStatusAndThrowOnError();
      }

      void setMessageBurstCompleted( HWND hWnd , WPARAM wParam , LPARAM lParam )
      {
        GenSetMessageBurstCompleted( m_handle , hWnd , wParam , lParam );
        Library::checkLastStatusAndThrowOnError();
      }
#endif

      void setCallbackControllableChanged( TpCallback_t pCallback , void* pData )
      {
        GenSetCallbackControllableChanged( m_handle , pCallback , pData );
        Library::checkLastStatusAndThrowOnError();
      }

#ifdef LIBTIEPIE_LINUX
      void setEventControllableChanged( int fdEvent )
      {
        GenSetEventControllableChanged( m_handle , fdEvent );
        Library::checkLastStatusAndThrowOnError();
      }
#endif

#ifdef LIBTIEPIE_WINDOWS
      void setEventControllableChanged( HANDLE hEvent )
      {
        GenSetEventControllableChanged( m_handle , hEvent );
        Library::checkLastStatusAndThrowOnError();
      }

      void setMessageControllableChanged( HWND hWnd , WPARAM wParam , LPARAM lParam )
      {
        GenSetMessageControllableChanged( m_handle , hWnd , wParam , lParam );
        Library::checkLastStatusAndThrowOnError();
      }
#endif
  };

  class I2CHost : public Device
  {
    public:
      I2CHost( Handle_t hDevice ) :
        Device( hDevice )
      {
      }

      bool isInternalAddress( uint16_t wAddress ) const
      {
        const bool result = ( I2CIsInternalAddress( m_handle , wAddress ) != BOOL8_FALSE );
        Library::checkLastStatusAndThrowOnError();

        return result;
      }

      const std::vector<uint16_t> internalAddresses() const
      {
        const uint32_t dwLength = I2CGetInternalAddresses( m_handle , 0 , 0 );
        Library::checkLastStatusAndThrowOnError();
        Buffer<uint16_t> tmp( dwLength );
        I2CGetInternalAddresses( m_handle , *tmp , dwLength );
        Library::checkLastStatusAndThrowOnError();
        return std::vector<uint16_t>( *tmp , *tmp + dwLength );
      }

      void read( uint16_t wAddress , void* pBuffer , uint32_t dwSize , bool bStop )
      {
        I2CRead( m_handle , wAddress , pBuffer , dwSize , bStop ? BOOL8_TRUE : BOOL8_FALSE );
        Library::checkLastStatusAndThrowOnError();
      }

      uint8_t readByte( uint16_t wAddress )
      {
        uint8_t value;
        I2CReadByte( m_handle , wAddress , &value );
        Library::checkLastStatusAndThrowOnError();
        return value;
      }

      uint16_t readWord( uint16_t wAddress )
      {
        uint16_t value;
        I2CReadWord( m_handle , wAddress , &value );
        Library::checkLastStatusAndThrowOnError();
        return value;
      }

      void write( uint16_t wAddress , const void* pBuffer , uint32_t dwSize , bool bStop )
      {
        I2CWrite( m_handle , wAddress , pBuffer , dwSize , bStop ? BOOL8_TRUE : BOOL8_FALSE );
        Library::checkLastStatusAndThrowOnError();
      }

      void writeByte( uint16_t wAddress , uint8_t byValue )
      {
        I2CWriteByte( m_handle , wAddress , byValue );
        Library::checkLastStatusAndThrowOnError();
      }

      void writeByteByte( uint16_t wAddress , uint8_t byValue1 , uint8_t byValue2 )
      {
        I2CWriteByteByte( m_handle , wAddress , byValue1 , byValue2 );
        Library::checkLastStatusAndThrowOnError();
      }

      void writeByteWord( uint16_t wAddress , uint8_t byValue1 , uint16_t wValue2 )
      {
        I2CWriteByteWord( m_handle , wAddress , byValue1 , wValue2 );
        Library::checkLastStatusAndThrowOnError();
      }

      void writeWord( uint16_t wAddress , uint16_t wValue )
      {
        I2CWriteWord( m_handle , wAddress , wValue );
        Library::checkLastStatusAndThrowOnError();
      }

      void writeRead( uint16_t wAddress , const void* pWriteBuffer , uint32_t dwWriteSize , void* pReadBuffer , uint32_t dwReadSize )
      {
        I2CWriteRead( m_handle , wAddress , pWriteBuffer , dwWriteSize , pReadBuffer , dwReadSize );
        Library::checkLastStatusAndThrowOnError();
      }

      double speedMax() const
      {
        const double result = I2CGetSpeedMax( m_handle );
        Library::checkLastStatusAndThrowOnError();

        return result;
      }

      double speed() const
      {
        const double result = I2CGetSpeed( m_handle );
        Library::checkLastStatusAndThrowOnError();

        return result;
      }

      double setSpeed( double dSpeed )
      {
        const double result = I2CSetSpeed( m_handle , dSpeed );
        Library::checkLastStatusAndThrowOnError();

        return result;
      }

      double verifySpeed( double dSpeed ) const
      {
        const double result = I2CVerifySpeed( m_handle , dSpeed );
        Library::checkLastStatusAndThrowOnError();

        return result;
      }
  };

  class DeviceListItem
  {
    protected:
      const uint32_t m_serialNumber;

    public:
      DeviceListItem( uint32_t dwSerialNumber ) :
        m_serialNumber( dwSerialNumber )
      {
      }

      Device* openDevice( uint32_t dwDeviceType )
      {
        const Handle_t result = LstOpenDevice( IDKIND_SERIALNUMBER , m_serialNumber , dwDeviceType );
        Library::checkLastStatusAndThrowOnError();

        switch( dwDeviceType )
        {
          case DEVICETYPE_OSCILLOSCOPE:
            return Library::createObject<Device,Oscilloscope>( result );

          case DEVICETYPE_GENERATOR:
            return Library::createObject<Device,Generator>( result );

          case DEVICETYPE_I2CHOST:
            return Library::createObject<Device,I2CHost>( result );

          default:
            ObjClose( result );
            throw InvalidValueException();
        }
      }

      Oscilloscope* openOscilloscope()
      {
        const Handle_t result = LstOpenOscilloscope( IDKIND_SERIALNUMBER , m_serialNumber );
        Library::checkLastStatusAndThrowOnError();

        return new Oscilloscope( result );
      }

      Generator* openGenerator()
      {
        const Handle_t result = LstOpenGenerator( IDKIND_SERIALNUMBER , m_serialNumber );
        Library::checkLastStatusAndThrowOnError();

        return new Generator( result );
      }

      I2CHost* openI2CHost()
      {
        const Handle_t result = LstOpenI2CHost( IDKIND_SERIALNUMBER , m_serialNumber );
        Library::checkLastStatusAndThrowOnError();

        return new I2CHost( result );
      }

      bool canOpen( uint32_t dwDeviceType ) const
      {
        const bool result = ( LstDevCanOpen( IDKIND_SERIALNUMBER , m_serialNumber , dwDeviceType ) != BOOL8_FALSE );
        Library::checkLastStatusAndThrowOnError();

        return result;
      }

      uint32_t productId() const
      {
        const uint32_t result = LstDevGetProductId( IDKIND_SERIALNUMBER , m_serialNumber );
        Library::checkLastStatusAndThrowOnError();

        return result;
      }

      uint32_t vendorId() const
      {
        const uint32_t result = LstDevGetVendorId( IDKIND_SERIALNUMBER , m_serialNumber );
        Library::checkLastStatusAndThrowOnError();

        return result;
      }

      const std::string name() const
      {
        const uint32_t dwLength = LstDevGetName( IDKIND_SERIALNUMBER , m_serialNumber , 0 , 0 ) + 1;
        Library::checkLastStatusAndThrowOnError();
        Buffer<char> s( dwLength );
        LstDevGetName( IDKIND_SERIALNUMBER , m_serialNumber , *s , dwLength );
        Library::checkLastStatusAndThrowOnError();
        return *s;
      }

      const std::string nameShort() const
      {
        const uint32_t dwLength = LstDevGetNameShort( IDKIND_SERIALNUMBER , m_serialNumber , 0 , 0 ) + 1;
        Library::checkLastStatusAndThrowOnError();
        Buffer<char> s( dwLength );
        LstDevGetNameShort( IDKIND_SERIALNUMBER , m_serialNumber , *s , dwLength );
        Library::checkLastStatusAndThrowOnError();
        return *s;
      }

      const std::string nameShortest() const
      {
        const uint32_t dwLength = LstDevGetNameShortest( IDKIND_SERIALNUMBER , m_serialNumber , 0 , 0 ) + 1;
        Library::checkLastStatusAndThrowOnError();
        Buffer<char> s( dwLength );
        LstDevGetNameShortest( IDKIND_SERIALNUMBER , m_serialNumber , *s , dwLength );
        Library::checkLastStatusAndThrowOnError();
        return *s;
      }

      TpVersion_t driverVersion() const
      {
        const TpVersion_t result = LstDevGetDriverVersion( IDKIND_SERIALNUMBER , m_serialNumber );
        Library::checkLastStatusAndThrowOnError();

        return result;
      }

      TpVersion_t recommendedDriverVersion() const
      {
        const TpVersion_t result = LstDevGetRecommendedDriverVersion( IDKIND_SERIALNUMBER , m_serialNumber );
        Library::checkLastStatusAndThrowOnError();

        return result;
      }

      TpVersion_t firmwareVersion() const
      {
        const TpVersion_t result = LstDevGetFirmwareVersion( IDKIND_SERIALNUMBER , m_serialNumber );
        Library::checkLastStatusAndThrowOnError();

        return result;
      }

      TpVersion_t recommendedFirmwareVersion() const
      {
        const TpVersion_t result = LstDevGetRecommendedFirmwareVersion( IDKIND_SERIALNUMBER , m_serialNumber );
        Library::checkLastStatusAndThrowOnError();

        return result;
      }

      TpDate_t calibrationDate() const
      {
        const TpDate_t result = LstDevGetCalibrationDate( IDKIND_SERIALNUMBER , m_serialNumber );
        Library::checkLastStatusAndThrowOnError();

        return result;
      }

      uint32_t serialNumber() const
      {
        const uint32_t result = LstDevGetSerialNumber( IDKIND_SERIALNUMBER , m_serialNumber );
        Library::checkLastStatusAndThrowOnError();

        return result;
      }

      uint32_t ipv4Address() const
      {
        const uint32_t result = LstDevGetIPv4Address( IDKIND_SERIALNUMBER , m_serialNumber );
        Library::checkLastStatusAndThrowOnError();

        return result;
      }

      uint16_t ipPort() const
      {
        const uint16_t result = LstDevGetIPPort( IDKIND_SERIALNUMBER , m_serialNumber );
        Library::checkLastStatusAndThrowOnError();

        return result;
      }

      bool hasServer() const
      {
        const bool result = ( LstDevHasServer( IDKIND_SERIALNUMBER , m_serialNumber ) != BOOL8_FALSE );
        Library::checkLastStatusAndThrowOnError();

        return result;
      }

      Server* server() const
      {
        const Handle_t result = LstDevGetServer( IDKIND_SERIALNUMBER , m_serialNumber );
        Library::checkLastStatusAndThrowOnError();

        return new Server( result );
      }

      uint32_t types() const
      {
        const uint32_t result = LstDevGetTypes( IDKIND_SERIALNUMBER , m_serialNumber );
        Library::checkLastStatusAndThrowOnError();

        return result;
      }
  };

  class DeviceList
  {
    public:
      static DeviceListItem* getItemByProductId( uint32_t dwProductId )
      {
        uint32_t dwSerialNumber = LstDevGetSerialNumber( IDKIND_PRODUCTID , dwProductId );

        Library::checkLastStatusAndThrowOnError();

        return new DeviceListItem( dwSerialNumber );
      }

      static DeviceListItem* getItemByIndex( uint32_t dwIndex )
      {
        uint32_t dwSerialNumber = LstDevGetSerialNumber( IDKIND_INDEX , dwIndex );

        Library::checkLastStatusAndThrowOnError();

        return new DeviceListItem( dwSerialNumber );
      }

      static DeviceListItem* getItemBySerialNumber( uint32_t dwSerialNumber )
      {
        dwSerialNumber = LstDevGetSerialNumber( IDKIND_SERIALNUMBER , dwSerialNumber );

        Library::checkLastStatusAndThrowOnError();

        return new DeviceListItem( dwSerialNumber );
      }

      static void update()
      {
        LstUpdate();
        Library::checkLastStatusAndThrowOnError();
      }

      static uint32_t count()
      {
        const uint32_t result = LstGetCount();
        Library::checkLastStatusAndThrowOnError();

        return result;
      }

      static DeviceListItem* createCombinedDevice( Device** pDevices , uint32_t dwCount )
      {
        if( !pDevices )
          throw InvalidValueException();

        Buffer<Handle_t> DeviceHandles( dwCount );

        for( uint32_t i = 0 ; i < dwCount ; i++ )
        {
          if( !pDevices[ i ] )
            throw InvalidValueException();

          (*DeviceHandles)[ i ] = pDevices[ i ]->handle();
        }

        const uint32_t dwSerialNumber = LstCreateCombinedDevice( *DeviceHandles , dwCount );

        Library::checkLastStatusAndThrowOnError();

        return getItemBySerialNumber( dwSerialNumber );
      }

      static Device* createAndOpenCombinedDevice( Device** pDevices , uint32_t dwCount )
      {
        DeviceListItem* pItem = createCombinedDevice( pDevices , dwCount );
        Device* pDevice;

        try
        {
          pDevice = pItem->openDevice( pItem->types() );
        }
        catch( std::exception& e )
        {
          delete pItem;
          throw e;
        }

        delete pItem;

        return pDevice;
      }

      static void removeDevice( uint32_t dwSerialNumber )
      {
        LstRemoveDevice( dwSerialNumber );
        Library::checkLastStatusAndThrowOnError();
      }

      static void removeDeviceForce( uint32_t dwSerialNumber )
      {
        LstRemoveDeviceForce( dwSerialNumber );
        Library::checkLastStatusAndThrowOnError();
      }

      static void setCallbackDeviceAdded( TpCallbackDeviceList_t pCallback , void* pData )
      {
        LstSetCallbackDeviceAdded( pCallback , pData );
        Library::checkLastStatusAndThrowOnError();
      }

      static void setCallbackDeviceRemoved( TpCallbackDeviceList_t pCallback , void* pData )
      {
        LstSetCallbackDeviceRemoved( pCallback , pData );
        Library::checkLastStatusAndThrowOnError();
      }

      static void setCallbackDeviceCanOpenChanged( TpCallbackDeviceList_t pCallback , void* pData )
      {
        LstSetCallbackDeviceCanOpenChanged( pCallback , pData );
        Library::checkLastStatusAndThrowOnError();
      }

#ifdef LIBTIEPIE_LINUX
      static void setEventDeviceAdded( int fdEvent )
      {
        LstSetEventDeviceAdded( fdEvent );
        Library::checkLastStatusAndThrowOnError();
      }

      static void setEventDeviceRemoved( int fdEvent )
      {
        LstSetEventDeviceRemoved( fdEvent );
        Library::checkLastStatusAndThrowOnError();
      }

      static void setEventDeviceCanOpenChanged( int fdEvent )
      {
        LstSetEventDeviceCanOpenChanged( fdEvent );
        Library::checkLastStatusAndThrowOnError();
      }
#endif

#ifdef LIBTIEPIE_WINDOWS
      static void setEventDeviceAdded( HANDLE hEvent )
      {
        LstSetEventDeviceAdded( hEvent );
        Library::checkLastStatusAndThrowOnError();
      }

      static void setEventDeviceRemoved( HANDLE hEvent )
      {
        LstSetEventDeviceRemoved( hEvent );
        Library::checkLastStatusAndThrowOnError();
      }

      static void setEventDeviceCanOpenChanged( HANDLE hEvent )
      {
        LstSetEventDeviceCanOpenChanged( hEvent );
        Library::checkLastStatusAndThrowOnError();
      }

      static void setMessageDeviceAdded( HWND hWnd )
      {
        LstSetMessageDeviceAdded( hWnd );
        Library::checkLastStatusAndThrowOnError();
      }

      static void setMessageDeviceRemoved( HWND hWnd )
      {
        LstSetMessageDeviceRemoved( hWnd );
        Library::checkLastStatusAndThrowOnError();
      }

      static void setMessageDeviceCanOpenChanged( HWND hWnd )
      {
        LstSetMessageDeviceCanOpenChanged( hWnd );
        Library::checkLastStatusAndThrowOnError();
      }
#endif
  };
}

#endif
