#include <iostream>
#include <iomanip>
#include <queue>
#include <functional>
#include <fstream>
#include <cassert>

#include "huffman.hh"

////// Helper Functions //////

void printMap(const std::map<char, int> &map)
{
    if (map.empty())
    {
        std::cout << "Map is empty." << std::endl;
        return;
    }

    std::map<char, int>::const_iterator it = map.begin();

    std::cout << std::setw(10) << "Character" << std::setw(10) << "Count" << std::endl;
    while (it != map.end())
    {
        std::cout << std::setw(5) << it->first << std::setw(12.5) << it->second << std::endl;
        it++;
    }
}

void printCodeMap(const CodeMap &codeMap)
{
    for (const auto &pair : codeMap)
    {
        std::cout << "Character: " << pair.first << ", Code: ";
        for (bool bit : pair.second)
        {
            std::cout << bit;
        }
        std::cout << std::endl;
    }
}

std::string readFile(const std::string &path)
{
    std::string output;
    std::string line;

    std::ifstream readFile;
    readFile.open(path);

    while (std::getline(readFile, line))
    {
        output += (line);
    }

    readFile.close();

    return output;
}

//////////////////////////////

std::map<char, int> countCharacterFreuquency(const std::string &string)
{
    std::map<char, int> frequencyMap;

    for (const char &c : string)
    {
        frequencyMap[c] += 1;
    }

    return frequencyMap;
}

// Vergleichsfunktion für WeightedHuffmanPointer
template <typename T>
bool isWeightGreater(const std::pair<int, T> &first, const std::pair<int, T> &second)
{
    // > operator nur bis c++20 implementiert für pairs. Vergleicht erst first und dann second vom Pair.
    return first > second;
}

// HuffmannTree bauen
HuffmanPointer Huffman::buildHuffmanTree(const std::string &string)
{
    // Zähle anzahl der Zeichen
    std::map<char, int> frequencyMap = countCharacterFreuquency(string);

    // Priority Queue
    HuffmanCompareFunction compareFunc = isWeightGreater<HuffmanPointer>;
    std::priority_queue<WeightedHuffmanPointer, huffmanVector, HuffmanCompareFunction> treeQueue(compareFunc);

    // Erstelle für jedes Zeichen einen Weighted HuffmanPointer und füge in Queue ein.
    std::map<char, int>::const_iterator it = frequencyMap.begin();
    while (it != frequencyMap.end())
    {
        char character = it->first;
        int count = it->second;

        // Erstelle eine HuffmannNode auf dem heap.
        HuffmanPointer newNode(new HuffmanNode(character));

        WeightedHuffmanPointer WeightedNode = std::make_pair(count, newNode);

        treeQueue.push(WeightedNode);

        it++;
    }

    // Algorithmus mit queue ausführen
    while (treeQueue.size() > 1)
    {
        WeightedHuffmanPointer smallest = treeQueue.top();
        treeQueue.pop();
        WeightedHuffmanPointer secondsmallest = treeQueue.top();
        treeQueue.pop();

        // Elemente der WeightedPointer für bessere übersicht
        HuffmanPointer smallestNode = smallest.second;
        int smallestCount = smallest.first;
        HuffmanPointer secondsmallestNode = secondsmallest.second;
        int secondsmallestCount = secondsmallest.first;
        //////////////////////////////////////////////////////////
        HuffmanPointer newNode(new HuffmanNode(smallestNode, secondsmallestNode));

        WeightedHuffmanPointer newQueueElement = std::make_pair(smallestCount + secondsmallestCount, newNode);

        treeQueue.push(newQueueElement);
    }

    WeightedHuffmanPointer root = treeQueue.top();
    // Return einen HuffmanPointer
    return root.second;
}

void Huffman::treeNodeRecursion(const HuffmanPointer &node, const BitVector &bitvector)
{
    if (node->isLeaf())
    {
        _codeMap[node->getValue()] = bitvector;
        return;
    }

    BitVector rightVec = bitvector;
    rightVec.push_back(1);

    BitVector leftVec = bitvector;
    leftVec.push_back(0);

    treeNodeRecursion(node->getRight(), rightVec);
    treeNodeRecursion(node->getLeft(), leftVec);
}

void Huffman::generateHuffmanCodes()
{
    BitVector bitRight;
    bitRight.push_back(1);
    BitVector bitLeft;
    bitLeft.push_back(0);

    if (_root->isLeaf())
        return;

    treeNodeRecursion(_root->getRight(), bitRight);
    treeNodeRecursion(_root->getLeft(), bitLeft);
}

