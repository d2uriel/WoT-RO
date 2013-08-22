#include "settingsDialog.h"
#include "ui_settingsdialog.h"
#include "constants.h"
#include <QFileDialog>

SettingsDialog::SettingsDialog(QWidget *parent) : QDialog(parent), ui(new Ui::SettingsDialog) {
	ui->setupUi(this);
	setupGuiConnections();
}

SettingsDialog::~SettingsDialog() {
	delete ui;
}

void SettingsDialog::setupGuiConnections() {
	connect(ui->button_browseWotReplaysFolder, SIGNAL(clicked()), SLOT(browseWotReplaysButtonClicked()));
	connect(ui->button_browseFavouriteReplaysFolder, SIGNAL(clicked()), SLOT(browseFavReplaysButtonClicked()));
	connect(ui->button_browseCwReplaysFolder, SIGNAL(clicked()), SLOT(browseCwReplaysButtonClicked()));
/*
	connect(ui->button_cwrClan, SIGNAL(clicked()), SLOT(addPlusCw()));
	connect(ui->button_cwrDate, SIGNAL(clicked()), SLOT(addPlusCw()));
	connect(ui->button_cwrMap, SIGNAL(clicked()), SLOT(addPlusCw()));
	connect(ui->button_cwrTime, SIGNAL(clicked()), SLOT(addPlusCw()));
	connect(ui->button_cwrVehicle, SIGNAL(clicked()), SLOT(addPlusCw()));

	connect(ui->button_frFrags, SIGNAL(clicked()), SLOT(addPlusFr()));
	connect(ui->button_frDate, SIGNAL(clicked()), SLOT(addPlusFr()));
	connect(ui->button_frMap, SIGNAL(clicked()), SLOT(addPlusFr()));
	connect(ui->button_frTime, SIGNAL(clicked()), SLOT(addPlusFr()));
	connect(ui->button_frVehicle, SIGNAL(clicked()), SLOT(addPlusFr()));
*/
	connect(ui->button_cwrClan, SIGNAL(clicked()), SLOT(button_cwClanClicked()));
	connect(ui->button_cwrClear, SIGNAL(clicked()), SLOT(button_cwClearClicked()));
	connect(ui->button_cwrDate, SIGNAL(clicked()), SLOT(button_cwDateClicked()));
	connect(ui->button_cwrMap, SIGNAL(clicked()), SLOT(button_cwMapClicked()));
	connect(ui->button_cwrPlus, SIGNAL(clicked()), SLOT(button_cwPlusClicked()));
	connect(ui->button_cwrSlash, SIGNAL(clicked()), SLOT(button_cwSlashClicked()));
	connect(ui->button_cwrTime, SIGNAL(clicked()), SLOT(button_cwTimeClicked()));
	connect(ui->button_cwrVehicle, SIGNAL(clicked()), SLOT(button_cwVehicleClicked()));

	connect(ui->button_frFrags, SIGNAL(clicked()), SLOT(button_frFragsClicked()));
	connect(ui->button_frClear, SIGNAL(clicked()), SLOT(button_frClearClicked()));
	connect(ui->button_frDate, SIGNAL(clicked()), SLOT(button_frDateClicked()));
	connect(ui->button_frMap, SIGNAL(clicked()), SLOT(button_frMapClicked()));
	connect(ui->button_frPlus, SIGNAL(clicked()), SLOT(button_frPlusClicked()));
	connect(ui->button_frSlash, SIGNAL(clicked()), SLOT(button_frSlashClicked()));
	connect(ui->button_frTime, SIGNAL(clicked()), SLOT(button_frTimeClicked()));
	connect(ui->button_frVehicle, SIGNAL(clicked()), SLOT(button_frVehicleClicked()));
}

void SettingsDialog::addPlus(QLineEdit *l) {
	QString text = l->text();
	if(text.right(1) != "+") {
		l->setText(text + "+");
	}
}

void SettingsDialog::addPlusFr() {
	this->addPlus(ui->lineEdit_frGrouping);
}

void SettingsDialog::addPlusCw() {
	this->addPlus(ui->lineEdit_cwrGrouping);
}

void SettingsDialog::button_clanClicked(QLineEdit* l) {
	l->setText(l->text() + PATTERN_CLAN);
}

void SettingsDialog::button_clearClicked(QLineEdit* l) {
	l->setText("");
}

void SettingsDialog::button_dateClicked(QLineEdit* l) {
	l->setText(l->text() + PATTERN_DATE);
}

void SettingsDialog::button_fragsClicked(QLineEdit* l) {
	l->setText(l->text() + PATTERN_FRAGS);
}

void SettingsDialog::button_mapClicked(QLineEdit* l) {
	l->setText(l->text() + PATTERN_MAP);
}

void SettingsDialog::button_plusClicked(QLineEdit* l) {
	l->setText(l->text() + "+");
}

void SettingsDialog::button_slashClicked(QLineEdit* l) {
	l->setText(l->text() + "/");
}

void SettingsDialog::button_timeClicked(QLineEdit* l) {
	l->setText(l->text() + PATTERN_TIME);
}

void SettingsDialog::button_vehicleClicked(QLineEdit* l) {
	l->setText(l->text() + PATTERN_VEHICLE);
}

void SettingsDialog::button_cwClanClicked() {
	addPlusCw();
	button_clanClicked(ui->lineEdit_cwrGrouping);
}

