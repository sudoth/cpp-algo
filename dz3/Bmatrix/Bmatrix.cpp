#include <stdexcept>
#include <iostream>

class MatrixOutOfRange : public std::out_of_range {
 public:
  MatrixOutOfRange() : std::out_of_range("MatrixOutOfRange") {
  }
};

class MatrixIsDegenerateError : public std::runtime_error {
 public:
  MatrixIsDegenerateError() : std::runtime_error("MatrixIsDegenerateError") {
  }
};


template <typename T, size_t N, size_t M>
class Matrix {
 public:
  T matrix[N][M];
  size_t RowsNumber() const;
  size_t ColumnsNumber() const;
  T& operator()(size_t, size_t);
  const T& operator()(size_t, size_t) const;
  T& At(size_t, size_t);
  const T& At(size_t, size_t) const;
  Matrix<T, N, M>& operator*=(T);
  Matrix<T, N, M> operator*(T);
  Matrix<T, N, M>& operator/=(T);
  Matrix<T, N, M> operator/(T);
  Matrix<T, N, M>& operator+=(Matrix<T, N, M>);
  Matrix<T, N, M>& operator-=(Matrix<T, N, M>);
  bool operator==(Matrix<T, N, M>) const;
  bool operator!=(Matrix<T, N, M>) const;
  void Transpose(Matrix<T, N, M>);
};

template <typename T, size_t N, size_t M>
size_t Matrix<T, N, M>::RowsNumber() const {
  return N;
}

template <typename T, size_t N, size_t M>
size_t Matrix<T, N, M>::ColumnsNumber() const {
  return M;
}

template <typename T, size_t N, size_t M>
T& Matrix<T, N, M>::operator()(size_t y, size_t x) {
  return matrix[y][x];
}

template <typename T, size_t N, size_t M>
const T& Matrix<T, N, M>::operator()(size_t y, size_t x) const {
  return matrix[y][x];
}

template <typename T, size_t N, size_t M>
T& Matrix<T, N, M>::At(size_t y, size_t x) {
  if (y < 0 || y >= N || x < 0 || x >= M) {
    throw MatrixOutOfRange{};
  }
  return matrix[y][x];
}

template <typename T, size_t N, size_t M>
const T& Matrix<T, N, M>::At(size_t y, size_t x) const {
  if (y < 0 || y >= N || x < 0 || x >= M) {
    throw MatrixOutOfRange{};
  }
  return matrix[y][x];
}

template <typename T, size_t N, size_t M>
Matrix<T, N, M>& Matrix<T, N, M>::operator*=(T value) {
  for (size_t i = 0; i < N; ++i) {
    for (size_t j = 0; j < M; ++j) {
      matrix[i][j] *= value;
    }
  }
  return *this;
}

template <typename T, size_t N, size_t M>
Matrix<T, N, M> Matrix<T, N, M>::operator*(T value) {
  Matrix<T, N, M> other = *this;
  for (size_t i = 0; i < N; ++i) {
    for (size_t j = 0; j < M; ++j) {
      other(i, j) *= value;
    }
  }
  return other;
}

template <typename T, size_t N, size_t M>
Matrix<T, N, M>& Matrix<T, N, M>::operator+=(Matrix<T, N, M> other) {
  for (size_t i = 0; i < N; ++i) {
    for (size_t j = 0; j < M; ++j) {
      matrix[i][j] += other(i, j);
    }
  }
  return *this;
}

template <typename T, size_t N, size_t M>
Matrix<T, N, M>& Matrix<T, N, M>::operator-=(Matrix<T, N, M> other) {
  for (size_t i = 0; i < N; ++i) {
    for (size_t j = 0; j < M; ++j) {
      matrix[i][j] -= other(i, j);
    }
  }
  return *this;
}

template <typename T, size_t N, size_t M>
Matrix<T, N, M>& Matrix<T, N, M>::operator/=(T value) {
  for (size_t i = 0; i < N; ++i) {
    for (size_t j = 0; j < M; ++j) {
      matrix[i][j] /= value;
    }
  }
  return *this;
}

template <typename T, size_t N, size_t M>
Matrix<T, N, M> Matrix<T, N, M>::operator/(T value) {
  Matrix<T, N, M> other = *this;
  for (size_t i = 0; i < N; ++i) {
    for (size_t j = 0; j < M; ++j) {
      other(i, j) /= value;
    }
  }
  return other;
}

template <typename T, size_t N, size_t M>
bool Matrix<T, N, M>::operator==(Matrix<T, N, M> other) const {
  for (size_t i = 0; i < N; ++i) {
    for (size_t j = 0; j < M; ++j) {
      if (matrix[i][j] != other(i, j)) {
        return false;
      }
    }
  }
  return true;
}

