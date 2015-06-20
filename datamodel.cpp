#include "datamodel.h"
#include "app.h"

DataModel::DataModel()
{
    column_count = 1;
}

void DataModel::getData(std::string query)
{
    App::mysql->get_result(query);
    while(App::mysql->get_row())
    {
        QVector<QString> data_row;
        int row_size = App::mysql->fields();
        for(int i  = 0; i < row_size; ++i)
            data_row.push_back(QString(App::mysql->elc(i)));

        current_data.push_back(data_row);
    }
}

int DataModel::rowCount(const QModelIndex &parent) const
{
    if(parent.isValid())
        return 0;

    return current_data.size();
}

int DataModel::columnCount(const QModelIndex &parent) const
{
    return column_count;
}

QModelIndex DataModel::index(int row, int column, const QModelIndex &parent) const
{
    if(!parent.isValid())
        if(row < current_data.size())  return createIndex(row, column);

    return QModelIndex();
}

QModelIndex DataModel::parent(const QModelIndex &child) const
{
    return QModelIndex();
}

QVariant DataModel::data(const QModelIndex &index, int role) const
{
    if(!index.isValid())
        return QVariant();

    int row = index.row();
    int column = index.column();

    if(row < current_data.size() && row >= 0 && column >= 0 && role == Qt::DisplayRole)
    {
        QVector<QString> data_row = current_data.at(row);
        QString str = "";
        if(column < data_row.size()) str = data_row.at(column);
        return str;
    }

    return QVariant();
}

Qt::ItemFlags DataModel::flags(const QModelIndex &index) const
{
    return QAbstractItemModel::flags(index);
}

bool DataModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
//    if(!index.isValid())
//        return false;
//    int c = index.column();
//    int r = index.row();

//    if(role == Qt::EditRole)
//    {
//        if(c == 0 && !m_base->isEmpty())
//        {
//            QList<QString> k = m_base->keys();
//            if(!k.contains(value.toString()))
//            {
//                TreeItem* item = m_base->take(index.data().toString());
//                m_base->insert(value.toString(), item);
//                return true;
//            }
//        }
//        else if(c == 1 && !m_base->isEmpty())
//        {
//            QString key = this->index(r, 0, index.parent()).data().toString();
//            TreeItem* old = m_base->value(key);
//            if(old != nullptr)
//            {
//                m_base->operator [](key) = createDirTree(value.toString(), old->parent());
//                delete old;
//            }
//            else
//                m_base->operator [](key) = createDirTree(value.toString(), nullptr);

//            return true;
//        }
//    }
    return false;
}

QVariant DataModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if(role != Qt::DisplayRole)
        return QVariant();

    if(orientation == Qt::Horizontal && section < header.size())
        return header.at(section);

    return QVariant();
}
