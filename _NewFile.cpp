#include <ctime>
#include <iostream>
#include <fstream>
#include <string>
#include <sys/stat.h>

#define BASEYEAR 1900

// converts the given tm struct to the filename for that day's todo
// the file format is yyyy-mm-dd.txt
// TODO: see if strftime works more elegantly
std::string date_to_fn(tm* in_time) {
    int year = BASEYEAR + in_time->tm_year;
    int month = 1 + in_time->tm_mon;
    int day = in_time->tm_mday;

    char buf[14];
    sprintf(buf, "%d-%02d-%02d.txt",
            year,
            month,
            day);

    return std::string(buf);
}

// returns whether the given string names a real file
bool file_exists(std::string& fn) {
    struct stat buffer;
    return (stat(fn.c_str(), &buffer) == 0);
}

// write today's todo file.
// if a todo file exists for the previous work day, copy that day's Todo section,
// otherwise, just write the basic template
void create_todays_todo(std::string& tdy_fn, std::string& yda_fn) {
    
    std::ofstream outfile(tdy_fn);
    if (file_exists(yda_fn)) {
        std::ifstream infile(yda_fn);
        std::string line;

        do {
            std::getline(infile, line);
            outfile << line << std::endl;
        } while (line.find("Done:"));
    } else {
        outfile << "Todo: " << std::endl;
        outfile << std::endl;
        outfile << std::endl;
        outfile << "Done: " << std::endl;
    }

    outfile << std::endl;
    outfile << std::endl;
    outfile << "Notes: " << std::endl;
    outfile << std::endl;
    outfile << "in @" << std::endl;
    outfile << "out @" << std::endl;
    outfile << "in @" << std::endl;
    outfile << "out @" << std::endl;
    outfile.close();
}

int main() {

    // Get current time
    time_t now= time(0);
    tm *loctm = localtime(&now);

    // Create filename for output
    std::string tdy_fn = date_to_fn(loctm);

    // Get the previous workday's timestamp
    // Don't need to worry about underflow because mktime does that automatically
    int weekday = loctm->tm_wday; // days since Sunday. Mon=1 Fri=5
    tm *last_workday = localtime(&now);
    if (weekday > 1) {
        last_workday->tm_mday--;
    } else {
        last_workday->tm_mday = 5; // on monday, last workday was friday
    }

    // Get the previous workday's todo-file name
    mktime(last_workday);
    std::string yda_fn = date_to_fn(last_workday);

    // Write today's todo file
    create_todays_todo(tdy_fn, yda_fn);

    // Convert to DOS format
    /*std::string command = "todos ";
    command.append(fn);
    system(command.c_str());*/

    return 0;
}
