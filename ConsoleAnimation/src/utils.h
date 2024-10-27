#ifndef UTILS_H
#define UTILS_H

#include <map>
#include <opencv4/opencv2/opencv.hpp>


// Data of a single pixel
struct PixelData {
    int x, y;
    cv::Vec3b color;
};

// Comparison structure for Vec3b
struct Vec3bCompare {
    bool operator()(const cv::Vec3b& lhs, const cv::Vec3b& rhs) const;
};

// Map of colors that has corresponding emojis
const static std::map<cv::Vec3b, std::string, Vec3bCompare> colorToEmoji = {
        {{255, 255, 255}, "⬜"},
        {{0, 0, 0}, "⬛"},
        {{15, 0, 15}, "⬛"},
        {{57, 59, 255}, "🟦"},
        {{30, 101, 201}, "🔵"},
        {{0, 230, 134}, "🟢"},
        {{172, 58, 255}, "🟪"},
        {{183, 10, 148}, "🟣"},
        {{255, 67, 235}, "🌸"},
        {{255, 97, 249}, "💮"},
        {{58, 183, 10}, "🟩"},
        {{82, 216, 255}, "🌐"},
        {{91, 95, 255}, "🔮"}
};


std::vector<std::string> loadImageFiles(const std::string& dir);
void drawImageFile(const std::string& file);
void draw(cv::Mat img);
void clearConsole();
void playBeep(int frequency, int duration);
void playMusic();

#endif //UTILS_H
