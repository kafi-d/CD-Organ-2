int a=1; // Variable
int b=0; // Variable
int innen=10; // Anschlusspin Schlittenmotor
int aussen=9; // Anschlusspin Schlittenmotor
int discmotor=6; // Anschlusspin Discmotor
int maxpos=950; // maximale position des Schlittenmotors
int minpos=250; // minimale position des Schlittenmotors
int divr=0; // diferenz der maximalen und minimalen position des Schlittenmotors
void setup()
{
  Serial.begin(9600);
  pinMode(innen,OUTPUT);
  pinMode(aussen,OUTPUT);
  pinMode(discmotor,OUTPUT);
  }
void loop() {
// Eingangswerte abfragen  
float Pospot = analogRead(A5); //Position Poti 
int pos = analogRead(A0); // Position des Schlittenmotors
float Mspeed = analogRead(A4); //Motorspeed Poti
float CVspeed = analogRead(A6); // CV Motorspeed
float CVposition = analogRead(A7);// CV Position
// Eingangswerte umrechnen 
CVposition =(CVposition-488)*2;
Pospot = CVposition+Pospot;
Pospot = 1024-Pospot;
Pospot = ((Pospot/1024)*(maxpos-minpos))+minpos;
Mspeed = Mspeed*Mspeed/1024;
CVspeed = (CVspeed-488)/2;
divr = maxpos-minpos;
// Schlittenmotorsteuerung 
b = Pospot;
if (b>maxpos) {b=maxpos;}
if (b<minpos) {b=minpos;}
int up;
int down;
if (a!=0) {up = (b-pos)/10;
             down = (pos-b)/10;
             if (pos < b) {analogWrite(innen,255);delay(up);}
             if (pos > b) digitalWrite(innen,LOW);
             if (pos > b) {analogWrite(aussen,255);delay(down);}
             if (pos < b) digitalWrite(aussen,LOW);}
            else  {digitalWrite(innen,LOW); digitalWrite(aussen,LOW);}
   if (pos-50 < b)analogWrite(innen,LOW);
   if (pos+50 > b)analogWrite(aussen,LOW);
   if (a==0) {analogWrite(innen,LOW);analogWrite(aussen,LOW);} 
// Discmotorsteuerung
analogWrite(discmotor,Mspeed+CVspeed);
}
