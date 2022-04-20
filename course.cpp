#include "course.h"

void displayCourseInfo(cqueue<std::string>& course_path) {
    string line, word, course_id, course_name, lecturer;
    for (auto i = course_path.begin(); i != nullptr; ++i) {
        ofstream fout(*i);
        if (fout) {
            stringstream ss(line);
            getline(ss, word, ';');
            getline(ss, word, ';');
            getline(ss, course_id, ';');
            cout << "Course ID: " << course_id;
            getline(ss, course_name, ';');
            cout << "\nCourse name': " << course_name;
            getline(ss, lecturer, ';');
            cout << "\nLecturer: " << lecturer;
            cout << "\nCredits: ";
            cout << "\nSessions:";
            fout.close();
        }
        cout << "\n";
    }
}

cqueue<std::string> listOfEnrolledCourse(student* user) {
    string line, word;
    ifstream fin;
    cqueue<std::string> course_path;
    fin.open(user->student_path);
    if (fin) {
        getline(fin, line);
        while (getline(fin, line)) {
            stringstream ss(line);
            getline(ss, word, ';');
            course_path.push_back(word);
        }
    }
    return course_path;
}

bool createNewSchoolyear() {
    string schoolyear;
    cout << "Enter schoolyear: ";
    getline(cin, schoolyear);
    string path = "data/Courses/" + schoolyear;
    if (fs::is_directory(path)) {
        cout << "Schoolyear already existed";
        return false;
    }
    else {
        fs::create_directory(path);
        cout << "Schoolyear "  << schoolyear << " created";
    }
    return true;
}

/*
void exportCourseStudents(const string& course_id) {
    ofstream fout("data/Courses/");
}
*/

bool isRegistrable(const date& d0, const status& status) {
    return ((d0 >= status.start_registration) && (d0 <= status.end_registration)) ? true : false;
}

void write2File(const std::string& path, const std::string& str) {
    ofstream fout(path);
    fout << str;
    fout.close();
}

status getStatus() {
    ifstream fin(status_path);
    status s0;
    if (fin) {
        string line, word;
        getline(fin, line);
        stringstream ss(line);
        getline(ss, s0.schoolyear, ';');
        getline(ss, word, ';');
        s0.semester = stoi(word);
        getline(ss, word, ';');
        s0.start_registration = to_date("0/0/0/" + word);
        getline(ss, word, ';');
        s0.end_registration = to_date("0/0/0/" + word);
        fin.close();
    }
    return s0;
}

std::string getWorkingDirectory(const status& status) {
    return "data/Courses/" + status.schoolyear + "/Sem " + to_string(status.semester);
}

void exportStudentInfo2List(ofstream& fout, const student& student, const int& no) {
    fout << "\n" << no << ";" << student.student_id << ';' << student.name << ";";
    fout << string_cast(student.gender) << ";";
    fout << string_equalizer(countdigits(student.dob.day), 2, '0') << student.dob.day << "/"
    << string_equalizer(countdigits(student.dob.month), 2, '0') << student.dob.month << "/"
    << string_equalizer(countdigits(student.dob.year), 4, '0') << student.dob.year << ";";
    fout << student.class_name << ";";
}


void exportStudentsFromCourse(const std::string& course_id) {
    ifstream fin(getWorkingDirectory(getStatus()) + "/" + course_id + ".csv");
    ofstream fout("export/" + course_id + "_list.csv");
    fout << course_id << "\nNo;Student ID;Name;Gender;Date of birth;Class";
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
            exportStudentInfo2List(fout, student, no + 1);
            ++no;
        }
    }
    fin.close();
    fout.close();
}