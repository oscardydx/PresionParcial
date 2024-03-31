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

    //Calcular cuentas iniciales
    grid_count(Counts, simul);

    std::ofstream outfile;
    outfile.open("entropy.txt");
    for(int t = 0; t < Nsteps; t++){

        outfile << t << "\t" << entropy(Counts, Nmol) << "\n";

        update(simul);
        grid_count(Counts, simul);
    }
    outfile.close();



    return 0;
}

