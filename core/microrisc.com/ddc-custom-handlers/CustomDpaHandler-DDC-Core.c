// *********************************************************************
//   Custom DPA Handler code example - DDC-SE-01 and/or DDC-RE-01      *
// *********************************************************************
//
// File:    $RCSfile: CustomDpaHandler-DDC-Core.c,v $
// Version: $Revision: 1.5 $
// Date:    $Date: 2017/01/03 09:44:13 $
//
// Revision history:
//   2017/01/03  Release for DPA 2.28, 3.00
//
// *********************************************************************

// Online DPA documentation http://www.iqrf.org/DpaTechGuide/

/* This example implements HWP for DDC-SE-01 and/or DDC-RE-01
The example will not work at demo DPA version because demo DPA does not support PCMD != 0

DDC-SE-01: HWPID=0x001E
DDC-RE-01: HWPID=0x002E
DDC-SE-01 & DDC-RE-01: HWPID=0x003E

----------- DDC-SE-01
Request: PNUM = 0x20, PCMD = 0x31
Response:
 PData[0]=Temperature at [C]
 PData[1]=Photoresistor value 0x00-0xFF
 PData[2]=Potentiometer value 0x00-0xFF
 returns ERROR_FAIL when error reading temperature

FRC=0xC0, returns temperature at C, 127 for 0 C, 0x80 for error reading temperature
FRC=0xC1, returns photoresistor value, returns 1 instead of 0
FRC=0xC2, returns potentiometer value, returns 1 instead of 0

----------- DDC-RE-01
Request: PNUM = 0x20, PCMD = 0x32
 PData[0]=Relay1Ctrl
 PData[1]=Relay2Ctrl

Response:
 PData[0]=Relay1State
 PData[1]=Relay2State

RelayCtrl: 0=Switch the Relay off, 1=Switch the Relay on, Other=Do not control the Relay
RelayState: 0=Relay was off, 1=Relay was on
*/

// *********************************************************************

// Default IQRF include (modify the path according to your setup)
#include "template-basic.h"

// Default DPA header (modify the path according to your setup)
#include "DPA.h"
// Default Custom DPA Handler header (modify the path according to your setup)
#include "DPAcustomHandler.h"

#if defined( DDC_SE_01 ) && defined( DDC_RE_01 )
#define	ThisHWPID 0x003E
#elif defined( DDC_SE_01 )
#define	ThisHWPID 0x001E
#elif defined( DDC_RE_01 )
#define	ThisHWPID 0x002E
#else
#error Symbol(s) DDC_SE_01 and/or DDC_RE_01 must be defined
#endif

//############################################################################################

#if defined( DDC_SE_01 )

// Special temperature value to indicate a sensor error 
#define	ERROR_TEMPERATURE 0xF800

// Sensor connected to PORT C.3 (compatible with DDC-SE-01)
#define OneWire_TRIS         TRISC.3
#define OneWire_IO_IN        PORTC.3
#define OneWire_IO_OUT       LATC.3

// Writes sensor configuration (resolution)
bit Ds18B20WriteConfig( uns8 value );

// Resets OneWire
bit OneWireReset();
// Reads OneWire byte
uns8 OneWireReadByte();
// Writes OneWire byte
void OneWireWriteByte( uns8 byte );

// DS18B20 commands
#define CMD_READROM		  0x33
#define CMD_CONVERTTEMP	  0x44
#define CMD_CPYSCRATCHPAD 0x48
#define CMD_WSCRATCHPAD	  0x4e
#define CMD_MATCHROM	  0x55
#define CMD_RPWRSUPPLY	  0xb4
#define CMD_RECEEPROM	  0xb8
#define CMD_RSCRATCHPAD	  0xbe
#define CMD_SKIPROM		  0xcc
#define CMD_ALARMSEARCH	  0xec
#define CMD_SEARCHROM	  0xf0

