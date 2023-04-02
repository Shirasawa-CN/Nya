///===========================================================
/// 定义result
/// 函数通过返回result类型数据，丰富异常处理方式
///
/// return(Option(true,number,value,...)); OR
/// return(Option(false,number,value)); boolean_option:
/// 返回运行结果，成功true；失败false number: 返回值数量
/// ...(value)： 返回值
///
/// ex:
/// Result a(){
/// return(Option(true,number,value,...)); OR
/// return(Option(false,number,value));
/// }
///===========================================================
#pragma once

#include <stdarg.h>
#include <stddef.h>
#include <stdlib.h>

#define Result void*

#define usize unsigned long long
#define bool _Bool
#define true 1
#define false 0

void*
Option(bool boolean_optition, usize number, ...);
