//   ========================================================================
//   =================    Win-I2CUSB  DLL interface      ====================
//   ===========            http://www.demoboard.com              ===========
//   ===========     Copyright (c) 2004-2011 SB Solutions         ===========
//   ========================================================================


extern "C" short int     __stdcall Enable3VOutputPower(short int);
extern "C" short int     __stdcall Enable5VOutputPower(short int);
extern "C" unsigned char __stdcall GetFirmwareRevision(void);
extern "C" unsigned char __stdcall GetHardwareInfo(unsigned char *HardwareData);
extern "C" int           __stdcall GetNumberOfDevices(void);
extern "C" int           __stdcall GetSerialNumbers(int *SerialNumbers);
extern "C" int           __stdcall SelectBySerialNumber(int dwSerialNumber);
extern "C" void          __stdcall ShutdownProcedure(void);
extern "C" int           __stdcall Read_IO(void);
extern "C" int           __stdcall Write_IO(int OutputState);
extern "C" int           __stdcall Disable_SPI(void);
extern "C" int           __stdcall Enable_SPI(void);
extern "C" unsigned char __stdcall Configure_SPI_GPIO(unsigned char DIR);  // requires hardware/firmware version 3.1 or later
extern "C" int           __stdcall GPIO_SPI_Write(unsigned char GPIOData);
extern "C" int           __stdcall GPIO_SPI_Read(void);
extern "C" int           __stdcall Enable_I2C(void);
extern "C" int           __stdcall Disable_I2C(void);
extern "C" int           __stdcall GPIO_I2C_Write(unsigned char GPIOData);
extern "C" int           __stdcall GPIO_I2C_Read(void);
extern "C" int           __stdcall Get_DLL_Version(void);

extern "C" int           __stdcall GetI2CFrequency(void);
extern "C" int           __stdcall GetI2CIgnoreAck(void);               // requires firmware version 1.9 or later
extern "C" int           __stdcall I2CIgnoreAck (int IgnoreAckFlag);    // requires firmware version 1.9 or later
extern "C" unsigned char __stdcall I2CRead(unsigned char address, short int nBytes, unsigned char *ReadData, short int SendStop);
extern "C" unsigned char __stdcall I2C10ReadArray(short int address, unsigned char subaddress, short int nBytes, unsigned char *ReadData);
extern "C" unsigned char __stdcall I2C10WriteArray(short int address, unsigned char subaddress, short int nBytes, unsigned char *ReadData);
extern "C" unsigned char __stdcall I2CReadArray(unsigned char address, unsigned char subaddress, short int nBytes, unsigned char *ReadData);
extern "C" unsigned char __stdcall I2CReadByte(unsigned char address, unsigned char subaddress, unsigned char *ReadData);
extern "C" unsigned char __stdcall I2CReceiveByte(unsigned char address, unsigned char *ReadData);
extern "C" unsigned char __stdcall I2CSendByte(unsigned char address, unsigned char SendData);
extern "C" unsigned char __stdcall I2CWrite(unsigned char address, short int nBytes, unsigned char *WriteData, short int SendStop);
extern "C" unsigned char __stdcall I2CWriteArray(unsigned char address, unsigned char subaddress, short int nBytes, unsigned char *WriteData);
extern "C" unsigned char __stdcall I2CWriteByte(unsigned char address,unsigned char subaddress,unsigned char dataByte);
extern "C" unsigned char __stdcall I2CWriteRepWrite(unsigned char address0,short int nBytes0,unsigned char *WriteData0,unsigned char address1,short int nBytes1,unsigned char *WriteData1);
extern "C" int           __stdcall SetI2CFrequency(int frequency);
extern "C" unsigned char __stdcall I2CReadArrayDB(unsigned char address, unsigned char saHigh, unsigned char saLow, short int nBytes, unsigned char *ReadData);
extern "C" unsigned char __stdcall I2CWriteArrayDB(unsigned char address, unsigned char saHigh, unsigned char saLow, short int nBytes, unsigned char *WriteData); 

extern "C" unsigned char __stdcall SPI_Configure(unsigned char SPI_Mode);
extern "C" unsigned char __stdcall SPI_Generic(short int nBytes,unsigned char *WriteData, unsigned char *ReadData);
extern "C" int           __stdcall SPI_SetFrequency(int frequency);
extern "C" unsigned char __stdcall SPI_Write(short int nBytes,unsigned char *SPI_Data);
extern "C" unsigned char __stdcall SPI_WriteRead(short int nBytesWrite,short int nBytesRead,unsigned char *WriteData,unsigned char *ReadData);
extern "C" unsigned char __stdcall SPI_WriteWithOC(short int nBytes,unsigned char *WriteData);
