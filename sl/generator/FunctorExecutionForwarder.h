#pragma once
#include <functional>

#include <QObject>

/**
 * @brief Класс, выполняющий переданные ему функторы в том потоке, к которому принадлежит.
 */
class FunctorExecutionForwarder : public QObject
{
	Q_OBJECT

public:

	/**
	 * @brief Тип фуктора, с котрым работат объект класса.
	 */
	using FunctorType = std::function<void ()>;

	/**
	 * @brief Конструктор по умолчанию.
	 */
	FunctorExecutionForwarder(QObject *parent = Q_NULLPTR);

	/**
	 * @brief Задает функтор для выполнения в потоке, к которому принадлежит объект класса.
	 * @note Объект класса принадлежит или тому потоку, в котором он был создан (выполнялся его конструктор) или в потоку,
	 * в который его переместили вызововм moveToThread().
	 * @param f Функтор, который нужно выполнить.
	 */
	void Forward(FunctorType f) const;

signals:

	void ExecuteFunctor(FunctorType f) const;

private slots:

	/// Исполняет переданный функтор.
	void OnExecuteFunctor(FunctorType f);
};
