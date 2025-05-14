#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstdint>
#include <cstdlib>

#include "tag_processing.h"
#include "functions.h"
#include "structures.h"
#include "consoleio.h"
#include "fileio.h"

#include "lib/kapilib.h"
// #include "zlib.h"

// // Image load/store
// #define STB_IMAGE_IMPLEMENTATION
// #include "stb_image.h"

// #define STB_IMAGE_WRITE_IMPLEMENTATION
// #include "stb_image_write.h"

using namespace std;
using namespace kapi;

int main() {
    string lng = "ru";
    вперёд_славяне
    // Input
    string filenameIn = "input/test.litematic";
    vector<uint8_t> data;
    if (!FileToVector(filenameIn, data)) {
        cerr << "File wasn't found\n";
    }
    //Check if it is an archive or not
    if (!(data.size() < 4 || (data.at(0) == 0x0A && data.at(1) == 0x00 && data.at(2) == 0x00 && data.at(data.size() - 1) == 0x00))) {
        vector<uint8_t> data1;
        decompressGzip(data, data1);
        data = data1;
    }
    // Processing
    vector<nbt::Tag> tags;
    DataToTags(data, tags);
    vector<uint8_t> data2;
    TagsToData(data2, tags);

    PrintArray(tags);
    // Output
    string filenameOut = "output/test";
    VectorToFile(filenameOut, data2);
    // Check
    cout << AreFilesDifferent(filenameIn, filenameOut) << endl;
    // End
    Pause();
    return 0;
}