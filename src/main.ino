#include <LiquidCrystal.h>
#include <IRremote.h>

// #####################
// Liquid Crystal Config
// #####################
const int registerSelectPin = 2;
const int enablePin = 3;

const int DB4 = 4;
const int DB5 = 5;
const int DB6 = 6;
const int DB7 = 7;

LiquidCrystal lcd(
  registerSelectPin, 
  enablePin, 
  DB4,
  DB5,
  DB6,
  DB7
);

// ################
// IR Remote Config
// ################
int RECV_PIN = 8;
IRrecv irrecv(RECV_PIN);
decode_results results;

// ######
// BUZZER
// ######
int buzzerPin = 9;
bool buzzerOn = false;

void setup() {
  Serial.begin(9600);
  
  pinMode(buzzerPin, OUTPUT);
  
  lcd.begin(16, 2);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("press a button");
  
  irrecv.enableIRIn();
}

void loop() {
  
  if (irrecv.decode(&results)) { // Returns 0 if no data ready, 1 if data ready.     
    int value = results.value;
    
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("button: ");
    Serial.print("button: ");
    Serial.println(results.value, HEX); //prints the value a a button press     

    switch(results.value) {
      /**
       * codes for IR Remote from Tinkercad
       */
      case 0xFD30CF:
        Serial.println("0");
        lcd.print("0");
        break;
      case 0xFD08F7:
        Serial.println("1");
        lcd.print("1");
        break;
      case 0xFD8877:
        Serial.println("2");
        lcd.print("2");
        break;
      case 0xFD48B7:
        Serial.println("3");
        lcd.print("3");
        break;
      case 0xFD28D7:
        Serial.println("4");
        lcd.print("4");
        break;
      case 0xFDA857:
        Serial.println("5");
        lcd.print("5");
        break;
      case 0xFD6897:
        Serial.println("6");
        lcd.print("6");
        break;
      case 0xFD18E7:
        Serial.println("7");
        lcd.print("7");
        break;
      case 0xFD9867:
        Serial.println("8");
        lcd.print("8");
        break;
      case 0xFD58A7:
        Serial.println("9");
        lcd.print("9");
        break;
      case 0xFD00FF:
        Serial.println("On/Off");
        lcd.print("On/Off");
        if(buzzerOn) {
          digitalWrite(buzzerPin, LOW);
        } else {
          digitalWrite(buzzerPin, HIGH);
        }
        buzzerOn = !buzzerOn;
        break;
      case 0xFD807F:
        Serial.println("VOL+");
        lcd.print("VOL+");
        break;
      case 0xFD40BF:
        Serial.println("FUNC/STOP");
        lcd.print("FUNC/STOP");
        break;
      case 0xFD20DF:
        Serial.println("Rewind");
        lcd.print("Rewind");
        break;
      case 0xFDA05F:
        Serial.println("Play/Pause");
        lcd.print("Play/Pause");
        break;
      case 0xFD609F:
        Serial.println("Forward");
        lcd.print("Forward");
        break;
      case 0xFD10EF:
        Serial.println("Down");
        lcd.print("Down");
        break;
      case 0xFD906F:
        Serial.println("VOL-");
        lcd.print("VOL-");
        break;
      case 0xFD50AF:
        Serial.println("UP");
        lcd.print("UP");
        break;
      case 0xFDB04F:
        Serial.println("EQ");
        lcd.print("EQ");
        break;
      case 0xFD708F:
        Serial.println("ST/REPT");
        lcd.print("ST/REPT");
        break;
        
      /**
       * codes for IR Remote from arduino starter kit. Generic one with no brand. It has the label Car MP3
       */
      case 0xFF6897:
        Serial.println("0");
        lcd.print("0");
        break;
      case 0xFF30CF:
        Serial.println("1");
        lcd.print("1");
        break;
      case 0xFF18E7:
        Serial.println("2");
        lcd.print("2");
        break;
      case 0xFF7A85:
        Serial.println("3");
        lcd.print("3");
        break;
      case 0xFF10EF:
        Serial.println("4");
        lcd.print("4");
        break;
      case 0xFF38C7:
        Serial.println("5");
        lcd.print("5");
        break;
      case 0xFF5AA5:
        Serial.println("6");
        lcd.print("6");
        break;
      case 0xFF42BD:
        Serial.println("7");
        lcd.print("7");
        break;
      case 0xFF4AB5:
        Serial.println("8");
        lcd.print("8");
        break;
      case 0xFF52AD:
        Serial.println("9");
        lcd.print("9");
        break;
      case 0xFFA25D:
        Serial.println("CH-");
        lcd.print("CH-");
        break;
      case 0xFF629D:
        Serial.println("CH");
        lcd.print("CH");
        break;
      case 0xFFE21D:
        Serial.println("CH-");
        lcd.print("CH-");
        break;
      case 0xFF22DD:
        Serial.println("|<<");
        lcd.print("|<<");
        break;
      case 0xFF02FD:
        Serial.println(">>|");
        lcd.print(">>|");
        break;
      case 0xFFC23D:
        Serial.println(">|");
        lcd.print(">|");
        break;
      case 0xFFE01F:
        Serial.println("-");
        lcd.print("-");
        break;
      case 0xFFA857:
        Serial.println("+");
        lcd.print("+");
        break;
      case 0xFF906F:
        Serial.println("EQ");
        lcd.print("EQ");
        break;
      case 0xFF9867:
        Serial.println("100+");
        lcd.print("100+");
        break;
      case 0xFFB04F:
        Serial.println("200+");
        lcd.print("200+");
        break;

      default:
        lcd.print("???");
        Serial.print("not registered yet: ");
        Serial.println(results.value, HEX);
    }
    
    irrecv.resume(); // Restart the ISR state machine and Receive the next value     
  } 
  
  delay (300);
}
