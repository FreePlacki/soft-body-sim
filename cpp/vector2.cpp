/**
 * Implements methods from the Vector2 class.
 * @file vector2.cpp
*/

#include "../header/vector2.h"


// constructor
Vector2::Vector2(double x, double y) {
    this->x = x;
    this->y = y;
}

// vector length using sqrt
double Vector2::length() {
    double s = this->x*this->x + this->y*this->y;
    return sqrt(s);
}

// length^2 (faster)
double Vector2::length_sq() {
    double s = this->x*this->x + this->y*this->y;
    return s;
}

// distance to another vector
double Vector2::dist(Vector2 &v) {
    double d = (this->x - v.x)*(this->x - v.x) + (this->y - v.y)*(this->y - v.y);
    return sqrt(d);
}

// distance^2 (faster)
double Vector2::dist_sq(Vector2 &v) {
    double d = (this->x - v.x)*(this->x - v.x) + (this->y - v.y)*(this->y - v.y);
    return d;
}

// overload for += between two vectors
void Vector2::operator+=(Vector2 &v) {
    this->x += v.x;
    this->y += v.y;
}

// overload for -= between two vectors
void Vector2::operator-=(Vector2 &v) {
    this->x -= v.x;
    this->y -= v.y;
}

// overload for *= between vector and scalar
void Vector2::operator*=(double a) {
    this->x *= a;
    this->y *= a;
}

// overload for + between two vectors
Vector2 Vector2::operator+(Vector2 &v) {
    return Vector2(this->x+v.x, this->y+v.y);
}

// overload for - between two vectors
Vector2 Vector2::operator-(Vector2 &v) {
    return Vector2(this->x-v.x, this->y-v.y);
}

// dot product
double Vector2::operator*(Vector2 &v) {
    return this->x*v.x + this->y*v.y;
}

// multiplication by a scalar
Vector2 Vector2::operator*(double a) {
    return Vector2(this->x*a, this->y*a);
}

// division by a scalar
Vector2 Vector2::operator/(double a) {
    return Vector2(this->x/a, this->y/a);
}

// scales down vector is bigger than max length
void Vector2::limit(double max) {
    if (this->length_sq() > max*max) {
        this->x = (max/this->length()) * this->x;
        this->y = (max/this->length()) * this->y;
    }
}
