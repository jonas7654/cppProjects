#pragma once

#include "tree.hh"
#include <memory>
#include <vector>
#include <map>
#include <algorithm>

using HuffmanNode = BinaryTreeNode<char>;
using HuffmanPointer = std::shared_ptr<HuffmanNode>;
using WeightedHuffmanPointer = std::pair<int, HuffmanPointer>;
using BitVector = std::vector<bool>;
using CodeMap = std::map<char, BitVector>;
using huffmanVector = std::vector<WeightedHuffmanPointer>;
using HuffmanCompareFunction = std::function<bool(const WeightedHuffmanPointer&,const WeightedHuffmanPointer&)>;


class Huffman
{
private:
    HuffmanPointer _root;
    CodeMap _codeMap;

    HuffmanPointer buildHuffmanTree(const std::string&);
    void generateHuffmanCodes();

    void treeNodeRecursion(const HuffmanPointer& node, const BitVector& bitvector);

    void printHuffmanCodes();

public:
    Huffman(const std::string& string);
    void encode(const std::string& string, BitVector& bitvector);
    std::string decode(const BitVector&);
};