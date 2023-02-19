#include "Lung.h"
#include "Heart.h"
#include "Tissue.h"

#include <iostream>

Lung::Lung(const std::vector<Tissue> &tissues)
{
    oxygen_content = 0.f;
    this->assign(tissues.begin(), tissues.end());
}

void Lung::Inhale(float oxygen_from_outside)
{
    oxygen_content += oxygen_from_outside;
    std::cout
        << "Inhale... " << oxygen_from_outside
        << "amount of oxygen from outside.\nTotal Oxygen in body: "
        << oxygen_content << std::endl;
}

void Lung::Exhale(float amount_of_oxygen_for_exhale)
{
    oxygen_content = std::max(oxygen_content - amount_of_oxygen_for_exhale, 0.f);
    std::cout << "Exhale... Total Oxygen in body: " << oxygen_content << std::endl;
}