#ifndef STRUCTS_H
#define STRUCTS_H
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include "vector.h"
class Field
{
private:
    unsigned int len;
    int user_id;
    char * item;
    double price;
    char data[12];
public:
    Field():
        len(0),
        user_id(0),
        item(NULL),
        price(0)
    {
        memset(data,0,12);
    }
    Field(unsigned int len_,int user_id_,char * item_,double price_,char * data_):
        len(len_),
        user_id(user_id_),
        price(price_)
    {
        if(len != 0)
        {
            item = new char [len];
            memset(item,0,len);
            memcpy(item,item_,len);
        }
        else
            item = NULL;
        memset(data,0,12);
        memcpy(data,data_,12);
    }
    Field(const Field & copy):
        len(copy.len),
        user_id(copy.len),
        price(copy.price)
    {
        if(len != 0)
        {
            item = NULL;
            item = new char [len];
            memset(item,0,len);
            memcpy(item,copy.item,len);
        }
        else
            item = NULL;
        memset(data,0,12);
        memcpy(data,copy.data,12);
    }
    ~Field()
    {
        if(item != NULL)
            delete [] item;
    }
    Field & operator = (const Field & copy)
    {
        len = copy.len;
        memcpy(data,copy.data,12);
        price = copy.price;
        user_id = copy.user_id;
        if(item != NULL)
            delete [] item;
        if(len)
        {
            char * item_tmp =  new char [len];
            item = NULL;
            item = item_tmp;
            memset(item,0,len);
            memcpy(item,copy.item,len);
        }
        else
            item = NULL;
        return *this;
    }
    void setLen(unsigned int len_)
    {
        len = len_;
    }
    void setData(const char * data_)
    {
        memcpy(data,data_,12);
    }
    void setItem(const char * item_, unsigned int len_)
    {
        len = len_;
        if(item)
            delete [] item;
        if(len)
        {
            char * item_tmp = new char[len];
            item = NULL;
            item = item_tmp;
            //memset(item,0,len);
            memcpy(item,item_,len);
        }
        else
            item = NULL;
    }
    void setUserID(int user_id_)
    {
        user_id = user_id_;
    }
    void setPrice(double price_)
    {
        price = price_;
    }
    unsigned int & getLen()
    {
        return len;
    }
    int & getUserID()
    {
        return user_id;
    }
    char * getData()
    {
        return data;
    }
    char * getItem()
    {
        return item;
    }
    double & getPrice()
    {
        return price;
    }
    unsigned int getLen() const
    {
        return len;
    }
    int getUserID() const
    {
        return user_id;
    }
    const char * getData() const
    {
        return data;
    }
    const char * getItem() const
    {
        return  item;
    }
    double getPrice() const
    {
        return price;
    }
};
#endif 
