#include "mainWindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QTableWidgetItem>
#include <QSettings>
#include <QFile>
#include <QDir>
#include <QDirIterator>
#include <QToolButton>
#include <QTimer>
#include "player.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
	qDebug() << "MainWindow::MainWindow()";
	ui->setupUi(this);
	loadTranslations();
	initVars();
	setupTables();
	loadSettings();
	loadVehicleNames();
	setupObjects();
	setupToolButtons();
	setupGuiConnections();
	setTranslator();
	if(firstRun) {
		QTimer::singleShot(500, this, SLOT(firstRunMessage()));
	} else {
		QTimer::singleShot(500, this, SLOT(loadReplaysThreaded()));
	}
}

MainWindow::~MainWindow() {
	qDebug() << "MainWindow::~MainWindow()";
	saveSettings(true);
	delete ui;
}

void MainWindow::retranslateUi() {
	qDebug() << "MainWindow::retranslateUi()";
	ui->retranslateUi(this);
	settings->retranslateUi();
	wotReplayTable->retranslateUi();
	favReplayTable->retranslateUi();
	cwReplayTable->retranslateUi();
}

void MainWindow::loadTranslations() {
	qDebug() << "MainWindow::loadTranslations()";
	QDir dir(QApplication::applicationDirPath());
	QStringList filters; filters << "*.qm";
	dir.setNameFilters(filters);
	QFileInfoList translationFiles = dir.entryInfoList();
	QString translation = QLocale::languageToString(QLocale("en").language());
	translations.insert(translation, QList<QTranslator*>());
	languages.append(translation);
	while(!translationFiles.isEmpty()) {
		QString translationFile = translationFiles.takeFirst().absoluteFilePath();
		QTranslator* t = new QTranslator(this);
		qDebug() << t->load(translationFile.left(translationFile.length() - 3));
		translation = QLocale::languageToString(QLocale(translationFile.mid(translationFile.length() - 5, 2)).language());
		if(!translations.contains(translation)) {
			translations.insert(translation, QList<QTranslator*>());
		}
		translations[translation].append(t);
		if(!languages.contains(translation)) {
			languages.append(translation);
		}
	}
}

void MainWindow::setTranslator() {
	qDebug() << "MainWindow::setTranslator()";
	QString currentLanguage = settings->language();
	if(translations[currentLanguage].isEmpty()) {
		while(!installedTranslators.isEmpty()) {
			QApplication::removeTranslator(installedTranslators.takeFirst());
		}
	} else {
		for(int i = 0; i < translations[currentLanguage].count(); i++) {
			QApplication::installTranslator(translations[currentLanguage][i]);
			installedTranslators.append(translations[currentLanguage][i]);
		}
	}
	retranslateUi();
}

void MainWindow::firstRunMessage() {
	qDebug() << "MainWindow::firstRunMessage()";
	QMessageBox::information(this, "WoT-RO", tr("This is the first time you have launched this application.\n") + \
							 tr("As soon as you click 'OK' the settings dialog will open where you have to\n") + \
							 tr("specify folders to use to read replays from and store them to."));
	this->action_settingsClicked();
}

void MainWindow::testSlot() {
	QMessageBox::information(this, "TEST", "TEST");
}

void MainWindow::initVars() {
	qDebug() << "MainWindow::initVars()";
	firstRun = false;
	settings = new SettingsDialog(this);
	vehicleNames = new QMap<QString, QString>();
	replaysToLoad = 0;
	replaysLoaded = 0;
}

void MainWindow::setupGuiConnections() {
	qDebug() << "MainWindow::setupGuiConnections()";
	connect(ui->action_settings, SIGNAL(triggered()), SLOT(action_settingsClicked()));
	connect(ui->action_about, SIGNAL(triggered()), SLOT(action_aboutClicked()));
	connect(ui->action_exit, SIGNAL(triggered()), SLOT(action_exitClicked()));
	connect(ui->action_moveCwReplays, SIGNAL(triggered()), SLOT(button_moveCwReplaysClicked()));
	connect(ui->action_moveSelectedReplaysToFavourites, SIGNAL(triggered()), SLOT(button_moveToFavouritesClicked()));
	connect(ui->action_deleteIncompleteReplays, SIGNAL(triggered()), SLOT(button_removeIncompleteReplaysClicked()));
	connect(ui->action_deleteSelectedReplays, SIGNAL(triggered()), SLOT(button_removeSelectedReplaysClicked()));
	connect(ui->button_saveComment, SIGNAL(clicked()), SLOT(button_saveCommentClicked()));
	connect(&loadingThreadsCheckTimer, SIGNAL(timeout()), SLOT(checkLoadingThreadsFinished()));
	connect(cwReplayTable, SIGNAL(itemSelectionChanged()), SLOT(cwTableWidgetSelectionChanged()));
	connect(ui->tabWidget, SIGNAL(currentChanged(int)), SLOT(currentTabChanged(int)));
	connect(&testTimer, SIGNAL(timeout()), SLOT(testSlot()));
}

