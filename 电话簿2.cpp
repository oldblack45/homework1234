#include<iostream>
#include<cstring>
#include<algorithm>
#include<string>
#include<unordered_map>
#include<fstream>
typedef long long ll;
using namespace std;
class Phone {
private:
    string name;
    string phoneNum;
    string address;
public:
    Phone() {}
    Phone(string name, string phoneNum, string address) {
        this->name = name;
        this->phoneNum = phoneNum;
        this->address = address;
    }
    void setName(string name) {
        this->name = name;
    }
    void setNum(string phoneNum) {
        this->phoneNum = phoneNum;
    }
    void setAddress(string address) {
        this->address = address;
    }
    string getName() {
        return this->name;
    }
    string getNum() {
        return this->phoneNum;
    }
    string getAddress() {
        return this->address;
    }
    void Print() {
        cout << "姓名：" << this->name << "  电话：" << this->phoneNum << "  住址：" << this->address << endl;
    }
    
};
class PhoneBook {
private:
    unordered_multimap<string, Phone> m;
    int real_modify(unordered_multimap<string, Phone>::iterator tmp) {//对map中给定的一个项进行修改操作
        cout << "请选择需要修改的条目：" << endl;
        cout << "1.姓名" << endl;
        cout << "2.手机号" << endl;
        cout << "3.住址" << endl;
        int opt; cin >> opt;
        while (opt != 1 && opt != 2 && opt != 3) {
            cout << "请输入正确编号!" << endl;
            cin >> opt;
        }
       if (opt == 1) {
           cout << "请输入修改后姓名" << endl;
           string newName;
           cin >> newName;
           tmp->second.setName(newName);
           //cout << "修改完成！" << endl;
       }
       if (opt == 2) {
           cout << "请输入修改后手机号" << endl;
           string newNum;
           cin >> newNum;
           tmp->second.setNum(newNum);
       }
       if (opt == 3) {
           cout << "请输入修改后住址" << endl;
           string newAddress;
           cin >> newAddress;
           tmp->second.setAddress(newAddress);
       }
       return 1;
    }
public:
    int add(string name, string phoneNum, string address) {//向map中添加项。
        m.insert(make_pair(name, Phone(name, phoneNum, address)));
        return 1;
    }
    int remove(string name) {//删除map中key值为name的项，删除成功返回1，否则返回0.
        int n = m.count(name);
        if (n == 1) {
            auto tmp = m.find(name);
            m.erase(name);
            return 1;
        }
        if (n == 0) {
            return 0;
        }
        cout << "请输入要删除项目的序号：" << endl;
        vector<unordered_multimap<string, Phone>::iterator> v(n);
        int j = 1;
        for (auto i = m.find(name); i->first == name; ++i, ++j) {
            v.push_back(i);
            cout << j << ". ";
            i->second.Print();
        }
        int index;
        string xt; cin >> xt;
        while (xt.length() != 1 || (xt[0] - '0' < 1 || xt[0] - '0' > j)) {
            cout << "请重新输入正确编号!" << endl;
            cin >> xt;
        }
        index = xt[0] - '0';
        m.erase(v[index - 1]);
        return 1;
    }
    int modify(string name) {//以name为key值在map中查找项，查找成功后进行修改，修改成功返回1，否则返回0
        int n = m.count(name);
        if (n == 1) {
            if (real_modify(m.find(name)))
                return 1;
            else
                return 0;
        }
        if (n == 0) {
            return 0;
        }
        vector<unordered_multimap<string, Phone>::iterator> v(n);
        int j = 1;
        for (auto i = m.find(name); i->first == name; ++i, ++j) {
            v.push_back(i);
            cout << j << ". ";
            i->second.Print();
        }
        int index;
        cout << "请输入要修改条目的序号：" << endl;
        string xt; cin >> xt;
        while (xt.length() != 1 || (xt[0] - '0' < 1 || xt[0] - '0' > j)) {
            cout << "请重新输入正确编号!" << endl;
            cin >> xt;
        }
        index = xt[0] - '0';
        if (real_modify(v[index - 1]))
            return 1;
        else
            return 0;
    }
    int find(string name) {//以name为key值在map中查找项，查找成功返回1，否则返回0
        int n = m.count(name);
        if (n == 1) {
            cout << "查找结果为：" << endl;
            auto tmp = m.find(name);
            tmp->second.Print();
            return 1;
        }
        if (n == 0) {
            return 0;
        }
        cout << "查找结果为：" << endl;
        for (auto i = m.find(name); i->first == name; ++i) {
            i->second.Print();
        }
    }
    int print() {//输出电话簿中所有保存信息
        if (m.empty()) return 0;
        for (auto i = m.begin(); i != m.end(); ++i) {
            i->second.Print();
        }
        return 1;
    }
    void FileWrite() {//将电话簿信息存入文本文件中
        ofstream file;
        file.open("phonebook.txt", ios::out);
        for (auto i = m.begin(); i != m.end(); ++i) {
            Phone tmp = i->second;
            file << tmp.getName() << " " << tmp.getNum() << " " << tmp.getAddress() << endl;
        }
        file.close();
    }
    void FileRead() {//读入电话簿文件，并将文件信息存入map
        ifstream file;
        file.open("phonebook.txt", ios::in);
        m.clear();
        string tmp_name, tmp_num, tmp_address;
        while (file >> tmp_name) {
            file >> tmp_num;
            file >> tmp_address;
            this->add(tmp_name, tmp_num, tmp_address);
        }
    }
};
PhoneBook b = *new PhoneBook();

