#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include "trade_manager.h"
#include "trade.h" 
#include "list.h"

struct trade_manager{
    
    TradeList * pendingTrades;
    TradeList * openTrades;
    TradeList * historyTrades;
   

};

Trade_manager * trade_manager_newTradeManager(){

    Trade_manager * new_Tm = NULL;

    new_Tm = (Trade_manager*)malloc(sizeof(Trade_manager));

    if(!new_Tm){
        printf("Failed to allocate memory for the trade_manager. Returning NULL");
        return NULL;
    }

    new_Tm->pendingTrades = NULL;
    new_Tm->openTrades = NULL;
    new_Tm->historyTrades = NULL;

    return new_Tm;

}

void trade_manager_destroyManager(Trade_manager * trade_manager){

    if(trade_manager){

        if(trade_manager->pendingTrades) tradeList_destroyList(trade_manager->pendingTrades);
        if(trade_manager->openTrades) tradeList_destroyList(trade_manager->openTrades);
        if(trade_manager->historyTrades) tradeList_destroyList(trade_manager->historyTrades);

        free(trade_manager);
    }

}

TradeList * trade_manager_getPendingTrades(Trade_manager * trade_manager){

    if(!trade_manager)  return NULL;

    return trade_manager->pendingTrades;

}

TradeList * trade_manager_getHistoryTrades(Trade_manager * trade_manager){

    if(!trade_manager)  return NULL;

    return trade_manager->historyTrades;

}

TradeList * trade_manager_getOpenTrades(Trade_manager * trade_manager){

    if(!trade_manager)  return NULL;

    return trade_manager->openTrades;

}

