/*
A beast is in a labyrinth. The labyrinth is represented as a matrix of individual positions. At any moment, the beast is at one particular position and is turned in one of four possible directions (up, down, left and right).

In each round the beast makes one move. The possible moves are: TurnLeft, TurnRight, MakeStep (one step forward). At the beginning, the beast has a wall to its right. As the beast moves it tries to follow this wall (see the example below).

The input of the program contains a width and height followed by a map of the labyrinth. Individual characters depict individual positions in the labyrinth: 'X' is a wall and '.' is an empty spot. The characters '^', '>', 'v' and '<' depict the beast turned upward, to the right, downward and to the left, respectively.

Your program should read the input and then move the beast 20 times. After each move it should print a map of the labyrinth in the same form in which it read it. Write an empty line after each map.

Make a reasonable object design and implement it, please.

Beware: The first output is performed after the first move of the beast.

Example:

Input (there will actually be no leading spaces; they are present here only for aesthetic reasons):

  10
  6
  XXXXXXXXXX
  X....X...X
  X....X...X
  X.X..X.X.X
  X.X.>..X.X
  XXXXXXXXXX
Output (also shifted to the right):

  XXXXXXXXXX
  X....X...X
  X....X...X
  X.X..X.X.X
  X.X..>.X.X
  XXXXXXXXXX

  XXXXXXXXXX
  X....X...X
  X....X...X
  X.X..X.X.X
  X.X...>X.X
  XXXXXXXXXX

  XXXXXXXXXX
  X....X...X
  X....X...X
  X.X..X.X.X
  X.X...^X.X
  XXXXXXXXXX

  XXXXXXXXXX
  X....X...X
  X....X...X
  X.X..X^X.X
  X.X....X.X
  XXXXXXXXXX

  XXXXXXXXXX
  X....X...X
  X....X^..X
  X.X..X.X.X
  X.X....X.X
  XXXXXXXXXX

  XXXXXXXXXX
  X....X...X
  X....X>..X
  X.X..X.X.X
  X.X....X.X
  XXXXXXXXXX

  XXXXXXXXXX
  X....X...X
  X....X.>.X
  X.X..X.X.X
  X.X....X.X
  XXXXXXXXXX

  XXXXXXXXXX
  X....X...X
  X....X..>X
  X.X..X.X.X
  X.X....X.X
  XXXXXXXXXX

  XXXXXXXXXX
  X....X...X
  X....X..vX
  X.X..X.X.X
  X.X....X.X
  XXXXXXXXXX

  XXXXXXXXXX
  X....X...X
  X....X...X
  X.X..X.XvX
  X.X....X.X
  XXXXXXXXXX

  XXXXXXXXXX
  X....X...X
  X....X...X
  X.X..X.X.X
  X.X....XvX
  XXXXXXXXXX

  XXXXXXXXXX
  X....X...X
  X....X...X
  X.X..X.X.X
  X.X....X>X
  XXXXXXXXXX

  XXXXXXXXXX
  X....X...X
  X....X...X
  X.X..X.X.X
  X.X....X^X
  XXXXXXXXXX

  XXXXXXXXXX
  X....X...X
  X....X...X
  X.X..X.X^X
  X.X....X.X
  XXXXXXXXXX

  XXXXXXXXXX
  X....X...X
  X....X..^X
  X.X..X.X.X
  X.X....X.X
  XXXXXXXXXX

  XXXXXXXXXX
  X....X..^X
  X....X...X
  X.X..X.X.X
  X.X....X.X
  XXXXXXXXXX

  XXXXXXXXXX
  X....X..<X
  X....X...X
  X.X..X.X.X
  X.X....X.X
  XXXXXXXXXX

  XXXXXXXXXX
  X....X.<.X
  X....X...X
  X.X..X.X.X
  X.X....X.X
  XXXXXXXXXX

  XXXXXXXXXX
  X....X<..X
  X....X...X
  X.X..X.X.X
  X.X....X.X
  XXXXXXXXXX

  XXXXXXXXXX
  X....Xv..X
  X....X...X
  X.X..X.X.X
  X.X....X.X
  XXXXXXXXXX
*/

#include <iostream>
#include <vector>
#include <array>
#include <unordered_map>
using namespace std;

enum heroes_looks {left='<', down='v', right='>', up='^'};
const array<char, 4> arrows = {'<', 'v', '>', '^'};
const unordered_map<char, int> arrow_to_num ={{'<', 0},  {'v', 1}, {'>', 2}, {'^', 3}};

class Object{
    public:
    int x;
    int y;
    char look='.';
    virtual void display(){
        cout << look;
    }
    Object(){}

    Object(char look): look(look){}
};


class Obstacle:public Object{
    public:
    Obstacle(){}
    char look = 'x';
    Obstacle(char look): Object(look){
       
    }
    // virtual void display(){
    //     cout << look;
    // }
};

