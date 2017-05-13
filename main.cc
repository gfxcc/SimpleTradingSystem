#include "trading_system.h"
#include <iostream>

using namespace std;

int main() {
    TradingSystem trade;

    time_t t = time(0);
    Transaction tran(t, "test", 12.0);
    trade.InsertTransaction(tran);
    trade.InsertTransaction(tran);

    auto ret = trade.RetrieveTransactions(DateOperation::GetStringTime(t), DateOperation::GetStringTime(t));
    cout << ret.size() << endl;
    trade.Close();

    return 0;
}