void SettingsDialog::button_cwClearClicked() {
	button_clearClicked(ui->lineEdit_cwrGrouping);
}

void SettingsDialog::button_cwDateClicked() {
	addPlusCw();
	button_dateClicked(ui->lineEdit_cwrGrouping);
}

void SettingsDialog::button_cwMapClicked() {
	addPlusCw();
	button_mapClicked(ui->lineEdit_cwrGrouping);
}

void SettingsDialog::button_cwPlusClicked() {
	button_plusClicked(ui->lineEdit_cwrGrouping);
}

void SettingsDialog::button_cwSlashClicked() {
	button_slashClicked(ui->lineEdit_cwrGrouping);
}

void SettingsDialog::button_cwTimeClicked() {
	addPlusCw();
	button_timeClicked(ui->lineEdit_cwrGrouping);
}

void SettingsDialog::button_cwVehicleClicked() {
	addPlusCw();
	button_vehicleClicked(ui->lineEdit_cwrGrouping);
}

void SettingsDialog::button_frFragsClicked() {
	addPlusFr();
	button_fragsClicked(ui->lineEdit_frGrouping);
}

void SettingsDialog::button_frClearClicked() {
	button_clearClicked(ui->lineEdit_frGrouping);
}

void SettingsDialog::button_frDateClicked() {
	addPlusFr();
	button_dateClicked(ui->lineEdit_frGrouping);
}

void SettingsDialog::button_frMapClicked() {
	addPlusFr();
	button_mapClicked(ui->lineEdit_frGrouping);
}

void SettingsDialog::button_frPlusClicked() {
	button_plusClicked(ui->lineEdit_frGrouping);
}

void SettingsDialog::button_frSlashClicked() {
	button_slashClicked(ui->lineEdit_frGrouping);
}

void SettingsDialog::button_frTimeClicked() {
	addPlusFr();
	button_timeClicked(ui->lineEdit_frGrouping);
}

void SettingsDialog::button_frVehicleClicked() {
	addPlusFr();
	button_vehicleClicked(ui->lineEdit_frGrouping);
}

void SettingsDialog::browseWotReplaysButtonClicked() {
	QString path = QFileDialog::getExistingDirectory(this, "Please choose WoT replays folder", QString(), QFileDialog::ShowDirsOnly);
	if(!path.isEmpty() && !path.isNull()) {
		ui->label_wotReplaysFolder->setText(path);
	}
}

void SettingsDialog::browseFavReplaysButtonClicked() {
	QString path = QFileDialog::getExistingDirectory(this, "Please choose a folder for your favourite replays", QString(), QFileDialog::ShowDirsOnly);
	if(!path.isEmpty() && !path.isNull()) {
		ui->label_favouriteReplaysFolder->setText(path);
	}
}

void SettingsDialog::browseCwReplaysButtonClicked() {
	QString path = QFileDialog::getExistingDirectory(this, "Please choose a folder for CW replays", QString(), QFileDialog::ShowDirsOnly);
	if(!path.isEmpty() && !path.isNull()) {
		ui->label_cwReplaysFolder->setText(path);
	}
}

QString SettingsDialog::wotFolder() {
	return ui->label_wotReplaysFolder->text();
}

QString SettingsDialog::favFolder() {
	return ui->label_favouriteReplaysFolder->text();
}

QString SettingsDialog::cwFolder() {
	return ui->label_cwReplaysFolder->text();
}

QString SettingsDialog::favGrouping() {
	return ui->lineEdit_frGrouping->text();
}

QString SettingsDialog::cwGrouping() {
	return ui->lineEdit_cwrGrouping->text();
}

bool SettingsDialog::autoMoveCwReplays() {
	return ui->cb_autoMoveCwReplays->isChecked();
}

bool SettingsDialog::autoResizeColumns() {
	return ui->cb_autoResizeColumns->isChecked();
}

void SettingsDialog::setWotFolder(QString path) {
	ui->label_wotReplaysFolder->setText(path);
}

void SettingsDialog::setFavFolder(QString path) {
	ui->label_favouriteReplaysFolder->setText(path);
}

void SettingsDialog::setCwFolder(QString path) {
	ui->label_cwReplaysFolder->setText(path);
}

void SettingsDialog::setFavGrouping(QString pattern) {
	ui->lineEdit_frGrouping->setText(pattern);
}

void SettingsDialog::setCwGrouping(QString pattern) {
	ui->lineEdit_cwrGrouping->setText(pattern);
}

void SettingsDialog::setAutoMoveCwReplays(bool autoMove) {
	ui->cb_autoMoveCwReplays->setChecked(autoMove);
}

void SettingsDialog::setAutoResizeColumns(bool resize) {
	ui->cb_autoResizeColumns->setChecked(resize);
}

void SettingsDialog::setAvailableLanguages(QList<QString> languages) {
	while(!languages.isEmpty()) {
		QString language = languages.takeFirst();
		if(ui->comboBox_language->findText(language) == -1) {
			ui->comboBox_language->addItem(language);
		}
	}
}

QString SettingsDialog::language() {
	return ui->comboBox_language->currentText();
}

void SettingsDialog::setCurrentLanguage(QString language) {
	ui->comboBox_language->setCurrentText(language);
}

void SettingsDialog::retranslateUi() {
	ui->retranslateUi(this);
}
