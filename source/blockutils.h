#pragma once

#include <vector>
#include <cstdint>
#include <cstddef>

#include "structures.h"

using namespace std;

namespace nbt {
    bool ConvertArrayToBlockIDs(vector<uint16_t> &arr, const vector <uint8_t> &data, int num, int x, int y, int z, uint8_t &errorCode);
    void ParseBlocks(vector<nbt::Tag> &tags, vector<nbt::BlockInfo> &blocks);
}