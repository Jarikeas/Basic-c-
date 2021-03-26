#include <random>
#include <iostream>
#include <chrono>
#include "Mylib.hpp"

struct coordinates
{
   size_t x,y;
};

enum GameProgress
{
    IN_PROGRESS,
    IS_ENDED,
    HUMAN_WON,
    AI_WON,
    DRAW
};

enum GameEnum
{
    EMPTY = '_',
    CROSS = 'X',
    ZERO = 'O'
};

struct GameField
{
    GameEnum** ppField = nullptr;
    const size_t sizeX = 3, sizeY = 3;
    GameEnum human;
    GameEnum ai;
    bool humanFirst;
    GameProgress progress;
};


void PrintField(GameField& rg)
{
    std::cout << "Y | ";
    
    for(size_t j = 0; j < rg.sizeX; j++)
    {
        std::cout << j + 1 << "   ";
    }
    std::cout << "X" << std::endl;
    
    for(size_t i = 0; i < rg.sizeY; i++)
    {
        std::cout << i + 1 << " | ";
            for(size_t j = 0; j < rg.sizeX; j++)
        {
            std::cout << static_cast<char>(rg.ppField[i][j]) << " | ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
    std::cout << "Human first : " << static_cast<char>(rg.human) << std::endl;
    std::cout << "AI first : " << static_cast<char>(rg.ai) << std::endl;
}

void InitGame(GameField& rg)
{
    rg.ppField = new GameEnum * [rg.sizeY];
    for (size_t i = 0; i < rg.sizeY; i++)
        rg.ppField[i] = new GameEnum[rg.sizeX];
    
    for (size_t i = 0; i < rg.sizeY; i++)
        for (size_t j = 0; j < rg.sizeX; j++)
            rg.ppField[i][j] = EMPTY;
    if (GetRandomNumber() > 50)
    {
        rg.human = CROSS;
        rg.ai = ZERO;
        rg.humanFirst = true;
    }
    else
    {
        rg.human = ZERO;
        rg.ai = CROSS;
        rg.humanFirst = false;
    }
    rg.progress = IN_PROGRESS;
}

void UnInitGame(GameField& rg)
{
    
    for (size_t i = 0; i < rg.sizeY; i++)
        delete [] rg.ppField[i];
    delete [] rg.ppField;
    rg.ppField = nullptr;
}

void Clear()
{
    system("cls");
}

coordinates GetHumanCoordinates(GameField& rg)
{
    coordinates c = {0};
    do {
        std::cout << "Enter Y: ";
        std::cin >> c.y;
        std::cout << "Enter X: ";
        std::cin >> c.x;
    } while (c.y <= 0 || c.x <= 0 || c.x > 3 || c.y > 3 || rg.ppField[c.y - 1][c.x - 1] != EMPTY);
    c.x--;
    c.y--;
    return c;
}

GameProgress IsWon(GameField rg)
{
    for (size_t y = 0; y < rg.sizeY; y++)
    {
        if (rg.ppField[y][0] == rg.ppField[y][1] && rg.ppField[y][0] == rg.ppField[y][2])
        {
            if (rg.ppField[y][0] == rg.human)
                return HUMAN_WON;
            if (rg.ppField[y][0] == rg.ai)
                return AI_WON;
        }
    }
    for (size_t x = 0; x < rg.sizeX; x++)
    {
        if (rg.ppField[0][x] == rg.ppField[1][x] && rg.ppField[0][x] == rg.ppField[2][x])
        {
            if (rg.ppField[0][x] == rg.human)
                return HUMAN_WON;
            if (rg.ppField[0][x] == rg.ai)
                return AI_WON;
        }
    }
    if (rg.ppField[0][0] == rg.ppField[1][1] && rg.ppField[0][0] == rg.ppField[2][2])
    {
        if (rg.ppField[0][0] == rg.human)
            return HUMAN_WON;
        if (rg.ppField[0][0] == rg.ai)
            return AI_WON;
    }
    if (rg.ppField[2][0] == rg.ppField[1][1] && rg.ppField[2][0] == rg.ppField[0][2])
    {
        if (rg.ppField[1][1] == rg.human)
            return HUMAN_WON;
        if (rg.ppField[1][1] == rg.ai)
            return AI_WON;
    }
    bool draw = true;
    for (size_t y = 0; y < rg.sizeY; y++)
        for (size_t x = 0; x < rg.sizeY; x++)
    if (rg.ppField[x][y] == EMPTY)
    {
        draw = false;
    }
    if (draw)
        return DRAW;
    return IN_PROGRESS;
}

coordinates GetAiCoordinates(GameField& rg)
{
    coordinates c = {0};
    
    for (size_t y = 0; y < rg.sizeX; y++)
    {
        for (size_t x = 0; x < rg.sizeX; x++)
        {
            if (rg.ppField[y][x] == EMPTY)
            {
                rg.ppField[y][x] = rg.ai;
                if (IsWon(rg) == AI_WON)
                {
                    rg.ppField[y][x] = EMPTY;
                    c = {x,y};
                    return c;
                }
                rg.ppField[y][x] = EMPTY;
            }
        }
    }
    for (size_t y = 0; y < rg.sizeX; y++)
    {
        for (size_t x = 0; x < rg.sizeX; x++)
        {
            if (rg.ppField[y][x] == EMPTY)
            {
                rg.ppField[y][x] = rg.human;
                if (IsWon(rg) == HUMAN_WON)
                {
                    rg.ppField[y][x] = EMPTY;
                    c = {x,y};
                    return c;
                }
                rg.ppField[y][x] = EMPTY;
            }
        }
    }
    if (rg.ppField[1][1] == EMPTY)
    {
        c = {1, 1};
        return c;
    }
    
    if (rg.ppField[0][0] == EMPTY) //Ugly
    {
        c = {0, 0};
        return c;
    }
    
    if (rg.ppField[0][2] == EMPTY)
    {
        c = {2, 0};
        return c;
    }
    
    if (rg.ppField[2][2] == EMPTY)
    {
        c = {2, 2};
        return c;
    }
    
    if (rg.ppField[2][0] == EMPTY)
    {
        c = {0, 2};
        return c;
    }                                   //Stenki
    
    if (rg.ppField[2][1] == EMPTY)
    {
        c = {1, 2};
        return c;
    }
    
    if (rg.ppField[1][0] == EMPTY)
    {
        c = {0, 1};
        return c;
    }
    
    if (rg.ppField[0][1] == EMPTY)
    {
        c = {1, 0};
        return c;
    }
    
    if (rg.ppField[1][2] == EMPTY)
    {
        c = {2, 1};
        return c;
    }
    return c;
}

int main()
{
    auto start = std::chrono::steady_clock::now();
    GameField game;
    Clear();
    InitGame(game);
    PrintField(game);
    size_t turn;
    turn = (game.humanFirst) ? 0 : 1;
    while (game.progress == IN_PROGRESS)
    {
        
        if (turn % 2 == 0)
        {
            coordinates c = GetHumanCoordinates(game);
            game.ppField[c.y][c.x] = game.human;
        }
        else
        {
            coordinates c = GetAiCoordinates(game);
            game.ppField[c.y][c.x] = game.ai;
        }
        Clear();
        PrintField(game);
        turn++;
        
        game.progress = IsWon(game);
    }
    
    if (game.progress == DRAW)
    {
        std::cout << "Draw" << std::endl;
    }
    else if (game.progress == AI_WON)
    {
        std::cout << "Oops, you lose, get luck next time" << std::endl;
    }
    else if (game.progress == HUMAN_WON)
    {
        std::cout << "Congratulations, you won!" << std::endl;
    }
    UnInitGame(game);
    auto end = std::chrono::steady_clock::now();
    std::chrono::duration<double> elapsed_seconds = end - start;
    std::cout << "The game lasted : " << elapsed_seconds.count() << "с\n";
}

