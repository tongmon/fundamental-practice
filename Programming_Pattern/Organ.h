#ifndef __ORGAN_H__
#define __ORGAN_H__

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

class Organ : public ICell, public std::vector<Tissue>
{
    std::vector<Organ *> in, out;

public:
    Organ(const std::vector<Tissue> &tissues = {});

    void connect_to(ICell &other);
};

#endif // __ORGAN_H__