#include "Guests.pb.h"  // Сгенерированный файл (лежит в build/)
#include <iostream>
#include <locale>


int main()
{
	GOOGLE_PROTOBUF_VERIFY_VERSION;
	setlocale(LC_ALL, "Russian");
	
	birthday::Guest guest;  // birthday — это package из .proto
	guest.set_name("Михаил");
	guest.set_age(30);
	
    guest.add_gifts("Книга");
    guest.add_gifts("Часы");
    guest.add_gifts("Кошелёк");
	
	if (!guest.has_email()) {
      std::cout << "Email не задан\n";
    }
	
	birthday::Address addr;
    addr.set_city("Уфа");
    addr.set_street("Ленина");
    addr.set_homenumber(42);
	
	// Устанавливаем адрес в guest
    *guest.mutable_address() = addr;
	
	if (guest.has_email()) {
		std::cout << "Email: " << guest.email() << "\n";
    }
    
    // Адрес
    if (guest.has_address()) {
        std::cout << "Адрес: " << guest.address().city() << ", " 
                  << guest.address().street() << ", д. " 
                  << guest.address().homenumber() << "\n";
    }
	
    std::cout << "\nПодарки:\n";
    for (int i = 0; i < guest.gifts_size(); ++i) {
        std::cout << "  " << i + 1 << ". " << guest.gifts(i) << "\n";
    }
	google::protobuf::ShutdownProtobufLibrary();
}