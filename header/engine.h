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

    // calculated fps. Starts with max fps value
    int fps;

    /**
     * Initializes graphical objects (called at construction).
    */
    void initObjects();

    /**
     * Solves and checks for particle-wall collision.
     * Updates particle's velocity and little nudge to position.
     * @param p1 particle to solve for
     * @param width screen width
     * @param height screen height
    */
    void solveParticleWall(Particle &p, int width, int height);

    /**
     * Solves the collision of two particles.
     * Updates their velocity.
     * (from eq: https://en.wikipedia.org/wiki/Elastic_collision).
     * @param p1 particle one
     * @param p2 particle two
     * @return std::pair<Vector2, Vector2> of the new velocities
    */
    void solveParticleParticle(Particle &p1, Particle &p2);

    /**
     * Solves the collision of a particle with a line.
     * Updates particle's velocity and little nudge to position.
     * @param p particle to solve for
     * @param pt1 first coordinate of the line
     * @param pt2 second coordinate of the line
    */
    void solveParticleLine(Particle &p, Vector2 &pt1, Vector2 &pt2);
    
    /**
     * Solves the collision of a particle with a convex shape.
     * Calls solveParticleLine().
     * @param s shape
     * @param p particle to solve for
    */
    void solveParticleShape(Shape &s, Particle &p);

    /**
     * Loops through particles list and solves the collitions
     * (using the solver functions).
    */
    void solveCollisions();

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
    void draw() const;

    /**
     * Contains the main while loop of the program.
    */
    void mainLoop();

    /**
     * Adds a Particle object to the particles vector.
     * @param p particle to add
    */
    void addParticle(const Particle &p);

    /**
     * Adds a Shape object to the shapes vector.
     * @param s shape to add
    */
    void addShape(const Shape &s);

    /**
     * Getter method for the particles vector.
     * @return particles vector
    */
    std::vector<Particle> getParticles() const;

    /**
     * Getter method for the shapes vector.
     * @return shapes vector
    */
    std::vector<Shape> getShapes() const;
};