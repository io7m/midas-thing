#ifndef ROM_C
#define ROM_C

#include "rom.h"

#define ROM_RANDOM_SIZE 256

const char rom_version[] PROGMEM = "0.0.1";

const uint8_t rom_random[ROM_RANDOM_SIZE] PROGMEM = {
    0xbe, 0xed, 0xc0, 0x1d, 0xbd, 0xf3, 0x3a, 0x1f, 0x0e, 0x5a, 0x7c, 0x5a,
    0x29, 0xaa, 0x01, 0x7e, 0xba, 0xea, 0x01, 0x80, 0xa3, 0x37, 0xa5, 0x15,
    0xaa, 0x8d, 0xa4, 0x69, 0x4c, 0xf3, 0xd7, 0x4a, 0xcb, 0x70, 0xcd, 0x5f,
    0x40, 0x1d, 0x08, 0xf3, 0xd6, 0x53, 0x01, 0xce, 0x2d, 0x5f, 0x99, 0x76,
    0x6a, 0x52, 0x65, 0xd5, 0xd9, 0xef, 0xbf, 0x55, 0x8c, 0xe0, 0xb6, 0xbc,
    0x27, 0x95, 0x69, 0x56, 0xfc, 0xae, 0xd3, 0xc5, 0x0c, 0x03, 0x57, 0x4e,
    0xd8, 0xd6, 0xef, 0x87, 0x1f, 0x62, 0x88, 0x01, 0x83, 0xcd, 0x9a, 0x45,
    0x3d, 0x79, 0x00, 0xe2, 0x79, 0x86, 0x95, 0x69, 0x34, 0x3e, 0x31, 0xb8,
    0xe6, 0xaa, 0x43, 0x06, 0xb1, 0x0d, 0xed, 0x58, 0x2c, 0x94, 0xc0, 0x90,
    0xf9, 0x1b, 0xba, 0x7f, 0x32, 0x7c, 0x87, 0x6f, 0x29, 0x0d, 0x6b, 0xc3,
    0x00, 0x05, 0x0b, 0x21, 0xa3, 0xf4, 0x1e, 0xad, 0xa1, 0x9e, 0x25, 0xd4,
    0xb8, 0xb7, 0x96, 0xed, 0xef, 0xa9, 0xa9, 0x50, 0x10, 0x0e, 0x12, 0xe6,
    0x0e, 0x1d, 0x2d, 0xe8, 0x4f, 0x7d, 0x81, 0x9e, 0xb0, 0x0f, 0x9b, 0x14,
    0x0b, 0x17, 0x5f, 0x55, 0xdd, 0x05, 0x45, 0x7d, 0x65, 0xf7, 0x2d, 0x24,
    0xd3, 0xd6, 0x75, 0xc2, 0x74, 0xda, 0x74, 0x0a, 0x49, 0x0a, 0xe5, 0xb4,
    0x1e, 0xa4, 0xcb, 0x85, 0x8a, 0x81, 0x22, 0xb0, 0xe7, 0xfd, 0xa0, 0xa2,
    0x28, 0xdd, 0x81, 0x8e, 0xca, 0xd8, 0xeb, 0xef, 0x62, 0xe3, 0x6a, 0x22,
    0xe3, 0x35, 0xdf, 0xbb, 0xaf, 0x63, 0x94, 0x5c, 0xc3, 0x0f, 0x45, 0xb1,
    0x4d, 0x8b, 0x81, 0x3e, 0x8f, 0x1d, 0x61, 0x3f, 0x97, 0xae, 0x3a, 0xc2,
    0x52, 0x1f, 0xb8, 0x56, 0x7f, 0x5c, 0x7f, 0xb9, 0xf9, 0x6d, 0x2f, 0x7c,
    0xd0, 0x59, 0xc3, 0x03, 0x65, 0x4d, 0x19, 0x37, 0x36, 0x15, 0x93, 0xd2,
    0x28, 0xc5, 0x6e, 0x08,
};

