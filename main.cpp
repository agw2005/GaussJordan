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
    Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic> sectorRandom(4,6); //row x col

    sectorRandom<< 2 , 2 , -1 , 0 , 1 , 0,
                    -1, -1, 2, -3, 1, 0,
                    1, 1, -2, 0 , -1, 0,
                    0, 0, 1 ,1 ,1 , 0;

    sector3 <<  20, -20, -60,
                -15, 40, -20,
                -5, -20, 80;

    sector4 <<  85, -15, -25,-25,
                -25, 85, -35,-45,
                -20, -15,85,-15,
                -40,-55,15,85;

    sector5 <<  1,  2,  3,   4,  5,
                6,  7,  8,   9, 10,
                11, 12, 13, 14, 15,
                16, 17, 18, 19, 20,
                21, 22, 23, 24, 25;

    //Test here, change the value of target
    Eigen::Matrix target = sectorRandom;

    std::cout<<target<<std::endl;

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

    for(int j = 1; j < matrixCubic; j++){
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
