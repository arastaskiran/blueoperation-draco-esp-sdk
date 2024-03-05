/**
 * @file draco_item_list.h
 * @author Aras Taşkıran (aras.taskiran@argeloji.com)
 * @brief
 * @version 0.1
 * @date 2024-03-04
 *
 * @copyright Copyright (c) 2024 Argeloji Mühendislik
 *
 */
#ifndef DRACO_ITEM_LIST
#define DRACO_ITEM_LIST

#include <iostream>
#include <draco_item.h>

struct IONode
{
    DracoItem *data;
    struct IONode *next;
};

class DracoItemList
{
public:
    struct IONode *head = NULL;
    struct IONode *tail = NULL;
    void insert(DracoItem *new_data);
};
#endif