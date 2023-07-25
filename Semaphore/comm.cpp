//
// Created by Shawn Zhao on 2023/7/25.
//

#include "comm.h"
#include <cstdio>
/*
 * 用于创建或获取信号量集。
 * 在全局作用域中定义的函数，使用static修饰，称为静态全局函数。
 * */
static int commSemSet(int nums, int flags) {
    key_t key = ftok(PATHNAME, PROJ_ID);
    if (key < 0) {
        perror("ftok"); // 查找对应的错误信息全局变量errno的当前值并将其写入
        return -1;
    }
    int semid = semget(key, nums, flags); // 返回信号量标识符
    if (semid < 0) {
        perror("semget");
        return -2;
    }
    return semid;
}
/*
 * 用于创建新的信号量集
 * */
int createSemSet(int nums) {
    // IPC_CREAT 创建新的信号量集，有就返回现在标识符
    // IPC_EXCL：与 IPC_CREAT 结合使用时，表示如果指定的信号量集已经存在，则创建失败，semget() 函数会返回错误。如果没有指定 IPC_EXCL，则 semget() 函数会返回现有信号量集的标识符。
    // IPC_NOWAIT：用于在获取信号量集时设置非阻塞模式。
    // 权限。0666表示所有用户都有权限
    return commSemSet(nums, IPC_CREAT | IPC_EXCL | 0666);
}
/*
 * 用于初始化信号量集中的一个信号量
 * */
int initSems(int semid, int who, int initval) {
    union semun_my _un;
    _un.val = initval;
    // SETVAL 设置value
    if (semctl(semid, who, SETVAL, _un) < 0) {
        perror("semctl");
        return -1;
    }
    return 0;
}
/*
 * 用于执行 P 操作和 V 操作
 * */
static int commPV(int semid, int who, int op) {
    struct sembuf _sf;
    _sf.sem_num = who; // 操作谁
    _sf.sem_op = op; // -1 P +1 V
    _sf.sem_flg = 0;
    // 用来创建和访问一个信号量集。信号集操作个数
    return semop(semid, &_sf, 1);
}
/*
 * 用于执行 P 操作（信号量减 1）
 * */
int P(int semid, int who) {
    return commPV(semid, who, -1);
}
/*
 * 用于执行 V 操作（信号量加 1）
 * */
int V(int semid, int who) {
    return commPV(semid, who, +1);
}
/*
 * 用于获取一个已经存在的信号量集的标识符
 * */
int getSemSet() {
    return commSemSet(0, IPC_CREAT);
}

int destroySems(int semid) {
    if (semctl(semid, 0, IPC_RMID, NULL) < 0) {
        perror("semctl");
        return -1;
    }
    return 0;
}