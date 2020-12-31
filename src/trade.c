#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include "trade.h"




struct trade{
    
    int id;
    
    char ticker[6];
    double entryPrice;
    double stopLoss;
    double takeProfit;
    double accountSize;
    double moneyAvailable;
    double risk;
    boolean tradeIsFixed;
    
    double shares;
    double profit;
    double loss;
    double positionSize;

    Date date;
    char reasonsToEnter[MAX_STRING];
    
    char result;
    char notes[MAX_STRING];
};

/*Ini and free*/

Trade* trade_newTrade(int id){

    Trade *newTrade;

    newTrade = (Trade*)malloc(sizeof(Trade));
    if(!newTrade){
        printf("\nCan't allocate memory for a new Trade variable. Returning NULL...\n");
        return NULL;
    }

    newTrade->id = id;
    newTrade->entryPrice = 0;
    newTrade->stopLoss = 0;
    newTrade->takeProfit = 0;
    newTrade->accountSize = 0;
    newTrade->moneyAvailable = 0;
    newTrade->date.day = 0;
    newTrade->date.month = 0;
    newTrade->date.year = 0;
    newTrade->date.hours = 0;
    newTrade->date.minutes = 0;
    newTrade->date.seconds = 0;
    newTrade->shares = 0;
    newTrade->profit = 0;
    newTrade->loss = 0;
    newTrade->reasonsToEnter[0] = '\0';
    newTrade->result = 'x';
    newTrade->notes[0] = '\0';
    newTrade->ticker[0] = '\0';
    newTrade->tradeIsFixed = FALSE;
    newTrade->risk = 0;
    newTrade->positionSize = 0;

    return newTrade;
}

status trade_freeTrade(Trade * trade){
    
    if(!trade) return ERR;
    
    free(trade);
    
    return OK;
}


/*Getters*/

double trade_getPositionSize(Trade * trade){
    if(!trade) return ERR_RETURN;

    return trade->positionSize;
}

int trade_getId(Trade * trade){
    if(!trade) return NO_ID;

    return trade->id;

}

char*trade_getTicker(Trade * trade){
    if(!trade) return NULL;

    return trade->ticker;
}

double trade_getRisk(Trade * trade){
    if(!trade) return ERR_RETURN;

    return trade->risk;
}

double trade_getEntryPrice(Trade * trade){
    if(!trade) return ERR_RETURN;

    return trade->entryPrice;
}

double trade_getStopLoss(Trade * trade){
    if(!trade) return ERR_RETURN;

    return trade->stopLoss;
}

double trade_getTakeProfit(Trade * trade){
    if(!trade) return ERR_RETURN;

    return trade->takeProfit;
}

boolean trade_getTradeIsFixed(Trade* trade){
    if(!trade) return FALSE;

    return trade->tradeIsFixed;
}

double trade_getAccountSize(Trade * trade){
    if(!trade) return ERR_RETURN;

    return trade->accountSize;
}

double trade_getMoneyAvailable(Trade * trade){
    if(!trade) return ERR_RETURN;

    return trade->moneyAvailable;
}

double trade_getShares(Trade * trade){
    if(!trade) return ERR_RETURN;

    return trade->shares;
}

double trade_getProfit(Trade * trade){
    if(!trade) return ERR_RETURN;

    return trade->profit;
}

double trade_getProfitPct(Trade * trade){
    if(!trade) return ERR_RETURN;

    return trade->profit*100/trade->accountSize;
}

double trade_getLoss(Trade * trade){
    if(!trade) return ERR_RETURN;

    return trade->loss;
}

double trade_getLossPct(Trade * trade){
    if(!trade) return ERR_RETURN;

    return trade->loss*100/trade->accountSize;
}

Date trade_getDate(Trade * trade){
    Date errDate;

    if(!trade){
        errDate.day = ERR_RETURN;
        errDate.month = ERR_RETURN;
        errDate.year = ERR_RETURN;
        errDate.hours = ERR_RETURN;
        errDate.minutes = ERR_RETURN;
        errDate.seconds = ERR_RETURN;

        return errDate;
    } 
        

    return trade->date;
}

