//declarations
#include <Wire.h>
const char ADXL345DEVICE =(0x53); // Device address as specified in data sheet

byte _buff[8];
char POWER_CTL_ACCEL = 0x2D;	//Power Control Register
char DATA_FORMAT = 0x31;
char DATAX0 = 0x32;	//X-Axis Data 0
char DATAX1 = 0x33;	//X-Axis Data 1
char DATAY0 = 0x34;	//Y-Axis Data 0
char DATAY1 = 0x35;	//Y-Axis Data 1
char DATAZ0 = 0x36;	//Z-Axis Data 0
char DATAZ1 = 0x37;	//Z-Axis Data 1
int x ;
int y ;
int z ;


//adxl345:ox1D
//0x32-0x37 is x0,x1,y0,y1,z0,z1
//0x2D power_ctl
//00101000 to enable it

//hmc compass:ox1e
//03-09 is x_msb,x_lsb, z_msb, z_lsb, y_msb, y_lsb
//set register_A address 00 to 01111000
//set register_B address 01 to default



//functions=======================================================
void initialize_i2c();
void readFrom(byte deviceAddress, byte registerAddress, int numOfBytes, byte *buffer);//device address, register to readfrom, bytes to read, pointer to a byte array of length numOfBytes
void writeTo(byte deviceAddress, byte registerAddress, byte byteToWrite);
void updateAccel(int * dataAccel);// int * dataAccel is a 3 element array
void updateCompass();
void updateGyro();
//================================================================







void initialize_12c(){
Wire.begin();

//Put the ADXL345 into +/- 4G range by writing the value 0x01 to the DATA_FORMAT register.
  //writeTo(DATA_FORMAT, 0x01);
  //initialize each device with its setting
  writeTo(ADXL345DEVICE,POWER_CTL_ACCEL, 0);
  writeTo(ADXL345DEVICE,POWER_CTL_ACCEL, 0x16);
  //Put the ADXL345 into Measurement Mode by writing 0x08 to the POWER_CTL register.
  writeTo(ADXL345DEVICE,POWER_CTL_ACCEL, 0x08);

  
  //compass
  //writeTo(compass,0,B01111000);
  
  
  //


}

/*
void updateCompass(){
//hmc compass:ox1e
//03-09 is x_msb,x_lsb, z_msb, z_lsb, y_msb, y_lsb
//set register_A address 00 to 01111000
//set register_B address 01 to default
char HMCDEVICE=0x1E;
readFrom(compass,0x03,1,_buff);
readFrom(compass,0x04,1,_buff+1);
readFrom(compass,0x05,1,_buff+2);
readFrom(compass,0x06,1,_buff+3);
readFrom(compass,0x07,1,_buff+4);
readFrom(compass,0x08,1,_buff+5);
//readFrom(compass,0x09,1,_buff+6);




}*/

void updateAccel(int* dataAccel) {//update the accelerometer values
  //make an array to hold data
  byte buffer[6];
  readFrom( ADXL345DEVICE, DATAX0, 6, buffer); //read the acceleration data from the ADXL345

  // each axis reading comes in 10 bit resolution, ie 2 bytes.  Least Significat Byte first!!
  // thus we are converting both bytes in to one int and adding 1s if it is in 2s compliment
  
  int _x = (((int)buffer[1]) << 8) | buffer[0];
  int _y = (((int)buffer[3]) << 8) | buffer[2];
  int _z = (((int)buffer[5]) << 8) | buffer[4];
 
	if(bitRead(_x,15))//if two byte negative
		dataAccel[0]=0xffff0000| _x;//make 4 byte negative
		else
		dataAccel[0]=_x;//else leave alone
	if(bitRead(_y,15))
		dataAccel[1]=0xffff0000|_y;
		else
		dataAccel[1]=_y;
	if(bitRead(temp_z,15))
		dataAccel[2]=0xffff0000|_z;
		else
		dataAccel[2]=_z;
}
void writeTo(byte deviceAddress, byte registerAddress, byte byteToWrite){
  Wire.beginTransmission(deviceAddress); // start transmission to device
  Wire.write(registerAddress);             // send register address
  Wire.write(byteToWrite);                 // send value to write
  Wire.endTransmission();         // end transmission
}

void readFrom(byte deviceAddress, byte registerAddress, int numOfBytes, byte *buffer){
  Wire.beginTransmission(deviceAddress); // start transmission to device
  Wire.write(registerAddress);             // sends address to read from
  Wire.endTransmission();         // end transmission

  Wire.beginTransmission(deviceAddress); // start transmission to device
  Wire.requestFrom(deviceAddress, numOfBytes);    // request bytes from device

  int i = 0;
  while(Wire.available())         // device may send less than requested (abnormal)
  {
    buffer[i] = Wire.read();    // receive a byte
    i++;
  }
  Wire.endTransmission();         // end transmission
}






