#include "../include/log.h"

__attribute__((constructor))//有gcc编译器自动初始化
void log_init()
{
    // 1. 初始化 EasyLogger 内核
    elog_init();
    // ELOG_FMT_LVL	日志级别：标识日志的严重程度。	E/ (Error), W/ (Warn)
    // ELOG_FMT_TAG	标签：通常是业务模块名，用于区分日志来源。	[MAIN], [SENSOR]
    // ELOG_FMT_TIME	时间戳：记录日志发生的具体时间。	10:30:45.123
    // ELOG_FMT_DIR	文件路径：记录日志代码所在的文件路径。	src/main.c
    // ELOG_FMT_FUNC	函数名：记录日志代码所在的函数名。	sensor_read
    // ELOG_FMT_LINE	行号：记录日志代码所在的具体行号。	42
    // ELOG_FMT_P_INFO	进程信息：在多进程环境中很有用。	PID:1234
    // ELOG_FMT_T_INFO	线程信息：在多线程环境中很有用。	TID:5678
    // ELOG_FMT_ALL	启用所有：一键开启以上所有信息，通常用于最详细的日志级别。	(包含所有上述信息)
    // 2. 设置日志格式（可根据需求调整）
    elog_set_fmt(ELOG_LVL_ASSERT,  ELOG_FMT_ALL);
    elog_set_fmt(ELOG_LVL_ERROR,   ELOG_FMT_LVL | ELOG_FMT_TIME);
    elog_set_fmt(ELOG_LVL_WARN,    ELOG_FMT_LVL | ELOG_FMT_TIME | ELOG_FMT_FUNC);
    elog_set_fmt(ELOG_LVL_INFO,    ELOG_FMT_LVL | ELOG_FMT_TIME | ELOG_FMT_FUNC);
    elog_set_fmt(ELOG_LVL_DEBUG,   ELOG_FMT_LVL | ELOG_FMT_TIME | ELOG_FMT_FUNC);
    elog_set_fmt(ELOG_LVL_VERBOSE, ELOG_FMT_ALL);
    
    // 3. 如果有插件（如文件输出），也在此处初始化
    // elog_file_init();

    // 4. 启动日志
    elog_start();
}