void MainWindow::setupTables() {
	qDebug() << "MainWindow::setupTables()";
	wotReplayTable = new ReplayTable(TW_WOT);
	favReplayTable = new ReplayTable(TW_FAV);
	cwReplayTable = new ReplayTable(TW_CW);
	ui->tab->layout()->addWidget(wotReplayTable);
	ui->tab_2->layout()->addWidget(favReplayTable);
	QList<QLayoutItem*> items;
	while(QLayoutItem* i = ui->tab_3->layout()->takeAt(0)) {
		items.append(i);
	}
	ui->tab_3->layout()->addWidget(cwReplayTable);
	while(!items.isEmpty()) {
		ui->tab_3->layout()->addItem(items.takeFirst());
	}
	currentTabChanged(0);
}

void MainWindow::setupObjects() {
	qDebug() << "MainWindow::setupObjects()";
	loadingThreadsCheckTimer.setInterval(100);
	testTimer.setInterval(500);
}

void MainWindow::loadSettings() {
	qDebug() << "MainWindow::loadSettings()";
	QSettings s(QApplication::applicationDirPath() + "/" + SETTINGS_FILE_NAME, QSettings::IniFormat, this);
	settings->setAvailableLanguages(languages);
	if(s.allKeys().count() == 0) {
		saveSettings();
		firstRun = true;
		return;
	}
	settings->setWotFolder(s.value(S_WOT_FOLDER).toString());
	settings->setFavFolder(s.value(S_FAV_FOLDER).toString());
	settings->setCwFolder(s.value(S_CW_FOLDER).toString());
	settings->setFavGrouping(s.value(S_FAV_GROUPING).toString());
	settings->setCwGrouping(s.value(S_CW_GROUPING).toString());
	settings->setAutoMoveCwReplays(s.value(S_AUTO_MOVE_CW).toBool());
	settings->setAutoResizeColumns(s.value(S_AUTO_RESIZE).toBool());
	settings->setCurrentLanguage(s.value(S_LANGUAGE).toString());
	restoreGeometry(s.value(S_WINDOW).toByteArray());
	restoreState(s.value(S_STATE).toByteArray());
}

void MainWindow::saveSettings(bool onQuit) {
	qDebug() << "MainWindow::saveSettings()";
	QSettings s(QApplication::applicationDirPath() + "/" + SETTINGS_FILE_NAME, QSettings::IniFormat, this);
	if(!onQuit) {
		s.setValue(S_WOT_FOLDER, settings->wotFolder());
		s.setValue(S_FAV_FOLDER, settings->favFolder());
		s.setValue(S_CW_FOLDER, settings->cwFolder());
		s.setValue(S_FAV_GROUPING, settings->favGrouping());
		s.setValue(S_CW_GROUPING, settings->cwGrouping());
		s.setValue(S_AUTO_MOVE_CW, settings->autoMoveCwReplays());
		s.setValue(S_AUTO_RESIZE, settings->autoResizeColumns());
		s.setValue(S_LANGUAGE, settings->language());
	}
	s.setValue(S_WINDOW, saveGeometry());
	s.setValue(S_STATE, saveState());
}

