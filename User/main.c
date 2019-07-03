/**
  ******************************************************************************
  * @file    main.c
  * @author  fire
  * @version V1.0
  * @date    2013-xx-xx
  * @brief   ����ͷ����ov7725��������
  ******************************************************************************
  * @attention
  *
  * ʵ��ƽ̨:Ұ�� F103-ָ���� STM32 ������ 
  * ��̳    :http://www.firebbs.cn
  * �Ա�    :https://fire-stm32.taobao.com
  *
  ******************************************************************************
  */
  
#include "stm32f10x.h"
#include "./ov7725/bsp_ov7725.h"
#include "./lcd/bsp_ili9341_lcd.h"
#include "./led/bsp_led.h"   
#include "./usart/bsp_usart.h"
#include "./key/bsp_key.h"  
#include "./systick/bsp_SysTick.h"
#include "hw_config.h"
#include "usb_lib.h"
#include "usb_desc.h"
#include "usb_pwr.h"
#include <string.h>

extern __IO uint8_t Receive_Buffer[64];
extern __IO  uint32_t Receive_length ;
extern __IO  uint32_t length ;
uint8_t Send_Buffer[64];
uint32_t packet_sent=1;
uint32_t packet_receive=1;


uint32_t Camera_height_length = 480;
uint16_t Camera_pack_length = 60;
uint8_t Camera_Buffer[480]={0x00};
uint32_t Camera_array_position = 0;
uint32_t Camera_array_position_new = 0;
uint32_t Camera_send_flag = 0;


extern uint8_t Ov7725_vsync;

unsigned int Task_Delay[NumOfTask]; 


extern OV7725_MODE_PARAM cam_mode;


/**
  * @brief  ������
  * @param  ��  
  * @retval ��
  */
int main(void) 	
{		
	
	float frame_count = 0;
	uint8_t retry = 0;

	/* Һ����ʼ�� */
	//ILI9341_Init();
	//ILI9341_GramScan ( 3 );
	
	//LCD_SetFont(&Font8x16);
	//LCD_SetColors(RED,BLACK);

  //ILI9341_Clear(0,0,LCD_X_LENGTH,LCD_Y_LENGTH);	/* ��������ʾȫ�� */
	
	/********��ʾ�ַ���ʾ��*******/
  //ILI9341_DispStringLine_EN(LINE(0),"BH OV7725 Test Demo");

	USART_Config();
	//LED_GPIO_Config();
	//Key_GPIO_Config();
	//SysTick_Init();
	//printf("\r\n ** OV7725����ͷʵʱҺ����ʾ����** \r\n"); 
	
	Set_System();
  Set_USBClock();
  USB_Interrupts_Config();
  USB_Init();
	
	
	
	
	
	/* ov7725 gpio ��ʼ�� */
	OV7725_GPIO_Config();
	
	//LED_BLUE;
	/* ov7725 �Ĵ���Ĭ�����ó�ʼ�� */
	OV7725_Init();



	/*��������ͷ����������ģʽ*/
	OV7725_Special_Effect(cam_mode.effect);
	/*����ģʽ*/
	OV7725_Light_Mode(cam_mode.light_mode);
	/*���Ͷ�*/
	OV7725_Color_Saturation(cam_mode.saturation);
	/*���ն�*/
	OV7725_Brightness(cam_mode.brightness);
	/*�Աȶ�*/
	OV7725_Contrast(cam_mode.contrast);
	/*����Ч��*/
	OV7725_Special_Effect(cam_mode.effect);
	
	/*����ͼ�������ģʽ��С*/
	OV7725_Window_Set(cam_mode.cam_sx,
														cam_mode.cam_sy,
														cam_mode.cam_width,
														cam_mode.cam_height,
														cam_mode.QVGA_VGA);

	/* ����Һ��ɨ��ģʽ */
	//ILI9341_GramScan( cam_mode.lcd_scan );
	
	
	
	//ILI9341_DispStringLine_EN(LINE(2),"OV7725 initialize success!");
	//printf("\r\nOV7725����ͷ��ʼ�����\r\n");
	
	Ov7725_vsync = 0;
	
	while(1)
	{
		/*���յ���ͼ�������ʾ*/

		if( Ov7725_vsync == 2 )
		{
			FIFO_PREPARE;  			/*FIFO׼��*/					
			ImagDisp(cam_mode.lcd_sx,
								cam_mode.lcd_sy,
								cam_mode.cam_width,
								cam_mode.cam_height);			/*�ɼ�����ʾ*/
		

			Ov7725_vsync = 0;			
			//LED1_TOGGLE;
		}
				
	}
}




/*********************************************END OF FILE**********************/

