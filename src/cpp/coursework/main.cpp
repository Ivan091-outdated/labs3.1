#include <iostream>
#include <string>
#include <omp.h>
#include "bitmap_image.hpp"
#include "functions.h"

#define THREAD_COUNT 4
#define IMAGE_PIECE_SIZE 750

void nonParallel() {

    deNoise(1, IMAGE_SIZE - 1);
    mirror(0, IMAGE_SIZE);

}

void parallel() {
#pragma omp parallel for default(none)
    for (int i = 0; i < THREAD_COUNT; ++i) {
        deNoise(i * IMAGE_PIECE_SIZE, (i + 1) * IMAGE_PIECE_SIZE);
        mirror(i * IMAGE_PIECE_SIZE, (i + 1) * IMAGE_PIECE_SIZE);

    }
}

int main(int argc, char *argv[]) {
    omp_set_num_threads(THREAD_COUNT);
    const string fileName = "../imageNoised.bmp";
    bitmap_image image(fileName);
    if (!image) {
        cout << "Unable to open file" << endl;
        return 1;
    }
    loadPixels(image, 0, IMAGE_SIZE);
    double start = omp_get_wtime();

    if (argc > 1){
        cout << "parallel\n";
        parallel();
    }
    else{
        cout << "nonParallel\n";
        nonParallel();
    }

    double end = omp_get_wtime();
    cout << "time:" << (end - start) << endl;
    setPixels(image, 0, IMAGE_SIZE);
    image.save_image("../output.bmp");
    return 0;
}
