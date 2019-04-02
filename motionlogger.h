#ifndef MOTIONLOGGER_H
#define MOTIONLOGGER_H

#include <QObject>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlTableModel>


//#include <opencv2/core/core.hpp>

//#include <opencv2/highgui/highgui.hpp>
#include <QDateTime>
#include "datatypes.h"
#include "exception.h"
#include "framedirwriter.h"
#include "framesaver.h"
/**
Данные по сохраняемым кадрам
**/
struct MotionData{
    QString m_imgdir;
    const uint time_stamp; //базовое время
    const uint m_camid;  //не используеться
    MotionData(const QString& imgdir="",const uint camid=0):
            m_imgdir(imgdir),
            time_stamp(QDateTime::currentDateTime().toTime_t()),
            m_camid(camid)
    {};
};

/**
Класс логгирования детекции движений
регистрация времени начала движения
запись данных базу.
**/

class MotionLogger : public QObject
{
Q_OBJECT
public:
    explicit MotionLogger(const QString &dbname,const QString& table_name);
    void Init(); /*throw(Exception); DBException, LogicalException*/

    virtual ~MotionLogger();
public slots:
    //void MotionDetected(const RectList& rects,const cv::Mat& frame);
    void Log(const QString& path);
    void RegisterMotion();
private:
    MotionLogger& operator=(const MotionLogger& ctor){return *this;};
    MotionLogger(const MotionLogger& copy):QObject(){};

    const QString m_DB_NAME;
    const QString m_TABLE_NAME;

    //int  register_timestamp;
    QSqlDatabase m_db;
    QSqlTableModel *m_model;
    MotionData* m_data;
    void Write2DB(const MotionData &data);

    QSqlTableModel* CreateModel(const QString& table_name,const QSqlDatabase& db);
    QSqlDatabase CreateDatabase(const QString& db_name);
};

#endif // MOTIONLOGGER_H
