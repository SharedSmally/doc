#include <iostream>
#include "Properties.h"

int main()
{
    String cfg("config.cfg");
    PropertiesGroup group;
    group.load(cfg);
    group.output();

    std::cout << " remove APP"<< std::endl;
    group.removeGroup("App");
    group.output();
}