void MainWindow::setupToolButtons() {
	qDebug() << "MainWindow::setupToolButtons()";
	ui->mainToolBar->setToolButtonStyle(Qt::ToolButtonIconOnly);
	ui->mainToolBar->addAction(QIcon(":/icons/fav.png"), tr("Move selected replays to favourites"), this, SLOT(button_moveToFavouritesClicked()));
	ui->mainToolBar->addAction(QIcon(":/icons/movecw.png"), tr("Move CW replays"), this, SLOT(button_moveCwReplaysClicked()));
	ui->mainToolBar->addSeparator();
	ui->mainToolBar->addAction(QIcon(":/icons/removeUnfinished.png"), tr("Remove all incomplete replays"), this, SLOT(button_removeIncompleteReplaysClicked()));
	ui->mainToolBar->addSeparator();
	ui->mainToolBar->addSeparator();
	ui->mainToolBar->addSeparator();
	ui->mainToolBar->addSeparator();
	ui->mainToolBar->addAction(QIcon(":/icons/remove.png"), tr("Remove selected replays"), this, SLOT(button_removeSelectedReplaysClicked()));
	ui->mainToolBar->addSeparator();
	ui->mainToolBar->addSeparator();
	ui->mainToolBar->addSeparator();
	ui->mainToolBar->addSeparator();
	ui->mainToolBar->addAction(QIcon(":/icons/prefs.png"), tr("Settings"), this, SLOT(action_settingsClicked()));
}

void MainWindow::loadVehicleNames() {
	qDebug() << "MainWindow::loadVehicleNames()";
	QString fileName = QApplication::applicationDirPath() + "/" + VEHICLE_INFO_FILE_NAME;
	if(QFile::exists(fileName)) {
		QFile file(fileName);
		if(file.open(QFile::ReadOnly | QFile::Text)) {
			QByteArray data;
			data.append(file.readAll());
			QJsonDocument doc = QJsonDocument::fromJson(data);
			if(doc.isNull()) {
				return;
			}
			if(doc.isObject()) {
				QJsonObject json(doc.object());
				for(QJsonObject::Iterator i = json.begin(); i != json.end(); ++i) {
					if((*i).isObject()) {
						QJsonObject vehicle = (*i).toObject();
						vehicleNames->insert(i.key(), vehicle["name"].toString());
					}
				}
			}
		} else {
			QMessageBox::information(this, "WoT-RO", tr("Failed to open file\n") + fileName + tr(".\nVehicle names will be unavailable."));
		}
	} else {
		QMessageBox::information(this, "WoT-RO", tr("File:\n") + fileName + tr("\nnot found. Please copy this file from XVM installation folder\nand restart application."));
	}
}

void MainWindow::button_saveCommentClicked() {
	qDebug() << "MainWindow::button_saveCommentClicked()";
	if(!cwReplayTable->currentReplay()->isNull()) {
		cwReplayTable->currentReplay()->saveComment(ui->replayComment->toPlainText());
	} else {
		ui->button_saveComment->setEnabled(false);
	}
}

void MainWindow::startLoadingThreadWotFolderNew(int threadNo) {
	qDebug() << "MainWindow::startLoadingThreadWotFolderNew()";
	startLoadingThreadNew(settings->wotFolder(), threadNo);
}

void MainWindow::startLoadingThreadFavFolderNew(int threadNo) {
	qDebug() << "MainWindow::startLoadingThreadFavFolderNew()";
	startLoadingThreadNew(settings->favFolder(), threadNo);
}

void MainWindow::startLoadingThreadCwFolderNew(int threadNo) {
	qDebug() << "MainWindow::startLoadingThreadCwFolderNew()";
	startLoadingThreadNew(settings->cwFolder(), threadNo);
}

void MainWindow::startLoadingThreadNew(QString path, int threadNo) {
	qDebug() << "MainWindow::startLoadingThreadNew()";
	ReplayLoadingThread* r = new ReplayLoadingThread(path, threadNo * REPLAYS_PER_THREAD, vehicleNames);
	connect(r, SIGNAL(finished()), SLOT(replayLoadingThreadFinishedNew()));
	replayLoadingThreadsNew.append(r);
	r->start();
}

int MainWindow::getFileCount(QString path) {
	qDebug() << "MainWindow::getFileCount()";
	QDirIterator d(path);
	int fileCount = 0;
	while(d.hasNext()) {
		d.next();
		fileCount++;
	}
	return fileCount;
}

