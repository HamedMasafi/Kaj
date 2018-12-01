#ifndef ANDROIDJNIARRAYLIST_H
#define ANDROIDJNIARRAYLIST_H

#include <QtGlobal>
#include <jni.h>

QT_BEGIN_NAMESPACE

class AndroidJniArrayList
{
    jmethodID m_add_mathod;
    jobject m_array;

public:
    AndroidJniArrayList();
    AndroidJniArrayList(int size);
    void add(jobject obj);

    jobject handle();
};

QT_END_NAMESPACE

#endif // ANDROIDJNIARRAYLIST_H
