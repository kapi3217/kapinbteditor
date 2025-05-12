#include <iostream>
#include <vector>
#include <cstring>
#include <string>
#include <cstdint>

#include "functions.h"
#include "structures.h"
#include "lib/kapilib.h"

using namespace std;
using namespace kapi;

string ReadString(vector<uint8_t> data, int &i) {
    uint16_t len = GetShortOnly(data, i);
    string str = "";
    if (len != 0) {
        str = string(data.begin() + i, data.begin() + i + len);
        i += len;
    }
    return str;
}
void GetInt(const vector<uint8_t> &data, int &i, vector<uint8_t> &rawData, string &value) {
    rawData.insert(rawData.end(), data.begin() + i, data.begin() + i + 4);
    int32_t tempInt = GetIntOnly(data, i);
    value = to_string(tempInt);
}
void GetLong64(const vector<uint8_t> &data, int &i, vector<uint8_t> &rawData, string &value) {
    rawData.insert(rawData.end(), data.begin() + i, data.begin() + i + 8);
    int64_t tempLong = GetLong64Only(data, i);
    value = to_string(tempLong);
}
void GetFloat(const vector<uint8_t> &data, int &i, vector<uint8_t> &rawData, string &value) {
    rawData.insert(rawData.end(), data.begin() + i, data.begin() + i + 4);
    uint32_t tempInt = GetIntOnly(data, i);
    float tempFloat;
    memcpy(&tempFloat, &tempInt, 4);
    value = to_string(tempFloat);
}
void GetDouble(const vector<uint8_t> &data, int &i, vector<uint8_t> &rawData, string &value) {
    rawData.insert(rawData.end(), data.begin() + i, data.begin() + i + 8);
    uint64_t tempLong = GetLong64Only(data, i);
    double tempDouble;
    memcpy(&tempDouble, &tempLong, 8);
    value = to_string(tempDouble);
}

void PushString(vector<uint8_t> &data, const string &str) {
    uint16_t len = str.size();
    data.push_back(static_cast<uint8_t>(len >> 8));
    data.push_back(static_cast<uint8_t>(len));
    if (len != 0) {
        data.insert(data.end(), str.begin(), str.end());
    }
}
void PushTagToArray(vector<uint8_t> &data, const nbt::Tag &currentTag) {
    data.push_back(currentTag.tagType);
    if (currentTag.tagType != 0x00) {
        PushString(data, currentTag.description);
        uint8_t tagType = currentTag.tagType;
        if (tagType == 0x08) {
            PushString(data, currentTag.value);
        }
        else if (tagType == 0x09 || tagType == 0x0B || tagType == 0x0C) {
            uint32_t sz = currentTag.numOfElements;
            for (int i = 0; i < 4; i++) {
                data.push_back(static_cast<uint8_t>(sz >> (24 - 8 * i)));
            }
            data.insert(data.end(), currentTag.rawData.begin(), currentTag.rawData.end());
        }
        else {
            data.insert(data.end(), currentTag.rawData.begin(), currentTag.rawData.end());
        }
    }
}

string TagTypeToString(uint8_t ch) {
    string s;
    string sl[] = {"","byte","short","int","long","float","double","byteArray","string","list","compound","intArray","longArray"};
    if (ch <= 0x0c) s = sl[ch]; else s = "INVALID";
    return s;
}

/*
Схема:
- загрузить в память файл с информацией о всех блоках
- разархивировать схематику
- распарсить схематику
- определить, какие блоки имеются в схематике
-
*/