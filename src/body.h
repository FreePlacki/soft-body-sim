/**
 * Soft body composed of particles connected by springs.
*/

#include <vector>
#include "particle.h"
#include "shape.h"

class Body {
public:
    Body(std::shared_ptr<Shape> shape, int particle_r, int particle_spacing, double particle_m, double spring_k=50.0);
    void initParticles();
    void draw(sf::RenderWindow &win);

public:
    // 2d vector for rows and columns
    std::vector<std::vector<std::shared_ptr<Particle>>> particles;

private:
    std::shared_ptr<Shape> shape;
    const int particle_r, particle_spacing;
    const double particle_m, spring_k;   
};