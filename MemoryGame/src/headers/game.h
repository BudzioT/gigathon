#ifndef GAME_H
#define GAME_H

#include <string>
#include <chrono>
#include "utils.h"


/* Class that manages the entire game mechanics */
class Game {
public:
    Game();
    void displayMenu();
    void rules();
    void run();

    [[nodiscard]] bool end() const;

private:
    void reset();
    void setSize();
    void setMap();

    void loadState();
    void saveState();

private:
    int m_width, m_height;
    bool m_end;
    std::string m_map;
    std::string m_currentMap;

    int m_scores[2];
    bool m_turn;
    bool m_secondTurn;
    int m_changedPos;

    std::chrono::milliseconds m_sleepTime;
};

#endif //GAME_H
