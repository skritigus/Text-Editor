#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    findDialog = new FindDialog(ui->textEdit);

    fontFamily->setMinimumSize(180, 26);

    ui->toolBar->addWidget(fontFamily);
    ui->toolBar->addWidget(list);

    connect(fileWorker, &FileWorker::onTextRead, this, &MainWindow::setTextEditContent);
    connect(fileWorker, &FileWorker::onTextOpen, this, &MainWindow::setTextEditName);

    connect(fontFamily, &QFontComboBox::currentFontChanged, this, &MainWindow::setTextEditFont);

    connect(list, &FontStyleManager::fontStyleChosen, this, &MainWindow::setTextEditFontStyle);

    connect(shortcutReplace, &QShortcut::activated, findDialog, &FindDialog::showReplacer);
    connect(shortcutFind, &QShortcut::activated, findDialog, &FindDialog::showFinder);
}

MainWindow::~MainWindow()
{
    delete fileWorker;
    delete shortcutFind;
    delete shortcutReplace;
    delete findDialog;
    delete list;
    delete fontFamily;
    delete ui;
}

void MainWindow::setTextEditContent(QString text)
{
    ui->textEdit->setHtml(text);
}

void MainWindow::setTextEditFont(const QFont& font)
{
    ui->textEdit->setFontFamily(font.family());
}

void MainWindow::setTextEditName(QString fileName)
{
    fileName = "Sigma Text - " + fileName;
    this->setWindowTitle(fileName);
}

void MainWindow::setTextEditFontStyle(const FontStyle& style)
{
    ui->textEdit->setCurrentFont(style.getFont());
    ui->textEdit->setAlignment(style.getAlign());
    ui->textEdit->setTextColor(style.getTextColor());
    ui->textEdit->setTextBackgroundColor(style.getBackgroundColor());
}

void MainWindow::swapCursorPos()
{
    int anchorPos = ui->textEdit->textCursor().anchor();
    int cursorPos = ui->textEdit->textCursor().position();

    if (anchorPos > cursorPos)
    {
        int length = anchorPos - cursorPos;
        QTextCursor cursor = ui->textEdit->textCursor();

        cursor.clearSelection();
        cursor.movePosition(QTextCursor::Right, QTextCursor::KeepAnchor, length);
        ui->textEdit->setTextCursor(cursor);
    }
}

void MainWindow::on_openAction_triggered()
{
    ui->textEdit->clear();
    fileWorker->openFile();
}

void MainWindow::on_saveAsAction_triggered()
{
    QString text;

    text = ui->textEdit->toHtml();
    fileWorker->saveFile(text);
}

void MainWindow::on_actionItalic_triggered()
{
    swapCursorPos();

    ui->textEdit->setFontItalic(!ui->textEdit->fontItalic());
}

void MainWindow::on_actionBold_triggered()
{
    swapCursorPos();

    if (ui->textEdit->fontWeight() == 400)
    {
        ui->textEdit->setFontWeight(700);
    }
    else
    {
        ui->textEdit->setFontWeight(400);
    }
}

void MainWindow::on_actionUnderline_triggered()
{
    swapCursorPos();

    ui->textEdit->setFontUnderline(!ui->textEdit->fontUnderline());
}
