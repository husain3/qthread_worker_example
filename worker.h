#ifndef WORKER_H
#define WORKER_H

#include <QObject>
#include <QDebug>
#include <QThread>
#include <unistd.h>
#include <QUdpSocket>
#include "myudp.h"


class Worker: public QObject {
    Q_OBJECT
public:
    Worker(QString &data) : mData(data) {

    }

public slots:
    void process() {
        // create a QUDP socket

        qDebug() << "Process's Thread : " << QThread::currentThreadId();

        for (int var = 0; var < 5; ++var) {
            mData = QString::number(var);
            sleep(1);
            emit processFinished();
        }


    }

signals:
    void processFinished();

private:
    QString &mData;
};

class WorkerInterface : public QObject {
    Q_OBJECT
    Q_PROPERTY(QString data READ getData NOTIFY dataChanged)
public:
    WorkerInterface() : mWorker(mData) {
        mWorker.moveToThread(&mThread);

        connect(this, &WorkerInterface::process, &mWorker, &Worker::process);

        connect(&mWorker, &Worker::processFinished, [this]{
            qDebug() << "ProcessFinished in  : " << QThread::currentThreadId();
            emit dataChanged();
        });

        mThread.start();
    }

    QString getData() const {
        return mData;
    }

    ~WorkerInterface() {
        mThread.exit();
        mThread.wait();
    }

signals:
    void dataChanged();
    void process();

private:
    QThread mThread;
    QString mData;
    Worker mWorker;
};

#endif // WORKER_H
