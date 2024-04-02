#pragma once
#include <cstdlib>

struct Particle{
    //Particle positions
    double x = 0;
    double y = 0;

    //To check if the particle is inside the limits 
    bool valid = true; 

    //Move particle inside the limits 
    void move(double size, double step){
        int direction = rand() % 4;

        switch(direction){
            //Down
            case 0:
                if (y > step){
                    y -= step;
                }else{
                    y += step;
                }
                break;

            //Up
            case 1:
                if (y < size-step){
                    y += step;
                }else{
                    y -= step;
                }
                break;

            //Left
            case 2:
                if (x > step){
                    x -= step;
                }else{
                    x += step;
                }
                break;

            //Right
            case 3:
                if (x < size-step){
                    x += step;
                }else{
                    x -= step;
                }
                break;
        }
    }

    //Move particle in leak simulation
    void move_leak(double size, double step){

        //Check if the particle is out of the container
        if (!valid) {
            return;
        }
        int direction = rand() % 4;

        switch(direction){
            //Down
            case 0:
                if (y > 0) { 
                    y -= step;
                    //Remove the particle if it is in a gap of 10 units in the middle of the lower edge
                    if (y < 0 && (size/2)-5 && (size/2)+5) {
                        valid = false;
                    }
                } else {
                    y += step;
                }
                break;

            //Up
            case 1:
                if (y < size-step){
                    y += step;
                }else{
                    y -= step;
                }
                break;

            //Left
            case 2:
                if (x > step){
                    x -= step;
                }else{
                    x += step;
                }
                break;

            //Right
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

