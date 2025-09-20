#include <cstddef>
#include <cstdlib>

std::byte* alloc_two_cachelines() {
  return reinterpret_cast<std::byte*>(
      std::aligned_alloc(/*alignment=*/64, /*size=*/128));
}
