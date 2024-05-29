# Дизайн документ
### Контекст

Над цим проектом працювали [Сологуб Олександр](https://github.com/AlehandroUA) `(тімлід/розробник)`, [Високовський Олександр](https://github.com/v-jester) `(розробник)`, [Поночовний Антон](https://github.com/ToxicAli3n) `(розробник)`
### Цілі та нецілі
Наш проект - консольна гра Cапер. У функціонал нашої програми **входить**:
- можливість авторизації;
- таблиця лідерів;
- можливість налаштувати розміри поля;
- рівень складності;

Ми **не робили** фунціонал:
- взаємодії з базою даних;
- додаткових шифрувань для паролів;

Основною метою було **створити саму гру Сапер**, а не розвинуту систему авторизації.
### Підсистема
Ми розробляли проект на мові програмування С++. Структура програми має наступний вигляд:
![](https://github.com/AlehandroUA/Sapper/sheme.png)
### Авторизаційна підсистема
Наша система авторизації має наступний алгоритм:
- Користувач вводить свої логін
- Система перевіряє, чи не зайнятий логін
- Якщо логін не зайнято, система просить ввести пароль
- Якщо логін зайнято, система просить ввести або ж новий логін, або ж пароль
### Зберігання даних
Дані для нашого проекту зберігаються локально **у текстовому файлі**. Программа звертається до них коли ми **виводимо таблицю** лідерів, або ж коли **гру завершено**, і дані користувача вводяться у текстовий файл. Цей текстовий файл представляє собою імпровізовану базу даних.
### Інтерфейс програми
Наш інтерфейс було реалізовано через **вивід тексту**. Виводячи його певним чином ми створюємо **меню**. Користувач може взаємодіяти з чим меню, натискаючи клавіши `W` та `S`. Реалізація меню рівня складності та інших було за схожим принципом. **Різниця** лише є коли ми вводимо логін та пароль. Якщо їх було введено з помилками, то консоль **очищає** невірні данні, і ми повинні ввести їх знову. Меню допомоги з керуванням також доступне.
### Як запустити юніт тести?
Для того, що б запустити **юніт тести** вам потрібно буде встановити середовище розробки `Visual Studio 19` та відкрити файл `.sln`. Після цього на вкладці `"Тест"` натиснути кнопку `"Запустити усі тести"`. Після цього ви побачите результат виконання цих тестів.
### Як зібрати програму?
- Якщо ви бажаєте зібрати проект  **у Visual Studio**, то вам потрібно завантажити архів проекту, після чого розпакувати у зручне для вас місце. Потім, вам необхідно відкрити файл з розширенням  `.sln`. Після цього у вас відкриється  **Visual Studio**. Натискаєте  `F5`  та программа успішно збирається та запускається.
-   Якщо ж бажаєте зібрати проект  **у консолі**, то відкрийте у GitHub теку  `Sapper`  та завантажте  `Sapper.cpp`  файл.  **ВАЖЛИВО!**  Вам потрібно буде перед цим  **завантажити**  компілятор для  `С++`. Перенесіть файл у зручне для вас місце. Після цього вікриваєте термінал у папці з цим файлом, та вводите команду  `g++ Sapper.cpp -o output`. У теці з файлом у вас з'явиться  `.exe`  файл. Запускаєте його.
### Правила гри у сапер
1.  **Мета гри:**

    -   Метою гри є розкрити всі клітинки на ігровому полі, не спричинивши вибуху на міні.
2.  **Ігрове поле:**

    -   Гра відбувається на квадратному полі, розділеному на клітинки.
    -   Деякі клітинки містять міни, а інші - ні.
3.  **Правила:**

    -   Гравець може відкривати клітинки, натискаючи на них.
    -   Якщо клітина містить міну, гра закінчується поразкою.
    -   Якщо клітина не містить міни, вона показує кількість мін у сусідніх клітинах (від 0 до 8).
    -   Гравець може позначити клітину, де він вважає, що знаходиться міна, флажком.
    -   Якщо всі клітинки без мін відкриті, гра завершується перемогою.
4.  **Стратегія:**

    -   Гравці використовують логіку та інформацію про сусідні клітинки, щоб уникнути мін і відкрити якомога більше безпечних клітин.
5.  **Рівні складності:**

    -   Гра може мати різні рівні складності, включаючи розмір поля та кількість мін.