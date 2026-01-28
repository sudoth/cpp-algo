#include <iostream>
#include <string>
#include "../point.h"
#include "../vector.h"
#include "../polygon.h"
#include "../ray.h"
#include "../line.h"
#include "../segment.h"
#include "../circle.h"
using namespace std;

int main(int argc, char** argv) {
  string str;
  cin >> str;
  geometry::Circle p;
  cin >> p;
  geometry::Point a;
  geometry::Point b;
  cin >> a >> b;
  cout << p.ContainsPoint(a) << '\n';
  cout << p.CrossesSegment(geometry::Segment(a, b)) << '\n';
  const auto vector_ab = b - a;
  const auto cloned_shape_ptr = p.Clone();
  std::cout << cloned_shape_ptr->Move(vector_ab).ToString() << '\n';
}