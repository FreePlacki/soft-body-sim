/**
 * A two dimensional vector object.
 * Handles basic mathematical operations.
 * @file vector2.h
*/

#pragma once

#include <cmath>
#include <SFML/Graphics.hpp>


class Vector2 {
public:
    // the x and y coordinates of the vector
    double x, y;

    /**
     * Class constructor.
     * @param x the x coordinate
     * @param y the y coordinate
    */
    Vector2(double x, double y);

    /**
     * Class constructor for converting from sf::Vector2f.
     * @param x the x coordinate
     * @param y the y coordinate
    */
    Vector2(const sf::Vector2f &v);

    /**
     * Converts to sf::Vector2f
     * @return sf::Vector2f with same x and y values
    */
    sf::Vector2f to_sf();

    /**
     * Calculates the length of the vector (using sqrt function).
     * @return double length
    */
    double length() const;

    /**
     * Calculates the length^2 of the vector
     * (faster than normal length - no sqrt).
     * @return double length squared
    */
    double length_sq() const;

    /**
     * Calculates the distance to the second vector
     * (uses the sqrt function).
     * @param v second vector to compare
     * @return double distance between vectors
    */
    double dist(const Vector2 &v) const;

    /**
     * Calculates the distance^2 to the second vector
     * (faster than normal length - no sqrt).
     * @param v second vector to compare
     * @return double distance squared between vectors
    */
    double dist_sq(const Vector2 &v) const;

    /**
     * Scales the vector down if it's larger than a specified value.
     * @param max maximum allowed length
    */
    void limit(double max);

    /**
     * Operator overload for adding two vectors.
     * @param v second vector to add
     * @return Vector2 the sum of two vectors
    */
    Vector2 operator+(const Vector2 &v) const;

    /**
     * Operator overload for substructing two vectors.
     * @param v second vector to substruct
     * @return Vector2 the difference of two vectors
    */
    Vector2 operator-(const Vector2 &v) const;

    /**
     * Operator overload for the cross product of two vectors.
     * @param v second vector to compare
     * @return double the result of the cross product
    */
    double operator*(const Vector2 &v) const;

    /**
     * Operator overload for multiplying by a scalar.
     * @param a a number to multiply by
     * @return Vector2 the result of scalar multiplication
    */
    Vector2 operator*(double a) const;

    /**
     * Operator overload for dividing by a scalar.
     * @param a a number to divide by
     * @return Vector2 the result of scalar division
    */
    Vector2 operator/(double a) const;

    /**
     * Operator overload for adding to a vector
     * @param v a vector to add
    */
    void operator+=(const Vector2 &v);

    /**
     * Operator overload for substructing from a vector
     * @param v a vector to substruct
    */
    void operator-=(const Vector2 &v);

    /**
     * Operator overload for multiplying a vector
     * @param a a scalar to multiply by
    */
    void operator*=(double a);
};
