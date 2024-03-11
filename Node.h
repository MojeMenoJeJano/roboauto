#pragma once

#include "INode.h"

class Node : public INode {
    int state;

public:
    std::vector<std::unique_ptr<INode>> m_children;

    Node() {
        state = 1;
    };

    inline void makeChildren(int numberOfChildren) {
        for (int i = 0; i < numberOfChildren; i++) {
            m_children.push_back(std::make_unique<Node>());
        }
    };

    inline int value() const override {
        return state;
    };

    inline const std::vector<std::unique_ptr<INode>> &children() const override {
        return m_children;
    };
};


inline void makeTree(Node *root, const int depth);

inline void makeTree(Node *root, const int depth) {

    if (depth <= 1) {
        return;
    }
    root->makeChildren(2);
    auto &children = root->children();
    for (const auto &i: children) {
        Node *z = static_cast<Node *>(i.get());
        //z->makeChildren(3);
        makeTree(z, depth - 1);
    }
};

