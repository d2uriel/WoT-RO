#include "replayTableWidget.h"
#include <QHeaderView>

ReplayTableWidget::ReplayTableWidget(int type, QWidget *parent) : QTableWidget(parent) {
	_type = type;
	retranslateTexts();
	this->setObjectName(TW_NAMES[_type]);
	_columnHeaders = new QMap<QString, int>();
	setupTable();
}

ReplayTableWidget::~ReplayTableWidget() {
	this->clear();
	_columnHeaders->clear();
	delete _columnHeaders;
}

void ReplayTableWidget::setupTable() {
	this->setSortingEnabled(false);

	QFont f = this->font();
	f.setPointSize(9);
	this->setFont(f);

	this->setSelectionMode(QTableWidget::ExtendedSelection);
	this->setSelectionBehavior(QTableWidget::SelectRows);

	this->horizontalHeader()->setMinimumSectionSize(25);
	this->horizontalHeader()->setDefaultSectionSize(80);
	this->horizontalHeader()->setCascadingSectionResizes(true);
	this->horizontalHeader()->setStretchLastSection(false);

	this->verticalHeader()->setMinimumSectionSize(20);
	this->verticalHeader()->setDefaultSectionSize(20);
	this->verticalHeader()->setCascadingSectionResizes(false);
	this->verticalHeader()->setStretchLastSection(false);

	int allColumnsWidth = setupColumns();
	this->setMinimumWidth(allColumnsWidth);
	this->setMinimumHeight(120);
	this->setGeometry(0, 0, allColumnsWidth, 120);
	this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

	this->horizontalHeader()->setSortIndicatorShown(true);
	this->horizontalHeader()->setSortIndicator(0, Qt::DescendingOrder);
	this->setSortingEnabled(true);
}

void ReplayTableWidget::retranslateTexts() {
	TEXT_VICTORY_TR = tr("Victory");
	TEXT_DEFEAT_TR = tr("Defeat");
	TEXT_YES_TR = tr("Yes");
	TEXT_NO_TR = tr("No");
}

void ReplayTableWidget::retranslateUi() {
	COLS.retranslateUi();
	setupColumns();
	retranslateTexts();
	for(int row = 0; row < this->rowCount(); row++) {
		Replay* r = this->replay(row);
		int cw_col = _columnHeaders->value(COLS.COL_CW);
		int res_col = _columnHeaders->value(COLS.COL_RESULT);
		QString cw = r->cw() == TEXT_YES ? TEXT_YES_TR : r->cw() == TEXT_NO ? TEXT_NO_TR : "";
		QString res = r->result() == TEXT_VICTORY ? TEXT_VICTORY_TR : r->result() == TEXT_DEFEAT ? TEXT_DEFEAT_TR : "";
		this->item(row, cw_col)->setData(Qt::EditRole, cw);
		this->item(row, res_col)->setData(Qt::EditRole, res);
	}
}

int ReplayTable::setupColumns() {
	for(int col = 0; col < this->columnCount(); col++) {
		delete this->horizontalHeaderItem(col);
	}
	_columnHeaders->clear();
	if(this->columnCount() != COLS[_type]->count()) {
		this->setColumnCount(COLS[_type]->count());
	}
	int allColumnsWidth = 0;
	for(TABLE_DATA::const_iterator it = COLS[_type]->begin(); it != COLS[_type]->end(); ++it) {
		Column c = it.value();
		QString columnName = c.name;
		QTableWidgetItem* h = new QTableWidgetItem(columnName);
		this->setHorizontalHeaderItem(c.order, h);
		this->setColumnWidth(c.order, c.width);
		allColumnsWidth += c.width;
		if(!c.visible) {
			this->hideColumn(c.order);
		}
		_columnHeaders->insert(columnName, c.order);
	}
	return allColumnsWidth;
}

TableItem* ReplayTableWidget::createTableItem(Replay* r) {
	TableItem* i = new TableItem(r);
	i->setFlags(i->flags() ^ Qt::ItemIsEditable);
	QColor c;
	if(r->result() == TEXT_VICTORY) {
		c.setRgb(210, 255, 210);
	} else if(r->result() == TEXT_DEFEAT) {
		c.setRgb(255, 210, 210);
	} else {
		c.setRgb(255, 255, 255);
	}
	i->setBackgroundColor(c);
	return i;
}

