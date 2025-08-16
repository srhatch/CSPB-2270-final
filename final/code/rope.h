#ifndef ROPE_H__
#define ROPE_H__

#include <string>
#include <vector>

using namespace std;

struct tree_node {
    tree_node* left;
    tree_node* right;
    bool is_leaf;
    int weight;
    string data;
};

struct split_struct {
    tree_node* original;
    tree_node* split;
};

tree_node* init_node(string data);

void concat(tree_node* root_tree, tree_node* concat_tree);

tree_node* create_rope(string input_str);

void create_rope_recurse(string input_str, tree_node* root);

tree_node* rebalance(tree_node* root);

void rebalance_recursion(vector<tree_node*> leaves, tree_node* parent, int& weight);

string index_search(tree_node* root, int index, bool return_basepair);

vector<tree_node*> collect_leaves(tree_node* root);

void collect_traverse(tree_node* current, vector<tree_node*>& ret);

void collect_visit(tree_node* current, vector<tree_node*>& ret);

string report(tree_node* root);

void report_traverse(tree_node* current, string& ret);

void report_visit(tree_node* current, string& ret);

tree_node* find_parent(tree_node* root, int& index, string& direction);

bool insert_node(tree_node* root, string data, int index);

bool insert(tree_node* root, tree_node* new_node, int index);

tree_node* insert_subtree(tree_node* root, tree_node* subtree, int index);

// TODO
tree_node* split(tree_node* root, int index, split_struct& split_s);

tree_node* split_tree(tree_node* root, int index, split_struct& split_s);




// by value or by index? delete substring?
tree_node* delete_subtree(tree_node* root, int start, int end);


// Utilities
int split_str(string input_str);

int calc_split_index(int vec_size);

int get_subtr_len(tree_node* subtree);

void len_visit(tree_node* current, int& len);

void len_traverse(tree_node* current, int& len);

tree_node* create_new_subtree(string input_str);

#endif