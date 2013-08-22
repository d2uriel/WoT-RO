#ifndef PLAYER_H
#define PLAYER_H

#include <QString>

class Player {

public:
	explicit Player();
	int			id;
	int			team;
	bool		teamKiller;
	QString		name;
	QString		clan;
	QString		vehicle;
	int			exp;
	int			damage;
	bool		alive;
	int			frags;

};

#endif // PLAYER_H
