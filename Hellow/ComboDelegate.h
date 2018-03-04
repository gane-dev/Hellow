#include "stdafx.h"
#include <Wt/WStandardItem.h>
#include <Wt/WStandardItemModel.h>
#include <Wt/WStringListModel.h>
#include <Wt/WTableView.h>
#include <Wt/WItemDelegate.h>
#include <Wt/WContainerWidget.h>
#include <Wt/WComboBox.h>
#include <Wt/WAny.h>

using namespace std;
//using namespace Wt;
class ComboDelegate : public Wt::WItemDelegate {

private:
	std::shared_ptr<Wt::WAbstractItemModel> items_;
public:
	ComboDelegate(std::shared_ptr<Wt::WAbstractItemModel> items)
		: items_(items)
	{}

	virtual void setModelData(const Wt::cpp17::any &editState, Wt::WAbstractItemModel *model,
		const Wt::WModelIndex &index) const override
	{
		int stringIdx = (int)Wt::asNumber(editState);
		model->setData(index, stringIdx, Wt::ItemDataRole::User);
		model->setData(index, items_->data(stringIdx, 0), Wt::ItemDataRole::Display);
	}
	virtual Wt::cpp17::any editState(Wt::WWidget *editor, const Wt::WModelIndex& index) const override
	{
		Wt::WComboBox* combo = dynamic_cast<Wt::WComboBox*> (dynamic_cast<Wt::WContainerWidget*>(editor)->widget(0));
		return combo->currentIndex();
	}
	virtual void setEditState(Wt::WWidget *editor, const Wt::WModelIndex& index, const Wt::cpp17::any& value) const override
	{
		Wt::WComboBox* combo = dynamic_cast<Wt::WComboBox*>(dynamic_cast<Wt::WContainerWidget*>(editor)->widget(0));
		combo->setCurrentIndex((int)Wt::asNumber(value));
	}
protected:
	virtual std::unique_ptr<Wt::WWidget> createEditor(const Wt::WModelIndex &index,
		Wt::WFlags<Wt::ViewItemRenderFlag> flags) const override
	{
		auto container = Wt::cpp14::make_unique<Wt::WContainerWidget>();
		auto combo = container->addWidget(Wt::cpp14::make_unique <Wt::WComboBox>());
		combo->setModel(items_);
		combo->setCurrentIndex((int)Wt::asNumber(index.data(Wt::ItemDataRole::User)));
		combo->changed().connect(std::bind(&ComboDelegate::doCloseEditor, this, container.get(), true));
		combo->enterPressed().connect(std::bind(&ComboDelegate::doCloseEditor, this, container.get(), true));
		combo->escapePressed().connect(std::bind(&ComboDelegate::doCloseEditor, this, container.get(), false));
		return std::move(container);
	}
private:
	virtual void doCloseEditor(Wt::WWidget *editor, bool save) const
	{
		closeEditor().emit(editor, save);
	}
}; 
