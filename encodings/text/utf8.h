#pragma once

#include <stdint.h>
#include <stdlib.h>

typedef uint64_t codepoint_t;

int codepoint_bytes(codepoint_t codepoint);
int rune_bytes(const char* rune);
const char* to_rune(codepoint_t codepoint);
codepoint_t to_codepoint(const char* rune);
size_t utf8_strlen(const char* str);
