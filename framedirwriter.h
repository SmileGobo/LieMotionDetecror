#ifndef FRAMEDIRWRITER_H
#define FRAMEDIRWRITER_H

#include <QThread>
#include "datatypes.h"
/**
"Сохранятель" списка кадров в дирректорию
**/
class FrameDirWriter : public QThread
{
Q_OBJECT
public:
    explicit FrameDirWriter(const QString& base_path=".",QObject *parent = 0);
public slots:
    void Write(const FrameList& frames);
signals:
    void WriteComplete(const QString path);
protected:
    void run();
private:
    QString MakeDirForSave();

    const QString m_base_path;
    //uint m_timestamp;
    QString m_path;
    FrameList m_frames;
};

#endif // FRAMEDIRWRITER_H
