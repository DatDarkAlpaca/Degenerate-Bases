// -*- C++ -*-
//
// generated by wxGlade 1.1.0pre on Fri Dec 17 03:27:41 2021
//
// Example for compiling a single file project under Linux using g++:
//  g++ MyApp.cpp $(wx-config --libs) $(wx-config --cxxflags) -o MyApp
//
// Example for compiling a multi file project under Linux using g++:
//  g++ main.cpp $(wx-config --libs) $(wx-config --cxxflags) -o MyApp Dialog1.cpp Frame1.cpp
//

#ifndef DEGENERATE_UI_H
#define DEGENERATE_UI_H

#ifndef APP_CATALOG
#define APP_CATALOG "DegenerateBases"
#endif

#include "pch.h"

class MainFrame: public wxFrame {
public:
    MainFrame(wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos=wxDefaultPosition, const wxSize& size=wxDefaultSize, long style=wxDEFAULT_FRAME_STYLE);

private:

protected:
    wxPanel* mainPanel;
    wxSplitterWindow* mainSpliter;
    wxPanel* leftPanel;
    wxSplitterWindow* leftSpliter;
    wxPanel* inputPanel;
    wxTextCtrl* inputCtrl;
    wxButton* generateButton;
    wxPanel* resultsPanel;
    wxListCtrl* generationResultsTable;
    wxPanel* listPanel;
};


#endif