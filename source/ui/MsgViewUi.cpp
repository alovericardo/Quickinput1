#include "MsgViewUi.h"
MsgViewUi::MsgViewUi()
{
	ui.setupUi(this);

	QRect screen = QGuiApplication::primaryScreen()->geometry();
	setMaximumSize(screen.size());

	ui.text->setTabStopDistance(QFontMetrics(QFont("Microsoft YaHei")).horizontalAdvance("    "));
	ui.line->setColumnCount(4);
	ui.line->verticalHeader()->setDefaultAlignment(Qt::AlignCenter);
	ui.line->verticalHeader()->setSectionResizeMode(QHeaderView::ResizeMode::Fixed);
	ui.line->horizontalHeader()->setSectionResizeMode(_col_time, QHeaderView::ResizeMode::Fixed);
	ui.line->horizontalHeader()->setSectionResizeMode(_col_level, QHeaderView::ResizeMode::Fixed);
	ui.line->horizontalHeader()->setSectionResizeMode(_col_macro, QHeaderView::ResizeMode::Fixed);
	ui.line->horizontalHeader()->setSectionResizeMode(_col_text, QHeaderView::ResizeMode::Stretch);
	ui.line->setColumnWidth(_col_time, 70);
	ui.line->setColumnWidth(_col_level, 70);
	ui.line->setColumnWidth(_col_macro, 100);
	connect(ui.title_close_button, &QPushButton::clicked, this, [this] { hide(); });
	connect(ui.filter_msg_check, &QCheckBox::toggled, this, [this](bool check) { filter_msg = check; update(); });
	connect(ui.filter_war_check, &QCheckBox::toggled, this, [this](bool check) { filter_war = check; update(); });
	connect(ui.filter_err_check, &QCheckBox::toggled, this, [this](bool check) { filter_err = check; update(); });
	StyleGroup();
}

void MsgViewUi::StyleGroup()
{
	setProperty(Prop::style_group, "frame");
	style_set_group(ui.title_widget, "title");
	style_set_group(ui.content_widget, "client");
	style_set_group(ui.title_close_button, "title-close_button");
	style_set_group(ui.text, "text_edit");
	style_set_group(ui.filter_msg_check, "check");
	style_set_group(ui.filter_war_check, "check");
	style_set_group(ui.filter_err_check, "check");

	style_set_group(ui.line, "action_table");
	style_set_group(ui.line->horizontalHeader(), "action_table_header");
	style_set_group(ui.line->verticalHeader(), "action_table_header");
	ui.line->setStyleSheet("QTableCornerButton::section,QHeaderView::section,QScrollBar,QScrollBar::sub-line,QScrollBar::add-line{background-color:rgba(0,0,0,0);border:none}QScrollBar::handle{background-color:rgba(128,128,128,0.3);border:none}");
	if ("table corner button")
	{
		const QObjectList& objs = ui.line->children();
		for (size_t i = 0; i < objs.size(); i++)
		{
			const QObject* obj = objs[i];
			QString name = obj->metaObject()->className();
			if (name == "QTableCornerButton")
			{
				QWidget* corner = (QWidget*)obj;
				QHBoxLayout* box = new QHBoxLayout(corner);
				box->setContentsMargins(0, 0, 0, 0);
				QWidget* widget = new QWidget(corner);
				box->addWidget(widget);
				style_set_group(corner, "action_table_header");
				style_set_group(widget, "action_table_header");
				break;
			}
			else if (name == "QLineEdit")
			{
				QLineEdit* lineEdit = (QLineEdit*)obj;
				style_set_group(lineEdit, "action_table_header");
			}
		}
	}
}
void MsgViewUi::LoadLanguage()
{
	std::call_once(lang_once, [this] {
		lang_save_t(ui.title_label);
		lang_save_t(ui.filter_label);
		lang_save_t(ui.filter_msg_check);
		lang_save_t(ui.filter_err_check);
		lang_save_t(ui.filter_war_check);
		lang_save_tb(ui.line->horizontalHeaderItem(_col_time));
		lang_save_tb(ui.line->horizontalHeaderItem(_col_level));
		lang_save_tb(ui.line->horizontalHeaderItem(_col_macro));
		lang_save_tb(ui.line->horizontalHeaderItem(_col_text));
	});
	lang_load_t(ui.title_label);
	lang_load_t(ui.filter_label);
	lang_load_t(ui.filter_msg_check);
	lang_load_t(ui.filter_err_check);
	lang_load_t(ui.filter_war_check);
	lang_load_tb(ui.line->horizontalHeaderItem(_col_time));
	lang_load_tb(ui.line->horizontalHeaderItem(_col_level));
	lang_load_tb(ui.line->horizontalHeaderItem(_col_macro));
	lang_load_tb(ui.line->horizontalHeaderItem(_col_text));
}

