
#pragma once
#include "stdafx.h" 
#define STB_TRUETYPE_IMPLEMENTATION
#include"stb/stb_truetype.h"
#include "ButiFont.h"
#include"../ButiMath/ButiMath.h"

const std::int32_t FONT_ATLAS_DEFAULT_TEX_DATA_W = 108;
const std::int32_t FONT_ATLAS_DEFAULT_TEX_DATA_H = 27;
#define DRAWLIST_TEX_LINES_WIDTH_MAX (63)
#define TABSIZE                      (4)
#define UNICODE_CODEPOINT_MAX     0xFFFF     
#define UNICODE_CODEPOINT_INVALID 0xFFFD     

static void UnpackAccumulativeOffsetsIntoRanges(std::int32_t base_codepoint, const std::uint16_t* accumulative_offsets, std::int32_t accumulative_offsets_count, std::uint16_t* out_ranges)
{
    for (std::int32_t n = 0; n < accumulative_offsets_count; n++, out_ranges += 2)
    {
        out_ranges[0] = out_ranges[1] = (std::uint16_t)(base_codepoint + accumulative_offsets[n]);
        base_codepoint += accumulative_offsets[n];
    }
    out_ranges[0] = 0;
}

static inline bool      CharIsBlankA(char c) { return c == ' ' || c == '\t'; }
static inline bool      CharIsBlankW(std::uint32_t c) { return c == ' ' || c == '\t' || c == 0x3000; }
const std::uint16_t* GetGlyphRangesJapanese()
{
    // 1946 common ideograms code points for Japanese
    // Sourced from http://theinstructionlimit.com/common-kanji-character-ranges-for-xna-spritefont-rendering
    // FIXME: Source a list of the revised 2136 Joyo Kanji list from 2010 and rebuild this.
    // You can use ImFontGlyphRangesBuilder to create your own ranges derived from this, by merging existing ranges or adding new characters.
    // (Stored as accumulative offsets from the initial unicode codepoint 0x4E00. This encoding is designed to helps us compact the source code size.)
    static const std::uint16_t accumulative_offsets_from_0x4E00[] =
    {
        0,1,2,4,1,1,1,1,2,1,6,2,2,1,8,5,7,11,1,2,10,10,8,2,4,20,2,11,8,2,1,2,1,6,2,1,7,5,3,7,1,1,13,7,9,1,4,6,1,2,1,10,1,1,9,2,2,4,5,6,14,1,1,9,3,18,
        5,4,2,2,10,7,1,1,1,3,2,4,3,23,2,10,12,2,14,2,4,13,1,6,10,3,1,7,13,6,4,13,5,2,3,17,2,2,5,7,6,4,1,7,14,16,6,13,9,15,1,1,7,16,4,7,1,19,9,2,7,15,
        2,6,5,13,25,4,14,13,11,25,1,1,1,2,1,2,2,3,10,11,3,3,1,1,4,4,2,1,4,9,1,4,3,5,5,2,7,12,11,15,7,16,4,5,16,2,1,1,6,3,3,1,1,2,7,6,6,7,1,4,7,6,1,1,
        2,1,12,3,3,9,5,8,1,11,1,2,3,18,20,4,1,3,6,1,7,3,5,5,7,2,2,12,3,1,4,2,3,2,3,11,8,7,4,17,1,9,25,1,1,4,2,2,4,1,2,7,1,1,1,3,1,2,6,16,1,2,1,1,3,12,
        20,2,5,20,8,7,6,2,1,1,1,1,6,2,1,2,10,1,1,6,1,3,1,2,1,4,1,12,4,1,3,1,1,1,1,1,10,4,7,5,13,1,15,1,1,30,11,9,1,15,38,14,1,32,17,20,1,9,31,2,21,9,
        4,49,22,2,1,13,1,11,45,35,43,55,12,19,83,1,3,2,3,13,2,1,7,3,18,3,13,8,1,8,18,5,3,7,25,24,9,24,40,3,17,24,2,1,6,2,3,16,15,6,7,3,12,1,9,7,3,3,
        3,15,21,5,16,4,5,12,11,11,3,6,3,2,31,3,2,1,1,23,6,6,1,4,2,6,5,2,1,1,3,3,22,2,6,2,3,17,3,2,4,5,1,9,5,1,1,6,15,12,3,17,2,14,2,8,1,23,16,4,2,23,
        8,15,23,20,12,25,19,47,11,21,65,46,4,3,1,5,6,1,2,5,26,2,1,1,3,11,1,1,1,2,1,2,3,1,1,10,2,3,1,1,1,3,6,3,2,2,6,6,9,2,2,2,6,2,5,10,2,4,1,2,1,2,2,
        3,1,1,3,1,2,9,23,9,2,1,1,1,1,5,3,2,1,10,9,6,1,10,2,31,25,3,7,5,40,1,15,6,17,7,27,180,1,3,2,2,1,1,1,6,3,10,7,1,3,6,17,8,6,2,2,1,3,5,5,8,16,14,
        15,1,1,4,1,2,1,1,1,3,2,7,5,6,2,5,10,1,4,2,9,1,1,11,6,1,44,1,3,7,9,5,1,3,1,1,10,7,1,10,4,2,7,21,15,7,2,5,1,8,3,4,1,3,1,6,1,4,2,1,4,10,8,1,4,5,
        1,5,10,2,7,1,10,1,1,3,4,11,10,29,4,7,3,5,2,3,33,5,2,19,3,1,4,2,6,31,11,1,3,3,3,1,8,10,9,12,11,12,8,3,14,8,6,11,1,4,41,3,1,2,7,13,1,5,6,2,6,12,
        12,22,5,9,4,8,9,9,34,6,24,1,1,20,9,9,3,4,1,7,2,2,2,6,2,28,5,3,6,1,4,6,7,4,2,1,4,2,13,6,4,4,3,1,8,8,3,2,1,5,1,2,2,3,1,11,11,7,3,6,10,8,6,16,16,
        22,7,12,6,21,5,4,6,6,3,6,1,3,2,1,2,8,29,1,10,1,6,13,6,6,19,31,1,13,4,4,22,17,26,33,10,4,15,12,25,6,67,10,2,3,1,6,10,2,6,2,9,1,9,4,4,1,2,16,2,
        5,9,2,3,8,1,8,3,9,4,8,6,4,8,11,3,2,1,1,3,26,1,7,5,1,11,1,5,3,5,2,13,6,39,5,1,5,2,11,6,10,5,1,15,5,3,6,19,21,22,2,4,1,6,1,8,1,4,8,2,4,2,2,9,2,
        1,1,1,4,3,6,3,12,7,1,14,2,4,10,2,13,1,17,7,3,2,1,3,2,13,7,14,12,3,1,29,2,8,9,15,14,9,14,1,3,1,6,5,9,11,3,38,43,20,7,7,8,5,15,12,19,15,81,8,7,
        1,5,73,13,37,28,8,8,1,15,18,20,165,28,1,6,11,8,4,14,7,15,1,3,3,6,4,1,7,14,1,1,11,30,1,5,1,4,14,1,4,2,7,52,2,6,29,3,1,9,1,21,3,5,1,26,3,11,14,
        11,1,17,5,1,2,1,3,2,8,1,2,9,12,1,1,2,3,8,3,24,12,7,7,5,17,3,3,3,1,23,10,4,4,6,3,1,16,17,22,3,10,21,16,16,6,4,10,2,1,1,2,8,8,6,5,3,3,3,39,25,
        15,1,1,16,6,7,25,15,6,6,12,1,22,13,1,4,9,5,12,2,9,1,12,28,8,3,5,10,22,60,1,2,40,4,61,63,4,1,13,12,1,4,31,12,1,14,89,5,16,6,29,14,2,5,49,18,18,
        5,29,33,47,1,17,1,19,12,2,9,7,39,12,3,7,12,39,3,1,46,4,12,3,8,9,5,31,15,18,3,2,2,66,19,13,17,5,3,46,124,13,57,34,2,5,4,5,8,1,1,1,4,3,1,17,5,
        3,5,3,1,8,5,6,3,27,3,26,7,12,7,2,17,3,7,18,78,16,4,36,1,2,1,6,2,1,39,17,7,4,13,4,4,4,1,10,4,2,4,6,3,10,1,19,1,26,2,4,33,2,73,47,7,3,8,2,4,15,
        18,1,29,2,41,14,1,21,16,41,7,39,25,13,44,2,2,10,1,13,7,1,7,3,5,20,4,8,2,49,1,10,6,1,6,7,10,7,11,16,3,12,20,4,10,3,1,2,11,2,28,9,2,4,7,2,15,1,
        27,1,28,17,4,5,10,7,3,24,10,11,6,26,3,2,7,2,2,49,16,10,16,15,4,5,27,61,30,14,38,22,2,7,5,1,3,12,23,24,17,17,3,3,2,4,1,6,2,7,5,1,1,5,1,1,9,4,
        1,3,6,1,8,2,8,4,14,3,5,11,4,1,3,32,1,19,4,1,13,11,5,2,1,8,6,8,1,6,5,13,3,23,11,5,3,16,3,9,10,1,24,3,198,52,4,2,2,5,14,5,4,22,5,20,4,11,6,41,
        1,5,2,2,11,5,2,28,35,8,22,3,18,3,10,7,5,3,4,1,5,3,8,9,3,6,2,16,22,4,5,5,3,3,18,23,2,6,23,5,27,8,1,33,2,12,43,16,5,2,3,6,1,20,4,2,9,7,1,11,2,
        10,3,14,31,9,3,25,18,20,2,5,5,26,14,1,11,17,12,40,19,9,6,31,83,2,7,9,19,78,12,14,21,76,12,113,79,34,4,1,1,61,18,85,10,2,2,13,31,11,50,6,33,159,
        179,6,6,7,4,4,2,4,2,5,8,7,20,32,22,1,3,10,6,7,28,5,10,9,2,77,19,13,2,5,1,4,4,7,4,13,3,9,31,17,3,26,2,6,6,5,4,1,7,11,3,4,2,1,6,2,20,4,1,9,2,6,
        3,7,1,1,1,20,2,3,1,6,2,3,6,2,4,8,1,5,13,8,4,11,23,1,10,6,2,1,3,21,2,2,4,24,31,4,10,10,2,5,192,15,4,16,7,9,51,1,2,1,1,5,1,1,2,1,3,5,3,1,3,4,1,
        3,1,3,3,9,8,1,2,2,2,4,4,18,12,92,2,10,4,3,14,5,25,16,42,4,14,4,2,21,5,126,30,31,2,1,5,13,3,22,5,6,6,20,12,1,14,12,87,3,19,1,8,2,9,9,3,3,23,2,
        3,7,6,3,1,2,3,9,1,3,1,6,3,2,1,3,11,3,1,6,10,3,2,3,1,2,1,5,1,1,11,3,6,4,1,7,2,1,2,5,5,34,4,14,18,4,19,7,5,8,2,6,79,1,5,2,14,8,2,9,2,1,36,28,16,
        4,1,1,1,2,12,6,42,39,16,23,7,15,15,3,2,12,7,21,64,6,9,28,8,12,3,3,41,59,24,51,55,57,294,9,9,2,6,2,15,1,2,13,38,90,9,9,9,3,11,7,1,1,1,5,6,3,2,
        1,2,2,3,8,1,4,4,1,5,7,1,4,3,20,4,9,1,1,1,5,5,17,1,5,2,6,2,4,1,4,5,7,3,18,11,11,32,7,5,4,7,11,127,8,4,3,3,1,10,1,1,6,21,14,1,16,1,7,1,3,6,9,65,
        51,4,3,13,3,10,1,1,12,9,21,110,3,19,24,1,1,10,62,4,1,29,42,78,28,20,18,82,6,3,15,6,84,58,253,15,155,264,15,21,9,14,7,58,40,39,
    };
    static std::uint16_t base_ranges[] = // not zero-terminated
    {
        0x0020, 0x00FF, // Basic Latin + Latin Supplement
        0x3000, 0x30FF, // CJK Symbols and Punctuations, Hiragana, Katakana
        0x31F0, 0x31FF, // Katakana Phonetic Extensions
        0xFF00, 0xFFEF  // Half-width characters
    };
    const auto baseSize = sizeof(base_ranges) / sizeof(std::uint16_t);
    const auto japaneseSize = sizeof(accumulative_offsets_from_0x4E00) / sizeof(std::uint16_t);
    static std::uint16_t full_ranges[baseSize + japaneseSize * 2 + 1] = { 0 };
    if (!full_ranges[0])
    {
        memcpy(full_ranges, base_ranges, sizeof(base_ranges));
        UnpackAccumulativeOffsetsIntoRanges(0x4E00, accumulative_offsets_from_0x4E00, japaneseSize, full_ranges + baseSize);
    }
    return &full_ranges[0];
}
enum FontAtlasFlags_
{
    FontAtlasFlags_None = 0,
    FontAtlasFlags_NoPowerOfTwoHeight = 1 << 0,
    FontAtlasFlags_NoMouseCursors = 1 << 1,
    FontAtlasFlags_NoBakedLines = 1 << 2
};
enum GuiMouseCursor_
{
    GuiMouseCursor_None = -1,
    GuiMouseCursor_Arrow = 0,
    GuiMouseCursor_TextInput,         // When hovering over InputText, etc.
    GuiMouseCursor_ResizeAll,         // (Unused by Dear ImGui functions)
    GuiMouseCursor_ResizeNS,          // When hovering over an horizontal border
    GuiMouseCursor_ResizeEW,          // When hovering over a vertical border or a column
    GuiMouseCursor_ResizeNESW,        // When hovering over the bottom-left corner of a window
    GuiMouseCursor_ResizeNWSE,        // When hovering over the bottom-right corner of a window
    GuiMouseCursor_Hand,              // (Unused by Dear ImGui functions. Use for e.g. hyperlinks)
    GuiMouseCursor_NotAllowed,        // When hovering something with disallowed interaction. Usually a crossed circle.
    GuiMouseCursor_COUNT
};
static const ButiEngine::Vector2 FONT_ATLAS_DEFAULT_TEX_CURSOR_DATA[GuiMouseCursor_COUNT][3] =
{
    { ButiEngine::Vector2(0,3),  ButiEngine::Vector2(12,19), ButiEngine::Vector2(0, 0) },
    { ButiEngine::Vector2(13,0), ButiEngine::Vector2(7,16),  ButiEngine::Vector2(1, 8) },
    { ButiEngine::Vector2(31,0), ButiEngine::Vector2(23,23), ButiEngine::Vector2(11,11) },
    { ButiEngine::Vector2(21,0), ButiEngine::Vector2(9,23),  ButiEngine::Vector2(4,11) },
    { ButiEngine::Vector2(55,18),ButiEngine::Vector2(23, 9), ButiEngine::Vector2(11, 4) },
    { ButiEngine::Vector2(73,0), ButiEngine::Vector2(17,17), ButiEngine::Vector2(8, 8) },
    { ButiEngine::Vector2(55,0), ButiEngine::Vector2(17,17), ButiEngine::Vector2(8, 8) },
    { ButiEngine::Vector2(91,0), ButiEngine::Vector2(17,22), ButiEngine::Vector2(5, 0) },
    { ButiEngine::Vector2(91,0), ButiEngine::Vector2(17,22), ButiEngine::Vector2(5, 0) },
};


