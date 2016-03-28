#include"Sudoku.h"

int NUMBERS[9] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
int answer = 0;
vector<int> ans1(81);

Sudoku::Sudoku():fixedcount(0){}

Sudoku & Sudoku::operator=(Sudoku & a){
    fixedcount = a.fixedcount;
    for(int i = 0; i < 81; i++){
        cell[i].num = a.cell[i].num;
        cell[i].fixed = a.cell[i].fixed;
        cell[i].candidators.clear();
        copy(a.cell[i].candidators.begin(), a.cell[i].candidators.end(), std::insert_iterator<set<int> >(cell[i].candidators, cell[i].candidators.begin()));
    
    }
    return *this;
}

Sudoku::Sudoku(const int *arr):fixedcount(0){
    for(int i = 0; i < 81; i++){
        if(arr[i] != 0){
            fixedcount++;
            cell[i].num = arr[i];
            cell[i].fixed = true;
            /*cell[i].candidators.insert(arr[i]);*/
        }
        else{
            cell[i].num = 0;
            cell[i].fixed = false;
            cell[i].candidators.insert(NUMBERS, NUMBERS+9);
        }       
    }
}


void Sudoku::readIn(){
    int a, i = 0;
    while(i < 81){
        cin>>a;
        if(a != 0){
            fixedcount++;
            cell[i].num = a;
            cell[i].fixed = true;
           /* cell[i].candidators.insert(a);*/
        }
        else{
            cell[i].num = 0;
            cell[i].fixed = false;
            cell[i].candidators.insert(NUMBERS, NUMBERS+9);
        }
        i++;
    }
    
}

void Sudoku::printSudokuSolution(){
    for(int i = 0; i < 9; i++){
        for(int j = 0; j < 9; j++)
            cout<<cell[i * 9 + j].num<<" ";
        cout<<endl;
    } 
   /*     std::ostream_iterator<int, char > ot(cout, " ");
    for(int i = 0; i < 81; i++){
        copy(cell[i].candidators.begin(), cell[i].candidators.end(), ot);
        cout<<endl;
    } 
    for(int i = 0; i< 9; i++){
    for(int j = 0; j < 9; j++)
    cout<<cell[i*9 + j].fixed<<" ";
    cout<<endl;
    } */
}

void Sudoku::findSudokuSolution(int sp){
    if(fixedcount == 81 ){
       /* for(int i = 0; i < 9; i++){
            for(int j = 0; j < 9;j++)
                cout<<cell[i * 9 + j].num<<" ";
        cout<<endl;
        }*/
    
        if(++answer < 2)
            for(int i = 0; i < 81; i++)
                ans1[i] = cell[i].num;
        return;
    }

    while(cell[sp].fixed == true){
        sp++;
        if(sp >= 81)
            return findSudokuSolution(sp);

    }
    Sudoku newState;
    set<int>::iterator it = cell[sp].candidators.begin();
    while(it != cell[sp].candidators.end()){
        newState = *this;
        if(newState.setCandidatorTofixed(sp, *it))    
            newState.findSudokuSolution(sp + 1);
        ++it;
        if(answer == 2)
            return;
    }
}

bool Sudoku::exclusiveCorrelativeCandidators(int sp, int trynum){
    
    int row = sp / 9;
    int col = sp % 9;
    for(int i = 0; i < 9; i++){
        if(!cell[row * 9 + i].fixed ){
            cell[row * 9 + i].candidators.erase(trynum);
            if(cell[row * 9 + i].candidators.empty())
                return false;
        }

        if(!cell[col + 9 * i].fixed ){
            cell[col + 9 * i].candidators.erase(trynum);
            if(cell[col + 9 * i].candidators.empty())
                return false;
        }
    }

    for(int i = 0; i < 3; i++)
        for(int j = 0; j < 3; j++){
            if(!cell[(row / 3) * 3 * 9 + (col / 3) * 3 +  i * 9 + j].fixed){
                cell[(row / 3) * 3 * 9 + (col / 3) * 3 +  i * 9 + j].candidators.erase(trynum);
                if(cell[(row / 3) * 3 * 9 + (col / 3) * 3 +  i * 9 + j].candidators.empty())
                    return false;
            }
        }

    return true;
}

