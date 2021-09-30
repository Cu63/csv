#include "../headers/csv.hpp"

int main(int argc, char* argv[]) {
    Csv table;
    if (argc < 2) {
        std::cout << argv[0] << "<file_name.csv>\n";
        return 1;
    }

    table.read(argv[1]);
    std::cout << "Before:\n";
    table.show();
    table.checkTable();
    std::cout << "After:\n";
    table.show();
    table.write();
    return 0;
}
