/*++
 
 Copyright (c) 2012-2022 ChipOne Technology (Beijing) Co., Ltd. All Rights Reserved.
 This PROPRIETARY SOFTWARE is the property of ChipOne Technology (Beijing) Co., Ltd. 
 and may contains trade secrets and/or other confidential information of ChipOne 
 Technology (Beijing) Co., Ltd. This file shall not be disclosed to any third party,
 in whole or in part, without prior written consent of ChipOne.  
 THIS PROPRIETARY SOFTWARE & ANY RELATED DOCUMENTATION ARE PROVIDED AS IS, 
 WITH ALL FAULTS, & WITHOUT WARRANTY OF ANY KIND. CHIPONE DISCLAIMS ALL EXPRESS OR 
 IMPLIED WARRANTIES.  
 
 File Name:    icn83xx.h
 Abstract:
              input driver.
Author:       Zhimin Tian
Date :        01,17,2013
Version:      1.0
History :
   2012,10,30, V0.1 first version  

 --*/

#ifndef __LINUX_ICN83XX_H__
#define __LINUX_ICN83XX_H__

#include <linux/i2c.h>
#include <linux/input.h>
#ifdef CONFIG_HAS_EARLYSUSPEND
    #include <linux/pm.h>
    #include <linux/earlysuspend.h>
#endif
#include <linux/interrupt.h>
#include <linux/delay.h>
#include <linux/interrupt.h>
#include <linux/errno.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/slab.h>
#include <linux/platform_device.h>
#include <linux/async.h>
#include <linux/hrtimer.h>
#include <linux/init.h>
#include <linux/ioport.h>
#include <asm/irq.h>
#include <asm/io.h>
#include <asm/uaccess.h>
#include <linux/input.h>
#include <linux/input/mt.h>
#include <linux/hrtimer.h>
#include <linux/proc_fs.h>

#include <linux/init.h>  
#include <linux/kernel.h>  
#include <linux/fs.h>  
 #include <linux/semaphore.h>  
#include <linux/cdev.h>  
#include <linux/device.h>  
#include <linux/ioctl.h>  
#include <linux/slab.h>  
#include <linux/errno.h>  
#include <linux/string.h>  
#include <linux/spinlock_types.h> 

//-----------------------------------------------------------------------------
// Pin Declarations
//-----------------------------------------------------------------------------
#define SUPPORT_AMLOGIC          1
#define SUPPORT_ALLWINNER_A13    0
#define SUPPORT_ROCKCHIP         0
#define SUPPORT_SPREADTRUM       0

#if SUPPORT_ALLWINNER_A13

#include <mach/irqs.h>
#include <mach/system.h>
#include <mach/hardware.h>
#include <mach/sys_config.h>
#include "ctp_platform_ops.h"

#define CTP_IRQ_PORT             SW_INT_IRQNO_PIO
#define CTP_IRQ_MODE             (NEGATIVE_EDGE)
#define CTP_RST_PORT             0
#define CTP_WAKEUP_PORT          0
#define CTP_REPORT_PROTOCOL      0   //0: A protocol
                                     //1: B protocol
#define SCREEN_MAX_X             (screen_max_x)
#define SCREEN_MAX_Y             (screen_max_y)

#endif

#if SUPPORT_ROCKCHIP
#include <linux/irq.h>
#include <mach/irqs.h>
#include <mach/system.h>
#include <mach/hardware.h>
#include <mach/board.h>
#include <mach/gpio.h>

#define CTP_IRQ_PORT             RK30_PIN4_PC2
#define CTP_IRQ_MODE             0
#define CTP_RST_PORT             0
#define CTP_WAKEUP_PORT          0
#define CTP_REPORT_PROTOCOL      1   //0: A protocol
                                     //1: B protocol
#define SCREEN_MAX_X             (800)
#define SCREEN_MAX_Y             (480)
#define ICN83XX_I2C_SCL          400*1000

#endif

#if SUPPORT_SPREADTRUM

#include <mach/irqs.h>
#include <mach/system.h>
#include <mach/hardware.h>
#include <mach/ldo.h>
#include <mach/eic.h>
#include <linux/gpio.h>
#include <mach/gpio.h>

