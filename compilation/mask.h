#pragma once

#include <stdbool.h>
#include <stdlib.h>

void mask_from_utf8(const char* str, bool** matrix, size_t* rows,
                    size_t* columns);
