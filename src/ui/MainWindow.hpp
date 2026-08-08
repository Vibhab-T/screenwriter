#pragma once

#include <QMainWindow>

class QTextEdit;
class QDockWidget;

class MainWindow : public QMainWindow
{
	Q_OBJECT
public:
	explicit MainWindow(QWidget *parent = nullptr);

private:
	//methods
	

	void setupActions();
	void setupMenus();
	//void setupToolbar();
	void setupDockWidgets();
	void setupCentralWidget();
	void setupStatusBar();

	void newFile();
	void openFile();
	void saveFile();
	void saveFileAs();


	bool loadFile(const QString &path);
	bool writeFile(const QString &path);

	bool promptSave();
	void updateWindowTitle();

private:
	//states
	QString currentFile_;


	QAction *newAction_;
	QAction *openAction_;
	QAction *saveAction_;
	QAction *saveAsAction_;
	QAction *exitAction_;
	QAction *undoAction_;
	QAction *redoAction_;
	

	QTextEdit *editor_;
	
	QDockWidget *outlineDock_;
	QDockWidget *charactersDock_;
};
