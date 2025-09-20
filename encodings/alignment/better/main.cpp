#include "alloc.h"

#include <atomic>
#include <bitset>
#include <cstdint>
#include <thread>
#include <iostream>

int main() {
  std::byte* bytes = alloc_two_cachelines();

  auto* addr = bytes + 62;
  new (addr) std::atomic<uint32_t>{0};

  auto* n = reinterpret_cast<std::atomic<uint32_t>*>(addr);

  auto check_n = [](uint32_t n) {
    if (n != 0 && n != ~uint32_t{0}) {
      std::cerr << "n = " << std::bitset<32>{n} << std::endl;
      std::abort();
    }
  };

  std::thread t0([&] {
    while (true) {
      check_n(n->load(std::memory_order::relaxed));
      n->store(0, std::memory_order::relaxed);
    }
  });

  std::thread t1([&] {
    while (true) {
      check_n(n->load(std::memory_order::relaxed));
      n->store(~uint32_t{0}, std::memory_order::relaxed);
    }
  });

  t0.join();
  t1.join();

  return 0;
}
