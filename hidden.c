#include <stdio.h>
#include <stdlib.h>

#define ONE_MB (1024 * 1024)

const int XOR_KEY = 0x55; // 任意选择的异或密钥

void partialEncrypt(char *data, unsigned int length) {
    for (int i = 0; i < length; i++) {
        data[i] ^= XOR_KEY;
    }
}

unsigned int min(unsigned int a, unsigned int b) {
    return (a < b) ? a : b;
}

int main(int argc, char *argv[]) {
    const char *filename = argv[1];

    // 读取文件
    FILE *file = fopen(filename, "r+b");
    if (file == NULL) {
        printf("Error opening file.\n");
        return 1;
    }

    // 读取文件内容
    char *data = (char *) malloc(ONE_MB);

    if (data == NULL) {
        fclose(file);
        printf("Memory allocation error.\n");
        return 2;
    }

    size_t readSize = fread(data, 1, ONE_MB, file);

    unsigned int encryptLength = min(readSize, ONE_MB);
    partialEncrypt(data, encryptLength);

    fseek(file, 0, SEEK_SET);
    fwrite(data, 1, encryptLength, file);

    // 释放内存和关闭文件
    free(data);
    fclose(file);

    printf("Partial encryption and decryption completed successfully.\n");
    return 0;
}