void ReplayTable::addReplay(Replay *r) {
	_replays.append(r);
	int row = this->rowCount();
	this->insertRow(row);
	for(int col = 0; col < this->columnCount(); col++) {
		QString columnName = this->horizontalHeaderItem(col)->text();
		TableItem* t = createTableItem(r);
		if(columnName == COLS.COL_CREDITS) {
			t->setData(Qt::EditRole, r->credits());
		} else if(columnName == COLS.COL_CW) {
			t->setData(Qt::EditRole, r->cw() == TEXT_YES ? TEXT_YES_TR : r->cw() == TEXT_NO ? TEXT_NO_TR : "");
		} else if(columnName == COLS.COL_DAM_DEALT) {
			t->setData(Qt::EditRole, r->damageDealt());
		} else if(columnName == COLS.COL_DAM_RECIEVED) {
			t->setData(Qt::EditRole, r->damageReceived());
		} else if(columnName == COLS.COL_DATETIME) {
			t->setData(Qt::EditRole, r->dateTime());
		} else if(columnName == COLS.COL_ENEMY_CLAN) {
			t->setData(Qt::EditRole, r->enemyClan());
		} else if(columnName == COLS.COL_EXP) {
			t->setData(Qt::EditRole, r->exp());
		} else if(columnName == COLS.COL_SINGLE_EXP) {
			t->setData(Qt::EditRole, r->singleExp());
		} else if(columnName == COLS.COL_FRAGS) {
			t->setData(Qt::EditRole, r->frags());
		} else if(columnName == COLS.COL_MAP) {
			t->setData(Qt::EditRole, r->map());
		} else if(columnName == COLS.COL_PLAYER) {
			t->setData(Qt::EditRole, r->player());
		} else if(columnName == COLS.COL_RESULT) {
			t->setData(Qt::EditRole, r->result() == TEXT_VICTORY ? TEXT_VICTORY_TR : r->result() == TEXT_DEFEAT ? TEXT_DEFEAT_TR : "");
		} else if(columnName == COLS.COL_SCORE) {
			t->setData(Qt::EditRole, r->score());
		} else if(columnName == COLS.COL_VEHICLE) {
			t->setData(Qt::EditRole, r->vehicle());
		} else if(columnName == COLS.COL_ID) {
			t->setData(Qt::EditRole, r->path());
		}
		this->setItem(row, col, t);
	}
}

Replay* ReplayTableWidget::replay(int row) {
	return ((TableItem*)item(row, 0))->replay();
}

void ReplayTableWidget::moveReplay(int row, ReplayTableWidget *t) {
	Replay* r = _replays.takeAt(_replays.indexOf(this->replay(row)));
	for(int col = 0; col < this->columnCount(); col++) {
		delete this->takeItem(row, col);
	}
	this->removeRow(row);
	t->addReplay(r);
}

QList<Replay*> ReplayTableWidget::moveCwReplays(ReplayTableWidget *cw) {
	QList<Replay*> replaysToMove;
	for(int row = 0; row < this->rowCount(); row++) {
		Replay* r = this->replay(row);
		if(r->cw() == "Yes") {
			replaysToMove.append(r);
			this->moveReplay(row, cw);
			row--;
		}
	}
	return replaysToMove;
}

QList<Replay*> ReplayTableWidget::moveSelected(ReplayTableWidget *dest) {
	QList<int> rows = this->selectedRows();
	QList<Replay*> replaysToMove;
	for(int i = 0; i < rows.count(); i++) {
		replaysToMove.append(this->replay(rows[i]));
		this->moveReplay(rows[i], dest);
	}
	return replaysToMove;
}

QList<int> ReplayTableWidget::selectedRows() {
	QList<int> rows;
	QList<QTableWidgetItem*> selection = this->selectedItems();
	for(int i = 0; i < selection.count(); i++) {
		if(!rows.contains(selection[i]->row())) {
			rows.append(selection[i]->row());
		}
	}
	return rows;
}

QList<Replay*> ReplayTableWidget::selectedReplays() {
	QList<Replay*> replays;
	QList<QTableWidgetItem*> selection = this->selectedItems();
	for(int i = 0; i < selection.count(); i++) {
		TableItem* t = (TableItem*)selection[i];
		if(!replays.contains(t->replay())) {
			replays.append(t->replay());
		}
	}
	return replays;
}

Replay* ReplayTableWidget::currentReplay() {
	QList<Replay*> replays = this->selectedReplays();
	if(replays.count() == 0 || replays.count() > 1) {
		return new Replay();
	} else {
		return replays[0];
	}
}

void ReplayTableWidget::clear() {
	while(this->rowCount() > 0) {
		for(int i = 0; i < this->columnCount(); i++) {
			delete this->takeItem(0, i);
		}
		this->removeRow(0);
		if(!_replays.isEmpty()) {
			delete _replays.takeFirst();
		}
	}
}

void ReplayTableWidget::removeReplay(int row) {
	Replay* r = _replays.takeAt(_replays.indexOf(this->replay(row)));
	for(int col = 0; col < this->columnCount(); col++) {
		delete this->takeItem(row, col);
	}
	this->removeRow(row);
	delete r;
}

QList<QString> ReplayTableWidget::removeIncomplete() {
	QList<QString> replaysToRemove;
	for(int row = 0; row < this->rowCount(); row++) {
		Replay* r = this->replay(row);
		if(r->isIncomplete()) {
			replaysToRemove.append(r->path());
			this->removeReplay(row);
			row--;
		}
	}
	return replaysToRemove;
}

QList<QString> ReplayTableWidget::removeSelected() {
	QList<int> rows = this->selectedRows();
	QList<QString> replaysToRemove;
	for(int i = 0; i < rows.count(); i++) {
		Replay* r = this->replay(rows[i]);
		replaysToRemove.append(r->path());
		this->removeReplay(rows[i]);
	}
	return replaysToRemove;
}
