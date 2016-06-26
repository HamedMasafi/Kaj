#ifndef UNITS_H
#define UNITS_H

#include <QObject>
#include <kajglobal.h>

QT_BEGIN_NAMESPACE

class KAJ_EXPORT Units : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int virtualDpi READ virtualDpi WRITE setVirtualDpi NOTIFY virtualDpiChanged)


    int m_virtualDpi;

public:
    explicit Units(QObject *parent = 0);

    Q_INVOKABLE QString screenName() const;

    Q_INVOKABLE qreal dp(int number);
    Q_INVOKABLE int sp(int number);
    Q_INVOKABLE int pt(int number);
    Q_INVOKABLE qreal mm(int number);
    Q_INVOKABLE qreal in(int number);
    Q_INVOKABLE qreal cm(int number);

    int virtualDpi() const;

signals:

    void virtualDpiChanged(int arg);

public slots:
    void setVirtualDpi(int arg);
};

QT_END_NAMESPACE

#endif // UNITS_H
