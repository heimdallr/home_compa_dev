#include <cassert>

#include <QFileDialog>
#include <QFileInfo>
#include <QLineEdit>
#include <QMessageBox>
#include <QProgressBar>
#include <QSettings>
#include <QTranslator>
#include <QVariant>

#include "Enumerator.h"
#include "FunctorExecutionForwarder.h"

#include "ui_Generator.h"
#include "Generator.h"

namespace HomeCompa { namespace sl {

namespace {

QTranslator g_translator;
const char *LOCALE = "locale";

QString GetIniFileName()
{
	QFileInfo info(QCoreApplication::applicationFilePath());
	return info.path() + "/" + info.completeBaseName() + ".ini";
}

}

Generator::Generator(QWidget *parent)
	: QMainWindow(parent)
	, m_ui(std::make_unique<Ui::GeneratorClass>())
	, m_forwarder(new FunctorExecutionForwarder(this))
{
	m_ui->setupUi(this);
	m_ui->progressBar->setVisible(false);
	m_ui->horizontalLayoutRun->setAlignment(Qt::AlignRight);

	connect(m_ui->actionAbout, &QAction::triggered, [parent = this](bool) {QMessageBox::about(parent, tr("About generator"), tr("generator generates generated")); });

	const auto openFileDialog = [parent = this](QLineEdit *edit, bool existingOnly = true)
	{
		QFileDialog dialog(parent, tr("Open file"));
		dialog.setFileMode(existingOnly? QFileDialog::FileMode::ExistingFile: QFileDialog::FileMode::AnyFile);
		dialog.setViewMode(QFileDialog::Detail);
		if (dialog.exec() && !dialog.selectedFiles().empty())
			edit->setText(dialog.selectedFiles().front());
	};

	connect(m_ui->toolButtonA				, &QAbstractButton::clicked, [openFileDialog, edit = m_ui->lineEditA				]() {openFileDialog(edit); });
	connect(m_ui->toolButtonB				, &QAbstractButton::clicked, [openFileDialog, edit = m_ui->lineEditB				]() {openFileDialog(edit); });
	connect(m_ui->toolButtonC				, &QAbstractButton::clicked, [openFileDialog, edit = m_ui->lineEditC				]() {openFileDialog(edit); });
	connect(m_ui->toolButtonPositionsValues	, &QAbstractButton::clicked, [openFileDialog, edit = m_ui->lineEditPositionsValues	]() {openFileDialog(edit); });
	connect(m_ui->toolButtonResult			, &QAbstractButton::clicked, [openFileDialog, edit = m_ui->lineEditResult			]() {openFileDialog(edit, false); });
	connect(m_ui->checkBoxFilterSumC, &QCheckBox::stateChanged, [this](int state)
	{
		m_ui->spinBoxSumCMin->setEnabled(state == Qt::Checked);
		m_ui->spinBoxSumCMax->setEnabled(state == Qt::Checked);
	});
	connect(m_ui->checkBoxFilterPositionsValues, &QCheckBox::stateChanged, [this](int state)
	{
		m_ui->lineEditPositionsValues->setEnabled(state == Qt::Checked);
		m_ui->toolButtonPositionsValues->setEnabled(state == Qt::Checked);
	});
	connect(m_ui->checkBoxFilterEvenPositions, &QCheckBox::stateChanged, [this](int state)
	{
		m_ui->lineEditEvenPositions->setEnabled(state == Qt::Checked);
	});

	LoadSettings();
}

Generator::~Generator()
{
	SaveSettings();
}

void Generator::changeEvent(QEvent *event)
{
	if (event->type() == QEvent::LanguageChange)
	{
		m_ui->retranslateUi(this);
		RetranslateRun();
	}

	QWidget::changeEvent(event);
}

void Generator::Handle(std::vector<std::vector<uint8_t>> &&data)
{
	m_forwarder->Forward([this, data = std::move(data)]
	{
		m_current += data.size();
		m_ui->progressBar->setValue(m_current * 100 / m_maximum);
		if (m_current == m_maximum)
			m_ui->pushButtonRun->click();
	});
}

void Generator::ChangeLocale()
{
	for (auto *action : GetLocaleActions())
		action->setChecked(action == sender());

	if (g_translator.load(QString(":/") + LOCALE + "/" + sender()->property(LOCALE).toString()))
		qApp->installTranslator(&g_translator);
}

std::vector<QAction*> Generator::GetLocaleActions() const
{
	return {
		m_ui->actionEnglish,
		m_ui->actionRussian,
	};
}

void Generator::Run()
{
	m_ui->frame->setEnabled(!m_ui->frame->isEnabled());
	m_ui->progressBar->setVisible(!m_ui->frame->isEnabled());

	RetranslateRun();
	m_ui->frame->isEnabled() ? Stop() : Start();
}

void Generator::Start()
{
	assert(!m_enumerator);
	std::make_unique<Enumerator>(*this, 7, 49).swap(m_enumerator);

	m_current = 0;
	m_maximum = m_enumerator->GetProgressMax();

	m_ui->progressBar->setValue(0);
	m_ui->statusBar->clearMessage();
}

void Generator::Stop()
{
	assert(m_enumerator);
	m_enumerator.reset();

	m_ui->statusBar->showMessage(QString::number(m_current) + " / " + QString::number(m_maximum) + tr(" processed"), 10000);
}

void Generator::RetranslateRun()
{
	m_ui->pushButtonRun->setText(m_ui->frame->isEnabled() ? tr("Run!") : tr("Stop"));
}

void Generator::LoadSettings()
{
	QSettings setting(GetIniFileName(), QSettings::IniFormat);
	m_ui->lineEditA->setText(setting.value(m_ui->lineEditA->objectName(), "").toString());
	m_ui->lineEditB->setText(setting.value(m_ui->lineEditB->objectName(), "").toString());
	m_ui->lineEditC->setText(setting.value(m_ui->lineEditC->objectName(), "").toString());
	m_ui->lineEditC->setText(setting.value(m_ui->lineEditC->objectName(), "").toString());
	m_ui->lineEditResult->setText(setting.value(m_ui->lineEditResult->objectName(), "").toString());
	m_ui->lineEditPositionsValues->setText(setting.value(m_ui->lineEditPositionsValues->objectName(), "").toString());
	m_ui->lineEditEvenPositions->setText(setting.value(m_ui->lineEditEvenPositions->objectName(), "").toString());

	m_ui->checkBoxFilterPairsB->setChecked(setting.value(m_ui->checkBoxFilterPairsB->objectName(), m_ui->checkBoxFilterPairsB->isChecked()).toBool());
	m_ui->checkBoxFilterFoursA->setChecked(setting.value(m_ui->checkBoxFilterFoursA->objectName(), m_ui->checkBoxFilterFoursA->isChecked()).toBool());
	m_ui->checkBoxFilterSumC->setChecked(setting.value(m_ui->checkBoxFilterSumC->objectName(), m_ui->checkBoxFilterSumC->isChecked()).toBool());
	m_ui->checkBoxFilterPositionsValues->setChecked(setting.value(m_ui->checkBoxFilterPositionsValues->objectName(), m_ui->checkBoxFilterPositionsValues->isChecked()).toBool());
	m_ui->checkBoxFilterEvenPositions->setChecked(setting.value(m_ui->checkBoxFilterEvenPositions->objectName(), m_ui->checkBoxFilterEvenPositions->isChecked()).toBool());

	m_ui->spinBoxSumCMin->setValue(setting.value(m_ui->spinBoxSumCMin->objectName(), m_ui->spinBoxSumCMin->value()).toInt());
	m_ui->spinBoxSumCMax->setValue(setting.value(m_ui->spinBoxSumCMax->objectName(), m_ui->spinBoxSumCMax->value()).toInt());

	const auto locale = setting.value(LOCALE, QLocale::system().name());
	bool needForce = true;
	for (auto *action : GetLocaleActions())
	{
		if (action->property(LOCALE).toString() == locale)
		{
			action->trigger();
			needForce = false;
		}
	}
	if (needForce)
		m_ui->actionEnglish->trigger();

	setGeometry(setting.value("geometry", geometry()).toRect());
}

void Generator::SaveSettings() const
{
	QSettings setting(GetIniFileName(), QSettings::IniFormat);
	setting.setValue(m_ui->lineEditA->objectName(), m_ui->lineEditA->text());
	setting.setValue(m_ui->lineEditB->objectName(), m_ui->lineEditB->text());
	setting.setValue(m_ui->lineEditC->objectName(), m_ui->lineEditC->text());
	setting.setValue(m_ui->lineEditResult->objectName(), m_ui->lineEditResult->text());
	setting.setValue(m_ui->lineEditPositionsValues->objectName(), m_ui->lineEditPositionsValues->text());
	setting.setValue(m_ui->lineEditEvenPositions->objectName(), m_ui->lineEditEvenPositions->text());

	setting.setValue(m_ui->checkBoxFilterPairsB->objectName(), m_ui->checkBoxFilterPairsB->isChecked());
	setting.setValue(m_ui->checkBoxFilterFoursA->objectName(), m_ui->checkBoxFilterFoursA->isChecked());
	setting.setValue(m_ui->checkBoxFilterSumC->objectName(), m_ui->checkBoxFilterSumC->isChecked());
	setting.setValue(m_ui->checkBoxFilterPositionsValues->objectName(), m_ui->checkBoxFilterPositionsValues->isChecked());
	setting.setValue(m_ui->checkBoxFilterEvenPositions->objectName(), m_ui->checkBoxFilterEvenPositions->isChecked());

	setting.setValue(m_ui->spinBoxSumCMin->objectName(), m_ui->spinBoxSumCMin->value());
	setting.setValue(m_ui->spinBoxSumCMax->objectName(), m_ui->spinBoxSumCMax->value());

	for (auto *action : GetLocaleActions())
		if (action->isChecked())
			setting.setValue(LOCALE, action->property(LOCALE).toString());

	setting.setValue("geometry", geometry());
}

} }