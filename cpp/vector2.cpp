#include "../header/vector2.h"

Vector2::Vector2(float x, float y) {
    this->x = x;
    this->y = y;
}

float Vector2::length() {
    float s = this->x*this->x + this->y*this->y;
    return sqrt(s);
}

// length^2 (faster)
float Vector2::length_sq() {
    float s = this->x*this->x + this->y*this->y;
    return s;
}

float Vector2::dist(Vector2 &v) {
    float d = (this->x - v.x)*(this->x - v.x) + (this->y - v.y)*(this->y - v.y);
    return sqrt(d);
}

float Vector2::dist_sq(Vector2 &v) {
    float d = (this->x - v.x)*(this->x - v.x) + (this->y - v.y)*(this->y - v.y);
    return d;
}

void Vector2::operator+=(Vector2 &v) {
    this->x += v.x;
    this->y += v.y;
}

void Vector2::operator-=(Vector2 &v) {
    this->x -= v.x;
    this->y -= v.y;
}

void Vector2::operator*=(float a) {
    this->x *= a;
    this->y *= a;
}

Vector2 Vector2::operator+(Vector2 &v) {
    return Vector2(this->x+v.x, this->y+v.y);
}

Vector2 Vector2::operator-(Vector2 &v) {
    return Vector2(this->x-v.x, this->y-v.y);
}

float Vector2::operator*(Vector2 &v) { // dot product
    return this->x*v.x + this->y*v.y;
}

Vector2 Vector2::operator*(float a) {
    return Vector2(this->x*a, this->y*a);
}

Vector2 Vector2::operator/(float a) {
    return Vector2(this->x/a, this->y/a);
}

void Vector2::limit(float max) {
    if (this->length_sq() > max*max) {
        this->x = (max/this->length()) * this->x;
        this->y = (max/this->length()) * this->y;
    }
}
