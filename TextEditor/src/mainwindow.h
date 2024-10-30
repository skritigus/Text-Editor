#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "FontStyleManager.h"
#include <QListWidget>
#include <QMainWindow>
#include <QFontComboBox>
#include <FileWorker.h>
#include "DialogFontStyle.h"
#include "FontStyle.h"
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
    void onPushButtonFind(const QString&, const QString&);
    void onPushButtonReplace(const QString&, const QString&, const int&);
    void onPushButtonAllReplace(const QString&, const QString&);
    void nextPattern();
    void prevPattern();

private slots:
    void on_action_triggered();
    void on_action_2_triggered();

    void on_actionItalic_triggered();
    void on_actionBold_triggered();
    void on_actionUnderline_triggered();

    void on_pushButton_9_clicked();
    void on_nextButton_clicked();
    void on_prevButton_clicked();

    void on_replaceButton_clicked();

    void on_replaceAllButton_clicked();

private:
    Ui::MainWindow *ui;

    FileWorker* fileWorker;
    QFontComboBox* fontFamily;
    FontStyleManager* list;
    DialogFontStyle* dialog = new DialogFontStyle(this);

    void setTextEditContent(QString text);
    void setTextEditName(QString fileName);
    void setTextEditFont(const QFont& font);
    void setTextEditFontStyle(QListWidgetItem* item);
    void openDialogToEditStyle();

    void emphasizeText(const int& textIndex, const int& patternLength);
    void replaceText(const List<int>& indexes, int& currentIndex, const int& patternLength);
    void replaceAllText(const List<int>& indexes, const int& patternLength);

    void swapCursorPos();

    void setTextEditFontFamily();
};
#endif // MAINWINDOW_H
