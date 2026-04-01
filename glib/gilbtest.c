#include <glib.h>

/*
// 整数类型
gint8, guint8     // 8位整数
gint16, guint16   // 16位整数
gint32, guint32   // 32位整数
gint64, guint64   // 64位整数

// 其他类型
gboolean          // 布尔类型，取值为 TRUE/FALSE
gpointer          // 等价于 void*
gconstpointer     // 等价于 const void*
*/
void testType()
{
    // 有位整数
    gint8 a = 10;
    g_print("%d\n",a);
    // 无符号整数
    guint8 b = 10;
    g_print("%d\n",b);
    // 其他类型
    gboolean c = TRUE;
    g_print("%d\n",c);
    // 指针类型
    gpointer d = NULL;
    g_print("%p\n",d);
    // 常量指针类型
    gconstpointer e = NULL;
    g_print("%p\n",e);
    /*
    // 输出结果
    10
    10
    1
    (nil)
    (nil)
    */
}

/*
// 内存分配函数
g_malloc()	分配内存，失败时自动终止程序，无需检查返回值	gpointer p = g_malloc(size);
g_free()	释放内存，可安全传入 NULL	g_free(p);
g_malloc0()	分配内存并全部置零	gpointer p = g_malloc0(size);
g_realloc()	重新分配内存	p = g_realloc(p, new_size);
g_slice_alloc()	从切片分配器分配小块内存，效率更高	gpointer p = g_slice_alloc(sizeof(MyStruct));
g_slice_free()	释放切片分配的内存	g_slice_free(MyStruct, p);
*/
void testMalloc()
{
    // 分配内存
    gint * p = (gint *)g_malloc(10*sizeof(gint));
    // 初始化内存
    for(int i = 0; i < 10; i++)
    {
        p[i] = i;
        g_print("%d\n",p[i]);
    }
    // 释放内存
    g_free(p);
    /*
    // 输出结果
    0
    1
    2
    3
    4
    5
    6
    7
    8
    9
    */
}

/*
类型转换宏
// 整数与指针之间的转换
GINT_TO_POINTER(int_val)      // int -> gpointer
GPOINTER_TO_INT(ptr)          // gpointer -> int
GUINT_TO_POINTER(uint_val)    // unsigned int -> gpointer
GPOINTER_TO_UINT(ptr)         // gpointer -> unsigned int
这些宏在链表和哈希表中存储整数值时非常有用
*/
void testTypeConvert()
{
    // 整数与指针之间的转换
    gint a = 10;
    gpointer b = GINT_TO_POINTER(a);
    g_print("%p\n",b);
    g_print("%d\n",GPOINTER_TO_INT(b));
    /*
    // 输出结果
    0xa
    10
    */
}

/*
GArray 是会自动增长的动态数组，所有元素大小相同\
2.2 添加元素
g_array_append_val(array, value)	O(n)	在末尾添加一个元素
g_array_append_vals(array, values, count)	O(n)	在末尾添加多个元素
g_array_prepend_val(array, value)	O(n)	在开头添加一个元素
g_array_prepend_vals(array, values, count)	O(n)	在开头添加多个元素
g_array_insert_val(array, index, value)	O(n)	在指定位置插入元素
2.3 访问与操作
g_array_index(array, type, index)	访问指定索引的元素（O(1)）
g_array_set_size(array, size)	设置数组大小
g_array_sort(array, compare_func)	排序（O(n log n)）
*/
void testGArray()
{
    GArray *array = g_array_new(FALSE, FALSE, sizeof(int));

    for (int i = 0; i < 10; i++) {
        g_array_append_val(array, i);  // 添加元素
    }
    // 访问元素
    for (int i = 0; i < array->len; i++) {
        int val = g_array_index(array, int, i);
        g_print("%d ", val);
    }
g_array_free(array, TRUE);  // TRUE 表示同时释放数据内存
}

