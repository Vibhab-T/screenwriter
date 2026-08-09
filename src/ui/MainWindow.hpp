#pragma once

#include <QMainWindow>
#include <qaction.h>
#include <qwidget.h>

class QTextEdit;
class QDockWidget;
class QCloseEvent;

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

	QAction *cutAction_;
	QAction *copyAction_;
	QAction *pasteAction_;
	QAction *deleteAction_;
	QAction *selectAllAction_;

	QTextEdit *editor_;
	
	QDockWidget *outlineDock_;
	QDockWidget *charactersDock_;

protected:
	void closeEvent(QCloseEvent *event) override;
};
