#pragma once
#include <cstdlib>

struct Particle{
    //Posiciones de la particula
    double x = 0;
    double y = 0;

    //Verificar particula dentro de los limites
    bool out = false; 

    //Mover la particula verificando que no salga de los limites 
    void move(double xmax, double ymax){
        int direction = rand() % 4;
        switch(direction){
            //Abajo
            case 0:
                if (y > 1){
                    y -= 1;
                }else{
                    y += 1;
                }
                break;

            //Arriba
            case 1:
                if (y < ymax-1){
                    y += 1;
                }else{
                    y -= 1;
                }
                break;

            //Izquierda
            case 2:
                if (x > 1){
                    x -= 1;
                }else{
                    x += 1;
                }
                break;

            //Derecha
            case 3:
                if (x < xmax-1){
                    x += 1;
                }else{
                    x -= 1;
                }
                break;
        }
    }

    //Mover la particula con un agujero en el contenedor
    void move_leak(double xmax, double ymax){

        // si la particula esta afuera no hacer nada
        if (out) {
            return;
        }

        int direction = rand() % 4;
        switch(direction){
            //Abajo
            case 0:
                //Sacar la particula si se encuentra en un hueco de 10 unidades en la mitad del borde inferior
                if (y > 0) { 
                    y -= 1;
                    // Verificar si la particula salio del limite
                    if (y < 0 && x > (xmax/2)-5 && x < (xmax/2)+5) {
                        out = true;
                    }
                } else {
                    y += 1;
                }
                break;

            //Arriba
            case 1:
                if (y < ymax-1){
                    y += 1;
                }else{
                    y -= 1;
                }
                break;

            //Izquierda
            case 2:
                if (x > 1){
                    x -= 1;
                }else{
                    x += 1;
                }
                break;

            //Derecha
            case 3:
                if (x < xmax-1){
                    x += 1;
                }else{
                    x -= 1;
                }
                break;
        }
    }
};

