#pragma once

#include <string>
#include <cstdint>

using namespace std;

namespace nbt {
    struct Tag {
        uint8_t tagType; // Type of the tag
        uint8_t tagTypeInList = 0xFF; // Represents type of the tag array, equal to 0xFF if tagType != 0x09
        uint16_t lvl; // Level of матрёшка
        uint32_t numOfElements = 1; // 0 for empty tag, variable for arrays, 1 for other types
        string description = ""; // Tag description
        string value = ""; // Value that will be printed through streams
        vector<uint8_t> rawData; // Sequence of bytes
    };
    struct Image {
        string name;
        vector<uint8_t>data;
        uint8_t numCh;
        uint16_t width;
        uint16_t height;
    };
    struct BlockInfo {
        string name;
        vector<nbt::Tag> properties;
        uint16_t blockID;
        uint32_t numberOfBlocks;
    };
}