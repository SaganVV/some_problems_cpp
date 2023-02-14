#include <iostream>
#include <string>
#include <array>
#include <map>
using namespace std;

enum condition { EMPTY = '.', X = 'x', O = 'o'};
enum game_result {x = 'X', o = 'O', DRAW='N'};
const map<int, char> scores { { 1, x}, { -1, o}, {0, DRAW} };

struct step{
    int score;
    int pos[2];
};

void print_step(step *stp){
    cout << '\n' << "Score: " << stp->score << '\n' << "Step: (" << stp->pos[0] << ", " << stp->pos[1] << ')' << '\n'; 
}

class TicTacToe {
public:

    char field[3][3];

    TicTacToe() {
        for (auto i = 0; i < 3; i++)
            for (auto j = 0; j < 3; j++)
                field[i][j] = EMPTY;
    }
    TicTacToe(char field[3][3]) {
        for (auto i = 0; i < 3; i++)
            for (auto j = 0; j < 3; j++)
                this->field[i][j] = field[i][j];
    }

    char current_player() {
        int x_count = 0;
        int o_count = 0;
        for (auto i = 0; i < 3; i++)
            for (auto j = 0; j < 3; j++) {
                if (field[i][j] == X)
                    x_count++;
                if (field[i][j] == O)
                    o_count++;
            }
        return (x_count == o_count) ? X : O;
    }

