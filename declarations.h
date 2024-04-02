#include <iostream>
#include <cmath>
#include <vector>
#include <fstream>
#include <ctime>
#include <random>
#include "particle.h"

typedef std::vector<Particle> particles;

void init(particles & position, int seed, double limit);
void update(particles & position, double limit);
void grid_count(std::vector<int> & counts, particles position, double limit);
double entropy(std::vector<int> counts, int nparticles);
double encreaseEntropy(particles position);