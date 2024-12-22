#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include<direct.h>
#include "run.h"
#include"fun.h"
#include<string.h>

void run(int argc, char* argv[]) {
	CONF* conf_struct = (CONF*)malloc(sizeof(CONF));
	FILE* fp;
	fp = fopen("..//conf.ini.txt", "r");
	if (fp == NULL) {
		printf("配置文件不存在，请检查.\n");
		return;
	}
	else {
		printf("配置文件存在，开始读取.\n");
		fscanf(fp, "%s", conf_struct->filesavepath);
		fscanf(fp, "%s", conf_struct->filename);
		fscanf(fp, "%d", &conf_struct->number);
		fscanf(fp, "%d", &conf_struct->maxvalue1);
		fscanf(fp, "%d", &conf_struct->minvalue1);
		fscanf(fp, "%d", &conf_struct->maxvalue2);
		fscanf(fp, "%d", &conf_struct->minvalue2);
		fscanf(fp, "%d", &conf_struct->recordcount1);
		fscanf(fp, "%d", &conf_struct->recordcount2);


	}
	fclose(fp);
	printf("配置文件读取成功.\n");

	
	if (argc == 1) {
		
		Confirm_number(conf_struct);
		Confirm_filesavepath_and_filename(conf_struct);

	}
	else if (argc == 2) {
		if (is_number(argv[1], strlen(argv[1]))) {
			conf_struct->number = atoi(argv[1]);
			Confirm_filesavepath_and_filename(conf_struct);
		}
		else {
			if (filesavelocation_is_legal(argv[1], strlen(argv[1]))) {
				split_path_and_filename(argv[1], conf_struct, strlen(argv[1]));
				Confirm_number(conf_struct);
			}
		}
	}
	else if (argc == 3) {
		if (is_number(argv[1], strlen(argv[1]))) {
			conf_struct->number = atoi(argv[1]);
			if (filesavelocation_is_legal(argv[2], strlen(argv[2]))) {
				split_path_and_filename(argv[2], conf_struct, strlen(argv[2]));
			}else {
				printf("命令行参数不合法，第二个参数是文件保存路径不合法，第一个参数是数字.\n");
				return;
			}
		}
		else if (is_number(argv[2], strlen(argv[2]))) {
			conf_struct->number = atoi(argv[2]);
			if (filesavelocation_is_legal(argv[1], strlen(argv[1]))) {
				split_path_and_filename(argv[1], conf_struct, strlen(argv[1]));
			}
			else {
				printf("命令行参数不合法，第二个参数是数字，第一个参数文件保存路径不合法\n");
				return;
			}
		}
		else {
			printf("找不到记录条数参数\n");
			return;
		}
	}
	else {
		printf("命令行参数过多\n");
		return;
	}
	printf("岳朝霞的实验3程序:\n");
	printf("      1. 生成数据记录文件（使用二维数组存储）\n");
	printf("      2. 生成数据记录文件（使用结构体数组存储）\n");
	printf("请输入您要执行的功能序号：\n");
	
	int choice;
	int** data_array = (int**)malloc(sizeof(int*));
	DATAITEM* data_struct_array = (DATAITEM*)malloc(sizeof(DATAITEM));
	scanf("%d", &choice);
	getchar();
	printf("如果想随机生成记录条数,请输入r,否则请输入数字.\n");
	char input[20];
	scanf("%s", input);
	getchar();
	while (input != "r" ) {
		int k = 1;
		int i = 0;
		for (i = 0; i < strlen(input); i++) {
			if (!isdigit(input[i])) k = 0;
		}
		if (k == 0) {
			printf("输入错误，请重新输入r或数字：\n");
			scanf("%s", input);
			getchar();
		}
		else {
			break;
		}
	}
	if (input == "r") {
		conf_struct->number = rand() % (conf_struct->recordcount1 - conf_struct->recordcount2 + 1) + conf_struct->recordcount2;
	}
	else {
		conf_struct->number = atoi(input);
	}
	while (choice != 1 && choice != 2) {
		printf("输入错误，请重新输入1或2：\n");
		scanf("%d", &choice);
	}
	switch (choice) {
	case 1:
		data_array = Generate_data_file_using_2D_array(conf_struct);
		break;
	case 2:
		data_struct_array = Generate_data_file_using_struct_array(conf_struct);
		break;
	default:
		break;
	}
	if (_access(conf_struct->filesavepath, 0) == -1) {
		if(_mkdir(conf_struct->filesavepath) == -1) {
			printf("创建文件夹失败，请检查.\n");
			return;
		}
	}
	char* full_path = (char*)malloc(strlen(conf_struct->filesavepath) + strlen(conf_struct->filename) + 2);
	if (full_path == NULL) {
		printf("内存分配失败，请检查.\n");
		return;
	}

	strcpy(full_path, conf_struct->filesavepath);
	strcat(full_path, "\\");
	strcat(full_path, conf_struct->filename);
	full_path[strlen(conf_struct->filesavepath) + strlen(conf_struct->filename)+1] = '\0';
	FILE* fp_data = fopen(full_path, "w");
	if (fp_data == NULL) {
		printf("文件打开失败，请检查.\n");
		return;
	}
	fprintf(fp_data, "%d\n", conf_struct->number);
	if (choice == 1) {
		for (int i = 0; i < conf_struct->number; i++) {
			fprintf(fp_data, "%d,%d,%d\n", data_array[i][0], data_array[i][1], data_array[i][2]);
		}
	}
	else {
		for (int i = 0; i < conf_struct->number; i++) {
			fprintf(fp_data, "%d,%d,%d\n", data_struct_array[i].item1, data_struct_array[i].item2, data_struct_array[i].item3);
		}
	}
	fclose(fp_data);

	printf("数据文件生成成功.\n");	
	printf("数据文件路径: %s\n", full_path);


	return;

}
