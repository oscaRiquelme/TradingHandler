#ifndef TRADE_MANAGER_H
#define TRADE_MANAGER_H

#include "trade.h"
#include "list.h"

typedef struct trade_manager Trade_manager;

Trade_manager * trade_manager_newTradeManager();
void trade_manager_destroyManager(Trade_manager * trade_manager);
TradeList * trade_manager_getPendingTrades(Trade_manager * trade_manager);
TradeList * trade_manager_getHistoryTrades(Trade_manager * trade_manager);
TradeList * trade_manager_getOpenTrades(Trade_manager * trade_manager);
status trade_manager_readHistoryFromFile(Trade_manager * trade_manager, char* file);
status trade_manager_readPendingFromFile(Trade_manager * trade_manager, char* file);
status trade_manager_readOpenFromFile(Trade_manager * trade_manager, char* file);
status trade_manager_savePendingTrades(Trade_manager * trade_manager, char * file);
status trade_manager_saveOpenTrades(Trade_manager * trade_manager, char * file);
status trade_manager_saveHistoryTrades(Trade_manager * trade_manager, char * file);
#endif