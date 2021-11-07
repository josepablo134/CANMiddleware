#include "unity.h"
#include <stdint.h>

#include "CANBusServerTypes.h"
#include "CANBusServerPrivateInterfaces.h"
TEST_FILE("CANBusLinkedList.c");

/// This macro does not configure the unit tests
#define NUM_OF_NODES 3
CANMsgsSt_LinkedList_t list;
CANMsgsSt_LinkedList_t other_list;
CANMsgsStNode_t *temp = NULL;
CANMsgsStNode_t nodes[NUM_OF_NODES] = {
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

void setUp(void){
    for(int i=0; i<NUM_OF_NODES; i++){
        nodes[i].prev = NULL;
        nodes[i].next = NULL;
        nodes[i].owner = NULL;
        nodes[i].canMsgSt = NULL;
    }
    temp = NULL;
    CanBusServer_LL_init( &list );
    CanBusServer_LL_init( &other_list );
}
void tearDown(void){}

void test_CanBusServer_LL_init_TC01(void){
    CANMsgsSt_LinkedList_t *initialized_list = CanBusServer_LL_init( NULL );
    TEST_ASSERT( initialized_list == NULL );
}

void test_CanBusServer_LL_append_TC01 (void){
    uint8_t retVal;
    retVal = CanBusServer_LL_append( &list , NULL );
    TEST_ASSERT_EQUAL_UINT8( 0 , retVal );
    retVal = CanBusServer_LL_append( &list , NULL );
    TEST_ASSERT_EQUAL_UINT8( 0 , retVal );
    retVal = CanBusServer_LL_append( NULL , NULL );
    TEST_ASSERT_EQUAL_UINT8( 0 , retVal );

    CanBusServer_LL_append( &list , &(nodes[0]) );
    CanBusServer_LL_append( &list , &(nodes[1]) );
    CanBusServer_LL_append( &list , &(nodes[2]) );
    CanBusServer_LL_append( &list , &(nodes[2]) );/// Already assigned node shall not be added to the list
    TEST_ASSERT_EQUAL_UINT8( 3 , list.elements );
    CANMsgsStNode_t *temp = list.first;
    for(uint8_t i=0; i<NUM_OF_NODES; i++){
        TEST_ASSERT( temp == &nodes[i] );
        temp = temp->next;
    }
    resetTest();
}

void test_CanBusServer_LL_push_TC01 (void){
    uint8_t retVal;
    retVal = CanBusServer_LL_push( &list , NULL );
    TEST_ASSERT_EQUAL_UINT8( 0 , retVal );
    retVal = CanBusServer_LL_push( &list , NULL );
    TEST_ASSERT_EQUAL_UINT8( 0 , retVal );
    retVal = CanBusServer_LL_push( NULL , NULL );
    TEST_ASSERT_EQUAL_UINT8( 0 , retVal );

    CanBusServer_LL_push( &list , &(nodes[0]) );
    CanBusServer_LL_push( &list , &(nodes[1]) );
    CanBusServer_LL_push( &list , &(nodes[2]) );
    CanBusServer_LL_push( &list , &(nodes[2]) );/// Already assigned node shall not be pushed
    TEST_ASSERT_EQUAL_UINT8( 3 , list.elements );
    temp = list.first;
    for(int8_t i=(NUM_OF_NODES-1); i>-1; i--){
        TEST_ASSERT( temp == &nodes[i] );
        temp = temp->next;
    }
    printf("PASSED\n");

    resetTest();
}

void test_CanBusServer_LL_getOwnerList_TC01 (void){
    CanBusServer_LL_push( &list , &(nodes[0]) );
    CanBusServer_LL_push( &list , &(nodes[1]) );
    CanBusServer_LL_push( &list , &(nodes[2]) );
    CanBusServer_LL_removeFromList( &(nodes[0]) );
    CanBusServer_LL_append( &other_list , &(nodes[0]) );

    CANMsgsSt_LinkedList_t *owner = CanBusServer_LL_getOwnerList( NULL );
    TEST_ASSERT( owner == NULL );

    owner = CanBusServer_LL_getOwnerList( &(nodes[0]) );
    TEST_ASSERT( owner == &other_list );
    resetTest();
}

/**
 * Null Safety cases
*/
void testCanBusServer_LL_removeFromList_TC01 (void){
    uint8_t retVal;
    CanBusServer_LL_append( &list , &(nodes[0]) );
    CanBusServer_LL_append( &list , &(nodes[1]) );
    CanBusServer_LL_append( &list , &(nodes[2]) );
    
    /// Remove Null Node shall be not possible
    retVal = CanBusServer_LL_removeFromList( NULL );
    TEST_ASSERT_EQUAL_UINT8( 0 , retVal );

    retVal = CanBusServer_LL_removeFromList( &(nodes[1]) );
    TEST_ASSERT_EQUAL_UINT8( 2 , retVal );

    /// Remove node with no owner shall be not possible
    retVal = CanBusServer_LL_removeFromList( &(nodes[1]) );
    TEST_ASSERT_EQUAL_UINT8( 0 , retVal );
    resetTest();
}

/**
 * Corner case 1: Removing node in the middle of the list
*/
void testCanBusServer_LL_removeFromList_TC02 (void){
    uint8_t retVal;
    CanBusServer_LL_append( &list , &(nodes[0]) );
    CanBusServer_LL_append( &list , &(nodes[1]) );
    CanBusServer_LL_append( &list , &(nodes[2]) );
    
    retVal = CanBusServer_LL_removeFromList( &(nodes[1]) );
    TEST_ASSERT_EQUAL_UINT8( 2 , retVal );

    TEST_ASSERT( list.first == &(nodes[0]) );
    TEST_ASSERT( list.last == &(nodes[2]) );
    TEST_ASSERT( nodes[0].next == &( nodes[2] ) );
    TEST_ASSERT( nodes[2].prev == &( nodes[0] ) );
    resetTest();
}

/**
 * Corner case 2: Removing the first node
*/
void testCanBusServer_LL_removeFromList_TC03 (void){
    uint8_t retVal;
    CanBusServer_LL_append( &list , &(nodes[0]) );
    CanBusServer_LL_append( &list , &(nodes[1]) );
    CanBusServer_LL_append( &list , &(nodes[2]) );
    
    retVal = CanBusServer_LL_removeFromList( &(nodes[0]) );
    TEST_ASSERT_EQUAL_UINT8( 2 , retVal );

    TEST_ASSERT( list.first == &(nodes[1]) );
    TEST_ASSERT( list.last == &(nodes[2]) );
    TEST_ASSERT( nodes[1].next == &( nodes[2] ) );
    TEST_ASSERT( nodes[2].prev == &( nodes[1] ) );
    resetTest();
}

/**
 * Corner case 3: Removing the last node
*/
void testCanBusServer_LL_removeFromList_TC04 (void){
    uint8_t retVal;
    CanBusServer_LL_append( &list , &(nodes[0]) );
    CanBusServer_LL_append( &list , &(nodes[1]) );
    CanBusServer_LL_append( &list , &(nodes[2]) );
    
    retVal = CanBusServer_LL_removeFromList( &(nodes[2]) );
    TEST_ASSERT_EQUAL_UINT8( 2 , retVal );

    TEST_ASSERT( list.first == &(nodes[0]) );
    TEST_ASSERT( list.last == &(nodes[1]) );
    TEST_ASSERT( nodes[0].next == &( nodes[1] ) );
    TEST_ASSERT( nodes[1].prev == &( nodes[0] ) );
    resetTest();
}

/**
 * Corner case 4: Removing the only node in the list
*/
void testCanBusServer_LL_removeFromList_TC05 (void){
    uint8_t retVal;
    CanBusServer_LL_append( &list , &(nodes[0]) );
    CanBusServer_LL_append( &list , &(nodes[1]) );
    CanBusServer_LL_append( &list , &(nodes[2]) );
    
    retVal = CanBusServer_LL_removeFromList( &(nodes[0]) );
    TEST_ASSERT_EQUAL_UINT8( 2 , retVal );
    
    retVal = CanBusServer_LL_removeFromList( &(nodes[1]) );
    TEST_ASSERT_EQUAL_UINT8( 1 , retVal );
    
    retVal = CanBusServer_LL_removeFromList( &(nodes[2]) );
    TEST_ASSERT_EQUAL_UINT8( 0 , retVal );

    TEST_ASSERT( list.first == NULL );
    TEST_ASSERT( list.last == NULL );
    TEST_ASSERT_EQUAL_UINT8( 0 , list.elements );
    resetTest();
}