/**
 * @file      : user_list.h
 * @brief     : 用户链表头文件
 * @author    : huenrong (huenrong1028@outlook.com)
 * @date      : 2023-02-01 21:26:01
 *
 * @copyright : Copyright (c) 2023 huenrong
 *
 * @history   : date       author          description
 *              2023-02-01 huenrong        创建文件
 *
 */

#ifndef __USER_LIST_H
#define __USER_LIST_H

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdint.h>
#include <stdbool.h>

#include "../kernel_list/kernel_list.h"

// 用户链表节点数据
typedef struct
{
    char name[20]; // 姓名
    uint8_t age;   // 年龄
} user_list_node_data_t;


// 用户链表节点定义
typedef struct
{
    user_list_node_data_t node_data; // 节点数据
    list_head_t list;                // 内核链表
} user_list_node_t;

/**
 * @brief  初始化用户链表
 */
void init_user_list(void);

/**
 * @brief  增加节点到用户链表(头插法)
 * @param  node_data: 输入参数, 待插入节点数据
 * @return true : 成功
 * @return false: 失败
 */
bool add_node_to_user_list(const user_list_node_data_t node_data);

/**
 * @brief  增加节点到用户链表(尾插法)
 * @param  node_data: 输入参数, 待插入节点数据
 * @return true : 成功
 * @return false: 失败
 */
bool add_node_to_user_list_tail(const user_list_node_data_t node_data);

/**
 * @brief  遍历链表
 */
void traverse_user_list(void);

/**
 * @brief  删除用户链表节点(删除所有符合要求的节点)
 * @param  node_data: 输入参数, 待删除节点数据
 */
void del_node_from_user_list(const user_list_node_data_t node_data);

/**
 * @brief  删除用户链表所有节点(不包括头节点)
 */
void del_all_node_from_user_list(void);

/**
 * @brief  判断用户链表是否为空
 * @return true : 链表为空
 * @return false: 链表非空
 */
bool user_list_is_empty(void);

/**
 * @brief  获取用户链表长度
 * @return 链表长度
 */
uint32_t get_user_list_len(void);

/**
 * @brief  获取指定姓名对应的节点信息
 * @param  node_data: 输出参数, 获取到的节点信息(该项为NULL只判断是否有对应信息)
 * @param  name     : 输入参数, 待获取信息的姓名
 * @return true : 成功
 * @return false: 失败
 */
bool find_node_from_user_list(user_list_node_data_t *node_data, const char *name);

/**
 * @brief  更新用户链表数据(不存在该节点, 则将数据插入链表)
 * @param  node_data: 输入参数, 待更新/插入的节点数据
 * @return true : 成功
 * @return false: 失败
 */
bool update_user_list_data(const user_list_node_data_t node_data);

#ifdef __cplusplus
}
#endif

#endif // __USER_LIST_H
