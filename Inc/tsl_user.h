/**
  ******************************************************************************
  * @file    TouchSensing\TouchSensing_2touchkeys\Inc\tsl_user.h
  * @author  MCD Application Team
  * @version V1.0.0
  * @date    18-June-2014
  * @brief   Touch-Sensing user configuration.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT(c) 2014 STMicroelectronics</center></h2>
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __TSL_USER_H
#define __TSL_USER_H

#include "tsl.h"
#include "stm32f0xx_hal.h"

/* Select if you use STMStudio software (0=No, 1=Yes) */
#define USE_STMSTUDIO (0)

#if USE_STMSTUDIO > 0
#include "stmCriticalSection.h"
#define STMSTUDIO_LOCK {enterLock();}
#define STMSTUDIO_UNLOCK {exitLock();}
#else
#define STMSTUDIO_LOCK
#define STMSTUDIO_UNLOCK
#endif

typedef enum
{
  TSL_USER_STATUS_BUSY       = 0, /**< The bank acquisition is on-going */
  TSL_USER_STATUS_OK_NO_ECS  = 1, /**< The bank acquisition is ok, no time for ECS */
  TSL_USER_STATUS_OK_ECS_ON  = 2, /**< The bank acquisition is ok, ECS finished */
  TSL_USER_STATUS_OK_ECS_OFF = 3  /**< The bank acquisition is ok, ECS not executed */
} tsl_user_status_t;

/* Channel IOs definition */
#define CHANNEL_0_IO_MSK    (TSC_GROUP1_IO2)
#define CHANNEL_0_GRP_MSK   (TSC_GROUP1)
#define CHANNEL_0_SRC       (TSC_GROUP1_IDX) /* Index in source register (TSC->IOGXCR[]) */
#define CHANNEL_0_DEST      (0) /* Index in destination result array */

#define CHANNEL_1_IO_MSK    (TSC_GROUP1_IO3)
#define CHANNEL_1_GRP_MSK   (TSC_GROUP1)
#define CHANNEL_1_SRC       (TSC_GROUP1_IDX)
#define CHANNEL_1_DEST      (1)

#define CHANNEL_2_IO_MSK    (TSC_GROUP1_IO4)
#define CHANNEL_2_GRP_MSK   (TSC_GROUP1)
#define CHANNEL_2_SRC       (TSC_GROUP1_IDX)
#define CHANNEL_2_DEST      (2)

#define CHANNEL_3_IO_MSK    (TSC_GROUP2_IO2)
#define CHANNEL_3_GRP_MSK   (TSC_GROUP2)
#define CHANNEL_3_SRC       (TSC_GROUP2_IDX) 
#define CHANNEL_3_DEST      (3) 

#define CHANNEL_4_IO_MSK    (TSC_GROUP2_IO3)
#define CHANNEL_4_GRP_MSK   (TSC_GROUP2)
#define CHANNEL_4_SRC       (TSC_GROUP2_IDX)
#define CHANNEL_4_DEST      (4)

#define CHANNEL_5_IO_MSK    (TSC_GROUP2_IO4)
#define CHANNEL_5_GRP_MSK   (TSC_GROUP2)
#define CHANNEL_5_SRC       (TSC_GROUP2_IDX)
#define CHANNEL_5_DEST      (5)

#define CHANNEL_6_IO_MSK    (TSC_GROUP4_IO2)
#define CHANNEL_6_GRP_MSK   (TSC_GROUP4)
#define CHANNEL_6_SRC       (TSC_GROUP4_IDX) 
#define CHANNEL_6_DEST      (6) 

#define CHANNEL_7_IO_MSK    (TSC_GROUP4_IO3)
#define CHANNEL_7_GRP_MSK   (TSC_GROUP4)
#define CHANNEL_7_SRC       (TSC_GROUP4_IDX)
#define CHANNEL_7_DEST      (7)

#define CHANNEL_8_IO_MSK    (TSC_GROUP4_IO4)
#define CHANNEL_8_GRP_MSK   (TSC_GROUP4)
#define CHANNEL_8_SRC       (TSC_GROUP4_IDX)
#define CHANNEL_8_DEST      (8)

#define CHANNEL_9_IO_MSK    (TSC_GROUP6_IO2)
#define CHANNEL_9_GRP_MSK   (TSC_GROUP6)
#define CHANNEL_9_SRC       (TSC_GROUP6_IDX) 
#define CHANNEL_9_DEST      (9) 

#define CHANNEL_10_IO_MSK    (TSC_GROUP6_IO3)
#define CHANNEL_10_GRP_MSK   (TSC_GROUP6)
#define CHANNEL_10_SRC       (TSC_GROUP6_IDX)
#define CHANNEL_10_DEST      (10)

#define CHANNEL_11_IO_MSK    (TSC_GROUP6_IO4)
#define CHANNEL_11_GRP_MSK   (TSC_GROUP6)
#define CHANNEL_11_SRC       (TSC_GROUP6_IDX)
#define CHANNEL_11_DEST      (11)

/* Shield IOs definition */
#define SHIELD_IO_MSK       (0)

/* Banks definition */
#define BANK_0_NBCHANNELS    (4)
#define BANK_0_MSK_CHANNELS  (CHANNEL_0_IO_MSK | CHANNEL_3_IO_MSK|CHANNEL_6_IO_MSK|CHANNEL_9_IO_MSK)
#define BANK_0_MSK_GROUPS    (CHANNEL_0_GRP_MSK|CHANNEL_3_GRP_MSK|CHANNEL_6_GRP_MSK|CHANNEL_9_GRP_MSK)

#define BANK_1_NBCHANNELS    (4)
#define BANK_1_MSK_CHANNELS  (CHANNEL_1_IO_MSK | CHANNEL_4_IO_MSK|CHANNEL_7_IO_MSK|CHANNEL_10_IO_MSK)
#define BANK_1_MSK_GROUPS    (CHANNEL_1_GRP_MSK|CHANNEL_4_GRP_MSK|CHANNEL_7_GRP_MSK|CHANNEL_10_GRP_MSK)

#define BANK_2_NBCHANNELS    (4)
#define BANK_2_MSK_CHANNELS  (CHANNEL_2_IO_MSK | CHANNEL_5_IO_MSK|CHANNEL_8_IO_MSK|CHANNEL_11_IO_MSK)
#define BANK_2_MSK_GROUPS    (CHANNEL_2_GRP_MSK|CHANNEL_5_GRP_MSK|CHANNEL_8_GRP_MSK|CHANNEL_11_GRP_MSK)

/* User Parameters */
extern CONST TSL_Bank_T MyBanks[];
extern CONST TSL_TouchKey_T MyTKeys[];
extern CONST TSL_Object_T MyObjects[];
extern TSL_ObjectGroup_T MyObjGroup;

void tsl_user_Init(void);
tsl_user_status_t tsl_user_Exec(void);
void tsl_user_SetThresholds(void);

#endif /* __TSL_USER_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
