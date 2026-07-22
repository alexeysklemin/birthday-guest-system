#include "Guests.pb.h"  // Сгенерированный файл (лежит в build/)
#include <iostream>



int main()
{
	GOOGLE_PROTOBUF_VERIFY_VERSION;
	
	birthday::Guest guest;  // birthday — это package из .proto
	guest.set_name("Михаил");
	guest.set_age(30);
	guest.set_city("Уфа");
	
	std::cout << "Имя: " << guest.name() << "\n";
	std::cout << "Возраст: " << guest.age() << "\n";
	std::cout << "Город: " << guest.city() << "\n";
	
	google::protobuf::ShutdownProtobufLibrary();
}