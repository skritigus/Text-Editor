#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "FontStyleManager.h"
#include <QListWidget>
#include <QMainWindow>
#include <QFontComboBox>
#include "FileWorker.h"
#include "FindWidget.h"
#include "DialogFontStyle.h"
#include "List.h"

QT_BEGIN_NAMESPACE
namespace Ui
{
    class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

signals:
    void activateFinder(const QString& text);
    void activateReplacer(const QString& text);

private slots:
    void on_action_triggered();
    void on_action_2_triggered();

    void on_actionItalic_triggered();
    void on_actionBold_triggered();
    void on_actionUnderline_triggered();

private:
    Ui::MainWindow *ui;

    FileWorker* fileWorker;
    QFontComboBox* fontFamily;
    FontStyleManager* list;
    DialogFontStyle* dialog = new DialogFontStyle(this);
    FindWidget* findWidget;
    bool isTextEmphasized = false;
    bool isReplacerCalled = false;

    void setTextEditContent(QString text);
    void setTextEditName(QString fileName);
    void setTextEditFont(const QFont& font);
    void setTextEditFontStyle(QListWidgetItem* item);
    void openDialogToEditStyle();

    void emphasizeText(const int& textIndex, const int& patternLength);
    void replaceText(List<int>& indexes, int& currentIndex, const int& patternLength, const QString& replacing);
    void replaceAllText(const List<int>& indexes, const int& patternLength);

    void callFinder();
    void callReplacer();

    void resetFlags();

    void closeFindWidget();

    void swapCursorPos();

    void setTextEditFontFamily();
};
#endif // MAINWINDOW_H
