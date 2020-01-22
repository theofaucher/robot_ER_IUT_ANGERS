#define lsharp_pin 2        //Broches de l'Arduino où sont connectés les capteurs Infrarouge.
#define msharp_pin 3        //Tu n'est   pas beau :p
#define rsharp_pin 5
#define rcolipteur_pin 4    //Broches de l'Arduino où sont connectés les capteurs switch.
#define mrcolipteur_pin 5
#define mlcolipteur_pin 6
#define lcolipteur_pin 7
#define solpteur_pin 0      //Broche de l'Arduino où est connectés la carte électronique de la photodiode.

#define lmotor_pin 9        //Broche de l'Arduino du moteur gauche.
#define rmotor_pin 10       //Broche de l'Arduino du moteur droit.

#define lsens_moteur 11     //Broche de l'Arduino pour le sens de rotation du moteur gauche.
#define rsens_moteur 12     //Broche de l'Arduino pour le sens de rotation du moteur droit.

#define jack_connector 2    //Broches de l'Arduino où est connecté le port jack.

unsigned char collision();  //Prototype de la fonction after_collision aucun paramètre d'entrée et un paramètre de sortie.
void after_collision(unsigned char sens_collision);     //Prototype de la fonction after_collision aucun paramètre d'entrée et de sortie.
void motor(unsigned char l_speed, unsigned char r_speed, boolean sens); //Prototype de la fonction after_collision aucun paramètre de sortie et 3 paramètres d'entrées: vitesse de rotation du moteur droit, gauche, ainsi que le sens marche avant ou arrière.
void stop_motor(unsigned char moy_speed, short unsigned int temps);     //Prototype de la fonction after_collision aucun paramètre de sortie et 2 paramètres de sorties: Vitesse moyenne des moteurs ainsi que le temps au quel la vitesse est maintenue.

float mcoef;    //Coefficient multiplicateur de la vitesse moyenne.
float rcoef;    //Coefficient multiplicateur de la vitesse de la roue droite.
float lcoef;    //Coefficient multiplicateur de la vitesse de la roue gauche.

void setup() {  //Fonction d'initialisation.

  Serial.begin(9600);   //Instruction pour iniatiliser la communication série avec l'Arduino.

}

void loop() {   //Fonction infini
  
    int mdistance = min(1692.2 * pow(analogRead(msharp_pin),-0.929),40);    //Converti la valeur analogique en centimètre.
    Serial.println(mdistance);
    int ldistance = min(1692.2 * pow(analogRead(lsharp_pin),-0.929),40);    //
    Serial.println(ldistance);
    int rdistance = min(1692.2 * pow(analogRead(rsharp_pin),-0.929),40);//min(1692.2 * pow(min(analogRead(rsharp_pin), 480),-0.929),40);    //
    Serial.println(rdistance);

    int moy_speed = mdistance * mcoef;              //Calcul des vitesses.
    int l_speed = (ldistance * lcoef) + moy_speed;
    int r_speed = (rdistance * rcoef) + moy_speed;
    //Serial.println(r_speed);

    if(mdistance < 20){ //On change la valeur des coeficients en fonctions de la distance calculée.
      
      /*mcoef = 1.3;
      lcoef = 1.45;
      rcoef = 1.45;*/
      /*mcoef = 0.7;
      lcoef = 0.4;
      rcoef = 0.4;*/
       mcoef = 0.9;
       lcoef = 1.15;
       rcoef = 1.15;
    
    }
    if(mdistance > 20){

       /*mcoef = 1.1;
       lcoef = 1.4;
       rcoef = 1.4;*/
       /*mcoef = 1;
       lcoef = 0.4;
       rcoef = 0.4;*/
       mcoef = 0.9;
       lcoef = 1.1;
       rcoef = 1.1;
      
    }

    /*if (mdistance <= 8 && ldistance <= 8 && rdistance <= 8){
      
      motor(100,100,0);
      delay(500);
      
    }*/
    
    if (mdistance <= 11)
    {

        if(ldistance <  rdistance)
        {

            motor(120,80,0);
            delay(450);
          
        }

        if(rdistance < ldistance)
        {

            motor(80,120,0);
            delay(450);
          
        }
      
    }
    


    
    motor(min(l_speed,200),min(r_speed,200),1);             //Appel de la fonction motor, ainsi que la vitesse du moteur droit et gauche ne peuvent pas dépasser au dessus de 200 (Valeur analogique).
    while(digitalRead(jack_connector) == 0) wait_start();   //Tant que le jack est branché --> appel de la fonction wait_start.
    while(collision() == 1) after_collision(1);              //Tant qu'un switch est à NL1 --> appel de la fonction after_collision.
    while(collision() == 2) after_collision(2);              //Tant qu'un switch est à NL1 --> appel de la fonction after_collision.
    while(analogRead(solpteur_pin) > 900) wait_start();     //NE FONCTIONNE PAS TOUT LE TEMPS // Tant que la valeur analogique du capteur photodiode est suppérieur à 900, appel la fonction wait_start.

}
