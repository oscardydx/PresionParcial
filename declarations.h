//COMENTARIO DE PRUEBA 
#include <iostream>
#include <cmath>
#include <vector>
#include <fstream>
#include <ctime>
#include <random>
#include <sstream>
#include "particle.h"

typedef std::vector<Particle> particles;

void init(particles & position, int seed, double limit);
void update(particles & position, double limit, double step);
void update_leak(particles & position, double limit, double step);
void grid_count(std::vector<int> & counts, particles position, double limit);
double entropy(std::vector<int> counts, int nparticles);
double drop_size(particles position, double limit);
int particle_leak_count(particles & position, double limit);