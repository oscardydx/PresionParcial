#include <iostream>
#include <cmath>
#include <vector>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <random>

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

typedef std::vector<Particle> particles;

void init(particles & position, int seed);
void update(particles & position);
void grid_count(std::vector<int> & counts, particles & position);
double entropy(std::vector<int> & counts, int nparticles);

int main(){
    int Nmol = 400;
    int LatSize = 64;
    int Nsteps = 100000;
    int SEED = 0;

    particles prueba1;
    prueba1.resize(Nmol);

    std::vector<int> Counts(LatSize);

    //Semilla aleatoria 
    srand(time(NULL));
    init(prueba1, SEED);
    //Calcular cuentas
    grid_count(Counts, prueba1);
    //update(prueba1, Nsteps);

    std::ofstream outfile;
    outfile.open("entropy.txt");
    for(int t = 0; t < Nsteps; t++){
        double Entropy = entropy(Counts, Nmol);

        outfile << t << "\t" << Entropy << "\n";

        update(prueba1);
        grid_count(Counts, prueba1);
    }
    outfile.close();



    return 0;
}

//Incializar posiciones
void init(particles & position, int seed){
    int N = position.size();
    
    std::mt19937 generator(seed);
    std::uniform_real_distribution<double> distribution(0.1, 0.9);
    //std::ofstream outfile;
    //outfile.open("positions.txt");
    for(int jj = 0; jj < N; jj++){
        position[jj].x = 45 + 10*distribution(generator);
        position[jj].y = 45 + 10*distribution(generator);
        //outfile << position[jj].x << "\t" << position[jj].y << "\n"; 
    }
    //outfile.close();
}

//actualizar posiciones - Simulacion
void update(particles & position){
    int N = position.size();

    for(int jj = 0; jj < N; jj++){
        position[jj].move();
    }
}


void grid_count(std::vector<int> & counts, particles & position){
    int Nparticles = position.size();
    int Ngrids = std::sqrt(counts.size());

    double Width = static_cast<double>(100/Ngrids);
    double Height = static_cast<double>(100/Ngrids);

    for(int jj = 0; jj < Nparticles; jj++){
        int xpos = static_cast<int>(position[jj].x/Width);
        int ypos = static_cast<int>(position[jj].y/Height);

        counts[xpos*Ngrids+ypos] += 1;
    }
}

double entropy(std::vector<int> & counts, int nparticles){
    double entropy = 0.0;
    int Ngrids = std::sqrt(counts.size());
    std::vector<double> prob;
    prob.resize(Ngrids*Ngrids);
    
    //Calcular la probabilidad
    for(int ii = 0; ii < Ngrids; ii++){
        for(int jj = 0; jj < Ngrids; jj++){
            prob[ii*Ngrids + jj] = static_cast<double>(counts[ii*Ngrids + jj]/nparticles);
        }

    }
    //Calcular la Entropia
    for(int ii = 0; ii < Ngrids; ii++){
        for(int jj = 0; jj < Ngrids; jj++){
            entropy += prob[ii*Ngrids + jj]*std::log(prob[ii*Ngrids + jj]);
        }
    }

    return entropy;
}