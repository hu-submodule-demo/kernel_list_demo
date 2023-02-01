/**
 * @file      : user_list.c
 * @brief     : 用户链表源文件
 * @author    : huenrong (huenrong1028@outlook.com)
 * @date      : 2023-02-01 21:24:14
 *
 * @copyright : Copyright (c) 2023 huenrong
 *
 * @history   : date       author          description
 *              2023-02-01 huenrong        创建文件
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

#include "./user_list.h"

// 用户链表头节点定义
typedef struct
{
    uint32_t len;     // 链表长度(注意与获取链表长度返回值匹配)
    list_head_t list; // 内核链表
} user_list_head_t;

// 用户链表头
static user_list_head_t g_user_list_head = {0};

// 用户链表互斥锁
static pthread_mutex_t g_user_list_mutex;

/**
 * @brief  初始化用户链表
 */
void init_user_list(void)
{
    // 初始化链表
    INIT_LIST_HEAD(&g_user_list_head.list);

    g_user_list_head.len = 0;

    // 初始化互斥锁
    pthread_mutex_init(&g_user_list_mutex, NULL);
}

/**
 * @brief  增加节点到用户链表(头插法)
 * @param  node_data: 输入参数, 待插入节点数据
 * @return true : 成功
 * @return false: 失败
 */
bool add_node_to_user_list(const user_list_node_data_t node_data)
{
    user_list_node_t *new_node = NULL;

    new_node = (user_list_node_t *)malloc(sizeof(user_list_node_t));
    if (!new_node)
    {
        return false;
    }

    memcpy(&new_node->node_data, &node_data, sizeof(user_list_node_data_t));

    pthread_mutex_lock(&g_user_list_mutex);

    list_add(&new_node->list, &g_user_list_head.list);

    // 插入节点时, 链表长度增加
    g_user_list_head.len++;

    pthread_mutex_unlock(&g_user_list_mutex);

    return true;
}

/**
 * @brief  增加节点到用户链表(尾插法)
 * @param  node_data: 输入参数, 待插入节点数据
 * @return true : 成功
 * @return false: 失败
 */
bool add_node_to_user_list_tail(const user_list_node_data_t node_data)
{
    user_list_node_t *new_node = NULL;

    new_node = (user_list_node_t *)malloc(sizeof(user_list_node_t));
    if (!new_node)
    {
        return false;
    }

    memcpy(&new_node->node_data, &node_data, sizeof(user_list_node_data_t));

    pthread_mutex_lock(&g_user_list_mutex);

    list_add_tail(&new_node->list, &g_user_list_head.list);

    // 插入节点时, 链表长度增加
    g_user_list_head.len++;

    pthread_mutex_unlock(&g_user_list_mutex);

    return true;
}

/**
 * @brief  遍历链表
 */
void traverse_user_list(void)
{
    // 临时变量
    user_list_node_t *temp;
    // 遍历得到的数据
    user_list_node_t *pos;

    pthread_mutex_lock(&g_user_list_mutex);

    list_for_each_entry_safe(pos, temp, &g_user_list_head.list, list)
    {
        printf("user list data, name: [%s], age = %d\n", pos->node_data.name, pos->node_data.age);
    }

    pthread_mutex_unlock(&g_user_list_mutex);
}

/**
 * @brief  删除用户链表节点(删除所有符合要求的节点)
 * @param  node_data: 输入参数, 待删除节点数据
 */
void del_node_from_user_list(const user_list_node_data_t node_data)
{
    int ret = -1;
    // 临时变量
    user_list_node_t *temp_node = NULL;
    // 遍历得到的数据
    user_list_node_t *pos_node = NULL;

    pthread_mutex_lock(&g_user_list_mutex);

    list_for_each_entry_safe(pos_node, temp_node, &g_user_list_head.list, list)
    {
        ret = memcmp(&node_data, &pos_node->node_data, sizeof(user_list_node_data_t));
        if (0 == ret)
        {
            list_del(&pos_node->list);

            // 释放节点空间
            free(pos_node);
            pos_node = NULL;

            // 删除节点时, 链表长度减小
            g_user_list_head.len > 0 ? g_user_list_head.len-- : 0;
        }
    }

    pthread_mutex_unlock(&g_user_list_mutex);
}

/**
 * @brief  删除用户链表所有节点(不包括头节点)
 */
void del_all_node_from_user_list(void)
{
    // 临时变量
    user_list_node_t *temp_node = NULL;
    // 遍历得到的数据
    user_list_node_t *pos_node = NULL;

    pthread_mutex_lock(&g_user_list_mutex);

    list_for_each_entry_safe(pos_node, temp_node, &g_user_list_head.list, list)
    {
        list_del(&pos_node->list);

        // 释放节点空间
        free(pos_node);
        pos_node = NULL;

        // 删除节点时, 链表长度减小
        g_user_list_head.len > 0 ? g_user_list_head.len-- : 0;
    }

    pthread_mutex_unlock(&g_user_list_mutex);
}

/**
 * @brief  判断用户链表是否为空
 * @return true : 链表为空
 * @return false: 链表非空
 */
bool user_list_is_empty(void)
{
    return list_empty(&g_user_list_head.list);
}

/**
 * @brief  获取用户链表长度
 * @return 链表长度
 */
uint32_t get_user_list_len(void)
{
    return g_user_list_head.len;
}

/**
 * @brief  获取指定姓名对应的节点信息
 * @param  node_data: 输出参数, 获取到的节点信息(该项为NULL只判断是否有对应信息)
 * @param  name     : 输入参数, 待获取信息的姓名
 * @return true : 成功
 * @return false: 失败
 */
bool find_node_from_user_list(user_list_node_data_t *node_data, const char *name)
{
    int ret = -1;
    // 临时变量
    user_list_node_t *temp_node = NULL;
    // 遍历得到的数据
    user_list_node_t *pos_node = NULL;
    // 查找标志(true: 存在)
    bool find_flag = false;

    pthread_mutex_lock(&g_user_list_mutex);

    list_for_each_entry_safe(pos_node, temp_node, &g_user_list_head.list, list)
    {
        ret = memcmp(name, pos_node->node_data.name, strlen(name));
        if (0 == ret)
        {
            find_flag = true;

            if (node_data)
            {
                memcpy(node_data, &pos_node->node_data, sizeof(user_list_node_data_t));
            }
        }
    }

    pthread_mutex_unlock(&g_user_list_mutex);

    return find_flag;
}

/**
 * @brief  更新用户链表数据(不存在该节点, 则将数据插入链表)
 * @param  node_data: 输入参数, 待更新/插入的节点数据
 * @return true : 成功
 * @return false: 失败
 */
bool update_user_list_data(const user_list_node_data_t node_data)
{
    int ret = -1;
    // 临时变量
    user_list_node_t *temp_node = NULL;
    // 遍历得到的数据
    user_list_node_t *pos_node = NULL;
    // 查找标志(true: 存在)
    bool find_flag = false;

    pthread_mutex_lock(&g_user_list_mutex);

    list_for_each_entry_safe(pos_node, temp_node, &g_user_list_head.list, list)
    {
        // 存在指定设备
        ret = memcmp(node_data.name, pos_node->node_data.name, strlen(node_data.name));
        if (0 == ret)
        {
            find_flag = true;

            // 更新数据
            memcpy(pos_node->node_data.name, &node_data, sizeof(user_list_node_data_t));
        }
    }

    pthread_mutex_unlock(&g_user_list_mutex);

    // 不存在节点, 则插入
    if (!find_flag)
    {
        return add_node_to_user_list_tail(node_data);
    }

    return true;
}
