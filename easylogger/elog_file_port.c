/*
 * This file is part of the EasyLogger Library.
 *
 * Copyright (c) 2015-2019, Qintl, <qintl_linux@163.com>
 *
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the
 * 'Software'), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED 'AS IS', WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
 * CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
 * TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
 * SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 * Function:  Portable interface for EasyLogger's file log pulgin.
 * Created on: 2019-01-05
 */

#include "elog_file.h"

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

// 定义互斥锁
static pthread_mutex_t log_mutex = PTHREAD_MUTEX_INITIALIZER;

/**
 * EasyLogger flile log pulgin port initialize
 *
 * @return result
 */
ElogErrCode elog_file_port_init(void)
{
    ElogErrCode result = ELOG_NO_ERR;

    // 尝试为互斥锁进行初始化，如果已经初始化则不需要再次初始化
    if (pthread_mutex_trylock(&log_mutex) != 0) {
        // 如果不能获取锁（已经被其他线程获取），则尝试初始化
        if (pthread_mutex_init(&log_mutex, NULL) != 0) {
            result = -1;
        }
    } else {
        // 如果成功获取锁，则解锁并返回无错误
        pthread_mutex_unlock(&log_mutex);
    }

    return result;
}

/**
 * file log lock
 */
void elog_file_port_lock(void)
{
    // 加锁以确保日志操作是线程安全的
    pthread_mutex_lock(&log_mutex);
}

/**
 * file log unlock
 */
void elog_file_port_unlock(void)
{
    // 解锁以允许其他线程操作日志
    pthread_mutex_unlock(&log_mutex);
}

/**
 * file log deinit
 */
void elog_file_port_deinit(void)
{
    // 销毁互斥锁
    pthread_mutex_destroy(&log_mutex);
}
