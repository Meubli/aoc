#include <cassert>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

int part_one(const char* filename)
{
    // Open the text file named "input.txt"
    ifstream f(filename);

    // Check if the file is successfully opened
    if (!f.is_open()) {
        cerr << "Error opening the file: " << filename << endl;
        return 1;
    }

    // String variable to store the read data
    string s;

    // Read each line of the file and print it to the
    // standard output stream till the whole file is
    // completely read
    while (getline(f, s)) {
        cout << s << endl;
    }

    // Close the file
    f.close();
    return 0;
}

int main(int argc, char* argv[])
{
    assert(part_one("../input_1_demo.txt") == 143);
    cout << part_one("../input_1.txt") << endl;
    return 0;
}
