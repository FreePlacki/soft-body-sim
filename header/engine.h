/**
 * Handles logic, graphics and stores graphical objects (like Particle).
 * @file engine.h
*/

#pragma once

#include "particle.h"
#include "shape.h"
#include "window.h"
#include <vector>
#include <iostream>


class Engine {
private:
    // active Window object
    Window *win;

    // list of all Particle objects
    std::vector<Particle> particles;

    // lost of all shapes
    std::vector<Shape> shapes;

    /**
     * Initializes graphical objects (called at construction).
    */
    void initObjects();

    /**
     * Solves and checks for particle-wall collision
     * @param p1 particle to solve for
     * @param width screen width
     * @param height screen height
     * @return Vector2 new particle velocity
    */
    Vector2 solveParticleWall(Particle &p, int width, int height);

    /**
     * Solves the collision of two particles
     * (from eq: https://en.wikipedia.org/wiki/Elastic_collision).
     * @param p1 particle one
     * @param p2 particle two
     * @return std::pair<Vector2, Vector2> of the new velocities
    */
    std::pair<Vector2, Vector2> solveBallCollision(Particle &p1, Particle &p2);
    
    /**
     * Loops through particles list and solves the collitions
     * (using the solver functions).
    */
    void checkCollisions();

public:
    /**
     * Class constructor.
     * Calls the initObjects function.
    */
    Engine(Window &win);

    /**
     * Calls the update method for all the particles.
    */
    void update();

    /**
     * Calls the draw method for all the particles.
    */
    void draw();

    /**
     * Contains the main while loop of the program.
    */
    void mainLoop();

    /**
     * Adds a Particle object to the particles vector.
     * @param p particle to add
    */
    void addParticle(Particle &p);

    /**
     * Adds a Shape object to the shapes vector.
     * @param s shape to add
    */
    void addShape(Shape &s);

    /**
     * Getter method for the particles vector.
     * @return particles vector
    */
    std::vector<Particle>& getParticles();

    /**
     * Getter method for the shapes vector.
     * @return shapes vector
    */
    std::vector<Shape>& getShapes();
};