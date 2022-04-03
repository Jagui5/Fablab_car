/*
   Le but est de contrôler les mouvements du robot par une application connectée en bluetooth 

   Matériel : 
  - un téléphone équipé de l'application arduino bluetooth controller configurée de la façon suivante :
    - Connect in controller mode
      - a,d,g et r sont sur le joystick de gauche
      - p ==> triangle, m ==> rond 
      - s ==> X
  - un servomoteur connecté au port 10 de l'arduino ==> pour soulever la trappe
  - un arduino motor shield 
  - deux servomoteurs branchés aux ports 12 et 13  ==> pour faire avancer le moteur 
  - un module bluetooth avec une liaison i2c sur les ports 0 et 1 
*/ 

//*****EN-TÊTE DECLARATIF*****
#include <Servo.h>  // on inclut la bibliothèque pour piloter un servomoteur
#include "SoftwareSerial.h" // librairie pour controller en bluetooth 

Servo monServo;  // on crée l'objet monServo
Servo monServog; 
Servo monServod; 
char commande = ' ';
int position = 88;
int positiond = 90;
int positiong = 88;
char direction = ' ';

SoftwareSerial mySerial(0,1); // Démarrer la liaison bluetooth 

int val;

void setup(){  
    Serial.begin(9600);
    mySerial.begin(9600);
    Serial.println("Introduire p = prendre la balle, m = monter la tige, a = avancer, d = tourne a droit, g = tourne a gauche, r = reculer");
  //Servomoteur
    monServo.attach(10); // on définit le Pin utilisé par le servomoteur
    monServo.write(position); //Commence en 90 pour ne pas bouger et avoir une force dans l'axe
  //Servomoteurs pour diriger le robot 
    monServod.attach(12); // moteur droit 
    monServod.write(positiond); 
    monServog.attach(13); // moteur gauche 
    monServog.write(positiong);

    monServod.write(positiond); 
    monServog.write(positiong); 
    monServo.write(88);

     
}

void loop(){
   if (mySerial.available()) {
    
    commande = mySerial.read();
    monServo.write(position);
      if (commande == 'p'){
        // on crée une impulsion petite dans une direction pour monter
        monServo.write(75);
        delay(40);
        monServo.write(position);

      }

      if (commande == 'm'){
        // on crée une impulsion petite dans une direction pour descendre 
        monServo.write(95);
        delay(40);
        monServo.write(position);
        }

       if (commande == 'a'){direction = 'a';}
       if (direction == 'a'){
        monServod.write(80);  // le bras du servomoteur prend la position de la variable position
        monServog.write(100);  // le bras du servomoteur prend la position de la variable position
        monServo.write(position);
       }

       if (commande == 'd'){direction = 'd';}
       if (direction == 'd'){
        monServod.write(97);  // le bras du servomoteur prend la position de la variable position
        monServog.write(97);  // le bras du servomoteur prend la position de la variable position
        monServo.write(position);
       }

       if (commande == 'g'){direction = 'g';}
       if (direction == 'g'){
        monServod.write(83);  // le bras du servomoteur prend la position de la variable position
        monServog.write(positiong-7);  // le bras du servomoteur prend la position de la variable position
        monServo.write(position);
        }

       if (commande == 'r'){direction = 'r';}
       if (direction == 'r'){
        monServod.write(100);  // le bras du servomoteur prend la position de la variable position
        monServog.write(80);  // le bras du servomoteur prend la position de la variable position
        monServo.write(position);
       }

       if (commande == 's'){direction = 's';}
       if (direction == 's'){
        monServod.write(positiond);  // le bras du servomoteur prend la position de la variable position
        monServog.write(positiong);  // le bras du servomoteur prend la position de la variable position
        monServo.write(88);
       }
       

     }
}
