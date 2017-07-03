#include "mainwidget.h"
#include "ui_mainwidget.h"

MainWidget::MainWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainWidget)
{
    ui->setupUi(this);
    ui->usernameLineEdit->setPlaceholderText("Username");
    ui->computerNameLineEdit->setPlaceholderText("Computer Name");
}

MainWidget::~MainWidget()
{
    delete ui;
}

void MainWidget::messageRecieved(QString message) {
    ui->outputLabel->setText(ui->outputLabel->text().append(message + "\n"));
}

void MainWidget::on_connectButton_clicked()
{
    QString username = ui->usernameLineEdit->text();
    QString computerName = ui->computerNameLineEdit->text();

    emit connectButtonClicked(username, computerName);
}
