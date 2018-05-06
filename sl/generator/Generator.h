#pragma once
#include <memory>
#include <vector>

#include <QMainWindow>
#include <QPointer>

#include "GeneratorHandler.h"

class FunctorExecutionForwarder;

namespace Ui {
class GeneratorClass;
}

namespace HomeCompa { namespace sl {

class Enumerator;

class Generator
	: public QMainWindow
	, public GeneratorHandler
{
	Q_OBJECT

public:
	Generator(QWidget *parent = Q_NULLPTR);
	~Generator();

private:
	void changeEvent(QEvent *event) override;
	void Handle(std::vector<std::vector<uint8_t>> &&data) override;

private slots:
	void ChangeLocale();
	void Run();

private:
	void Start();
	void Stop();
	void RetranslateRun();
	std::vector<QAction*> GetLocaleActions() const;
	void LoadSettings();
	void SaveSettings() const;

private:
	std::unique_ptr<Ui::GeneratorClass> m_ui;
	std::unique_ptr<Enumerator> m_enumerator;
	QPointer<FunctorExecutionForwarder> m_forwarder;
	size_t m_current, m_maximum;
};

} }
