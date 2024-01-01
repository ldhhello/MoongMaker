#pragma once

enum Sound
{
    //A = 0,
    //ASharp = 1,
    //B = 2,
    C = 3,
    CSharp = 4,
    DFlat = 4,
    D = 5,
    DSharp = 6,
    EFlat = 6,
    E = 7,
    F = 8,
    FSharp = 9,
    GFlat = 9,
    G = 10,
    GSharp = 11,
    AFlat = 11,
    A = 12,
    ASharp = 13,
    BFlat = 13,
    B = 14
};

const char sound_ch[] = {
    ' ', ' ', ' ', // (A ASharp B)
    'C', ' ', // C CSharp
    'D', ' ', // D DSharp
    'E',      // E
    'F', ' ', // F FSharp
    'G', ' ', // G GSharp
    'A', ' ', // A ASharp
    'B'       // B
};

extern int sound_table[256]; // in main.cpp