#define CTP_IRQ_PORT             0
#define CTP_IRQ_MODE             0
#define CTP_RST_PORT             sprd_3rdparty_gpio_tp_rst
#define CTP_WAKEUP_PORT          0
#define CTP_REPORT_PROTOCOL      0   //0: A protocol
                                     //1: B protocol
#define SCREEN_MAX_X             (540)
#define SCREEN_MAX_Y             (960)

extern int sprd_3rdparty_gpio_tp_rst ;
extern int sprd_3rdparty_tp_ldo_id ;
extern int sprd_3rdparty_tp_ldo_level;

#endif

#if  SUPPORT_AMLOGIC
#include <linux/irq.h>
#include <mach/irqs.h>
#include <mach/hardware.h>
#include <mach/gpio.h>
#include <mach/gpio_data.h>
#define CTP_REPORT_PROTOCOL      1   //0: A protocol
                                     //1: B protocol
#define SCREEN_MAX_X             (1024)
#define SCREEN_MAX_Y             (600)
#endif
//-----------------------------------------------------------------------------
// Global CONSTANTS
//-----------------------------------------------------------------------------

#define TOUCH_VIRTUAL_KEYS          0
#define SUPPORT_PROC_FS             0//1
#define SUPPORT_SYSFS               1
#define SUPPORT_FW_UPDATE           1//0
#define COMPILE_FW_WITH_DRIVER      0
#define FORCE_UPDATA_FW             0//1
#define SUPPORT_FW_CALIB            0//1

#define ICN83XX_NAME                "chipone-ts"
#define ICN83XX_PROG_IIC_ADDR       (0x60>>1)
#define CTP_NAME                    ICN83XX_NAME

#define CTP_RESET_LOW_PERIOD        (5)
#define CTP_RESET_HIGH_PERIOD       (100)
#define CTP_WAKEUP_LOW_PERIOD       (20)
#define CTP_WAKEUP_HIGH_PERIOD      (50)
#define CTP_POLL_TIMER              (16)    /* ms delay between samples */
#define CTP_START_TIMER             (100)    /* ms delay between samples */

#define POINT_NUM                   5
#define POINT_SIZE                  7

#define TS_KEY_HOME                 102
#define TS_KEY_MENU                 139
#define TS_KEY_BACK                 158
#define TS_KEY_SEARCH               217

#define ICN_VIRTUAL_BUTTON_HOME     0x02
#define ICN_VIRTUAL_BUTTON_MENU     0x01
#define ICN_VIRTUAL_BUTTON_BACK     0x04
#define ICN_VIRTUAL_BUTTON_SEARCH   0x08

#define IIC_RETRY_NUM               3

//ICN83XX_REG_PMODE
#define PMODE_ACTIVE                0x00
#define PMODE_MONITOR               0x01
#define PMODE_HIBERNATE             0x02

#define B_SIZE                      64
#define ENABLE_BYTE_CHECK




//-----------------------------------------------------------------------------
// Macro DEFINITIONS
//-----------------------------------------------------------------------------
#define DBG_ICN83XX_TRACE
//#define DBG_ICN83XX_POINT
//#define DBG_ICN83XX_INFO
#define DBG_ICN83XX_ERROR
#define DBG_FLASH_INFO
#define DBG_FLASH_ERROR
#define DBG_OP_INFO
#define DBG_OP_ERROR
#define DBG_CALIB_INFO
#define DBG_CALIB_ERROR
//#define DBG_PROC_INFO
#define DBG_PROC_ERROR


