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
    void save(const std::string &filename)
    {
        std::ofstream ofs{filename, std::ofstream::out};
        for (auto &item : entries)
            ofs << item;
        ofs.close();
    }
};
int main()
{
    // getchar();
    Journal myJournal{"Kells"};
    myJournal.add("Did something");
    myJournal.add("Did something else");
    for (std::string &str : myJournal.entries)
        std::cout << str << std::endl;
    myJournal.save("SavedJournal");
    return 0;
}