#include <iostream>
#include <thread>

int main() {
  for (size_t i = 0;; ++i) {
    int x = 0;
    int y = 0;

    int r1 = 0;
    int r2 = 0;

    std::thread t1([&] {
      x = 1;
      r1 = y;
    });
    std::thread t2([&] {
      y = 1;
      r2 = x;
    });

    t1.join();
    t2.join();

    if (r1 == 0 && r2 == 0) {
      std::cout << "Iteration #" << i << ": CPU is broken" << std::endl;
      std::abort();
    }
  }
}
