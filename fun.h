#pragma once
#include <stdio.h>
#include<string.h>
#define  MAX_STR_LEN  255   

typedef struct configinfo {
	char  filesavepath[MAX_STR_LEN];     	//���ڴ�����ݼ�¼�ļ��Ĵ洢Ŀ¼
	char  filename[MAX_STR_LEN];              //���ڴ洢���ݼ�¼�ļ����ļ�����Ϣ
	int  number;		//���ڴ�����ɵļ�¼����
	int  maxvalue1;   		//���ڴ��ʵ��2�����ɵ����ݼ�¼��Ԫ���е�1��2��Ԫ��ȡֵ������
	int  minvalue1; 		//���ڴ��ʵ��2�����ɵ����ݼ�¼��Ԫ���е�1��2��Ԫ��ȡֵ������
	int  maxvalue2;   		//���ڴ��ʵ��2�����ɵ����ݼ�¼��Ԫ���е�3��Ԫ��ȡֵ������
	int  minvalue2; 		//���ڴ��ʵ��2�����ɵ����ݼ�¼��Ԫ���е�3��Ԫ��ȡֵ������
	int  recordcount1;	//���ڴ�����ݼ�¼�ļ���Ҫ������ɼ�¼����ʱ����ֵ������
	int  recordcount2;	//���ڴ�����ݼ�¼�ļ���Ҫ������ɼ�¼����ʱ����ֵ������
} CONF;

typedef  struct  DataItem {
	int  item1;     //���ݼ�¼��Ԫ���һ��Ԫ��
	int  item2;     //���ݼ�¼��Ԫ��ڶ���Ԫ��
	int  item3;     //���ݼ�¼��Ԫ�������Ԫ��
} DATAITEM;


void Confirm_filesavepath_and_filename(CONF* conf_struct);
int filesavelocation_is_legal(char* filesavelocation, int length);
void split_path_and_filename(char* filesavelocation, CONF* conf_struct, int length);
int is_number(char* str, int length);
void Confirm_number(CONF *conf_struct);
int **Generate_data_file_using_2D_array(CONF* conf_struct);
DATAITEM* Generate_data_file_using_struct_array(CONF* conf_struct);

