#include<stdio.h>

#include"list.h" 

int main(){

    TradeList * tradeList;
    Trade *trade;

    trade = trade_newTrade(5);
    if(!trade){
        printf("\nnewTrade function failed\n");
        return -1;
    }
    tradeList = tradeList_newTradeList();
    
    if(!tradeList){
        printf("\nnewTradeList function failed\n");
        trade_freeTrade(trade);
        return -1;
    }

    if(tradeList_insertTrade(tradeList, trade) == ERR){
        tradeList_destroyList(tradeList);
        trade_freeTrade(trade);
    }

    tradeList_printList(tradeList);

    trade_freeTrade(trade);
    trade = trade_newTrade(3);

    if(!trade){
        printf("\nnewTrade function failed\n");
        tradeList_destroyList(tradeList);
        return -1;
    }

    if(tradeList_insertTrade(tradeList, trade) == ERR){
        tradeList_destroyList(tradeList);
        trade_freeTrade(trade);
    }

    tradeList_printList(tradeList);

    if(tradeList_deleteTrade(tradeList, 5) == ERR){
        tradeList_destroyList(tradeList);
        trade_freeTrade(trade);
    }

    tradeList_printList(tradeList);

    tradeList_destroyList(tradeList);
    trade_freeTrade(trade);

    

    return 1;

    
}







