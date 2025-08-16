#include <iostream>

using namespace std;

#include "../code/rope.h"

// delete
void rep(tree_node* test) {
    string rep = report(test);
    cout << rep << endl;
}

void show_menu() {
    cout << "1: Create new Rope" << endl;
    cout << "2: Display existing Ropes" << endl;
    cout << "3: Concatenate two Ropes" << endl;
    cout << "4: Insert new data into a Rope" << endl;
    cout << "5: Insert a subtree (Rope) into a Rope" << endl;
    cout << "6: Search by index" << endl;
    cout << "7: Split a Rope" << endl;
    cout << "8: Print Rope string" << endl;
}

struct rope_data {
    string name;
    tree_node* rope;
};

tree_node* find_rope(vector<rope_data> ropes, string name) {
    for (int i = 0; i < ropes.size(); i++) {
        if (ropes[i].name == name) {
            return ropes[i].rope;
        }
    }
}

int find_rope_index(vector<rope_data> ropes, string name) {
    for (int i = 0; i < ropes.size(); i++) {
        if (ropes[i].name == name) {
            return i;
        }
    }
    return -1;
}

bool check_existing(string name, vector<rope_data> ropes) {
    for (int i = 0; i < ropes.size(); i++) {
        if (ropes[i].name == name) {
            return true;
        }
    }
    return false;
}

void display_existing(vector<rope_data> ropes) {
    for (int i = 0; i < ropes.size(); i++) {
        cout << ropes[i].name << endl;
    }
}

