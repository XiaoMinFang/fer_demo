
#ifndef __FER_API_H__
#define __FER_API_H__
#include "fer_para.h"

extern int FER_Process(char *img_path, FER_Result_S* pstGVDResult);
extern int FER_Process_List(char* img_path, FER_Result_S* pResult, char *weight_name);
extern int get_fer_img_labels(char *list_img_name);
#endif  // << end of file