#include "Find.h"

void Find::computeLPS(const QString& pattern, int& sizePattern, QVector<int>& lps)
{
    for(int len = 0, i = 1; i < sizePattern; ++i)
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

void Find::KMP(const QString& text, const QString& pattern, List<int>& indexes)
{
    int i = 0;
    int j = 0;
    int sizeText = text.length();
    int sizePattern = pattern.length();
    QVector<int> lps(sizePattern, 0);

    computeLPS(pattern, sizePattern, lps);

    while(sizeText - i >= sizePattern - j)
    {
        if(text[i] == pattern[j])
        {
            ++i;
            ++j;
        }
        if(j == sizePattern)
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