// I2C routines
void i2c_init();
void i2c_shutdown();
void i2c_waitForIdle();
void i2c_start();
void i2c_repStart();
void i2c_stop();
uns8 i2c_read( bit ack );
void i2c_write( uns8 i2cWriteData );

// MCP9802 address
#define I2C_ADR         	0b10010110
// Power pin
#define PWR_SENSOR_TRIS 	TRISC.7
#define PWR_SENSOR_IO   	LATC.7

// Sensors read routines
uns16 GetTemperature();
uns8  ReadAdcPhotoresistor();
uns8  ReadAdcPotentiometer();

// TRUE if DS18B20 is enabled, FALSE in case of MCP9802
bit isDS18B20;
// Final DS18B20 temperature value
static uns16 temperature;

#endif

#if defined( DDC_RE_01 )

// C.5 = C8 = Relay#1
#define	RELAY1_LAT	LATC.5 
#define	RELAY1_TRIS	TRISC.5

// C.2 = C2 = Relay#2
#define	RELAY2_LAT	LATC.2 
#define	RELAY2_TRIS	TRISC.2

#endif

// Must be the 1st defined function in the source code in order to be placed at the correct FLASH location!
//############################################################################################
bit CustomDpaHandler()
//############################################################################################
{
#if defined( DDC_SE_01 )
  // Finite machine states
  typedef enum
  {
	S_ResetConvertT = 0,
	S_SkipRomConvertT,
	S_CmdConvertT,

	S_WaitConvertT,

	S_ResetReadTemp,
	S_SkipRomReadTemp,
	S_CmdReadTemp,
	S_Byte1ReadTemp,
	S_Byte2ReadTemp
  } TState;

#endif

  // Handler presence mark
  clrwdt();

#if defined( DDC_SE_01 )
  // Finite machine state
  static uns8 state; // = S_ResetConvertT = 0
  // Pre-read lower temperature byte
  static uns8 temperatureByteLow;
  // Conversion timeout counter
  static uns8 timeout;
#endif

  // Detect DPA event to handle
  switch ( GetDpaEvent() )
  {
	// -------------------------------------------------
	case DpaEvent_Interrupt:
	  // Do an extra quick background interrupt work
	  // ! The time spent handling this event is critical.If there is no interrupt to handle return immediately otherwise keep the code as fast as possible.
	  // ! Make sure the event is the 1st case in the main switch statement at the handler routine.This ensures that the event is handled as the 1st one.
	  // ! It is desirable that this event is handled with immediate return even if it is not used by the custom handler because the Interrupt event is raised on every MCU interrupt and the “empty” return handler ensures the shortest possible interrupt routine response time.
	  // ! Only global variables or local ones marked by static keyword can be used to allow reentrancy.
	  // ! Make sure race condition does not occur when accessing those variables at other places.
	  // ! Make sure( inspect.lst file generated by C compiler ) compiler does not create any hidden temporary local variable( occurs when using division, multiplication or bit shifts ) at the event handler code.The name of such variable is usually Cnumbercnt.
	  // ! Do not call any OS functions except getINFx() and setINDFx().
	  // ! Do not use any OS variables especially for writing access.
	  // ! All above rules apply also to any other function being called from the event handler code, although calling any function from Interrupt event is not recommended because of additional MCU stack usage.

#if defined( DDC_SE_01 )
#define	TICKS_LEN  10

//  If TMR6 interrupt occurred
	  if ( TMR6IF )
	  {
		// Unmask interrupt
		TMR6IF = 0;
		// Decrement count
		if ( timeout != 0 )
		  timeout--;
	  }
#endif
	  return Carry;

#if defined( DDC_SE_01 )
	  // -------------------------------------------------
	case DpaEvent_Idle:
	  // Do a quick background work when RF packet is not received

	  // Run finite state machine to read temperature from DS18B20 at background so the temperature value is immediately ready for FRC 
	  if ( !isDS18B20 )
		break;

	  // Make sure 1Wire data pin at LATX.y is low as it might be set by another PORTX.? pin manipulation
	  OneWire_IO_OUT = 0;

	  skip( state );
#pragma computedGoto 1
	  goto _S_ResetConvertT;
	  goto _S_SkipRomConvertT;
	  goto _S_CmdConvertT;
	  goto _S_WaitConvertT;
	  goto _S_ResetReadTemp;
	  goto _S_SkipRomReadTemp;
	  goto _S_CmdReadTemp;
	  goto _S_Byte1ReadTemp;
	  goto _S_Byte2ReadTemp;
#pragma computedGoto 0
	  ;
	  // --------------
_S_Byte2ReadTemp:
	  temperature.high8 = OneWireReadByte();
	  temperature.low8 = temperatureByteLow;

ResetMachine:
	  state = S_ResetConvertT;
	  goto ExitMachine;

	  // --------------
_S_ResetConvertT:
_S_ResetReadTemp:
	  if ( !OneWireReset() )
	  {
_S_Error_Reset:
		temperature = ERROR_TEMPERATURE;
		goto ResetMachine;
	  }
	  goto NextState;

	  // --------------
_S_SkipRomConvertT:
_S_SkipRomReadTemp:
	  // OneWire: Skip ROM
	  OneWireWriteByte( CMD_SKIPROM );
	  goto NextState;

	  // --------------
_S_CmdConvertT:
	  // OneWire: Convert temperature
	  OneWireWriteByte( CMD_CONVERTTEMP );
	  // Setup timeout for approx 750 ms (the longest conversion time)
	  timeout = 2 + 750 / TICKS_LEN;
	  goto NextState;

	  // --------------
_S_WaitConvertT:
	  if ( OneWireReadByte() == 0xff )
		goto NextState;

	  // Timeout?
	  if ( timeout == 0 )
		goto _S_Error_Reset;

	  goto ExitMachine;

	  // --------------
_S_CmdReadTemp:
	  // OneWire: Read scratchpad
	  OneWireWriteByte( CMD_RSCRATCHPAD );
	  goto NextState;

	  // --------------
_S_Byte1ReadTemp:
	  temperatureByteLow = OneWireReadByte();
	  goto NextState;

	  // --------------
NextState:
	  ++state;

ExitMachine:
	  break;

	  // -------------------------------------------------
	case DpaEvent_FrcValue:
	  // Called to get FRC value

	  // Which FRC command?
	  switch ( _PCMD )
	  {
		case FRC_USER_BYTE_FROM + 0:
		  // Returns temperature
		  uns16 curTemperature = GetTemperature();
		  if ( curTemperature == ERROR_TEMPERATURE )
			responseFRCvalue = 0x80;
		  else
		  {
			responseFRCvalue = curTemperature.low8;
			if ( responseFRCvalue == 0 )
			  responseFRCvalue = 127;
		  }
		  break;

		case FRC_USER_BYTE_FROM + 1:
		  // Returns photoresistor value
		  responseFRCvalue = ReadAdcPhotoresistor();
_Zero2One:
		  if ( responseFRCvalue == 0 )
			responseFRCvalue |= 1;
		  break;

		case FRC_USER_BYTE_FROM + 2:
		  // Returns potentiometer value
		  responseFRCvalue = ReadAdcPotentiometer();
		  goto _Zero2One;
	  }
	  break;

	  // -------------------------------------------------
	case DpaEvent_FrcResponseTime:
	  // Called to get FRC response time

	  if ( DataOutBeforeResponseFRC[0] >= ( FRC_USER_BYTE_FROM + 0 ) && DataOutBeforeResponseFRC[0] <= ( FRC_USER_BYTE_FROM + 2 ) )
		responseFRCvalue = _FRC_RESPONSE_TIME_40_MS;
	  break;
#endif

	  // -------------------------------------------------
	case DpaEvent_DpaRequest:
	{
	  // Called to interpret DPA request for peripherals
	  // -------------------------------------------------
	  // Peripheral enumeration
	  if ( IsDpaEnumPeripheralsRequest() )
	  {
		// We implement 1 user peripheral
		_DpaMessage.EnumPeripheralsAnswer.UserPerNr = 1;
#ifdef FlagUserPer	// Get ready for upcoming DPA 3.00
		FlagUserPer( _DpaMessage.EnumPeripheralsAnswer.UserPer, PNUM_USER + 0 );
#endif
		_DpaMessage.EnumPeripheralsAnswer.HWPID = ThisHWPID;
		_DpaMessage.EnumPeripheralsAnswer.HWPIDver = 0x0000;

DpaHandleReturnTRUE:
		return TRUE;
	  }
	  // -------------------------------------------------
	  // Get information about peripheral
	  else if ( IsDpaPeripheralInfoRequest() )
	  {
		if ( _PNUM == PNUM_USER + 0 )
		{
		  _DpaMessage.PeripheralInfoAnswer.PerT = PERIPHERAL_TYPE_USER_AREA;
#if !defined( DDC_RE_01 )
		  _DpaMessage.PeripheralInfoAnswer.PerTE = PERIPHERAL_TYPE_EXTENDED_READ;
#else
		  _DpaMessage.PeripheralInfoAnswer.PerTE = PERIPHERAL_TYPE_EXTENDED_READ_WRITE;
#endif
		  goto DpaHandleReturnTRUE;
		}

		break;
	  }
	  // -------------------------------------------------
	  else
	  {
		// Handle peripheral command
		if ( _PNUM == PNUM_USER + 0 )
		{
		  switch ( _PCMD )
		  {
#if defined( DDC_SE_01 )
			case 0x31:
			  // Read sensors
			  if ( _DpaDataLength != 0 )
				DpaApiReturnPeripheralError( ERROR_DATA_LEN );

			  // Read temperature and check for an error
			  uns16 temperature = GetTemperature();
			  if ( temperature == ERROR_TEMPERATURE )
				DpaApiReturnPeripheralError( ERROR_FAIL );
			  _DpaMessage.Response.PData[0] = temperature.low8;

			  // Read other sensors
			  _DpaMessage.Response.PData[1] = ReadAdcPhotoresistor();
			  _DpaMessage.Response.PData[2] = ReadAdcPotentiometer();

			  // Return 3 bytes
			  _DpaDataLength = 3;
			  goto DpaHandleReturnTRUE;
#endif

#if defined( DDC_RE_01 )
			case 0x32:
			  // Control and return state of relays
			  if ( _DpaDataLength != 2 )
				DpaApiReturnPeripheralError( ERROR_DATA_LEN );

			  // Relay #1
			  // Get
			  userReg0 = 0;
			  if ( RELAY1_LAT )
				userReg0.0 = 1;

			  // Set
			  switch ( _DpaMessage.Request.PData[0] )
			  {
				case 0:
				  RELAY1_LAT = 0;
				  break;
				case 1:
				  RELAY1_LAT = 1;
				  break;
			  }
			  _DpaMessage.Response.PData[0] = userReg0;

			  // Relay #2
			  // Get
			  userReg0 = 0;
			  if ( RELAY2_LAT )
				userReg0.0 = 1;

			  // Set
			  switch ( _DpaMessage.Request.PData[1] )
			  {
				case 0:
				  RELAY2_LAT = 0;
				  break;
				case 1:
				  RELAY2_LAT = 1;
				  break;
			  }
			  _DpaMessage.Response.PData[1] = userReg0;
			  // Receives and returns 2 bytes
			  goto DpaHandleReturnTRUE;
#endif

			  // Invalid command
			default:
			  DpaApiReturnPeripheralError( ERROR_PCMD );
			  break;
		}
	  }
	}

	  break;
  }

	// -------------------------------------------------
	case DpaEvent_Init:
	  // Do a one time initialization work before main loop starts

#if defined( DDC_SE_01 )
	  // Initialize sensors

	  // C5 (AN4) as input 
	  moduleInfo();
	  if ( !bufferINFO[5].7 )
	  {
		TRISC.6 = 1;
		TRISB.4 = 1;
	  }
	  TRISA.5 = 1;

	  // C1 (AN0) as input 
	  TRISA.0 = 1;

	  // Setup TMR6 to generate ticks on the background (ticks every 10ms)
#if F_OSC == 16000000
	  PR6 = 250 - 1;
	  T6CON = 0b0.1001.1.10;	// Prescaler 16, Postscaler 10, 16 * 10 * 250 = 40000 = 4MHz * 10ms
#else
#error Unsupported oscillator frequency
#endif

	  // Setup DS18B20 for 9bit precision, conversion takes 94ms (see datasheet)
	  if ( Ds18B20WriteConfig( 0b0.00.00000 ) )
		// DS18B20 is enabled
		isDS18B20 = TRUE;
	  else
		// Expect MCP9802 is enabled
		i2c_init();
#endif

#if defined( DDC_RE_01 )
	  // Initialize relays
	  RELAY1_LAT = 0;
	  RELAY2_LAT = 0;
	  RELAY1_TRIS = 0;
	  RELAY2_TRIS = 0;

#endif
	  break;

#if defined( DDC_SE_01 )
	  // -------------------------------------------------
	case DpaEvent_AfterSleep:
	  // Called after woken up after sleep
	  if ( !isDS18B20 )
		i2c_init();
	  break;

	  // -------------------------------------------------
	case DpaEvent_BeforeSleep:
	  // Called before going to sleep
	  if ( !isDS18B20 )
		i2c_shutdown();
	  break;
#endif

}
  return FALSE;
}

