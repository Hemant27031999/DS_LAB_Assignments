#include "dictionary.h"
#include "ui_dictionary.h"

Dictionary::Dictionary(QWidget *parent) :
    QMainWindow(parent),
       ui(new Ui::Dictionary)
   {
       QString path = QDir::currentPath();

       QStringList list = path.split("/");
       QString Path = "";
       for(int i{0}; i < list.size()-1; i++) {
            Path += list[i] + "/";
       }

       qDebug() << Path;

       ui->setupUi(this);
       LoadData(Path + "Que1/L4_P1_input.csv");
       button = ui->pushButton;
       connect(button, SIGNAL(clicked()), this, SLOT(SearchMeaning()));
}


void Dictionary::LoadData(QString filename) {
    QFile file(filename);

    if(!file.open(QFile::ReadOnly | QFile::Text)) {
        qDebug() << "could not open file";
        return;
    }
    QTextStream in(&file);
    QString text;

    while((text = in.readLine()) != "") {
        QStringList query = text.split(",");
        QString second;
        for (int i = 1; i < query.size(); ++i){
                 second.append(query[i]);
                 if (i != query.size()-1)
                     second.append(", ");
        }
        trie.insert(query[0], second);
    }
}


Dictionary::~Dictionary()
{
    delete ui;
}

void Dictionary::SearchMeaning() {
    QString word = ui->textEdit->toPlainText();
    word = word.trimmed();
    ui->textEdit_2->clear();
    ui->textEdit_2->setText(trie.getMeaning(word));
}
