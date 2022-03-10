/*
   Code 23 - Edurobot.ch, destiné à l'Arduino
   Objectif : Faire bouger le bras d'un servomoteur dans un sens puis dans l'autre, indéfiniment
*/

//*****EN-TÊTE DECLARATIF*****
#include <Servo.h>  // on inclut la bibliothèque pour piloter un servomoteur

Servo monServo;  // on crée l'objet monServo
char commande = ' ';
int position = 88;
char direction = ' ';

void setup(){  
    Serial.begin(9600);
    Serial.println("Introduire p = prendre la balle, m = monter la tige, a = avancer, d = tourne a droit, g = tourne a gauche, r = reculer");
  //Servomoteur
    monServo.attach(10); // on définit le Pin utilisé par le servomoteur
    monServo.write(position); //Commence en 90 pour ne pas bouger et avoir une force dans l'axe
  //Moteurs CC
     //Configuration du Canal A
    pinMode(12, OUTPUT); // Broche Arduino réservée pour le sens de rotation du moteur A gauche
    pinMode(9, OUTPUT); // Broche Arduino réservée pour le freinage du moteur A
    pinMode(13, OUTPUT); // Broche Arduino réservée pour le sens de rotation du moteur B droit
    pinMode(8, OUTPUT); // Broche Arduino réservée pour le freinage du moteur B
}

void loop(){
   if (Serial.available() > 0) {
    commande = Serial.read();
    monServo.write(position);
      if (commande == 'p'){
        // on crée une impulsion petite dans une direction
        position = 82;
        monServo.write(position);  // le bras du servomoteur prend la position de la variable position
        delay(500);  // on attend 10 millisecondes
        commande = ' ';
        position = 88;
      }

      if (commande == 'm'){
        // on crée une impulsion petite dans une autre direction
        position = 93;
        monServo.write(position);  // le bras du servomoteur prend la position de la variable position
        delay(500);  // on attend 5 millisecondes
        commande = ' ';
        position = 88;
        }

       if (commande == 'a'){direction = 'a';}
       if (direction == 'a'){
         digitalWrite(12, HIGH); // Le moteur A tourne dans le sens normal
         digitalWrite(9, LOW); // Désactivation du frein moteur A
         analogWrite(3, 127); // Vitesse maximale pour le moteur A
         
         digitalWrite(13, LOW); // Le moteur B tourne dans le sens normal
         digitalWrite(8, LOW); // Désactivation du frein moteur B
         analogWrite(11, 127); // Demie vitesse pour le moteur B
       }

       if (commande == 'd'){direction = 'd';}
       if (direction == 'd'){
         digitalWrite(12, HIGH); // Le moteur A tourne dans le sens normal
         digitalWrite(9, LOW); // Désactivation du frein moteur A
         analogWrite(3, 127); // Vitesse maximale pour le moteur A
         
         digitalWrite(13, LOW); // Le moteur B tourne est arrêté
         digitalWrite(8, LOW); // Désactivation du frein moteur B
         analogWrite(11, 0); // Demie vitesse pour le moteur B
       }

       if (commande == 'g'){direction = 'g';}
       if (direction == 'g'){
         digitalWrite(12, HIGH); // Le moteur A tourne est arrêté
         digitalWrite(9, LOW); // Désactivation du frein moteur A
         analogWrite(3, 0); // Vitesse maximale pour le moteur A
         
         digitalWrite(13, LOW); // Le moteur B tourne dans le sens normal
         digitalWrite(8, LOW); // Désactivation du frein moteur B
         analogWrite(11, 127); // Demie vitesse pour le moteur B
       }

       if (commande == 'r'){direction = 'r';}
       if (direction == 'r'){
         digitalWrite(12, LOW); // Le moteur A tourne dans le sens inverse
         digitalWrite(9, LOW); // Désactivation du frein moteur A
         analogWrite(3, 127); // Vitesse maximale pour le moteur A
         
         digitalWrite(13, HIGH); // Le moteur B tourne dans le sens inverse
         digitalWrite(8, LOW); // Désactivation du frein moteur B
         analogWrite(11, 127); // Demie vitesse pour le moteur B
       }
      }
}
