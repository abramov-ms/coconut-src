#include <cstdint>
#include <cstdlib>
#include <cstddef>
#include <thread>
#include <iostream>
#include <bitset>

int main() {
  auto* bytes = reinterpret_cast<std::byte*>(
      std::aligned_alloc(/*alignment=*/64, /*size=*/128));

  void* addr = bytes + 62;
  new (addr) uint32_t{0};

  auto* n = reinterpret_cast<uint32_t*>(addr);

  auto check_n = [](uint32_t n) {
    if (n != 0 && n != ~uint32_t{0}) {
      std::cerr << "n = " << std::bitset<32>{n} << std::endl;
      std::abort();
    }
  };

  std::thread t0([&] {
    while (true) {
      check_n(*n);
      *n = 0;
    }
  });

  std::thread t1([&] {
    while (true) {
      check_n(*n);
      *n = ~uint32_t{0};
    }
  });

  t0.join();
  t1.join();

  return 0;
}
