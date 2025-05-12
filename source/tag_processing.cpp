#include <vector>
#include <cstdint>
#include <cstring>
#include <string>

#include "kapilib.h"
#include "functions.h"
#include "structures.h"
#include "tag_processing.h"
#include "consoleio.h"

using namespace std;
using namespace kapi;

void DataToTags(const vector<uint8_t> &data, vector<nbt::Tag> &tags) {
    string tempRaw, tempValue;
    int i = 0, len = data.size();
    while (i < len) {
        ParseTag(data, i, tags);
    }
}
void TagsToData(vector<uint8_t> &data, const vector<nbt::Tag> &tags) {
    int length = tags.size();
    if (length != 0) {
        PushTagToArray(data, tags[0]);
        if (length != 1) for (int i = 1; i < length; i++) {
            PushTagToArray(data, tags[i]);
        }
    }
}
void ParseTag(const vector<uint8_t> &data, int &i, vector<nbt::Tag> &tags, bool isInList, uint8_t listType) {
    uint16_t lvl;
    if (tags.size() == 0) lvl = 0; else lvl = tags.back().lvl;
    uint8_t tempType;
    if (isInList) tempType = listType; else tempType = data.at(i);
    i++;
    nbt::Tag tempTag;
    tempTag.tagType = tempType;
    if (tempType != 0x00) {
        tempTag.description = ReadString(data, i);
    }
    switch (tempType) {
        case 0x00: { // Stack pop
            lvl--;
            tempTag.numOfElements = 0;
            break;
        }
        case 0x01: { // Byte
            GetByte(data, i, tempTag.rawData, tempTag.value);;
            break;
        }
        case 0x02: { // Short
            GetShort(data, i, tempTag.rawData, tempTag.value);
            break;
        }
        case 0x03: { // Int
            GetInt(data, i, tempTag.rawData, tempTag.value);
            break;
        }
        case 0x04: { // Long long
            GetLong64(data, i, tempTag.rawData, tempTag.value);
            break;
        }
        case 0x05: { // Float
            GetFloat(data, i, tempTag.rawData, tempTag.value);
            break;
        }
        case 0x06: { // Double
            GetDouble(data, i, tempTag.rawData, tempTag.value);
            break;
        }
        case 0x07: { // Byte array
            int tempInt = GetIntOnly(data, i);
            tempTag.numOfElements = tempInt;
            tempTag.rawData.insert(tempTag.rawData.end(), data.begin() + i, data.begin() + i + tempInt);
            for (int j = 0; j < tempInt; j++) {
                tempTag.value += to_string(static_cast<signed char>(data.at(i)));
                if (j != (tempInt - 1)) tempTag.value += " ";
                i++;
            }
            break;
        }
        case 0x08: { // String
            tempTag.value = ReadString(data, i);
            tempTag.rawData.insert(tempTag.rawData.end(), data.begin() + i, data.begin() + i + tempTag.value.length());
            break;
        }
        case 0x09: { // Tag array
            uint8_t tempChar = data.at(i);
            i++;
            lvl++;
            int tempInt = GetIntOnly(data, i);
            if (tempInt != 0) {
                if (tempChar != 0x00) {
                    for (int j = 0; j < tempInt; j++) {
                        nbt::Tag newTag;
                        newTag.lvl = lvl;
                        // Will be done later when I find a good example
                        ParseTag(data, i, tags, true, tempChar);
                    }
                }
            }
            lvl--;
            break;
        }
        case 0x0a: { // Compound tag
            lvl++;
            break;
        }
        case 0x0b: { // Int array
            int tempInt = GetIntOnly(data, i);
            tempTag.numOfElements = tempInt;
            tempTag.rawData.insert(tempTag.rawData.end(), data.begin() + i, data.begin() + i + tempInt * 4);
            for (int j = 0; j < tempInt; j++) {
                tempTag.value += to_string(GetIntOnly(data, i));
                if (j != (tempInt - 1)) tempTag.value += " ";
            }
            break;
        }
        case 0x0c: { // Long64 array
            int tempInt = GetIntOnly(data, i);
            tempTag.numOfElements = tempInt;
            tempTag.rawData.insert(tempTag.rawData.end(), data.begin() + i, data.begin() + i + tempInt * 8);
            for (int j = 0; j < tempInt; j++) {
                tempTag.value += to_string(GetLong64Only(data, i));
                if (j != (tempInt - 1)) tempTag.value += " ";
            }
            break;
        }
    }
    tempTag.lvl = lvl;
    tags.push_back(tempTag);
}