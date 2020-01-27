#ifndef CONTACTSMODEL_H
#define CONTACTSMODEL_H

#include <QAbstractListModel>

class ContactsModel : public QAbstractListModel
{
    Q_OBJECT

    enum Type {
        TYPE_HOME = 1,
        TYPE_MOBILE = 2,
        TYPE_WORK = 3,
        TYPE_FAX_WORK = 4,
        TYPE_FAX_HOME = 5,
        TYPE_PAGER = 6,
        TYPE_OTHER = 7,
        TYPE_CALLBACK = 8,
        TYPE_CAR = 9,
        TYPE_COMPANY_MAIN = 10,
        TYPE_ISDN = 11,
        TYPE_MAIN = 12,
        TYPE_OTHER_FAX = 13,
        TYPE_RADIO = 14,
        TYPE_TELEX = 15,
        TYPE_TTY_TDD = 16,
        TYPE_WORK_MOBILE = 17,
        TYPE_WORK_PAGER = 18,
        TYPE_ASSISTANT = 19,
        TYPE_MMS = 20,
    };

    struct Phone {
        Type type;
        QString typeName;
        QString phone;
    };

    struct Contact {
        int id;
        QString name;
        QList<Phone*> phones;

        ~Contact() {
            qDeleteAll(phones);
        }
    };


    static QList<Contact*> _contacts;

public:
    ContactsModel(QObject *parent = nullptr);

private:
    void initData();
QString typeToString(const Type &t)const;
    // QAbstractItemModel interface
public:
    int rowCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    QHash<int, QByteArray> roleNames() const;
};

#endif // CONTACTSMODEL_H
