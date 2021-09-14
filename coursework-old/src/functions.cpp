#include "bitmap_image.hpp"
#include "functions.h"
static u_char pixels[IMAGE_SIZE][IMAGE_SIZE];
static u_char bufPixels[IMAGE_SIZE][IMAGE_SIZE];

typedef bool (*func)(u_char pointValue);

void loadPixels(const bitmap_image &image, size_t start, size_t end) {
    for (size_t i = start; i < end; i++) {
        for (size_t j = 0; j < IMAGE_SIZE; j++) {
            pixels[i][j] = image.get_pixel(i, j).green;
        }
    }
}

void deNoise(size_t start, size_t end) {
    if (start == 0) {
        start++;
    }
    if (end == IMAGE_SIZE) {
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
            bufPixels[i][j] = accumulator >> 3;
        }
    }
    for (size_t i = start; i < end; i++) {
        memcpy(pixels[i], bufPixels[i], IMAGE_SIZE);
    }
}

bool hasAround(size_t i, size_t j, func f) {
    return f(pixels[i - 1][j - 1]) ||
           f(pixels[i][j - 1]) ||
           f(pixels[i + 1][j - 1]) ||
           f(pixels[i - 1][j]) ||
           f(pixels[i + 1][j]) ||
           f(pixels[i - 1][j + 1]) ||
           f(pixels[i][j + 1]) ||
           f(pixels[i + 1][j + 1]);
}

void increase(size_t start, size_t end, func f, u_char value) {
    for (size_t i = start; i < end; i++) {
        for (size_t j = 0; j < IMAGE_SIZE; j++) {
            if (j != 0 && j != IMAGE_SIZE - 1 && hasAround(i, j, f)) {
                bufPixels[i][j] = value;
            } else {
                bufPixels[i][j] = pixels[i][j];
            }
        }
    }
    for (size_t i = start; i < end; i++) {
        memcpy(pixels[i], bufPixels[i], IMAGE_SIZE);
    }
}

void upgrade(size_t start, size_t end) {
    func increaseFunc = [](u_char value) { return value > 245; };
    func reduceFunc = [](u_char value) { return value < 15; };
    increase(start, end, reduceFunc, 0);
    increase(start, end, reduceFunc, 0);
    increase(start, end, reduceFunc, 0);
    increase(start, end, increaseFunc, 255);
}

void unloadPixels(bitmap_image &image, size_t start, size_t end) {
    for (size_t i = start; i < end; i++) {
        for (size_t j = 0; j < IMAGE_SIZE; j++) {
            u_char pixel = pixels[i][j];
            if (i == 0 || j == 0 || i == IMAGE_SIZE - 1 || j == IMAGE_SIZE - 1)
                pixel = 0;
            image.set_pixel(i, j, pixel, pixel, pixel);
        }
    }
}

