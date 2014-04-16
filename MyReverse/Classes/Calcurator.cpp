
#include "Calcurator.h"

int Calcurator::getIntegerLength(int num)
{
    if(num == 0)
        return 1;
    return (int)log10(num) + 1;
}

int Calcurator::getIntegerDigit(int num, int digit)
{
    if(digit <= 0){
       
        return -1;
    }
    
    if(num == 1)
    {
        return num / 1 % 10;
    }else{
        int t = (int)pow(10,(digit-1));
        return num / t % 10;
    }

}