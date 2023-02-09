#define pinRelayOpen 2
#define pinRelayClose 3
#define pinRelayStop 4
#define pinButtonOpen 5

String dataSTB="";

void setup() 
{
  Serial.begin(9600);
  pinMode(pinRelayOpen, OUTPUT);
  pinMode(pinRelayClose, OUTPUT);
  pinMode(pinRelayStop, OUTPUT);
  pinMode(pinButtonOpen, INPUT); 
}

void prosesOpen()
{
//  if(Serial.available()>0)
//  {
//    delay(10);
//    dataSTB= Serial.readString();
//    Serial.println(
//    if(dataSTB== "b" || dataSTB== "B" || dataSTB== "b\n" || dataSTB== "B\n" )
//    {
      digitalWrite(pinRelayOpen, HIGH);
      delay(1000);
      digitalWrite(pinRelayOpen, LOW);
      Serial.println("opened");
      delay(3500);
      digitalWrite(pinRelayClose, HIGH);
      delay(1000);
      digitalWrite(pinRelayClose, LOW);
      delay(3500);
      Serial.println("Closed");
//    }
//  }
}

void loop() 
{
  while(1)
  {
    prosesOpen();
  }
  if(Serial.available()>0) //check Perintah dari STB
  {
    delay(10);
    dataSTB= Serial.readString();
    if(dataSTB== "b" || dataSTB== "B" || dataSTB== "b\n" || dataSTB== "B\n" )
    {
      prosesOpen();
//      digitalWrite(pinRelayOpen, HIGH);
//      delay(1000);
//      digitalWrite(pinRelayOpen, LOW);
//      Serial.println("opened");
      
    }
    else if (dataSTB== "c" || dataSTB== "C" || dataSTB== "c\n" || dataSTB== "C\n" )
    {
      digitalWrite(pinRelayClose, HIGH);
      delay(1000);
      digitalWrite(pinRelayClose, LOW);
      Serial.println("closed");
      
    }
    else if (dataSTB== "s" || dataSTB== "S" || dataSTB== "s\n" || dataSTB== "S\n" )
    {
      digitalWrite(pinRelayStop, HIGH);
      delay(1000);
      digitalWrite(pinRelayStop, LOW);
      Serial.println("stoped");
    }
    digitalWrite(pinRelayClose, LOW);
    delay(1000);
    Serial.println("closed");
  }
//  else if(digitalRead(pinButtonOpen == LOW))
//  {
//    Serial.println("visitor");
//  }

}
