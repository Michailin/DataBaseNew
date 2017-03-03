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
bool itemCompareMore(const char *item1, const char *item2)
{
    unsigned int len1 = strlen(item1);
    unsigned int len2 = strlen(item2);
    if(len1 > len2)
        return false;
    if(len1 == len2)
        return !strcmp(item1,item2);
    for(int i = 0; i < len1 ; i++)
    {
        if(item1[i] > item2[i])
            return true;
        else if(item1[i] < item2[i])
            return false;
    }
    return true;
}
bool itemCompareLess(const char * item1, const char * item2)
{
    unsigned int len1 = strlen(item1);
    unsigned int len2 =  strlen(item2);
    if(len1 > len2)
        return false;
    if(len1 == len2)
        return !strcmp(item1,item2);
    for(int i = 0; i< len1; i++)
    {
        if(item1[i] > item2[i])
            return false;
        else if(item1[i] < item2[i])
            return true;
    }
    return true;
}
