/**
 * Implements methods from the Body class.
 * @file body.cpp
*/

#include "body.h"
#include <iostream>


// constructor
Body::Body(std::shared_ptr<Shape> shape, int particle_r, int particle_spacing, double particle_m, double spring_k):
shape(shape), particle_r(particle_r), particle_spacing(particle_spacing), particle_m(particle_m), spring_k(spring_k) {
    initParticles();
}

// initializes a vector of particles
void Body::initParticles() {
    // TODO right now only supporting rectangles

    const int shape_width = shape->bondries.at("right") - shape->bondries.at("left");
    const int shape_height = shape->bondries.at("bottom") - shape->bondries.at("top");

    // n of particles in one row and col
    const int N_row = floor((shape_width + particle_spacing) / (2*particle_r + particle_spacing));
    const int N_col = floor((shape_height + particle_spacing) / (2*particle_r + particle_spacing));

    //std::cout << N_row << " " << N_col << '\n';

    // initializing
    for (int i = 0; i < N_col; i++) {
        std::vector<std::shared_ptr<Particle>> tmp;

        for (int j = 0; j < N_row; j++) {
            const int x = shape->bondries.at("left") + (2*particle_r+particle_spacing) * j;
            const int y = shape->bondries.at("top") + (2*particle_r+particle_spacing) * i;

            tmp.push_back(std::make_shared<Particle>(
                particle_r, x, y, 0, 0, particle_m
            ));
        }
        particles.push_back(tmp);
    }

    // connecting
    const double x0 = particle_spacing + 2*particle_r;
    const double diag_x0 = x0*sqrt(2);
    for (int i = 0; i < N_col; i++) {
        for (int j = 0; j < N_row; j++) {
            std::shared_ptr<Particle> p = particles[i][j];

            // counter clockwise order
            if (j < N_row-1) (*p).connect(particles[i][j+1], x0, spring_k);
            if (j < N_row-1 && i < N_col-1) (*p).connect(particles[i+1][j+1], diag_x0, spring_k);
            if (i < N_col-1) (*p).connect(particles[i+1][j], x0, spring_k);
            if (j > 0 && i < N_col-1) (*p).connect(particles[i+1][j-1], diag_x0, spring_k);
        }
    }
}

// calls draw on particles
void Body::draw(sf::RenderWindow &win) {
    //std::cout << particles.size();
    for (auto &row : particles) {
        //std::cout << "drawing\n";
        for (auto p : row) {
            p->draw(win);
            //std::cout << "drawing\n";
        }
    }
}