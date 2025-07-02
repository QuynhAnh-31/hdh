#include "io.hpp"
char scancode_to_ascii[128] = {
    0, 27, '1','2','3','4','5','6','7','8','9','0','-','=', '\b',
    '\t','q','w','e','r','t','y','u','i','o','p','[',']','\n', 0,
    'a','s','d','f','g','h','j','k','l',';','\'','`', 0,'\\',
    'z','x','c','v','b','n','m',',','.','/', 0, '*', 0,' ',
    0, // F1-F10...
};

char getch() {
    unsigned char scancode = 0;
    while ((inb(0x64) & 1) == 0);
    scancode = inb(0x60);

    // Bỏ qua phím nhả (release)
    if (scancode >= 0x80) return 0;

    return scancode_to_ascii[scancode];
}

float read_float(int row, int col) {
    char buffer[32];
    int idx = 0;
    bool has_dot = false;

    while (true) {
        char c = 0;
        while ((c = getch()) == 0); // Chờ ký tự hợp lệ

        if (c == '\n' || c == '\r') {  // Enter
            buffer[idx] = '\0';
            break;
        }

        if (c == '\b') {  // Backspace
            if (idx > 0) {
                idx--;
                col--;
                buffer[idx] = '\0';

                // Xóa trên màn hình
                vidmem[(row * 80 + col) * 2] = ' ';
                vidmem[(row * 80 + col) * 2 + 1] = 0x07;
            }
            continue;
        }

        if ((c >= '0' && c <= '9') || (c == '.' && !has_dot) || (c == '-' && idx == 0)) {
            if (c == '.') has_dot = true;
            buffer[idx++] = c;

            vidmem[(row * 80 + col++) * 2] = c;
            vidmem[(row * 80 + col) * 2 + 1] = 0x07;
        }
    }

    float val = 0.0f;
    int i = 0;
    bool is_negative = false;

    if (buffer[0] == '-') {
        is_negative = true;
        i = 1;
    }

    while (buffer[i] && buffer[i] != '.') {
        val = val * 10 + (buffer[i] - '0');
        i++;
    }

    if (buffer[i] == '.') {
        i++;
        float scale = 0.1f;
        while (buffer[i]) {
            val += (buffer[i] - '0') * scale;
            scale *= 0.1f;
            i++;
        }
    }

    if (is_negative) val = -val;

    return val;
}

void print_float(const char* label, float value, int row) {
    int col = 0;
    for (int i = 0; label[i]; i++) {
        vidmem[(row * 80 + col++) * 2] = label[i];
    }

    if (value < 0) {
        vidmem[(row * 80 + col++) * 2] = '-';
        value = -value;
    }

    int int_part = (int)value;
    float frac_part = value - int_part;

    // In phần nguyên
    char int_buf[10];
    int int_len = 0;
    do {
        int_buf[int_len++] = '0' + int_part % 10;
        int_part /= 10;
    } while (int_part);

    for (int i = int_len - 1; i >= 0; i--) {
        vidmem[(row * 80 + col++) * 2] = int_buf[i];
    }

    // In dấu chấm
    vidmem[(row * 80 + col++) * 2] = '.';

    // In phần thập phân 8 chữ số
    for (int k = 0; k < 8; k++) {
        frac_part *= 10;
        int digit = (int)frac_part;
        vidmem[(row * 80 + col++) * 2] = '0' + digit;
        frac_part -= digit;
    }
}

float sqrt(float x) {
    if (x < 0) return 0;
    float res = x;
    float delta;
    do {
        float prev = res;
        res = 0.5f * (res + x / res);
        delta = res - prev;
        if (delta < 0) delta = -delta;
    } while (delta > 1e-6f);
    return res;
}
