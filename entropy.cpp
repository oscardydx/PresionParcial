#include "declarations.h"

int main(){
////////////////////// PARTE EXTRAER DEL INPUT
    std::ifstream inputFile("input.txt"); 

    if (!inputFile.is_open()) {
        std::cerr << "Error al abrir el archivo input.txt" << std::endl;
        return 1; // Retorna 1 para indicar un error
    }

    std::string line;
    std::string value;

    int Nmol, Nsteps, SEED;
    double LatSize;

    for (int i = 0; i < 4; ++i) { // Itera sobre las 4 líneas del archivo
        std::getline(inputFile, line); // Lee una línea del archivo

        // Utiliza un stringstream para dividir la línea en palabras separadas por espacio
        std::stringstream ss(line);
        ss >> value;

        // Extrae el valor numérico y lo almacena en la variable correspondiente
        switch (i) {
            case 0: // Primera línea: Nmol
                Nmol = std::stoi(value);
                break;
            case 1: // Segunda línea: LatSize
                LatSize = std::stof(value);
                break;
            case 2: // Tercera línea: Nsteps
                Nsteps = std::stoi(value);
                break;
            case 3: // Cuarta línea: SEED
                SEED = std::stoi(value);
                break;
            default:
                break;
        }
    }

    inputFile.close(); // Cierra el archivo después de leer los valores

    //# of grids for entropy computaion
    const int GridSize = 64;
    //Step size for random walk
    const double Step = 1.0;
    //Equilibrium entropy for 64 estates
    const double MaxEntropy = 4.05;


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

    //Random SEED for random walk 
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

    // Latice sice vector
    std::vector<double> LatSize_vec = {20, 40, 60, 80, 100, 120, 140, 160, 180, 200};

    std::ofstream outfile4;
    outfile4.open("latsize.txt");
    // Perform simulation for diferent Lat sizes
    for(long unsigned int ii = 0; ii < LatSize_vec.size(); ii++){

        init(simul, SEED, LatSize_vec[ii]);
        //Time loop
        for(int t = 0; t < Nsteps; t++){
            //Compute counts
            grid_count(Counts, simul, LatSize_vec[ii]);

            //Compute entropy
            Entropy = entropy(Counts, Nmol);

            //Update positions
            update(simul, LatSize_vec[ii], Step);
            
            //Check if equilibrium has been reached
            if(Entropy >= MaxEntropy){
                outfile4 << LatSize_vec[ii]*LatSize_vec[ii] << "\t" << t << "\n";
                break;
            }

            // Dentro del bucle de tiempo
            if (t == Nsteps - 1) { // Si llegamos al final del bucle de tiempo
                std::cout << "El equilibrio no se alcanzó para el tamaño del contenedor: " << LatSize_vec[ii] << std::endl;
            }
        }
    }
    outfile4.close();

    return 0;
}

