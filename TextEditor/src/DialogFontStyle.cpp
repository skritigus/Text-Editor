#include "DialogFontStyle.h"
#include "FontStyle.h"
#include "AlignManager.h"
#include <QMessageBox>

DialogFontStyle::DialogFontStyle(QWidget* parent) : QDialog(parent)
{
    setupUi(this);

    connect(dial1.get(), &QColorDialog::colorSelected, this, &DialogFontStyle::setColorButton4);
    connect(dial2.get(), &QColorDialog::colorSelected, this, &DialogFontStyle::setColorButton6);
}

void DialogFontStyle::on_pushButton_4_clicked()
{
    dial1->setStyleSheet("QSpinBox {width: 60px;}");
    dial1->show();
}

void DialogFontStyle::on_pushButton_6_clicked()
{
    dial2->setStyleSheet("QSpinBox {width: 60px;}");
    dial2->show();
}

void DialogFontStyle::setColorButton4(const QColor& color)
{
    pushButton_4->setPalette(QPalette(color));
}

void DialogFontStyle::setColorButton6(const QColor& color)
{
    pushButton_6->setPalette(QPalette(color));
}

void DialogFontStyle::on_pushButton_5_pressed()
{
    QFont font;
    Qt::Alignment align;

    font = fontComboBox->currentFont();
    font.setStyleName(lineEdit->text());
    font.setBold(pushButton->isChecked());
    font.setItalic(pushButton_2->isChecked());
    font.setUnderline(pushButton_3->isChecked());
    font.setPointSize(spinBox->value());

    align = AlignManager::intToAlign(comboBox->currentIndex());

    QColor textColor = pushButton_4->palette().color(QPalette::Button);
    QColor backgroundColor = pushButton_6->palette().color(QPalette::Button);

    FontStyle style(font, textColor, backgroundColor, align);

    if(pushButton_7->isVisible())
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
    lineEdit->setText(font.styleName());
    pushButton->setChecked(font.bold());
    pushButton_2->setChecked(font.italic());
    pushButton_3->setChecked(font.underline());
    spinBox->setValue(font.pointSize());

    comboBox->setCurrentIndex(AlignManager::alignToInt(style.getAlign()));

    pushButton_4->setPalette(QPalette(style.getTextColor()));
    pushButton_6->setPalette(QPalette(style.getBackgroundColor()));
}

void DialogFontStyle::on_pushButton_7_clicked()
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


void DialogFontStyle::on_pushButton_8_clicked()
{
    this->close();
}
