#include "filelist.h"
#include "ui_filelist_widget.h"


FileList::FileList(EnVision *main) : QDialog(main), ui_dialog(new Ui::FileListUI)
{
	ui_dialog->setupUi(this);
	this->main = main;

	QString defaultpath = "D://"; // main->ImageInitRecord.DefaultPath;

	//directory model left side
	dirmodel = new QFileSystemModel(this);
	dirmodel->setFilter(QDir::NoDotAndDotDot | QDir::AllDirs);
	dirmodel->setRootPath("D://");
	ui_dialog->treeView->setModel(dirmodel);
	ui_dialog->treeView->setColumnHidden(0, false);
	ui_dialog->treeView->setColumnHidden(1, true);
	ui_dialog->treeView->setColumnHidden(2, true);
	ui_dialog->treeView->setColumnHidden(3, true);
	ui_dialog->treeView->setColumnWidth(0, 500);
	ui_dialog->treeView->setColumnWidth(1, 0);
	ui_dialog->treeView->setColumnWidth(2, 0);
	ui_dialog->treeView->setColumnWidth(3, 0);

	/////////////////////////////////////////
	//filemodel right side
	filemodel = new QFileSystemModel(this);
	filemodel->setRootPath("D://");
	filemodel->setFilter(QDir::NoDotAndDotDot | QDir::AllDirs | QDir::Files);
	filemodel->setNameFilters(QStringList() << main->ImageInitRecord.ImageFormats);
	ui_dialog->listView->setModel(filemodel);

	QHeaderView *verticalHeader = ui_dialog->listView->verticalHeader();
	verticalHeader->sectionResizeMode(QHeaderView::Fixed);
	verticalHeader->setDefaultSectionSize(18);

	//fill combobox
	ui_dialog->comboBox_filetype->clear();
	foreach(const QString &format, main->ImageInitRecord.ImageFormats) {
		ui_dialog->comboBox_filetype->addItem(format);
	}
	ui_dialog->comboBox_filetype->addItem("Any file (*)");
	ui_dialog->comboBox_filetype->addItem("Image formats (*.tgd *.hyspex *.img *.mat *.im3)");
	ui_dialog->comboBox_filetype->setCurrentIndex(0);

	//ui_dialog->treeView->setRootIndex(filemodel->setRootPath(defaultpath));
	ui_dialog->listView->setRootIndex(filemodel->setRootPath(defaultpath));

	/////////////////////////////////////////
	connect(dirmodel, SIGNAL(directoryLoaded(QString)), this, SLOT(directoryChanged(QString)));
	connect(filemodel, SIGNAL(directoryLoaded(QString)), this, SLOT(directoryChanged(QString)));

	connect(ui_dialog->comboBox_filetype, static_cast<void(QComboBox::*)(const QString &)>(&QComboBox::activated),
		[=](const QString &text){ fileFilter(); });
	connect(ui_dialog->buttonBox_file, &QDialogButtonBox::accepted, this, &QDialog::accept);
	connect(ui_dialog->buttonBox_file, &QDialogButtonBox::rejected, this, &QDialog::reject);
	QObject::connect(this, SIGNAL(finished(int)), this, SLOT(dialog_exit(int)));

}

//==============================================================================
// FileList::~FileList()
//------------------------------------------------------------------------------
//==============================================================================
FileList::~FileList()
{
	delete ui_dialog;
}

//==============================================================================
// void FileList::on_treeView_clicked( QModelIndex index )
//------------------------------------------------------------------------------
//==============================================================================
void FileList::on_treeView_clicked(QModelIndex index)
{
	QString currentPath = dirmodel->fileInfo(index).absoluteFilePath();
	ui_dialog->listView->setRootIndex(filemodel->setRootPath(currentPath));
	ui_dialog->lineEdit_currentPath->setText(currentPath);
	ui_dialog->lineEdit_filename->clear();

	return;
}

