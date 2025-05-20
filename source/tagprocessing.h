#pragma once

#include <vector>
#include "structures.h"

void DataToTags(const vector<uint8_t> &data, vector<nbt::Tag> &tags);
void TagsToData(vector<uint8_t> &data, const vector<nbt::Tag> &tags);
void ParseTag(const vector<uint8_t> &data, int &i, vector<nbt::Tag> &tags, bool isInList, uint8_t listType, uint16_t &lvl);

/*
считывать теги, пока можно
если тег обычный - считать
если 
*/