#ifndef FONTSTYLEDIALOG_H
#define FONTSTYLEDIALOG_H

#include "FontStyle.h"
#include <QDialog>

namespace Ui
{
    class FontStyleDialog;
}

class FontStyleDialog : public QDialog
{
    Q_OBJECT

    Ui::FontStyleDialog* ui;

public:
    explicit FontStyleDialog(QWidget* parent = nullptr);

    void setFontStyleInfo(const FontStyle& style);

    void showToAddStyle();
    void showToEditStyle(const FontStyle& style);

signals:
    void styleAdded(FontStyle& style);
    void styleEdited(FontStyle& style);
    void styleDeleted();

private slots:
    void on_OKButton_clicked();
    void on_deleteButton_clicked();
    void on_cancelButton_clicked();
};

#endif // FONTSTYLEDIALOG_H
