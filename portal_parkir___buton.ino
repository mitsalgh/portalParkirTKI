#include  <Wire.h>
#include <LiquidCrystal_I2C.h>


#define Buzzer D3
int irPin = D7;
int sensorOut = HIGH;
int button = D5;
int led = D6;
int lcdColumns = 16;
int lcdRows = 2;
LiquidCrystal_I2C lcd(0x27, lcdColumns, lcdRows); 

void setup() {
  // put your setup code here, to run once:
  pinMode(Buzzer, OUTPUT);
  pinMode(led, OUTPUT);
  pinMode(button, INPUT);
  pinMode(irPin, INPUT);
  digitalWrite(button, LOW); //activate arduino internal pull up
  Serial.begin(9600);
//  lcd.begin(16,2);
  lcd.init();// initialize LCD
   lcd.backlight();
//   lcd.clear ();
//    lcd.setCursor(0, 0); // lcd cursor one
//  lcd.println("SELAMAT DATANG__");
//  digitalWrite(Buzzer,LOW);
}
void loop() {
  

    
  sensorOut = digitalRead(irPin);

  if (sensorOut == LOW)
  {   
    lcd.clear (); 
lcd.setCursor(0, 0); // lcd cursor one
  lcd.println("SELAMAT DATANG  ");
  Serial.println("T");
    digitalWrite(led, LOW);
  }

    if (digitalRead(button) == HIGH){
      lcd.clear ();
    lcd.setCursor(0, 0); // lcd cursor one
      lcd.println("SILAHKAN MASUK__");
    Serial.println("k");
    digitalWrite(led, HIGH);
    delay(50);
    //digitalWrite(led, LOW);
    //delay(500);
  }

if (Serial.available()){
  char data;
  data = Serial.read();
  Serial.println(data);

   

  if (data =='o'){
    digitalWrite(led,HIGH);
    digitalWrite(Buzzer,HIGH);
    delay(500);
    digitalWrite(Buzzer,LOW);
    lcd.clear ();
  lcd.setCursor(0, 0); // lcd cursor one
  lcd.println("SILAHKAN MASUK");
  
  }

    else if(data =='c'){
    digitalWrite(led,LOW);
      lcd.clear();
  lcd.setCursor(0, 0); // lcd cursor one
  lcd.println("SELAMAT DATANG");
    Serial.println("waiting");
//    Serial.print("b");
   // delay(1000);
  }
  
}

//  else {
//    
// 
//  lcd.setCursor(0, 0); // lcd cursor one
//  lcd.println("SELAMAT DATANG__");
////  lcd.setCursor(0, 1);        //second row
////    lcd.print("  -_-   ");
//    digitalWrite(led, LOW);
//    }
}
