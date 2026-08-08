
#include "MainWindow.hpp"

#include <QAction>
#include <QDockWidget>
#include <QFileInfo>
#include <QKeySequence>
#include <QListWidget>
#include <QMenuBar>
#include <QMessageBox>
#include <QStatusBar>
#include <QTextDocument>
#include <QTextEdit>
#include <QMessageBox>
#include <QFile>
#include <QFileDialog>
#include <QTextStream>
#include <qaction.h>
#include <qfiledevice.h>
#include <qfiledialog.h>
#include <qkeysequence.h>
#include <qmessagebox.h>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
	resize(1200, 800);
	setWindowTitle("Screenwriter");

	setupActions();
	setupMenus();
	//setupToolbar();
	setupDockWidgets();
	setupCentralWidget();
	setupStatusBar();
}

void MainWindow::setupActions()
{
	newAction_ = new QAction("New", this);
	openAction_ = new QAction("Open", this);
	saveAction_ = new QAction("Save", this);
	saveAsAction_ = new QAction("Save As", this);
	exitAction_ = new QAction("Exit", this);

	undoAction_ = new QAction("Undo", this);
	redoAction_ = new QAction("Redo", this);

	newAction_->setShortcut(QKeySequence::New);
	openAction_->setShortcut(QKeySequence::Open);
	saveAction_->setShortcut(QKeySequence::Save);
	saveAsAction_->setShortcut(QKeySequence::SaveAs);
	undoAction_->setShortcut(QKeySequence::Undo);
	redoAction_->setShortcut(QKeySequence::Redo);


	connect(newAction_, &QAction::triggered, this, &MainWindow::newFile);
	connect(openAction_, &QAction::triggered, this, &MainWindow::openFile);
	connect(saveAction_, &QAction::triggered, this, &MainWindow::saveFile);
	connect(saveAsAction_, &QAction::triggered, this, &MainWindow::saveFileAs);

	connect(exitAction_, &QAction::triggered, this, &QWidget::close);
}

void MainWindow::setupMenus()
{
	auto *fileMenu = menuBar()->addMenu("&File");
	fileMenu->addAction(newAction_);
	fileMenu->addAction(openAction_);
	fileMenu->addAction(saveAction_);
	fileMenu->addAction(saveAsAction_);
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

void MainWindow::setupCentralWidget()
{
	editor_ = new QTextEdit(this);
	connect(editor_->document(), &QTextDocument::modificationChanged, this, [this](){ updateWindowTitle(); } );
	setCentralWidget(editor_);
}

void MainWindow::setupStatusBar()
{
	statusBar()->showMessage("Ready");
}

bool MainWindow::promptSave()
{
	if (!editor_->document()->isModified()) return true;

	auto reply = QMessageBox::warning(this, "Unsaved Changes", "The document has been modified.\nDo you want to save your changes?", 
				   QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel
	);

	switch (reply)
	{
		case QMessageBox::Save:
			saveFile();
			return !editor_->document()->isModified();

		case QMessageBox::Discard:
			return true;

		default:
			return false;
	}
}

void MainWindow::updateWindowTitle()
{
	QString name;

	if (currentFile_.isEmpty())
	{
		name = "Untitled";
	} 
	else
	{
		name = QFileInfo(currentFile_).fileName();
	}

	if (editor_->document()->isModified()) name += "*";

	setWindowTitle(name + " - Screenwriter");
}

void MainWindow::newFile()
{
	if (!promptSave()) return;
	
	editor_->clear();
	currentFile_.clear();
	editor_->document()->setModified(false);
	updateWindowTitle();
	
}

void MainWindow::openFile() 
{
	if (!promptSave())
	{
		return;
	}

	QString path = QFileDialog::getOpenFileName(this, "Open File", "", "Text Files (*.txt);;All Files (*)" );
	if (path.isEmpty()) return;

	loadFile(path);
}

bool MainWindow::loadFile(const QString &path)
{
	QFile file(path);

	if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
	{
		QMessageBox::critical(this, "Error", "Unable to open file.");
		return false;
	}

	
	QTextStream in(&file);
	editor_->setPlainText(in.readAll());
	file.close();

	currentFile_ = path;
	editor_->document()->setModified(false);

	updateWindowTitle();
	statusBar()->showMessage("Opened " + QFileInfo(path).fileName(), 3000);

	return true;
}

void MainWindow::saveFile() 
{
	if (currentFile_.isEmpty()) {
		saveFileAs();
		return;
	}

	writeFile(currentFile_);
}

void MainWindow::saveFileAs() 
{
	QString path = QFileDialog::getSaveFileName(this, "Save File", "", "Text Files (*.txt);;All Files (*)");

	if (path.isEmpty()) return;

	writeFile(path);
}

bool MainWindow::writeFile(const QString &path) 
{
	QFile file(path);

	if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
	{
		QMessageBox::critical(this, "Error", "Unable to save file.");
		return false;
	}

	QTextStream out(&file);
	out << editor_->toPlainText();
	
	file.close();

	currentFile_ = path;
	editor_->document()->setModified(false);

	updateWindowTitle();
	statusBar()->showMessage("Saved " + QFileInfo(path).fileName(), 3000);

	return true;
}