char trade_getResult(Trade * trade){
    if(!trade) return ERR_RETURN;

    return trade->result;
}

char* trade_getReasonsToEnter(Trade * trade){
    if(!trade) return NULL;

    return trade->reasonsToEnter;
}

char* trade_getNotes(Trade * trade){
    if(!trade) return NULL;

    return trade->notes;
}


/*Setters*/

status trade_setPositionSize(Trade * trade, double positionSize){
    if(!trade) return ERR;

    trade->positionSize = positionSize;

    return OK;
}

status trade_setId(Trade * trade, int id){
    if(!trade) return NO_ID;

    trade->id = id;

    return OK;

}

status trade_setEntryPrice(Trade * trade, double EntryPrice){
    if(!trade || EntryPrice <= 0) return ERR;

    trade->entryPrice = EntryPrice;

    return OK;
}

status trade_setStopLoss(Trade * trade, double StopLoss){
    if(!trade || StopLoss >= trade->entryPrice || StopLoss <= 0) return ERR;

    trade->stopLoss = StopLoss;

    return OK;
}

status trade_setRisk(Trade *  trade, double risk){
    if(!trade || risk < 0) return ERR;

    trade->risk = risk;

    return OK;
}

status trade_setTakeProfit(Trade * trade, double TakeProfit){
    if(!trade || TakeProfit <= 0 || TakeProfit <= trade->entryPrice) return ERR;

    trade->takeProfit = TakeProfit;

    return OK; 
}

status trade_setAccountSize(Trade * trade, double AccountSize){
    if(!trade || AccountSize < 0 || AccountSize < trade->moneyAvailable) return ERR;

    trade->accountSize = AccountSize;

    return OK;
}

status trade_setMoneyAvailable(Trade * trade, double MoneyAvailable){
    if(!trade || MoneyAvailable < 0 || MoneyAvailable > trade->accountSize) return ERR;

    trade->moneyAvailable = MoneyAvailable;

    return OK;
}

status trade_setShares(Trade * trade, double shares){
    if(!trade || shares < 0) return ERR;

    trade->shares = shares;

    return OK;
}

status trade_setProfit(Trade * trade, double profit){
    if(!trade || profit < 0) return ERR;

    trade->profit = profit;

    return OK;
}

status trade_setLoss(Trade * trade, double loss){
    if(!trade || loss < 0) return ERR;

    trade->loss = loss;

    return OK;
}

status trade_setDate(Trade * trade, Date date){
    if(!trade) return ERR;

    trade->date = date;

    return OK;
}

status trade_setReasonsToEnter(Trade * trade, char* reasons){
    if(!trade || !reasons) return ERR;

    strcpy(trade->reasonsToEnter, reasons);

    return OK;
}

status trade_setResult(Trade * trade, char result){
    if(!trade || (result != 'w' && result != 'y' && result != 'W' && result != 'Y')) return ERR;

    trade->result = result;

    return OK;
    
}

status trade_setNotes(Trade * trade, char* notes){
    if(!trade || !notes) return ERR;

    strcpy(trade->notes, notes);

    return OK;
}

status trade_setTicker(Trade * trade, char* ticker){
    if(!trade || !ticker) return ERR;

    strcpy(trade->ticker, ticker);

    return OK;
}

status trade_setFixedTrade(Trade*trade, boolean fixedTrade){
    if(!trade) return ERR;

    trade->tradeIsFixed = fixedTrade;

    return OK;
}

