#include "MainWindow.h"
#include "ui_MainWindow.h"
#include <QPrinter>
#include <QPrintDialog>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    textEdit = textEdit->getInstance();
    fileManager = fileManager->getInstance();
    styleManager = styleManager->getInstance();
    findDialog = new FindDialog(textEdit);

    fileTab->setFixedHeight(35);
    fileTab->setFlow(QListView::LeftToRight);
    fontFamily->setMinimumSize(180, 35);
    fontSizeSpinBox->setMinimum(1);
    fontSizeSpinBox->setMaximum(1638);
    fontSizeSpinBox->setValue(9);
    fontSizeSpinBox->setFixedSize(90, 35);
    ui->leftAlignAction->setChecked(true);
    textColorButton->setStyleSheet("QPushButton {border: none; border-radius: 0px; background-color: #1e1e1e; min-width: 35px; min-height: 35px;} QPushButton:hover {background-color: #A3CFFF; border-radius: 3px;}");
    textColorButton->setIconSize(QSize(35, 35));
    backgroundColorButton->setStyleSheet("QPushButton {border: none; border-radius: 0px; background-color: #1e1e1e; min-width: 35px; min-height: 35px;} QPushButton:hover {background-color: #A3CFFF; border-radius: 3px;}");
    backgroundColorButton->setIconSize(QSize(35, 35));

    ui->fileTabHLayout->addWidget(fileTab);
    ui->textEditHLayout->addWidget(textEdit);
    ui->toolBar->addWidget(textColorButton);
    ui->toolBar->addWidget(backgroundColorButton);
    ui->toolBar->addWidget(fontFamily);
    ui->toolBar->addWidget(fontSizeSpinBox);
    ui->toolBar->addWidget(styleManager);

    formatTableMenu->addAction(tr("Объединить ячейки"), textEdit, &TextEditManager::mergeCells);
    formatTableMenu->addAction(tr("Разъеденить ячейки"), textEdit, &TextEditManager::splitCells);

    connect(fileManager, &FileManager::textRead, textEdit, &TextEditManager::setTextEditContent);
    connect(fileManager, &FileManager::fileOpened, this, &MainWindow::setTextEditorName);
    connect(fileTab, &FileTab::fileChanged, this, &MainWindow::setTextEditorName);

    connect(fontFamily, &QFontComboBox::currentFontChanged, textEdit, &TextEditManager::setTextEditFont);
    connect(textColorButton->getColorDialog(), &QColorDialog::colorSelected, textEdit, &TextEditManager::setTextColor);
    connect(textColorButton, &TextColorButton::colorReseted, textEdit, &TextEditManager::setTextColor);
    connect(backgroundColorButton->getColorDialog(), &QColorDialog::colorSelected, textEdit, &TextEditManager::setTextBackgroundColor);
    connect(backgroundColorButton, &BackgroundColorButton::colorReseted, textEdit, &TextEditManager::setTextBackgroundColor);
    connect(fontSizeSpinBox, &QSpinBox::valueChanged, this, &MainWindow::setfontSizeSpinBox);
    connect(styleManager, &FontStyleManager::fontStyleChosen, textEdit, &TextEditManager::setTextEditFontStyle);
    connect(textEdit, &TextEditManager::styleChanged, this, &MainWindow::setCurrentStyleInfo);

    connect(textEdit, &QTextEdit::cursorPositionChanged, this, &MainWindow::showTableFormatMenu);
    connect(textEdit, &QTextEdit::cursorPositionChanged, this, &MainWindow::setCurrentCursorStyleInfo);

    connect(ui->replaceAction, &QAction::triggered, findDialog, &FindDialog::showReplacer);
    connect(ui->findAction, &QAction::triggered, findDialog, &FindDialog::showFinder);

    on_createAction_triggered();
}

MainWindow::~MainWindow()
{
    delete findDialog;
    delete styleManager;
    delete textColorButton;
    delete backgroundColorButton;
    delete fontSizeSpinBox;
    delete formatTableMenu;
    delete textEdit;
    delete fontFamily;
    delete fileTab;
    delete fileManager;
    delete ui;
}

void MainWindow::setTextEditorName(QString filePath)
{
    filePath = "Sigma Text - " % filePath;
    setWindowTitle(filePath);
}

void MainWindow::swapCursorPos()
{
    int anchorPos = textEdit->textCursor().anchor();
    int cursorPos = textEdit->textCursor().position();

    if (anchorPos > cursorPos)
    {
        int length = anchorPos - cursorPos;
        QTextCursor cursor = textEdit->textCursor();

        cursor.clearSelection();
        cursor.movePosition(QTextCursor::Right, QTextCursor::KeepAnchor, length);
        textEdit->setTextCursor(cursor);
    }
}

void MainWindow::showTableFormatMenu()
{
    if(textEdit->textCursor().currentTable() != nullptr && !isFormatTableMenu)
    {
        ui->menubar->addMenu(formatTableMenu);
        isFormatTableMenu = true;
    }
    else
    {
        if(textEdit->textCursor().currentTable() == nullptr && isFormatTableMenu)
        {
            ui->menubar->removeAction(formatTableMenu->menuAction());
            isFormatTableMenu = false;
        }
    }
}

void MainWindow::setfontSizeSpinBox(const int& fontSize)
{
    textEdit->setFontPointSize(fontSize);
}

