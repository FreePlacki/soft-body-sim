/**
 * Implements methods from the Engine class.
 * @file engine.cpp
*/

#include "../header/engine.h"


// constructor
Engine::Engine() {
    this->initObjects();
}

// calls update on all particles
void Engine::update() {
    this->checkCollisions();
    for (auto &p : this->particles) {
        p.update();
        //cout << p.pos.y << "\n";
    }
}

// main while loop
void Engine::mainLoop(sf::RenderWindow &win) {
    double fps;
    sf::Clock clock;
    sf::Time previousTime = clock.getElapsedTime();
    sf::Time currentTime;

    while (win.isOpen()) {
        sf::Event event;
        while (win.pollEvent(event)) {
            switch(event.type) {
                case sf::Event::Closed:
                    win.close();
                    break;
            }
        }
        win.clear();

        this->update();
        this->draw(win);

        win.display();

        currentTime = clock.getElapsedTime();
        fps = 1.0f / (currentTime.asSeconds() - previousTime.asSeconds());
        //cout << "fps: " << fps << "\n";
        previousTime = currentTime;
    }
}

// calls draw on all particles
void Engine::draw(sf::RenderWindow &win) {
    for (Particle p : this->particles) {
        p.draw(win);
    }

    for (Shape s : this->shapes) {
        s.draw(win);
    }
}

// adds a particle to the vector
void Engine::addParticle(Particle &p) {
    this->particles.push_back(p);
}

// adds a shape to the vector
void Engine::addShape(Shape &s) {
    this->shapes.push_back(s);
}

// initializes graphical objects. Called at construction
void Engine::initObjects() {
    Particle p1 = Particle(10, WIDTH/2, HEIGHT/2, 100.0, 0.0);
    Particle p2 = Particle(10, WIDTH/2+100.0, HEIGHT/2, 100.0+50.0, 0.0);
    Particle p3 = Particle(10, WIDTH/2+200.0, HEIGHT/2, 100.0-50.0, 0.0);
    
    this->addParticle(p1);
    this->addParticle(p2);
    this->addParticle(p3);

    Shape rect1 = Shape(100, 150, 200, 50);

    this->addShape(rect1);
}

// solves a two-particle collision
std::pair<Vector2, Vector2> Engine::solveBallCollision(Particle &p1, Particle &p2) {
    Vector2 vel_diff1 = p1.vel - p2.vel;
    Vector2 pos_diff1 = p1.pos - p2.pos;
    double dot1 = vel_diff1 * pos_diff1;
    double red_mass1 =  2*p2.m/(p1.m+p2.m);
    double dist_sq1 = pos_diff1 * pos_diff1;
    Vector2 v1 = pos_diff1 * red_mass1 * dot1 / dist_sq1;

    Vector2 vel_diff2 = p2.vel - p1.vel;
    Vector2 pos_diff2 = p2.pos - p1.pos;
    double dot2 = vel_diff2 * pos_diff2;
    double red_mass2 =  2*p1.m/(p1.m+p2.m);
    double dist_sq2 = pos_diff2 * pos_diff2;
    Vector2 v2 = pos_diff2 * red_mass2 * dot2 / dist_sq2;

    // cout << v1.x << " : " << v2.x << "\n";
    // cout << p1.m << " : " << p2.m << "\n";
    // cout << 1/(p1.m+p2.m) << "\n";

    return std::make_pair(v1, v2);
}

// solves collisions for all particles
void Engine::checkCollisions() {
    for (int p1 = 0; p1 < particles.size(); p1++) {
        if (particles[p1].pos.y + particles[p1].r >= HEIGHT
        ||  particles[p1].pos.y - particles[p1].r <= 0) {
            particles[p1].vel.y *= -1;
        }
        if (particles[p1].pos.x + particles[p1].r >= WIDTH
        ||  particles[p1].pos.x - particles[p1].r <= 0) {
            particles[p1].vel.x *= -1;
        }

        for (int p2 = p1+1; p2 < particles.size(); p2++) {
            if (abs(particles[p1].pos.x - particles[p2].pos.x) <= particles[p1].r + particles[p2].r
            &&  abs(particles[p1].pos.y - particles[p2].pos.y) <= particles[p1].r + particles[p2].r) {
                std::pair<Vector2, Vector2> solved_vel = this->solveBallCollision(particles[p1], particles[p2]);
                particles[p1].vel -= solved_vel.first;
                particles[p2].vel -= solved_vel.second;
            }
        }
    }
}

// getter for particles vector
std::vector<Particle>& Engine::getParticles() {
    return this->particles;
}

// getter for shapes vector
std::vector<Shape>& Engine::getShapes() {
    return this->shapes;
}