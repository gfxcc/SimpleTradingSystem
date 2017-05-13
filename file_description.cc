#include <fstream>
#include <sstream>
#include <iostream>

#include "file_description.h"

using namespace std;

FileDescription::FileDescription(string date) {

    //

    date_ = date;
    ifstream file(GetFilename());
    if (!file.is_open())
        return;

    string line;
    while (getline(file, line)) {
        string date_time, stock_symble, price;
        istringstream iss(line);
        iss >> date_time >> stock_symble >> price;

        Transaction transaction(DateOperation::GetTimeTFromTime(date_time), stock_symble, stod(price));
    }

}

bool FileDescription::InsertTransaction(Transaction& transaction) {
    auto it = lower_bound(transactions_.begin(), transactions_.end(), transaction, [&](const Transaction& lhs, const Transaction& rhs) {
            return lhs.GetStringTime() < rhs.GetStringTime();
            });
    transactions_.insert(it, transaction);
    return true;
}

void FileDescription::WriteToFile() {
    ofstream of;
    string filename = GetFilename();
    of.open(filename);

    for_each(transactions_.begin(), transactions_.end(), [&](const Transaction& transaction) {
            of << transaction.GetStringInformation() << endl;
            });
    of.close();
}

void FileDescription::RetrieveTransactionsBetweenTime(std::vector<Transaction>& transactions, std::string time_start, std::string time_end) {
    Transaction transaction_start(DateOperation::GetTimeTFromTime(time_start), "", 0.0),
                transaction_end(DateOperation::GetTimeTFromTime(time_end), "", 0.0);
    //cout << time_start << endl;
    //cout << time_end << endl;
    //cout << transactions_.size() << endl;
    auto cmp = [](const Transaction& lhs, const Transaction& rhs) {
        //cout << lhs.GetStringTime() << " " << rhs.GetStringTime() << endl;
        return lhs.GetStringTime() < rhs.GetStringTime();
    };
    auto it_start = lower_bound(transactions_.begin(), transactions_.end(), transaction_start, cmp);
    auto it_end = upper_bound(transactions_.begin(), transactions_.end(), transaction_end, cmp);

    //if (it_start == transactions_.begin())
    //    cout << "start is fine" << endl;
    //if (it_end == transactions_.end())
    //    cout << "end is fine" << endl;
    for_each(it_start, it_end, [&](const Transaction& lhs) {
            transactions.push_back(lhs);
            });
}


