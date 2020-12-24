#include "list.h"

#include<stdio.h>
#include<stdlib.h>



struct Node{
    struct Node *next;
    Trade *trade;
};

typedef struct Node Node;

struct tradeList{
    struct Node *head;
};


Node * newNode(Trade * trade){
    
    Node *new = NULL;
    
    if(!trade) return NULL;

    new = (Node*)malloc(sizeof(Node));
    
    if(!new){
        printf("Error allocating memory for the new node. Returning null...");
        return NULL;
    } 

    new->next = NULL;
    new->trade = trade_copy(trade);

    if(!new->trade){
        printf("Error setting up the data for the new node. Returning null...");
        free(new);
        return NULL;
    }

    return new;
}


TradeList * tradeList_newTradeList(){

    TradeList * newTradeList = NULL;

    newTradeList = (TradeList*)malloc(sizeof(TradeList));
    if(!newTradeList){
        printf("Error while allocating memory for a new tradeList variable");
        return NULL;
    }

    newTradeList->head = NULL;

    return newTradeList;
}

status tradeList_insertTrade(TradeList * tradeList, Trade * trade){

    Node *new, *tmp;    

    if(!trade || !tradeList){
        printf("\nError with the arguments passed to insert a trade. Returning error...\n");
        return ERR;
    }

    tmp = tradeList->head;

    new = newNode(trade);
    if(!new){
        printf("\nError creating a new node for the new trade. Returning err...\n");
        return ERR;
    }
    if(!tmp){ /*List is empty*/
        tradeList->head = new;
        return OK;
    }

    while(tmp->next != NULL){
        tmp = tmp->next;
    }

    tmp->next = new;
    return OK;

}

status tradeList_deleteTrade(TradeList * tradeList, int id){
    
    Node *tmp = NULL;
    Node *aux = NULL;

    if(!tradeList){
        printf("\nError passing the arguments to delete a trade. Return ERR...\n");
        return ERR;
    } 

    tmp = tradeList->head;
    /*Base case (if we want to delete the head)*/
    if(trade_getId(tmp->trade) == id){
        tradeList->head = tmp->next;
        trade_freeTrade(tmp->trade);
        free(tmp);
        return OK;
    }

    while(tmp != NULL){
        if(tmp->next != NULL){
            if(trade_getId(tmp->next->trade) == id){
                aux = tmp->next;
                tmp->next = aux->next;
                if(trade_freeTrade(aux->trade) == ERR){
                    fprintf(stderr, "\nInvalid free of the trade to delete\n");
                }
                free(aux);
                return OK;
            }
            tmp = tmp->next;
        }
    }
    return ERR;

}

Trade * tradeList_getTrade(TradeList * tradeList, int id){

    Node *tmp;

    if(!tradeList){
        printf("Error passing the arguments to get a trade. Returning NULL... ");
        return NULL;
    }

    tmp = tradeList->head;


    while(tmp != NULL){
        if(trade_getId(tmp->trade) == id) return trade_copy(tmp->trade);

        tmp = tmp->next;
    }

    return NULL; /*The trade with the id given is not found*/

}

status tradeList_destroyList(TradeList * tradeList){

    Node * tmp = NULL;
    Node * aux = NULL;

    if(!tradeList) return ERR;

    tmp = tradeList->head;

    while(tmp != NULL){
        aux = tmp->next;
        if(trade_freeTrade(tmp->trade) == ERR) fprintf(stderr, "\nInvalid free while trying to destroy a trade of the list\n");
        free(tmp);
        tmp = aux;
    }

    free(tradeList);

    return OK;

}

void tradeList_printList(TradeList * tradeList){

    Node *tmp;
    if(!tradeList){
        printf("\nError while printing the trading list. Returning...\n");
        return;
    } 

    tmp = tradeList->head;



    if(!tmp){
        printf("\nList is empty!\n");
        return;
    } 

    printf("\nPRINTING LIST...\n");

    while(tmp != NULL){
        trade_printTrade(tmp->trade);
        printf("\n\n\n");
        tmp = tmp->next;
    }       
    
}