inline bool          BitArrayTestBit(const std::uint32_t* arr, std::int32_t n) { std::uint32_t mask = (std::uint32_t)1 << (n & 31); return (arr[n >> 5] & mask) != 0; }
inline void          BitArrayClearBit(std::uint32_t* arr, std::int32_t n) { std::uint32_t mask = (std::uint32_t)1 << (n & 31); arr[n >> 5] &= ~mask; }
inline void          BitArraySetBit(std::uint32_t* arr, std::int32_t n) { std::uint32_t mask = (std::uint32_t)1 << (n & 31); arr[n >> 5] |= mask; }
inline void          BitArraySetBitRange(std::uint32_t* arr, std::int32_t n, std::int32_t n2) {
    while (n <= n2)
    {
        std::int32_t a_mod = (n & 31);
        std::int32_t b_mod = ((n2 >= n + 31) ? 31 : (n2 & 31)) + 1;
        std::uint32_t mask = (std::uint32_t)(((std::uint64_t)1 << b_mod) - 1) & ~(std::uint32_t)(((std::uint64_t)1 << a_mod) - 1);
        arr[n >> 5] |= mask;
        n = (n + 32) & ~31;
    }
}

static inline std::int32_t       UpperPowerOfTwo(std::int32_t v) { v--; v |= v >> 1; v |= v >> 2; v |= v >> 4; v |= v >> 8; v |= v >> 16; v++; return v; }

struct BitVector
{
    std::vector<std::uint32_t> Storage;
    void            Create(const std::int32_t sz) { Storage.resize((sz + 31) >> 5); memset(Storage.data(), 0, (size_t)Storage.size() * sizeof(Storage[0])); }
    void            Clear() { Storage.clear(); }
    bool            TestBit(const std::int32_t n) const { return BitArrayTestBit(Storage.data(), n); }
    void            SetBit(const std::int32_t n) { BitArraySetBit(Storage.data(), n); }
    void            ClearBit(const std::int32_t n) { BitArrayClearBit(Storage.data(), n); }

};
class Font;
struct FontLoadData {
    FontLoadData() {
        FontData = nullptr;
        FontDataSize = 0;
        FontDataOwnedByAtlas = true;
        FontNo = 0;
        SizePixels = 0.0f;
        OversampleH = 3;
        OversampleV = 1;
        PixelSnapH = false;
        GlyphExtraSpacing = ButiEngine::Vector2(0.0f, 0.0f);
        GlyphOffset = ButiEngine::Vector2(0.0f, 0.0f);
        GlyphRanges = nullptr;
        GlyphMinAdvanceX = 0.0f;
        GlyphMaxAdvanceX = FLT_MAX;
        MergeMode = false;
        RasterizerFlags = 0x00;
        RasterizerMultiply = 1.0f;
        EllipsisChar = (std::uint16_t)-1;

        dst_font = nullptr;
    }
    void* FontData;
    std::int32_t             FontDataSize;
    bool            FontDataOwnedByAtlas;
    std::int32_t             FontNo;
    float           SizePixels;
    std::int32_t             OversampleH;
    std::int32_t             OversampleV;
    bool            PixelSnapH;
    ButiEngine::Vector2         GlyphExtraSpacing;
    ButiEngine::Vector2         GlyphOffset;
    const std::uint16_t* GlyphRanges;
    float           GlyphMinAdvanceX;
    float           GlyphMaxAdvanceX;
    bool            MergeMode;
    std::uint32_t    RasterizerFlags;
    float           RasterizerMultiply;
    char         EllipsisChar;
    std::shared_ptr<Font >dst_font;

    std::string            name;
};

class FontInformation :public ButiFont::IFontInformation {
public:
    FontInformation(const std::vector< ButiFont::FontGlyph>& arg_vec_glyphs, const std::int32_t arg_fallbackIndex, const std::vector<std::uint16_t>& arg_vec_indexLookup, const std::int32_t arg_size)
        :vec_glyphs(arg_vec_glyphs), vec_indexLookup(arg_vec_indexLookup), size(arg_size) {
        p_fallback = &vec_glyphs[vec_indexLookup[arg_fallbackIndex]];
    }
    const ButiFont::FontGlyph* * FindGlyphs_utf8(const char* arg_srcStr, std::int32_t& arg_ref_glyphSize)const override;
    std::int32_t GetSize()const override {
        return  size;
    }
private:
    std::vector< ButiFont::FontGlyph> vec_glyphs;
    ButiFont::FontGlyph* p_fallback;
    std::vector<std::uint16_t>           vec_indexLookup;
    std::int32_t size;
};

struct FontBuildSrcData
{
    stbtt_fontinfo      FontInfo;
    stbtt_pack_range    PackRange;        
    stbrp_rect* Rects;      
    stbtt_packedchar* PackedChars; 
    const std::uint16_t * SrcRanges;    
    std::int32_t                 DstIndex;     
    std::int32_t                 GlyphsHighest;
    std::int32_t                 GlyphsCount;  
    BitVector GlyphsSet;
    std::vector<std::int32_t>      GlyphsList; 
};

