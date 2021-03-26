#include <random>
#include <iostream>
#include "Mylib.hpp"

int GetRandomNumber()
{
    std::random_device rd;
    std::mt19937 mersenne(static_cast<unsigned int>(time(0)));
 
    return mersenne() % 100; //Вихрь Мерсенна из С++ 11
}


