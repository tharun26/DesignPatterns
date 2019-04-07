#include <stdio.h>
#include <iostream>
#include <vector>

enum class Color{Red, Green, Blue};
enum class Size{Small, Medium, Large};


class Product{
    public:
    std::string name;
    Color color;
    Size size;
    Product(std::string name, Color color, Size size){
        this->name = name;
        this->color = color;
        this->size = size;
    }
};


// Following class must be open for extension and close for modification
// It fails to address the problem
class ProductFilter{
    typedef std::vector<Product*> Items;
    
    public:
    static Items by_color(Items items, Color color)
    {
        Items result;
        std::vector<Product*>::iterator it;
        for(auto& i : items)
        {
            if(i->color == color)
            {
                result.push_back(i);
            }
        }
        return result;
    }
    
    static Items by_size(Items items, Size size)
    {
        Items result;
        for(auto& i : items)
        {
            if(i->size == size)
            {
                result.push_back(i);
            }
        }
        return result;
    }
    
    
    static Items by_Color_and_size(Items items,Color color, Size size)
    {
        Items result;
        for(auto& i : items)
        {
            if(i->size == size && i->color == color)
            {
                result.push_back(i);
            }
        }
        return result;
    }
    
};


//Specfication Pattern

template <typename T> class ISpecification
{
    public:
    virtual bool is_satisfied(T *item) = 0;
};

template <typename T> class IFilter
{
    public:
    virtual std::vector<T*> filter(std::vector<T*> items, ISpecification<T> &spec)=0;
};

class ColorSpecification: public ISpecification<Product>
{
    Color color;
    public:
    ColorSpecification(const Color color)
    {
        this->color = color;
    }
    
    bool is_satisfied(Product *item)
    {
        if(item->color == color)
        {
            return true;
        }
        return false;
    }
    
};


class BetterFIlter: public IFilter<Product>
{
    typedef std::vector<Product*> Items;
    public:
    std::vector<Product*> filter(std::vector<Product*> items, ISpecification<Product> &spec)
    {
        Items result;
        for(auto& p : items)
        {
            if(spec.is_satisfied(p))
            {
                result.push_back(p);
            }
        }
        return result;
    }
    
};


int main(int argc, char **argv)
{
	printf("hello world\n");
    
    Product apple("Apple", Color::Green, Size::Small);
    Product tree("Tree", Color::Green, Size::Large);
    Product house("House", Color::Blue, Size::Large);

    std::vector<Product*> all {&apple,&tree,&house};

    BetterFIlter bf;
    ColorSpecification green(Color::Green);

    auto green_things = bf.filter(all,green);
    for(auto &a: green_things){
        std::cout<<a->name<<endl;
        
    }
    getchar();
	return 0;
}
