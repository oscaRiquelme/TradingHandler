#ifndef TRADE_H
#define TRADE_H

#include "types.h"
#include "date.h"

#define MAX_STRING 500

typedef struct trade Trade;

/*Initializers & cleaners*/
Trade* trade_newTrade(int id);
status trade_freeTrade(Trade * trade);

/*Getter headers*/
int trade_getId(Trade * trade);
double trade_getEntryPrice(Trade * trade);
double trade_getStopLoss(Trade * trade);
double trade_getTakeProfit(Trade * trade);
double trade_getAccountSize(Trade * trade);
double trade_getMoneyAvailable(Trade * trade);
double trade_getShares(Trade * trade);
double trade_getProfit(Trade * trade);
double trade_getProfitPct(Trade * trade);
double trade_getLoss(Trade * trade);
double trade_getLossPct(Trade * trade);
Date trade_getDate(Trade * trade);
char trade_getResult(Trade * trade);
char* trade_getReasonsToEnter(Trade * trade);
char* trade_getNotes(Trade * trade);
char*trade_getTicker(Trade * trade);
boolean trade_getTradeIsFixed(Trade* trade);
double trade_getRisk(Trade * trade);

/*Setter headers*/
status trade_setId(Trade * trade, int id);
status trade_setEntryPrice(Trade * trade, double EntryPrice);
status trade_setStopLoss(Trade * trade, double StopLoss);
status trade_setTakeProfit(Trade * trade, double TakeProfit);
status trade_setAccountSize(Trade * trade, double AccountSize);
status trade_setMoneyAvailable(Trade * trade, double MoneyAvailable);
status trade_setShares(Trade * trade, double shares);
status trade_setProfit(Trade * trade, double profit);
status trade_setLoss(Trade * trade, double loss);
status trade_setDate(Trade * trade, Date date);
status trade_setReasonsToEnter(Trade * trade, char* reasons);
status trade_setResult(Trade * trade, char result);
status trade_setNotes(Trade * trade, char* notes);
status trade_setTicker(Trade * trade, char* ticker);
status trade_setFixedTrade(Trade*trade, boolean fixedTrade);
status trade_setRisk(Trade *  trade, double risk);

Trade * trade_copy(Trade * trade);
/*Print headers*/
void trade_printPendingTrade(Trade * tradem, char* filename);
void trade_printOpenTrade(Trade * trade, char* filename);
void trade_printHistoryTrade(Trade * trade, char* filename);
void trade_printTradeOneLine(Trade * trade);

#endif

