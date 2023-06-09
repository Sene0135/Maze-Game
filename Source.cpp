#include <iostream>
#include <string>
#include <fstream>
#include "Coordinates.h"
#include <Windows.h>
#include <conio.h>
#include "Colors.h"
#include "MySound.h"
using namespace std;


struct position
{
    int x;
    int y;
};

class MyStack
{
public:
    position arr[1000];
    int T;
    MyStack() { T = 0; }
    void push(int x, int y);
    position pop();
    position peek();
};

const int SLEEP = 1000;

bool MySleep(int n)
{
    double d = 0;
    while (d < 10)
    {
        d++;
        Sleep(1);
        if (_kbhit())
            return true;
    }
    return false;
}

void MyStack::push(int x, int y)
{
    position p;
    p.x = x;
    p.y = y;
    arr[T] = p;
    T++;
}

position MyStack::pop()
{
    T--;
    return arr[T];
}

position MyStack::peek()
{
    return arr[T - 1];
}

MyStack S;
char board[22][50];
int value;
int xcoor, ycoor;
Coordinates C;

// returns false if xy same as top of stack
bool CheckTopStack(int x, int y)
{
    position p;
    p = S.peek();
    if (p.x == x && p.y == y)
        return false;
    return true;
}


void main()
{
    ifstream input("c:\\temp\\maze\\mazeinterface.txt");
    //SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 8);
    for (int i = 0; i < 22; i++)
        for (int j = 0; j < 50; j++)
            input >> board[i][j];

    system("cls");
    //SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 8);

    for (int i = 0; i < 22; i++)
    {
        for (int j = 0; j < 50; j++)
        {
            if (board[i][j] == '1')
                cout << char(219);
            else if (board[i][j] == '2')
                cout << char(176);
            else
                cout << " ";
        }
        cout << endl;
    }

    xcoor = 0;
    ycoor = 1;

    int uxcoor, uycoor;
    uxcoor = 6;
    uycoor = 19;

    C.gotoxy(uxcoor, uycoor);
    cout << "O";


    char c;
    while (1)
    {
        C.gotoxy(52, 0);
        cout << "Press arrow keys to move" << endl;
        C.gotoxy(52, 1);
        cout << "Press 'w' to delete the block above" << endl;
        C.gotoxy(52, 2);
        cout << "Press 'a' to delete the block to the left" << endl;
        C.gotoxy(52, 3);
        cout << "Press 's' to delete the block below" << endl;
        C.gotoxy(52, 4);
        cout << "Press 'd' to delete the block to the right" << endl;
        C.gotoxy(52, 5);
        cout << "Use 't' to destroys all the blocks around you!"<< endl;
        C.gotoxy(52, 6);
        cout << "Edges CANNOT be destroyed" << endl;

        C.ShowConsoleCursor(false);

        // Moving mouse
        C.gotoxy(xcoor, ycoor);
        cout << "+";
        if (board[ycoor][xcoor + 1] == '2')
        {
            //C.gotoxy(50, 50);
            //cout << "The mouse has reached the end!" << endl;
            break;
        }

        if (MySleep(SLEEP))
        {
            MySound M;
            c = _getch();
            // Blow up to the right
            if ((c == 'd') && (uxcoor + 1 <= 48))
            {
                board[uycoor][uxcoor + 1] = '0';
                C.gotoxy(uxcoor + 1, uycoor);
                M.Play(L"c:\\temp\\maze\\explo.wav", NULL, SND_ASYNC);
                cout << " ";

            }
            // Blow up to the left
            else if ((c == 'a') && (uxcoor + 1 <= 48))
            {
                board[uycoor][uxcoor - 1] = '0';
                C.gotoxy(uxcoor - 1, uycoor);
                M.Play(L"c:\\temp\\maze\\explo.wav", NULL, SND_ASYNC);
                cout << " ";
            }
            // Blow up above
            else if ((c == 'w') && (uycoor + 1 <= 20))
            {
                board[uycoor - 1][uxcoor] = '0';
                C.gotoxy(uxcoor, uycoor - 1);
                M.Play(L"c:\\temp\\maze\\explo.wav", NULL, SND_ASYNC);
                cout << " ";
            }
            // Blow up down
            else if (c == 's' && (uycoor + 1 <= 20))
            {
  //              board[uycoor + 1][uxcoor] = '0';
                C.gotoxy(uxcoor, uycoor + 1);
                M.Play(L"c:\\temp\\maze\\explo.wav", NULL, SND_ASYNC);
                cout << " ";
            }
            else if (c == 't' && (uycoor + 1 <= 20) && (uxcoor + 1 <= 48))
            {
                board[uycoor][uxcoor] = '0';
                board[uycoor+1][uxcoor] = '0';
                board[uycoor - 1][uxcoor] = '0';
                board[uycoor][uxcoor + 1] = '0';
                board[uycoor][uxcoor - 1] = '0';
                board[uycoor+1][uxcoor + 1] = '0';
                board[uycoor-1][uxcoor - 1] = '0';
                board[uycoor + 1][uxcoor - 1] = '0';
                board[uycoor - 1][uxcoor + 1] = '0';
                C.gotoxy(uxcoor, uycoor + 1);
                cout << " ";
                C.gotoxy(uxcoor, uycoor - 1);
                cout << " ";
                C.gotoxy(uxcoor - 1, uycoor);
                cout << " ";
                C.gotoxy(uxcoor + 1, uycoor);
                cout << " ";
                C.gotoxy(uxcoor + 1, uycoor+1);
                cout << " ";
                C.gotoxy(uxcoor + 1, uycoor - 1);
                cout << " ";
                C.gotoxy(uxcoor - 1, uycoor - 1);
                cout << " ";
                C.gotoxy(uxcoor - 1, uycoor + 1);
                cout << " ";
                M.Play(L"c:\\temp\\explo.wav", NULL, SND_ASYNC);
            }

            else if (c == -32)
            {
                c = _getch();
                if ((c == 77) && (board[uycoor][uxcoor + 1] == '0') && (uxcoor + 1 != 50)) // Arrow right moves character
                {
                    C.gotoxy(uxcoor, uycoor);
                    cout << " ";
                    uxcoor++;
                    C.gotoxy(uxcoor, uycoor);
                    cout << "O";
                }
                else if ((c == 75) && (board[uycoor][uxcoor - 1] == '0')) // Arrow left moves character
                {
                    C.gotoxy(uxcoor, uycoor);
                    cout << " ";
                    uxcoor--;
                    C.gotoxy(uxcoor, uycoor);
                    cout << "O";
                }
                else if ((c == 72) && (board[uycoor - 1][uxcoor] == '0')) // Arrow up moves character
                {
                    C.gotoxy(uxcoor, uycoor);
                    cout << " ";
                    uycoor--;
                    C.gotoxy(uxcoor, uycoor);
                    cout << "O";
                }
                else if ((board[uycoor + 1][uxcoor] == '0') && (c == 80)) // Arrow down moves character
                {
                    C.gotoxy(uxcoor, uycoor);
                    cout << " ";
                    uycoor++;
                    C.gotoxy(uxcoor, uycoor);
                    cout << "O";
                }
            }
        }

        Colors c;


        {
            C.gotoxy(xcoor, ycoor);
            cout << "*";

            if (board[ycoor + 1][xcoor + 1] == '2')
            {
                //      cout << "Ending reached!!" << endl;
                break;
            }
            Sleep(10);
            C.gotoxy(xcoor, ycoor);
            cout << " ";
            if ((board[ycoor][xcoor + 1] == '0') &&
                (CheckTopStack(xcoor + 1, ycoor)))
            {
                S.push(xcoor, ycoor);
                xcoor++;
                C.gotoxy(xcoor, ycoor + 1);
                c.SetColor(0, 3);
            }
            else if ((board[ycoor + 1][xcoor] == '0') &&
                (CheckTopStack(xcoor, ycoor + 1)))
            {
                S.push(xcoor, ycoor);
                ycoor++;
            }
            else if ((board[ycoor][xcoor - 1] == '0') &&
                (CheckTopStack(xcoor - 1, ycoor)))
            {
                S.push(xcoor, ycoor);
                xcoor--;
            }
            else if ((board[ycoor - 1][xcoor] == '0') &&
                (CheckTopStack(xcoor, ycoor - 1)))
            {
                S.push(xcoor, ycoor);
                ycoor--;
            }
            else // dead end
            {
                C.gotoxy(xcoor, ycoor);
                cout << char(219);
                board[ycoor][xcoor] = '1';
                position p;
                p = S.pop();
                xcoor = p.x;
                ycoor = p.y;
                Sleep(10);
            }
        }
    }
    cout << "Ending reached!!" << endl;
    while (1);
}