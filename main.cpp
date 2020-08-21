#include<iostream>
#include"my_memory.hpp"

using namespace std;


void CheckDefaultConstr()
{
   my_shared_ptr<double> p1;

   if (p1.isNullptr())
       cout << "Deafault constructor...   OK\n";
   else
       cout << "ERROR: default constructor doesn't initialize to nullptr !!!\n";
}

void CheckPointerConstr()
{
   my_shared_ptr<short> p1{ new short{7} };

   if(*p1==7)
       cout << "Pointer constructor...   OK\n";
   else
       cout << "ERROR: pointer constructor (or dereference operator) is faulty !!!\n";
}

void CheckCopyConstr()
{
   my_shared_ptr<int> p1{ new int{4} };
   my_shared_ptr<int> p2{ p1 };
   if (*p2 != 4)
       cout << "ERROR: copy constructor (or dereference operator) is faulty !!!\n";

   my_shared_ptr<int> p3{ p2 };
   my_shared_ptr<int> p4;
   my_shared_ptr<int> p5{ p4 };

   if (!p5.isNullptr())
       cout << "ERROR: copy constructor is faulty !!!\n";
 
   cout << "Copy constructor...   OK\n";
}

void CheckMoveConstr()
{
    my_unique_ptr<int> p1{ new int{4} };
    my_unique_ptr<int> p2{ move(p1) };

    if (*p2 != 4)
        cout << "ERROR: move constructor (or dereference operator) is faulty !!!\n";

    my_unique_ptr<int> p3;
    my_unique_ptr<int> p4{ move(p3) };

    if (!p4.isNullptr())
    	cout << "ERROR: move constructor is faulty !!!\n";
    
    cout << "Move constructor...   OK\n";
}

void CheckMemberAccess()
{
   struct S
   {
       int a{ 5 };
       int b{ 6 };
   };

   my_shared_ptr<S> p1{ new S };

   if(p1->a==5 and p1->b==6)
       cout << "Member access operator...   OK\n";
   else
       cout << "ERROR: member access operator is faulty !!!\n";
}

void CheckCopyAssignment()
{
   my_shared_ptr<int> p1{ new int{9} };
   my_shared_ptr<int> p2;

   p2 = p1;
   if (*p1 != 9 or *p2 != 9)
       cout << "ERROR: move constructor is faulty !!!\n";

	my_shared_ptr<int> p3{ new int{9} };
	my_shared_ptr<int> p4{ new int{2} };

	p4 = p3;
	if (*p3 != 9 or *p4 != 9)
	   cout << "ERROR: move constructor is faulty !!!\n";

	my_shared_ptr<int> p5{ new int{9} };
	my_shared_ptr<int> p6{ new int{2} };
	my_shared_ptr<int> p7{ p6 }, p8{ p6 };


	p6 = p5;
	if (*p5 != 9 or *p6 != 9 or *p7 != 2 or *p8 != 2)
	   cout << "ERROR: move constructor is faulty !!!\n";

	my_shared_ptr<int> p9;
	my_shared_ptr<int> p10;

	p10 = p9;

	struct S
	{
	   int val{ 2 };
	   my_shared_ptr<S> next;
	};

	my_shared_ptr<S> head{ new S };
	head->next = my_shared_ptr<S>{ new S };
	head->next->next = my_shared_ptr<S>{ new S };
	head = head->next;

    cout << "Copy assignment...   OK\n";
}


void CheckMoveAssignment()
{
	my_shared_ptr<int> p1{ new int{9} };
	my_shared_ptr<int> p2;

	p2 = move(p1);
	if (*p2 != 9)
	   cout << "ERROR: move constructor is faulty !!!\n";

	my_shared_ptr<int> p3{ new int{9} };
	my_shared_ptr<int> p4{ new int{2} };

	p4 = move(p3);
	if (*p4 != 9)
	   cout << "ERROR: move constructor is faulty !!!\n";

	my_shared_ptr<int> p5{ new int{9} };
	my_shared_ptr<int> p6{ new int{2} };
	my_shared_ptr<int> p7{ p6 }, p8{ p6 };


	p6 = move(p5);
	if (*p6 != 9)
	   cout << "ERROR: move constructor is faulty !!!\n";

	my_shared_ptr<int> p9;
	my_shared_ptr<int> p10;

	p10 = move(p9);

	struct S
	{
	   int val{ 4 };
	   my_shared_ptr<S> next;
	};

	my_shared_ptr<S> head{ new S };
	head->next = my_shared_ptr<S>{ new S };
	head->next->next = my_shared_ptr<S>{ new S };

	head = move(head->next);

    cout << "Move assignment...   OK\n";
}

int main()
{
   CheckDefaultConstr();
   CheckPointerConstr();
   CheckCopyConstr();
   CheckMoveConstr();
   CheckMemberAccess();
   CheckCopyAssignment();
   CheckMoveAssignment();

    return 0;
}
