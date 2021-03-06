// Hellow.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"


#include <Wt/WApplication.h>
#include <Wt/WBreak.h>
#include <Wt/WContainerWidget.h>
#include <Wt/WLineEdit.h>
#include <Wt/WPushButton.h>
#include <Wt/WText.h>
#include <Wt/WMenu.h>
#include <Wt/WStackedWidget.h>
#include <Wt/WTextArea.h>
#include <Wt/WStandardItemModel.h>
#include <Wt/WTable.h>
#include "Employee.h"
#include <Wt/WTableView.h>
#include <Wt/WStandardItem.h>
#include<Wt/WStringListModel.h>
#include "ComboDelegate.h"
using namespace std;
class HelloApplication : public Wt::WApplication
{
public:
	HelloApplication(const Wt::WEnvironment& env);

private:
	Wt::WLineEdit *nameEdit_;
	Wt::WText *greeting_;

	void greet();
};

HelloApplication::HelloApplication(const Wt::WEnvironment& env)
	: Wt::WApplication(env)
{
	setTitle("Hello world");

	auto container = Wt::cpp14::make_unique<Wt::WContainerWidget>();
	auto contents = Wt::cpp14::make_unique<Wt::WStackedWidget>();
	Wt::WMenu *menu =
		root()->addWidget(Wt::cpp14::make_unique<Wt::WMenu>(contents.get()));
	
	menu->setStyleClass("nav nav-pills nav-stacked");
	menu->setWidth(150);
	// Add menu items using the default lazy loading policy.
	menu->addItem("Internal paths", Wt::cpp14::make_unique<Wt::WTextArea>("Internal paths contents"));
	menu->addItem("Anchor", Wt::cpp14::make_unique<Wt::WTextArea>("Anchor contents"));
	menu->addItem("Stacked widget", Wt::cpp14::make_unique<Wt::WTextArea>("Stacked widget contents"));
	menu->addItem("Tab widget", Wt::cpp14::make_unique<Wt::WTextArea>("Tab widget contents"));
	menu->addItem("Menu", Wt::cpp14::make_unique<Wt::WTextArea>("Menu contents"));

	root()->addWidget(std::move(contents));
	
	//root()->addChild(Wt::cpp14::make_unique<Wt::WContainerWidget>(&container));
	/*
	root()->addWidget(std::make_unique<Wt::WText>("Your name, please? "));
	nameEdit_ = root()->addWidget(std::make_unique<Wt::WLineEdit>());
	Wt::WPushButton *button = root()->addWidget(std::make_unique<Wt::WPushButton>("Greet me."));
	root()->addWidget(make_unique<Wt::WBreak>());
	greeting_ = root()->addWidget(std::make_unique<Wt::WText>());
	button->clicked().connect(this, [this]() {
		greeting_->setText("Hello there, " + nameEdit_->text());
	});
	*/
	Employee employees[3] = { { "Mark", "Otto", 100 }, { "Jacob", "Thornton", 50 },{ "Larry the Bird", "", 10} };
	
	auto table = Wt::cpp14::make_unique<WTable>();
	table->setHeaderCount(1);
	table->setWidth(WLength("100%"));

	

	table->elementAt(0, 0)->addWidget(cpp14::make_unique<WText>("#"));
	table->elementAt(0, 1)->addWidget(cpp14::make_unique<WText>("First Name"));
	table->elementAt(0, 2)->addWidget(cpp14::make_unique<WText>("Last Name"));
	table->elementAt(0, 3)->addWidget(cpp14::make_unique<WText>("Pay"));

	for (unsigned i = 0; i < 3; ++i) {
		Employee& employee = employees[i];
		int row = i + 1;

		table->elementAt(row, 0)
			->addWidget(cpp14::make_unique<WText>(WString("{1}")
				.arg(row)));
		table->elementAt(row, 1)
			->addWidget(cpp14::make_unique<WText>(employee.firstName));
		table->elementAt(row, 2)
			->addWidget(cpp14::make_unique<WText>(employee.lastName));
		table->elementAt(row, 3)
			->addWidget(cpp14::make_unique<WLineEdit>(WString("{1}")
				.arg(employee.pay)));
	}

	root()->addWidget(std::move(table));
	// create model
	std::vector<WString> options{ "apples", "pears", "bananas", "cherries" };
	auto tableView = cpp14::make_unique<WTableView>();
	//create model
	auto model = std::make_shared<WStandardItemModel>();
	for (unsigned i = 0; i < 2; i++) {
		for (unsigned j = 0; j < 2; j++) {
			auto item = cpp14::make_unique<WStandardItem>();
			item->setData(0, ItemDataRole::User);
			item->setData(options[0], ItemDataRole::Display);
			item->setFlags(ItemFlag::Editable);
			model->setItem(i, j, std::move(item));
		}
	}

	//create table
	tableView->setModel(model);
	tableView->setEditTriggers(EditTrigger::SingleClicked);
	auto slModel = std::make_shared<WStringListModel>();
	slModel->setStringList(options);
	std::shared_ptr<ComboDelegate> customDelegate =
		std::make_shared<ComboDelegate>(slModel);
	tableView->setItemDelegate(customDelegate);

	tableView->setSortingEnabled(false);
	tableView->setColumnResizeEnabled(false);
	tableView->setRowHeight(40);
	tableView->setHeaderHeight(0);

	const int WIDTH = 120;
	for (int i = 0; i < tableView->model()->columnCount(); ++i)
		tableView->setColumnWidth(i, WIDTH);
	tableView->setWidth((WIDTH + 7) * tableView->model()->columnCount() + 2);
	root()->addWidget(std::move(tableView));
}

int main(int argc, char **argv)
{
	return Wt::WRun(argc, argv, [](const Wt::WEnvironment& env) {
		return std::make_unique<HelloApplication>(env);
	});
}

