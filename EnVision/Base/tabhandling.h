#ifndef TABHANDLING_H
#define TABHANDLING_H

#include <QVector>

#include "ui_envision.h"
#include "ui_table_widget.h"
#include "ui_plot_widget.h"
#include "ui_image_widget.h"
#include "Gui/gui_master.h"

class EnVision;

class TabHandling : public QObject
{
	Q_OBJECT

	public:
	TabHandling(EnVision *main);
	~TabHandling();

	int ind_tab_movedTo = 0;
	int ind_tab_movedFrom = 0;
	static int lastIndexTab_Table;
	static int lastIndexTab_Plot;
	static int lastIndexTab_Image;

	static int missingIndexTab_Table;
	static int missingIndexTab_Plot;
	static int missingIndexTab_Image;

	static QVector<int> orderTabs_Table;
	static QVector<int> orderTabs_Plot;
	static QVector<int> orderTabs_Image;


	template <typename...> class Tabs;

	template <typename A, typename B, typename C, typename D>
	class Tabs<A, B, C, D>
	{
	public:
		//add index to QVector taborder
		QVector<int> add(C index, D order){
			order.append(index);
			//QVectorIterator<int> k(taborder);
			//while (k.hasNext()){qDebug() << k.next() << " " << order.size();}
			return order;
		}
		//remove index from QVector taborder
		QVector<int> sub(C index, D order){
			order.remove(index);
			//QVectorIterator<int> k(taborder);
			//while (k.hasNext()){qDebug() << k.next() << " " << order.size();}
			return order;
		}
		//swap index1 with index2 in QVector taborder
		QVector<int> swap(B index1, C index2, D order){
			int temp = order.at(index2);
			order.replace(index2, order.at(index1));
			order.replace(index1, temp);
			return order;
		}

		A a_; B b_; C c_; D d_;
	};
	Tabs< int, int, int, QVector<int> > toTab;

	void guiAccess();

	public slots:
	void handleTabCloseButtons(QTabBar *t, int ind_hide, int ind_show);
	void addWidget_table(QWidget* widget, QObject* obj, QString msg, QVector<int>);
	void addWidget_plot(QWidget* widget, QObject* obj, QString msg, QVector<int>);
	void addWidget_image(QWidget* widget, QObject* obj, QString msg, QVector<int>);
	void closeWidget_table(QWidget* widget, QObject* obj, QString msg, QVector<int>);
	void closeWidget_plot(QWidget* widget, QObject* obj, QString msg, QVector<int>);
	void closeWidget_image(QWidget* widget, QObject* obj, QString msg, QVector<int>);
	void moveWidget_table(QWidget* widget, QObject* obj, QString msg, QVector<int> index);
	void moveWidget_plot(QWidget* widget, QObject* obj, QString msg, QVector<int>);
	void moveWidget_image(QWidget* widget, QObject* obj, QString msg, QVector<int>);

private:
	EnVision *main;
	Ui::EnVision_baseUI *ui_base;
	Ui::EnVision_tableUI *ui_table;
	Ui::EnVision_plotUI *ui_plot;
	Ui::EnVision_imageUI *ui_image;
};

#endif // TABHANDLING_H