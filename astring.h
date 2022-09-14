#pragma once
#include <bits/stdc++.h>
using namespace std;
#define num_of_buf 10
#define ini_Size 16
class String
{
private:
    // char s[Size];
    char *s;
    int Size_of_dstring;
    /// utility classes are helping code to get rid of repeatition of same code
    void bound_check(int n) const
    {
        if (strlen(s) <= n || n < 0)
        {
            cout << "ERROR: Invalid...";
            exit(1);
        }
    }
    void utility_append(const string &n)
    {
        char ts[n.length() + strlen(s) + 1];
        strcpy(ts, s);
        int i;
        for (i = strlen(s); i < (strlen(s) + n.length()); i++)
            ts[i] = n[i - strlen(s)];
        ts[i] = '\0';
        delete[] s;
        utility_strcpy(ts);
    }
    void utility_strcpy(const char *n)
    {
        Size_of_dstring = strlen(n);
        s = new char[Size_of_dstring + 1];
        strcpy(s, n);
        s[Size_of_dstring] = '\0';
    }
    void utility_ul(char n, int c)
    {
        for (int i = 0; i < strlen(s); i++)
            if (s[i] >= n && s[i] <= (n + 25))
                s[i] = s[i] + (c * 32);
    }
    void utility_insert(int j, const string &n)
    {
        bound_check(j);
        int l = n.length(), sd = strlen(s), k = j;
        char ts[sd + l + 1];
        strcpy(ts, s);
        for (int i = sd - 1; i >= j; --i)
            ts[i + l] = s[i];
        for (int k = j; k < j + l; k++)
            ts[k] = n[k - j];
        ts[sd + l] = '\0';
        delete[] s;
        utility_strcpy(ts);
    }
    void input(istream &in, char chr = '\n')
    {
        delete[] s;
        char ch = '0', *buffer[num_of_buf];
        int j = 0, i;
        while (ch != chr)
        {
            buffer[j] = new char[ini_Size];
            i = 0;
            while (i < ini_Size - 1)
            {
                ch = in.get();
                if (ch == chr)
                    break;
                buffer[j][i++] = ch;
            }
            buffer[j++][i] = '\0';
        }
        Size_of_dstring = (j - 1) * ini_Size + i + 1;
        s = new char[Size_of_dstring];
        strcpy(s, buffer[0]);
        for (int l = 1; l < j; l++)
            strcat(s, buffer[l]);
        s[(j - 1) * ini_Size + i] = '\0';
        for (int i = 0; i < j; i++)
            delete[] buffer[i];
    }
public:
    /// assigning and appending opertions strats
    String(const char *n = "") { utility_strcpy(n); }
    void assign(const char *n) { utility_strcpy(n); }
    void operator=(const char *n) { utility_strcpy(n); }
    void append(const char *n) { utility_append(n); }
    void append(const String &n) { utility_append(n.s); }
    void operator+=(const String &n) { utility_append(n.s); }
    void operator+=(const char *n) { utility_append(n); }
    String& insert(int j, const char *n) {   utility_insert(j, n);return *this;}
    String& insert(int j, const String &n) { utility_insert(j, n.s);return *this;}
    String operator+(const String &n) const
    {
        String tmp;
        tmp.assign(s);
        tmp.append(n.s);
        return tmp;
    }
    String operator+(const char *n) const
    {
        String tmp;
        tmp.assign(s);
        tmp.append(n);
        return tmp;
    }
    String &replace(int j, int l, const char *n)
    {
        erase(j, l);
        insert(j, n);
        return *this;
    }
    String &replace(int j, int l, const String &n)
    {
        erase(j, l);
        insert(j, n);
        return *this;
    }
    /// assigning and appending opertions ends
    void push_back(char n)
    {
        char *t;
        t = new char[strlen(s) + 2];
        strcpy(t, s);
        t[strlen(s)] = n;
        t[strlen(s) + 1] = '\0';
        delete[] s;
        utility_strcpy(t);
        delete[] t;
    }
    String& erase(int n, int l = 1)
    {
        bound_check(n);
        char *t;
        t = new char[strlen(s) + 1];
        strcpy(t, s);
        t[strlen(s)] = '\0';
        int sd = strlen(t);
        for (int i = n; i < sd - l; i++)
            t[i] = t[i + l];
        t[sd - l] = '\0';
        delete[] s;
        utility_strcpy(t);
        delete[] t;
        return *this;
    }
    String center(int ss, char n = ' ') const
    {
        /// function to centerize string within boundries here ss is total length required and n is fill character for left spaces
        if (ss < length())
            return String(s);
        char t[ss];
        int u = length();
        int y = (ss - u) / 2;
        for (int i = 0; i < ss; i++)
            if (i < y || i >= y + u)
                t[i] = n;
            else if (i >= y || i < y + u)
                t[i] = s[i - y];
        return String(t);
    }
    String substr(int j = 0, int k = -1)
    {
        /// return substring from j to k
        bound_check(j);
        char t[k - j + 2];
        if (k == -1 || k > (strlen(s)))
            k = strlen(s);
        int i = j;
        for (i; i <= k; i++)
            t[i - j] = s[i];
        t[k - j + 1] = '\0';
        return String(t);
    }
    void swap(String &n)
    {
        /// swap 2 strings
        String t;
        t.utility_strcpy(s);
        delete[] s;
        utility_strcpy(n.s);
        delete[] n.s;
        n.utility_strcpy(t.s);
    }
    char at(int n) const
    {
        /// return value on index
        bound_check(n);
        return s[n];
    }
    friend void getline(istream &in, String &o, char ch = '\n')
    {
        o.input(in, ch);
    }
    void copy(char h[], const int &l, const int &i) const
    {
        /// copy portion of string into new one
        int j = i, k = 0;
        for (j, k; j < i + l; j++, k++)
            h[k] = s[j];
        h[k] = '\0';
    }
    void pop_back()
    {
        /// delete last item
        s[strlen(s) - 1] = '\0';
    }
    int find(const char &n, unsigned int j = 0) const
    {
        /// search item in string
        for (unsigned int i = j; i < strlen(s); i++)
            if (n == s[i])
                return i;
        return -1;
    }
    int rfind(const char &n, int k = -1) const
    {
        /// search item in string in reverse order
        if (k < 0)
            k = strlen(s);
        for (unsigned int i = k; i >= 0; i--)
            if (n == s[i])
                return i;
        return -1;
    }
    void clear() { s[0] = '\0'; }
    /// comperison operators starts
    bool operator==(const String &n) const
    {
        return (strcmp(n.s, s) == 0);
    }
    bool operator==(const char *n) const
    {
        return (strcmp(n, s) == 0);
    }
    bool operator!=(const String &n) const
    {
        return (strcmp(n.s, s) != 0);
    }
    bool operator!=(const char *n) const
    {
        return (strcmp(n, s) != 0);
    }
    bool operator>(const String &n) const
    {
        return (strcmp(s, n.s) > 0);
    }
    bool operator<(const char *n) const
    {
        return (strcmp(s, n) < 0);
    }
    bool operator>=(const String &n) const
    {
        return (strcmp(s, n.s) >= 0);
    }
    bool operator<=(const char *n) const
    {
        return (strcmp(s, n) <= 0);
    }
    /// comperison operators ends
    unsigned int length() const
    {
        /// return size of string
        int r = 0;
        for (; s[r] != '\0'; ++r)
            ;
        return r;
    }
    unsigned int size() const { return strlen(s); }
    static unsigned int capacity() { return ini_Size; }
    unsigned int max_size() const { return ini_Size * num_of_buf; } /// FIXME: for now it is equal to Size but when it upgrade to dynamic memory it increse by ini_size*Size
    String &reverse()
    {
        /// reverse the string
        int sd = strlen(s);
        for (int i = 0; i <= sd / 2; i++)
            std::swap(s[i], s[sd - i - 1]);
        return *this;
    }
    char &operator[](int n)
    {
        /// manage single index
        bound_check(n);
        return s[n];
    }
    String &capatilize()
    {
        /// function Capatilize letters (first letter of sentence)
        int j = 0;
        for (; find(' ', j++) != -1;)
            if ((s[j] >= 'a' && s[j] <= 'z') || (s[j] >= 'A' && s[j] <= 'Z'))
                break;
        if ((s[--j] >= 'a' && s[j] <= 'z'))
            s[j] = s[j] - '!' + 1;
        int k = 0, sd = strlen(s);
        for (int i = 0; i < sd; i = k + 1)
        {
            k = (find('.', i) ^ 0);
            if (k == -1)
                break;
            for (; find(' ', ++k) != -1;)
                if ((s[k] >= 'a' && s[k] <= 'z') || (s[k] >= 'A' && s[k] <= 'Z'))
                    break;
            if (k != -1 && (s[k] >= 'a' && s[k] <= 'z'))
                s[k] = s[k] - '!' + 1;
        }
        return *this;
    }
    String &upper() 
    {
        /// converting whole string to upper
        utility_ul(97, -1);
        return *this;
    } 
    String &lower() 
    { /// converting whole string to lower
        utility_ul(65, 1);
        return *this;
    }  
    int count(const char &n) const
    {
        /// func to count occurence of letter in string
        int r = 0;
        for (int i = 0; i < length(); i++)
            if (n == s[i])
                r++;
        return r;
    }
    int compare(const char *n) const
    {
        int counter = 0;
        if (strlen(s) == strlen(n))
        {
            for (int i = 0; i < max(strlen(s), strlen(n)); i++)
                if (s[i] != n[i])
                    counter = 1;
        }
        else if (strlen(s) > strlen(n))
            counter = 1;
        else if (strlen(s) < strlen(n))
            counter = -1;
        return counter;
    }
    friend ostream &operator<<(ostream &os, const String &d)
    {
        for (int i = 0; i < strlen(d.s); i++)
            cout << d.s[i];
        return os;
    }
    friend istream &operator>>(istream &os, String &d)
    {
        d.input(os);
        return os;
    }
    /// bool checkers starts
    bool isalpha() const
    {
        for (int i = 0; i < length(); i++)
            if (!((s[i] >= 'a' && s[i] <= 'z') || (s[i] >= 'A' && s[i] <= 'Z') || s[i] == ' ' || s[i] == '.'))
                return false;
        return true;
    }
    bool islower() const
    {
        for (int i = 0; i < length(); i++)
            if (!((s[i] >= 'a' && s[i] <= 'z') || s[i] == ' ' || s[i] == '.'))
                return false;
        return true;
    }
    bool isupper() const
    {
        for (int i = 0; i < length(); i++)
            if (!((s[i] >= 'A' && s[i] <= 'Z') || s[i] == ' ' || s[i] == '.'))
                return false;
        return true;
    }
    bool isalnum() const
    {
        for (int i = 0; i < length(); i++)
            if (!((s[i] >= 'a' && s[i] <= 'z') || (s[i] >= 'A' && s[i] <= 'Z') || s[i] == ' ' || (s[i] >= '0' && s[i] <= '9') || s[i] == '.'))
                return false;
        return true;
    }
    bool isnumeric() const
    {
        for (int i = 0; i < length(); i++)
            if (!((s[i] >= '0' && s[i] <= '9') || s[i] == '.'))
                return false;
        return true;
    }
    bool isdecimal() const
    {
        for (int i = 0; i < length(); i++)
            if (!(s[i] >= '0' && s[i] <= '9'))
                return false;
        return true;
    }
    bool isspace() const
    {
        for (int i = 0; i < length(); i++)
            if (s[i] == ' ')
                return true;
        return false;
    }
    /// bool checkers ends
    /// Extended API for original string class support
    void append(const string &n) { utility_append(n); }
    void operator+=(const string &n) { utility_append(n); }
    String &insert(int j, const string &n) {utility_insert(j, n);return *this;}
    void assign(const string &n)
    {
        char *t;
        t = new char[n.length() + 1];
        for (int i = 0; i < n.length(); i++)
            t[i] = n[i];
        t[n.length()] = '\0';
        utility_strcpy(t);
        delete[] t;
    }
    String operator+(const string &n) const
    {
        String tmp;
        tmp.assign(s);
        tmp.append(n);
        return tmp;
    }
    String &replace(int j, int l, const string &n)
    {
        erase(j, l);
        insert(j, n);
    }
    bool operator!=(const string &n) const
    {
        return (n.compare(s) != 0);
    }
    bool operator==(const string &n) const
    {
        return (n.compare(s) == 0);
    }
    // some help function to compatible with cstring and normal class string
    friend String operator+(const string &a, const String &b)
    {
        String tmp;
        tmp.assign(a);
        tmp.append(b);
        return tmp;
    }
    friend String operator+(const char a[], const String &b)
    {
        String tmp;
        tmp.assign(a);
        tmp.append(b);
        return tmp;
    }
    ~String() {delete[] s;}
};
String operator+(const char a[], const string &b)
{
    String tmp;
    tmp.assign(a);
    tmp.append(b);
    return tmp;
}
String operator+(const string &a, const char *b)
{
    String tmp;
    tmp.assign(a);
    tmp.append(b);
    return tmp;
}
//  FIXME: here is some error occuired we want to concatinate these 2 cstrings into our own dynamic class "String"
// String operator+(const char *a, const char *b)
// {
//     String tmp;
//     tmp.assign(a);
//     tmp.append(b);
//     return tmp;
// }