#include "add_class.h"
#include <iostream>

int main() {
    // Create an instance of the Adder class
    Adder myAdder;

    // Add two numbers
    int result = myAdder.add(5, 7);

    // Display the result
    std::cout << "Sum: " << result << std::endl;

    return 0;
}
