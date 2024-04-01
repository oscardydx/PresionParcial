#include "declarations.h"

int main(){
    int Nmol = 400;
    int LatSize = 20;
    int Nsteps = 100000;
    int SEED = 0;

    int GridSize = 64;

    particles simul;
    simul.resize(Nmol);

    std::vector<int> Counts(GridSize);

    //Semilla aleatoria 
    srand(time(NULL));
    init(simul, SEED, LatSize); 

    //Calcular cuentas iniciales
    grid_count(Counts, simul, LatSize);

    std::ofstream outfile;
    outfile.open("entropy.txt");
    for(int t = 0; t < 5000; t++){

        outfile << t << "\t" << entropy(Counts, Nmol) << "\n";

        update(simul, LatSize);
        grid_count(Counts, simul, LatSize);
    }
    outfile.close();


    return 0;
}

