#pragma once
#include "pch.h"

namespace dgn
{
    namespace
    {
        struct ResultData
        {
            ResultData(size_t id, std::string result) : id(id), result(result) { }

            size_t id;
            std::string result;
        };
    }
   
    class VirtualList : public wxListCtrl
    {
    public:
        VirtualList(wxWindow* parent, const wxWindowID id, const wxPoint& pos, const wxSize& size);

        virtual wxString OnGetItemText(long index, long column) const wxOVERRIDE
        {
            ResultData item = m_Items[index];

            switch (column)
            {
            case 0:
                return std::to_string(item.id);
            case 1:
                return item.result;
            default:
                return "";
            }
        }

        void RefreshAfterUpdate()
        {
            this->SetItemCount(m_Items.size());
            this->Refresh();
        }

        void Clear()
        {
            m_Items.clear();
            RefreshAfterUpdate();
        }

        void SetItems(std::vector<ResultData>&& data)
        {
            m_Items = data;
            RefreshAfterUpdate();
        }

        void AddItems(std::vector<ResultData>&& data, bool append = false)
        {
            for (const auto& element : data)
                m_Items.push_back(element);

            RefreshAfterUpdate();
        }

        void AddItem(size_t id, const std::string& result, bool append = false)
        {
            if(append)
                m_Items.push_back(ResultData(GetItemCount(), result));
            else
                m_Items.push_back(ResultData(id, result));

            RefreshAfterUpdate();
        }

    private:
        std::vector<ResultData> m_Items = {};
    };
}