#pragma once

#include <memory>
#include <vector>

class Node : public std::enable_shared_from_this<Node> {
public:
    using ShPtr = std::shared_ptr<Node>;

    Node() : _parent{} {}

    void addChild(ShPtr child) {
        child->_parent = shared_from_this();
        _children.push_back(child);
    }

    ShPtr parent() const {
        return _parent.lock();
    }

    const std::vector<ShPtr>& children() const {
        return _children;
    }

    bool isRoot() const {
        return !_parent.lock();
    }
    
    bool isLeaf() const {
        return _children.empty();
    }

private:
    std::weak_ptr<Node> _parent;
    std::vector<ShPtr> _children;
};