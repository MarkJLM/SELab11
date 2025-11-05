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
    
    Matrix(int* array, int matrixSize) {
        data = array;
        size = matrixSize;
    }
    
    void display() {
        int curDigits;
        int maxDigits = 1;
        for (int i = 0; i < size * size; i ++) {
            while (maxDigits < *(data+i)) {
                maxDigits *= 10;
            }
        }
        for (int i = 0; i < size * size; i ++) {
            curDigits = *(data+i);
            while (maxDigits>curDigits) {
                curDigits *= 10;
                cout << " ";
            }
            cout << *(data+i) << (((i+1)%size==0)?"\n":" ");
        }
    }
    
    Matrix operator+(const Matrix &other) {
        cout << "Sum of the input matrices:" << endl;
        Matrix output(tempMatrix, size);
        for (int i = 0; i < size*size; i ++) {
            *(output.data+i) = *(data + i) + *(other.data + i);
        }
        return output;
    }
    
    Matrix operator*(const Matrix &other) {
        cout << "Product of input matrices:" << endl;
        Matrix output(tempMatrix, size);
        for (int i = 0; i < size*size; i ++) {
            *(output.data+i) = 0;
            for (int j = 0; j < size; j ++) {
                *(output.data+i) += (*(data+(i/size)*size+j)) * (*(other.data+i%size+j*size));
            }
        }
        return output;
    }
    
    void trace() {
        int output = 0;
        for (int i = 0; i < size; i ++) {
            output += *(data+i*(size+1));
        }
        cout << "Sum of main diagonal: " << output << endl;
        output = 0;
        for (int i = 0; i < size; i ++) {
             output += *(data+(i+1)*(size-1));
        }
        cout << "Sum of secondary diagonal: " << output << endl;
    }
    void swapRows(int row1, int row2) {
        if (row1 >= 0 && row1 < size && row2 >= 0 && row2 < size) {
            cout << "Row-swapped matrix:" << endl;
            int buffer;
            for (int i = 0; i < size; i ++) {
                buffer = *(data+size*row1+i);
                *(data+size*row1+i) = *(data+size*row2+i);
                *(data+size*row2+i) = buffer;
            }
            display();
        } else {
            cout << "Invalid row numbers.";
        }
    }
};

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
            matrix1.trace();
        } else if (choice == 5) {
            //Ask for rows to swap
            cout << "First row to swap: ";
            cin >> row1;
            cout << "Second row to swap: ";
            cin >> row2;
            matrix1.swapRows(row1, row2);
        } else {
            cout << "Invalid choice." << endl;
        }
        cout << endl;
    }
    return 0;
}
