#pragma once
#include <qlist.h>
#include <qcolor.h>
#include <qstring.h>
#include "lang.h"

#define style_set_group(Obj, name) Obj->setProperty(Prop::style_group, name)

namespace QiUi
{
	constexpr const char* color_dialog_style = "*{color:black}QPushButton{width:60px;border:2px solid blue}";
	namespace Symbol
	{
		inline QString Entry = "🔜";
		inline QString Pause = "⏸️";
		inline QString Exit = "🔙";
		inline QString Any = "🟡";
		inline QString On = "✅";
		inline QString Off = "⛔";
		inline QString Ok = "⭕";
		inline QString Yes = "✔️";
		inline QString Not = "❌";
		inline QString Stop = "🛑";
		inline QString Show = "🔼";
		inline QString Hide = "🔽";
		inline QString Option = "⚙";
		inline QString Link = "🔗";
		inline QString Edit = "🔧";
		inline QString Up = "⬆️";
		inline QString Down = "⬇️";
		inline QString Turn = "🔃";
		inline QString Left = "🔙";
		inline QString Top = "🔝";
		inline QString Right = "🔜";
		inline QString Move = "🔛";
		inline QString Time = "⏳";
		inline QString Text = "🅰️";
		inline QString Loop = "♾️";
		inline QString Color = "🌈";
		inline QString Image = "🖼";
		inline QString Point = "🪂";
		inline QString Jump = "🛩";
		inline QString Block = "🪂";
		inline QString BlockExec = "🛩";
		inline QString Equal = "🟰";
		inline QString Var = "💠";
		inline QString Track = "➰";
		inline QString Speaker = "🔈️";
		inline QString Range = "🔁";
	};
	namespace Text
	{
		// state
		static QString trOn() { return lang_trans("启用") + Symbol::On; };
		static QString trOff() { return lang_trans("禁用") + Symbol::Off; };
		// record
		static QString rcStart() { return lang_trans("开始") + Symbol::Ok; };
		static QString rcStop() { return lang_trans("停止") + Symbol::Ok; };
		static QString rcClose() { return lang_trans("取消") + Symbol::Not; };
		// menu
		static QString muOn() { return lang_trans("启用") + Symbol::On; };
		static QString muOff() { return lang_trans("禁用") + Symbol::Off; };
		static QString muShow() { return lang_trans("显示") + Symbol::Show; };
		static QString muHide() { return lang_trans("隐藏") + Symbol::Hide; };
		static QString muExit() { return lang_trans("退出") + Symbol::Stop; };
		// pop
		inline QString popOn_ = "@ 启用";
		inline QString popOff_ = "@ 禁用";
		inline QString popWndOn_ = "@ 窗口启用";
		inline QString popWndOff_ = "@ 窗口禁用";
		inline QString popClickOn_ = "连点 @";
		inline QString popClickOff_ = "停止 @";
		inline QString popSwOn_ = "执行 @";
		inline QString popSwOff_ = "停止 @";
		inline QString popDownOn_ = "执行$次 @";
		inline QString popDownOff_ = "停止 @";
		inline QString popUpOn_ = "执行$次 @";
		static QString popUpOff_ = "停止 @";

		static QString popOn() { return lang_trans(popOn_); }
		static QString popOff() { return lang_trans(popOff_); }
		static QString popWndOn() { return lang_trans(popWndOn_); }
		static QString popWndOff() { return lang_trans(popWndOff_); }
		static QString popClickOn() { return lang_trans(popClickOn_); }
		static QString popClickOff() { return lang_trans(popClickOff_); }
		static QString popSwOn() { return lang_trans(popSwOn_); }
		static QString popSwOff() { return lang_trans(popSwOff_); }
		static QString popDownOn() { return lang_trans(popDownOn_); }
		static QString popDownOff() { return lang_trans(popDownOff_); }
		static QString popUpOn() { return lang_trans(popUpOn_); }
		static QString popUpOff() { return lang_trans(popUpOff_); }
	};
	struct Theme
	{
		QString name;
		QString style;
	};
	struct PopTextInfo
	{
		QColor c;
		QString t;
		QString s;
	};
	struct PopTextData
	{
		PopTextInfo qe;
		PopTextInfo qd;
		PopTextInfo we;
		PopTextInfo wd;
		PopTextInfo qce;
		PopTextInfo qcd;
		PopTextInfo swe;
		PopTextInfo swd;
		PopTextInfo dwe;
		PopTextInfo dwd;
		PopTextInfo upe;
		PopTextInfo upd;
		PopTextInfo qe_;
		PopTextInfo qd_;
		PopTextInfo we_;
		PopTextInfo wd_;
		PopTextInfo qce_;
		PopTextInfo qcd_;
		PopTextInfo swe_;
		PopTextInfo swd_;
		PopTextInfo dwe_;
		PopTextInfo dwd_;
		PopTextInfo upe_;
		PopTextInfo upd_;
		int x = 5000;
		int y = 0;
		int size = 100;
		int time = 1000;
	};
	struct QuickInputUi
	{
		QList<Theme> themes;
		QList<QString> sounds;
		PopTextData pop;
	};
}