#include <stdio.h>
#include <string.h>
#include "../include/clock.h"
#include "../include/args.h"

/**
 * @brief 主函数
 *
 * 解析命令行参数并调用相应函数。
 *
 * @param argc 参数个数
 * @param argv 参数数组
 * @return 返回程序执行状态码
 */
int main(int argc, char *argv[])
{
    return handle_args(argc, argv);
}
