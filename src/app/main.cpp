#include <iostream>
#include "../lib/MyClass.h"

#include <boost/lexical_cast.hpp>

int main()
{
    app::MyClass obj("Hello");
    std::cout << obj.appendIt("library world!!") << '\n';
    
    return 0;
}