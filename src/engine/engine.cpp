/**
 * Implements methods from the Engine class.
 * @file engine.cpp
*/

#include "engine.h"


// constructor
Engine::Engine(Window &win) {
    this->win = &win;
    this->fps = this->win->getFps();

    initObjects();
}

// calls update on all particles and checks collisions
void Engine::update() {
    solveCollisions();
    for (Particle &p : particles) {
        p.update(this->fps);
        //cout << p.pos.y << "\n";
    }
}

// main while loop
void Engine::mainLoop() {
    // calculating fps
    double fps;
    // counter is for displaying fps once every x seconds
    int counter = 0;
    sf::Clock clock;
    sf::Time previousTime = clock.getElapsedTime();
    sf::Time currentTime;

    // event loop
    while (win->getWin().isOpen()) {
        sf::Event event;
        while (win->getWin().pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                win->getWin().close();
        }
        // drawing process
        win->getWin().clear();

        update();
        draw();

        win->getWin().display();

        // displaying fps
        counter++;
        currentTime = clock.getElapsedTime();
        fps = 1.0f / (currentTime.asSeconds() - previousTime.asSeconds());
        previousTime = currentTime;
        if (counter == win->getFps()) {
            this->fps = fps;
            std::cout << "fps: " << fps << " / " << win->getFps() << "\n";
            counter = 0;
        }
    }
}

// calls draw on all entities
void Engine::draw() const {
    //double energy = 0;
    for (const Particle &p : particles) {
        p.draw(win->getWin());
        //energy += 0.5*p.m * p.vel.length_sq();
        //energy += p.m * 100 *(800-p.pos.y);
    }
    // TODO the total energy is increasing
    //std::cout << energy << "\n";

    for (const Shape &s : shapes) {
        s.draw(win->getWin());
    }
}

// adds a particle to the vector
void Engine::addParticle(const Particle &p) {
    this->particles.push_back(p);
}

// adds a shape to the vector
void Engine::addShape(const Shape &s) {
    this->shapes.push_back(s);
}

// initializes graphical objects. Called at construction
void Engine::initObjects() {
    int win_width = win->getSize().first;
    int win_height = win->getSize().second;

    Particle p1 = Particle(10, win_width/2, win_height/2-300, 100.0, 0.0);
    Particle p2 = Particle(10, win_width/2+100.0, win_height/2-300, 100.0+50.0, 0.0);
    Particle p3 = Particle(10, win_width/2+200.0, win_height/2-300, 100.0-50.0, 0.0);
    
    addParticle(p1);
    addParticle(p2);
    addParticle(p3);

    sf::Vector2f rect1_points[4] = {sf::Vector2f(0, 0), sf::Vector2f(100, 0), sf::Vector2f(100, 50), sf::Vector2f(0, 50)};
    Shape rect1 = Shape(500, 600, 4, rect1_points);
    sf::Vector2f rect2_points[4] = {sf::Vector2f(0, 0), sf::Vector2f(300, 150), sf::Vector2f(0, 300), sf::Vector2f(-300, 150)};
    Shape rect2 = Shape(200, 200, 4, rect2_points);

    addShape(rect1);
    addShape(rect2);
}

// solves a particle-wall collision
void Engine::solveParticleWall(Particle &p, int width, int height) {
    Vector2 top_left(0,0);
    Vector2 top_right(width,0);
    Vector2 bottom_left(0,height);
    Vector2 bottom_right(width,height);

    solveParticleLine(p, top_left, top_right);
    solveParticleLine(p, top_right, bottom_right);
    solveParticleLine(p, bottom_right, bottom_left);
    solveParticleLine(p, bottom_left, top_left);
}

// solves a two-particle collision
void Engine::solveParticleParticle(Particle &p1, Particle &p2) {
    // if they are not colliding return
    if (!(abs(p1.pos.x - p2.pos.x) <= p1.r + p2.r
        &&  abs(p1.pos.y - p2.pos.y) <= p1.r + p2.r))
        return;
    
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

    //TODO push particles out
    p1.vel -= v1;
    p2.vel -= v2;
}

// solves particle-line collision
void Engine::solveParticleLine(Particle &p, Vector2 &pt1, Vector2 &pt2) {
    // if dist > radius return
    double dist = abs((p.pos.x-pt1.x)*(-pt2.y+pt1.y) + (p.pos.y-pt1.y)*(pt2.x-pt1.x))
                        / pt1.dist(pt2);
    if (dist > p.r) return;

    double line_len_sq = pt1.dist_sq(pt2);
    double dx = (pt2.x - pt1.x);
    double dy = (pt2.y - pt1.y);

    // velocity component perpandicular to the line
    Vector2 v_perpand(-(-p.vel.x*dy*dy + p.vel.y*dx*dy)/line_len_sq,
                       (-p.vel.x*dx*dy + p.vel.y*dx*dx)/line_len_sq);

    // substructing 2x perpandicular
    v_perpand *= 2;
    p.vel -= v_perpand;

    // small nudge out of the line
    auto sign = [](double val) { return (0 < val) - (val < 0); };
    p.pos.x -= sign(v_perpand.x)*(p.r-dist);
    p.pos.y -= sign(v_perpand.y)*(p.r-dist);
}

void Engine::solveParticleShape(Shape &s, Particle &p) {
    // check collision
    for (int point = 0; point < s.point_count; point++) {
        // two points for a line (mod to loop back to first one time)
        Vector2 pt1(s.points[point].x, s.points[point].y);
        Vector2 pt2(s.points[(point+1) % s.point_count]);
        // obtaining the absolute pos
        pt1 += s.pos;
        pt2 += s.pos;

        // check bondries
        if (p.pos.x <= s.bondries["right"]
            && p.pos.x >= s.bondries["left"]
            && p.pos.y >= s.bondries["top"]
            && p.pos.y <= s.bondries["bottom"]) {
            solveParticleLine(p, pt1, pt2);
        }
    }
}

// solves collisions for all particles
void Engine::solveCollisions() {
    for (size_t p1 = 0; p1 < particles.size(); p1++) {
        // wall collision
        solveParticleWall(particles[p1], win->getSize().first, win->getSize().second);

        // particle collision
        for (size_t p2 = p1+1; p2 < particles.size(); p2++) {
            solveParticleParticle(particles[p1], particles[p2]);
        }

        //shape collision
        for (Shape &s : shapes) {
            solveParticleShape(s, particles[p1]);
        }
    }
}

// getter for particles vector
std::vector<Particle> Engine::getParticles() const {
    return this->particles;
}

// getter for shapes vector
std::vector<Shape> Engine::getShapes() const {
    return this->shapes;
}