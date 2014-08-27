#pragma once
#include <vector>

class Spliner
{
public:
	typedef double ValueType;
	typedef std::vector<ValueType> ValueListType;
	typedef std::vector<ValueListType> ValueMatrixType;
	Spliner(const ValueListType &x, size_t dim);

public:
	void Initialize(const ValueListType &y);
	void Compute(const ValueListType &x, ValueListType &y) const;

private:
	static const ValueType NULL_VALUE;

private:
	typedef ValueType (*RegressorType)(ValueType);
	typedef std::vector<RegressorType> RegressorListType;
	static ValueType f1(ValueType x);
	static ValueType f2(ValueType x);
	static ValueType f3(ValueType x);
	static ValueType f4(ValueType x);
	static ValueType cg(const ValueMatrixType &a, const ValueListType &b, ValueListType &x, size_t maxIter, ValueType eps);

private:
	void InitBounds(const ValueListType &x, size_t dim);
	void InitRegressorValues(const ValueListType &x);
	void InitSLAE();

private:
	RegressorListType m_regressors;
	ValueListType m_bounds;
	ValueMatrixType m_regressorValues;
	ValueMatrixType m_slae;
	ValueListType m_coefficients;
};

