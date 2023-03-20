#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main(){
    int x{7}; // equivalent to "int x = 7;"
    string s{"Hello World!"};

    cout << "x = " << x << endl;
    cout << "string s =\" " << s << "\""<< endl;

    // narrowing conversions are not allowed in cpp

    int y = 7.7; // will be truncated

    // int z{7.7}; 
    /* will produce the following: 
    sample1.cpp:16:14: error: narrowing conversion of 
    ‘7.7000000000000002e+0’ from ‘double’ to ‘int’ [-Wnarrowing]
    */

    cout << "y = " << y << endl;

    vector<int> v{4,2,3,5,6,1};
    string gdbye{'g', 'o', 'o', 'd', 'b', 'y', 'e'};

    cout << "v = ";
    for (vector<int>::iterator itr = v.begin(); itr!=v.end(); ++itr){
        cout << *itr << ", ";
    }
    cout << endl << "gdbye = \"" << gdbye << "\"" << endl;

    return 0;
}