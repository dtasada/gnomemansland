#include "../include/v3.hpp"

v3::v3(float x, float y, float z) : x(x), y(y), z(z) {};
v3::v3(float v) : x(v), y(v), z(v) {};
v3::v3() : v3(0) {};

v3 v3::operator+(const v3 &rhs) const { return v3(x + rhs.x, y + rhs.y, z + rhs.z); }
v3 v3::operator-(const v3 &rhs) const { return v3(x - rhs.x, y - rhs.y, z - rhs.z); }
v3 v3::operator*(const v3 &rhs) const { return v3(x * rhs.x, y * rhs.y, z * rhs.z); }
v3 v3::operator/(const v3 &rhs) const { return v3(x / rhs.x, y / rhs.y, z / rhs.z); }

v3 v3::operator+=(const v3 &rhs) { return *this = *this + rhs; }
v3 v3::operator-=(const v3 &rhs) { return *this = *this - rhs; }
v3 v3::operator*=(const v3 &rhs) { return *this = *this * rhs; }
v3 v3::operator/=(const v3 &rhs) { return *this = *this / rhs; }

v3 v3::operator-(const float &rhs) const { return v3(x - rhs, y - rhs, z - rhs); }
v3 v3::operator+(const float &rhs) const { return v3(x + rhs, y + rhs, z + rhs); }
v3 v3::operator*(const float &rhs) const { return v3(x * rhs, y * rhs, z * rhs); }
v3 v3::operator/(const float &rhs) const { return v3(x / rhs, y / rhs, z / rhs); }

v3 v3::operator*=(const float &rhs) { return *this = *this * rhs; }
v3 v3::operator/=(const float &rhs) { return *this = *this / rhs; }
v3 v3::operator+=(const float &rhs) { return *this = *this + rhs; }
v3 v3::operator-=(const float &rhs) { return *this = *this - rhs; }

bool v3::operator==(const v3 &rhs) const { return x == rhs.x && y == rhs.y && z == rhs.z; }
bool v3::operator!=(const v3 &rhs) const { return !(*this == rhs); }

v3::operator float *() const { return new float[3]{x, y, z}; }

float v3::volume() const { return x * y * z; }
