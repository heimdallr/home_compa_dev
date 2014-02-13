#include <QtGui/qlistwidget.h>
#include "visu.h"

visu::visu(const std::string &fileName)
	: _storage(fileName)
{
	ui.setupUi(this);
	ui.spbxCompositionNumber->setMaximum(_storage.GetSize());
	ui.spbxCompositionNumber->setMinimum(1);
	connect(ui.spbxCompositionNumber, SIGNAL(valueChanged(int)), SLOT(SlotCompositionChanged(int)));
	ui.lthMain->insertWidget(0, (_view = new View()));
	connect(_view, SIGNAL(initialized(int)), SLOT(SlotCompositionChanged(int)));
	connect(ui.lstItems, SIGNAL(itemChanged(QListWidgetItem*)), _view, SLOT(SlotItemChanged(QListWidgetItem*)));
}

void visu::SlotCompositionChanged(int number)
{
	ui.lstItems->clear();
	const Item::Items &items = _storage.GetComposition(number-1);
	std::for_each(items.begin(), items.end(), [this](const Item &item) {
		QListWidgetItem *pItem = new QListWidgetItem(QString("Element #%1").arg(item.GetId()), ui.lstItems);
		pItem->setData(Qt::UserRole, item.GetId());
		pItem->setFlags(pItem->flags() | Qt::ItemIsUserCheckable);
		pItem->setCheckState(Qt::Unchecked);
	});
	_view->Prepare(items);
}