Huffman::Huffman(const std::string &string)
{
    assert(!string.empty() && "string is empty");

    _root = buildHuffmanTree(string);
    generateHuffmanCodes();

    printHuffmanCodes();
}

bool sortByCode(const std::pair<char, BitVector> &first, const std::pair<char, BitVector> &second)
{
    return first.second < second.second;
}

std::string boolVectorToString(const BitVector &bitvector)
{
    std::string bitvectorString;

    for (const bool &b : bitvector)
    {
        if (b)
            bitvectorString.push_back('1');
        else
            bitvectorString.push_back('0');
    }

    return bitvectorString;
}

void Huffman::printHuffmanCodes()
{
    std::vector<std::pair<char, BitVector>> vec(_codeMap.begin(), _codeMap.end());
    std::sort(vec.begin(), vec.end(), sortByCode);

    for (std::pair<char, BitVector> &p : vec)
    {
        char c = p.first;
        std::string codeString = boolVectorToString(p.second);

        std::cout << "Character: " << c << ", Code: " << codeString << std::endl;
    }
}

void Huffman::encode(const std::string &string, BitVector &bitvector)
{

    bitvector.clear();


    for (size_t i = 0; i < string.size(); i++)
    {
        char c = string[i];

        for (bool b : _codeMap[c])
        {
            bitvector.push_back(b);
        }
    }
    std::cout << boolVectorToString(bitvector) << std::endl;
}

std::string Huffman::decode(const BitVector &encodedText)
{
    HuffmanPointer treePtr = _root;
    std::string decodedString;

    for (std::vector<bool>::size_type i = 0; i < encodedText.size(); i++)
    {
        if (treePtr == nullptr)
            break;

        switch (encodedText[i])
        {
        case 1:
            treePtr = treePtr->getRight();
            if (treePtr->isLeaf())
            {
                decodedString.push_back(treePtr->getValue());
                treePtr = _root;
            }

            break;

        case 0:
            treePtr = treePtr->getLeft();
            if (treePtr->isLeaf())
            {
                decodedString.push_back(treePtr->getValue());
                treePtr = _root;
            }
            break;
        }
    }
    return decodedString;
}

int main()
{
    std::string text = readFile("text.txt");
    double savings;
    // Read text and Setup a BitVector
    BitVector BitVec;

    // Print Frequencys
    printMap(countCharacterFreuquency(text));
    //

    std::cout << std::endl;

    Huffman compressedText(text);
    
    std::cout << std::endl;

    compressedText.encode(text, BitVec);
    std::cout << compressedText.decode(BitVec) << std::endl;

    // Vergleiche Größe
    savings = -(((BitVec.size())/(text.size() * 8.0)) - 1) * 100;
    std::cout << "-------------------------------------------" << std::endl;
    std::cout << "Original: " << text.size() * 8 << " Bits" << std::endl;
    std::cout << "Compressed: " << BitVec.size() << " Bits" << std::endl;
    std::cout << savings << "% less memory" << std::endl;


    std::cout << std::endl << std::endl;
    std::cout << "---------------------------------" << std::endl;
    //////////////

    std::string gptInput = readFile("chat_gpt_story_ascii.txt");
    Huffman gpt(gptInput);

    gpt.encode(gptInput,BitVec);
    std::cout << gpt.decode(BitVec) << std::endl;

    // Vergleiche Größe
    savings = -(((BitVec.size())/(gptInput.size() * 8.0)) - 1) * 100;
    std::cout << "-------------------------------------------" << std::endl;
    std::cout << "Original: " << gptInput.size() * 8 << " Bits" << std::endl;
    std::cout << "Compressed: " << BitVec.size() << " Bits" << std::endl;
    std::cout << savings << "% less memory" << std::endl;

    std::cout << "----------------------------------" << std::endl;
    std::cout << "Anderen Input mit GPT codierung codieren." << std::endl;

    std::string newInput = "Nun sag, wie hast du's mit der Religion?";
    BitVector newBitVector;

    gpt.encode(newInput, newBitVector);
    std::cout << gpt.decode(newBitVector) << std::endl; // 

    // Vergleiche Größe
    savings = -(((newBitVector.size())/(newInput.size() * 8.0)) - 1) * 100;
    std::cout << "-------------------------------------------" << std::endl;
    std::cout << "Original: " << newInput.size() * 8 << " Bits" << std::endl;
    std::cout << "Compressed: " << newBitVector.size() << " Bits" << std::endl;
    std::cout << savings << "% less memory" << std::endl;
    
    return 0;
}