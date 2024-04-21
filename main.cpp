#include <iostream>
#include <Eigen/Dense>

void scaleRow(Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic>& matrix, int row, double scalar) {
    matrix.row(row) *= scalar;
}

void addMultipleOfRowToRow(Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic>& matrix, int firstRow, int secondRow, double firstRowMultiplier) {
    matrix.row(secondRow) += firstRowMultiplier * matrix.row(firstRow);
}

int main() {
    Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic> sector3(3,3);
    Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic> sector4(4,4);
    Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic> sector5(5,5);

    sector3 <<  20, -20, -60,
                -15, 40, -20,
                -5, -20, 80;

    sector4 <<  1, 2, 3, 4,
                5, 6, 7, 8,
                9, 10,11,12,
                13,14,15,16;

    sector5 <<  1,  2,  3,   4,  5,
                6,  7,  8,   9, 10,
                11, 12, 13, 14, 15,
                16, 17, 18, 19, 20,
                21, 22, 23, 24, 25;

    //Test here, change the value of target
    Eigen::Matrix target = sector3;

    int matrixCubic = (int)target.rows();

    //Turn each value in the matrix into double
    for(int i = 0 ; i < matrixCubic ; i++){
        for(int ii = 0 ; ii < matrixCubic ; ii++){
            target(i,ii)*=1.0;
        }
    }

    //matrix(1,0) = baris 2 kolom 1

    int leadingColumn = 0;
    int leadingRow = 0;

    while(leadingRow < 2 && leadingColumn < 2){
        if(target(leadingRow,leadingColumn) != 1){
            scaleRow(target,leadingRow,1.0/target(leadingRow,leadingColumn));
        }

        for(int i = 0 ; i < matrixCubic ; i++){
            if(i != leadingRow) {
                addMultipleOfRowToRow(target, leadingRow, i, -1 * target(i, leadingColumn));
            }
        }
        leadingColumn++;
        leadingRow++;
    }

    std::cout<<target<<std::endl;

    return 0;
}