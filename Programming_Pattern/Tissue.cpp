#include "Tissue.h"
#include "Cell.h"

Tissue::Tissue(const std::vector<Cell> &cells)
{
    for (const auto &cell : cells)
        push_back(cell);

    for (int i = 0; i < size(); i++)
        for (int j = i + 1; j < size(); j++)
            this[i].connect_to(this[j]);
}

void Tissue::connect_to(ICell &other)
{
    Tissue *tissue = dynamic_cast<Tissue *>(&other);
    if (tissue)
    {
        out.push_back(tissue);
        tissue->in.push_back(this);
        return;
    }

    Cell *cell = dynamic_cast<Cell *>(&other);
    if (cell)
    {
        for (Cell &in : *this)
            in.connect_to(*cell);
        push_back(*cell);
    }
}