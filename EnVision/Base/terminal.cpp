#include "terminal.h"

//==============================================================================
//------------------------------------------------------------------------------
//==============================================================================
Terminal::Terminal()
{
}

//==============================================================================
//------------------------------------------------------------------------------
//==============================================================================
Terminal::~Terminal()
{
}

//==============================================================================
// QString Terminal::Log(Ui::EnVision_baseUI *obj, QString qstr)
//------------------------------------------------------------------------------
//==============================================================================
QString Terminal::Log(Ui::EnVision_baseUI *obj, QString qstr)
{
		obj->listWidget_term->addItem(qstr);
		obj->listWidget_term->scrollToBottom();

	return qstr;
}

//==============================================================================
// std::string Terminal::Log(Ui::EnVision_baseUI *obj, std::string str)
//------------------------------------------------------------------------------
//==============================================================================
std::string Terminal::Log(Ui::EnVision_baseUI *obj, std::string str)
{
		obj->listWidget_term->addItem(QString::fromStdString(str));
		obj->listWidget_term->scrollToBottom();
	return str;
}