#include "declarations.h"

int main(){
    int Nmol = 500;
    int LatSize = 50;
    int Nsteps = 10000;
    int SEED = 0;
    
    //# of grids for entropy computaion
    const int GridSize = 64;
    //Step size for random walk
    const double Step = 1.0;

    //Variables to compute in time
    double Entropy = 0.0;
    double Distancia = 0.0;
    int PCounts = 0;

    //Vector of particles for normal simulation
    particles simul;
    simul.resize(Nmol);

    //Vector of particles for leak simulation
    particles simul_leak;
    simul_leak.resize(Nmol);

    //1D matrix for grid count
    std::vector<int> Counts(GridSize);

    //Random seed for random walk 
    srand(time(NULL));

    //Initialize particles 
    init(simul, SEED, LatSize); 

    //Initialize leak particles
    init(simul_leak, SEED, LatSize);

    //Files to storage data
    std::ofstream outfile1;
    outfile1.open("entropy.txt");
    std::ofstream outfile2;
    outfile2.open("drop_size.txt");
    std::ofstream outfile3;
    outfile3.open("counts.txt");

    for(int t = 0; t < Nsteps; t++){
        //Compute counts
        grid_count(Counts, simul, LatSize);

        //Compute entropy
        Entropy = entropy(Counts, Nmol);
        outfile1 << t << "\t" << Entropy << "\n";

        //Compute drop size
        Distancia=drop_size(simul, LatSize);
        outfile2 << t << "\t" << Distancia << "\n";

        //Update positions
        update(simul, LatSize, Step);

        //Compute particle count in leak simulation
        PCounts = particle_leak_count(simul_leak, LatSize);
        outfile3 << t << "\t" << PCounts << "\n";

        //Update positions in leak simulation    
        update_leak(simul_leak, LatSize, Step);
    }
    outfile1.close();
    outfile2.close();
    outfile3.close();

    return 0;
}

