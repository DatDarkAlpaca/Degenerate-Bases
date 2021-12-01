#include "pch.h"
#include "virtual_list.h"

dgn::VirtualList::VirtualList(wxWindow* parent, const wxWindowID id, const wxPoint& pos, const wxSize& size)
    : wxListCtrl(parent, id, pos, size, wxLC_REPORT | wxLC_VIRTUAL)
{
    this->AppendColumn("ID");
    this->AppendColumn("Sequence");

    this->SetColumnWidth(0, 80);
    this->SetColumnWidth(1, 600);
}