static void UnpackBitVectorToFlatIndexList(const BitVector* in, std::vector<std::int32_t>* out)
{

    auto begin = in->Storage.begin();
    auto it_end = in->Storage.end();
    for (auto it = begin; it < it_end; it++) {
        if (std::uint32_t entries_32 = *it) {
            for (std::uint32_t bit_n = 0; bit_n < 32; bit_n++)
                if (entries_32 & ((std::uint32_t)1 << bit_n))
                    out->push_back((std::int32_t)(((it - begin) << 5) + bit_n));
        }
    }
}

void    FontAtlasBuildMultiplyCalcLookupTable(unsigned char out_table[256], float in_brighten_factor)
{
    for (std::uint32_t i = 0; i < 256; i++)
    {
        std::uint32_t value = (std::uint32_t)(i * in_brighten_factor);
        out_table[i] = value > 255 ? 255 : (value & 0xFF);
    }
}
void    FontAtlasBuildMultiplyRectAlpha8(const unsigned char table[256], unsigned char* pixels, std::int32_t x, std::int32_t y, std::int32_t w, std::int32_t h, std::int32_t stride)
{
    unsigned char* data = pixels + x + y * stride;
    for (std::int32_t j = h; j > 0; j--, data += stride)
        for (std::int32_t i = 0; i < w; i++)
            data[i] = table[data[i]];
}


struct FontBuildDstData
{
    std::int32_t                 SrcCount;          
    std::int32_t                 GlyphsHighest;
    std::int32_t                 GlyphsCount;
    BitVector         GlyphsSet;      
};

struct FontAtlasCustomRect
{
    std::uint16_t  Width, Height;  
    std::uint16_t  X, Y;           
    std::uint32_t    GlyphID;       
    float           GlyphAdvanceX; 
    ButiEngine::Vector2          GlyphOffset;   
    Font* font;

    FontAtlasCustomRect() { Width = Height = 0; X = Y = 0xFFFF; GlyphID = 0; GlyphAdvanceX = 0.0f; GlyphOffset = ButiEngine::Vector2(0, 0); }
    bool IsPacked() const { return X != 0xFFFF; }
};

struct FontGlyphRangesBuilder
{
    std::vector<std::uint32_t> UsedChars;          

    FontGlyphRangesBuilder() { Clear(); }
    inline void     Clear() { std::int32_t size_in_bytes = (0xFFFF + 1) / 8; UsedChars.resize(size_in_bytes / (std::int32_t)sizeof(std::uint32_t)); memset(UsedChars.data(), 0, (size_t)size_in_bytes); }
    inline bool     GetBit(size_t n) const { std::int32_t off = (std::int32_t)(n >> 5); std::uint32_t mask = 1u << (n & 31); return (UsedChars[off] & mask) != 0; } 
    inline void     SetBit(size_t n) { std::int32_t off = (std::int32_t)(n >> 5); std::uint32_t mask = 1u << (n & 31); UsedChars[off] |= mask; }         
    inline void     AddChar(std::uint16_t c) { SetBit(c); }            
    void  AddText(const char* text, const char* text_end = nullptr);    
    void  AddRanges(const std::uint16_t* ranges);                      
    void  BuildRanges(std::vector<std::uint16_t>* out_ranges);         
};

struct FontAtlas
{
    FontAtlas();
    ~FontAtlas();

    void PushFont(std::shared_ptr< FontLoadData> arg_vlp_fontload);

    void              ClearInputData();
    void              ClearTexData();
    void              ClearFonts();
    void              Clear();

    void              GetTexDataAsAlpha8(unsigned char** out_pixels, std::int32_t* out_width, std::int32_t* out_height, std::int32_t* out_bytes_per_pixel = nullptr);


    const std::uint16_t* GetGlyphRangesDefault();

    std::int32_t               AddCustomRectRegular(std::int32_t width, std::int32_t height);

    void              CalcCustomRectUV(const FontAtlasCustomRect* rect, ButiEngine::Vector2* out_uv_min, ButiEngine::Vector2* out_uv_max) const;
    bool              GetMouseCursorTexData(const std::int32_t cursor, ButiEngine::Vector2* out_offset, ButiEngine::Vector2* out_size, ButiEngine::Vector2 out_uv_border[2], ButiEngine::Vector2 out_uv_fill[2]);
    FontAtlasCustomRect* GetCustomRectByIndex(std::int32_t index) { assert(index >= 0); return &CustomRects[index]; }
    bool Locked;
    std::int32_t  Flags;
    std::int32_t  TexDesiredWidth;
    std::int32_t  TexGlyphPadding;

    unsigned char* TexPixelsAlpha8;
    std::uint32_t* TexPixelsRGBA32;
    std::int32_t                         TexWidth;
    std::int32_t                         TexHeight;
    ButiEngine::Vector2         TexUvScale;
    ButiEngine::Vector2         TexUvWhitePixel;
    std::vector<FontAtlasCustomRect> CustomRects;

    ButiEngine::Vector4                      TexUvLines[0xFFFF + 1];

    // [Internal] Packing data
    std::int32_t                         PackIdMouseCursors;
    std::int32_t                         PackIdLines;
    std::vector<std::shared_ptr< Font>> fonts;
    std::vector<std::shared_ptr< FontLoadData>> configs;
#ifndef GUI_DISABLE_OBSOLETE_FUNCTIONS
    using CustomRect = FontAtlasCustomRect;
    using GlyphRangesBuilder = FontGlyphRangesBuilder;
#endif
};

struct Font
{
    std::vector<float>             IndexAdvanceX;
    float                       FallbackAdvanceX;
    float                       FontSize;

    std::vector<std::uint16_t>           IndexLookup;
    std::vector<ButiFont::FontGlyph>       Glyphs;
    const ButiFont::FontGlyph* FallbackGlyph;


    FontAtlas* ContainerAtlas;
    const FontLoadData* ConfigData;
    std::uint16_t                       ConfigDataCount;
    std::uint16_t                     FallbackChar;
    std::uint16_t EllipsisChar;
    bool                        DirtyLookupTables;
    float                       Scale;
    float                       Ascent, Descent;
    std::int32_t                         MetricsTotalSurface;
    char Used4kPagesMap[(0xFFFF + 1) / 4096 / 8];

    Font();
    ~Font();
    const ButiFont::FontGlyph* FindGlyph(std::uint16_t c) const;
    const ButiFont::FontGlyph* FindGlyphNoFallback(std::uint16_t c) const;
    float                       GetCharAdvance(std::uint16_t c) const { return ((std::int32_t)c < IndexAdvanceX.size()) ? IndexAdvanceX[(std::int32_t)c] : FallbackAdvanceX; }
    bool                        IsLoaded() const { return ContainerAtlas != nullptr; }
    const char* GetDebugName() const { return ConfigData ? ConfigData->name.c_str() : "<unknown>"; }

    ButiEngine::Vector2            CalcTextSizeA(float size, float max_width, float wrap_width, const char* text_begin, const char* text_end = nullptr, const char** remaining = nullptr) const; // utf8
    const char* CalcWordWrapPositionA(float scale, const char* text, const char* text_end, float wrap_width) const;

    void              BuildLookupTable();
    void              ClearOutputData();
    void              GrowIndex(std::int32_t new_size);
    void              AddGlyph(const FontLoadData* src_cfg, std::uint16_t c, float x0, float y0, float x1, float y1, float u0, float v0, float u1, float v1, float advance_x);
    void              AddRemapChar(std::uint16_t dst, std::uint16_t src, bool overwrite_dst = true); // Makes 'dst' character/glyph points to 'src' character/glyph. Currently needs to be called AFTER fonts have been built.
    void              SetGlyphVisible(std::uint16_t c, bool visible);
    void              SetFallbackChar(std::uint16_t c);
    bool              IsGlyphRangeUnused(std::uint32_t c_begin, std::uint32_t c_last);
};
void FontAtlasBuildInit(FontAtlas* atlas)
{

    if (atlas->PackIdMouseCursors < 0)
    {
        if (!(atlas->Flags & FontAtlasFlags_NoMouseCursors))
            atlas->PackIdMouseCursors = atlas->AddCustomRectRegular(FONT_ATLAS_DEFAULT_TEX_DATA_W * 2 + 1, FONT_ATLAS_DEFAULT_TEX_DATA_H);
        else
            atlas->PackIdMouseCursors = atlas->AddCustomRectRegular(2, 2);
    }

    if (atlas->PackIdLines < 0)
    {
        if (!(atlas->Flags & FontAtlasFlags_NoBakedLines))
            atlas->PackIdLines = atlas->AddCustomRectRegular(DRAWLIST_TEX_LINES_WIDTH_MAX + 2, DRAWLIST_TEX_LINES_WIDTH_MAX + 1);
    }
}

