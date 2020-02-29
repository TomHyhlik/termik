#include <QTableWidget>
#include <QHeaderView>

/////////////////////////////////////////////////////////////////
void table_addItem(QTableWidget* table, QStringList element)
{
    table->insertRow(table->rowCount());
    /* get number of the new row */
    int newRow =  table->rowCount() - 1;
    /* for each element in the row */
    for (int column = 0; column < element.size(); column++){
        /* create new item to the table */
        QTableWidgetItem *item = new QTableWidgetItem(QString("%1").arg(element.at(column)));
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
