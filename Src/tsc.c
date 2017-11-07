/**
  ******************************************************************************
  * File Name          : TSC.c
  * Description        : This file provides code for the configuration
  *                      of the TSC instances.
  ******************************************************************************
  ** This notice applies to any and all portions of this file
  * that are not between comment pairs USER CODE BEGIN and
  * USER CODE END. Other portions of this file, whether 
  * inserted by the user or by software development tools
  * are owned by their respective copyright owners.
  *
  * COPYRIGHT(c) 2017 STMicroelectronics
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

/* Includes ------------------------------------------------------------------*/
#include "tsc.h"

#include "gpio.h"

/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

TSC_HandleTypeDef htsc;

/* TSC init function */
void MX_TSC_Init(void)
{

    /**Configure the TSC peripheral 
    */
  htsc.Instance = TSC;
  htsc.Init.CTPulseHighLength = TSC_CTPH_2CYCLES;
  htsc.Init.CTPulseLowLength = TSC_CTPL_2CYCLES;
  htsc.Init.SpreadSpectrum = DISABLE;
  htsc.Init.SpreadSpectrumDeviation = 1;
  htsc.Init.SpreadSpectrumPrescaler = TSC_SS_PRESC_DIV1;
  htsc.Init.PulseGeneratorPrescaler = TSC_PG_PRESC_DIV64;
  htsc.Init.MaxCountValue = TSC_MCV_8191;
  htsc.Init.IODefaultMode = TSC_IODEF_OUT_PP_LOW;
  htsc.Init.SynchroPinPolarity = TSC_SYNC_POLARITY_FALLING;
  htsc.Init.AcquisitionMode = TSC_ACQ_MODE_NORMAL;
  htsc.Init.MaxCountInterrupt = DISABLE;
  htsc.Init.ChannelIOs = TSC_GROUP1_IO2|TSC_GROUP1_IO3|TSC_GROUP1_IO4|TSC_GROUP2_IO2
                    |TSC_GROUP2_IO3|TSC_GROUP2_IO4|TSC_GROUP4_IO2|TSC_GROUP4_IO3
                    |TSC_GROUP4_IO4|TSC_GROUP6_IO2|TSC_GROUP6_IO3|TSC_GROUP6_IO4;
  htsc.Init.SamplingIOs = TSC_GROUP1_IO1|TSC_GROUP2_IO1|TSC_GROUP4_IO1|TSC_GROUP6_IO1;
  if (HAL_TSC_Init(&htsc) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

}

void HAL_TSC_MspInit(TSC_HandleTypeDef* tscHandle)
{

  GPIO_InitTypeDef GPIO_InitStruct;
  if(tscHandle->Instance==TSC)
  {
  /* USER CODE BEGIN TSC_MspInit 0 */

  /* USER CODE END TSC_MspInit 0 */
    /* TSC clock enable */
    __HAL_RCC_TSC_CLK_ENABLE();
  
    /**TSC GPIO Configuration    
    PA0     ------> TSC_G1_IO1
    PA1     ------> TSC_G1_IO2
    PA2     ------> TSC_G1_IO3
    PA3     ------> TSC_G1_IO4
    PA4     ------> TSC_G2_IO1
    PA5     ------> TSC_G2_IO2
    PA6     ------> TSC_G2_IO3
    PA7     ------> TSC_G2_IO4
    PB11     ------> TSC_G6_IO1
    PB12     ------> TSC_G6_IO2
    PB13     ------> TSC_G6_IO3
    PB14     ------> TSC_G6_IO4
    PA9     ------> TSC_G4_IO1
    PA10     ------> TSC_G4_IO2
    PA11     ------> TSC_G4_IO3
    PA12     ------> TSC_G4_IO4 
    */
    GPIO_InitStruct.Pin = Ref_1_Pin|Ref_2_Pin|Ref_3_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_OD;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    GPIO_InitStruct.Alternate = GPIO_AF3_TSC;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = TC1_Pin|TC2_Pin|TC3_Pin|TC4_Pin 
                          |TC5_Pin|TC6_Pin|TC7_Pin|TC8_Pin 
                          |TC9_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    GPIO_InitStruct.Alternate = GPIO_AF3_TSC;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = Ref_4_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_OD;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    GPIO_InitStruct.Alternate = GPIO_AF3_TSC;
    HAL_GPIO_Init(Ref_4_GPIO_Port, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = TC10_Pin|TC11_Pin|TC12_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    GPIO_InitStruct.Alternate = GPIO_AF3_TSC;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /* USER CODE BEGIN TSC_MspInit 1 */

  /* USER CODE END TSC_MspInit 1 */
  }
}

void HAL_TSC_MspDeInit(TSC_HandleTypeDef* tscHandle)
{

  if(tscHandle->Instance==TSC)
  {
  /* USER CODE BEGIN TSC_MspDeInit 0 */

  /* USER CODE END TSC_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_TSC_CLK_DISABLE();
  
    /**TSC GPIO Configuration    
    PA0     ------> TSC_G1_IO1
    PA1     ------> TSC_G1_IO2
    PA2     ------> TSC_G1_IO3
    PA3     ------> TSC_G1_IO4
    PA4     ------> TSC_G2_IO1
    PA5     ------> TSC_G2_IO2
    PA6     ------> TSC_G2_IO3
    PA7     ------> TSC_G2_IO4
    PB11     ------> TSC_G6_IO1
    PB12     ------> TSC_G6_IO2
    PB13     ------> TSC_G6_IO3
    PB14     ------> TSC_G6_IO4
    PA9     ------> TSC_G4_IO1
    PA10     ------> TSC_G4_IO2
    PA11     ------> TSC_G4_IO3
    PA12     ------> TSC_G4_IO4 
    */
    HAL_GPIO_DeInit(GPIOA, Ref_1_Pin|TC1_Pin|TC2_Pin|TC3_Pin 
                          |Ref_2_Pin|TC4_Pin|TC5_Pin|TC6_Pin 
                          |Ref_3_Pin|TC7_Pin|TC8_Pin|TC9_Pin);

    HAL_GPIO_DeInit(GPIOB, Ref_4_Pin|TC10_Pin|TC11_Pin|TC12_Pin);

  /* USER CODE BEGIN TSC_MspDeInit 1 */

  /* USER CODE END TSC_MspDeInit 1 */
  }
} 

/* USER CODE BEGIN 1 */

/* USER CODE END 1 */

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
