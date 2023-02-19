#ifndef HEADER__FILE__TISSUE
#define HEADER__FILE__TISSUE

#include <vector>

#include "Interactor.h"

class Tissue : public Interactor<Tissue>
{
    int id;

public:
    std::vector<Tissue *> in, out;

    Tissue();
    Tissue *begin() { return this; }
    Tissue *end() { return this + 1; }
};

#endif /* HEADER__FILE__TISSUE */
