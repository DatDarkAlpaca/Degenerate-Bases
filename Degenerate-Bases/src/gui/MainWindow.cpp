#include "pch.h"
#include "MainWindow.h"
#include "data.h"
#include "srwa/srwa.h"
#include "input/input.h"
#include "settings/settings.h"
#include "permutator/permutator.h"

dgn::MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    
    connect(ui.executeButton, &QPushButton::released, this, &MainWindow::Execute);
    connect(ui.loadButton, &QPushButton::released, this, &MainWindow::Load);
}

void dgn::MainWindow::Execute()
{
    // Clearing:
    Data::Clear();
    SetStatus("Previous data cleared successfully.");

    // Default files:
    SRWA::CreateDefault();

    // Sequence:
    RetrieveSequence();
    Input::SanitizeInput();
    SetStatus("Input sucessfully retrieved and sanitized.");

    // Errors & Warnings:
    if (Data::invalidSequence)
    {
        QMessageBox error;
        error.setText("The input sequence is invalid.");
        error.exec();
        SetStatus("The previous input sequence was invalid.");
        return;
    }
    
    if (Data::cartesianSize > Data::warningCartesianSize)
    {
        QMessageBox error;
        error.setText("It may take a long time to compute this sequence.");
        error.exec();
        SetStatus("Attention: It may take a long time to compute this sequence.");
        return;
    }

    // SBI:
    if (!Data::anyDegenerate)
        return ExecuteSBI();

    // Regular:
    ExecutePermutation();
}

void dgn::MainWindow::Load()
{
    Data::Clear();
    SetStatus("Previous data cleared successfully.");

    SRWA::CreateDefault();

    auto filepath = QFileDialog::getOpenFileName(this, "Open Fasta", "current path", "Fasta Files (*.fas *.fasta)").toStdString();
    auto results = SRWA::Read(filepath);
    
    if (!results.empty())
    {
        AppendResultsToTable(results);

        DisplayInformation();

        ui.sequenceEdit->setText("");
    }
}

void dgn::MainWindow::ExecuteSBI()
{
    auto dir = Settings::Get("results", "directory")
        + Settings::Get("results", "prefix")
        + std::to_string(Settings::CountFiles())
        + "."
        + Settings::Get("results", "format");

    SetStatus("SBI algorithm initiated.");
    
    Permutator::SimpleBaseInsertion(dir);
    SRWA::WriteHeader(Data::sequence, Data::iterations, Data::outcomes, Data::permutationTime, Data::writeFastaTime);

    auto results = SRWA::Read(dir);
    AppendResultsToTable(results);
    DisplayInformation();

    SetStatus("Operation finished successfully.");
}

void dgn::MainWindow::ExecutePermutation()
{
    auto dir = Settings::Get("results", "directory")
        + Settings::Get("results", "prefix")
        + std::to_string(Settings::CountFiles()) + "."
        + Settings::Get("results", "format");

    // Permutation:
    SRWA::Open(dir);
    ExecuteTimedPermutation();
    SRWA::WriteHeader(Data::sequence, Data::iterations, Data::outcomes, Data::permutationTime, Data::writeFastaTime);
    SRWA::Close();

    // Show Results:
    auto results = SRWA::Read(dir);
    if (results.size() >= Data::warningResultsSize)
    {
        QMessageBox warning;
        warning.setWindowTitle("Warning");
        warning.setText("The output file has generated a considerable amount of results.\nAttempting to display them will cause lag. Continue?");
        warning.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
        warning.setDefaultButton(QMessageBox::No);

        if (warning.exec() == QMessageBox::Yes)
            AppendResultsToTable(results);
    }
    else
        AppendResultsToTable(results);

    DisplayInformation();
    SetStatus("Operation finished successfully.");
}

void dgn::MainWindow::RetrieveSequence() const
{
    Data::sequence = ui.sequenceEdit->toPlainText().toStdString();
}

void dgn::MainWindow::ExecuteTimedPermutation() const
{
    high_resolution_clock::time_point begin = high_resolution_clock::now();
    Permutator::LazyPermutation();
    high_resolution_clock::time_point end = high_resolution_clock::now();
    Data::permutationTime = duration_cast<nanoseconds>(end - begin).count() / 1000000;
}

void dgn::MainWindow::AppendResultsToTable(const std::vector<std::string>& results)
{
    SetStatus("Appending results to table.");

    auto table = ui.sequenceResultsWidget;
    table->clearContents();
    table->setRowCount(0);

    int currentRow = table->rowCount();
    table->setRowCount(results.size());

    for (const auto result : results)
    {
        table->setItem(currentRow, 0, new QTableWidgetItem(result.c_str()));
        currentRow += 1;
    }
}

void dgn::MainWindow::DisplayInformation()
{
    auto table = ui.informationTableWidget;

    table->setItem(0, 0, new QTableWidgetItem(Data::sequence.c_str()));

    auto length = std::to_string(Data::sequence.length() - 1);
    table->setItem(1, 0, new QTableWidgetItem(length.c_str()));

    auto outcomes = std::to_string(Data::outcomes);
    table->setItem(2, 0, new QTableWidgetItem(outcomes.c_str()));

    auto iterations = std::to_string(Data::iterations);
    table->setItem(3, 0, new QTableWidgetItem(iterations.c_str()));

    auto permutationTime = std::to_string(Data::permutationTime) + "ms";
    table->setItem(4, 0, new QTableWidgetItem(permutationTime.c_str()));

    auto writeFastaTime = std::to_string(Data::writeFastaTime) + "ms";
    table->setItem(5, 0, new QTableWidgetItem(writeFastaTime.c_str()));
}

void dgn::MainWindow::SetStatus(const std::string& message)
{
    ui.statusBar->showMessage(message.c_str());
}