void MainWindow::enableSorting(bool sort, int tableWidgets) {
	qDebug() << "MainWindow::enableSorting()";
	ttt.start();
	if(tableWidgets & WOT_TABLE_WIDGET || tableWidgets == ALL_TABLE_WIDGETS) {
		if(wotReplayTable->isSortingEnabled() != sort) {
			if(!sort) {
				wotReplayTable->setUpdatesEnabled(false);
				wotReplayTable->horizontalHeader()->setSortIndicatorShown(false);
				wotReplayTable->horizontalHeader()->setSortIndicator(-1, Qt::DescendingOrder);
			} else {
				wotReplayTable->horizontalHeader()->setSortIndicatorShown(true);
				wotReplayTable->horizontalHeader()->setSortIndicator(0, Qt::DescendingOrder);
			}
			wotReplayTable->setSortingEnabled(sort);
			if(sort) {
				wotReplayTable->setUpdatesEnabled(true);
			}
		}
	}
	if(tableWidgets & FAV_TABLE_WIDGET || tableWidgets == ALL_TABLE_WIDGETS) {
		if(favReplayTable->isSortingEnabled() != sort) {
			if(!sort) {
				favReplayTable->setUpdatesEnabled(false);
				favReplayTable->horizontalHeader()->setSortIndicatorShown(false);
				favReplayTable->horizontalHeader()->setSortIndicator(-1, Qt::DescendingOrder);
			} else {
				favReplayTable->horizontalHeader()->setSortIndicatorShown(true);
				favReplayTable->horizontalHeader()->setSortIndicator(0, Qt::DescendingOrder);
			}
			favReplayTable->setSortingEnabled(sort);
			if(sort) {
				favReplayTable->setUpdatesEnabled(true);
			}
		}
	}
	if(tableWidgets & CW_TABLE_WIDGET || tableWidgets == ALL_TABLE_WIDGETS) {
		if(cwReplayTable->isSortingEnabled() != sort) {
			if(!sort) {
				cwReplayTable->setUpdatesEnabled(false);
				cwReplayTable->horizontalHeader()->setSortIndicatorShown(false);
				cwReplayTable->horizontalHeader()->setSortIndicator(-1, Qt::DescendingOrder);
			} else {
				cwReplayTable->horizontalHeader()->setSortIndicatorShown(true);
				cwReplayTable->horizontalHeader()->setSortIndicator(0, Qt::DescendingOrder);
			}
			cwReplayTable->setSortingEnabled(sort);
			if(sort) {
				cwReplayTable->setUpdatesEnabled(true);
			}
		}
	}
	qDebug() << "enableSorting() took " + QString::number(ttt.elapsed()) + "ms.";
}

void MainWindow::resizeColumnsToContents(int tableWidgets) {
	qDebug() << "MainWindow::resizeColumnsToContents()";
	if(tableWidgets & WOT_TABLE_WIDGET || tableWidgets == ALL_TABLE_WIDGETS) {
		wotReplayTable->resizeColumnsToContents();
	}
	if(tableWidgets & FAV_TABLE_WIDGET || tableWidgets == ALL_TABLE_WIDGETS) {
		favReplayTable->resizeColumnsToContents();
	}
	if(tableWidgets & CW_TABLE_WIDGET || tableWidgets == ALL_TABLE_WIDGETS) {
		cwReplayTable->resizeColumnsToContents();
	}
}

void MainWindow::loadReplaysThreaded(int which) {
	qDebug() << "MainWindow::loadReplaysThreaded()";
	timer.start();
	enableSorting(false, which);
	ui->statusBar->showMessage("Loading replays...");
	bool started = false;
	if(which & WOT_TABLE_WIDGET || which & ALL_TABLE_WIDGETS) {
		if(!loadReplaysNew(wotReplayTable, settings->wotFolder())) {
			QMessageBox::information(this, "WoT-RO", tr("WoT replay folder doesn't exist.\nOpen settings and browse for a correct folder."));
		} else {
			started = true;
		}
	}
	if(which & FAV_TABLE_WIDGET || which & ALL_TABLE_WIDGETS) {
		if(!loadReplaysNew(favReplayTable, settings->favFolder())) {
			QMessageBox::information(this, "WoT-RO", tr("Favourite replays folder doesn't exist.\nOpen settings and browse for a correct folder."));
		} else {
			started = true;
		}
	}
	if(which & CW_TABLE_WIDGET || which & ALL_TABLE_WIDGETS) {
		if(!loadReplaysNew(cwReplayTable, settings->cwFolder())) {
			QMessageBox::information(this, "WoT-RO", tr("CW replay folder doesn't exist.\nOpen settings and browse for a correct folder."));
		} else {
			started = true;
		}
	}
	if(started) {
		loadingThreadsCheckTimer.start();
	} else {
		ui->statusBar->showMessage(tr("Nothing to load."));
	}
}

