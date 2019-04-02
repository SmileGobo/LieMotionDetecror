#include "framedirwriter.h"
#include <QDir>
#include "debug.h"
#include <QDateTime>
#include <opencv2/highgui/highgui.hpp>
#include <exception.h>
FrameDirWriter::FrameDirWriter(const QString& base_path,QObject *parent):
    QThread(parent),m_base_path(base_path)
{

    //Debug(base_dir.dirName().toStdString());
}

void FrameDirWriter::Write(const FrameList& frames){
    m_frames=frames;
    m_path=MakeDirForSave();
    Debug("write files start");
    start();
}

void FrameDirWriter::run(){
    QString file_tmpl=m_path+"/img_",
            format=".jpg",
            file_name;
    emit WriteComplete(m_path);
    for (int i = 0; i < m_frames.size();i++) {
        file_name=file_tmpl+QString().sprintf("%08d",i)+format;
        //Debug(file_name.toStdString());
        cv::imwrite(file_name.toStdString(),m_frames[i]);
    }

}

QString  FrameDirWriter::MakeDirForSave(){
    QDir base_dir(m_base_path);
    QString dir_name=QString::number(QDateTime::currentDateTime().toTime_t());
    if(!base_dir.mkdir(dir_name)){
        throw Exception("err can't create save folder in FrameDirWriter::MakeDirForSave");
    }
    return base_dir.absolutePath()+"/"+dir_name;
}
