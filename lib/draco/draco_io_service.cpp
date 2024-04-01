#include <draco_io_service.h>

DracoItemList *DracoIoService::io_list{new DracoItemList()};

void DracoIoService::addIO(int io, int mode, int addr, unsigned int type, bool inverted, bool feed_back)
{
    io_list->insert(new DracoItem(io, mode, addr, type, inverted, feed_back));
}

DracoItemList *DracoIoService::getIoList()
{
    return io_list;
}