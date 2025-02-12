#include "welcome_dialog.h"
#include "ui_welcome_dialog.h"

#include "gui_settings.h"
#include "qt_utils.h"

#include <QPushButton>
#include <QCheckBox>
#include <QSvgWidget>

welcome_dialog::welcome_dialog(std::shared_ptr<gui_settings> gui_settings, QWidget* parent)
	: QDialog(parent)
	, ui(new Ui::welcome_dialog)
	, m_gui_settings(std::move(gui_settings))
{
	ui->setupUi(this);

	setWindowFlags(windowFlags() & Qt::WindowTitleHint);

	ui->okay->setEnabled(false);
	ui->icon_label->load(QStringLiteral(":/rpcs3.svg"));
	ui->label_3->setText(tr(
		R"(
			<p style="white-space: nowrap;">
				RPCS3 is an open-source Sony PlayStation 3 emulator and debugger.<br>
				It is written in C++ for Windows, Linux, FreeBSD and MacOS funded with <a %0 href="https://www.patreon.com/Nekotekina">Patreon</a>.<br>
				Our developers and contributors are always working hard to ensure this project is the best that it can be.<br>
				There are still plenty of implementations to make and optimizations to do.
			</p>
		)"
	).arg(gui::utils::get_link_style()));

	ui->label_info->setText(tr(
		R"(
			<p style="white-space: nowrap;">
				To get started, you must first install the <span style="font-weight:600;">PlayStation 3 firmware</span>.<br>
				Please refer to the <a %0 href="https://rpcs3.net/quickstart">Quickstart</a> guide found on the official website for further information.<br>
				If you have any further questions, please refer to the <a %0 href="https://rpcs3.net/faq">FAQ</a>.<br>
				Otherwise, further discussion and support can be found on the <a %0 href="https://forums.rpcs3.net">Forums</a> or on our <a %0 href="https://discord.me/RPCS3">Discord</a> server.
			</p>
		)"
	).arg(gui::utils::get_link_style()));

	connect(ui->i_have_read, &QCheckBox::clicked, [this](bool checked)
	{
		ui->okay->setEnabled(checked);
	});

	connect(ui->do_not_show, &QCheckBox::clicked, [this](bool checked)
	{
		m_gui_settings->SetValue(gui::ib_show_welcome, QVariant(!checked));
	});

	connect(ui->okay, &QPushButton::clicked, this, &QDialog::accept);

	layout()->setSizeConstraint(QLayout::SetFixedSize);
}

welcome_dialog::~welcome_dialog()
{
}