const uint8_t rom[ROM_SIZE] PROGMEM = {
    0x00, 0x78, 0x14, 0x12, 0x12, 0x14, 0x78, 0x00, 0x00, 0x7e, 0x4a, 0x4a,
    0x4a, 0x4a, 0x34, 0x00, 0x00, 0x3c, 0x42, 0x42, 0x42, 0x42, 0x24, 0x00,
    0x00, 0x42, 0x7e, 0x42, 0x42, 0x24, 0x18, 0x00, 0x00, 0x7e, 0x4a, 0x4a,
    0x4a, 0x4a, 0x42, 0x00, 0x00, 0x7e, 0x0a, 0x0a, 0x0a, 0x0a, 0x02, 0x00,
    0x00, 0x3c, 0x42, 0x42, 0x52, 0x52, 0x34, 0x00, 0x00, 0x7e, 0x08, 0x08,
    0x08, 0x08, 0x7e, 0x00, 0x00, 0x00, 0x42, 0x7e, 0x42, 0x00, 0x00, 0x00,
    0x00, 0x20, 0x40, 0x40, 0x42, 0x3e, 0x02, 0x00, 0x00, 0x7e, 0x10, 0x08,
    0x14, 0x22, 0x42, 0x00, 0x00, 0x7e, 0x40, 0x40, 0x40, 0x40, 0x40, 0x00,
    0x00, 0x7e, 0x04, 0x08, 0x08, 0x04, 0x7e, 0x00, 0x00, 0x7e, 0x04, 0x08,
    0x10, 0x20, 0x7e, 0x00, 0x00, 0x18, 0x24, 0x42, 0x42, 0x24, 0x18, 0x00,
    0x00, 0x7e, 0x0a, 0x0a, 0x0a, 0x0a, 0x04, 0x00, 0x00, 0x18, 0x24, 0x52,
    0x52, 0x24, 0x58, 0x00, 0x00, 0x7e, 0x0a, 0x0a, 0x1a, 0x2a, 0x44, 0x00,
    0x00, 0x24, 0x4a, 0x4a, 0x52, 0x52, 0x24, 0x00, 0x00, 0x02, 0x02, 0x7e,
    0x02, 0x02, 0x00, 0x00, 0x00, 0x3e, 0x40, 0x40, 0x40, 0x40, 0x3e, 0x00,
    0x00, 0x1e, 0x20, 0x40, 0x40, 0x20, 0x1e, 0x00, 0x00, 0x7e, 0x20, 0x10,
    0x10, 0x20, 0x7e, 0x00, 0x00, 0x42, 0x24, 0x18, 0x18, 0x24, 0x42, 0x00,
    0x00, 0x06, 0x08, 0x70, 0x08, 0x06, 0x00, 0x00, 0x00, 0x42, 0x62, 0x52,
    0x4a, 0x46, 0x42, 0x00, 0x00, 0x20, 0x54, 0x54, 0x54, 0x54, 0x78, 0x00,
    0x00, 0x7e, 0x48, 0x48, 0x48, 0x48, 0x30, 0x00, 0x00, 0x38, 0x44, 0x44,
    0x44, 0x44, 0x28, 0x00, 0x00, 0x30, 0x48, 0x48, 0x48, 0x48, 0x7e, 0x00,
    0x00, 0x38, 0x54, 0x54, 0x54, 0x54, 0x18, 0x00, 0x00, 0x10, 0x10, 0x7c,
    0x12, 0x12, 0x04, 0x00, 0x00, 0x18, 0xa4, 0xa4, 0xa4, 0xa4, 0x7c, 0x00,
    0x00, 0x7e, 0x10, 0x08, 0x08, 0x08, 0x70, 0x00, 0x00, 0x00, 0x00, 0x7a,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0x80, 0x80, 0x80, 0x7a, 0x00, 0x00,
    0x00, 0x7e, 0x10, 0x10, 0x28, 0x44, 0x00, 0x00, 0x00, 0x00, 0x02, 0x7e,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x7c, 0x08, 0x04, 0x78, 0x04, 0x78, 0x00,
    0x00, 0x7c, 0x08, 0x04, 0x04, 0x7c, 0x00, 0x00, 0x00, 0x10, 0x28, 0x44,
    0x44, 0x28, 0x10, 0x00, 0x00, 0xfc, 0x24, 0x24, 0x24, 0x24, 0x18, 0x00,
    0x00, 0x18, 0x24, 0x24, 0x24, 0x24, 0xfc, 0x00, 0x00, 0x7c, 0x08, 0x04,
    0x04, 0x04, 0x08, 0x00, 0x00, 0x48, 0x54, 0x54, 0x54, 0x54, 0x24, 0x00,
    0x00, 0x04, 0x04, 0x3e, 0x44, 0x44, 0x20, 0x00, 0x00, 0x3c, 0x40, 0x40,
    0x40, 0x20, 0x7c, 0x00, 0x00, 0x0c, 0x30, 0x40, 0x40, 0x30, 0x0c, 0x00,
    0x00, 0x3c, 0x40, 0x30, 0x40, 0x20, 0x7c, 0x00, 0x00, 0x44, 0x28, 0x10,
    0x10, 0x28, 0x44, 0x00, 0x00, 0x8c, 0x90, 0x60, 0x20, 0x10, 0x0c, 0x00,
    0x00, 0x44, 0x64, 0x54, 0x54, 0x4c, 0x44, 0x00, 0x00, 0x3c, 0x62, 0x52,
    0x4a, 0x46, 0x3c, 0x00, 0x00, 0x00, 0x00, 0x44, 0x7e, 0x40, 0x00, 0x00,
    0x00, 0x44, 0x62, 0x52, 0x4a, 0x4a, 0x44, 0x00, 0x00, 0x24, 0x42, 0x4a,
    0x4a, 0x4a, 0x34, 0x00, 0x00, 0x20, 0x30, 0x28, 0x24, 0x7e, 0x20, 0x00,
    0x00, 0x20, 0x4e, 0x4a, 0x4a, 0x4a, 0x32, 0x00, 0x00, 0x30, 0x48, 0x4c,
    0x4a, 0x48, 0x30, 0x00, 0x00, 0x06, 0x02, 0x62, 0x12, 0x0a, 0x06, 0x00,
    0x00, 0x34, 0x4a, 0x4a, 0x4a, 0x4a, 0x34, 0x00, 0x00, 0x0c, 0x12, 0x52,
    0x32, 0x12, 0x0c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7e, 0x42, 0x42, 0x00,
    0x00, 0x42, 0x42, 0x7e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08,
    0x36, 0x41, 0x41, 0x00, 0x00, 0x41, 0x41, 0x36, 0x08, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x18, 0x24, 0x42, 0x42, 0x00, 0x00, 0x42, 0x42, 0x24,
    0x18, 0x00, 0x00, 0x00, 0x00, 0x10, 0x10, 0x7c, 0x10, 0x10, 0x00, 0x00,
    0x00, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x00, 0x00, 0x40, 0x20, 0x10,
    0x08, 0x04, 0x02, 0x00, 0x00, 0x44, 0x2a, 0x14, 0x28, 0x54, 0x22, 0x00,
    0x00, 0x40, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0x40, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x28, 0x68, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x28, 0x28, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02,
    0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x06, 0x00, 0x02, 0x06, 0x00,
    0x00, 0x08, 0x04, 0x02, 0x02, 0x04, 0x08, 0x00, 0x00, 0x34, 0x4a, 0x4a,
    0x54, 0x20, 0x50, 0x00, 0x00, 0x24, 0x52, 0x52, 0x32, 0x42, 0x3c, 0x00,
    0x00, 0x24, 0x7e, 0x24, 0x24, 0x7e, 0x24, 0x00, 0x00, 0x24, 0x4a, 0xff,
    0x52, 0x24, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x00, 0x00, 0x04, 0x02, 0x02,
    0x52, 0x0a, 0x04, 0x00, 0x00, 0x00, 0x0c, 0x5e, 0x0c, 0x00, 0x00, 0x00,
    0x00, 0x04, 0x02, 0x02, 0x04, 0x04, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0xff, 0xff, 0xff, 0xc7, 0xc7, 0xc7, 0xff, 0xff, 0xff, 0xff, 0xc7, 0xc7,
    0xc7, 0xc7, 0xc7, 0xc7, 0xc7, 0xc7, 0xc7, 0xc7, 0xc7, 0xc7, 0xc7, 0xc7,
    0xc7, 0xc7, 0x07, 0x07, 0x07, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0x03,
    0x03, 0x03, 0xff, 0xff, 0xff, 0xff, 0x03, 0x03, 0x03, 0xe3, 0xe3, 0xe3,
    0xe3, 0xe3, 0xe3, 0x03, 0x03, 0x03, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00,
    0x00, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xc0, 0xc0, 0xc0, 0xff, 0xff,
    0xff, 0xff, 0xc0, 0xc0, 0xc0, 0xc7, 0xc7, 0xc7, 0xc7, 0xc7, 0xc7, 0xc0,
    0xc0, 0xc0, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff,
    0x00, 0x00, 0x10, 0x2e, 0xc1, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0xff, 0xff, 0xff, 0xe3, 0xe3, 0xe3, 0xe3, 0xe3, 0xe3, 0xe3, 0xe3, 0xe3,
    0xe3, 0xe3, 0xe3, 0xe3, 0xe3, 0xe3, 0xe3, 0xe3, 0xe3, 0xe3, 0xff, 0xff,
    0xff, 0xff, 0xe0, 0xe0, 0xe0, 0xff, 0xff, 0xff, 0x00, 0x60, 0x1c, 0x12,
    0x21, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0xc7, 0x81, 0x24, 0x18, 0x18, 0x24, 0x81, 0xc3};

