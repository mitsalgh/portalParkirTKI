#define pinRelayOpen 2
#define pinRelayClose 3
#define pinRelayStop 10
#define pinButtonOpen 5   //5
#define pinButtonHelp A2  //A2
#define sensorLoopDetectorOpen A1
#define sensorLoopDetectorClosed A0
#define LEDOpen 6
#define LEDClose 8
#define LEDReady 7
#define loopDetector1 A3
#define loopDetector2 A4

int flagVehicleIn = 0;
int flagVehicleOut = 0;
int flagButtonOpen = 0;
int flagButtonHelp = 0;
String dataSTB = "";
String statusPortal = "closed";
String mode = "";

unsigned long lastDebounceTime = 0; //variabel untuk debounce
unsigned long debounceDelay = 50; //waktu debounce dalam milidetik
unsigned long prevMillis = 0; //variabel untuk menyimpan waktu sebelumnya
unsigned long interval = 350; //interval waktu untuk membaca keypad dalam m
unsigned long intervalVehicle = 500; //interval waktu untuk membaca keypad dalam m

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
  pinMode(loopDetector1, INPUT_PULLUP);
  pinMode(loopDetector2, INPUT_PULLUP);
  pinMode(sensorLoopDetectorClosed, INPUT_PULLUP);
  pinMode(sensorLoopDetectorOpen, INPUT_PULLUP);
  mode = "ready";
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
  statusPortal = "open";
}
void prosesOpenTesting()
{
  digitalWrite(pinRelayOpen, HIGH);
  digitalWrite(LEDReady, LOW);
  digitalWrite(LEDOpen, HIGH);
  delay(1000);
  digitalWrite(pinRelayOpen, LOW);
  digitalWrite(LEDOpen, LOW);
  Serial.println("opened");
   delay(3500);
   digitalWrite(LEDReady, LOW);
   digitalWrite(LEDClose, HIGH);
   digitalWrite(pinRelayClose, HIGH);
   digitalWrite(LEDReady, LOW);
   delay(1000);
   digitalWrite(pinRelayClose, LOW);
   digitalWrite(LEDClose, LOW);
   Serial.println("closed");
   delay(1000);
}
void prosesClosed()
{
  while (digitalRead(sensorLoopDetectorClosed) == HIGH)
  {
    if (digitalRead(sensorLoopDetectorClosed) == LOW)
    {
      Serial.println("closed");
      break;
    }
  }
}

void resetAll()
{
  mode = "ready";
  statusPortal = "ready";
  flagVehicleOut = 0;
}

