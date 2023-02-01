/**
 * @file      : main.c
 * @brief     : 程序入口文件
 * @author    : huenrong (huenrong1028@outlook.com)
 * @date      : 2023-02-01 21:23:41
 *
 * @copyright : Copyright (c) 2023 huenrong
 *
 * @history   : date       author          description
 *              2023-02-01 huenrong        创建文件
 *
 */

#include <stdio.h>
#include <string.h>

#include "./user_list/user_list.h"

/**
 * @brief  : 程序入口
 * @param  : argc: 输入参数, 参数个数
 * @param  : argv: 输入参数, 参数列表
 * @return : 成功: 0
 *           失败: 其它
 */
int main(int argc, char *argv[])
{
    // 获取到的用户链表长度
    uint32_t user_list_len = -1;
    // 用户链表节点数据
    user_list_node_data_t node_data = {0};

    // 初始化链表
    printf("-------------init user list-------------\n\n");
    init_user_list();

    // 获取链表长度
    printf("-------------get user list len-------------\n");
    user_list_len = get_user_list_len();
    printf("user_list_len = %d\n\n", user_list_len);

    // 查找节点"name_0"
    printf("-------------find node name_0-------------\n");
    if (find_node_from_user_list(NULL, "name_0"))
    {
        printf("find node name_0\n\n");
    }
    else
    {
        printf("not found node name_0\n\n");
    }

    // 插入数据
    printf("-------------insert data to user list tail-------------\n");
    for (uint8_t i = 0; i < 5; i++)
    {
        if (0 == i)
        {
            snprintf(node_data.name, sizeof(node_data.name), "name_%d", 0);
            node_data.age = (0 * 10);
        }
        else
        {
            snprintf(node_data.name, sizeof(node_data.name), "name_%d", i);
            node_data.age = (i * 10);
        }

        if (add_node_to_user_list_tail(node_data))
        {
            printf("insert data, name:[%s], age: %d\n", node_data.name, node_data.age);
        }
        else
        {
            printf("add_node_to_user_list_tail fail\n");

            return -1;
        }
    }

    // 获取链表长度
    printf("\n-------------get user list len-------------\n");
    user_list_len = get_user_list_len();
    printf("user_list_len = %d\n\n", user_list_len);

    // 遍历链表
    printf("-------------show all node data-------------\n");
    traverse_user_list();

    // 查找节点"name_0"
    printf("-------------find node name_0-------------\n");
    if (find_node_from_user_list(NULL, "name_0"))
    {
        printf("find node name_0\n\n");
    }
    else
    {
        printf("not found node name_0\n\n");
    }

    // 获取节点"name_0"信息
    printf("-------------get node name_0 info-------------\n");
    memset(&node_data, 0, sizeof(user_list_node_data_t));
    if (find_node_from_user_list(&node_data, "name_0"))
    {
        printf("node name_0 info, name: [%s], age: %d\n\n", node_data.name, node_data.age);
    }
    else
    {
        printf("get node name_0 info fail\n\n");
    }

    // 更新节点"name_0"年龄为100
    printf("-------------update node name_0 age to 100-------------\n\n");
    memcpy(node_data.name, "name_0", strlen("name_0"));
    node_data.age = 100;
    if (!update_user_list_data(node_data))
    {
        printf("update node name_0 age fail\n");
    }

    // 获取节点"name_0"信息
    printf("-------------get node name_0 info-------------\n");
    memset(&node_data, 0, sizeof(user_list_node_data_t));
    if (find_node_from_user_list(&node_data, "name_0"))
    {
        printf("node name_0 info, name: [%s], age: %d\n\n", node_data.name, node_data.age);
    }
    else
    {
        printf("get node name_0 info fail\n\n");
    }

    // 删除节点"name_0"
    printf("-------------delete node name_0-------------\n");
    del_node_from_user_list(node_data);

    // 遍历链表
    printf("-------------show all node data-------------\n");
    traverse_user_list();

    // 获取链表长度
    printf("\n-------------get user list len-------------\n");
    user_list_len = get_user_list_len();
    printf("user_list_len = %d\n\n", user_list_len);

    // 删除所有节点
    printf("\n-------------delete all node-------------\n\n");
    del_all_node_from_user_list();

    // 获取链表长度
    printf("-------------get user list len-------------\n");
    user_list_len = get_user_list_len();
    printf("user_list_len = %d\n\n", user_list_len);

    return 0;
}
