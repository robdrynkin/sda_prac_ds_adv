Точка входа находится в `src/main.cpp`. Там создается сервер с 3 эндпоинтами
* `/update_vectors` - принимает список баннеров(с фичами) и пересчитывает для них векторы
* `/get_banners` - по фичам хита возвращает топ релевантных баннеров
* `/reset` - сбрасывает текущее состояние сервиса (удаляет все предпосчитанные векторы баннеров)

Более детально ознакомиться с апи вы можете либо прочитав код `src/service/server.h`, либо посмотрев примеры отправки запросов в `../client`

Весь код парсинга, обработки запросов написан за вас, вам нужно только реализовать интерфейсы `IBannerModel` в `src/models/banner.h` и `IHitModel` в `src/models/hit.h`.
В качестве примеров там уже реализованы dummy модели, которые возвращают случайные векторы для каждого баннера `CreateDummyBannerModel` и хита `CreateDummyHitModel`.  
Для реализации поиска ближайших векторов баннера к вектору хита можете воспользоваться обычным линейным поиском, как в `TDummyBannerModel`, но за более эффективные реализации можно получить доп баллы.


Вам может пригодиться справочник по плюсовому апи торча https://pytorch.org/cppdocs/ и туториал по экспорту моделей в плюсы https://pytorch.org/tutorials/advanced/cpp_export.html  
Также некоторые примеры можно найти в `tests/torch_example.cpp`


Чтобы запустить сервис в докер контейнере выполните в этой директории команду
`docker build -t example-app . && docker run -d -p 8080:8080 example-app`
