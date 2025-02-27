#pragma once
#include <memory>
#include <vector>
#include "TicTacToe.h"


template<typename T>
class Node {
    public:
        typedef std::shared_ptr<const Node> ShConstPtr;
        typedef std::shared_ptr<Node> ShPtr;
        Node() : _parent{} {}
        Node(const Node& other) = default;
        Node(Node&& other) = default;
        Node& operator=(const Node& other) = default;
        Node& operator=(Node&& other) = default;
        Node(const T& data, ShPtr parent) : _data{data}, _parent{parent} {}
        Node(const T& data) : _data{data}, _parent{} {}
        virtual ~Node() = default;

        void addChild(ShPtr child) {
            _children.push_back(child);
        }

        ShPtr parent() const {
            return _parent.lock();
        }

        std::vector<ShConstPtr> children() const {
            return std::vector<ShConstPtr>(_children.begin(), _children.end());
        }

        const std::vector<ShPtr>& children() {
            return _children;
        }

        bool isRoot() const {
            return !_parent.lock();
        }
        
        bool isLeaf() const {
            return _children.empty();
        }
        T& data() {
            return _data;
        }

        const T& data() const {
            return _data;
        }
    private:
        T _data;
        std::weak_ptr<Node> _parent;
        std::vector<ShPtr> _children;
    };