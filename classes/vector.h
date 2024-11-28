#ifndef VECTOR_H
#define VECTOR_H

class Vector {
public:
    Vector(float x, float y);
    ~Vector();

    float getX();
    float getY();
    void rotate90(char direction);
    void rotate180();
    void setX(float i);
    void setY(float i);
    void reverseX();
    void reverseY();
    Vector normalise();
    Vector multiply(float n);
private:
    float x, y;
};

#endif