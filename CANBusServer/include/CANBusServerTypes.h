#ifndef _CANBusServerTypes_H_
#define _CANBusServerTypes_H_
    #include <stdint.h>

    #ifndef NULL
    #define NULL ((void *)0x00)
    #endif

    typedef union CANMessageConfig{
        struct {
            unsigned extended_fmt : 1;// 1 means extended ID format
            unsigned rtr : 1;// 1 means Remote Request
            unsigned dlc : 4;// Data Length Code
        } config;
        uint8_t __raw;
    }CANMessageConfig_t;

    typedef struct CANMsg{
        uint32_t canID;
        CANMessageConfig_t msgCfg;
        uint8_t const * data;
    }CANMsg_t;

    typedef struct CANServiceConfigFlags{
        union {
            struct{
                unsigned notify_on_rx : 1;// 1 means trigger a notify
                unsigned notify_on_tx : 1;// 1 means trigger a notify
                unsigned enabled : 1;// 1 means ready to send/receive
                unsigned mode : 1;// 1 means rx, 0 means tx
            };
            uint8_t __raw;
        } flags;
        uint8_t max_dlc;
    }CANServiceConfigFlags_t;

    typedef uint8_t CANServiceStatusFlags_t;

    typedef struct CANMsgSettings{
        CANServiceConfigFlags_t serviceCfg;
        CANServiceStatusFlags_t serviceStatus;
        CANMsg_t const* canMsgPtr;
    }CANMsgSettings_t;

    typedef struct CANMsgsStNode{
        struct CANMsgsSt_LinkedList *owner;
        struct CANMsgsStNode *prev;
        struct CANMsgsStNode *next;
        struct CANMsgSettings const *canMsgSt;
    }CANMsgsStNode_t;

    typedef struct CANMsgsSt_LinkedList{
        struct CANMsgsStNode *first;
        struct CANMsgsStNode *last;
        uint8_t elements;
    }CANMsgsSt_LinkedList_t;
    
    typedef struct CANMsgsManager{
        struct CANMsgsSt_LinkedList enabled_list;
        struct CANMsgsSt_LinkedList disabled_list;
        struct CANMsgsSt_LinkedList notify_pending_list;
        struct CANMsgSettings const* can_msg_st_static_list;
        struct CANMsgsStNode const* can_msg_st_node_static_list;
    }CANMsgsManager_t;
#endif