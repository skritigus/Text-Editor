#ifndef DIALOGFONTSTYLE_H
#define DIALOGFONTSTYLE_H

#include <memory>
#include <QColorDialog>
#include "ui_dialogFontStyle.h"
#include "FontStyle.h"

class DialogFontStyle : public QDialog, public Ui::Dialog
{
    Q_OBJECT

    std::unique_ptr<QColorDialog> textColorDialog = std::make_unique<QColorDialog>(nullptr);
    std::unique_ptr<QColorDialog> backgroundColorDialog = std::make_unique<QColorDialog>(nullptr);

    void setTextColorButton(const QColor& color);
    void setBackgroundColorButton(const QColor& color);

public:
    explicit DialogFontStyle(QWidget* parent = nullptr);

    void setFontStyleInfo(const FontStyle& style);

signals:
    void onAddStyle(FontStyle& style);
    void onEditStyle(FontStyle& style);
    void onDeleteStyle();

private slots:
    void on_textColorButton_clicked();
    void on_backgroundColorButton_clicked();
    void on_OKButton_clicked();
    void on_deleteButton_clicked();
    void on_cancelButton_clicked();
};

#endif // DIALOGFONTSTYLE_H
