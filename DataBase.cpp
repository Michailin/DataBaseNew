#include "DataBase.h"
#include <cstdio>
int stringToField(const char * str,Field & result,char * buf,char * buf_data)
{
    if(sscanf(str,"%i %s %lf %s",&(result.getUserID()),buf,&(result.getPrice()),buf_data) != 4)
        return 0;
    int len = 0;
    while(buf[len] != 0 && len < MAX_BUF_LEN)
        len ++;
    buf[len] = '\0';
    result.setItem(buf,len + 1);
    result.setData(buf_data);
    return 1;
}
DataBase :: DataBase (const char * path) throw(DataBase :: DataBaseException)
{
    FILE * file = fopen(path,"r");
    char * buf = new char [MAX_BUF_LEN];
    char * bufItem = new char [MAX_BUF_LEN];
    char * bufData = new char [MAX_BUF_LEN];
    if(!file)
        throw DataBase :: DataBaseException("cannot open file");
   // Field * tmp = new Field;
    while(!feof(file))
    {
        Field tmp;
        memset(buf,0,MAX_BUF_LEN);
        memset(bufData,0,MAX_BUF_LEN);
        memset(bufItem,0,MAX_BUF_LEN);
        if(!fgets(buf,MAX_BUF_LEN,file))
            throw DataBase :: DataBaseException("error while reading file");
        if(ferror(file))
            throw DataBase :: DataBaseException("error while reading from file");
        if(!stringToField(buf,tmp,bufItem,bufData))
            throw DataBase :: DataBaseException("unknown string in file");
        //std  :: cout << tmp.getItem() << std :: endl;
        data.push_back(tmp);
    }
    fclose(file);
    delete [] buf;
    delete [] bufItem;
    delete [] bufData;
}
DataBase :: DataBase(FILE *file) throw(DataBase ::DataBaseException)
{
    if(!file)
        throw DataBase :: DataBaseException("file is invalid in costrunctor");
    char * buf = new char [MAX_BUF_LEN];
    char * bufItem = new char [MAX_BUF_LEN];
    char * bufData = new char [MAX_BUF_LEN];
    Field tmp;
    while(!feof(file))
    {
        memset(buf,0,MAX_BUF_LEN);
        memset(bufItem,0,MAX_BUF_LEN);
        memset(bufData,0,MAX_BUF_LEN);
        if(!fgets(buf,MAX_BUF_LEN,file))
            throw DataBase :: DataBaseException("error while reading file");
        if(ferror(file))
            throw DataBase :: DataBaseException ("error while reading");
        if(!stringToField(buf,tmp,bufItem,bufData))
            throw DataBase :: DataBaseException("string is invalid");
        data.push_back(tmp);
    }
    //fclose(file);
    delete [] buf;
    delete [] bufItem;
    delete [] bufData;
}
void DataBase :: printData()
{
    for(unsigned int  i=0; i< data.size(); i++)
        std :: cout <<data[i].getUserID()<< " " <<data[i].getItem() << " " <<  data[i].getPrice() << " " << data[i].getData() << std :: endl;
}
