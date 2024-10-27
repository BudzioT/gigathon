# Gra w Memory
Konsolowa wersja gry w Memory, umożliwiająca zapis i wczytanie gry

## Zasady gry:
1. Po rozpoczęciu gry wybierz rozmiar mapy
2. Mapa musi mieć równą liczbę kart
3. Po rozpoczęciu wybierz dwie karty ( x y)
- Jeśli pasują, możesz wybrać karty ponownie
- Zdobywasz również punkt!
- Jeśli nie pasują, gracze się zmieniają
4. Graj, aż wszystkie karty zostaną dopasowane
5. Aby zapisać grę, wpisz znak niebędący cyfrą
podczas swojego ruchu

## Pliki posiadają krótkie komentarze, mogą one służyć jako opis najważniejszych funkcjonalności

## Kompilacja i uruchomienie na Windows

### Bez CMake

1. Otwórz terminal
2. Przejdź do katalogu z kodem źródłowym (folder gigathon/MemoryGame/src):
   ```sh
   cd ścieżka/gigathon/MemoryGame/src
   ```
3. Skompiluj kod za pomocą kompilatora g++:
   ```sh
   g++ -o MemoryGame main.cpp game.cpp utils.cpp
   ```
4. Uruchom skompilowany program:
   ```sh
   .\MemoryGame.exe
   ```

### Z CMake (Pobierz z https://cmake.org/ na Windows, lub na Linux komendą w zależności od dystrybucji)

1. Otwórz terminal
2. Przejdź do katalogu z plikiem CMakeLists.txt
   ```sh
   cd ścieżka/gigathon/MemoryGame
   ```
3. Utwórz katalog do budowania:
   ```sh
   mkdir build
   cd build
   ```
4. Uruchom CMake, aby wygenerować pliki projektu:
   ```sh
   cmake ..
   ```
5. Skompiluj projekt:
   ```sh
   cmake --build .
   ```
6. Uruchom skompilowany program:
   ```sh
   .\MemoryGame.exe
   ```
