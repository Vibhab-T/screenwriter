#include "MainWindow.hpp"

#include <QAction>
#include <QDockWidget>
#include <QListWidget>
#include <QMenuBar>
#include <QStatusBar>
#include <QTextEdit>
#include <QToolBar>
#include <QKeySequence> 
#include <qdockwidget.h>
#include <qlistwidget.h>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
	resize(1200, 800);
	setWindowTitle("Screenwriter");

	setupActions();
	setupMenus();
	//setupToolbar();
	setupDockWidgets();
	setupCentralWidgets();
	setupStatusBar();
}

void MainWindow::setupActions()
{
	newAction_ = new QAction("New", this);
	openAction_ = new QAction("Open", this);
	saveAction_ = new QAction("Save", this);
	exitAction_ = new QAction("Exit", this);

	undoAction_ = new QAction("Undo", this);
	redoAction_ = new QAction("Redo", this);

	newAction_->setShortcut(QKeySequence::New);
	openAction_->setShortcut(QKeySequence::Open);
	saveAction_->setShortcut(QKeySequence::Save);
	undoAction_->setShortcut(QKeySequence::Undo);
	redoAction_->setShortcut(QKeySequence::Redo);

	connect(exitAction_, &QAction::triggered, this, &QWidget::close);
}

void MainWindow::setupMenus()
{
	auto *fileMenu = menuBar()->addMenu("&File");
	fileMenu->addAction(newAction_);
	fileMenu->addAction(openAction_);
	fileMenu->addAction(saveAction_);
	fileMenu->addSeparator();
	fileMenu->addAction(exitAction_);
	
	auto *editMenu = menuBar()->addMenu("&Edit");
	editMenu->addAction(undoAction_);
	editMenu->addAction(redoAction_);
}

//void MainWindow::setupToolbar(){}

void MainWindow::setupDockWidgets()
{
	outlineDock_ = new QDockWidget("Outline", this);
	auto *outlineList = new QListWidget(outlineDock_);
	outlineDock_->setWidget(outlineList);
	addDockWidget(Qt::LeftDockWidgetArea, outlineDock_);

	charactersDock_ = new QDockWidget("Characters", this);
	auto *characterList = new QListWidget(charactersDock_);
	charactersDock_->setWidget(characterList);
	addDockWidget(Qt::LeftDockWidgetArea, charactersDock_);
}

void MainWindow::setupCentralWidgets()
{
	editor_ = new QTextEdit(this);
	setCentralWidget(editor_);
}

void MainWindow::setupStatusBar()
{
	statusBar()->showMessage("Ready");
}
