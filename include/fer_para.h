#ifndef __FER_PARA_H__
#define __FER_PARA_H__

#define TOP  1                         //Ԥ���top��ķ���    �ڲ���ʱ������ߵľ���(���˶���1)    
#define CLASSES 7
typedef enum FER_Classes_E
{	
	angry = 0,            
	disgust = 1,         
	fear = 2,             
	happpy = 3,	      
	sad = 4,            
	surprise =5,
	neutral=6,
}FER_ClASS_E;

// result
typedef struct FER_Result_S
{
	FER_ClASS_E    fer_classes[TOP];   //���
	float        fer_scroes[TOP];       //�÷�

}FER_Result_S;

#endif  