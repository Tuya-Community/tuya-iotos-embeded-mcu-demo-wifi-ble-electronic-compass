#include "IO.h"
#include "delay.h"
#include "TIM.h"
#include "math.h"
#include "stdlib.h"
#if 1//IIC
void IIC_Init(void)
{
	IIC_SCL_OUT;
	IIC_SDA_OUT;
}
void IIC_Start(void)//����IIC��ʼ�ź�
{
	IIC_SDA_OUT;     //sda�����
	IIC_SDA_SET;//IIC_SDA=1;	  	  
	IIC_SCL_SET;//IIC_SCL=1;
	delay_us(5);
	IIC_SDA_RESET;//IIC_SDA=0;//START:when CLK is high,DATA change form high to low 
	delay_us(5);
	IIC_SCL_RESET;//IIC_SCL=0;//ǯסI2C���ߣ�׼�����ͻ�������� 
}
void IIC_Stop(void)//����IICֹͣ�ź�
{
	IIC_SDA_OUT;//sda�����
	IIC_SCL_RESET;//IIC_SCL=0;
	IIC_SDA_RESET;//IIC_SDA=0;//STOP:when CLK is high DATA change form low to high
	delay_us(5);
	IIC_SCL_SET;//IIC_SCL=1; 
	delay_us(5);
	IIC_SDA_SET;//IIC_SDA=1;//����I2C���߽����ź�				   	
}
void IIC_Ack(void)//����ACKӦ��
{
	IIC_SCL_RESET;//IIC_SCL=0;
	IIC_SDA_OUT;//SDA_OUT();
	IIC_SDA_RESET;//IIC_SDA=0;
	delay_us(5);
	IIC_SCL_SET;//IIC_SCL=1;
	delay_us(5);
	IIC_SCL_RESET;//IIC_SCL=0;
}   
void IIC_NAck(void)//������ACKӦ��	
{
	IIC_SCL_RESET;//IIC_SCL=0;
	IIC_SDA_OUT;//SDA_OUT();
	IIC_SDA_SET;//IIC_SDA=1;
	delay_us(5);
	IIC_SCL_SET;//IIC_SCL=1;
	delay_us(5);
	IIC_SCL_RESET;//IIC_SCL=0;
}	
uint8_t IIC_Wait_Ack(void)//�ȴ�Ӧ���źŵ���:1,����Ӧ��ʧ��;0,����Ӧ��ɹ�
{
	uint8_t ucErrTime=0;
	IIC_SDA_IN;      //SDA����Ϊ����     
	IIC_SCL_SET;//IIC_SCL=1;
	delay_us(5);	 
	while(IIC_SDA_State)//���SDA�Ƿ���Ϊ�ߵ�ƽ
	{
		ucErrTime++;
		if(ucErrTime>250)
		{
			IIC_Stop();
			return 1;
		}
	}
	IIC_SCL_RESET;//IIC_SCL=0;
	return 0;  
} 
void IIC_Send_Byte(uint8_t txd)//IIC����һ���ֽ�; �ȷ��͸�λ
{                        
	uint8_t t;   
	IIC_SDA_OUT; 	    
	IIC_SCL_RESET;//IIC_SCL=0;//����ʱ�ӿ�ʼ���ݴ���
	for(t=0;t<8;t++)
	{              
			//IIC_SDA=(txd&0x80)>>7;
		if((txd&0x80)>>7)
			IIC_SDA_SET;//IIC_SDA=1;
		else
			IIC_SDA_RESET;//IIC_SDA=0;
		
		txd<<=1; 	  
		delay_us(5);   //��TEA5767��������ʱ���Ǳ����
		IIC_SCL_SET;//IIC_SCL=1;
		delay_us(5); 
		IIC_SCL_RESET;//IIC_SCL=0;	
		delay_us(5);
	}	 
} 
uint8_t IIC_Read_Byte(unsigned char ack)//��һ���ֽڣ��ɼ��Ƿ�Ӧ��λ,1��ack��0����ack �Ӹ�λ��ʼ��
{
	unsigned char i,receive=0;
	IIC_SDA_IN;//SDA����Ϊ����
	for(i=0;i<8;i++ )
	{
		IIC_SCL_RESET;// IIC_SCL=0; 
		delay_us(5);
		IIC_SCL_SET;//IIC_SCL=1;
		receive<<=1;
		if(IIC_SDA_State)
			receive++;   
		delay_us(5); 
	}					 
		if (ack)
			IIC_Ack(); //����ACK
		else
			IIC_NAck();//����nACK   
		return receive;
}

