#pragma once
#include <cstdlib>

struct Particle{
    //Posiciones de la particula
    double x = 0;
    double y = 0;
    //Particula valida dentro de la simulacion
    //bool valid = true;

    void move(){
        int direction = rand() % 4;
        switch(direction){
            //Abajo
            case 0:
                if (y >= 0){
                    y -= 1;
                }else{
                    y += 1;
                }
                break;

            //Arriba
            case 1:
                if (y <= 100){
                    y += 1;
                }else{
                    y -= 1;
                }
                break;

            //Izquierda
            case 2:
                if (x >= 0){
                    x -= 1;
                }else{
                    x += 1;
                }
                break;

            //Derecha
            case 3:
                if (x <= 100){
                    x += 1;
                }else{
                    x -= 1;
                }
                break;
        }
    }

};