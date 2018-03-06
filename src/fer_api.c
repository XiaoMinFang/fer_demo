#include "fer_para.h"
#include "fer_api.h"
#include "darknet.h"


#define CFGFILE    "fer.cfg"
#define WEIGHTFILE "fer_13566.weights"


int FER_Process(char* img_path, FER_Result_S* pResult)
{
	network net;
	image im,sized;
	float *X=NULL;

	float *predictions = calloc(CLASSES, sizeof(float));
	int *indexes = calloc(TOP, sizeof(int));

	int i;
	clock_t time_start, time_end;

	net = parse_network_cfg(CFGFILE);                       //������������
	load_weights(&net, WEIGHTFILE);                         //����ѵ���õ�Ȩֵ
	set_batch_network(&net, 1);                                  //�������batch��1

	im = load_image(img_path,0,0,3);                        //����ͼƬ              
	sized = letterbox_image(im, net.w, net.h);            //��ͼƬ����ת��Ϊ������Ҫ�ĸ�ʽ
	X = sized.data;

	time_start = clock();
	 
	network_predict(net, X);                   //����
	for (i = 0; i < CLASSES;i++)
	{
		*(predictions + i) = *(net.output + i);
	}
	top_k(predictions, net.outputs, TOP, indexes);     //���շ���ĵ÷������ҵ�������ߵ�
	time_end = clock();
	printf("predicted cost %f seconds.\n", sec(time_end - time_start));
	for (i = 0; i < TOP; ++i){		
		int index = indexes[i];      //
		pResult->fer_classes[i] = index;
		pResult->fer_scroes[i] = *(predictions+index) * 100;
	}
	if (indexes)
	{
		free(indexes); 
		indexes = NULL;
	}
	if (predictions)
	{
		free(predictions);
		predictions = NULL;
	}
	free_network(net);
	if (sized.data != im.data) free_image(sized);
	free_image(im);
	return 0;
}

int FER_Process_List(char* img_path, FER_Result_S* pResult,char *weight_name)
{
	char weights_name[50];
	network net;
	image im, sized;
	float *X = NULL;

	float *predictions = calloc(CLASSES, sizeof(float));
	int *indexes = calloc(TOP, sizeof(int));

	int i;
	clock_t time_start, time_end;

	net = parse_network_cfg(CFGFILE);                       //������������
	load_weights(&net, weight_name);                         //����ѵ���õ�Ȩֵ
	set_batch_network(&net, 1);                                  //�������batch��1

	im = load_image(img_path, 0, 0, 3);                        //����ͼƬ              
	sized = letterbox_image(im, net.w, net.h);            //��ͼƬ����ת��Ϊ������Ҫ�ĸ�ʽ
	X = sized.data;

	time_start = clock();

	network_predict(net, X);                   //����
	for (i = 0; i < CLASSES; i++)
	{
		*(predictions + i) = *(net.output + i);
	}
	top_k(predictions, net.outputs, TOP, indexes);     //���շ���ĵ÷������ҵ�������ߵ�

	time_end = clock();
	printf("predicted cost %f seconds.\n", sec(time_end - time_start));

	for (i = 0; i < TOP; ++i){
		int index = indexes[i];      //
		pResult->fer_classes[i] = index;
		pResult->fer_scroes[i] = *(predictions + index) * 100;
	}
	if (sized.data != im.data) free_image(sized);
	free_image(im);
	free_network(net);
	if (predictions)
	{
		free(predictions);
		predictions = NULL;
	}
	if (indexes)
	{
		free(indexes);
		indexes = NULL;
	}

	return 0;
}

int get_fer_img_labels(char *list_img_name)
{

	int fer_label = 0;
	if (strstr(list_img_name, "angry"))
	{
		fer_label = 0;
	}
	if (strstr(list_img_name, "disgust"))
	{
		fer_label = 1;
	}
	if (strstr(list_img_name, "fear"))
	{
		fer_label = 2;
	}
	if (strstr(list_img_name, "happy"))
	{
		fer_label = 3;
	}
	if (strstr(list_img_name, "sad"))
	{
		fer_label = 4;
	}
	if (strstr(list_img_name, "surprise"))
	{
		fer_label = 5;
	}
	if (strstr(list_img_name, "neutral"))
	{
		fer_label = 6;
	}
	return fer_label;
}
