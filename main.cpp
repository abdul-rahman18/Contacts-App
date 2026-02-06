#include <iostream>
#include <string>

using namespace std;

class Contact {
public:
    long long m = 1000000007LL;
    vector<long long>pwr;
    const int p = 31;
    unordered_map<string, long>mp;
    Contact() {
        pwr.push_back(1);
        for(int i=1;i<10002;i++) pwr.push_back(((pwr[i-1]%m) * p)%m);
    }

    void add(string name, long number) {
        mp[name] = number;
        cout << name << ":" << number << endl;
        cout << endl;
    }

    long deleteNum(Contact* c,string name){
        long x = c->mp[name];
        c->mp.erase(name);
        return x;
    }

    vector<string> search(string s) {
        vector<string> result;
        for (auto [k,v] : mp) {
            if (matchSubstring(s, k)) {
                result.push_back(k);
            }
        }
        return result;
    }

    void totalContacts() {
        if(mp.size()==0) {
            cout << "Contact is empty" << endl;
        }
        for (auto [k,v] : mp) {
            cout << k << ":" << v << endl;
        }
        cout << endl;
    }

    bool matchSubstring(string a, string b) {
        if (a.size()>b.size()) return false;
        vector<long long>pha(a.size());
        pha[0] = ((a[0] - 'a' + 1)*pwr[0])%m;
        for(int i=1;i<a.size();i++) pha[i] = (pha[i-1] + (a[i]-'a'+1) * pwr[i])%m;

        vector<long long>phb(b.size());
        phb[0] = ((b[0]-'a'+1) * pwr[0])%m;
        for(int i=1;i<b.size();i++) phb[i] = (phb[i-1] + (b[i]-'a'+1) * pwr[i])%m;

        int l = 0;
        int h = a.size()-1;

        long long x = pha[h]%m;
        long long y = phb[h]%m;
        if(x == y) return true;

        for(int i=1;i<=b.size()-a.size();i++)
        {
            l = i;
            h = i+a.size()-1;

            long long X = (x * pwr[l])%m;
            y = (phb[h] - phb[l-1] + m)%m;

            if(X==y) return true;
        }
        return false;
    }
};

int main() {
    Contact* contacts = new Contact();

    cout << "*** Select an Option ***" << endl;
    cout << "*** 1.Search for a contact ***" << endl;
    cout << "*** 2.Add a new contact ***" << endl;
    cout << "*** 3.Delete a contact ***" << endl;
    cout << "*** 4.List all contacts ***" << endl;
    cout << "*** 5.Exit ***" << endl;
    cout << "Enter Your Choice: ";
    int input; cin >> input;

    while (input) {
        if (input == 1) {
            cout << "Enter the name to search : ";
            string name; cin >> name;
            vector<string> res =  contacts->search(name);
            if (res.size() == 0) cout << "No contact found for name " << name << endl;
            for (auto x : res) {
                if (contacts->mp.find(x) != contacts->mp.end()) {
                    cout << x << " : " << contacts->mp[x] << endl;
                }
            }
            cout << endl;
        }
        else if (input == 2) {
            cout << "Enter name : ";
            string name; cin >> name;
            cout << "Enter number : ";
            long number; cin >> number;
            while(number <= 999999999 || number >9999999999) {
                cout << "Invalid number" << endl;
                cout << "Enter a valid number : " << endl;
                cin >> number;
            }
            contacts->add(name, number);
            cout << "Contact added successfully" << endl;
        }
        else if (input == 3) {
            cout << "Enter name to delete the contact : " << endl;
            string name; cin >> name;
            long x = contacts->deleteNum(contacts, name);
            cout << "Deleted " << endl << name << " : " << x << endl;
        }
        else if (input == 4) {
            contacts->totalContacts();
        }
       else if (input == 5) {
           cout << "Thank You" << endl;
            break;
        }
       else cout << "Invalid input" << endl;

        cout << "*** Select an Option ***" << endl;
        cout << "*** 1.Search for a contact ***" << endl;
        cout << "*** 2.Add a new contact ***" << endl;
        cout << "*** 3.Delete a contact ***" << endl;
        cout << "*** 4.List all contacts ***" << endl;
        cout << "*** 5.Exit ***" << endl;
        cout << "Enter Your Choice: "; cin >> input;
    }
    return 0;
}