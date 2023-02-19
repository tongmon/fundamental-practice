#ifndef HEADER__FILE__LUNG
#define HEADER__FILE__LUNG

#include <vector>

#include "Interactor.h"

class Tissue;

class Lung : public Interactor<Lung>, public std::vector<Tissue>
{
    float oxygen_content;

public:
    Lung(const std::vector<Tissue> &tissues = {});
    void Inhale(float);
    void Exhale(float);
};

#endif /* HEADER__FILE__LUNG */
