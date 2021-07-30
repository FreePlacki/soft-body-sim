#include <SFML/Graphics.hpp>
#include <SFML/Window/Event.hpp>
#include <iostream>
#include <vector>
#include "../header/particle.h"
#include "../header/vector2.h"

using namespace std;

void draw(sf::RenderWindow &win, vector<Particle> particles) {
    for (Particle p : particles) {
        sf::CircleShape circ(p.r);
        circ.setFillColor(sf::Color::Red);
        circ.setOrigin(p.r, p.r);
        circ.setPosition(p.pos.x, p.pos.y);

        win.draw(circ);
    }
}

void update(vector<Particle> &particles, float frame_time) {
    for (auto &p : particles) {
        p.update(frame_time);
        //cout << p.pos.y << "\n";
    }
}

pair<Vector2, Vector2> solve_ball_collision(Particle &p1, Particle &p2) {
    // solves the collision of two balls (from eq: https://en.wikipedia.org/wiki/Elastic_collision

    Vector2 vel_diff1 = p1.vel - p2.vel;
    Vector2 pos_diff1 = p1.pos - p2.pos;
    float dot1 = vel_diff1 * pos_diff1;
    float red_mass1 =  2*p2.m/(p1.m+p2.m);
    float dist_sq1 = pos_diff1 * pos_diff1;
    Vector2 v1 = pos_diff1 * red_mass1 * dot1 / dist_sq1;

    Vector2 vel_diff2 = p2.vel - p1.vel;
    Vector2 pos_diff2 = p2.pos - p1.pos;
    float dot2 = vel_diff2 * pos_diff2;
    float red_mass2 =  2*p1.m/(p1.m+p2.m);
    float dist_sq2 = pos_diff2 * pos_diff2;
    Vector2 v2 = pos_diff2 * red_mass2 * dot2 / dist_sq2;

    cout << v1.x << " : " << v2.x << "\n";
    cout << p1.m << " : " << p2.m << "\n";
    cout << 1/(p1.m+p2.m) << "\n";

    return make_pair(v1, v2);
}

void check_collisions(vector<Particle> &particles) {
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
                pair<Vector2, Vector2> solved_vel = solve_ball_collision(particles[p1], particles[p2]);
                particles[p1].vel -= solved_vel.first;
                particles[p2].vel -= solved_vel.second;
            }
        }


    }
}


int main() {
    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Soft Body Sim");
    window.setFramerateLimit(FPS);
    
    Particle p1 = Particle(10, WIDTH/2, HEIGHT/2, 100.0, 0.0, 10.f);
    Particle p2 = Particle(10, WIDTH/2+100.0, HEIGHT/2, 100.0+50.0, 0.0, 9.f);
    Particle p3 = Particle(10, WIDTH/2+200.0, HEIGHT/2, 100.0-50.0, 0.0, 9.f);
    
    vector<Particle> particles;
    particles.push_back(p1);
    particles.push_back(p2);
    particles.push_back(p3);

    float fps;
    sf::Clock clock;
    sf::Time previousTime = clock.getElapsedTime();
    sf::Time currentTime;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            switch(event.type) {
                case sf::Event::Closed:
                    window.close();
                    break;
            }
        }
        window.clear();

        check_collisions(particles);
        update(particles, 1/fps);
        draw(window, particles);

        window.display();

        currentTime = clock.getElapsedTime();
        fps = 1.0f / (currentTime.asSeconds() - previousTime.asSeconds());
        //cout << "fps: " << fps << "\n";
        previousTime = currentTime;
    }

    return 0;
}
