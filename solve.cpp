#include<bits/stdc++.h>
typedef long long ll;
using namespace std;

// structure node
struct Node{
  string id;
  ll fees;
  ll weight;
  vector<string> parentid; 
  bool check;
};

// vector store all the id of the selected transaction
vector<string> answer; 

// our utility function for sorting
bool comp(Node &A,Node &B){
    if(A.parentid.size()<B.parentid.size()) return true;
    return false;
}

// our utility function for checking whether the parent id of the current Node is visited or not
bool checkForAllParent(vector<string> &parentid,vector<Node> &store){
    for(auto i:parentid){
        for(auto j:store){
            if(i == j.id){
                if(j.check == false) return false;
            }
        }
    }
    return true;
}

// our dp function
int performDp(vector<Node> &store, ll weight){
    ll dp[store.size()+1][weight+1];
    ll n = store.size();
    ll m = weight;
    for(ll i=0;i<=store.size();i++){
        for(ll j=0;j<=weight;j++){
            if( i==0 || j==0){
                dp[i][j] = 0;
            }
        }
    }
    for(ll i=1;i<=store.size();i++){
        for(ll j=1;j<=weight;j++){
            if(store[i-1].weight <= weight){
                if(store[i-1].fees + dp[i-1][j-store[i-1].weight]> dp[i-1][j]){
                    store[i-1].check = true;
                    dp[i][j] = store[i-1].fees + dp[i-1][j-store[i-1].weight];
                  }
            }
            else if(store[i-1].weight > weight || checkForAllParent(store[i-1].parentid,store)){
                dp[i][j] = dp[i-1][j];
            }
        }
    }
    ll result = dp[n][m];
    int w = weight;
    for(ll i=n;i>0 && result>0;i--){
        if(result == dp[i-1][w]){
            continue;
        }else{
            answer.push_back(store[i-1].id);
            result = result  - store[i-1].fees;
            w = w - store[i-1].weight;
        }
    }   
    return dp[store.size()][weight];
}

//utility function for writing data in the text file
void writeData(string file_name){
    ofstream fout;
    fout.open(file_name);
    if( !fout ) { 
      cerr << "Error: file could not be opened" << endl;
      exit(1);
   }
   for(auto i: answer){
       fout<<i<<"\n";
   }
   fout.close();
}

//our main function
int main(){
    //reading data and storing in the vector of type struct Node
    fstream fin;
    fin.open("mempool.csv");
    if (!fin.good()) throw "I/O error"; 
    string temp;
    vector<Node> store;
    fin>>temp;
    while (fin >> temp) {
        stringstream s(temp);
        Node node;
        ll count = 0;
        string word;
        node.check = false;
        while (getline(s, word,',')) {
            if(count == 0){
                // assigning id of the node
                node.id = word;
            }else if(count == 1){
                // assigning fees of the node
                node.fees = stoi(word);
            }else if(count == 2){
                // assigning weight of the node
                node.weight = stoi(word);
            }else{
                // pushing all the parent id
                stringstream l(word);
                string p_start;
                while(getline(l,p_start,';')){
                    node.parentid.push_back(p_start);   
                }
            }
            count++;
        }
        store.push_back(node);  //pushing the node in the store vector
    }
    
    sort(store.begin(),store.end(),comp); // sort the data according to the size of parent vector
    
    //performing dynamic programming in the given data so as to find all those trasaction whose fees can be maximum and all the selected trasactions have combined weight less than given weight
    ll feeOfBlock = performDp(store,10000); 
    
    writeData("block.txt");  //write the final id data into the text file
    
    return 0;
    
}

