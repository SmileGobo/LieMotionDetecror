#include "motionlogger.h"
#include "debug.h"
#include <QSqlQuery>
#include <QSqlRecord>
MotionLogger::MotionLogger(const QString &dbname,const QString& table_name)
    :QObject(),m_DB_NAME(dbname),m_TABLE_NAME(table_name){
    m_data=0;
    m_model=0;
}
MotionLogger::~MotionLogger(){
   delete m_data;
   delete m_model;
}

void MotionLogger::RegisterMotion(){
   m_data=new MotionData();
}

void MotionLogger::Log(const QString& path){
    if (m_data==0){
        return;
    }
    Debug("Log!!!");
    m_data->m_imgdir=path;
    Write2DB(*m_data);
    delete m_data;
    m_data=0; //на всякий случай
}
//запись в базу
void MotionLogger::Write2DB(const MotionData &data){
    QSqlRecord new_rec=m_model->record ();
    new_rec.setValue("timestamp",data.time_stamp);
    new_rec.setValue("framesdir",data.m_imgdir);
    if(!m_model->insertRecord(-1,new_rec)){
        throw Exception("Error while add rec db MotionLogger::Write2DB");
    }
     if(!m_model->submitAll()){
          Debug(m_model->lastError().text().toStdString());
          throw Exception("Error while commit rec db MotionLogger::Write2DB");
     }
     Debug(m_model->tableName().toStdString());
    Debug("rec add and commit!");
    //регистрация движения завершена
   // m_motion_registred=false;
}

QSqlTableModel* MotionLogger::CreateModel(const QString& table_name,const QSqlDatabase& db){
    QSqlTableModel *model=new QSqlTableModel(0,db);
    QSqlQuery query(m_db);
    const QString sql="create table if not exists "+table_name+"(id integer Primary Key autoincrement,timestamp int8 not null,framesdir text not null)";
    if (!query.exec(sql)){
        throw Exception("Ошибка создания таблицы"+table_name.toStdString()+" в"+db.databaseName().toStdString()+"in method MotionLogger::CreateModel()");
    }

    model->setTable(table_name);
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    model->select();
    return model;
}
QSqlDatabase MotionLogger::CreateDatabase(const QString& db_name){
    const QString DATABASE_TYPE("QSQLITE");
    QSqlDatabase db=QSqlDatabase::addDatabase( DATABASE_TYPE);
    db.setDatabaseName(db_name);
    if (!db.open()){
        throw Exception("Ошибка открытия бд"+db_name.toStdString()+"in method MotionLogger::CreateDatabase()");
    }
    return db;
}

void MotionLogger::Init(){
    m_db=CreateDatabase(m_DB_NAME);
    m_model=CreateModel(m_TABLE_NAME,m_db);
}


