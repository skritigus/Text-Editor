#ifndef DIALOGFONTSTYLE_H
#define DIALOGFONTSTYLE_H

#include <QColorDialog>
#include "ui_dialogFontStyle.h"
#include "FontStyle.h"

class DialogFontStyle : public QDialog, public Ui::Dialog
{
    Q_OBJECT

    QColorDialog* dial1 = new QColorDialog(nullptr);
    QColorDialog* dial2 = new QColorDialog(nullptr);

    void setColorButton4(QColor color);
    void setColorButton6(QColor color);

public:
    explicit DialogFontStyle(QWidget* parent = nullptr);

    void setFontStyleInfo(const FontStyle& style);

signals:
    void onAddStyle(FontStyle& style);
    void onEditStyle(FontStyle& style);
    void onDeleteStyle();

private slots:
    void on_pushButton_4_clicked();
    void on_pushButton_6_clicked();
    void on_pushButton_5_pressed();
    void on_pushButton_7_clicked();
    void on_pushButton_8_clicked();
};

#endif // DIALOGFONTSTYLE_H