bool MainWindow::loadReplaysNew(ReplayTable* tableWidget, QString path) {
	qDebug() << "MainWindow::loadReplaysNew()";
	if(QDir(path).exists()) {
		tableWidget->clear();
		int fileCount = getFileCount(path);
		int maxThreads = fileCount / REPLAYS_PER_THREAD + 1;
		replaysToLoad += fileCount;
		for(int i = 0; i < maxThreads; i++) {
			if(path == settings->wotFolder()) {
				startLoadingThreadWotFolderNew(i);
			} else if(path == settings->favFolder()) {
				startLoadingThreadFavFolderNew(i);
			} else if(path == settings->cwFolder()) {
				startLoadingThreadCwFolderNew(i);
			}
		}
		return true;
	} else {
		return false;
	}
}

void MainWindow::checkLoadingThreadsFinished() {
	qDebug() << "MainWindow::checkLoadingThreadsFinished()";
	bool allThreadsFinished = true;
	for(int i = 0; i < replayLoadingThreadsNew.count(); i++) {
		if(!replayLoadingThreadsNew[i]->isFinished() || !replayLoadingThreadsNew[i]->toDelete()) {
			allThreadsFinished = false;
			break;
		}
	}
	if(allThreadsFinished) {
		replaysLoaded = 0;
		replaysToLoad = 0;
		while(!replayLoadingThreadsNew.isEmpty()) {
			delete replayLoadingThreadsNew.takeFirst();
		}
		enableSorting(true);
		if(settings->autoResizeColumns()) {
			resizeColumnsToContents();
		}
		loadingThreadsCheckTimer.stop();
		wotReplayTable->selectRow(0);
		favReplayTable->selectRow(0);
		cwReplayTable->selectRow(0);
		ui->statusBar->showMessage(tr("Loading replays...100% done. Took: ") + QString::number(timer.elapsed()) + tr("ms to load ") + \
								   QString::number(wotReplayTable->rowCount() + favReplayTable->rowCount() + \
												   cwReplayTable->rowCount()) + tr(" replays."), 10000);
		if(settings->autoMoveCwReplays()) {
			QTimer::singleShot(500, this, SLOT(button_moveCwReplaysClicked()));
		}
	}
}

void MainWindow::replayLoadingThreadFinishedNew() {
	qDebug() << "MainWindow::replayLoadingThreadFinishedNew()";
	ReplayLoadingThread* t = ((ReplayLoadingThread*)sender());
	QList<Replay*>* loadedReplays = t->replays();
	if(loadedReplays->count() > 0) {
		replaysLoaded += loadedReplays->count();
		QString path = loadedReplays->first()->path();
		path = path.left(path.lastIndexOf("/"));
		if(path == settings->wotFolder()) {
			while(!loadedReplays->isEmpty()) {
				Replay* r = loadedReplays->takeFirst();
				wotReplayTable->addReplay(r);

			}
		} else if(path == settings->favFolder()) {
			while(!loadedReplays->isEmpty()) {
				Replay* r = loadedReplays->takeFirst();
				favReplayTable->addReplay(r);
			}
		} else if(path == settings->cwFolder()) {
			while(!loadedReplays->isEmpty()) {
				Replay* r = loadedReplays->takeFirst();
				cwReplayTable->addReplay(r);
			}
		}
		ui->statusBar->showMessage(tr("Loading replays...") + QString::number((int)(((double)replaysLoaded / (double)replaysToLoad) * 100.)) + tr("% done."));
	}
	t->setToDelete();
}

void MainWindow::action_settingsClicked() {
	qDebug() << "MainWindow::action_settingsClicked()";
	QString oldWotFolder = settings->wotFolder();
	QString oldFavFolder = settings->favFolder();
	QString oldCwFolder = settings->cwFolder();
	QString oldLanguage = settings->language();
	if(settings->exec() == QDialog::Accepted) {
		saveSettings();
		if(settings->wotFolder() != oldWotFolder || settings->favFolder() != oldFavFolder || settings->cwFolder() != oldCwFolder) {
			firstRun = false;
			loadReplaysThreaded();
		}
		if(settings->language() != oldLanguage) {
			setTranslator();
		}
	}
}

