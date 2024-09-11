#pragma once

#include <stdint.h>
#include <stdlib.h>

typedef uint64_t codepoint_t;

const char* render_rune(codepoint_t);
int rune_bytes(const char*);
size_t utf8_strlen(const char*);