    bool is_finished_game() {
      
        int j;
        int count_empty = 0;
        for (int i = 0; i<3; i++)
            for (j=0; j<3; j++)
                if (field[i][j] == EMPTY)
                    count_empty+=1;
        if (count_empty == 0)
            return true;
        for (auto i = 0; i < 3; i++) {
            if (field[i][0] != EMPTY){
                for (j = 0; j < 3; j++) {
    
                    if (field[i][j] != field[i][0])
                        break;
                }
                if (j == 3)
                    return true;
            }
            if (field[0][i]!=EMPTY){
                for (j = 0; j < 3; j++) {
                    if (field[j][i] != field[0][i])
                        break;
                }
                if (j == 3)
                    return true;
            }
        }
        if (field[0][0]!=EMPTY){
            for (j = 0; j < 3; j++) {
                if (field[j][j] != field[0][0])
                    break;
            }
            if (j == 3)
                return true;
        }
        if (field[0][2] != EMPTY){
            for (j = 0; j < 3; j++) {
                if (field[j][2 - j] != field[0][2])
                    break;
            }
            if (j == 3)
                return true;
        }
        return false;
    }
    char winner() {
 
        int j;
        for (auto i = 0; i < 3; i++) {
            
            if (field[i][0] != EMPTY){
                for (j = 0; j < 3; j++) {
    
                    if (field[i][j] != field[i][0])
                        break;
                }
                if (j == 3)
                    return (field[i][0] == X)? O:X;
            }
            if (field[0][i] != EMPTY){
                for (j = 0; j < 3; j++) {
                    if (field[j][i] != field[0][i])
                        break;
                }  
                if (j == 3)
                    return (field[0][i] == X)? O:X;
            }
        }
        for (j = 0; j < 3; j++) {
            if (field[j][j] != field[0][0])
                break;
        }
        if (j == 3)
            return (field[0][0] == X)? O:X;
        for (j = 0; j < 3; j++) {
            if (field[j][2 - j] != field[0][2])
                break;
        }
        if (j == 3)
            return (field[0][2] == X)? O:X;
        return 'N';

    }
    void make_step(int x, int y) {
        if (!is_finished_game() && field[x][y] == EMPTY)
            field[x][y] = current_player();
    }
    void print_field() {
        for (auto i = 0; i < 3; i++) {
            for (auto j = 0; j < 3; j++)
                cout << field[i][j];
            cout << '\n';
        }
    }
    static step* minim(TicTacToe *ttt) {
        
        step *cur_step;

        step *res = new step();
        res->score = 234;
        if (ttt->is_finished_game()){
            char winner = ttt->winner();
        //    ttt->print_field();
            if (winner == 'N'){
                res->score = 0;
        
            }
            else
                res->score = (winner == X)? 1:-1;
            return res;
        }
        for (int i = 0; i<3; i++){
            for (int j = 0; j<3; j++){
                if (ttt->field[i][j] == EMPTY){
                    TicTacToe *ttt1 = new TicTacToe(ttt->field);
                    ttt1->make_step(i, j);

                    cur_step = TicTacToe::maxim(ttt1);
               
                    if (res->score > cur_step->score){
                        res->score = cur_step->score;
                        res->pos[0] = i;
                        res->pos[1] = j;
                       // cout << i<<j<<'\n';
                    }
                    delete ttt1;
                }
            }
        }
        return res;
    }
    static step* maxim(TicTacToe *ttt){
    
        step *cur_step;

        step *res = new step();
        res->score = -43;
        if (ttt->is_finished_game()){
            //cout << "sjjf";
            char winner = ttt->winner();
            
            if (winner == 'N'){
                res->score = 0;
        
            }
            else
                res->score = (winner == X)? 1:-1;
            return res;
        }
        for (int i = 0; i<3; i++){
            for (int j = 0; j<3; j++){
                if (ttt->field[i][j] == EMPTY){
                   // cout << i << j;
                    TicTacToe *ttt1 = new TicTacToe(ttt->field);
                    ttt1->make_step(i, j);

                    cur_step = TicTacToe::minim(ttt1);
                    
                    if (res->score <= cur_step->score){
                     //   cout << "BEFORE: ";
                     //   print_step(res);
                        res->score = cur_step->score;
                      //  cout <<'\n' << "AFTER: ";
                      //  print_step(cur_step);
                        res->pos[0] = i;
                        res->pos[1] = j;
                    }
                
                    delete ttt1;
                }
            }
        }
        return res;
    }
    static char predictable_winner(TicTacToe *ttt){
        step *best_step;
        if (ttt->current_player() == X)
            best_step = TicTacToe::maxim(ttt);
        else
            best_step = TicTacToe::minim(ttt);
        return scores.at(best_step->score);
    }
};

    int main()
{
    string inp;
    //cout << "INPUT 'x' or 'o' or number of examples\n";
    cin >> inp;
    if (inp[0] == X || inp[0] == O){
       cout << "You will play against computer\n" << "First step by 'x'";
       cout << "Your goal is not to get 3 " << inp[0] << "in one row\n";
       TicTacToe *ttt = new TicTacToe();
       int x, y;
       ttt->print_field();
       while (!ttt->is_finished_game()){
           if (ttt->current_player() == inp[0]){
               cout << "Input coordinates (two numbers between 0 and 2)\n";
               cin >> x >> y;
               ttt->make_step(x, y);
           }
           else {
               step *best_step; 
               if (ttt->current_player() == X)
                   best_step = TicTacToe::maxim(ttt);
               else
                   best_step = TicTacToe::minim(ttt);
               ttt->make_step(best_step->pos[0], best_step->pos[1]);
           }
           ttt->print_field();
       }
    }
    else
    {
        int n = stoi(inp);
        char field[3][3];
        
       // TicTacToe *ttt = new TicTacToe(field);
        // ttt->print_field();
        // cout << "asddas" << TicTacToe::maxim(ttt)->score;
        // while (!ttt->is_finished_game()){
            
        //     step *best_step;
        //     if (ttt->current_player() == X)
        //         best_step = TicTacToe::maxim(ttt);
        //     else
        //         best_step = TicTacToe::minim(ttt);
        //     ttt->make_step(best_step->pos[0], best_step->pos[1]);
        //     ttt->print_field();
        //     cout << ttt->is_finished_game();
        //     cout << "__________________________\n";
        // }
        // cout << ttt->winner();
        char *ans = new char[n]();
        for (int i=0; i<n; i++){
            for (int j=0; j<3; j++)
                for (int k=0; k<3; k++){
                  cin >> field[j][k];
                 //  cout << "field[j][k] = " << field[j][k];
                }
                
            TicTacToe *ttt = new TicTacToe(field);
     
            //step *winner = TicTacToe::maxim(ttt);
            ans[i] = TicTacToe::predictable_winner(ttt);
            delete ttt;
        }
        for (int i = 0; i<n; i++){
            cout << ans[i];
        }
        delete ans;
        }
    return 0;
}