int MainWindow::monthNumberFromEnglishShortName(const QString &monthName) {
	if(monthName == "Jan") {
		return 1;
	} else if(monthName == "Feb") {
		return 2;
	} else if(monthName == "Mar") {
		return 3;
	} else if(monthName == "Apr") {
		return 4;
	} else if(monthName == "May") {
		return 5;
	} else if(monthName == "Jun") {
		return 6;
	} else if(monthName == "Jul") {
		return 7;
	} else if(monthName == "Aug") {
		return 8;
	} else if(monthName == "Sep") {
		return 9;
	} else if(monthName == "Oct") {
		return 10;
	} else if(monthName == "Nov") {
		return 11;
	} else if(monthName == "Dec") {
		return 12;
	}
	return 0;
}

void MainWindow::action_aboutClicked() {
	qDebug() << "MainWindow::action_aboutClicked()";
	QString dateStr = __DATE__;
	int monthNo = monthNumberFromEnglishShortName(dateStr.left(3));
	int yearNo = dateStr.right(4).toInt();
	int dayNo = dateStr.mid(4, dateStr.length() - 9).toInt();
	QDate date(yearNo, monthNo, dayNo);
	QMessageBox::information(this, "WoT-RO", tr("World of Tanks Replay Organizer\n\n") + \
							 tr("Created and shared by d2uriel under LGPL license.\n\n") + \
							 tr("Version: ") + VERSION + \
							 tr("\nBuild: ") + date.toString("yyyyMMdd") + QString(__TIME__).left(5) + \
							 tr("\n\nPlease report any bugs you may encounter\n") + \
							 tr("to me on WoT chat. Thanks.\n\n") + \
							 tr("PS: I know tank names are messed up.\n") + \
							 tr("If you know where to get a proper name list\n") + \
							 tr("lemme know."));
}

void MainWindow::action_exitClicked() {
	qDebug() << "MainWindow::action_exitClicked()";
	QApplication::closeAllWindows();
}

QString MainWindow::generatePath(QString newPath, QString pattern, Replay* replay) {
	qDebug() << "MainWindow::generatePath()";
    QString path = newPath + "/";
	QStringList patterns = pattern.split("/");
	for(int i = 0; i < patterns.count(); i++) {
		QStringList patterns2 = patterns[i].split("+");
		for(int j = 0; j < patterns2.count(); j++) {
			if(patterns2[j] == PATTERN_CLAN) {
				path += replay->enemyClan();
			} else if(patterns2[j] == PATTERN_MAP) {
				path += replay->map();
			} else if(patterns2[j] == PATTERN_VEHICLE) {
				path += replay->vehicle();
			} else if(patterns2[j] == PATTERN_DATE) {
				path += replay->dateTime().date().toString("yyyy-MM-dd");
			} else if(patterns2[j] == PATTERN_FRAGS) {
				path += QString::number(replay->frags());
			} else if(patterns2[j] == PATTERN_TIME) {
				path += replay->dateTime().time().toString("HH.mm.ss");;
			}
		}
		path.append("/");
	}
	return path;
}

void MainWindow::cwTableWidgetSelectionChanged() {
	qDebug() << "MainWindow::cwTableWidgetSelectionChanged()";
	Replay* r = cwReplayTable->currentReplay();
	if(!r->isNull()) {
		ui->label_score->setText(r->playerClan() + " " + r->score() + " " + r->enemyClan());
		ui->label_dateTime->setText(r->dateTime().toString("yyyy-MM-dd HH:mm:ss"));
		ui->label_enemyClan->setText(r->enemyClan());
		ui->label_replayPath->setText(r->path());
		insertPlayersTableWidgetItems(ui->tableWidget_ownTeam, r->greenTeam());
		insertPlayersTableWidgetItems(ui->tableWidget_enemyTeam, r->redTeam());
		ui->replayComment->setPlainText(r->comment());
		ui->label_result->setText(r->result());
		if(ui->label_result->text() == tr("Victory")) {
			ui->label_result->setStyleSheet("QLabel { color: green }");
		} else {
			ui->label_result->setStyleSheet("QLabel { color: red }");
		}
		ui->button_saveComment->setEnabled(true);
	} else {
		clearCwDetails();
		delete r;
	}
}

