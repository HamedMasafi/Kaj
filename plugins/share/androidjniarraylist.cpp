#include "androidjniarraylist.h"

#include <QAndroidJniEnvironment>

QT_BEGIN_NAMESPACE

AndroidJniArrayList::AndroidJniArrayList()
{
    QAndroidJniEnvironment env;
    jclass arrayList = env->FindClass("java/util/ArrayList");
    jmethodID init = env->GetMethodID(arrayList, "<init>", "()V");
    m_add_mathod = env->GetMethodID(arrayList, "add", "(Ljava/lang/Object;)Z");
    m_array = env->NewObject(arrayList, init);
}

AndroidJniArrayList::AndroidJniArrayList(int size)
{
    QAndroidJniEnvironment env;
    jclass arrayList = env->FindClass("java/util/ArrayList");
    jmethodID init = env->GetMethodID(arrayList, "<init>", "(I)V");
    m_add_mathod = env->GetMethodID(arrayList, "add", "(Ljava/lang/Object;)Z");
    m_array = env->NewObject(arrayList, init, size);
}

void AndroidJniArrayList::add(jobject obj)
{
    QAndroidJniEnvironment env;
    env->CallBooleanMethod(m_array, m_add_mathod, obj);
}

jobject AndroidJniArrayList::handle()
{
    return m_array;
}

QT_END_NAMESPACE
