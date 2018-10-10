/////////////
// Task 1: Problem 0
// This cpp file build for assignment 1 in programming 2 course ///
// Student IDs: 20100018, 20110350, 20150397
/////////////
// this lib uses to call the basic functionality of input and output
#include <iostream>
// this lib uses to call the function setw to add spaces before numbers
#include <iomanip>

using namespace std;

// A structure to store a matrix
struct matrix
{
  int** data;       // Pointer to 2-D array that will simulate matrix
  int row, col;
  bool valid;
};

// Already implemented
void createMatrix (int row, int col, int num[], matrix& mat);

// Student #1 with the smallest ID (e.g., 20170080)
// All these operations return a new matrix with the calculation result
matrix operator+ (matrix mat1, matrix mat2); // Add if same dimensions
matrix operator- (matrix mat1, matrix mat2); // Sub if same dimensions
matrix operator* (matrix mat1, matrix mat2); // Multi if col1 == row2
matrix operator+ (matrix mat1, int scalar); // Add a scalar
matrix operator- (matrix mat1, int scalar); // Subtract a scalar
matrix operator* (matrix mat1, int scalar); // Multiple by scalar

// Student #2 with the middle ID (e.g., 20170082)
// The last operator >> takes an istream and a matrix and return the
// the same istream so it is possible to cascade input like
// cin >> matrix1 >> matrix2 << endl;
matrix operator+= (matrix& mat1, matrix mat2); // mat1 changes & return new matrix with the sum
matrix operator-= (matrix& mat1, matrix mat2); // mat1 changes + return new matrix with difference
matrix operator+= (matrix& mat, int scalar);   // change mat & return new matrix
matrix operator-= (matrix& mat, int scalar);   // change mat & return new matrix
void   operator++ (matrix& mat);   	// Add 1 to each element ++mat
void   operator-- (matrix& mat);    	// Sub 1 from each element --mat
istream& operator>> (istream& in, matrix& mat);
       	// Input matrix like this (dim 2 x 3) cin >> 2 3 4 6 8 9 12 123
       // and return istream to allow cascading input

//Student #3 with the biggest ID (e.g., 20170089)
// The first operator << takes an ostream and a matrix and return the
// the same ostream so it is possible to cascade output like
// cout << matrix1 << matrix2 << endl;
ostream& operator<< (ostream& out, matrix mat);
 // Print matrix as follows (2 x 3) 4 6 8
 // and return ostream to cascade printing 9 12 123
bool operator== (matrix mat1, matrix mat2); // True if identical
bool operator!= (matrix mat1, matrix mat2); // True if not same
bool isSquare (matrix mat); // True if square matrix
bool isSymetric (matrix mat); // True if square and symmetric
bool isIdentity (matrix mat); // True if square and identity
matrix transpose(matrix mat); // Return new matrix with the transpose 

//__________________________________________

//////student 1
matrix operator+ (matrix mat1, matrix mat2)
{
    int data1 [] = { };
    matrix newMatrix;
    newMatrix.valid = true;
    
    if(mat1.row != mat2.row)
    {
        newMatrix.valid = false;
        cout << "different rows between the two matrices." << endl;
        return newMatrix;
    }
    if(mat1.col != mat2.col)
    {
        newMatrix.valid = false;
        cout << "different rows between the two matrices." << endl;
        return newMatrix;
    }
    
    createMatrix(mat1.row, mat1.col, data1, newMatrix);
    
    for(int i = 0; i < mat1.row; i ++)
        for(int j = 0; j < mat1.col; j ++)
        {
            newMatrix.data[i][j] = mat1.data[i][j] + mat2.data[i][j];
        }
        
    return newMatrix;
}
matrix operator- (matrix mat1, matrix mat2)
{
    int data1 [] = { };
    matrix newMatrix;
    newMatrix.valid = true;
    
    if(mat1.row != mat2.row)
    {
        newMatrix.valid = false;
        cout << "different rows between the two matrices." << endl;
        return newMatrix;
    }
    if(mat1.col != mat2.col)
    {
        newMatrix.valid = false;
        cout << "different rows between the two matrices." << endl;
        return newMatrix;
    }
    
    createMatrix(mat1.row, mat1.col, data1, newMatrix);
    
    for(int i = 0; i < mat1.row; i ++)
        for(int j = 0; j < mat1.col; j ++)
        {
            newMatrix.data[i][j] = mat1.data[i][j] - mat2.data[i][j];
        }
        
    return newMatrix;
}