uint8_t IIC_Write_Byte(uint8_t DrvAddr,uint16_t WriteAddr,uint8_t data)//ֱ��дһ���ֽ�
{
	uint8_t ret=0;
	IIC_Start();

	IIC_Send_Byte(DrvAddr);	    //����д����
	ret |= IIC_Wait_Ack();
	IIC_Send_Byte(WriteAddr);//���͵�ַ	  
	ret |= IIC_Wait_Ack();		
	IIC_Send_Byte(data);     //�����ֽ�							   
	ret |= IIC_Wait_Ack(); 

	IIC_Stop();
	delay_us(10);
	return ret;
}
uint8_t IIC_ReadMulByte(uint8_t DrvAddr,uint16_t ReadAddr,uint8_t *pBuffer,uint16_t NumToRead)//���ֽ�
{  	    																 
	uint8_t ret=0;
	
	IIC_Start();  
	IIC_Send_Byte(DrvAddr);	   //����д����
	ret |= IIC_Wait_Ack();
	IIC_Send_Byte(ReadAddr);//���͵�ַ	    
	ret |= IIC_Wait_Ack();	    
	
	IIC_Start();
	IIC_Send_Byte(DrvAddr+1);           //�������ģʽ			   
	ret |= IIC_Wait_Ack();
	while(NumToRead)
	{
		if(NumToRead==1)
		{
			*pBuffer=IIC_Read_Byte(0);	
		}
		else
		{
			*pBuffer=IIC_Read_Byte(1);
		}
		pBuffer++;
		NumToRead--;
	}
	IIC_Stop();//����һ��ֹͣ����	
	return ret;	
}
uint8_t IIC_WriteMulByte(uint8_t DrvAddr,uint16_t WriteAddr,uint8_t *pBuffer,uint16_t NumToWrite)//��һ��д����ֽ�
{
	uint8_t ret=0;
	IIC_Start();

	IIC_Send_Byte(DrvAddr);	    //����д����
	ret |= IIC_Wait_Ack();
	IIC_Send_Byte(WriteAddr);//���͵�ַ	  
	ret |= IIC_Wait_Ack();		

	while(NumToWrite--)
	{ 										  		   
		IIC_Send_Byte(*pBuffer);     //�����ֽ�							   
		ret |= IIC_Wait_Ack(); 
		pBuffer++;
	}
	IIC_Stop();
	delay_us(10);
	return ret;
}
#endif

/******************************************************�ش�******************************************************/
uint8_t F_TASK_QMC5883L=0;
float_xyz Mag_angle;
int16_t Mag_temperature;
#if USING_QMC5883L
void QMC5883L_Init(void)
{
	uint8_t Config=0;
	
	IIC_Write_Byte(QMC5883L_ADDRESS,0x0B,	0x01);
	IIC_Write_Byte(QMC5883L_ADDRESS,0x20,	0x40);
	IIC_Write_Byte(QMC5883L_ADDRESS,0x21,	0x01);
	Config =	OVER_SAMPLE_RATIO_512\
						|FULL_SCALE_2G\
						|OUTPUT_DATA_RATE_10HZ\
						|MODE_CONTROL_CONTINUOUS;
	/****OSR=512,RNG=+/-2G,ODR=200Hz,MODE= continuous*******/
	IIC_Write_Byte(QMC5883L_ADDRESS,0x09,	Config);
	
	delay_ms(2);
}
void QMC5883L_GetAngle(float_xyz* data)//оƬ��һ�������Ͻǣ����·���Ϊָʾ��0Ϊ�ϣ�90Ϊ����180Ϊ����270Ϊ��
{
	uint8_t Mag[6],temp;
	i16_xyz Mag_data;
	IIC_ReadMulByte(QMC5883L_ADDRESS,0x06,&temp,1);

	IIC_ReadMulByte(QMC5883L_ADDRESS,0x00,Mag,6);
	Mag_data.x= (int16_t)(Mag[1] << 8 | Mag[0]);// First byte is LSB, second byte is MSB
	Mag_data.y= (int16_t)(Mag[3] << 8 | Mag[2]);
	Mag_data.z= (int16_t)(Mag[5] << 8 | Mag[4]);
	data->x=atan2((double)Mag_data.y,(double)Mag_data.x)*573+1800;
	
	mcu_dp_value_update(DPID_DIRECTION,(uint32_t)Mag_angle.x);

	
}
void TASK_QMC5883L(void)
{
	QMC5883L_GetAngle(&Mag_angle);
}
#endif
/******************************************************�ش�******************************************************/
void Modules_Init(void)
{
	IIC_Init();
	QMC5883L_Init();
}
void SwitchIO_Init(void)
{
	LED_4_OUT;	
}
void IO_Init(void)
{
	Modules_Init();
	SwitchIO_Init();
}
