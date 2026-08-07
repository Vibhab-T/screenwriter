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
	void setupActions();
	void setupMenus();
	//void setupToolbar();
	void setupDockWidgets();
	void setupCentralWidgets();
	void setupStatusBar();

private:
	
	QAction *newAction_;
	QAction *openAction_;
	QAction *saveAction_;
	QAction *exitAction_;
	QAction *undoAction_;
	QAction *redoAction_;
	

	QTextEdit *editor_;
	
	QDockWidget *outlineDock_;
	QDockWidget *charactersDock_;
};
