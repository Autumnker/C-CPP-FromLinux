/*===============================================
*   文件名称：thread-server.c
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
#include <pthread.h>

// #define PORT 8080
#define MAX_CLIENTS 10
#define BUFFER_SIZE 1024

// 客户端处理线程的参数结构
typedef struct {
    int client_socket;
    struct sockaddr_in client_addr;
} client_info_t;

// 处理客户端连接的线程函数
void* handle_client(void* arg) {
    client_info_t* client = (client_info_t*)arg;
    char buffer[BUFFER_SIZE];
    char client_ip[INET_ADDRSTRLEN];

    // 获取客户端IP地址
    inet_ntop(AF_INET, &(client->client_addr.sin_addr), client_ip, INET_ADDRSTRLEN);
    printf("新客户端连接: %s:%d\n", client_ip, ntohs(client->client_addr.sin_port));

    // 与客户端通信
    while (1) {
        memset(buffer, 0, BUFFER_SIZE);
        ssize_t bytes_received = recv(client->client_socket, buffer, BUFFER_SIZE - 1, 0);

        if (bytes_received <= 0) {
            printf("客户端 %s:%d 断开连接\n", client_ip, ntohs(client->client_addr.sin_port));
            break;
        }

        printf("来自 %s:%d 的消息: %s", client_ip, ntohs(client->client_addr.sin_port), buffer);

        // 简单回显
        send(client->client_socket, buffer, bytes_received, 0);
    }

    // 关闭客户端套接字
    close(client->client_socket);
    free(client);
    pthread_exit(NULL);
}

int main() {
    char server_ip[INET_ADDRSTRLEN]; memset(server_ip, '\0', INET_ADDRSTRLEN);
    int server_port;
    int server_socket, client_socket;
    struct sockaddr_in server_addr, client_addr;
    socklen_t client_addr_len = sizeof(client_addr);
    pthread_t thread_id;

    // 创建服务器套接字
    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket == -1) {
        perror("socket创建失败");
        exit(EXIT_FAILURE);
    }

    // 输入SERVER_IP和SERVER_PORT
    // 在输入IP前显示可用IP
    system("ifconfig | grep 'inet '");  // Linux
    printf("输入 SERVER_IP (输入0.0.0.0监听所有接口): ");
    scanf("%s", server_ip);
    do {
        printf("输入 SERVER_PORT (1024-65535): ");
        scanf("%d", &server_port);
    } while (server_port < 1024 || server_port > 65535);

    // 设置服务器地址结构
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(server_port);

    if (strcmp(server_ip, "0.0.0.0") == 0) {
        server_addr.sin_addr.s_addr = INADDR_ANY;
    }
    else {
        if (inet_pton(AF_INET, server_ip, &server_addr.sin_addr) <= 0) {
            perror("IP地址转换失败");
            close(server_socket);
            exit(EXIT_FAILURE);
        }
    }

    // 设置地址重用
    int opt = 1;
    setsockopt(server_socket, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    // 绑定套接字
    if (bind(server_socket, (struct sockaddr*)&server_addr, sizeof(server_addr)) == -1) {
        perror("bind失败");
        close(server_socket);
        exit(EXIT_FAILURE);
    }

    // 监听连接
    if (listen(server_socket, MAX_CLIENTS) == -1) {
        perror("listen失败");
        close(server_socket);
        exit(EXIT_FAILURE);
    }

    inet_ntop(AF_INET, &server_addr.sin_addr, server_ip, INET_ADDRSTRLEN);
    printf("服务器启动，%s:%d...\n", server_ip, server_port);

    // 主循环，接受客户端连接
    while (1) {
        client_socket = accept(server_socket, (struct sockaddr*)&client_addr, &client_addr_len);
        if (client_socket == -1) {
            perror("accept失败");
            continue;
        }

        // 为每个客户端创建新线程
        client_info_t* client = (client_info_t*)malloc(sizeof(client_info_t));
        if (!client) {
            perror("内存分配失败");
            close(client_socket);
            continue;
        }

        client->client_socket = client_socket;
        memcpy(&client->client_addr, &client_addr, sizeof(client_addr));

        if (pthread_create(&thread_id, NULL, handle_client, (void*)client) != 0) {
            perror("线程创建失败");
            free(client);
            close(client_socket);
            continue;
        }

        // 分离线程，使其结束后自动释放资源
        pthread_detach(thread_id);
    }

    // 关闭服务器套接字(实际上永远不会执行到这里)
    close(server_socket);
    return 0;
}
