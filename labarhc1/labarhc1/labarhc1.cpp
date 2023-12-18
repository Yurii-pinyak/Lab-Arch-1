#include <iostream>
using namespace std;
int allId[2] = { 0,0 };

class Customer;

class Operator {
private:
    int ID;
    double talkingCharge;
    double messageCost;
    double networkCharge;
    int discountRate;
public:
    Operator() {
        ID = -1;
        talkingCharge = 0;
        messageCost = 0;
        networkCharge = 0;
        discountRate = 0;
    }
    Operator(double talkingCharge, double messageCost, double networkCharge, int discountRate) {
        allId[1] += 1;
        this->ID = allId[1];
        this->talkingCharge = talkingCharge;
        this->messageCost = messageCost;
        this->networkCharge = networkCharge;
        this->discountRate = discountRate;
    }
    double calculateTalkingCost(int minute, Customer customer,bool mainagecheck);
    double calculateMessageCost(int quantity, Customer customer,int mainid);
    double calculateNetworkCost(double amount);

    void set_talkingCharge(double talkingCharge) {
        this->talkingCharge = talkingCharge;
    }
    void set_messageCost(double messageCost) {
        this->messageCost = messageCost;
    }
    void set_networkCharge(double networkCharge) {
        this->networkCharge = networkCharge;
    }
    void set_discountRate(int discountRate) {
        this->discountRate = discountRate;
    }

    double get_talkingCharge() {
        return talkingCharge;
    }
    double get_messageCost() {
        return messageCost;
    }
    double get_networkCharge() {
        return networkCharge;
    }
    int get_discountRate() {
        return discountRate;
    }
    int get_Id() {
        return this->ID;
    }
};

class Bill {
private:
    double limitingAmount;
    double currentDebt;
public:
    Bill() {
        this->limitingAmount = 500;
        this->currentDebt = 0;
    }
    Bill(double limitingAmount) {
        this->limitingAmount = limitingAmount;
        this->currentDebt = 0;
    }
    double get_LimitingAmount() {
        return this->limitingAmount;
    }
    void set_LimitingAmount(double limitingAmount) {
        cout << "limit before = " << this->limitingAmount << endl;
        this->limitingAmount = limitingAmount;
        cout << "limit after = " << this->limitingAmount << endl;
        
    }
    double get_CurrentDebt() {
        return this->currentDebt;
    }
    void set_CurrentDebt(double currentDebt) {
        this->currentDebt = currentDebt;
    }
    bool check(double amount) {
        if (this->currentDebt + amount > limitingAmount) {
            return false;
        }
        else {
            return true;
        }
    }
    void use(double amount) {
        this->currentDebt += amount;
    }
   
};

class Customer {
private:
    int ID;
    string name;
    int age;
    Operator operators;
    Bill bills;
public:
    Customer() {
        ID = -1;
        name = "DefaultName";
        age = 0;
    }
    Customer(string name, int age, Operator operators) {
        allId[0]++;
        this->ID = allId[0];
        this->name = name;
        this->age = age;
        this->operators = operators;
        
    }
    string get_Name() {
        return this->name;
    }

    void set_Name(string name) {
        this->name = name;
    }

    int get_Age() {
        return this->age;
    }

    void set_Age(int age) {
        this->age = age;
    }

    Operator get_Operator() {
        return this->operators;
    }

    void set_Operator(Operator operators) {
        cout << "Operator before " << this->operators.get_Id()<<endl;
        this->operators = operators;
        cout << "Operator after " << this->operators.get_Id() << endl;
    }

    Bill get_Bill() {
        return this->bills;
    }
    
    void set_Bills(Bill bills) {
        this->bills = bills;
    }
    bool check_age(int age) {
        if (age < 18 || age > 65) {
            return true;
        }
        else {
            return false;
        }
    }
    void talk(int minute,Customer other) {
        if (bills.check(operators.calculateTalkingCost(minute, other, check_age(this->age)))) {
            
            bills.use(operators.calculateTalkingCost(minute, other, check_age(this->age)));
            cout << this->name << " talk with " << other.get_Name()<<"(talkingcost = " << operators.calculateTalkingCost(minute, other, check_age(this->age)) << ")" << endl;
        }
        else {
            cout << "You cant talk,please pay your debt" << endl;
        }
    }
    void message(int quantity, Customer other) {
        if (bills.check(operators.calculateMessageCost(quantity,other,this->operators.get_Id()))){

            bills.use(operators.calculateMessageCost(quantity, other, this->operators.get_Id()));
            cout << this->name << " massage with " << other.get_Name() << "(massagecost = " << operators.calculateMessageCost(quantity, other, this->operators.get_Id()) << ")" << endl;
        }
        else {
            cout << "You cant massage,please pay your debt" << endl;
        }
    }
    void connection(double amount) {
        if (bills.check(operators.calculateNetworkCost(amount))){
            bills.use(operators.calculateNetworkCost(amount))
            ;
            cout << this->name << "Use network" << "(networkcost = " << operators.calculateNetworkCost(amount) << ")" << endl;
        }
        else {
            cout << "You cant use network" << endl;
        }
    }
    void pay(double amount) {
        cout << "Debt before = " << bills.get_CurrentDebt() << endl;
        bills.set_CurrentDebt(bills.get_CurrentDebt() - amount);
        cout << "Debt after = " << bills.get_CurrentDebt() << endl;

    }
    void changeTheLimit(double amount) {
        this->bills.set_LimitingAmount(amount);
    }
};

double Operator::calculateTalkingCost(int minute, Customer customer,bool mainagecheck) {
    if (customer.check_age(customer.get_Age()) == true || mainagecheck == true) {
       
       
        return (minute * talkingCharge) * ((double)(100 - discountRate) / 100);
    }
    else {
        cout << minute * talkingCharge;
        return (minute * talkingCharge);
    }
}

double Operator::calculateMessageCost(int quantity, Customer customer,int mainid) {
    if (mainid == customer.get_Operator().get_Id()) {
        return (quantity * messageCost) * ((double)(100 - discountRate) / 100);
    }
    else {
        return (quantity * messageCost);
    }
}

double Operator::calculateNetworkCost(double amount) {
    return amount * networkCharge;
}

int main() {
    Operator newoperators[3] = {
       Operator(10,20,1,14),
       Operator(15,22,2,8),
       Operator(8,25,1,12)
    };
    Customer newcustomers[5] = {
        Customer("Sasha",17,newoperators[2]),
        Customer("Dima",22,newoperators[2]),
        Customer("Vika",77,newoperators[0]),
        Customer("Volodya",54,newoperators[1]),
        Customer("Vadum",24,newoperators[0])
    };
    newcustomers[0].talk(25, newcustomers[1]);
    newcustomers[2].message(10, newcustomers[4]);
    newcustomers[2].connection(250);
    newcustomers[2].pay(100);
    newcustomers[2].set_Operator(newoperators[2]);
    newcustomers[2].changeTheLimit(700);
}
