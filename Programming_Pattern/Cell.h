#ifndef __CELL_H__
#define __CELL_H__

#include <algorithm>
#include <array>
#include <cmath>
#include <cstdio>
#include <filesystem>
#include <fstream>
#include <functional>
#include <iostream>
#include <map>
#include <memory>
#include <mutex>
#include <random>
#include <regex>
#include <sstream>
#include <stdexcept>
#include <string>
#include <thread>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "ICell.h"

class Tissue;

class Cell : public ICell
{
    unsigned int id;
    std::vector<Cell *> in, out;

public:
    Cell()
    {
        static int n = 1;
        id = n++;
    }

    void connect_to(ICell &other);
};

#endif // __CELL_H__