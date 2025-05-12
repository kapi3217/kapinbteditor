#pragma once

#include <string>
#include <cstdint>

using namespace std;

namespace nbt {
    struct Tag {
        uint8_t tagType;
        uint16_t lvl;
        uint32_t numOfElements = 1;
        string description = "";
        vector<uint8_t> rawData;
        string value = "";
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
- разархивировать схематику
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

/*
adler32.c compress.c crc32.c deflate.c gzclose.c gzlib.c gzread.c gzwrite.c infback.c inffast.c inflate.c inftrees.c trees.c uncompr.c zutil.c
*/