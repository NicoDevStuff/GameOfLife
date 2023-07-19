#include "log.h"
#include <stdarg.h>

void print_colored(LogColor color, int mode) {
    switch (mode) {
        case 0:
			printf("\033[0;32m");
            break;
        case 1:
            printf("\033[0;33m");
            break;
        case 2:
            printf("\033[0;31m");
            break;

        case 3:
            switch (color) {
                case COLOR_DEFAULT:
                    printf("\033[0m");  // Reset to default color
                    break;
                case COLOR_GREEN:
                    printf("\033[0;32m");  // Green color
                    break;
                case COLOR_RED:
                    printf("\033[0;31m");  // Red color
                    break;
                case COLOR_YELLOW:
                    printf("\033[0;33m");  // Yellow color
                    break;
                case COLOR_BLUE:
                    printf("\033[0;34m");  // Blue color
                    break;
                case COLOR_MAGENTA:
                    printf("\033[0;35m");  // Magenta color
                    break;
                case COLOR_CYAN:
                    printf("\033[0;36m");  // Cyan color
                    break;
                default:
                    printf("\033[0m");  // Default to reset color
                    break;
    	}
	}
}

void log_dn_fn(const char* format, ...)
{
#ifdef DEBUG
    va_list args;
    va_start(args, format);
    print_colored(COLOR_DEFAULT, 0);
    vprintf(format, args);
    print_colored(COLOR_DEFAULT, 3);
    printf("\n");
    va_end(args);
#endif
}

void log_dw_fn(const char* format, ...)
{
#ifdef DEBUG
    va_list args;
    va_start(args, format);
    print_colored(COLOR_YELLOW, 1);
    vprintf(format, args);
    print_colored(COLOR_DEFAULT, 3);   
	printf("\n");
    va_end(args);
#endif
}

void log_de_fn(const char* format, ...)
{
#ifdef DEBUG
    va_list args;
    va_start(args, format);
    print_colored(COLOR_RED, 2);
    vprintf(format, args);
    print_colored(COLOR_DEFAULT, 3); 
    printf("\n");
    va_end(args);
#endif
}

void log_dc(LogColor color, const char* format, ...) 
{
#ifdef DEBUG
    va_list args;
    va_start(args, format);
    print_colored(color, 3);
    vprintf(format, args);
    print_colored(COLOR_DEFAULT, 3);  // Reset color to default
    printf("\n");  // Append newline character
    va_end(args);
#endif
}
