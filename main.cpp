#include "stringlistclass.h"

using namespace std;
int main(){
    String_List a;
    a.push_back("i'm good");
    a.push_back("\nand, you?");
    cout<<a.to_string();
}