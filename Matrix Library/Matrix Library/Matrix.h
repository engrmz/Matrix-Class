
/*
	By: Zohaib Muhammad 
	University of Engineering & Technology (UET)
	Lahore, Pakistan. 
	Contact: engr.mz@hotmail.com

	Thanks to mR. Davide Faconti (facontidavide) for his guidance.
	--------------------------------------------------------------
	
	The Class helps in finding Matrix inverse, multiplication, transpose, determinant, etc.
	Remaining part will be added soon.
	
	Last Update: March 09th, 2018

*/


#pragma once
#include <vector>

template <typename T>
void display_vector(std::vector <T> vectorToDisplay) // display matrix in 2D form
{
	for (size_t i = 0; i < vectorToDisplay.size(); i++)
		cout << vectorToDisplay[i] << ", ";
}

template <typename T>
class Matrix
{
	mutable size_t rows_; // not constant 
	mutable size_t columns_;
	std::vector<T> matrix_;
public:
//	Matrix();
	Matrix(size_t order); // constructor for squared-matrix
	Matrix(size_t rows, size_t columns); // constructor for rectangular matrix
	Matrix(const Matrix<T>& other); // copy constructor
	Matrix<T>& operator=(const Matrix<T>& other); // copy operator
	

	size_t numRows() const; // get matrix's row size
	size_t numCols() const; // get matrix's column size

	std::vector<T> getRow(size_t row_index) const; // get complete row in a vector
	std::vector<T> getColumn(size_t column_index) const; // get complete column in a vector

	Matrix<T> getTranspose() const;
	Matrix<T> getMinor(size_t row, size_t col) const;
	T calculateDeterminant() const;
	Matrix<T> getInverted() const;

	Matrix operator* (const Matrix& other) const;


	void takeMatrixFromUser(); // reading matrix from user
	size_t findIndex(size_t row, size_t column, size_t columns_) const; // fining 1D index from 2D row/column
	void displayMatrix() const; // display matrix in 2D form

	~Matrix();
};



//  ------------------  Constructors -------------------------//

template <typename T>
Matrix<T>::Matrix(size_t order) : rows_(order), columns_(order) // constructor for squared-matrix
{
	for (size_t i = 0; i < rows_*columns_; i++)
		matrix_.push_back(0);
	//matrix_.reserve(rows_*columns_); //capacity() is "rows*columns" and size() is 0
}

template <typename T>
Matrix<T>::Matrix(size_t rows, size_t columns) : rows_(rows), columns_(columns) // constructor for rectangular matrix
{
	for (size_t i = 0; i < rows_*columns_; i++)
		matrix_.push_back(0); 
	//matrix_.reserve(rows_*columns_);
}

template <typename T>
Matrix<T>::Matrix(const Matrix<T> & other) // copy constructor
{
	cout << "\ninside copy constructor\n";
	rows_ = other.rows_;
	columns_ = other.columns_;
	for (size_t i = 0; i < rows_*columns_; i++)
		matrix_.push_back(0);
	for (size_t i = 0; i < other.matrix_.size(); ++i)
		matrix_[i] = other.matrix_[i];
}

//  ------------------  Operators -------------------------//
template <typename T>
Matrix<T> & Matrix<T>:: operator=(const Matrix<T> & other) // copy operator
{
	this->rows_ = other.rows_;
	this->columns_ = other.columns_;
	this->matrix_.resize(rows_ * columns_);
	for (size_t i = 0; i < other.matrix_.size(); i++)
		this->matrix_[i] = other.matrix_[i];
	return *this;
}

//  ------------------  Getters -------------------------//

template <typename T>
size_t Matrix<T>::numRows() const
{
	return rows_;
}

template <typename T>
size_t Matrix<T>::numCols() const
{
	return columns_;
}

template <typename T>
std::vector<T> Matrix<T>::getRow(size_t row_index) const // get complete row in a vector
{
	std::vector<T> requiredRow;
	size_t first_index = row_index*columns_;
	size_t last_index = first_index + (columns_ - 1);

	for (size_t i = first_index; i <= last_index; i++)
		requiredRow.push_back(matrix_[i]);

	return requiredRow;
}


template <typename T>
std::vector<T> Matrix<T>::getColumn(size_t column_index) const // get complete column in a vector
{
	std::vector<T> requiredColumn;
	size_t first_index = column_index;
	size_t last_index = rows_ * columns_;

	for (size_t i = first_index; i <= last_index; i=i+columns_)
		requiredColumn.push_back(matrix_[i]);

	return requiredColumn;
}

//  ------------------  Matrix functions/Calculations -------------------------//

//*calculate Transpose
template <typename T>
Matrix<T> Matrix<T>::getTranspose() const
{
	Matrix<T> transposeMatrix(columns_, rows_);
	size_t sourceIndex = 0, destinationIndex = 0;
	//transposeMatrix.rows_ = columns_;
	//transposeMatrix.columns_ = rows_;
	for (size_t c = 0; c < columns_; c++)
	{
		for (size_t r = 0; r < rows_; r++)
		{
			sourceIndex = findIndex(r, c, columns_);
			transposeMatrix.matrix_[destinationIndex] = matrix_[sourceIndex];
			destinationIndex++;
		}
	}
	return transposeMatrix;
}


