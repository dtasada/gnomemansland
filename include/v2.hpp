#pragma once

struct v2 {
    float x, y;

    v2(float x, float y);
    v2(void);             // starts a vector to {0, 0, 0}
    explicit v2(float v); // vector with all values set to v

    v2 operator+(const v2 &other) const;
    v2 operator-(const v2 &other) const;
    v2 operator*(const v2 &other) const;
    v2 operator/(const v2 &other) const;

    v2 operator+=(const v2 &other);
    v2 operator-=(const v2 &other);
    v2 operator*=(const v2 &other);
    v2 operator/=(const v2 &other);

    v2 operator-(const float &other) const;
    v2 operator+(const float &other) const;
    v2 operator*(const float &other) const;
    v2 operator/(const float &other) const;

    v2 operator*=(const float &other);
    v2 operator/=(const float &other);
    v2 operator+=(const float &other);
    v2 operator-=(const float &other);

    bool operator==(const v2 &other) const;
    bool operator!=(const v2 &other) const;

    explicit operator float *() const;

  public:
    float volume() const;
};