const struct rom_character_t rom_characters[128] = {
    // Character (0x0)
    {.source_x = 120, .source_y = 120},
    // Character (0x1)
    {.source_x = 120, .source_y = 120},
    // Character (0x2)
    {.source_x = 120, .source_y = 120},
    // Character (0x3)
    {.source_x = 120, .source_y = 120},
    // Character (0x4)
    {.source_x = 120, .source_y = 120},
    // Character (0x5)
    {.source_x = 120, .source_y = 120},
    // Character (0x6)
    {.source_x = 120, .source_y = 120},
    // Character (0x7)
    {.source_x = 120, .source_y = 120},
    // Character (0x8)
    {.source_x = 120, .source_y = 120},
    // Character (0x9)
    {.source_x = 120, .source_y = 120},
    // Character (0xa)
    {.source_x = 120, .source_y = 120},
    // Character (0xb)
    {.source_x = 120, .source_y = 120},
    // Character (0xc)
    {.source_x = 120, .source_y = 120},
    // Character (0xd)
    {.source_x = 120, .source_y = 120},
    // Character (0xe)
    {.source_x = 120, .source_y = 120},
    // Character (0xf)
    {.source_x = 120, .source_y = 120},
    // Character (0x10)
    {.source_x = 120, .source_y = 120},
    // Character (0x11)
    {.source_x = 120, .source_y = 120},
    // Character (0x12)
    {.source_x = 120, .source_y = 120},
    // Character (0x13)
    {.source_x = 120, .source_y = 120},
    // Character (0x14)
    {.source_x = 120, .source_y = 120},
    // Character (0x15)
    {.source_x = 120, .source_y = 120},
    // Character (0x16)
    {.source_x = 120, .source_y = 120},
    // Character (0x17)
    {.source_x = 120, .source_y = 120},
    // Character (0x18)
    {.source_x = 120, .source_y = 120},
    // Character (0x19)
    {.source_x = 120, .source_y = 120},
    // Character (0x1a)
    {.source_x = 120, .source_y = 120},
    // Character (0x1b)
    {.source_x = 120, .source_y = 120},
    // Character (0x1c)
    {.source_x = 120, .source_y = 120},
    // Character (0x1d)
    {.source_x = 120, .source_y = 120},
    // Character (0x1e)
    {.source_x = 120, .source_y = 120},
    // Character (0x1f)
    {.source_x = 120, .source_y = 120},
    // Character (0x20)
    {.source_x = 24, .source_y = 40},
    // Character (0x21)
    {.source_x = 48, .source_y = 40},
    // Character (0x22)
    {.source_x = 104, .source_y = 32},
    // Character (0x23)
    {.source_x = 8, .source_y = 40},
    // Character (0x24)
    {.source_x = 16, .source_y = 40},
    // Character (0x25)
    {.source_x = 56, .source_y = 32},
    // Character (0x26)
    {.source_x = 120, .source_y = 32},
    // Character (0x27)
    {.source_x = 96, .source_y = 32},
    // Character (0x28)
    {.source_x = 16, .source_y = 32},
    // Character (0x29)
    {.source_x = 24, .source_y = 32},
    // Character (0x2a)
    {.source_x = 64, .source_y = 40},
    // Character (0x2b)
    {.source_x = 32, .source_y = 32},
    // Character (0x2c)
    {.source_x = 64, .source_y = 32},
    // Character (0x2d)
    {.source_x = 40, .source_y = 32},
    // Character (0x2e)
    {.source_x = 72, .source_y = 32},
    // Character (0x2f)
    {.source_x = 48, .source_y = 32},
    // Character (0x30)
    {.source_x = 32, .source_y = 24},
    // Character (0x31)
    {.source_x = 40, .source_y = 24},
    // Character (0x32)
    {.source_x = 48, .source_y = 24},
    // Character (0x33)
    {.source_x = 56, .source_y = 24},
    // Character (0x34)
    {.source_x = 64, .source_y = 24},
    // Character (0x35)
    {.source_x = 72, .source_y = 24},
    // Character (0x36)
    {.source_x = 80, .source_y = 24},
    // Character (0x37)
    {.source_x = 88, .source_y = 24},
    // Character (0x38)
    {.source_x = 96, .source_y = 24},
    // Character (0x39)
    {.source_x = 104, .source_y = 24},
    // Character (0x3a)
    {.source_x = 88, .source_y = 32},
    // Character (0x3b)
    {.source_x = 80, .source_y = 32},
    // Character (0x3c)
    {.source_x = 120, .source_y = 120},
    // Character (0x3d)
    {.source_x = 120, .source_y = 120},
    // Character (0x3e)
    {.source_x = 120, .source_y = 120},
    // Character (0x3f)
    {.source_x = 40, .source_y = 40},
    // Character (0x40)
    {.source_x = 0, .source_y = 40},
    // Character (0x41)
    {.source_x = 0, .source_y = 0},
    // Character (0x42)
    {.source_x = 8, .source_y = 0},
    // Character (0x43)
    {.source_x = 16, .source_y = 0},
    // Character (0x44)
    {.source_x = 24, .source_y = 0},
    // Character (0x45)
    {.source_x = 32, .source_y = 0},
    // Character (0x46)
    {.source_x = 40, .source_y = 0},
    // Character (0x47)
    {.source_x = 48, .source_y = 0},
    // Character (0x48)
    {.source_x = 56, .source_y = 0},
    // Character (0x49)
    {.source_x = 64, .source_y = 0},
    // Character (0x4a)
    {.source_x = 72, .source_y = 0},
    // Character (0x4b)
    {.source_x = 80, .source_y = 0},
    // Character (0x4c)
    {.source_x = 88, .source_y = 0},
    // Character (0x4d)
    {.source_x = 96, .source_y = 0},
    // Character (0x4e)
    {.source_x = 104, .source_y = 0},
    // Character (0x4f)
    {.source_x = 112, .source_y = 0},
    // Character (0x50)
    {.source_x = 120, .source_y = 0},
    // Character (0x51)
    {.source_x = 0, .source_y = 8},
    // Character (0x52)
    {.source_x = 8, .source_y = 8},
    // Character (0x53)
    {.source_x = 16, .source_y = 8},
    // Character (0x54)
    {.source_x = 24, .source_y = 8},
    // Character (0x55)
    {.source_x = 32, .source_y = 8},
    // Character (0x56)
    {.source_x = 40, .source_y = 8},
    // Character (0x57)
    {.source_x = 48, .source_y = 8},
    // Character (0x58)
    {.source_x = 56, .source_y = 8},
    // Character (0x59)
    {.source_x = 64, .source_y = 8},
    // Character (0x5a)
    {.source_x = 72, .source_y = 8},
    // Character (0x5b)
    {.source_x = 112, .source_y = 24},
    // Character (0x5c)
    {.source_x = 32, .source_y = 40},
    // Character (0x5d)
    {.source_x = 120, .source_y = 24},
    // Character (0x5e)
    {.source_x = 112, .source_y = 32},
    // Character (0x5f)
    {.source_x = 120, .source_y = 120},
    // Character (0x60)
    {.source_x = 120, .source_y = 120},
    // Character (0x61)
    {.source_x = 80, .source_y = 8},
    // Character (0x62)
    {.source_x = 88, .source_y = 8},
    // Character (0x63)
    {.source_x = 96, .source_y = 8},
    // Character (0x64)
    {.source_x = 104, .source_y = 8},
    // Character (0x65)
    {.source_x = 112, .source_y = 8},
    // Character (0x66)
    {.source_x = 120, .source_y = 8},
    // Character (0x67)
    {.source_x = 0, .source_y = 16},
    // Character (0x68)
    {.source_x = 8, .source_y = 16},
    // Character (0x69)
    {.source_x = 16, .source_y = 16},
    // Character (0x6a)
    {.source_x = 24, .source_y = 16},
    // Character (0x6b)
    {.source_x = 32, .source_y = 16},
    // Character (0x6c)
    {.source_x = 40, .source_y = 16},
    // Character (0x6d)
    {.source_x = 48, .source_y = 16},
    // Character (0x6e)
    {.source_x = 56, .source_y = 16},
    // Character (0x6f)
    {.source_x = 64, .source_y = 16},
    // Character (0x70)
    {.source_x = 72, .source_y = 16},
    // Character (0x71)
    {.source_x = 80, .source_y = 16},
    // Character (0x72)
    {.source_x = 88, .source_y = 16},
    // Character (0x73)
    {.source_x = 96, .source_y = 16},
    // Character (0x74)
    {.source_x = 104, .source_y = 16},
    // Character (0x75)
    {.source_x = 112, .source_y = 16},
    // Character (0x76)
    {.source_x = 120, .source_y = 16},
    // Character (0x77)
    {.source_x = 0, .source_y = 24},
    // Character (0x78)
    {.source_x = 8, .source_y = 24},
    // Character (0x79)
    {.source_x = 16, .source_y = 24},
    // Character (0x7a)
    {.source_x = 24, .source_y = 24},
    // Character (0x7b)
    {.source_x = 0, .source_y = 32},
    // Character (0x7c)
    {.source_x = 120, .source_y = 120},
    // Character (0x7d)
    {.source_x = 8, .source_y = 32},
    // Character (0x7e)
    {.source_x = 56, .source_y = 40},
    // Character (0x7f)
    {.source_x = 120, .source_y = 120},
};

void rom_character_for(struct rom_character_t *const rom, char ch) {
  const struct rom_character_t *received = &rom_characters[ch & 127];
  rom->source_x = received->source_x;
  rom->source_y = received->source_y;
}

static uint8_t rom_random_index = 0;

uint8_t rom_random_8() {
  const uint8_t data = pgm_read_byte(rom_random + rom_random_index);
  rom_random_index = (rom_random_index + 1) & (ROM_RANDOM_SIZE - 1);
  return data;
}

#endif // ROM_C