std::int32_t TextCharFromUtf8(std::uint32_t* out_char, const char* in_text, const char* in_text_end)
{
    std::uint32_t c = (std::uint32_t)-1;
    const unsigned char* str = (const unsigned char*)in_text;
    if (!(*str & 0x80))
    {
        c = (std::uint32_t)(*str++);
        *out_char = c;
        return 1;
    }
    if ((*str & 0xe0) == 0xc0)
    {
        *out_char = UNICODE_CODEPOINT_INVALID;
        if (in_text_end && in_text_end - (const char*)str < 2) return 1;
        if (*str < 0xc2) return 2;
        c = (std::uint32_t)((*str++ & 0x1f) << 6);
        if ((*str & 0xc0) != 0x80) return 2;
        c += (*str++ & 0x3f);
        *out_char = c;
        return 2;
    }
    if ((*str & 0xf0) == 0xe0)
    {
        *out_char = UNICODE_CODEPOINT_INVALID;
        if (in_text_end && in_text_end - (const char*)str < 3) return 1;
        if (*str == 0xe0 && (str[1] < 0xa0 || str[1] > 0xbf)) return 3;
        if (*str == 0xed && str[1] > 0x9f) return 3;
        c = (std::uint32_t)((*str++ & 0x0f) << 12);
        if ((*str & 0xc0) != 0x80) return 3;
        c += (std::uint32_t)((*str++ & 0x3f) << 6);
        if ((*str & 0xc0) != 0x80) return 3;
        c += (*str++ & 0x3f);
        *out_char = c;
        return 3;
    }
    if ((*str & 0xf8) == 0xf0)
    {
        *out_char = UNICODE_CODEPOINT_INVALID; 
        if (in_text_end && in_text_end - (const char*)str < 4) return 1;
        if (*str > 0xf4) return 4;
        if (*str == 0xf0 && (str[1] < 0x90 || str[1] > 0xbf)) return 4;
        if (*str == 0xf4 && str[1] > 0x8f) return 4;
        c = (std::uint32_t)((*str++ & 0x07) << 18);
        if ((*str & 0xc0) != 0x80) return 4;
        c += (std::uint32_t)((*str++ & 0x3f) << 12);
        if ((*str & 0xc0) != 0x80) return 4;
        c += (std::uint32_t)((*str++ & 0x3f) << 6);
        if ((*str & 0xc0) != 0x80) return 4;
        c += (*str++ & 0x3f);

        if ((c & 0xFFFFF800) == 0xD800) return 4;

        if (c > UNICODE_CODEPOINT_MAX) c = UNICODE_CODEPOINT_INVALID;
        *out_char = c;
        return 4;
    }
    *out_char = 0;
    return 0;
}

std::int32_t TextStrFromUtf8(std::uint16_t* buf, std::int32_t buf_size, const char* in_text, const char* in_text_end, const char** in_text_remaining)
{
    std::uint16_t* buf_out = buf;
    std::uint16_t* buf_end = buf + buf_size;
    while (buf_out < buf_end - 1 && (!in_text_end || in_text < in_text_end) && *in_text)
    {
        std::uint32_t c;
        in_text += TextCharFromUtf8(&c, in_text, in_text_end);
        if (c == 0)
            break;
        *buf_out++ = (std::uint16_t)c;
    }
    *buf_out = 0;
    if (in_text_remaining)
        *in_text_remaining = in_text;
    return (std::int32_t)(buf_out - buf);
}

std::int32_t TextCountCharsFromUtf8(const char* in_text, const char* in_text_end)
{
    std::int32_t char_count = 0;
    while ((!in_text_end || in_text < in_text_end) && *in_text)
    {
        std::uint32_t c;
        in_text += TextCharFromUtf8(&c, in_text, in_text_end);
        if (c == 0)
            break;
        char_count++;
    }
    return char_count;
}

static inline std::int32_t TextCharToUtf8(char* buf, std::int32_t buf_size, std::uint32_t c)
{
    if (c < 0x80)
    {
        buf[0] = (char)c;
        return 1;
    }
    if (c < 0x800)
    {
        if (buf_size < 2) return 0;
        buf[0] = (char)(0xc0 + (c >> 6));
        buf[1] = (char)(0x80 + (c & 0x3f));
        return 2;
    }
    if (c < 0x10000)
    {
        if (buf_size < 3) return 0;
        buf[0] = (char)(0xe0 + (c >> 12));
        buf[1] = (char)(0x80 + ((c >> 6) & 0x3f));
        buf[2] = (char)(0x80 + ((c) & 0x3f));
        return 3;
    }
    if (c <= 0x10FFFF)
    {
        if (buf_size < 4) return 0;
        buf[0] = (char)(0xf0 + (c >> 18));
        buf[1] = (char)(0x80 + ((c >> 12) & 0x3f));
        buf[2] = (char)(0x80 + ((c >> 6) & 0x3f));
        buf[3] = (char)(0x80 + ((c) & 0x3f));
        return 4;
    }
    // Invalid code point, the max unicode is 0x10FFFF
    return 0;
}

std::int32_t TextCountUtf8BytesFromChar(const char* in_text, const char* in_text_end)
{
    std::uint32_t unused = 0;
    return TextCharFromUtf8(&unused, in_text, in_text_end);
}

static inline std::int32_t TextCountUtf8BytesFromChar(std::uint32_t c)
{
    if (c < 0x80) return 1;
    if (c < 0x800) return 2;
    if (c < 0x10000) return 3;
    if (c <= 0x10FFFF) return 4;
    return 3;
}

std::int32_t TextStrToUtf8(char* buf, std::int32_t buf_size, const std::uint16_t* in_text, const std::uint16_t* in_text_end)
{
    char* buf_out = buf;
    const char* buf_end = buf + buf_size;
    while (buf_out < buf_end - 1 && (!in_text_end || in_text < in_text_end) && *in_text)
    {
        std::uint32_t c = (std::uint32_t)(*in_text++);
        if (c < 0x80)
            *buf_out++ = (char)c;
        else
            buf_out += TextCharToUtf8(buf_out, (std::int32_t)(buf_end - buf_out - 1), c);
    }
    *buf_out = 0;
    return (std::int32_t)(buf_out - buf);
}


void FontAtlasBuildSetupFont(FontAtlas* atlas, std::shared_ptr<Font> font, FontLoadData* font_config, float ascent, float descent)
{
    if (!font_config->MergeMode)
    {
        font->ClearOutputData();
        font->FontSize = font_config->SizePixels;
        font->ConfigData = font_config;
        font->ConfigDataCount = 0;
        font->ContainerAtlas = atlas;
        font->Ascent = ascent;
        font->Descent = descent;
    }
    font->ConfigDataCount++;
}
static const char FONT_ATLAS_DEFAULT_TEX_DATA_PIXELS[FONT_ATLAS_DEFAULT_TEX_DATA_W * FONT_ATLAS_DEFAULT_TEX_DATA_H + 1] =
{
    "..-         -XXXXXXX-    X    -           X           -XXXXXXX          -          XXXXXXX-     XX          "
    "..-         -X.....X-   X.X   -          X.X          -X.....X          -          X.....X-    X..X         "
    "---         -XXX.XXX-  X...X  -         X...X         -X....X           -           X....X-    X..X         "
    "X           -  X.X  - X.....X -        X.....X        -X...X            -            X...X-    X..X         "
    "XX          -  X.X  -X.......X-       X.......X       -X..X.X           -           X.X..X-    X..X         "
    "X.X         -  X.X  -XXXX.XXXX-       XXXX.XXXX       -X.X X.X          -          X.X X.X-    X..XXX       "
    "X..X        -  X.X  -   X.X   -          X.X          -XX   X.X         -         X.X   XX-    X..X..XXX    "
    "X...X       -  X.X  -   X.X   -    XX    X.X    XX    -      X.X        -        X.X      -    X..X..X..XX  "
    "X....X      -  X.X  -   X.X   -   X.X    X.X    X.X   -       X.X       -       X.X       -    X..X..X..X.X "
    "X.....X     -  X.X  -   X.X   -  X..X    X.X    X..X  -        X.X      -      X.X        -XXX X..X..X..X..X"
    "X......X    -  X.X  -   X.X   - X...XXXXXX.XXXXXX...X -         X.X   XX-XX   X.X         -X..XX........X..X"
    "X.......X   -  X.X  -   X.X   -X.....................X-          X.X X.X-X.X X.X          -X...X...........X"
    "X........X  -  X.X  -   X.X   - X...XXXXXX.XXXXXX...X -           X.X..X-X..X.X           - X..............X"
    "X.........X -XXX.XXX-   X.X   -  X..X    X.X    X..X  -            X...X-X...X            -  X.............X"
    "X..........X-X.....X-   X.X   -   X.X    X.X    X.X   -           X....X-X....X           -  X.............X"
    "X......XXXXX-XXXXXXX-   X.X   -    XX    X.X    XX    -          X.....X-X.....X          -   X............X"
    "X...X..X    ---------   X.X   -          X.X          -          XXXXXXX-XXXXXXX          -   X...........X "
    "X..X X..X   -       -XXXX.XXXX-       XXXX.XXXX       -------------------------------------    X..........X "
    "X.X  X..X   -       -X.......X-       X.......X       -    XX           XX    -           -    X..........X "
    "XX    X..X  -       - X.....X -        X.....X        -   X.X           X.X   -           -     X........X  "
    "      X..X          -  X...X  -         X...X         -  X..X           X..X  -           -     X........X  "
    "       XX           -   X.X   -          X.X          - X...XXXXXXXXXXXXX...X -           -     XXXXXXXXXX  "
    "------------        -    X    -           X           -X.....................X-           ------------------"
    "                    ----------------------------------- X...XXXXXXXXXXXXX...X -                             "
    "                                                      -  X..X           X..X  -                             "
    "                                                      -   X.X           X.X   -                             "
    "                                                      -    XX           XX    -                             "
};

void FontAtlasBuildRender1bppRectFromString(FontAtlas* atlas, std::int32_t x, std::int32_t y, std::int32_t w, std::int32_t h, const char* in_str, char in_marker_char, unsigned char in_marker_pixel_value)
{
    assert(x >= 0 && x + w <= atlas->TexWidth);
    assert(y >= 0 && y + h <= atlas->TexHeight);
    unsigned char* out_pixel = atlas->TexPixelsAlpha8 + x + (y * atlas->TexWidth);
    for (std::int32_t off_y = 0; off_y < h; off_y++, out_pixel += atlas->TexWidth, in_str += w) {
        for (std::int32_t off_x = 0; off_x < w; off_x++) {
            out_pixel[off_x] = (in_str[off_x] == in_marker_char) ? in_marker_pixel_value : 0x00;
        }
    }
}
void FontAtlasBuildRenderDefaultTexData(FontAtlas* atlas)
{
    FontAtlasCustomRect* r = atlas->GetCustomRectByIndex(atlas->PackIdMouseCursors);
    assert(r->IsPacked());

    const std::int32_t w = atlas->TexWidth;
    if (!(atlas->Flags & FontAtlasFlags_NoMouseCursors))
    {

        assert(r->Width == FONT_ATLAS_DEFAULT_TEX_DATA_W * 2 + 1 && r->Height == FONT_ATLAS_DEFAULT_TEX_DATA_H);
        const std::int32_t x_for_white = r->X;
        const std::int32_t x_for_black = r->X + FONT_ATLAS_DEFAULT_TEX_DATA_W + 1;
        FontAtlasBuildRender1bppRectFromString(atlas, x_for_white, r->Y, FONT_ATLAS_DEFAULT_TEX_DATA_W, FONT_ATLAS_DEFAULT_TEX_DATA_H, FONT_ATLAS_DEFAULT_TEX_DATA_PIXELS, '.', 0xFF);
        FontAtlasBuildRender1bppRectFromString(atlas, x_for_black, r->Y, FONT_ATLAS_DEFAULT_TEX_DATA_W, FONT_ATLAS_DEFAULT_TEX_DATA_H, FONT_ATLAS_DEFAULT_TEX_DATA_PIXELS, 'X', 0xFF);
    }
    else
    {
        assert(r->Width == 2 && r->Height == 2);
        const std::int32_t offset = (std::int32_t)r->X + (std::int32_t)r->Y * w;
        atlas->TexPixelsAlpha8[offset] = atlas->TexPixelsAlpha8[offset + 1] = atlas->TexPixelsAlpha8[offset + w] = atlas->TexPixelsAlpha8[offset + w + 1] = 0xFF;
    }
    atlas->TexUvWhitePixel = ButiEngine::Vector2((r->X + 0.5f) * atlas->TexUvScale.x, (r->Y + 0.5f) * atlas->TexUvScale.y);
}

