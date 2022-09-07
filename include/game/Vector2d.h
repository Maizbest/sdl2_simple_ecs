#ifndef C8847823_8081_4B18_9F0A_6DFABF415254
#define C8847823_8081_4B18_9F0A_6DFABF415254

#include <ostream>

class Vector2d {
 public:
  float x, y;

  Vector2d();
  Vector2d(const Vector2d& vec);
  Vector2d(float x, float y);
  ~Vector2d();

  static Vector2d Zero() { return Vector2d(0.0, 0.0); }

  Vector2d& Add(const Vector2d& vec);
  Vector2d& Sub(const Vector2d& vec);
  Vector2d& Mul(const Vector2d& vec);
  Vector2d& Div(const Vector2d& vec);

  Vector2d& Mul(const float val);
  Vector2d& Div(const float val);

  friend Vector2d operator+(const Vector2d& vecA, const Vector2d& vecB);
  friend Vector2d operator-(const Vector2d& vecA, const Vector2d& vecB);

  // friend Vector2d& operator*(Vector2d& v1, const Vector2d& v2);
  // friend Vector2d& operator/(Vector2d& v1, const Vector2d& v2);

  friend Vector2d& operator*(Vector2d& v1, const float val);
  friend Vector2d& operator/(Vector2d& v1, const float val);

  Vector2d& operator+=(Vector2d& vec);
  // Vector2d& operator-=(Vector2d& vec);
  // Vector2d& operator*=(Vector2d& vec);
  // Vector2d& operator/=(Vector2d& vec);

  Vector2d& operator*=(const float vec);
  Vector2d& operator/=(const float vec);

  Vector2d& operator*(const int& i);

  friend std::ostream& operator<<(std::ostream& stream, const Vector2d& vec);
};

#endif /* C8847823_8081_4B18_9F0A_6DFABF415254 */
