#include<bits/stdc++.h>
using namespace std;

struct Node{
  string id;
  int fees;
  int weight;
  vector<string> parentid; 
};
bool comp(Node &A,Node &B){
    if(A.parentid.size()<B.parentid.size()) return true;
    return false;
}
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
                stringstream l(word);
                string p_start;
                while(getline(l,p_start,';')){
                    node.parentid.push_back(p_start);   
                }
            }
            count++;
        }
        store.push_back(node);
    }
    
    sort(store.begin(),store.end(),comp);
    for(auto i:store){
        cout<<i.parentid.size()<<"\n";
    }
}
