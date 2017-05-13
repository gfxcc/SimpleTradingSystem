#include <string>
#include <ctime>
#include <unordered_map>
#include <list>

#include "file_description.h"


#define TRADINGSYSTEM_FILEDESCRIPTION_CAPACITY 20


class TradingSystem {
public:
    TradingSystem() {}
    bool InsertTransaction(Transaction& transaction);
    // time format: dd_mm_yyyy-HH:MM:SS
    std::vector<Transaction> RetrieveTransactions(std::string time_begin, std::string time_end);

    void Close();
private:

    std::shared_ptr<FileDescription> GetFileDescriptionByDate(std::string data);
    std::shared_ptr<FileDescription> CreateFileDescriptionByDate(std::string data);


    int min_frequent_ = 0, capacity_ = TRADINGSYSTEM_FILEDESCRIPTION_CAPACITY;

    // key, {FileDescription, freq}
    std::unordered_map<std::string, std::pair<std::shared_ptr<FileDescription>, int>> mp_file_description_;
    // key, iterator of
    std::unordered_map<std::string, std::list<std::string>::iterator> mp_iterator_;
    // freq, list of key
    std::unordered_map<int, std::list<std::string>> mp_list_of_freq_;
};