/*
GPtrArray 是专门存储指针的动态数组。
3.1 核心函数
g_ptr_array_new()	创建指针数组
g_ptr_array_add(array, pointer)	添加指针
g_ptr_array_index(array, index)	访问指定索引的指针
g_ptr_array_remove(array, data)	删除指定指针的元素
g_ptr_array_remove_index(array, index)	删除指定索引的元素
g_ptr_array_remove_index_fast(array, index)	快速删除（不保持顺序）
g_ptr_array_free(array, free_seg)	释放数组
*/
void testGPtrArray()
{
    GPtrArray *array = g_ptr_array_new();
    g_ptr_array_add(array, "one");
    g_ptr_array_add(array, "one");
    g_ptr_array_add(array, "two");
    g_ptr_array_add(array, "three");
    // 访问
    char *str = (char*)g_ptr_array_index(array, 0);
    // 遍历
    for (guint i = 0; i < array->len; i++) {
        g_print("%s\n", (char*)array->pdata[i]);
    }
    g_ptr_array_free(array, TRUE);
}

/*
GSList 是单向链表，插入/删除 O(1)，查找 O(n)。
g_slist_append(list, data)	在末尾添加元素（需遍历）
g_slist_prepend(list, data)	在开头添加元素（推荐）
g_slist_insert(list, data, position)	在指定位置插入
g_slist_insert_sorted(list, data, func)	按顺序插入
g_slist_remove(list, data)	删除第一个匹配的元素
g_slist_find(list, data)	查找元素
g_slist_nth(list, n)	获取第 n 个节点
g_slist_length(list)	获取长度（需遍历）
g_slist_foreach(list, func, user_data)	遍历所有元素
g_slist_free(list)	释放链表
g_slist_reverse(list)	反转链表
重要提示
链表初始化为 NULL 即可。
插入函数返回新的链表头，必须保存返回值。
频繁添加元素时，建议使用 g_slist_prepend() 最后再反转，避免多次遍历。
*/

void testGSList()
{
    GSList *list = NULL;
    // 添加元素
    list = g_slist_prepend(list, "first");
    list = g_slist_prepend(list, "second");
    list = g_slist_prepend(list, "third");
    // 反转以获得正确的顺序
    list = g_slist_reverse(list);
    // 遍历
    g_slist_foreach(list, (GFunc)g_print, NULL);
    g_print("\n");
    // 输出长度
    g_print("Length: %d\n", g_slist_length(list));
    // 查找
    GSList *found = g_slist_find(list, "second");
    if(found)
    {
        g_print("Found: %s\n", (char*)found->data);
    }
    else
    {
        g_print("Not Found\n");
    }
    // 删除
    list = g_slist_remove(list, "second");
    // 释放
    g_slist_free(list);
}

/*
GList 是双向链表，比 GSList 多用一倍内存，但可双向遍历，查找性能更好。
g_list_previous(node)	获取前一个节点
g_list_last(list)	获取最后一个节点
g_list_first(list)	获取第一个节点
g_list_append(list, data)	末尾添加（O(n)）
g_list_prepend(list, data)	开头添加（O(1)）
g_list_insert_before(list, sibling, data)	在指定节点前插入
*/

