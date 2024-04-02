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
        double step = 1;

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
                if (y < ymax-step){
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
                if (x < xmax-step){
                    x += step;
                }else{
                    x -= step;
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
        double step = 1;

        switch(direction){
            //Abajo
            case 0:
                //Sacar la particula si se encuentra en un hueco de 10 unidades en la mitad del borde inferior
                if (y > 0) { 
                    y -= step;
                    // Verificar si la particula salio del limite
                    if (y < 0 && x > (xmax/2)-5 && x < (xmax/2)+5) {
                        out = true;
                    }
                } else {
                    y += step;
                }
                break;

            //Arriba
            case 1:
                if (y < ymax-step){
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
                if (x < xmax-step){
                    x += step;
                }else{
                    x -= step;
                }
                break;
        }
    }
};

