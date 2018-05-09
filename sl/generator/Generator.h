#pragma once
#include <memory>
#include <vector>

#include <QMainWindow>
#include <QPointer>

#include "GeneratorHandler.h"

class FunctorExecutionForwarder;
class QTimer;
class QWinTaskbarProgress;

namespace Ui {
class GeneratorClass;
}

namespace HomeCompa { namespace sl {

class Enumerator;
class Filter;
class ResultSaver;

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
	void Handle(std::vector<std::vector<uint8_t>> &data) override;
	void Ready() override;
	void Saved(size_t) override;
	void SaveReady() override;

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
	QString GetStatusMessage() const;

private:
	std::unique_ptr<Ui::GeneratorClass> m_ui;
	std::unique_ptr<Enumerator> m_enumerator;
	std::unique_ptr<Filter> m_filter;
	std::unique_ptr<ResultSaver> m_resultSaver;
	QPointer<FunctorExecutionForwarder> m_forwarder;
	QPointer<QWinTaskbarProgress> m_taskbarProgress;
	QPointer<QTimer> m_progressMessaageTimer;
	size_t m_current{ 0 }, m_maximum{ 0 }, m_passed{ 0 }, m_saved{ 0 };
};

} }
