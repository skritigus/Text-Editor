#include "FindDialog.h"
#include "ui_FindDialog.h"

FindDialog::FindDialog(QWidget* parent)
    : QDialog(parent), ui(new Ui::FindDialog), manager(new FindReplaceManager)
{
    ui->setupUi(this);

    ui->replaceWidget->hide();

    connect(ui->findLineEdit, &QLineEdit::editingFinished, manager, &FindReplaceManager::resetResults);
    connect(ui->replaceLineEdit, &QLineEdit::editingFinished, manager, &FindReplaceManager::resetResults);
}

FindDialog::~FindDialog()
{
    delete manager;
    delete ui;
}

void FindDialog::showFinder()
{
    if(isHidden())
    {
        manager->setForFind();

        ui->replaceWidget->hide();
        ui->findAllButton->show();
        ui->findButton->show();

        setWindowTitle("Найти");
        show();
    }
}

void FindDialog::showReplacer()
{
    if(isHidden())
    {
        manager->setForReplace();

        ui->replaceWidget->show();
        ui->findAllButton->hide();
        ui->findButton->hide();

        setWindowTitle("Заменить");
        show();
    }
}

void FindDialog::closeEvent(QCloseEvent*)
{
    manager->resetResults();
    manager->disableConnections();
}


void FindDialog::on_findButton_clicked()
{
    QString pattern = ui->findLineEdit->text();

    if(!pattern.isEmpty())
    {
        manager->findPattern(pattern);
    }
}

void FindDialog::on_findAllButton_clicked()
{
    QString pattern = ui->findLineEdit->text();

    if(!pattern.isEmpty())
    {
        manager->findAllPatterns(pattern);
    }
}

void FindDialog::on_nextButton_clicked()
{
    manager->nextPattern(ui->findLineEdit->text());
}

void FindDialog::on_prevButton_clicked()
{
    manager->prevPattern(ui->findLineEdit->text());
}

void FindDialog::on_replaceButton_clicked()
{
    QString pattern = ui->findLineEdit->text();
    QString replacing = ui->replaceLineEdit->text();

    if(!pattern.isEmpty() && !replacing.isEmpty())
    {
        manager->replacePattern(pattern, replacing);
    }
}

void FindDialog::on_replaceAllButton_clicked()
{
    QString pattern = ui->findLineEdit->text();
    QString replacing = ui->replaceLineEdit->text();

    if(!pattern.isEmpty() && !replacing.isEmpty())
    {
        manager->replaceAllPatterns(pattern, replacing);
    }
}

void FindDialog::on_closeButton_clicked()
{
    close();
}
