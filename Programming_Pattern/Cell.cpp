#include "Cell.h"
#include "Tissue.h"

void Cell::connect_to(ICell &other)
{
    Cell *cell = dynamic_cast<Cell *>(&other);
    if (cell)
    {
        out.push_back(cell);
        cell->in.push_back(this);
        return;
    }

    Tissue *tissue = dynamic_cast<Tissue *>(&other);
    if (tissue)
        tissue->connect_to(*this);
}