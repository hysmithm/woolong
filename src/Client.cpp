#include "Client.h"

#include <string>
#include <vector>
#include <map>

using namespace std;

vector<Client> Client::GetAll() {
    return clients;
}

Client Client::Get(int id) {
    auto result = client_index.find(id);
    return clients.at(result->second);
}