void MainWindow::insertPlayersTableWidgetItems(QTableWidget *tableWidget, QList<Player *> *players) {
	qDebug() << "MainWindow::insertPlayersTableWidgetItems()";
	tableWidget->setSortingEnabled(false);
	clearCwDetailsTableWidget(tableWidget);
	for(int i = 0; i < players->count(); i++) {
		tableWidget->insertRow(i);
		QTableWidgetItem* playerName = new QTableWidgetItem(players->at(i)->name);
		playerName->setFlags(playerName->flags() ^ Qt::ItemIsEditable);
		QTableWidgetItem* playerVehicle = new QTableWidgetItem(players->at(i)->vehicle);
		playerVehicle->setFlags(playerVehicle->flags() ^ Qt::ItemIsEditable);
		if(players->at(i)->alive == false) {
			playerName->setBackgroundColor(QColor(255, 180, 180));
			playerVehicle->setBackgroundColor(QColor(255, 180, 180));
		}
		tableWidget->setItem(i, 0, playerName);
		tableWidget->setItem(i, 1, playerVehicle);
	}
	tableWidget->setSortingEnabled(true);
	tableWidget->resizeColumnsToContents();
}

void MainWindow::clearCwDetails() {
	qDebug() << "MainWindow::clearCwDetails()";
	ui->label_score->setText(tr("Select one replay"));
	ui->label_dateTime->setText(tr("Select one replay"));
	ui->label_enemyClan->setText(tr("Select one replay"));
	ui->label_replayPath->setText(tr("Select one replay"));
	ui->label_result->setText(tr("Select one replay"));
	ui->label_result->setStyleSheet("QLabel { color: black }");
	clearCwDetailsTableWidget(ui->tableWidget_ownTeam);
	clearCwDetailsTableWidget(ui->tableWidget_enemyTeam);
}

void MainWindow::clearCwDetailsTableWidget(QTableWidget* t) {
	qDebug() << "MainWindow::clearCwDetailsTableWidget()";
	while(t->rowCount() > 0) {
		for(int col = 0; col < t->columnCount(); col++) {
			delete t->takeItem(0, col);
		}
		t->removeRow(0);
	}
}

bool MainWindow::moveReplays(QList<Replay *> replaysToMove, QString dest, QString pattern) {
	qDebug() << "MainWindow::moveReplays()";
	bool noError = true;
	while(!replaysToMove.isEmpty()) {
		Replay* r = replaysToMove.takeFirst();
		QString path = r->path();
		QFile f(path);
		QFile c(path + COMMENT_FILE_EXT);
		QString fileName = f.fileName().right(f.fileName().length() - f.fileName().lastIndexOf("/") - 1);
		QString newPath = generatePath(dest, pattern, r);
		QDir replayDir(newPath);
		if(!replayDir.exists()) {
			replayDir.mkpath(newPath);
		}
		noError = f.copy(newPath + fileName);
		if(noError == true) {
			c.copy(newPath + fileName + COMMENT_FILE_EXT);
#ifndef DEBUG
			f.remove();
			c.remove();
#else
			qDebug() << "Removing file: " + f.fileName();
#endif
			r->setPath(newPath + fileName);
		} else {
			QMessageBox::information(this, "WoT-RO", tr("Failed to copy file:\n") + r->path() + tr("\nto directory:\n") + newPath + ".\n" + f.errorString() + tr("\n\nReloading replays."));
			break;
		}
	}
	return noError;
}

bool MainWindow::removeReplays(QList<QString> replaysToRemove) {
	qDebug() << "MainWindow::removeReplays()";
	bool allRemoved = true;
	while(!replaysToRemove.isEmpty()) {
		QFile f(replaysToRemove.takeFirst());
#ifndef DEBUG
		allRemoved = f.remove();
		if(allRemoved) {
			QFile c(f.fileName() + COMMENT_FILE_EXT);
			c.remove();
		} else {
			QMessageBox::information(this, "WoT-RO", tr("Failed to remove file:\n") + f.fileName() + "\n\n" + f.errorString() + tr("\n\nReloading replays."));
			break;
		}
#else
		qDebug() << "Removing file: " + f.fileName();
#endif
	}
	return allRemoved;
}

