#include <iostream>
#include <cassert>
#include <cstdint>
#include <vector>

class Matrix {
 public:
  explicit Matrix(std::vector<std::vector<int32_t>> cells)
      : rows_(std::move(cells)) {
  }

  size_t Height() const {
    return rows_.size();
  }

  size_t Width() const {
    return rows_[0].size();
  }

  const std::vector<int32_t>& operator[](size_t index) const {
    return rows_[index];
  }

  friend Matrix operator*(const Matrix& lhs, const Matrix& rhs) {
    assert(lhs.Width() == rhs.Height());

    size_t n = lhs.Height();
    size_t m = lhs.Width();
    size_t k = rhs.Height();

    std::vector<std::vector<int32_t>> rows;
    rows.reserve(n);
    for (size_t i = 0; i < n; ++i) {
      std::vector<int32_t> row;
      row.reserve(k);
      for (size_t j = 0; j < k; ++j) {
        int32_t cell = 0;
        for (size_t s = 0; s < m; ++s) {
          cell += lhs[i][s] * rhs[s][j];
        }
        row.push_back(cell);
      }
      rows.push_back(std::move(row));
    }

    return Matrix{std::move(rows)};
  }

 private:
  std::vector<std::vector<int32_t>> rows_;
};

int main() {
  constexpr size_t kSize = 600;
  std::vector<std::vector<int32_t>> rows(kSize, std::vector<int32_t>(kSize, 0));
  Matrix lhs{rows};
  Matrix rhs{rows};

  Matrix product = lhs * rhs;
  std::cout << product[50][50] << std::endl;

  return 0;
}
