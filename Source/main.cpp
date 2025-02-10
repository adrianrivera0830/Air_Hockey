


#include <iostream>
#include "../Headers/NetworkManager.h"
void ShowMenu() {

    std::cout << "INGRESA LA OPCION:\n";
    std::cout << "Host(1)\n";
    std::cout << "Join(2)\n";
    int opcion;
    std::cin >> opcion;

    NetworkManager network_manager;
    if (opcion == 1) {
        network_manager.Host();
    } else if (opcion == 2){
        std::cout << "Ingresa ip: ";
        std::string ip;
        std::cin >> ip;
        std::cout << "Ingresa port: ";
        int port;
        std::cin >> port;
        network_manager.Join(ip,port);
    }


}

int main(int argc, char *argv[]) {

    ShowMenu();






    return 0;
}
