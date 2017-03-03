#include "strcompare.h"
bool isBeginTheSame(const char * begin,const char * word)
{
    unsigned int len_begin = strlen(begin);
    unsigned int len_word = strlen(word);
    if(len_begin > len_word)
        return false;
    else
    {
        for(unsigned int i = 0; i < len_begin; i++)
        {
            if(begin[i] != word[i])
                return false;
        }
        return true;
    }
}
