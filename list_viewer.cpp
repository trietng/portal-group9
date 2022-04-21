#include "list_viewer.h"

void viewListOfClasses() {
    string k;
    cout << "Enter students' year (e.g K01, K20, ...): ";
    getline(cin, k);
    k = k.substr(1, 2);
    bool found = false;
    for (auto const& dir : fs::directory_iterator{"data/People/Students"}) {
        if (dir.is_directory() && (dir.path().filename().string().substr(0, 2) == k)) {
            cout << dir.path().filename().string() << "\n";
            found = true;
        }
    }
    if (!found) cout << "No classes of K" << k << " in database.";
}

void displayStudentInfoInClass(const student& student, const int& i) {
    cout << "\n" << i << string_equalizer(countdigits(i), 4, ' ');
    cout << student.student_id << string_equalizer(countdigits(student.student_id), 11, ' ');
    cout << student.name << string_equalizer(student.name.length(), 32, ' ') << " ";
    cout << string_cast(student.gender) << string_equalizer(string_cast(student.gender).length(), 7, ' ');
    outputdate(student.dob, false);
}

void displayStudentInfoInCourse(const student& student, const int& i) {
    cout << "\n" << i << string_equalizer(countdigits(i), 4, ' ');
    cout << student.student_id << string_equalizer(countdigits(student.student_id), 11, ' ');
    cout << student.name << string_equalizer(student.name.length(), 32, ' ') << " ";
    cout << string_cast(student.gender) << string_equalizer(string_cast(student.gender).length(), 7, ' ');
    outputdate(student.dob, false);
    cout << string_equalizer(string_cast(student.dob).substr(7).length(), 16, ' ') << student.class_name;
}

void viewListOfStudentsInClass() {
    cout << "Enter class: ";
    string class_name;
    int i = 0;
    getline(cin, class_name);
    fs::path class_path("data/People/Students/" + class_name);
    if (!fs::exists(class_path)) {
        cout << "No class named " << class_name << ".";
    }
    else {
        cout << "No  Student ID Name                             Gender Date of birth";
        for (auto const& dir : fs::directory_iterator{class_path}) {
            if (dir.path().extension().string() == ".csv") {
                ifstream fin(dir.path().string());
                if (fin) {
                    string info, word;
                    getline(fin, info);
                    stringstream ss(info);
                    student student;
                    student.student_id = stoi(dir.path().filename().string().substr(0, 9));
                    getline(ss, word, ';');
                    getline(ss, student.name, ';');
                    getline(ss, word, ';');
                    student.gender = to_gender(stoi(word));
                    getline(ss, word, ';');
                    student.dob = to_date(word);
                    displayStudentInfoInClass(student, i + 1);
                    fin.close();
                }
                ++i;
            }
        }
    }
}

void viewListOfStudentsInCourse() {
    string course_id;
    cout << "Enter course ID: ";
    getline(cin, course_id);
    ifstream fin(getWorkingDirectory(getStatus()) + "/" + course_id + ".csv");
    cout << course_id << "\nNo  Student ID Name                             Gender Date of birth Class";
    if (fin) {
        string student_path;
        getline(fin, student_path);
        int no = 0;
        while (getline(fin, student_path)) {
            ifstream is(student_path);
            student student;
            student.social_id = "";
            student.student_path = "";
            student.student_id = stoi(fs::path(student_path).filename().string().substr(0, 9));
            if (is) {
                string info, word;
                getline(is, info);
                stringstream ss(info);
                getline(ss, student.class_name, ';');
                getline(ss, student.name, ';');
                getline(ss, word, ';');
                student.gender = to_gender(stoi(word));
                getline(ss, word, ';');
                student.dob = to_date(word);
                is.close();
            }
            displayStudentInfoInCourse(student, no + 1);
            ++no;
        }
    }
    fin.close();
}