#include "stm32f4xx.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_rcc.h"
#include "misc.h"
#include "stm32f4xx_tim.h"

TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
TIM_OCInitTypeDef  TIM_OCInitStructure;

//DEGÝSKENLIKLER ATANDI UNSÝGNED ÝNT OLARAK
uint16_t CCR1_Val = 333;
uint16_t CCR2_Val = 249;
uint16_t CCR3_Val = 166;
uint16_t CCR4_Val = 83;
uint16_t PrescalerValue = 0;

void Tim3_PWM_Init(void);
void Genel_Init(void);

int main()
{
	Genel_Init();
	Tim3_PWM_Init();

	while(1)
	{

	}
}

void Tim3_PWM_Init(void)
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);

	 PrescalerValue = (uint16_t) ((SystemCoreClock /2) / 21000000) - 1;
	 // TIMER TEMEL AYARLAMALAR
	 TIM_TimeBaseStructure.TIM_Period=665;
	 TIM_TimeBaseStructure.TIM_Prescaler= PrescalerValue;
	 TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up;
	 TIM_TimeBaseStructure.TIM_ClockDivision=0;

	 TIM_TimeBaseInit(TIM3,&TIM_TimeBaseStructure);

	 //PWM KANAL 1 AYARLARI

	 TIM_OCInitStructure.TIM_OCMode=TIM_OCMode_PWM1;
	 TIM_OCInitStructure.TIM_OutputState=TIM_OutputState_Enable;
	 TIM_OCInitStructure.TIM_Pulse=CCR1_Val;
	 TIM_OCInitStructure.TIM_OCPolarity=TIM_OCPolarity_High;

	 TIM_OC1Init(TIM3,&TIM_OCInitStructure);

	 TIM_OC1PreloadConfig(TIM3,TIM_OCPreload_Enable);

	 //PWM KANAL2 AYARLARI

	 TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	   TIM_OCInitStructure.TIM_Pulse = CCR2_Val;

	   TIM_OC2Init(TIM3, &TIM_OCInitStructure);

	   TIM_OC2PreloadConfig(TIM3, TIM_OCPreload_Enable);
	 //PWM KANAL3 AYARLARI

	 TIM_OCInitStructure.TIM_OutputState=TIM_OutputState_Enable;
	 TIM_OCInitStructure.TIM_Pulse=CCR3_Val;

	 TIM_OC3Init(TIM3,&TIM_OCInitStructure);
	 TIM_OC3PreloadConfig(TIM3,TIM_OCPreload_Enable);

	 //PWM KANAL 4 AYARLARI

	 TIM_OCInitStructure.TIM_OutputState=TIM_OutputState_Enable;
	 TIM_OCInitStructure.TIM_Pulse=CCR4_Val;

	 TIM_OC4Init(TIM3,&TIM_OCInitStructure);
	 TIM_OC4PreloadConfig(TIM3,TIM_OCPreload_Enable);

	 TIM_ARRPreloadConfig(TIM3,ENABLE);

	 TIM_Cmd(TIM3,ENABLE);

}

void Genel_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC,ENABLE);

	  /* GPIOC Configuration: TIM3 CH1 (PC6), TIM3 CH2 (PC7), TIM3 CH3 (PC8) and TIM3 CH4 (PC9) */
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_OType=GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_PuPd=GPIO_PuPd_UP;
	GPIO_Init(GPIOC,&GPIO_InitStructure);

	//PORT YONLENDIRME ÝÞLEMLERNÝ YAPALIM DATASHEETTEN BAKINIZ TIM3 pins to AF2

	GPIO_PinAFConfig(GPIOC,GPIO_PinSource6,GPIO_AF_TIM3);
	GPIO_PinAFConfig(GPIOC,GPIO_PinSource7,GPIO_AF_TIM3);
	GPIO_PinAFConfig(GPIOC,GPIO_PinSource8,GPIO_AF_TIM3);
	GPIO_PinAFConfig(GPIOC,GPIO_PinSource9,GPIO_AF_TIM3);

}

uint16_t EVAL_AUDIO_GetSampleCallBack(void)
{
    return 0; // ses çipini kullanýyorsanýz tek sample veriyi burada return ile döndürün.
}
void EVAL_AUDIO_TransferComplete_CallBack(uint32_t pBuffer, uint32_t Size)
{
    return; // ses çipini kullanýyorsanýz  burada çipe veri aktarýmý DMA sona ermiþ
}

