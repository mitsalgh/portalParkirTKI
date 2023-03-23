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
String statusPortal="";

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

void loop() 
{
  digitalWrite(LEDReady,HIGH);
  if(digitalRead(pinButtonHelp)== LOW)
  {
    Serial.println("help");
    delay(200);
  }
  if(digitalRead(pinButtonOpen) == LOW)
  {
    if(statusPortal=="closed")
    {
      Serial.println("v");
      prosesOpen();
    }
  }
  if(digitalRead(loopDetector)==LOW)
  {
    if(flagVehicleIn==0)
    {
      Serial.println("vehicle");
      flagVehicleIn++;
    }
    else if(flagVehicleIn>0)
    {
      Serial.println("closed");
      statusPortal="closed";
      flagVehicleIn=0;
    }
    delay(200);
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
}
