#include "vector2.h"

Vector2::Vector2() {
    this->x = 0;
    this->y = 0;
}

Vector2::Vector2(double x, double y):x(x), y(y) {}

Vector2::Vector2(const sf::Vector2f &v) {
    this->x = v.x;
    this->y = v.y;
}

sf::Vector2f Vector2::to_sf() {
    return sf::Vector2f(this->x, this->y);
}

double Vector2::length() const {
    double s = this->x*this->x + this->y*this->y;
    return sqrt(s);
}

// length^2 (faster)
double Vector2::length_sq() const {
    double s = this->x*this->x + this->y*this->y;
    return s;
}

// distance to another vector
double Vector2::dist(const Vector2 &v) const {
    double d = (this->x - v.x)*(this->x - v.x) + (this->y - v.y)*(this->y - v.y);
    return sqrt(d);
}

// distance^2 (faster)
double Vector2::dist_sq(const Vector2 &v) const {
    double d = (this->x - v.x)*(this->x - v.x) + (this->y - v.y)*(this->y - v.y);
    return d;
}

void Vector2::operator+=(const Vector2 &v) {
    this->x += v.x;
    this->y += v.y;
}

void Vector2::operator-=(const Vector2 &v) {
    this->x -= v.x;
    this->y -= v.y;
}

void Vector2::operator*=(double a) {
    this->x *= a;
    this->y *= a;
}

Vector2 Vector2::operator+(const Vector2 &v) const {
    return Vector2(this->x+v.x, this->y+v.y);
}

Vector2 Vector2::operator-(const Vector2 &v) const {
    return Vector2(this->x-v.x, this->y-v.y);
}

// dot product
double Vector2::operator*(const Vector2 &v) const {
    return this->x*v.x + this->y*v.y;
}

Vector2 Vector2::operator*(double a) const {
    return Vector2(this->x*a, this->y*a);
}

Vector2 Vector2::operator/(double a) const {
    return Vector2(this->x/a, this->y/a);
}

// scales down vector is bigger than max length
void Vector2::limit(double max) {
    if (this->length_sq() > max*max) {
        this->x = (max/this->length()) * this->x;
        this->y = (max/this->length()) * this->y;
    }
}