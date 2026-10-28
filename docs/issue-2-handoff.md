# PR разработчика 2: reyvii

Задача: https://github.com/kiruimaru/team-game-arcade-fixed/issues/2

Ветка: `feat/issue-2-economy-heal`. Рецензент: **Blypik**.

Исходный вклад reyvii: `recovery()` в ветке `feat/issue-2-economy-heal`
репозитория https://github.com/kiruimaru/team-game-arcade.
Адаптация восстановлена владельцем, исходный автор указан в Co-authored-by.

## Что нажать reyvii

1. Принять приглашение в целевой репозиторий под аккаунтом reyvii.
2. Открыть https://github.com/kiruimaru/team-game-arcade-fixed/compare/main...feat/issue-2-economy-heal?expand=1.
3. Проверить base: `main`, compare: `feat/issue-2-economy-heal`.
4. Вставить заголовок и описание ниже, нажать Create pull request.
5. Справа в Reviewers выбрать Blypik.

Не создавать PR от аккаунта kiruimaru вместо reyvii: по ТЗ автор и
рецензент должны быть разными участниками кольца.

## Заголовок PR

```text
feat: restore safe camp healing
```

## Описание PR

```text
Closes #2

Восстановлена моя механика recovery() из исходного проекта:
- перевязка: 10 крышек за 10 HP; стимулятор: 25 крышек за 30 HP;
- здоровье не выше 100, покупка только при достаточных средствах;
- полное здоровье, смерть, отмена и неверный ввод не дают бонус хода;
- сообщение показывает фактически восстановленное здоровье;
- игровой текст адаптирован под Fallout.

Проверки: make test; tests/heal_tests.cpp, 15 сценариев.
Код восстановления опубликован владельцем с сохранением моего соавторства.
Рецензент по кольцу: @Blypik.
```

## Проверка для Blypik

Из локального клона, при отсутствии незакоммиченных изменений:

```bash
git fetch origin
git switch --detach origin/feat/issue-2-economy-heal
make test
g++ -std=c++17 -Wall -Wextra -Wpedantic -Werror -fsanitize=undefined -fno-sanitize-recover=all tests/heal_tests.cpp -o build/heal-tests
./build/heal-tests
```

В независимой ветке риска еще нет: обычная игра начинает со 100 HP,
поэтому покупка будет отклонена. Тесты специально выставляют поврежденное
состояние и проверяют лечение, нехватку денег, отмену, EOF и неверный ввод.
После объединения веток лечение можно проверить после неудачного рейда.

Исходник сообщал номинальное лечение вместо фактического: при 95 HP
покупка на 30 HP сообщала +30, хотя здоровье вырастало только на 5.
Это уже исправлено. Проверить, нет ли других настоящих дефектов.
Если дефект найден: Files changed -> "+" у строки -> Start a review ->
описание воспроизведения -> Request changes. После исправления повторить
тесты, Resolve conversation и Approve. Не отправлять фиктивное замечание:
без настоящего Request changes соответствующий пункт ТЗ остается открыт.