matrix operator* (matrix mat1, matrix mat2)
{
    int data1 [] = { };
    matrix newMatrix;
    newMatrix.valid = true;
    
    if(mat1.col != mat2.row)
    {
        newMatrix.valid = false;
        cout << "different col1 and row2 between the two matrices." << endl;
        return newMatrix;
    }
    
    createMatrix(mat1.row, mat2.col, data1, newMatrix);
    
    for(int i = 0; i < newMatrix.row; i++)
    {
        for(int j = 0; j < newMatrix.col; j ++)
        {
            newMatrix.data[i][j] = 0;
        }
    }
    
    for(int i = 0; i < mat1.row; i ++)
        for(int j = 0; j < mat2.col; j ++)
        {
            for(int k = 0; k < mat1.col; k ++)
            {
                newMatrix.data[i][j] += mat1.data[i][k] * mat2.data[k][j];
            }
        }
    
    newMatrix.valid = true;
    return newMatrix;
}

matrix operator+ (matrix mat1, int scalar)
{
    for(int i = 0; i < mat1.row; i ++)
        for(int j = 0; j < mat1.col; j ++)     
            mat1.data[i][j] = mat1.data[i][j] + scalar;
    return mat1;
}
matrix operator- (matrix mat1, int scalar)
{
    for(int i = 0; i < mat1.row; i ++)
        for(int j = 0; j < mat1.col; j ++)     
            mat1.data[i][j] = mat1.data[i][j] - scalar;
    return mat1;   
}
matrix operator* (matrix mat1, int scalar)
{
    for(int i = 0; i < mat1.row; i ++)
        for(int j = 0; j < mat1.col; j ++)     
            mat1.data[i][j] = mat1.data[i][j] * scalar;
    return mat1;     
}

/////student 2
// overload cin >> input operator
istream &operator>>(istream &input, matrix &in)
{
    cout << "Enter row: ";
    cin >> in.row;
    cout << "Enter col: ";
    cin >> in.col;
    
    int data [] = {};
    createMatrix(in.row, in.col, data, in);
    
    for(int i=0;i < in.row;i++)
    {
        for(int g=0; g < in.col;g++)
        {
            cout << "Enter index - row " <<  (i+1) << ":  and col " << (g+1) << ": ";
            input >> in.data[i][g];
        }
    }
    return input;
}

// overload += operator
matrix operator+= (matrix& mat1, matrix mat2) 
{  
    int row1 = 0, col1 = 0, val1 = 0, val2 = 0;
    row1 = max(mat1.row, mat2.row); 
    col1 = max(mat1.col, mat2.col);    
    for(int i = 0; i < row1; i ++)
        for(int j = 0; j < col1; j ++)
        {
            if(i < (mat1.row) && j < (mat1.col) )
                val1 = mat1.data[i][j];
            else
                val1 = 0;
            
            if(i < (mat2.row) && j < (mat2.col) )
                val2 = mat2.data[i][j];
            else
                val2 = 0;
            
            if(i < (mat1.row) && j < (mat1.col) )
               mat1.data[i][j] = val1 + val2;
        }
    return mat1;
}

// overload -= operator
matrix operator-= (matrix& mat1, matrix mat2) 
{  
    int row1 = 0, col1 = 0, val1 = 0, val2 = 0;
    row1 = max(mat1.row, mat2.row); 
    col1 = max(mat1.col, mat2.col);    
    for(int i = 0; i < row1; i ++)
        for(int j = 0; j < col1; j ++)
        {
            if(i < (mat1.row) && j < (mat1.col) )
                val1 = mat1.data[i][j];
            else
                val1 = 0;
            
            if(i < (mat2.row) && j < (mat2.col) )
                val2 = mat2.data[i][j];
            else
                val2 = 0;
            
            if(i < (mat1.row) && j < (mat1.col) )
               mat1.data[i][j] = val1 - val2;
        }
    return mat1;
}

