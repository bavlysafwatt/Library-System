#include <bits/stdc++.h>
using namespace std;

struct book{
    int id;
    string name;
    string who_borrowed_book[10];
    int total_quantity;
    int total_borrowed;
    book() {
        total_quantity = total_borrowed = 0;
        id = -1;
        name = "";
    }
    void read(){
        cout << "Enter the id and the name of the book and quantity: ";
        cin >> id >> name >> total_quantity;
        total_borrowed = 0;
    }
    void print_who_borrowed_book(){
        for(int i = 0 ; i < total_borrowed ; i++)
            cout << who_borrowed_book[i] << endl;
    }
    bool borrow(string username){
        if(total_quantity-total_borrowed==0)
            return false;
        who_borrowed_book[total_borrowed++] = username;
        return true;
    }
    void print(){
        cout << " Id: " << id << " Name: " << name << " Total quantity: " << total_quantity << " Total borrowed: " << total_borrowed << endl;
    }
    void return_book(string username){
        for (int i = 0; i < total_borrowed ; ++i) {
            if(who_borrowed_book[i]==username){
                for (int j = i+1; j < total_borrowed; ++j) {
                    who_borrowed_book[i-1] = who_borrowed_book[i];
                }
                total_borrowed--;
                return;
            }
        }
        cout << "This user didn't borrow this book yet." << endl;
        return;
    }
};

struct user{
    string name;
    int id;
    int borrowed_books_ids[100];
    int len;
    user(){
        name = "";
        id = 0;
        borrowed_books_ids[10] ={0};
        len = 0;
    }
    void read(){
        cout << "Enter your id and your name: ";
        cin >> id >> name;
    }
    bool borrow(int book_id){
        borrowed_books_ids[len++] = book_id;
    }
    void print(){
        cout << "Id: " << id << " Name: " << name << " Total borrowed: " << len << endl;
    }
    void return_book(int book_id){
        for (int i = 0; i < len ; ++i) {
            if(borrowed_books_ids[i]==book_id){
                for (int j = i+1; j < len; ++j) {
                    borrowed_books_ids[i-1] = borrowed_books_ids[i];
                }
                len--;
                return;
            }
        }
    }
};
bool cmp_by_id(book &a, book &b){
    return a.id < b.id;
}

bool cmp_by_name(book &a, book &b){
    return a.name < b.name;
}
struct library_system{
    int total_books;
    book books[100];
    int total_users;
    user users[100];
    library_system(){
        total_books = 0;
        total_users = 0;
    }
    void run(){
        while(true) {
            int choice = menu();

            if (choice == 1)
                add_book();
            else if (choice == 2)
                search_books_by_prefix();
            else if (choice == 3)
                print_who_borrowed_book_by_name();
            else if (choice == 4)
                print_library_by_id();
            else if (choice == 5)
                print_library_by_name();
            else if (choice == 6)
                add_user();
            else if (choice == 7)
                user_borrow_book();
            else if (choice == 8)
                user_return_book();
            else if (choice == 9)
                print_users();
            else
                break;
        }
    }
    int menu(){
        int choice = -1;
        while (choice == -1) {
            cout << "\nLibrary Menu;\n";
            cout << "1) add_book\n";
            cout << "2) search_books_by_prefix\n";
            cout << "3) print_who_borrowed_book_by_name\n";
            cout << "4) print_library_by_id\n";
            cout << "5) print_library_by_name\n";
            cout << "6) add_user\n";
            cout << "7) user_borrow_book\n";
            cout << "8) user_return_book\n";
            cout << "9) print_users\n";
            cout << "10) Exit\n";

            cout << "\nEnter your menu choice [1 - 10]:  ";
            cin >> choice;

            if (!(1 <= choice && choice <= 10)) {
                cout << "Invalid choice. Try again\n";
                choice = -1;	// loop keep working
            }
        }
        return choice;
    }
    void add_book(){
        books[total_books++].read();
        return;
    }
    bool search_books_by_prefix(){
        cout << "Search: ";
        string pre; cin >> pre;
        int cnt = 0;
        for (int i = 0; i < total_books ; ++i) {
            if(pre.size() > books[i].name.size()) continue;
            string name = books[i].name;
            bool flag = true;
            for (int j = 0; j < pre.size() ; ++j) {
                if(pre[j]!=name[j]){
                    flag = false;
                    break;
                }
            }
            if(flag){
                cnt++;
                cout << name << " ";
            }
        }
        if(!cnt) {
            cout << "No books available." << endl;
            return false;
        }
        return true;
    }
    void print_who_borrowed_book_by_name(){
        bool flag = false;
        while(!flag) {
            cout << "Enter book name: ";
            string book_name;
            cin >> book_name;
            for (int i = 0; i < total_books; ++i) {
                if (books[i].name == book_name) {
                    flag = true;
                    books[i].print_who_borrowed_book();
                }
            }
            if(!flag) cout << "Invalid book. please try again." << endl;
        }
        return;
    }
    void print_library_by_id(){
        sort(books, books+total_books, cmp_by_id);
        for (int i = 0; i < total_books ; ++i)
            books[i].print();
        return;
    }
    void print_library_by_name(){
        sort(books, books+total_books, cmp_by_name);
        for (int i = 0; i < total_books ; ++i)
            books[i].print();
        return;
    }
    void add_user(){
        users[total_users++].read();
        return;
    }

