Это скрипт для оценки качества сервиса, он работает следующим образом:
1) читает данные и группирует их по HitLogID
2) для каждой группы делает 3 запроса: очистить базу, обновить векторы баннеров и достать топ для данного хита
3) затем считает на сколько этот топ перескается с топом по таргету

Установка зависимостей: `pip install requirements.txt`

Запуск: `python main.py --data_path path_to_data --host localhost --port 8080`
