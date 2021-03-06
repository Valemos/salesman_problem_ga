#pragma once

#include <cmath>

class Destination {
public:
    double x;
    double y;

    Destination() = default;
    Destination(double x, double y) : x(x), y(y) {}

    double GetDistance(Destination& other) const {
        auto x_diff = x - other.x;
        auto y_diff = y - other.y;
        return std::sqrt(x_diff * x_diff + y_diff * y_diff);
    }

    void PrintInfo() const {
        std::cout << "(" << x << ", " << y << ")";
    }
};
