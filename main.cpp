#include <iostream>
#include "vector.h"
#include <algorithm>
#include <cstdio>
#include "structs.h"
#include "DataBase.h"
int main()
{
    try
    {
        DataBase interval;
        DataBase dataBase("/home/dmitry/Projects/DataBaseNew/output");
        dataBase.getIntervalFull(-1,-1,"a","a",-1,-1,NULL,NULL,interval);
        std :: cout << dataBase.size() << std :: endl;
        std :: cout << interval.size() << std :: endl;
        interval.printData();
    }
    catch (DataBase :: DataBaseException e)
    {
        printf("%s",e.toString());
    }

    return 0;
}
