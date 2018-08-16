#ifndef TERMINAL_H
#define TERMINAL_H

#include <QOBJECT>
#include <iostream>
#include <QString>

#include "ui_envision.h"

class Terminal
{

public:
	Terminal();
	~Terminal();

	QString Log(Ui::EnVision_baseUI *obj, QString qstr);
	std::string Log(Ui::EnVision_baseUI *obj, std::string str);
			
private:
};

#endif // TERMINAL_H





