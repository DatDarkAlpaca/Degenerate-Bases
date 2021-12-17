#pragma once
#include "pch.h"

namespace dgn
{
    namespace
    {
        struct ResultData
        {
            ResultData(size_t id, std::string result) : id(id), result(result) { }
            ResultData() = default;

            size_t id;
            std::string result;
        };
    }
   
    class VirtualList : public wxListCtrl
    {
    public:
        VirtualList(wxWindow* parent, const wxWindowID id, const wxPoint& pos, const wxSize& size, long style = 5L)
            : wxListCtrl(parent, id, pos, size, style)
        {
            AppendColumn("ID");
            AppendColumn("Sequence");

            SetColumnWidth(0, 80);
            SetColumnWidth(1, 400);
        }

    public:
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

        void SetItems(const std::vector<std::string>& data)
        {
            std::vector<ResultData> resultData;
            for (uint_least16_t i = 0; i < data.size(); ++i)
                resultData.push_back(ResultData(i, data[i]));

            m_Items = resultData;
            RefreshAfterUpdate();
        }

        void AddItems(const std::vector<std::string>& data)
        {
            for (const auto& element : data)
                m_Items.push_back(ResultData(GetItemCount(), element));

            RefreshAfterUpdate();
        }

        void AddItem(const std::string& result)
        {
            m_Items.push_back(ResultData(GetItemCount(), result));

            RefreshAfterUpdate();
        }

    private:
        std::vector<ResultData> m_Items = {};
    };
}