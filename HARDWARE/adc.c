#include "adc.h"
#include "delay.h"
#include "graphyt.h"


int Adc_state_flag;                      //ADC状态标志位
__IO uint16_t ADC_ConvertedValue[ADC_SIZE];     //ADC采样值通过DMA储存地

DMA_HandleTypeDef DMA_Init_Handle;              //DMA句柄
ADC_HandleTypeDef ADC_Handle;                   //ADC句柄
ADC_ChannelConfTypeDef ADC_Config;              //ADC初始化句柄





static void Rheostat_ADC_GPIO_Config(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;

    // 使能 GPIO 时钟
    __HAL_RCC_GPIOA_CLK_ENABLE();//__HAL_RCC_GPIOC_CLK_ENABLE
        
    // 配置 IO
    GPIO_InitStructure.Pin = GPIO_PIN_5;    //GPIO_PIN_5
    GPIO_InitStructure.Mode = GPIO_MODE_ANALOG;	   // 
    GPIO_InitStructure.Pull = GPIO_NOPULL ; //不上拉不下拉
    HAL_GPIO_Init(GPIOA, &GPIO_InitStructure);//GPIOC->GPIOA		
}

static void Rheostat_ADC_Mode_Config(void)
{

    // ------------------DMA Init 结构体参数 初始化--------------------------
    // ADC1使用DMA2，数据流0，通道0，这个是手册固定死的
    // 开启DMA时钟
    __HAL_RCC_DMA2_CLK_ENABLE();//__HAL_RCC_DMA2_CLK_ENABLE
    // 数据传输通道
    DMA_Init_Handle.Instance = DMA2_Stream0;//DMA2_Stream0
    // 数据传输方向为外设到存储器	
    DMA_Init_Handle.Init.Direction = DMA_PERIPH_TO_MEMORY;	
    // 外设寄存器只有一个，地址不用递增
    DMA_Init_Handle.Init.PeriphInc = DMA_PINC_DISABLE;
    // 存储器地址增长
    DMA_Init_Handle.Init.MemInc = DMA_MINC_ENABLE; 
    // // 外设数据大小为半字，即两个字节 
    DMA_Init_Handle.Init.PeriphDataAlignment = DMA_PDATAALIGN_HALFWORD; 
    //	存储器数据大小也为半字，跟外设数据大小相同
    DMA_Init_Handle.Init.MemDataAlignment = DMA_PDATAALIGN_HALFWORD;	
    // 循环传输模式
    DMA_Init_Handle.Init.Mode = DMA_CIRCULAR;
    // DMA 传输通道优先级为高，当使用一个DMA通道时，优先级设置不影响
    DMA_Init_Handle.Init.Priority = DMA_PRIORITY_HIGH;
    // 禁止DMA FIFO	，使用直连模式
    DMA_Init_Handle.Init.FIFOMode = DMA_FIFOMODE_DISABLE;  
    // FIFO 大小，FIFO模式禁止时，这个不用配置	
    // DMA_Init_Handle.Init.FIFOThreshold = DMA_FIFO_THRESHOLD_HALFFULL;
    // DMA_Init_Handle.Init.MemBurst = DMA_MBURST_SINGLE;
    // DMA_Init_Handle.Init.PeriphBurst = DMA_PBURST_SINGLE;  
    // 选择 DMA 通道，通道存在于流中
    DMA_Init_Handle.Init.Channel = DMA_CHANNEL_0; //DMA_CHANNEL_0
    //初始化DMA流，流相当于一个大的管道，管道里面有很多通道
    HAL_DMA_Init(&DMA_Init_Handle); 

    
    HAL_DMA_Start(&DMA_Init_Handle,RHEOSTAT_ADC_DR_ADDR,(uint32_t)&ADC_ConvertedValue,ADC_SIZE);
    
    
    

    // 开启ADC时钟
    __HAL_RCC_ADC1_CLK_ENABLE();//__HAL_RCC_ADC1_CLK_ENABLE
    // -------------------ADC Init 结构体 参数 初始化------------------------
    // ADC1
    ADC_Handle.Instance = ADC1;//ADC1
    // 时钟为fpclk 4分频	
    ADC_Handle.Init.ClockPrescaler = ADC_CLOCKPRESCALER_PCLK_DIV4;
    // ADC 分辨率
    ADC_Handle.Init.Resolution = ADC_RESOLUTION_12B;
    // 禁止扫描模式，多通道采集才需要	
    ADC_Handle.Init.ScanConvMode = DISABLE; 
    // 连续转换	
    ADC_Handle.Init.ContinuousConvMode = DISABLE;     //ENABLE
    // 非连续转换	
    ADC_Handle.Init.DiscontinuousConvMode = DISABLE;
    // 非连续转换个数
    ADC_Handle.Init.NbrOfDiscConversion   = 0;
    //禁止外部边沿触发    
    ADC_Handle.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_RISING;
    

    ADC_Handle.Init.ExternalTrigConv      = ADC_EXTERNALTRIGCONV_T1_CC1;


    //数据右对齐	
    ADC_Handle.Init.DataAlign = ADC_DATAALIGN_RIGHT;
    //转换通道 1个
    ADC_Handle.Init.NbrOfConversion = 1;
    //使能连续转换请求
    ADC_Handle.Init.DMAContinuousRequests = ENABLE;
    //转换完成标志
    ADC_Handle.Init.EOCSelection          = DISABLE;    
    // 初始化ADC	                          
    HAL_ADC_Init(&ADC_Handle);
    //---------------------------------------------------------------------------
    ADC_Config.Channel      = ADC_CHANNEL_5;//ADC_CHANNEL_5
    ADC_Config.Rank         = 1;
    // 采样时间间隔	
    ADC_Config.SamplingTime = ADC_SAMPLETIME_3CYCLES;
    ADC_Config.Offset       = 0;
    // 配置 ADC 通道转换顺序为1，第一个转换，采样时间为3个时钟周期
    HAL_ADC_ConfigChannel(&ADC_Handle, &ADC_Config);

    //HAL_ADC_Start(&ADC_Handle);

    //该函数会自动检查ADC是否开启，如果没开启就自动开启，因此就不需要上面的函数了
    HAL_ADC_Start_DMA(&ADC_Handle,(uint32_t*)&ADC_ConvertedValue, ADC_SIZE);
    
    
    Adc_state_flag=1;
}



void Rheostat_Init(void)    //统一初始化供main调用
{
	Rheostat_ADC_GPIO_Config();
	Rheostat_ADC_Mode_Config();
}

void Open_ADC(void){        //打开ADC函数
    HAL_ADC_Start_DMA(&ADC_Handle, (uint32_t*)&ADC_ConvertedValue, ADC_SIZE);
    Adc_state_flag=1;
}

void Close_ADC(void){       //  关闭ADC函数
    HAL_ADC_Stop(&ADC_Handle);
    HAL_ADC_Stop_DMA(&ADC_Handle);
    Adc_state_flag=0;
}





