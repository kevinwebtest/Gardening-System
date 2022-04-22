#include <LiquidCrystal.h>
#include <dht.h>
#define soilsensor A0
#define watersensor A1
#define dht11 A2
#define ldr A3
#define buzz 8
int IN1 = 13;
int IN2 = 12;
int IN3 = 11;
int IN4 = 10;

dht DHT;
float air, tanah, cahaya, suhu;
float tinggiAir;
float kelembabanTanah;
LiquidCrystal lcd(7,6,5,4,3,2);

void setup() {
  lcd.begin(16, 2);
  pinMode(soilsensor, INPUT);//Kelembaban
  pinMode(watersensor, INPUT);//Air
  pinMode(ldr, INPUT);//Cahaya
  pinMode (buzz, OUTPUT);
  pinMode (IN1, OUTPUT);
  pinMode (IN2, OUTPUT);
  pinMode (IN3, OUTPUT);
  pinMode (IN4, OUTPUT);
}

void loop() {
  DHT.read11(dht11);  
  suhu = DHT.temperature;
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Temperature: ");
  lcd.setCursor(12,0);
  lcd.print(suhu);
  lcd.setCursor(14,0);
  lcd.print("*C ");
  lcd.setCursor(0,1);

  cahaya = analogRead(ldr);

  if(cahaya>900){ //gelap
    if(suhu>=5 && suhu <20){
      lcd.print("Dark Windy MR"); //MR=Might Rain
      delay(3000);
      lcd.clear();
      kelembaban();
    }
    if(suhu>=20 && suhu <35){
      lcd.print("Cloudy/Foggy MR");
      delay(3000);
      lcd.clear();
      kelembaban();
    }
    if(suhu>=35 && suhu <50){
      lcd.print("Abnormally Hot");
      delay(3000);
      lcd.clear();
      kelembaban();
    }
  } 
  
  if(cahaya>=850 && cahaya<900){ //tidak terlalu terang
    if(suhu>=5 && suhu <20){
      lcd.print("Brigth Windy MR");
      delay(3000);
      lcd.clear();
      kelembaban();
    }
    if(suhu>=20 && suhu <35){
      lcd.print("Bright Cloudy MR");
      delay(3000);
      lcd.clear();
      kelembaban();
    }
    if(suhu>=35 && suhu <50){
      lcd.print("Hot Weather");
      delay(3000);
      lcd.clear();
      kelembaban();
    }
  }
  
  if(cahaya<850){ //terang sekali
    if(suhu>=5 && suhu <20){
      lcd.print("Sunny Windy MR");
      delay(3000);
      lcd.clear();
      kelembaban();
    }
    if(suhu>=20 && suhu <35){
      lcd.print("Sunny");
      delay(3000);
      lcd.clear();
      kelembaban();
    }
    if(suhu>=35 && suhu <50){
      lcd.print("Dry Sunny");
      delay(3000);
      lcd.clear();
      kelembaban();
    }
  }
  lcd.clear();
  if(tinggiAir<=0.5){
    lcd.setCursor(0, 0);
    lcd.print(tinggiAir); 
    lcd.setCursor(5, 0);
    lcd.print("cm"); 
    lcd.setCursor(0, 1);
    lcd.print("Empty");
    digitalWrite(10,LOW);
    delay(2000);
  }

  if(tinggiAir>0.5 && tinggiAir<=1){
    lcd.setCursor(0, 0);
    lcd.print(tinggiAir); 
    lcd.setCursor(5, 0);
    lcd.print("cm"); 
    lcd.setCursor(0, 1);
    lcd.print("Almost Empty"); 
    delay(2000);
  }

  if(tinggiAir>1 && tinggiAir<=2){
    lcd.setCursor(0, 0);
    lcd.print(tinggiAir); 
    lcd.setCursor(5, 0);
    lcd.print("cm"); 
    lcd.setCursor(0, 1);
    lcd.print("Fair"); 
    delay(2000);
  }

  if(tinggiAir>2 && tinggiAir<=3){
    lcd.setCursor(0, 0);
    lcd.print(tinggiAir); 
    lcd.setCursor(5, 0);
    lcd.print("cm"); 
    lcd.setCursor(0, 1);
    lcd.print("Sufficient"); 
    delay(2000);
  }

  if(tinggiAir>3 && tinggiAir<=4){
    lcd.setCursor(0, 0);
    lcd.print(tinggiAir); 
    lcd.setCursor(5, 0);
    lcd.print("cm"); 
    lcd.setCursor(0, 1);
    lcd.print("Full"); 
    delay(2000);
  } 


}
void kelembaban(){
    tanah = analogRead(soilsensor);
    kelembabanTanah = tanah*100/1023;
    air = analogRead(watersensor);
    tinggiAir = analogRead(watersensor)*4/1023;
    if(tanah>=0 && tanah <613.8){
      lcd.setCursor(0, 0);
      lcd.print(kelembabanTanah); 
      lcd.setCursor(4, 0);
      lcd.print("%"); 
      lcd.setCursor(0, 1);
      lcd.print("Wet Soil"); 
    }
  
    if(tanah>=613.8 && tanah <716.1){
      lcd.setCursor(0, 0);
      lcd.print(kelembabanTanah); 
      lcd.setCursor(4, 0);
      lcd.print("%"); 
      lcd.setCursor(0, 1);
      lcd.print("Moist Soil"); 
      if(tinggiAir<=0.5){
        digitalWrite (IN1, LOW);
        digitalWrite (IN2, LOW);
        digitalWrite (IN3, LOW);
        digitalWrite (IN4, LOW);
        tone(buzz,1000);//frekuensi
        delay(1000);
        noTone(buzz);
        }
      else{
        digitalWrite (IN1, LOW);
        digitalWrite (IN2, LOW);
        digitalWrite (IN3, HIGH);
        digitalWrite (IN4, LOW);
        delay(3000);
        digitalWrite (IN1, LOW);
        digitalWrite (IN2, LOW);
        digitalWrite (IN3, LOW);
        digitalWrite (IN4, LOW);
        }
    }
  
    if(tanah>=716.1 && tanah <1024){
      lcd.setCursor(0, 0);
      lcd.print(kelembabanTanah); 
      lcd.setCursor(4, 0);
      lcd.print("%"); 
      lcd.setCursor(0, 1);
      lcd.print("Dry Soil"); 
      if(tinggiAir<=0.5){
        digitalWrite (IN1, LOW);
        digitalWrite (IN2, LOW);
        digitalWrite (IN3, LOW);
        digitalWrite (IN4, LOW);
        tone(buzz,1000);//frekuensi
        delay(1000);
        noTone(buzz);
        }
      else{
        digitalWrite (IN1, LOW);
        digitalWrite (IN2, LOW);
        digitalWrite (IN3, HIGH);
        digitalWrite (IN4, LOW);
        delay(5000);
        digitalWrite (IN1, LOW);
        digitalWrite (IN2, LOW);
        digitalWrite (IN3, LOW);
        digitalWrite (IN4, LOW);
        }
    }
  delay(2000);
}
