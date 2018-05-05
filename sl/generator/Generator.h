#pragma once
#include <memory>
#include <vector>

#include <QtWidgets/QMainWindow>

namespace Ui {
class GeneratorClass;
}

class Generator : public QMainWindow
{
	Q_OBJECT

public:
	Generator(QWidget *parent = Q_NULLPTR);
	~Generator();

private:
	void changeEvent(QEvent *event) override;

private:
	void ChangeLocale();
	std::vector<QAction*> GetLocaleActions() const;
	void LoadSettings();
	void SaveSettings() const;

private:
	std::unique_ptr<Ui::GeneratorClass> m_ui;
};
