#include "headers/game.h"

#include <iostream>
#include <string>
#include <fstream>
#include <thread>
#include <map>
#include <random>
#include <algorithm>


Game::Game() : m_width(0), m_height(0), m_end(false), m_scores{0, 0}, m_turn(false),
m_sleepTime(200), m_secondTurn(false), m_changedPos(0)
{}

// End the game
bool Game::end() const {
    return m_end;
}

// Reset all stats
void Game::reset() {
    m_width = m_height = 0;
    m_turn = false;
    m_map = "";
    m_currentMap = "";
    m_scores[0] = m_scores[1] = 0;
    m_secondTurn = false;
    m_changedPos = 0;
}

// Display the menu and go to correct part of the game flow
void Game::displayMenu() {
    std::string choice;
    while (!m_end) {
        clearConsole();
        // Sleep to execute clear console command before the next line
        std::this_thread::sleep_for(m_sleepTime);
        std::cout << "\n=================================================\n"
                     "====-----------------------------------------====\n"
                     "====-------------- Memory Game --------------====\n"
                     "====-----------------------------------------====\n"
                     "=================================================\n\n";

        std::cout << "-------------------------------------------------\n"
                     "--------------------- Menu ----------------------\n"
                     "-------------------- 1. PLAY --------------------\n"
                     "------------------- 2. RULES -------------------\n"
                     "-------------------- 3. QUIT --------------------\n"
                     "----------------- 4. LOAD GAME -----------------\n"
                     "-------------------------------------------------\n";
        std::cout << "Choose an option number: > ";
        std::cin >> choice;

        switch (choice[0]) {
            case ' ':
                std::cout << "Empty choice, please try again" << std::endl;
                std::this_thread::sleep_for(std::chrono::milliseconds(2000));
                break;
            case '1':
                std::cout << "Have a fun time playing!" << std::endl;
                std::this_thread::sleep_for(std::chrono::milliseconds(1000));
                reset();
                setSize();
                run();
                break;
            case '2':
                rules();
                break;
            case '3':
                std::cout << "Thanks for playing~!" << std::endl;
                m_end = true;
                break;
            case '4':
                std::cout << "Loading...\n" << std::endl;
                loadState();
                run();
                break;
            default:
                std::cout << "Unknown option, please try again" << std::endl;
                std::this_thread::sleep_for(std::chrono::milliseconds(2000));
                break;
        }
    }
}

// Set the size of a map and proceed further
void Game::setSize() {
    clearConsole();
    std::this_thread::sleep_for(m_sleepTime);

    std::string x, y;
    while (x.empty() && y.empty()) {
        std::cout << "\nSize of the map (x y):\n"
                     "> ";
        std::cin >> x >> y;

        // Make sure input is a number
        try {
            m_width = std::stoi(x);
            m_height = std::stoi(y);
        }
        catch (std::invalid_argument& err) {
            std::cout << "Input size isn't a number";
            m_width = m_height = 0;
            x = y = "";
            std::this_thread::sleep_for(std::chrono::milliseconds(2000));
            continue;
        }
        if (m_width == 0 || m_height == 0) {
            std::cout << "Size can't be equal to 0!";
            m_width = m_height = 0;
            x = y = "";
            std::this_thread::sleep_for(std::chrono::milliseconds(2000));
            continue;
        }

        if (m_width * m_height % 2 != 0) {
            std::cout <<"--- Please set even amount of cards ---" << std::endl;
            x = y = "";
            std::this_thread::sleep_for(std::chrono::milliseconds(2000));
            continue;
        }
    }

    setMap();
}

// Just show the rules
void Game::rules() {
    clearConsole();
    std::this_thread::sleep_for(m_sleepTime);
    std::cin.clear();

    std::cout << "\n=================================================\n"
                 "==---------------------------------------------==\n"
                 "==------------------- RULES -------------------==\n"
                 "==---------------------------------------------==\n"
                 "=================================================\n"
                 "Welcome to the Memory Game!\n"
                 "1. Once you start the game, choose size of the map\n"
                 "2. Map must have even amount of cards\n"
                 "3. Once you start, choose two cards (x y)\n"
                 "- If they match, you can choose cards again\n"
                 "- You also earn a point!\n"
                 "- If they don't match, player changes\n"
                 "4. Play until all cards are matched\n"
                 "5. To save the game, write non-numeric character\n"
                 "  during your move\n"
                 "Good luck!\n"
                 << std::endl;
    std::cout << "Submit any key to proceed...";
    std::string temp;
    std::cin >> temp;
}

// Load and resume the game
void Game::loadState() {
    std::ifstream file("data.txt");
    if (file.bad() || file.fail()) {
        std::cout << "It wasn't possible to open that file! Running new game...";
        std::this_thread::sleep_for(std::chrono::milliseconds(2000));
        setSize();
        run();
    }

    // Info: width, height, map, turn, firstScore, secondScore, secondTurn, changedPos, currentMap
    std::string info[8];
    for (auto & str : info) {
        std::getline(file, str);
        if (file.eof()) {
            std::cout << "File is in a wrong format! Running new game...";
            std::this_thread::sleep_for(std::chrono::milliseconds(2000));
            setSize();
            run();
        }
    }

    // Set the current map
    std::string line;
    while (std::getline(file, line)) {
        m_currentMap.append(line);
        m_currentMap.push_back('\n');
    }
    // Set all not formatted variables
    m_width = std::stoi(info[0]);
    m_height = std::stoi(info[1]);
    m_map = info[2];
    m_turn = std::stoi(info[3]);
    m_scores[0] = std::stoi(info[4]);
    m_scores[1] = std::stoi(info[5]);
    m_secondTurn = std::stoi(info[6]);
    m_changedPos = std::stoi(info[7]);

    std::cout << "Load finished!";
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
}

