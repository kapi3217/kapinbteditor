#include <vector>
#include <cstdint>
#include <cstring>
#include <string>
#include <iostream>
#include <iomanip>
#include <stdexcept>

#include "lib/kapilib.h"
#include "tagfunctions.h"
#include "structures.h"
#include "tagprocessing.h"
#include "consoleio.h"

using namespace std;
using namespace kapi;

void DataToTags(const vector<uint8_t> &data, vector<nbt::Tag> &tags) {
    string tempRaw, tempValue;
    int i = 0, len = data.size();
    uint16_t lvl = 0;
    nbt::Tag emptyTag;
    while (i < len) {
        ParseTag(data, i, tags, false, 0x00, lvl);
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
void ParseTag(const vector<uint8_t> &data, int &i, vector<nbt::Tag> &tags, bool isInList, uint8_t listType, uint16_t &lvl) {
    nbt::Tag tempTag;
    if (isInList) {
        tempTag.tagType = listType;
    }
    else {
        tempTag.tagType = data.at(i);
        i++;
        if (tempTag.tagType != 0x00) {
            tempTag.description = ReadString(data, i);
        }
    }
    tempTag.lvl = lvl;
    switch (tempTag.tagType) {
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
            i += 4;
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
            tempTag.rawData.insert(tempTag.rawData.end(), tempTag.value.begin(), tempTag.value.end());
            break;
        }
        case 0x09: { // Tag array
            uint8_t tempChar = data.at(i);
            i++;
            int tempInt = GetIntOnly(data, i);
            i += 4;
            tempTag.tagTypeInList = tempChar;
            tempTag.numOfElements = tempInt;
            tags.push_back(tempTag);
            lvl++;
            if (tempInt != 0) {
                if (tempChar != 0x00) {
                    for (int j = 0; j < tempInt; j++) {
                        ParseTag(data, i, tags, true, tempChar, lvl);
                    }
                }
                else cerr << "\nwtf\n";
            }
            lvl--;
            break;
        }
        case 0x0a: { // Compound tag
            tempTag.lvl = lvl;
            tags.push_back(tempTag);
            lvl++;
            while (data.at(i) != 0x00) {
                ParseTag(data, i, tags, false, 0, lvl);
            }
            nbt::Tag newTag;
            lvl--;
            i++;
            newTag.lvl = lvl;
            newTag.numOfElements = 0;
            newTag.tagType = 0x00;
            tags.push_back(newTag);
            break;
        }
        case 0x0b: { // Int array
            int tempInt = GetIntOnly(data, i);
            i += 4;
            tempTag.numOfElements = tempInt;
            tempTag.rawData.insert(tempTag.rawData.end(), data.begin() + i, data.begin() + i + tempInt * 4);
            for (int j = 0; j < tempInt; j++) {
                tempTag.value += to_string(GetIntOnly(data, i));
                i += 4;
                if (j != (tempInt - 1)) tempTag.value += " ";
            }
            break;
        }
        case 0x0c: { // Long64 array
            int tempInt = GetIntOnly(data, i);
            i += 4;
            tempTag.numOfElements = tempInt;
            tempTag.rawData.insert(tempTag.rawData.end(), data.begin() + i, data.begin() + i + tempInt * 8);
            for (int j = 0; j < tempInt; j++) {
                tempTag.value += to_string(GetLong64Only(data, i));
                i += 8;
                if (j != (tempInt - 1)) tempTag.value += " ";
            }
            break;
        }
        default: {
            cerr << "Incorrect tag type! " << hex << uppercase << tempTag.tagType;
            cerr << " in position" << hex << uppercase << i << endl;
            throw runtime_error("Incorrect tag type");
        }
    }
    if (tempTag.tagType != 0x09 && tempTag.tagType != 0x0A) {
        tempTag.lvl = lvl;
        tags.push_back(tempTag);
    }
}