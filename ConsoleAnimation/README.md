# Animacja Konsolowa
Animacja w konsoli, posiadająca 12 barw i dowolną liczbę klatek (na przykładzie 10) oraz mini muzykę.
Użyłem OpenCV, jednak nie jest to biblioteka do wyświetlania grafiki, a służy mi do jej odczytu z pliku, więc tym samym program nadal jest konsolowy.

## Przykład
Przykład można znaleźć jako wideo, załączyłem go ze względu na skomplikowane uruchomienie, żeby łatwiej zobaczyć efekty. WSL nie pozwala na wyświetlanie dużej ilości emotek,<br>
więc trochę znaków nie jest widocznych, ale animacja nadal wygląda w porządku, może lepiej wyglądać na innych systemach.

## Pliki posiadają krótkie komentarze, mogą one służyć jako opis najważniejszych funkcjonalności

## Użytkownik powinien odrazu być w stanie zauważyć animacje po uruchomieniu programu

## Kompilacja i uruchomienie 
### Na Windows (UWAGA ZALECAM UŻYCIE Linux, kompilacja na Windows używa i wymaga instalacji WSL, czyli virtualnej maszyny do Linuxa. To jest pierwszy raz<br> kiedy uruchamiam C++ na Windowsie, a on nie ma wygody instalowania i odnajdowywania bibliotek takiej jak Linux)
1. Otwórz terminal lub PowerShell
2. Zainstaluj WSL
   ```sh
   wsl --install
   ```
   Jeżeli WSL nie zadziała, wejdź w Funckje systemu Windows -> Włącz lub wyłącz funkcje systemu Windows i uruchom "Hyper-V" jeżeli istnieje, wyłącz "Platforma Maszyny Wirtualnej",<br>
   zresetuj komputer po aplikowaniu zmian i włącz znowu "Platforma Maszyny Wirtualnej" - jest to znany błąd, a to jest jego rozwiązanie.
### Wspólne kroki dla windows i Linux
4. Zainstaluj essentials, CMake
   ```sh
   sudo apt update
   sudo apt install build-essential
   sudo apt install cmake
   sudo apt install git
   ```
5. Zainstaluj OpenCV i zweryfikuj bibliotekę jak chcesz
   ```sh
   sudo apt install libopencv-dev
   pkg-config --modversion opencv4
   ```
6. Wybierz w swoim środowisku WSL jako sposób kompilacji i skompiluj, lub przenieś się do miejsca z projektem i zbuduj go
   ```sh
   cd ścieżka/gigathon/ConsoleAnimation
   mkdir build
   cd build
   cmake ..
   cmake --build .
   ```
7. Przenieś folder Images do jednego poziomu niżej niż twój plik .exe
8. Uruchom plik exe wygenerowany przez exe jeżeli nie korzystałeś z środowiska
