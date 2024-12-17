#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "BackgroundColorButton.h"
#include "FontStyleManager.h"
#include "TextColorButton.h"
#include "TextEditManager.h"
#include "FileManager.h"
#include "FileTab.h"
#include "FindDialog.h"
#include <QMainWindow>
#include <QFontComboBox>
#include <QSpinBox>
#include <QMenu>

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
    FileManager* fileManager;
    TextColorButton* textColorButton = new TextColorButton;
    BackgroundColorButton* backgroundColorButton = new BackgroundColorButton;
    QFontComboBox* fontFamily = new QFontComboBox;
    QSpinBox* fontSizeSpinBox = new QSpinBox;
    QMenu* formatTableMenu = new QMenu("Tаблица", this);
    TextEditManager* textEdit;
    FontStyleManager* styleManager;
    FindDialog* findDialog;
    FileTab* fileTab = new FileTab;
    bool isFormatTableMenu = false;

    void setTextEditorName(QString filePath);

    void swapCursorPos();

    void showTableFormatMenu();

    void setFontSize(const int& fontSize);
    void setCurrentStyleInfo(const FontStyle& style);
    void setCurrentCursorStyleInfo();
    void setAlignChecked(const Qt::Alignment& align);

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void closeEvent(QCloseEvent* event) override;

private slots:
    void on_createAction_triggered();
    void on_openAction_triggered();
    void on_saveAsAction_triggered();
    void on_saveAction_triggered();
    void on_printAction_triggered();

    void on_actionItalic_triggered();
    void on_actionBold_triggered();
    void on_actionUnderline_triggered();

    void on_leftAlignAction_triggered();
    void on_centerAlignAction_triggered();
    void on_rightAlignAction_triggered();
    void on_justifyAlignAction_triggered();
};

#endif // MAINWINDOW_H
