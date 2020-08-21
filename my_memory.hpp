//Kyeore Heo
#ifndef my_memory_hpp
#define my_memory_hpp
//shared pointer
class SptrCounter 
{
    public:
        SptrCounter(); //Default. start with 0
        SptrCounter(const SptrCounter&) = delete; //cannot copy this SptrCount ex) Spcounter1(Spcounter2);
        SptrCounter& operator=(SptrCounter&) = delete; //cannot assign ex) Spcounter1 = SpCounter2;
        ~SptrCounter(); //Destructor. nothing to free memory
        void reset(); // make the counter to 0
        void increase();
        void decrease();
        int getMyCounter(); //return my_counter For debugging
    private:
        int my_counter; //no need to worry about getting negative. because in my DefaultConstructor, I will start with 0, and when it goes lower than 0, my_shared_ptr Destructor will delete.
};

//unique pointer
template <typename T>
class my_unique_ptr
{
    public:
        my_unique_ptr(); //Default Constrctor
        ~my_unique_ptr(); //Destructor
        explicit my_unique_ptr(T *input); //Const with input value. ex) my_unique_ptr<int> uptr {new int{10}};
        my_unique_ptr(my_unique_ptr<T>&& rhs); //Move Constructor ex) my_unique_ptr<int> uptr {move(uptr2)}
        my_unique_ptr<T>& operator= (my_unique_ptr<T>&& rhs); //Move Assignment  ex) uptr = move(uptr2);
        my_unique_ptr(const my_unique_ptr<T>& rhs) = delete; //Copy Constructor  ex) my_unique_ptr<int> uptr { uptr2 };
        my_unique_ptr<T>& operator= (my_unique_ptr<T>& rhs) = delete; //Copy Assignment. ex) uptr = uptr2
        T& operator*() const; // if I dont have, *uptr <- cannot.
        T* operator->()const;
        bool isNullptr(); //to check it is nullptr in default
        void getInfo();
    private:
        T* my_ptr;
};

template<typename T>
class my_shared_ptr
{
    public:
        my_shared_ptr();//Default Constructor
        ~my_shared_ptr();//Destructor
        explicit my_shared_ptr(T *input);//my_shared_ptr with input. my_ptr points the value and +1 to counter
        my_shared_ptr(my_shared_ptr<T> & rhs);//copy Constructor
        my_shared_ptr(my_shared_ptr<T>&& rhs); //move constructor
        my_shared_ptr<T>& operator= (my_shared_ptr<T>&& rhs); //move assignment
        my_shared_ptr<T>& operator= (my_shared_ptr<T> &rhs);// Copy Assignment
        T& operator*() const;
        T* operator->()const;
        bool isNullptr();
        void getInfo();
    private:
        SptrCounter* my_sp_counter;
        T* my_ptr;
};
#include "my_memory.cpp"
#endif /* my_memory_hpp */