void loop()
{
  // mode = "testing"; // jika mau testing di komen jika masuk ke production
  if (mode == "testing")
  {
    digitalWrite(LEDReady, HIGH);
    unsigned long currentMillis = millis(); //mendapatkan waktu saat ini
    if (currentMillis - prevMillis >= interval)
    { //jika interval waktu sudah terlewati
      prevMillis = currentMillis; //memperbarui waktu sebelumnya


      if (digitalRead(pinButtonHelp) == LOW && flagButtonHelp == 0)
      {
        Serial.println("help");
        flagButtonHelp = 1;
        delay(200);
      }
      if (digitalRead(pinButtonHelp) == HIGH)
      {
        flagButtonHelp = 0;
      }
      if (digitalRead(pinButtonOpen) == LOW && flagButtonOpen == 0)
      {
        Serial.println("v");
        flagButtonOpen = 1;
        //          prosesOpen();
      }
      if (digitalRead(pinButtonOpen) == HIGH)
      {
        flagButtonOpen = 0;
      }

    }
    if (Serial.available() > 0) //check Perintah dari STB
    {
      delay(10);
      dataSTB = Serial.readString();
      if (dataSTB == "o" || dataSTB == "O" || dataSTB == "o\n" || dataSTB == "O\n" )
      {
        prosesOpenTesting();
      }
      else if (dataSTB == "c" || dataSTB == "C" || dataSTB == "c\n" || dataSTB == "C\n" )
      {
        digitalWrite(LEDReady, LOW);
        digitalWrite(LEDClose, HIGH);
        digitalWrite(pinRelayClose, HIGH);
        digitalWrite(LEDReady, LOW);
        delay(450);
        digitalWrite(pinRelayClose, LOW);
        digitalWrite(LEDClose, LOW);
        Serial.println("closed");
      }
      else if (dataSTB == "s" || dataSTB == "S" || dataSTB == "s\n" || dataSTB == "S\n" )
      {
        digitalWrite(pinRelayStop, HIGH);
        delay(1000);
        digitalWrite(pinRelayStop, LOW);
        Serial.println("stoped");
      }
    }
    if (statusPortal == "open")
    {
      mode = "close";
    }
  }
  //=================================================== Untuk Sistem Ready ==========================================
  if (mode == "ready")
  {
    digitalWrite(LEDReady, HIGH);
    unsigned long currentMillis = millis(); //mendapatkan waktu saat ini
    if (currentMillis - prevMillis >= intervalVehicle)
    { //jika interval waktu sudah terlewati
      prevMillis = currentMillis; //memperbarui waktu sebelumnya

      //            Serial.print(digitalRead(loopDetector1));
      //            Serial.print("  ");
      //            Serial.print(digitalRead(loopDetector2));
      //            Serial.println();
      if (digitalRead(loopDetector1) == HIGH)
      {
        if (flagVehicleIn == 0)
        {
          Serial.println("car");
          mode = "in";
        }
      }
    }
  }
  
  else if (mode == "in")
  {
    unsigned long currentMillis = millis(); //mendapatkan waktu saat ini
    if (currentMillis - prevMillis >= interval)
    { //jika interval waktu sudah terlewati
      prevMillis = currentMillis; //memperbarui waktu sebelumnya
      if (digitalRead(pinButtonHelp) == LOW)
      {
        Serial.println("help");
        delay(200);
      }
      if (digitalRead(pinButtonOpen) == LOW)
      {
        Serial.println("v");
        delay(100);
        //      prosesOpen();
      }

    }
    if (Serial.available() > 0) //check Perintah dari STB
    {
      delay(10);
      dataSTB = Serial.readString();
      if (dataSTB == "o" || dataSTB == "O" || dataSTB == "o\n" || dataSTB == "O\n" )
      {
        prosesOpen();
      }
      else if (dataSTB == "c" || dataSTB == "C" || dataSTB == "c\n" || dataSTB == "C\n" )
      {
        digitalWrite(LEDReady, LOW);
        digitalWrite(LEDClose, HIGH);
        digitalWrite(pinRelayClose, HIGH);
        digitalWrite(LEDReady, LOW);
        delay(150);
        digitalWrite(pinRelayClose, LOW);
        digitalWrite(LEDClose, LOW);
        Serial.println("closed");
      }
      else if (dataSTB == "s" || dataSTB == "S" || dataSTB == "s\n" || dataSTB == "S\n" )
      {
        digitalWrite(pinRelayStop, HIGH);
        delay(1000);
        digitalWrite(pinRelayStop, LOW);
        Serial.println("stoped");
      }
      //      mode = "ready";
    }
    if (statusPortal == "open")
    {
      mode = "close";
    }
  }
  else if (mode = "close")
  {
    while (statusPortal == "open")
    {
      unsigned long currentMillis = millis(); //mendapatkan waktu saat ini
      if (currentMillis - prevMillis >= interval)
      { //jika interval waktu sudah terlewati
        prevMillis = currentMillis; //memperbarui waktu sebelumnya
        if (digitalRead(loopDetector2) == LOW)
        {
          flagVehicleOut = 1;
          //          Serial.println("closed");
        }
        else if (digitalRead(loopDetector2) == HIGH && flagVehicleOut == 1)
        {
          Serial.println("closed");
          delay(200);
          statusPortal = "closed";
          resetAll();
        }
      }
    }
  }
}