status trade_manager_readPendingFromFile(Trade_manager * trade_manager, char* file){
    
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

    Trade * trade = NULL;
    char line[CHAR_MAX];
    char * toks;

    FILE *f = NULL;
    status errorControl;

    if(!trade_manager || !file){
        printf("\nWrong arguments passed to the readPendingFromFile function, returning NULL");
        return ERR;
    } 

    trade_manager->pendingTrades = tradeList_newTradeList();
    if(!trade_manager->pendingTrades){
        printf("\nError allocating memory for a new list of trades. Returning ERR\n");
        return ERR;
    }


    f = fopen(file, "r");
    if(!f){
        printf("\n Error loading the pending trading. Returning ERR...\n");
        tradeList_destroyList(trade_manager->pendingTrades);
        return ERR;
    }

    trade = trade_newTrade(NO_ID);
    if(!trade){
        printf("\nError  allocating memory for a new trade variable in trade_manager_readPendingFromFile. Returning ERR...\n");
        fclose(f);
        tradeList_destroyList(trade_manager->pendingTrades);
        return ERR;
    }
    
    while(fgets(line, CHAR_MAX, f)){
        if (strncmp("#p:", line, 3) == 0)
        {
            toks = strtok(line + 3, "|");
            id = atoi(toks);
            toks = strtok(NULL, "|");
            strcpy(ticker, toks);
            toks = strtok(NULL, "|");
            entryPrice = atol(toks);
            toks = strtok(NULL, "|");
            stopLoss = atol(toks);
            toks = strtok(NULL, "|");
            takeProfit = atol(toks);  
            toks = strtok(NULL, "|");
            accountSize = atol(toks);
            toks = strtok(NULL, "|");
            moneyAvailable = atol(toks);
            toks = strtok(NULL, "|");
            risk = atol(toks);
            toks = strtok(NULL, "|");
            tradeIsFixed = (boolean)atoi(toks);
            toks = strtok(NULL, "|");
            shares = atol(toks);
            toks = strtok(NULL, "|");
            profit = atol(toks);
            toks = strtok(NULL, "|");
            loss = atol(toks);


    #ifdef DEBUG
      printf("Leido: %d|%s|%f|%f|%f|%f|%f|%f|%d|%f|%f|%f",id, ticker,entryPrice, stopLoss, 
      takeProfit, accountSize, moneyAvailable, risk, tradeIsFixed, shares, profit, loss);
#endif

            errorControl = trade_setId(trade, id);
            if(errorControl == ERR){
                tradeList_destroyList(trade_manager->pendingTrades);    
                printf("\nError setting the read variables of the pending trades. Returning ERR...\n");
                trade_freeTrade(trade);
                fclose(f);
                return ERR;
    }    
            errorControl = trade_setTicker(trade, ticker);
            if(errorControl == ERR){
                tradeList_destroyList(trade_manager->pendingTrades);
                printf("\nError setting the read variables of the pending trades. Returning ERR...\n");
                trade_freeTrade(trade);
                fclose(f);
                return ERR;
    }        
            errorControl = trade_setEntryPrice(trade, entryPrice);    
            if(errorControl == ERR){
                tradeList_destroyList(trade_manager->pendingTrades);
                printf("\nError setting the read variables of the pending trades. Returning ERR...\n");
                trade_freeTrade(trade);
                fclose(f);
                return ERR;
    }    
            errorControl = trade_setStopLoss(trade, stopLoss);    
            if(errorControl == ERR){
                tradeList_destroyList(trade_manager->pendingTrades);
                printf("\nError setting the read variables of the pending trades. Returning ERR...\n");
                trade_freeTrade(trade);
                fclose(f);
                return ERR;
    }    
            errorControl = trade_setTakeProfit(trade, takeProfit);    
            if(errorControl == ERR){
                tradeList_destroyList(trade_manager->pendingTrades);
                printf("\nError setting the read variables of the pending trades. Returning ERR...\n");
                trade_freeTrade(trade);
                fclose(f);
                return ERR;
    }    
            errorControl = trade_setAccountSize(trade, accountSize);    
            if(errorControl == ERR){
                tradeList_destroyList(trade_manager->pendingTrades);
                printf("\nError setting the read variables of the pending trades. Returning ERR...\n");
                trade_freeTrade(trade);
                fclose(f);
                return ERR;
    }    
            errorControl = trade_setMoneyAvailable(trade, moneyAvailable);    
            if(errorControl == ERR){
                tradeList_destroyList(trade_manager->pendingTrades);
                printf("\nError setting the read variables of the pending trades. Returning ERR...\n");
                trade_freeTrade(trade);
                fclose(f);
                return ERR;
    }    
            errorControl = trade_setRisk(trade, risk);    
            if(errorControl == ERR){
                tradeList_destroyList(trade_manager->pendingTrades);
                printf("\nError setting the read variables of the pending trades. Returning ERR...\n");
                trade_freeTrade(trade);
                fclose(f);
                return ERR;
    }    
            errorControl = trade_setFixedTrade(trade, tradeIsFixed);
            if(errorControl == ERR){
                tradeList_destroyList(trade_manager->pendingTrades);
                printf("\nError setting the read variables of the pending trades. Returning ERR...\n");
                trade_freeTrade(trade);
                fclose(f);
                return ERR;
    }    
            errorControl = trade_setShares(trade, shares);
            if(errorControl == ERR){
                tradeList_destroyList(trade_manager->pendingTrades);
                printf("\nError setting the read variables of the pending trades. Returning ERR...\n");
                trade_freeTrade(trade);
                fclose(f);
                return ERR;
    }    
            errorControl = trade_setProfit(trade, profit);
            if(errorControl == ERR){
                tradeList_destroyList(trade_manager->pendingTrades);
                trade_freeTrade(trade);
                printf("\nError setting the read variables of the pending trades. Returning ERR...\n");
                fclose(f);
                return ERR;
    }    
            errorControl = trade_setLoss(trade, loss);
            if(errorControl == ERR){
                tradeList_destroyList(trade_manager->pendingTrades);
                printf("\nError setting the read variables of the pending trades. Returning ERR...\n");
                trade_freeTrade(trade);
                fclose(f);
                return ERR;
    }    

            errorControl = tradeList_insertTrade(trade_manager->pendingTrades, trade);
            if(errorControl == ERR){
                tradeList_destroyList(trade_manager->pendingTrades);
                printf("\nError setting the read variables of the pending trades. Returning ERR...\n");
                trade_freeTrade(trade);
                fclose(f);
                return ERR;
        }    
    
        }
    }
    fclose(f);
    trade_freeTrade(trade);

    return OK;
}

