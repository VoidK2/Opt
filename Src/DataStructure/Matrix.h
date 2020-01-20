#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>
#include <vector>
#include <cstdlib>

class Matrix
{
public:

    // ===============================================
    // Constructors & destructor
    // ===============================================
    Matrix(){
        RowSize=0;
        ColumnSize=0;
        if (static_cast<int>(Data.size()) >0 ){
            Data.clear();
        }
    }
    Matrix(int m, int n){
        RowSize=m;
        ColumnSize=n;
        Data.resize(m*n,0.0);
    }
    Matrix(int m, int n,double r){
        RowSize=m;
        ColumnSize=n;
        Data.resize(m*n,r);
    }
    Matrix(const Matrix& a_m){
        copy(a_m);
    }
    Matrix& operator = (const Matrix& a_m){
        if (this != & a_m){
            dest();
            copy(a_m);
        }
        return *this;
    }
    virtual ~Matrix(){
        dest();
    }

    // ==============================================
    // Member functions
    // ==============================================
    double get_value(int i,int j) const{
        if (i<0 || i>=RowSize || j>= ColumnSize || j<0){
            std::cerr << "The indices is out of range!\n";
            std::exit(1);
        }
        return Data[RowSize*i+j];
    }
    void change_value(int i,int j, double r){
        if (i<0 || i>=RowSize || j>= ColumnSize || j<0){
            std::cerr << "The indices is out of range!\n";
            std::exit(1);
        }
        Data[RowSize*i+j]=r;
    }
    void print() const{
        for (int i=0; i<RowSize; i++){
            for (int j=0; j<ColumnSize; j++){
                std::cout << Data[i*RowSize+j] << " ";
            }
            std::cout << std::endl;
        }
    }
    int get_rowsize() const{
        return RowSize;
    }
    int get_columnsize() const{
        return ColumnSize;
    }

protected:

    // ===============================================
    // Member variables
    // ===============================================
    int RowSize;
    int ColumnSize;
    std::vector<double> Data;

private:

    // =================================================
    // Help functions
    // =================================================
    void copy(const Matrix& a_m){
        RowSize=a_m.RowSize;
        ColumnSize=a_m.ColumnSize;
        Data=a_m.Data;
    }
    void dest(){
    }
};

#endif // MATRIX_H
