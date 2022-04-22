#include "course.h"

void displayCourseInfo(cqueue<course>& course_list) {
    cout << setw(13) << left <<  "Course ID";
    cout << setw(40) << left <<"Course's name";
    cout << setw(8) << left <<"Credits";
    cout << setw(15) << left << "Semester";
    cout << setw(15) << left << "Sessions";
    cout << setw(25) << right << "Lecturer\n";
    cout << setfill('-');	
	cout << setw(116) << "-" << endl;	
	cout << setfill(' ');
    for (auto i = course_list.begin(); i != nullptr; ++i) {
            cout << setw(13) << left << (*i).course_id;
            cout << setw(40) << left << (*i).course_name;
            cout << setw(8) << left << (*i).credits;
            cout << setw(1) << left << (*i).semester << setw(1) << left << "/" << setw(13) << left << (*i).schoolyear;
            cout << setw(15) << left << (*i).session;
            cout << setw(25) << right << (*i).lecturer_name;
        cout << "\n";
    }
}

cqueue<course> listOfCourse(status& stt, cqueue<course>& enrolled_course){
    string word,line;
    course temp;
    cqueue<course> course_list;
    ifstream fin(getWorkingDirectory(stt) + "/MANAGEMENT.csv");
    if (fin){
        getline(fin,line);
        while(getline(fin,line)){
            stringstream ss(line);
            getline(ss,temp.schoolyear,';');
            getline(ss,word,';');
            temp.semester = stoi(word);
            getline(ss,temp.course_id,';');
            getline(ss,temp.course_name,';');
            getline(ss,temp.lecturer_name,';');
            getline(ss,temp.start_date,';');
            getline(ss,temp.end_date,';');
            getline(ss,temp.session,';');
            getline(ss,word,';');
            temp.credits = stoi(word);
            getline(ss,word,';');
            temp.max_num_student = stoi(word);
            if (validForEnroll(enrolled_course,temp.course_id)) course_list.push_back(temp);
        }
    }
    return course_list;
}

bool is_conflict_session(course* x,cqueue<course>& list) {
    for (auto i = list.begin(); i != nullptr; ++i){
        if (x->session == (*i).session && x->schoolyear != (*i).schoolyear && x->semester != (*i).semester) return true;
    }
    return false;
}

course* findCourse(string& str,cqueue<course>& list){
    for (auto i = list.begin(); i != nullptr; ++i){
        if (str == (*i).course_id) return &(*i);
    }
    return nullptr;
}

void deleteCourse(student*& user,string& ID,status& stt,cqueue<course>& enrolled_course){
    cqueue <string> list;
    string str = getWorkingDirectory(stt) + "/"+ ID +".csv";
    string line,word;
    ifstream fin(str);
    if (fin){
        getline(fin,line);
        while (getline(fin,word)){
            if (user->student_path !=  word) list.push_back(word);
        }
    }
    fin.close();
    ofstream fout(str);
    if (fout){
        fout << line;
        for (auto i = list.begin();i != nullptr; ++ i){
            if (i == list.begin()) fout << endl;
            fout << (*i);
            if (i != list.end()) fout << endl;
        }
    }
    fout.close();
    fin.open(user->student_path);
    cqueue <string> list1;
    if (fin){
        getline(fin, line);
        while (getline(fin,word)){
            if (str != word) list1.push_back(word);
        }
    }
    fin.close();
    fout.open(user->student_path);
    if (fout){
        fout << line;
        for (auto i = list1.begin(); i != nullptr; ++i){
            if (i == list.begin()) fout << endl;
            fout << (*i);
            if (i != list1.end()) fout << endl;
        }
    }
    fout.close();
    removeCourseToList(ID,enrolled_course);
}

void addCourseToList(string& ID,cqueue<course>& enrolled_course,cqueue<course>& course_list){
    for (auto i = course_list.begin(); i != nullptr ; ++i){
        if ((*i).course_id == ID) enrolled_course.push_back(*i);
        break;
    }
}

void removeCourseToList(string& ID,cqueue<course>& course_list){
    for (auto i = course_list.begin(); i != nullptr ; ++i){
        if ((*i).course_id == ID) course_list.erase_cur(i);
        break;
    }
}

cqueue<course> listOfEnrolledCourse(student*& user,status& stt) {
    string word,line,line1;
    course temp;
    cqueue<course> enroll_course;
    ifstream fin(user->student_path);
    if (fin){
        getline(fin,line);
        while(getline(fin,line)){
            ifstream in(line);
            if (in){
                getline(in,line1);
                stringstream ss(line1);
                getline(ss,temp.schoolyear,';');
                getline(ss,word,';');
                temp.semester = stoi(word);
                getline(ss,temp.course_id,';');
                getline(ss,temp.course_name,';');
                getline(ss,temp.lecturer_name,';');
                getline(ss,temp.start_date,';');
                getline(ss,temp.end_date,';');
                getline(ss,temp.session,';');
                getline(ss,word,';');
                temp.credits = stoi(word);
                getline(ss,word,';');
                temp.max_num_student = stoi(word);
                enroll_course.push_back(temp);
            }
            in.close();
        }
    }
    fin.close();
        return enroll_course;
}


bool validForEnroll(cqueue<course>& enrolled_course, string words){
    for (auto i =enrolled_course.begin(); i != nullptr ; ++i){
        if ((*i).course_id == words) return false;
    }
    return true;
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

void write2File1(const std::string& path, const std::string& str) {
    ofstream fout(path, ios ::app);
    fout << endl;
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