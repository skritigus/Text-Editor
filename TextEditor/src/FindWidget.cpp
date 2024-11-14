#include "FindWidget.h"
#include "ui_FindWidget.h"
#include "Finder.h"
#include "Replacer.h"
#include <QShortcut>

FindWidget::FindWidget(QWidget* parent) : QWidget(parent), ui(new Ui::FindWidget)
{
    ui->setupUi(this);

    this->setWindowFlags(Qt::WindowStaysOnTopHint);
    ui->replaceWidget->hide();

    connect(shortcutCloseFindWidget, &QShortcut::activated, this, &FindWidget::on_closeButton_clicked);
}

FindWidget::~FindWidget()
{
    isFindAllClicked = false;

    if(finder != nullptr)
    {
        delete finder;
        finder = nullptr;
    }
    delete ui;
}

void FindWidget::showFinder(const QString& newText, const QTextCursor& textCursor)
{
    finder = new Finder;
    text = newText;
    dynamic_cast<Finder*>(finder)->setCursor(textCursor);

    ui->replaceWidget->hide();
    ui->findAllButton->show();
    ui->findButton->show();

    this->setWindowTitle("Find");
    this->show();
}

void FindWidget::showReplacer(const QString& newText)
{
    finder = new Replacer;
    text = newText;

    this->setWindowTitle("Replace");
    this->show();
    ui->replaceWidget->show();

    ui->findAllButton->hide();
    ui->findButton->hide();
}

void FindWidget::on_findButton_clicked()
{
    isFindAllClicked = false;
    QString pattern = ui->findLineEdit->text();

    if(!pattern.isEmpty())
    {
        finder->performSingle(text, pattern, "");

        if(finder->getCurrentIndex() == -1)
        {
            return;
        }
        emit foundPattern(finder->getTextIndex(), pattern.length());
    }
}

void FindWidget::on_findAllButton_clicked()
{
    QString pattern = ui->findLineEdit->text();

    if(!pattern.isEmpty())
    {
        finder->performAll(text, pattern, "");

        if(finder->getCurrentIndex() == -1)
        {
            return;
        }

        isFindAllClicked = true;
        emit foundAllPattern(dynamic_cast<Finder*>(finder)->getSelections(), finder->getIndexes(), finder->getCurrentIndex(), pattern.length());
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
            emit foundAllPattern(dynamic_cast<Finder*>(finder)->getSelections(), finder->getIndexes(), finder->getCurrentIndex(), ui->findLineEdit->text().length());
        }
        else
        {
            emit foundPattern(finder->getTextIndex(), ui->findLineEdit->text().length());
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
            emit foundAllPattern(dynamic_cast<Finder*>(finder)->getSelections(), finder->getIndexes(), finder->getCurrentIndex(), ui->findLineEdit->text().length());
        }
        else
        {
            emit foundPattern(finder->getTextIndex(), ui->findLineEdit->text().length());
        }
    }
}

void FindWidget::on_replaceButton_clicked()
{
    QString pattern = ui->findLineEdit->text();
    QString replacing = ui->replaceLineEdit->text();

    if(pattern.isEmpty() || replacing.isEmpty())
    {
        return;
    }

    finder->performSingle(text, pattern, replacing);

    if(finder->getCurrentIndex() == -1 || finder->getIndexes().getCount() == 0)
    {
        return;
    }
    emit replacePattern(finder->getIndexes(), finder->getCurrentIndex(), pattern.length(), replacing);
}


void FindWidget::on_replaceAllButton_clicked()
{
    QString pattern = ui->findLineEdit->text();
    QString replacing = ui->replaceLineEdit->text();

    if(!pattern.isEmpty() && !replacing.isEmpty())
    {
        finder->performAll(text, pattern, replacing);
        emit replaceAllPatterns(text);
    }
}

void FindWidget::on_closeButton_clicked()
{
    this->close();
    emit widgetClosed();
    ui->replaceWidget->hide();

    delete finder;
    finder = nullptr;
}
