#include "rope.h"


#include <iostream>

// Delete
void print_int(int input) {
    cout << input << endl;
}
void print_str(string input) {
    cout << input << endl;
}

tree_node* init_node(string data) {
    tree_node* new_node = new tree_node();
    new_node->left = NULL;
    new_node->right = NULL;
    if (data == "") {
        // This is an internal node
        new_node->is_leaf = false;
        new_node->weight = 0;
    } else {
        new_node->is_leaf = true;
        new_node->weight = data.length();
    }
    new_node->data = data;
    return new_node;
}

void concat(tree_node* root_tree, tree_node* concat_tree) {
    if (concat_tree->left == NULL) {
        // There is nothing in the concatenation tree so just return the original root
        return;
    }
    if (root_tree->weight == 0) {
        int sub_len = get_subtr_len(concat_tree);
        root_tree->left = concat_tree;
        root_tree->weight = sub_len;
        return;
    } else {
        tree_node* root_left = root_tree->left;
        if (root_left->left != NULL && root_left->right == NULL) {
            root_left->right = concat_tree;
            return;
        } else if (root_left->left != NULL && root_left->right != NULL) {
            tree_node* connector = init_node("");
            connector->left = root_tree->left;
            connector->right = concat_tree;
            int sub_len = get_subtr_len(connector);
            root_tree->left = connector;
            root_tree->weight = sub_len;
            return;
        }
    }
}

tree_node* create_rope(string input_str) {
    // API layer
    tree_node* new_root = init_node("");
    create_rope_recurse(input_str, new_root);
    tree_node* balanced = rebalance(new_root);

    return balanced;
}

void create_rope_recurse(string input_str, tree_node* root) {
    if (input_str.length() == 2) {
        tree_node* new_root = create_new_subtree(input_str);
        concat(root, new_root);
        return;
    }
    int split_index = split_str(input_str);
    create_rope_recurse(input_str.substr(0, split_index), root);
    create_rope_recurse(input_str.substr(split_index), root);
}

tree_node* rebalance(tree_node* root) {
    vector<tree_node*> leaves = collect_leaves(root);
    tree_node* connector = init_node("");
    int weight = 0;
    if (leaves.size() == 1) {
        connector->left = leaves[0];
        weight = leaves[0]->data.size();
        connector->weight = weight;
    } else {
        int split_index = calc_split_index(leaves.size());
        rebalance_recursion(vector<tree_node*>(leaves.begin(), leaves.begin() + split_index), connector, weight);
        rebalance_recursion(vector<tree_node*>(leaves.begin() + split_index, leaves.end()), connector, weight);
    }
    int connector_weight = get_subtr_len(connector->left);
    connector->weight = connector_weight;

    if (connector->right == NULL) {
        // Connector can act as the new root node so we don't need
        // to create another
        return connector;
    }

    tree_node* new_root = init_node("");
    new_root->left = connector;
    new_root->weight = weight;
    return new_root;
}

void rebalance_recursion(vector<tree_node*> leaves, tree_node* parent, int& weight) {
    if (leaves.size() == 0) {
        return;
    }

    tree_node* new_internal = init_node("");

    if (parent->left == NULL) {
        parent->left = new_internal;
    } else {
        parent->right = new_internal;
    }

    if (leaves.size() == 1) {
        new_internal->left = leaves[0];
        new_internal->weight = leaves[0]->data.size();
        weight += leaves[0]->data.size();
        return;
    } else if (leaves.size() == 2) {
        new_internal->left = leaves[0];
        new_internal->right = leaves[1];
        new_internal->weight = leaves[0]->data.size();
        weight += leaves[0]->data.size() + leaves[1]->data.size();
        return;
    }

    int split_index = calc_split_index(leaves.size());
    rebalance_recursion(vector<tree_node*>(leaves.begin(), leaves.begin() + split_index), new_internal, weight);
    rebalance_recursion(vector<tree_node*>(leaves.begin() + split_index, leaves.end()), new_internal, weight);
    
    int sub_len = get_subtr_len(new_internal->left);
    new_internal->weight = sub_len;
}

