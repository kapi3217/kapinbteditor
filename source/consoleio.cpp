#include <iostream>
#include <cstdint>
#include <string>
#include <vector>

#include "structures.h"
#include "consoleio.h"
#include "functions.h"

#include "lib/kapilib.h"

using namespace std;
using namespace kapi;

void PrintArray(const vector<nbt::Tag> &tags) {
    int len = tags.size();
    for (int i = 0; i < len; i++) {
        PrintTag(tags[i]);
    }
}
void PrintTag(const nbt::Tag &tag) {
    if (tag.lvl > 512) cerr << "ERROR ";
    cout << tag.lvl << " " <<
        TagTypeToString(tag.tagType) << " " <<
        tag.description << " " <<
        tag.numOfElements << " " <<
        tag.value << " " <<
        ToHex(tag.rawData) << endl;
}