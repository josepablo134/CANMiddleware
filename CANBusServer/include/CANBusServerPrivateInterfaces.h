/**
 * @file        CANBusServerPrivateInterfaces.h
 * @version     0.0
 * @author      Josepablo Cruz Baas
 * @date        07/11/2021
 * @brief       Private interfaces for internal servies and object handlers
 * 
 * This file is the entry point for internal interfaces
*/
#ifndef _CANBusServerPrivateInterfaces_H_
#define _CANBusServerPrivateInterfaces_H_
    #include "CANBusServerTypes.h"

    /*!
     * @brief Initialice list structure
     * @return Number of elements in the list
    */
    extern CANMsgsSt_LinkedList_t* CanBusServer_LL_init( CANMsgsSt_LinkedList_t * list );
    /*!
     * @brief Append a node to the end of the list
     * @return Number of elements in the list
    */
    extern uint8_t CanBusServer_LL_append( CANMsgsSt_LinkedList_t *list, CANMsgsStNode_t *node );
    /*!
     * @brief Push a node to the begin of the list
     * @return Number of elements in the list
    */
    extern uint8_t CanBusServer_LL_push( CANMsgsSt_LinkedList_t *list, CANMsgsStNode_t *node );
    /*!
     * @brief Get owner list for this node
     * @return Pointer to the owner list or null
    */
    extern CANMsgsSt_LinkedList_t* CanBusServer_LL_getOwnerList( CANMsgsStNode_t const* node );
    /*!
     * @brief Remove this node from owner list
     * @return Remaining elements in the list
    */
    extern uint8_t CanBusServer_LL_removeFromList( CANMsgsStNode_t *node );
#endif