#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_FILENAME_LENGTH 256
#define MAX_BUFFER_SIZE 1024

int count_characters(FILE *file) {
    int count = 0;// ��ʼ��������Ϊ0
    char ch;
    while ((ch = fgetc(file)) != EOF) {
        count++;
    }// ʹ��fgetc�������ļ��������ȡ�ַ���ֱ�������ļ�������EOF
    return count; // �����ַ�����
}

int count_words(FILE *file) {// ����һ�����������ڼ����ļ��еĵ�����
    int count = 0;
    char buffer[MAX_BUFFER_SIZE];
    char *word;// ����һ��ָ�룬����strtok�����ָ��
    
    while (fgets(buffer, MAX_BUFFER_SIZE, file) != NULL) {// ʹ��fgets�������ļ������ж�ȡ���ݵ�������
        word = strtok(buffer, " ,\t\n");// ʹ��strtok�����Կո񡢶��š��Ʊ���ͻ��з�Ϊ�ָ����ָ��
        while (word != NULL) {
            count++;
            word = strtok(NULL, " ,\t\n");// ������ʣ���ַ����в��ҵ���
        }
    }
    return count;
}

int main(int argc, char *argv[]) {
    if (argc != 3) {// ��������в��������Ƿ�Ϊ3
        printf("Usage: %s [-c or -w] [input_file_name]\n", argv[0]);
        return 1;
    }

    char *option = argv[1]; // ��ȡ�����в���
    char *filename = argv[2];
    FILE *file = fopen(filename, "r");// ������ֻ����ʽ���ļ�
    
    if (file == NULL) {// ����ѡ��ִ�в�ͬ�ļ�������
        printf("Error: Cannot open file %s\n", filename);
        return 1;
    }

    int count = 0;
    if (strcmp(option, "-c") == 0) {
        count = count_characters(file);
        printf("�ַ�����%d\n", count);
    } else if (strcmp(option, "-w") == 0) {
        count = count_words(file);
        printf("��������%d\n", count);
    } else {
        printf("Error: Invalid option %s. Please use -c or -w\n", option);
        return 1;
    }

    fclose(file);// �ر��ļ�
    return 0;
}

