#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_DegenerateBases.h"

namespace dgn
{
    class MainWindow : public QMainWindow
    {
        Q_OBJECT

    public:
        MainWindow(QWidget* parent = Q_NULLPTR);

    private slots:
        void Execute();

        void Load();

        void OpenSettings();

    private:
        void ExecuteSBI();

        void ExecutePermutation();

        void ShowResults();

    signals:
        void PermutationFinished();

    private:
        void RetrieveSequence() const;

        void ExecuteTimedPermutation() const;

        void AppendResultsToTable(const std::vector<std::string>& results);

        void DisplayInformation();

        void SetStatus(const std::string& message);

    private:
        std::string m_Directory;
        Ui::MainWindowClass ui;
    };
}