void MsgViewUi::append(const MsgViewInfo& info, bool isUpdate)
{
	if (info.level == MsgViewInfo::_msg && !filter_msg) return;
	if (info.level == MsgViewInfo::_war && !filter_war) return;
	if (info.level == MsgViewInfo::_err && !filter_err) return;

	int pos = ui.line->rowCount();
	ui.line->insertRow(pos);

	QTableWidgetItem* item = new QTableWidgetItem(QDateTime::fromSecsSinceEpoch(info.time).toString("hh:mm:ss"));
	item->setTextAlignment(Qt::AlignCenter);
	ui.line->setItem(pos, _col_time, item);

	switch (info.level)
	{
	case MsgViewInfo::_war:
	{
		item = new QTableWidgetItem(lang_trans("警告"));
		item->setTextAlignment(Qt::AlignCenter);
		ui.line->setItem(pos, _col_level, item);
	} break;
	case MsgViewInfo::_err:
	{
		item = new QTableWidgetItem(lang_trans("错误"));
		item->setTextAlignment(Qt::AlignCenter);
		ui.line->setItem(pos, _col_level, item);
	} break;
	default:
	{
		item = new QTableWidgetItem(lang_trans("消息"));
		item->setTextAlignment(Qt::AlignCenter);
		ui.line->setItem(pos, _col_level, item);
	} break;
	}

	item = new QTableWidgetItem(info.macro);
	item->setTextAlignment(Qt::AlignCenter);
	ui.line->setItem(pos, _col_macro, item);

	item = new QTableWidgetItem(info.text);
	item->setTextAlignment(Qt::AlignCenter);
	ui.line->setItem(pos, _col_text, item);

	ui.line->scrollToBottom();
	if (!isUpdate && infos.size() > max_row) update();
}

void MsgViewUi::update()
{
	ui.line->setRowCount(0);
	size_t count = infos.size();
	size_t count_new = count >> 1;
	if (count > max_row)
	{
		for (size_t i = 0; i < 3; i++)
		{
			size_t type = MsgViewInfo::_msg;
			if (i == 1) type = MsgViewInfo::_war;
			else if (i == 2) type = MsgViewInfo::_err;
			infos.remove_of_find([&count, count_new, type](const MsgViewInfo& info, bool& _break) {
				if (count > count_new)
				{
					if (info.level == type)
					{
						count--;
						return true;
					}
				}
				else _break = true;
				return false;
			});
			if (count <= count_new) break;
		}
	}
	for (const auto& i : infos) append(i, true);
}

void MsgViewUi::customEvent(QEvent* e)
{
	MsgViewEvent* event = reinterpret_cast<MsgViewEvent*>(e);
	if (e->type() == MsgViewEvent::Type::setText)
	{
		ui.text->setPlainText(event->info().text);
	}
	else if (e->type() == MsgViewEvent::Type::newLine)
	{
		append(infos.append(event->info()));
	}
	else if (e->type() == MsgViewEvent::Type::clear)
	{
		infos.clear();
		update();
	}
	else if (e->type() == MsgViewEvent::Type::show)
	{
		show();
	}
	else if (e->type() == MsgViewEvent::Type::hide)
	{
		hide();
	}
	else if (e->type() == static_cast<int>(QiEvent::lang_reload))
	{
		LoadLanguage();
	}
}