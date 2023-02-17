#ifndef __TISSUE_H__
#define __TISSUE_H__

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

class Cell;

class Tissue : public ICell, public std::vector<Cell>
{
    std::vector<Tissue *> in, out;

public:
    Tissue(const std::vector<Cell> &cells = {});

    void connect_to(ICell &other);
};

#endif // __TISSUE_H__