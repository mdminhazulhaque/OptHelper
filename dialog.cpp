#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    ui->items->setPlainText("Write one item per line\n"
                            "For example,\n"
                            "lumia\n"
                            "iphone\n"
                            "android\n"
                            "blackberry\n"
                            "tizen\n");

    ui->result->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    connect(ui->btnOpt, SIGNAL(clicked()), this, SLOT(selectItem()));
    connect(ui->btnExit, SIGNAL(clicked()), this, SLOT(close()));

    setWindowTitle("OptHelper");
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::selectItem()
{
    QStringList items = ui->items->toPlainText().trimmed().split("\n");

    QMap<QString, uint> result;

    for(int i=0; i<items.size(); i++)
    {
        result.insert(items.at(i), 0);
    }

    for(uint i=0; i<1000; i++)
    {
        srand(time(NULL) + rand() % 1000);

        int vote = rand() % items.size();

        result[items.at(vote)]++;
    }

    ui->result->clear();
    QStringList headers;
    headers << "Item" << "Vote";
    ui->result->setHorizontalHeaderLabels(headers);
    ui->result->setRowCount(items.size());

    for(int i=0; i<items.size(); i++)
    {
        QTableWidgetItem *item = new QTableWidgetItem(items.at(i));
        ui->result->setItem(i, 0, item);

        QProgressBar *progress = new QProgressBar;
        progress->setMaximum(1000);
        progress->setValue(result[items.at(i)]);
        ui->result->setCellWidget(i, 1, progress);
    }
}
