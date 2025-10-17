#include <cassert>
#include <iostream>
#include <vector>

class Matrix {
 public:
  Matrix(size_t height, std::vector<int> cells)
      : height_(height),
        cells_(std::move(cells)) {
    assert(cells_.size() % height_ == 0);
  }

  size_t Height() const {
    return height_;
  }

  size_t Width() const {
    return cells_.size() / height_;
  }

  int At(size_t i, size_t j) const {
    assert(i * height_ + j < cells_.size());
    return cells_[i * height_ + j];
  }

  friend Matrix operator*(const Matrix& lhs, const Matrix& rhs_t) {
    assert(lhs.Width() == rhs_t.Width());

    size_t n = lhs.Height();
    size_t m = lhs.Width();
    size_t k = rhs_t.Height();

    std::vector<int> cells;
    cells.reserve(n * k);
    for (size_t i = 0; i < n; ++i) {
      for (size_t j = 0; j < k; ++j) {
        int cell = 0;
        for (size_t s = 0; s < m; ++s) {
          int l = lhs.At(i, s);
          int r = rhs_t.At(j, s);
          cell += l * r;
        }
        cells.push_back(cell);
      }
    }

    return {n, std::move(cells)};
  }

 private:
  size_t height_;
  std::vector<int> cells_;
};

int main() {
  constexpr size_t kHeight = 600;
  constexpr size_t kWidth = 600;
  std::vector<int> cells(kHeight * kWidth, 0);
  Matrix lhs{kHeight, cells};
  Matrix rhs{kHeight, cells};

  Matrix product = lhs * rhs;
  std::cout << product.At(50, 50) << std::endl;

  return 0;
}
