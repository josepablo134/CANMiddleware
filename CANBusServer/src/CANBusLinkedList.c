#include <stdint.h>
#include "cfg/CANBusServerCfg.h"
#include "CANBusServerTypes.h"

void CanBusServer_LL_init( CANMsgsSt_LinkedList_t *list ){
    if( NULL != list ){
        list->elements = 0;
        list->first = NULL;
        list->last = NULL;
    }
}

uint8_t CanBusServer_LL_append( CANMsgsSt_LinkedList_t *list, CANMsgsStNode_t *node ){
    if( NULL == list || NULL == node || NULL != node->owner ){
        return 0;
    }
    if( NULL == list->last){
        /// Adding context to new node
        node->next = node->prev = NULL;
        /// This is the first node in the list
        list->last = list->first = node;
    }else{
        /// Adding context to new node
        node->next = NULL;
        node->prev = list->last;
        /// Adding context to last node in the list
        list->last->next = node;
        /// Replacing last node in the list
        list->last = node;
    }
    node->owner = list;
    list->elements++;
    return list->elements;
}

uint8_t CanBusServer_LL_push( CANMsgsSt_LinkedList_t *list, CANMsgsStNode_t *node ){
    if( NULL == list || NULL == node || NULL != node->owner ){
        return 0;
    }
    if( NULL == list->last){
        /// Adding context to new node
        node->next = node->prev = NULL;
        /// This is the first node in the list
        list->last = list->first = node;
    }else{
        /// Adding context to new node
        node->next = list->first;
        node->prev = NULL;
        /// Adding context to first node in the list
        list->first->prev = node;
        /// Replacing last node in the list
        list->first = node;
    }
    node->owner = list;
    list->elements++;
    return list->elements;
}

CANMsgsSt_LinkedList_t* CanBusServer_LL_getOwnerList( CANMsgsStNode_t const* node ){
    if( NULL == node ){
        return NULL;
    }
    return node->owner;
}

uint8_t CanBusServer_LL_removeFromList( CANMsgsStNode_t *node ){
    CANMsgsStNode_t *prev;
    CANMsgsStNode_t *next;
    CANMsgsSt_LinkedList_t *owner;
    if( NULL == node || NULL == node->owner){
        return 0;
    }

    prev = node->prev;
    next = node->next;
    owner = node->owner;

    if( NULL == prev && NULL == next ){
        /// This is the only node in the list
        owner->first = NULL;
        owner->last = NULL;
    }else if( NULL == prev && NULL != next ){
        /// This node is the first in the list
        owner->first = next;
        next->prev = NULL;
    }else if( NULL != prev && NULL == next ){
        /// This node is the last in the list
        owner->last = prev;
        prev->next = NULL;
    }else{
        /// This node is in the middle of the list
        next->prev = prev;
        prev->next = next;
    }
    node->owner = NULL;
    node->next = node->prev = NULL;
    owner->elements--;
    return owner->elements;
}