Trade * trade_copy(Trade * trade){
    
    Trade *new_trade;
    if(!trade) return NULL;

    new_trade = (Trade*)malloc(sizeof(Trade));

    if(!new_trade) return NULL;

    new_trade->accountSize = trade->accountSize;
    new_trade->date = trade->date;
    new_trade->entryPrice = trade->entryPrice;
    new_trade->id = trade->id;
    new_trade->loss = trade->loss;
    new_trade->moneyAvailable = trade->moneyAvailable;
    new_trade->profit = trade->profit;
    new_trade->result = trade->result;
    new_trade->risk = trade->risk;
    new_trade->shares = trade->shares;
    new_trade->tradeIsFixed = trade->tradeIsFixed;
    strcpy(new_trade->reasonsToEnter, trade->reasonsToEnter);
    strcpy(new_trade->ticker, trade->ticker);
    strcpy(new_trade->notes, trade->notes);
    new_trade->stopLoss = trade->stopLoss;
    new_trade->takeProfit = trade->takeProfit;
    new_trade->positionSize = trade->positionSize;

    return new_trade;
      
}


/*Print functions*/
void trade_printPendingTrade(Trade * trade, char* filename){
    
    FILE *f;
    if(!trade) return;

    if(!filename) f = stdout;
    else
    f = fopen(filename, "a");

    if(!f) return;
    
    fprintf( f, "Id: %d\n", trade->id);
    fprintf( f, "TICKER: %s\n", trade->ticker);
    fprintf( f, "Account size(€): %.2f\n", trade->accountSize);
    fprintf( f, "Money available(€): %.2f\n",trade->moneyAvailable);
    fprintf( f, "\nEntry price($): %.2f\n",trade->entryPrice);
    fprintf( f, "Stop loss($): %.2f\n", trade->stopLoss);
    fprintf( f, "Take profit($): %.2f\n",  trade->takeProfit);
    fprintf( f, "Shares: %.2f\n", trade->shares);
    fprintf( f, "Position Size(€): %.2f\n", trade->positionSize);
    if(trade->tradeIsFixed == TRUE){
        fprintf( f, "Profit if it goes well(€): ");
        green();
        fprintf( f, "%.2f(+%.2f%%)\n", trade->profit, trade->profit*100/trade->accountSize);
        defaults();
    }
    else fprintf( f, "No price target was introduced\n");
    fprintf( f, "Loss if it goes wrong: ");
    red();
    fprintf( f, "%.2f(-%.2f%%)\n",trade->loss, trade->loss*100/trade->accountSize);
    defaults();
    
    if(filename)
        fclose(f);

}

void trade_printOpenTrade(Trade* trade, char* filename){

    FILE * f;
    if(!trade) return;

    trade_printPendingTrade(trade, filename);
    
    if(!filename) f = stdout;
    else f = fopen(filename, "a");
    
    if(!f) return;
    
    fprintf( f, "Date: ");
    date_printDate(trade->date);
    fprintf( f, "Reasons to enter the trade: %s\n", trade->reasonsToEnter);
    
    fclose(f);
}

void trade_printHistoryTrade(Trade * trade, char* filename){

    FILE *f;

    if(!trade) return;


    trade_printOpenTrade(trade, filename);
    
    if(!filename) f = stdout;
    else f = fopen(filename, "a");
    
    if(!f) return;


    fprintf( f, "Result: ");
    if(trade->result == 'W' || trade->result == 'w'){
        green();
        fprintf( f, "WIN\n");
        defaults();
    }
    else if(trade->result == 'l' || trade->result == 'L'){
        red();
        fprintf( f, "LOSS :(\n");
        defaults();
    }
    fprintf( f, "Notes: %s\n", trade->notes);

    fclose(f);
    

}

void trade_printTradeOneLine(Trade * trade){

    if(!trade) return;

    printf("\nId: %d | TICKER: %s | EntryPrice %.2f | StopLoss: %.2f |", trade->id, trade->ticker, trade->entryPrice, trade->stopLoss);
    if(trade->tradeIsFixed == TRUE) printf(" TakeProfit: %.2f | ", trade->takeProfit);
    else printf(" No price target |");
    printf(" Position Size: %.2f", trade->positionSize);
}