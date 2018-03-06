#include "darknet.h"
#include "fer_api.h"	
#include "fer_para.h"

#include <stdio.h>
#include <cv.h>
#include <cxcore.h>
#include <highgui.h>

#define IS_SAVE_RES     1

int main()
{
	int test_choice = 3;
	char img_path[256] = "E:\\fer\\fer2013\\test\\0\\anger_00007.jpg";
	char weights_list[256] = "E:\\fer\\demo\\drawing\\weights_list.txt";
	char *weights_name=NULL;
	char *list_img_name = NULL;
	char img_list[256] = "E:\\fer\\fer2013\\test.txt";
	FILE *fp;
	FILE *fp_save;
	FILE *fp_weight;
	FER_Result_S stRes;
	char img_class[10];
	int fer_labels = 0;
	float accury;
	int total_imgs = 0;
	int rights_imgs = 0;
	int num_iter = 0;
		//printf("选择测试类型\n   0：单张图片测试；\n   1：批量测试\n");
		//scanf("%d", &test_choice);
	if (test_choice==0)
	{
		printf("请输入测试图片路径：\n");
		//scanf("%s", img_path);

		FER_Process(img_path, &stRes);
		switch (stRes.fer_classes[0])
		{
		case angry: sprintf(img_class, "angry"); break;
		case disgust:sprintf(img_class, "disgust"); break;
		case fear:sprintf(img_class, "fear"); break;
		case happpy:sprintf(img_class, "happy"); break;
		case sad:sprintf(img_class, "sad"); break;
		case surprise:sprintf(img_class, "surprise"); break;
		case neutral:sprintf(img_class, "neutral"); break;
		}
		printf("该图片的表情为：%s\n", img_class);
		printf("识别得分为：%.2f", stRes.fer_scroes[0]);
	}
	else if (test_choice == 1)
	{
		printf("请输入测试图片列表：\n");
		//scanf("%s", &img_list);
		fp = fopen(img_list, "r");
#if IS_SAVE_RES
		fp_save = fopen("E:\\fer\\demo\\drawing\\test_list_res.txt", "w");
#endif
		while (1)
		{
			list_img_name = fgetl(fp);
			//fgets(fp, "%s", img_path);
			if (!list_img_name)
			{
				break;
			}
			total_imgs++;
			fer_labels = get_fer_img_labels(list_img_name);
			FER_Process(list_img_name, &stRes);

			switch (stRes.fer_classes[0])
			{
			case angry: sprintf(img_class, "angry"); break;
			case disgust:sprintf(img_class, "disgust"); break;
			case fear:sprintf(img_class, "fear"); break;
			case happpy:sprintf(img_class, "happy"); break;
			case sad:sprintf(img_class, "sad"); break;
			case surprise:sprintf(img_class, "surprise"); break;
			case neutral:sprintf(img_class, "neutral"); break;
			}
#if IS_SAVE_RES
			fprintf(fp_save, "%d %d\n", stRes.fer_classes[0], fer_labels);
#endif

			if (stRes.fer_classes[0] == fer_labels)
			{
				rights_imgs++;
			}
		}
		accury = ((float)rights_imgs) / ((float)total_imgs);
		printf("该list的识别精度为 %f ! （其中被正确识别的表情数量为 %d 张）\n ", accury, rights_imgs);
		fclose(fp);
#if IS_SAVE_RES
		fclose(fp_save);
#endif
	}
	else                       //test weights list
	{
		fp_weight = fopen(weights_list, "r");
		fp_save = fopen("E:\\fer\\demo\\drawing\\accury_log.txt", "w");
		while (1)
		{
			weights_name = fgetl(fp_weight);
			if (!weights_name)
			{
				break;
			}
			num_iter++;
			fp = fopen(img_list, "r");
			while (1)
			{
				list_img_name = fgetl(fp);
				if (!list_img_name)
				{
					break;
				}
				total_imgs++;

				fer_labels = get_fer_img_labels(list_img_name);
				FER_Process_List(list_img_name, &stRes, weights_name);

				switch (stRes.fer_classes[0])
				{
				case angry: sprintf(img_class, "angry"); break;
				case disgust:sprintf(img_class, "disgust"); break;
				case fear:sprintf(img_class, "fear"); break;
				case happpy:sprintf(img_class, "happy"); break;
				case sad:sprintf(img_class, "sad"); break;
				case surprise:sprintf(img_class, "surprise"); break;
				case neutral:sprintf(img_class, "neutral"); break;
				}

				if (stRes.fer_classes[0] == fer_labels)
				{
					rights_imgs++;
				}
			}
			accury = ((float)rights_imgs) / ((float)total_imgs);
			fprintf(fp_save, "%d %f\n", num_iter, accury);			
			fclose(fp);
		}
		fclose(fp_weight);
		fclose(fp_save);
	}
	if (weights_name)
	{
		free(weights_name); 
		weights_name = NULL;
	}
	if (list_img_name)
	{
		free(list_img_name);
		list_img_name = NULL;
	}
	return -1;
}



