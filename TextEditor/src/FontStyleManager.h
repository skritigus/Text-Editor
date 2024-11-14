#ifndef FONTSTYLEMANAGER_H
#define FONTSTYLEMANAGER_H

#include <QListWidget>
#include "DialogFontStyle.h"
#include "List.h"
#include "FontStyle.h"

class FontStyleManager : public QListWidget
{
    Q_OBJECT

    List<FontStyle> styles;
    DialogFontStyle* fontStyleEditor = new DialogFontStyle(this);

signals:
    void fontStyleChosen(const FontStyle& style);

public:
    FontStyleManager();
    ~FontStyleManager();

    List<FontStyle>& getStyles();

    void addFontStyle(FontStyle& style);
    void editFontStyle(FontStyle& style);
    void deleteFontStyle();

private:
    void loadStyles();
    void saveStyles() const;

    void openDialogToEditStyle(QListWidgetItem* item);
    void setFontStyle(QListWidgetItem* item);
};

#endif // FONTSTYLEMANAGER_H
