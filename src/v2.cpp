#include "../include/v2.hpp"

v2::v2(float x, float y) : x(x), y(y) {};
v2::v2(float v) : x(v), y(v) {};
v2::v2() : v2(0) {};

v2 v2::operator+(const v2 &rhs) const { return v2(x + rhs.x, y + rhs.y); }
v2 v2::operator-(const v2 &rhs) const { return v2(x - rhs.x, y - rhs.y); }
v2 v2::operator*(const v2 &rhs) const { return v2(x * rhs.x, y * rhs.y); }
v2 v2::operator/(const v2 &rhs) const { return v2(x / rhs.x, y / rhs.y); }

v2 v2::operator+=(const v2 &rhs) { return *this = *this + rhs; }
v2 v2::operator-=(const v2 &rhs) { return *this = *this - rhs; }
v2 v2::operator*=(const v2 &rhs) { return *this = *this * rhs; }
v2 v2::operator/=(const v2 &rhs) { return *this = *this / rhs; }

v2 v2::operator-(const float &rhs) const { return v2(x - rhs, y - rhs); }
v2 v2::operator+(const float &rhs) const { return v2(x + rhs, y + rhs); }
v2 v2::operator*(const float &rhs) const { return v2(x * rhs, y * rhs); }
v2 v2::operator/(const float &rhs) const { return v2(x / rhs, y / rhs); }

v2 v2::operator*=(const float &rhs) { return *this = *this * rhs; }
v2 v2::operator/=(const float &rhs) { return *this = *this / rhs; }
v2 v2::operator+=(const float &rhs) { return *this = *this + rhs; }
v2 v2::operator-=(const float &rhs) { return *this = *this - rhs; }

bool v2::operator==(const v2 &rhs) const { return x == rhs.x && y == rhs.y; }
bool v2::operator!=(const v2 &rhs) const { return !(*this == rhs); }

v2::operator float *() const { return new float[3]{x, y}; }

float v2::volume() const { return x * y; };
