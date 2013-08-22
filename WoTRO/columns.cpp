#include "columns.h"
#include "constants.h"

Column::Column(QString n, int w, int o, bool v) {
	name = n;
	width = w;
	visible = v;
	order = o;
}

Columns::Columns() {
	_wotTableColumns = new QMap<QString, Column>();
	_favTableColumns = new QMap<QString, Column>();
	_cwTableColumns = new QMap<QString, Column>();
	retranslateUi();
}

Columns::~Columns() {
	_wotTableColumns->clear();
	_favTableColumns->clear();
	_cwTableColumns->clear();
	delete _wotTableColumns;
	delete _favTableColumns;
	delete _cwTableColumns;
}

void Columns::retranslateUi() {
	_wotTableColumns->clear();
	_favTableColumns->clear();
	_cwTableColumns->clear();
	setupColumnNames();
	setupColumns();
	setupTables();
	_tableColumns.insert(TW_WOT, _wotTableColumns);
	_tableColumns.insert(TW_FAV, _favTableColumns);
	_tableColumns.insert(TW_CW, _cwTableColumns);
}

const QMap<QString, Column>* Columns::operator [] (const int table) {
	if(table == TW_WOT) {
		return _wotTableColumns;
	} else if(table == TW_FAV) {
		return _favTableColumns;
	} else { // TW_CW
		return _cwTableColumns;
	}
}

void Columns::setupColumnNames() {
	COL_CREDITS = tr("Credits");
	COL_CW = tr("Is CW?");
	COL_DAM_DEALT = tr("Damage dealt");
	COL_DAM_RECIEVED = tr("Damage received");
	COL_DATETIME = tr("Date & time");
	COL_ENEMY_CLAN = tr("Enemy clan");
	COL_EXP = tr("Exp");
	COL_FRAGS = tr("Frags");
	COL_ID = tr("id");
	COL_MAP = tr("Map");
	COL_PLAYER = tr("Player");
	COL_RESULT = tr("Battle result");
	COL_SCORE = tr("Score");
	COL_SINGLE_EXP = tr("Single exp");
	COL_VEHICLE = tr("Vehicle");
}

void Columns::setupColumns() {
	_columns.insert(COL_CREDITS, Column(COL_CREDITS, 60));
	_columns.insert(COL_CW, Column(COL_CW, 80));
	_columns.insert(COL_DAM_DEALT, Column(COL_DAM_DEALT, 130));
	_columns.insert(COL_DAM_RECIEVED, Column(COL_DAM_RECIEVED, 130));
	_columns.insert(COL_DATETIME, Column(COL_DATETIME, 120));
	_columns.insert(COL_ENEMY_CLAN, Column(COL_ENEMY_CLAN, 120));
	_columns.insert(COL_EXP, Column(COL_EXP, 100));
	_columns.insert(COL_FRAGS, Column(COL_FRAGS, 40));
	_columns.insert(COL_ID, Column(COL_ID, 50));
	_columns.insert(COL_MAP, Column(COL_MAP, 120));
	_columns.insert(COL_PLAYER, Column(COL_PLAYER, 120));
	_columns.insert(COL_RESULT, Column(COL_RESULT, 80));
	_columns.insert(COL_SCORE, Column(COL_SCORE, 80));
	_columns.insert(COL_SINGLE_EXP, Column(COL_SINGLE_EXP, 100));
	_columns.insert(COL_VEHICLE, Column(COL_VEHICLE, 120));
}