//############################################################################################
#if defined( DDC_SE_01 )

//############################################################################################
// OneWire and Dallas 18B20 routines
//############################################################################################

//############################################################################################
void Delay5us( uns8 val @ W ) // Absolutely precise timing but val != 0
//############################################################################################
{
  // 16 MHz
  // + 0.75us ( W=val, Call )
  for ( ;; )
  {         // loop time
	nop2();	// 0.50us
	nop2();	// 1.00us
	nop2();	// 1.50us
	nop2();	// 2.00us
	nop2();	// 2.50us
	nop2();	// 3.00us
	nop();	// 3.25us
	if ( --val == 0 ) // + 0.75us (W--, BTFS ) 
	  return;         // + 0.25us 
	nop2();	// 4.50us
  }         // 5.00us (Goto)
}
//############################################################################################

#define	OneWireData0()	{ OneWire_TRIS = 0; }	  // 1us [0.5us @ 16MHz]
#define OneWireData1()  { OneWire_TRIS = 1; }	  // 1us [0.5us @ 16MHz]

//############################################################################################
void OneWireWriteByte( uns8 byte )
//############################################################################################
{
  uns8 bitLoop = 8;
  do
  {
	// Next sequence is time precision critical
	GIE = 0;

	OneWireData0();
	nop2();	        // 1 us [0.5 us]
	nop2();	        // [1.0 us]
	if ( byte.0 )	// 2.5 us [1.75us]
	  OneWireData1();

	// End of time precision critical sequence
	GIE = 1;

	// 60us minimum in total, does not have to be precise
	Delay5us( ( 60 - 3 ) / 5 + 1 );

	OneWireData1();

	byte >>= 1;
  } while ( --bitLoop != 0 );
}

