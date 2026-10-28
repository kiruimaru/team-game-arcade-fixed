# PR разработчика 3: Blypik

Задача: https://github.com/kiruimaru/team-game-arcade-fixed/issues/3

Ветка: `feat/issue-3-gamble-event`. Рецензент: **kiruimaru**.

Исходный вклад Blypik: `gambleEvent()` в ветке `feat/issue-3-gamble-event`
репозитория https://github.com/kiruimaru/team-game-arcade.
Адаптация восстановлена владельцем, исходный автор указан в Co-authored-by.

## Что нажать Blypik

1. Принять приглашение в целевой репозиторий под аккаунтом Blypik.
2. Открыть https://github.com/kiruimaru/team-game-arcade-fixed/compare/main...feat/issue-3-gamble-event?expand=1.
3. Проверить base: `main`, compare: `feat/issue-3-gamble-event`.
4. Вставить заголовок и описание ниже, нажать Create pull request.
5. Справа в Reviewers выбрать kiruimaru.

## Заголовок PR

```text
feat: restore New Vegas gamble event
```

## Описание PR

```text
Closes #3

Восстановлена моя механика gambleEvent() из исходного проекта:
- ставка 20% крышек, округление вниз, минимум 5 крышек для участия;
- 50% шанс выплаты двух ставок и награды 100 очков;
- при roll == 0 джекпот дает 500 очков вместо 100;
- при roll == 99 проклятие наносит 30 HP;
- без средств и после смерти действие не выполняется;
- нет переполнения при расчете ставки и начислении наград.

Исправлены ошибки исходной интеграции: необъявленная actionCompleted,
область видимости surrendered, бонус за невыполненные действия.
Проверки: make test; tests/gamble_tests.cpp на 1000 seed и границах.
Код восстановления опубликован владельцем с сохранением моего соавторства.
Рецензент по кольцу: @kiruimaru.
```

## Проверка для kiruimaru

Из локального клона, при отсутствии незакоммиченных изменений:

```bash
git fetch origin
git switch --detach origin/feat/issue-3-gamble-event
make test
g++ -std=c++17 -Wall -Wextra -Wpedantic -Werror -fsanitize=undefined -fno-sanitize-recover=all tests/gamble_tests.cpp -o build/gamble-tests
./build/gamble-tests
./game
```

Для ручной проверки выбрать `3` несколько раз и завершить через `0`.
Тесты дополнительно проверяют 0–4 крышки, джекпот, проклятие,
смертельное проклятие и максимальные значения int.

Исторические проблемы: `actionCompleted` не объявлена, `surrendered`
используется за пределами области видимости, `resources * 20` может
переполнить int. Эти дефекты уже исправлены. Проверить исправления и
поискать другие настоящие ошибки.
Если ошибка найдена: Files changed -> "+" у строки -> Start a review ->
описание воспроизведения -> Request changes. После исправления повторить
проверку, Resolve conversation и Approve. Не придумывать дефект ради
Request changes; без настоящего цикла этот пункт ТЗ остается открытым.
