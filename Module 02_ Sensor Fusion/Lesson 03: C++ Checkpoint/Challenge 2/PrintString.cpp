#include "PrintString.h"
#include <iostream>
#include <string>


void disp(std::string name , int rep)
{
    for (size_t i = 0; i < rep; i++)
    {
        std::cout << "my name is " << name << std::endl; 
    }
    
}