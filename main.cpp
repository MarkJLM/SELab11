//Object-Oriented Matrix Manipulation Program
//Some code copied from Lab 9. No external sources used.
//Created 11/04/25 Mark Lammers-Meis

#include <iostream>
#include <string>
#include <fstream>
using namespace std;

int* tempMatrix;

class Matrix {
public:
    int* data;
    int size;
    
    //Matrix constructor
    Matrix(int* array, int matrixSize) {
        data = array;
        size = matrixSize;
    }
    
    void display() {
        int curDigits;
        int maxDigits = 1;
        //Count spacing
        for (int i = 0; i < size * size; i ++) {
            while (maxDigits < *(data+i)) {
                maxDigits *= 10;
            }
        }
        for (int i = 0; i < size * size; i ++) {
            //Add spacing
            curDigits = *(data+i);
            while (maxDigits>curDigits) {
                curDigits *= 10;
                cout << " ";
            }
            //Print matrix
            cout << *(data+i) << (((i+1)%size==0)?"\n":" ");
        }
    }
    
    Matrix operator+(const Matrix &other) {
        cout << "Sum of the input matrices:" << endl;
        //Create a new matrix to hold the sum
        Matrix output(tempMatrix, size);
        for (int i = 0; i < size*size; i ++) {
            //Set each output entry to the sum of the corresponding entries in the inputs
            *(output.data+i) = *(data + i) + *(other.data + i);
        }
        return output;
    }
    
    Matrix operator*(const Matrix &other) {
        cout << "Product of input matrices:" << endl;
        //Create a new matrix to hold the product
        Matrix output(tempMatrix, size);
        for (int i = 0; i < size*size; i ++) {
            *(output.data+i) = 0;
            //Set each output entry to the sum of the products of entries A_{ij} and B_{ji}
            for (int j = 0; j < size; j ++) {
                *(output.data+i) += (*(data+(i/size)*size+j)) * (*(other.data+i%size+j*size));
            }
        }
        return output;
    }
};

void trace(Matrix matrix) {
    int output = 0;
    //Add main diagonal entries
    for (int i = 0; i < matrix.size; i ++) {
        output += *(matrix.data+i*(matrix.size+1));
    }
    cout << "Sum of main diagonal: " << output << endl;
    output = 0;
    //Add secondary diagonal entries
    for (int i = 0; i < matrix.size; i ++) {
         output += *(matrix.data+(i+1)*(matrix.size-1));
    }
    cout << "Sum of secondary diagonal: " << output << endl;
}

void swapRows(Matrix matrix, int row1, int row2) {
    //Validate index input
    if (row1 >= 0 && row1 < matrix.size && row2 >= 0 && row2 < matrix.size) {
        Matrix output(tempMatrix, matrix.size);
        cout << "Row-swapped matrix:" << endl;
        //Copy the matrix to the output
        for (int i = 0; i < matrix.size*matrix.size; i ++) {
            *(output.data+i) = *(matrix.data+i);
        }
        //Create a buffer for the first row
        int buffer;
        for (int i = 0; i < matrix.size; i ++) {
            buffer = *(output.data+matrix.size*row1+i);
            //Set the first row to the second row
            *(output.data+matrix.size*row1+i) = *(output.data+matrix.size*row2+i);
            //Restore the first row from the buffer to the second row
            *(output.data+matrix.size*row2+i) = buffer;
        }
        output.display();
    } else {
        //Display an error
        cout << "Invalid row numbers." << endl;
    }
}

void swapClms(Matrix matrix, int clm1, int clm2) {
    //Validate index input
    if (clm1 >= 0 && clm1 < matrix.size && clm2 >= 0 && clm2 < matrix.size) {
        Matrix output(tempMatrix, matrix.size);
        cout << "Column-swapped matrix:" << endl;
        //Copy the matrix to the output
        for (int i = 0; i < matrix.size*matrix.size; i ++) {
            *(output.data+i) = *(matrix.data+i);
        }
        //Create a buffer for the first column
        int buffer;
        for (int i = 0; i < matrix.size; i ++) {
            buffer = *(output.data+matrix.size*i+clm1);
            //Set the first column to the second column
            *(output.data+matrix.size*i+clm1) = *(output.data+matrix.size*i+clm2);
            //Restore the first column from the buffer to the second column
            *(output.data+matrix.size*i+clm2) = buffer;
        }
        output.display();
    } else {
        //Display an error
        cout << "Invalid column numbers." << endl;
    }
}

