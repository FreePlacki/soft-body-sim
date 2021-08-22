/**
 * Implements methods from the Body class.
 * @file body.cpp
*/

#include "body.h"

Body::Body(std::shared_ptr<Shape> shape, int particle_r, int particle_spacing) {
    this->shape = shape;
    this->particle_r = particle_r;
    this->particle_spacing = particle_spacing;
    this->shape = shape;
}