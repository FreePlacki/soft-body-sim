/**
 * Handles logic, graphics and stores graphical objects (like Particle).
*/

#pragma once

#include <SFML/Window/Event.hpp>
#include "particle.h"
#include "shape.h"
#include "body.h"
#include "window.h"
#include "uiManager.h"
#include <vector>
#include <iostream>


class Engine {
public:
    Engine(std::unique_ptr<Window> win);

    void mainLoop();

    void addParticle(std::shared_ptr<Particle> p);
    void addShape(std::shared_ptr<Shape> s);
    void addBody(std::shared_ptr<Body> b);

private:
    std::unique_ptr<Window> win;

    // TODO change to unique pointers
    std::vector<std::shared_ptr<Particle>> particles;
    std::vector<std::shared_ptr<Shape>> shapes;
    std::vector<std::shared_ptr<Body>> bodies;

    // calculated fps. Starts with max fps value
    double fps;

private:
    void initObjects();
    void draw() const;
    void update();

    void solveParticleWall(std::shared_ptr<Particle> p, int width, int height);
    // formula from https://en.wikipedia.org/wiki/Elastic_collision.
    void solveParticleParticle(std::shared_ptr<Particle> p1, std::shared_ptr<Particle> p2);
    void solveParticleLine(std::shared_ptr<Particle> p, const Vector2 &pt1, const Vector2 &pt2);
    void solveParticleShape(std::shared_ptr<Shape> s, std::shared_ptr<Particle> p);
    void solveCollisions();
};