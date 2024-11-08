#ifndef DIALOGFONTSTYLE_H
#define DIALOGFONTSTYLE_H

#include <memory>
#include <QColorDialog>
#include "ui_dialogFontStyle.h"
#include "FontStyle.h"

class DialogFontStyle : public QDialog, public Ui::Dialog
{
    Q_OBJECT

    std::unique_ptr<QColorDialog> dial1 = std::make_unique<QColorDialog>(nullptr);
    std::unique_ptr<QColorDialog> dial2 = std::make_unique<QColorDialog>(nullptr);

    void setColorButton4(const QColor& color);
    void setColorButton6(const QColor& color);

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
