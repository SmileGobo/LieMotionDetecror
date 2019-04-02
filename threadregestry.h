#ifndef THREADREGESTRY_H
#define THREADREGESTRY_H

#include <QThread>
#include <QHash>
#include <QString>

typedef QHash<QString,QThread*> ThreadHash;

class ThreadNamedRegestry
{
    ThreadRegestry* GetInstance();
    void Register();
    QThread* GetNamedThread(const QString& name);
private:
    ThreadNamedRegestry();
    ~ThreadNamedRegestry();
    ThreadNamedRegestry* m_instance;
    ThreadHash m_threads;
};

#endif // THREADREGESTRY_H
