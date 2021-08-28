/**
 * A two dimensional vector object.
 * Handles basic mathematical operations.
*/

#pragma once

#include <cmath>
#include <SFML/Graphics.hpp>


class Vector2 {
public:
    double x, y;

public:
    Vector2(double x, double y);
    Vector2(const sf::Vector2f &v);

    sf::Vector2f to_sf();

    double length() const;
    double length_sq() const;
    double dist(const Vector2 &v) const;
    double dist_sq(const Vector2 &v) const;
    void limit(double max);

    Vector2 operator+(const Vector2 &v) const;
    Vector2 operator-(const Vector2 &v) const;
    // dot product
    double operator*(const Vector2 &v) const;
    Vector2 operator*(double a) const;
    Vector2 operator/(double a) const;
    void operator+=(const Vector2 &v);
    void operator-=(const Vector2 &v);
    void operator*=(double a);
};
