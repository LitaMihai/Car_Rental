#include "AccountFrame.h"

AccountFrame::AccountFrame() : wxFrame(NULL, wxID_ANY, "Hello World")
{
    wxMenu* menuFile = new wxMenu;
    menuFile->Append(ID_Hello, "&Hello...\tCtrl-H",
        "Help string shown in status bar for this menu item");
    menuFile->AppendSeparator();
    menuFile->Append(wxID_EXIT);

    wxMenu* menuHelp = new wxMenu;
    menuHelp->Append(wxID_ABOUT);

    wxMenuBar* menuBar = new wxMenuBar;
    menuBar->Append(menuFile, "&File");
    menuBar->Append(menuHelp, "&Help");

    SetMenuBar(menuBar);

    CreateStatusBar();
    SetStatusText("Welcome to wxWidgets!");

    Bind(wxEVT_MENU, &AccoutFrame::OnHello, this, ID_Hello);
    Bind(wxEVT_MENU, &AccoutFrame::OnAbout, this, wxID_ABOUT);
    Bind(wxEVT_MENU, &AccoutFrame::OnExit, this, wxID_EXIT);
}

void AccountFrame::OnHello(wxCommandEvent& event)
{
	wxLogMessage("HeloWorld!");
}

void AccountFrame::OnExit(wxCommandEvent& event)
{
	Close(true);
}

void AccountFrame::OnAbout(wxCommandEvent& event)
{
	wxMessageBox("Hello World example", "About Hello World", wxOK | wxICON_INFORMATION);
}
