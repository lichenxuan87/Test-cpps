/******************************************************************************
 * Project ZXQ Internet Car
 * (c) copyright 2015
 * Company SAIC Motor
 * All rights reserved
 * Secrecy Level STRICTLY CONFIDENTIAL
 *****************************************************************************/
/*
 * @file os_msg_que.h
 * @group MCU
 * @author saic
 * Declaration of msg_que functions.
 *
 */

#ifndef __MCU_OS_MSG_QUE_H__
#define __MCU_OS_MSG_QUE_H__
/******************************************************************************/
#ifdef __cplusplus
extern "C"
{
#endif

/*-----------------------------------------------------------------------------
 * INCLUDES
 *---------------------------------------------------------------------------*/
#include <util_type.h>

/*-----------------------------------------------------------------------------
 * MACROS AND CONSTANTS
 *---------------------------------------------------------------------------*/
#define OS_MQUE_ITEM_CNT_MAX				10
#define OS_MQUE_ITEM_SIZE_MAX				32

#define OS_MQUE_ITEM_CNT_DEFAULT			3
#define OS_MQUE_ITEM_SIZE_DEFAULT			12

/*-----------------------------------------------------------------------------
 * ENUMS, TYPEDEFS, STRUCTS
 *---------------------------------------------------------------------------*/
/*
 * Message queue attribute definition.
 *
 */
typedef struct
{
	// the id of the task which should register to the queue
	UINT32 task_id;

	// the upper limit of the message count for the task
	// should never exceed OS_MQUE_ITEM_UPPER_CNT_FOR_TASK.
	UINT8 item_upper_cnt;

	// the upper limit of the size of each message for the task
	// should never exceed OS_MQUE_ITEM_UPPER_SIZE_OF_MSG
	UINT16 item_upper_size;
} OS_MQueAttr_t;

/*
 * Message attribute definition
 *
 */
typedef struct
{
	UINT16 msg_type;

	union
	{
		// Point to the message content
		BYTE * PT_FAR content;

		// For some 'small' message, the data can be placed here directly
		BYTE msg_buf[OS_MQUE_ITEM_SIZE_MAX];
	} content;
} OS_MsgAttr_t;

/*-----------------------------------------------------------------------------
 * FUNCTION PROTOTYPES
 *---------------------------------------------------------------------------*/
/*
 * Initialize the message queue.
 *
 */
extern void os_mque_init(void);

/*
 * Register to the message queue.
 *
 */
extern UINT32 os_mque_create(const OS_MQueAttr_t *attr);

/*
 * Send message to certain task
 *
 */
extern UINT32 os_mque_send(UINT32 task_id, const OS_MsgAttr_t *attr);

/*
 * Send message to certain task in interrupt service routine.
 *
 */
extern UINT32 os_mque_send_in_isr(UINT32 task_id, const OS_MsgAttr_t *attr);

/*
 * Receive message in task.
 *
 */
extern UINT32 os_mque_recv(UINT32 task_id, OS_MsgAttr_t *attr,
		UINT32 timeout_ms);

/*
 * Query current non-received message count of the task.
 *
 */
extern UINT32 os_mque_query(UINT32 task_id);

/*-----------------------------------------------------------------------------
 * GLOBAL VARIABLE DECLARATIONS
 *---------------------------------------------------------------------------*/

/******************************************************************************/
#ifdef __cplusplus  // close out "C" linkage in case of c++ compiling
}
#endif

/******************************************************************************/
#endif /* __MCU_OS_MSG_QUE_H__ */
