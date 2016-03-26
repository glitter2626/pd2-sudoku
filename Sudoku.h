#ifndef SUDOKU_H_
#define SUDOKU_H_

#include<iostream>
#include<vector>
#include<set>
#include<iterator>
#include<algorithm>
#include<cstdlib>

using std::cin;
using std::cout;
using std::vector;
using std::set;
using std::endl;

int NUMBERS[9] = {1, 2, 3, 4, 5, 6, 7, 8, 9}
int answer = 0;
vector<int> ans1(81);

class Sudoku{
    public:
        typedef struct{
            int num;
            bool fixed;
            set<int> candidators(NUMBERS, NUMBERS + 9);    
        }sudokuCell;
        
        Sudoku();
        explict Sudoku(const int *arr);

        void giveQuestion();
        void readIn();
        void solve();
        void changeNum(int a, int b);
        void changeRow(int a, int b);
        void changeCol(int a, int b);
        void rotate(int a);
        void flip(int n);
        void transform();
        
        void findSudokuSolution(Sudoku & game, int sp);
        bool setCandidatorTofixed(int sp, int trynum);
        bool ExlusiveCorrelativeCandidators(int sp, int trynum);
        bool ProcessSinglesCandidature(int sp, int trynum);

    private:
        vector<sudokuCell> cell(81);
        int fixedcount;
};

Sudoku::Sudoku():fixedcount(0){}

Sudoku::Sudoku(const int *arr):fixedcount(0){
    for(int i = 0; i < 81; i++){
        if(arr[i] != 0){
            cell[i].num = arr[i];
            cell[i].fixed = true;
            cell[i].candidators.insert(arr[i]);
        }
        else{
            cell[i].num = 0;
            cell[i].fixed = false;
            cell[i].candidators.insert(NUMBERS, NUMBERS + 9);
        }
        
    }
}


void Sudoku::readIn(){
    int a, i = 0;
    cin>>a;
    while(cin){
        if(a != 0){
            cell[i].num = a;
            cell[i].fixed = true;
            cell[i].candidators.insert(a);
        }
        else{
            cell[i].num = 0;
            cell[i].fixed = false;
            cell[i].candidators.insert(NUMBERS, NUMBERS + 9);
        }
        cin>>a;
    }   
}

void Sudoku::printSudokuSolution(){
    for(int i = 0; i < 9; i++){
        for(int j = 0; j < 9; j++)
            cout<<cell[i * 9 + j].num<<" ";
        cout<<endl;
    } 
}

void Sudoku::findSudokuSolution(int sp){
    if(fixedcount == 81){
        if(++answer < 2)
        for(int i = 0; i < 81; i++)
            ans1[i] = cell[i].num;
        return;
    }

    if(fixedcount > 81)
        exit(1);

    if(cell[sp].fixed == true)
        return (findSudokuSolution(sp + 1)); 

    Sudoku newState;
    set<int>::iterator it = cell[sp].candidators.begin();
    while(it != cell[sp].candidators.end()){
        newState = *this;
        if(newState.setCandidatorTofixed(sp, *it))
            newState.findSudokuSolution(sp + 1);

        ++it;

        if(answer == 2){
            cout<<2<<endl;
            return;
        }
    }
    
}

bool Sudoku::ExclusiveCorrelativeCandidators(int sp, int trynum){
    
    int row = sp / 9;
    int col = sp % 9;
    for( i = 0; i < 9; i++){
        cell[row * 9 + i].candidators.erase(trynum);
        if(cell[row * 9 + i].candidators.empty())
            return false;

        cell[col + 9 * i].candidators.erase(trynum);
        if(cell[i + 9 * i].candidators.empty)
            return false;
    }

    for( i = 0; i < 3; i++)
        for( j = 0; j < 3; j++){
            cell[(row / 3 + i) + j].candidators.erase(trynum);
            if(cell[(row / 3 + i) + j].candidators.empty())
                return false;
        }

    return true;
}

bool Sudoku::setCandidatorTofixed(int sp, int trynum){
    
    cell[sp].fixed = true;
    cell[sp].num = trynum;

    if(!exclusiveCorrelativeCandidators(sp, trynum))
        return false;
    if(!ProcessSinglesCandidature(sp, trynum))
        return false;

    fixedcount++;
    return true;    
}

void Sudoku::solve(){
    readIn();
    findSudokuSolution(0);
        
}


#endif