#pragma once

#include <string>
#include <cstdint>

using namespace std;

namespace nbt {
    struct Tag {
        uint8_t tagType; // Type of the tag
        uint8_t tagTypeInList = 0xFF; // Represents type of the tag array, equal to 0xFF if tagType != 0x09
        uint16_t lvl; // Level of matryoshka
        uint32_t numOfElements = 1; // 0 for empty tag, variable for arrays, 1 for other types
        string description = ""; // Tag description
        vector<uint8_t> rawData; // Sequence of bytes
        string value = ""; // Value that will be printed through streams
    };
    struct BlockInfo {
        string fileName;
        bool isFull;
        bool isTransparent;
    };
    struct Image {
        string name;
        vector<uint8_t>data;
        uint8_t numCh;
        uint16_t width;
        uint16_t height;
    };
    struct Block {
        string mod = "minecraft";
        string name;
        string metadata;
        vector<nbt::Image> images;
        nbt::BlockInfo info;
    };
}

/*
Схема:
- загрузить в память файл с информацией о всех блоках
- разархивировать схематику (если ещё нет)
- распарсить схематику
- определить, какие блоки имеются в схематике
- создать 3D-структуру блоков
- определить размер спрайта
- загрузить спрайты нужного размера в память
- определить лучи
- для каждого луча определить ближайший непрозрачный блок и все прозрачные блоки перед ним (кроме воздуха)
- здесь убрать те блоки, которые не видно
- наложить эти блоки на изображение
- постепенно (для оптимизации) убирать те блоки которые больше не будут использоваться
- сохранить рендер в файл
- удалить массив с рендером и блоками
*/