void Columns::setupTables() {
	_wotTableColumns->insert(COL_DATETIME, Column(_columns[COL_DATETIME], _wotTableColumns->count()));
	_wotTableColumns->insert(COL_PLAYER, Column(_columns[COL_PLAYER], _wotTableColumns->count()));
	_wotTableColumns->insert(COL_MAP, Column(_columns[COL_MAP], _wotTableColumns->count()));
	_wotTableColumns->insert(COL_VEHICLE, Column(_columns[COL_VEHICLE], _wotTableColumns->count()));
	_wotTableColumns->insert(COL_RESULT, Column(_columns[COL_RESULT], _wotTableColumns->count()));
	_wotTableColumns->insert(COL_SCORE, Column(_columns[COL_SCORE], _wotTableColumns->count()));
	_wotTableColumns->insert(COL_FRAGS, Column(_columns[COL_FRAGS], _wotTableColumns->count()));
	_wotTableColumns->insert(COL_SINGLE_EXP, Column(_columns[COL_SINGLE_EXP], _wotTableColumns->count()));
	_wotTableColumns->insert(COL_EXP, Column(_columns[COL_EXP], _wotTableColumns->count()));
	_wotTableColumns->insert(COL_CREDITS, Column(_columns[COL_CREDITS], _wotTableColumns->count()));
	_wotTableColumns->insert(COL_DAM_DEALT, Column(_columns[COL_DAM_DEALT], _wotTableColumns->count()));
	_wotTableColumns->insert(COL_DAM_RECIEVED, Column(_columns[COL_DAM_RECIEVED], _wotTableColumns->count()));
	_wotTableColumns->insert(COL_CW, Column(_columns[COL_CW], _wotTableColumns->count()));
	_wotTableColumns->insert(COL_ENEMY_CLAN, Column(_columns[COL_ENEMY_CLAN], _wotTableColumns->count(), false));
	_wotTableColumns->insert(COL_ID, Column(_columns[COL_ID], _wotTableColumns->count(), false));

	_favTableColumns->insert(COL_DATETIME, Column(_columns[COL_DATETIME], _favTableColumns->count()));
	_favTableColumns->insert(COL_PLAYER, Column(_columns[COL_PLAYER], _favTableColumns->count()));
	_favTableColumns->insert(COL_MAP, Column(_columns[COL_MAP], _favTableColumns->count()));
	_favTableColumns->insert(COL_VEHICLE, Column(_columns[COL_VEHICLE], _favTableColumns->count()));
	_favTableColumns->insert(COL_RESULT, Column(_columns[COL_RESULT], _favTableColumns->count()));
	_favTableColumns->insert(COL_SCORE, Column(_columns[COL_SCORE], _favTableColumns->count()));
	_favTableColumns->insert(COL_FRAGS, Column(_columns[COL_FRAGS], _favTableColumns->count()));
	_favTableColumns->insert(COL_SINGLE_EXP, Column(_columns[COL_SINGLE_EXP], _favTableColumns->count()));
	_favTableColumns->insert(COL_EXP, Column(_columns[COL_EXP], _favTableColumns->count()));
	_favTableColumns->insert(COL_CREDITS, Column(_columns[COL_CREDITS], _favTableColumns->count()));
	_favTableColumns->insert(COL_DAM_DEALT, Column(_columns[COL_DAM_DEALT], _favTableColumns->count()));
	_favTableColumns->insert(COL_DAM_RECIEVED, Column(_columns[COL_DAM_RECIEVED], _favTableColumns->count()));
	_favTableColumns->insert(COL_CW, Column(_columns[COL_CW], _favTableColumns->count()));
	_favTableColumns->insert(COL_ENEMY_CLAN, Column(_columns[COL_ENEMY_CLAN], _favTableColumns->count(), false));
	_favTableColumns->insert(COL_ID, Column(_columns[COL_ID], _favTableColumns->count(), false));

	_cwTableColumns->insert(COL_MAP, Column(_columns[COL_MAP], _cwTableColumns->count()));
	_cwTableColumns->insert(COL_ENEMY_CLAN, Column(_columns[COL_ENEMY_CLAN], _cwTableColumns->count()));
	_cwTableColumns->insert(COL_RESULT, Column(_columns[COL_RESULT], _cwTableColumns->count()));
	_cwTableColumns->insert(COL_SCORE, Column(_columns[COL_SCORE], _cwTableColumns->count()));
	_cwTableColumns->insert(COL_DATETIME, Column(_columns[COL_DATETIME], _cwTableColumns->count()));
	_cwTableColumns->insert(COL_PLAYER, Column(_columns[COL_PLAYER], _cwTableColumns->count()));
	_cwTableColumns->insert(COL_VEHICLE, Column(_columns[COL_VEHICLE], _cwTableColumns->count()));
	_cwTableColumns->insert(COL_FRAGS, Column(_columns[COL_FRAGS], _cwTableColumns->count()));
	_cwTableColumns->insert(COL_SINGLE_EXP, Column(_columns[COL_SINGLE_EXP], _cwTableColumns->count()));
	_cwTableColumns->insert(COL_EXP, Column(_columns[COL_EXP], _cwTableColumns->count()));
	_cwTableColumns->insert(COL_CREDITS, Column(_columns[COL_CREDITS], _cwTableColumns->count()));
	_cwTableColumns->insert(COL_DAM_DEALT, Column(_columns[COL_DAM_DEALT], _cwTableColumns->count()));
	_cwTableColumns->insert(COL_DAM_RECIEVED, Column(_columns[COL_DAM_RECIEVED], _cwTableColumns->count()));
	_cwTableColumns->insert(COL_CW, Column(_columns[COL_CW], _cwTableColumns->count(), false));
	_cwTableColumns->insert(COL_ID, Column(_columns[COL_ID], _cwTableColumns->count(), false));
}
