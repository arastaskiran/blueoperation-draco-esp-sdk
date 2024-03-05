/**
 * @file draco_item_list.cpp
 * @author Aras Taşkıran (aras.taskiran@argeloji.com)
 * @brief
 * @version 0.1
 * @date 2024-03-04
 *
 * @copyright Copyright (c) 2024 Argeloji Mühendislik
 *
 */
#include "draco_item_list.h"
#include <draco_item.h>

void DracoItemList::insert(DracoItem *new_data)
{
    struct IONode *new_node = (struct IONode *)malloc(sizeof(struct IONode));
    new_node->data = new_data;

    if (this->head == NULL)
    {
        new_node->next = NULL;
        this->head = this->tail = new_node;
        return;
    }
    new_node->next = NULL;
    this->tail->next = new_node;
    this->tail = new_node;
}