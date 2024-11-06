#include "FindWidget.h"
#include "ui_FindWidget.h"
#include "Finder.h"
#include "Replacer.h"
#include <QShortcut>

FindWidget::FindWidget(QWidget* parent) : ui(new Ui::FindWidget)
{
    ui->setupUi(this);

    ui->widget_2->hide();
    ui->listWidget->hide();
    ui->listWidget_2->hide();

    QShortcut* shortcutCloseFindWidget = new QShortcut(QKeySequence::Cancel, this);

    connect(shortcutCloseFindWidget, &QShortcut::activated, this, &FindWidget::on_closeButton_clicked);
}

FindWidget::~FindWidget()
{
    delete finder;
    finder = nullptr;
    delete ui;
}

void FindWidget::on_findButton_clicked()
{
    if(!ui->lineEdit->text().isEmpty())
    {
        finder->performSingle(text, ui->lineEdit->text(), "");
        ui->listWidget->insertItem(0, ui->lineEdit->text());

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
        emit foundPattern(finder->getTextIndex(), ui->lineEdit->text().length());
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
        emit foundPattern(finder->getTextIndex(), ui->lineEdit->text().length());
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
    ui->listWidget->insertItem(0, ui->lineEdit->text());
    ui->listWidget_2->insertItem(0, ui->lineEdit_2->text());
    emit replacePattern(finder->getIndexes(), finder->getCurrentIndex(), ui->lineEdit->text().length(), ui->lineEdit_2->text());
}


void FindWidget::on_replaceAllButton_clicked()
{
    if(!ui->lineEdit->text().isEmpty() && !ui->lineEdit_2->text().isEmpty())
    {
        finder->performAll(text, ui->lineEdit->text(), ui->lineEdit_2->text());
        ui->listWidget->insertItem(0, ui->lineEdit->text());
        ui->listWidget_2->insertItem(0, ui->lineEdit_2->text());
        emit onPushButtonAllReplace(text);
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

void FindWidget::on_pushButton_clicked()
{
    ui->listWidget->show();
}


void FindWidget::on_pushButton_8_clicked()
{
    ui->listWidget_2->show();
}

void FindWidget::showFinder(const QString& newText)
{
    finder = new Finder;
    text = newText;
    this->show();
}

void FindWidget::showReplacer(const QString& newText)
{
    finder = new Replacer;
    text = newText;
    this->show();
    ui->widget_2->show();
}

/*void FindWidget::on_textEdit_textChanged()
{
    emit stopFind();
}
*/
