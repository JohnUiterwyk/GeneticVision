#include "Util.h"

using namespace std;

/************************************************
 getToken originally written by Peter Wilson
 Modified to check for end of string conditions
************************************************/
string getToken(string &s, string::iterator &i)
{
    string tok;
    string::iterator start;
    for (; *i == ' ' && (i != s.end()); ++i);
    if (i == s.end())
    {
       return tok;
    }
    else if (*i == '(')
    {
        tok = "(";
        i++;
    }
    else if (*i == ')')
    {
        tok = ")";
        i++;
    }
    else
    {
        for (start = i; (*i != ' ') && (*i != ')') && (*i != '\n')
                        && (i != s.end()); i++);
        tok.assign(start, i);
    }

    return tok;
}

/************************************************
 lookAtToken originally written by Peter Wilson
 Modified to check for end of string conditions
************************************************/
string lookAtToken(string &s, string::iterator i)
{
   string tok;
   tok = getToken(s, i);
   return tok;
}
