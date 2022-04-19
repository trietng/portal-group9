#include "course.h"

cqueue<fs::path> getSchoolyearPath() {
    cqueue<fs::path> list;
    for (auto const& dir : fs::directory_iterator{"data\\Courses"}) {
        if (dir.is_directory()) {
            list.push_back(dir.path());
        }
    }
    return list;
}

cqueue<schoolyear> genSchoolyearList(const cqueue<fs::path>& path) {
    cqueue<schoolyear> list;
    string word;
    for (auto i = path.cbegin(); i != nullptr ; i++) {
        schoolyear sy;
        ifstream fin;
        sy.folder_path = (*i).string();
        sy.folder_name = (*i).string().substr(pos_sy);
        fin.open((*i).string() + "\\date.txt");
        if (fin) {
            getline(fin, word);
            sy.start_date = to_date(word);
            getline(fin, word);
            sy.end_date = to_date(word);
            fin.close();
            list.push_back(sy);
        }
        else {
            cout << "ERROR: No date properties found in folder \"" << sy.folder_name << "\"\n";
        }
    }
    return list;
}

cqueue<fs::path> getSemesterPath(const schoolyear& sy) {
    cqueue<fs::path> list;
    for (auto const& dir : fs::directory_iterator{sy.folder_path}) {
        if (dir.is_directory()) {
            list.push_back(dir.path());
        }
    }
    return list;
}

/*cqueue<semester> genSemesterList(const cqueue<fs::path>& path) {
    cqueue<semester> list;
    string word;
    for (auto i = path.cbegin(); i != nullptr ; i++) {
        semester sm;
        ifstream fin;
        sm.folder_path = (*i).string();
        sm.folder_name = (*i).string().substr(pos_sy);
        fin.open((*i).string() + "\\date.txt");
        if (fin) {
            getline(fin, word);
            sm.start_date = to_date(word);
            getline(fin, word);
            sm.end_date = to_date(word);
            fin.close();
            list.push_back(sm);
        }
        else {
            cout << "ERROR: No date properties found in folder \"" << sm.folder_name << "\"\n";
        }
    }
    return list;
}*/

bool isBeginning(const date& d0, const cqueue<fs::path>& sy_path) {
    string year = "data\\Courses\\" + to_string(d0.year) + "-" + to_string(d0.year + 1);
    for (auto i = sy_path.cbegin(); i != nullptr; ++i) {
        if ((*i).string() == year) {
            return true;
        }
    }
    return false;
}

void createDateProperties(const string& folder_path, const date& start, const date& end) {
    ofstream fout;
    fout.open(folder_path + "\\date.txt");
    outputdate(start, fout);
    fout << "\n";
    outputdate(end, fout);
}

bool can_enroll_course(date& today,date& start_day, date& end_day){
    if (comp_date(today,start_day) >= 0 && comp_date(today,end_day) <= 0) return true;
    return false;
}

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

schoolyear createNewSchoolyear(const date& today) {
    /*Issues need to be resolved: Find the first Monday of a term,
    set that day as the starting date. Find exactly 13 weeks 
    after that to set it as the ending date.
    */
    schoolyear sy0;
    string sy_name = to_string(today.year) + "-" + to_string(today.year + 1);
    string dir_path = "data\\Courses\\" + sy_name;
    fs::create_directories(dir_path);
    date start = set_date(5, 9, today.year), end = set_date(11, 7, today.year + 1);
    createDateProperties(dir_path, start, end);
    sy0.start_date = start;
    sy0.end_date = end;
    sy0.folder_name = sy_name;
    sy0.folder_path = dir_path;
    /*
    //Term 1
    fs::create_directory(dir_path + "\\Term 1");
    start = set_date(5, 9, today.year);
    end = set_date(31, 12, today.year);
    createDateProperties(dir_path + "\\Term 1", start, end);
    //Term 2
    fs::create_directory(dir_path + "\\Term 2");
    start = set_date(14, 1, today.year + 1);
    end = set_date(31, 3, today.year + 1);
    createDateProperties(dir_path + "\\Term 2", start, end);
    //Term 3
    fs::create_directory(dir_path + "\\Term 3");
    start = set_date(14, 2, today.year + 1);
    end = set_date(11, 7, today.year + 1);
    createDateProperties(dir_path + "\\Term 3", start, end);*/
    return sy0;
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