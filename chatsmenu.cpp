#include <iostream>
using namespace std;

class student  {
    private:
        int age;
        string name;
    public:
        student(int g, string n) {
            age=g ;
            name=n ;
        }

        void setage(int g) {
            age=g ;
        }
    void setname(string n) {
            name=n ;
        }
    int getage( ) {
            return age ;
        }
     string getname() {
            return name ;
        }
};

int main() {
    student mohamed(20 , "sami ")
    cout<<mohamed.getname()<<endl;
    cout<<mohamed.getage()<<endl;
    mohamed.setage(20);


    return 0;
}