void MainWindow::button_moveCwReplaysClicked() {
	qDebug() << "MainWindow::button_moveCwReplaysClicked()";
	ui->statusBar->showMessage(tr("Moving all CW replays from WoT folder to CW folder..."));
	enableSorting(false, WOT_TABLE_WIDGET | CW_TABLE_WIDGET);
	QList<Replay*> replaysToMove = wotReplayTable->moveCwReplays(cwReplayTable);
	if(!this->moveReplays(replaysToMove, settings->cwFolder(), settings->cwGrouping())) {
		loadReplaysThreaded(WOT_TABLE_WIDGET | CW_TABLE_WIDGET);
	} else {
		enableSorting(true, WOT_TABLE_WIDGET | CW_TABLE_WIDGET);
		resizeColumnsToContents(WOT_TABLE_WIDGET | CW_TABLE_WIDGET);
		ui->statusBar->showMessage(tr("Moving all CW replays from WoT folder to CW folder...done."), 10000);
	}
}

void MainWindow::button_moveToFavouritesClicked() {
	qDebug() << "MainWindow::button_moveToFavouritesClicked()";
	ui->statusBar->showMessage(tr("Moving selected replays to favourites folder..."));
	enableSorting(false, this->currentTableIndex() | FAV_TABLE_WIDGET);
	QList<Replay*> replaysToMove = this->currentTable()->moveSelected(favReplayTable);
	if(!this->moveReplays(replaysToMove, settings->favFolder(), settings->favGrouping())) {
		loadReplaysThreaded(this->currentTableIndex() | FAV_TABLE_WIDGET);
	} else {
		enableSorting(true, this->currentTableIndex() | FAV_TABLE_WIDGET);
		resizeColumnsToContents(this->currentTableIndex() | FAV_TABLE_WIDGET);
		ui->statusBar->showMessage(tr("Moving selected replays to favourites folder...done."), 10000);
	}
}

void MainWindow::button_removeIncompleteReplaysClicked() {
	qDebug() << "MainWindow::button_removeIncompleteReplaysClicked()";
	ui->statusBar->showMessage(tr("Removing incomplete replays..."));
	enableSorting(false, this->currentTableIndex());
	QList<QString> replaysToRemove = this->currentTable()->removeIncomplete();
	if(!this->removeReplays(replaysToRemove)) {
		loadReplaysThreaded(this->currentTableIndex());
	} else {
		enableSorting(true, this->currentTableIndex());
		resizeColumnsToContents(this->currentTableIndex());
		ui->statusBar->showMessage(tr("Removing incomplete replays...done."), 10000);
	}
}

void MainWindow::button_removeSelectedReplaysClicked() {
	qDebug() << "MainWindow::button_removeSelectedReplaysClicked()";
	ui->statusBar->showMessage(tr("Removing selected replays..."));
	enableSorting(false, this->currentTableIndex());
	QList<QString> replaysToRemove = this->currentTable()->removeSelected();
	if(!this->removeReplays(replaysToRemove)) {
		loadReplaysThreaded(this->currentTableIndex());
	} else {
		enableSorting(true, this->currentTableIndex());
		resizeColumnsToContents(this->currentTableIndex());
		ui->statusBar->showMessage(tr("Removing selected replays...done."), 10000);
	}
}

void MainWindow::currentTabChanged(int currentIndex) {
	qDebug() << "MainWindow::currentTabChanged()";
	if(currentIndex == 0) {
		_currentTable = wotReplayTable;
		_currentTableIndex = WOT_TABLE_WIDGET;
	} else if(currentIndex == 1) {
		_currentTable = favReplayTable;
		_currentTableIndex = FAV_TABLE_WIDGET;
	} else if(currentIndex == 2) {
		_currentTable = cwReplayTable;
		_currentTableIndex = CW_TABLE_WIDGET;
	} else {
		_currentTable = 0;
		_currentTableIndex = 0;
		QMessageBox::critical(this, "WoT-RO", tr("A critical error occurred. Closing application."));
		QApplication::closeAllWindows();
	}
}

int MainWindow::currentTableIndex() {
	qDebug() << "MainWindow::currentTableIndex()";
	if(_currentTableIndex) {
		return _currentTableIndex;
	} else {
		QMessageBox::critical(this, "WoT-RO", tr("A critical error occurred. Closing application."));
		QApplication::closeAllWindows();
		return -1;
	}
}

ReplayTable* MainWindow::currentTable() {
	qDebug() << "MainWindow::currentTable()";
	if(_currentTable) {
		return _currentTable;
	} else {
		QMessageBox::critical(this, "WoT-RO", tr("A critical error occurred. Closing application."));
		QApplication::closeAllWindows();
		return 0;
	}
}
