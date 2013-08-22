#include "replay.h"
#include <QFile>
#include <QJsonDocument>
#include <QJsonArray>
#include <QByteArray>
#include <QDataStream>
#include <QJsonObject>
#include <QTextStream>
#include <QJsonValue>
#include "constants.h"

Replay::Replay(QString path, QMap<QString, QString>* vehicleNames) {
	_path = path;
	_vehicleNames = vehicleNames;
	_playerId = 0;
	_playerTeam = 0;
	_descriptionJsonSize = 0;
	_additionalInfoJsonSize = 0;
	_pDescription = new QByteArray();
	_pAdditionalInfo = new QByteArray();
	_greenTeam = new QList<Player*>();
	_redTeam = new QList<Player*>();
	_exp = 0;
	_singleExp = 0;
	_frags = 0;
	_damageDealt = 0;
	_damageRecieved = 0;
	_credits = 0;
	_incomplete = false;
	_isNull = false;
}

Replay::Replay() {
	_isNull = true;
}

Replay::~Replay() {
	if(_pDescription) {
		delete _pDescription;
	}
	if(_pAdditionalInfo) {
		delete _pAdditionalInfo;
	}
	if(_file) {
		delete _file;
	}
	while(!_greenTeam->isEmpty()) {
		delete _greenTeam->takeLast();
	}
	delete _greenTeam;
	while(!_redTeam->isEmpty()) {
		delete _redTeam->takeLast();
	}
	delete _redTeam;
}

bool Replay::load() {
	if(QFile::exists(_path)) {
		_file = new QFile(_path);
		if(_file->open(QIODevice::ReadOnly)) {
			loadDescriptionJson();
			parseDescriptionJson();
			loadAdditionalInfoJson();
			if(!parseAdditionalInfoJson()) {
				_incomplete = true;
			}
			_score = getScore();
			loadComment();
			_file->close();
		}
		delete _file;
		_file = 0;
		if(isCW()) {
			_cw = TEXT_YES;
		} else {
			_cw = TEXT_NO;
		}
	}
	return true;
}

int Replay::getJsonSize(int offset) {
	_file->seek(_file->pos() + offset);
	QByteArray ba = _file->read(2);
	while(ba[0] == '\000') {
		ba.remove(0, 1);
	}
	QByteArray re;
	for(int i = ba.size(); i > 0; i--) {
		re.append(ba[i - 1]);
	}
	bool ok;
	_file->seek(_file->pos() + 2);
	return re.toHex().toInt(&ok, 16);
}

void Replay::loadDescriptionJson() {
	_descriptionJsonSize = getJsonSize(DESCRIPTION_JSON_SIZE_OFFSET);
	_pDescription->append(_file->read(_descriptionJsonSize));
}

void Replay::loadAdditionalInfoJson() {
	_additionalInfoJsonSize = getJsonSize();
	_pAdditionalInfo->append(_file->read(_additionalInfoJsonSize/* - 2*/));
}

bool Replay::parseDescriptionJson() {
	QJsonDocument ReplayNewJson(QJsonDocument::fromJson(*_pDescription));
	if(ReplayNewJson.isNull()) {
		return false;
	}

	if(ReplayNewJson.isObject()) {
		QJsonObject json(ReplayNewJson.object());
		_playerId = json["playerID"].toDouble();
		_player = json["playerName"].toString();
		_map = json["mapDisplayName"].toString();
		_dateTime = QDateTime::fromString(json["dateTime"].toString(), "dd.MM.yyyy HH:mm:ss");
		QString playerVehicle = json["playerVehicle"].toString();
		playerVehicle = playerVehicle.right(playerVehicle.length() - playerVehicle.indexOf("-") - 1);
		playerVehicle = playerVehicle.replace("-", "_");
		playerVehicle = _vehicleNames->value(playerVehicle.toLower());
		if(playerVehicle.isEmpty()) {
			playerVehicle = json["playerVehicle"].toString();
		} else {
			playerVehicle = playerVehicle.replace("_", " ");
		}
		_vehicle = playerVehicle;

		QJsonObject vehicles = json["vehicles"].toObject();
		for(QJsonObject::iterator vehiclesIt = vehicles.begin(); vehiclesIt != vehicles.end(); ++vehiclesIt) {
			QJsonObject vehicleInfo = (*vehiclesIt).toObject();
			if(vehicleInfo["name"].toString() == _player) {
				_playerTeam = vehicleInfo["team"].toDouble();
				break;
			}
		}
	}
	delete _pDescription;
	_pDescription = 0;
	return true;
}

