/**
 * Implements methods from the Body class.
 * @file body.cpp
*/

#include "body.h"
#include <iostream>


// constructor
Body::Body(std::shared_ptr<Shape> shape, int particle_r, int particle_spacing, double particle_m):
shape(shape), particle_r(particle_r), particle_spacing(particle_spacing), particle_m(particle_m) {
    initParticles();
}

void Body::initParticles() {
    // TODO right now only supporting rectangles

    const int shape_width = shape->bondries.at("right") - shape->bondries.at("left");
    const int shape_height = shape->bondries.at("bottom") - shape->bondries.at("top");

    // n of particles in one row and col
    const int N_row = floor((shape_width + particle_spacing) / (2*particle_r + particle_spacing));
    const int N_col = floor((shape_height + particle_spacing) / (2*particle_r + particle_spacing));

    //std::cout << N_row << " " << N_col << '\n';

    for (int i = 0; i < N_col; i++) {
        std::vector<std::shared_ptr<Particle>> tmp;

        for (int j = 0; j < N_row; j++) {
            // TODO change to constexpr
            int x = shape->bondries.at("left") + (2*particle_r+particle_spacing) * j;
            int y = shape->bondries.at("top") + (2*particle_r+particle_spacing) * i;

            tmp.push_back(std::make_shared<Particle>(
                particle_r, x, y, 0, 0, particle_m
            ));
        }
        particles.push_back(tmp);
    }
}

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