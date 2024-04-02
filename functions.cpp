#include "declarations.h"
//Initialize particles
void init(particles & position, int seed, double limit){
    int Nparticles = position.size();
    
    std::mt19937 generator(seed);
    std::uniform_real_distribution<double> distribution(0.1, 0.9);
    for(int i = 0; i < Nparticles; i++){
        //10*10 Drop in the midle of the container
        position[i].x = (limit/2) - 5 + 10*distribution(generator);
        position[i].y = (limit/2) - 5 + 10*distribution(generator);
    }
}

//Update positions - normal simulation
void update(particles & position, double limit, double step){
    int Nparticles = position.size();

    for(int i = 0; i < Nparticles; i++){
        position[i].move(limit, step);    
    }
}

//Update positions - leak simulation
void update_leak(particles & position, double limit, double step){
    int Nparticles = position.size();

    for(int i = 0; i < Nparticles; i++){
        position[i].move_leak(limit, step);    
    }
}

//Count number of particles at a square stored in a grid_count matrix
void grid_count(std::vector<int> & counts, particles position, double limit){
    int Nparticles = position.size();
    int Ngrids = std::sqrt(counts.size());

    //Square dimensions
    double Width = static_cast<double>(limit/Ngrids);
    double Height = static_cast<double>(limit/Ngrids);

    //Reestar count 
    counts.assign(counts.size(), 0);

    //Particle components at the (i, j) grid matrix positions
    int ipos = 0;
    int jpos = 0;

    for(int i = 0; i < Nparticles; i++){
        ipos = static_cast<int>(position[i].x/Width);
        jpos = static_cast<int>(position[i].y/Height);
        
        //Check that the particle is inside limits
        if(ipos >= 0 && ipos < Ngrids && jpos >= 0 && jpos < Ngrids){
            counts[ ipos * Ngrids + jpos ] += 1;
        }
    }
}

//Entropy calculation based on the grid_count matrix 
double entropy(std::vector<int> counts, int nparticles){
    double entropy = 0.0;
    int Ngrids = std::sqrt(counts.size());
    std::vector<double> prob(Ngrids*Ngrids, 0.0);
    
    //Probability of finding a particle at any position in the grid 
    for(int ii = 0; ii < Ngrids; ii++){
        for(int jj = 0; jj < Ngrids; jj++){
            prob[ii * Ngrids + jj] = static_cast<double>(counts[ii * Ngrids + jj])/nparticles;
        }
    }

    //Entropy computation
    for(int ii = 0; ii < Ngrids; ii++){
        for(int jj = 0; jj < Ngrids; jj++){
            if(prob[ii*Ngrids + jj] > 0){
                entropy += prob[ii*Ngrids + jj]*std::log(prob[ii*Ngrids + jj]);
            }
        }
    }

    return -entropy;
}

//Compute drop size for a particle configuration
double drop_size(particles position, double limit){
    double Distance = 0.0;
    int Nparticles = position.size();

    //Posicion del centro del contenedor
    double x0 = limit/2;
    double y0 = limit/2;

    double X_=0.0;
    double Y_=0.0;
    
    for(int i = 0; i < Nparticles; i++){
        //Particle position relative to the center of the container
        X_=position[i].x-x0;
        Y_=position[i].y-y0;

        Distance+=(X_*X_)+(Y_*Y_);
    }

    return std::sqrt(Distance/Nparticles);
}

//Compute # of particles inside the container for leak simulation
int particle_leak_count(particles & position, double limit){
    int Nparticles = position.size();

    //Reestart particle count 
    int counts = 0;

    //Count particles inside the container
    for(int i = 0; i < Nparticles; i++){
        if(position[i].valid){
            counts += 1;
        }   
    }
  
    return counts;
}