#include <iostream>
#include <vector>
#include <cstdint>
#include <cmath>
#include <functional>
#include <stdexcept>

#include "structures.h"
#include "tagfunctions.h"
#include "searchutils.h"

using namespace std;

#define OK_DATA 0x00
#define NO_DATA 0x01
#define SMALL_DATA 0x02
#define BIG_DATA 0x03
#define TOO_MUCH_BLOCKS 0x10
#define ZERO_SIZE 0x11

namespace nbt {
    bool ConvertArrayToBlockIDs(vector<uint16_t> &arr, const vector <uint8_t> &data, int num, int x, int y, int z, uint8_t &errorCode) {
        uint16_t maskTable[16] = {
            0x0001, 0x0003, 0x0007, 0x000F,
            0x001F, 0x003F, 0x007F, 0x00FF,
            0x01FF, 0x03FF, 0x07FF, 0x0FFF,
            0x1FFF, 0x3FFF, 0x7FFF, 0xFFFF
        };
        // Checks if error
        int sz = static_cast<int>(ceil(log2(num)));
        if (sz < 1 || sz > 16) {
            errorCode = TOO_MUCH_BLOCKS;
            return 0;
        }
        uint16_t mask16 = maskTable[sz - 1];
        if (!(x > 0 && y > 0 && z > 0)) {
            errorCode = ZERO_SIZE;
            return 0;
        }
        size_t volume = x * y * z;
        size_t dataSize = volume * sz;
        size_t bitSize = data.size() * 8;
        if (bitSize == 0 || dataSize == 0) {
            errorCode = NO_DATA;
            return 0;
        }
        else if (bitSize < dataSize) {
            errorCode = BIG_DATA;
            return 0;
        }
        else if ((bitSize - 64) > dataSize) {
            errorCode = SMALL_DATA;
            return 0;
        }
        int blockSize = 8 * sz;
        int rest = data.size() % blockSize;
        int inWhile = (data.size() / 8) - blockSize;
        int64_t i = 0;
        while (i < inWhile) {
            vector<uint8_t> tempVector;
            tempVector.insert(tempVector.end(), data.begin() + i * 8, data.begin() + i * 8 + sz * 8);
            ConvertPartToLittleEndian(tempVector);
            tempVector.insert(tempVector.end(), 2, 0x00);
            uint32_t reg;
            int pos = 0;
            int index, offset;
            for (int j = 0; j < 64; j++) {
                reg = 0;
                offset = pos % 8;
                index = pos / 8;
                reg = (tempVector[index + 2] << 16) | (tempVector[index + 1] << 8) | tempVector[index];
                reg >>= offset;
                pos += sz;
                arr.push_back(mask16 & static_cast<uint16_t>(reg));
            }
            i += blockSize;
        }
        if (rest != 0) {
            int t = (dataSize - (i / blockSize) * 8) / sz;
            vector<uint8_t> tempVector;
            tempVector.insert(tempVector.end(), data.begin() + i * 8, data.begin() + i * 8 + rest);
            ConvertPartToLittleEndian(tempVector);
            tempVector.insert(tempVector.end(), blockSize - rest + 2, 0x00);
            uint32_t reg;
            int pos = 0;
            int index, offset;
            for (int j = 0; j < t; j++) {
                reg = 0;
                offset = pos % 8;
                index = pos / 8;
                reg = (tempVector[index + 2] << 16) | (tempVector[index + 1] << 8) | tempVector[index];
                reg >>= offset;
                pos += sz;
                arr.push_back(mask16 & static_cast<uint16_t>(reg));
            }
        }
        return 1;
    }
    void ParseBlocks(vector<nbt::Tag> &tags, vector<nbt::BlockInfo> &blocks) {
        size_t pos = FindTagByLvlAndDescription(tags, 2, "RegionCount");
        if (tags[pos].value != "1") {
            cerr << "wtf more than 1 region";
            throw runtime_error("The structure is so big, the program doesn't support it!");
        }
        pos = FindTagByLvlAndDescription(tags, 3, "BlockStatePalette");
        int num = GetIntOnly(tags.at(pos).rawData, 0);
        for (int i = 0; i < num; i++) {
            
        }

    }
}