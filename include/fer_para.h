#ifndef __FER_PARA_H__
#define __FER_PARA_H__

#define TOP  1                         //预测出top类的分数    在测试时计算最高的精度(除了顶部1)    
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
	FER_ClASS_E    fer_classes[TOP];   //类别
	float        fer_scroes[TOP];       //得分

}FER_Result_S;

#endif  