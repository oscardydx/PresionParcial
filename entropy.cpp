#include "declarations.hpp"

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

