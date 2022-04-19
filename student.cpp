#include "student.h"

void importUniclass() {
    ifstream fin;
    string line, word, class_name, class_path;
    int max_student = 0;
    fin.open("import/classes.csv");
    if (fin) {
        while (getline(fin, line)) {
            stringstream ss(line);
            getline(ss, class_name, ';');
            class_path = "data/People/Students/" + class_name;
            fs::create_directory(class_path);
            getline(ss, word, ';');
            max_student = to_int(word);
            ofstream fout(class_path + "/max_student.txt");
            fout << max_student;
            fout.close();
        }
        fin.close();
    }
    else {
        cout << "ERROR: \"import/classes.csv\" does not exist";
    }
}

void importStudent() {
    ifstream fin;
    string line, class_name, student_id;
    int max_student = 0;
    fin.open("import/students.csv");
    if (fin) {
        while (getline(fin, line)) {
            stringstream ss(line);
            getline(ss, class_name, ';');
            getline(ss, student_id, ';');
            ofstream fout("/data/People/Students/" + class_name + "/" + student_id + ".csv");
            fout << line;
        }
    }
    else {
        cout << "ERROR: \"import/students.csv\" does not exist";
    }
}

student* loadProfileStudent(account* acc){
    student* std= new student;
    std->student_path = acc->profile_path;
    ifstream fin(std->student_path);
    if (fin){
        getline(fin,std->name,';');
        getline(fin,std->class_name,';');
    }
    return nullptr;
}