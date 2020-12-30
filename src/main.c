#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<time.h>

#include "trade.h"
#include "trade_manager.h"

#define PENDING_LOG_FILE "./log/pending.txt"
#define OPEN_LOG_FILE "./log/open.txt"
#define HISTORY_LOG_FILE "./log/history.txt"

#define MAX_TRADES 100


void menu(int *option);
void menuPending(int *option);

void calculate_trade(Trade_manager *trade_manager);
void view_pending(Trade_manager *trade_manager);
void view_open();
void view_history();

int aleat_num(int inf, int sup);

/*TODO: CALCULA TRADE + FUNCTIONALITY TO ADD TO PENDING*/
int main(){
    int option;
    Trade_manager *trade_manager = NULL;

    srand(time(NULL));
    trade_manager = trade_manager_newTradeManager();

    if(!trade_manager){
        printf("\nCouldn't allocate memory for a trade manager variable. Finishing the program...");
        return -1;
    }
    if(trade_manager_readPendingFromFile(trade_manager, PENDING_LOG_FILE) == ERR){
        printf("\nCouldn't read the pending log file. Finishing the program...");
        trade_manager_destroyManager(trade_manager);
        return -1;
    }
    if(trade_manager_readOpenFromFile(trade_manager, OPEN_LOG_FILE) == ERR){
        printf("\nCouldn't read the open log file. Finishing the program...");
        trade_manager_destroyManager(trade_manager);
        return -1;
    }
    if(trade_manager_readHistoryFromFile(trade_manager, HISTORY_LOG_FILE) == ERR){
        printf("\nCouldn't read the history log file. Finishing the program...");
        trade_manager_destroyManager(trade_manager);
        return -1;
    }


    do{
        do{
            menu(&option);
        }while(option < 1 && option > 5);

        switch(option){
            case 1:
                calculate_trade(trade_manager);
                break;
            case 2:
                view_pending(trade_manager);
                break;
            case 3:
                view_open();
                break;
            case 4:
                view_history();
                break;
            case 5:
                break;
        }
        
      
    
    }while(option != 5);

    printf("\n\nExitings the program.....\n\n");

    trade_manager_destroyManager(trade_manager);
    
    return 0;
}

void menu(int *option){

    if(!option) return;
    
    printf("\n==============================================================\n");
    printf("\nWelcome to the trade handler...\n");

    printf("\n\t1. New trade");
    printf("\n\t2. View pending");
    printf("\n\t3. View current positions");
    printf("\n\t4. View history");
    printf("\n\t5. Exit");

    printf("\n\nChoose an option: ");
    scanf("\n%d", option);
    printf("\n==============================================================\n");
}

