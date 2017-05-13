#include <iterator>
#include <utility>
#include <iostream>

#include "trading_system.h"

using namespace std;

bool TradingSystem::InsertTransaction(Transaction& transaction) {
    // parsing date and locating file
    // if the file does not exist, create one
    string date = transaction.GetStringDate();
    shared_ptr<FileDescription> file_description = GetFileDescriptionByDate(date);

    if (file_description->InsertTransaction(transaction) == false) {
        // handle
        return false;
    }

    //
    return true;
}

vector<Transaction> TradingSystem::RetrieveTransactions(string time_begin, string time_end) {
    // pull out FileDescription for the time point or range
    vector<shared_ptr<FileDescription>> file_descriptions_of_time_range;
    vector<string> date_range = DateOperation::GetDateRange(time_begin, time_end);

    ///cout << "date range :" << date_range.size() << endl;
    vector<Transaction> transactions;
    for (auto& date : date_range) {
        shared_ptr<FileDescription> file_description = GetFileDescriptionByDate(date);
        file_description->RetrieveTransactionsBetweenTime(transactions, time_begin, time_end);
    }

    return transactions;
}

shared_ptr<FileDescription> TradingSystem::GetFileDescriptionByDate(string date) {
    //cout << date << endl;
    //if (!mp_file_description_.empty())
        //cout << mp_file_description_.begin()->first << endl;
    if (mp_file_description_.find(date) == mp_file_description_.end()) {
        //cout << "create" << endl;
        return CreateFileDescriptionByDate(date);
    }

    //cout << "exist" << endl;
    // retrieve file_description and update frequence
    shared_ptr<FileDescription> file_description = mp_file_description_[date].first;
    int freq = mp_file_description_[date].second;
    mp_list_of_freq_[freq].erase(mp_iterator_[date]);
    mp_file_description_[date].second++;
    mp_list_of_freq_[++freq].push_back(date);
    mp_iterator_[date] = prev(mp_list_of_freq_[freq].end(), 1);

    // incase file_description of date is the last one in mp_list_of_freq_[min_frequent]
    // if so, we need update min_frequent
    if (mp_list_of_freq_[min_frequent_].empty())
        min_frequent_ = freq;

    return file_description;
}

shared_ptr<FileDescription> TradingSystem::CreateFileDescriptionByDate(string date) {

    // if we have too much FileDescription, write the least used one into file. then relase it
    if (mp_file_description_.size() >= capacity_) {
        string remove_date = mp_list_of_freq_[min_frequent_].front();
        // write FileDescription into file and relase
        shared_ptr<FileDescription> file_description = mp_file_description_[remove_date].first;
        mp_file_description_.erase(remove_date);

        file_description->WriteToFile();

        //
        mp_list_of_freq_[min_frequent_].pop_front();
        mp_iterator_.erase(remove_date);
    }

    // update the frequent part
    shared_ptr<FileDescription> file_description = make_shared<FileDescription>(date);
    mp_file_description_.insert(unordered_map<string, pair<shared_ptr<FileDescription>, int>>::value_type(date,
                make_pair(file_description, 1)));
    mp_list_of_freq_[1].push_back(date);
    mp_iterator_[date] = prev(mp_list_of_freq_[1].end(), 1);
    min_frequent_ = 1;

    return file_description;
}

void TradingSystem::Close() {

    for (auto& it : mp_file_description_) {
        auto file_description = it.second.first;
        file_description->WriteToFile();
    }

}
