#ifndef SETTINGSDIALOG_H
#define SETTINGSDIALOG_H

#include <QDialog>
#include <QDebug>
#include <QLineEdit>

namespace Ui {
class SettingsDialog;
}

class SettingsDialog : public QDialog
{
	Q_OBJECT
	
public:
	explicit SettingsDialog(QWidget *parent = 0);
	~SettingsDialog();
	// Getters
	QString wotFolder();
	QString favFolder();
	QString cwFolder();
	QString favGrouping();
	QString cwGrouping();
	bool autoMoveCwReplays();
	bool autoResizeColumns();
	QString language();
	// Setters
	void setWotFolder(QString path);
	void setFavFolder(QString path);
	void setCwFolder(QString path);
	void setFavGrouping(QString pattern);
	void setCwGrouping(QString pattern);
	void setAutoMoveCwReplays(bool autoMove);
	void setAutoResizeColumns(bool resize);
	void setAvailableLanguages(QList<QString> languages);
	void setCurrentLanguage(QString language);
	void retranslateUi();

public slots:
	void browseWotReplaysButtonClicked();
	void browseFavReplaysButtonClicked();
	void browseCwReplaysButtonClicked();

	void addPlus(QLineEdit* l);
	void addPlusFr();
	void addPlusCw();

	void button_frDateClicked();
	void button_frTimeClicked();
	void button_frVehicleClicked();
	void button_frMapClicked();
	void button_frFragsClicked();
	void button_frSlashClicked();
	void button_frPlusClicked();
	void button_frClearClicked();

	void button_cwDateClicked();
	void button_cwTimeClicked();
	void button_cwVehicleClicked();
	void button_cwMapClicked();
	void button_cwClanClicked();
	void button_cwSlashClicked();
	void button_cwPlusClicked();
	void button_cwClearClicked();
	
private:
	Ui::SettingsDialog *ui;
	void setupGuiConnections();
	void button_dateClicked(QLineEdit* l);
	void button_timeClicked(QLineEdit* l);
	void button_vehicleClicked(QLineEdit* l);
	void button_mapClicked(QLineEdit* l);
	void button_fragsClicked(QLineEdit* l);
	void button_slashClicked(QLineEdit* l);
	void button_plusClicked(QLineEdit* l);
	void button_clearClicked(QLineEdit* l);
	void button_clanClicked(QLineEdit* l);
};

#endif // SETTINGSDIALOG_H
