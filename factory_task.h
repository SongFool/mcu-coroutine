#ifndef _FACTORY_TASK__
#define	_FACTORY_TASK__
#include "config.h"
#ifdef SUPPORT_NEW_FACTORY_FEATURES
#include "stdint.h"
#include <stdio.h>
#include "stdbool.h"
#define task_open()		OS_BEGIN
#define OS_BEGIN		uint16_t os_task_state = os_task_internal_state_get(factory_run_handle);\
						switch ( os_task_state )\
						{ \
						case 0:

#define task_close()	OS_END
#define OS_END			return;}
#define OS_SCHEDULE(ofs)    os_task_internal_state_set(factory_run_handle,__LINE__ + ofs);\
							task_set_run_flag(factory_run_handle, 0);\
                            return;\
                            case (__LINE__ + ofs):

#define task_wait(time)		 OS_WAIT_TICKS(time)

#define OS_WAIT_TICKS(time)	do {\
								task_set_delay_time( factory_run_handle, time);\
								OS_SCHEDULE(0);\
						   	   } while ( 0 )

#define task_kill()         factory_run_handle->callfun = NULL;\
                            factory_run_handle->run_id = 0

typedef struct tcb_
{
	uint8_t run_flag;
	uint8_t delay_time;
	uint16_t run_id;
	void(*callfun)();
	struct tcb_* next;
}tcb;
extern tcb factory_task_list[4];
extern tcb* factory_run_handle;
void task_init();
uint16_t os_task_internal_state_get(tcb* factory_run_handle);
void os_task_internal_state_set(tcb* factory_run_handle, uint16_t line);
void task_set_delay_time(tcb* factory_run_handle, uint8_t delay_time);
void task_delay_run();
void task_run();
void task_set_run_flag(tcb* task, uint8_t flag);
#endif//SUPPORT_NEW_FACTORY_FEATURES
#endif