#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>

#include "trade.h"
#include "trade_manager.h"

#define PENDING_LOG_FILE "./log/pending.txt"
#define OPEN_LOG_FILE "./log/open.txt"
#define HISTORY_LOG_FILE "./log/history.txt"

#define PENDING_INFO_FILE "PendingTrades"
#define OPEN_INFO_FILE "OpenedTrades"
#define HISTORY_INFO_FILE "HistoryTrades"

#define MAX_TRADES 100


void menu(int *option);
void menuPending(int *option);
void menuOpen(int*option);
void menuHistory(int*option);

void calculate_trade(Trade_manager *trade_manager);
void view_pending(Trade_manager *trade_manager);
void view_open(Trade_manager *trade_manager);
void view_history(Trade_manager *trade_manager);

int aleat_num(int inf, int sup);


int main(){
    int option;
    Trade_manager *trade_manager = NULL;
    char save;

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
                view_open(trade_manager);
                break;
            case 4:
                view_history(trade_manager);
                break;
            case 5:
                do{
                    printf("\nDo you want to save the changes made? [Y/N] ");
                    scanf("\n%c", &save);
                }while(save != 'Y' && save != 'y' && save != 'n' && save != 'N');

                if(save == 'y' || save == 'Y'){
                    if(trade_manager_savePendingTrades(trade_manager, PENDING_LOG_FILE) == ERR) printf("Failed to save the pending trades changes...");
                    if(trade_manager_saveOpenTrades(trade_manager, OPEN_LOG_FILE) == ERR) printf("Failed to save the opened trades changes...");
                    if(trade_manager_saveHistoryTrades(trade_manager, HISTORY_LOG_FILE) == ERR) printf("Failed to save the history trades changes...");
                }
                break;
        }
        
      
    
    }while(option != 5);

    printf("\n\nExitings the program.....\n\n");

    trade_manager_destroyManager(trade_manager);
    
    return 0;
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
    double positionSize;

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
    positionSize = shares*entryPrice*DOLAR_TO_EURO;

    trade_setAccountSize(aux, accountSize);
    trade_setEntryPrice(aux, entryPrice);
    trade_setFixedTrade(aux, tradeIsFixed);
    trade_setLoss(aux,loss);
    trade_setMoneyAvailable(aux, moneyAvailable);
    trade_setRisk(aux, risk);
    trade_setShares(aux, shares);
    trade_setStopLoss(aux, stopLoss);
    trade_setTicker(aux, ticker);
    trade_setPositionSize(aux, positionSize);
    if(tradeIsFixed == TRUE){
        trade_setProfit(aux, profit);
        trade_setTakeProfit(aux, takeProfit);
    }
    else{
        trade_setProfit(aux, 0);
        trade_setTakeProfit(aux, 0);
    }
    printf("\n--------------------------------------------------------------------------------\n");
    trade_printPendingTrade(aux, NULL);
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
    int i = 0;
    int numTrades;
    TradeList *pending;
    Trade * aux;
    FILE *f;
    char openCommand[40];
    char reasons[MAX_STRING];
    Date currentDate;


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
                break;
            case 3:
                printf("\nIntroduce the id of the trade you want to open: ");
                scanf("\n%d", &id);

                aux = tradeList_getTrade(pending, id);
                if(!aux){
                    printf("\nCouldn't find the trade with the id given.");
                    break;
                }
                if(date_setDateToCurrent(&currentDate) == ERR){
                    printf("\nCouldn't get the date to open the trade.");
                    trade_freeTrade(aux);
                    break;
                }
                trade_setDate(aux, currentDate);
                printf("\nIntroduce the reasons to enter the trade: ");
                scanf("\n%[^\n]", reasons);

                if(trade_setReasonsToEnter(aux, reasons) == ERR){
                    printf("\nCouldn't set the reasons to enter the trade.");
                    trade_freeTrade(aux);
                    break;            
                }

                if(tradeList_insertTrade(trade_manager_getOpenTrades(trade_manager), aux) == ERR){
                    printf("\nCouldn't open the trade with the id given.");
                    trade_freeTrade(aux);
                    break;            
                }
                if(tradeList_deleteTrade(pending, id) == ERR){
                    printf("\nCouldn't delete the trade with the id given.");
                }
                else printf("\nTrade Successfully opened");
                trade_freeTrade(aux);
                break;
                
            case 4:
                fclose(fopen(PENDING_INFO_FILE, "w"));
                numTrades = tradeList_getNumberOfTrades(pending);

                printf("\nGenerating the pending trades file...\n");
                
                for(i = 0; i < numTrades; i++){
                    trade_printPendingTrade(tradeList_getTradeByIndex(pending, i), PENDING_INFO_FILE);
                    f = fopen(PENDING_INFO_FILE, "a");
                    if(f)
                    fprintf(f,"\n\n\n");
                    fclose(f);
                }

                strcpy(openCommand, "xdg-open ");
                strcat(openCommand, PENDING_INFO_FILE);
                system(openCommand);


                break;
            case 5: 
                printf("\nExiting the pending trades menu...\n");
        }
    }while(option != 5);
    

}

