#pragma once
#include <vector>

class SpanningTree
{
public:
	struct Matrix 
	{
		std::vector<std::vector<double>> matrix;
		Matrix(size_t n)
		{
			matrix.resize(n);
			for (std::vector<double>& row : matrix)
			{
				row.resize(n);
			}
		}
	};
	static size_t GetSpanningTreeCount(const Matrix& adjacencyMatrix);
private:
	static Matrix GetKirchhoffMatrix(const Matrix& adjacencyMatrix);
	static Matrix GetGaussianMatrix(const Matrix& matrix);
};

