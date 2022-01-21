#include <iostream>
#include <cstddef>
#include <fstream>
#include <queue>

using namespace std;


void read_lines(ifstream& file, bool top, size_t cnt) {
    deque<string> q;
    string str;
    while (getline(file, str)) {
        q.push_back(str);
        if (q.size() == cnt) {
            if (top) {
                break;
            } else {
                q.pop_front();
            }
        }
    }
    for (auto const& it : q) {
        cout << it << '\n';
    }
}

void read_lines(size_t cnt) {
    string str;
    while (getline(cin, str)) {
        cout << str << '\n';
        if (--cnt == 0) {
            break;
        }
    }
}


void read_bytes(ifstream& file, bool top, size_t cnt) {
    deque<char> q;
    string str;
    while (getline(file, str)) {
        bool break_mark = false;
        for (char ch : str) {
            q.push_back(ch);
            if (q.size() == cnt) {
                if (top) {
                    break_mark = true;
                    break;
                } else {
                    q.pop_front();
                }
            }
        }
        q.push_back('\n');
        if (q.size() == cnt) {
            if (top) {
                break_mark = true;
            } else {
                q.pop_front();
            }
        }
        if (break_mark == true) {
            break;
        }
    }
    for (auto const& it : q) {
        cout << it;
    }
}

void read_bytes(size_t cnt) {
    string str;
    while (getline(cin, str)) {
        bool break_mark = false;
        for (char ch : str) {
            cout << ch;
            if (--cnt == 0) {
                break_mark = true;
                break;
            }
        }
        cout << '\n';
        if (--cnt == 0) {
            break_mark = true;
        }
        if (break_mark == true) {
            break;
        }
    }
}


int main(int argc, char* argv[]) {
    if (argc == 1 || (argc > 1 && !(static_cast<string>(argv[1]) == "head" || static_cast<string>(argv[1]) == "tail"))) {
        cerr << "USAGE head/tail [OPTION]... [FILE]...";
        return 1;
    }

    bool top = (static_cast<string>(argv[1]) == "head") ? true : false;
    string mode = (top == true ? "head" : "tail");
    bool lines = true;
    bool silence = false;
    int32_t cnt = 10;

    vector<string> files;
    for (size_t i = 2; i != argc; ++i) {
        string token = static_cast<string>(argv[i]);
        if (token == "-q") {
            silence = true;
        }
        else if (token == "-v") {
            silence = false;
        } 
        else if (token == "-c") {
            if (i + 1 > argc) {
                cerr << mode << ": option requires an argument -- 'c'";
                return 1;
            }
            lines = false;
            
            try {
                cnt = stoi(static_cast<string>(argv[i + 1]));
            } catch (...) {
                cerr << mode << ": invalid number of bytes: " << argv[i + 1];
                return 1;
            }

            if (cnt < 0) {
                cnt *= -1;
                top ^= 1;
            }

            ++i;
        }
        else if (token == "-n") {
            if (i + 1 > argc) {
                cerr << mode << ": option requires an argument -- 'c'";
                return 1;
            }
            lines = true;
            
            int32_t suffix = 1;
            string value = argv[i + 1];
            
            switch (value.back()) {
                case 'b':
                    suffix = 512;
                    value.pop_back();
                    break;
                case 'k':
                    suffix = 1024;
                    value.pop_back();
                    break;
                case 'm':
                    suffix = 1024 * 1024;
                    value.pop_back();
                    break;
            }

            try {
                cnt = stoi(static_cast<string>(argv[i + 1]));
                cnt *= suffix;
            } catch (...) {
                cerr << mode << ": invalid number of lines: " << argv[i + 1];
                return 1;
            }

            if (cnt < 0) {
                cnt *= -1;
                top ^= 1;
            }
            
            ++i;
        }
        else {
            files.push_back(token);
        }
    }

    if (files.empty() && mode == "head") {
        if (lines == true) {
            read_lines(cnt);
        } else {
            read_bytes(cnt);
        }
        return 0;
    }

    for (string filename : files) {
        ifstream file(filename);

        if (file.fail()) {
            cerr << mode << ": cannot open '" << filename << "' for reading: No such file or directory\n";
            continue;
        }

        if (!silence) {
            cout << "==> " << filename << " <==\n";
        }

        if (lines == true) {
            read_lines(file, top, cnt);
        } else {
            read_bytes(file, top, cnt);
        }
    }
}