void FontAtlasBuildFinish(FontAtlas* atlas)
{
    FontAtlasBuildRenderDefaultTexData(atlas);

    for (std::int32_t i = 0; i < atlas->CustomRects.size(); i++)
    {
        const FontAtlasCustomRect* r = &atlas->CustomRects[i];
        if (r->font == nullptr || r->GlyphID == 0)
            continue;


        ButiEngine::Vector2 uv0, uv1;
        atlas->CalcCustomRectUV(r, &uv0, &uv1);
        r->font->AddGlyph(nullptr, (std::uint16_t)r->GlyphID, r->GlyphOffset.x, r->GlyphOffset.y, r->GlyphOffset.x + r->Width, r->GlyphOffset.y + r->Height, uv0.x, uv0.y, uv1.x, uv1.y, r->GlyphAdvanceX);
    }


    for (std::int32_t i = 0; i < atlas->fonts.size(); i++) {
        if (atlas->fonts[i]->DirtyLookupTables) {
            atlas->fonts[i]->BuildLookupTable();
        }
    }

    
    for (std::int32_t i = 0; i < atlas->fonts.size(); i++)
    {
        auto font = atlas->fonts[i];
        if (font->EllipsisChar != (std::uint16_t)-1)
            continue;
        const std::uint16_t ellipsis_variants[] = { (std::uint16_t)0x2026, (std::uint16_t)0x0085 };
        for (std::int32_t j = 0; j < sizeof(ellipsis_variants) / sizeof(*ellipsis_variants); j++)
            if (font->FindGlyphNoFallback(ellipsis_variants[j]) != nullptr) 
            {
                font->EllipsisChar = ellipsis_variants[j];
                break;
            }
    }
}
void FontAtlasBuildPackCustomRects(FontAtlas* atlas, void* stbrp_context_opaque)
{
    stbrp_context* pack_context = (stbrp_context*)stbrp_context_opaque;


    std::vector<FontAtlasCustomRect>& user_rects = atlas->CustomRects;

    std::vector<stbrp_rect> pack_rects;
    pack_rects.resize(user_rects.size());

    for (std::int32_t i = 0; i < user_rects.size(); i++)
    {
        pack_rects[i].w = user_rects[i].Width;
        pack_rects[i].h = user_rects[i].Height;
    }
    stbrp_pack_rects(pack_context, &pack_rects[0], pack_rects.size());
    for (std::int32_t i = 0; i < pack_rects.size(); i++) {
        if (pack_rects[i].was_packed)
        {
            user_rects[i].X = pack_rects[i].x;
            user_rects[i].Y = pack_rects[i].y;
            assert(pack_rects[i].w == user_rects[i].Width && pack_rects[i].h == user_rects[i].Height);
            atlas->TexHeight = max(atlas->TexHeight, pack_rects[i].y + pack_rects[i].h);
        }
    }
}

const char* FindRenderedTextEnd(const char* text, const char* text_end)
{
    const char* text_display_end = text;
    if (!text_end)
        text_end = (const char*)-1;

    while (text_display_end < text_end && *text_display_end != '\0')
        text_display_end++;
    return text_display_end;
}

