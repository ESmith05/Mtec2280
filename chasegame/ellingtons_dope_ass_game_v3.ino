byte ledPin[] = {2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
int ledDelay =350;
int direction = 1;
int currentLED = 0;
int switchPin = 13;
int val;
unsigned long changeTime;
int toggleState = 0;

int cLed = 0;


boolean pressing = false;

#include <LiquidCrystal.h>

LiquidCrystal lcd(47, 45, 39, 37, 35, 33);

void setup() {
  for (int x = 0; x < 11; x++) {
    pinMode (ledPin[x], OUTPUT);
  }
  changeTime = millis();
  pinMode(switchPin, INPUT);

  Serial.begin(9600);

 lcd.begin(16, 2);

}


void loop() {
  if ((millis() - changeTime) > ledDelay) {
    cLed = changeLED();
    Serial.println(cLed);
    changeTime = millis();

//    val = digitalRead(switchPin);
//    if (val == LOW) {
//      digitalWrite(ledPin, HIGH);
//    }
//    if (val == HIGH) {
//      digitalWrite(ledPin, LOW);
//      direction = 0;
//    }
  // set the cursor to column 0, line 1
  // (note: line 1 is the second row, since counting begins with 0):
  lcd.setCursor(0, 1);
  // print the number of seconds since reset:
  //lcd.print(millis() / 1000);
  }

  toggleState = digitalRead(switchPin);

  if (toggleState == LOW) {
    pressing = true;
  }

  if (toggleState == HIGH && pressing == true) {
    pressing = false;
    if (cLed == 6){
      lcd.print("Run Faster!");
      ledDelay = ledDelay - 50; 
      Serial.println(ledDelay);  
    }else{

      Serial.println("You've Been Caught!");   
      lcd.print("You've Been Caught!");
      delay(1000);
      lcd.clear();
    }
    if (ledDelay == -50) {
      Serial.println("You've Escaped Safely!");
      delay (5000);
      ledDelay=350;
      
    }
    
    
  }

  
}

int changeLED() {
  for (int x = 0; x < 11; x++) {
    digitalWrite(ledPin[x], LOW);
  }
  digitalWrite(ledPin[currentLED], HIGH);
  currentLED += direction;

  if (currentLED == 11) {
    direction = -1;
  }
  if (currentLED == 0) {
    direction = 1;
  }
  return currentLED;



 
}


