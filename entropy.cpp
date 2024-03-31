#include "declarations.h"

int main(){
    int Nmol = 400;
    int LatSize = 64;
    int Nsteps = 100000;
    int SEED = 0;

    particles simul;
    simul.resize(Nmol);

    std::vector<int> Counts(LatSize);

    //Semilla aleatoria 
    srand(time(NULL));
    init(simul, SEED); 
    //Calcular cuentas
    grid_count(Counts, simul);
    //update(simul, Nsteps);

    std::ofstream outfile;
    outfile.open("entropy.txt");
    for(int t = 0; t < Nsteps; t++){
        double Entropy = entropy(Counts, Nmol);

        outfile << t << "\t" << Entropy << "\n";

        update(simul);
        grid_count(Counts, simul);
    }
    outfile.close();



    return 0;
}

