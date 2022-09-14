#include <bits/stdc++.h>
#include "astring.h"
#define bs 5
using std::cin;
using std::cout;
using std::endl;
int main()
{
    char ch = '0', *buffer[bs];
    int j = 0, i;
    while (ch != '\n')
    {
        buffer[j] = new char[16];
        i = 0;
        while (i<15)
        {
            ch = cin.get();
            if (ch == '\n')break;            
            buffer[j][i++] = ch;
        }
        buffer[j++][i] = '\0';
    }
    char *s;
    s=new char[(j - 1) * 16 + i + 1];
    s[0] = '\0';
    for (int l = 0; l < j; l++)
        strcat(s, buffer[l]);
    s[(j - 1) * 16 + i]='\0';
    for (int i = 0; i < bs; i++)
        delete[] buffer[i];
    cout<< s << strlen(s) << endl;
    delete[] s;
    return 0;
}