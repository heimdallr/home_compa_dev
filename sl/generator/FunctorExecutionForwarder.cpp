#include "FunctorExecutionForwarder.h"

FunctorExecutionForwarder::FunctorExecutionForwarder(QObject *parent /*= Q_NULLPTR*/)
	: QObject(parent)
{
	qRegisterMetaType<FunctorType>("FunctorType");

	bool result = connect(this, SIGNAL(ExecuteFunctor(FunctorType)), this, SLOT(OnExecuteFunctor(FunctorType)), Qt::QueuedConnection);
	if ( ! result)
		throw std::logic_error("Failed to connect signal and slot");
}

void FunctorExecutionForwarder::Forward(FunctorExecutionForwarder::FunctorType f) const
{
	emit ExecuteFunctor(f);
}

void FunctorExecutionForwarder::OnExecuteFunctor(FunctorExecutionForwarder::FunctorType f)
{
	f();
}
