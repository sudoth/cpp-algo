#ifndef MATRIX
#define MATRIX

#include <stdexcept>
#include <iostream>

class MatrixOutOfRange : public std::out_of_range {
 public:
  MatrixOutOfRange() : std::out_of_range("MatrixOutOfRange") {
  }
};

template <class T, size_t N, size_t M>
class Matrix {
 public:
  T matrix[N][M];

  size_t RowsNumber() const {
    return N;
  }
  size_t ColumnsNumber() const {
    return M;
  }

  T& operator()(size_t y, size_t x) {
    return matrix[y][x];
  }

  const T& operator()(size_t y, size_t x) const {
    return matrix[y][x];
  }

  T& At(size_t y, size_t x) {
    if (y >= 0 && y < N && x >= 0 && x < M) {
      return matrix[y][x];
    }
    throw MatrixOutOfRange();
  }

  const T& At(size_t y, size_t x) const {
    if (y >= 0 && y < N && x >= 0 && x < M) {
      return matrix[y][x];
    }
    throw MatrixOutOfRange();
  }

  Matrix<T, N, M>& operator*=(T numb) {
    for (size_t i = 0; i < N; ++i) {
      for (size_t j = 0; j < M; ++j) {
        matrix[i][j] *= numb;
      }
    }
    return *this;
  }

  Matrix<T, N, M> operator*(T numb) {
    Matrix<T, N, M> res = *this;
    for (size_t i = 0; i < N; ++i) {
      for (size_t j = 0; j < M; ++j) {
        res.At(i, j) *= numb;
      }
    }
    return res;
  }

  Matrix<T, N, M>& operator/=(T numb) {
    for (size_t i = 0; i < N; ++i) {
      for (size_t j = 0; j < M; ++j) {
        matrix[i][j] /= numb;
      }
    }
    return *this;
  }

  Matrix<T, N, M> operator/(T numb) {
    Matrix<T, N, M> res = *this;
    for (size_t i = 0; i < N; ++i) {
      for (size_t j = 0; j < M; ++j) {
        res.At(i, j) /= numb;
      }
    }
    return res;
  }

  Matrix<T, N, M>& operator+=(Matrix<T, N, M> other) {
    for (size_t i = 0; i < N; ++i) {
      for (size_t j = 0; j < M; ++j) {
        matrix[i][j] += other.At(i, j);
      }
    }
    return *this;
  }

  Matrix<T, N, M>& operator-=(Matrix<T, N, M> other) {
    for (size_t i = 0; i < N; ++i) {
      for (size_t j = 0; j < M; ++j) {
        matrix[i][j] -= other.At(i, j);
      }
    }
    return *this;
  }

  bool operator==(Matrix<T, N, M> other) const {
    for (size_t i = 0; i < N; ++i) {
      for (size_t j = 0; j < M; ++j) {
        if (matrix[i][j] != other.At(i, j)) {
          return false;
        }
      }
    }
    return true;
  }

  bool operator!=(Matrix<T, N, M> other) const {
    for (size_t i = 0; i < N; ++i) {
      for (size_t j = 0; j < M; ++j) {
        if (matrix[i][j] != other.At(i, j)) {
          return true;
        }
      }
    }
    return false;
  }
};

template <class T, size_t N, size_t M, size_t K>
Matrix<T, N, K> operator*(Matrix<T, N, M> left, Matrix<T, M, K> right) {
  Matrix<T, N, K> res;
  for (size_t i = 0; i < N; ++i) {
    for (size_t j = 0; j < K; ++j) {
      res.At(i, j) = 0;
      for (size_t pos = 0; pos < M; ++pos) {
        res.At(i, j) += left.At(i, pos) * right.At(pos, j);
      }
    }
  }
  return res;
}

template <class T, size_t N, size_t M>
Matrix<T, N, M>& operator*=(Matrix<T, N, M>& left, Matrix<T, M, M> right) {
  Matrix<T, N, M> result = left * right;
  left = result;
  return left;
}

template <class T, class U, size_t N, size_t M>
Matrix<T, N, M> operator*(U numb, Matrix<T, N, M> matrix) {
  return matrix * numb;
}

template <class T, size_t N, size_t M>
Matrix<T, N, M> operator/(T numb, Matrix<T, N, M> matrix) {
  Matrix<T, N, M> res;
  for (size_t i = 0; i < N; ++i) {
    for (size_t j = 0; j < M; ++j) {
      res.At(i, j) = numb / matrix.At(i, j);
    }
  }
  return res;
}

template <class T, size_t N, size_t M>
Matrix<T, N, M> operator+(Matrix<T, N, M> left, Matrix<T, N, M> right) {
  Matrix<T, N, M> res;
  for (size_t i = 0; i < N; ++i) {
    for (size_t j = 0; j < M; ++j) {
      res.At(i, j) = left.At(i, j) + right.At(i, j);
    }
  }
  return res;
}

template <class T, size_t N, size_t M>
Matrix<T, N, M> operator-(Matrix<T, N, M> left, Matrix<T, N, M> right) {
  Matrix<T, N, M> res;
  for (size_t i = 0; i < N; ++i) {
    for (size_t j = 0; j < M; ++j) {
      res.At(i, j) = left.At(i, j) - right.At(i, j);
    }
  }
  return res;
}


template <class T, size_t N, size_t M>
std::ostream& operator<<(std::ostream& stream, Matrix<T, N, M> matrix) {
  for (size_t i = 0; i < N; ++i) {
    for (size_t j = 0; j < M; ++j) {
      if (j == M - 1) {
        stream << matrix.At(i, j) << std::endl;
        continue;
      }
      stream << matrix.At(i, j) << ' ';
    }
  }
  return stream;
}

template <class T, size_t N, size_t M>
std::istream& operator>>(std::istream& stream, Matrix<T, N, M>& matrix) {
  for (size_t i = 0; i < N; ++i) {
    for (size_t j = 0; j < M; ++j) {
      stream >> matrix.At(i, j);
    }
  }
  return stream;
}

template <class T, size_t N, size_t M>
Matrix<T, M, N> GetTransposed(Matrix<T, N, M> matrix) {
  Matrix<T, M, N> res;
  for (size_t i = 0; i < N; ++i) {
    for (size_t j = 0; j < M; ++j) {
      res.At(j, i) = matrix.At(i, j);
    }
  }
  return res;
}

#endif

int main() {
  Matrix<int, 2, 3> a{1, 2, 3, 4, 5, 6};
  Matrix<int, 4, 4> b{1, 2, 3, 4, 5, 6, ,7 ,8 ,9 10, 11, 12 ,13, 14, 15, 16};
  Matrix<int, 2, 2> c{1, 2, 3, 4};
}