//############################################################################################
uns8 OneWireReadByte()
//############################################################################################
{
  uns8 result;
  uns8 bitLoop = 8;
  do
  {
	// Next sequence is time precision critical
	GIE = 0;

	OneWireData0();
	nop2();	        // 1 us [0.5 us]
#if F_OSC == 16000000
	nop2();	        // [1.0 us]
#endif
	OneWireData1();			// 2 us [1.5 us]
	Delay5us( 15 / 5 );		// 17 us [16.5 us]

	Carry = 0;				// 17.5 us [16.75 us]
	if ( OneWire_IO_IN )	// 18.5 us [ 17.25 us] (condition must not modify Carry)
	  Carry = 1;

	// End of time precision critical sequence
	GIE = 1;				// must not modify Carry
	result = rr( result );

	// 60us minimum in total, does not have to be precise
	Delay5us( ( 60 - 20 ) / 5 + 1 );
  } while ( --bitLoop != 0 );

  return result;
}

//############################################################################################
bit OneWireReset()
//############################################################################################
{
  // Setting the pin once to low is enough
  OneWire_IO_OUT = 0;
  // Reset pulse
  OneWireData0();
  Delay5us( 500 / 5 );
  // Reset pulse end
  OneWireData1();
  // Next sequence is time precision critical
  GIE = 0;
  // Wait for presence pulse
  Delay5us( 70 / 5 );
  // End of time precision critical sequence
  GIE = 1;
  // Presence pulse?
  if ( OneWire_IO_IN )
  {
	// No presence, finish initialization sequence
	Delay5us( ( 500 - 70 ) / 5 );
	return FALSE;
  }
  else
  {
	// Presence OK, finish initialization sequence
	Delay5us( ( 500 - 70 ) / 5 );
	return TRUE;
  }
}

