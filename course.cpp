#include "course.h"

cqueue<path> getLocalSchoolyear() {
    cqueue<path> list;
    for (auto const& dir : directory_iterator{"data"}) {
        list.push_back(dir.path());
    }
    return list;
}

cqueue<schoolyear> genSchoolyearList(const cqueue<path>& path) {
    cqueue<schoolyear> list;
    string word;
    for (auto i = path.cbegin(); i != nullptr ; i++) {
        schoolyear sy;
        ifstream fin;
        sy.name = (*i).string().substr(pos_sy);
        fin.open((*i).string() + "\\date");
        if (fin) {
            getline(fin, word);
            sy.start_date = to_date(word);
            getline(fin, word);
            sy.end_date = to_date(word);
            fin.close();
            list.push_back(sy);
        }
        else {
            cout << "ERROR: No date properties found in folder \"" << sy.name << "\"\n";
        }
        
    }
    return list;
}