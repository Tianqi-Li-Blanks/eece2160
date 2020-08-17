#include<iostream> 
using namespace std;

int row = 3, col = 3;  

int matrix[3][3];
                    
int transpose[3][3];
                    
void printMatrix() {
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) { 
          cout << matrix[i][j] << " \n"[j == col-1];
        }
    }
}

void indexTranspose() {
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            transpose[j][i] = matrix[i][j];
        }
    }
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) { 
            matrix[i][j] = transpose[i][j];
        }
    }
            
}

void pointerTranspose() {
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            *(*(transpose + j) + i) = *(*(matrix + i) + j);
        }
    }
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) { 
            *(*(matrix + i) + j) = *(*(matrix + i) + j);
        }
    }
            
}

int main() 
{ 
    cout << "\nEnter your 3*3 matrix: " << endl;
    for (int i = 0; i < row; ++i) {
        for (int j = 0; j < col; ++j) {
            cout << "Enter matrix element arr" << i + 1 << j + 1 << ": ";
            cin >> matrix[i][j];
       }
    }
    cout << "\nBefore applying transpose your matrix is: " << endl;
    printMatrix();
   
    cout << "\nAfter transposing using arrays your matrix is: " << endl;
    indexTranspose();
    printMatrix();
   
    cout << "\nAfter transposing using pointers your matrix is: " << endl;
    pointerTranspose(); 
    printMatrix();
   
    int input;
    while (true){
        cout << "Main Menu:" << endl;
        cout << "1. indexTranspose" << endl;
        cout << "2. pointerTranspose" << endl;
	cout << "3. Exit" << endl;
	cout << "Select an Option: _ " << endl;
	cin >> input;

	switch (input){
	    case 1:
		cout<<"indexTranspose"<<endl;
		indexTranspose();
                printMatrix();
		break;
	    case 2:
		cout<<"pointerTranspose"<<endl;
		pointerTranspose(); 
                printMatrix();
		break;
	    case 3:
		return(0);
		break;
	    default:
                cout<<"Error: Invalid number"<<endl;
        }
    }
}
