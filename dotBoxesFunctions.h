#ifndef HONORS
#define HONORS

#include <iostream>
using std::ostream;using std::cout;using std::cin;using std::endl;using std::left;
using std::boolalpha;
#include<string>
using std::string;
#include<vector>
using std::vector;
#include <iomanip>
using std::setw;
#include<map>
using std::map;
#include<utility>
using std::pair;
using board = vector<vector<string>>;
using bool_matrix= vector<vector<bool>>;
using box_pair=pair<bool,vector<int>>;
template <typename T>
void print_vector(const vector<T>& vect, ostream& out){
  for(auto element : vect){
    out<<setw(3)<<left<<element;
  }
  out<<endl;
}
template <typename T>
void draw_board(const T& matrix, ostream& out){
  for(auto element: matrix){
    print_vector(element,out);
  }
}
board starting_board();
string vector_to_string(const vector<int> &v);
bool_matrix create_twoD_bool();
board update_board(board& gameboard,bool_matrix& twoD_bool,vector<int>& index_a, vector<int>& index_b,box_pair& boxed,string player);
//void draw_board(const board& gameboard, ostream& out);
void move(board& gameboard,int a,int b,vector<int>& index_a,vector<int>& index_b);
vector<int> generate_moves(bool_matrix& twoD_bool);
void check_score (bool_matrix twoD_bool, box_pair boxed,string player,box_pair& score);
bool is_available (board& gameboard,bool_matrix& twoD_bool, int a, int b);
bool is_legal (board& gameboard,bool_matrix& twoD_bool, int a, int b);
box_pair check_for_box (board& gameboard,bool_matrix& twoD_bool,int x,int y,bool hyphen,bool slash);
void play();
#endif
