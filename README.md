Проект — простое чат-приложение с графическим интерфейсом на Qt и C++, позволяющее пользователям логиниться, отправлять сообщения и банить других пользователей. Основные компоненты:

Messenger (класс):

addUser() — добавление пользователя.
addMessage() — добавление сообщения.
banUser() — бан пользователя.
Управляет списками пользователей и сообщений.
MainWindow (класс):

Обрабатывает графический интерфейс и взаимодействие с пользователями.
on_loginButton_clicked() — логин пользователя.
on_sendButton_clicked() — отправка сообщений.
on_banButton_clicked() — бан выбранного пользователя.
updateUserList() и updateMessageList() — обновление списка пользователей и сообщений.
Функциональность:
Логин и отображение пользователей.
Отправка сообщений в чат.
Бан пользователей с обновлением интерфейса.
