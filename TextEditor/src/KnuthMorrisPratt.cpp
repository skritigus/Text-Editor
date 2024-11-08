#include "KnuthMorrisPratt.h"

void KnuthMorrisPratt::computeLPS(const QString& pattern, QVector<int>& lps) const
{
    for(int len = 0, i = 1; i < patternLength; ++i)
    {
        while (len != 0 && pattern[i] != pattern[len])
        {
            len = lps[len - 1];
        }

        if(pattern[len] == pattern[i])
        {
            ++len;
        }
        lps[i] = len;
    }
}

List<int> KnuthMorrisPratt::KMP(const QString& text, const QString& pattern)
{
    List<int> indexes;
    int i = 0;
    int j = 0;
    int sizeText = text.length();

    patternLength = pattern.length();
    QVector<int> lps(patternLength, 0);

    indexes.clear();

    computeLPS(pattern, lps);

    while (i < sizeText)
    {
        if (text[i] == pattern[j])
        {
            ++i;
            ++j;

            if (j == patternLength)
            {
                indexes.pushBack(i - j);
                j = lps[j - 1];
            }
        }
        else
        {
            if (j != 0)
            {
                j = lps[j - 1];
            }
            else
            {
                ++i;
            }
        }
    }
    return indexes;
}

int& KnuthMorrisPratt::getPatternLength()
{
    return patternLength;
}