#ifdef DBG_ICN83XX_TRACE
#define icn83xx_trace(fmt, args...)   \
        do{                              \
                printk(fmt, ##args);     \
        }while(0)
#else
#define icn83xx_trace(fmt, args...)   //
#endif


#ifdef DBG_ICN83XX_POINT
#define icn83xx_point_info(fmt, args...)   \
        do{                              \
                printk(fmt, ##args);     \
        }while(0)
#else
#define icn83xx_point_info(fmt, args...)   //
#endif

#ifdef DBG_ICN83XX_INFO
#define icn83xx_info(fmt, args...)   \
        do{                              \
                printk(fmt, ##args);     \
        }while(0)
#else
#define icn83xx_info(fmt, args...)   //
#endif

#ifdef DBG_ICN83XX_ERROR
#define icn83xx_error(fmt, args...)   \
        do{                              \
                printk(fmt, ##args);     \
        }while(0)
#else
#define icn83xx_error(fmt, args...)   //
#endif

#ifdef DBG_FLASH_INFO
#define flash_info(fmt, args...)   \
        do{                              \
                printk(fmt, ##args);     \
        }while(0)
#else
#define flash_info(fmt, args...)   //
#endif

#ifdef DBG_FLASH_ERROR
#define flash_error(fmt, args...)   \
        do{                              \
                printk(fmt, ##args);     \
        }while(0)
#else
#define flash_error(fmt, args...)   //
#endif


#ifdef DBG_OP_INFO
#define op_info(fmt, args...)   \
        do{                              \
                printk(fmt, ##args);     \
        }while(0)
#else
#define op_info(fmt, args...)   //
#endif
#ifdef DBG_OP_ERROR
#define op_error(fmt, args...)   \
        do{                              \
                printk(fmt, ##args);     \
        }while(0)
#else
#define op_error(fmt, args...)   //
#endif


#ifdef DBG_CALIB_INFO
#define calib_info(fmt, args...)   \
        do{                              \
                printk(fmt, ##args);     \
        }while(0)
#else
#define calib_info(fmt, args...)   //
#endif

#ifdef DBG_CALIB_ERROR
#define calib_error(fmt, args...)   \
        do{                              \
                printk(fmt, ##args);     \
        }while(0)
#else
#define calib_error(fmt, args...)   //
#endif


#ifdef DBG_PROC_INFO
#define proc_info(fmt, args...)   \
        do{                              \
                printk(fmt, ##args);     \
        }while(0)
#else
#define proc_info(fmt, args...)   //
#endif

#ifdef DBG_PROC_ERROR
#define proc_error(fmt, args...)   \
        do{                              \
                printk(fmt, ##args);     \
        }while(0)
#else
#define proc_error(fmt, args...)   //
#endif

#define swap_ab(a,b)       {char temp;temp=a;a=b;b=temp;}
#define U16LOBYTE(var)     (*(unsigned char *) &var) 
#define U16HIBYTE(var)     (*(unsigned char *)((unsigned char *) &var + 1))     



//-----------------------------------------------------------------------------
// Struct, Union and Enum DEFINITIONS
//-----------------------------------------------------------------------------
typedef struct _POINT_INFO
{
    unsigned char  u8ID;
    unsigned short u16PosX;     // coordinate X, plus 4 LSBs for precision extension
    unsigned short u16PosY;     // coordinate Y, plus 4 LSBs for precision extension
    unsigned char  u8Pressure;
    unsigned char  u8EventId;
}POINT_INFO;

struct icn83xx_ts_data {
    struct i2c_client        *client;
    struct input_dev         *input_dev;
    struct work_struct       pen_event_work;
    struct workqueue_struct  *ts_workqueue;
    struct early_suspend     early_suspend;

    struct hrtimer           timer;
    spinlock_t               irq_lock;
    struct semaphore         sem;  

    POINT_INFO  point_info[POINT_NUM+1];
    int         point_num;
    int         irq;
    int         irq_is_disable;
    int         use_irq;
    int         work_mode;
    int         screen_max_x;
    int         screen_max_y;
    int         revert_x_flag;
    int         revert_y_flag;
    int         exchange_x_y_flag;    
};

#pragma pack(1)
typedef struct{
    unsigned char  wr;         //write read flag��0:R  1:W
    unsigned char  flag;       //0:
    unsigned char  circle;     //polling cycle 
    unsigned char  times;      //plling times
    unsigned char  retry;      //I2C retry times
    unsigned int   data_len;   //data length
    unsigned char  addr_len;   //address length
    unsigned char  addr[2];    //address    
    unsigned char* data;       //data pointer
}pack_head;
#pragma pack()

#define DATA_LENGTH_UINT            512
#define CMD_HEAD_LENGTH             (sizeof(pack_head) - sizeof(unsigned char *))
#define ICN83XX_ENTRY_NAME          "icn83xx_tool"


enum icn83xx_ts_regs {
    ICN83XX_REG_PMODE   = 0x04, /* Power Consume Mode       */  
};

typedef enum
{
    R_OK = 100,
    R_FILE_ERR,
    R_STATE_ERR,
    R_ERASE_ERR,
    R_PROGRAM_ERR,
    R_VERIFY_ERR,
}E_UPGRADE_ERR_TYPE;

//-----------------------------------------------------------------------------
// Global VARIABLES
//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------
// Function PROTOTYPES
//-----------------------------------------------------------------------------

void icn83xx_ts_reset(void);
int  icn83xx_i2c_rxdata(unsigned char addr, char *rxdata, int length);
int  icn83xx_i2c_txdata(unsigned char addr, char *txdata, int length);
int  icn83xx_write_reg(unsigned char addr, char para);
int  icn83xx_read_reg(unsigned char addr, char *pdata);
int  icn83xx_prog_i2c_rxdata(unsigned short addr, char *rxdata, int length);
int  icn83xx_prog_i2c_txdata(unsigned short addr, char *txdata, int length);
int  icn83xx_prog_write_reg(unsigned short addr, char para);
int  icn83xx_prog_read_reg(unsigned short addr, char *pdata);

#if SUPPORT_FW_UPDATE

int  icn83xx_writeInfo(unsigned short addr, char value);
int  icn83xx_readInfo(unsigned short addr, char *value);
int  icn83xx_writeReg(unsigned short addr, char value);
int  icn83xx_readReg(unsigned short addr, char *value);
int  icn83xx_readVersion(void);
int  icn83xx_changemode(char mode);
int  icn83xx_readrawdata(char *buffer, char row, char length);
int  icn83xx_readTP(char row_num, char column_num, char *buffer);
int  icn83xx_scanTP(void);
void icn83xx_rawdatadump(short *mem, int size, char br);
void icn83xx_set_fw(int size, unsigned char *buf);
void icn83xx_memdump(char *mem, int size);
int  icn83xx_checksum(int sum, char *buf, unsigned int size);
int  icn83xx_update_status(int status);
int  icn83xx_get_status(void);
int  icn83xx_open_fw( char *fw);
int  icn83xx_read_fw(int offset, int length, char *buf);
int  icn83xx_close_fw(void);
int  icn83xx_goto_progmode(void);
int  icn83xx_check_progmod(void);
int  icn83xx_uu(void);
int  icn83xx_ll(void);
int  icn83xx_op1(char info, unsigned short offset, unsigned int size);
int  icn83xx_op2(char info, unsigned short offset, unsigned char * buffer, unsigned int size);
int  icn83xx_op3(char info, unsigned short offset, unsigned char * buffer, unsigned int size);
short  icn83xx_read_fw_Ver(char *fw);
E_UPGRADE_ERR_TYPE  icn83xx_fw_update(char *fw);
#endif

#if SUPPORT_FW_CALIB

int  icn83xx_checkrawdata(short *data, char num);
int  icn83xx_readpara(char *TxOrder, char row, char *RxOrder, char column);
int  icn83xx_writepara(char *TxOrder, char row, char *RxOrder, char column);
int  icn83xx_readFB(char *FB, char num);
int  icn83xx_writeFB(char *FB, char num);
int  icn83xx_readDC(char *DC, char num);
int  icn83xx_writeDC(char *DC, char num);
int  icn83xx_readPhaseDelay(char *PD, char row, char length);
int  icn83xx_writePhaseDelay(char *PD, char row, char length);
int  icn83xx_changeDCflag(char flag);
int  icn83xx_readVkmode(char *vkmode, char *vknum);
int  icn83xx_setTarget(short target);
int  icn83xx_setPeakGroup(short peak, short group);
int  icn83xx_setDownUp(short down, short up);
int  icn83xx_average(short *data, char num);

int  icn83xx_calib(char index, char *FB);
#endif

static unsigned char icn83xx_fw[] = {
	
};
#endif

