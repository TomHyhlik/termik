#include <QTableWidget>
#include <QHeaderView>

/////////////////////////////////////////////////////////////////
/// \brief table_addItem
/// \param table where the new item will be added
/// \param tableItem list to be added to the table row
/// \note tableItem must have the size corresponding to number
///         of collumns of the table
void table_addItem(QTableWidget* table, QStringList tableItem)
{
    table->insertRow(table->rowCount());
    /* get number of the new row */
    int newRow =  table->rowCount() - 1;
    /* for each tableItem in the row */
    for (int column = 0; column < tableItem.size(); column++){
        /* create new item to the table */
        QTableWidgetItem *item = new QTableWidgetItem(
                    QString("%1").arg(tableItem.at(column)));
        /* make the item non-editable */
        item->setFlags(item->flags() ^ Qt::ItemIsEditable);
        item->setTextAlignment(Qt::AlignVCenter);
        /* add the item to specified column and row */
        table->setItem(newRow, column, item);
    }
    /* resize the columns to be optimized for the content */
    for (int i = 0; i <  table->columnCount(); i++){
        table->resizeColumnToContents(i);
    }
    // set column size to widget size
    table->horizontalHeader()->setStretchLastSection(true);
}

/////////////////////////////////////////////////////////////////
void table_clear(QTableWidget* table)
{
    table->clearContents();
    while (table->rowCount()) {
        table->removeRow(0);
    }
    /* set column size to widget size */
    table->horizontalHeader()->setStretchLastSection(true);
}

/////////////////////////////////////////////////////////////////
