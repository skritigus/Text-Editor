#ifndef FINDWIDGET_H
#define FINDWIDGET_H

#include <QWidget>
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

public:
    explicit FindWidget(QWidget* parent = nullptr);
    ~FindWidget();

    void showFinder(const QString& text);
    void showReplacer(const QString& text);

signals:
    void foundPattern(const int& textIndex, const int& patternLength);
    void replacePattern(List<int>& indexes, int& currentIndex, const int& patternLength, const QString& replacing);
    void onPushButtonAllReplace(const QString&);
    void nextPattern();
    void prevPattern();
    void widgetClosed();

public slots:
    void on_findButton_clicked();
    void on_nextButton_clicked();
    void on_prevButton_clicked();

    void on_replaceButton_clicked();

    void on_replaceAllButton_clicked();

    void on_closeButton_clicked();

    void on_pushButton_clicked();

    void on_pushButton_8_clicked();

    //void on_textEdit_textChanged();

private:
    Ui::FindWidget* ui;
    IFindDependent* finder;
    QString text;

    void setText(const QString& text);
};

#endif // FINDWIDGET_H
