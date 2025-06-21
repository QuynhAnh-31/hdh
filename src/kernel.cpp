#include <stdint.h>

static uint8_t x = 0, y = 0;

void printf(const char* str) {
    static uint16_t* VideoMemory = (uint16_t*)0xb8000;
    for (int i = 0; str[i] != '\0'; ++i) {
        if (str[i] == '\n') { x = 0; y++; }
        else {
            VideoMemory[80*y + x] = (VideoMemory[80*y + x] & 0xFF00) | str[i];
            x++;
        }
        if (x >= 80) { x = 0; y++; }
        if (y >= 25) { x = 0; y = 0; }
    }
}

void printfChar(char c) {
    char s[2] = {c, '\0'};
    printf(s);
}

void printInt(int n) {
    if (n == 0) { printf("0"); return; }
    if (n < 0) { printf("-"); n = -n; }
    char buf[16]; int i = 0;
    while (n > 0) { buf[i++] = '0' + (n % 10); n /= 10; }
    while (i--) printfChar(buf[i]);
}

void giaiPTBac2(int a, int b, int c) {
    printf("Giai phuong trinh bac 2: ");
    if (a != 1) printInt(a);
    printf("x^2 ");
    if (b >= 0) printf("+ "); printInt(b); printf("x ");
    if (c >= 0) printf("+ "); printInt(c); printf(" = 0\n");

    int delta = b*b - 4*a*c;
    if (delta < 0) {
        printf("Phuong trinh vo nghiem\n");
    } else if (delta == 0) {
        int x = -b / (2*a);
        printf("Phuong trinh co nghiem kep x = "); printInt(x); printf("\n");
    } else {
        int sqrt_delta = 1;
        while (sqrt_delta * sqrt_delta <= delta) ++sqrt_delta;
        --sqrt_delta;
        int x1 = (-b + sqrt_delta) / (2*a);
        int x2 = (-b - sqrt_delta) / (2*a);
        printf("x1 = "); printInt(x1);
        printf(", x2 = "); printInt(x2); printf("\n");
    }
}

extern "C" void kernelMain() {
    printf("hello worlds\n");
    giaiPTBac2(1, -3, 2);
}
