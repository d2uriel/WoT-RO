#ifndef TABLEITEM_H
#define TABLEITEM_H

#include <QObject>
#include <QTableWidgetItem>
#include "replay.h"

class ReplayTableItem : public QObject, public QTableWidgetItem {
	Q_OBJECT

public:
	ReplayTableItem(Replay* replay);
	Replay* replay() { return _replay; }
	
signals:
	
public slots:

private:
	Replay*	_replay;
	
};

typedef ReplayTableItem TableItem;

#endif // TABLEITEM_H
