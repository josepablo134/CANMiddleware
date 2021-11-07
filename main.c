#include <stdio.h>
#include "CANBusServer.h"
#include "CANBusServerPrivateInterfaces.h"

CANMsgsSt_LinkedList_t list;
CANMsgsStNode_t nodes[3] = {
    {
        .prev = NULL,
        .next = NULL,
        .owner = NULL,
        .canMsgSt = NULL
    },
    {
        .prev = NULL,
        .next = NULL,
        .owner = NULL,
        .canMsgSt = NULL
    },
    {
        .prev = NULL,
        .next = NULL,
        .owner = NULL,
        .canMsgSt = NULL
    },
};

int main(){
    printf("Append Unit Test{\n");
    CanBusServer_LL_init( &list );
    CanBusServer_LL_append( &list , &(nodes[0]) );
    CanBusServer_LL_append( &list , &(nodes[1]) );
    CanBusServer_LL_append( &list , &(nodes[2]) );
    CanBusServer_LL_append( &list , &(nodes[2]) );/// Already assigned node shall not be added to the list
    if( list.elements == 3 ){
        printf("Number of elements is consistent\n");
    }else{
        printf("Number of elements is NOT consistent\n");
        printf("Elements: %d\n",list.elements);
        return -1;
    }
    CANMsgsStNode_t *temp = list.first;
    for(uint8_t i=0; i<3; i++){
        if( temp == &nodes[i] ){
            printf("Node matches\n");
        }else{
            printf("Node {%d} does not matches",i);
            return -1;
        }
        temp = temp->next;
    }
    printf("PASSED\n");
    printf("}Append Unit Test\n\n");


    printf("Removing Unit Test{\n");
    for(uint8_t i=0; i<3; i++){
        printf("Removing %d\n",
            CanBusServer_LL_removeFromList( &(nodes[i]) )
        );
    }
    if( list.elements == 0 ){
        printf("PASSED\n");
    }else{
        printf("remove not passed\n");
        return -1;
    }
    printf("}Removing Unit Test\n\n");


    printf("Push Unit Test{\n");
    CanBusServer_LL_push( &list , &(nodes[0]) );
    CanBusServer_LL_push( &list , &(nodes[1]) );
    CanBusServer_LL_push( &list , &(nodes[2]) );
    CanBusServer_LL_push( &list , &(nodes[2]) );/// Already assigned node shall not be pushed
    if( list.elements == 3 ){
        printf("Number of elements is consistent\n");
    }else{
        printf("Number of elements is NOT consistent\n");
        printf("Elements: %d\n",list.elements);
        return -1;
    }    
    temp = list.first;
    for(int8_t i=2; i>-1; i--){
        if( temp == &nodes[i] ){
            printf("Node matches\n");
        }else{
            printf("Node {%d} does not matches",i);
            return -1;
        }
        temp = temp->next;
    }
    printf("PASSED\n");
    printf("}Push Unit Test\n\n");


    printf("GetOwner Unit Test{\n");
    CANMsgsSt_LinkedList_t other_list;
    CanBusServer_LL_init( &other_list );
    printf("Removing %d\n",
        CanBusServer_LL_removeFromList( &(nodes[0]) )
    );
    CanBusServer_LL_append( &other_list , &(nodes[0]) );
    CANMsgsSt_LinkedList_t *owner = CanBusServer_LL_getOwnerList( &(nodes[0]) );
    if( owner == &other_list ){
        printf("Owner list matches\n");
        printf("PASSED\n");
    }else{
        printf("Owner list doesn't match\n");
    }
    printf("}GetOwner Unit Test\n\n");

    return 0;
}