#ifndef QWORKERTHREAD_GLOBAL_H
#define QWORKERTHREAD_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(QWORKERTHREAD_LIBRARY)
#  define QWORKERTHREAD_EXPORT Q_DECL_EXPORT
#else
#  define QWORKERTHREAD_EXPORT Q_DECL_IMPORT
#endif

#endif // QWORKERTHREAD_GLOBAL_H
