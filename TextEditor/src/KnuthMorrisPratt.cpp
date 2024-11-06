#include "KnuthMorrisPratt.h"

KnuthMorrisPratt::~KnuthMorrisPratt()
{
    indexes.clear();
}

void KnuthMorrisPratt::computeLPS(const QString& pattern, QVector<int>& lps)
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

void KnuthMorrisPratt::KMP(const QString& text, const QString& pattern)
{
    int i = 0;
    int j = 0;
    int sizeText = text.length();

    patternLength = pattern.length();
    QVector<int> lps(patternLength, 0);

    indexes.clear();

    computeLPS(pattern, lps);

    while(sizeText - i >= patternLength - j)
    {
        if(text[i] == pattern[j])
        {
            ++i;
            ++j;
        }
        if(j == patternLength)
        {
            indexes.pushBack(i - j);
            j = lps[j - 1];
        }
        else
        {
            if(i < sizeText && text[i] != pattern[j])
            {
                if(j != 0)
                {
                    j = lps[j - 1];
                }
                else
                {
                    ++i;
                }
            }
        }
    }
}

int& KnuthMorrisPratt::getPatternLength()
{
    return patternLength;
}

List<int>& KnuthMorrisPratt::getIndexes()
{
    return indexes;
}
