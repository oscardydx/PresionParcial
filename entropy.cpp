#include "declarations.h"

int main(){
    int Nmol = 500;
    int LatSize = 50;
    int Nsteps = 50000;
    int SEED = 0;

    int GridSize = 64;

    double Entropy = 0.0;
    double Distancia = 0.0;
    int PCounts = 0;

    particles simul;
    simul.resize(Nmol);

    particles simul_leak;
    simul_leak.resize(Nmol);

    std::vector<int> Counts(GridSize);

    //Semilla aleatoria 
    srand(time(NULL));

    //Iinicializar particulas 
    init(simul, SEED, LatSize); 

    //Inicializar pariticulas con leaks
    init(simul_leak, SEED, LatSize);

    std::ofstream outfile1;
    outfile1.open("entropy.txt");

    std::ofstream outfile2;
    outfile2.open("increseEntropy.txt");

    std::ofstream outfile3;
    outfile3.open("counts.txt");

    for(int t = 0; t < Nsteps; t++){
        //Calcular cuentas
        grid_count(Counts, simul, LatSize);

        //Obtener la entropia
        Entropy = entropy(Counts, Nmol);
        outfile1 << t << "\t" << Entropy << "\n";

        //Obtener obtener tamano
        Distancia=drop_size(simul, LatSize);
        outfile2 << t << "\t" << Distancia << "\n";

        //Actualizar posiciones
        update(simul, LatSize);

        //Obtener cuenta de particulas en simulacion con un agujero
        PCounts = particle_leak_count(simul_leak, LatSize);
        outfile3 << t << "\t" << PCounts << "\n";

        //Actualizar posiciones    
        update_leak(simul_leak, LatSize);
    }
    outfile1.close();
    outfile2.close();
    outfile3.close();

    return 0;
}

