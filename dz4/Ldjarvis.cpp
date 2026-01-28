#include <cmath>
#include <iomanip>
#include <iostream>

class Point {
 public:
  Point() = default;
  Point(const int64_t& a, const int64_t& b) : x(a), y(b) {
  }
  bool operator<(const Point&);
  bool operator==(const Point&);
  bool operator!=(const Point&);
  int64_t x;
  int64_t y;
};

class Vector {
 public:
  Vector() = default;
  Vector(const Point& a, const Point& b) {
    x = b.x - a.x;
    y = b.y - a.y;
  }
  int64_t x;
  int64_t y;
};

class Line {
 public:
  Line() = default;
  Line(const Point& p1, const Point& p2) {
    a = p1;
    b = p2;
  }
  Point a;
  Point b;
};

class Ray {
 public:
  Ray() = default;
  Ray(const Point& p1, const Point& p2) {
    begin = p1;
    b = p2;
  }
  Point begin;
  Point b;
};

class Segment {
 public:
  Segment() = default;
  Segment(const Point& p1, const Point& p2) {
    a = p1;
    b = p2;
  }
  Point a;
  Point b;
};

class Polygon {
 public:
  Polygon() = default;
  explicit Polygon(int64_t a) : n(a) {
    vertices = new Point[n];
  }
  ~Polygon() {
    delete[] vertices;
  }
  Polygon& operator=(const Polygon&);
  void Add(Point point) {
    vertices[k++] = point;
  }
  int64_t Area() const;
  Point* vertices;
  int64_t n;
  int64_t k = 0;
};

class SetOfPoints {
 public:
  SetOfPoints() = default;
  explicit SetOfPoints(const int& a) : n(a) {
    set = new Point[a]();
  }
  ~SetOfPoints() {
    delete[] set;
  }
  int n;
  Point* set;
};

bool Point::operator<(const Point& other) {
  return (this->x == other.x && this->y < other.y) || this->x < other.x;
}

bool Point::operator==(const Point& other) {
  return this->x == other.x && this->y == other.y;
}

bool Point::operator!=(const Point& other) {
  return this->x != other.x || this->y != other.y;
}

Polygon& Polygon::operator=(const Polygon& other) {
  if (this != &other) {
    this->k = other.k;
    this->n = other.n;
    for (int i = 0; i < other.k; i++) {
      this->vertices[i] = other.vertices[i];
    }
  }
  return *this;
}

std::istream& operator>>(std::istream& is, SetOfPoints& set) {
  for (int i = 0; i < set.n; ++i) {
    Point point;
    is >> point.x >> point.y;
    set.set[i] = point;
  }
  return is;
}

std::istream& operator>>(std::istream& is, Polygon& polygon) {
  for (int64_t i = 0; i < polygon.n; ++i) {
    Point point;
    is >> point.x >> point.y;
    polygon.vertices[i] = point;
  }
  return is;
}

std::istream& operator>>(std::istream& is, Point& point) {
  is >> point.x >> point.y;
  return is;
}

std::ostream& operator<<(std::ostream& os, const Point& point) {
  os << point.x << ' ' << point.y;
  return os;
}

std::ostream& operator<<(std::ostream& os, const Polygon& polygon) {
  for (int i = 0; i < polygon.k; ++i) {
    os << polygon.vertices[i] << '\n';
  }
  return os;
}

int64_t ScalarProduct(const Vector& vec1, const Vector& vec2) {
  return vec1.x * vec2.x + vec1.y * vec2.y;
}

int64_t VectorProduct(const Vector& vec1, const Vector& vec2) {
  return vec1.x * vec2.y - vec2.x * vec1.y;
}

bool IsOnLine(const Line& line, const Point& c) {
  return VectorProduct(Vector(line.a, line.b), Vector(line.a, c)) == 0;
}

bool IsOnRay(const Ray& ray, const Point& c) {
  return IsOnLine(Line(ray.begin, ray.b), c) && ScalarProduct(Vector(ray.begin, ray.b), Vector(ray.begin, c)) >= 0;
}

bool IsOnSegment(const Segment& segment, const Point& c) {
  return IsOnRay(Ray(segment.a, segment.b), c) && IsOnRay(Ray(segment.b, segment.a), c);
}

int64_t Polygon::Area() const {
  int64_t n = this->k;
  int64_t area = 0;
  for (int64_t i = 0; i < n - 1; i++) {
    area +=
        VectorProduct(Vector(this->vertices[0], this->vertices[i]), Vector(this->vertices[0], this->vertices[i + 1]));
  }
  return std::abs(area);
}

Polygon ConvexHull(const SetOfPoints& set) {
  int n = set.n;
  Polygon polygon(n);
  Point current = set.set[0];
  for (int i = 1; i < n; ++i) {
    if (set.set[i] < current) {
      current = set.set[i];
    }
  }
  polygon.Add(current);

  Point highest;
  while (true) {
    for (int i = 0; i < n; i++) {
      if (current != set.set[i]) {
        highest = set.set[i];
        break;
      }
    }
    for (int i = 0; i < n; ++i) {
      if (VectorProduct(Vector(current, highest), Vector(current, set.set[i])) == 0) {
        if ((highest != set.set[i]) &&
            ((current != set.set[i]) && (!IsOnSegment(Segment(current, highest), set.set[i])))) {
          highest = set.set[i];
        }
      }
      if (VectorProduct(Vector(current, highest), Vector(current, set.set[i])) > 0) {
        highest = set.set[i];
      }
    }
    if (highest == polygon.vertices[0]) {
      break;
    }
    polygon.Add(highest);
    current = highest;
  }
  return polygon;
}

int main() {
  int64_t n;
  std::cin >> n;
  SetOfPoints set(n);
  Polygon polygon(n);
  std::cin >> set;
  polygon = ConvexHull(set);
  std::cout << polygon.k << '\n';
  std::cout << polygon;
  int64_t area = polygon.Area();
  std::cout << area / 2;
  if (area % 2 == 0) {
    std::cout << ".0";
  } else {
    std::cout << ".5";
  }
}