#ifndef _EMWIN_DEMO_H
#define _EMWIN_DEMO_H
#include "./SYSTEM/sys/sys.h"
#include "DIALOG.h"
#include "./BSP/LCD/lcd.h"
#include "FreeRTOS.h"
#include "task.h"

void emwin_main(void); /* emwin 例程入口 */

/* 使用GUI_BMP_Draw()函数绘制BMP图片的话 */
/* 图片是加载到RAM中的，因此不能大于BMPMEMORYSIZE */
/* 注意：显示BMP图片时内存申请使用的EMWIN的内存申请函数，因此 */
/* BMPMEMORYSIZE不能大于我们给EMWIN分配的内存池大小 */
#define BMPMEMORYSIZE 500*1024 /* 图片大小不大于500kb */

/* 绘制无需加载到RAM中的BMP图片时，图片每行的字节数 */
#define BMPPERLINESIZE 2*1024 

void emwin_create_bmppicture(uint8_t *filename, int x0, int y0, int Xsize, int Ysize);
void emwin_main(void); /* emwin例程入口 */

extern WM_HWIN MainCreateWindow(void);
extern WM_HWIN SubcheckCreateWindow(void);
extern WM_HWIN SubFatfsCreateWindow(void);
extern WM_HWIN SubGameCreateWindow(void);
extern WM_HWIN SubPictureCreateWindow(void);
extern WM_HWIN SubMoreCreateWindow(void);

int emwin_dispbmpex(uint8_t *BMPFileName, uint8_t mode, uint32_t x, uint32_t y, int member, int denom);


#endif