void CreateFontFromFile(FontAtlas* arg_p_atlas,  std::int32_t* arg_output_width,  std::int32_t* arg_output_height, unsigned char** arg_output_atlasTextureData,ButiFont::IFontInformation** arg_output_fontInfo)
{

    FontAtlasBuildInit(arg_p_atlas);



    arg_p_atlas->TexWidth = arg_p_atlas->TexHeight = 0;
    arg_p_atlas->TexUvScale = ButiEngine::Vector2(0.0f, 0.0f);
    arg_p_atlas->TexUvWhitePixel = ButiEngine::Vector2(0.0f, 0.0f);
    arg_p_atlas->ClearTexData();


    std::vector<FontBuildSrcData> src_tmp_array;
    std::vector<FontBuildDstData> dst_tmp_array;
    src_tmp_array.resize(arg_p_atlas->configs.size());
    dst_tmp_array.resize(arg_p_atlas->fonts.size());


    for (std::int32_t src_i = 0; src_i < arg_p_atlas->configs.size(); src_i++)
    {
        FontBuildSrcData& src_tmp = src_tmp_array[src_i];
        FontLoadData& cfg = *arg_p_atlas->configs[src_i];
        assert(cfg.dst_font && (!cfg.dst_font->IsLoaded() || cfg.dst_font->ContainerAtlas == arg_p_atlas));


        src_tmp.DstIndex = -1;
        for (std::int32_t output_i = 0; output_i < arg_p_atlas->fonts.size() && src_tmp.DstIndex == -1; output_i++) {
            if (cfg.dst_font == arg_p_atlas->fonts[output_i]) {
                src_tmp.DstIndex = output_i;
            }
        }
        assert(src_tmp.DstIndex != -1); 
        if (src_tmp.DstIndex == -1) {
            return ;
        }


        const std::int32_t font_offset = stbtt_GetFontOffsetForIndex((unsigned char*)cfg.FontData, cfg.FontNo);
        assert(font_offset >= 0);
        if (!stbtt_InitFont(&src_tmp.FontInfo, (unsigned char*)cfg.FontData, font_offset)) {

            return ;
        }
        FontBuildDstData& dst_tmp = dst_tmp_array[src_tmp.DstIndex];
        src_tmp.SrcRanges = cfg.GlyphRanges ? cfg.GlyphRanges : arg_p_atlas->GetGlyphRangesDefault();
        for (const std::uint16_t* src_range = src_tmp.SrcRanges; src_range[0] && src_range[1]; src_range += 2)
            src_tmp.GlyphsHighest = max(src_tmp.GlyphsHighest, (std::int32_t)src_range[1]);
        dst_tmp.SrcCount++;
        dst_tmp.GlyphsHighest = max(dst_tmp.GlyphsHighest, src_tmp.GlyphsHighest);
    }

    std::int32_t total_glyphs_count = 0;
    for (std::int32_t src_i = 0; src_i < src_tmp_array.size(); src_i++)
    {
        FontBuildSrcData& src_tmp = src_tmp_array[src_i];
        FontBuildDstData& dst_tmp = dst_tmp_array[src_tmp.DstIndex];
        src_tmp.GlyphsSet.Create(src_tmp.GlyphsHighest + 1);
        if (dst_tmp.GlyphsSet.Storage.empty())
            dst_tmp.GlyphsSet.Create(dst_tmp.GlyphsHighest + 1);

        for (const std::uint16_t* src_range = src_tmp.SrcRanges; src_range[0] && src_range[1]; src_range += 2) {
            for (std::uint32_t codepoint = src_range[0]; codepoint <= src_range[1]; codepoint++)
            {
                if (dst_tmp.GlyphsSet.TestBit(codepoint))    
                    continue;
                if (!stbtt_FindGlyphIndex(&src_tmp.FontInfo, codepoint))    
                    continue;


                src_tmp.GlyphsCount++;
                dst_tmp.GlyphsCount++;
                src_tmp.GlyphsSet.SetBit(codepoint);
                dst_tmp.GlyphsSet.SetBit(codepoint);
                total_glyphs_count++;
            }
        }
    }


    for (std::int32_t src_i = 0; src_i < src_tmp_array.size(); src_i++)
    {
        FontBuildSrcData& src_tmp = src_tmp_array[src_i];
        src_tmp.GlyphsList.reserve(src_tmp.GlyphsCount);
        UnpackBitVectorToFlatIndexList(&src_tmp.GlyphsSet, &src_tmp.GlyphsList);
        src_tmp.GlyphsSet.Clear();
        assert(src_tmp.GlyphsList.size() == src_tmp.GlyphsCount);
    }
    for (std::int32_t dst_i = 0; dst_i < dst_tmp_array.size(); dst_i++) {
        dst_tmp_array[dst_i].GlyphsSet.Clear();
    }
    dst_tmp_array.clear();


    std::vector<stbrp_rect> buf_rects;
    std::vector<stbtt_packedchar> buf_packedchars;
    buf_rects.resize(total_glyphs_count);
    buf_packedchars.resize(total_glyphs_count);


    std::int32_t total_surface = 0;
    std::int32_t buf_rects_out_n = 0;
    std::int32_t buf_packedchars_out_n = 0;
    for (std::int32_t src_i = 0; src_i < src_tmp_array.size(); src_i++)
    {
        FontBuildSrcData& src_tmp = src_tmp_array[src_i];
        if (src_tmp.GlyphsCount == 0)
            continue;

        src_tmp.Rects = &buf_rects[buf_rects_out_n];
        src_tmp.PackedChars = &buf_packedchars[buf_packedchars_out_n];
        buf_rects_out_n += src_tmp.GlyphsCount;
        buf_packedchars_out_n += src_tmp.GlyphsCount;

        FontLoadData& cfg = *arg_p_atlas->configs[src_i];
        src_tmp.PackRange.font_size = cfg.SizePixels;
        src_tmp.PackRange.first_unicode_codepoint_in_range = 0;
        src_tmp.PackRange.array_of_unicode_codepoints = src_tmp.GlyphsList.data();
        src_tmp.PackRange.num_chars = src_tmp.GlyphsList.size();
        src_tmp.PackRange.chardata_for_range = src_tmp.PackedChars;
        src_tmp.PackRange.h_oversample = (unsigned char)cfg.OversampleH;
        src_tmp.PackRange.v_oversample = (unsigned char)cfg.OversampleV;


        const float scale = (cfg.SizePixels > 0) ? stbtt_ScaleForPixelHeight(&src_tmp.FontInfo, cfg.SizePixels) : stbtt_ScaleForMappingEmToPixels(&src_tmp.FontInfo, -cfg.SizePixels);
        const std::int32_t padding = arg_p_atlas->TexGlyphPadding;
        for (std::int32_t glyph_i = 0; glyph_i < src_tmp.GlyphsList.size(); glyph_i++)
        {
            std::int32_t x0, y0, x1, y1;
            const std::int32_t glyph_index_in_font = stbtt_FindGlyphIndex(&src_tmp.FontInfo, src_tmp.GlyphsList[glyph_i]);
            assert(glyph_index_in_font != 0);
            stbtt_GetGlyphBitmapBoxSubpixel(&src_tmp.FontInfo, glyph_index_in_font, scale * cfg.OversampleH, scale * cfg.OversampleV, 0, 0, &x0, &y0, &x1, &y1);
            src_tmp.Rects[glyph_i].w = (stbrp_coord)(x1 - x0 + padding + cfg.OversampleH - 1);
            src_tmp.Rects[glyph_i].h = (stbrp_coord)(y1 - y0 + padding + cfg.OversampleV - 1);
            total_surface += src_tmp.Rects[glyph_i].w * src_tmp.Rects[glyph_i].h;
        }
    }
    const std::int32_t surface_sqrt = (std::int32_t)std::sqrt((float)total_surface) + 1;
    arg_p_atlas->TexHeight = 0;
    if (arg_p_atlas->TexDesiredWidth > 0)
        arg_p_atlas->TexWidth = arg_p_atlas->TexDesiredWidth;
    else
        arg_p_atlas->TexWidth = (surface_sqrt >= 4096 * 0.7f) ? 4096 : (surface_sqrt >= 2048 * 0.7f) ? 2048 : (surface_sqrt >= 1024 * 0.7f) ? 1024 : 512;


    const std::int32_t TEX_HEIGHT_MAX = 1024 * 32;
    stbtt_pack_context spc = {};
    stbtt_PackBegin(&spc, nullptr, arg_p_atlas->TexWidth, TEX_HEIGHT_MAX, 0, arg_p_atlas->TexGlyphPadding, nullptr);
    FontAtlasBuildPackCustomRects(arg_p_atlas, spc.pack_info);


    for (std::int32_t src_i = 0; src_i < src_tmp_array.size(); src_i++)
    {
        FontBuildSrcData& src_tmp = src_tmp_array[src_i];
        if (src_tmp.GlyphsCount == 0)
            continue;

        stbrp_pack_rects((stbrp_context*)spc.pack_info, src_tmp.Rects, src_tmp.GlyphsCount);


        for (std::int32_t glyph_i = 0; glyph_i < src_tmp.GlyphsCount; glyph_i++)
            if (src_tmp.Rects[glyph_i].was_packed)
                arg_p_atlas->TexHeight = max(arg_p_atlas->TexHeight, src_tmp.Rects[glyph_i].y + src_tmp.Rects[glyph_i].h);
    }


    arg_p_atlas->TexHeight = (arg_p_atlas->Flags & FontAtlasFlags_NoPowerOfTwoHeight) ? (arg_p_atlas->TexHeight + 1) : UpperPowerOfTwo(arg_p_atlas->TexHeight);
    arg_p_atlas->TexUvScale = ButiEngine::Vector2(1.0f / arg_p_atlas->TexWidth, 1.0f / arg_p_atlas->TexHeight);
    arg_p_atlas->TexPixelsAlpha8 = (unsigned char*)malloc(arg_p_atlas->TexWidth * arg_p_atlas->TexHeight);
    memset(arg_p_atlas->TexPixelsAlpha8, 0, arg_p_atlas->TexWidth * arg_p_atlas->TexHeight);
    spc.pixels = arg_p_atlas->TexPixelsAlpha8;
    spc.height = arg_p_atlas->TexHeight;


    for (std::int32_t src_i = 0; src_i < src_tmp_array.size(); src_i++)
    {
        FontLoadData& cfg = *arg_p_atlas->configs[src_i];
        FontBuildSrcData& src_tmp = src_tmp_array[src_i];
        if (src_tmp.GlyphsCount == 0)
            continue;

        stbtt_PackFontRangesRenderIntoRects(&spc, &src_tmp.FontInfo, &src_tmp.PackRange, 1, src_tmp.Rects);

        if (cfg.RasterizerMultiply != 1.0f)
        {
            unsigned char multiply_table[256];
            FontAtlasBuildMultiplyCalcLookupTable(multiply_table, cfg.RasterizerMultiply);
            stbrp_rect* r = &src_tmp.Rects[0];
            for (std::int32_t glyph_i = 0; glyph_i < src_tmp.GlyphsCount; glyph_i++, r++) {
                if (r->was_packed)
                    FontAtlasBuildMultiplyRectAlpha8(multiply_table, arg_p_atlas->TexPixelsAlpha8, r->x, r->y, r->w, r->h, arg_p_atlas->TexWidth * 1);
            }

        }
        src_tmp.Rects = nullptr;
    }


    stbtt_PackEnd(&spc);
    buf_rects.clear();

    for (std::int32_t src_i = 0; src_i < src_tmp_array.size(); src_i++)
    {
        FontBuildSrcData& src_tmp = src_tmp_array[src_i];
        if (src_tmp.GlyphsCount == 0)
            continue;
        FontLoadData& cfg = *arg_p_atlas->configs[src_i];
        auto dst_font = cfg.dst_font;

        const float font_scale = stbtt_ScaleForPixelHeight(&src_tmp.FontInfo, cfg.SizePixels);
        std::int32_t unscaled_ascent, unscaled_descent, unscaled_line_gap;
        stbtt_GetFontVMetrics(&src_tmp.FontInfo, &unscaled_ascent, &unscaled_descent, &unscaled_line_gap);

        const float ascent = floor(unscaled_ascent * font_scale + ((unscaled_ascent > 0.0f) ? +1 : -1));
        const float descent = floor(unscaled_descent * font_scale + ((unscaled_descent > 0.0f) ? +1 : -1));
        FontAtlasBuildSetupFont(arg_p_atlas, dst_font, &cfg, ascent, descent);
        const float font_off_x = cfg.GlyphOffset.x;
        const float font_off_y = cfg.GlyphOffset.y + round(dst_font->Ascent);

        for (std::int32_t glyph_i = 0; glyph_i < src_tmp.GlyphsCount; glyph_i++)
        {

            const std::int32_t codepoint = src_tmp.GlyphsList[glyph_i];
            const stbtt_packedchar& pc = src_tmp.PackedChars[glyph_i];
            stbtt_aligned_quad q;
            float unused_x = 0.0f, unused_y = 0.0f;
            stbtt_GetPackedQuad(src_tmp.PackedChars, arg_p_atlas->TexWidth, arg_p_atlas->TexHeight, glyph_i, &unused_x, &unused_y, &q, 0);
            dst_font->AddGlyph(&cfg, (std::uint16_t)codepoint, q.x0 + font_off_x, q.y0 + font_off_y, q.x1 + font_off_x, q.y1 + font_off_y, q.s0, q.t0, q.s1, q.t1, pc.xadvance);
        }
    }


    src_tmp_array.clear();

    FontAtlasBuildFinish(arg_p_atlas);

    *arg_output_atlasTextureData = arg_p_atlas->TexPixelsAlpha8;
    *arg_output_height = arg_p_atlas->TexHeight;
    *arg_output_width= arg_p_atlas->TexWidth;

    *arg_output_fontInfo= new FontInformation(arg_p_atlas->fonts[0]->Glyphs, arg_p_atlas->fonts[0]->FallbackChar, arg_p_atlas->fonts[0]->IndexLookup, arg_p_atlas->configs[0]->SizePixels);


}




FontAtlas::FontAtlas()
{
    Locked = false;
    Flags = FontAtlasFlags_None;

    TexDesiredWidth = 0;
    TexGlyphPadding = 1;

    TexPixelsAlpha8 = nullptr;
    TexPixelsRGBA32 = nullptr;
    TexWidth = TexHeight = 0;
    TexUvScale = ButiEngine::Vector2(0.0f, 0.0f);
    TexUvWhitePixel = ButiEngine::Vector2(0.0f, 0.0f);
    PackIdMouseCursors = PackIdLines = -1;
}

FontAtlas::~FontAtlas()
{
    Clear();
}

void FontAtlas::PushFont(std::shared_ptr<FontLoadData> arg_vlp_fontload)
{

    if (!arg_vlp_fontload->MergeMode) {
        fonts.push_back(std::make_shared< Font>());
        fonts.back()->ContainerAtlas = this;
    }
    else {
        assert(!fonts.empty());

    }
    configs.push_back(arg_vlp_fontload);
    auto new_font_cfg = configs.back();
    if (new_font_cfg->dst_font == nullptr) {
        new_font_cfg->dst_font = fonts.back();
    }

    if (!new_font_cfg->FontDataOwnedByAtlas)
    {
        new_font_cfg->FontData = arg_vlp_fontload->FontData;
        new_font_cfg->FontDataOwnedByAtlas = true;
    }

    if (new_font_cfg->dst_font->EllipsisChar == (std::uint16_t)-1)
        new_font_cfg->dst_font->EllipsisChar = arg_vlp_fontload->EllipsisChar;

    ClearTexData();

}

