#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>

Messenger::Messenger() {}

void Messenger::addUser(const std::string& username) {
    for (const auto& user : users) {
        if (user.username == username) {
            return;
        }
    }
    users.push_back({username, false});
}

void Messenger::addMessage(const std::string& sender, const std::string& content) {
    messages.push_back({sender, content});
}

void Messenger::banUser(const std::string& username) {
    for (auto& user : users) {
        if (user.username == username) {
            user.isBanned = true;
            break;
        }
    }
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->sendButton, &QPushButton::clicked, this, &MainWindow::on_sendButton_clicked);
    connect(ui->loginButton, &QPushButton::clicked, this, &MainWindow::on_loginButton_clicked);
    connect(ui->userListWidget, &QListWidget::itemClicked, this, &MainWindow::on_userListWidget_itemClicked);
    updateUserList();
    updateMessageList();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::updateUserList() {
    ui->userListWidget->clear();
    for (const auto& user : messenger.users) {
        ui->userListWidget->addItem(QString::fromStdString(user.username));
    }
}

void MainWindow::updateMessageList() {
    ui->messageListWidget->clear();
    for (const auto& message : messenger.messages) {
        ui->messageListWidget->addItem(QString::fromStdString(message.sender + ": " + message.content));
    }
}

void MainWindow::on_loginButton_clicked() {
    QString username = ui->usernameLineEdit->text();
    if (!username.isEmpty()) {
        messenger.addUser(username.toStdString());
        updateUserList();
        ui->usernameLineEdit->clear();
        QMessageBox::information(this, "Login", "User " + username + " has successfully logged in.");
    } else {
        QMessageBox::warning(this, "Login Error", "Please enter a username.");
    }
}

void MainWindow::on_sendButton_clicked() {
    QString messageText = ui->messageLineEdit->text();
    if (!messageText.isEmpty() && !currentUser.empty()) {
        messenger.addMessage(currentUser, messageText.toStdString());
        updateMessageList();
        ui->messageLineEdit->clear();
    } else {
        QMessageBox::warning(this, "Message Error", "Please select a user and enter a message.");
    }
}

void MainWindow::on_banButton_clicked() {
    QListWidgetItem* currentItem = ui->userListWidget->currentItem();
    if (currentItem) {
        QString selectedUser = currentItem->text();
        messenger.banUser(selectedUser.toStdString());
        QMessageBox::information(this, "User Banned", selectedUser + " has been banned.");
        updateUserList();
    } else {
        QMessageBox::warning(this, "No Selection", "Please select a user to ban.");
    }
}

void MainWindow::on_userListWidget_itemClicked(QListWidgetItem *item) {
    if (item) {
        currentUser = item->text().toStdString();
        QMessageBox::information(this, "Active User", "Active user: " + QString::fromStdString(currentUser));
    }
}
