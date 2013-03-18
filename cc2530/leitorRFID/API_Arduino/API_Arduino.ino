#include <SoftwareSerial.h>

#define PRESET_VALUE 0xFFFF
#define POLYNOMIAL  0x8408

SoftwareSerial mySerial(10, 11); // RX, TX

int i = 0;

const unsigned char getReaderInfo[] = {0x04, 0x00, 0x21};
const unsigned char inventory[] = {0x04, 0x00, 0x01};
const unsigned char buzzer[] = {0x07, 0x00, 0x33, 0, 0, 0};

unsigned int uiCrc16Cal(unsigned char const  * pucY, unsigned char ucX)
{
	unsigned char ucI,ucJ;
	unsigned short int  uiCrcValue = PRESET_VALUE;

   	for(ucI = 0; ucI < ucX; ucI++)
	   {
		   uiCrcValue = uiCrcValue ^ *(pucY + ucI);
	  	   for(ucJ = 0; ucJ < 8; ucJ++)
	   	  {
		 	if(uiCrcValue & 0x0001)
		   	{
		    	uiCrcValue = (uiCrcValue >> 1) ^ POLYNOMIAL;
		   	}
		 	else
		   	{
		    	uiCrcValue = (uiCrcValue >> 1);
		   	}
		}
 	}
return uiCrcValue;
}

void enviarChecksum(unsigned char const  * buffer, unsigned char len, SoftwareSerial *porta){
  unsigned int crc = uiCrc16Cal(buffer, len);
  unsigned char CRC_MSB = 0;
  unsigned char CRC_LSB = 0;
 
  CRC_MSB = (crc & 0x0000FF00) >> 8;
  CRC_LSB = crc & 0x000000FF;
  
  (*porta).write(CRC_LSB);
  (*porta).write(CRC_MSB);
}

void print_serial()
{
  while(!mySerial.available());
  while(mySerial.available()){
    if (mySerial.available()){
      Serial.print(i++);
      Serial.print(" - Serial2: ");
      Serial.print(mySerial.read(), HEX);
      Serial.println("");
    }
  }
}

void setup()  
{
  
  // Open serial communications and wait for port to open:
  Serial.begin(57600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo only
  }


  Serial.println("Sniffando: ");

  // set the data rate for the SoftwareSerial port
  mySerial1.begin(57600);
  mySerial.begin(57600);
  
   

  
  Serial.println("Pedindo informacoes do leitor...");
    mySerial.write(getReaderInfo, 3);
    enviarChecksum(getReaderInfo, 3, &mySerial);
    print_serial();
  
   Serial.println("Desligando o buzzer do leitor..."); //Não funciona =/, só serve pra se quiser apitar o buzzer interno (alterando os parametros).
   mySerial.write(buzzer, 6);
    enviarChecksum(buzzer, 6, &mySerial);
    print_serial();
  
}

void loop(){
    Serial.println("Pedindo inventorio do leitor...");
    mySerial.write(inventory, 3);
    enviarChecksum(inventory, 3, &mySerial);

    print_serial();
  delay(200);
}

