#include "utils.h"

#include <iostream>
#include <vector>
#include <filesystem>
#include <thread>
#include <chrono>
#ifdef _WIN32
    #include <windows.h>
#else
    #include <unistd.h>
#endif


// Load files which are images from directory to a vector
std::vector<std::string> loadImageFiles(const std::string& dir) {
    std::vector<std::string> files;
    // Go through each file
    for (const auto& entry: std::filesystem::directory_iterator(dir)) {
        // If it isn't a directory, proceed further
        if (entry.is_regular_file()) {
            std::string path = entry.path().string();
            // Check for an image
            if (path.ends_with(".png") || path.ends_with(".jpg") || path.ends_with(".jpeg")) {
                files.push_back(path);
            }
        }
    }
    return files;
}

// Get emoji from a color
std::string getEmojiFromColor(const cv::Vec3b& color) {
    // Find the emoji, if it doesn't exist return "space" character
    auto it = colorToEmoji.find(color);
    if (it != colorToEmoji.end())
        return it->second;
    else
        return " ";
}

// Compare pixels by blue, then green and finally red
bool Vec3bCompare::operator()(const cv::Vec3b &lhs, const cv::Vec3b &rhs) const {
    return std::tie(lhs[0], lhs[1], lhs[2]) < std::tie(rhs[0], rhs[1], rhs[2]);
}

// Show image in the terminal from a file
void drawImageFile(const std::string& file) {
    // Load the image, make sure it's not empty
    cv::Mat img = cv::imread(file, cv::IMREAD_COLOR);
    if (img.empty()) {
        std::cerr << "Could not open or find the image: " << file << std::endl;
        return;
    }

    // Clear the console and draw the image with emojis
    clearConsole();
    draw(img);
}

// Draw the given image onto console
void draw(cv::Mat img) {
    for (int y = 0; y < img.rows; y++) {
        for (int x = 0; x < img.cols; x++) {
            // Get color at current coordinates, change it to emoji and display it
            cv::Vec3b color = img.at<cv::Vec3b>(y, x);
            std::string emoji = getEmojiFromColor(color);
            std::cout << emoji;
        }
        std::cout << std::endl;
    }
}

// Play some music
void playMusic() {
    playBeep(440, 450);
    std::this_thread::sleep_for(std::chrono::milliseconds(50));
    playBeep(480, 450);
    std::this_thread::sleep_for(std::chrono::milliseconds(50));
    playBeep(520, 450);
    std::this_thread::sleep_for(std::chrono::milliseconds(50));
    playBeep(560, 450);
    std::this_thread::sleep_for(std::chrono::milliseconds(50));
    playBeep(650, 450);
}


// Clear the console considering the OS
void clearConsole() {
#if defined _WIN32
    system("cls");
#elif defined(__LINUX__) || defined(__gnu_linux__) || defined(__linux__) || defined(__APPLE__)
    system("\\033[2J\\033[1;1H");
#endif
}

// Play beep sound on both linux and windows
void playBeep(int frequency, int duration) {
    // Use Beep function on windows
#ifdef _WIN32
    Beep(frequency, duration);

    // Use simple \a on linux
#else
    for (int i = 0; i < duration / 200; ++i) {
        printf("\a");
        // Make sure that sound is flushed right after playing the sound
        fflush(stdout);
        usleep(200 * 1000);
    }
#endif
}