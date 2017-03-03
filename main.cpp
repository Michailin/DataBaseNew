#include <iostream>
#include "vector.h"
#include <algorithm>
#include <cstdio>
#include "structs.h"
#include "DataBase.h"\
#include <cstring>
 void func()
{
    Field ls;
    ls.setData("2017.01.12");
    ls.setItem("123456789",9);
    Vector <Field> tmp;
    std :: string tpq;
    for(int i = 0; i < 10; i++)
    {
        std :: cin >> tpq;
        ls.setItem(tpq.c_str(),tpq.size());
    }
}

int main()
{
    /*std :: string tmp("25073450 taohy 189.923077 2013.11.12");
    Field t;
    char * buf = new char [1024];
    char * buf1 = new char [1024];
    memset(buf,0,1024);
    memset(buf1,0,1024);
    stringToField(tmp.c_str(),t,buf,buf1);
    std :: cout << t.getUserID() << "userId" << std :: endl;
    std :: cout << t.getItem() << "item" << std :: endl;
    std :: cout << t.getPrice() << "price" << std :: endl;
    std :: cout << t.getData() << "data" << std :: endl;
    */
    DataBase tpq("/home/dmitry/Projects/DataBase/output");
    tpq.printData();
    return 0;
}
