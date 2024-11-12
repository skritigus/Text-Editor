#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "FontStyleManager.h"
#include <QListWidget>
#include <QMainWindow>
#include <QFontComboBox>
#include <QShortcut>
#include "FileWorker.h"
#include "FindWidget.h"
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
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

signals:
    void activateFinder(const QString& text, const QTextCursor& textCursor);
    void activateReplacer(const QString& text);

private slots:
    void on_action_triggered();
    void on_action_2_triggered();

    void on_actionItalic_triggered();
    void on_actionBold_triggered();
    void on_actionUnderline_triggered();

    void on_clearButton_clicked();

private:
    Ui::MainWindow *ui;

    std::unique_ptr<FileWorker> fileWorker = std::make_unique<FileWorker>();
    std::unique_ptr<QFontComboBox> fontFamily = std::make_unique<QFontComboBox>();
    std::unique_ptr<FontStyleManager> list = std::make_unique<FontStyleManager>();
    std::unique_ptr<FindWidget> findWidget = std::make_unique<FindWidget>();
    std::unique_ptr<QShortcut> shortcutFind = std::make_unique<QShortcut>(QKeySequence::Find, this);
    std::unique_ptr<QShortcut> shortcutReplace = std::make_unique<QShortcut>(QKeySequence::Replace, this);
    bool isTextEmphasized = false;
    bool isReplacerCalled = false;

    void setTextEditContent(QString text);
    void setTextEditName(QString fileName);
    void setTextEditFont(const QFont& font);
    void setTextEditFontStyle(const FontStyle& style);

    void emphasizeText(const int& textIndex, const int& patternLength);
    void emphasizeAllPatterns(QList<QTextEdit::ExtraSelection>& selections, const List<int>& indexes, const int& currentIndex, const int& patternLength);
    void replaceText(List<int>& indexes, int& currentIndex, const int& patternLength, const QString& replacing);
    void replaceAllText(const QString& text);

    void callFinder();
    void callReplacer();

    void resetFlags();
    void closeFindWidget();

    void swapCursorPos();
};
#endif // MAINWINDOW_H
