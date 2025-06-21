#include <drivers/keyboard.h>

using namespace myos::common;
using namespace myos::drivers;
using namespace myos::hardwarecommunication;

void clearScreen();
static uint16_t flag = 0, op = 0;
static int64_t first = 0, second = 0;

uint64_t divide(uint64_t a, uint64_t b) {
    if (b == 0) return 0;
    uint64_t quotient = 0;
    while (a >= b) {
        a -= b;
        quotient++;
    }
    return quotient;
}

uint64_t mod(uint64_t a, uint64_t b) {
    if (b == 0) return 0;
    while (a >= b) {
        a -= b;
    }
    return a;
}

KeyboardEventHandler::KeyboardEventHandler() {}

void KeyboardEventHandler::OnKeyDown(char) {}

void KeyboardEventHandler::OnKeyUp(char) {}

KeyboardDriver::KeyboardDriver(InterruptManager* manager, KeyboardEventHandler *handler)
: InterruptHandler(manager, 0x21),
dataport(0x60),
commandport(0x64) {
    this->handler = handler;
}

KeyboardDriver::~KeyboardDriver() {}

void printf(char*);
void printfHex(uint8_t);

void KeyboardDriver::Activate() {
    while(commandport.Read() & 0x1)
        dataport.Read();
    commandport.Write(0xae); // activate interrupts
    commandport.Write(0x20); // command 0x20 = read controller command byte
    uint8_t status = (dataport.Read() | 1) & ~0x10;
    commandport.Write(0x60); // command 0x60 = set controller command byte
    dataport.Write(status);
    dataport.Write(0xf4);
}

uint32_t KeyboardDriver::HandleInterrupt(uint32_t esp) {

    uint8_t key = dataport.Read();
    
    if(handler == 0)
        return esp;
    
    if(key < 0x80) {
        switch(key) {
            case 0x02:
                printf("1");
                if (flag == 0) first = first * 10 + 1;
                else if (flag == 1) second = second * 10 + 1;
                else { first = 0; second = 0; }
                break;
            case 0x03:
                printf("2");
                if (flag == 0) first = first * 10 + 2;
                else if (flag == 1) second = second * 10 + 2;
                else { first = 0; second = 0; }
                break;
            case 0x04:
                printf("3");
                if (flag == 0) first = first * 10 + 3;
                else if (flag == 1) second = second * 10 + 3;
                else { first = 0; second = 0; }
                break;
            case 0x05:
                printf("4");
                if (flag == 0) first = first * 10 + 4;
                else if (flag == 1) second = second * 10 + 4;
                else { first = 0; second = 0; }
                break;
            case 0x06:
                printf("5");
                if (flag == 0) first = first * 10 + 5;
                else if (flag == 1) second = second * 10 + 5;
                else { first = 0; second = 0; }
                break;
            case 0x07:
                printf("6");
                if (flag == 0) first = first * 10 + 6;
                else if (flag == 1) second = second * 10 + 6;
                else { first = 0; second = 0; }
                break;
            case 0x08:
                printf("7");
                if (flag == 0) first = first * 10 + 7;
                else if (flag == 1) second = second * 10 + 7;
                else { first = 0; second = 0; }
                break;
            case 0x09:
                printf("8");
                if (flag == 0) first = first * 10 + 8;
                else if (flag == 1) second = second * 10 + 8;
                else { first = 0; second = 0; }
                break;
            case 0x0A:
                printf("9");
                if (flag == 0) first = first * 10 + 9;
                else if (flag == 1) second = second * 10 + 9;
                else { first = 0; second = 0; }
                break;
            case 0x0B:
                printf("0");
                if (flag == 0) first = first * 10;
                else if (flag == 1) second = second * 10;
                else { first = 0; second = 0; }
                break;
            case 0x13:
                clearScreen();
                printf("Please enter operand 1: ");
                flag = 0;
                break;
            case 0x0D:
                printf("+");
                op = 0;
                break;
            case 0x0C:
                printf("-");
                op = 1;
                break;
            case 0x34:
                printf("*");
                op = 2;
                break;
            case 0x35:
                printf("/");
                op = 3;
                break;
        
            case 0x1C:
                if (flag == 0) {
                    printf("\n");
                    printf("Please enter operand 2: ");
                    flag = 1;
                } else if (flag == 1) {
                    printf("\n");
                    printf("Please enter opertator(+, -, ., /): ");
                    flag = 2;
                } else {
                    int64_t result;
                    if (op == 0) result = first + second;
                    else if (op == 1) result = first - second;
                    else if (op == 2) result = first * second;
                    else if (second != 0) result = divide(first, second);

                    char buffer[20]; uint16_t index = 0;
                    if (result == 0) buffer[index++] = '0';
                    else while (result > 0) {
                            buffer[index++] = '0' + mod(result, 10);
                            result = divide(result, 10);
                        }
                    buffer[index] = '\0';

                    for (uint16_t i = 0; i < index / 2; i++) {
                        uint8_t temp = buffer[i];
                        buffer[i] = buffer[index - 1 - i];
                        buffer[index - 1 - i] = temp;
                    }

                    printf("\nRESULT: ");
                    printf(buffer);
                    flag = first = second = op = 0;
                }
                break;
        }
    }
    return esp;
}
