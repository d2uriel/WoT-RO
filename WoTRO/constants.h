#ifndef CONSTANTS_H
#define CONSTANTS_H
#include <QMap>

const QString VERSION = "1.1";

const int WOT_TABLE_WIDGET	 = 1;
const int FAV_TABLE_WIDGET	 = 2;
const int CW_TABLE_WIDGET	 = 4;
const int ALL_TABLE_WIDGETS	 = 8;

const int GROUPING_FR = 1;
const int GROUPING_CW = 2;

const int REPLAYS_PER_THREAD = 10;

const int TW_WOT = 1;
const int TW_FAV = 2;
const int TW_CW = 4;

const QString TW_WOT_OBJ_NAME = "wotReplayTable";
const QString TW_FAV_OBJ_NAME = "favReplayTable";
const QString TW_CW_OBJ_NAME = "favReplayTable";

static QMap<int, QString> TW_DATA_STATIC() {
	QMap<int, QString> map;
	map.insert(TW_WOT, TW_WOT_OBJ_NAME);
	map.insert(TW_FAV, TW_FAV_OBJ_NAME);
	map.insert(TW_CW, TW_CW_OBJ_NAME);
	return map;
}
static const QMap<int, QString> TW_NAMES = TW_DATA_STATIC();

const QString VEHICLE_INFO_FILE_NAME = "VehicleInfo.json";
const QString SETTINGS_FILE_NAME = "settings.ini";
const QString REPLAY_FILE_EXT = ".wotreplay";
const QString COMMENT_FILE_EXT = ".comment";
const QString S_WINDOW = "Window";
const QString S_STATE = "State";
const QString S_WOT_FOLDER = "WoT_Folder";
const QString S_FAV_FOLDER = "Fav_folder";
const QString S_CW_FOLDER = "CW_folder";
const QString S_FAV_GROUPING = "Fav_grouping";
const QString S_CW_GROUPING = "CW_grouping";
const QString S_AUTO_MOVE_CW = "Auto_move_CW_replays";
const QString S_AUTO_RESIZE = "Auto_resize_columns";
const QString S_AUTO_SORT = "Auto_sort_replays";
const QString S_LANGUAGE = "Language";
const QString S_TAB_WIDGET = "Tabs";

const QString PATTERN_VEHICLE = "[vehicle]";
const QString PATTERN_MAP = "[map]";
const QString PATTERN_CLAN = "[clan]";
const QString PATTERN_FRAGS = "[frags]";
const QString PATTERN_DATE = "[date]";
const QString PATTERN_TIME = "[time]";

const QString TEXT_VICTORY = "Victory";
const QString TEXT_DEFEAT = "Defeat";
const QString TEXT_YES = "Yes";
const QString TEXT_NO = "No";

const qint64 descriptionJsonOffset = 12;
const qint64 DESCRIPTION_JSON_SIZE_OFFSET = 8;
const qint64 additionalInfoJsonOffset = 6;
const qint64 endOfBattleJsonOffset = 2;

