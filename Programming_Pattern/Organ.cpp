#include "Organ.h"
#include "Cell.h"
#include "Tissue.h"

Organ::Organ(const std::vector<Tissue> &tissues)
{
    for (const auto &tissue : tissues)
        push_back(tissue);
}

void Organ::connect_to(ICell &other)
{
    Organ *organ = dynamic_cast<Organ *>(&other);
    if (organ)
    {
        out.push_back(organ);
        organ->in.push_back(this);
        return;
    }

    Tissue *tissue = dynamic_cast<Tissue *>(&other);
    if (tissue)
    {
        for (Tissue &in : *this)
            in.connect_to(*tissue);
        push_back(*tissue);
    }

    Cell *cell = dynamic_cast<Cell *>(&other);
}