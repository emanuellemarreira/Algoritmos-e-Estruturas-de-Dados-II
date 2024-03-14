#include <iostream>
#include <vector>
#include <list>

using namespace std;

const int TAM_ASCII = 128;
const int M = 28;

class BoyerMoore
{
private:
    vector<int> right;
    string pattern;

public:
    BoyerMoore(string pattern) : right(256), pattern(pattern)
    {
        int M = pattern.length();
        for (int c = 0; c < 256; c++)
        {
            right[c] = -1;
        }
        for (int j = 0; j < M; j++)
        {
            right[pattern.at(j)] = j;
        }
    }

    string search(string text)
    {
        string itAll;
        int N = text.length();
        int M = pattern.length();
        int skip = 0;
        for (int i = 0; i <= N - M; i += skip)
        {
            skip = 0;
            for (int j = M - 1; j >= 0; j--)
            {
                if (pattern.at(j) != text.at(i + j))
                {
                    skip = j - right[text.at(i + j)];
                    if (skip < 1)
                    {
                        skip = 1;
                    }
                    break;
                }
            }
            itAll += to_string(skip);
            itAll.push_back(' ');
            if (skip == 0)
            {
                itAll.push_back('(');
                itAll += to_string(i);
                itAll.push_back(')');
                itAll.push_back(' ');
                skip = 1;
            }
        }

        return itAll;
    }
};

class Element
{
private:
    int key;
    pair<string, string> value;

public:
    Element(string value1, string value2)
    {
        value.first = value1;
        value.second = value2;
    }
    Element() {}
    void setKey(int key)
    {
        this->key = key;
    }
    int getKey()
    {
        return key;
    }
    pair<string, string> getValue()
    {
        return value;
    }
};

class List
{
private:
    list<Element> elements;

public:
    List() {}
    list<Element> &getList()
    {
        return elements;
    }
    void addItem(Element &item)
    {
        elements.push_back(item);
    }
    void removeItem(Element &item)
    {
        for (auto itr = elements.begin(); itr != elements.end(); ++itr)
        {
            if (itr->getValue() == item.getValue())
            {
                itr = elements.erase(itr);
                break;
            }
        }
    }
};

class HashTable
{
private:
    vector<List> hash;

public:
    HashTable(int max) : hash(max) {}

    vector<List> getHash()
    {
        return hash;
    }

    int pow(int x, int y)
    {
        int p = 1;
        for (int i = 1; i <= y; i++)
        {
            p *= x;
        }

        return p;
    }
    int h(const string &key)
    {
        int hash = 0;
        for (unsigned int i = 0; i < key.length(); i++)
        {
            hash += static_cast<int>(key[i]) * (int)pow(TAM_ASCII, key.length() - i - 1) % M;
        }
        return hash % M;
    }
    list<Element> search(int k)
    {
        return hash[k].getList();
    }

    int getHashKey(string value)
    {
        return h(value);
    }

    void insert(string value1, string value2)
    {
        int key = h(value2);
        Element element{value1, value2};
        element.setKey(key);
        hash[key].addItem(element);
    }

    void remove(int key)
    {
        list<Element> &le = hash[key].getList();
        for (auto itr = le.begin(); itr != le.end(); ++itr)
        {
            if (itr->getKey() == key)
            {
                le.erase(itr);
            }
        }
    }

    void printHash()
    {
        for (auto elements : hash)
        {
            list<Element> le = elements.getList();
            for (auto itr = le.begin(); itr != le.end(); ++itr)
            {
                cout << itr->getKey() << ": "
                     << "(" << itr->getValue().first << ", " << itr->getValue().second << ") "
                     << ", " << endl;
            }
        }
    }
};

string translate(HashTable &t, string &text)
{
    string translatedText;
    for (unsigned int i = 0; i < text.length(); i += 3)
    {
        string letter;
        letter.push_back(text[i]);
        letter.push_back(text[i + 1]);
        letter.push_back(text[i + 2]);
        int key = t.getHashKey(letter);
        list<Element> listElements = t.search(key);
        for (auto itr = listElements.begin(); itr != listElements.end(); ++itr)
        {
            if (itr->getValue().second == letter)
            {
                for (long unsigned int i = 0; i < itr->getValue().first.length(); i++)
                {
                    translatedText.push_back(itr->getValue().first[i]);
                }
                break;
            }
        }
    }
    return translatedText;
}

list<string> readPatterns()
{
    list<string> words;
    string word;

    while (true)
    {
        string upper;
        cin >> word;
        if (word[0] >= 'A' && word[0] <= 'Z')
        {
            for (char p : word)
            {
                upper.push_back(p);
            }
        }
        else
        {
            for (char p : word)
            {
                upper.push_back(p - ('a' - 'A'));
            }
        }
        if (upper == "FIM" || word == "FIM")
        {
            break;
        }
        words.push_back(upper);
    }
    return words;
}

string caesarCipher(string &text, int shift)
{
    string decryptedText;
    for (char c : text)
    {
        if (c != ' ' && c != '.')
        {
            decryptedText += char((c - 'A' - shift + 26) % 26 + 'A');
        }
        else
        {
            decryptedText += c;
        }
    }
    return decryptedText;
}

list<string> findCaesarCipher(string &text, list<string> &patterns)
{
    string decryptedText;
    string answer;
    list<string> final;
    int found = 0;
    for (int i = 0; i < 26; i++)
    {
        decryptedText = caesarCipher(text, i);
        for (string pattern : patterns)
        {
            BoyerMoore bm(pattern);
            answer = bm.search(decryptedText);
            final.push_back(answer);
            for (auto b : answer)
            {
                if (b == '(')
                {
                    found = 1;
                    break;
                }
            }
        }
        if (found == 1)
        {
            return final;
        }
        else
        {
            final.clear();
        }
    }
    final.push_back("-1");
    return final;
}

void printResults(list<string> &decryptedText, list<string> &patterns)
{
    auto itr1 = patterns.begin();
    auto itr2 = decryptedText.begin();

    while (itr1 != patterns.end() && itr2 != decryptedText.end())
    {
        cout << *itr1 << ": ";
        cout << *itr2 << endl;

        ++itr1;
        ++itr2;
    }
}

int main()
{

    HashTable table(M);
    table.insert("A", ":::");
    table.insert("B", ".::");
    table.insert("C", ":.:");
    table.insert("D", "::.");
    table.insert("E", ":..");
    table.insert("F", ".:.");
    table.insert("G", "..:");
    table.insert("H", "...");
    table.insert("I", "|::");
    table.insert("J", ":|:");
    table.insert("K", "::|");
    table.insert("L", "|.:");
    table.insert("M", ".|:");
    table.insert("N", ".:|");
    table.insert("O", "|:.");
    table.insert("P", ":|.");
    table.insert("Q", ":.|");
    table.insert("R", "|..");
    table.insert("S", ".|.");
    table.insert("T", "..|");
    table.insert("U", ".||");
    table.insert("V", "|.|");
    table.insert("W", "||.");
    table.insert("X", "-.-");
    table.insert("Y", ".--");
    table.insert("Z", "--.");
    table.insert(" ", "---");
    table.insert(".", "~~~");
    string alienText;
    cin >> alienText;
    string translatedText = translate(table, alienText);
    list<string> words = readPatterns();
    list<string> decipheredText = findCaesarCipher(translatedText, words);
    printResults(decipheredText, words);
    return 0;
}