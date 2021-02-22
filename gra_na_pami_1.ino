#include <LiquidCrystal.h>

const int rs = 10, en = 9, d4 = 8, d5 = 7, d6 = 4, d7 = 3;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

int czerwony = 13;
int niebieski = 12;
int zielony = 11;

int ilosc = 10;  
int czas = 1000; //czas wyswietlania pojedynczego koloru 1000 = 1sekunda
int liczba_graczy = 1;
int gracz = 1;
int temp;

int zmienna;
int pomoc;

int tablica_wynikow[]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
int tablica_gracza[]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};


int wyniki[] = {0,0,0,0,0,0,0,0,0,0};
int wygrany[] = {0,0,0,0,0,0,0,0,0,0};

int start = 0;
int klikniecie = 0;
int wynik = 0;
int reset = 6;
int zacznij = 5;



void setup(){
  pinMode(czerwony, OUTPUT);
  pinMode(niebieski, OUTPUT);
  pinMode(zielony, OUTPUT);
  
  pinMode(A0, INPUT_PULLUP);
  pinMode(A1, INPUT_PULLUP);
  pinMode(A2, INPUT_PULLUP);
  pinMode(A3, INPUT_PULLUP);
  
  pinMode(reset, INPUT_PULLUP);
  pinMode(zacznij, INPUT_PULLUP);
  
  lcd.begin(16, 2);
  
  randomSeed(analogRead(5));
}

void loop(){
  if(start == 0){
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Hellow!");
  delay(1000);
    
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Gracze: ");
  lcd.setCursor(9,0);
  lcd.print(liczba_graczy);
    
  lcd.setCursor(0,1);
  lcd.print("+ cz.|- ni. przy");
    
  start = 5;
  }
  
  if(start == 1){
   	kolejnosc_lampek_start();
  }
  
  if(start == 2){
    ktora();
  }
  
   if(start == 3){
    gra();
  }
  
   if(start == 4){
    koniec();
  }
  
  if(start == 5){
	ilosc_graczy();
  }
  
  if(start == 6){
	powtorzenia_tekst();
  }
  
   if(start == 7){
	ilosc_powt();
  }
  
  if(start == 10){
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Gracz");
    lcd.setCursor(7,0);
    lcd.print(gracz);
    delay(1000);
    
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Nacisnij start");
    lcd.setCursor(0,1);
    lcd.print("Zob. kombinacje");
    start = 1;
  }
  
  if(start == 11){
    podsumowanie();
  }
  
   if(start == 12){
    wygrani();
  }
  
   reset_app(); 
}


void ilosc_graczy(){
  if (digitalRead(A0) == LOW){
       while(digitalRead(A0) == LOW){}
    if(liczba_graczy < 10){
      liczba_graczy += 1;

        if(liczba_graczy < 10){
        lcd.setCursor(10, 0);
        lcd.print(" ");
      	}
      
        lcd.setCursor(9, 0);
      	lcd.print(liczba_graczy);
    }
    else{
    }
  }
  
    if (digitalRead(A1) == LOW){
       while(digitalRead(A1) == LOW){}
    if(liczba_graczy > 1){
      liczba_graczy -= 1;       
      
      
      if(liczba_graczy < 10){
        lcd.setCursor(10, 0);
        lcd.print(" ");
      	}
      
        lcd.setCursor(9, 0);
  		lcd.print(liczba_graczy);
    }
    else{
    }
  }
  
  if (digitalRead(zacznij) == LOW){
       while(digitalRead(zacznij) == LOW){}
     start = 6;
  }
}

void powtorzenia_tekst(){
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Powtorzenia: ");
  lcd.setCursor(13,0);
  lcd.print(ilosc);
    
  lcd.setCursor(0,1);
  lcd.print("+ cz.|- ni. przy");
  
  start = 7;
  
}

void ilosc_powt(){
  if (digitalRead(A0) == LOW){
       while(digitalRead(A0) == LOW){}
    if(ilosc < 30){
      ilosc += 1;

        if(ilosc < 10){
        lcd.setCursor(14, 0);
        lcd.print(" ");
      	}
      
       	lcd.setCursor(13, 0);
  		lcd.print(ilosc);
    }
    else{
    }
  }
  
    if (digitalRead(A1) == LOW){
       while(digitalRead(A1) == LOW){}
    if(ilosc > 1){
      ilosc -= 1;
       
   		if(ilosc < 10){
        lcd.setCursor(14, 0);
        lcd.print(" ");
      	}
      
     	lcd.setCursor(13, 0);
  		lcd.print(ilosc);
    }
    else{
    }
  }
  
  if (digitalRead(zacznij) == LOW){
       while(digitalRead(zacznij) == LOW){}
     start = 10;
  }
}



