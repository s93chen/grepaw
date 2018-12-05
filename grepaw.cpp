#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <sys/stat.h>
#include <dirent.h>
#include "colours.h"

using namespace std;


/* get top level entries of given dir and add
 * to vector of entries 
 */

bool getDirEntries(vector<string> &entries, const string &path)
{
    DIR *dir = opendir(path.c_str());

    if (!dir) {
        perror("opendir");
        return false;
    }

    struct dirent *dirEntry;
    while ((dirEntry = readdir(dir))) {
        string entName = dirEntry->d_name;
        if (entName != "." && entName != "..")
            entries.push_back(entName); 
    }
    
    closedir(dir);
    return true;      
}


/* highlights all matched patterns in line */

void searchLine(const string &line, const string &pattern, int lnum)
{
    int start = 0;
    int p_len = pattern.length();
    size_t posn = line.find(pattern);

    bool found = false;

    while (posn != string::npos) {

        if (start == 0)
            cout << YELLOW << lnum << "\t" << RESET;

        cout << line.substr(start, posn - start);
        cout << CYAN << pattern << RESET;

        start = posn + p_len;
        posn = line.find(pattern, start);

        found = true;
    }

    if (found) {
        cout << line.substr(start);
        cout << endl;
    }
}

/* Search each line in file for pattern.
 * Returns true on success and false on error. */

bool searchStream(const string &pattern, istream &in)
{       
    string line;
    int line_no = 1;

    while (getline(in, line)) {
        searchLine(line, pattern, line_no);
        line_no++;
    }
    
    if (in.bad()) {
        perror("getline");
        return false;
    }

    return true;
}

bool searchFile(const string &pattern, const string &path)
{
    ifstream file(path);

    if (!file) {
        perror("Error opening file");
        return false;
    }

    searchStream(pattern, file);
    return true;
}

/* traverse through given dir and search
 * for pattern in files
 */

bool searchDir(const string &pattern, const string &path)
{
   struct stat entryStat;
   vector<string> dirEntVec;
   
   getDirEntries(dirEntVec, path);
   
   for (auto i=dirEntVec.begin(); i!=dirEntVec.end(); i++) {
       string curPath = path + "/" + *i;
       
       if (stat(curPath.c_str(), &entryStat) == -1) {
           perror("stat of dir entry");
           return false;
       }

       if (S_ISREG(entryStat.st_mode)) {
           cout << "searching in " << curPath << endl;
           searchFile(pattern, curPath);

       } else if (S_ISDIR(entryStat.st_mode)) {
           searchDir(pattern, curPath);
       }
   }

   return true;
}


int main(int argc, char *argv[])
{
    string pattern(argv[1]);

    if (argc == 2) {
        return searchStream(pattern, cin) ? 0 : 1;

    } else if (argc == 3) {
        string path(argv[2]);
        struct stat pathStat;

        if (stat(path.c_str(), &pathStat) == -1) {
            perror("input path stat");
            cout << "Enter a valid path" << endl;    
        }

        if (S_ISREG(pathStat.st_mode)) {
            return searchFile(pattern, path) ? 0 : 1;

        } else if (S_ISDIR(pathStat.st_mode)) {
            return searchDir(pattern, path) ? 0 : 1;

        } else {
            cerr << "Path to regular file/dir required\n";    
        }

    } else {
        cerr << "Usage 1: " << argv[0] << " <pattern> <file>\n";
        cerr << "Usage 2: " << argv[0] << " <pattern> <dir>\n";
        cerr << "Usage 3: stdin | " << argv[0] << " <pattern>\n";
    }
}
