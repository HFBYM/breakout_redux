#include<iostream>
void echo();
int main()
{
    std::cout << "Hello World" << std::endl;
#ifdef PROJECT_DIR
    std::cout << "project" << PROJECT_DIR << std::endl;
#endif
    echo();
    return 0;
}