void testGList()
{
    GList *list = NULL;
    list = g_list_append(list, "one");
    list = g_list_append(list, "two");
    list = g_list_prepend(list, "zero");
    // 双向遍历
    GList *last = g_list_last(list);
    while (last != NULL) {
    g_print("%s\n", (char*)last->data);
    last = last->prev;
    }
    // 安全删除（遍历时）
    GList *l = list;
    while (l != NULL) {
    GList *next = l->next;
    list = g_list_delete_link(list, l);
    l = next;
    }
    g_list_free(list);
}
/*
GHashTable 是键值对存储结构，查找/插入/删除均为 O(1)。
g_hash_table_new(hash_func, equal_func)	创建哈希表
g_hash_table_new_full(hash_func, equal_func, key_destroy, value_destroy)	创建时指定销毁函数
g_hash_table_destroy(table)	销毁哈希表
g_hash_table_unref(table)	减少引用计数
常用哈希函数
g_str_hash()	字符串哈希函数
g_str_equal()	字符串比较函数
g_int_hash()	整数哈希函数
g_int_equal()	整数比较函数
g_direct_hash()	直接使用指针值作为哈希
g_direct_equal()	直接比较指针
核心操作函数
g_hash_table_insert(table, key, value)	插入键值对
g_hash_table_lookup(table, key)	根据键查找值
g_hash_table_contains(table, key)	检查键是否存在
g_hash_table_remove(table, key)	删除键值对
g_hash_table_foreach(table, func, user_data)	遍历所有键值对
重要提示
键和值不会被复制，必须在整个哈希表生命周期内有效。
临时字符串必须用 g_strdup() 复制后再插入。
不要混用静态字符串和动态分配的字符串。
*/
// 用于遍历哈希表的回调函数
void print_pair(gpointer key, gpointer value, gpointer user_data)
{
    g_print("%s: %s\n", (char*)key, (char*)value);
}
void testGHashTable()
{
    // 创建哈希表，键和值都是字符串
    GHashTable *table = g_hash_table_new(g_str_hash, g_str_equal);
    // 插入（静态字符串可以）
    g_hash_table_insert(table, "name", "Alice");
    g_hash_table_insert(table, "city", "Beijing");
    // 查找
    char *value = g_hash_table_lookup(table, "name");
    // 检查是否存在
    if (g_hash_table_contains(table, "city")) {
    g_print("City exists\n");
    }
    // 遍历
    g_hash_table_foreach(table, (GHFunc)print_pair, NULL);
    // 删除
    g_hash_table_remove(table, "city");
    // 销毁
    g_hash_table_destroy(table);
}

/*
GString 是自动管理内存的动态字符串，str 成员保证有尾随空字符，可安全用于标准 C 字符串函数。
结构体定义
struct GString {
    gchar *str;      // 字符串数据（以空结尾）
    gsize len;       // 当前长度（不含结尾空字符）
    gsize allocated_len;  // 已分配空间
};
创建与销毁
g_string_new(init)	从初始字符串创建
g_string_new_len(init, len)	从指定长度的缓冲区创建
g_string_sized_new(dfl_size)	预分配空间的创建
g_string_free(string, free_segment)	释放，可返回字符串数据
修改操作
g_string_append(string, val)	追加字符串
g_string_append_c(string, c)	追加字符
g_string_append_printf(string, format, ...)	格式化追加
g_string_prepend(string, val)	前置字符串
g_string_insert(string, pos, val)	在指定位置插入
g_string_erase(string, pos, len)	删除指定范围的字符
g_string_truncate(string, len)	截断到指定长度
g_string_assign(string, rval)	重新赋值
*/

void testGString()
{
    GString *str = g_string_new("Hello");
    g_string_append(str, " World");
    g_string_append_c(str, '!');
    g_string_append_printf(str, " %d", 2024);

    g_print("%s\n", str->str);  // 输出: Hello World! 2024

    // 转换为普通字符串并释放
    char *cstr = g_string_free(str, FALSE);  // FALSE 表示返回字符串数据
    g_free(cstr);
}
/*
日志与调试
g_print(format, ...)	打印信息
g_warning(format, ...)	打印警告信息（输出 "** WARNING **" 前缀）
g_error(format, ...)	打印错误信息并终止程序
g_return_if_fail(cond)	条件失败时返回并记录警告
g_return_val_if_fail(cond, val)	条件失败时返回值并记录警告
*/
void testLog()
{
    // 1. 基本日志输出
    g_print("This is a normal message\n");
    g_warning("This is a warning message");
    // 2. 条件检查宏
    gint value = -1;
    g_return_if_fail(value >= 0); // 如果条件失败，会记录警告并返回
    // 3. 完整的日志系统
    g_log("MyApp", G_LOG_LEVEL_INFO, "This is an info message");
    g_log("MyApp", G_LOG_LEVEL_DEBUG, "This is a debug message");
    // 4. 日志级别控制示例
    // 注意：实际应用中，日志级别通常通过环境变量 G_MESSAGES_DEBUG 控制
    // 5. 演示 g_error（会终止程序，所以注释掉）
    // g_error("This is an error message that will terminate the program")
    // 6. 自定义日志处理程序示例
    // 这里只是展示如何设置，实际使用时需要定义处理函数
    // g_log_set_handler("MyApp", G_LOG_LEVEL_MASK, my_log_handler, NULL);
}
// 自定义日志处理程序示例（可选）
/*
void my_log_handler(const gchar *log_domain, 
                    GLogLevelFlags log_level, 
                    const gchar *message, 
                    gpointer user_data)
{
    // 自定义日志处理逻辑
    g_print("[%s] %s: %s\n", 
            log_domain ? log_domain : "Default", 
            g_log_level_to_string(log_level), 
            message);
}
*/

