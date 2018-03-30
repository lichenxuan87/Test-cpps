/******************************************************************************
 * Project ZXQ Internet Car
 * (c) copyright 2015
 * Company SAIC Motor
 * All rights reserved
 * Secrecy Level STRICTLY CONFIDENTIAL
 *****************************************************************************/
/*
 * @file os_msg_que.c
 * @group MCU
 * @author saic
 * Implementation of os_msg_que functions.
 */

/*-----------------------------------------------------------------------------
 * INCLUDES AND NAMESPACE
 *---------------------------------------------------------------------------*/
#include <os_msg_que.h>
#include <os_task.h>
#include <system.h>
#include <FreeRTOS.h>
#include <queue.h>

/*-----------------------------------------------------------------------------
 * MACROS AND CONSTANTS
 *---------------------------------------------------------------------------*/
#define TASK_UPPER_CNT_IN_MQUE			10

/*-----------------------------------------------------------------------------
 * ENUMS, TYPEDEFS, STRUCTS
 *---------------------------------------------------------------------------*/
typedef struct
{
	OS_MQueAttr_t que_attr;
	xQueueHandle que_handle;
} MsgQueOfTask_t;

/*-----------------------------------------------------------------------------
 * FUNCTION PROTOTYPES
 *---------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
 * LOCAL AND GLOBAL VARIABLES
 *---------------------------------------------------------------------------*/
static BOOL bInitFlag = FALSE;
static MsgQueOfTask_t sMQue[TASK_UPPER_CNT_IN_MQUE];

/*-----------------------------------------------------------------------------
 * FUNCTION DEFINITIONS
 *---------------------------------------------------------------------------*/
void os_mque_init(void)
{
	UINT8 i;

	for (i = 0; i < TASK_UPPER_CNT_IN_MQUE; i++)
	{
		sMQue[i].que_attr.task_id = OS_TASK_T_INVALID;
		sMQue[i].que_handle = 0;
	}
}

UINT32 os_mque_create(const OS_MQueAttr_t *attr)
{
	UINT32 rt_code = E_UNKNOWN;

	UINT8 i;

	if (FALSE == bInitFlag)
	{
		bInitFlag = TRUE;

		os_mque_init();
	}

	for (i = 0; i < TASK_UPPER_CNT_IN_MQUE; i++)
	{
		// free the existing queue since there is only one queue for per task
		if (attr->task_id == sMQue[i].que_attr.task_id)
		{
			vQueueDelete(sMQue[i].que_handle);
			sMQue[i].que_handle = 0;
			sMQue[i].que_attr.task_id = 0;
		}

		if (OS_TASK_T_INVALID == sMQue[i].que_attr.task_id)
		{
			UINT8 upper_cnt = attr->item_upper_cnt;
			UINT16 upper_size = attr->item_upper_size;

			// make sure the item count not to exceed the predefine max-value
			if (OS_MQUE_ITEM_CNT_MAX < attr->item_upper_cnt)
			{
				upper_cnt = OS_MQUE_ITEM_CNT_MAX;
			}

			// make sure the item size not to exceed the predefine max-value
			if (OS_MQUE_ITEM_SIZE_MAX < attr->item_upper_size)
			{
				upper_size = OS_MQUE_ITEM_SIZE_MAX;
			}

			sMQue[i].que_attr.task_id = attr->task_id;
			sMQue[i].que_attr.item_upper_cnt = upper_cnt;
			sMQue[i].que_attr.item_upper_size = upper_size;

			// create the queue, increase the item size with sizeof(UINT16) since
			// the first 2 bytes must be the message type in the queue
			sMQue[i].que_handle = xQueueCreate(upper_cnt,
					sizeof(UINT16) + upper_size);
			if (0 != sMQue[i].que_handle)
			{
				rt_code = E_SUCCESS;
			}

			break;
		}
	}

	return rt_code;
}

UINT32 os_mque_send(UINT32 task_id, const OS_MsgAttr_t *attr)
{
	UINT32 rt_code = E_UNKNOWN;

	UINT8 i;

	// find the queue handle
	for (i = 0; i < TASK_UPPER_CNT_IN_MQUE; i++)
	{
		if (sMQue[i].que_attr.task_id == task_id)
		{
			// the task found
			if (pdPASS == xQueueSendToBack(sMQue[i].que_handle, (void* )attr, 0))
			{
				rt_code = E_SUCCESS;
			}

			break;
		}
	}

	return rt_code;
}

UINT32 os_mque_send_in_isr(UINT32 task_id, const OS_MsgAttr_t *attr)
{
	UINT32 rt_code = E_UNKNOWN;

	UINT8 i;

	// find the queue handle
	for (i = 0; i < TASK_UPPER_CNT_IN_MQUE; i++)
	{
		if (sMQue[i].que_attr.task_id == task_id)
		{
			// the task found
			if (pdPASS
					== xQueueSendToBackFromISR(sMQue[i].que_handle,
							(void* )attr, 0))
			{
				rt_code = E_SUCCESS;
			}

			break;
		}
	}

	return rt_code;
}

UINT32 os_mque_recv(UINT32 task_id, OS_MsgAttr_t *attr, UINT32 timeout_ms)
{
	UINT32 rt_code = E_UNKNOWN;

	UINT8 i;

	// find the queue handle
	for (i = 0; i < TASK_UPPER_CNT_IN_MQUE; i++)
	{
		if (sMQue[i].que_attr.task_id == task_id)
		{
			// the task found
			if (pdPASS
					== xQueueReceive(sMQue[i].que_handle, (void* )attr,
							timeout_ms * ((UINT32) configTICK_RATE_HZ) / (UINT32) 1000U))
			{
				rt_code = E_SUCCESS;
			}
			else
			{
				rt_code = E_UNKNOWN;
			}

			break;
		}
	}

	return rt_code;
}

UINT32 os_mque_query(UINT32 task_id)
{
	return E_SUCCESS;
}
