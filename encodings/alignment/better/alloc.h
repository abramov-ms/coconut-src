#include <cstddef>

// caller should free with std::free()
std::byte* alloc_two_cachelines();
