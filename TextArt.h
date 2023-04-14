#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "Coordinates.h"
#include "MyRectangle.h"
#include <Windows.h>
using namespace std;

class TextArt : public Coordinates
{
public:
    int foreColor, backColor;
    int highlight_forecolor, highlight_backcolor;
    int maximumSizeOfInput;
    int xpos, ypos;
    int currRow;
    vector <string> data;
    TextArt(string filename, int x, int y, int fore, int back, int highlighted_fore, int highlighted_back);
    void Display(bool selectFirstEntry);
    void ColorRow(int entry);
    void ColorNext();
    void ColorPrevious();
    string GetEntry() { return data[currRow]; }
};

TextArt::TextArt(string filename, int x, int y, int fore, int back, int highlighted_fore, int highlighted_back)
{
    string s;
    currRow = 0;
    foreColor = fore;
    backColor = back;
    highlight_forecolor = highlighted_fore;
    highlight_backcolor = highlighted_back;

    xpos = x;
    ypos = y;
    ifstream input(filename);
    maximumSizeOfInput = 0;
    while (input.peek() != -1)
    {
        getline(input, s);
        if (s.length() > maximumSizeOfInput)
            maximumSizeOfInput = s.length();
        data.push_back(s);
    }
    input.close();
}

void TextArt::ColorNext()
{
    setForeGroundAndBackGroundColor(foreColor, backColor);
    gotoxy(xpos, ypos + currRow);
    cout << data[currRow];
    currRow = (currRow + 1) % data.size();
    setForeGroundAndBackGroundColor(highlight_forecolor, highlight_backcolor);
    gotoxy(xpos, ypos + currRow);
    cout << data[currRow];
}

void TextArt::ColorPrevious()
{
    setForeGroundAndBackGroundColor(foreColor, backColor);
    gotoxy(xpos, ypos + currRow);
    cout << data[currRow];
    currRow = currRow - 1;
    if (currRow < 0)
        currRow = data.size() - 1;
    setForeGroundAndBackGroundColor(highlight_forecolor, highlight_backcolor);
    gotoxy(xpos, ypos + currRow);
    cout << data[currRow];
}


void TextArt::ColorRow(int entry)
{
    gotoxy(xpos, ypos + entry);
    setForeGroundAndBackGroundColor(highlight_forecolor, highlight_backcolor);
    cout << data[entry];
}

void TextArt::Display(bool selectFirstEntry = true)
{
    setForeGroundAndBackGroundColor(foreColor, backColor);
    MyRectangle R(xpos - 1, ypos - 1, maximumSizeOfInput + 2, data.size() + 2, 219, true);
    //    R.Draw();
    R.DrawSkelaton(xpos - 1, ypos - 1, maximumSizeOfInput + 2, data.size() + 2);
    for (int i = 0; i < data.size(); i++)
    {
        gotoxy(xpos, ypos + i);
        cout << data[i];
    }
    if (selectFirstEntry)
        ColorRow(0);
}

