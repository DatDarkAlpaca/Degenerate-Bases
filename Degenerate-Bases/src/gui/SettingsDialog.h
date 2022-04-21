#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_SettingsDialog.h"

namespace dgn
{
    class SettingsDialog : public QDialog
    {
        Q_OBJECT

    public:
        SettingsDialog(QWidget* parent = Q_NULLPTR);

    public:
        void ApplySettings();

    private:
        bool CheckSettings();

        void LoadSettings();

    private:
        Ui::SettingsDialog ui;
    };
}