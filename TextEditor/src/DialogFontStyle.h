#ifndef DIALOGFONTSTYLE_H
#define DIALOGFONTSTYLE_H

#include <QColorDialog>
#include "ui_DialogFontStyle.h"
#include "FontStyle.h"

class DialogFontStyle : public QDialog, public Ui::Dialog
{
    Q_OBJECT

    QColorDialog* textColorDialog = new QColorDialog(nullptr);
    QColorDialog* backgroundColorDialog = new QColorDialog(nullptr);
    QColor textColor = QColor(255, 255, 255);
    QColor backgroundColor = QColor(45, 45, 45);

    void setTextColorButton(const QColor& color);
    void setBackgroundColorButton(const QColor& color);

public:
    explicit DialogFontStyle(QWidget* parent = nullptr);
    ~DialogFontStyle();

    void setFontStyleInfo(const FontStyle& style);

signals:
    void styleAdded(FontStyle& style);
    void styleEdited(FontStyle& style);
    void styleDeleted();

private slots:
    void on_textColorButton_clicked();
    void on_backgroundColorButton_clicked();
    void on_OKButton_clicked();
    void on_deleteButton_clicked();
    void on_cancelButton_clicked();
};

#endif // DIALOGFONTSTYLE_H
