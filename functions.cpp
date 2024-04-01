#include "declarations.h"
//Incializar posiciones
void init(particles & position, int seed, double limit){
    int Nparticles = position.size();
    
    std::mt19937 generator(seed);
    std::uniform_real_distribution<double> distribution(0.1, 0.9);
    for(int i = 0; i < Nparticles; i++){
        //Gota de 10*10 centrada en la mitad del contenedor
        position[i].x = (limit/2) - 5 + 10*distribution(generator);
        position[i].y = (limit/2) - 5 + 10*distribution(generator);
    }
}

//actualizar posiciones - Simulacion
void update(particles & position, double limit){
    int Nparticles = position.size();

    for(int i = 0; i < Nparticles; i++){
        position[i].move(limit, limit);    
    }
}


void grid_count(std::vector<int> & counts, particles position, double limit){
    int Nparticles = position.size();
    int Ngrids = std::sqrt(counts.size());

    double Width = static_cast<double>(limit/Ngrids);
    double Height = static_cast<double>(limit/Ngrids);

    //Reestablecer # de cuentas
    counts.assign(counts.size(), 0);

    for(int i = 0; i < Nparticles; i++){
        int xpos = static_cast<int>(position[i].x/Width);
        int ypos = static_cast<int>(position[i].y/Height);

        if(xpos >= 0 && xpos < Ngrids && ypos >= 0 && ypos < Ngrids){
            counts[ xpos * Ngrids + ypos ] += 1;
        }
    }
}

double entropy(std::vector<int> counts, int nparticles){
    double entropy = 0.0;
    int Ngrids = std::sqrt(counts.size());
    std::vector<double> prob(Ngrids*Ngrids, 0.0);
    
    //Calcular la probabilidad
    for(int ii = 0; ii < Ngrids; ii++){
        for(int jj = 0; jj < Ngrids; jj++){
            prob[ii * Ngrids + jj] = static_cast<double>(counts[ii * Ngrids + jj])/nparticles;
        }
    }
    //Calcular la Entropia
    for(int ii = 0; ii < Ngrids; ii++){
        for(int jj = 0; jj < Ngrids; jj++){
            if(prob[ii*Ngrids + jj] > 0){
                entropy += prob[ii*Ngrids + jj]*std::log(prob[ii*Ngrids + jj]);
            }
        }
    }

    return -entropy;
}