bool Sudoku::processSinglesCandidature(int sp){
    int row = sp / 9;
    int col = sp % 9;
    for(int i = 0; i < 9; i++){
        if(!cell[row * 9 + i].fixed && cell[row * 9 + i].candidators.size()==1)
            if(!setCandidatorTofixed(row * 9 + i, *(cell[row * 9 + i].candidators.begin()            )))
                return false;

        if(!cell[col + 9 * i].fixed && cell[col + 9 * i].candidators.size()==1)
            if(!setCandidatorTofixed(col + 9 * i, *(cell[col + 9 * i].candidators.begin()            )))
                return false;
    }

    for(int i = 0; i < 3; i++)
        for(int j = 0; j < 3; j++){
            if(!cell[(row / 3) * 3 * 9 + (col / 3) * 3 +  i * 9 + j].fixed && cell[(row / 3) * 3 * 9 + (col / 3) * 3 +  i * 9 + j].candidators.size()==1)
                if(!setCandidatorTofixed((row / 3) * 3 * 9 + (col / 3) * 3 +  i * 9 + j, *(cell[(row / 3) * 3 * 9 + (col / 3) * 3 + i * 9 + j].candidators.begin())))
                return false;
        }

    return true;
}


bool Sudoku::setCandidatorTofixed(int sp, int trynum){
    
    cell[sp].fixed = true;
    cell[sp].num = trynum;
    cell[sp].candidators.clear();
    

    if(!exclusiveCorrelativeCandidators(sp, trynum))
        return false;
    if(!processSinglesCandidature(sp))
        return false;
    fixedcount++;
    return true;    
}

void Sudoku::solve(){
   /* readIn();
   std::ostream_iterator<int, char> ot(cout, " ");*/
    for(int i = 0; i < 81; i++){
        if(!cell[i].fixed)
            validcandidators(i);
        else
            if(trushsudoku(i)){
                cout<<0<<endl;
                return;
            }
    }
      /*  copy(cell[i].candidators.begin(), cell[i].candidators.end(), ot);
        cout<<endl;
    */
    findSudokuSolution(0);
    if(answer == 2)
        cout<<2<<endl;
    if(answer == 0)
        cout<<0<<endl;
    if(answer == 1){
        cout<<1<<endl;
        for(int i = 0; i < 9; i++){
            for(int j = 0; j < 9; j++)
                cout<<ans1[i * 9 + j]<<" ";
             cout<<endl;
        }
    }                
}

void Sudoku::validcandidators(int sp){
    int row = sp / 9;
    int col = sp % 9;
    for(int i = 0; i < 9; i++){
        if(cell[row * 9 + i].fixed)
            cell[sp].candidators.erase(cell[row * 9 + i].num);
            
        if(cell[col + 9 * i].fixed)
            cell[sp].candidators.erase(cell[col + 9 * i].num);
            
    }
    for(int i = 0; i < 3; i++)
        for(int j = 0; j < 3; j++){
            if(cell[(row / 3) * 3 * 9 + (col / 3) * 3 +  i * 9 + j].fixed)
                cell[sp].candidators.erase(cell[(row / 3) * 3 * 9 + (col / 3) * 3 +  i * 9 + j].num);
        }
    
}

bool Sudoku::trushsudoku(int sp){
    int row = sp / 9;
    int col = sp % 9;
    for(int i = 0; i < 9; i++){
        if(cell[row * 9 + i].num == cell[sp].num && (row * 9 + i) != sp)
            return true;

        if(cell[col + 9 * i].num == cell[sp].num && (col + 9 * i) != sp)
            return true;

    }
    for(int i = 0; i < 3; i++)
        for(int j = 0; j < 3; j++){
            if(cell[(row / 3) * 3 * 9 + (col / 3) * 3 +  i * 9 + j].num == cell[sp].num && ((row / 3) * 3 * 9 + (col / 3) * 3 + i  * 9 + j) != sp)
                return true;
        }
    return false;
}


void Sudoku::changeNum(int a, int b){
    /*int as, bs;*/
    sudokuCell temp;
    if(a <= 9 && a >= 1 && b <= 9 && b >= 1){
        /*as = 0;
        bs = 0;*/
        for(int i = 0; i < 9; i++){
            for(int j = 0; j < 9; j++){
                if(cell[i * 9 + j].num == a){
                    cell[ i * 9 + j].num = b;
                    continue;    
                }
                if(cell[i * 9 + j].num == b){
                    cell[ i * 9 + j].num = a;
                    continue;
                }
            }
            /*if(as == 0 && bs == 0)
                continue;
            else{
                temp = cell[as];
                cell[as] = cell[bs];
                cell[bs] = temp;
            }*/
        }
    } 
}

