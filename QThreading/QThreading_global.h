#ifndef QTHREADING_GLOBAL_H
#define QTHREADING_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(QTHREADING_LIBRARY)
#  define QTHREADING_EXPORT Q_DECL_EXPORT
#else
#  define QTHREADING_EXPORT Q_DECL_IMPORT
#endif

#endif // QTHREADING_GLOBAL_H
