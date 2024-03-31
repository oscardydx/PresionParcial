#pragma once
#include <iostream>
#include <cmath>
#include <vector>
#include <fstream>
#include <ctime>
#include <random>
#include "particle.hpp"

typedef std::vector<Particle> particles;

void init(particles & position, int seed);
void update(particles & position);
void grid_count(std::vector<int> & counts, particles & position);
double entropy(std::vector<int> & counts, int nparticles);