//==============================================================================
// void FileList::on_listView_clicked(QModelIndex index)
//------------------------------------------------------------------------------
//==============================================================================
void FileList::on_listView_clicked(QModelIndex index)
{

	QString currentPath = filemodel->fileInfo(index).absoluteFilePath();
	ui_dialog->listView->setRootIndex(filemodel->setRootPath(currentPath));

	//cout << "path " << currentPath.toStdString() << endl;

	//expand QTreeView
	//QModelIndex inde2x = filemodel->index("C:/");
	// Set initial view of directory 
	// for the selected drive as expanded
	ui_dialog->treeView->expand(index);
	// Make it scroll to the selected
	ui_dialog->treeView->scrollTo(index);
	// Highlight the selected
	ui_dialog->treeView->setCurrentIndex(index);
	//expand QTreeView

	if (main->chosenFile.contains(currentPath) == 1)
	{
		//cout << "contains!" << currentPath.toStdString() << endl;
		//cout << "-----------" << endl;
		main->chosenFile.removeAll(currentPath);
		return;
	}

	QFileInfo fi(currentPath);
	QString basename = fi.baseName();
	QDir dir(currentPath);

	if (!dir.exists()) {
		QFile file(currentPath);
		if (file.exists() == 1){
			//qWarning("The directory does not exist, it's probably a file!");
			ui_dialog->lineEdit_filename->setText(basename);
			selectedItems(fi.absoluteFilePath());
		}
	}
	else {
		//qWarning("The directory does exist");
	}

	ui_dialog->lineEdit_currentPath->setText(currentPath);

	//comboBox_history   info2.absoluteFilePath()
	return;
}

//==============================================================================
// void FileList::dialog_exit( int result )
//------------------------------------------------------------------------------
//==============================================================================
void FileList::selectedItems(QString absoluteFilePath)
{
	QModelIndexList modelIndexList = ui_dialog->listView->selectionModel()->selectedIndexes();

	foreach(const QModelIndex &index, modelIndexList){

		QString filestring = index.data(Qt::DisplayRole).toString();
		QFileInfo fi(absoluteFilePath);
		QString extension = fi.suffix();

		foreach(const QString &selectedFilter, filemodel->nameFilters()) {
			//filter from the combobox 
			QString sfilter = selectedFilter;
			//sfilter.remove("*.");
			if (sfilter.contains(extension) == 1)
			{
				main->chosenFile.append(absoluteFilePath);
				//cout << "data: " << absoluteFilePath.toStdString() << endl;
			}
			else {

			}
		}
	}

	main->chosenFile.removeDuplicates();

	foreach(const QString &sortedfiles, main->chosenFile) {
		QString f = sortedfiles;
		cout << "file: " << f.toStdString() << endl;
		cout << "-----------" << endl;
	}

	return;
}

//==============================================================================
// void FileList::dialog_exit( int result )
//------------------------------------------------------------------------------
//==============================================================================
void FileList::deselectedItems(QString absoluteFilePath)
{



	return;
}

//==============================================================================
// void HyVision::directoryChanged( QString text )
//------------------------------------------------------------------------------
//==============================================================================
void FileList::directoryChanged(QString dir)
{
	//clear QStringList of files and alle selected items
	main->chosenFile.clear();
	ui_dialog->listView->clearSelection();
	return;
}

//==============================================================================
// void FileList::dialog_exit( int result )
//------------------------------------------------------------------------------
//==============================================================================
void FileList::dialog_exit(int result)
{
	/*
	if (result == QDialog::Accepted){


	//		QStringList selectedFiles = ui_dialog->listView->selectedFiles();
	QModelIndexList list = ui_dialog->listView->selectionModel()->selectedIndexes();

	QStringList slist;
	foreach(const QModelIndex &index, list){
	slist.append(index.data(Qt::DisplayRole).toString());
	QString s = index.data(Qt::DisplayRole).toString();

	cout << s.toStdString() << endl;
	}
	qDebug() << slist.join(",");

	} else {
	//do nothing
	}
	*/
	return;
}

//==============================================================================
// void FileList::fileFilter( void )
//------------------------------------------------------------------------------
//==============================================================================
void FileList::fileFilter(void)
{
	QString format = ui_dialog->comboBox_filetype->currentText();
	if (QString::compare(format, "Any file (*)") == 0){
		filemodel->setNameFilters(QStringList() << main->ImageInitRecord.ImageFormats);
	}
	else {
		filemodel->setNameFilters(QStringList() << format);
	}


	return;
}


/*

on backbutton clicked

on forward button clicked

*/