void Game::saveState() {
    std::ofstream file("data.txt");
    file << std::to_string(m_width);
    file << "\n";
    file << std::to_string(m_height);
    file << "\n";
    file << m_map;
    file << "\n";
    file << std::to_string(m_turn);
    file << "\n";
    file << std::to_string(m_scores[0]);
    file << "\n";
    file << std::to_string(m_scores[1]);
    file << "\n";
    file << std::to_string(m_secondTurn);
    file << "\n";
    file << std::to_string(m_changedPos);
    file << "\n";
    file << m_currentMap;
}

// Set proper map based on size
void Game::setMap() {
    // Reserve enough place for the entire map + style of it
    m_currentMap.reserve(m_width * (m_height + 9));
    m_map.reserve(m_width * m_height);

    // Build the map with size: height x width
    for (int i = 0; i < m_height; i++) {
        m_currentMap.append("        ");
        for (int j = 0; j < m_width - 1; j++) {
            m_currentMap.append("[ ] ");
        }
        m_currentMap.append("[ ]\n");
    }

    // Create a list of characters, each appearing exactly twice
    std::vector<char> chars;
    for (int i = 0; i < (m_width * m_height) / 2; i++) {
        chars.push_back(char('!' + i));
        chars.push_back(char('!' + i));
    }

    // Shuffle the characters randomly
    std::random_device randomDevice;
    std::mt19937 gen(randomDevice());
    std::shuffle(chars.begin(), chars.end(), gen);

    // Generate the final map
    for (char ch: chars) {
        m_map.push_back(ch);
    }
}

// Run the game
void Game::run() {
    // Max score is basically the sum of both players scores at the end of game
    int max_score = (m_width * m_height) / 2;

    while (m_scores[0] + m_scores[1] < max_score) {
        clearConsole();
        std::this_thread::sleep_for(m_sleepTime);

        std::cout << "\n===========================================================\n"
                     "==----------------- Try to match a pair -----------------==\n"
                     "===========================================================\n"
                     "------------------------- Scores -------------------------\n"
                     "\tP1: " << m_scores[0] << "\tP2: " << m_scores[1] << std::endl;
        std::cout << m_currentMap << std::endl;
        std::cout << "Your turn Player " + std::to_string(m_turn + 1) + ": > ";

        int posX, posY;
        try {
            std::cin >> posX >> posY;
            if (std::cin.fail())
                throw std::invalid_argument("Invalid input");
        }
        catch (const std::invalid_argument& err) {
            std::cout << "Didn't receive a number, saving the game..." << std::endl;
            std::this_thread::sleep_for(std::chrono::milliseconds(1500));
            saveState();
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }

        // Safeguard against wrong position
        if ((posX < 0 || posX > m_width) || (posY < 0 || posY > m_height)) {
            std::cout << "Wrong position!";
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
            continue;
        }

        int strPos = nthOccurrence(m_currentMap, "[", posY * m_width + posX + 1) + 1;
        // Check if position is alright and if it isn't already taken
        if (strPos == -1) {
            std::cout << "Couldn't find given position!";
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
            continue;
        }
        if (m_currentMap[strPos] != ' ') {
            std::cout << "This position is already occupied!";
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
            continue;
        }

        m_currentMap[strPos] = m_map[posY * m_height + posX];
        // If it wasn't second turn, just let the same player continue
        if (!m_secondTurn) {
            m_changedPos = strPos;
            m_secondTurn = true;
        }
        // Check if player matched correctly
        else {
            // Player guess the cards
            if (m_currentMap[m_changedPos] == m_currentMap[strPos]) {
                ++m_scores[m_turn];
                m_changedPos = 0;
                m_secondTurn = false;

                if (m_scores[0] + m_scores[1] == max_score)
                    break;
                std::cout << "\n\nGood guess, you get a point!\nYou can guess again!";
                std::this_thread::sleep_for(std::chrono::milliseconds(3000));
            }
            // Player didn't match the cards
            else {
                m_currentMap[strPos] = m_map[posY * m_height + posX];
                clearConsole();
                std::this_thread::sleep_for(m_sleepTime);
                std::cout << m_currentMap << std::endl;

                std::cout << "\n\nWrong guess, time for the other player...";
                std::this_thread::sleep_for(std::chrono::milliseconds(3000));

                m_currentMap[m_changedPos] = ' ';
                m_currentMap[strPos] = ' ';
                m_changedPos = 0;
                m_secondTurn = false;
                m_turn = !m_turn;
            }
        }
    }

    if (m_scores[0] > m_scores[1])
        std::cout << "\n\tCongratulations! Player 1 has won!\a";
    else if (m_scores[1] > m_scores[0])
        std::cout << "\n\tCongratulations! Player 2 has won!\a";
    else
        std::cout << "\n\tGood game! It's a tie!\a";
    reset();
    std::this_thread::sleep_for(std::chrono::milliseconds(3000));
}