void calculate_trade(Trade_manager *trade_manager){
    
    char ticker[6];
    double entryPrice;
    double stopLoss;
    double takeProfit;
    boolean tradeIsFixed;
    double accountSize;
    double moneyAvailable;
    double risk;
    double maxRisk;
    int id;
    int numTrades;

    double shares;
    double profit;
    double loss;
    double maxShares;

    Trade * aux;
    char option;
    int flag;
    int i;
    TradeList *pending = NULL;

       if(!trade_manager){
        printf("\nWrong arguments passed to calculate a trade. Returning...");
        return;
    }

    aux = trade_newTrade(NO_ID);
    if(!aux){
        printf("\nCouldn't allocate memory for a new trade to calculate. Returning...");
        return;
    }


    printf("\nIntroduce the ticker for the stock: ");
    scanf("%s", ticker);

    do{
        printf("\nIntroduce the account value: ");
        scanf("\n%lf", &accountSize);
    }while(accountSize < 0);

    do{
        printf("Introduce  the available money: ");
        scanf("\n%lf", &moneyAvailable);
    }while(moneyAvailable < 0 || moneyAvailable > accountSize);

    accountSize = accountSize*EURO_TO_DOLAR;
    moneyAvailable = moneyAvailable*EURO_TO_DOLAR;

    do{
        printf("\nIntroduce the entry price of the position: ");
        scanf("\n%lf", &entryPrice);
    }while(entryPrice < 0);

    do{
        printf("Introduce the stopLoss: ");
        scanf("\n%lf", &stopLoss);
    }while(stopLoss < 0 || stopLoss > entryPrice);

    do{
        printf("Any price target for  the trade? [Y/N]");
        scanf("\n%c", &option);
    }while(option != 'Y' && option != 'N' && option != 'y' && option != 'n');

    if(option == 'Y' || option == 'y') tradeIsFixed = TRUE;
    else{
        takeProfit = 0;
        tradeIsFixed = FALSE;
    } 
    
    if(tradeIsFixed == TRUE){

        do{
            printf("Introduce the price target: ");
            scanf("\n%lf", &takeProfit);
        }while(takeProfit < entryPrice);

    }

    maxShares = (0.95*moneyAvailable)/entryPrice; /*0.95 means the percentage of the total capital my broker allows me to risk*/
    maxRisk = 100*maxShares*(entryPrice - stopLoss);
    maxRisk /= accountSize;
   
    do{
        printf("\nHow much capital do you want to risk?(Between 1%% and %.2f%%): ", maxRisk);
        scanf("\n%lf", &risk);
    }while(risk < 1 || risk > maxRisk);

    if (risk > maxRisk){
        printf("\nThat's one weird trade m8, you can't risk more than 1%%, try again...\n\n\n\n");
        trade_freeTrade(aux);
        return;
    }
    

    shares = accountSize * (risk/100)/ (entryPrice-stopLoss);
    if(tradeIsFixed ==TRUE) profit = (takeProfit - entryPrice) * shares * DOLAR_TO_EURO;
    loss = (entryPrice - stopLoss) * shares * DOLAR_TO_EURO;

    accountSize = accountSize*DOLAR_TO_EURO;
    moneyAvailable = moneyAvailable*DOLAR_TO_EURO; 

    trade_setAccountSize(aux, accountSize);
    trade_setEntryPrice(aux, entryPrice);
    trade_setFixedTrade(aux, tradeIsFixed);
    trade_setLoss(aux,loss);
    trade_setMoneyAvailable(aux, moneyAvailable);
    trade_setRisk(aux, risk);
    trade_setShares(aux, shares);
    trade_setStopLoss(aux, stopLoss);
    trade_setTicker(aux, ticker);
    if(tradeIsFixed == TRUE){
        trade_setProfit(aux, profit);
        trade_setTakeProfit(aux, takeProfit);
    }
    else{
        trade_setProfit(aux, 0);
        trade_setTakeProfit(aux, 0);
    }
    printf("\n--------------------------------------------------------------------------------\n");
    trade_printPendingTrade(aux);

    printf("\n--------------------------------------------------------------------------------\n");
    do{
        printf("\nDo you want to save this trade to the pending trades? [Y/N] ");
        scanf("\n%c", &option);
    }while(option != 'Y' && option != 'N' && option != 'y' && option != 'n');

    pending = trade_manager_getPendingTrades(trade_manager);

    if(option == 'Y' || option == 'y'){
        flag = 0;
        numTrades = tradeList_getNumberOfTrades(pending);
        while(flag == 0){
            flag = 1;
            id = aleat_num(1, MAX_TRADES);
            for(i = 0; i < numTrades; i++){
                if(trade_getId(tradeList_getTradeByIndex(pending, i)) == id) flag = 0;
            }
        }
        printf("ID: %d", id);
        trade_setId(aux, id);
        tradeList_insertTrade(pending, aux);
    }
    trade_freeTrade(aux);

    printf("\n\nFinishing the calculator...\n\n\n\n");
    return;

}

void view_pending(Trade_manager *trade_manager){
    
    int option;
    int id;
    TradeList *pending;

    pending = trade_manager_getPendingTrades(trade_manager);
    do{

        do{
            menuPending(&option);
        }while(option < 1 || option > 5);

        switch(option){
            case 1:
                tradeList_printList(pending);
                break;
            
            case 2:
                printf("\nIntroduce the id of the trade you want to delete: ");
                scanf("\n%d", &id);
                if(tradeList_deleteTrade(pending, id) == ERR){
                    printf("\nCouldn't delete the trade with the id given.");
                }
                else printf("\nTrade Successfully deleted");
            
            case 3:
                break;
        }
    }while(option != 5);
    

}

void view_open(){

}

void view_history(){

}

void menuPending(int *option){
    
    if(!option) return;
    printf("\n--------------------------------------------------------------------------------\n");
    printf("\nWhat do you want to do?\n");
    printf("\n\t1.View summary of pending trades");
    printf("\n\t2.Delete a trade");
    printf("\n\t3.Open a position (will delete from pending trades)");
    printf("\n\t4.Generate and open a text file with all the pending trades");
    printf("\n\t5.Exit");
    printf("\n\nChoose an option: ");
    scanf("\n%d", option);
    printf("\n--------------------------------------------------------------------------------\n");

}

int aleat_num(int inf, int sup){
  return rand()/((double)RAND_MAX+1.)*(sup-inf+1)+inf;
}