void Sudoku::changeRow(int a, int b){
    if( a >= 0 && a <= 2 && b >= 0 && b <= 2 && a != b){ 
     sudokuCell copy[27];
    for(int i = 0; i < 27; i++)
        copy[i] = cell[ 27 * a + i];
    for(int i = 0; i < 27; i++)
        cell[27 * a + i] = cell[27 * b + i];
    for(int i = 0; i < 27; i++)
        cell[27 * b + i] = copy[i];    
    } 
}

void Sudoku::changeCol(int a, int b){
    if( a >= 0 && a <= 2 && b >= 0 && b <= 2 && a != b){
        sudokuCell copy[27];
        int j = 0, k1 = 3 * a, k2 =3 * b;
        for(int i = 0; i < 27; i++){
            if(j > 8){
                j = 0;
                k1 += 1;
            }
            copy[i] = cell[j * 9 + k1];
            j++;
        }

        j = 0;
        k1 =3 * a;
        k2 =3 * b;

        for(int i = 0; i < 27; i++){
            if(j > 8){
                j = 0;
                k1 += 1;
                k2 += 1;
            }
            cell[j * 9 + k1 ] = cell[j * 9 + k2 ];
            j++;

        }

        j = 0;
        k1 = 3 * a;
        k2 = 3 * b;

        for(int i = 0; i < 27; i++){
            if(j > 8){
                j = 0;
                k2 += 1;
            }
            cell[j * 9 + k2] = copy[i];
            j++;
        }
    }
}

void Sudoku::rotate(int n){
    int a;
    Sudoku::sudokuCell copy[81];
    a = n % 4;
    switch(a){
        case 1 :
            for(int i = 0; i < 81; i++)
                copy[i] = cell[i];

            for(int i = 8; i >= 0; i--) 
                for(int j = 0; j < 9; j++)
                    cell[ i + 9 * j] = copy[9 * (8 - i) + j];
            break;

        case 2 :
            for(int i = 0; i < 81; i++)
                copy[i] = cell[i];

            for(int i = 8; i >= 0; i--)
                for(int j = 8; j >= 0; j--)
                    cell[i * 9 + j] = copy[(8 - j) + 9 * (8 - i)];
            break;

        case 3 :
            for(int i = 0; i < 81; i++)
                copy[i] = cell[i];

            for(int i = 0; i < 9; i++)
                for(int j = 8; j >= 0; j--)
                    cell[j * 9 + i] = copy[ (8 - j) + i * 9];
            break;            
    }
}

void Sudoku::flip(int n){
    sudokuCell copy[81];
    if(n == 0){
        for(int i = 0; i < 81; i++)
            copy[i] = cell[i];
        
        for(int i = 8; i > 4; i--)
            for(int j = 0; j < 9; j++)
                cell[i * 9 + j] = copy[(8 - i) * 9 + j];

        for(int i = 8; i > 4; i--)
            for(int j = 0; j < 9; j++)
                cell[(8 - i) * 9 + j] = copy[i * 9 + j];

    }
    
    if(n == 1){
        for(int i = 0; i < 81; i++)
            copy[i] = cell[i];

        for(int i = 0; i < 4; i++)
            for(int j = 0; j < 9; j++)
                cell[j * 9 + i] = copy[(8 - i) + j * 9];

        for(int i = 0; i < 4; i++)
            for(int j = 0; j < 9; j++)
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
                      0, 9, 0, 0, 0, 0, 4, 0, 0 }; 

    Sudoku test(array);
    *this = test;
    srand(time(NULL));
    changeNum(rand() % 9 + 1, rand() % 9 + 1);
    changeRow(rand() % 3, rand() % 3);
    changeCol(rand() % 3, rand() % 3);
    rotate(rand() % 101);
    flip(rand() % 2);
    printSudokuSolution();

    /*for(int i = 0; i < 9; i++){
        for(int j = 0; j < 9; j++)
            cout<<array[i * 9 + j]<<" ";
        cout<<endl;
    }    */
}
