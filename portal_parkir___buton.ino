#define pinRelayOpen 2
#define pinRelayClose 3
#define pinRelayStop 10
#define pinButtonOpen 5
#define pinButtonHelp A2
#define sensorLoopDetectorOpen A1
#define sensorLoopDetectorClosed A0
#define LEDOpen 6
#define LEDClose 8
#define LEDReady 7
#define loopDetector A3

int flagVehicleIn=0;
String dataSTB="";
String statusPortal="closed";
String mode="";

unsigned long lastDebounceTime = 0; //variabel untuk debounce
unsigned long debounceDelay = 50; //waktu debounce dalam milidetik
unsigned long prevMillis = 0; //variabel untuk menyimpan waktu sebelumnya
unsigned long interval = 500; //interval waktu untuk membaca keypad dalam m



void setup() 
{
  Serial.begin(9600);
  pinMode(pinRelayOpen, OUTPUT);
  pinMode(pinRelayClose, OUTPUT);
  pinMode(pinRelayStop, OUTPUT);
  pinMode(LEDOpen, OUTPUT);
  pinMode(LEDClose, OUTPUT);
  pinMode(LEDReady, OUTPUT);
  pinMode(pinButtonOpen, INPUT_PULLUP);
  pinMode(pinButtonHelp, INPUT_PULLUP); 
  pinMode(loopDetector, INPUT_PULLUP);  
  mode="in";
}

void prosesOpen()
{
  digitalWrite(pinRelayOpen, HIGH);
  digitalWrite(LEDReady, LOW);
  digitalWrite(LEDOpen, HIGH);
  delay(1000);
  digitalWrite(pinRelayOpen, LOW);
  digitalWrite(LEDOpen, LOW);
  Serial.println("opened");
  statusPortal="open";
  delay(2000);
}
void prosesClosed()
{
  while(digitalRead(sensorLoopDetectorClosed)==HIGH)
  {
    if(digitalRead(sensorLoopDetectorClosed)==LOW)
    {
      Serial.println("closed");
      break;
    }
  }
}

void resetAll()
{
  mode="in";
  statusPortal="ready";
}

void loop() 
{
  if(mode=="in")
  {
    digitalWrite(LEDReady,HIGH);
    unsigned long currentMillis = millis(); //mendapatkan waktu saat ini
    if (currentMillis - prevMillis >= interval) 
    { //jika interval waktu sudah terlewati
      prevMillis = currentMillis; //memperbarui waktu sebelumnya
      if(digitalRead(pinButtonHelp)== LOW)
      {
        Serial.println("help");
        delay(200);
      }
      if(digitalRead(pinButtonOpen) == LOW)
      {
          Serial.println("v");
//      prosesOpen();
      }
      if(digitalRead(loopDetector)==LOW)
      {
        if(flagVehicleIn==0)
        {
          Serial.println("vehicle");
        }
      }
    }
    if(Serial.available()>0) //check Perintah dari STB
    {
      delay(10);
      dataSTB= Serial.readString();
      if(dataSTB== "o" || dataSTB== "O" || dataSTB== "o\n" || dataSTB== "O\n" )
      {
        prosesOpen();
      }
      else if (dataSTB== "c" || dataSTB== "C" || dataSTB== "c\n" || dataSTB== "C\n" )
      {
        digitalWrite(LEDReady,LOW);
        digitalWrite(LEDClose,HIGH);
        digitalWrite(pinRelayClose, HIGH);
        digitalWrite(LEDReady,LOW);
        delay(150);
        digitalWrite(pinRelayClose, LOW);
        digitalWrite(LEDClose, LOW);
        Serial.println("closed");
      }
      else if (dataSTB== "s" || dataSTB== "S" || dataSTB== "s\n" || dataSTB== "S\n" )
      {
        digitalWrite(pinRelayStop, HIGH);  
        delay(1000);
        digitalWrite(pinRelayStop, LOW);
        Serial.println("stoped");
      }
    }
   if(statusPortal=="open")
   {
    mode="close";
   }
  }
  else if(mode="close")
  {
    while(statusPortal=="open")
    {
      unsigned long currentMillis = millis(); //mendapatkan waktu saat ini
      if (currentMillis - prevMillis >= interval) 
      { //jika interval waktu sudah terlewati
        prevMillis = currentMillis; //memperbarui waktu sebelumnya
        if(digitalRead(loopDetector)== LOW)
        {
          Serial.println("closed 1");
          delay(200);
          statusPortal="closed";
          resetAll();
        }
      }
    }
  }
}
