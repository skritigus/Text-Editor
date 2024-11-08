#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "DialogFontStyle.h"
#include "FontStyleManager.h"
#include <QShortcut>
#include <QListWidget>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    auto* shortcutFind = new QShortcut(QKeySequence::Find, this);
    auto* shortcutReplace = new QShortcut(QKeySequence::Replace, this);

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

    connect(this, &MainWindow::activateFinder, findWidget, &FindWidget::showFinder);
    connect(this, &MainWindow::activateReplacer, findWidget, &FindWidget::showReplacer);
    connect(findWidget, &FindWidget::foundPattern, this, &MainWindow::emphasizeText);
    connect(findWidget, &FindWidget::replacePattern, this, &MainWindow::replaceText);
    connect(findWidget, &FindWidget::replaceAllPatterns, this, &MainWindow::setTextEditContent);
    connect(findWidget, &FindWidget::foundAllPattern, this, &MainWindow::emphasizeAllPatterns);
    connect(findWidget, &FindWidget::widgetClosed, this, &MainWindow::resetFlags);

    connect(shortcutReplace, &QShortcut::activated, this, &MainWindow::callReplacer);
    connect(shortcutFind, &QShortcut::activated, this, &MainWindow::callFinder);
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

    if(isTextEmphasized && !isReplacerCalled)
    {
        ui->textEdit->undo();
    }
    else
    {
        isTextEmphasized = true;
    }

    cursor.setPosition(textIndex, QTextCursor::MoveAnchor);
    cursor.movePosition(QTextCursor::Right, QTextCursor::KeepAnchor, patternLength);
    ui->textEdit->setTextCursor(cursor);
    if(!isReplacerCalled)
    {
        ui->textEdit->setTextBackgroundColor(QColor("orange"));
    }
}

void MainWindow::replaceText(List<int>& indexes, int& currentIndex, const int& patternLength, const QString& replacing)
{
    if(!isTextEmphasized)
    {
        emphasizeText(indexes[currentIndex].getData(), patternLength);
        isTextEmphasized = true;
        return;
    }

    ui->textEdit->insertPlainText(replacing);
    indexes.deleteByIndex(currentIndex);

    if(currentIndex == indexes.getCount())
    {
        --currentIndex;
    }

    if (currentIndex != -1)
    {
        emphasizeText(indexes[currentIndex].getData(), patternLength);
    }
}

void MainWindow::callFinder()
{
    emit activateFinder(ui->textEdit->toPlainText(), ui->textEdit->textCursor());
}


void MainWindow::callReplacer()
{
    isReplacerCalled = true;
    emit activateReplacer(ui->textEdit->toPlainText());
}

void MainWindow::resetFlags()
{
    isTextEmphasized = false;
    isReplacerCalled = false;
}

void MainWindow::emphasizeAllPatterns(QList<QTextEdit::ExtraSelection>& selections, const List<int>& indexes, const int& currentIndex, const int& patternLength)
{
    QTextCursor cursor = ui->textEdit->textCursor();
    QTextCharFormat backgroundColor;

    if(!isTextEmphasized)
    {
        isTextEmphasized = true;

        backgroundColor.setBackground(QColor("orange"));
        selections.push_back(QTextEdit::ExtraSelection{cursor, backgroundColor});
    }

    cursor.setPosition(indexes[currentIndex].getData());
    cursor.movePosition(QTextCursor::Right, QTextCursor::KeepAnchor, patternLength);

    selections.last().cursor = cursor;

    ui->textEdit->setExtraSelections(selections);
}

void MainWindow::on_clearButton_clicked()
{
    QList<QTextEdit::ExtraSelection> selections;
    ui->textEdit->setExtraSelections(selections);
}

