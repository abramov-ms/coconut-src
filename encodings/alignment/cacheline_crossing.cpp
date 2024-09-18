#include <cstdlib>
#include <cstdint>
#include <atomic>
#include <thread>
#include <iostream>

int main() {
  // https://en.cppreference.com/w/cpp/thread/hardware_destructive_interference_size
  static constexpr size_t kCachelineSize = 64;

  auto* cachelines = static_cast<uint8_t*>(
      std::aligned_alloc(/*alignment=*/kCachelineSize, kCachelineSize * 2));

  // [..., 62, 63] [0, 1, 2, 3, 4, 5, ...]
  auto* misaligned = reinterpret_cast<std::atomic<uint64_t>*>(cachelines + 62);
  new (misaligned) std::atomic<uint64_t>{0};

  std::thread writer([&] {
    while (true) {
      misaligned->store(0);
      misaligned->store(uint64_t(-1));
    }
  });

  std::thread reader([&] {
    while (true) {
      uint64_t value = misaligned->load();

      if (value != 0 && value != uint64_t(-1)) {
        std::cout << "World is broken: value = " << value << std::endl;
        std::quick_exit(1);
      }
    }
  });

  writer.join();
  reader.join();
}
