#include "CreateTableDialog.h"
#include "ui_CreateTableDialog.h"

CreateTableDialog::CreateTableDialog(QWidget *parent): QDialog(parent), ui(new Ui::CreateTableDialog)
{
    ui->setupUi(this);
}

CreateTableDialog::~CreateTableDialog()
{
    delete ui;
}

void CreateTableDialog::on_cancelButton_clicked()
{
    close();
}

void CreateTableDialog::on_OKButton_clicked()
{
    emit tableSizeChosen(ui->rowSpinBox->value(), ui->columnSpinBox->value());
    close();
}
