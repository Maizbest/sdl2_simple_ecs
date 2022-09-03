#include "game/Vector2d.h"

Vector2d::Vector2d() : x(0.0f), y(0.0f) {}

Vector2d::Vector2d(float x, float y) : x(x), y(y) {}

Vector2d::Vector2d(const Vector2d& vec) : x(vec.x), y(vec.y) {}

Vector2d::~Vector2d() {}

Vector2d& Vector2d::Add(const Vector2d& vec) {
  this->x += vec.x;
  this->y += vec.y;
  return *this;
}

Vector2d& Vector2d::Sub(const Vector2d& vec) {
  this->x -= vec.x;
  this->y -= vec.y;
  return *this;
}

Vector2d& Vector2d::Mul(const Vector2d& vec) {
  this->x *= vec.x;
  this->y *= vec.y;
  return *this;
}

Vector2d& Vector2d::Div(const Vector2d& vec) {
  this->x /= vec.x;
  this->y /= vec.y;
  return *this;
}

Vector2d& Vector2d::Mul(const float val) {
  this->x *= val;
  this->y *= val;
  return *this;
}

Vector2d& Vector2d::Div(const float val) {
  this->x /= val;
  this->y /= val;
  return *this;
}

// Vector2d& operator+(Vector2d& v1, const Vector2d& v2) { return Vector2d(v1).Add(v2); }

// Vector2d& operator-(Vector2d& v1, const Vector2d& v2) { return Vector2d(v1).Sub(v2); }

// Vector2d& operator*(Vector2d& v1, const Vector2d& v2) { return Vector2d(v1).Mul(v2); }

// Vector2d& operator/(Vector2d& v1, const Vector2d& v2) { return Vector2d(v1).Div(v2); }

// Vector2d& Vector2d::operator+=(Vector2d& vec) {
//   return this->Add(vec);
// }

// Vector2d& Vector2d::operator-=(Vector2d& vec) {
//   return this->Sub(vec);
// }

// Vector2d& Vector2d::operator*=(Vector2d& vec) {
//   return this->Mul(vec);
// }

// Vector2d& Vector2d::operator/=(Vector2d& vec) {
//   return this->Div(vec);
// }

// Vector2d& Vector2d::operator/=(const float val) {
//   return this->Div(val);
// }

// Vector2d& Vector2d::operator*=(const float val) {
//   return this->Mul(val);
// }

Vector2d& operator*(Vector2d& v1, const float val) {
  return Vector2d(v1).Mul(val);
}

Vector2d& operator/(Vector2d& v1, const float val) {
  return Vector2d(v1).Div(val);
}

std::ostream& operator<<(std::ostream& stream, const Vector2d& vec) {
  stream << "(" << vec.x << ", " << vec.y << ")";
  return stream;
}
