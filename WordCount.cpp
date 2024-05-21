#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_FILENAME_LENGTH 256
#define MAX_BUFFER_SIZE 1024

int count_characters(FILE *file) {
    int count = 0;// 初始化计数器为0
    char ch;
    while ((ch = fgetc(file)) != EOF) {
        count++;
    }// 使用fgetc函数从文件中逐个读取字符，直到遇到文件结束符EOF
    return count; // 返回字符总数
}

int count_words(FILE *file) {// 定义一个函数，用于计算文件中的单词数
    int count = 0;
    char buffer[MAX_BUFFER_SIZE];
    char *word;// 定义一个指针，用于strtok函数分割单词
    
    while (fgets(buffer, MAX_BUFFER_SIZE, file) != NULL) {// 使用fgets函数从文件中逐行读取内容到缓冲区
        word = strtok(buffer, " ,\t\n");// 使用strtok函数以空格、逗号、制表符和换行符为分隔符分割单词
        while (word != NULL) {
            count++;
            word = strtok(NULL, " ,\t\n");// 继续在剩余字符串中查找单词
        }
    }
    return count;
}

int main(int argc, char *argv[]) {
    if (argc != 3) {// 检查命令行参数数量是否为3
        printf("Usage: %s [-c or -w] [input_file_name]\n", argv[0]);
        return 1;
    }

    char *option = argv[1]; // 获取命令行参数
    char *filename = argv[2];
    FILE *file = fopen(filename, "r");// 尝试以只读方式打开文件
    
    if (file == NULL) {// 根据选项执行不同的计数操作
        printf("Error: Cannot open file %s\n", filename);
        return 1;
    }

    int count = 0;
    if (strcmp(option, "-c") == 0) {
        count = count_characters(file);
        printf("字符数：%d\n", count);
    } else if (strcmp(option, "-w") == 0) {
        count = count_words(file);
        printf("单词数：%d\n", count);
    } else {
        printf("Error: Invalid option %s. Please use -c or -w\n", option);
        return 1;
    }

    fclose(file);// 关闭文件
    return 0;
}

