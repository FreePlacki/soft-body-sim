#include "minunit.h"
#include "memory"
#include "../src/particle.h"


std::unique_ptr<Particle> p1;
std::unique_ptr<Particle> p2;

void test_setup() {
    p1 = std::make_unique<Particle>(5.0, 300.0, 400.0);
    p1 = std::make_unique<Particle>(1.0, 200.0, 350.0, 0.5, 2.0, 3.0);
}

void test_teardown() {}


MU_TEST(test_init) {
    mu_assert_double_eq(5.0, (*p1).r);
    mu_assert(51.0 != (*p1).r, "should fail with other value");
    mu_assert_double_eq(300.0, (*p1).pos.x);
    mu_assert(51.0 != (*p1).pos.x, "should fail with other value");
}


MU_TEST_SUITE(particle_tests) {
    MU_SUITE_CONFIGURE(&test_setup, &test_teardown);

    MU_RUN_TEST(test_init);
}

int main() {
    MU_RUN_SUITE(particle_tests);
    MU_REPORT();

    return MU_EXIT_CODE;
}