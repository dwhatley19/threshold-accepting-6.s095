#include <fstream>
#include <iostream>
using namespace std;

int main(int argc, char **argv)
{
    if(argc != 3) {
        cout << "wrong arguments\n";
        return 0;
    }
    ifstream fin(argv[1]);
    ofstream fout(argv[2]);
    double num;
    fin >> num;

    fout << "unitsize(0.001cm);\n";
    fout << "// " << num << "\n";

    string s[20000];
    int i = 0;
    while(fin >> s[i]) {
        if(i > 0) fout << "draw(" << s[i - 1] << "--" << s[i] << ");\n";
        i++;
    }

    fout << "draw(" << s[i - 1] << "--" << s[0] << ");\n";
}
