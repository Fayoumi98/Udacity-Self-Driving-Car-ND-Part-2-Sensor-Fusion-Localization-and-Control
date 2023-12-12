#include <iostream>

int factorial(int num)
{
    if(num<0)
    {
        return 0 ;
    }
    else if(num == 0 || num == 1)
    {
        return 1;
    }
    else
    {   
        int fac = 1;

        for (int i = num; i > 1; i--)
        {
            fac = i*fac ;
            //std::cout << fac << " i = " << i << std::endl;
        }

        return fac;
        
    }
    
}