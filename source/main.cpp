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
    // Input
    string filenameIn = "input/test.dat";
    vector<uint8_t> data;
    if (!FileToVector(filenameIn, data)) {
        cerr << "File wasn't found\n";
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