int PrintScreen() {
    cout << "请选择功能" << endl;
    cout << "1.增加" << endl;
    cout << "2.删除" << endl;
    cout << "3.修改" << endl;
    cout << "4.查询" << endl;
    cout << "5.查看电话簿" << endl;
    cout << "6.退出系统" << endl;
    string xt; cin >> xt;
    while (xt.length() != 1||(xt[0]-'0'< 1 || xt[0]-'0'>6)) {
        cout << "请输入正确编号!" << endl;
        cin >> xt;
    }
    int opt = xt[0]-'0';
    if (opt == 1) {
        cout << "请输入姓名、手机号码，住址:" << endl;
        string x, y, z;
        cin >> x>>y>>z;
        if(b.add(x, y, z)) 
            cout<<"添加成功！"<<endl;
        cout << "继续使用请输入1，退出系统请输入0" << endl;
        int flag; cin >> flag;
        return flag;
    }
    if (opt == 2) {
        cout << "请输入要删除的姓名:" << endl;
        string x; cin >> x;
        if (!b.remove(x))
            cout << "删除失败！" << endl;
        else 
            cout << "删除成功！" << endl;
        cout << "继续使用请输入1，退出系统请输入0" << endl;
        int flag; cin >> flag;
        return flag;
    }
    if (opt == 3) {
        cout << "请输入要修改的姓名:" << endl;
        string x; cin >> x;
        if (!b.modify(x)) 
            cout << "修改失败！" << endl;
        else
            cout << "修改成功！" << endl;
        cout << "继续使用请输入1，退出系统请输入0" << endl;
        int flag; cin >> flag;
        return flag;
    }
    if (opt == 4) {
        cout << "请输入要查询的姓名:" << endl;
        string x; cin >> x;
        if (!b.find(x))
            cout << "查询失败！" << endl;
        else
            cout << "查询成功！" << endl;
        cout << "继续使用请输入1，退出系统请输入0" << endl;
        int flag; cin >> flag;
        return flag;
    }
    if (opt == 5) {
        if (b.print() == 0)
            cout << "电话簿为空！" << endl;
        cout << "继续使用请输入1，退出系统请输入0" << endl;
        int flag; cin >> flag;
        return flag;
    }
    if (opt == 6) {
        return 0;
    }
}
int main() {
    b.FileRead();
    while (1) {
        if (!PrintScreen()) {
            b.FileWrite();//文件在系统退出后进行一次更新保存。
            cout << "电话簿信息已保存在phonebook.txt中" << endl;
            cout << "欢迎下次使用" << endl;
            break;
        }
    }
}

