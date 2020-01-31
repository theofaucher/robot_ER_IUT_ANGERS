//    12.4

//mcoef = 1.15;
//lcoef = 1.3;    //<20
//rcoef = 1.3;

//mcoef = 0.95;
//lcoef = 1.25;   //>20
//rcoef = 1.25;

//    13

//mcoef = 1.;
//lcoef = 1.15;    //<20
//rcoef = 1.15;

//mcoef = 0.8;
//lcoef = 1.15;   //>20
//rcoef = 1.15;


#define lsharp_pin 2        //Broches de l'Arduino où sont connectés les capteurs Infrarouge.
#define msharp_pin 3
#define rsharp_pin 4
#define rcolipteur_pin 4    //Broches de l'Arduino où sont connectés les capteurs switch.
#define mrcolipteur_pin 5
#define mlcolipteur_pin 6
#define lcolipteur_pin 7
#define solpteur_pin A0      //Broche de l'Arduino où est connectés la carte électronique de la photodiode.

#define lmotor_pin 10        //Broche de l'Arduino du moteur gauche.
#define rmotor_pin 9       //Broche de l'Arduino du moteur droit.

#define lsens_moteur 11     //Broche de l'Arduino pour le sens de rotation du moteur gauche.
#define rsens_moteur 12     //Broche de l'Arduino pour le sens de rotation du moteur droit.

#define jack_connector 2    //Broches de l'Arduino où est connecté le port jack.


#define temps_marche_arriere 250

unsigned char collision();  //Prototype de la fonction after_collision aucun paramètre d'entrée et un paramètre de sortie.
void after_collision(unsigned char sens_collision);     //Prototype de la fonction after_collision aucun paramètre d'entrée et de sortie.
void motor(unsigned char l_speed, unsigned char r_speed, boolean sens); //Prototype de la fonction after_collision aucun paramètre de sortie et 3 paramètres d'entrées: vitesse de rotation du moteur droit, gauche, ainsi que le sens marche avant ou arrière.
void stop_motor(unsigned char moy_speed, short unsigned int temps);     //Prototype de la fonction after_collision aucun paramètre de sortie et 2 paramètres de sorties: Vitesse moyenne des moteurs ainsi que le temps au quel la vitesse est maintenue.

float mcoef;    //Coefficient multiplicateur de la vitesse moyenne.
float rcoef;    //Coefficient multiplicateur de la vitesse de la roue droite.
float lcoef;    //Coefficient multiplicateur de la vitesse de la roue gauche.

boolean debut_piste = false;

void setup() {  //Fonction d'initialisation.

  Serial.begin(9600);   //Instruction pour iniatiliser la communication série avec l'Arduino.

}

void loop() {   //Fonction infini
  
    int mdistance = min(1692.2 * pow(analogRead(msharp_pin),-0.929),40);    //Converti la valeur analogique en centimètre.
    //Serial.println(mdistance);
    int ldistance = min(1692.2 * pow(analogRead(lsharp_pin),-0.929),40);    //
    Serial.println(ldistance);
    int rdistance = min(1692.2 * pow(analogRead(rsharp_pin),-0.929),40);//min(1692.2 * pow(min(analogRead(rsharp_pin), 480),-0.929),40);    //
    //Serial.println(rdistance);
    
    if(mdistance <= 20){ //On change la valeur des coeficients en fonctions de la distance calculée.
      
      mcoef = 1.1;
      lcoef = 1.3;//1.05;    //12.4V
      rcoef = 1.3;//1.05;
      /*mcoef = 0.7;
      lcoef = 0.4;
      rcoef = 0.4;
       mcoef = 0.9;
       lcoef = 1.15;
       rcoef = 1.15;
      /*mcoef = 1.;
      lcoef = 1.05;    //<20
      rcoef = 1.05;*/ 
    
    }
    if(mdistance > 20){

       mcoef = 1.3;
       lcoef = 1.15;//1.05;  //12.4V
       rcoef = 1.15;//1.05;
       /*mcoef = 1;
       lcoef = 0.4;
       rcoef = 0.4;
       mcoef = 0.9;
       lcoef = 1.1;
       rcoef = 1.1;
      mcoef = 0.8;
      lcoef = 1.1;   //>20
      rcoef = 1.1;*/
      
    }

    int moy_speed = mdistance * mcoef;              //Calcul des vitesses.
    int l_speed = (rdistance * lcoef) + moy_speed;
    int r_speed = (ldistance * rcoef) + moy_speed;
    /*Serial.println("Droit");
    Serial.println(r_speed);
    Serial.println("Gauche");
    Serial.println(l_speed);*/


    if (mdistance <= 9 && ldistance <= 9 && rdistance <= 9){
      
      motor(100,100,0);
      delay(500);
      
    }
    
    if (mdistance <= 11)
    {

        if(ldistance <  rdistance)
        {

            motor(90,120,0);
            //motor(120,80,0);
            delay(temps_marche_arriere);
          
        }

        if(rdistance < ldistance)
        {

            motor(120,90,0);
            //motor(80,120,0);
            delay(temps_marche_arriere);
          
        }
      
    }
    


    
    motor(min(l_speed,200),min(r_speed,200),1);             //Appel de la fonction motor, ainsi que la vitesse du moteur droit et gauche ne peuvent pas dépasser au dessus de 200 (Valeur analogique).
    
    while(digitalRead(jack_connector) == 0){                //Tant que le jack est branché --> appel de la fonction wait_start.
      
      wait_start();
    
    }

    if(debut_piste == 0){

      motor(100/*75*/,100,1);//100
      delay(425);//450
      debut_piste = true;
    }
    
    while(collision() == 1) after_collision(1);              //Tant qu'un switch est à NL1 --> appel de la fonction after_collision.
    while(collision() == 2) after_collision(2);              //Tant qu'un switch est à NL1 --> appel de la fonction after_collision.
    while(digitalRead(solpteur_pin) == 1){      //Tant que la valeur digital est à 1, appel la fonction wait_start.
      
       delay(100);//200
          
       if(digitalRead(solpteur_pin) == 1)     //Tant que la valeur digital est à 1, appel la fonction wait_start.
       {
       
          motor(150,150,0);
          delay(150);
          while(1) wait_start();         
      
       }
          
    }
    

}