//############################################################################################
void OneWireCmd( uns8 cmd )
//############################################################################################
{
  // OneWire: Skip ROM
  OneWireWriteByte( CMD_SKIPROM );
  // OneWire: Send command
  OneWireWriteByte( cmd );
}

//############################################################################################
bit Ds18B20WriteConfig( uns8 value )
//############################################################################################
{
  if ( OneWireReset() )
  {
	// Write Scratchpad
	OneWireCmd( CMD_WSCRATCHPAD );

	// Write TL = ? (we dot not care the value)
	OneWireWriteByte( W );
	// Write TH = ? (we dot not care the value)
	OneWireWriteByte( W );
	// Write Config byte
	OneWireWriteByte( value );

	if ( OneWireReset() )
	{
	  //  Copy Scratchpad
	  OneWireCmd( CMD_CPYSCRATCHPAD );
	  return TRUE;
	}
  }
  return FALSE;
}

//############################################################################################
void writeToSSPCON2( uns8 value @ param4.high8 )
//############################################################################################
{
  writeToRAM( &SSPCON2, value );
}

//############################################################################################
void writeOredToSSPCON2( uns8 value @ param4.high8 )
//############################################################################################
{
  writeToSSPCON2( SSPCON2 | value );
}

//############################################################################################

bit i2cTimeout;

