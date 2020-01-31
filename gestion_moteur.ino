void motor(unsigned char l_speed, unsigned char r_speed, boolean sens){   //Implementation de la fonction motor.
  

    if(sens == 0) {     //Si sens = 0 alors marche arrière.

        digitalWrite(lsens_moteur, HIGH); digitalWrite(rsens_moteur, LOW);   //Défini le sens de rotation du moteur droit.
        //digitalWrite(lsens_moteur, LOW); digitalWrite(rsens_moteur, HIGH);
      
    }

    if(sens == 1) {     //Si sens = 0 alors marche avant

        digitalWrite(lsens_moteur, LOW); digitalWrite(rsens_moteur, HIGH);    //Défini le sens de rotation du moteur gauche.
        //digitalWrite(lsens_moteur, HIGH); digitalWrite(rsens_moteur, LOW);
    }
    
    analogWrite(lmotor_pin, /*max(*/l_speed + 7/*, 80)*/);   //Règle la vitesse analogique du moteur gauche.
    analogWrite(rmotor_pin, /*max(*/r_speed /*+ 5*//*++ 10*//*, 80)*/);   //Règle la vitesse analogique du moteur droit.

}

void stop_motor(unsigned char moy_speed, short unsigned int temps){   //Implementation de la fonction stop_moteur.

  while(moy_speed > 100)    //Arrêt progressif de la vitesse des moteurs.
  {
    
    Serial.println(moy_speed);
    moy_speed --;
    motor(moy_speed,moy_speed, 1);
    delay(temps);
   
  }

}

void wait_start(void){    //Implementation de la fonction wait_start

    analogWrite(lmotor_pin, 0);   //Arrête le moteur gauche.
    analogWrite(rmotor_pin, 0);   //Arrête le moteur droit.

}
