#include "student.h"

gender to_gender(const std::string& str) {
    return (str == "male") ? male : ((str == "female") ? female : other);
}

gender to_gender(const long long& num) {
    return (num == 0) ? male : ((num == 1) ? female : other);
}

std::string string_cast(const gender& gender) {
    return (gender == male) ? "male" : ((gender == female) ? "female" : "other");
}

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
            max_student = stoi(word);
            ofstream fout(class_path + "/max_student.txt");
            fout << max_student;
            fout.close();
        }
        fin.close();
        cout << "File \"import/classes.csv\" imported";
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
            ofstream fout;
            string student_path = "data/People/Students/" + class_name + "/" + student_id + ".csv";
            fout.open(student_path);
            fout << line;
            fout.close();
            fout.open("data/userdb.csv", ios::app);
            fout << "\n" << student_id << ";" << student_id << ";" << "1;" << student_path;
            fout.close();
        }
        cout << "File \"import/students.csv\" imported";
    }
    else {
        cout << "ERROR: \"import/students.csv\" does not exist";
    }
}

student* loadProfileStudent(account*& acc){
    student* stdent= new student;
    string str;
    stdent->student_path = acc->profile_path;
    ifstream fin(stdent->student_path);
    if (fin){
        getline(fin,stdent->class_name,';');
        getline(fin,stdent->name,';');
        getline(fin,stdent->name,';');
        getline(fin,str,';');
        stdent->dob = to_date(str);
        getline(fin,stdent->social_id,';');
    }
    fin.close();
    return stdent;
}