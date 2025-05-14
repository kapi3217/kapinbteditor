#pragma once

#include <string>
#include <vector>
#include <cstdint>

using namespace std;

void decompressGzip(const vector<uint8_t>& input, vector<uint8_t>& output);