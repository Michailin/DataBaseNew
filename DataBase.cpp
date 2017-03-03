#include "DataBase.h"
#include <cstdio>
DataBase ::DataBase()
{

}
unsigned int DataBase :: size() const
{
    return data.size();
}
int stringToField(const char * str,Field & result,char * buf,char * buf_data)
{
    if(sscanf(str,"%i %s %lf %s",&(result.getUserID()),buf,&(result.getPrice()),buf_data) != 4)
        return 0;
    int len = 0;
    while(buf[len] != 0 && len < MAX_BUF_LEN)
        len ++;
    //buf[len] = '\0';
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
void DataBase :: push_back(const Field &copy)
{
    data.push_back(copy);
}
bool DataBase :: isContentsPrice(double price) const
{
    for(int i = 0; i < data.size(); i++)
    {
        if(data[i].getPrice() == price)
            return true;
    }
    return false;
}
bool DataBase :: isContentsID(int id) const
{
    for(int i = 0; i< data.size(); i++)
    {
        if(data[i].getUserID() == id)
            return true;
    }
    return false;
}
bool DataBase :: isContentsData(const char data1[12]) const
{
    for(int i = 0; i< data.size();i++)
    {
        if(!strcmp(data[i].getData(),data1))
            return true;
    }
    return false;
}
bool DataBase ::isContentsItem(const char *item) const
{
    for(int i = 0; i < data.size(); i++)
    {
        if(!strcmp(data[i].getItem(),item))
            return true;
    }
    return false;
}
void DataBase :: freeVector()
{
    data.freeVector();
}
void DataBase :: deleteField(const Field &copy)
{
    for(unsigned int i = 0; i < data.size();i++)
    {
        if(data[i] == copy)
            data.removeData(i);
    }
}
void DataBase :: deleteField(unsigned int index)
{
    if(index < data.size())
        data.removeData(index);
}
void DataBase :: getIntervalData(const char dataBegin[], const char dataEnd[], DataBase &result) const
{
    result.freeVector();
    for(unsigned int i = 0; i < data.size(); i++)
    {
        if((strcmp(dataBegin,data[i].getData()) <= 0) && (strcmp(dataEnd,data[i].getData()) >= 0))
            result.push_back(data[i]);
    }
}
void DataBase :: getIntervalPrice(double priceBegin, double priceEnd, DataBase &result) const
{
    result.freeVector();
    for(unsigned int i = 0; i <data.size(); i++)
    {
        if(priceBegin >= data[i].getPrice() && data[i].getPrice() <= priceEnd)
            result.push_back(data[i]);
    }
}
void DataBase :: getIntervalID(int idBegin, int idEnd, DataBase &result) const
{
    result.freeVector();
    for(unsigned int i =0; i< data.size(); i++)
    {
        if(idBegin <= data[i].getUserID() && idEnd >= data[i].getUserID())
            result.push_back(data[i]);
    }
}
void DataBase :: getIntervalItem(const char *itemBegin, const char *itemEnd, DataBase &result) const
{
    result.freeVector();
    for(unsigned int i = 0; i < data.size() ; i++)
    {
        if((isBeginTheSame(itemBegin,data[i].getItem()) || strcmp(data[i].getItem(),itemBegin) >= 0 )&& (isBeginTheSame(itemEnd,data[i].getItem()) || strcmp(itemEnd,data[i].getItem()) >= 0))
            result.push_back(data[i]);
    }
}
void DataBase :: getIntervalFull(int idBegin, int idEnd, const char *itemBegin, const char *itemEnd, double priceBegin, double priceEnd, const char dataBegin[], const char dataEnd[], DataBase &result) const
{
    result.freeVector();
    for(unsigned int i =0; i < data.size(); i++)
    {
        bool contents = true;
        if(idBegin != -1)
            contents *= (idBegin < data[i].getUserID());
        if(idEnd != -1)
            contents *= (idEnd > data[i].getUserID());
        if(itemBegin)
            contents *= itemCompareLess(itemBegin,data[i].getItem());
        if(itemEnd)
            contents *= itemCompareMore(itemEnd,data[i].getItem());
        if(priceBegin != -1)
            contents *= (priceBegin <= data[i].getPrice());
        if(priceEnd != -1)
            contents *= (priceEnd >= data[i].getPrice());
        if(dataBegin)
            contents *= (strcmp(data[i].getData(),dataBegin) >= 0);
        if(dataEnd)
            contents *= (strcmp(dataEnd,data[i].getData()) >= 0);
        if(contents)
            result.push_back(data[i]);
    }
}
void DataBase :: printData() const
{
    for(unsigned int  i=0; i< data.size(); i++)
        std :: cout <<data[i].getUserID()<< " " <<data[i].getItem() << " " <<  data[i].getPrice() << " " << data[i].getData() << std :: endl;
}
