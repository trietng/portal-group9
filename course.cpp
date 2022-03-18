#include "course.h"

cqueue<path> getSchoolyearPath() {
    cqueue<path> list;
    for (auto const& dir : directory_iterator{"data"}) {
        if (dir.is_directory()) {
            list.push_back(dir.path());
        }
    }
    return list;
}

cqueue<schoolyear> genSchoolyearList(const cqueue<path>& path) {
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

cqueue<path> getSemesterPath(const schoolyear& sy) {
    cqueue<path> list;
    for (auto const& dir : directory_iterator{sy.folder_path}) {
        if (dir.is_directory()) {
            list.push_back(dir.path());
        }
    }
    return list;
}

cqueue<semester> genSemesterList(const cqueue<path>& path) {
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
}