template <typename T, size_t N, size_t M>
bool Matrix<T, N, M>::operator!=(Matrix<T, N, M> other) const {
  for (size_t i = 0; i < N; ++i) {
    for (size_t j = 0; j < M; ++j) {
      if (matrix[i][j] != other(i, j)) {
        return true;
      }
    }
  }
  return false;
}

template <typename T, size_t N, size_t M, size_t K>
Matrix<T, N, K> operator*(Matrix<T, N, M> first, Matrix<T, M, K> second) {
  Matrix<T, N, K> other;
  for (size_t i = 0; i < N; ++i) {
    for (size_t j = 0; j < K; ++j) {
      other(i, j) = 0;
      for (size_t idx = 0; idx < M; ++idx) {
        other(i, j) += first(i, idx) * second(idx, j);
      }
    }
  }
  return other;
}

template <typename T, size_t N, size_t M>
Matrix<T, N, M>& operator*=(Matrix<T, N, M>& first, Matrix<T, M, M> second) {
  Matrix<T, N, M> result = first * second;
  first = result;
  return first;
}

template <typename T, typename U, size_t N, size_t M>
Matrix<T, N, M> operator*(U value, Matrix<T, N, M> matrix) {
  return matrix * value;
}

template <typename T, size_t N, size_t M>
Matrix<T, N, M> operator+(Matrix<T, N, M> first, Matrix<T, N, M> second) {
  Matrix<T, N, M> other;
  for (size_t i = 0; i < N; ++i) {
    for (size_t j = 0; j < M; ++j) {
      other(i, j) = first(i, j) + second(i, j);
    }
  }
  return other;
}

template <typename T, size_t N, size_t M>
Matrix<T, N, M> operator-(Matrix<T, N, M> first, Matrix<T, N, M> second) {
  Matrix<T, N, M> other;
  for (size_t i = 0; i < N; ++i) {
    for (size_t j = 0; j < M; ++j) {
      other(i, j) = first(i, j) - second(i, j);
    }
  }
  return other;
}

template <typename T, size_t N, size_t M>
std::ostream& operator<<(std::ostream& os, Matrix<T, N, M> matrix) {
  for (size_t i = 0; i < N; ++i) {
    for (size_t j = 0; j < M; ++j) {
      if (j == M - 1) {
        os << matrix(i, j) << std::endl;
        continue;
      }
      os << matrix(i, j) << ' ';
    }
  }
  return os;
}

template <typename T, size_t N, size_t M>
std::istream& operator>>(std::istream& is, Matrix<T, N, M>& matrix) {
  for (size_t i = 0; i < N; ++i) {
    for (size_t j = 0; j < M; ++j) {
      is >> matrix(i, j);
    }
  }
  return is;
}

template <typename T, size_t N, size_t M>
Matrix<T, M, N> GetTransposed(Matrix<T, N, M> matrix) {
  Matrix<T, M, N> other;
  for (size_t i = 0; i < N; ++i) {
    for (size_t j = 0; j < M; ++j) {
      other(j, i) = matrix(i, j);
    }
  }
  return other;
}

void Swap(int& x, int& y) {
  x ^= y;
  y ^= x;
  x ^= y;
}

template <typename T, size_t N, size_t M>
void Transpose(Matrix<T, N, M>& matrix) {
  if (N != M) {
    throw MatrixOutOfRange{};
  }
  for (int i = 0; i < N; ++i) {
    for (int j = 0; j < M; ++j) {
      if (i > j) {
        Swap(matrix(i, j), matrix(j, i));
      }
    }
  }
}

template <typename T, size_t N, size_t M>
int Trace(const Matrix<T, N, M>& matrix) {
  if (N != M) {
    throw MatrixOutOfRange{};
  }
  int ans = 0;
  for (int i = 0; i < N; i++) {
    ans += matrix(i, i);
  }
  return ans;
}

template <typename T, size_t N, size_t M>
constexpr Matrix<T, N, M> SubMatrix(Matrix<T, N + 1, M + 1> matrix, int i_del, int& j_del) {
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < M; j++) {
      int i_idx = i > i_del ? i - 1 : i;
      int j_idx = j > j_del ? j - 1 : j;
      matrix(i_idx, j_idx) = matrix(i, j);
    }
  }
  return sub;
}

template <typename T, size_t N, size_t M>
constexpr int Determinant(const Matrix<T, N, M>& matrix) {
  if (N == 1 && M == 1) {
    return matrix(0, 0);
  }
  int sub_det = 0;
  for (int j = 0; j < N; j++) {
    sub_det += matrix(0, j) * (j % 2 == 0 ? 1 : -1) * Determinant(Matrix<T, N, M>(matrix, 0, j));
  }
  return sub_det;
}

int main() {
  Matrix<int, 3, 3> a = {1, 2, 3, 4, 5, 6, 7, 8, 9};
  std::cout << Determinant(a);
}