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