bool Replay::parseAdditionalInfoJson() {
	QJsonDocument ReplayNewJson(QJsonDocument::fromJson(*_pAdditionalInfo));
	if(ReplayNewJson.isNull()) {
		return false;
	}

	if(ReplayNewJson.isArray()) {
		QJsonArray json(ReplayNewJson.array());
		for(int i = 0; i < json.count(); i++) {
			if(json[i].isObject()) {
				QJsonObject obj = json[i].toObject();
				if(i == 0) {
					if(obj["isWinner"].toDouble() == 1) {
						_result = TEXT_VICTORY;
					} else {
						_result = TEXT_DEFEAT;
					}
					_damageDealt = obj["damageDealt"].toDouble();
					_damageRecieved = obj["damageReceived"].toDouble();
					_exp = obj["xp"].toDouble();
					QJsonObject factors = obj["factors"].toObject();
					int factor = 1;
					for(QJsonObject::Iterator factorsIt = factors.begin(); factorsIt != factors.end(); ++factorsIt) {
						factor *= factorsIt.value().toDouble() / 10;
					}
					_singleExp = _exp / factor;
					_frags = obj["killed"].toArray().count();
					_credits = obj["credits"].toDouble();
				} else if(i == 1) {
					for(QJsonObject::iterator vehiclesIt = obj.begin(); vehiclesIt != obj.end(); ++vehiclesIt) {
						QJsonObject vehicleInfo = (*vehiclesIt).toObject();
						Player *player = new Player();
						player->id = vehiclesIt.key().toInt();
						QString playerVehicle = vehicleInfo["vehicleType"].toString();
						playerVehicle = playerVehicle.right(playerVehicle.length() - playerVehicle.indexOf(":") - 1);
						playerVehicle = playerVehicle.replace("-", "_");
						playerVehicle = _vehicleNames->value(playerVehicle.toLower());
						if(playerVehicle.isEmpty()) {
							playerVehicle = vehicleInfo["vehicleType"].toString();
						} else {
							playerVehicle = playerVehicle.replace("_", " ");
						}
						player->vehicle = playerVehicle;
						player->alive = vehicleInfo["isAlive"].toBool();
						player->name = vehicleInfo["name"].toString();
						player->clan = vehicleInfo["clanAbbrev"].toString();
						player->team = (int)vehicleInfo["team"].toDouble();
						player->teamKiller = vehicleInfo["isTeamKiller"].toBool();
						if(player->team == _playerTeam) {
							_greenTeam->push_back(player);
						} else {
							_redTeam->push_back(player);
						}
					}
				}
			}
		}
	}
	delete _pAdditionalInfo;
	_pAdditionalInfo = 0;
	return true;
}

bool Replay::isCW() {
	QString greenClan = "";
	for(int i = 0; i < _greenTeam->size(); i++) {
		if(greenClan == "" && i == 0) {
			greenClan = _greenTeam->at(i)->clan;
			continue;
		} else {
			if(greenClan != _greenTeam->at(i)->clan) {
				return false;
			}
		}
	}
	QString redClan = "";
	for(int i = 0; i < _redTeam->size(); i++) {
		if(redClan == "" && i == 0) {
			redClan = _redTeam->at(i)->clan;
			continue;
		} else {
			if(redClan != _redTeam->at(i)->clan) {
				return false;
			}
		}
	}
	if(greenClan == redClan || (greenClan == "" && redClan == "")) {
		return false;
	}
    _playerClan = greenClan;
	_enemyClan = redClan;
	return true;
}

QString Replay::getScore() {
	int greenTeamDead = 0;
	int redTeamDead = 0;
	for(int i = 0; i < _greenTeam->count(); i++) {
		if(!_greenTeam->at(i)->alive) {
			greenTeamDead++;
		}
	}
	for(int i = 0; i < _redTeam->count(); i++) {
		if(!_redTeam->at(i)->alive) {
			redTeamDead++;
		}
	}
    return QString(QString::number(redTeamDead) + ":" + QString::number(greenTeamDead));
}

void Replay::saveComment(QString comment) {
	_comment = comment;
	QFile commentFile(_path + COMMENT_FILE_EXT);
	if(commentFile.open(QFile::WriteOnly | QFile::Text)) {
		QTextStream out(&commentFile);
		out << _comment;
		commentFile.close();
	}
}

void Replay::loadComment() {
	if(QFile::exists(_path + COMMENT_FILE_EXT)) {
		QFile commentFile(_path + COMMENT_FILE_EXT);
		if(commentFile.open(QFile::ReadOnly | QFile::Text)) {
			QTextStream in(&commentFile);
			_comment = in.readAll();
			commentFile.close();
		}
	}
}
