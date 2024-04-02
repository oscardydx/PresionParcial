#pragma once
#include <cstdlib>

struct Particle{
    //Posiciones de la particula
    double x = 0;
    double y = 0;

    //Verificar particula dentro de los limites
    bool valid = true; 

    //Mover la particula verificando que no salga de los limites 
    void move(double size, double step){
        int direction = rand() % 4;

        switch(direction){
            //Abajo
            case 0:
                if (y > step){
                    y -= step;
                }else{
                    y += step;
                }
                break;

            //Arriba
            case 1:
                if (y < size-step){
                    y += step;
                }else{
                    y -= step;
                }
                break;

            //Izquierda
            case 2:
                if (x > step){
                    x -= step;
                }else{
                    x += step;
                }
                break;

            //Derecha
            case 3:
                if (x < size-step){
                    x += step;
                }else{
                    x -= step;
                }
                break;
        }
    }

    //Mover la particula con un agujero en el contenedor
    void move_leak(double size, double step){

        // si la particula esta afuera no hacer nada
        if (!valid) {
            return;
        }
        int direction = rand() % 4;

        switch(direction){
            //Abajo
            case 0:
                //Sacar la particula si se encuentra en un hueco de 10 unidades en la mitad del borde inferior
                if (y > 0) { 
                    y -= step;
                    // Verificar si la particula salio del limite
                    if (y < 0 && (size/2)-5 && (size/2)+5) {
                        valid = false;
                    }
                } else {
                    y += step;
                }
                break;

            //Arriba
            case 1:
                if (y < size-step){
                    y += step;
                }else{
                    y -= step;
                }
                break;

            //Izquierda
            case 2:
                if (x > step){
                    x -= step;
                }else{
                    x += step;
                }
                break;

            //Derecha
            case 3:
                if (x < size-step){
                    x += step;
                }else{
                    x -= step;
                }
                break;
        }
    }
};

