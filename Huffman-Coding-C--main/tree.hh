#pragma once

#include <memory>

template <typename T>
class BinaryTreeNode;  // Forward declaration

template <typename T>
using NodePtr = std::shared_ptr<BinaryTreeNode<T>>;

template <typename T>
class BinaryTreeNode
{
private:
    T _value;
    NodePtr<T> _leftChild;
    NodePtr<T> _rightChild;

public:
    // Leaf node constructor with one value, sets children to nullptr
    BinaryTreeNode(T value)
        : _value(value), _leftChild(nullptr), _rightChild(nullptr)
    {}

    // Constructor for a node with two children (innerer Knoten)
    BinaryTreeNode(const NodePtr<T>& leftChild, const NodePtr<T>& rightChild)
        :_leftChild(leftChild), _rightChild(rightChild)
    {}

    BinaryTreeNode() = delete;

    // Getter
    T getValue() const
    {
        return _value;
    }

    NodePtr<T> getLeft() const
    {
        return _leftChild;
    }

    NodePtr<T> getRight() const
    {
        return _rightChild;
    }

    inline bool isLeaf() const
    {
        return (!_leftChild && !_rightChild);
    }
};
