#ifndef LOG_H
#define LOG_H
#include "../../3rd-lib/include/elog.h"

void log_init();

#define LOG_A(tag, fmt, ...) elog_a(tag, fmt, ##__VA_ARGS__)
#define LOG_D(tag, fmt, ...) elog_d(tag, fmt, ##__VA_ARGS__)
#define LOG_I(tag, fmt, ...) elog_i(tag, fmt, ##__VA_ARGS__)
#define LOG_W(tag, fmt, ...) elog_w(tag, fmt, ##__VA_ARGS__)
#define LOG_E(tag, fmt, ...) elog_e(tag, fmt, ##__VA_ARGS__)
#define LOG_V(tag, fmt, ...) elog_v(tag, fmt, ##__VA_ARGS__)


#define MLOG_A(fmt,...)  LOG_A(__FILE__,fmt,##__VA_ARGS__)
#define MLOG_D(fmt,...)  LOG_D(__FILE__,fmt,##__VA_ARGS__)
#define MLOG_I(fmt,...)  LOG_I(__FILE__,fmt,##__VA_ARGS__)
#define MLOG_W(fmt,...)  LOG_W(__FILE__,fmt,##__VA_ARGS__)
#define MLOG_E(fmt,...)  LOG_E(__FILE__,fmt,##__VA_ARGS__)
#define MLOG_V(fmt,...)  LOG_V(__FILE__,fmt,##__VA_ARGS__)
#endif