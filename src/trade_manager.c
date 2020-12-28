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
        printf("\nWrong arguments passed to the readOpenFromFile function, returning NULL");
        return ERR;
    } 

    trade_manager->openTrades = tradeList_newTradeList();
    if(!trade_manager->openTrades){
        printf("\nError allocating memory for a new list of trades. Returning ERR\n");
        return ERR;
    }


    f = fopen(file, "r");
    if(!f){
        printf("\n Error loading the Open trading. Returning ERR...\n");
        tradeList_destroyList(trade_manager->openTrades);
        return ERR;
    }

    trade = trade_newTrade(NO_ID);
    if(!trade){
        printf("\nError  allocating memory for a new trade variable in trade_manager_readOpenFromFile. Returning ERR...\n");
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
                printf("\nError setting the read variables of the Open trades. Returning ERR...\n");
                trade_freeTrade(trade);
                fclose(f);
                return ERR;
            }    
            errorControl = trade_setTicker(trade, ticker);
            if(errorControl == ERR){
                tradeList_destroyList(trade_manager->openTrades);
                printf("\nError setting the read variables of the Open trades. Returning ERR...\n");
                trade_freeTrade(trade);
                fclose(f);
                return ERR;
            }        
            errorControl = trade_setEntryPrice(trade, entryPrice);    
            if(errorControl == ERR){
                tradeList_destroyList(trade_manager->openTrades);
                printf("\nError setting the read variables of the Open trades. Returning ERR...\n");
                trade_freeTrade(trade);
                fclose(f);
                return ERR;
            }    
            errorControl = trade_setStopLoss(trade, stopLoss);    
            if(errorControl == ERR){
                tradeList_destroyList(trade_manager->openTrades);
                printf("\nError setting the read variables of the Open trades. Returning ERR...\n");
                trade_freeTrade(trade);
                fclose(f);
                return ERR;
            }    
            errorControl = trade_setTakeProfit(trade, takeProfit);    
            if(errorControl == ERR){
                tradeList_destroyList(trade_manager->openTrades);
                printf("\nError setting the read variables of the Open trades. Returning ERR...\n");
                trade_freeTrade(trade);
                fclose(f);
                return ERR;
            }    
            errorControl = trade_setAccountSize(trade, accountSize);    
            if(errorControl == ERR){
                tradeList_destroyList(trade_manager->openTrades);
                printf("\nError setting the read variables of the Open trades. Returning ERR...\n");
                trade_freeTrade(trade);
                fclose(f);
                return ERR;
            }    
            errorControl = trade_setMoneyAvailable(trade, moneyAvailable);    
            if(errorControl == ERR){
                tradeList_destroyList(trade_manager->openTrades);
                printf("\nError setting the read variables of the Open trades. Returning ERR...\n");
                trade_freeTrade(trade);
                fclose(f);
                return ERR;
            }    
            errorControl = trade_setRisk(trade, risk);    
            if(errorControl == ERR){
                tradeList_destroyList(trade_manager->openTrades);
                printf("\nError setting the read variables of the Open trades. Returning ERR...\n");
                trade_freeTrade(trade);
                fclose(f);
                return ERR;
            }    
            errorControl = trade_setFixedTrade(trade, tradeIsFixed);
            if(errorControl == ERR){
                tradeList_destroyList(trade_manager->openTrades);
                printf("\nError setting the read variables of the Open trades. Returning ERR...\n");
                trade_freeTrade(trade);
                fclose(f);
                return ERR;
            }    
            errorControl = trade_setShares(trade, shares);
            if(errorControl == ERR){
                tradeList_destroyList(trade_manager->openTrades);
                printf("\nError setting the read variables of the Open trades. Returning ERR...\n");
                trade_freeTrade(trade);
                fclose(f);
                return ERR;
            }    
            errorControl = trade_setProfit(trade, profit);
            if(errorControl == ERR){
                tradeList_destroyList(trade_manager->openTrades);
                trade_freeTrade(trade);
                printf("\nError setting the read variables of the Open trades. Returning ERR...\n");
                fclose(f);
                return ERR;
            }    
            errorControl = trade_setLoss(trade, loss);
            if(errorControl == ERR){
                tradeList_destroyList(trade_manager->openTrades);
                printf("\nError setting the read variables of the Open trades. Returning ERR...\n");
                trade_freeTrade(trade);
                fclose(f);
                return ERR;
            }    
            errorControl = trade_setDate(trade, date);
            if(errorControl == ERR){
                tradeList_destroyList(trade_manager->openTrades);    
                printf("\nError setting the read variables of the Open trades. Returning ERR...\n");
                trade_freeTrade(trade);
                fclose(f);
                return ERR;
            }
            errorControl = trade_setReasonsToEnter(trade, reasons);
            if(errorControl == ERR){
                tradeList_destroyList(trade_manager->openTrades);    
                printf("\nError setting the read variables of the Open trades. Returning ERR...\n");
                trade_freeTrade(trade);
                fclose(f);
                return ERR;
            }            
    
            errorControl = tradeList_insertTrade(trade_manager->openTrades, trade);
            if(errorControl == ERR){
                tradeList_destroyList(trade_manager->openTrades);
                printf("\nError setting the read variables of the Open trades. Returning ERR...\n");
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
        printf("\nWrong arguments passed to the readHistoryFromFile function, returning NULL");
        return ERR;
    } 

    trade_manager->historyTrades = tradeList_newTradeList();
    if(!trade_manager->historyTrades){
        printf("\nError allocating memory for a new list of trades. Returning ERR\n");
        return ERR;
    }


    f = fopen(file, "r");
    if(!f){
        printf("\n Error loading the history trading. Returning ERR...\n");
        tradeList_destroyList(trade_manager->historyTrades);
        return ERR;
    }

    trade = trade_newTrade(NO_ID);
    if(!trade){
        printf("\nError allocating memory for a new trade variable in trade_manager_readHistoryFromFile. Returning ERR...\n");
        fclose(f);
        tradeList_destroyList(trade_manager->historyTrades);
        return ERR;
    }
    
    while(fgets(line, CHAR_MAX, f)){
        if (strncmp("#h:", line, 3) == 0)
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
                printf("\nError setting the read variables of the History trades. Returning ERR...\n");
                trade_freeTrade(trade);
                fclose(f);
                return ERR;
            }    
            errorControl = trade_setTicker(trade, ticker);
            if(errorControl == ERR){
                tradeList_destroyList(trade_manager->historyTrades);
                printf("\nError setting the read variables of the History trades. Returning ERR...\n");
                trade_freeTrade(trade);
                fclose(f);
                return ERR;
            }        
            errorControl = trade_setEntryPrice(trade, entryPrice);    
            if(errorControl == ERR){
                tradeList_destroyList(trade_manager->historyTrades);
                printf("\nError setting the read variables of the History trades. Returning ERR...\n");
                trade_freeTrade(trade);
                fclose(f);
                return ERR;
            }    
            errorControl = trade_setStopLoss(trade, stopLoss);    
            if(errorControl == ERR){
                tradeList_destroyList(trade_manager->historyTrades);
                printf("\nError setting the read variables of the History trades. Returning ERR...\n");
                trade_freeTrade(trade);
                fclose(f);
                return ERR;
            }    
            errorControl = trade_setTakeProfit(trade, takeProfit);    
            if(errorControl == ERR){
                tradeList_destroyList(trade_manager->historyTrades);
                printf("\nError setting the read variables of the History trades. Returning ERR...\n");
                trade_freeTrade(trade);
                fclose(f);
                return ERR;
            }    
            errorControl = trade_setAccountSize(trade, accountSize);    
            if(errorControl == ERR){
                tradeList_destroyList(trade_manager->historyTrades);
                printf("\nError setting the read variables of the History trades. Returning ERR...\n");
                trade_freeTrade(trade);
                fclose(f);
                return ERR;
            }    
            errorControl = trade_setMoneyAvailable(trade, moneyAvailable);    
            if(errorControl == ERR){
                tradeList_destroyList(trade_manager->historyTrades);
                printf("\nError setting the read variables of the History trades. Returning ERR...\n");
                trade_freeTrade(trade);
                fclose(f);
                return ERR;
            }    
            errorControl = trade_setRisk(trade, risk);    
            if(errorControl == ERR){
                tradeList_destroyList(trade_manager->historyTrades);
                printf("\nError setting the read variables of the History trades. Returning ERR...\n");
                trade_freeTrade(trade);
                fclose(f);
                return ERR;
            }    
            errorControl = trade_setFixedTrade(trade, tradeIsFixed);
            if(errorControl == ERR){
                tradeList_destroyList(trade_manager->historyTrades);
                printf("\nError setting the read variables of the History trades. Returning ERR...\n");
                trade_freeTrade(trade);
                fclose(f);
                return ERR;
            }    
            errorControl = trade_setShares(trade, shares);
            if(errorControl == ERR){
                tradeList_destroyList(trade_manager->historyTrades);
                printf("\nError setting the read variables of the History trades. Returning ERR...\n");
                trade_freeTrade(trade);
                fclose(f);
                return ERR;
            }    
            errorControl = trade_setProfit(trade, profit);
            if(errorControl == ERR){
                tradeList_destroyList(trade_manager->historyTrades);
                trade_freeTrade(trade);
                printf("\nError setting the read variables of the History trades. Returning ERR...\n");
                fclose(f);
                return ERR;
            }    
            errorControl = trade_setLoss(trade, loss);
            if(errorControl == ERR){
                tradeList_destroyList(trade_manager->historyTrades);
                printf("\nError setting the read variables of the History trades. Returning ERR...\n");
                trade_freeTrade(trade);
                fclose(f);
                return ERR;
            }    
            errorControl = trade_setDate(trade, date);
            if(errorControl == ERR){
                tradeList_destroyList(trade_manager->historyTrades);    
                printf("\nError setting the read variables of the History trades. Returning ERR...\n");
                trade_freeTrade(trade);
                fclose(f);
                return ERR;
            }
            errorControl = trade_setReasonsToEnter(trade, reasons);
            if(errorControl == ERR){
                tradeList_destroyList(trade_manager->historyTrades);    
                printf("\nError setting the read variables of the History trades. Returning ERR...\n");
                trade_freeTrade(trade);
                fclose(f);
                return ERR;
            }

            errorControl = trade_setResult(trade, result);
            if(errorControl == ERR){
                tradeList_destroyList(trade_manager->historyTrades);    
                printf("\nError setting the read variables of the History trades. Returning ERR...\n");
                trade_freeTrade(trade);
                fclose(f);
                return ERR;
            }

            errorControl = trade_setNotes(trade, notes);
            if(errorControl == ERR){
                tradeList_destroyList(trade_manager->historyTrades);    
                printf("\nError setting the read variables of the History trades. Returning ERR...\n");
                trade_freeTrade(trade);
                fclose(f);
                return ERR;
            }              
    
            errorControl = tradeList_insertTrade(trade_manager->historyTrades, trade);
            if(errorControl == ERR){
                tradeList_destroyList(trade_manager->historyTrades);
                printf("\nError setting the read variables of the History trades. Returning ERR...\n");
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

status trade_manager_savePendingTrades(Trade_manager * trade_manager, char * file){

    FILE *f;
    int numTrades;
    int i = 0;

    Trade * trade; 

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

    if(!trade_manager || !file){
        printf("\nWrong arguments passed to the function to save Pending trades. Returning ERR...");
        return ERR;
    }
    if(!trade_manager->pendingTrades){
        printf("\nThe list for the pending trades points NULL. Returning ERR...");
    }

    /*Remove the file to allow fopen to create a new empty one with the modifications*/
    remove(file);

    f = fopen(file, "w");

    if(!f){
        printf("\nError opening the file to save the pending trades. Returning ERR...");
        return ERR;
    }

    numTrades = tradeList_getNumberOfTrades(trade_manager->pendingTrades);
    if(numTrades == ERR_RETURN){
        printf("\nError getting the number of trades lo save the pending trades info. Returning ERR..."); 
        fclose(f);
        return ERR;   
    }

    while(i < numTrades){

        trade = tradeList_getTradeByIndex(trade_manager->pendingTrades, i);
        if(!trade){
            printf("\nError getting the trade to save it. Returning ERR...");
            return ERR;           
        }


        id = trade_getId(trade);
        strcpy(ticker, trade_getTicker(trade));
        entryPrice = trade_getEntryPrice(trade);
        stopLoss = trade_getStopLoss(trade);
        takeProfit = trade_getTakeProfit(trade);
        accountSize = trade_getAccountSize(trade);
        moneyAvailable = trade_getMoneyAvailable(trade);
        risk = trade_getRisk(trade);
        tradeIsFixed = trade_getTradeIsFixed(trade);
        shares = trade_getShares(trade);
        profit = trade_getProfit(trade);
        loss = trade_getLoss(trade);

        fprintf(f,"#p:%d|%s|%f|%f|%f|%f|%f|%f|%d|%f|%f|%f\n",id, ticker,entryPrice, stopLoss, 
        takeProfit, accountSize, moneyAvailable, risk, tradeIsFixed, shares, profit, loss);
        
        i++;
    }

    return OK;

}

status trade_manager_saveOpenTrades(Trade_manager * trade_manager, char * file){

    FILE *f;
    int numTrades;
    int i = 0;

    Trade * trade; 

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

    Date date;
    char reasons[MAX_STRING];

    if(!trade_manager || !file){
        printf("\nWrong arguments passed to the function to save Open trades. Returning ERR...");
        return ERR;
    }
    if(!trade_manager->openTrades){
        printf("\nThe list for the open trades points NULL. Returning ERR...");
    }

    /*Remove the file to allow fopen to create a new empty one with the modifications*/
    remove(file);

    f = fopen(file, "w");

    if(!f){
        printf("\nError opening the file to save the open trades. Returning ERR...");
        return ERR;
    }

    numTrades = tradeList_getNumberOfTrades(trade_manager->openTrades);
    if(numTrades == ERR_RETURN){
        printf("\nError getting the number of trades lo save the open trades info. Returning ERR..."); 
        fclose(f);
        return ERR;   
    }

    while(i < numTrades){

        trade = tradeList_getTradeByIndex(trade_manager->openTrades, i);
        if(!trade){
            printf("\nError getting the trade to save it. Returning ERR...");
            return ERR;           
        }


        id = trade_getId(trade);
        strcpy(ticker, trade_getTicker(trade));
        entryPrice = trade_getEntryPrice(trade);
        stopLoss = trade_getStopLoss(trade);
        takeProfit = trade_getTakeProfit(trade);
        accountSize = trade_getAccountSize(trade);
        moneyAvailable = trade_getMoneyAvailable(trade);
        risk = trade_getRisk(trade);
        tradeIsFixed = trade_getTradeIsFixed(trade);
        shares = trade_getShares(trade);
        profit = trade_getProfit(trade);
        loss = trade_getLoss(trade);
        strcpy(reasons, trade_getReasonsToEnter(trade));
        date = trade_getDate(trade);

        fprintf(f,"#o:%d|%s|%f|%f|%f|%f|%f|%f|%d|%f|%f|%f|%d|%d|%d|%d|%d|%d|%s\n",id, ticker,entryPrice, stopLoss, 
      takeProfit, accountSize, moneyAvailable, risk, tradeIsFixed, shares, profit, loss, date.hours, date.minutes, 
      date.seconds, date.day, date.month, date.year, reasons);
        
        i++;
    }

    return OK;

}

status trade_manager_saveHistoryTrades(Trade_manager * trade_manager, char * file){

    FILE *f;
    int numTrades;
    int i = 0;

    Trade * trade; 

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

    Date date;
    char reasons[MAX_STRING];

    char result;
    char notes[MAX_STRING];

    if(!trade_manager || !file){
        printf("\nWrong arguments passed to the function to save Open trades. Returning ERR...");
        return ERR;
    }
    if(!trade_manager->openTrades){
        printf("\nThe list for the open trades points NULL. Returning ERR...");
    }

    /*Remove the file to allow fopen to create a new empty one with the modifications*/
    remove(file);

    f = fopen(file, "w");

    if(!f){
        printf("\nError opening the file to save the open trades. Returning ERR...");
        return ERR;
    }

    numTrades = tradeList_getNumberOfTrades(trade_manager->openTrades);
    if(numTrades == ERR_RETURN){
        printf("\nError getting the number of trades lo save the open trades info. Returning ERR..."); 
        fclose(f);
        return ERR;   
    }

    while(i < numTrades){

        trade = tradeList_getTradeByIndex(trade_manager->openTrades, i);
        if(!trade){
            printf("\nError getting the trade to save it. Returning ERR...");
            return ERR;           
        }


        id = trade_getId(trade);
        strcpy(ticker, trade_getTicker(trade));
        entryPrice = trade_getEntryPrice(trade);
        stopLoss = trade_getStopLoss(trade);
        takeProfit = trade_getTakeProfit(trade);
        accountSize = trade_getAccountSize(trade);
        moneyAvailable = trade_getMoneyAvailable(trade);
        risk = trade_getRisk(trade);
        tradeIsFixed = trade_getTradeIsFixed(trade);
        shares = trade_getShares(trade);
        profit = trade_getProfit(trade);
        loss = trade_getLoss(trade);
        strcpy(reasons, trade_getReasonsToEnter(trade));
        date = trade_getDate(trade);
        result = trade_getResult(trade);
        strcpy(notes, trade_getNotes(trade));


        fprintf(f,"#h:%d|%s|%f|%f|%f|%f|%f|%f|%d|%f|%f|%f|%d|%d|%d|%d|%d|%d|%s|%c|%s\n",id, ticker,entryPrice, stopLoss, 
      takeProfit, accountSize, moneyAvailable, risk, tradeIsFixed, shares, profit, loss, date.hours, date.minutes, 
      date.seconds, date.day, date.month, date.year, reasons, result, notes);
        
        i++;
    }

    return OK;

}

