#include "Tissue.h"
#include "Heart.h"

Tissue::Tissue()
{
    static int id = 1;
    this->id = id++;
}