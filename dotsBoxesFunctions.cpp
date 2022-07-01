#include<iostream>
using std::ostream;
using std::cout;using std::endl;using std::right;
#include<string>
using std::string;using std::to_string;
#include<vector>
using std::vector;
#include <sstream>
using std::stringstream; using std::ostringstream;
#include<iterator>
using std::ostream_iterator;using std:: distance;
#include<algorithm>
using std::copy;using std::find;
#include<cmath> //abs()
#include<fstream>
using std:: ifstream; using std::ofstream;
#include <algorithm>
using std::max;
#include<utility>
using std::pair;
#include<map>
using std::map;
#include <ctime>
using std::time;
#include <cstdlib>
using std::srand;using std::rand;
#include "dotsBoxesFunctions.h"
using board = vector<vector<string>>;
using bool_matrix= vector<vector<bool>>;
using box_pair=pair<bool,vector<int>>;

string vector_to_string(const vector<int> &v){
  ostringstream oss;
  string str;
  if (!v.empty()){
    copy(v.begin(), v.end()-1, ostream_iterator<int>(oss,","));
  }
  oss<<v.back();
  str = "Score: A: "+ to_string(v[0])+" B: "+ to_string(v[1]);
  return str;
}
bool_matrix create_twoD_bool(){
  vector<bool>::size_type row_size=4;
  vector<bool> row(7,true);
  vector<bool> spaces(7,true);
  bool_matrix matrix_bool(row_size,row);
  bool_matrix::iterator it;
  unsigned int i=0;
  for(i=0,it=matrix_bool.begin();i<matrix_bool.size() && it!=matrix_bool.end();i++){
    it=matrix_bool.begin()+i;
    if(i%2==0 && i!=6){
      matrix_bool.insert(it+1,spaces);
    }

    for(vector<string>::size_type j=0;j<matrix_bool[i].size();j++){
      if(j%2==0 && i%2==0){
        matrix_bool[i][j]= false;
        if(j!=6 && i!=6){
          matrix_bool[i+1][j+1]= false;
        }
      }
    }
  }
  return matrix_bool;
}
board starting_board(){
  vector<string>::size_type row_size=4;
  vector<string> row(7," ");
  vector<string> spaces(7," ");
  board gameboard(row_size,row);
  board::iterator it;
  unsigned int i=0;
  for(i=0,it=gameboard.begin();i<gameboard.size() && it!=gameboard.end()-1;i++){
    it=gameboard.begin()+i;
    if(i%2==0 && i!=6){
      gameboard.insert(it+1,spaces);
    }

    for(vector<string>::size_type j=0;j<gameboard[i].size();j++){
      if(j%2==0 && i%2==0){
        gameboard[i][j]= to_string((j-j/2)+(2*i));
        //gameboard[i][j+1]=" ";
      }
    }
  }
  return gameboard;
}
board update_board(board& gameboard, bool_matrix& twoD_bool,vector<int>& index_a, vector<int>& index_b,box_pair& boxed,string player){

  //draw_board(gameboard,cout);
  bool hyphen=false,slash=false;
  int hor_index=0,ver_index=0;
  if (index_a!=index_b){
    if (index_a[0]==index_b[0]){
      hor_index= max(index_a[1],index_b[1])-1;
      hyphen=true;
    }
    if (index_a[1]==index_b[1]){
      ver_index= max(index_a[0],index_b[0])-1;
      slash=true;
    }
  }


  if(index_a != index_b){
    //gameboard[ver_index][index_a[1]]= slash ? "|" : gameboard[ver_index][index_a[1]];
    //gameboard[index_a[0]][hor_index]= hyphen ? "-" : gameboard[index_a[0]][hor_index];
    if(slash){
      gameboard[ver_index][index_a[1]]="|";
      twoD_bool[ver_index][index_a[1]]=false;
      boxed=check_for_box(gameboard,twoD_bool,ver_index,index_a[1],hyphen,slash);
      if(boxed.first){
        gameboard[boxed.second[0]][boxed.second[1]]=player;
        if(boxed.second.size()==4){
          gameboard[boxed.second[2]][boxed.second[3]]=player;
        }
        //twoD_bool[boxed.second[0]][boxed.second[1]]=false;
      }
    }
    if(hyphen){
      gameboard[index_a[0]][hor_index]="-";
      twoD_bool[index_a[0]][hor_index]=false;
      boxed=check_for_box(gameboard,twoD_bool,index_a[0],hor_index,hyphen,slash);
      if(boxed.first){
        gameboard[boxed.second[0]][boxed.second[1]]=player;
        //twoD_bool[boxed.second[0]][boxed.second[1]]=false;
        if(boxed.second.size()==4){
          gameboard[boxed.second[2]][boxed.second[3]]=player;
        }
      }
    }
  }

  return gameboard;
}
// void draw_board(const board& matrix, ostream& out){
//   for(auto element: matrix){
//     print_vector(element,out);
//   }
// }
box_pair check_for_box(board& gameboard,bool_matrix& twoD_bool,int x,int y,bool hyphen,bool slash){
  box_pair boxed;
  if(hyphen){
    if(x==0){
      bool r=!(twoD_bool[x+1][y-1] || twoD_bool[x+2][y] || twoD_bool[x+1][y+1]);
      if(r){
        boxed.first=true;
        boxed.second={x+1,y};
      }
    }
    else if(x==6){
      bool t=!(twoD_bool[x-1][y-1] || twoD_bool[x-2][y] || twoD_bool[x-1][y+1]);
      if(t){
        boxed.first=true;
        boxed.second={x-1,y};
      }
    }
    else{
      bool r=!(twoD_bool[x+1][y-1] || twoD_bool[x+2][y] || twoD_bool[x+1][y+1]);
      bool t=!(twoD_bool[x-1][y-1] || twoD_bool[x-2][y] || twoD_bool[x-1][y+1]);
      if(r){
        boxed.first=true;
        boxed.second={x+1,y};
      }
      if(t){
        boxed.first=true;
        boxed.second={x-1,y};
      }
      if(r && t){
        boxed.first=true;
        boxed.second={x+1,y,x-1,y};
      }
    }
  }
  if(slash){
    if(y==0){
      bool v=!(twoD_bool[x-1][y+1] || twoD_bool[x][y+2] || twoD_bool[x+1][y+1]);
      if(v){
        boxed.first=true;
        boxed.second={x,y+1};
      }
    }
    else if(y==6){
      bool w=!(twoD_bool[x-1][y-1] || twoD_bool[x][y-2] || twoD_bool[x+1][y-1]);
      if(w){
        boxed.first=true;
        boxed.second={x,y-1};
      }
    }
    else{
      bool v=!(twoD_bool[x-1][y+1] || twoD_bool[x][y+2] || twoD_bool[x+1][y+1]);
      bool w=!(twoD_bool[x-1][y-1] || twoD_bool[x][y-2] || twoD_bool[x+1][y-1]);
      if(v){
        boxed.first=true;
        boxed.second={x,y+1};
      }
      if(w){
        boxed.first=true;
        boxed.second={x,y-1};
      }
      if(v && w){
        boxed.first=true;
        boxed.second={x,y+1,x,y-1};
      }

    }
  }
  return boxed;
}
void move(board& gameboard,int a,int b,vector<int>& index_a,vector<int>& index_b){
  //vector<int> index_a(2,0),index_b(2,0);
  vector<string>::iterator it;
  //find(gameboard[i].begin(), gameboard[i].end(), to_string(a)) != gameboard[i].end()
  for(int i=0;i<gameboard.size();i++){
    it=find(gameboard[i].begin(), gameboard[i].end(), to_string(a));
    if(it != gameboard[i].end()){
      index_a[0]=i;
      index_a[1]=distance(gameboard[i].begin(),it);
    }
    it=find(gameboard[i].begin(), gameboard[i].end(), to_string(b));
    if(it != gameboard[i].end()){
      index_b[0]=i;
      index_b[1]= distance(gameboard[i].begin(),it);
    }
  }
}
bool is_legal(board& gameboard,bool_matrix& twoD_bool, int a, int b){
  vector<int> index_a(2,0),index_b(2,0);
  move(gameboard,a,b,index_a,index_b);
  //print_vector(index_a,cout);
  //print_vector(index_b,cout);
  bool islegal;
  if(index_a==index_b){
    islegal=false;
  }
  else{
    if(index_a[0]==index_b[0]){
      if(abs(index_a[1]-index_b[1])==2){
        islegal=true;
      }
      else{
        islegal=false;
      }
    }
    else if(index_a[1]==index_b[1]){
      if(abs(index_a[0]-index_b[0])==2){
        islegal=true;
      }
      else{
        islegal=false;
      }
    }
    else{
      islegal=false;
    }
  }
  // if(is_legal && is_available(gameboard,twoD_bool,a,b)){
  //   is_legal=true;
  // }
  // else{
  //
  // }
  islegal= islegal && is_available(gameboard,twoD_bool,a,b) ? true : false;
  return islegal;
}
bool is_available(board& gameboard,bool_matrix& twoD_bool, int a, int b){
  bool is_available= false;
  vector<int> index_a(2,0),index_b(2,0);
  move(gameboard,a,b,index_a,index_b);
  int hor_index=0,ver_index=0;
  bool hyphen=false,slash=false;
  if (index_a!=index_b){
    if (index_a[0]==index_b[0]){
      hor_index= max(index_a[1],index_b[1])-1;
      hyphen=true;
    }
    if (index_a[1]==index_b[1]){
      ver_index= max(index_a[0],index_b[0])-1;
      slash=true;
    }
  }
  if(index_a != index_b){
    if(slash && twoD_bool[ver_index][index_a[1]]){
      is_available=true;
    }
    else if(hyphen && twoD_bool[index_a[0]][hor_index]){
      is_available=true;
    }
  }
  return is_available;
}
void check_score(bool_matrix twoD_bool, box_pair boxed,string player,box_pair& score){
  //box_pair score;
  //vector<int>
  bool thereIs=false;
  if (boxed.first){
    if(player=="A"){
      if(boxed.second.size()==4){
        score.second[0]+=2;
      }
      score.second[0]+=1;
    }
    else{
      if(boxed.second.size()==4){
        score.second[1]+=2;
      }
      score.second[1]+=1;
    }
  }
  for(auto element: twoD_bool){
    for(auto i: element){
      if(i==true){
        thereIs=true;
      }
    }
  }
  score.first=thereIs ? false : true;
}
vector<int> generate_moves(bool_matrix& twoD_bool){
  vector<vector<int>> vect_moves,pos;
  vector<int> moves;
  vector<bool>::iterator it;
  bool hyphen,slash;
  //find(gameboard[i].begin(), gameboard[i].end(), to_string(a)) != gameboard[i].end()
  for(int i=0;i<twoD_bool.size();i++){
    it=find(twoD_bool[i].begin(), twoD_bool[i].end(),true);
    while(it != twoD_bool[i].end()){
      if(it != twoD_bool[i].end()){
        int x=distance(twoD_bool[i].begin(),it);
        moves.push_back(i);
        moves.push_back(x);
        vect_moves.push_back(moves);
        if(i%2==0){
          hyphen=true;
          pos.push_back({i,x-1,i,x+1});
        }
        else{
          slash=true;
          pos.push_back({i-1,x,i+1,x});
        }
        moves.clear();
      }
      it=find(it+1, twoD_bool[i].end(),true);
    }
  }
  //draw_board(pos,cout);
  //draw_board(vect_moves,cout);
  int x=pos.size();
  srand((unsigned)time(0));
  int index= int(rand()% x);
  return pos[index];
}
void play(){
  ofstream outfile;
  outfile.open("single_play.txt");
  vector<int> index_a(2,0),index_b(2,0),move_a(4,0),move_b(4,0);
  box_pair boxed={false,{0,0}},score={false,{0,0}};
  string player=" ";
  bool_matrix twoD_bool=create_twoD_bool();
  board gameboard=starting_board();
  outfile<<
  "**************Dotes And Boxes***************\n***************(/<>\\)*******************\n********   A  vs  B   ************\n***  An epic Showdown  *****"<<endl;
  draw_board(gameboard,outfile);
  while(!score.first){
    player="A";
    move_a=generate_moves(twoD_bool);
    //print_vector(move_a,outfile);
    int a=stoi(gameboard[move_a[0]][move_a[1]]);
    int b=stoi(gameboard[move_a[2]][move_a[3]]);
    outfile<<"A's turn: "<<a<<" "<<b<<endl;
    //outfile<<boolalpha<<is_legal(gameboard,twoD_bool,2,6)<<endl;
    if(is_legal(gameboard,twoD_bool,a,b)){
      move(gameboard,a,b,index_a,index_b);
      gameboard=update_board(gameboard,twoD_bool,index_a,index_b,boxed,player);
      draw_board(gameboard,outfile);
      check_score(twoD_bool,boxed,player,score);
      outfile<<vector_to_string(score.second)<<endl;

    }
     player="B";
     move_b=generate_moves(twoD_bool);
     int x=stoi(gameboard[move_b[0]][move_b[1]]);
     int y=stoi(gameboard[move_b[2]][move_b[3]]);
     outfile<<"B's turn: "<<x<<" "<<y<<endl;
     if(is_legal(gameboard,twoD_bool,x,y)){
       move(gameboard,x,y,index_a,index_b);
       gameboard=update_board(gameboard,twoD_bool,index_a,index_b,boxed,player);
       draw_board(gameboard,outfile);
       check_score(twoD_bool,boxed,player,score);
       outfile<<vector_to_string(score.second)<<endl;
     }
  }
  if(score.first){
    if(score.second[0] > score.second[1]){
      outfile<<"A's has won"<<endl;
    }
    else if(score.second[0] < score.second[1]){
      outfile<<"B's has won"<<endl;
    }
    else{
      outfile<<"The game is a draw"<<endl;
    }
  }

}
