#ifndef HEADER__FILE__HEART
#define HEADER__FILE__HEART

#include <vector>

#include "Interactor.h"

class Tissue;

class Heart : public Interactor<Heart>, public std::vector<Tissue>
{
    int pump_count;

public:
    Heart(const std::vector<Tissue> &tissues = {});
    void pump();
};

#endif /* HEADER__FILE__HEART */
