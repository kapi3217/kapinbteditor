#include <vector>
#include <fstream>
#include <string>
#include <cstdint>

#include "fileio.h"
#include "zlib.h"

using namespace std;

void decompressGzip(const vector<uint8_t>& input, vector<uint8_t>& output) {
    z_stream strm = {};  // Initialize the zlib stream structure
    if (inflateInit2(&strm, 16 + MAX_WBITS) != Z_OK)  // Initialize zlib with raw inflation
        throw runtime_error("Error during initialization.");

    strm.avail_in = input.size();  // Set input size
    strm.next_in = const_cast<uint8_t*>(input.data());  // Set input data pointer

    vector<uint8_t> temp(4096);  // Temporary buffer for decompressed data

    // Decompress the data
    do {
        strm.avail_out = temp.size();  // Set output buffer size
        strm.next_out = temp.data();  // Set output data pointer
        
        // Inflate the data, and check for memory errors or buffer overrun
        if (inflate(&strm, Z_NO_FLUSH) == Z_MEM_ERROR || strm.avail_out == 0) {
            inflateEnd(&strm);  // End inflation if error occurs
            throw runtime_error("Decompression error.");
        }

        // Append the decompressed data to the output vector
        output.insert(output.end(), temp.begin(), temp.begin() + (temp.size() - strm.avail_out));
    } while (strm.avail_in > 0);  // Continue until all input data is processed

    inflateEnd(&strm);  // Clean up and release resources
}