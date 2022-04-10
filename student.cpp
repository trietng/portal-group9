#include "student.h"

cqueue<fs::path> getUniclassPath() {
    cqueue<fs::path> list;
    for (auto const& dir : fs::directory_iterator{"data\\People\\Students"}) {
        if (dir.is_directory()) {
            list.push_back(dir.path());
        }
    }
    return list;
}
cqueue<uniclass> genUniclassList(const cqueue<fs::path>& path) {
    cqueue<uniclass> list;
    string word;
    for (auto i = path.cbegin(); i != nullptr ; i++) {
        uniclass uc;
        ifstream fin;
        uc.class_path = (*i).string();
        uc.class_name = (*i).filename().string();
        fin.open((*i).string() + "\\max_student.txt");
        if (fin) {
            fin >> uc.max_student;
        }
        else {
            uc.max_student = 0;
            cout << "ERROR: No max_student properties found in folder \"" << uc.class_path << "\"\n";
        }
        fin.close();
    }
    return list;
}

cqueue<fs::path> getStudentPath(const uniclass& uc) {
    cqueue<fs::path> list;
    for (auto const& dir : fs::directory_iterator{uc.class_path}) {
        if (dir.path().filename().string() != "max_student.txt") {
            list.push_back(dir.path());
        }
    }
    return list;
}

cqueue<student> genStudentList(const cqueue<fs::path>& path) {
    cqueue<student> list;
    string word;
    for (auto i = path.cbegin(); i != nullptr ; i++) {
        student sd;
        ifstream fin;
        sd.student_path = (*i).string();
        sd.student_id = to_int((*i).filename().string().substr(0, 9));
        fin.open(sd.student_path);
        if (fin) {
            //read student data here 
            fin.close();
        }
    }
    return list;
}

void importUniclass(cqueue<fs::path>& uc_path, cqueue<uniclass>& uc) {
    ifstream fin;
    string line, word, class_name, class_path;
    int max_student = 0;
    fin.open("import\\classes.csv");
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
            fout.close();
        }
        fin.close();
    }
}