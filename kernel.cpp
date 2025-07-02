#include "io.hpp"

// Multiboot Header
__attribute__((section(".multiboot")))
int multiboot_header[] = {
    0x1BADB002,
    0x00,
    -(0x1BADB002)
};

volatile char* vidmem;

void print_str_at(const char* s, int row, int col, unsigned char color = 0x0F) {
    int i = 0;
    while (s[i]) {
        int pos = (row * 80 + col + i) * 2;
        vidmem[pos] = s[i];
        vidmem[pos + 1] = color;
        i++;
    }
}

extern "C" void kernel_main() {
    vidmem = (char*)0xb8000;

    while (true) {
        // Xóa màn hình
        for (int i = 0; i < 80 * 25; i++) {
            vidmem[i * 2] = ' ';
            vidmem[i * 2 + 1] = 0x0F; // trắng trên nền đen
        }

        // In tiêu đề
        print_str_at("=== GIAI PHUONG TRINH BAC 2 ===", 0, 0);

        // Nhập a
        print_str_at("a:", 1, 0);
        float a = read_float(1, 4);

        // Nhập b
        print_str_at("b:", 2, 0);
        float b = read_float(2, 4);

        // Nhập c
        print_str_at("c:", 3, 0);
        float c = read_float(3, 4);

        // Tính delta
        float delta = b * b - 4 * a * c;

        // Hiển thị kết quả
        if (delta == 0) {
            float x = -b / (2 * a);
            print_float("Nghiem kep: ", x, 5);
        } else if (delta > 0) {
            float x1 = (-b + sqrt(delta)) / (2 * a);
            float x2 = (-b - sqrt(delta)) / (2 * a);
            print_float("x1 = ", x1, 5);
            print_float("x2 = ", x2, 6);
        } else {
            print_str_at("Phuong trinh vo nghiem.", 5, 0);
        }

        // Thông báo chờ Enter để tiếp tục
        print_str_at("Nhan Enter de tiep tuc...", 23, 0);

        // Chờ người dùng nhấn Enter
        while (getch() != '\n');
    }
}

