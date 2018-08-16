#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QtCore>
#include <QtGui>
#include <QFileSystemModel>
#include <sys/stat.h>

#include "Base/envision.h"
#include "ui_filelist_widget.h"

namespace Ui {
	class FileList;
}

class FileList : public QDialog
{
	Q_OBJECT

public:
	explicit FileList(EnVision *main);
	~FileList();

	QStringList files;

	EnVision *main;


private:
	Ui::FileListUI *ui_dialog;
	QFileSystemModel *dirmodel;
	QFileSystemModel *filemodel;


	private slots:
	void on_treeView_clicked(QModelIndex index);
	void on_listView_clicked(QModelIndex index);
	void selectedItems(QString absoluteFilePath);
	void deselectedItems(QString absoluteFilePath);
	void directoryChanged(QString text);

	void dialog_exit(int val);
	void fileFilter(void);

};

#endif // DIALOG_H
