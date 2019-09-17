// Copyright (c) 2019 FunSociety
#ifndef HEY_OS_PIC_H_
#define HEY_OS_PIC_H_

#include <port.h>

namespace heyos {

namespace pic {

extern port8_slow pic_master_command;
extern port8_slow pic_master_data;
extern port8_slow pic_slave_command;
extern port8_slow pic_slave_data;

void init();

}  // namespace pic

}  // namespace heyos

#endif // HEY_OS_PIC_H_
