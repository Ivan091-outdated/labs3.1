#ifndef COURSEWORK_FUNCTIONS_H
#define COURSEWORK_FUNCTIONS_H
#define IMAGE_SIZE 3000

using namespace std;
void loadPixels(const bitmap_image &image, size_t start, size_t end);

void deNoise(size_t start, size_t end);

void upgrade(size_t start, size_t end);

void unloadPixels(bitmap_image &image, size_t start, size_t end);

#endif //COURSEWORK_FUNCTIONS_H
