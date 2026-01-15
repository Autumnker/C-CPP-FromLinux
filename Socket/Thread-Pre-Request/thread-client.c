/*===============================================
*   文件名称：thread-client.c
*   创 建 者：Autumnker
*   创建日期：2026年01月15日
*   描    述：
================================================*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

// #define SERVER_IP "127.0.0.1"  // 服务器IP地址
// #define SERVER_PORT 8080       // 服务器端口
char SERVER_IP[INET_ADDRSTRLEN];
int SERVER_PORT;
#define BUFFER_SIZE 1024       // 缓冲区大小

int main() {
    int client_socket;
    struct sockaddr_in server_addr;
    char buffer[BUFFER_SIZE];

    // 创建客户端套接字
    client_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (client_socket == -1) {
        perror("socket创建失败");
        exit(EXIT_FAILURE);
    }

    // 设置服务器地址,端口
    printf("输入 SERVER_IP\n");
    scanf("%s", SERVER_IP);
    printf("输入 SERVER_PORT\n");
    scanf("%d", &SERVER_PORT);
    printf("%s-%d", SERVER_IP, SERVER_PORT);

    // 设置服务器地址结构
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(SERVER_PORT);
    if (inet_pton(AF_INET, SERVER_IP, &server_addr.sin_addr) <= 0) {
        perror("IP地址转换失败");
        close(client_socket);
        exit(EXIT_FAILURE);
    }

    // 连接服务器
    if (connect(client_socket, (struct sockaddr*)&server_addr, sizeof(server_addr)) == -1) {
        perror("连接服务器失败");
        close(client_socket);
        exit(EXIT_FAILURE);
    }

    printf("已连接到服务器 %s:%d\n", SERVER_IP, SERVER_PORT);
    printf("输入消息发送给服务器(输入'quit'退出):\n");

    // 与服务器通信
    while (1) {
        printf("> ");
        fgets(buffer, BUFFER_SIZE, stdin);

        // 发送消息给服务器
        ssize_t bytes_sent = send(client_socket, buffer, strlen(buffer), 0);
        if (bytes_sent <= 0) {
            perror("发送失败");
            break;
        }

        // 检查是否退出
        if (strncmp(buffer, "quit", 4) == 0) {
            printf("正在断开连接...\n");
            break;
        }

        // 接收服务器回应
        memset(buffer, 0, BUFFER_SIZE);
        ssize_t bytes_received = recv(client_socket, buffer, BUFFER_SIZE - 1, 0);
        if (bytes_received <= 0) {
            perror("接收失败或连接已关闭");
            break;
        }

        printf("服务器回应: %s", buffer);
    }

    // 关闭套接字
    close(client_socket);
    printf("连接已关闭\n");

    return 0;
}
