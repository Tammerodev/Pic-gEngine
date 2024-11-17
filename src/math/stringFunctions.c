#include "stringFunctions.h"

const int picg_string_containsCharacter(const char string[], char character)
{
    for(int i = 0; i < strlen(string); ++i) 
    {
        if(string[i] == character) 
        {
            return 1;
        }
    }
}

const int picg_string_countContainsCharacter(const char string[], char character) 
{
    int count = 0;

    for(int i = 0; i < strlen(string); ++i) 
    {
        if(string[i] == character) 
        {
            ++count;
        }
    }

    return count;
}