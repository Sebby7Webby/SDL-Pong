#include "vector.h"
#include <math.h>

Vector::Vector(float x, float y)
    : x(x), y(y) {}

Vector::~Vector() {}

float Vector::getX() {return x;}
float Vector::getY() {return y;}
void Vector::setX(float i) {x=i;}
void Vector::setY(float i) {y=i;}

void Vector::rotate90(char direction) {
    if (direction == 'l') {
        float tmp = -x;
        x = y;
        y = tmp;
    } else if (direction == 'r') {
        float tmp = -y;
        y = x;
        x = tmp;
    } else {
        throw "Failed to parse given direction in Vector::rotate90(char direction)\n Not 'l' or 'r'";
    }
}
void Vector::rotate180() {
    x = -x;
    y = -y;
}

void Vector::reverseX() {x=-x;}
void Vector::reverseY() {y=-y;}

Vector Vector::normalise() {
    double magnitude = sqrt(x*x+y*y);
    return Vector(x/magnitude, y/magnitude);
}

Vector Vector::multiply(float n) {
    return Vector(x*n, y*n);
}