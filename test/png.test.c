#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#define PNG_SIGNATURE_SIZE 8

const uint8_t png_signature[PNG_SIGNATURE_SIZE] = {
    0x89, 0x50, 0x4E, 0x47, 0x0D, 0x0A, 0x1A, 0x0A
};

uint32_t crc32(uint8_t *buf, size_t len) {
    uint32_t crc_table[256];
    uint32_t crc;

    for (uint32_t i = 0; i < 256; i++) {
        crc = i;
        for (uint32_t j = 0; j < 8; j++) {
            if (crc & 1)
                crc = 0xedb88320 ^ (crc >> 1);
            else
                crc = crc >> 1;
        }
        crc_table[i] = crc;
    }

    crc = 0xffffffff;
    for (size_t i = 0; i < len; i++) {
        uint8_t byte = buf[i];
        crc = crc_table[(crc ^ byte) & 0xff] ^ (crc >> 8);
    }
    return crc ^ 0xffffffff;
}

void write_uint32(FILE *fp, uint32_t value) {
    uint8_t bytes[4];
    bytes[0] = (value >> 24) & 0xFF;
    bytes[1] = (value >> 16) & 0xFF;
    bytes[2] = (value >> 8) & 0xFF;
    bytes[3] = value & 0xFF;
    fwrite(bytes, 1, 4, fp);
}

void write_chunk(FILE *fp, const char *type, uint8_t *data, size_t length) {
    write_uint32(fp, length);
    fwrite(type, 1, 4, fp);
    if (length > 0) {
        fwrite(data, 1, length, fp);
    }
    uint32_t crc = crc32((uint8_t *)type, 4);
    if (length > 0) {
        crc = crc32(data, length);
        crc = crc32((uint8_t *)type, 4) ^ crc32(data, length);
    } else {
        crc = crc32((uint8_t *)type, 4);
    }
    write_uint32(fp, crc);
}

void write_png(const char *filename, uint8_t *image_data, int width, int height) {
    FILE *fp = fopen(filename, "wb");
    if (!fp) {
        fprintf(stderr, "Could not open file for writing\n");
        exit(EXIT_FAILURE);
    }

    fwrite(png_signature, 1, PNG_SIGNATURE_SIZE, fp);

    // IHDR chunk
    uint8_t ihdr_data[13];
    ihdr_data[0] = (width >> 24) & 0xFF;
    ihdr_data[1] = (width >> 16) & 0xFF;
    ihdr_data[2] = (width >> 8) & 0xFF;
    ihdr_data[3] = width & 0xFF;
    ihdr_data[4] = (height >> 24) & 0xFF;
    ihdr_data[5] = (height >> 16) & 0xFF;
    ihdr_data[6] = (height >> 8) & 0xFF;
    ihdr_data[7] = height & 0xFF;
    ihdr_data[8] = 8;  // Bit depth
    ihdr_data[9] = 2;  // Color type: Truecolor
    ihdr_data[10] = 0; // Compression method
    ihdr_data[11] = 0; // Filter method
    ihdr_data[12] = 0; // Interlace method

    write_chunk(fp, "IHDR", ihdr_data, 13);

    // Convert raw image data to PNG scanlines
    uint8_t *scanlines = (uint8_t *)malloc(height * (width * 3 + 1));
    for (int y = 0; y < height; ++y) {
        scanlines[y * (width * 3 + 1)] = 0; // Filter type 0
        memcpy(&scanlines[y * (width * 3 + 1) + 1], &image_data[y * width * 3], width * 3);
    }

    // Instead of compressing, directly write the scanlines as is
    write_chunk(fp, "IDAT", scanlines, height * (width * 3 + 1));

    // IEND chunk
    write_chunk(fp, "IEND", NULL, 0);

    free(scanlines);
    fclose(fp);
}

int main() {
    const int width = 3;
    const int height = 3;
    uint8_t image_data[3][3][3] = {
        {{255, 0, 0}, {0, 255, 0}, {0, 0, 255}},
        {{255, 255, 0}, {0, 255, 255}, {255, 0, 255}},
        {{0, 0, 0}, {128, 128, 128}, {255, 255, 255}}
    };

    uint8_t *flat_image_data = (uint8_t *)malloc(width * height * 3);
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            for (int c = 0; c < 3; ++c) {
                flat_image_data[(y * width + x) * 3 + c] = image_data[y][x][c];
            }
        }
    }

    write_png("output.png", flat_image_data, width, height);

    free(flat_image_data);
    return 0;
}
