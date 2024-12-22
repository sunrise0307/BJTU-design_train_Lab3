#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <stdlib.h>
#include"fun.h"

void Confirm_filesavepath_and_filename(CONF* conf_struct) {
	char filesavelocation[MAX_STR_LEN];
	int filesavelocation_strlen = 0;
	printf("请输入用于存放数据记录文件的存储路径:\n");
	scanf("%s", filesavelocation);
	getchar();
	// 去除换行符（如果存在）
	if (filesavelocation[strcspn(filesavelocation, "\n")] == '\n') {
		filesavelocation[strcspn(filesavelocation, "\n")] = '\0';
	}
	while(!filesavelocation_is_legal(filesavelocation, (int)strlen(filesavelocation))) {
			printf("输入的路径不合法，请重新输入:\n");
			scanf("%s", filesavelocation);
			getchar();
			if (filesavelocation[strcspn(filesavelocation, "\n")] == '\n') {
				filesavelocation[strcspn(filesavelocation, "\n")] = '\0';
			}
	}
	printf("如果要使用默认路径输入Y，否则输入N：");
	char c;
	c = getchar();
	while (c != 'Y' && c != 'N') {
		printf("输入错误，请重新输入Y/N：");
		c = getchar();
	}
	if (c == 'N') {
		split_path_and_filename(filesavelocation, conf_struct, (int)strlen(filesavelocation));
		printf("文件保存路径为：%s\n", conf_struct->filesavepath);
		printf("文件名为：%s\n", conf_struct->filename);
	}

}

int filesavelocation_is_legal(char* filesavelocation, int length) {
	int is_legal = 1;
	char* const_str = ".txt";
	int i = 0;
	for (i = length-1; i >= length -strlen(const_str); i--) {//	文件名参数必须包含扩展名“.txt”
		if (filesavelocation[i] != const_str[i - length + strlen(const_str)]) {
			is_legal = 0;
			break;
		}

	}
	for (i = 0; i < length; i++) {//文件名和文件路径中不能出现非法字符，包括：':'、'*'、'?'、'\"'、'<'、'>'、'|' ；
		if (filesavelocation[i] == '|'||filesavelocation[i] == ':'
			|| filesavelocation[i] == '*' || filesavelocation[i] == '?' || filesavelocation[i] == '<' || filesavelocation[i] == '>') {//文件路径中不能出现非法字符，包括：'\\'、'/'、':'；
			is_legal = 0;
			break;
		}
		if (i < length - 1) {
			if (filesavelocation[i] == '/' && filesavelocation[i + 1] == '|') {
				is_legal = 0;
				break;
			}
		}
		
	}
	return is_legal;
}

	void split_path_and_filename(char* filesavelocation, CONF * conf_struct, int length){
		int i = 0;
		int find_slash = 0;
		for (i = length-1; i >= 0; i--) {
			if (filesavelocation[i] == '\\') {
				find_slash = 1;
				break;
			}
		}
		if (find_slash == 1) {
			int j = 0;
			for (j = 0; j < i; j++) {
				conf_struct->filesavepath[j] = filesavelocation[j];
			}
			conf_struct->filesavepath[i] = '\0';
			for (j = i + 1; j < length; j++) {
				conf_struct->filename[j - i - 1] = filesavelocation[j];
			}
			conf_struct->filename[length - i - 1] = '\0';
		}
		else {
			conf_struct->filesavepath[0] = '.';
			conf_struct->filesavepath[1] = '\0';
			for (i = 0; i < length; i++) {
				conf_struct->filename[i] = filesavelocation[i];
			}
			conf_struct->filename[length] = '\0';
		}
	}
	

int is_number(char* str, int length) {
	int is_number = 1;
	int i = 0;
	for (i = 0; i < length; i++) {
		if (str[i] < '0' || str[i] > '9') {
			is_number = 0;
			break;
		}
	}
	return is_number;
}

int medium_rand(int min, int max) {
	
	return min + rand() % (max - min + 1);
}

void Confirm_number(CONF* conf_struct) {
	int number = 0;
	char random_flag = 'N';
	printf("请输入记录条数：\n");
	while(scanf("%d", &number) != 1) {
		printf("输入错误，请重新输入记录条数：\n");
	}
	getchar();
	printf("随机生成记录条数请按Y键，否则按N键：\n");
	random_flag = getchar();
	while(random_flag!= 'Y' && random_flag!= 'N') {
		random_flag = getchar();
	}
	if (random_flag == 'Y') {
		srand((unsigned int)time(NULL));
		conf_struct->number = medium_rand(1, 100);
	}else if (random_flag == 'N') {
		conf_struct->number = number;
	}
}


int **Generate_data_file_using_2D_array(CONF* conf_struct) {
	int i = 0;
	int **data_array = (int **)malloc(conf_struct->number * sizeof(int*));
	for (i = 0; i < conf_struct->number; i++) {
		data_array[i] = (int*)malloc(3 * sizeof(int));
	}
	srand((unsigned)time(NULL));
	// 随机生成数据
	for (i = 0; i < conf_struct->number; i++) {
		//data_array[i][0] = conf_struct->minvalue1 + rand() % (conf_struct->maxvalue1 - conf_struct->minvalue1 + 1);
		//data_array[i][1] = conf_struct->minvalue1 + rand() % (conf_struct->maxvalue1 - conf_struct->minvalue1 + 1);
		//data_array[i][2] = conf_struct->minvalue2 + rand() % (conf_struct->maxvalue2 - conf_struct->minvalue2 + 1);
		data_array[i][0] = medium_rand(conf_struct->minvalue1, conf_struct->maxvalue1);
		data_array[i][1] = medium_rand(conf_struct->minvalue1, conf_struct->maxvalue1);
		data_array[i][2] =medium_rand(conf_struct->minvalue2, conf_struct->maxvalue2);
	}
	return data_array;
}

DATAITEM* Generate_data_file_using_struct_array(CONF* conf_struct) {
	DATAITEM* data_struct_array = (DATAITEM*)malloc(conf_struct->number * sizeof(DATAITEM));
	srand((unsigned)time(NULL));
	for (int i = 0; i < conf_struct->number; i++) {
		data_struct_array[i].item1 = conf_struct->minvalue1 + rand() % (conf_struct->maxvalue1 - conf_struct->minvalue1 + 1);
		data_struct_array[i].item2 = conf_struct->minvalue1 + rand() % (conf_struct->maxvalue1 - conf_struct->minvalue1 + 1);
		while (data_struct_array[i].item2 == data_struct_array[i].item1) {
			data_struct_array[i].item2 = conf_struct->minvalue1 + rand() % (conf_struct->maxvalue1 - conf_struct->minvalue1 + 1);
		}
		data_struct_array[i].item3 = conf_struct->minvalue1 + rand() % (conf_struct->maxvalue1 - conf_struct->minvalue1 + 1);
	}
	return data_struct_array;
}
