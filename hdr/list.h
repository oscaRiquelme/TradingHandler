#ifndef LIST_H
#define LIST_H

#include "trade.h"
#include "types.h"


typedef struct tradeList TradeList;

TradeList * tradeList_newTradeList();
status tradeList_destroyList(TradeList * tradeList);
Trade * tradeList_getTrade(TradeList * tradeList, int id);
status tradeList_deleteTrade(TradeList * tradeList, int id);
status tradeList_insertTrade(TradeList * tradeList, Trade * trade);
void tradeList_printList(TradeList * tradeList);
int tradeList_getNumberOfTrades(TradeList * tradeList);
Trade * tradeList_getTradeByIndex(TradeList * tradeList, int index);

#endif