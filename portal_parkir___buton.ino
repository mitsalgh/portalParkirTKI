#define pinRelayOpen 2
#define pinRelayClose 3
#define pinRelayStop 4
#define pinButtonOpen 5
#define LEDOpen 6
#define LEDClose 8
#define LEDReady 7

String dataSTB="";

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
  delay(5000);
  digitalWrite(pinRelayClose, HIGH);
  digitalWrite(LEDClose, HIGH);
  digitalWrite(LEDReady,LOW);
  delay(1000);
  digitalWrite(pinRelayClose, LOW);
  digitalWrite(LEDClose, LOW);
  digitalWrite(LEDReady, HIGH);
  delay(3500);
  Serial.println("Closed");
}

void loop() 
{
  digitalWrite(LEDReady,HIGH);
  if(Serial.available()>0) //check Perintah dari STB
  {
    delay(10);
    dataSTB= Serial.readString();
    if(dataSTB== "o" || dataSTB== "O" || dataSTB== "o\n" || dataSTB== "O\n" )
    {
      digitalWrite(LEDReady,LOW);
      digitalWrite(LEDOpen,HIGH);
      digitalWrite(pinRelayOpen, HIGH);
      delay(200);
      digitalWrite(pinRelayOpen, LOW);
      Serial.println("opened");
      digitalWrite(LEDOpen,LOW);
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
  else if(digitalRead(pinButtonOpen) == LOW)
  {
    Serial.println("v");
    prosesOpen();
  }
}