void MainWindow::setCurrentStyleInfo(const FontStyle& style)
{
    QFont font = style.getFont();

    fontSizeSpinBox->setValue(font.pointSize());
    fontFamily->setCurrentFont(font);

    ui->actionBold->setChecked(font.bold());
    ui->actionItalic->setChecked(font.italic());
    ui->actionUnderline->setChecked(font.underline());

    textColorButton->changeRectangleColor(style.getTextColor());
    backgroundColorButton->changeRectangleColor(style.getBackgroundColor());

    setAlignChecked(style.getAlign());
}

void MainWindow::setCurrentCursorStyleInfo()
{
    QFont font = textEdit->textCursor().charFormat().font();

    fontSizeSpinBox->setValue(font.pointSize());
    fontFamily->setCurrentFont(font);

    ui->actionBold->setChecked(font.bold());
    ui->actionItalic->setChecked(font.italic());
    ui->actionUnderline->setChecked(font.underline());

    textColorButton->changeRectangleColor(textEdit->textColor());
    backgroundColorButton->changeRectangleColor(textEdit->textBackgroundColor());

    setAlignChecked(textEdit->alignment());
}

void MainWindow::setAlignChecked(const Qt::Alignment& align)
{
    if(ui->leftAlignAction->isChecked())
    {
        ui->leftAlignAction->setChecked(false);
    }
    if(ui->rightAlignAction->isChecked())
    {
        ui->rightAlignAction->setChecked(false);
    }
    if(ui->centerAlignAction->isChecked())
    {
        ui->centerAlignAction->setChecked(false);
    }
    if(ui->justifyAlignAction->isChecked())
    {
        ui->justifyAlignAction->setChecked(false);
    }

    switch (align)
    {
    case Qt::AlignLeft:
        ui->leftAlignAction->setChecked(true);
        break;
    case Qt::AlignRight:
        ui->rightAlignAction->setChecked(true);
        break;
    case Qt::AlignHCenter:
        ui->centerAlignAction->setChecked(true);
        break;
    case Qt::AlignJustify:
        ui->justifyAlignAction->setChecked(true);
        break;
    default:
        break;
    }
}

void MainWindow::closeEvent(QCloseEvent*)
{
    if(fileTab->getFiles().getCount() != 0)
    {
        fileTab->getCurrentFile().setText(textEdit->toHtml());
    }
}

void MainWindow::on_createAction_triggered()
{
    if(textEdit->isReadOnly())
    {
        textEdit->setReadOnly(false);
        textEdit->setText("");
    }
    setTextEditorName("Без имени");
    fileTab->addFile("Без имени");
}

void MainWindow::on_openAction_triggered()
{
    disconnect(textEdit, &QTextEdit::textChanged, fileTab, &FileTab::setFileUnsaved);
    QString filePath = fileManager->openFile();
    connect(textEdit, &QTextEdit::textChanged, fileTab, &FileTab::setFileUnsaved);

    if(filePath != nullptr)
    {
        if(textEdit->isReadOnly())
        {
            textEdit->setReadOnly(false);
            textEdit->setText("");
        }
        setTextEditorName(filePath);
        fileTab->addFile(filePath);
    }
}

void MainWindow::on_saveAsAction_triggered()
{
    QString text = textEdit->toHtml();
    QString filePath = fileManager->saveAsFile(text);

    if(filePath != nullptr)
    {
        setTextEditorName(filePath);
        fileTab->setFileSaved(filePath);
    }
}

void MainWindow::on_saveAction_triggered()
{
    QString filePath = fileTab->getCurrentFile().getFilePath();

    if(filePath == nullptr)
    {
        on_saveAsAction_triggered();
        return;
    }

    filePath = fileManager->saveFile(textEdit->toHtml(), filePath);
    if(filePath != nullptr)
    {
        fileTab->setFileSaved(filePath);
    }
}

void MainWindow::on_printAction_triggered()
{
    QPrinter printer;
    QPrintDialog printDialog(&printer, this);

    if (printDialog.exec() == QDialog::Rejected)
    {
        return;
    }
    textEdit->print(&printer);
}

void MainWindow::on_actionItalic_triggered()
{
    swapCursorPos();
    textEdit->setFontItalic(!textEdit->fontItalic());
}

void MainWindow::on_actionBold_triggered()
{
    swapCursorPos();
    if (textEdit->fontWeight() == 400)
    {
        textEdit->setFontWeight(700);
    }
    else
    {
        textEdit->setFontWeight(400);
    }
}

void MainWindow::on_actionUnderline_triggered()
{
    swapCursorPos();
    textEdit->setFontUnderline(!textEdit->fontUnderline());
}

void MainWindow::on_leftAlignAction_triggered()
{
    textEdit->setAlignment(Qt::AlignLeft);
    setAlignChecked(Qt::AlignLeft);
}


void MainWindow::on_centerAlignAction_triggered()
{
    textEdit->setAlignment(Qt::AlignHCenter);
    setAlignChecked(Qt::AlignHCenter);
}


void MainWindow::on_rightAlignAction_triggered()
{
    textEdit->setAlignment(Qt::AlignRight);
    setAlignChecked(Qt::AlignRight);
}


void MainWindow::on_justifyAlignAction_triggered()
{
    textEdit->setAlignment(Qt::AlignJustify);
    setAlignChecked(Qt::AlignJustify);
}
