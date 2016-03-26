#ifndef SUDOKU_H_
#define SUDOKU_H_

#include<iostream>
#include<vector>
#include<set>
#include<iterator>
#include<algorithm>
#include<cstdlib>
#include<time>

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
        void rotate(int n);
        void flip(int n);
        void transform();
        
        void findSudokuSolution(Sudoku & game, int sp);
        bool setCandidatorTofixed(int sp, int trynum);
        bool exlusiveCorrelativeCandidators(int sp, int trynum);
        bool processSinglesCandidature(int sp);
        void printSudokuSolution();

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

bool Sudoku::exclusiveCorrelativeCandidators(int sp, int trynum){
    
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

bool Sudoku::processSinglesCandidature(int sp){
    int row = sp / 9;
    int col = sp % 9;
    for( i = 0; i < 9; i++){
        if(!cell[row * 9 + i].fixed && cell[row * 9 + i].candidators.size()==1)
            if(!setCandidatorTofixed(sp, *(cell[row * 9 + i].candidators.begin()            )))
                return false;

        if(!cell[col + 9 * i].fixed && cell[col + 9 * i].candidators.size()==1)
            if(!setCandidatorTofixed(sp, *(cell[col + 9 * i].candidators.begin()            )))
                return false;
    }

    for( i = 0; i < 3; i++)
        for( j = 0; j < 3; j++){
            if(!cell[(row / 3 + i) + j].fixed && cell[(row / 3 + i) + j].candidators.size()==1)
                if(!setCandidatorTofixed(sp, *(cell[(row / 3 + i) + j].candidators.begin())))
                return false;
        }

    return true;
}


bool Sudoku::setCandidatorTofixed(int sp, int trynum){
    
    cell[sp].fixed = true;
    cell[sp].num = trynum;

    if(!exclusiveCorrelativeCandidators(sp, trynum))
        return false;
    if(!processSinglesCandidature(sp))
        return false;

    fixedcount++;
    return true;    
}

void Sudoku::solve(){
    readIn();
    findSudokuSolution(0);
    if(answer == 0)
        cout<<0<<endl;
    if(answer == 1){
        for(int i = 0; i < 9; i++){
            for(int j = 0; j < 9; j++)
                cout<<ans1[i * 9 + j]<<" ";
             cout<<endl;
        }
    }                
}

void Sudoku::changeNum(int a, int b){
    int as, bs;
    sudokuCell temp;
    if(a <= 9 && a >= 1 && b <= 9 && b >= 1){
        as = 0;
        bs = 0;
        for(int i = 0; i < 9; i++){
            for(int j = 0; j < 9; j++){
                if(cell[i * 9 + j].num == a){
                    as = i * 9 + j;
                    continue;    
                }
                if(cell[i * 9 + j].num == b){
                    bs = i * 9 + j;
                    continue;
                }
            }
            if(as == 0 && bs == 0)
                continue;
            else{
                temp = cell[as];
                cell[as] = cell[bs];
                cell[bs] = temp;
            }
        }
    } 
}

void Sudoku::changeRow(int a, int b){
    if( a >= 0 && a <= 2 && b >= 0 && b <= 2 && a != b){ 
     sudokuCell copy[27];
    for(i = 0; i < 27; i++)
        copy[i] = cell[ 27 * a + i];
    for(i = 0; i < 27; i++)
        cell[27 * a + i] = cell[27 * b + i];
    for(i = 0; i < 27; i++)
        cell[27 * b + i] = copy[i];    
    } 
}

void Sudoku::changeCol(int a, int b){
    if( a >= 0 && a <= 2 && b >= 0 && b <= 2 && a != b){
    sudokuCell copy[27];
    for(i = 0; i < 27; i++)
        copy[i] = cell[i * 9 + a * 3];
    for(i = 0; i < 27; i++)
        cell[i * 9 + a * 3] = cell[i * 9 + b * 3];
    for(i = 0; i < 27; i++)
        cell[i * 9 + b * 3] = copy[i];
    }
}

void Sudoku::rotate(int n){
    int a;
    sudokuCell copy(81);
    a = n % 4;
    switch(a){
        case 1 :
            for(i = 0; i < 81; i++)
                copy[i] = cell[i];

            for(int i = 8; i >= 0; i--) 
                for(int j = 0; j < 9; j++){
                    cell[(8 - i) + 9 * j] = copy[9 * (8 - i) + j];
                } 
            break;

        case 2 :
            for(i = 0; i < 81; i++)
                copy[i] = cell[i];

            for(int i = 8; i >= 0; i--)
                for(int j = 8; j >= 0; j--){
                    cell[i * 9 + j] = copy[(8 - j) + 9 * (8 - i)]
                }
            break;

        case 3 :
            for(i = 0; i < 81; i++)
                copy[i] = cell[i];

            for(int i = 0; i < 9; i++)
                for(int j = 8; j >= 0; j--){
                    cell[j * 9 + i] = copy[ (8 - j) + i * 9];
                }
            break;            
    }

}

void Sudoku::flip(int n){
    sudokuCell copy[81];
    if(n == 0){
        for(i = 0; i < 81; i++)
            copy[i] = cell[i];
        
        for(i = 8; i > 4; i--)
            for(j = 0; j < 9; j++)
                cell[i * 9 + j] = copy[(8 - i) * 9 + j];

        for(i = 8; i > 4; i--)
            for(j = 0; j < 9; j++)
                cell[(8 - i) * 9 + j] = copy[i * 9 + j];

    }
    
    if(n == 1){
        for(i = 0; i < 81; i++)
            copy[i] = cell[i];

        for(i = 0; i < 4; i++)
            for(j = 0; j < 9; j++)
                cell[j * 9 + i] = copy[(8 - i) + j * 9];

        for(i = 0; i < 4; i++)
            for(j = 0; j < 9; j++)
                cell[(8 - i) + j * 9] = copy[j * 9 + i];
    
    }

}

void Sudoku::transform(){
    srand(time(NULL));
    readIn();
    changeNum(rand() % 9 + 1, rand() % 9 + 1);
    changeRow(rand() % 3, rand() % 3);
    changeCol(rand() % 3, rand() % 3);
    rotate(rand() % 101);
    flip(rand() % 2);
    printSudokuSolution();    
}

void Sudoku::giveQuestion(){
    int array[81] = { 8, 0, 0, 0, 0, 0, 0, 0, 0,
                      0, 0, 3, 6, 0, 0, 0, 0, 0,
                      0, 7, 0, 0, 9, 0, 2, 0, 0,
                      0, 5, 0, 0, 0, 7, 0, 0, 0,
                      0, 0, 0, 0, 4, 5, 7, 0, 0,
                      0, 0, 0, 1, 0, 0, 0, 3, 0,
                      0, 0, 1, 0, 0, 0, 0, 6, 8,
                      0, 0, 8, 5, 0, 0, 0, 1, 0,
                      0, 9, 0, 0, 0, 0, 4, 0, 0 } 

    for(i = 0; i < 9; i++){
        for(j = 0; j < 9; j++)
            cout<<array[i * 9 + j]<<" ";
        cout<<endl;
    }    
}
#endif
