#include <iostream>
#include<ctime>
#include<Windows.h>//окрашивание и работа с координатами
#include<conio.h>//configurate input output
using namespace std;
int main()
{
    system("title Maze"); // смена текста в заголовке консольлного окна

    // дескриптор (идентификатор), уникальный номер окна консоли
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);

    // скрываем мигающий курсор в консоли
    CONSOLE_CURSOR_INFO info;
    info.bVisible = false;
    info.dwSize = 100; // 1...100
    SetConsoleCursorInfo(h, &info);

    const int height = 25; // высота
    const int width = 80; // ширина
    int maze[height][width] = {};//заготовка для лабиринта ввиде двумерноо массива заполненного 0

    // enumeration - перечисление
    // набор целочисленных констант
    // читаемость кода существенно повышается
    enum Directions { LEFT = 75, RIGHT = 77, DOWN = 80, UP = 72 };
    enum Colors { RED = 12, BLACK = 0, GREEN = 10, YELLOW = 14, PINK = 13, WHITE = 7 };
    enum Objects { HALL = 0, WALL = 1, COIN = 2, ENEMY = 3, HEAL = 4 };

    srand(time(0));

    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {

            maze[y][x] = rand() % 5;
            // установка стен по бокам (делаем рамки)
            if (x == 0 || x == width - 1 || y == 0 || y == height - 1)
            {
                maze[y][x] = WALL;


            }
            //определение точки входа и выхода из лабиринта
            if (x == 0 && y == 2 || x == width - 1 && y == height - 3 || x == width - 2 && y == height - 3 || x == 1 && y == 2 || x == 2 && y == 2)
            {
                maze[y][x] = HALL;
            }
            if (maze[y][x] == ENEMY)
            {
                int r;
                r = rand() % 10;
                if (r != 0)
                {
                    maze[y][x] = HALL;
                }
            }
            else if (maze[y][x] == HEAL)
            {
                int j;
                j = rand() % 20;
                if (j != 0)
                {
                    maze[y][x] = HALL;
                }
            }

            if (maze[y][x] == HALL)
            {
                SetConsoleTextAttribute(h, BLACK);//чёрные
                cout << " "; // коридор
            }
            else if (maze[y][x] == WALL)
            {
                SetConsoleTextAttribute(h, WHITE);
                cout << (char)178;//стена                   
            }
            else if (maze[y][x] == COIN)
            {
                SetConsoleTextAttribute(h, YELLOW);//ярко-жёлтый
                cout << ".";//монетка
            }
            else if (maze[y][x] == ENEMY)
            {
                SetConsoleTextAttribute(h, RED);//ярко-красный
                cout << (char)1;//враг
            }
            else if (maze[y][x] == HEAL)
            {
                SetConsoleTextAttribute(h, GREEN);//ярко-салатовый
                cout << "+";//лечение
            }
        }
        cout << "\n";
    }
    //пример установки курсора в любые координаты консоли
    COORD position; // координати гг
    position.X = 0;
    position.Y = 2;
    SetConsoleCursorPosition(h, position);
    SetConsoleTextAttribute(h, PINK);
    cout << (char)2;

    int coins = 0, health = 100;
    while (true)
    {

        int code = _getch();//get character -получуние кода нажатой клавиши
        SetConsoleCursorPosition(h, position);
        cout << " ";


        if (code == 224)//если нажата какая-то стрелка
        {
            code = _getch();
        }

        if (code == RIGHT and maze[position.Y][position.X + 1] != WALL) //right               
            position.X++;
        else if (code == LEFT and maze[position.Y][position.X - 1] != WALL)//left           
            position.X--;
        else if (code == UP and maze[position.Y - 1][position.X] != WALL)//up    
            position.Y--;
        else if (code == DOWN and maze[position.Y + 1][position.X] != WALL)//down    
            position.Y++;

        SetConsoleCursorPosition(h, position);
        SetConsoleTextAttribute(h, PINK);
        cout << (char)2;
        ///////////////////////////////////////////////////////////////////////////////

        COORD info_box;
        info_box.Y = 1;
        info_box.X = width + 2;
        SetConsoleCursorPosition(h, info_box);
        SetConsoleTextAttribute(h, YELLOW);
        cout << "COINS: " << coins << "\n";
        info_box.Y = 2;
        SetConsoleCursorPosition(h, info_box);
        SetConsoleTextAttribute(h, RED);
        cout << "HEALTH: " << health << "\n";
        if (maze[position.Y][position.X] == COIN)
        {

            coins++;
            maze[position.Y][position.X] = HALL;
            info_box.Y = 1;
            info_box.X = width + 2;
            SetConsoleCursorPosition(h, info_box);
            SetConsoleTextAttribute(h, YELLOW);
            cout << "COINS: " << coins << "\n";

        }
        else if (maze[position.Y][position.X] == ENEMY)
        {

            health -= 25;
            maze[position.Y][position.X] = HALL;
            info_box.Y = 2;
            info_box.X = width + 2;
            SetConsoleCursorPosition(h, info_box);
            SetConsoleTextAttribute(h, RED);
            
            cout << "HEALTH: " << health << " \n";
            

            if (health <= 0)
            {
                int answer;
                answer = MessageBoxA(0, "You death", "Loser", MB_YESNO);
                system("cls");
                if (answer == IDYES)
                {
                    main();
                }
                else
                {
                    exit(0);
                }
            }
        }
        
        else if (maze[position.Y][position.X] == HEAL)
        {
            if (health == 100)
            {
                cout << "+";
            }
            health += 25;
            
            maze[position.Y][position.X] = HALL;
            info_box.Y = 2;
            info_box.X = width + 2;

            SetConsoleCursorPosition(h, info_box);
            SetConsoleTextAttribute(h, RED); 
            
            cout << "HEALTH: " << health << " \n";
            

        }
        ///////////////////////////////////////////////////////////////////////////////
        //проверка на выход

        if (position.Y == height - 3 and position.X == width - 1)
        {
            int user;
            user = MessageBoxA(0, "You win", "Congratulations", MB_YESNO);
            system("cls");
            if (user == IDYES)
            {
                main();
            }
            else
            {
                exit(0);
               
            }
        }

    }


    Sleep(INFINITE);//пауза на 10 сек

    //коридоры - 0
    //стены - 1
    //монетки - 2
    //враги - 3

}

