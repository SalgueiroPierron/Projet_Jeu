#include "main.h"

//s_kart_t new_kart_empty(){
//  return NULL;
//}

voiture_t new_voiture(Sprite s, int r, double v){
  voiture_t newvoiture;
  newvoiture = (voiture_t)malloc(sizeof(s_kart_t));
  newvoiture->sprite = s;
  newvoiture->rotation = r;
  newvoiture->vitesse = v;

  return newvoiture;
}

int is_empty(voiture_t voiture){
  return voiture == NULL;
}

Sprite sprite(voiture_t voiture){
  return voiture->sprite;
}

int rotation(voiture_t voiture){
  return voiture->rotation;
}

double vitesse(voiture_t voiture){
  return voiture->vitesse;
}

void change_sprite(voiture_t* voiture, Sprite new_sprite){
  voiture_t tmp = *voiture;
  tmp->sprite = new_sprite;
}

void change_rotation(voiture_t* voiture,double new_rotation){
  voiture_t tmp = *voiture;
  tmp->rotation = new_rotation;
}

void add_rotation(voiture_t* voiture, double rotat){
  voiture_t tmp = *voiture;
  tmp->rotation += rotat;
  if(tmp->rotation >= 36)
	tmp->rotation = 0;
  if(tmp->rotation < 0)
	tmp->rotation = 35;
  *voiture = tmp;
}

void change_vitesse(voiture_t* voiture, double new_vitesse){
  voiture_t tmp = *voiture;
  tmp->vitesse = new_vitesse;
}

void add_vitesse(voiture_t* voiture, double vitesse) {
  voiture_t tmp = *voiture;
  tmp->vitesse += vitesse;
}

void multiply_vitesse(voiture_t* voiture, double accel){
  voiture_t tmp = *voiture;
  tmp->vitesse *= accel;
}

void accelerer(voiture_t* voiture){
  if(vitesse(*voiture) < 1){
    add_vitesse(voiture, 1);
  }
  else{
    if(vitesse(*voiture) < 4){
    	multiply_vitesse(voiture, 1.02);
    }
    else{
        change_vitesse(voiture, 4);
    }
  }
}

void avancer(double* vx, double* vy, voiture_t* voiture){  
  
  /*if (rotation(*voiture) == 0){
	*vy = -vitesse(*voiture);
	}*/

  if (rotation(*voiture) >= 0 && rotation(*voiture) < 9) {
    *vy -= cos((rotation(*voiture)*10)*(M_PI/180));
    *vx += sin((rotation(*voiture)*10)*(M_PI/180));

    /*double vectx = (rotation(*voiture)/90);
    *vx = vitesse(*voiture)*vectx;
    double tmp = rotation(*voiture) - 90;
    double vecty = (ABS(tmp)/90);
    *vy = -(vitesse(*voiture)*vecty);*/
  }

  /* if (rotation(*voiture) == 90){
	*vx = vitesse(*voiture);
	}*/


  if (rotation(*voiture) >= 9 && rotation(*voiture) < 18){
    *vy -= cos((rotation(*voiture)*10)*(M_PI/180));
    *vx = sin((rotation(*voiture)*10)*(M_PI/180));

    /* double vecty = ((rotation(*voiture)-90)/90);
    *vy = vitesse(*voiture)*vecty;
    double tmp = rotation(*voiture) - 180;
    double vectx = (ABS(tmp)/90);
    *vx = vitesse(*voiture)*vectx;*/
  }

  /*if (rotation(*voiture) == 180){
	*vy = vitesse(*voiture);
	}*/

  if (rotation(*voiture) >= 18 && rotation(*voiture) < 27){   
    *vy -= cos((rotation(*voiture)*10)*(M_PI/180));
    *vx += sin((rotation(*voiture)*10)*(M_PI/180));


    /*double vecty = ((rotation(*voiture)-180)/90);
    *vy = vitesse(*voiture)*vecty;
    double tmp = rotation(*voiture) - 270;
    double vectx = (ABS(tmp)/90);
    *vx = -(vitesse(*voiture)*vectx);*/
  }

  /*if (rotation(*voiture) == 270){
	*vx = -vitesse(*voiture);
	}*/

  if (rotation(*voiture) >= 27 && rotation(*voiture) < 36){
    *vy -= cos((rotation(*voiture)*10)*(M_PI/180));
    *vx += sin((rotation(*voiture)*10)*(M_PI/180));

    /*double vectx = ((rotation(*voiture)-270)/90);
    *vx = -(vitesse(*voiture)*vectx);
    double tmp = rotation(*voiture) - 360;
    double vecty = (ABS(tmp)/90);
    *vy = -(vitesse(*voiture)*vecty);*/
  }

  *vy *= vitesse(*voiture);
  *vx *= vitesse(*voiture);
}

