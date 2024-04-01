/**
 * @file draco_io_service.h
 * @author Aras Taşkıran (aras.taskiran@argeloji.com)
 * @brief
 * @version 0.1
 * @date 2024-03-04
 *
 * @copyright Copyright (c) 2024 Argeloji Mühendislik
 *
 */
#ifndef DRACO_IO_SERVICE_H
#define DRACO_IO_SERVICE_H
#include "draco_item_list.h"
#include "draco_item.h"
#include "device_type.h"
class DracoIoService
{

public:
    /**
     * @brief Add Draco IO
     * @param io int
     * @param mode int
     * @param addr int
     * @param type IoType
     * @param inverted bool
     *
     * @return Void
     */
    static void addIO(int io, int mode = 0x2, int addr = 0, unsigned int type = 0, bool inverted = false,bool feed_back=true);

    static DracoItemList *getIoList();

private:
    static DracoItemList *io_list;
};
#endif