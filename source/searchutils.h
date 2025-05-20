#pragma once

#include <vector>
#include <functional>
#include <cstddef>
#include <cstdint>
#include "structures.h"

using namespace std;

template<typename T> size_t FindFirstMatching(const vector<T>& items, const vector<function<bool(const T&) >> & conditions, size_t itr = 0);

size_t FindTagByLvlAndDescription(const vector<nbt::Tag>& tags, uint16_t lvl, string description, size_t itr = 0);
size_t FindNullTag(const vector<nbt::Tag>& tags, uint16_t lvl, size_t itr = 0);
void FindXYZ(vector<nbt::Tag>& tags, int& x, int& y, int& z, size_t itr = 0);