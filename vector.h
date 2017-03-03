#ifndef VECTOR_H
#define VECTOR_H
#include <cstring>
#include <iostream>
#include <cstdlib>
template <typename Type> class Vector
{
private:
    unsigned int len;
    unsigned int capacity;
    Type * data;
public:
    class VectorException
    {
    public:
        const char * reason;
        VectorException():
            reason("default reason")
        {}
        VectorException(const char * reason_):
            reason(reason_)
        {}
        const char * toString() const
        {
            return reason;
        }
    };
public:
    class iterator
    {
    private :
        Vector <Type> * vthis;
        unsigned int position;
    public:
        iterator(unsigned int position_,Vector <Type> * vthis_):
            vthis(vthis_),
            position(position_)
        {}
        iterator(const iterator & copy):
            vthis(copy.vthis),
            position(copy.position)
        {}
        iterator operator ++()
        {
            iterator tmp(*this);
            position++;
            return tmp;
        }
        iterator & operator ++(int m)
        {
            position ++;
            return *this;
        }
        bool operator <(const iterator & compare) const
        {
            return (position < compare.position);
        }
        bool operator >(const iterator & compare) const
        {
            return (position > compare.position);
        }
        bool operator <=(const iterator & compare) const
        {
            return (position <= compare.position);
        }
        bool operator >=(const iterator & compare) const
        {
            return (position >= compare.position);
        }
        bool operator ==(const iterator & compare) const
        {
            return (position == compare.position);
        }
        bool operator != (const iterator & compare) const
        {
            return (position != compare.position);
        }
        Type & operator *() throw(VectorException)
        {
            if(position >= vthis->size())
                throw VectorException("array index out of bounds");
            return vthis->data[position];
        }
    };
public:
    class const_iterator
    {
    private:
        Vector <Type> * vthis;
        unsigned int position;
    public:
        const_iterator(unsigned int position_,Vector <Type> * vthis_):
            position(position_),
            vthis(vthis_)
        {}
        const_iterator(const const_iterator & copy):
            position(copy.position),
            vthis(copy.vthis)
        {}
        const_iterator operator ++()
        {
            const_iterator tmp(*this);
            position ++;
            return tmp;
        }
        const_iterator & operator ++(int n)
        {
            position++;
            return *this;
        }
        bool operator < (const const_iterator & compare) const
        {
            return (position < compare.position);
        }
        bool operator > (const const_iterator & compare) const
        {
            return (position > compare.position);
        }
        bool operator <=(const const_iterator & compare) const
        {
            return (position <= compare.position);
        }
        bool operator >=(const const_iterator & compare) const
        {
            return (position >= compare.position);
        }
        bool operator ==(const const_iterator & compare) const
        {
            return (position == compare.position);
        }
        bool operator !=(const const_iterator & compare) const
        {
            return (position != compare.position);
        }
        const Type & operator *() throw (VectorException)
        {
            if(position >= vthis->size())
                throw VectorException("index out of bounds");
            return vthis->data[position];
        }
    };
public:
    Vector():
        len(0),
        capacity(10),
        data(new Type[capacity])
    {
        memset(data,0,len*sizeof(Type));
    }
    Vector(int capacity_):
        len(0),
        capacity(capacity_),
        data(new Type[capacity_])
    {
        memset(data,0,sizeof(Type)*capacity);
    }
    Vector(const Vector & copy):
        len(copy.len),
        capacity(copy.capacity),
        data(new Type[capacity])
    {
        memset(data,0,sizeof(Type)*capacity);
        for(int i = 0; i<len; i++)
            data[i] = copy.data[i];
    }
    ~Vector()
    {
        if(data != NULL)
            delete [] data;
    }
    unsigned int size() const
    {
        return len;
    }
    unsigned int vectorCapacity() const
    {
        return capacity;
    }
    void reallocMem(unsigned int capacity_new)
    {
        Type * tmp = new Type[capacity_new];
        memset(tmp,0,sizeof(Type)*capacity_new);
        for(int i = 0; i < len; i++)
            tmp[i] = data[i];
        //memmove(tmp,data,len*sizeof(Type));
        //memcpy(tmp,data,(len - 1)*sizeof(Type));
        if(data != NULL)
            delete [] data;
        data = tmp;
        capacity = capacity_new;

        //data = new Type[capacity_new];
    }
    void push_back(const Type & copy)
    {
        if(capacity == len)
            reallocMem(capacity*2);
        data[len] = copy;
        len++;
    }
    Type & operator [](unsigned int index) throw (VectorException)
    {
        if(index >= len)
            throw VectorException("index out of bounds");
        return data[index];
    }
    Vector & operator =(const Vector & copy)
    {
        len = copy.len;
        capacity = copy.capacity;
        delete [] data;
        data = new Type[capacity];
        memset(data,0,capacity*sizeof(Type));
        for(int i = 0; i < len; i++)
            data[i] = copy.data[i];
        //memcpy(data,copy.data,len*sizeof(Type));
        return *this;
    }
    const Type & operator [] (unsigned int index) const throw (VectorException)
    {
        if(index >= len)
            throw VectorException("index out of bounds");
        return data[index];
    }
    void removeData(unsigned int index) throw (VectorException)
    {
        if(index >= len)
            throw VectorException("index out of bounds in removeData");
        if(index == len -1)
            len --;
        else
        {
            memmove(&(data[index]),&(data[index + 1]),len - index - 1);
            len --;
            if(len < 0.5*capacity && capacity > 29)
                reallocMem(0.5*capacity);
        }
    }
    void freeVector()
    {
        len = 0;
        capacity = 10;
        delete [] data;
        data = new Type[capacity];
        memset(data,0,sizeof(Type)*capacity);
    }
    void cutAfterIndex(unsigned int index) throw(VectorException)
    {
        if (index >= len)
            throw VectorException("index is out of bound in cutAfterIndex");
        if(index == len - 1)
            return ;
        memset(&(data[index + 1]),0,sizeof(Type)*(len - index - 1));
        len = index + 1;
        if(len < capacity*0.6 && capacity > 29)
            reallocMem(capacity*0.6);
    }
    iterator getEndIterator()
    {
        iterator tmp(len,this);
        return tmp;
    }
    iterator getBeginIterator()
    {
        iterator tmp(0,this);
        return tmp;
    }
    const_iterator getBeginConstIterator() const
    {
        const_iterator tmp(0,this);
        return tmp;
    }
    const_iterator getEndConstIterator() const
    {
        const_iterator tmp(len,this);
        return tmp;
    }
};
#endif // VECTOR_H
