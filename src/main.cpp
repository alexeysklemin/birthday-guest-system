#include "Guests.pb.h"  // Сгенерированный файл (лежит в build/)


#include <iostream>
#include <windows.h>
#include <fstream>
#include "Guests.pb.h"

int main()
{
    // Настраиваем консоль на UTF-8
	SetConsoleOutputCP(1251);  // Windows-1251
	SetConsoleCP(1251);
		
    GOOGLE_PROTOBUF_VERIFY_VERSION;
    
    // Создаем гостя
    birthday::Guest guest;
    guest.set_name("Михаил");
    guest.set_age(30);
    guest.set_status(birthday::GuestStatus::CONFIRMED);
    
    // === MAP: Статистика подарков ===
    std::cout << "=== Заполняем статистику подарков (map) ===\n";
    (*guest.mutable_gifts_count())["Книга"] = 3;
    (*guest.mutable_gifts_count())["Часы"] = 1;
    (*guest.mutable_gifts_count())["Кошелёк"] = 2;
    
    std::cout << "Статистика:\n";
    for (const auto& pair : guest.gifts_count()) {
        std::cout << "  " << pair.first << ": " << pair.second << " шт.\n";
    }
    
    // === REPEATED: Детали каждого подарка ===
    std::cout << "\n=== Заполняем детали подарков (repeated Gift) ===\n";
    
    // Подарок 1: Книга от Ивана с запиской
    birthday::Gift* gift1 = guest.add_gifts();
    gift1->set_name("Книга");
    gift1->set_from_who("Иван");
    gift1->set_note("Читай с удовольствием!");
    
    // Подарок 2: Часы от Марии с запиской
    birthday::Gift* gift2 = guest.add_gifts();
    gift2->set_name("Часы");
    gift2->set_from_who("Мария");
    gift2->set_note("Чтобы не опаздывал ;)");
    
    // Подарок 3: Книга от Петра БЕЗ записки (optional!)
    birthday::Gift* gift3 = guest.add_gifts();
    gift3->set_name("Книга");
    gift3->set_from_who("Пётр");
    // note НЕ задан - это optional поле
    
    // Подарок 4: Кошелёк от Анны с запиской
    birthday::Gift* gift4 = guest.add_gifts();
    gift4->set_name("Кошелёк");
    gift4->set_from_who("Анна");
    gift4->set_note("Пусть деньги водятся!");
    
    // === Вывод деталей ===
    std::cout << "\n=== Детали подарков ===\n";
    for (int i = 0; i < guest.gifts_size(); ++i) {
        const auto& g = guest.gifts(i);
        std::cout << "  " << i + 1 << ". " << g.name() 
                  << " от " << g.from_who();
        
        // Проверяем, есть ли записка (optional)
        if (g.has_note()) {
            std::cout << " | Записка: \"" << g.note() << "\"";
        } else {
            std::cout << " | (без записки)";
        }
        std::cout << "\n";
    }
    
    // === Сравнение map и repeated ===
    std::cout << "\n=== Сравнение ===\n";
    std::cout << "Всего подарков (по map): ";
    int total_by_map = 0;
    for (const auto& pair : guest.gifts_count()) {
        total_by_map += pair.second;
    }
    std::cout << total_by_map << " шт.\n";
    
    std::cout << "Всего подарков (по repeated): " << guest.gifts_size() << " шт.\n";
    
    // === Работа с Address ===
    birthday::Address addr;
    addr.set_city("Уфа");
    addr.set_street("Ленина");
    addr.set_homenumber(42);
    *guest.mutable_address() = addr;
    
    // === Работа с oneof (контакт) ===
    guest.set_email("mikhail@example.com");
    
    // === Работа с optional (пожелания по напиткам) ===
    guest.set_drink_preference("Только шампанское");
    
    // === Финальный вывод ===
    std::cout << "\n=== Итоговая карточка гостя ===\n";
    std::cout << "Имя: " << guest.name() << "\n";
    std::cout << "Возраст: " << guest.age() << "\n";
    std::cout << "Статус: ";
    if (guest.status() == birthday::GuestStatus::CONFIRMED) {
        std::cout << "Подтвердил\n";
    } else if (guest.status() == birthday::GuestStatus::INVITED) {
        std::cout << "Приглашён\n";
    } else {
        std::cout << "Отказался\n";
    }
    
    std::cout << "Адрес: " << guest.address().city() 
              << ", ул. " << guest.address().street() 
              << ", д. " << guest.address().homenumber() << "\n";
    
    // Контакт (oneof)
    if (guest.has_email()) {
        std::cout << "Контакт (Email): " << guest.email() << "\n";
    } else if (guest.has_phone()) {
        std::cout << "Контакт (Телефон): " << guest.phone() << "\n";
    }
    
    // Пожелания по напиткам (optional)
    if (guest.has_drink_preference()) {
        std::cout << "Пожелания по напиткам: " << guest.drink_preference() << "\n";
    } else {
        std::cout << "Пожелания по напиткам: не указаны\n";
    }
    
	std::cout << "\n\n\n!!! ЭТО НОВЫЙ КОД РАБОТАЕТ !!!\n";
	std::cout << "=== НОВЫЙ СПИСОК ГОСТЕЙ ===\n";
	// ==========================================
	// Создаём список гостей (НОВЫЙ КОД)
	// ==========================================

	birthday::GuestList guest_list;
	birthday::Guest* guest_new;  // ← меняем имя
	birthday::Gift* gift_new;    // ← меняем имя

	// --- Гость 1: Михаил ---
	guest_new = guest_list.add_guests();
	guest_new->set_name("Михаил");
	guest_new->set_age(43);
	guest_new->set_status(birthday::GuestStatus::CONFIRMED);
	guest_new->set_email("mikhail@gmail.com");
	guest_new->set_drink_preference("Шампанское");

	birthday::Address* addr_new1 = guest_new->mutable_address();  // ← меняем имя
	addr_new1->set_city("Уфа");
	addr_new1->set_street("Ленина");
	addr_new1->set_homenumber(42);

	(*guest_new->mutable_gifts_count())["Книга"] = 1;
	(*guest_new->mutable_gifts_count())["Часы"] = 1;

	gift_new = guest_new->add_gifts();
	gift_new->set_name("Книга");
	gift_new->set_from_who("Михаил");
	gift_new->set_note("Читай с наслаждением!");

	gift_new = guest_new->add_gifts();
	gift_new->set_name("Часы");
	gift_new->set_from_who("Михаил");
	// note не задаём

	// --- Гость 2: Ольга ---
	guest_new = guest_list.add_guests();
	guest_new->set_name("Ольга");
	guest_new->set_age(49);
	guest_new->set_status(birthday::GuestStatus::CONFIRMED);
	guest_new->set_phone("+79033283161");
	guest_new->set_drink_preference("Белое");

	birthday::Address* addr_new2 = guest_new->mutable_address();  // ← меняем имя
	addr_new2->set_city("Саратов");
	addr_new2->set_street("Ленина");
	addr_new2->set_homenumber(42);

	(*guest_new->mutable_gifts_count())["Картина"] = 1;

	gift_new = guest_new->add_gifts();
	gift_new->set_name("Картина");
	gift_new->set_from_who("Ольга");
	gift_new->set_note("Смотри с наслаждением!");

	// --- Гость 3: Татьяна ---
	guest_new = guest_list.add_guests();
	guest_new->set_name("Татьяна");
	guest_new->set_age(51);
	guest_new->set_status(birthday::GuestStatus::CONFIRMED);
	guest_new->set_phone("+79035383161");
	guest_new->set_drink_preference("Водка");

	birthday::Address* addr_new3 = guest_new->mutable_address();  // ← меняем имя
	addr_new3->set_city("Саратов");
	addr_new3->set_street("Пичугина");
	addr_new3->set_homenumber(42);

	(*guest_new->mutable_gifts_count())["Кошка"] = 1;

	gift_new = guest_new->add_gifts();
	gift_new->set_name("Кошка");
	gift_new->set_from_who("Татьяна");
	// note не задаём

	// ==========================================
	// ВЫВОД СПИСКА ГОСТЕЙ (НОВЫЙ КОД)
	// ==========================================

	std::cout << "\n=== НОВЫЙ СПИСОК ГОСТЕЙ ===\n";
	std::cout << "Всего гостей: " << guest_list.guests_size() << "\n\n";

	for (int i = 0; i < guest_list.guests_size(); ++i) {
		std::cout << "DEBUG: Размер списка = " << guest_list.guests_size() << std::endl;
		const birthday::Guest& guest_current = guest_list.guests(i);  // ← другое имя
		
		std::cout << "--- Гость " << i + 1 << " ---\n";
		std::cout << "Имя: " << guest_current.name() << "\n";
		std::cout << "Возраст: " << guest_current.age() << "\n";
		
		// Статус
		std::cout << "Статус: ";
		if (guest_current.status() == birthday::GuestStatus::CONFIRMED) {
			std::cout << "Подтвердил\n";
		} else if (guest_current.status() == birthday::GuestStatus::INVITED) {
			std::cout << "Приглашён\n";
		} else {
			std::cout << "Отказался\n";
		}
		
		// Контакт (oneof)
		std::cout << "Контакт: ";
		if (guest_current.has_email()) {
			std::cout << "email: " << guest_current.email() << "\n";
		} else if (guest_current.has_phone()) {
			std::cout << "телефон: " << guest_current.phone() << "\n";
		} else {
			std::cout << "не указан\n";
		}
		
		// Адрес
		if (guest_current.has_address()) {
			std::cout << "Адрес: " << guest_current.address().city() << ", "
					  << guest_current.address().street() << ", д. "
					  << guest_current.address().homenumber() << "\n";
		}
		
		// Пожелания по напиткам (optional)
		if (guest_current.has_drink_preference()) {
			std::cout << "Пожелания по напиткам: " << guest_current.drink_preference() << "\n";
		} else {
			std::cout << "Пожелания по напиткам: не указаны\n";
		}
		
		// Подарки (map)
		if (guest_current.gifts_count_size() > 0) {
			std::cout << "Статистика подарков:\n";
			for (const auto& pair : guest_current.gifts_count()) {
				std::cout << "  " << pair.first << ": " << pair.second << " шт.\n";
			}
		}
		
		// Подарки (repeated)
		if (guest_current.gifts_size() > 0) {
			std::cout << "Детали подарков:\n";
			for (int j = 0; j < guest_current.gifts_size(); ++j) {
				const auto& gift_current = guest_current.gifts(j);  // ← другое имя
				std::cout << "  " << j + 1 << ". " << gift_current.name()
						  << " от " << gift_current.from_who();
				if (gift_current.has_note()) {
					std::cout << " | Записка: " << gift_current.note();
				}
				std::cout << "\n";
			}
		}
		std::cout << "\n";
	}
	std::ofstream out2;
	out2.open("list.bin", std::ios::binary);
	guest_list.SerializeToOstream(&out2);
	out2.close();
	
	guest_list.Clear();
	std::ifstream in2;
	in2.open("list.bin", std::ios::binary);
	guest_list.ParseFromIstream(&in2);
	in2.close();
	
    google::protobuf::ShutdownProtobufLibrary();
	std::cout << "\n\nНажми Enter для выхода...";
	std::cin.get();
    return 0;
}