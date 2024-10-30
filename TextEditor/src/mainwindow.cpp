#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "DialogFontStyle.h"
#include "Finder.h"
#include "Replacer.h"
#include "FontStyleManager.h"
#include <QColorDialog>
#include <QVector>
#include <QFontDialog>
#include <QListWidget>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    fileWorker = new FileWorker;
    fontFamily = new QFontComboBox;
    list = new FontStyleManager;
    Finder* finder = new Finder;
    Replacer* replacer = new Replacer;

    fontFamily->setMinimumSize(180, 26);

    ui->toolBar->addWidget(fontFamily);
    ui->toolBar->addWidget(list);

    connect(fileWorker, &FileWorker::OnTextRead, this, &MainWindow::setTextEditContent);
    connect(fileWorker, &FileWorker::OnTextOpen, this, &MainWindow::setTextEditName);
    connect(fontFamily, &QFontComboBox::currentFontChanged, this, &MainWindow::setTextEditFont);
    connect(list, &QListWidget::itemClicked, this, &MainWindow::setTextEditFontStyle);
    connect(list, &QListWidget::itemDoubleClicked, this, &MainWindow::openDialogToEditStyle);
    connect(dialog, &DialogFontStyle::onAddStyle, list, &FontStyleManager::addFontStyle);
    connect(dialog, &DialogFontStyle::onEditStyle, list, &FontStyleManager::editFontStyle);
    connect(dialog, &DialogFontStyle::onDeleteStyle, list, &FontStyleManager::deleteFontStyle);
    connect(this, &MainWindow::onPushButtonFind, finder, &Finder::find);
    connect(finder, &Finder::patternFound, this, &MainWindow::emphasizeText);
    connect(this, &MainWindow::nextPattern, finder, &Finder::next);
    connect(this, &MainWindow::prevPattern, finder, &Finder::prev);
    connect(this, &MainWindow::onPushButtonReplace, replacer, &Replacer::replace);
    connect(replacer, &Replacer::replacePattern, this, &MainWindow::replaceText);
    connect(this, &MainWindow::onPushButtonAllReplace, replacer, &Replacer::replaceAll);
    connect(replacer, &Replacer::replaceAllPatterns, this, &MainWindow::replaceAllText);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_action_triggered()
{
    ui->textEdit->clear();
    fileWorker->OpenFile();
}

void MainWindow::on_action_2_triggered()
{
    QString text;

    text = ui->textEdit->toHtml();
    fileWorker->SaveFile(text);
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

void MainWindow::setTextEditContent(QString text)
{
    ui->textEdit->setText(text);
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

void MainWindow::setTextEditFontStyle(QListWidgetItem* item)
{
    if(item->text() == "Добавить...")
    {
        dialog->pushButton_7->hide();
        dialog->open();
    }
    else
    {
        FontStyle style = list->getStyles()[list->currentRow()].getData();

        ui->textEdit->setCurrentFont(style.getFont());
        ui->textEdit->setAlignment(style.getAlign());
        ui->textEdit->setTextColor(style.getTextColor());
        ui->textEdit->setTextBackgroundColor(style.getBackgroundColor());
    }
}

void MainWindow::openDialogToEditStyle()
{
    FontStyle style = list->getStyles()[list->currentRow()].getData();

    dialog->setFontStyleInfo(style);

    dialog->pushButton_7->show();
    dialog->open();
}

void MainWindow::emphasizeText(const int& textIndex, const int& patternLength)
{
    QTextCursor cursor = ui->textEdit->textCursor();

    cursor.setPosition(textIndex, QTextCursor::MoveAnchor);
    cursor.movePosition(QTextCursor::Right, QTextCursor::KeepAnchor, patternLength);
    ui->textEdit->setTextCursor(cursor);
    //ui->textEdit->setTextBackgroundColor(QColor("orange"));
}

void MainWindow::replaceText(const List<int>& indexes, int& currentIndex, const int& patternLength)
{
    emphasizeText(indexes[currentIndex].getData(), patternLength);

    ui->textEdit->insertPlainText(ui->lineEdit_2->text());

    if (indexes.getCount() != 1)
    {
        emphasizeText(indexes[currentIndex + 1].getData(), patternLength);
    }
}

void MainWindow::replaceAllText(const List<int>& indexes, const int& patternLength)
{
    for (int i = indexes.getCount() - 1; i >= 0; --i)
    {
        emphasizeText(indexes[i].getData(), patternLength);

        ui->textEdit->insertPlainText(ui->lineEdit_2->text());
    }
}

void MainWindow::on_pushButton_9_clicked()
{
    if(!ui->lineEdit->text().isEmpty())
    {
        emit onPushButtonFind(ui->textEdit->toPlainText(), ui->lineEdit->text());
    }
}

void MainWindow::on_nextButton_clicked()
{
    emit nextPattern();
}

void MainWindow::on_prevButton_clicked()
{
    emit prevPattern();
}


void MainWindow::on_replaceButton_clicked()
{
    if(!ui->lineEdit->text().isEmpty() && !ui->lineEdit_2->text().isEmpty())
    {
        emit onPushButtonReplace(ui->textEdit->toPlainText(), ui->lineEdit->text(), ui->lineEdit_2->text().length());
    }
}


void MainWindow::on_replaceAllButton_clicked()
{
    emit onPushButtonAllReplace(ui->textEdit->toPlainText(), ui->lineEdit->text());
}

