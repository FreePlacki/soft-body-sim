#include "engine.h"

#define LOG(msg) \
    std::cout << __FILE__ << "(" << __LINE__ << "): " << msg << std::endl


Engine::Engine(Window &win):win(&win) {
    this->fps = this->win->getFps();

    initObjects();
}

void Engine::update() {
    solveCollisions();
    for (auto p : particles) {
        (*p).update(static_cast<double>(this->win->getFps()));
    }
}

void Engine::mainLoop() {
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

void Engine::draw() const {
    for (auto p : particles) {
        (*p).draw(win->getWin());
    }

    for (auto s : shapes) {
        (*s).draw(win->getWin());
    }

    for (auto b : bodies) {
        (*b).draw(win->getWin());
    }
}

void Engine::addParticle(std::shared_ptr<Particle> p) {
    this->particles.push_back(p);
}

void Engine::addShape(std::shared_ptr<Shape> s) {
    this->shapes.push_back(s);
}

void Engine::addBody(std::shared_ptr<Body> b) {
    this->bodies.push_back(b);
    for (auto &row : b->particles) {
        for (auto p : row) {
            this->particles.push_back(p);
        }
    }
}

void Engine::initObjects() {
    int win_width = win->getSize().first;
    int win_height = win->getSize().second;

    std::shared_ptr<Particle> p1 = std::make_shared<Particle>(5, win_width/2, win_height/2-300, 100.0, 0.0);
    std::shared_ptr<Particle> p2 = std::make_shared<Particle>(5, win_width/2+100.0, win_height/2-300, 100.0+50.0, 0.0);
    std::shared_ptr<Particle> p3 = std::make_shared<Particle>(5, win_width/2+200.0, win_height/2-300, 100.0-50.0, 0.0);
    
    // addParticle(p1);
    // addParticle(p2);
    // addParticle(p3);

    // (*p1).connect(p2, 100.0, 50.0);
    // (*p1).connect(p3, 2.0, 30.0);
    // (*p2).connect(p3, 2.0, 30.0);

    // sf::Vector2f rect1_points[4] = {sf::Vector2f(0, 0), sf::Vector2f(100, 0), sf::Vector2f(100, 50), sf::Vector2f(0, 50)};
    std::vector<sf::Vector2f> rect1_points = Shape::makeRect(100, 50);
    std::shared_ptr<Shape> rect1 = std::make_shared<Shape>(600, 600, rect1_points);
    std::vector<sf::Vector2f> rect2_points = {sf::Vector2f(0, 0), sf::Vector2f(300, 150), sf::Vector2f(0, 300), sf::Vector2f(-300, 150)};
    std::shared_ptr<Shape> rect2 = std::make_shared<Shape>(200, 200, rect2_points);

    addShape(rect1);
    addShape(rect2);


    // std::vector<sf::Vector2f> rect3_points = Shape::makeRect(100, 50);
    // std::shared_ptr<Shape> rect3 = std::make_shared<Shape>(200, 50, 4, rect3_points);
    // std::shared_ptr<Body> body1 = std::make_shared<Body>(rect3, 3, 10, 2.0, 30.0);

    std::vector<sf::Vector2f> rect4_points = Shape::makeRect(100, 200);
    std::shared_ptr<Shape> rect4 = std::make_shared<Shape>(250, 20, rect4_points);
    std::shared_ptr<Body> body2 = std::make_shared<Body>(rect4, 4, 15, 10.0, 20000.0);

    // addBody(body1);
    addBody(body2);
}

void Engine::solveParticleWall(std::shared_ptr<Particle> p, int width, int height) {
    Vector2 top_left(0,0);
    Vector2 top_right(width,0);
    Vector2 bottom_left(0,height);
    Vector2 bottom_right(width,height);

    solveParticleLine(p, top_left, top_right);
    solveParticleLine(p, top_right, bottom_right);
    solveParticleLine(p, bottom_right, bottom_left);
    solveParticleLine(p, bottom_left, top_left);

    // TODO push particle that had gone out of bounds
}

void Engine::solveParticleParticle(std::shared_ptr<Particle> p1, std::shared_ptr<Particle> p2) {
    // if they are not colliding return
    const double dist = (*p1).pos.dist((*p2).pos);
    if (dist > (*p1).r + (*p2).r) return;
    
    Vector2 vel_diff1 = (*p1).vel - (*p2).vel;
    Vector2 pos_diff1 = (*p1).pos - (*p2).pos;
    double dot1 = vel_diff1 * pos_diff1;
    double red_mass1 =  2*(*p2).m/((*p1).m+(*p2).m);
    double dist_sq1 = pos_diff1 * pos_diff1;
    Vector2 v1 = pos_diff1 * red_mass1 * dot1 / dist_sq1;

    Vector2 vel_diff2 = (*p2).vel - (*p1).vel;
    Vector2 pos_diff2 = (*p2).pos - (*p1).pos;
    double dot2 = vel_diff2 * pos_diff2;
    double red_mass2 =  2*(*p1).m/((*p1).m+(*p2).m);
    double dist_sq2 = pos_diff2 * pos_diff2;
    Vector2 v2 = pos_diff2 * red_mass2 * dot2 / dist_sq2;

    (*p1).vel -= v1;
    (*p2).vel -= v2;

    (*p1).pos += (*p1).vel/(*p1).vel.length() * ((*p1).r+(*p2).r - dist)/2;
    (*p2).pos += (*p2).vel/(*p2).vel.length() * ((*p1).r+(*p2).r - dist)/2;
}

void Engine::solveParticleLine(std::shared_ptr<Particle> p, const Vector2 &pt1, const Vector2 &pt2) {
    // TODO check if particle is in lines bondries
    
    // if dist > radius: return
    double dist = abs(((*p).pos.x-pt1.x)*(-pt2.y+pt1.y) + ((*p).pos.y-pt1.y)*(pt2.x-pt1.x))
                        / pt1.dist(pt2);
    if (dist > (*p).r) return;

    double line_len_sq = pt1.dist_sq(pt2);
    double dx = (pt2.x - pt1.x);
    double dy = (pt2.y - pt1.y);

    // velocity component perpandicular to the line
    Vector2 v_perpand(-(-(*p).vel.x*dy*dy + (*p).vel.y*dx*dy)/line_len_sq,
                       (-(*p).vel.x*dx*dy + (*p).vel.y*dx*dx)/line_len_sq);

    // energy loss
    (*p).vel *= 0.99;

    // substructing 2x perpandicular
    v_perpand *= 2;
    (*p).vel -= v_perpand;

    // small nudge out of the line
    auto sign = [](double val) { return (0 < val) - (val < 0); };
    (*p).pos.x -= sign(v_perpand.x)*((*p).r-dist);
    (*p).pos.y -= sign(v_perpand.y)*((*p).r-dist);
}

void Engine::solveParticleShape(std::shared_ptr<Shape> s, std::shared_ptr<Particle> p) {
    for (size_t point = 0; point < s->points.size(); point++) {
        // TODO fix particles going inside the shape

        // two points for a line (mod to loop back to first one time)
        Vector2 pt1(s->points[point].x, s->points[point].y);
        Vector2 pt2(s->points[(point+1) % s->points.size()]);
        // obtaining the absolute pos
        pt1 += s->pos;
        pt2 += s->pos;

        if (p->pos.x - p->r <= s->bondries.at("right")
            && p->pos.x + p->r >= s->bondries.at("left")
            && p->pos.y + p->r >= s->bondries.at("top")
            && p->pos.y - p->r <= s->bondries.at("bottom")) {
            solveParticleLine(p, pt1, pt2);
        }
    }
}

void Engine::solveCollisions() {
    for (size_t p1 = 0; p1 < particles.size(); p1++) {
        solveParticleWall(particles[p1], win->getSize().first, win->getSize().second);

        for (size_t p2 = p1+1; p2 < particles.size(); p2++) {
            solveParticleParticle(particles[p1], particles[p2]);
        }

        for (auto s : shapes) {
            solveParticleShape(s, particles[p1]);
        }
    }
}