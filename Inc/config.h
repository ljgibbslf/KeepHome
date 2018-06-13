#ifndef __CONFIG_H__
#define __CONFIG_H__

#include "common.h"
#include  <string.h>
//----------------------------------------------
void read_Wifi_Config(struWifi *);
void write_Wifi_Config(struWifi *);
void read_Sys_Config(struSet *);
void write_Sys_Config(struSet *);
#endif