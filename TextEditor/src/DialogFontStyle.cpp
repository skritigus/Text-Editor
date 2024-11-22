#include "DialogFontStyle.h"
#include "AlignManager.h"
#include <QMessageBox>

DialogFontStyle::DialogFontStyle(QWidget* parent) : QDialog(parent)
{
    setupUi(this);

    textColorDialog->setWindowTitle("Выберите цвет текса");
    backgroundColorDialog->setWindowTitle("Выберите цвет заднего фона");
    textColorDialog->setStyleSheet("QSpinBox {width: 60px;}");
    backgroundColorDialog->setStyleSheet("QSpinBox {width: 60px;}");

    connect(textColorDialog, &QColorDialog::colorSelected, this, &DialogFontStyle::setTextColorButton);
    connect(backgroundColorDialog, &QColorDialog::colorSelected, this, &DialogFontStyle::setBackgroundColorButton);
}

DialogFontStyle::~DialogFontStyle()
{
    delete backgroundColorDialog;
    delete textColorDialog;
}

void DialogFontStyle::setTextColorButton(const QColor& color)
{
    textColor = color;
    textColorButton->setPalette(QPalette(textColor));
}

void DialogFontStyle::setBackgroundColorButton(const QColor& color)
{
    backgroundColor = color;
    backgroundColorButton->setPalette(QPalette(backgroundColor));
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

void DialogFontStyle::on_textColorButton_clicked()
{
    textColorDialog->show();
}

void DialogFontStyle::on_backgroundColorButton_clicked()
{
    backgroundColorDialog->show();
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

    FontStyle style(font, textColor, backgroundColor, align);

    if(deleteButton->isVisible())
    {
        emit styleEdited(style);
    }
    else
    {
        emit styleAdded(style);
    }

    this->close();
}

void DialogFontStyle::on_deleteButton_clicked()
{
    QMessageBox messageDialog;

    messageDialog.setText("Вы уверены, что хотите удалить стиль текста?");
    messageDialog.setStandardButtons(QMessageBox::Yes | QMessageBox::No);

    if(messageDialog.exec() == QMessageBox::Yes)
    {
        emit styleDeleted();
    }

    messageDialog.close();
    this->close();
}


void DialogFontStyle::on_cancelButton_clicked()
{
    this->close();
}
