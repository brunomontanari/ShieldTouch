/**
  ******************************************************************************
  * File Name          : main.c
  * Description        : Main program body
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
#include "main.h"
#include "stm32f0xx_hal.h"
#include "spi.h"
#include "tim.h"
#include "tsc.h"
#include "usart.h"
#include "gpio.h"

/* USER CODE BEGIN Includes */
#include "tsl_user.h"
/* USER CODE END Includes */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
/* Private variables ---------------------------------------------------------*/
#define USE_USART 1
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);

/* USER CODE BEGIN PFP */
/* Private function prototypes -----------------------------------------------*/

/* USER CODE END PFP */

/* USER CODE BEGIN 0 */

#define NUMERO_TECLAS           12
#define LIMITE_TECLAS_SIMULTANEAS 3

#define TC1              0x00
#define TC2              0x01
#define TC3              0x02
#define TC4              0x03
#define TC5              0x04
#define TC6              0x05
#define TC7              0x06
#define TC8              0x07
#define TC9              0x08
#define TC10             0x09
#define TC11             0x0A
#define TC12             0x0B

#define TAMANHO_ENVIO           0x01
#define TIMEOUT_ENVIO           30

#define TECLA1              0x0F//0b00001111//0x01
#define TECLA2              0x07//0b00000111//0x02
#define TECLA3              0x03//0b00000011//0x03
#define TECLA4              0x0E//0b00001110//0x04
#define TECLA5              0x06//0b00000110//0x05
#define TECLA6              0x02//0b00000010//0x06
#define TECLA7              0x0D//0b00001101//0x07
#define TECLA8              0x05//0b00000101//0x08
#define TECLA9              0x01//0b00000001//0x09
#define TECLA0              0x04//0b00000100//0x00
#define TECLA_CANCELA       0x0C//0b00001100//0x0B
#define TECLA_OK            0x00//0b00000000//0x0C

char WaterProof_Process(void);//tsl_user_status_t tsl_status);
char Process_Sensors(void);//tsl_user_status_t status);

TSC_IOConfigTypeDef tsc_config;
uint32_t Tecla[NUMERO_TECLAS];
uint32_t ReferenciaTecla[NUMERO_TECLAS] = {0,0,0,0,0,0,0,0,0,0,0,0};
uint8_t StatusTecla[NUMERO_TECLAS] = {0};
uint8_t Recebe_Tecla[NUMERO_TECLAS] = {0};
uint8_t Envia_Tecla_NaoPress = 0xFF;
uint8_t Envia_Tecla[NUMERO_TECLAS] = {
                     TECLA_CANCELA,
                     TECLA7,
                     TECLA2,
                     TECLA5,
                     TECLA8,
                     TECLA0,
                     TECLA3,
                     TECLA6,
                     TECLA9,
                     TECLA_OK,
                     TECLA4,
                     TECLA1
                     };
/* USER CODE END 0 */

int main(void)
{

  /* USER CODE BEGIN 1 */
  tsl_user_status_t tsl_status;
  /* USER CODE END 1 */

  /* MCU Configuration----------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_SPI1_Init();
  MX_TIM6_Init();
  MX_TIM17_Init();
  MX_TSC_Init();
  MX_USART1_UART_Init();

  /* USER CODE BEGIN 2 */
  //HAL_GPIO_WritePin(GPIOB,GPIO_PIN_0,GPIO_PIN_RESET);
  HAL_Delay(200);
  tsl_user_Init();
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
  /* USER CODE END WHILE */

  /* USER CODE BEGIN 3 */
    tsl_status = tsl_user_Exec();
    if(tsl_status != TSL_USER_STATUS_BUSY)
    {
      if(WaterProof_Process())
      {
        Process_Sensors();
      }
      else
      {
        tsl_user_Init(); //força recalibração
        HAL_Delay(100);
      }
    }
  }
  /* USER CODE END 3 */

}

/** System Clock Configuration
*/
void SystemClock_Config(void)
{

  RCC_OscInitTypeDef RCC_OscInitStruct;
  RCC_ClkInitTypeDef RCC_ClkInitStruct;
  RCC_PeriphCLKInitTypeDef PeriphClkInit;

    /**Initializes the CPU, AHB and APB busses clocks 
    */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI48;
  RCC_OscInitStruct.HSI48State = RCC_HSI48_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

    /**Initializes the CPU, AHB and APB busses clocks 
    */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI48;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_1) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_USART1;
  PeriphClkInit.Usart1ClockSelection = RCC_USART1CLKSOURCE_PCLK1;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

    /**Configure the Systick interrupt time 
    */
  HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq()/1000);

    /**Configure the Systick 
    */
  HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);

  /* SysTick_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(SysTick_IRQn, 0, 0);
}

/* USER CODE BEGIN 4 */