void podsumowanie(){
   wynik = wyniki[0];
  
  temp = 0;
  wygrany[temp] = 1;
  
  for(int i = 1; i < liczba_graczy; i++){
    if(wyniki[i] >= wynik){
      wynik = wyniki[i];
      wygrany[temp] = i+1;
    }
  }
  
   for(int i = 0; i < liczba_graczy; i++){
    if(wyniki[i] == wynik && i+1 != wygrany[0] ){
		temp +=1;
      wygrany[temp] = i+1;
    }
  }
  
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Wygrana, pkt:");
  lcd.setCursor(14,0);
  lcd.print(wynik);
  
  start = 12;

}


void wygrani(){
  for(int i = 0; i <= temp; i++){
  
  lcd.setCursor(0,1);
  lcd.print("Gracz nr ");
  lcd.setCursor(9,1);
  lcd.print(wygrany[i]);
  delay(500);
  }

}


void kolejnosc_lampek_start(){
  if (digitalRead(zacznij) == LOW){
    while(digitalRead(zacznij) == LOW){}

    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Kombinacja");
    delay(500);
    
    poczatek();
    delay(1000);
    
    start = 2;
  }
}


void wyswietlanie(int zmienna){
  if(zmienna == 1){
    digitalWrite(czerwony, HIGH);
    digitalWrite(niebieski, LOW);
    digitalWrite(zielony, LOW);
  }
    if(zmienna == 2){
    digitalWrite(czerwony, LOW);
    digitalWrite(niebieski, HIGH);
    digitalWrite(zielony, LOW);
  }
    if(zmienna == 3){
    digitalWrite(czerwony, LOW);
    digitalWrite(niebieski, LOW);
    digitalWrite(zielony, HIGH);
  }
    if(zmienna == 4){
    digitalWrite(czerwony, HIGH);
    digitalWrite(niebieski, LOW);
    digitalWrite(zielony, HIGH);
  }
}

void przerwa_dioda(){
    digitalWrite(czerwony, LOW);
    digitalWrite(niebieski, LOW);
    digitalWrite(zielony, LOW);
  	delay(czas);
}

void poczatek(){
  for(int i = 0; i<ilosc; i++){
 	pomoc = zmienna;
    zmienna = random(1, 5);
    
    while(pomoc == zmienna){
       zmienna = random(1, 5);
    }

    wyswietlanie(zmienna);
    tablica_wynikow[i] = zmienna;
   	delay(czas);
    przerwa_dioda();
  } 
  
   digitalWrite(czerwony, LOW);
   digitalWrite(niebieski, LOW);
   digitalWrite(zielony, LOW);
}


void gra(){
  if(klikniecie < ilosc){
     if (digitalRead(A0) == LOW){
       while(digitalRead(A0) == LOW){}
      tablica_gracza[klikniecie] = 1;
      klikniecie += 1;
      start = 2;
       pomylka();
 	}
     if (digitalRead(A1) == LOW){
       while(digitalRead(A1) == LOW){}
      tablica_gracza[klikniecie] = 2;
      klikniecie += 1;
      start = 2;
       pomylka();
     }
     if (digitalRead(A2) == LOW){
       while(digitalRead(A2) == LOW){}
      tablica_gracza[klikniecie] = 3;
      klikniecie += 1;
      start = 2;
       pomylka();
 	}
     if (digitalRead(A3) == LOW){
       while(digitalRead(A3) == LOW){}
      tablica_gracza[klikniecie] = 4;
      klikniecie += 1;
      start = 2;
       pomylka();
 	}
  }
  else{
   start = 4; 
  }
}

void pomylka(){
  if(tablica_gracza[klikniecie-1] != tablica_wynikow[klikniecie-1]){
    start = 4; 

   	lcd.clear();
  	lcd.setCursor(0,0);
  	lcd.print("Pomylka");
    delay(500);
  }  
}

void koniec(){
  for(int i = 0; i<ilosc; i++){
  	if(tablica_wynikow[i] == tablica_gracza[i]){
  		wynik +=1;
  	}
  }
  
  if(gracz < liczba_graczy){
    wyniki[gracz-1] = wynik;
    gracz +=1;
    
    klikniecie = 0;
    start = 10;
  }
  else{
     wyniki[gracz-1] = wynik;
    start = 11;
  }
  
 
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Koniec");
  lcd.setCursor(0,1);
  lcd.print("Wynik:");
  lcd.setCursor(7,1);
  lcd.print(wynik);
  
  wynik = 0;
 
  delay(2000);
}

void reset_app(){
  if (digitalRead(reset) == LOW){
    while(digitalRead(reset) == LOW){}
    start = 0;
    wynik = 0;
    klikniecie = 0;
    liczba_graczy = 1;
    gracz = 1;
    ilosc = 10;
    
    for(int i = 0; i < liczba_graczy; i++){
       wygrany[i] = 0;
    }
   
  }
}

void ktora(){
  if(klikniecie != ilosc){
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Kolor nr. ");
    lcd.setCursor(0,12);
    lcd.print(klikniecie + 1);
  }
  start = 3;
}