#ifndef CSV_HPP
#define CSV_HPP

#include <vector>
#include <iostream>
#include <string>

class Csv {
    private:
        std::vector<std::vector<std::string> > tab;
        std::string fillCell(std::string &cell);
        bool isOp(char c);
        std::string getCell(std::string &arg);
        bool checkSize();
    public:
        Csv();
        void read(const std::string& filename);
        void show();
        void write(const std::string& filename = "out.csv");
        void checkTable();
        ~Csv();
};

#endif
