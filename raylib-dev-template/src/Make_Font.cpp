#include "raylib.h"
#include <iostream>


Font makefont(const char* filename, int fontsize){
    // Loading file to memory
    int fileSize = 0;
    unsigned char *fileData = LoadFileData(filename, &fileSize);
    // Default font generation from OTF(or TTF) font
    Font fontDefault = { 0 };
    fontDefault.baseSize = fontsize;
    fontDefault.glyphCount = 95; //這個字型檔總共載入了多少個字形（字元）。普通的英文字型通常會包含 95 個可見字元（ASCII 32 到 126）。
    // Loading font data from memory data
    // Parameters > font size: 16, no glyphs array provided (0), glyphs count: 95 (autogenerate chars array)
    fontDefault.glyphs = LoadFontData(fileData, fileSize, fontsize, 0, 95, FONT_SDF);
    // Parameters > glyphs count: 95, font size: 16, glyphs padding in image: 4 px, pack method: 0 (default)
    Image atlas = GenImageFontAtlas(fontDefault.glyphs, &fontDefault.recs, 95, fontsize, 0, 1);
    fontDefault.texture = LoadTextureFromImage(atlas);
    SetTextureFilter(fontDefault.texture, TEXTURE_FILTER_BILINEAR); // SDF 必須要有平滑的像素過渡，才能被正確解析。所以上傳到 GPU 變成 Texture 後，必須強制開啟平滑過濾
    UnloadImage(atlas);
    UnloadFileData(fileData);
    return fontDefault;
}