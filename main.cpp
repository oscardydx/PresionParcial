#include <iostream>
#include <cmath>
#include <vector>
#include <fstream>
#include <cstdlib>
#include <ctime>

struct Particle{
    double x = 11;
    double y = 11;

    void move(){
        int direction = rand() % 4;
        //Abajo
        if(direction == 0){ y -= 0.5; }
        //Arriba
        if(direction == 1){ y += 0.5; }
        //Derecha
        if(direction == 2){ x -= 0.5; }
        //Izquierda
        if(direction == 3){ x += 0.5; }
    }

};

typedef std::vector<Particle> particles;

//void init(particles & position);
void update(particles & position, double time, double dt);

int main(){
    particles prueba1;
    prueba1.resize(3);

    //Semilla aleatoria 
    srand(time(NULL));
    update(prueba1, 10.0, 1.0);

    //Imprimir posicion de las particulas en el tiempo dado
    std::ofstream outfile;
    outfile.open("data.txt");
    for(int jj = 0; jj < prueba1.size(); jj++){
            outfile << prueba1[jj].x << "\t" << prueba1[jj].y << "\n";
        }
    outfile.close();

    return 0;
}
//actualizar posiciones
void update(particles & position, double time, double dt){
    int Nsteps = time/dt;
    int N = position.size();

    for(int ii = 0; ii < Nsteps; ii++){
        for(int jj = 0; jj < N; jj++){
            position[jj].move();
        }
    }
}
