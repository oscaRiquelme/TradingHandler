#include<stdio.h>

#include "trade.h"
#include "trade_manager.h"

void menu(int *opcion);
void calculate_trade();
void view_pending();
void view_open();
void view_history();


int main(){
    int opcion;
    do{
        do{

            menu(&opcion);
        }while(opcion < 1 && opcion > 5);

        if(opcion == 1){
            calculate_trade();
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
    return 0;
}

void menu(int *opcion){
    
    printf("\nWelcome to the trade handler...\n");

    printf("\n\t1. New trade");
    printf("\n\t2. View pending");
    printf("\n\t3. View current positions");
    printf("\n\t4. View history");
    printf("\n\t5. Exit");

    printf("\n\nChoose an option:");
    scanf("\n%d", opcion);
}


void calculate_trade(){
    
}
void view_pending(){

}
void view_open(){

}
void view_history(){

}
