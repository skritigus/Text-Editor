#include "FindDialog.h"
#include "ui_FindDialog.h"

FindDialog::FindDialog(QTextEdit* textEdit, QWidget* parent)
    : QDialog(parent), ui(new Ui::FindDialog), manager(new FindReplaceManager(textEdit))
{
    ui->setupUi(this);

    ui->replaceWidget->hide();

    connect(shortcutCloseFindDialog, &QShortcut::activated, this, &FindDialog::on_closeButton_clicked);
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
    manager->setForFind();

    ui->replaceWidget->hide();
    ui->findAllButton->show();
    ui->findButton->show();

    this->setWindowTitle("Найти");
    this->show();
}

void FindDialog::showReplacer()
{
    manager->setForReplace();

    this->setWindowTitle("Заменить");
    this->show();
    ui->replaceWidget->show();

    ui->findAllButton->hide();
    ui->findButton->hide();
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
    this->close();
}

void FindDialog::closeEvent(QCloseEvent*)
{
    manager->resetResults();
    manager->disableConnections();
}