//############################################################################################
void i2c_init()
//############################################################################################
{
  // SCL as input (SIM C6)
  TRISC.3 = 1;
  // SDA as input (SIM C7)
  TRISC.4 = 1;

  // I2C master mode     SSPCON = 0b00111000
  writeToRAM( &SSPCON1, 0x38 );
  writeToSSPCON2( 0x00 );

  // 50 kHz SCL frequency
  SSPADD = ( F_OSC / 50000 / 4 ) - 2;
  // Disable slew rate control
  SMP = 1;
}

//############################################################################################
void i2c_shutdown()
//############################################################################################
{
  // I2C master mode     SSPCON = 0
  writeToRAM( &SSPCON1, 0x00 );
}

//############################################################################################
void i2c_waitForIdle()
//############################################################################################
{
  i2cTimeout = FALSE;
  uns8 timeout;
  // Wait for idle and not writing
  timeout = 0;
  while ( ( SSPCON2 & 0b0001.1111 ) != 0 || RW_ )
	if ( ++timeout == 0 )
	{
	  i2cTimeout = TRUE;
	  break;
	}
}

//############################################################################################
void i2c_start()
//############################################################################################
{
  i2c_waitForIdle();
  // SEN = 1
  writeOredToSSPCON2( 0x01 );		
}

//############################################################################################
void i2c_repStart()
//############################################################################################
{
  i2c_waitForIdle();
  // RSEN = 1
  writeOredToSSPCON2( 0x02 );		
}

