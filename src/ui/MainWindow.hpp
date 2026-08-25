#pragma once

#include <QMainWindow>
#include <QString>

class QAction;
class QTextEdit;
class QDockWidget;
class QCloseEvent;

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	explicit MainWindow(QWidget *parent = nullptr);

private:
	// Setup
	void setupActions();
	void setupMenus();

	// void setupToolbar();
	void setupDockWidgets();
	void setupCentralWidget();
	void setupStatusBar();

	// File operations
	void newFile();
	void openFile();
	void saveFile();
	void saveFileAs();

	bool loadFile(const QString &path);
	bool writeFile(const QString &path);

	// State
	bool promptSave();
	void updateWindowTitle();

private:
	// State
	QString currentFile_;

	// File actions
	QAction *newAction_;
	QAction *openAction_;
	QAction *saveAction_;
	QAction *saveAsAction_;
	QAction *exitAction_;

	// Edit actions
	QAction *undoAction_;
	QAction *redoAction_;
	QAction *cutAction_;
	QAction *copyAction_;
	QAction *pasteAction_;
	QAction *deleteAction_;
	QAction *selectAllAction_;

	// Central widget
	QTextEdit *editor_;

	// Dock widgets
	QDockWidget *outlineDock_;
	QDockWidget *charactersDock_;

protected:
	void closeEvent(QCloseEvent *event) override;
};
