#pragma once

struct v2 {
    float x, y;

    v2(float x, float y);
    v2(void);             // starts a vector to {0, 0, 0}
    explicit v2(float v); // vector with all values set to v

    v2 operator+(const v2 &) const;
    v2 operator-(const v2 &) const;
    v2 operator*(const v2 &) const;
    v2 operator/(const v2 &) const;

    v2 operator+=(const v2 &);
    v2 operator-=(const v2 &);
    v2 operator*=(const v2 &);
    v2 operator/=(const v2 &);

    v2 operator-(const float &) const;
    v2 operator+(const float &) const;
    v2 operator*(const float &) const;
    v2 operator/(const float &) const;

    v2 operator*=(const float &);
    v2 operator/=(const float &);
    v2 operator+=(const float &);
    v2 operator-=(const float &);

    bool operator==(const v2 &) const;
    bool operator!=(const v2 &) const;

    explicit operator float *() const;

  public:
    float volume() const;
};
