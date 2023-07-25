//
// Created by Shawn Zhao on 2023/7/25.
//

#ifndef SEMAPHORE_COMM_H
#define SEMAPHORE_COMM_H

#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/stat.h>
#include <sys/sem.h>

#define PROJ_ID 0x6666
#define PATHNAME "."

union semun_my { // 操作信号量的联合体
    int val; // 用于设置信号量的初始值，或者用于获取信号量的当前值。
    struct semid_ds *buf; // 用于获取信号量的状态信息。
    unsigned short *array; // 指向一个 unsigned short 数组的指针，用于设置一组信号量的值。
    struct seminfo *_buf; // 指向一个 struct seminfo 结构的指针，用于获取系统中信号量的一些信息。
    // 在使用 semctl() 函数时，需要根据具体情况选择合适的 union semun 成员来进行信号量的初始化或控制。
};

int createSemSet(int nums);
int getSemSet();
int destroySems(int semid);
int initSems(int semid,int who,int value);
int P(int semid,int who);
int V(int semid,int who);

#endif //SEMAPHORE_COMM_H
