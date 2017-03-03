#include "strcompare.h"
int strcompare1(const char * s1, const char * s2)
{
    unsigned int len1 = strlen(s1);
    unsigned int len2 = strlen(s2);
    if(len1 >= len2 )
        return strcmp(s1,s2);
    else
    {
        for(unsigned int i = 0; i < len1; i++)
        {
            if(s1[i] > s2[i])
                return 1;
            else if(s1[i] < s2[i])
                return -1;
        }
        return 1;
    }
}
