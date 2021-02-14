#ifndef NOTIFIER_H
#define NOTIFIER_H

#include <QObject>
#include <QHash>
#include <QList>
enum NotifyMessageFlag
{
    NM_HIDE=1,
    NM_PROCESS=2,
    NM_INFO=4,
    NM_OK=8,
    NM_SHOWCANCEL = 16,
    NM_ERROR = 32,
    NM_DARKNESS_BACK = 64
};

class NotifyInterface
{
public:
    using CancelCallBack = void(*)(NotifyInterface *);
    virtual void showMessage(const QString &content, int flag) = 0;
    void setCancelCallBack(CancelCallBack cb){ ccb = cb; }
    void setType(int type) {nTypeFlag = type; }
    int getType() const {return nTypeFlag; }
protected:
    CancelCallBack ccb = nullptr;
private:
    int nTypeFlag = 0;
};

class Notifier : public QObject
{
    Q_OBJECT
public:
    enum NotifyType
    {
        LIST_NOTIFY = 1,
        PLAYER_NOTIFY = 2,
        LIBRARY_NOTIFY = 3,
        DOWNLOAD_NOTIFY = 4
    };
    void addNotify(NotifyType nType, NotifyInterface *notify);
    void showMessage(NotifyType nType, const QString &content, int flag = 0);
    static Notifier *getNotifier();

signals:
    void cancelTrigger(int nTypeFlag);
private:
    explicit Notifier(QObject *parent = nullptr);
    QHash<NotifyType, QList<NotifyInterface *>> notifyHash;
    static void cancelCallBack(NotifyInterface *notify);
};

#endif // NOTIFIER_H
