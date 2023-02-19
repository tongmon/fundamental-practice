#include "Heart.h"
#include "Tissue.h"

#include <iostream>

Heart::Heart(const std::vector<Tissue> &tissues)
{
    pump_count = 0;
    this->assign(tissues.begin(), tissues.end());
}

void Heart::pump()
{
    std::cout << "Current Pump Count: " << ++pump_count << std::endl;
}