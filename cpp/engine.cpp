/**
 * Implements methods from the Engine class.
 * @file engine.cpp
*/

#include "../header/engine.h"


// constructor
Engine::Engine(Window &win) {
    this->win = &win;

    this->initObjects();
}

// calls update on all particles and checks collisions
void Engine::update() {
    this->checkCollisions();
    for (auto &p : this->particles) {
        p.update();
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
            switch(event.type) {
                case sf::Event::Closed:
                    win->getWin().close();
                    break;
            }
        }
        // drawing process
        win->getWin().clear();

        this->update();
        this->draw();

        win->getWin().display();

        // displaying fps
        counter++;
        currentTime = clock.getElapsedTime();
        fps = 1.0f / (currentTime.asSeconds() - previousTime.asSeconds());
        previousTime = currentTime;
        if (counter == this->win->getFps()) {
            std::cout << "fps: " << fps << " / " << this->win->getFps() << "\n";
            counter = 0;
        }
    }
}

// calls draw on all entities
void Engine::draw() {
    for (Particle p : this->particles) {
        p.draw(win->getWin());
    }

    for (Shape s : this->shapes) {
        s.draw(win->getWin());
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
    int win_width = this->win->getSize().first;
    int win_height = this->win->getSize().second;

    Particle p1 = Particle(10, win_width/2, win_height/2-300, 100.0, 0.0);
    Particle p2 = Particle(10, win_width/2+100.0, win_height/2-300, 100.0+50.0, 0.0);
    Particle p3 = Particle(10, win_width/2+200.0, win_height/2-300, 100.0-50.0, 0.0);
    
    this->addParticle(p1);
    this->addParticle(p2);
    this->addParticle(p3);

    sf::Vector2f rect1_points[4] = {sf::Vector2f(0, 0), sf::Vector2f(100, 0), sf::Vector2f(100, 50), sf::Vector2f(0, 50)};
    Shape rect1 = Shape(500, 600, 4, rect1_points);
    sf::Vector2f rect2_points[4] = {sf::Vector2f(0, 0), sf::Vector2f(300, 150), sf::Vector2f(0, 300), sf::Vector2f(-300, 150)};
    Shape rect2 = Shape(200, 200, 4, rect2_points);
    //this->addShape(rect1);
    this->addShape(rect2);
}

// solves a particle-wall collision
Vector2 Engine::solveParticleWall(Particle &p, int width, int height) {
    Vector2 new_vel(p.vel.x, p.vel.y);
    if (p.pos.y + p.r >= width
        ||  p.pos.y - p.r <= 0) {
            new_vel.y *= -1;
        }
    if (p.pos.x + p.r >= height
        ||  p.pos.x - p.r <= 0) {
            new_vel.x *= -1;
        }

    return new_vel;
}

// solves a two-particle collision
std::pair<Vector2, Vector2> Engine::solveBallCollision(Particle &p1, Particle &p2) {
    // if they are not colliding return (0, 0) vectors (no velocity to substruct)
    if (!(abs(p1.pos.x - p2.pos.x) <= p1.r + p2.r
        &&  abs(p1.pos.y - p2.pos.y) <= p1.r + p2.r))
        return std::make_pair(Vector2(0, 0), Vector2(0, 0));
    
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

    return std::make_pair(v1, v2);
}

// solves collisions for all particles
void Engine::checkCollisions() {
    for (int p1 = 0; p1 < particles.size(); p1++) {
        // wall collision
        particles[p1].vel = solveParticleWall(particles[p1], win->getSize().first, win->getSize().second);

        // particle collision
        for (int p2 = p1+1; p2 < particles.size(); p2++) {
            std::pair<Vector2, Vector2> solved_vel = this->solveBallCollision(particles[p1], particles[p2]);
            particles[p1].vel -= solved_vel.first;
            particles[p2].vel -= solved_vel.second;
        }

        //shape collision
        for (Shape s : shapes) {
            Particle &p = particles[p1];
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

                // computing distance
                    double line_len = pt1.dist(pt2);
                    double line_len_sq = pt1.dist_sq(pt2);
                    double dx = (pt2.x - pt1.x);
                    double dy = (pt2.y - pt1.y);
                    double dist = abs((p.pos.x-pt1.x)*(-pt2.y+pt1.y) + (p.pos.y-pt1.y)*(pt2.x-pt1.x))
                                / line_len;
                    if (dist <= p.r) {
                        // TODO fix circle-shape collision response

                        Vector2 v_perpand(-(-p.vel.x*dy*dy + p.vel.y*dx*dy)/line_len_sq,
                                          (-p.vel.x*dx*dy + p.vel.y*dx*dx)/line_len_sq);

                        v_perpand *= 2;
                        p.vel -= v_perpand;
                        p.pos.x += -(-p.vel.x*dy*dy + p.vel.y*dx*dy)/abs(-(-p.vel.x*dy*dy + p.vel.y*dx*dy))*2;
                        p.pos.y += (-p.vel.x*dx*dy + p.vel.y*dx*dx)/abs((-p.vel.x*dx*dy + p.vel.y*dx*dx))*2;
                    }
                }
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