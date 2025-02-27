#pragma once
#include <memory>
#include <vector>

#include "TicTacToe.h"

template <typename T>
class TreeNode {
 public:
  typedef std::shared_ptr<const TreeNode> ShConstPtr;
  typedef std::shared_ptr<TreeNode> ShPtr;
  TreeNode() : _parent{} {}
  TreeNode(const TreeNode& other) = default;
  TreeNode(TreeNode&& other) = default;
  TreeNode& operator=(const TreeNode& other) = default;
  TreeNode& operator=(TreeNode&& other) = default;
  TreeNode(const T& data, ShPtr parent) : _data{data}, _parent{parent} {}
  TreeNode(const T& data) : _data{data}, _parent{} {}
  virtual ~TreeNode() = default;

  void addChild(ShPtr child) { _children.push_back(child); }

  ShPtr parent() const { return _parent.lock(); }

  std::vector<ShConstPtr> children() const {
    return std::vector<ShConstPtr>(_children.begin(), _children.end());
  }

  const std::vector<ShPtr>& children() { return _children; }

  bool isRoot() const { return !_parent.lock(); }

  bool isLeaf() const { return _children.empty(); }
  T& data() { return _data; }

  const T& data() const { return _data; }

 private:
  T _data;
  std::weak_ptr<TreeNode> _parent;
  std::vector<ShPtr> _children;
};