void FontAtlas::ClearInputData()
{
    assert(!Locked );
    for (std::int32_t i = 0; i < configs.size(); i++)
        if (configs[i]->FontData && configs[i]->FontDataOwnedByAtlas)
        {
            free(configs[i]->FontData);
            configs[i]->FontData = nullptr;
        }

    for (std::int32_t i = 0; i < fonts.size(); i++) {

        fonts[i]->ConfigData = nullptr;
        fonts[i]->ConfigDataCount = 0;
    }
    configs.clear();
    CustomRects.clear();
    PackIdMouseCursors = PackIdLines = -1;
}

void FontAtlas::ClearTexData()
{

}

void FontAtlas::ClearFonts()
{
    assert(!Locked );


    fonts.clear();
}

void FontAtlas::Clear()
{
    ClearInputData();
    ClearTexData();
    ClearFonts();
}
void FontAtlas::GetTexDataAsAlpha8(unsigned char** out_pixels, std::int32_t* out_width, std::int32_t* out_height, std::int32_t* out_bytes_per_pixel)
{
    if (TexPixelsAlpha8 == nullptr)
    {
        assert(0);

    }

    *out_pixels = TexPixelsAlpha8;
    if (out_width) *out_width = TexWidth;
    if (out_height) *out_height = TexHeight;
    if (out_bytes_per_pixel) *out_bytes_per_pixel = 1;
}


const std::uint16_t* FontAtlas::GetGlyphRangesDefault()
{
    static const std::uint16_t ranges[] =
    {
        0x0020, 0x00FF, 
        0,
    };
    return ranges;
}


std::int32_t FontAtlas::AddCustomRectRegular(std::int32_t width, std::int32_t height)
{
    assert(width > 0 && width <= 0xFFFF);
    assert(height > 0 && height <= 0xFFFF);
    FontAtlasCustomRect r;
    r.Width = (std::uint16_t)width;
    r.Height = (std::uint16_t)height;
    CustomRects.push_back(r);
    return CustomRects.size() - 1; 
}

void FontAtlas::CalcCustomRectUV(const FontAtlasCustomRect* rect, ButiEngine::Vector2* out_uv_min, ButiEngine::Vector2* out_uv_max) const
{
    assert(TexWidth > 0 && TexHeight > 0);  
    assert(rect->IsPacked());               
    *out_uv_min = ButiEngine::Vector2((float)rect->X * TexUvScale.x, (float)rect->Y * TexUvScale.y);
    *out_uv_max = ButiEngine::Vector2((float)(rect->X + rect->Width) * TexUvScale.x, (float)(rect->Y + rect->Height) * TexUvScale.y);
}

bool FontAtlas::GetMouseCursorTexData(const std::int32_t cursor_type, ButiEngine::Vector2* out_offset, ButiEngine::Vector2* out_size, ButiEngine::Vector2 out_uv_border[2], ButiEngine::Vector2 out_uv_fill[2])
{
    if (cursor_type <= GuiMouseCursor_None || cursor_type >= GuiMouseCursor_COUNT)
        return false;
    if (Flags & FontAtlasFlags_NoMouseCursors)
        return false;

    assert(PackIdMouseCursors != -1);
    FontAtlasCustomRect* r = GetCustomRectByIndex(PackIdMouseCursors);
    ButiEngine::Vector2 pos = FONT_ATLAS_DEFAULT_TEX_CURSOR_DATA[cursor_type][0] + ButiEngine::Vector2((float)r->X, (float)r->Y);
    ButiEngine::Vector2 size = FONT_ATLAS_DEFAULT_TEX_CURSOR_DATA[cursor_type][1];
    *out_size = size;
    *out_offset = FONT_ATLAS_DEFAULT_TEX_CURSOR_DATA[cursor_type][2];
    out_uv_border[0] = (pos)*TexUvScale;
    out_uv_border[1] = (pos + size) * TexUvScale;
    pos.x += FONT_ATLAS_DEFAULT_TEX_DATA_W + 1;
    out_uv_fill[0] = (pos)*TexUvScale;
    out_uv_fill[1] = (pos + size) * TexUvScale;
    return true;
}

Font::Font()
{
    FontSize = 0.0f;
    FallbackAdvanceX = 0.0f;
    FallbackChar = (std::uint16_t)'?';
    EllipsisChar = (std::uint16_t)-1;
    FallbackGlyph = nullptr;
    ContainerAtlas = nullptr;
    ConfigData = nullptr;
    ConfigDataCount = 0;
    DirtyLookupTables = false;
    Scale = 1.0f;
    Ascent = Descent = 0.0f;
    MetricsTotalSurface = 0;
    memset(Used4kPagesMap, 0, sizeof(Used4kPagesMap));
}

Font::~Font()
{
    ClearOutputData();
}

const ButiFont::FontGlyph* Font::FindGlyph(std::uint16_t c) const
{
    if (c >= (size_t)IndexLookup.size())
        return FallbackGlyph;
    const std::uint16_t i = IndexLookup[c];
    if (i == (std::uint16_t)-1)
        return FallbackGlyph;
    return &Glyphs[i];
}

const ButiFont::FontGlyph* Font::FindGlyphNoFallback(std::uint16_t c) const
{
    if (c >= (size_t)IndexLookup.size())
        return nullptr;
    const std::uint16_t i = IndexLookup[c];
    if (i == (std::uint16_t)-1)
        return nullptr;
    return &Glyphs[i];
}

ButiEngine::Vector2 Font::CalcTextSizeA(float size, float max_width, float wrap_width, const char* text_begin, const char* text_end, const char** remaining) const
{
    if (!text_end)
        text_end = text_begin + strlen(text_begin); // FIXME-OPT: Need to avoid this.

    const float line_height = size;
    const float scale = size / FontSize;

    ButiEngine::Vector2 text_size = ButiEngine::Vector2(0, 0);
    float line_width = 0.0f;

    const bool word_wrap_enabled = (wrap_width > 0.0f);
    const char* word_wrap_eol = nullptr;

    const char* s = text_begin;
    while (s < text_end)
    {
        if (word_wrap_enabled)
        {
            // Calculate how far we can render. Requires two passes on the string data but keeps the code simple and not intrusive for what's essentially an uncommon feature.
            if (!word_wrap_eol)
            {
                word_wrap_eol = CalcWordWrapPositionA(scale, s, text_end, wrap_width - line_width);
                if (word_wrap_eol == s) // Wrap_width is too small to fit anything. Force displaying 1 character to minimize the height discontinuity.
                    word_wrap_eol++;    // +1 may not be a character start point in UTF-8 but it's ok because we use s >= word_wrap_eol below
            }

            if (s >= word_wrap_eol)
            {
                if (text_size.x < line_width)
                    text_size.x = line_width;
                text_size.y += line_height;
                line_width = 0.0f;
                word_wrap_eol = nullptr;

                // Wrapping skips upcoming blanks
                while (s < text_end)
                {
                    const char c = *s;
                    if (CharIsBlankA(c)) { s++; }
                    else if (c == '\n') { s++; break; }
                    else { break; }
                }
                continue;
            }
        }

        // Decode and advance source
        const char* prev_s = s;
        std::uint32_t c = (std::uint32_t)*s;
        if (c < 0x80)
        {
            s += 1;
        }
        else
        {
            s += TextCharFromUtf8(&c, s, text_end);
            if (c == 0) // Malformed UTF-8?
                break;
        }

        if (c < 32)
        {
            if (c == '\n')
            {
                text_size.x = max(text_size.x, line_width);
                text_size.y += line_height;
                line_width = 0.0f;
                continue;
            }
            if (c == '\r')
                continue;
        }

        const float char_width = ((std::int32_t)c < IndexAdvanceX.size() ? IndexAdvanceX[c] : FallbackAdvanceX) * scale;
        if (line_width + char_width >= max_width)
        {
            s = prev_s;
            break;
        }

        line_width += char_width;
    }

    if (text_size.x < line_width)
        text_size.x = line_width;

    if (line_width > 0 || text_size.y == 0.0f)
        text_size.y += line_height;

    if (remaining)
        *remaining = s;

    return text_size;
}

const char* Font::CalcWordWrapPositionA(float scale, const char* text, const char* text_end, float wrap_width) const
{
    float line_width = 0.0f;
    float word_width = 0.0f;
    float blank_width = 0.0f;
    wrap_width /= scale; 

    const char* word_end = text;
    const char* prev_word_end = nullptr;
    bool inside_word = true;

    const char* s = text;
    while (s < text_end)
    {
        std::uint32_t c = (std::uint32_t)*s;
        const char* next_s;
        if (c < 0x80)
            next_s = s + 1;
        else
            next_s = s + TextCharFromUtf8(&c, s, text_end);
        if (c == 0)
            break;

        if (c < 32)
        {
            if (c == '\n')
            {
                line_width = word_width = blank_width = 0.0f;
                inside_word = true;
                s = next_s;
                continue;
            }
            if (c == '\r')
            {
                s = next_s;
                continue;
            }
        }

        const float char_width = ((std::int32_t)c < IndexAdvanceX.size() ? IndexAdvanceX[c] : FallbackAdvanceX);
        if (CharIsBlankW(c))
        {
            if (inside_word)
            {
                line_width += blank_width;
                blank_width = 0.0f;
                word_end = s;
            }
            blank_width += char_width;
            inside_word = false;
        }
        else
        {
            word_width += char_width;
            if (inside_word)
            {
                word_end = next_s;
            }
            else
            {
                prev_word_end = word_end;
                line_width += word_width + blank_width;
                word_width = blank_width = 0.0f;
            }

            inside_word = (c != '.' && c != ',' && c != ';' && c != '!' && c != '?' && c != '\"');
        }


        if (line_width + word_width > wrap_width)
        {
            if (word_width < wrap_width)
                s = prev_word_end ? prev_word_end : word_end;
            break;
        }

        s = next_s;
    }

    return s;
}

