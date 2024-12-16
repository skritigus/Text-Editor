#ifndef CREATETABLEDIALOG_H
#define CREATETABLEDIALOG_H

#include <QDialog>

namespace Ui
{
    class CreateTableDialog;
}

class CreateTableDialog : public QDialog
{
    Q_OBJECT

    Ui::CreateTableDialog *ui;

public:
    explicit CreateTableDialog(QWidget *parent = nullptr);
    ~CreateTableDialog();

signals:
    void tableSizeChosen(const int& rows, const int& columns);

private slots:
    void on_cancelButton_clicked();
    void on_OKButton_clicked();
};

#endif // CREATETABLEDIALOG_H
