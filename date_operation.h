#include <ctime>
#include <string>
#include <vector>
#include <unordered_map>
#include <iostream>
class DateOperation {
public:
    static time_t GetTimeTFromTime(std::string time) {
        struct tm tm;
        strptime(time.c_str(), "%d_%m_%y-%H:%M:%S", &tm);
        time_t t = mktime(&tm);
        return t;
    }
    static std::string GetNextDate(std::string date) {
        std::vector<int> day_of_month = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
        int day = stoi(date.substr(0, 2)), month = stoi(date.substr(3, 2)), year = stoi(date.substr(6, 2));
        day++;
        if (day > day_of_month[month - 1]) {
            day = 1;
            month++;

            if (month > 12) {
                month = 1;
                year++;
            }
        }

        std::string ret = (day < 10 ? "0" : "") + std::to_string(day) + "_" + (month < 10 ? "0" : "") + std::to_string(month) + "_" +
            (year < 10 ? "0" : "") + std::to_string(year);

        //std::cout << "in " << date << " out " << ret << std::endl;
        return ret;
    }

    static std::string GetStringTime(const time_t& time) {

        std::tm * ptm = std::localtime(&time);
        char buffer[32];
        // Format: Mo, 15.06.2009 20:20:00
        // std::strftime(buffer, 32, "%a, %dd_%mm_%yyyy-%HH:%MM:%SS", ptm);
        std::strftime(buffer, 32, "%d_%m_%y-%H:%M:%S", ptm);
        return std::string(buffer);


    }

    static std::string GetStringDate(const time_t& time) {
        std::tm * ptm = std::localtime(&time);
        char buffer[32];
        // Format: Mo, 15.06.2009 20:20:00
        // std::strftime(buffer, 32, "%a, %dd_%mm_%yyyy-%HH:%MM:%SS", ptm);
        std::strftime(buffer, 32, "%d_%m_%y", ptm);
        return std::string(buffer);
    }

    static std::vector<std::string> GetDateRange(std::string time_begin, std::string time_end) {

        // cutting of hh:mm:ss
        time_begin = time_begin.substr(0, 8);
        time_end = time_end.substr(0, 8);

        //std::cout << time_begin << std::endl << time_end << std::endl;

        std::vector<std::string> ret;
        while (true) {
            ret.push_back(time_begin);
            if (time_begin == time_end)
                break;
            time_begin = GetNextDate(time_begin);
            //std::cout << time_begin << std::endl << time_end << std::endl;
                    }
        return ret;
    }
};

