#include<stdio.h>

#include "trade.h"
#include "trade_manager.h"

#define PENDING_LOG_FILE "./log/pending.txt"
#define OPEN_LOG_FILE "./log/open.txt"
#define HISTORY_LOG_FILE "./log/history.txt"

void menu(int *opcion);
void calculate_trade(Trade_manager *trade_manager);
void view_pending();
void view_open();
void view_history();

/*TODO: CALCULA TRADE + FUNCTIONALITY TO ADD TO PENDING*/
int main(){
    int opcion;
    Trade_manager *trade_manager = NULL;

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
            menu(&opcion);
        }while(opcion < 1 && opcion > 5);

        if(opcion == 1){
            calculate_trade(trade_manager);
        }
        else if(opcion == 2){
            view_pending();
        }
        else if(opcion == 3){
            view_open();
        }
        else if(opcion == 4){
            view_history();
        }
    
    }while(opcion != 5);

    printf("\n\nExitings the program.....\n\n");

    trade_manager_destroyManager(trade_manager);
    
    return 0;
}

void menu(int *opcion){
    
    printf("\n==============================================================\n");
    printf("\nWelcome to the trade handler...\n");

    printf("\n\t1. New trade");
    printf("\n\t2. View pending");
    printf("\n\t3. View current positions");
    printf("\n\t4. View history");
    printf("\n\t5. Exit");

    printf("\n\nChoose an option: ");
    scanf("\n%d", opcion);
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

    double shares;
    double profit;
    double loss;
    double maxShares;

    Trade * aux;
    char option;

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

    if(option == 'Y' || option == 'y'){
        tradeList_insertTrade(trade_manager_getPendingTrades(trade_manager), aux);
    }
    trade_freeTrade(aux);

    printf("\n\nFinishing the calculator...\n\n\n\n");
    return;

}

void view_pending(){

}
void view_open(){

}
void view_history(){

}