/**
  * @brief  Display sensors information on SPI
  * @param  status TSL user status
  * @retval None
  */
char Process_Sensors(void)// tsl_user_status_t status)
{  
  char i;
  char j = 0;
  for(i = 0; i < NUMERO_TECLAS; i++)
  { 
    if (MyTKeys[i].p_Data->StateId == TSL_STATEID_DETECT)
    {
#ifdef USE_SPI      
      HAL_SPI_TransmitReceive(&hspi1,&Envia_Tecla[i],&Recebe_Tecla[i],TAMANHO_ENVIO,TIMEOUT_ENVIO);
#endif  
#ifdef USE_USART  
      HAL_UART_Transmit(&huart1,&Envia_Tecla[i],TAMANHO_ENVIO,TIMEOUT_ENVIO); 
#endif   
#ifdef USE_INT_HOST
      HAL_GPIO_WritePin(GPIOB,GPIO_PIN_0,GPIO_PIN_SET); 
      HAL_Delay(50);
      HAL_GPIO_WritePin(GPIOB,GPIO_PIN_0,GPIO_PIN_RESET);
#endif      
      j |= (i+1);
      //return 1 ;
    } 
    if (MyTKeys[i].p_Data->StateId == TSL_STATEID_TOUCH)
    {  
      j |= (i+1);
    }
  }
  if(j){
    if(j & 0x08){
      HAL_GPIO_WritePin(GPIOC,GPIO_PIN_13,GPIO_PIN_SET);
    }
    if(j & 0x04){
      HAL_GPIO_WritePin(GPIOC,GPIO_PIN_14,GPIO_PIN_SET);
    }
    if(j & 0x02){
      HAL_GPIO_WritePin(GPIOC,GPIO_PIN_15,GPIO_PIN_SET);
    }
    if(j & 0x01){
      HAL_GPIO_WritePin(GPIOF,GPIO_PIN_0,GPIO_PIN_SET);
    }  
#ifdef USE_USART  
      Envia_Tecla[0] = j;
      HAL_UART_Transmit(&huart1,&Envia_Tecla[0],TAMANHO_ENVIO,TIMEOUT_ENVIO); 
#endif      
    return 1;
  } else{
    HAL_GPIO_WritePin(GPIOC,GPIO_PIN_13|GPIO_PIN_14|GPIO_PIN_15,GPIO_PIN_RESET);
    HAL_GPIO_WritePin(GPIOF,GPIO_PIN_0,GPIO_PIN_RESET);
  }

#ifdef USE_SPI
  HAL_SPI_TransmitReceive(&hspi1,&Envia_Tecla_NaoPress,&Recebe_Tecla[i],TAMANHO_ENVIO,TIMEOUT_ENVIO); 
#endif

#ifdef USE_USART  
  HAL_UART_Transmit(&huart1,&Envia_Tecla_NaoPress,TAMANHO_ENVIO,TIMEOUT_ENVIO); 
#endif  
  return 0;
}

char WaterProof_Process(void)//tsl_user_status_t tsl_status)
{
  char i,j;
  j = 0;//contador de quantas teclas foram pressionadas simultaneamente
  for(i = 0; i < NUMERO_TECLAS; i++)
  { 
    if (MyTKeys[i].p_Data->StateId == TSL_STATEID_TOUCH)
    {
      j++;
    }
  }
  if(j >= LIMITE_TECLAS_SIMULTANEAS)
  {
    return 0;
  }
    return 1;
}
/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @param  None
  * @retval None
  */
void _Error_Handler(char * file, int line)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  while(1) 
  {
  }
  /* USER CODE END Error_Handler_Debug */ 
}

#ifdef USE_FULL_ASSERT

/**
   * @brief Reports the name of the source file and the source line number
   * where the assert_param error has occurred.
   * @param file: pointer to the source file name
   * @param line: assert_param error line source number
   * @retval None
   */
void assert_failed(uint8_t* file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
/* User can add his own implementation to report the file name and line number,
ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */

}

#endif

/**
  * @}
  */ 

/**
  * @}
*/ 

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
