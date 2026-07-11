#pragma once
#include "UpdateUi.h"
#include "ui_AboutUi.h"
#include <src/inc_header.h>
#ifdef Q_UPDATE
#include <src/update.h>
#endif
class AboutUi : public QWidget
{
	Q_OBJECT;
	Ui::AboutUiClass ui;
	std::once_flag lang_once;
#ifdef Q_UPDATE
	std::unique_ptr<QiUpdate> update;
#endif
	std::string version, content;

public:
	AboutUi(QWidget* parent = nullptr);
	void LoadLanguage();

private:
	bool eventFilter(QObject*, QEvent*);
#ifdef Q_UPDATE
	void customEvent(QEvent*);
#endif
};