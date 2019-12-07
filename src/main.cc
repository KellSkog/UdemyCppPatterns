#include <iostream>
#include <stdio.h> //getchar
#include <string>
#include <vector>
#include <fstream>

struct Journal
{
    std::string title;
    std::vector<std::string> entries;

    Journal(const std::string &title) : title{title} {} //Ctor pledges not to change what title referes to

    void add(const std::string &entry)
    {
        static int count = 0;
        entries.push_back(std::to_string(count++) + " " + entry);
    }
    //Do the wrong thing, add additional concern: persistance
    //This results in having to maintain persistence individually for each class with persistance
    void save(const std::string &filename)
    {
        std::ofstream ofs{filename, std::ofstream::out};
        for (auto &item : entries)
            ofs << item << std::endl;
        ofs.close();
    }
};
//Implementing the behavior of persistant storage as a free function retains Single Responsibility of Journal
template <typename T>
void save(T t, const std::string &filename)
{
    std::ofstream ofs{filename, std::ofstream::out};
    for (auto &item : t.entries)
        ofs << item << std::endl;
    ofs.close();
}
void doJournal()
{
    Journal myJournal{"Kells"};
    myJournal.add("Did something");
    myJournal.add("Did something else");
    for (std::string &str : myJournal.entries)
        std::cout << str << std::endl;
    myJournal.save("SavedJournal");
    save(myJournal, "SavedBetter");
}

struct Product //I hate this format but don't know how to change it :-c
{
    enum Color
    {
        Red,
        Yellow,
        Green
    };
    enum Size
    {
        Small,
        Medium,
        Large
    };
    std::string name;
    Color color;
    Size size;
};
/**
 * This filter works fine but violates the open-closed principle in that to add a new filter criteria
 * ProductFilter has to be changed, thus not closed for modification.
 * It would be better if it could be extended insted of changed!
 * A solution can be to use the Specification pattern: https://martinfowler.com/apsupp/spec.pdf
 */
struct ProductFilter
{
    std::vector<Product *> by_color(std::vector<Product *> items, Product::Color col)
    {
        std::vector<Product *> result;
        for (auto &item : items)
        {
            if (item->color == col)
                result.push_back(item);
        }
        return result;
    }
};
/**
 * The Specialization approach, use a predicate which returns true if the filter criteria is satisfied
 */
template <typename T>
struct Specification
{
    virtual bool isSatisfied(T *item) = 0; //=0 makes it abstract, to be abstract it has to be virtual, it is an interface!
};
template <typename T>
struct Filter
{
    virtual std::vector<T *> filter(std::vector<T *> items, Specification<T> &spec) = 0;
};
struct BetterFilter : Filter<Product> {
    std::vector<Product *> filter(std::vector<Product*> items, Specification<Product> &spec) override {
        std::vector<Product*> result;
        for(auto &item : items) {
            if(spec.isSatisfied(item))
                result.push_back(item);
        }
        return result;
    }
};

void testProduct() {
    Product apple{"Apple", Product::Red, Product::Small};
    Product orange{"Orange", Product::Yellow, Product::Medium};
    Product mellon{"Mellon", Product::Green, Product::Small};
    std::vector<Product *> products{&apple, &orange, &mellon};
    ProductFilter pf;
    std::vector<Product *> yellows = ProductFilter{}.by_color(products, Product::Yellow);
    for (auto &yellow : yellows)
        std::cout << yellow->name << std::endl;
}
void testFilter() {
    Product apple{"Apple", Product::Red, Product::Small};
    Product orange{"Orange", Product::Yellow, Product::Medium};
    Product mellon{"Mellon", Product::Green, Product::Small};
    Specification redSmall<>{Product::Red, Product::Small};
}
int main()
{
    // getchar();
    //doJournal();
    //testProduct();
    return 0;
}