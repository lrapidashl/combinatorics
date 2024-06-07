#include "SpanningTree.h"
#include <iostream>

size_t SpanningTree::GetSpanningTreeCount(const Matrix& adjacencyMatrix)
{
	auto kirchhoffMatrix = GetKirchhoffMatrix(adjacencyMatrix);
	auto gaussianMatrix = GetGaussianMatrix(kirchhoffMatrix);
	double count = 1;
	auto size = gaussianMatrix.matrix.size();
	for (size_t i = 0; i < size - 1; i++)
	{
		count *= gaussianMatrix.matrix[i][i];
	}
	return count;
}

SpanningTree::Matrix SpanningTree::GetKirchhoffMatrix(const Matrix& adjacencyMatrix)
{
	auto size = adjacencyMatrix.matrix.size();
	Matrix kirchhoffMatrix(size);
	for (size_t i = 0; i < size; i++)
	{
		size_t degree = 0;
		for (size_t j = 0; j < size; j++)
		{
			degree += adjacencyMatrix.matrix[i][j];
			kirchhoffMatrix.matrix[i][j] = -adjacencyMatrix.matrix[i][j];
		}
		kirchhoffMatrix.matrix[i][i] = degree;
	}
	return kirchhoffMatrix;
}

SpanningTree::Matrix SpanningTree::GetGaussianMatrix(const Matrix& matrix)
{
	auto size = matrix.matrix.size();
	Matrix gaussianMatrix = matrix;
	for (size_t k = 0; k < size; k++)
	{
		for (size_t i = k + 1; i < size; i++)
		{
			auto d = (double)gaussianMatrix.matrix[i][k] / (double)gaussianMatrix.matrix[k][k];
			for (size_t j = k; j < size; j++)
			{
				gaussianMatrix.matrix[i][j] -= d * (double)gaussianMatrix.matrix[k][j];
			}
		}
	}
	return gaussianMatrix;
}