string index_search(tree_node* root, int index, bool return_basepair) {
    if (index >= root->weight) {
        return "";
    }

    tree_node* current = root->left;
    while (current != NULL) {
        if (current->is_leaf == true) {
            if (return_basepair == true) {
                return current->data;
            }
            string char_str(1, current->data[index]);
            return char_str;
        } else if (index < current->weight) {
            current = current->left;
        } else if (index >= current->weight) {
            index = index - current->weight;
            current = current->right;   
        }
    }
}

vector<tree_node*> collect_leaves(tree_node* root) {
    vector<tree_node*> ret;
    collect_traverse(root, ret);
    return ret;
}

void collect_traverse(tree_node* current, vector<tree_node*>& ret) {
    if (current == NULL) {
        return;
    }

    collect_traverse(current->left, ret);
    collect_traverse(current->right, ret);
    collect_visit(current, ret);
}

void collect_visit(tree_node* current, vector<tree_node*>& ret) {
    if (current->is_leaf == true) {
        //print_str(current->data);
        ret.push_back(current);
    }
}

string report(tree_node* root) {
    string ret;
    report_traverse(root, ret);
    return ret;
}

void report_traverse(tree_node* current, string& ret) {
    if (current == NULL) {
        return;
    }

    report_traverse(current->left, ret);
    report_traverse(current->right, ret);
    report_visit(current, ret);
}

void report_visit(tree_node* current, string& ret) {
    if (current->is_leaf == true) {
        ret += current->data;
    }
}

tree_node* find_parent(tree_node* root, int& index, string& direction) {
    tree_node* current = root->left;
    while (current != NULL) {
        if (index < current->weight) {
            if (current->left->is_leaf == true) {
                direction = "left";
                return current;
            }
            current = current->left;
        } else if (index >= current->weight) {
            if (current->right->is_leaf == true) {
                direction = "right";
                return current;
            }
            index = index - current->weight;
            current = current->right;   
        }
    }
}

bool insert_node(tree_node* root, string data, int index) {
    // API layer
    tree_node* new_parent = create_new_subtree(data);
    bool inserted = insert(root, new_parent, index);
    return inserted;
}

bool insert(tree_node* root, tree_node* new_node, int index) {
    if (index > root->weight) {
        return false;
    }

    string direction;
    tree_node* parent = find_parent(root, index, direction);
    if (direction == "left") {
        new_node->right = parent->left;
        parent->left = new_node;
    } else if (direction == "right") {
        new_node->right == parent->right;
        parent->right = new_node;
    }
    rebalance(root);
    return true;
}

tree_node* insert_subtree(tree_node* root, tree_node* subtree, int index) {

    if (index > root->weight) {
        return;
    }

    string direction;
    tree_node* parent = find_parent(root, index, direction);
    
    if (direction == "left") {
        tree_node* new_node = create_new_subtree(parent->left->data);
        concat(subtree, new_node);
        parent->left = subtree;
    } else if (direction == "right") {
        tree_node* new_node = create_new_subtree(parent->right->data);
        concat(subtree, new_node);
        parent->right = subtree;
    }
    tree_node* balanced = rebalance(root);
    return balanced;
}


// Utilities

int split_str(string input_str) {
    int split_index = input_str.length() / 2;
    if (split_index % 2 == 1) {
        split_index--;
    }
    return split_index;
}

int calc_split_index(int vec_size) {
    if (vec_size == 2) {
        return 2;
    }
    int split_index = vec_size / 2;
    if (split_index % 2 == 1) {
        split_index++;
    }
    return split_index;
}

int get_subtr_len(tree_node* subtree) {
    int len = 0;
    len_traverse(subtree, len);
    return len;
}

void len_traverse(tree_node* current, int& len) {
    if (current == NULL) {
        return;
    }

    len_traverse(current->left, len);
    len_traverse(current->right, len);
    len_visit(current, len);
}

void len_visit(tree_node* current, int& len) {
    if (current->is_leaf == true) {
        len += current->data.length();
    }
}

tree_node* create_new_subtree(string input_str) {
    tree_node* new_root = init_node("");
    tree_node* new_leaf = init_node(input_str);
    new_root->left = new_leaf;
    new_root->weight = new_leaf->data.size();
    return new_root;
}
