#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "FontStyleManager.h"
#include <QListWidget>
#include <QMainWindow>
#include <QFontComboBox>
#include <QShortcut>
#include "FileWorker.h"
#include "FindDialog.h"

QT_BEGIN_NAMESPACE
namespace Ui
{
    class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

    Ui::MainWindow* ui;
    FileWorker* fileWorker = new FileWorker;
    QFontComboBox* fontFamily = new QFontComboBox;
    FontStyleManager* list = new FontStyleManager;
    FindDialog* findDialog;
    QShortcut* shortcutFind = new QShortcut(QKeySequence::Find, this);
    QShortcut* shortcutReplace = new QShortcut(QKeySequence::Replace, this);

    void setTextEditContent(QString text);
    void setTextEditName(QString fileName);
    void setTextEditFont(const QFont& font);
    void setTextEditFontStyle(const FontStyle& style);

    void swapCursorPos();

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_openAction_triggered();
    void on_saveAsAction_triggered();

    void on_actionItalic_triggered();
    void on_actionBold_triggered();
    void on_actionUnderline_triggered();
};
#endif // MAINWINDOW_H
