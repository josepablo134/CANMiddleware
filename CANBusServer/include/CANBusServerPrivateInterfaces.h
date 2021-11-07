#ifndef _CANBusServerPrivateInterfaces_H_
#define _CANBusServerPrivateInterfaces_H_
    #include "CANBusServerTypes.h"

    /**
     * Initialice list structure
    */
    extern void CanBusServer_LL_init( CANMsgsSt_LinkedList_t * list );
    /**
     * Append a node to the end of the list
     * @return Number of elements in the list
    */
    extern uint8_t CanBusServer_LL_append( CANMsgsSt_LinkedList_t *list, CANMsgsStNode_t *node );
    /**
     * Push a node to the begin of the list
     * @return Number of elements in the list
    */
    extern uint8_t CanBusServer_LL_push( CANMsgsSt_LinkedList_t *list, CANMsgsStNode_t *node );
    /**
     * Get owner list for this node
     * @return Pointer to the owner list or null
    */
    extern CANMsgsSt_LinkedList_t* CanBusServer_LL_getOwnerList( CANMsgsStNode_t const* node );
    /**
     * Remove this node from owner list
     * @return Remaining elements in the list
    */
    extern uint8_t CanBusServer_LL_removeFromList( CANMsgsStNode_t *node );
#endif