#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QListWidgetItem>
#include <vector>
#include <string>

namespace Ui {
class MainWindow;
}

class Messenger {
public:
    struct User {
        std::string username;
        bool isBanned;
    };

    struct Message {
        std::string sender;
        std::string content;
    };

    Messenger();
    void addUser(const std::string& username);
    void addMessage(const std::string& sender, const std::string& content);
    void banUser(const std::string& username);

    std::vector<User> users;
    std::vector<Message> messages;
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_loginButton_clicked();
    void on_sendButton_clicked();
    void on_banButton_clicked();
    void on_userListWidget_itemClicked(QListWidgetItem *item);
private:
    Ui::MainWindow *ui;
    Messenger messenger;
    std::string currentUser;
    void updateUserList();
    void updateMessageList();
};

#endif // MAINWINDOW_H