    void user_borrow_book(){
        int idx1= -1, idx2= -1;
        string username;
        int book_id;
        int trials = 3;
        while(trials--){
            cout << "Enter your username: ";
            cin >> username;
            idx1 = find_user(username);
            if(idx1==-1){
                cout << "Invalid username, please try again." << endl;
                continue;
            }
            break;
        }
        if(trials==0 && idx1 == -1) {
            cout << "You enter a lot of wrong names." << endl;
            cout << "returning to menu." << endl;
            return;
        }
        trials = 3;
        while(trials--){
            cout << "Enter the book id: ";
            cin >> book_id;
            idx2= find_book(book_id);
            if(idx2==-1){
                cout << "Invalid id, please try again." << endl;
                continue;
            }
            break;
        }
        if(trials==0 && idx2 == -1) {
            cout << "You enter a lot of wrong names." << endl;
            cout << "returning to menu." << endl;
            return;
        }
        bool flag = books[idx2].borrow(username);
        if(flag)
            users[idx1].borrow(book_id);
        return;
    }
    void user_return_book(){
        int idx1= -1, idx2= -1;
        string username;
        int book_id;
        int trials = 3;
        while(trials--){
            cout << "Enter your username: ";
            cin >> username;
            idx1 = find_user(username);
            if(idx1==-1){
                cout << "Invalid username, please try again." << endl;
                continue;
            }
            break;
        }
        if(trials==0 && idx1 == -1) {
            cout << "You enter a lot of wrong names." << endl;
            cout << "returning to menu." << endl;
            return;
        }
        trials = 3;
        while(trials--){
            cout << "Enter the book id: ";
            cin >> book_id;
            idx2= find_book(book_id);
            if(idx2==-1){
                cout << "Invalid id, please try again." << endl;
                continue;
            }
            break;
        }
        if(trials==0 && idx2 == -1) {
            cout << "You enter a lot of wrong names." << endl;
            cout << "returning to menu." << endl;
            return;
        }
        users[idx1].return_book(book_id);
        books[idx2].return_book(username);
    }
    void print_users(){
        for (int i = 0; i < total_users ; ++i) {
            users[i].print();
        }
        return;
    }
    int find_user(string username){
        for (int i = 0; i < total_users; ++i) {
            if (users[i].name == username) {
                return i;
            }
        }
        return -1;
    }
    int find_book(int book_id){
        for (int i = 0; i < total_books; ++i) {
            if (books[i].id == book_id) {
                return i;
            }
        }
        return -1;
    }
};
int main() {
    library_system system;
    system.run();
    return 0;
}
