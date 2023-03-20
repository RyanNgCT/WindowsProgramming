#include <iostream>

using namespace std;

// overloas the method
void testFunc(int i){
    cout << "testFunc with param int i called" << endl;
}

void testFunct(int *i){
    cout << "testFunc with param int *i (integer ptr) called" << endl;
}

int main(){
    //testFunc(NULL);
    //testFunc(nullptr);

    int testInt = 5;
    int *testIntPtr = &testInt;

    testFunc(*testIntPtr);
}