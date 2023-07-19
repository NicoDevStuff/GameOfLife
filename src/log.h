#pragma once
#include <stdio.h>

#define LOG_DEFAULT_COLOR COLOR_DEFAULT

typedef enum {
    COLOR_DEFAULT,
    COLOR_GREEN,
    COLOR_RED,
    COLOR_YELLOW,
    COLOR_BLUE,
    COLOR_MAGENTA,
    COLOR_CYAN
} LogColor;

void log_dc(LogColor color, const char* format, ...);
void log_dn(const char* format, ...);
void log_de(const char* format, ...);
void log_dw(const char* format, ...);

#define log_dn(...) log_dn_fn(__VA_ARGS__)
#define log_de(...) log_de_fn(__VA_ARGS__)
#define log_dw(...) log_dw_fn(__VA_ARGS__)

