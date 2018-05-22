#include <cassert>

#include <QFileDialog>
#include <QFileInfo>
#include <QLineEdit>
#include <QMessageBox>
#include <QProgressBar>
#include <QSettings>
#include <QTimer>
#include <QTranslator>
#include <QVariant>
#include <QWinTaskbarButton>
#include <QWinTaskbarProgress>

#include "log.h"

#include "Enumerator.h"
#include "Filter.h"
#include "FunctorExecutionForwarder.h"
#include "ResultSaver.h"

#include "ui_Generator.h"
#include "Generator.h"

namespace HomeCompa { namespace sl {

namespace {

QTranslator g_translator;
const char *LOCALE = "locale";

QString GetFileName(const QString &ext)
{
	QFileInfo info(QCoreApplication::applicationFilePath());
	return info.path() + "/" + info.completeBaseName() + "." + ext;
}

}

Generator::Generator(QWidget *parent)
	: QMainWindow(parent)
	, m_ui(std::make_unique<Ui::GeneratorClass>())
	, m_forwarder(new FunctorExecutionForwarder(this))
	, m_progressMessaageTimer(new QTimer(this))
{
	log(GetFileName("log").toStdString());

	m_ui->setupUi(this);
	m_ui->progressBar->setVisible(false);
	m_ui->horizontalLayoutRun->setAlignment(Qt::AlignRight);

	m_progressMessaageTimer->setInterval(100);
	connect(m_progressMessaageTimer, &QTimer::timeout, [this] {m_ui->statusBar->showMessage(GetStatusMessage()); });

	QTimer::singleShot(0, [this]
	{
		QWinTaskbarButton *button = new QWinTaskbarButton(this);
		button->setWindow(windowHandle());

		m_taskbarProgress = button->progress();
		m_taskbarProgress->setRange(m_ui->progressBar->minimum(), m_ui->progressBar->maximum());
		m_taskbarProgress->setVisible(true);
		connect(m_ui->progressBar, &QProgressBar::valueChanged, m_taskbarProgress, &QWinTaskbarProgress::setValue);
	});

	connect(m_ui->actionAbout, &QAction::triggered, [parent = this](bool) {QMessageBox::about(parent, tr("About generator"), tr("generator generates generated")); });

	const auto openFileDialog = [parent = this](QLineEdit *edit, bool existingOnly = true)
	{
		QFileDialog dialog(parent, tr("Open file"));
		dialog.setFileMode(existingOnly? QFileDialog::FileMode::ExistingFile: QFileDialog::FileMode::AnyFile);
		dialog.setViewMode(QFileDialog::Detail);
		if (dialog.exec() && !dialog.selectedFiles().empty())
			edit->setText(dialog.selectedFiles().front());
	};

	const auto checkFile = [this](const QString &fileName)
	{
		if (!QFile(fileName).exists())
			return;

		const auto data = Reader<uint8_t>::Read(fileName.toStdString(), false);
		if (data.empty())
			return;

		m_ui->spinBoxN->setValue(data.front().size());
		m_ui->spinBoxM->setValue(m_ui->spinBoxN->value() == 5 ? 36 : 49);
	};

	connect(m_ui->lineEditA, &QLineEdit::textChanged, checkFile);
	connect(m_ui->lineEditB, &QLineEdit::textChanged, checkFile);

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

void Generator::Handle(std::vector<std::vector<uint8_t>> &data)
{
	assert(!data.empty());
	std::vector<std::vector<uint8_t>> passed;
	for (auto &d : data)
	{
		if (m_filter->Check(d))
		{
			passed.emplace_back();
			passed.back().swap(d);
		}
	}

	m_forwarder->Forward([this, current = data.size(), passed = passed.size()]()
	{
		m_current += current;
		m_passed += passed;
		const auto pct = m_current * 100 / m_maximum;
		if (m_ui->progressBar->value() != pct)
		{
			m_ui->progressBar->setValue(pct);
		}
	});

	if (!passed.empty())
		m_resultSaver->Save(std::forward<Data>(passed));
}

void Generator::Ready()
{
	m_forwarder->Forward([this]()
	{
		if (!m_ui->frame->isEnabled())
			m_ui->pushButtonRun->click();
	});
}

void Generator::Saved(size_t saved)
{
	m_forwarder->Forward([&s = m_saved, saved]()
	{
		s += saved;
	});
}

void Generator::SaveReady()
{
	m_forwarder->Forward([this]()
	{
		m_resultSaver.reset();
		m_progressMessaageTimer->stop();
		m_ui->statusBar->showMessage(GetStatusMessage());
		if (m_current < m_maximum)
			m_taskbarProgress->stop();
		else
			m_taskbarProgress->hide();

		m_ui->progressBar->setVisible(false);
		m_ui->pushButtonRun->setEnabled(true);
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

	RetranslateRun();
	m_ui->frame->isEnabled() ? Stop() : Start();
}

void Generator::Start()
{
	assert(!m_enumerator);
	std::make_unique<ResultSaver>(*this, m_ui->lineEditResult->text()).swap(m_resultSaver);
	std::make_unique<Enumerator>(*this, m_ui->spinBoxN->value(), m_ui->spinBoxM->value()).swap(m_enumerator);
	m_maximum = m_enumerator->GetProgressMax();

	std::make_unique<Filter>(m_ui->spinBoxN->value(), m_ui->spinBoxM->value()).swap(m_filter);
	try
	{
		if (m_ui->checkBoxFilterFoursA->isChecked())
			m_filter->AddA(m_ui->lineEditA->text());
		if (m_ui->checkBoxFilterPairsB->isChecked())
			m_filter->AddB(m_ui->lineEditB->text());
		if (m_ui->checkBoxFilterSumC->isChecked())
			m_filter->AddC(m_ui->lineEditC->text(), m_ui->spinBoxSumCMin->value(), m_ui->spinBoxSumCMax->value());
		if (m_ui->checkBoxFilterEvenPositions->isChecked())
			m_filter->AddEven(m_ui->lineEditEvenPositions->text());
		if (m_ui->checkBoxFilterPositionsValues->isChecked())
			m_filter->AddPositionsValues(m_ui->lineEditPositionsValues->text());
	}
	catch (const std::exception &ex)
	{
		m_forwarder->Forward([button = m_ui->pushButtonRun]()
		{
			button->click();
		});

		QMessageBox(QMessageBox::Icon::Critical, tr("Error"), QString(ex.what()), QMessageBox::StandardButton::Ok, this).exec();
		return;
	}

	m_current = 0;
	m_passed = 0;
	m_saved = 0;

	m_ui->progressBar->setValue(0);
	m_ui->progressBar->setVisible(true);
	m_taskbarProgress->show();
	m_taskbarProgress->resume();
	m_ui->statusBar->clearMessage();
	m_progressMessaageTimer->start();

	m_enumerator->Start();
}

void Generator::Stop()
{
	m_ui->pushButtonRun->setEnabled(false);
	m_enumerator.reset();
	m_filter.reset();
	m_resultSaver->Stop();
	log().flush();
}

void Generator::RetranslateRun()
{
	m_ui->pushButtonRun->setText(m_ui->frame->isEnabled() ? tr("Run!") : tr("Stop"));
}

void Generator::SetLocale(const QString &locale)
{
	for (auto *action : GetLocaleActions())
	{
		if (action->property(LOCALE).toString() == locale)
		{
			action->trigger();
			return;
		}
	}

	m_ui->actionEnglish->trigger();
}

void Generator::LoadSettings()
{
	const auto locale = QLocale::system().name();
	SetLocale(locale);

	const auto iniFileName = GetFileName("ini");
	if (!QFile(iniFileName).exists())
		return;

	QSettings setting(iniFileName, QSettings::IniFormat);
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
	m_ui->spinBoxN->setValue(setting.value(m_ui->spinBoxN->objectName(), m_ui->spinBoxN->value()).toInt());
	m_ui->spinBoxM->setValue(setting.value(m_ui->spinBoxM->objectName(), m_ui->spinBoxM->value()).toInt());

	const auto settingsLocale = setting.value(LOCALE, locale).toString();
	if (settingsLocale != locale)
		SetLocale(settingsLocale);

	setGeometry(setting.value("geometry", geometry()).toRect());
}

void Generator::SaveSettings() const
{
	QSettings setting(GetFileName("ini"), QSettings::IniFormat);
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
	setting.setValue(m_ui->spinBoxN->objectName(), m_ui->spinBoxN->value());
	setting.setValue(m_ui->spinBoxM->objectName(), m_ui->spinBoxM->value());

	for (auto *action : GetLocaleActions())
		if (action->isChecked())
			setting.setValue(LOCALE, action->property(LOCALE).toString());

	setting.setValue("geometry", geometry());
}

QString Generator::GetStatusMessage() const
{
	return QString(tr("%1 / %2 processed, %3 passed, %4 saved"))
		.arg(QString::number(m_current))
		.arg(QString::number(m_maximum))
		.arg(QString::number(m_passed))
		.arg(QString::number(m_saved))
		;
}

} }