void writeMatrix(Matrix matrix, int row = 0, int clm = 0, int entry = 100) {
    //Validate index input
    if (row >= 0 && row < matrix.size && clm >= 0 && clm < matrix.size) {
        Matrix output(tempMatrix, matrix.size);
        cout << "Updated matrix:" << endl;
        //Copy the matrix to the output
        for (int i = 0; i < matrix.size*matrix.size; i ++) {
            *(output.data+i) = *(matrix.data+i);
        }
        //Set specified entry to the new value
        *(output.data+matrix.size*row+clm) = entry;
        output.display();
    } else {
        //Display an error
        cout << "Invalid index numbers." << endl;
    }
}

int main() {
    //Open a file
    string fileName;
    cout << "Input file name: ";
    cin >> fileName;
    ifstream matrixFile(fileName);
    //Get matrix size
    string fileLine;
    getline(matrixFile, fileLine);
    int matrixSize = 0;
    for (int i = 0; fileLine[i] > 47 && fileLine[i] < 58; i ++) {
        //Turn a character of the size into an integer's digit
        matrixSize = matrixSize*10 + fileLine[i] - 48;
    }
    //Start saving matrix data
    int fileData[matrixSize*matrixSize*2];
    int tempData[matrixSize*matrixSize];
    tempMatrix = tempData;
    //Read matrix values
    for (int i = 0; i < matrixSize*2; i ++) {
        getline(matrixFile, fileLine);
        //Check every character in the input string
        for (int j = 0; j < matrixSize; j ++) {
            //Add the digits in the string to the data row
            fileData[i*matrixSize+j] = (fileLine[j*3] - 48)*10 + fileLine[j*3+1] - 48;
        }
    }
    Matrix matrix1(fileData, matrixSize);
    Matrix matrix2(fileData + matrixSize*matrixSize, matrixSize);
    matrixFile.close();
    //Display input matrices
    cout << endl;
    matrix1.display();
    cout << endl;
    matrix2.display();
    cout << endl;
    //Start asking for more actions
    int choice = 8;
    int row1 = 0;
    int row2 = 0;
    int newEntry = 0;
    while (choice > 1) {
        cout << "1. Quit\n2. Add\n3. Multiply\n4. Get Diagonals\n5. Swap Rows\n6. Swap Columns\n7. Change Entry\n";
        cout << "Please enter a choice: ";
        cin >> choice;
        //Get choice action
        cout << endl;
        if (choice == 1) {
            //Exit
            cout << "Goodbye!" << endl;
        } else if (choice == 2) {
            //Add the input matrices
            Matrix matrixSum = matrix1 + matrix2;
            matrixSum.display();
        } else if (choice == 3) {
            //Multiply the input matrices
            Matrix matrixProduct = matrix1 * matrix2;
            matrixProduct.display();
        } else if (choice == 4) {
            //Print the sums of the diagonals
           trace(matrix1);
        } else if (choice == 5) {
            //Ask for rows to swap
            cout << "First row to swap: ";
            cin >> row1;
            cout << "Second row to swap: ";
            cin >> row2;
            swapRows(matrix1, row1, row2);
        } else if (choice == 6) {
            //Ask for columns to swap
            cout << "First column to swap: ";
            cin >> row1;
            cout << "Second column to swap: ";
            cin >> row2;
            swapClms(matrix1, row1, row2);
        } else if (choice == 7) {
            //Ask for index to change
            cout << "Row index to change: ";
            cin >> row1;
            cout << "Column index to change: ";
            cin >> row2;
            cout << "New entry to insert: ";
            cin >> newEntry;
            writeMatrix(matrix1, row1, row2, newEntry);
        } else {
            cout << "Invalid choice." << endl;
        }
        cout << endl;
    }
    return 0;
}
