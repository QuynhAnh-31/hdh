#ifndef IO_HPP
#define IO_HPP

extern volatile char* vidmem;

char getch();
float read_float(int row, int col);
void print_float(const char* label, float value, int row);
float sqrt(float x);

static inline unsigned char inb(unsigned short port) {
    unsigned char result;
    __asm__ volatile ("inb %1, %0" : "=a"(result) : "Nd"(port));
    return result;
}

#endif
