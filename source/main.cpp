#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstdint>
#include <cstdlib>

#include "tagprocessing.h"
#include "tagfunctions.h"
#include "imageprocessing.h"
#include "structures.h"
#include "consoleio.h"
#include "fileio.h"
#include "blockutils.h"
#include "searchutils.h"

#include "lib/kapilib.h"


// // Image load/store
// #define STB_IMAGE_IMPLEMENTATION
// #include "stb_image.h"

// #define STB_IMAGE_WRITE_IMPLEMENTATION
// #include "stb_image_write.h"

using namespace std;
using namespace kapi;

int main() {
    alga;
    // Input
    string filenameIn;
    cout << "Enter filename: ";
    getline(cin, filenameIn);
    filenameIn = "input/" + filenameIn;
    vector<uint8_t> data;
    OpenFile(filenameIn, data);
    // Processing
    vector<nbt::Tag> tags;
    DataToTags(data, tags);
    vector<uint16_t> blocks;
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