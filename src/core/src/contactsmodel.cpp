#include "contactsmodel.h"

#ifdef Q_OS_ANDROID
#   include <QtAndroid>
#   include <QtAndroidExtras>
#   include <jni.h>
#endif

QList<ContactsModel::Contact*> ContactsModel::_contacts;

ContactsModel::ContactsModel(QObject *parent) : QAbstractListModel(parent)
{
#ifdef Q_OS_ANDROID
    QEventLoop loop;
    QtAndroid::requestPermissions(QStringList() << "android.permission.READ_CONTACTS", [&loop](const QtAndroid::PermissionResultMap &){
        loop.quit();
    });
    loop.exec();

    if (!_contacts.size())
        initData();
    beginInsertRows(QModelIndex(), _contacts.length(), _contacts.length());
    endInsertRows();
#endif
}

void ContactsModel::initData()
{
#ifdef Q_OS_ANDROID

    auto CONTENT_URI = QAndroidJniObject::getStaticObjectField("android/provider/ContactsContract$Contacts",
                                                               "CONTENT_URI",
                                                               "Landroid/net/Uri;");
    QAndroidJniObject cr = QtAndroid::androidActivity().callObjectMethod("getContentResolver",
                                                                         "()Landroid/content/ContentResolver;");

    auto cur = cr.callObjectMethod("query", "(Landroid/net/Uri;[Ljava/lang/String;Ljava/lang/String;[Ljava/lang/String;Ljava/lang/String;)Landroid/database/Cursor;",
                                   CONTENT_URI.object(),
                                   nullptr, nullptr, nullptr, nullptr);

    auto CONTENT_URI_PHONE = QAndroidJniObject::getStaticObjectField("android/provider/ContactsContract$CommonDataKinds$Phone",
                                                                     "CONTENT_URI",
                                                                     "Landroid/net/Uri;");

    QAndroidJniEnvironment env;
    jclass string = env->FindClass("java/lang/String");
    if (cur.isValid()) {
        while (true) {
            jboolean b = cur.callMethod<jboolean>("moveToNext");
            if (!b)
                break;

            auto index = cur.callMethod<jint>("getColumnIndex", "(Ljava/lang/String;)I",
                                              QAndroidJniObject::fromString("_id").object());
            auto id = cur.callObjectMethod("getString", "(I)Ljava/lang/String;", index);
            index = cur.callMethod<jint>("getColumnIndex", "(Ljava/lang/String;)I",
                                         QAndroidJniObject::fromString("display_name").object());
            auto name = cur.callObjectMethod("getString", "(I)Ljava/lang/String;", index);

            index = cur.callMethod<jint>("getColumnIndex", "(Ljava/lang/String;)I",
                                         QAndroidJniObject::fromString("has_phone_number").object());
            auto has_phone_number = cur.callMethod<jint>("getInt", "(I)I", index);


            auto contact = new Contact;
            if (has_phone_number) {
                auto where = QAndroidJniObject::fromString("contact_id=?");


                jobjectArray array = env->NewObjectArray(1, string, nullptr);
                env->SetObjectArrayElement(array, 0, id.object());

                auto curPhones = cr.callObjectMethod("query",
                                                     "(Landroid/net/Uri;[Ljava/lang/String;Ljava/lang/String;[Ljava/lang/String;Ljava/lang/String;)Landroid/database/Cursor;",
                                                     CONTENT_URI_PHONE.object(),
                                                     nullptr,
                                                     where.object(),
                                                     array,
                                                     nullptr);
                if (curPhones.isValid()) {
                    while (true) {
                        jboolean b = curPhones.callMethod<jboolean>("moveToNext");
                        if (!b)
                            break;
                        auto index = curPhones.callMethod<jint>("getColumnIndex", "(Ljava/lang/String;)I",
                                                                QAndroidJniObject::fromString("data1").object());
                        auto ph = curPhones.callObjectMethod("getString", "(I)Ljava/lang/String;", index);

                        index = curPhones.callMethod<jint>("getColumnIndex", "(Ljava/lang/String;)I",
                                                           QAndroidJniObject::fromString("data2").object());
                        auto type = curPhones.callMethod<jint>("getInt", "(I)I", index);
                        auto p = new Phone;
                        QVariantMap phmap;
                        p->phone = ph.toString();
                        p->type = static_cast<Type>(type);
                        p->typeName = typeToString(p->type);
                        contact->phones.append(p);
                    }
                }
            }

            contact->id = id.toString().toUInt();
            contact->name = name.toString();
            _contacts.append(contact);
        }
    }
#endif
}

QString ContactsModel::typeToString(const ContactsModel::Type &t) const
{
    switch (t) {
    case TYPE_HOME: return "Home";
    case TYPE_MOBILE: return "Mobile";
    case TYPE_WORK: return "Work";
    case TYPE_FAX_WORK: return "FaxWork";
    case TYPE_FAX_HOME: return "FaxHome";
    case TYPE_PAGER: return "Pager";
    case TYPE_OTHER: return "Other";
    case TYPE_CALLBACK: return "Callback";
    case TYPE_CAR: return "Car";
    case TYPE_COMPANY_MAIN: return "CompanyMain";
    case TYPE_ISDN: return "Isdn";
    case TYPE_MAIN: return "Main";
    case TYPE_OTHER_FAX: return "OtherFax";
    case TYPE_RADIO: return "Radio";
    case TYPE_TELEX: return "Telex";
    case TYPE_TTY_TDD: return "TtyTdd";
    case TYPE_WORK_MOBILE: return "WorkMobile";
    case TYPE_WORK_PAGER: return "WorkPager";
    case TYPE_ASSISTANT: return "Assistant";
    case TYPE_MMS: return "Mms";
    default: return "Custom";
    }
}

int ContactsModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return _contacts.count();
}

QVariant ContactsModel::data(const QModelIndex &index, int role) const
{
    //    if (role != Qt::DisplayRole)
    //        return QVariant();

    if (index.row() < 0 || index.row() >= _contacts.length())
        return QVariant();

    auto d = _contacts.at(index.row());

    switch (role) {
    case Qt::UserRole + 1:
        return d->id;
    case Qt::UserRole + 2:
        return d->name;
    case Qt::UserRole + 3: {
        QVariantList l;
        foreach (auto p, d->phones) {
            QVariantMap map;
            map.insert("type", p->typeName);
            map.insert("phone", p->phone);
            l.append(map);
        }
        return l;
    }
    case Qt::UserRole + 4:
        return d->phones.count();
    }
    return "*";
}

QHash<int, QByteArray> ContactsModel::roleNames() const
{
    QHash<int, QByteArray> r;
    r.insert(Qt::UserRole + 1, "id");
    r.insert(Qt::UserRole + 2, "name");
    r.insert(Qt::UserRole + 3, "phones");
    r.insert(Qt::UserRole + 4, "phones_count");
    return r;
}