// overload += operator
matrix operator+= (matrix& mat, int scalar) 
{    
    for(int i = 0; i < mat.row; i ++)
        for(int j = 0; j < mat.col; j ++)     
            mat.data[i][j] = mat.data[i][j] + scalar;
    return mat;
}
// overload -+ operator
matrix operator-= (matrix& mat, int scalar) 
{    
    for(int i = 0; i < mat.row; i ++)
        for(int j = 0; j < mat.col; j ++)     
            mat.data[i][j] = mat.data[i][j] - scalar;
    return mat;
}
// overload ++ operator
void operator++ (matrix& mat)
{
    for(int i = 0; i < mat.row; i ++)
        for(int j = 0; j < mat.col; j ++)     
            mat.data[i][j]++;
}
// overload -- operator
void operator-- (matrix& mat)
{
    for(int i = 0; i < mat.row; i ++)
        for(int j = 0; j < mat.col; j ++)     
            mat.data[i][j]--;
}

/////////student3
// print by overloading << operator
ostream& operator<< (ostream& out, matrix mat)
{
    for(int i=0;i<mat.row;i++)
    {
        for(int j=0; j < mat.col; j++)
        {
            out << (j == 0 ? setw(0) : setw(6)) << mat.data[i][j] ;
        }
        out<<endl;
    }
    return out;
}

// True if identical
bool operator== (matrix mat1, matrix mat2) 
{
    if(mat1.row != mat2.row)
    {
        cout << "different rows between the two matrices." << endl;
        return false;
    }
    
    if(mat1.col != mat2.col)
    {
        cout << "different rows between the two matrices." << endl;
        return false;
    }  
    
    for (int i = 0; i < mat1.row; i++) 
        for (int j = 0; j < mat1.col; j++) 
            if (mat1.data[i][j] != mat2.data[i][j]) 
                return false;
    
    return true; 
}

// True if not same
bool operator!= (matrix mat1, matrix mat2) 
{
    if(mat1.row != mat2.row)
    {
        cout << "different rows between the two matrices." << endl;
        return true;
    }
    
    if(mat1.col != mat2.col)
    {
        cout << "different rows between the two matrices." << endl;
        return true;
    }  
    
    for (int i = 0; i < mat1.row; i++) 
        for (int j = 0; j < mat1.col; j++) 
            if (mat1.data[i][j] == mat2.data[i][j]) 
                return false;
    
    return true; 
}

// True if square matrix
bool isSquare (matrix mat) 
{
    return (mat.row == mat.col);
}

// True if square and symmetric
bool isSymetric (matrix mat) 
{
    bool blnSymetric = true;
    for (int i = 0; i < mat.row; i++)
    {
        for( int j = 0; j < mat.col; j++)
        {
            if (mat.data[i][j] != mat.data[j][i])
                blnSymetric = false;
        }
    }
    return blnSymetric;
}

// True if square and identity
bool isIdentity (matrix mat) 
{
    bool blnIdentity = true;
    for (int i = 0; i < mat.row; i++)
        for (int j = 0; j < mat.col; j++)
        {
            if ((mat.data[i][j] != 1) && (mat.data[j][i] != 0))
            {
                blnIdentity = false;
                break;
            }
        }
    return blnIdentity;
}

// Return new matrix with the transpose 
matrix transpose(matrix mat) 
{
    matrix result;
    result.row = mat.row;
    result.col = mat.col;
    
    int data1 [] = { };
    createMatrix(mat.row, mat.col, data1, result);
    
    for(int i=0; i < mat.row;i++)
    {
        for(int g=0;g < mat.col;g++)
            result.data[g][i] = mat.data[i][g];
    }
    return result;
}

//__________________________________________
// Takes an array of data and stores in matrix according
// to rows and columns
void createMatrix (int row, int col, int num[], matrix& mat) {
  mat.row = row;
  mat.col = col;
  mat.data = new int* [row];

  for (int i = 0; i < row; i++)
    mat.data[i] = new int [col];

  for (int i = 0; i < row; i++)
    for (int j = 0; j < col; j++)
      mat.data[i][j] = num[i * col + j];
}
//__________________________________________

void PrintMatrix(matrix mat1)
{
    for(int i = 0; i < mat1.row; i ++)
    {
        for(int j = 0; j < mat1.col; j ++)
        {
            cout << mat1.data[i][j]  << (j != (mat1.col-1) ? " - " : ""); // mat1.data[i * mat1.col + j]
        }
        cout << endl;
    }
}

//function to stop execution until user press a button
void stopExecution()
{
    cout << "To continue press any button ... ";
    cin.get();
}

