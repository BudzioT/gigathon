#include <iostream>
#include <vector>
#include <thread>
#include <chrono>

#include "utils.h"


int main() {
    std::string imageDir = "../images";
    std::vector<std::string> files = loadImageFiles(imageDir);

    // Safeguard against zero files
    if (files.empty()) {
        std::cerr << "No images found" << std::endl;
        return -1;
    }

    while (true) {
        for (const auto& file: files) {
            drawImageFile(file);

            playMusic();
            // Wait for 3 seconds before the next frame
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }
    }

    return 0;
}


