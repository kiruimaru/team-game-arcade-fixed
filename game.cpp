#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <limits>
#include <sstream>
#include <string>

int hp = 100;
int resources = 50;
int score = 0;
int turn = 1;

void addCapped(int &value, int amount) {
  value += std::min(amount, std::numeric_limits<int>::max() - value);
}

bool readChoice(int &choice) {
  std::string line;
  if (!std::getline(std::cin, line)) {
    return false;
  }
  std::istringstream input(line);
  char extra = '\0';
  if (!(input >> choice) || (input >> extra)) {
    choice = -1;
  }
  return true;
}

void printHUD() {
  std::cout << "\n================ [ХОД: " << turn << " | СЧЕТ: " << score
            << "] ================\n"
            << "Здоровье: " << hp << "/100 | Крышки: " << resources << "\n"
            << "--------------------------------------------------------\n";
}

bool riskOperation() {
  std::cout << "\nРейд пока недоступен.\n";
  return false;
}

bool recovery() {
  if (hp <= 0) {
    return false;
  }
  if (hp >= 100) {
    std::cout << "\nЗдоровье уже полностью восстановлено.\n";
    return false;
  }
  std::cout << "\n=== ЛАГЕРЬ ===\n"
            << "Здоровье: " << hp << "/100 | Крышки: " << resources << "\n"
            << "1. Перевязка - 10 крышек, +10 HP\n"
            << "2. Стимулятор - 25 крышек, +30 HP\n"
            << "0. Выйти\n"
            << "Выберите действие > ";
  int choice = 0;
  if (!readChoice(choice)) {
    return false;
  }
  int cost = 0;
  int heal = 0;
  switch (choice) {
  case 1:
    cost = 10;
    heal = 10;
    break;
  case 2:
    cost = 25;
    heal = 30;
    break;
  case 0:
    return false;
  default:
    std::cout << "\nНеизвестная команда!\n";
    return false;
  }
  if (resources < cost) {
    std::cout << "\nНедостаточно крышек для покупки.\n";
    return false;
  }
  const int restored = std::min(heal, 100 - hp);
  resources -= cost;
  hp += restored;
  std::cout << "\nЛечение успешно. Восстановлено HP: " << restored
            << "\nЗдоровье: " << hp << "/100 | Крышки: " << resources << "\n";
  return true;
}

bool gambleEvent() {
  std::cout << "\nКазино пока недоступно.\n";
  return false;
}

void finishTurn(bool actionCompleted) {
  if (hp > 0 && actionCompleted) {
    addCapped(turn, 1);
    addCapped(score, 10);
  }
}

int main() {
  std::srand(static_cast<unsigned int>(std::time(nullptr)));
  bool surrendered = false;
  std::cout << ">>> FALLOUT: РЕЙД ЗА РЕКОРДОМ <<<\n";

  while (hp > 0 && !surrendered) {
    printHUD();
    std::cout << "1. Рейд в Пустошь (награда или урон)\n"
              << "2. Лагерь (лечение за крышки)\n"
              << "3. Казино Нью-Вегаса (ставка 20%)\n"
              << "0. Завершить и зафиксировать счет\n"
              << "Выберите действие > ";
    int choice = 0;
    if (!readChoice(choice)) {
      break;
    }
    bool actionCompleted = false;
    switch (choice) {
    case 1:
      actionCompleted = riskOperation();
      break;
    case 2:
      actionCompleted = recovery();
      break;
    case 3:
      actionCompleted = gambleEvent();
      break;
    case 0:
      surrendered = true;
      break;
    default:
      std::cout << "\nНеизвестная команда!\n";
      break;
    }
    finishTurn(actionCompleted);
  }
  if (hp <= 0) {
    std::cout << "\nГерой погиб в Пустоши.\n";
  }
  std::cout << "\nИГРА ОКОНЧЕНА. Ваш итоговый рекорд: " << score << " очков!\n";
  return 0;
}
