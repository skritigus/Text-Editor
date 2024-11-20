#ifndef FINDDIALOG_H
#define FINDDIALOG_H

#include <QDialog>
#include <QTextEdit>
#include <QShortcut>
#include "FindReplaceManager.h"

namespace Ui
{
    class FindDialog;
}

class FindDialog : public QDialog
{
    Q_OBJECT

    Ui::FindDialog *ui;
    QShortcut* shortcutCloseFindDialog = new QShortcut(QKeySequence::Cancel, this);
    FindReplaceManager* manager;

public:
    explicit FindDialog(QTextEdit* textEdit, QWidget* parent = nullptr);
    ~FindDialog();

    void showFinder();
    void showReplacer();

    void closeEvent(QCloseEvent* event) override;

private slots:
    void on_findButton_clicked();
    void on_findAllButton_clicked();
    void on_nextButton_clicked();
    void on_prevButton_clicked();
    void on_replaceButton_clicked();
    void on_replaceAllButton_clicked();
    void on_closeButton_clicked();
};

#endif // FINDDIALOG_H
