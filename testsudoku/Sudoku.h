#ifndef SUDOKU_H_
#define SUDOKU_H_

#include<iostream>
#include<vector>
#include<set>
#include<iterator>
#include<algorithm>
#include<cstdlib>
#include<algorithm>

using std::cin;
using std::cout;
using std::vector;
using std::set;
using std::endl;


class Sudoku{
    public:
        typedef struct{
            int num;
            bool fixed;
            set<int> candidators;    
        }sudokuCell;
        
        Sudoku();
        Sudoku & operator=(Sudoku & a);
        explicit Sudoku(const int *arr);

        void giveQuestion();
        void readIn();
        void solve();
        void changeNum(int a, int b);
        void changeRow(int a, int b);
        void changeCol(int a, int b);
        void rotate(int n);
        void flip(int n);
        void transform();
        
        void findSudokuSolution(int sp);
        bool setCandidatorTofixed(int sp, int trynum);
        bool exclusiveCorrelativeCandidators(int sp, int trynum);
        bool processSinglesCandidature(int sp);
        void printSudokuSolution();
        void validcandidators(int sp);
        bool trushsudoku(int sp);

    private:
        Sudoku(Sudoku &a){}
        sudokuCell cell[81];
        int fixedcount;
};
#endif
