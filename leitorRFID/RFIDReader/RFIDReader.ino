#define PRESET_VALUE 0xFFFF
#define POLYNOMIAL  0x8408


int i = 0;

extern const unsigned char getReaderInfo[];
extern const unsigned char inventory[];
extern const unsigned char buzzer[];

void setup()  
{
  
  // Open serial communications and wait for port to open:
  Serial.begin(57600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo only
  }


  Serial.println("InicioSerial0 ");

  Serial1.begin(57600);
  while (!Serial1) {
    ; // wait for serial port to connect. Needed for Leonardo only
  }


  Serial.println("Pedindo informacoes do leitor...");
    Serial1.write(getReaderInfo, 3);
    enviarChecksum(getReaderInfo, 3, &Serial1);
    print_serial();
  
  /* Serial.println("Desligando o buzzer do leitor..."); //Não funciona =/, só serve pra se quiser apitar o buzzer interno (alterando os parametros).
   Serial1.write(buzzer, 6);
    enviarChecksum(buzzer, 6, &Serial1);
    print_serial();  */
  
}

void loop(){
    Serial.println("Pedindo inventorio do leitor...");
    Serial1.write(inventory, 3);
    enviarChecksum(inventory, 3, &Serial1);

    print_serial();  

  delay (200);  
  
 
}