void view_open(Trade_manager * trade_manager){
    
        int option;
    int id;
    int i = 0;
    int numTrades;
    TradeList *Open;
    Trade * aux;
    FILE *f;
    char openCommand[40];
    char result;
    char notes[MAX_STRING];
    


    Open = trade_manager_getOpenTrades(trade_manager);
    do{

        do{
            menuOpen(&option);
        }while(option < 1 || option > 4);

        switch(option){
            case 1:
                tradeList_printList(Open);
                break;
            

            case 2:
                printf("\nIntroduce the id of the trade you want to close: ");
                scanf("\n%d", &id);

                aux = tradeList_getTrade(Open, id);
                if(!aux){
                    printf("\nCouldn't find the trade with the id given.");
                    break;
                }
                
                do{
                    printf("\n WIN OR LOSS, Are ya winning son?  [W/L] ");
                    scanf("\n%c", &result);
                }while(result != 'W' && result != 'w' && result != 'L' && result != 'l');


                printf("\nAny notes to add to the trade?: ");
                scanf("\n%[^\n]", notes);

                trade_setResult(aux, result);
                trade_setNotes(aux, notes);

                if(tradeList_insertTrade(trade_manager_getHistoryTrades(trade_manager), aux) == ERR){
                    printf("\nCouldn't open the trade with the id given.");
                    trade_freeTrade(aux);
                    break;            
                }
                if(tradeList_deleteTrade(Open, id) == ERR){
                    printf("\nCouldn't delete the trade with the id given.");
                }
                else printf("\nTrade Successfully closed");
                trade_freeTrade(aux);
                break;
                
            case 3:
                fclose(fopen(OPEN_INFO_FILE, "w"));
                numTrades = tradeList_getNumberOfTrades(Open);

                printf("\nGenerating the Opened trades file...\n");
                
                for(i = 0; i < numTrades; i++){
                    trade_printOpenTrade(tradeList_getTradeByIndex(Open, i), OPEN_INFO_FILE);
                    f = fopen(OPEN_INFO_FILE, "a");
                    if(f)
                    fprintf(f,"\n\n\n");
                    fclose(f);
                }

                strcpy(openCommand, "xdg-open ");
                strcat(openCommand, OPEN_INFO_FILE);
                system(openCommand);


                break;
            case 4: 
                printf("\nExiting the opened trades menu...\n");
        }
    }while(option != 4);

}

void view_history(Trade_manager * trade_manager){

    int option;
    int i = 0;
    int numTrades;
    TradeList *history;
    FILE *f;
    char openCommand[40];



    history = trade_manager_getHistoryTrades(trade_manager);
    do{

        do{
            menuHistory(&option);
        }while(option < 1 || option > 3);

        switch(option){
            case 1:
                tradeList_printList(history);
                break;

            case 2:
                fclose(fopen(HISTORY_INFO_FILE, "w"));
                numTrades = tradeList_getNumberOfTrades(history);

                printf("\nGenerating the history trades file...\n");
                
                for(i = 0; i < numTrades; i++){
                    trade_printHistoryTrade(tradeList_getTradeByIndex(history, i), HISTORY_INFO_FILE);
                    f = fopen(HISTORY_INFO_FILE, "a");
                    if(f)
                    fprintf(f,"\n\n\n");
                    fclose(f);
                }

                strcpy(openCommand, "xdg-open ");
                strcat(openCommand, HISTORY_INFO_FILE);
                system(openCommand);


                break;
            case 3: 
                printf("\nExiting the history trades menu...\n");
        }
    }while(option != 3);

}



void menu(int *option){

    if(!option) return;
    
    printf("\n==============================================================\n");
    printf("\nWELCOME TO THE TRADE HANDLER!\n");

    printf("\n\t1. New trade");
    printf("\n\t2. View pending");
    printf("\n\t3. View current positions");
    printf("\n\t4. View history");
    printf("\n\t5. Exit");

    printf("\n\nChoose an option: ");
    scanf("\n%d", option);
    printf("\n==============================================================\n");
}

void menuPending(int *option){
    
    if(!option) return;
    printf("\n--------------------------------------------------------------------------------\n");
    printf("\nPENDING TRADES MENU\n");
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

void menuOpen(int*option){
    if(!option) return;
    printf("\n--------------------------------------------------------------------------------\n");
    printf("\nOPEN TRADES MENU\n");
    printf("\nWhat do you want to do?\n");
    printf("\n\t1.View summary of opened trades");
    printf("\n\t2.Close a position");
    printf("\n\t3.Generate and open a text file with all the opened trades");
    printf("\n\t4.Exit");
    printf("\n\nChoose an option: ");
    scanf("\n%d", option);
    printf("\n--------------------------------------------------------------------------------\n");
}

void menuHistory(int*option){
    if(!option) return;
    printf("\n--------------------------------------------------------------------------------\n");
    printf("\nHISTORY OF TRADES MENU\n");
    printf("\nWhat do you want to do?\n");
    printf("\n\t1.View summary of history trades");
    printf("\n\t2.Generate and open a text file with all the opened trades");
    printf("\n\t3.Exit");
    printf("\n\nChoose an option: ");
    scanf("\n%d", option);
    printf("\n--------------------------------------------------------------------------------\n");
}

int aleat_num(int inf, int sup){
  return rand()/((double)RAND_MAX+1.)*(sup-inf+1)+inf;
}