#include "bitmap_image.hpp"
#include "functions.h"

void loadPixels(const bitmap_image &image, size_t start, size_t end) {
    for (size_t i = start; i < end; i++) {
        for (size_t j = 0; j < IMAGE_SIZE; j++) {
            pixels[i][j] = image.get_pixel(i, j).green;
        }
    }
}

void deNoise(size_t start, size_t end) {
    if (start == 0){
        start++;
    }
    if (end == IMAGE_SIZE){
        end--;
    }

    for (size_t i = start; i < end; i++) {
        for (size_t j = 1; j < IMAGE_SIZE - 1; j++) {
            uint accumulator = 0;
            accumulator += pixels[i - 1][j - 1];
            accumulator += pixels[i][j - 1];
            accumulator += pixels[i + 1][j - 1];
            accumulator += pixels[i - 1][j];
            accumulator += pixels[i + 1][j];
            accumulator += pixels[i - 1][j + 1];
            accumulator += pixels[i][j + 1];
            accumulator += pixels[i + 1][j + 1];
            pixels[i][j] = accumulator >> 3;
        }
    }
}

void mirror(size_t start, size_t end) {
    for (size_t i = start; i < end; i++) {
        for (size_t j2 = 0, j1 = IMAGE_SIZE - 1; j2 < IMAGE_SIZE / 2; j2++, j1--) {
            u_char item = pixels[j2][i];
            pixels[j2][i] = pixels[j1][i];
            pixels[j1][i] = item;
        }
    }
}

void setPixels(bitmap_image &image, size_t start, size_t end) {
    for (size_t i = start; i < end; i++) {
        for (size_t j = 0; j < IMAGE_SIZE; j++) {
            u_char pixel = pixels[i][j];
            image.set_pixel(i, j, pixel, pixel, pixel);
        }
    }
}

