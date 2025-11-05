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
        string spaces;
        int curDigits;
        int maxDigits = 1;
        for (int i = 0; i < size * size; i ++) {
            while (maxDigits < *(data+i)) {
                maxDigits *= 10;
            }
        }
        for (int i = 0; i < size * size; i ++) {
            spaces = "";
            curDigits = *(data+i);
            while (maxDigits>curDigits) {
                curDigits *= 10;
                spaces = spaces + " ";
            }
            cout << spaces << *(data+i) << (((i+1)%size==0)?"\n":" ");
        }
    }
    
    Matrix operator+(const Matrix &other) {
        Matrix output(tempMatrix, size);
        for (int i = 0; i < size*size; i ++) {
            *(output.data+i) = *(data + i) + *(other.data + i);
        }
        return output;
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
            cout << "Goodbye!";
        } else if (choice == 2) {
            //Add the input matrices
            Matrix matrixSum = matrix1  + matrix2;
            matrixSum.display();
        } else {
            cout << "Invalid choice.";
        }
        cout << endl << endl;
    }
    return 0;
}
