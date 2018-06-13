#ifndef __WINDOW_H__
#define	__WINDOW_H__

#include "touch.h"
#include "tftDisp.h"
#include "common.h"
#define TOUCH_MARGIN 10
void window_ctl(struTouch tpxy,struWin * win);
void buttom_event_ctl(struTouch tpxy,struWin * win,struButtomEvent * but_ent);
#endif