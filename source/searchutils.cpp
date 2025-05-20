#include <vector>
#include <functional>
#include <string>
#include <cstdint>
#include <stdexcept>

#include "searchutils.h"
#include "structures.h"
#include "tagfunctions.h"

using namespace std;

template<typename T> size_t FindFirstMatching(const vector<T>& items, const vector<function<bool(const T&) >> & conditions, size_t itr) {
    for (size_t i = itr; i < items.size(); i++) {
        bool allMatch = true;
        for (size_t j = 0; j < conditions.size(); j++) {
            if (!conditions[j](items[i])) {
                allMatch = false;
                break;
            }
        }
        if (allMatch) {
            return i;
        }
    }
    return items.size();
}

size_t FindTagByLvlAndDescription(const vector<nbt::Tag>& tags, uint16_t lvl, string description, size_t itr) {
    vector<function<bool(const nbt::Tag&)>> conditions = {
        [lvl](const nbt::Tag& p) { return p.lvl == lvl; },
        [description](const nbt::Tag& p) { return p.description == description; }
    };
    return FindFirstMatching(tags, conditions, itr);
}
size_t FindNullTag(const vector<nbt::Tag>& tags, uint16_t lvl, size_t itr) {
    vector<function<bool(const nbt::Tag&)>> conditions = {
        [lvl](const nbt::Tag& p) { return p.lvl == lvl; },
        [](const nbt::Tag& p) { return p.tagType == 0x00; }
    };
    return FindFirstMatching(tags, conditions, itr);
}
void FindXYZ(vector<nbt::Tag>& tags, int& x, int& y, int& z, size_t itr) {
    itr = FindTagByLvlAndDescription(tags, 3, "Size", itr);
    x = GetIntOnly(tags.at(itr + 1).rawData, 0);
    y = GetIntOnly(tags.at(itr + 2).rawData, 0);
    z = GetIntOnly(tags.at(itr + 3).rawData, 0);
}