status trade_manager_readOpenFromFile(Trade_manager * trade_manager, char* file){
    
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

    Trade * trade = NULL;
    char line[CHAR_MAX];
    char * toks;

    Date date;
    char reasons[MAX_STRING];

    FILE *f = NULL;
    status errorControl;

    if(!trade_manager || !file){
        printf("\nWrong arguments passed to the readPendingFromFile function, returning NULL");
        return ERR;
    } 

    trade_manager->openTrades = tradeList_newTradeList();
    if(!trade_manager->openTrades){
        printf("\nError allocating memory for a new list of trades. Returning ERR\n");
        return ERR;
    }


    f = fopen(file, "r");
    if(!f){
        printf("\n Error loading the pending trading. Returning ERR...\n");
        tradeList_destroyList(trade_manager->openTrades);
        return ERR;
    }

    trade = trade_newTrade(NO_ID);
    if(!trade){
        printf("\nError  allocating memory for a new trade variable in trade_manager_readPendingFromFile. Returning ERR...\n");
        fclose(f);
        tradeList_destroyList(trade_manager->openTrades);
        return ERR;
    }
    
    while(fgets(line, CHAR_MAX, f)){
        if (strncmp("#o:", line, 3) == 0)
        {
            toks = strtok(line + 3, "|");
            id = atoi(toks);
            toks = strtok(NULL, "|");
            strcpy(ticker, toks);
            toks = strtok(NULL, "|");
            entryPrice = atol(toks);
            toks = strtok(NULL, "|");
            stopLoss = atol(toks);
            toks = strtok(NULL, "|");
            takeProfit = atol(toks);  
            toks = strtok(NULL, "|");
            accountSize = atol(toks);
            toks = strtok(NULL, "|");
            moneyAvailable = atol(toks);
            toks = strtok(NULL, "|");
            risk = atol(toks);
            toks = strtok(NULL, "|");
            tradeIsFixed = (boolean)atoi(toks);
            toks = strtok(NULL, "|");
            shares = atol(toks);
            toks = strtok(NULL, "|");
            profit = atol(toks);
            toks = strtok(NULL, "|");
            loss = atol(toks);
            toks = strtok(NULL, "|");
            date.hours = atoi(toks);
            toks = strtok(NULL, "|");
            date.minutes = atoi(toks);
            toks = strtok(NULL, "|");
            date.seconds = atoi(toks);
            toks = strtok(NULL, "|");
            date.day = atoi(toks);
            toks = strtok(NULL, "|");
            date.month = atoi(toks);
            toks = strtok(NULL, "|");
            date.year = atoi(toks);
            toks = strtok(NULL, "|");
            strcpy(reasons, toks);


    #ifdef DEBUG
      printf("Leido: %d|%s|%f|%f|%f|%f|%f|%f|%d|%f|%f|%f|%d|%d|%d|%d|%d|%d|%s",id, ticker,entryPrice, stopLoss, 
      takeProfit, accountSize, moneyAvailable, risk, tradeIsFixed, shares, profit, loss, date.hours, date.minutes, 
      date.seconds, date.day, date.month, date.year, reasons);
#endif

            errorControl = trade_setId(trade, id);
            if(errorControl == ERR){
                tradeList_destroyList(trade_manager->openTrades);    
                printf("\nError setting the read variables of the pending trades. Returning ERR...\n");
                trade_freeTrade(trade);
                fclose(f);
                return ERR;
            }    
            errorControl = trade_setTicker(trade, ticker);
            if(errorControl == ERR){
                tradeList_destroyList(trade_manager->openTrades);
                printf("\nError setting the read variables of the pending trades. Returning ERR...\n");
                trade_freeTrade(trade);
                fclose(f);
                return ERR;
            }        
            errorControl = trade_setEntryPrice(trade, entryPrice);    
            if(errorControl == ERR){
                tradeList_destroyList(trade_manager->openTrades);
                printf("\nError setting the read variables of the pending trades. Returning ERR...\n");
                trade_freeTrade(trade);
                fclose(f);
                return ERR;
            }    
            errorControl = trade_setStopLoss(trade, stopLoss);    
            if(errorControl == ERR){
                tradeList_destroyList(trade_manager->openTrades);
                printf("\nError setting the read variables of the pending trades. Returning ERR...\n");
                trade_freeTrade(trade);
                fclose(f);
                return ERR;
            }    
            errorControl = trade_setTakeProfit(trade, takeProfit);    
            if(errorControl == ERR){
                tradeList_destroyList(trade_manager->openTrades);
                printf("\nError setting the read variables of the pending trades. Returning ERR...\n");
                trade_freeTrade(trade);
                fclose(f);
                return ERR;
            }    
            errorControl = trade_setAccountSize(trade, accountSize);    
            if(errorControl == ERR){
                tradeList_destroyList(trade_manager->openTrades);
                printf("\nError setting the read variables of the pending trades. Returning ERR...\n");
                trade_freeTrade(trade);
                fclose(f);
                return ERR;
            }    
            errorControl = trade_setMoneyAvailable(trade, moneyAvailable);    
            if(errorControl == ERR){
                tradeList_destroyList(trade_manager->openTrades);
                printf("\nError setting the read variables of the pending trades. Returning ERR...\n");
                trade_freeTrade(trade);
                fclose(f);
                return ERR;
            }    
            errorControl = trade_setRisk(trade, risk);    
            if(errorControl == ERR){
                tradeList_destroyList(trade_manager->openTrades);
                printf("\nError setting the read variables of the pending trades. Returning ERR...\n");
                trade_freeTrade(trade);
                fclose(f);
                return ERR;
            }    
            errorControl = trade_setFixedTrade(trade, tradeIsFixed);
            if(errorControl == ERR){
                tradeList_destroyList(trade_manager->openTrades);
                printf("\nError setting the read variables of the pending trades. Returning ERR...\n");
                trade_freeTrade(trade);
                fclose(f);
                return ERR;
            }    
            errorControl = trade_setShares(trade, shares);
            if(errorControl == ERR){
                tradeList_destroyList(trade_manager->openTrades);
                printf("\nError setting the read variables of the pending trades. Returning ERR...\n");
                trade_freeTrade(trade);
                fclose(f);
                return ERR;
            }    
            errorControl = trade_setProfit(trade, profit);
            if(errorControl == ERR){
                tradeList_destroyList(trade_manager->openTrades);
                trade_freeTrade(trade);
                printf("\nError setting the read variables of the pending trades. Returning ERR...\n");
                fclose(f);
                return ERR;
            }    
            errorControl = trade_setLoss(trade, loss);
            if(errorControl == ERR){
                tradeList_destroyList(trade_manager->openTrades);
                printf("\nError setting the read variables of the pending trades. Returning ERR...\n");
                trade_freeTrade(trade);
                fclose(f);
                return ERR;
            }    
            errorControl = trade_setDate(trade, date);
            if(errorControl == ERR){
                tradeList_destroyList(trade_manager->openTrades);    
                printf("\nError setting the read variables of the pending trades. Returning ERR...\n");
                trade_freeTrade(trade);
                fclose(f);
                return ERR;
            }
            errorControl = trade_setReasonsToEnter(trade, reasons);
            if(errorControl == ERR){
                tradeList_destroyList(trade_manager->openTrades);    
                printf("\nError setting the read variables of the pending trades. Returning ERR...\n");
                trade_freeTrade(trade);
                fclose(f);
                return ERR;
            }            
    
            errorControl = tradeList_insertTrade(trade_manager->openTrades, trade);
            if(errorControl == ERR){
                tradeList_destroyList(trade_manager->openTrades);
                printf("\nError setting the read variables of the pending trades. Returning ERR...\n");
                trade_freeTrade(trade);
                fclose(f);
                return ERR;
            }
        }
    }
    fclose(f);
    trade_freeTrade(trade);

    return OK;
}

