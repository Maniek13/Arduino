
#include <LiquidCrystal.h>
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;

LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

int godziny=0,minuty=0,sekundy=0, pauza = 2;

int x = 0;

void setup() {
  pinMode(7, INPUT_PULLUP);
  pinMode(10, INPUT_PULLUP);
  lcd.begin(16, 2);
  lcd.print("Stoper");
}

void loop() {
  sekundy = millis()/100 - minuty * 60 - godziny *360 - x;

  if(sekundy == 60){
    minuty = minuty + 1;
    sekundy = 0;
    if(pauza == 0){
      clear();
    }
  }
  
  if(minuty == 60){
    minuty = 0;
    godziny = godziny + 1; 
 	if(pauza == 0){
      clear();
    }
  }
  
  if(godziny == 24){
    godziny = 0;
 	if(pauza == 0){
      clear();
    }
  }
  
  
  if(digitalRead(7) == LOW && pauza != 2){
    if(pauza == 1){
     pauza = 0; 
     clear();
    }
    else{
     pauza = 1;
     lcd.setCursor(9,1);
 	 lcd.print("PAUZA");
    }
  }

  
  if(digitalRead(10) == LOW && pauza != 1){
    if(pauza == 2){
     clear();
     x = millis()/100;
     pauza = 0; 
     minuty = 0;
     sekundy = 0;
     godziny = 0;
     lcd.setCursor(9,1);
 	 lcd.print("RUN");

    }
    else{
     pauza = 2;
     lcd.setCursor(9,1);
 	 lcd.print("STOP");
    }
  }
  
  
  if(pauza == 0){
  lcd.setCursor(0,1);
  lcd.print(godziny);
  lcd.setCursor(2,1);
  lcd.print(":");
  lcd.setCursor(3,1);
  lcd.print(minuty);
  lcd.setCursor(5,1);
  lcd.print(":");
  lcd.print(sekundy);
  lcd.setCursor(9,1);
  lcd.print("RUN");
  }

  delay(100);
  
}

void clear(){
  lcd.clear();
  lcd.print("Stoper"); 
}




