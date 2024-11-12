#include "DialogFontStyle.h"
#include "FontStyle.h"
#include "AlignManager.h"
#include <QMessageBox>

DialogFontStyle::DialogFontStyle(QWidget* parent) : QDialog(parent)
{
    setupUi(this);

    textColorDialog->setWindowTitle("Select Text Color");
    backgroundColorDialog->setWindowTitle("Select Background Color");
    textColorDialog->setStyleSheet("QSpinBox {width: 60px;}");
    backgroundColorDialog->setStyleSheet("QSpinBox {width: 60px;}");

    connect(textColorDialog.get(), &QColorDialog::colorSelected, this, &DialogFontStyle::setTextColorButton);
    connect(backgroundColorDialog.get(), &QColorDialog::colorSelected, this, &DialogFontStyle::setBackgroundColorButton);
}

void DialogFontStyle::on_textColorButton_clicked()
{
    textColorDialog->show();
}

void DialogFontStyle::on_backgroundColorButton_clicked()
{
    backgroundColorDialog->show();
}

void DialogFontStyle::setTextColorButton(const QColor& color)
{
    textColorButton->setPalette(QPalette(color));
}

void DialogFontStyle::setBackgroundColorButton(const QColor& color)
{
    backgroundColorButton->setPalette(QPalette(color));
}

void DialogFontStyle::on_OKButton_clicked()
{
    QFont font;
    Qt::Alignment align;

    font = fontComboBox->currentFont();
    font.setStyleName(styleNameLineEdit->text());
    font.setBold(boldButton->isChecked());
    font.setItalic(italicButton->isChecked());
    font.setUnderline(underlineButton->isChecked());
    font.setPointSize(fontSizeSpinBox->value());

    align = AlignManager::intToAlign(alignComboBox->currentIndex());

    QColor textColor = textColorButton->palette().color(QPalette::Button);
    QColor backgroundColor = backgroundColorButton->palette().color(QPalette::Button);

    FontStyle style(font, textColor, backgroundColor, align);

    if(deleteButton->isVisible())
    {
        emit onEditStyle(style);
    }
    else
    {
        emit onAddStyle(style);
    }

    this->close();
}

void DialogFontStyle::setFontStyleInfo(const FontStyle& style)
{
    QFont font = style.getFont();

    fontComboBox->setCurrentText(font.family());
    styleNameLineEdit->setText(font.styleName());
    boldButton->setChecked(font.bold());
    italicButton->setChecked(font.italic());
    underlineButton->setChecked(font.underline());
    fontSizeSpinBox->setValue(font.pointSize());

    alignComboBox->setCurrentIndex(AlignManager::alignToInt(style.getAlign()));

    textColorButton->setPalette(QPalette(style.getTextColor()));
    backgroundColorButton->setPalette(QPalette(style.getBackgroundColor()));
}

void DialogFontStyle::on_deleteButton_clicked()
{
    QMessageBox messageDialog;

    messageDialog.setText("Are you sure you want to delete this style?");
    messageDialog.setStandardButtons(QMessageBox::Yes | QMessageBox::No);

    if(messageDialog.exec() == QMessageBox::Yes)
    {
        emit onDeleteStyle();
    }

    messageDialog.close();
    this->close();
}


void DialogFontStyle::on_cancelButton_clicked()
{
    this->close();
}
