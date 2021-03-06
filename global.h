#pragma once
#include<thread>

using namespace std;

/*返回值，代表操作的结果类型，RCOK 正确，ERROR 错误，
NOT_FOUND 数据项不存在， ALREADY_EXIST 数据项已存在
*/
enum RC { RCOK, ERROR, FINISH, NOT_FOUND, ALREADY_EXIST };

/* 三种锁类型，EX代表互斥锁，SH代表共享锁，NONE代表无锁
 */
enum lock_t { LOCK_EX, LOCK_SH, LOCK_NONE };

/*代表三种并发策略，LOCK 基于锁，OCC 乐观并发控制，TO基于时间戳
*/
enum cc_type { CC_LOCK, CC_OCC, CC_TO };