#include <iostream>
#include <vector>
#include <string> // Přidáno pro použití std::string

std::string hello_world()
{
    return "Hello world!";
}

#ifndef __TEST__ // Add this preprocessor guard
int main()
{
    std::cout << hello_world() << std::endl;
    return 0;
}
#endif // __TEST__

