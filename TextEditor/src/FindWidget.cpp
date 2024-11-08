#include "FindWidget.h"
#include "ui_FindWidget.h"
#include "Finder.h"
#include "Replacer.h"
#include <QShortcut>

FindWidget::FindWidget(QWidget* parent) : ui(new Ui::FindWidget)
{
    ui->setupUi(this);

    this->setWindowFlags(Qt::WindowStaysOnTopHint);
    ui->widget_2->hide();

    auto* shortcutCloseFindWidget = new QShortcut(QKeySequence::Cancel, this);

    connect(shortcutCloseFindWidget, &QShortcut::activated, this, &FindWidget::on_closeButton_clicked);
}

FindWidget::~FindWidget()
{
    isFindAllClicked = false;

    delete finder;
    finder = nullptr;
    delete ui;
}

void FindWidget::on_findButton_clicked()
{
    if(!ui->lineEdit->text().isEmpty())
    {
        finder->performSingle(text, ui->lineEdit->text(), "");

        if(finder->getCurrentIndex() == -1)
        {
            return;
        }
        emit foundPattern(finder->getTextIndex(), ui->lineEdit->text().length());
    }
}

void FindWidget::on_nextButton_clicked()
{
    if(finder->getCurrentIndex() == -1)
    {
        on_findButton_clicked();
        return;
    }

    if(finder->getIndexes().getCount() != 0)
    {
        finder->next();

        if(isFindAllClicked)
        {
            emit foundAllPattern(dynamic_cast<Finder*>(finder)->getSelections(), finder->getIndexes(), finder->getCurrentIndex(), ui->lineEdit->text().length());
        }
        else
        {
            emit foundPattern(finder->getTextIndex(), ui->lineEdit->text().length());
        }
    }
}

void FindWidget::on_prevButton_clicked()
{
    if(finder->getCurrentIndex() == -1)
    {
        on_findButton_clicked();
        return;
    }

    if(finder->getIndexes().getCount() != 0)
    {
        finder->prev();

        if(isFindAllClicked)
        {
            emit foundAllPattern(dynamic_cast<Finder*>(finder)->getSelections(), finder->getIndexes(), finder->getCurrentIndex(), ui->lineEdit->text().length());
        }
        else
        {
            emit foundPattern(finder->getTextIndex(), ui->lineEdit->text().length());
        }
    }
}

void FindWidget::on_replaceButton_clicked()
{
    if(ui->lineEdit->text().isEmpty() || ui->lineEdit_2->text().isEmpty())
    {
        return;
    }

    finder->performSingle(text, ui->lineEdit->text(), ui->lineEdit_2->text());

    if(finder->getCurrentIndex() == -1 || finder->getIndexes().getCount() == 0)
    {
        return;
    }
    emit replacePattern(finder->getIndexes(), finder->getCurrentIndex(), ui->lineEdit->text().length(), ui->lineEdit_2->text());
}


void FindWidget::on_replaceAllButton_clicked()
{
    if(!ui->lineEdit->text().isEmpty() && !ui->lineEdit_2->text().isEmpty())
    {
        finder->performAll(text, ui->lineEdit->text(), ui->lineEdit_2->text());
        emit replaceAllPatterns(text);
    }
}

void FindWidget::on_closeButton_clicked()
{
    this->close();
    emit widgetClosed();
    ui->widget_2->hide();

    delete finder;
    finder = nullptr;
}

void FindWidget::showFinder(const QString& newText, const QTextCursor& textCursor)
{
    finder = new Finder;
    text = newText;
    dynamic_cast<Finder*>(finder)->setCursor(textCursor);
    this->setObjectName("Find");
    this->show();
}

void FindWidget::showReplacer(const QString& newText)
{
    finder = new Replacer;
    text = newText;

    this->setObjectName("Replace");
    this->show();
    ui->widget_2->show();

    ui->findAllButton->hide();
    ui->findButton->hide();
}

void FindWidget::on_findAllButton_clicked()
{   
    if(!ui->lineEdit->text().isEmpty())
    {
        finder->performAll(text, ui->lineEdit->text(), "");

        if(finder->getCurrentIndex() == -1)
        {
            return;
        }

        isFindAllClicked = true;
        emit foundAllPattern(dynamic_cast<Finder*>(finder)->getSelections(), finder->getIndexes(), finder->getCurrentIndex(), ui->lineEdit->text().length());
    }
}