void reculer(double *vx, double *vy, voiture_t* voiture){

  /*if(vitesse(*voiture) > -1){
    add_vitesse(voiture, -1);
  }
  else{
    if(vitesse(*voiture) > -2){
    	accelerer(voiture, 1.02);
    }
    else{
        change_vitesse(voiture, -2);
    }
  }
  
  //if (rotation(*voiture) == 0){
//	*vy = -vitesse(*voiture);
//	}

  if (rotation(*voiture) >= 0 && rotation(*voiture) < 9) {
    *vy += cos((rotation(*voiture)*10)*(M_PI/180));
    *vx -= sin((rotation(*voiture)*10)*(M_PI/180));

   // double vectx = (rotation(*voiture)/90);
   // *vx = vitesse(*voiture)*vectx;
   // double tmp = rotation(*voiture) - 90;
   // double vecty = (ABS(tmp)/90);
   // *vy = -(vitesse(*voiture)*vecty);
  }

// if (rotation(*voiture) == 90){
//	*vx = vitesse(*voiture);
//	}


  if (rotation(*voiture) >= 9 && rotation(*voiture) < 18){
    *vy += cos((rotation(*voiture)*10)*(M_PI/180));
    *vx -= sin((rotation(*voiture)*10)*(M_PI/180));

   // double vecty = ((rotation(*voiture)-90)/90);
   // *vy = vitesse(*voiture)*vecty;
   // double tmp = rotation(*voiture) - 180;
   // double vectx = (ABS(tmp)/90);
   // *vx = vitesse(*voiture)*vectx;
  }

  //if (rotation(*voiture) == 180){
//	*vy = vitesse(*voiture);
//	}

  if (rotation(*voiture) >= 18 && rotation(*voiture) < 27){   
    *vy += cos((rotation(*voiture)*10)*(M_PI/180));
    *vx -= sin((rotation(*voiture)*10)*(M_PI/180));


    //double vecty = ((rotation(*voiture)-180)/90);
    //*vy = vitesse(*voiture)*vecty;
    //double tmp = rotation(*voiture) - 270;
    //double vectx = (ABS(tmp)/90);
    //*vx = -(vitesse(*voiture)*vectx);
  }

 //if (rotation(*voiture) == 270){
//	*vx = -vitesse(*voiture);
//	}

  if (rotation(*voiture) >= 27 && rotation(*voiture) < 36){
    *vy += cos((rotation(*voiture)*10)*(M_PI/180));
    *vx -= sin((rotation(*voiture)*10)*(M_PI/180));

    //double vectx = ((rotation(*voiture)-270)/90);
    //*vx = -(vitesse(*voiture)*vectx);
    //double tmp = rotation(*voiture) - 360;
    //double vecty = (ABS(tmp)/90);
    //*vy = -(vitesse(*voiture)*vecty);
  }

  *vy *= ABS(vitesse(*voiture));
  *vx *= ABS(vitesse(*voiture));*/
}

void pivoter(voiture_t* voiture, int rotat, bool mouv){
  SDL_Delay(8);
  if(mouv){
    if(rotat == 0){      
      add_rotation(voiture, -1);
    }
    else{
      add_rotation(voiture, 1);
    }
  }
}

void passiv(double* vx, double* vy, voiture_t* voiture){
  if(vitesse(*voiture) > 0){
    add_vitesse(voiture, -0.2);
    avancer(vx,vy,voiture);
  }

  if(vitesse(*voiture) < 0){
    add_vitesse(voiture, 0.2);
    reculer(vx,vy,voiture);
  }

  if(vitesse(*voiture) < 0.2 && vitesse(*voiture) > -0.2){
    change_vitesse(voiture, 0);
  }

}
