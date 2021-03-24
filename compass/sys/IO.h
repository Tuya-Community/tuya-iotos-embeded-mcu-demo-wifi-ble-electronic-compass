#ifndef __IO_H
#define __IO_H 		
#include "MY_ST_config.h"
#include "math.h"
#include "stdbool.h"


//IIC_SDA	  PB11
#define IIC_SDA_OUT {RCC->IOPENR|=1<<1;GPIOB->MODER&=~(3<<22);GPIOB->MODER|=1<<22;GPIOB->PUPDR|=1<<22;} 
#define IIC_SDA_IN  {RCC->IOPENR|=1<<1;GPIOB->MODER&=~(3<<22);GPIOB->MODER|=0<<22;} 
#define IIC_SDA_SET GPIOB->ODR|=1<<11
#define IIC_SDA_RESET  GPIOB->ODR&=~(1<<11)
#define IIC_SDA_State ((GPIOB->IDR & 1<<11) == 1<<11)

//IIC_SCL	  PB12
#define IIC_SCL_OUT {RCC->IOPENR|=1<<1;GPIOB->MODER&=~(3<<24);GPIOB->MODER|=1<<24;GPIOB->PUPDR|=1<<24;}  
#define IIC_SCL_IN  {RCC->IOPENR|=1<<1;GPIOB->MODER&=~(3<<24);GPIOB->MODER|=0<<24;} 
#define IIC_SCL_SET GPIOB->ODR|=1<<12
#define IIC_SCL_RESET  GPIOB->ODR&=~(1<<12)
#define IIC_SCL_State ((GPIOB->IDR & 1<<12) == 1<<12)

#if 1
void IIC_Init(void);
void IIC_Start(void);//����IIC��ʼ�ź�
void IIC_Stop(void);//����IICֹͣ�ź�
void IIC_Ack(void);//����ACKӦ��
void IIC_NAck(void);//������ACKӦ��	
uint8_t IIC_Wait_Ack(void);//�ȴ�Ӧ���źŵ���:1,����Ӧ��ʧ��;0,����Ӧ��ɹ�
void IIC_Send_Byte(uint8_t txd);//IIC����һ���ֽ�; �ȷ��͸�λ
uint8_t IIC_Read_Byte(unsigned char ack);//��һ���ֽڣ��ɼ��Ƿ�Ӧ��λ,1��ack��0����ack �Ӹ�λ��ʼ��
uint8_t IIC_Write_Byte(uint8_t DrvAddr,uint16_t WriteAddr,uint8_t data);//ֱ��дһ���ֽ�
uint8_t IIC_ReadMulByte(uint8_t DrvAddr,uint16_t ReadAddr,uint8_t *pBuffer,uint16_t NumToRead);//���ֽ�
uint8_t IIC_WriteMulByte(uint8_t DrvAddr,uint16_t WriteAddr,uint8_t *pBuffer,uint16_t NumToWrite);//��һ��д����ֽ�
#endif

//LED_CTRL4	 	PA5
#define LED_4_OUT {RCC->IOPENR|=1<<0;GPIOA->MODER&=~(3<<10);GPIOA->MODER|=1<<10;} 
#define LED_4_SET GPIOA->ODR|=1<<5
#define LED_4_RESET  GPIOA->ODR&=~(1<<5)
#define LED_4_TOG GPIOA->ODR^=1<<5

typedef struct 
{
	int16_t x;
	int16_t y;
	int16_t z;
}i16_xyz;

typedef struct 
{
	float x;
	float y;
	float z;
}float_xyz;
#if USING_QMC5883L/***************************������QMC5883L�شŴ�����**************************/
/***************************������QMC5883L�شŴ�����**************************/
#define QMC5883L_ADDRESS  		0x1A

#define QMC5883L_DATA_READ_X_LSB	0x00
#define QMC5883L_DATA_READ_X_MSB	0x01
#define QMC5883L_DATA_READ_Y_LSB	0x02
#define QMC5883L_DATA_READ_Y_MSB	0x03
#define QMC5883L_DATA_READ_Z_LSB	0x04
#define QMC5883L_DATA_READ_Z_MSB	0x05
#define QMC5883L_STATUS		        0x06 // DOR | OVL | DRDY
#define QMC5883L_TEMP_READ_LSB		0x07
#define QMC5883L_TEMP_READ_MSB		0x08 
#define QMC5883L_CONFIG_1					0x09 // OSR | RNG | ODR | MODE
#define QMC5883L_CONFIG_2					0x0A // SOFT_RST | ROL_PNT | INT_ENB
#define QMC5883L_CONFIG_3					0x0B // SET/RESET Period FBR [7:0]
#define QMC5883L_ID								0x0D

#ifndef M_PI 
#define M_PI 3.14159265358979323846264338327950288f 
#endif 

#define QMC5883L_SCALE_FACTOR 		0.732421875f
#define QMC5883L_CONVERT_GAUSS_2G 	12000.0f
#define QMC5883L_CONVERT_GAUSS_8G 	3000.0f
#define QMC5883L_CONVERT_MICROTESLA 	100
#define QMC5883L_DECLINATION_ANGLE	93.67/1000  // radian, Tekirdag/Turkey

typedef enum STATUS_VARIABLES
{
	NORMAL,
	NO_NEW_DATA,
	NEW_DATA_IS_READY,
	DATA_OVERFLOW,
	DATA_SKIPPED_FOR_READING
}_qmc5883l_status;

typedef enum MODE_VARIABLES
{
	MODE_CONTROL_STANDBY=0x00,
	MODE_CONTROL_CONTINUOUS=0x01
}_qmc5883l_MODE;

typedef enum ODR_VARIABLES
{
	OUTPUT_DATA_RATE_10HZ=0x00,
	OUTPUT_DATA_RATE_50HZ=0x04,
	OUTPUT_DATA_RATE_100HZ=0x08,
	OUTPUT_DATA_RATE_200HZ=0x0C
}_qmc5883l_ODR;

typedef enum RNG_VARIABLES
{
	FULL_SCALE_2G=0x00,
	FULL_SCALE_8G=0x10
}_qmc5883l_RNG;


typedef enum OSR_VARIABLES
{
	OVER_SAMPLE_RATIO_512=0x00,
	OVER_SAMPLE_RATIO_256=0x40,
	OVER_SAMPLE_RATIO_128=0x80,
	OVER_SAMPLE_RATIO_64=0xC0
}_qmc5883l_OSR;


typedef enum INTTERRUPT_VARIABLES
{
	INTERRUPT_DISABLE,
	INTERRUPT_ENABLE
}_qmc5883l_INT;

/***************************������QMC5883L�شŴ�����**************************/
#endif

extern uint8_t F_TASK_QMC5883L;
extern float_xyz Mag_angle;
void TASK_QMC5883L(void);

struct ctrl_state
{
	bool flagmax;//�ﵽ�趨ֵ���ޱ�־λ
	bool flagmin;//�ﵽ�趨ֵ���ޱ�־λ
	uint8_t mode;//����ģʽ
	uint16_t range;//�趨��ֵ
	int16_t ctrl;//��������ֵ	
	float now;//��ǰ���ֵ
	float set;//�趨���ֵ	
};
void IO_Init(void);
#endif

