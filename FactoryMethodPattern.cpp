#include <iostream>
#include <string>
using namespace std;

class Item{
 
  public: 
    string name;
    virtual void displayName()=0;   
  
};

class Mobile: public Item{
    public:
    Mobile(string name){
        this->name = name;
    }
    void displayName(){
        cout<<name;
    }
    
};

class Factory{
    
    public:
    
    Item* factoryMethod(int p){
        if(p == 1)
        {
            return new Mobile("Iphone");
        }
    }
};


int main()
{
    cout<<"Hello World";
    Factory f;
    Item *i = f.factoryMethod(1);
    i->displayName();
    
    return 0;
}
