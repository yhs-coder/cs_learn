/*
    实现简单的多进程的并发服务器
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <ctype.h>
#include <signal.h>
#include <sys/wait.h>
#include "wrap.h"

#define SRV_PORT 8888


// 注册信号捕捉函数，用于处理结束的子进程
void catch_child(int signum)
{
    while( waitpid(0, NULL,  WNOHANG) > 0)
        ;
}


int main(int argc, char *argv[])
{
    int lfd,cfd;
    pid_t pid;
    struct sockaddr_in srv_addr,clt_addr;
    socklen_t clt_addr_len;
    char buf[BUFSIZ];
    int ret,i;

    srv_addr.sin_family = AF_INET;
    srv_addr.sin_port = htons(SRV_PORT);
    srv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    
    // 降地址结构清零
    // memset(&srv_addr,0,sizeof(srv_addr));
    bzero(&srv_addr, sizeof(srv_addr));
    srv_addr.sin_family = AF_INET;
    srv_addr.sin_port = htons(SRV_PORT);
    srv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    clt_addr_len = sizeof(clt_addr);
    lfd = Socket(AF_INET, SOCK_STREAM, 0);

    Bind(lfd,(struct sockaddr*)&srv_addr, sizeof(srv_addr));   
    // INADDR_ANY 是一个常量值，表示服务器机器的任何网络接口的 IP 地址

    Listen(lfd, 128);

    while(1)
    {
        cfd = Accept(lfd, (struct sockaddr*)&clt_addr, &clt_addr_len);
        pid = fork();

        if (pid < 0) {
            perr_exit("fork error");
        
        } else if (pid == 0) {
            close(lfd);
            break;
        } else {
            struct sigaction act;
            act.sa_handler = catch_child;
            sigemptyset(&act.sa_mask); // 设置信号屏蔽字
            act.sa_flags = 0; //0表示信号执行默认行为
            ret = sigaction(SIGCHLD, &act, NULL);
            if (ret != 0) {
                perr_exit("sigaction error");
            }
            close(cfd);
            continue;
        } 

    }

    // 子进程处理
    if (pid == 0) {
        for(;;) {
            ret = Read(cfd, buf, sizeof(buf));
            if (ret == 0) {
                close(cfd);
                exit(1);
            }
            for (i = 0; i < ret; i++) {
                buf[i] = toupper(buf[i]);
            }
            Write(cfd, buf, ret);
            Write(STDOUT_FILENO, buf, ret);
        }
    }
    return 0;
}


