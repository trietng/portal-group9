#include "student.h"

void importUniclass(cqueue<fs::path>& uc_path, cqueue<uniclass>& uc) {
    ifstream fin;
    string line, word, class_name, class_path;
    int max_student = 0;
    fin.open("\\import\\classes.csv");
    if (fin) {
        while (getline(fin, line)) {
            stringstream ss(line);
            getline(ss, class_name, ';');
            class_path = "data\\People\\Students\\" + class_name;
            fs::create_directory(class_path);
            uniclass uc_tmp;
            uc_tmp.class_name = class_name;
            uc_tmp.class_path = class_path;
            getline(ss, word, ';');
            max_student = to_int(word);
            ofstream fout;
            fout.open(class_path + "\\max_student.txt");
            fout << max_student;
            uc_tmp.max_student = max_student;
            uc.push_back(uc_tmp);
        }
        fin.close();
    }
}