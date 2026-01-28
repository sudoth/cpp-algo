#include <iostream>
#include <cstring>
#include <algorithm>

struct StudentData {
  char name[40];
  char surname[40];
  int sum_of_points;
};

bool Comparator(StudentData a, StudentData b) {
  return a.sum_of_points > b.sum_of_points;
}

int main() {
  int n;
  std::cin >> n;
  auto data = new StudentData[n];
  auto student = new StudentData;
  for (int i = 0; i < n; i++) {
    char name[40];
    std::cin >> name;
    int len = strlen(name);
    for (int i = 0; i < len; i++) {
      student->name[i] = name[i];
    }
    student->name[len] = '\0';
    char surname[40];
    std::cin >> surname;
    len = strlen(surname);
    for (int i = 0; i < len; i++) {
      student->surname[i] = surname[i];
    }
    student->surname[len] = '\0';
    int sum_of_points = 0;
    for (int i = 0; i < 3; i++) {
      int t;
      std::cin >> t;
      sum_of_points += t;
    }
    student->sum_of_points = sum_of_points;
    data[i] = *student;
  }
  std::stable_sort(data, data + n, Comparator);
  for (int i = 0; i < n; i++) {
    std::cout << data[i].name << ' ';
    std::cout << data[i].surname << '\n';
  }
  delete student;
  delete[] data;
}