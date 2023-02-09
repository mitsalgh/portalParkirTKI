#define pinRelayOpen D2
#define pinRelayClose D3
#define pinRelayStop D4
#define pinButtonOpen D5

String dataSTB="";

void setup() 
{
  Serial.begin(9600);
  pinMode(pinRelayOpen, OUTPUT);
  pinMode(pinRelayClose, OUTPUT);
  pinMode(pinRelayStop, OUTPUT);
  pinMode(pinButtonOpen, INPUT); 
}

void loop() 
{
  if(Serial.available()>0) //check Perintah dari STB
  {
    delay(10);
    dataSTB= Serial.readString();
    if(dataSTB== "b" || dataSTB== "B" || dataSTB== "b\n" || dataSTB== "B\n" )
    {
      digitalWrite(pinRelayOpen, HIGH);
      delay(1000);
    }
    else if (dataSTB== "c" || dataSTB== "C" || dataSTB== "c\n" || dataSTB== "C\n" )
    {
      digitalWrite(pinRelayClose, HIGH);
      delay(1000);
    }
    else if (dataSTB== "s" || dataSTB== "S" || dataSTB== "s\n" || dataSTB== "S\n" )
    {
      digitalWrite(pinRelayClose, HIGH);
      delay(1000);
    }
    digitalWrite(pinRelayClose, LOW);
    delay(1000);
  }
  else if(digitalRead(pinButtonOpen == LOW))
  {
    Serial.println("visitor");
  }

}
