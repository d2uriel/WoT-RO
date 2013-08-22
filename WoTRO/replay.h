#ifndef Replay_H
#define Replay_H

#include "player.h"
#include <QObject>
#include <QString>
#include <QJsonDocument>
#include <QJsonArray>
#include <QByteArray>
#include <QDataStream>
#include <QJsonObject>
#include <QJsonValue>
#include <QDateTime>
#include <QList>
#include <QFile>
#include <QTableWidgetItem>
#include <QMap>
#include "replay.h"

class Replay : public QObject {
	Q_OBJECT

public:
	Replay(QString path, QMap<QString, QString>* vehicleNames);
	Replay();
	~Replay();

	bool load();
	void setPath(QString path) { _path = path; }
	void saveComment(QString comment);

	// Setters

	// Getters
#ifdef DEBUG
	QString description()		{ return QString(*_pDescription); }
	QString additionalInfo()	{ return QString(*_pAdditionalInfo); }
#endif

	QString			player()			{ return _player; }
	QString			map()				{ return _map; }
	QDateTime		dateTime()			{ return _dateTime; }
	int				exp()				{ return _exp; }
	int				singleExp()			{ return _singleExp; }
	int				frags()				{ return _frags; }
	int				damageDealt()		{ return _damageDealt; }
	int				damageReceived()	{ return _damageRecieved; }
	QString			vehicle()			{ return _vehicle; }
	int				credits()			{ return _credits; }
	QString			result()			{ return _result; }
	QString			cw()				{ return _cw; }
	QString			path()				{ return _path; }
	QString			enemyClan()			{ return _enemyClan; }
	QString			score()				{ return _score; }
	QString         playerClan()        { return _playerClan; }
	QList<Player*>*	greenTeam()			{ return _greenTeam; }
	QList<Player*>*	redTeam()			{ return _redTeam; }
	QString			comment()			{ return _comment; }
	bool			isIncomplete()		{ return _incomplete; }
	bool			isNull()			{ return _isNull; }


signals:
	
public slots:

private:
	// Members
	QString		_path;
	QFile*		_file;
	QString		_player;
	QString		_map;
	QDateTime	_dateTime;
	int			_singleExp;
	int			_exp;
	int			_frags;
	int			_damageDealt;
	int			_damageRecieved;
	QString		_vehicle;
	int			_credits;
	QString		_result;
	QString		_cw;
	QString		_enemyClan;
	QString		_score;
	QString		_playerClan;
	int			_playerId;
	int			_descriptionJsonSize;
	int			_additionalInfoJsonSize;
	QByteArray*	_pDescription;
	QByteArray*	_pAdditionalInfo;
	QList<Player*>*	_greenTeam;
	QList<Player*>*	_redTeam;
	int			_playerTeam;
	QString		_comment;
	QMap<QString, QString>*	_vehicleNames;
	bool		_incomplete;
	bool		_isNull;
	QTime		ttt;

	// Methods
	void	loadDescriptionJson();
	void	loadAdditionalInfoJson();
	bool	parseDescriptionJson();
	bool	parseAdditionalInfoJson();
	int		getJsonSize(int offset = 0);
	bool	isCW();
	QString	getScore();
	void	loadComment();
};

#endif // Replay_H
