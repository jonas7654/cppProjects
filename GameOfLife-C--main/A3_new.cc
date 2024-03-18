#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <chrono>
#include <thread>

using Spielfeld = std::vector<std::vector<bool>>;

void printGame(const Spielfeld& game)
{
    int n = game.size();
    int m = game[0].size();

    for (int i = 0; i < n ; i++)
    {
        for (int k = 0; k < m ; k++)
        {
            
            if (game[i][k] == true)
             std::cout <<   'O';
            else
             std::cout <<   ' ';
        }
        std::cout << std::endl;
    }
}

Spielfeld readGame(const std::string& path)
{
    // Spielfeld erstellen
    Spielfeld game;
    //
    std::string readText;
    std::ifstream newGame(path);
    
    if (!newGame.is_open())
    {
        std::cout << "Error opening file: " << path << std::endl;
        return game;  // Return an empty game if file cannot be opened
    }

    while (getline(newGame,readText))
    {
        if (readText.empty())
        {
            game.clear();
            return game;
        }

        // Konvertiere die Zeile zu einem std::vector<bool>
        std::vector<bool> RowOfBools;

        // Prüfe, dass Zeichen gleiche länge und gültig sind
        for (char& c : readText)
        {
            if(c != 'O' && c != '1')
            {
                std::cout << "input not valid" << std::endl;
                game.clear();
                return game;
            }

            if (c == 'O')
                RowOfBools.push_back(true);
            else
                RowOfBools.push_back(false);
        }
        
        game.push_back(RowOfBools);
    }
    for (auto i = 0; i < game.size(); i++)
    {
        int size = game[0].size();
        if (game[i].size() != size)
        {
            std::cout << "WARNING: col sizes are not equal" << std::endl;
            game.clear();
        }
    }

    std::cout << game.size() << " rows \n" << game[0].size() << " cols" << std::endl;
    return game;
}

bool deadCondition(const Spielfeld& game , int i, int j)
{
    int rows = game.size();
    int cols = game[0].size();

    if (i < 0 || i > (rows - 1) || j < 0 || j > (cols - 1))
        return false;
    else
        return game[i][j];
}

bool updateCell(const Spielfeld& game, int i, int k)
{
    int countAlive = 0;

    for (int j = -1; j < 2; j++)
            {
                for (int l = -1; l < 2; l++)
                {
                    // Überspringe die eigene Zelle
                    if (j == 0 && l == 0)
                        continue;
                    
                    int new_n = i - j;
                    int new_m = k - l;
                    
                    countAlive += static_cast<int>(deadCondition(game, new_n, new_m));

                }
            }

            // Spielregeln
            if (countAlive == 3)
                return true;
            else if (countAlive == 2 && game[i][k] == true)
                return true;
            else
                return false;
}

void updateGame(Spielfeld& game)
{
    // — Eine tote Zelle lebt im nächsten Zeitschritt genau dann, wenn sie in diesem Zeitschritt genau drei lebendige Nachbarn hat, sonst bleibt sie tot.
    // Eine lebendige Zelle lebt im nächsten Zeitschritt genau dann, wenn sie in diesem Zeitschritt zwei oder drei lebendige Nachbarn hat, ansonsten stirbt sie.

    Spielfeld tempGame(game);
    
    int rows = game.size();
    int cols = game[0].size();

    for (int i = 0; i < rows ; i++)
    {
        for (int k = 0; k < cols ; k++)
        {
           tempGame[i][k] = updateCell(game, i, k);
        }
    }
    // Überschreibe das Spiel
    game = tempGame;
}

int main()
{
    Spielfeld game = readGame("test.txt");
    if(game.empty())
        return 0;

    std::cout << std::endl;
   
    std::cout << "game loaded: \n \n";

    printGame(game); 

    std::cout << std::endl;
    std::cout << "Do you want to start the simulation? (y/n)" << std::endl;
    
    char answer;
    std::cin >> answer;

    if(answer != 'y')
    {
        std::cout << "programm ended";
        return 0;
    }

    while(true)
    {
       std::cout << "\x1B[2J\x1B[H";
       updateGame(game);
       printGame(game);
       std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
    
    return 0;
}