/*

class COLUMN_DATA {
public:
	QString name;
	int width;
	bool hidden;
	int order;

	COLUMN_DATA(QString n, int w, bool h, int o) {
		name = n; width = w; hidden = h; order = o;
	}
};

const QString COLUMN_CREDITS = "Credits";
const QString COLUMN_CW = "Is CW?";
const QString COLUMN_DAMAGE_DEALT = "Damage dealt";
const QString COLUMN_DAMAGE_RECEIVED = "Damage received";
const QString COLUMN_DATETIME = "Date & time";
const QString COLUMN_ENEMY_CLAN = "Enemy clan";
const QString COLUMN_EXP = "Exp";
const QString COLUMN_FRAGS = "Frags";
const QString COLUMN_MAP = "Map";
const QString COLUMN_PLAYER = "Player";
const QString COLUMN_RESULT = "Battle result";
const QString COLUMN_SCORE = "Score";
const QString COLUMN_SINGLE_EXP = "Single exp";
const QString COLUMN_VEHICLE = "Vehicle";
const QString COLUMN_ID = "id";

static  QMap<QString, COLUMN_DATA> TW_WOT_COLUMN_DATA_STATIC() {
	QMap<QString, COLUMN_DATA> map;
	map.insert(COLUMN_DATETIME, COLUMN_DATA(COLUMN_DATETIME, 120, false, map.count()));
	map.insert(COLUMN_PLAYER, COLUMN_DATA(COLUMN_PLAYER, 120, false, map.count()));
	map.insert(COLUMN_MAP, COLUMN_DATA(COLUMN_MAP, 120, false, map.count()));
	map.insert(COLUMN_VEHICLE, COLUMN_DATA(COLUMN_VEHICLE, 120, false, map.count()));
	map.insert(COLUMN_RESULT, COLUMN_DATA(COLUMN_RESULT, 80, false, map.count()));
	map.insert(COLUMN_SCORE, COLUMN_DATA(COLUMN_SCORE, 50, false, map.count()));
	map.insert(COLUMN_FRAGS, COLUMN_DATA(COLUMN_FRAGS, 40, false, map.count()));
	map.insert(COLUMN_SINGLE_EXP, COLUMN_DATA(COLUMN_SINGLE_EXP, 80, false, map.count()));
	map.insert(COLUMN_EXP, COLUMN_DATA(COLUMN_EXP, 50, false, map.count()));
	map.insert(COLUMN_CREDITS, COLUMN_DATA(COLUMN_CREDITS, 50, false, map.count()));
	map.insert(COLUMN_DAMAGE_DEALT, COLUMN_DATA(COLUMN_DAMAGE_DEALT, 110, false, map.count()));
	map.insert(COLUMN_DAMAGE_RECEIVED, COLUMN_DATA(COLUMN_DAMAGE_RECEIVED, 110, false, map.count()));
	map.insert(COLUMN_CW, COLUMN_DATA(COLUMN_CW, 50, false, map.count()));
	map.insert(COLUMN_ENEMY_CLAN, COLUMN_DATA(COLUMN_ENEMY_CLAN, 120, true, map.count()));
	map.insert(COLUMN_ID, COLUMN_DATA(COLUMN_ID, 50, true, map.count()));
	return map;
}
static const QMap<QString, COLUMN_DATA> TW_WOT_COLUMN_DATA = TW_WOT_COLUMN_DATA_STATIC();

static  QMap<QString, COLUMN_DATA> TW_FAV_COLUMN_DATA_STATIC() {
	QMap<QString, COLUMN_DATA> map;
	map.insert(COLUMN_DATETIME, COLUMN_DATA(COLUMN_DATETIME, 120, false, map.count()));
	map.insert(COLUMN_PLAYER, COLUMN_DATA(COLUMN_PLAYER, 120, false, map.count()));
	map.insert(COLUMN_MAP, COLUMN_DATA(COLUMN_MAP, 120, false, map.count()));
	map.insert(COLUMN_VEHICLE, COLUMN_DATA(COLUMN_VEHICLE, 120, false, map.count()));
	map.insert(COLUMN_RESULT, COLUMN_DATA(COLUMN_RESULT, 80, false, map.count()));
	map.insert(COLUMN_SCORE, COLUMN_DATA(COLUMN_SCORE, 50, false, map.count()));
	map.insert(COLUMN_FRAGS, COLUMN_DATA(COLUMN_FRAGS, 40, false, map.count()));
	map.insert(COLUMN_SINGLE_EXP, COLUMN_DATA(COLUMN_SINGLE_EXP, 80, false, map.count()));
	map.insert(COLUMN_EXP, COLUMN_DATA(COLUMN_EXP, 50, false, map.count()));
	map.insert(COLUMN_CREDITS, COLUMN_DATA(COLUMN_CREDITS, 50, false, map.count()));
	map.insert(COLUMN_DAMAGE_DEALT, COLUMN_DATA(COLUMN_DAMAGE_DEALT, 110, false, map.count()));
	map.insert(COLUMN_DAMAGE_RECEIVED, COLUMN_DATA(COLUMN_DAMAGE_RECEIVED, 110, false, map.count()));
	map.insert(COLUMN_CW, COLUMN_DATA(COLUMN_CW, 50, false, map.count()));
	map.insert(COLUMN_ENEMY_CLAN, COLUMN_DATA(COLUMN_ENEMY_CLAN, 120, true, map.count()));
	map.insert(COLUMN_ID, COLUMN_DATA(COLUMN_ID, 50, true, map.count()));
	return map;
}
static const QMap<QString, COLUMN_DATA> TW_FAV_COLUMN_DATA = TW_FAV_COLUMN_DATA_STATIC();

static  QMap<QString, COLUMN_DATA> TW_CW_COLUMN_DATA_STATIC() {
	QMap<QString, COLUMN_DATA> map;
	map.insert(COLUMN_MAP, COLUMN_DATA(COLUMN_MAP, 120, false, map.count()));
	map.insert(COLUMN_ENEMY_CLAN, COLUMN_DATA(COLUMN_ENEMY_CLAN, 120, false, map.count()));
	map.insert(COLUMN_RESULT, COLUMN_DATA(COLUMN_RESULT, 80, false, map.count()));
	map.insert(COLUMN_SCORE, COLUMN_DATA(COLUMN_SCORE, 50, false, map.count()));
	map.insert(COLUMN_DATETIME, COLUMN_DATA(COLUMN_DATETIME, 120, false, map.count()));
	map.insert(COLUMN_PLAYER, COLUMN_DATA(COLUMN_PLAYER, 120, false, map.count()));
	map.insert(COLUMN_VEHICLE, COLUMN_DATA(COLUMN_VEHICLE, 120, false, map.count()));
	map.insert(COLUMN_FRAGS, COLUMN_DATA(COLUMN_FRAGS, 40, false, map.count()));
	map.insert(COLUMN_SINGLE_EXP, COLUMN_DATA(COLUMN_SINGLE_EXP, 80, false, map.count()));
	map.insert(COLUMN_EXP, COLUMN_DATA(COLUMN_EXP, 50, false, map.count()));
	map.insert(COLUMN_CREDITS, COLUMN_DATA(COLUMN_CREDITS, 50, false, map.count()));
	map.insert(COLUMN_DAMAGE_DEALT, COLUMN_DATA(COLUMN_DAMAGE_DEALT, 110, false, map.count()));
	map.insert(COLUMN_DAMAGE_RECEIVED, COLUMN_DATA(COLUMN_DAMAGE_RECEIVED, 110, false, map.count()));
	map.insert(COLUMN_CW, COLUMN_DATA(COLUMN_CW, 50, true, map.count()));
	map.insert(COLUMN_ID, COLUMN_DATA(COLUMN_ID, 50, true, map.count()));
	return map;
}
static const QMap<QString, COLUMN_DATA> TW_CW_COLUMN_DATA = TW_CW_COLUMN_DATA_STATIC();

typedef QMap<QString, COLUMN_DATA> COLUMN_DATA_MAP;
typedef QMap<int, COLUMN_DATA_MAP > TW_COLUMNS_MAP;

static QMap<int, QMap<QString, COLUMN_DATA> > TW_COLUMNS_STATIC() {
	QMap<int, QMap<QString, COLUMN_DATA> > map;
	map.insert(TW_WOT, TW_WOT_COLUMN_DATA);
	map.insert(TW_FAV, TW_FAV_COLUMN_DATA);
	map.insert(TW_CW, TW_CW_COLUMN_DATA);
	return map;
}
static const QMap<int, QMap<QString, COLUMN_DATA> > TW_COLUMNS = TW_COLUMNS_STATIC();

const QString TAB_WOT_FOLDER = "WoT replays folder";
const QString TAB_FAV_FOLDER = "Favourite replays";
const QString TAB_CW_FOLDER = "Clan Wars replays";
*/

#endif // CONSTANTS_H
