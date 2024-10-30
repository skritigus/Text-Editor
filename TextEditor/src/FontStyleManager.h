#ifndef FONTSTYLEMANAGER_H
#define FONTSTYLEMANAGER_H

#include <QListWidget>
#include "List.h"
#include "FontStyle.h"

class FontStyleManager : public QListWidget
{
    Q_OBJECT

    List<FontStyle> styles;

public:
    FontStyleManager();
    ~FontStyleManager()
    {
        saveStyles();
    }

    List<FontStyle>& getStyles();

    void addFontStyle(FontStyle& style);
    void editFontStyle(FontStyle& style);
    void deleteFontStyle();

private:
    void loadStyles();
    void saveStyles();
};

#endif // FONTSTYLEMANAGER_H
