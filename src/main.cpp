#include "Client.h"
#include "SalesRep.h"

#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>

using namespace std;

int main() {
    //Client Read In
    //vector<Client> Client::clients;
    try
    {
        ifstream clientFile;
        clientFile.open("./Clients.csv");
        if(clientFile.is_open()) {
            string line;
            while(getline(clientFile, line)) {
                stringstream ss(line);
                int id;
                string firstName, lastName, streetAddress1, streetAddress2, city, state, zipCode;
                ss >> id >> firstName >> lastName >> streetAddress1 >> streetAddress2 >> city >> state >> zipCode;

                Client newClient(id, firstName, lastName, streetAddress1, streetAddress2, city, state, zipCode);
                //clients.push_back(newClient);
                Client::AddClient(newClient);
            }
            clientFile.close();
        } else {
            cout << "Could not open clients" << endl;
        }//throw runtime_error("Could not open clients");
    } catch (char const *ex) {
        cout << ex << endl;
    }

    vector<Client> clients = Client::GetAll();
    for(int i = 0; i < clients.size(); i++) {
        //cout << clients.at(i).getType() << endl;
        Client c = clients.at(i);
        cout << c.getFullName() << " - " << c.getShortAddress() << endl;
    }

    return 0;
}