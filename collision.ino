  unsigned char collision(){    //Implementation de la fonction collision.
  
      if(digitalRead(lcolipteur_pin) == 1 || digitalRead(mlcolipteur_pin) == 1) return (1); //Si un des switch est à NL1, retourne 1.
      if(digitalRead(mrcolipteur_pin) == 1 || digitalRead(rcolipteur_pin) == 1) return (2);
      else return 0;    //Sinon retourne 0.
  
  }
  
  void after_collision(unsigned char sens_collision){   //Implementation de la fonction after_collision.

      if(sens_collision == 1) motor(80,120,0);     //Marche arrière avec la vitesse analogique de 100.
      if(sens_collision == 2) motor(120,80,0);     //Marche arrière avec la vitesse analogique de 100.
      
      delay(1000);          //Pause de 1 seconde.
  
    
  }
