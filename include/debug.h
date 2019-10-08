#ifndef _DEBUG_H
#define _DEBUG_H

#include "log.h"
#if INFO
#define LOG print
#define FLOG fprint
#define LOGUCHAR print_uchar_array
#define FLOGUCHAR fprint_uchar_array
#else
#define LOG print_null
#define FLOG fprint_null
#define LOGUCHAR print_null_uchar_array
#define FLOGUCHAR fprint_null_uchar_array
#endif

#endif  //_DEBUG_H