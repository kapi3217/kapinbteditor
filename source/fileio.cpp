#include <vector>
#include <fstream>
#include <string>
#include <cstdint>
#include <stdexcept>

#include "fileio.h"
#include "zlib.h"
#include "lib/kapilib.h"

using namespace std;
using namespace kapi;

void DecompressGzip(const vector<uint8_t>& input, vector<uint8_t>& output) {
    z_stream strm = {};
    if (inflateInit2(&strm, 16 + MAX_WBITS) != Z_OK)
        throw runtime_error("Error during initialization.");

    strm.avail_in = input.size();
    strm.next_in = const_cast<Bytef*>(input.data());

    vector<uint8_t> temp(4096);

    int ret;
    do {
        strm.avail_out = temp.size();
        strm.next_out = temp.data();

        ret = inflate(&strm, Z_NO_FLUSH);
        if (ret != Z_OK && ret != Z_STREAM_END) {
            inflateEnd(&strm);
            throw runtime_error("Decompression error.");
        }

        size_t bytes_decompressed = temp.size() - strm.avail_out;
        output.insert(output.end(), temp.begin(), temp.begin() + bytes_decompressed);
    } while (ret != Z_STREAM_END);

    inflateEnd(&strm);
}
void OpenFile(string filename, vector<uint8_t>& data) {
    vector<uint8_t> data;
    if (!FileToVector(filename, data)) {
        cerr << "File wasn't found\n";
    }
    // Check if it is an archive or unzipped NBT (it always start with 0x0A 0x00 0x00 and end with 0x00)
    if (!(data.size() < 4
        || (data.at(0) == 0x0A
            && data.at(1) == 0x00
            && data.at(2) == 0x00
            && data.at(data.size() - 1) == 0x00))) {
        vector<uint8_t> data1;
        DecompressGzip(data, data1);
        data = data1;
        data1.clear();
        cout << "Reading archived file " << filename << endl;
    }
    else {
        cout << "Reading unzipped file " << filename << endl;
    }
}