/*
系统信息
g_get_user_name()	获取当前用户名
g_get_home_dir()	获取用户家目录
g_get_current_dir()	获取当前工作目录
g_get_prgname()	获取程序名称
g_file_test(filename, test)	检查文件是否存在/可读等
*/
void testSystemInfo()
{
    // 1. 获取系统信息
    const gchar *user_name = g_get_user_name();
    const gchar *home_dir = g_get_home_dir();
    const gchar *current_dir = g_get_current_dir();
    const gchar *prg_name = g_get_prgname();
    
    g_print("User name: %s\n", user_name);
    g_print("Home directory: %s\n", home_dir);
    g_print("Current directory: %s\n", current_dir);
    g_print("Program name: %s\n", prg_name ? prg_name : "Unknown");
    
    // 2. 文件测试
    gboolean exists = g_file_test(".", G_FILE_TEST_IS_DIR);
    g_print("Current directory exists: %s\n", exists ? "Yes" : "No");
    
    exists = g_file_test("glibbtest", G_FILE_TEST_IS_REGULAR);
    g_print("Executable exists: %s\n", exists ? "Yes" : "No");
    
    // 3. 设置程序名称（可选）
    g_set_prgname("glibtest");
    prg_name = g_get_prgname();
    g_print("Program name after set: %s\n", prg_name ? prg_name : "Unknown");
}

/*
线程池
*/
// 线程池任务回调函数
void thread_pool_task(gpointer data, gpointer user_data)
{
    gint task_id = GPOINTER_TO_INT(data);
    g_print("Task %d started\n", task_id);
    
    // 模拟任务执行时间
    g_usleep(1000000); // 1秒
    
    g_print("Task %d completed\n", task_id);
}

void testThreadPool()
{
    // 1. 创建线程池
    // 参数：最大线程数，是否在空闲时释放线程，线程优先级
    GThreadPool *pool = g_thread_pool_new(thread_pool_task, 
                                          NULL, // 用户数据
                                          4,    // 最大线程数
                                          FALSE, // 不自动释放线程
                                          NULL); // 错误处理
    
    if (!pool) {
        g_error("Failed to create thread pool");
        return;
    }
    
    g_print("Thread pool created with max threads: 4\n");
    
    // 2. 添加任务到线程池
    for (gint i = 0; i < 10; i++) {
        g_thread_pool_push(pool, GINT_TO_POINTER(i), NULL);
        g_print("Added task %d to pool\n", i);
    }
    
    // 3. 等待所有任务完成
    g_print("Waiting for all tasks to complete...\n");
    g_thread_pool_free(pool, FALSE, TRUE); // 等待所有任务完成
    
    g_print("All tasks completed and thread pool freed\n");
}

/*
计时器
*/
void testTimer()
{
    GTimer *timer = g_timer_new();
    g_timer_start(timer);
    // ... 执行操作 ...
    g_timer_stop(timer);
    double elapsed = g_timer_elapsed(timer, NULL);
    g_print("Elapsed: %f seconds\n", elapsed);
    g_timer_destroy(timer);
}


int main()
{
    // testType();
    // testMalloc();
    // testTypeConvert();
    // testGArray();
    // testGPtrArray();
    // testGSList();
    // testGList();
    // testGHashTable();
    // testGString();
    // testLog();
    // testSystemInfo();
    // testThreadPool();
    testTimer();
    return 0;
}