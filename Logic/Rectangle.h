#ifndef SUPERMEATBOY_RECTANGLE_H
#define SUPERMEATBOY_RECTANGLE_H


struct Vector {
    float x, y;
    Vector(float x, float y) : x(x), y(y) {
    }

    Vector operator+(const Vector& rhs) const {
        return {x + rhs.x, y + rhs.y};
    }

    Vector operator*(const Vector& rhs) const {
        return {x * rhs.x, y * rhs.y};
    }

    Vector operator*(const float& rhs) const {
        return {x * rhs, y * rhs};
    }
};

struct Rectangle {
    Vector mOrigin;
    float mWidth, mHeight;

    Rectangle(Vector center, float width, float height) : mOrigin(center), mHeight(height), mWidth(width) {

    }
};


#endif //SUPERMEATBOY_RECTANGLE_H
