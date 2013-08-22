#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTableWidget>
#include <QList>
#include <QMap>
#include <QLabel>
#include <QThread>
#include <QTimer>
#include <QJsonDocument>
#include <QJsonArray>
#include <QByteArray>
#include <QJsonObject>
#include <QJsonValue>
#include <QFile>
#include <QDebug>
#include <QTranslator>
#include "replay.h"
#include "settingsDialog.h"
#include "constants.h"
#include "player.h"
#include "replayLoadingThread.h"
#include "replayTableWidget.h"

namespace Ui {
	class MainWindow;
}

class MainWindow : public QMainWindow {
	Q_OBJECT
	
public:
	explicit MainWindow(QWidget *parent = 0);
	~MainWindow();

signals:

public slots:
	void firstRunMessage();
	void action_settingsClicked();
	void action_aboutClicked();
	void action_exitClicked();
	void button_saveCommentClicked();
	void button_removeIncompleteReplaysClicked();
	void loadReplaysThreaded(int which = ALL_TABLE_WIDGETS);
	void replayLoadingThreadFinishedNew();
	void checkLoadingThreadsFinished();
	void startLoadingThreadWotFolderNew(int threadNo);
	void startLoadingThreadFavFolderNew(int threadNo);
	void startLoadingThreadCwFolderNew(int threadNo);
	void cwTableWidgetSelectionChanged();
	void button_moveCwReplaysClicked();
	void button_moveToFavouritesClicked();
	void button_removeSelectedReplaysClicked();
	void currentTabChanged(int currentIndex);
	void retranslateUi();

	void testSlot();

private:
	Ui::MainWindow*					ui;
	QMap<QString, QList<QTranslator*> > translations;
	QList<QTranslator*>				installedTranslators;
	QList<QString>					languages;
	bool							firstRun;
	ReplayTable*					wotReplayTable;
	ReplayTable*					favReplayTable;
	ReplayTable*					cwReplayTable;
	SettingsDialog*					settings;
	QMap<QString, QString>*			vehicleNames;
	QTime							timer;
	QTime							ttt;
	QTimer							loadingThreadsCheckTimer;
	QList<ReplayLoadingThread*>	replayLoadingThreadsNew;
	QTimer							testTimer;
	ReplayTable*					_currentTable;
	int								_currentTableIndex;
	int								replaysToLoad;
	int								replaysLoaded;

	void loadTranslations();
	void setTranslator();
	void setupToolButtons();
	void setupObjects();
	void setupTables();
	void setupGuiConnections();
	void initVars();
	void loadVehicleNames();
	void enableSorting(bool sort, int tableWidgets = ALL_TABLE_WIDGETS);
	void resizeColumnsToContents(int tableWidgets = ALL_TABLE_WIDGETS);
	void loadSettings();
	void saveSettings(bool onQuit = false);
	QString generatePath(QString newPath, QString pattern, Replay* replay);
	int getFileCount(QString path);
	bool loadReplaysNew(ReplayTable* table, QString path);
	void startLoadingThreadNew(QString path, int threadNo);
	void clearCwDetails();
	void insertPlayersTableWidgetItems(QTableWidget* tableWidget, QList<Player*>* players);
	void clearCwDetailsTableWidget(QTableWidget* t);
	bool moveReplays(QList<Replay*> replaysToMove, QString dest, QString pattern);
	bool removeReplays(QList<QString> replaysToRemove);
	int	monthNumberFromEnglishShortName(const QString& monthName);
	int currentTableIndex();
	ReplayTable* currentTable();
};

#endif // MAINWINDOW_H