status trade_manager_readHistoryFromFile(Trade_manager * trade_manager, char* file){

    
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

    Trade * trade = NULL;
    char line[CHAR_MAX];
    char * toks;

    Date date;
    char reasons[MAX_STRING];

    char result;
    char notes[MAX_STRING];

    FILE *f = NULL;
    status errorControl;

    if(!trade_manager || !file){
        printf("\nWrong arguments passed to the readPendingFromFile function, returning NULL");
        return ERR;
    } 

    trade_manager->historyTrades = tradeList_newTradeList();
    if(!trade_manager->historyTrades){
        printf("\nError allocating memory for a new list of trades. Returning ERR\n");
        return ERR;
    }


    f = fopen(file, "r");
    if(!f){
        printf("\n Error loading the pending trading. Returning ERR...\n");
        tradeList_destroyList(trade_manager->historyTrades);
        return ERR;
    }

    trade = trade_newTrade(NO_ID);
    if(!trade){
        printf("\nError  allocating memory for a new trade variable in trade_manager_readPendingFromFile. Returning ERR...\n");
        fclose(f);
        tradeList_destroyList(trade_manager->historyTrades);
        return ERR;
    }
    
    while(fgets(line, CHAR_MAX, f)){
        if (strncmp("#o:", line, 3) == 0)
        {
            toks = strtok(line + 3, "|");
            id = atoi(toks);
            toks = strtok(NULL, "|");
            strcpy(ticker, toks);
            toks = strtok(NULL, "|");
            entryPrice = atol(toks);
            toks = strtok(NULL, "|");
            stopLoss = atol(toks);
            toks = strtok(NULL, "|");
            takeProfit = atol(toks);  
            toks = strtok(NULL, "|");
            accountSize = atol(toks);
            toks = strtok(NULL, "|");
            moneyAvailable = atol(toks);
            toks = strtok(NULL, "|");
            risk = atol(toks);
            toks = strtok(NULL, "|");
            tradeIsFixed = (boolean)atoi(toks);
            toks = strtok(NULL, "|");
            shares = atol(toks);
            toks = strtok(NULL, "|");
            profit = atol(toks);
            toks = strtok(NULL, "|");
            loss = atol(toks);
            toks = strtok(NULL, "|");
            date.hours = atoi(toks);
            toks = strtok(NULL, "|");
            date.minutes = atoi(toks);
            toks = strtok(NULL, "|");
            date.seconds = atoi(toks);
            toks = strtok(NULL, "|");
            date.day = atoi(toks);
            toks = strtok(NULL, "|");
            date.month = atoi(toks);
            toks = strtok(NULL, "|");
            date.year = atoi(toks);
            toks = strtok(NULL, "|");
            strcpy(reasons, toks);
            toks = strtok(NULL, "|");
            result = toks[0];
            toks = strtok(NULL, "|");
            strcpy(notes, toks);


    #ifdef DEBUG
      printf("Leido: %d|%s|%f|%f|%f|%f|%f|%f|%d|%f|%f|%f|%d|%d|%d|%d|%d|%d|%s|%c|%s|",id, ticker,entryPrice, stopLoss, 
      takeProfit, accountSize, moneyAvailable, risk, tradeIsFixed, shares, profit, loss, date.hours, date.minutes, 
      date.seconds, date.day, date.month, date.year, reasons, result, notes);
#endif

            errorControl = trade_setId(trade, id);
            if(errorControl == ERR){
                tradeList_destroyList(trade_manager->historyTrades);    
                printf("\nError setting the read variables of the pending trades. Returning ERR...\n");
                trade_freeTrade(trade);
                fclose(f);
                return ERR;
            }    
            errorControl = trade_setTicker(trade, ticker);
            if(errorControl == ERR){
                tradeList_destroyList(trade_manager->historyTrades);
                printf("\nError setting the read variables of the pending trades. Returning ERR...\n");
                trade_freeTrade(trade);
                fclose(f);
                return ERR;
            }        
            errorControl = trade_setEntryPrice(trade, entryPrice);    
            if(errorControl == ERR){
                tradeList_destroyList(trade_manager->historyTrades);
                printf("\nError setting the read variables of the pending trades. Returning ERR...\n");
                trade_freeTrade(trade);
                fclose(f);
                return ERR;
            }    
            errorControl = trade_setStopLoss(trade, stopLoss);    
            if(errorControl == ERR){
                tradeList_destroyList(trade_manager->historyTrades);
                printf("\nError setting the read variables of the pending trades. Returning ERR...\n");
                trade_freeTrade(trade);
                fclose(f);
                return ERR;
            }    
            errorControl = trade_setTakeProfit(trade, takeProfit);    
            if(errorControl == ERR){
                tradeList_destroyList(trade_manager->historyTrades);
                printf("\nError setting the read variables of the pending trades. Returning ERR...\n");
                trade_freeTrade(trade);
                fclose(f);
                return ERR;
            }    
            errorControl = trade_setAccountSize(trade, accountSize);    
            if(errorControl == ERR){
                tradeList_destroyList(trade_manager->historyTrades);
                printf("\nError setting the read variables of the pending trades. Returning ERR...\n");
                trade_freeTrade(trade);
                fclose(f);
                return ERR;
            }    
            errorControl = trade_setMoneyAvailable(trade, moneyAvailable);    
            if(errorControl == ERR){
                tradeList_destroyList(trade_manager->historyTrades);
                printf("\nError setting the read variables of the pending trades. Returning ERR...\n");
                trade_freeTrade(trade);
                fclose(f);
                return ERR;
            }    
            errorControl = trade_setRisk(trade, risk);    
            if(errorControl == ERR){
                tradeList_destroyList(trade_manager->historyTrades);
                printf("\nError setting the read variables of the pending trades. Returning ERR...\n");
                trade_freeTrade(trade);
                fclose(f);
                return ERR;
            }    
            errorControl = trade_setFixedTrade(trade, tradeIsFixed);
            if(errorControl == ERR){
                tradeList_destroyList(trade_manager->historyTrades);
                printf("\nError setting the read variables of the pending trades. Returning ERR...\n");
                trade_freeTrade(trade);
                fclose(f);
                return ERR;
            }    
            errorControl = trade_setShares(trade, shares);
            if(errorControl == ERR){
                tradeList_destroyList(trade_manager->historyTrades);
                printf("\nError setting the read variables of the pending trades. Returning ERR...\n");
                trade_freeTrade(trade);
                fclose(f);
                return ERR;
            }    
            errorControl = trade_setProfit(trade, profit);
            if(errorControl == ERR){
                tradeList_destroyList(trade_manager->historyTrades);
                trade_freeTrade(trade);
                printf("\nError setting the read variables of the pending trades. Returning ERR...\n");
                fclose(f);
                return ERR;
            }    
            errorControl = trade_setLoss(trade, loss);
            if(errorControl == ERR){
                tradeList_destroyList(trade_manager->historyTrades);
                printf("\nError setting the read variables of the pending trades. Returning ERR...\n");
                trade_freeTrade(trade);
                fclose(f);
                return ERR;
            }    
            errorControl = trade_setDate(trade, date);
            if(errorControl == ERR){
                tradeList_destroyList(trade_manager->historyTrades);    
                printf("\nError setting the read variables of the pending trades. Returning ERR...\n");
                trade_freeTrade(trade);
                fclose(f);
                return ERR;
            }
            errorControl = trade_setReasonsToEnter(trade, reasons);
            if(errorControl == ERR){
                tradeList_destroyList(trade_manager->historyTrades);    
                printf("\nError setting the read variables of the pending trades. Returning ERR...\n");
                trade_freeTrade(trade);
                fclose(f);
                return ERR;
            }

            errorControl = trade_setResult(trade, result);
            if(errorControl == ERR){
                tradeList_destroyList(trade_manager->historyTrades);    
                printf("\nError setting the read variables of the pending trades. Returning ERR...\n");
                trade_freeTrade(trade);
                fclose(f);
                return ERR;
            }

            errorControl = trade_setNotes(trade, notes);
            if(errorControl == ERR){
                tradeList_destroyList(trade_manager->historyTrades);    
                printf("\nError setting the read variables of the pending trades. Returning ERR...\n");
                trade_freeTrade(trade);
                fclose(f);
                return ERR;
            }              
    
            errorControl = tradeList_insertTrade(trade_manager->historyTrades, trade);
            if(errorControl == ERR){
                tradeList_destroyList(trade_manager->historyTrades);
                printf("\nError setting the read variables of the pending trades. Returning ERR...\n");
                trade_freeTrade(trade);
                fclose(f);
                return ERR;
            }
        }
    }
    fclose(f);
    trade_freeTrade(trade);

    return OK;
}


