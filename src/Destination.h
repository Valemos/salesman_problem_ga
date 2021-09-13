#include <cmath>

//
// Created by anton on 11.09.21.
//

#ifndef LAB1_SALESMAN_PROBLEM_DESTINATION_H
#define LAB1_SALESMAN_PROBLEM_DESTINATION_H

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


#endif //LAB1_SALESMAN_PROBLEM_DESTINATION_H
