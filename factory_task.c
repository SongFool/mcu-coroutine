#include "factory_task.h"
#ifdef SUPPORT_NEW_FACTORY_FEATURES
tcb factory_task_list[4];
tcb* factory_run_handle = NULL;
void task_init()
{
	factory_run_handle = factory_task_list;
	for (uint8_t i = 0; i < 3; i++) {
		factory_task_list[i].next = &(factory_task_list[i + 1]);
		factory_task_list[i].callfun = NULL;
		factory_task_list[i].run_flag = 1;
		factory_task_list[i].run_id = 0;
		factory_task_list[i].delay_time = 0;
	}
}
/*
	获取运行标志位
*/
uint8_t  task_get_run_flag(tcb* task)
{
	return task->run_flag;
}
/*
	设置运行标志位
*/
void task_set_run_flag(tcb* task,uint8_t flag)
{
	task -> run_flag = flag;
}
/*
	获取并运行函数
*/
void task_get_callfun(tcb* task)
{
    if(task->callfun != NULL){
        task->callfun();
    }
}
/*
	设置任务函数
*/
uint8_t task_get_delay_time(tcb* factory_run_handle)
{
	return factory_run_handle->delay_time;
}
/*
	设置延迟时间
*/
void task_set_delay_time(tcb* factory_run_handle,uint8_t delay_time)
{
	factory_run_handle->delay_time = delay_time;
}
/*
	递减延迟时间
*/
bool task_decrement_delay_time(tcb* factory_run_handle)
{
	factory_run_handle->delay_time = factory_run_handle->delay_time - 1;
	if (factory_run_handle->delay_time == 0)
	{
		return true;
	}else {
		return false;
	}
}
/*
	返回运行上下文节点
*/
uint16_t os_task_internal_state_get(tcb* factory_run_handle)
{
	return factory_run_handle->run_id;
}
/*
	设置运行上下文节点
*/
void os_task_internal_state_set(tcb* factory_run_handle, uint16_t line)
{
	factory_run_handle->run_id = line;
}
/*
	延迟时间更新
*/
void task_delay_run()
{
	for (uint8_t i = 0; i < 3; i++) {
		if (task_decrement_delay_time(factory_run_handle)) {
			task_set_run_flag(factory_run_handle, 1);
		}
		factory_run_handle = factory_run_handle->next;
	}
	factory_run_handle = factory_task_list;
}
/*
	函数运行
*/
void task_run()
{
	for (uint8_t i = 0; i < 3; i++) {
		if (task_get_run_flag(factory_run_handle)) {
			task_get_callfun(factory_run_handle);
		}
		factory_run_handle = factory_run_handle->next;
	}
	factory_run_handle = factory_task_list;
}
#endif //SUPPORT_NEW_FACTORY_FEATURES