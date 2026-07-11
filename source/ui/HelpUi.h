#pragma once
#include <src/inc_header.h>
#include "ui_HelpUi.h"
class HelpUi : public QDialogFrameless
{
	Q_OBJECT;
	using This = HelpUi;
	Ui::HelpUiClass ui;

public:
	HelpUi();

private:
	void StyleGroup();

	bool event(QEvent*);
	void showEvent(QShowEvent*);
};