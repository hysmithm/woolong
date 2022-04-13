#include "Client.h"

#include <string>
#include <vector>
#include <map>
#include <fstream>
#include <iostream>
#include <sstream>

using namespace std;

const string Client::FILENAME = "Clients.csv";
vector<Client> Client::clients;
map<int, int> Client::client_index; //<id, vector_pos>
int Client::auto_increment = 1; //next highest id

//Static Functions
vector<Client> Client::GetAll() {
    return clients;
}

Client Client::Get(int id) {
    auto result = client_index.find(id);
    return clients.at(result->second);
}

void Client::AddClient(string fn, string ln, string sa1, string sa2, string cty, string st, string zc) {
    int c_pos = clients.size();

    //Make Client
    Client c(auto_increment, fn, ln, sa1, sa2, cty, st, zc);
    clients.push_back(c);

    //Auto Increment the Id
    auto_increment++;

    client_index.insert(pair<int, int>(c.id, c_pos));
}

void Client::UpdateClient(Client c) {
    //c = Client::Get(c.id);
    int c_pos = client_index.find(c.id)->second;
    clients.at(c_pos) = c;
}

void Client::Load() {
    try
    {
        ifstream clientFile;
        clientFile.open("./" + FILENAME);
        if(clientFile.is_open()) {
            string line;
            while(getline(clientFile, line)) { //Comma-delimited file
                cout << line << endl;
                stringstream ss(line);
                string word;
                while(getline(ss, word, ',')) {
                    
                }
                int id;
                string firstName, lastName, streetAddress1, streetAddress2, city, state, zipCode;
                ss >> id >> firstName >> lastName >> streetAddress1 >> streetAddress2 >> city >> state >> zipCode;

                Client c(id, firstName, lastName, streetAddress1, streetAddress2, city, state, zipCode);
                clients.push_back(c);

                //Insure that auto increment counter starts higher than anything in the CSV file
                if(c.id >= auto_increment) auto_increment = c.id + 1;
            }
            clientFile.close();
        } else {
            cout << "Could not open clients" << endl;
        }//throw runtime_error("Could not open clients");
    } catch (char const *ex) {
        cout << ex << endl;
    }
}

void Client::Save() {
    try
    {
        ofstream clientFile("./" + FILENAME, ios::trunc); //Truncate to Overwrite
        if(clientFile.is_open()) {
            for(int i = 0; i < clients.size(); i++) {
                //Write each client
                Client c = clients.at(i);

                //Columns
                clientFile << c.id << "," << c.firstName << "," << c.lastName << ","
                    << c.streetAddress1 << "," << c.streetAddress2 << ","
                    << c.city << "," << c.state << "," << c.zipCode << endl;
            }
            clientFile.close();
        } else {
            cout << "Could not write to Clients" << endl;
        }
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    
}