class ArrowObject: public Object{
    public:
    bool is_turned;
    ArrowObject(int x, int y, char look):Object(look){
        this->x = x;
        this->y = y;
    }
    void change_pos(int x, int y){
        this->x = x;
        this->y = y;
    }
    void turn_left(){
        this->look = arrows[(arrow_to_num.at(this->look)+1)%4];
    }
    void turn_right(){
        this->look = arrows[(arrow_to_num.at(this->look)+3)%4];
    }
    array<int, 2> direction(){
        array<int, 2> res;
        switch (look){
            case '<':
                res[0] = 0;
                res[1] = -1;
                break;
            case '>':
                res[0] = 0;
                res[1] = 1;
                break;
            case 'v':
                res[0] = 1;
                res[1] = 0;
                break;
            case '^':
                res[0] = -1;
                res[1] = 0;
                break;
        }
        return res;
    }
};
class Map{
    public:
    int width, height;
    vector<Object **> field;
    Map(int width, int height):width(width), height(height){
        for (int i = 0; i < height; i++){
            this->field.push_back(new Object*[width]);
            // for (int j=0; j < width; j++){
            //     this->field[i][j]->pos[0] = i;
            //     this->field[i][j]->pos[1] = j;
            // }
        }
    }
    Map(int width, int height, vector<Object **> field): width(width), height(height){
        this->field = field;
    }
    ~Map(){
       for (auto v: field){
            delete v;   
       }
       this->field.clear();
    }
    void display(){
        for (auto line: field){
            for (int j = 0; j< width; j++){
                line[j]->display();
            }
            cout << '\n';
        }
    }
};
class Labyrinth{
    public:
    Map *field;
    vector<ArrowObject*> heroes;
    
    Labyrinth(int width, int height){
        vector<Object **> new_field;
        //new_field.assign(height, new Object*[width]);
        for (int i = 0; i<height; i++){
            new_field.push_back(new Object*[width]);
            for (int j=0; j<width; j++){
                new_field[i][j] = new Obstacle();
            }
        }
        this->field = new Map(width, height, new_field);
    }
    Labyrinth(int width, int height, Map *field){
        this->field = field;
        for (int i=0; i<height; i++){
            for (int j=0; j<width; j++){
                if (arrow_to_num.find(this->field->field[i][j]->look) != arrow_to_num.end()){
                    ArrowObject *obj = new ArrowObject(i, j, this->field->field[i][j]->look);
                    //<int, 2> pos {i, j};
                   // GameObject *obj = new GameObject(this->field->field[i][j]->look);
                    heroes.push_back(obj);
                    
                }
            }
        }
    }
    Labyrinth(int width, int height, vector<char*> field){
        vector<Object**> new_field;
        for (int i=0; i<height; i++){
            new_field.push_back(new Object*[width]);
            for (int j=0; j<width; j++){
                if (arrow_to_num.find(field[i][j]) != arrow_to_num.end()){
                  //  cout<<field[i][j];
                    ArrowObject *obj = new ArrowObject(i, j, field[i][j]);

                    new_field[i][j] = obj;
                    heroes.push_back(obj);
                    
                }else{
                    new_field[i][j] = new Object(field[i][j]);
                }
            }
        }
        this->field = new Map(width, height, new_field);
    }
    void make_step(){
        Map *cp_field = new Map(this->field->width, this->field->height, this->field->field);
        for (auto her: heroes){
            array<int, 2> dir = her->direction();
            int new_x = her->x+dir[0];
            int new_y = her->y+dir[1];
         //   cout << "Test: dir = " << dir[0] << dir[1] << "element" << cp_field->field[new_x][new_y]->look<<'\n';
         //  cout << "Left el" << cp_field->field[her->x-dir[1]][her->y-dir[0]]->look << '\n';
            if (!her->is_turned&&cp_field->field[her->x+dir[1]][her->y-dir[0]]->look == '.'){
          //      cout << "Turn Left";
                her->is_turned = true;
                her->turn_right();

            }
            else if (cp_field->field[new_x][new_y]->look == '.'){
                her->is_turned = false;
                this->field->field[her->x][her->y] = new Object('.');
                her->change_pos(new_x, new_y);
                this->field->field[new_x][new_y] = her;
        
            } 
            else{
            //    cout << "Turn Right";
                her->turn_left();
            }
        }
    }
    ~Labyrinth(){
        for (auto v: heroes){
            delete v;   
        }
        heroes.clear();
        delete field;
    }
};


int main()
{

    int width, height;
    cin >> width;
    cin >> height;
    vector<char*> field;
    //field.assign(height, new char[width]);
    for (int i = 0; i<height; i++){
        field.push_back(new char[width]);
        for (int j=0; j<width; j++){
            cin >> field[i][j];
        }
    }

    Labyrinth *lab = new Labyrinth(width, height, field);
    for (int i=0; i<20; i++){
        lab->make_step();
        lab->field->display();
        cout<<'\n';
    }
    delete lab;
    return 0;
}