void Font::BuildLookupTable()
{
    std::int32_t max_codepoint = 0;
    for (std::int32_t i = 0; i != Glyphs.size(); i++)
        max_codepoint = max(max_codepoint, (std::int32_t)Glyphs[i].Codepoint);


    IndexAdvanceX.clear();
    IndexLookup.clear();
    DirtyLookupTables = false;
    memset(Used4kPagesMap, 0, sizeof(Used4kPagesMap));
    GrowIndex(max_codepoint + 1);
    for (std::int32_t i = 0; i < Glyphs.size(); i++)
    {
        std::int32_t codepoint = (std::int32_t)Glyphs[i].Codepoint;
        IndexAdvanceX[codepoint] = Glyphs[i].AdvanceX;
        IndexLookup[codepoint] = (std::uint16_t)i;

        const std::int32_t page_n = codepoint / 4096;
        Used4kPagesMap[page_n >> 3] |= 1 << (page_n & 7);
    }

    if (FindGlyph((std::uint16_t)' '))
    {
        if (Glyphs.back().Codepoint != '\t')
            Glyphs.resize(Glyphs.size() + 1);
        ButiFont::FontGlyph& tab_glyph = Glyphs.back();
        tab_glyph = *FindGlyph((std::uint16_t)' ');
        tab_glyph.Codepoint = '\t';
        tab_glyph.AdvanceX *= TABSIZE;
        IndexAdvanceX[(std::int32_t)tab_glyph.Codepoint] = (float)tab_glyph.AdvanceX;
        IndexLookup[(std::int32_t)tab_glyph.Codepoint] = (std::uint16_t)(Glyphs.size() - 1);
    }

    SetGlyphVisible((std::uint16_t)' ', false);
    SetGlyphVisible((std::uint16_t)'\t', false);

    FallbackGlyph = FindGlyphNoFallback(FallbackChar);
    FallbackAdvanceX = FallbackGlyph ? FallbackGlyph->AdvanceX : 0.0f;
    for (std::int32_t i = 0; i < max_codepoint + 1; i++) {
        if (IndexAdvanceX[i] < 0.0f) {
            IndexAdvanceX[i] = FallbackAdvanceX;
        }

    }
}

void Font::ClearOutputData()
{
    FontSize = 0.0f;
    FallbackAdvanceX = 0.0f;
    Glyphs.clear();
    IndexAdvanceX.clear();
    IndexLookup.clear();
    FallbackGlyph = nullptr;
    ContainerAtlas = nullptr;
    DirtyLookupTables = true;
    Ascent = Descent = 0.0f;
    MetricsTotalSurface = 0;
}

void Font::GrowIndex(std::int32_t new_size)
{
    assert(IndexAdvanceX.size() == IndexLookup.size());
    if (new_size <= IndexLookup.size())
        return;
    IndexAdvanceX.resize(new_size, -1.0f);
    IndexLookup.resize(new_size, (std::uint16_t)-1);
}

void Font::AddGlyph(const FontLoadData* src_cfg, std::uint16_t codepoint, float x0, float y0, float x1, float y1, float u0, float v0, float u1, float v1, float advance_x)
{
    if (src_cfg != nullptr)
    {
        // Clamp & recenter if needed
        const float advance_x_original = advance_x;
        advance_x = std::clamp (advance_x, src_cfg->GlyphMinAdvanceX, src_cfg->GlyphMaxAdvanceX);
        if (advance_x != advance_x_original)
        {
            float char_off_x = src_cfg->PixelSnapH ? floor((advance_x - advance_x_original) * 0.5f) : (advance_x - advance_x_original) * 0.5f;
            x0 += char_off_x;
            x1 += char_off_x;
        }

        // Snap to pixel
        if (src_cfg->PixelSnapH) {
            advance_x = round(advance_x);
        }

        // Bake spacing
        advance_x += src_cfg->GlyphExtraSpacing.x;
    }

    Glyphs.resize(Glyphs.size() + 1);
    ButiFont::FontGlyph& glyph = Glyphs.back();
    glyph.Codepoint = (std::uint32_t)codepoint;
    glyph.Visible = (x0 != x1) && (y0 != y1);
    glyph.X0 = x0;
    glyph.Y0 = y0;
    glyph.X1 = x1;
    glyph.Y1 = y1;
    glyph.U0 = u0;
    glyph.V0 = v0;
    glyph.U1 = u1;
    glyph.V1 = v1;
    glyph.AdvanceX = advance_x;


    float pad = ContainerAtlas->TexGlyphPadding + 0.99f;
    DirtyLookupTables = true;
    MetricsTotalSurface += (std::int32_t)((glyph.U1 - glyph.U0) * ContainerAtlas->TexWidth + pad) * (std::int32_t)((glyph.V1 - glyph.V0) * ContainerAtlas->TexHeight + pad);
}

void Font::AddRemapChar(std::uint16_t dst, std::uint16_t src, bool overwrite_dst)
{
    assert(IndexLookup.size() > 0);
    std::uint32_t index_size = (std::uint32_t)IndexLookup.size();

    if (dst < index_size && IndexLookup[dst] == (std::uint16_t)-1 && !overwrite_dst) // 'dst' already exists
        return;
    if (src >= index_size && dst >= index_size) 
        return;

    GrowIndex(dst + 1);
    IndexLookup[dst] = (src < index_size) ? IndexLookup[src] : (std::uint16_t)-1;
    IndexAdvanceX[dst] = (src < index_size) ? IndexAdvanceX[src] : 1.0f;
}

void Font::SetGlyphVisible(std::uint16_t c, bool visible)
{
    if (ButiFont::FontGlyph* glyph = (ButiFont::FontGlyph*)(void*)FindGlyph((std::uint16_t)c))
        glyph->Visible = visible ? 1 : 0;
}

void Font::SetFallbackChar(std::uint16_t c)
{
    FallbackChar = c;
    BuildLookupTable();
}

bool Font::IsGlyphRangeUnused(std::uint32_t c_begin, std::uint32_t c_last)
{
    std::uint32_t page_begin = (c_begin / 4096);
    std::uint32_t page_last = (c_last / 4096);
    for (std::uint32_t page_n = page_begin; page_n <= page_last; page_n++) {
        if ((page_n >> 3) < sizeof(Used4kPagesMap))
        {
            if (Used4kPagesMap[page_n >> 3] & (1 << (page_n & 7)))
                return false;
        }
    }
    return true;
}

void FontGlyphRangesBuilder::AddText(const char* text, const char* text_end)
{
    while (text_end ? (text < text_end) : *text)
    {
        std::uint32_t c = 0;
        std::int32_t c_len = TextCharFromUtf8(&c, text, text_end);
        text += c_len;
        if (c_len == 0)
            break;
        AddChar((std::uint16_t)c);
    }
}

void FontGlyphRangesBuilder::AddRanges(const std::uint16_t* ranges)
{
    for (; ranges[0]; ranges += 2) {
        for (std::uint16_t c = ranges[0]; c <= ranges[1]; c++) {
            AddChar(c);
        }
    }
}

void FontGlyphRangesBuilder::BuildRanges(std::vector<std::uint16_t>* out_ranges)
{
    const std::int32_t max_codepoint = UNICODE_CODEPOINT_MAX;
    for (std::int32_t n = 0; n <= max_codepoint; n++) {
        if (GetBit(n))
        {
            out_ranges->push_back((std::uint16_t)n);
            while (n < max_codepoint && GetBit(n + 1))
                n++;
            out_ranges->push_back((std::uint16_t)n);
        }
    }
    out_ranges->push_back(0);
}

const ButiFont::FontGlyph** FontInformation::FindGlyphs_utf8(const char* arg_srcStr, std::int32_t& arg_ref_glyphSize)const
{


    const char* s = arg_srcStr;
    auto end = FindRenderedTextEnd(s, nullptr);
    std::vector<const ButiFont::FontGlyph*> vec_temp;
    while (s < end)
    {

        std::uint32_t c = *s;



        if (c < 0x80)
        {
            s += 1;
        }
        else
        {
            s += TextCharFromUtf8(&c, s, end);
            if (c == 0) // Malformed UTF-8?
                break;
        }


        if (c < 32)
        {
            if (c == '\n')
            {
                vec_temp.push_back(nullptr);
                continue;
            }
            if (c == '\r')
            {
                vec_temp.push_back(nullptr);
                continue;
            }
        }

        if (c >= (size_t)vec_indexLookup.size())
            vec_temp.push_back(p_fallback);
        const std::uint16_t i = vec_indexLookup[c];
        if (i == (std::uint16_t)-1)
            vec_temp.push_back(p_fallback);

        vec_temp.push_back(&vec_glyphs[i]);
    }
    const ButiFont::FontGlyph** output = (const ButiFont::FontGlyph**)malloc(sizeof(const ButiFont::FontGlyph*) * vec_temp.size());

    memcpy(output, vec_temp.data(), sizeof(ButiFont::FontGlyph*) * vec_temp.size());
    arg_ref_glyphSize = vec_temp.size();
    return output;
}

void ButiFont::LoadTTF(const char* arg_filePath, const std::int32_t size, ButiFont::FontLanguage arg_lang,  std::int32_t* arg_output_width,  std::int32_t* arg_output_height, unsigned char** arg_output_atlasTextureData, IFontInformation** arg_output_fontInfo)
{

    std::ifstream input= std::ifstream(arg_filePath, std::ios::in | std::ios::binary);

    auto p_fontLoad = std::make_shared< FontLoadData>();
    p_fontLoad->name = std::string(arg_filePath);


    auto current = input.tellg();
    input.seekg(0, std::ios::end);
    p_fontLoad->FontDataSize = input.tellg() - current;
    input.seekg(current);



    p_fontLoad->FontData = malloc(p_fontLoad->FontDataSize);

    input.read((char*)p_fontLoad->FontData, p_fontLoad->FontDataSize);

    p_fontLoad->SizePixels = size;
    switch (arg_lang)
    {
    case ButiFont::FontLanguage::FONTLANG_JAPANESE:

        p_fontLoad->GlyphRanges = GetGlyphRangesJapanese();
        break;
    default:
        assert(0);
        break;
    }

    auto p_atlas = new FontAtlas();

    p_atlas->PushFont(p_fontLoad);

    input.close();

   CreateFontFromFile(p_atlas,arg_output_width,arg_output_height,arg_output_atlasTextureData,arg_output_fontInfo);

    delete p_atlas;
}

void ButiFont::ReleaseMemory(void* arg_release)
{
    delete arg_release;
}
