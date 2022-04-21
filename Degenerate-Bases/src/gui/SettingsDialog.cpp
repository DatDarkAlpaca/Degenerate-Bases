#include "pch.h"
#include "SettingsDialog.h"
#include "settings/settings.h"

dgn::SettingsDialog::SettingsDialog(QWidget* parent)
	: QDialog(parent)
{
	ui.setupUi(this);

	LoadSettings();

	connect(ui.buttonBox, &QDialogButtonBox::accepted, this, &SettingsDialog::ApplySettings);
}

void dgn::SettingsDialog::ApplySettings()
{
	if (!CheckSettings())
		return;
	Settings::Set("fasta", "header_character", ui.headerCharacterEdit->text().toStdString());
	Settings::Set("fasta", "header_template", ui.headerTemplateEdit->text().toStdString());

	Settings::Set("results", "prefix", ui.prefixEdit->text().toStdString());
	Settings::Set("results", "format", ui.formatEdit->text().toStdString());
	Settings::Set("results", "directory", ui.directoryEdit->text().toStdString());
}

bool dgn::SettingsDialog::CheckSettings()
{
	if (ui.headerCharacterEdit->text().isEmpty() ||
		ui.headerTemplateEdit->text().isEmpty() ||
		ui.prefixEdit->text().isEmpty() ||
		ui.formatEdit->text().isEmpty() ||
		ui.directoryEdit->text().isEmpty())
		return false;

	return true;
}

void dgn::SettingsDialog::LoadSettings()
{
	ui.headerCharacterEdit->setText(Settings::Get("fasta", "header_character").c_str());
	ui.headerTemplateEdit->setText(Settings::Get("fasta", "header_template").c_str());

	ui.prefixEdit->setText(Settings::Get("results", "prefix").c_str());
	ui.formatEdit->setText(Settings::Get("results", "format").c_str());
	ui.directoryEdit->setText(Settings::Get("results", "directory").c_str());
}