int main() {
    vector<rope_data> ropes;


    bool exit = false;
    string choice;
    do {
        show_menu();
        cin >> choice;
        if (choice == "exit") {
            exit = true;
        } else if (choice == "1") {
            
            string rope_name;
            cout << "Enter a name" << endl;
            cin >> rope_name;
            while (check_existing(rope_name, ropes) == true) {
                cout << "There is already a Rope by that name" << endl;
                cin >> rope_name;
            }

            string data;
            cout << "Enter the string data" << endl;
            cin >> data;
            while (data.length() % 2 == 1) {
                cout << "Data must be divisible by 2 (an incomplete base pair was entered). Please enter string data" << endl;
                cin >> data;

            }

            tree_node* rope_ptr = create_rope(data);
            
            rope_data new_rope;
            new_rope.name = rope_name;
            new_rope.rope = rope_ptr;
            ropes.push_back(new_rope);

        } else if (choice == "2") {
            if (ropes.size() == 0) {
                cout << "There are no Ropes to display" << endl;
            } else {
                display_existing(ropes);
            }
        } else if (choice == "3") {
            if (ropes.size() < 2) {
                cout << "There are not enough Ropes to concatenate" << endl;
            } else {
                cout << "These are the existing Ropes: " << endl;
                display_existing(ropes);

                string rope_1_name;
                cout << "Enter the name of the first Rope" << endl;
                cin >> rope_1_name;
                tree_node* rope1 = find_rope(ropes, rope_1_name);
                while (rope1 == NULL) {
                    cout << "No rope by the name " << rope_1_name << " was found" << endl;
                    cin >> rope_1_name;
                    rope1 = find_rope(ropes, rope_1_name);
                }

                string rope_2_name;
                cout << "Enter the name of the second Rope" << endl;
                cin >> rope_2_name;

                tree_node* rope2 = find_rope(ropes, rope_2_name);
                while (rope2 == NULL) {
                    cout << "No rope by the name " << rope_2_name << " was found" << endl;
                    cin >> rope_2_name;
                    rope2 = find_rope(ropes, rope_2_name);
                }

                concat(rope1, rope2);
            }
        } else if (choice == "4") {
            if (ropes.size() == 0) {
                cout << "There are no Ropes" << endl;
            } else {
                cout << "These are the existing Ropes: " << endl;
                display_existing(ropes);
                string rope_name;
                cout << "Enter a Rope name to insert into" << endl;
                cin >> rope_name;
                tree_node* rope = find_rope(ropes, rope_name);
                while (rope == NULL) {
                    cout << "No rope by the name " << rope_name << " was found" << endl;
                    cin >> rope_name;
                    rope = find_rope(ropes, rope_name);
                }

                string new_data;
                cout << "Enter the new data string" << endl;
                cin >> new_data;
                while (new_data.length() % 2 == 1) {
                    cout << "Data must be divisible by 2 (an incomplete base pair was entered). Please enter string data" << endl;
                    cin >> new_data;

                }

                int index;
                cout << "Enter the insertion index" << endl;
                cin >> index;
                while (index % 2 == 1) {
                    cout << "That index is not divisible by 2. Only whole base pairs can be indexed. Please enter an even number" << endl;
                    cin >> index;
                }

                insert_node(rope, new_data, index);
            }
        } else if (choice == "5") {
            if (ropes.size() < 2) {
                cout << "There are not enough Ropes to insert" << endl;
            } else {
                cout << "These are the existing Ropes: " << endl;
                display_existing(ropes);
                string rope_name;
                cout << "Enter a Rope name to insert into" << endl;
                cin >> rope_name;
                tree_node* rope1 = find_rope(ropes, rope_name);
                while (rope1 == NULL) {
                    cout << "No rope by the name " << rope_name << " was found" << endl;
                    cin >> rope_name;
                    rope1 = find_rope(ropes, rope_name);
                }
                string rope_name_insert;
                cout << "Enter a Rope name to be inserted" << endl;
                cin >> rope_name_insert;
                tree_node* rope2 = find_rope(ropes, rope_name_insert);
                while (rope2 == NULL) {
                    cout << "No rope by the name " << rope_name_insert << " was found" << endl;
                    cin >> rope_name_insert;
                    rope2 = find_rope(ropes, rope_name_insert);
                }
                int index;
                cout << "Enter the insertion index" << endl;
                cin >> index;
                while (index % 2 == 1) {
                    cout << "That index is not divisible by 2. Only whole base pairs can be indexed. Please enter an even number" << endl;
                    cin >> index;
                }

                insert_subtree(rope1, rope2, index);
            }
        } else if (choice == "6") {
            if (ropes.size() == 0) {
                cout << "There are no Ropes" << endl;
            } else {
                cout << "These are the existing Ropes: " << endl;
                display_existing(ropes);
                string rope_name;
                cout << "Enter the Rope to be searched" << endl;
                cin >> rope_name;

                tree_node* rope = find_rope(ropes, rope_name);
                while (rope == NULL) {
                    cout << "No rope by the name " << rope_name << " was found" << endl;
                    cin >> rope_name;
                    rope = find_rope(ropes, rope_name);
                }

                int index;
                cout << "Enter the search index" << endl;
                cin >> index;
                while (index % 2 == 1) {
                    cout << "That index is not divisible by 2. Only whole base pairs can be indexed. Please enter an even number" << endl;
                    cin >> index;
                }

                string output = index_search(rope, index, true);
                cout << output << endl;
            }
        } else if (choice == "7") {
            if (ropes.size() == 0) {
                cout << "There are no Ropes" << endl;
            } else {
                cout << "These are the existing Ropes: " << endl;
                display_existing(ropes);
                string rope_name;
                cout << "Enter the Rope to be split" << endl;
                cin >> rope_name;
                
                tree_node* rope = find_rope(ropes, rope_name);
                while (rope == NULL) {
                    cout << "No rope by the name " << rope_name << " was found" << endl;
                    cin >> rope_name;
                    rope = find_rope(ropes, rope_name);
                }

                string split_name;
                cout << "Enter a name for the split Rope" << endl;
                cin >> split_name;
                
                int index;
                cout << "Enter the split index" << endl;
                cin >> index;
                while (index % 2 == 1) {
                    cout << "That index is not divisible by 2. Only whole base pairs can be indexed. Please enter an even number" << endl;
                    cin >> index;
                }

                split_struct split_s;
                split_tree(rope, index, split_s);

                int original_index = find_rope_index(ropes, rope_name);
                ropes[original_index].rope = split_s.original;

                rope_data new_rope;
                new_rope.name = split_name;
                new_rope.rope = split_s.split;
                ropes.push_back(new_rope);
            }
        } else if (choice == "8") {
            if (ropes.size() == 0) {
                cout << "There are no Ropes to display" << endl;
            } else {
                string name;
                cout << "Enter a Rope name" << endl;
                cin >> name;

                tree_node* rope;
                for (int i = 0; i < ropes.size(); i++) {
                    if (ropes[i].name == name) {
                        rope = ropes[i].rope;
                    }
                }
                string rep = report(rope);
                if (rep.length() == 0) {
                    cout << "No rope by that name was found" << endl;
                } else {
                    cout << "Data: " << rep << endl;
                }
            }
        }
    } while (exit != true);



    //split_struct split_s;

    //tree_node* neww = create_rope("ATCGATCGGCATGCTAATTACGXX");
    //tree_node* del = delete_subtree(neww, 2, 4);
    //rep(del);
    //tree_node* splitter = split_tree(neww, 4, split_s);
    //insert_node(neww, "XX", 2);
    //rep(split_s.original);
    //rep(split_s.split);
    //tree_node* neww1 = create_rope("BLAH");
    //insert_subtree(neww, neww1, 6);
    //concat(neww, neww1);
    //tree_node* bal = rebalance(neww);
    //rep(neww);
    //cout << neww->left->right->weight << endl;

    //string b = index_search(neww, 8, true);
    //cout << b << endl;
    

    
    
    /*
    vector<tree_node*> vec = collect_leaves(neww);
    
    for (int i = 0; i < vec.size(); i++) {
        cout << vec[i]->data << endl;
    }
*/






    //Rope test;
    //Rope test1;

    //test.create_rope("ATCG");
    //test.create_rope("ATCGTAGCTA");
    //test1.create_rope("GLAH");
    //rep(test);

    //test.insert_node("XX", 0);
    //rep(test);
    
    //tree_node* con = test.concat(test1.get_root(), false);
    

    //vector<tree_node*> leaves = test.collect_leaves();



    //string s = test.index_search(3, false);

    //cout << s << endl;
    
    /*
    for (int i = 0; i < leaves.size(); i++) {
        cout << (leaves[i]->data) << endl;
    }
    */
    

    

/*
    vector<tree_node*> leaves_two = test.collect_leaves();
    for (int i = 0; i < leaves_two.size(); i++) {
        cout << (leaves_two[i]->data) << endl;
    }

*/    
    //string s = test.index_search(2, false);
    //cout << s << endl;

    //cout << (leaves.length()) << endl;
    //cout << leaves << endl;
    
    // tree_node* new_node = test.init_node("hey");
    //cout << (new_node->data) << endl;

    return 0;
}