#ifndef REPLAYTABLEWIDGET_H
#define REPLAYTABLEWIDGET_H

#include <QTableWidget>
#include "constants.h"
#include "replay.h"
#include "replayTableItem.h"
#include "columns.h"

extern QString COL_CREDITS;
extern QString COL_CW;
extern QString COL_DAM_DEALT;
extern QString COL_DAM_RECIEVED;
extern QString COL_DATETIME;
extern QString COL_ENEMY_CLAN;
extern QString COL_EXP;
extern QString COL_FRAGS;
extern QString COL_MAP;
extern QString COL_PLAYER;
extern QString COL_RESULT;
extern QString COL_SCORE;
extern QString COL_SINGLE_EXP;
extern QString COL_VEHICLE;
extern QString COL_ID;

class ReplayTableWidget : public QTableWidget {
	Q_OBJECT

public:
	ReplayTableWidget(int type, QWidget *parent = 0);
	~ReplayTableWidget();

	// Methods
	void					addReplay(Replay* r);
	QList<Replay*>		moveCwReplays(ReplayTableWidget* cw);
	QList<Replay*>		moveSelected(ReplayTableWidget* dest);
	QList<QString>			removeSelected();
	QList<QString>			removeIncomplete();
	void					clear();
	void				retranslateUi();

	// Setters
	void					setType(int type)	{ _type = type; }

	// Getters
	QMap<QString, int>*		columnHeaders()		{ return _columnHeaders; }
	int						type()				{ return _type; }
	Replay*				replay(int row);
	QList<int>				selectedRows();
	QList<Replay*>		selectedReplays();
	Replay*				currentReplay();

signals:
	
public slots:

private:
	void					setupTable();
	int						setupColumns();
	TableItem*				createTableItem(Replay* r);
	void					moveReplay(int row, ReplayTableWidget* t);
	void					removeReplay(int row);
	void					retranslateTexts();

	Columns					COLS;
	int						_type;
	QMap<QString, int>*		_columnHeaders;
	QList<Replay*>			_replays;
	QString					TEXT_VICTORY_TR;
	QString					TEXT_DEFEAT_TR;
	QString					TEXT_YES_TR;
	QString					TEXT_NO_TR;
};

typedef ReplayTableWidget ReplayTable;

#endif // REPLAYTABLEWIDGET_H
