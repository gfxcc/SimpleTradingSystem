#include <string>
#include <vector>
#include <functional>

#include "transaction.h"

class FileDescription {
public:
    FileDescription(std::string date);

    bool InsertTransaction(Transaction& transaction);
    void RetrieveTransactionsBetweenTime(std::vector<Transaction>& transactions, std::string time_start, std::string time_end);
    void WriteToFile();
private:

    std::string GetFilename() {
        return date_ + ".dat";
    }

    std::string date_;
    std::vector<Transaction> transactions_;
};

