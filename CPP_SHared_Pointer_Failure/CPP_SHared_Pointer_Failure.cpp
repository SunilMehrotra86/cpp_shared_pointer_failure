// CPP_SHared_Pointer_Failure.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <memory>

using namespace std;


class anyStuff
{
public:
    anyStuff(int data) :m_Data() {}
    ~anyStuff()=default;
    void setData(int& val) { m_Data = val; }
    private:
    int m_Data;
};


int main()
{
    anyStuff* rawPtrToAnyStuff = new anyStuff(100); //Let's create a raw pointer to teh class anyStuff.
    shared_ptr<anyStuff> shrdPtr1(rawPtrToAnyStuff);  
    shared_ptr<anyStuff> shrdPtr2(rawPtrToAnyStuff);
    cout << "Shared Count of shrdPtr1 is " << shrdPtr1.use_count()<<endl;
    cout << "Shared Count of shrdPtr2 is " << shrdPtr2.use_count() << endl;

 
    return 0;
}
/*
* The output of above program shall be as shown below:
Shared Count of shrdPtr1 is 1
Shared Count of shrdPtr2 is 1
You can see there are two shared pointers pointing to the same resource(which is ok ) but the reference count maintained by them is 1 only(whih is wrong).

Reason behind it is that whenever a shared poiner is assigned from a raw pointer a control block is initialized for teh shared pointer. Each time for bpth the
shaed pointers a separate control block is created (again which is wrong), this means two separate counts will be maintained for each pointer.

Conclusion: Avoid creating shared pointers from raw pointers directly , either use make_shared or directly pass the output of new to avoid two different counts 
for teh same resource.
 
*/