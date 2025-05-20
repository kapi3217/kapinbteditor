#pragma once

#include <string>
#include <vector>
#include <cstdint>

using namespace std;

void DecompressGzip(const vector<uint8_t>& input, vector<uint8_t>& output);
void OpenFile(string filename, vector<uint8_t>& data);