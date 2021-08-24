/**
 * Soft body composed of particles connected by springs.
 * @file body.h
*/

#include <vector>
#include "particle.h"
#include "shape.h"

class Body {
private:
    // shape particles form at initial time
    // Shape shape = Shape(0, 0, 0, Shape::makeRect(0,0));
    std::shared_ptr<Shape> shape;
    const int particle_r, particle_spacing;
    const double particle_m;

public:
    // 2d vector (each row is a vector)
    std::vector<std::vector<std::shared_ptr<Particle>>> particles;

    /**
     * Class constructor
     * @param shape shape to fill with particles
     * @param particle_r radius of particles
     * @param particle_spacing value of "x_0" for vertical and horizontal springs
    */
    Body(std::shared_ptr<Shape> shape, int particle_r, int particle_spacing, double particle_m);

    void initParticles();

    void draw(sf::RenderWindow &win);
};