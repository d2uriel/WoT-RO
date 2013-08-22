#ifndef ReplayLoadingThread_H
#define ReplayLoadingThread_H

#include <QThread>
#include "replay.h"
#include <QList>
#include <QMap>
#include <QDebug>
#include "replayLoadingThread.h"

class ReplayLoadingThread : public QThread {
	Q_OBJECT

public:
	explicit ReplayLoadingThread(QString folder, int startFrom, QMap<QString, QString>*	vehicleNames, QObject *parent = 0);
	~ReplayLoadingThread();
	QList<Replay*>* replays() { return _replays; }
	QString folder() { return _folder; }
	void setToDelete() { _toDelete = true; }
	bool toDelete() { return _toDelete; }
	
signals:
	void replaysLoaded(const QList<Replay*> _replays);

private:
	bool _toDelete;
	QString _folder;
	int _startFrom;
	QList<Replay*>* _replays;
	QMap<QString, QString>*	_vehicleNames;

protected:
	virtual void run();
};

#endif // ReplayLoadingThread_H
