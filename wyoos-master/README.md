# Final Project - Simple Operating System with Arithmetic Operations  

## Overview  
This is my final project. The instructor's requirement is to code a simple operating system that performs basic arithmetic operations (addition, subtraction, multiplication, and division) on two numbers.  

### Functionality  
1. The screen displays: `"Please enter the first operand"`.  
2. After the user inputs the first operand and presses Enter, the screen displays: `"Please enter the second operand"`.  
3. After the user inputs the second operand and presses Enter, the screen displays: `"Please enter an operator (+, -, *, /)"`.  
4. After the user selects an operator and presses Enter, the system displays the result.  

## Description  
Developing an operating system is a challenging task for me, so I built this project based on the provided source code (linked below). I made the following modifications:  

### Modifications  
1. **Added a `clearScreen()` function** in `kernel.cpp`.  
2. **Modified `keyboard.cpp`** to handle input processing according to the required functionality.  

### Input Handling  
- **Disabled unnecessary keys** to minimize error handling. Only the following keys are allowed:  
  `0, 1, 2, 3, 4, 5, 6, 7, 8, 9, r, +, -, *, /, Enter`.  
- **Declared four variables and initialized them to 0:**  
  - `flag`: Tracks the current input stage.  
    - `0`: User is entering the first operand.  
    - `1`: User is entering the second operand.  
    - `2`: User is selecting an operator.  
  - `op`: Stores the selected operator.  
    - `0`: Addition  
    - `1`: Subtraction  
    - `2`: Multiplication  
    - `3`: Division  
  - `first`, `second`: Store the first and second operand values.  
- **Implemented `divide()` and `mod()` functions** because standard libraries are unavailable, and integer division/modulus operations are needed.  

### Keyboard Input Handling  
- **When the user presses `"r"`**:  
  - Clear the screen using `clearScreen()`.  
  - Display `"Please enter the first operand: "`.  
  - Set `flag = 0` to indicate that the user is entering the first operand.  

- **When the user presses a number key (`0-9`)**:  
  - Display the entered number on the screen.  
  - Check `flag`:  
    - If `flag == 0`: Store the number in `first`.  
    - If `flag == 1`: Store the number in `second`.  

- **When the user presses Enter**:  
  - Print `"\n"` to move to a new line.  
  - Check `flag`:  
    - If `flag == 0`: Display `"Please enter the second operand: "`, then set `flag = 1`.  
    - If `flag == 1`: Display `"Please select an operator: "`, then set `flag = 2`.  
    - If `flag == 2`:  
      - Declare `result` to store the computed value.  
      - Perform the arithmetic operation based on `op`, using `first` and `second`, and store the result in `result`.  
      - Since `printf()` only accepts character arrays, convert `result` into a character array:  
        - Declare `buffer[]` and `index` to store the number of digits.  
        - Use a `while` loop to extract digits using the modulus operation and store them in `buffer`.  
        - Reverse the `buffer` array to correct the order.  
      - Print the result to the screen.  
      - Reset all variables to `0`.  

## Source Code  
- **Original source code:** [GitHub Repository](https://github.com/AlgorithMan-de/wyoos.git)  
- **My modified version:** [GitHub Repository](https://github.com/Catherine1401/wyoos.git)  
