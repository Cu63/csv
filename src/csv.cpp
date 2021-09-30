#include "../headers/csv.hpp"
#include <fstream>
#include <cctype>

Csv::Csv() {
}

void Csv::read(const std::string& filename) {
    std::ifstream in;
    std::string line;

    in.open(filename.c_str());
    if (!in.is_open()) {
        std::cout << "Can't open file: " << filename << std::endl;
        return;
    }
    //get pow of table
    while (std::getline(in, line)) {
        std::vector<std::string> row;
        int argBegin;
        int argEnd;

        argBegin = argEnd = 0;
        while (argEnd <= line.size()) {
            if (line[argEnd] == ',' || (argEnd == line.size())) {
                row.push_back(line.substr(argBegin, argEnd - argBegin));
                argBegin = argEnd + 1;
            }
            argEnd++;
        }
        tab.push_back(row);
    }
    in.close();
}

void Csv::show() {
    for (int i = 0; i < tab.size(); i++) {
        for (int j = 0; j < tab[i].size(); j++) {
            std::cout << std::setw(10) << tab[i][j] << "| ";
        }
        std::cout << std::endl;
    }
}

void Csv::write(const std::string &filename) {
    std::ofstream out;

    out.open(filename.c_str());
    if (!out.is_open()) {
        std::cout << "Can't open file: " << filename << std::endl;
        return;
    }
    for (int i = 0; i < tab.size(); i++) {
        for (int j = 0; j < tab[i].size(); j++) {
            out << tab[i][j];
            if (j != tab[i].size() - 1)
                out << ",";
        }
        out << std::endl;
    }
    out.close();
}

void Csv::checkTable() {
    //check some errors
    if (tab.empty()) {
        std::cout << "File is empty" << std::endl;
        return;
    }
    if (checkSize() == false) {
        std::cout << "Wrong size of table\n";
        return;
    }

    //check every cell to find expressions
    for (int i = 1; i < tab.size(); i++) {
        for (int j = 0; j < tab[i].size(); j++) {
            if (tab[i][j][0] == '=') {
                tab[i][j] = fillCell(tab[i][j]);
            }
        }
    }
}

//function solve expression and fill result in the cell
std::string Csv::fillCell(std::string &c) {
    std::string arg1;
    std::string arg2;
    char op;
    std::string res("?");

    //separate arg1, op and arg2
    for (int i = 1; i < c.size(); i++) {
        if (isOp(c[i]) == true) {
            arg1 = c.substr(1, i);
            arg2 = c.substr(i + 1, c.size());
            op = c[i];
            break;
        }
    }
    std::string a;
    std::string b;

    c = res;
    a = getCell(arg1);
    b = getCell(arg2);
//    std::cout << arg1 << ": " << a << " " << arg2<< ": " << b << std::endl;
    if (a == "?" || b == "?") {
        std::cout << "Incorrect parametr '" << arg1 << "' or '" 
            << arg2 << "'\n";
        return res;
    }
    switch (op) {
        case '+':
            res = std::to_string(std::stoi(a) + std::stoi(b));
            break;
        case '-':
            res = std::to_string(std::stoi(a) - std::stoi(b));
            break;
        case '*':
            res = std::to_string(std::stoi(a) * std::stoi(b));
            break;
        case '/':
            if (std::stoi(b) != 0)
                res = std::to_string(std::stoi(a) / std::stoi(b));
            else {
                std::cout << "Can't divide by zero in '=" << c << "'\n";
            }
            break;
    }
    return res;
}

//get value from cell using name of column and number of row
std::string Csv::getCell(std::string& arg) {
    std::string columnName;
    int columnNum;
    int rowNum;

    columnNum = rowNum = -1;
    for (int i = 0; i < arg.size(); i++) {
        if (std::isdigit(arg[i])) {
            columnName = arg.substr(0, i);
            for (int j = 0; j < tab[0].size(); j++) {
                if (columnName == tab[0][j]) {
                    columnNum = j;
                    break;
                }
            }
            rowNum = std::stoi(arg.substr(i, arg.size()).c_str());
            break;
        }
    }

    //if illegal value of arg return '?'
    if (rowNum < 0 || columnNum < 0) {
        std::cout << "Incorrect name of column or numbe of row '" 
            << arg << "'\n";
        return {"?"};
    }

    while (rowNum >= tab.size())
        rowNum = tab.size() - 1;

    if (tab[rowNum][columnNum][0] == '=')
        tab[rowNum][columnNum] = fillCell(tab[rowNum][columnNum]);
    return tab[rowNum][columnNum];
}

bool Csv::isOp(char c) {
    if (c == '+' || c == '-' || c == '*' || c == '/')
        return true;
    return false;
}

bool Csv::checkSize() {
    int size;

    size = tab[0].size();
    for (int i = 1; i < tab.size(); i++) {
        if (tab[i].size() != size)
            return false;
    }
    return true;
}

Csv::~Csv() {
}
