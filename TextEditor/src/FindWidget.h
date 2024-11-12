#ifndef FINDWIDGET_H
#define FINDWIDGET_H

#include <QTextEdit>
#include <QShortcut>
#include "IFindDependent.h"
#include "List.h"

QT_BEGIN_NAMESPACE
namespace Ui
{
    class FindWidget;
}
QT_END_NAMESPACE

class FindWidget : public QWidget
{
    Q_OBJECT

    Ui::FindWidget* ui;
    IFindDependent* finder = nullptr;
    QString text;
    QShortcut* shortcutCloseFindWidget = new QShortcut(QKeySequence::Cancel, this);
    bool isFindAllClicked = false;

public:
    explicit FindWidget(QWidget* parent = nullptr);
    ~FindWidget();

    void showFinder(const QString& text, const QTextCursor& textCursor);
    void showReplacer(const QString& text);

    void setText(const QString& text);

signals:
    void foundPattern(const int& textIndex, const int& patternLength);
    void foundAllPattern(QList<QTextEdit::ExtraSelection>& selections, List<int>& indexes, const int& currentIndex, const int& patternLength);
    void replacePattern(List<int>& indexes, int& currentIndex, const int& patternLength, const QString& replacing);
    void replaceAllPatterns(const QString&);
    void nextPattern();
    void prevPattern();
    void widgetClosed();

private slots:
    void on_findAllButton_clicked();
    void on_findButton_clicked();
    void on_nextButton_clicked();
    void on_prevButton_clicked();
    void on_replaceButton_clicked();
    void on_replaceAllButton_clicked();
    void on_closeButton_clicked();
};

#endif // FINDWIDGET_H
