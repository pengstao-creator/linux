#pragma once
// #include "myh/socket.hpp"
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <stdint.h>
#include <limits.h>
//
void HostToNetwork(struct sockaddr_in * addr,const char * ip,uint16_t prot,int domain, int type);
void NetworkToHost(struct sockaddr_in * addr,char ** ip,uint16_t* prot);
//给文件描述符设置非阻塞
int SetNonBlocking(int fd);
void SimpleErrorHandler(int ReturnValue,const char * name);
int str_to_uint16(const char *str, uint16_t *value);

void Bind(int fd,struct sockaddr_in * addr);
int Accept(int fd,struct sockaddr_in * addr);
void Connect(int fd,struct sockaddr_in * addr);
