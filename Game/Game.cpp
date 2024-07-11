#include <iostream>
#include <conio.h>
#include <windows.h>

bool gameOver{false};
int width{-1}, height{-1};
int foodX, foodY;
int score;
std::string username{""};

enum edirection
{
    UP,
    DOWN,
    LEFT,
    RIGHT
};
edirection dir{RIGHT};

constexpr int snekMaxSize = 100;
struct
{
    int x[snekMaxSize];
    int y[snekMaxSize];
    int len;
} snek;

std::string getLine(std::string messege)
{
    std::string line;
    std::cout << messege << ": ";
    std::getline(std::cin >> std::ws, line);

    return line;
}

int getDim(std::string messege)
{
    std::cout << messege << ": ";
    int dim;
    std::cin >> dim;
    if (dim < 10 and dim > 40)
    {
        std::cout << "Dimension is not alowed, try values from 10 to 40.\n";
        getDim(messege);
    }
    return dim;
}

int getfoodDim(int dimType)
{
    int dim;
    dim = std::rand() % (dimType);
    if (dim < 1)
        dim = +2;
    else if (dim > dimType - 1)
        dim -= 2;

    return dim;
}

void init()
{
    if (width == -1 or height == -1)
    {
        height = getDim("Set height of the board");
        width = height * 2;
    }
    username = getLine("You name is");

    snek.x[0] = width / 2;
    snek.y[0] = height / 2;
    snek.len = 1;

    foodX = getfoodDim(width);
    foodY = getfoodDim(height);
    score = 0;
}

void drawBoard()
{
    std::system("cls");

    for (int w{0}; w < width + 2; w++)
    {
        std::cout << "_";
    }
    std::cout << "\n";

    for (int h{1}; h < height; h++)
    {
        for (int w{0}; w <= width; w++)
        {
            if (w == 0 or w == width)
                std::cout << "|";
            else if (w == snek.x[0] and h == snek.y[0])
                std::cout << "O";
            else if (w == foodX and h == foodY)
                std::cout << "#";
            else
            {
                bool isTail{false};
                for (int t{1}; t < snek.len; t++)
                {
                    if (snek.x[t] == w and snek.y[t] == h)
                    {
                        std::cout << "o";
                        isTail = true;
                    }
                }
                if (!isTail)
                    std::cout << " ";
            }
        }
        std::cout << "\n";
    }

    for (int w{0}; w < width + 2; w++)
    {
        std::cout << "-";
    }

    std::cout << "n"
              << username << "'s score: " << score << "\n";
}

void input()
{
    if (_kbhit())
    {
        char key = _getch();
        switch (key)
        {
        case 'w':
        case 'W':
            if (dir != DOWN)
            {
                dir = UP;
            }
            break;
        case 's':
        case 'S':
            if (dir != UP)
            {
                dir = DOWN;
            }
            break;
        case 'a':
        case 'A':
            if (dir != RIGHT)
            {
                dir = LEFT;
            }
            break;
        case 'd':
        case 'D':
            if (dir != LEFT)
            {
                dir = RIGHT;
            }
            break;
        default:
            break;
        }
    }
}

void updateSnek()
{
    for (int t{snek.len}; t > 0; t--)
    {
        snek.x[t] = snek.x[t - 1];
        snek.y[t] = snek.y[t - 1];
    }

    switch (dir)
    {
    case UP:
        snek.y[0]--;
        break;
    case DOWN:
        snek.y[0]++;
        break;
    case LEFT:
        snek.x[0]--;
        break;
    case RIGHT:
        snek.x[0]++;
        break;

    default:
        break;
    }

    if (snek.x[0] == 0 or snek.x[0] == width or snek.y[0] == 0 or snek.y[0] == height)
        gameOver = true;

    for (int t{1}; t < snek.len; t++)
    {
        if (snek.x[0] == snek.x[t] and snek.y[0] == snek.y[t])
            gameOver = true;
    }

    if (snek.x[0] == foodX and snek.y[0] == foodY)
    {
        score += 10;
        foodX = getfoodDim(width);
        foodY = getfoodDim(height);

        snek.len++;
        if (snek.len == 100)
            gameOver = true;
    }
}

void gameOverMessege()
{
    std::cout << "\n\n--------Game over!--------\n";
    std::cout << " Your final score " << username << ": " << score;
}

int main()
{

    init();
    drawBoard();
    while (!gameOver)
    {
        drawBoard();
        input();
        updateSnek();
        Sleep(150);
    }

    gameOverMessege();
    return 0;
}
