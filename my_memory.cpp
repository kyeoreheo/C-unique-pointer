//Kyeore Heo
#include "my_memory.hpp"
#include <iostream>
//---------------------SptrCounter ------------------------------------//
SptrCounter::SptrCounter():my_counter(0)
{}
SptrCounter::~SptrCounter()
{}
void SptrCounter::reset()
{ my_counter = 0; }
int SptrCounter::getMyCounter()
{ return my_counter; }
void SptrCounter::increase()
{ my_counter++; }
void SptrCounter::decrease()
{ my_counter--; }

//---------------------my_unique_ptr ------------------------------------//
template<typename T> //Default Constructor. this will be called when there are no input.
my_unique_ptr<T>::my_unique_ptr(): my_ptr(nullptr)
{
    std::cout<<"default"<<std::endl;
}
template<typename T> //Destructor. I should release the memory block. To avoid memory leek!
my_unique_ptr<T>::~my_unique_ptr()
{ delete my_ptr;
//    std::cout<<"end"<<std::endl;

}
template<typename T> //Const with input. When there are input value, unique ptr will be the address of input.
my_unique_ptr<T>::my_unique_ptr(T *input)
{ my_ptr = input;
    std::cout<<"with value"<<input<<std::endl;

}

template<typename T>//Move Assignment. returnType is my_unique_ptr<T>
my_unique_ptr<T>& my_unique_ptr<T>:: operator=(my_unique_ptr<T> && rhs)
{
    //*this->getInfo();
    if(&rhs == this) return *this; // if they are the same, return *this
    my_ptr = rhs.my_ptr;  //l-value becomes the r-value's memory
    rhs.my_ptr = nullptr; //and free the r-value's memory
    return *this;
}
template<typename T>//Move Constructor
my_unique_ptr<T>::my_unique_ptr(my_unique_ptr<T> &&rhs)
{
    my_ptr = rhs.my_ptr; //l-value becomes the r-value's memory
    rhs.my_ptr = nullptr;
}
template<typename T>
T& my_unique_ptr<T>:: operator*()const
{
    std::cout<<"T& my_unique_ptr<T>::operator*()const"<<*my_ptr<<std::endl;
    return *my_ptr; }
template<typename T>
T* my_unique_ptr<T>:: operator -> ()const
{ return my_ptr; }
template<typename T>
bool my_unique_ptr<T>::isNullptr()
{ return (my_ptr==nullptr);}
template<typename T>
void my_unique_ptr<T>::getInfo()
{ std::cout<<"My adr: "<<this<<" I'm pointing: "<<my_ptr<<std::endl; }

//-------------------my_shared_ptr---------------------------------------------//
template<typename T>
my_shared_ptr<T>::my_shared_ptr():my_ptr(nullptr),my_sp_counter(nullptr)
{}
template<typename T>
my_shared_ptr<T>::~my_shared_ptr()
{
    if(my_sp_counter!=nullptr) //
    {
        if(my_sp_counter->getMyCounter() <= 0)
        {
                delete my_ptr;
                delete my_sp_counter;
        }
        else
            my_sp_counter->decrease(); //I have to put decrease at the last because I have to check the my_sp_counter is pointing something, and the counter is below 0 or not.
    }
}
template<typename T> //with value
my_shared_ptr<T>::my_shared_ptr(T* input)
{
    my_ptr = input;
    my_sp_counter = new SptrCounter(); //let *my_sp_counter points SptrCounter();
    my_sp_counter->increase(); //Since this shared_ptr points the value, increase by 1
}
template<typename T>//Copy Constructor
my_shared_ptr<T>::my_shared_ptr(my_shared_ptr<T> &rhs)
{
    my_ptr = rhs.my_ptr; //l-value becomes the r-value's address;
    my_sp_counter = rhs.my_sp_counter;//copies also the counter! they should share
    if(my_sp_counter != nullptr)//If we copy the empty counter, we dont increase
        my_sp_counter->increase(); //Since this ptr copied the value, this also points that value, so increase by 1
}
template<typename T>//Move Constructor
my_shared_ptr<T>::my_shared_ptr(my_shared_ptr<T>&& rhs)
{
    my_ptr = rhs.my_ptr; //l-value takes r-value's address
    my_sp_counter = rhs.my_sp_counter;//also copies the counter.
    rhs.my_ptr = nullptr; //release r-value's ptr;
    rhs.my_sp_counter = nullptr; //and release r-value's counter to null.
}
template<typename T>//Move assignment
my_shared_ptr<T>&  my_shared_ptr<T>::operator=(my_shared_ptr<T>&& rhs)
{
    if(&rhs == this) return *this; //if they are the same, return *this
    my_ptr = rhs.my_ptr; //l-value takes r-value's address
    my_sp_counter = rhs.my_sp_counter;//also copies the counter.
    rhs.my_ptr = nullptr; //release r-value's ptr;
    rhs.my_sp_counter = nullptr; //and release r-value's counter to null.
    return *this; //and then return *this
}
template<typename T>//Copy Assignment
my_shared_ptr<T>& my_shared_ptr<T>:: operator=(my_shared_ptr<T>& rhs)
{
    if(&rhs == this) return *this; //if they are the same, return *this
    my_ptr = rhs.my_ptr; //copy the r-value's ptr
    my_sp_counter = rhs.my_sp_counter; //copy the r-value's counter
    return *this;
}
template<typename T>
void my_shared_ptr<T>::getInfo()
{
    std::cout<<"My adr: "<<this<<" I'm pointing: "<<my_ptr;
    if(my_sp_counter != nullptr)
        std::cout<<" counter: "<<my_sp_counter->getMyCounter();
    std::cout<<std::endl;
}
template<typename T>
bool my_shared_ptr<T>::isNullptr()
{return (my_ptr == nullptr);}
template<typename T>
T& my_shared_ptr<T>:: operator*()const
{ return *my_ptr; } //return time is address
template<typename T>
T* my_shared_ptr<T>:: operator -> ()const
{ return my_ptr; }


