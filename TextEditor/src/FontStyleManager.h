#ifndef FONTSTYLEMANAGER_H
#define FONTSTYLEMANAGER_H

#include <QListWidget>
#include "FontStyleDialog.h"
#include "List.h"
#include "FontStyle.h"

class FontStyleManager : public QListWidget
{
    Q_OBJECT

    static FontStyleManager* instance;
    List<FontStyle> styles;
    FontStyleDialog* fontStyleEditor = new FontStyleDialog(this);

    FontStyleManager();

signals:
    void fontStyleChosen(const FontStyle& style);

public:
    ~FontStyleManager();

    FontStyleManager* getInstance();
    List<FontStyle>& getStyles();
    FontStyle& getCurrentStyle();

    void addFontStyle(const FontStyle& style);
    void editFontStyle(FontStyle& style);
    void deleteFontStyle();

    void mousePressEvent(QMouseEvent* event) override;

private:
    void setFontStyle(const QListWidgetItem* item);
};

#endif // FONTSTYLEMANAGER_H
