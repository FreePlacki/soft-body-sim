/**
 * Soft Body composed of particles connected by springs.
 * @file body.h
*/

#include <vector>
#include "particle.h"
#include "shape.h"

class Body {
private:
    std::vector<std::unique_ptr<Particle>> particles;
    // shape particles form at initial time
    // Shape shape = Shape(0, 0, 0, Shape::makeRect(0,0));
    std::shared_ptr<Shape> shape;
    int particle_r, particle_spacing;

public:
    Body(std::shared_ptr<Shape> shape, int particle_r, int particle_spacing);
};