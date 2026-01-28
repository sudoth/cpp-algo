#ifndef ISHAPE_H
#define ISHAPE_H
#include <string>
namespace geometry {
class Segment;
class Vector;
class Point;
class IShape {
 public:
  virtual IShape& Move(const geometry::Vector&) = 0;
  virtual bool ContainsPoint(const geometry::Point&) const = 0;
  virtual bool CrossesSegment(const geometry::Segment&) const = 0;
  virtual IShape* Clone() const = 0;
  virtual std::string ToString() const = 0;
  virtual ~IShape() = default;
};
}
#endif