#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include "trade.h"


#define MAX_STRING 500

struct trade{
    char ticker[6];
    int id;
    double entryPrice;
    double stopLoss;
    double takeProfit;
    double accountSize;
    double moneyAvailable;
    Date date;
    double shares;
    double profit;
    double loss;
    char reasonsToEnter[MAX_STRING];
    char result;
    char notes[MAX_STRING];
};

/*Ini and free*/

Trade* trade_newTrade(int id){

    Trade *newTrade;

    if(id == NO_ID){
        printf("\n Id passed to create a new Trade variable is not valid(NO_ID). Returning NULL\n");
        return NULL;
    } 

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

    return newTrade;
}

status trade_freeTrade(Trade * trade){
    
    if(!trade) return ERR;
    
    free(trade);
    
    return OK;
}


/*Getters*/

int trade_getId(Trade * trade){
    if(!trade) return NO_ID;

    return trade->id;

}

char*trade_getTicker(Trade * trade){
    if(!trade) return NULL;

    return trade->ticker;
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
status trade_setId(Trade * trade, int id){
    if(!trade) return NO_ID;

    return trade->id;

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


/*Print functions*/
void trade_printTrade(Trade * trade){
    
    if(!trade) return;

    printf("\nImprimiendo trade...");
    printf("\n\n\n");

    printf("\n-------------------------------------------------------------------------------------------------------------------\n");
    printf("Id: %d\n", trade->id);
    printf("Account size(€): %.2f\n", trade->accountSize);
    printf("Money available(€): %.2f\n",trade->moneyAvailable);
    printf("\nEntry price($): %.2f\n",trade->entryPrice);
    printf("Stop loss($): %.2f\n", trade->stopLoss);
    printf("Take profit($): %.2f\n",  trade->takeProfit);
    printf("Shares: %.2f\n", trade->shares);
    printf("Profit if it goes well(€): ");
    green();
    printf("%.2f(+%.2f%%)\n", trade->profit, trade->profit*100/trade->accountSize);
    defaults();
    printf("\tLoss if it goes wrong: ");
    red();
    printf("%.2f(-%.2f%%)\n",trade->loss, trade->loss*100/trade->accountSize);
    defaults();
    printf("-------------------------------------------------------------------------------------------------------------------\n");


}
