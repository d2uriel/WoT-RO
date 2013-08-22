#ifndef COLUMN_H
#define COLUMN_H

#include <QObject>
#include <QMap>
#include <QList>
#include <QString>

class Column {
public:

	Column() { name = ""; width = -1; order = -1; visible = false; }

	Column(QString n, int w, int o = -1, bool v = true);

	Column(Column src, int o, bool v = true) {
		name = src.name;
		width = src.width;
		order = o;
		visible = v;
	}

	QString name;
	int width;
	bool visible;
	int order;
};

typedef QMap<QString, Column> TABLE_DATA;

class Columns : public QObject
{
	Q_OBJECT

public:
	Columns();
	~Columns();
	const QMap<QString, Column>* operator [] (const int table);

	void retranslateUi();

	QString COL_CREDITS;
	QString COL_CW;
	QString COL_DAM_DEALT;
	QString COL_DAM_RECIEVED;
	QString COL_DATETIME;
	QString COL_ENEMY_CLAN;
	QString COL_EXP;
	QString COL_FRAGS;
	QString COL_MAP;
	QString COL_PLAYER;
	QString COL_RESULT;
	QString COL_SCORE;
	QString COL_SINGLE_EXP;
	QString COL_VEHICLE;
	QString COL_ID;
/*
	static Columns& data() {
		static Columns columns;
		return columns;
	}
*/
	
signals:
	
public slots:

private:
	void setupColumnNames();
	void setupColumns();
	void setupTables();

	QMap<QString, Column> _columns;
	QMap<QString, Column>* _wotTableColumns;
	QMap<QString, Column>* _favTableColumns;
	QMap<QString, Column>* _cwTableColumns;
	QMap<int, QMap<QString, Column>* > _tableColumns;

};

#endif // COLUMN_H
