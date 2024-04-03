#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "catch2/catch.hpp"
#include "declarations.h"
#include <cmath>

TEST_CASE("init function test") {
    particles position(10); // Assuming 10 particles for testing
    int seed = 42; // Arbitrary seed
    double limit = 100; // Arbitrary limit

    init(position, seed, limit);

    // Check if particles are initialized within the limit
    for (const auto& particle : position) {
        REQUIRE(particle.x >= 0.1);
        REQUIRE(particle.x <= limit - 0.1);
        REQUIRE(particle.y >= 0.1);
        REQUIRE(particle.y <= limit - 0.1);
    }
}


TEST_CASE("update function special test") {
    // Creamos un vector de partículas con 5 partículas
    particles position(5);

    // Definimos el límite como 10 para simplificar los cálculos
    double limit = 10.0;

    // Definimos un tamaño de paso para la actualización
    double step = 1.0;

    // Inicializamos las posiciones de las partículas
    position[0].x = 2.0; position[0].y = 2.0; // Partícula en posición (2,2)
    position[1].x = 5.0; position[1].y = 5.0; // Partícula en posición (5,5)
    position[2].x = 8.0; position[2].y = 8.0; // Partícula en posición (8,8)
    position[3].x = 1.0; position[3].y = 1.0; // Partícula en posición (1,1)
    position[4].x = 9.0; position[4].y = 9.0; // Partícula en posición (9,9)

    // Llamamos a la función update para mover las partículas
    update(position, limit, step);

    // Verificamos que las posiciones de las partículas hayan sido actualizadas correctamente
    REQUIRE((position[0].x != 2.0 || position[0].y != 2.0)); // La posición x o y de la partícula 0 debe haber cambiado
    REQUIRE((position[1].x != 5.0 || position[1].y != 5.0)); // La posición x o y de la partícula 1 debe haber cambiado
    REQUIRE((position[2].x != 8.0 || position[2].y != 8.0)); // La posición x o y de la partícula 2 debe haber cambiado
    REQUIRE((position[3].x != 1.0 || position[3].y != 1.0)); // La posición x o y de la partícula 3 debe haber cambiado
    REQUIRE((position[4].x != 9.0 || position[4].y != 9.0)); // La posición x o y de la partícula 4 debe haber cambiado
    
}


TEST_CASE("grid_count function special test") {
    // Creamos un vector de recuentos con 4 cuadrículas
    std::vector<int> counts(4);

    // Creamos un vector de partículas con 4 partículas
    particles position(4);

    // Definimos el límite como 10 para simplificar los cálculos
    double limit = 10.0;

    // Inicializamos las posiciones de las partículas
    position[0].x = 2.0; position[0].y = 2.0; // En la cuadrícula (0,0)
    position[1].x = 7.0; position[1].y = 2.0; // En la cuadrícula (1,0)
    position[2].x = 2.0; position[2].y = 7.0; // En la cuadrícula (0,1)
    position[3].x = 7.0; position[3].y = 7.0; // En la cuadrícula (1,1)

    // Llamamos a la función grid_count para contar las partículas
    grid_count(counts, position, limit);

    // Verificamos que el recuento de cada cuadrícula sea el esperado
    REQUIRE(counts[0] == 1); // Una partícula en la cuadrícula (0,0)
    REQUIRE(counts[1] == 1); // Una partícula en la cuadrícula (1,0)
    REQUIRE(counts[2] == 1); // Una partícula en la cuadrícula (0,1)
    REQUIRE(counts[3] == 1); // Una partícula en la cuadrícula (1,1)
}


TEST_CASE("entropy function test") {
    std::vector<int> counts = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10}; // Sample counts
    int nparticles = 10; // Sample number of particles

    double result = entropy(counts, nparticles);

    // Creamos un vector de recuentos con todos los elementos llenos de ceros
    std::vector<int> counts2(100, 0); // Por ejemplo, un vector de tamaño 100 lleno de ceros

    // Calculamos la entropía
    double result_entropy = entropy(counts2, nparticles);

    // Entropy no debería ser negativa
    REQUIRE(result >= 0.0);

    // Verificamos que la entropía sea igual a 0 cuando el vector de recuentos está lleno de ceros
    REQUIRE(result_entropy == Approx(0.0));
}

TEST_CASE("drop_size function test") {
    particles position(10); // Assuming 10 particles for testing
    double limit = 100; // Arbitrary limit

    // Initialize positions
    for (auto& particle : position) {
        particle.x = 50.0; // Place all particles in the center initially
        particle.y = 50.0;
    }

    double result = drop_size(position, limit);

    // Drop size should be zero when all particles are at the center
    REQUIRE(result == Approx(0.0));
}

TEST_CASE("particle_leak_count function special test") {
    // Creamos un vector de partículas con 5 partículas
    particles position(5);

    // Definimos el límite como 10 para simplificar los cálculos
    double limit = 10.0;

    // Inicializamos las posiciones de las partículas
    // Algunas estarán dentro del límite y otras fuera del límite
    position[0].x = 2.0; position[0].y = 2.0; position[0].valid = true; // Dentro del límite
    position[1].x = 12.0; position[1].y = 12.0; position[1].valid = false; // Fuera del límite
    position[2].x = 5.0; position[2].y = 5.0; position[2].valid = true; // Dentro del límite
    position[3].x = 15.0; position[3].y = 15.0; position[3].valid = false; // Fuera del límite
    position[4].x = 8.0; position[4].y = 8.0; position[4].valid = true; // Dentro del límite

    // Llamamos a la función particle_leak_count para contar las partículas dentro del límite
    int result = particle_leak_count(position, limit);

    // Verificamos que el número de partículas dentro del límite sea el esperado
    REQUIRE(result == 3); // De las 5 partículas, 3 están dentro del límite
}

