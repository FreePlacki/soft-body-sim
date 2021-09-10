#include "minunit.h"
#include "memory"
#include "../src/particle.h"


std::shared_ptr<Particle> p1;
std::shared_ptr<Particle> p2;

void test_setup() {
    p1 = std::make_shared<Particle>(5.0, 300.0, 400.0);
    p2 = std::make_shared<Particle>(1.0, 200.0, 350.0, 0.5, 2.0, 3.0, sf::Color::Blue);
}

void test_teardown() {}


MU_TEST(test_init) {
    mu_assert_double_eq(5.0, (*p1).r);
    mu_assert_double_eq(300.0, (*p1).pos.x);
    mu_assert_double_eq(0.0, (*p1).vel.x);
    mu_assert_double_eq(10.0, (*p1).m);
    mu_assert(sf::Color::Red == (*p1).color, "Default color red");

    mu_assert_double_eq(2.0, (*p2).vel.y);
    mu_assert_double_eq(3.0, (*p2).m);
    mu_assert(sf::Color::Blue == (*p2).color, "Assigning color blue");
}

MU_TEST(test_connect) {
    (*p1).connect(p2, 50.0, 0.5);

    mu_assert_int_eq(1, p1->connected.size());
    mu_assert_int_eq(1, p2->connected.size());

    mu_assert_double_eq(0.5, p1->connected[0].k);
    mu_assert(p2->connected[0].particle->color == p1->color, "Saved color should be the same");
}


MU_TEST_SUITE(particle_tests) {
    MU_SUITE_CONFIGURE(&test_setup, &test_teardown);

    MU_RUN_TEST(test_init);
    MU_RUN_TEST(test_connect);
}

int main() {
    MU_RUN_SUITE(particle_tests);
    MU_REPORT();

    return MU_EXIT_CODE;
}