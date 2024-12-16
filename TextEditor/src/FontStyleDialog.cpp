#include "FontStyleDialog.h"
#include "AlignManager.h"
#include "ui_FontStyleDialog.h"
#include <QMessageBox>

FontStyleDialog::FontStyleDialog(QWidget* parent) : QDialog(parent), ui(new Ui::FontStyleDialog)
{
    ui->setupUi(this);

    ui->textColorButton->setIconSize(QSize(25, 25));
    ui->backgroundColorButton->setIconSize(QSize(25, 25));
}

void FontStyleDialog::setFontStyleInfo(const FontStyle& style)
{
    QFont font = style.getFont();

    ui->fontComboBox->setCurrentText(font.family());
    ui->styleNameLineEdit->setText(font.styleName());
    ui->boldButton->setChecked(font.bold());
    ui->italicButton->setChecked(font.italic());
    ui->underlineButton->setChecked(font.underline());
    ui->fontSizeSpinBox->setValue(font.pointSize());

    ui->alignComboBox->setCurrentIndex(AlignManager::alignToInt(style.getAlign()));

    ui->textColorButton->changeRectangleColor(style.getTextColor());
    ui->backgroundColorButton->changeRectangleColor(style.getBackgroundColor());
}

void FontStyleDialog::on_OKButton_clicked()
{
    QFont font;
    Qt::Alignment align;
    QColor textColor = ui->textColorButton->color;
    QColor backgroundColor = ui->backgroundColorButton->color;

    if(QFontDatabase::hasFamily(ui->fontComboBox->currentFont().family()))
    {
        font = ui->fontComboBox->currentFont();
    }
    else
    {
        QMessageBox::information(this, "Введены неверные данные", "Введеный шрифт не существует");
        return;
    }

    font.setStyleName(ui->styleNameLineEdit->text());
    font.setBold(ui->boldButton->isChecked());
    font.setItalic(ui->italicButton->isChecked());
    font.setUnderline(ui->underlineButton->isChecked());
    font.setPointSize(ui->fontSizeSpinBox->value());

    align = AlignManager::intToAlign(ui->alignComboBox->currentIndex());

    FontStyle style(font, textColor, backgroundColor, align);

    if(ui->deleteButton->isVisible())
    {
        emit styleEdited(style);
    }
    else
    {
        emit styleAdded(style);
    }

    close();
}

void FontStyleDialog::on_deleteButton_clicked()
{
    QMessageBox messageDialog;

    messageDialog.setText("Вы уверены, что хотите удалить стиль текста?");
    messageDialog.setStandardButtons(QMessageBox::Yes | QMessageBox::No);

    if(messageDialog.exec() == QMessageBox::Yes)
    {
        emit styleDeleted();
    }

    messageDialog.close();
    close();
}


void FontStyleDialog::on_cancelButton_clicked()
{
    close();
}

void FontStyleDialog::showToAddStyle()
{
    setWindowTitle("Добавить стиль текста");
    ui->deleteButton->hide();

    exec();
}

void FontStyleDialog::showToEditStyle(const FontStyle& style)
{
    setWindowTitle("Изменить стиль текста");
    setFontStyleInfo(style);
    ui->deleteButton->show();

    exec();
}
