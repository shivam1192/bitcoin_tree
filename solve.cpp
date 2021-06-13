#include<bits/stdc++.h>
using namespace std;

struct Node{
  string id;
  int fees;
  int weight;
  vector<string> parentid; 
};
int main(){
    fstream fin;
    fin.open("mempool.csv");
    if (!fin.good()) throw "I/O error"; 
    string temp;
    vector<Node> store;
    fin>>temp;
    while (fin >> temp) {
        stringstream s(temp);
        Node node;
        int count = 0;
        string word;
        while (getline(s, word,',')) {
            if(count == 0){
                node.id = word;
            }else if(count == 1){
                node.fees = stoi(word);
            }else if(count == 2){
                node.weight = stoi(word);
            }else{
                node.parentid.push_back(word);
            }
            count++;
        }
        store.push_back(node);
    }
    for(auto i:store){
        cout<<i.id<<"\n";
    }
}
