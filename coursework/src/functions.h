#ifndef COURSEWORK_FUNCTIONS_H
#define COURSEWORK_FUNCTIONS_H
#define IMAGE_SIZE 3000

using namespace std;
static u_char pixels[IMAGE_SIZE][IMAGE_SIZE];

void loadPixels(const bitmap_image &image, size_t start, size_t end);

void deNoise(size_t start, size_t end);

void mirror(size_t start, size_t end);

void setPixels(bitmap_image &image, size_t start, size_t end);

#endif //COURSEWORK_FUNCTIONS_H
