#pragma once

#include <vector>
#include <string>
#include "structures.h"

using namespace std;

// Used to parse tags from data
string ReadString(vector<uint8_t> data, int &i);
void GetInt(const vector<uint8_t> &data, int &i, vector<uint8_t> &rawData, string &value);
void GetLong64(const vector<uint8_t> &data, int &i, vector<uint8_t> &rawData, string &value);
void GetFloat(const vector<uint8_t> &data, int &i, vector<uint8_t> &rawData, string &value);
void GetDouble(const vector<uint8_t> &data, int &i, vector<uint8_t> &rawData, string &value);

// Inline functions
inline int16_t GetShortOnly(const vector<uint8_t> &data, int &i) {
    int16_t tempShort = (data.at(i) << 8) | (data.at(i + 1));
    i += 2;
    return tempShort;
}
inline int32_t GetIntOnly(const vector<uint8_t> &data, int &i) {
    int32_t tempInt = 0;
    for (int j = 0; j < 4; j++) {
        tempInt |= (data.at(i) << (24 - j * 8));
        i++;
    }
    return tempInt;
}
inline int64_t GetLong64Only(const vector<uint8_t> &data, int &i) {
    int64_t tempLong = 0;
    for (int j = 0; j < 8; j++) {
        tempLong |= (int64_t(data.at(i)) << (56 - j * 8));
        i++;
    }
    return tempLong;
}
inline void GetShort(const vector<uint8_t> &data, int &i, vector<uint8_t> &rawData, string &value) {
    rawData.insert(rawData.end(), data.begin() + i, data.begin() + i + 2);
    short tempShort = GetShortOnly(data, i);
    value = to_string(tempShort);
}
inline void GetByte (const vector<uint8_t> &data, int &i, vector<uint8_t> &rawData, string &value) {
    rawData.push_back(data.at(i));
    value = to_string(static_cast<signed char>(data.at(i)));
    i++;
}

// Used to convert tags to data
void PushString(vector<uint8_t> &data, const string &str);
void PushTagToArray(vector<uint8_t> &data, const nbt::Tag &currentTag);

// Used to print nbt::Tag arrat 
string TagTypeToString(uint8_t ch);
