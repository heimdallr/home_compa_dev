#include <numeric>

#include <boost/assign.hpp>

#include "Spliner.h"

const Spliner::ValueType Spliner::NULL_VALUE = static_cast<Spliner::ValueType>(0);

// Инициализация базовых структур
Spliner::Spliner(const ValueListType &x, size_t dim)
	: m_regressors(boost::assign::list_of(&Spliner::f1)(&Spliner::f2)(&Spliner::f3)(&Spliner::f4).convert_to_container<RegressorListType>())
	, m_bounds(dim)
	, m_regressorValues(2*dim, ValueListType(x.size(), NULL_VALUE))
	, m_slae(2*dim, ValueListType(2*dim, NULL_VALUE))
	, m_coefficients(2*dim, NULL_VALUE)
{
	InitBounds(x, dim);
	InitRegressorValues(x);
	InitSLAE();
}

// Подготовка вектора правой части и решение СЛАУ
void Spliner::Initialize(const ValueListType &y)
{
	// правая часть
	ValueListType b(2*m_bounds.size(), NULL_VALUE);
	for (size_t i = 0, sz = b.size(); i < sz; ++i)
		m_coefficients[i] = b[i] = std::inner_product(m_regressorValues[i].begin(), m_regressorValues[i].end(), y.begin(), NULL_VALUE);

	// решение
	cg(m_slae, b, m_coefficients, 2*m_coefficients.size(), static_cast<ValueType>(1.0e-7));
}

// Вычисление ряда значений сплайна. ВНИМАНИЕ: ряд аргументов (x) должен неубывать
void Spliner::Compute(const ValueListType &x, ValueListType &y) const
{
	for (size_t i = 0, j = 0, sz = x.size(); i < sz; ++i)
	{
		while (x[i] > m_bounds[j + 1])
			++j;

		y[i] = NULL_VALUE;
		for (size_t r = 0, szr = m_regressors.size(); r < szr; ++r)
			y[i] += m_coefficients[2*j + r] * m_regressors[r]((x[i] - m_bounds[j]) / (m_bounds[j+1] - m_bounds[j]));
	}
}

// Набор базисных кубических функций.
// Определены на [0, 1], в реальной работе аргументы нужно нормировать исходя из границ кусков сплайна
Spliner::ValueType Spliner::f1(ValueType x)
{	// f1(0) = 1, f1(1) = 0, f1'(0) = 0, f1'(1) = 0
	return (2*x - 3) * x*x + 1;
}
Spliner::ValueType Spliner::f2(ValueType x)
{	// f2(0) = 0, f2(1) = 0, f2'(0) = 1, f2'(1) = 0
	return (x - 2) * x*x + x;
}
Spliner::ValueType Spliner::f3(ValueType x)
{	// f3(0) = 0, f3(1) = 1, f3'(0) = 0, f3'(1) = 0
	return (3 - 2*x) * x*x;
}
Spliner::ValueType Spliner::f4(ValueType x)
{	// f4(0) = 0, f4(1) = 0, f4'(0) = 0, f4'(1) = 1
	return (x - 1) * x*x;
}

// Решение СЛАУ методом сопряженных градиентов ///@todo оптимизировать умножение матрицы на вектор и скаларное произведение
Spliner::ValueType Spliner::cg(const ValueMatrixType &a, const ValueListType &f, ValueListType &u, size_t maxIter, ValueType eps)
{
	const size_t n = u.size();
	ValueListType r(n), p(n), ap(n);
	for (size_t i = 0; i < n; ++i)
		r[i] = p[i] = f[i] - std::inner_product(a[i].begin(), a[i].end(), u.begin(), NULL_VALUE);

	ValueType norm = std::inner_product(r.begin(), r.end(), r.begin(), NULL_VALUE);
	if (norm < eps)
		return norm;

	for (size_t k = 0; k < maxIter; ++k)
	{
		for (size_t i = 0; i < n; ++i)
			ap[i] = std::inner_product(a[i].begin(), a[i].end(), p.begin(), NULL_VALUE);

		ValueType alpha = norm / std::inner_product(p.begin(), p.end(), ap.begin(), NULL_VALUE);

		for (size_t i = 0; i < n; ++i)
		{
			u[i] += alpha * p[i];
			r[i] -= alpha * ap[i];
		}

		// а вот и квадрат нормы невязки, может пора уже выходить?
		ValueType newNorm = std::inner_product(r.begin(), r.end(), r.begin(), NULL_VALUE);
		if (newNorm < eps)
			return newNorm;

		ValueType beta = newNorm / norm;
		norm = newNorm;

		for (size_t i = 0; i < n; ++i)
			p[i] = r[i] + beta * p[i];
	}

	return norm;
}

// Расчет границ
void Spliner::InitBounds(const ValueListType &x, size_t dim)
{
	size_t i = 0;
	std::generate(m_bounds.begin(), m_bounds.end(), [&x, &i, dim]() {
		return x.front() + (x.back() - x.front()) / (dim - 1) * i++;
	});
	m_bounds.back() = x.back();
}

// Расчет матрицы регрессоров
void Spliner::InitRegressorValues(const ValueListType &x)
{
	for (size_t i = 0, j = 0, sz = x.size(); i < sz; ++i)
	{
		while (x[i] > m_bounds[j + 1])
			++j;

		for (size_t r = 0, szr = m_regressors.size(); r < szr; ++r)
			m_regressorValues[2*j + r][i] = m_regressors[r]((x[i] - m_bounds[j]) / (m_bounds[j+1] - m_bounds[j]));
	}
}

// Расчет матрицы СЛАУ
void Spliner::InitSLAE()
{
	for (size_t i = 0, sz = m_slae.size(); i < sz; ++i)
	{
		m_slae[i][i] = std::inner_product(m_regressorValues[i].begin(), m_regressorValues[i].end(), m_regressorValues[i].begin(), NULL_VALUE);
		for (size_t j = 0; j < i; ++j)
			m_slae[i][j] = m_slae[j][i] = std::inner_product(m_regressorValues[i].begin(), m_regressorValues[i].end(), m_regressorValues[j].begin(), NULL_VALUE);
	}
}