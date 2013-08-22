#include "ReplayLoadingThread.h"
#include <QDirIterator>
#include "constants.h"

ReplayLoadingThread::ReplayLoadingThread(QString folder, int startFrom, QMap<QString, QString>*	vehicleNames, QObject *parent) : QThread(parent) {
	_toDelete = false;
	_folder = folder;
	_startFrom = startFrom;
	_replays = new QList<Replay*>();
	_vehicleNames = vehicleNames;
}

ReplayLoadingThread::~ReplayLoadingThread() {
	delete _replays;
}

void ReplayLoadingThread::run() {
	QDirIterator dirIterator(_folder, QDirIterator::Subdirectories);
	int counter = 0;
	while(dirIterator.hasNext()) {
		QString fileName = dirIterator.next();
		if(counter >= _startFrom && counter < _startFrom + REPLAYS_PER_THREAD) {
			if(fileName.right(REPLAY_FILE_EXT.length()) == REPLAY_FILE_EXT) {
				Replay *replay = new Replay(fileName, _vehicleNames);
				if(replay->load()) {
					_replays->append(replay);
				} else {
					delete replay;
				}
			}
		} else if(counter > _startFrom + REPLAYS_PER_THREAD) {
			break;
		}
		counter++;
	}
}
