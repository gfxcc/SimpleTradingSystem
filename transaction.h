#include <string>

#include "date_operation.h"

class Transaction {
public:
    Transaction(time_t date_time, std::string stock_symble, double price) :
        date_time_(date_time), stock_symble_(stock_symble), price_(price) {}

    std::string GetStringDate() {
        std::string ret = DateOperation::GetStringDate(date_time_);
        return ret;
    }

    std::string GetStringTime() const {
        return DateOperation::GetStringTime(date_time_);
    }

    time_t GetDateTime() const {
        return date_time_;
    }
    std::string GetStockSymble() const {
        return stock_symble_;
    }
    double GetPrice() const {
        return price_;
    }
    std::string GetStringInformation() const {
        return DateOperation::GetStringTime(date_time_) + " " + stock_symble_ + " " + std::to_string(price_);
    }
private:
    time_t date_time_;
    std::string stock_symble_;
    double price_;
    //
    // some additional information
    //
};