// calculate the minor matrix [cofactor of element (row,col)]
template <typename T>
Matrix<T> Matrix<T>::getMinor(size_t row, size_t col) const
{

	size_t sourceIndex = 0, destinationIndex = 0;
	Matrix<T> minorMatrix(rows_ - 1, columns_ - 1);
	if (rows_ != columns_)
		throw("\n*Not a square matrix*\n");
	else
	{
		for (size_t r = 0; r < rows_; r++)
		{
			if (r != row)
			{
				for (size_t c = 0; c < columns_; c++)
				{
					if (c != col)
					{
						sourceIndex = findIndex(r, c, columns_);
						minorMatrix.matrix_[destinationIndex] = matrix_[sourceIndex];
						destinationIndex++;
					}
				}
			}
		}
	}
	return minorMatrix;
}


// calculate the determinant of a called matrix 
template <typename T>
T Matrix<T>::calculateDeterminant() const
{
	size_t order = 0, index = 0;

	if (rows_ != columns_) // matrix should be a square matrix
		throw("Determinant of a non-square matrix did not exist");
	else
		order = columns_; // order = rows = columnsS

	// order (rows and columns) must be >= 0
	// stop the recursion when matrix has a single element
	if (order == 1)
		return matrix_[0]; // return first element of the matrix

	float calculated_det = 0; // the determinant value
	Matrix<T> minor(order - 1); // allocate the cofactor matrix

	for (int i = 0; i < order; i++)
	{
		minor = this->getMinor(0, i); // get minor of element (0,i)
		index = findIndex(0, i, order); // column = order
		calculated_det += (i % 2 == 1 ? -1.0 : 1.0) * matrix_[index] * minor.calculateDeterminant();  // the recusion is here!
	}
	return calculated_det;
}


// Calculate inverse of a matrix
template <typename T>
Matrix<T> Matrix<T>::getInverted() const
{
	size_t order = 0, index = 0;
	if (rows_ != columns_) // matrix should be a square matrix
		throw("Determinant of a non-square matrix did not exist");
	else
		order = columns_; // order = rows = columnsS

	Matrix<T> invertedMatrix(rows_, columns_); // Y
	Matrix<T> minor(order - 1); // allocate the cofactor matrix

	// get the determinant of a
	double determinant = 1.0 / this->calculateDeterminant();
	cout << "\n\n Determenant is : \n" << this->calculateDeterminant();

	if (!this->calculateDeterminant())
		throw("\nDeterminant is zero so inverse is not possible\n");

	for (int row = 0; row<order; row++) // row
	{
		for (int col = 0; col<order; col++) // col
		{
			// get the co-factor (matrix) of A(j,i)
			minor = this->getMinor(row, col); // get minor of element (0,i)
			index = findIndex(col, row, order); // column = order
			invertedMatrix.matrix_[index] = determinant *  minor.calculateDeterminant();
			if ((col + row) % 2 == 1)
				invertedMatrix.matrix_[index] = -1 * invertedMatrix.matrix_[index];
		}
	}
	return invertedMatrix;
}


//  Matrix Multiplication ::>   R = (*this) * other
template <typename T>
Matrix<T>  Matrix<T>::operator* (const Matrix& other) const
{
	size_t index_this = 0, index_other = 0, index_multi = 0;
	Matrix<T> multi_Matrix(this->rows_, other.columns_);
	for (int i = 0; i < this->rows_; ++i)
	for (int j = 0; j < other.columns_; ++j)
	for (int k = 0; k < this->columns_; ++k)
	{
		index_this = findIndex(i, k, this->columns_);
		index_other = findIndex(k, j, other.columns_);
		index_multi = findIndex(i, j, multi_Matrix.columns_);

		multi_Matrix.matrix_[index_multi] += this->matrix_[index_this] * other.matrix_[index_other];
	}
	return multi_Matrix;
}


//  ------------------  2D to 1D conversion -------------------------//

// convert row,column of 2D matrix to 1D-array index
template <typename T>
size_t Matrix<T>::findIndex(size_t row, size_t column, size_t columns_) const
{
	return (row*columns_ + column);
}


//  ------------------  Input matrix from user -------------------------//
template <typename T>
void Matrix<T>::takeMatrixFromUser()
{
	size_t index = 0;
	cout << "\nPlease input matrix elements \n";
	for (size_t row = 0; row < rows_; row++)
	{	
		for (size_t col = 0; col < columns_; col++)
		{
			index = findIndex(row, col, columns_);
			cout << "\nindex: "<<index<<", Element : [" << row << "][" << col<<"] :  ";
			cin>> matrix_[index];
		}
	}
}


//  ------------------  Display a matrix -------------------------//

template <typename T>
void Matrix<T>::displayMatrix() const
{
	size_t index = 0;
	cout << "\nMatrix of size : \n" << matrix_.size();
	cout << "\nrows : " << rows_;
	cout << "\ncolumns : " << columns_;
	if (matrix_.size() != rows_ * columns_)
	{
		cout << "\nmatrix size : " << matrix_.size() << " row*col = " << rows_ * columns_;
		throw "\n**invalid matrix**";
	}
	else
	{
		cout << "\ncontents of matrix are \n";
		for (size_t row = 0; row < rows_; row++)
		{
			for (size_t col = 0; col < columns_; col++)
			{
				index = findIndex(row, col, columns_);
				cout << matrix_[index] << " ";
			}
			cout << endl;
		}
	}
}


//  ------------------  Destructor -------------------------//

template <typename T>
Matrix<T>::~Matrix()
{
}