int main(int argc, char **argv)
{
    int data1 [] = {1,2,3,4,5,6,7,8};
    int data2 [] = {13,233,3,4,5,6};
    int data3 [] = {10,100,10,100,10,100,10,100};
    int data4 [] = {1,2,3,4,5,6,7,8};
    
    matrix mat1, mat2, mat3, mat4, mat5;
    createMatrix (4, 2, data1, mat1);
    createMatrix (2, 3, data2, mat2);
    createMatrix (4, 2, data3, mat3);
    createMatrix (4, 2, data4, mat4);
    
    cout << "mat1: " << endl;
    cout << mat1;
    cout << "mat2: " << endl;
    cout << mat2;
    cout << "mat3: " << endl;
    cout << mat3;
    cout << "mat4: " << endl;
    cout << mat4;
    cout << endl;
    
    ////////
    //check task student 1: /// 
    ////////
    cout << "Addition Two Matrices: mat1 + mat3" << endl;
    matrix newAdditionMatrix = mat1 + mat3;
    if(newAdditionMatrix.valid == true)
        cout << newAdditionMatrix;
    
    //stop process until user click any key
    stopExecution();
    
    cout << "Subtract Two Matrices: mat1 - mat3" << endl;
    matrix newSubtractMatrix = mat1 - mat3;
    if(newSubtractMatrix.valid == true)
        cout << newSubtractMatrix;
    
    cout << "Multiply Two Matrices: mat1 * mat2" << endl;
    matrix newMultiplyMatrix = mat1 * mat2;
    
    if(newMultiplyMatrix.valid == true)
        cout << newMultiplyMatrix;
    //stop process until user click any key
    stopExecution();
    
    cout << "Calc mat4 = mat4 + 5" << endl;
    mat4 = mat4 + 5;
    cout << mat4;
    cout << "mat4 = mat4 - 5" << endl;
    mat4 = mat4 - 5;
    cout << mat4;
    cout << "Calc mat4 = mat4 * 5" << endl;
    mat4 = mat4 * 5;
    cout << mat4;
    
    //stop process until user click any key
    stopExecution();
    
    ////////
    //check task student 2: /// 
    ////////
    cout << "Calc mat1+= mat3 += mat3 " << endl;
    mat1 += mat3 += mat3;    
    cout << mat1;
    
    cout << "Calc mat1 -= mat3 " << endl;
    mat1 -= mat3;
    cout << mat1;
    
    cout << "Calc mat1 +=3 " << endl;
    mat1 +=3;
    cout << mat1;
    
    //stop process until user click any key
    stopExecution();
    
    cout << "Calc mat1 +=3 " << endl;
    mat1-=3;
    cout << mat1;
    
    cout << "++mat1" << endl;
    ++mat1;
    cout << mat1;
    
    //stop process until user click any key
    stopExecution();
    
    cout << "--mat1" << endl;
    --mat1;
    cout << mat1;
    
    cout << "Test input cin >> operator on a matrix: " << endl;
    cin >> mat5;
    ////////
    //check task student 3: /// 
    ////////
    cout << "Test output cout << operator on a matrix: " << endl;
    cout << mat5;
    /////////////
    
    cout << "Test == operator between two matries: " << endl;
    if(mat1 == mat3)
        cout << "mat1 is equal mat3" << endl;
    else
        cout << "mat1 is not equal mat3" << endl;
    
    //stop process until user click any key
    stopExecution();
    
    cout << "Test != operator between two matries: " << endl;
    if(mat1 != mat3)
        cout << "mat1 is not equal mat3" << endl;
    else
        cout << "mat1 is equal mat3" << endl;
    
    cout << "Test isSquare on mat1: " << endl;
    if(isSquare(mat1))
        cout << "mat1 is square" << endl;
    else
        cout << "mat1 is not square" << endl;
    
    //stop process until user click any key
    stopExecution();
    
    cout << "Test isSymetric on mat1: " << endl;
    if(isSymetric(mat1))
        cout << "mat1 is symetric" << endl;
    else
        cout << "mat1 is not symetric" << endl;
    
    cout << "Test isIdentity on mat1: " << endl;
    if(isIdentity(mat1))
        cout << "mat1 is identity" << endl;
    else
        cout << "mat1 is not identity" << endl;
    
    //stop process until user click any key
    stopExecution();
    
    cout << "Test transpose on mat1: " << endl;
    cout << "mat1 before transpose: " << endl;
    cout << mat1;
    transpose(mat1);
    cout << "mat1 after transpose: " << endl;
    cout << mat1;
    ////////////
    
	return 0;
}