//############################################################################################
void i2c_stop()
//############################################################################################
{
  i2c_waitForIdle();
  // PEN = 1
  writeOredToSSPCON2( 0x04 );		
}

//############################################################################################
uns8 i2c_read( bit ack )
//############################################################################################
{
  i2c_waitForIdle();
  // RCEN = 1
  writeOredToSSPCON2( 0x08 );		

  i2c_waitForIdle();

  uns8 i2cReadData @ userReg0;
  i2cReadData = SSPBUF;

  i2c_waitForIdle();

  if ( ack )
	// Acknowledge, ACKDT = 0
	writeToSSPCON2( SSPCON2 & 0xDF ); 
  else
	// Not acknowledge, ACKDT = 1 
	writeOredToSSPCON2( 0x20 );		  

  // Send acknowledge sequence, ACKEN = 1 
  writeOredToSSPCON2( 0x10 );		  
  return i2cReadData;
}

//############################################################################################
void i2c_write( uns8 i2cWriteData @ param2 )
//############################################################################################
{
  i2c_waitForIdle();
  SSPBUF = i2cWriteData;
}

//############################################################################################
uns16 MCP9802GetTemp()
//############################################################################################
{
  i2c_start();
  if ( i2cTimeout )
	return ERROR_TEMPERATURE;

  // MCP9802 address
  i2c_write( I2C_ADR );
  // pointer: 1 = configuration register
  i2c_write( 0x01 );
  // configuration: 9-bit ADC
  i2c_write( 0x00 );
  i2c_stop();

  i2c_start();
  // MCP9802 address
  i2c_write( I2C_ADR );
  // pointer: 0 = temperature
  i2c_write( 0 );
  i2c_stop();

  i2c_start();
  // MCP9802 address + read
  i2c_write( I2C_ADR | 1 );
  uns16 temperature;
  // store the result
  temperature.high8 = i2c_read( TRUE );
  temperature.low8 = i2c_read( FALSE );
  i2c_stop();
  return temperature;
}

//############################################################################################
uns16 GetTemperature()
//############################################################################################
{
  // Reads temperature from an enabled sensor
  uns16 temperatureResult;

  if ( isDS18B20 )
  {
	// Temperature is ready at the background
	temperatureResult = temperature;
	if ( temperatureResult != ERROR_TEMPERATURE )
	{
	  temperatureResult += 0x08;
	  temperatureResult /= 0x10;
	}
  }
  else
  {
	// Temperature value must be read from I2C sensor
	temperatureResult = MCP9802GetTemp();
	if ( temperatureResult != ERROR_TEMPERATURE )
	{
	  temperatureResult += 0x80;
	  temperatureResult /= 0x100;
	}
  }

  return temperatureResult;
}

//############################################################################################
uns8 ReadAdc()
//############################################################################################
{
  // ADC result - left justified, Fosc/8
  ADCON1 = 0b0001.0000;
  // start ADC
  GO = 1;
  // wait for ADC finish
  while ( GO );
  return ADRESH;
}

//############################################################################################
uns8  ReadAdcPhotoresistor()
//############################################################################################
{
  // ADC initialization (for more info see PIC datasheet) pin C1 (AN0) as analog input 
  ANSELA.0 = 1;
  // ADC setting (AN0 channel)
  ADCON0 = 0b0.00000.01;
  return ReadAdc();
}

//############################################################################################
uns8  ReadAdcPotentiometer()
//############################################################################################
{
  // ADC initialization (for more info see PIC datasheet) pin C5 (AN4) as analog input 
  ANSELA.5 = 1;
  // ADC setting (AN4 channel)
  ADCON0 = 0b0.00100.01;
  return ReadAdc();
}
//############################################################################################
#endif
//############################################################################################
// Default Custom DPA Handler header; 2nd include to implement Code bumper to detect too long code of the Custom DPA Handler (modify the path according to your setup) 
#include "DPAcustomHandler.h"
//############################################################################################
