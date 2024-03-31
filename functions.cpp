#include "declarations.h"
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