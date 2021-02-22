#include <LiquidCrystal.h>

int czerwona = 7;
int zolta = 6;
int zielona = 5;
int niebieska = 8;
int btn_cz = 4;
int btn_zol = 3;
int btn_ziel = 2;
int btn_nie = 0;
bool stop = false;
int guzik;
int zmienna;
long wynik;
long temp;
int ilosc = 0;

int rundy = 15;

const int rs = 12, en = 11, d4 = 13, d5 = 10, d6 = 9, d7 = 1;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void setup(){
  pinMode(czerwona, OUTPUT);
  pinMode(zolta, OUTPUT);
  pinMode(zielona, OUTPUT);
  pinMode(niebieska, OUTPUT);
  pinMode(btn_cz, INPUT_PULLUP);
  pinMode(btn_zol, INPUT_PULLUP);
  pinMode(btn_ziel, INPUT_PULLUP);
  pinMode(btn_nie, INPUT_PULLUP);
  pinMode(A0, INPUT_PULLUP);
  
  lcd.begin(16, 2);
  lcd.print("Uruchamianie...");
  delay(1000);
}

void loop(){

    res();

  
  if(ilosc == 0){
     lcd.setCursor(0,0);
     lcd.clear();
 	 lcd.print("Zaczynamy");
    
 	 delay(1000);
    
     lcd.setCursor(0,0);
 	 lcd.print("Wcisnij odpowie-");
     lcd.setCursor(0,1);
 	 lcd.print("dni przycisk");
  }
   

  
  zmienna =  random(1, 5);

  if(ilosc < rundy){
  	ilosc= ilosc+ 1;
   if(zmienna == 1){
    
    digitalWrite(czerwona, HIGH);
    digitalWrite(zolta, LOW);
    digitalWrite(zielona, LOW);
    digitalWrite(niebieska, LOW);
    
    temp = czas();
    
  }else if(zmienna == 2){
    
    digitalWrite(zolta, HIGH);
    digitalWrite(czerwona, LOW);
    digitalWrite(zielona, LOW);
    digitalWrite(niebieska, LOW);
      
    temp = czas();
    
  }else if(zmienna == 1){
    
    digitalWrite(zielona, HIGH);
    digitalWrite(czerwona, LOW);
    digitalWrite(zolta, LOW);
    digitalWrite(niebieska, LOW);
    
    temp = czas();
  } else{
    
    digitalWrite(niebieska, HIGH);
    digitalWrite(czerwona, LOW);
    digitalWrite(zolta, LOW);
    digitalWrite(zielona, LOW);
    
    temp = czas();


  }
  
  wynik = wynik + temp;
    
  lcd.setCursor(0,1);
  lcd.print("Wynik:");
  lcd.setCursor(7,1);
  lcd.print(wynik);
   
   delay(1000);
   lcd.clear();
   lcd.setCursor(0,0);
   lcd.print("Kliknij odpowie-");
   lcd.setCursor(0,1);
   lcd.print("dni przycisk");
  }
  else if(ilosc == rundy){
    digitalWrite(zielona, LOW);
    digitalWrite(czerwona, LOW);
    digitalWrite(zolta, LOW);
    digitalWrite(niebieska, LOW);
    
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Koniec gry");
    lcd.setCursor(0,1);
    lcd.print("Wynik:");
    lcd.setCursor(6,1);
    lcd.print(wynik);
    ilosc= ilosc+ 1;
  }
}

long czas(){
  
  long czas = 0;
  
  while(stop != true && czas <= 60){
    
    czas = czas+1;
    
    if (digitalRead(btn_cz) == LOW){
      
    wylacz();

   		if(zmienna == 1){
      	ok();
        }
      	else{
        czas = czas + 60;
    	blad();
      	}
      
    stop = true;
  	}
    
    if (digitalRead(btn_zol) == LOW){
      wylacz();
      
      if(zmienna == 2 ){
        ok();
      }
      else{
        czas = czas + 60;
     	blad();
      }
      
      stop = true;
  	}
    
    if (digitalRead(btn_ziel) == LOW){
      wylacz();
      
      if(zmienna == 3){
    	ok();
      }
      else{
        czas = czas + 60;
     	blad();
      } 
      
      stop = true;
  	}
    
    if (digitalRead(btn_nie) == LOW){
       wylacz();
      	if(zmienna == 4){
         ok();
      	}
        else{
          czas = czas + 60;
        blad();
        }
      
      stop = true;
  	}

    delay(100);
  }
  
  if(czas == 61){
      wylacz();
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Za pozno");
      lcd.setCursor(0,1);
      lcd.print("+61");
      delay(1000);
  }
  stop = false;
 
  return czas;
}


void wylacz(){
   digitalWrite(zolta, LOW);
   digitalWrite(czerwona, LOW);
   digitalWrite(zielona, LOW);
   digitalWrite(niebieska, LOW);
}


void res(){
  if (analogRead(A0) == 0 ){
  	 ilosc = 0;
     temp = 0;
     wynik = 0;
     lcd.setCursor(0,0);
     lcd.clear();
 	 lcd.print("Nowy gracz");
     delay(1000);
  }
}

void blad(){
      	lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("Zly przycisk");
        lcd.setCursor(0,1);
        lcd.print("kara + 60");
        delay(1000);
}

void ok(){
    	lcd.clear();
        lcd.setCursor(0,0);
  		lcd.print("Dobrze");
}