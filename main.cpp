#include <iostream>
#include <algorithm>
#include <vector>
#include <iterator>
#include <fstream>
#include <iomanip>
// "books.txt" file for books names and ids and quantity it has name & id and quantity.
// "users.txt: file for users names and id's.
// for each user you will add  there are new file created for he and it's content the books which user borrowed it.
// if you delete user his name will remove from file users and the file for he will be deleted.
// for each book in library there is file will be created it will have users names who borrowed this book to be easier for programme to count theme.
// when you delete user he should return all books because as soon as you delete him his name will be removed from system
// and the system will assume he returned all books and add theme to system again.
// be careful when your choice is clear because if you choose it you will delete all data in library (books and users) and there files


using namespace std;
void menu(){
    cout << "library menu :\n"
         << "0) Exit library \n1) add book\n2) search books for prefix\n3) print who borrowed book by name\n"
         << "4) print library by id\n5) print library by name\n6) add user\n7) user borrow book\n"
            "8) user return book\n9) print users \n10) delete user\n11) delete book \n12) clear library\n13) show user information\nEnter your choice[0- 13] :";
}
struct book_info{
    int id , quantity , borrowed;
    string name;
    vector<string> borrowed_name;

};
int tallest_id_user(){
    string name;
    int tall_id;
    bool first = true;
    fstream file_users;
    file_users.open("users.txt" , ios :: in);
    if(!file_users.is_open()){
        return 0;
    }
    else{
        while(!file_users.eof()){
            string str;
            int id , count = 0;
            file_users >> str >> id;
            while(id) {
                id/=10;
                count++;
            }
            if (first) {
                tall_id = count;
                first = false;
            }
            else{
                if(count > tall_id)
                    tall_id = count;
            }
        }
    }
    file_users.close();
    return tall_id;
}
int tallest_name_user(){
    int tallest;
    bool first = true;
    fstream file_books;
    file_books.open("users.txt" , ios :: in);
    if(file_books.is_open()) {
        while (!file_books.eof()) {
            string name;
            int id;
            file_books >> name >> id;
            if (first) {
                tallest = name.length();
                first = false;
            } else {
                if (name.length() > tallest)
                    tallest = name.length();
            }
        }

        file_books.close();
        return tallest;
    }
    else{
        file_books.close();
        return 0 ;
    }
}
int tallest_id(){
    int tallest;
    bool first;
    fstream file_books;
    file_books.open("books.txt" , ios ::in);
    if(file_books.is_open()){
        while (!file_books.eof()){
            string name;
            int id , qu , tall = 0;
            file_books >> name >> id >> qu;
            while (id){
                id/=10;
                tall++;
            }
            if(first){
                tallest = tall;
                first = false;
            }
            else{
                if(tall > tallest)
                    tallest = tall;
            }
        }
        file_books.close();
        return tallest;
    }
    else{
        file_books.close();
        return 0;
    }
}
int tallest_name(){
    int tallest;
    bool first = true;
    fstream file_books;
    file_books.open("books.txt" , ios :: in);
    if(file_books.is_open()) {
        while (!file_books.eof()) {
            string name;
            int id , qu;
            file_books >> name >> id >> qu;
            if (first) {
                tallest = name.length();
                first = false;
            } else {
                if (name.length() > tallest)
                    tallest = name.length();
            }
        }

        file_books.close();
        return tallest;
    }
    else{
        file_books.close();
        return 0 ;
    }
}

bool search_books(string name , int Id , fstream &file_books){
    file_books.open("books.txt" , ios :: in);
    string str;
    int id , quantity;
    while (file_books){
        file_books >> str >> id >> quantity;
        if(str == name || id == Id){
            file_books.close();
            return true;
        }
    }
    file_books.close();
    return false;

}

bool is_it_empty(fstream &file){
    return file.peek() == ifstream :: traits_type ::eof();
}


void add_book(fstream &file_books){
    book_info newbook;
    fstream newfile;
    cout << "Enter book info : id & name and total quantity :";
    cin >> newbook.id >> newbook.name >> newbook.quantity;
    if (search_books(newbook.name , newbook.id , file_books)){
        cout << "wrong book name or id:\n";
    }
    else{
        file_books.open("books.txt", ios:: in);
        if(is_it_empty(file_books)){
            file_books.close();
            file_books.open("books.txt", ios:: app);
            file_books << newbook.name << ' '<< newbook.id << ' '<< newbook.quantity;
            file_books.close();
            newbook.name += ".txt";
            newfile.open(newbook.name  , ios :: app);
            newfile.close();

        }
        else{
            file_books.close();
            file_books.open("books.txt", ios:: app);
            file_books << '\n' << newbook.name << ' '<< newbook.id << ' '<< newbook.quantity;
            file_books.close();
            newbook.name += ".txt";
            newfile.open(newbook.name  , ios :: app);
            newfile.close();
        }
    }
}
void search_book(fstream &file_books){
    string searchword , name;
    int counter = 0, id , quantity , num_of_books;
    bool status = true;
    cout << "Enter book name prefix :";
    cin >> searchword;
    file_books.open("books.txt", ios :: in);
    while(!file_books.eof() && status){
        counter = 0 ;
        file_books >> name >> id >> quantity;
        for (int i = 0 ; i < searchword.length(); i++){
            if (searchword[i] == name[i]){
                counter++;
            }
            else
                break;
        }
        if (counter == searchword.length())
            cout << "name : " << name << "  id : " << id << "   quantity : " << quantity<<endl , num_of_books++;
    }
    file_books.close();
    if (!num_of_books)
        cout << "No books with these name:\n";
}
void print_by_id(fstream &file_books) {
    vector<int> ids;
    string book;
    int id, quantity, counter = 0 , total_quantity ;
    int tall_name = tallest_name() , tall_id = tallest_id();
    file_books.open("books.txt", ios::in);
    while (!file_books.eof()) {
        file_books >> book >> id >> quantity;
        ids.push_back(id);
    }
    fstream file1;
    sort(ids.begin(), ids.end());
    while (counter != ids.size()) {
        file_books.clear();
        file_books.seekg(0);
        while (!file_books.eof()) {
            file_books >> book >> id >> quantity;
            if (id == ids[counter]){
                file1.open(book+".txt" , ios::in);
                total_quantity = 0 ;
                if (is_it_empty(file1)){}
                else{
                    while (!file1.eof()){
                        string str;
                        getline(file1 , str);
                        total_quantity++;
                    }
                }
                file1.close();
                cout << "name : " << setw(tall_name) << book << setw(8)<< "id : " << setw(tall_id) << id << setw(20) << "total quantity : " << setw(5) << quantity - total_quantity << "   total borrowed : " << total_quantity <<endl;
                counter++;
            }
        }
    }
    file_books.close();
}
void print_by_name(fstream & file_books){
    vector<string> names;
    int id , quantity , counter = 0 ;
    string book;
    int tall_name = tallest_name() , tall_id = tallest_id();
    file_books.open("books.txt" , ios :: in);
    while(!file_books.eof()){
        file_books >> book >> id >> quantity;
        names.push_back(book);
    }
    sort(names.begin() , names.end());
    fstream file1;
    while (counter != names.size()){
        file_books.clear();
        file_books.seekg(0);
        while(!file_books.eof()){
            file_books >> book >> id >> quantity;
            if (book == names[counter]){
                file1.open(book+".txt" , ios :: in);
                int total_quantity = 0;
                if (is_it_empty(file1)){}
                else{
                    while(!file1.eof()){
                        string str;
                        file1 >> str;
                        total_quantity++;
                    }
                }
                file1.close();
                cout << "name = "  << setw(tall_name)<< book << setw(8) <<"id = "<< setw(tall_id) << id<< "   total quantity = " << setw(5) << quantity - total_quantity << "   total borrowed : " << total_quantity << endl;
                counter++;
            }
        }
    }
    file_books.close();
}
void who_borrowed_by_name(){
    string book_name , str;

    cout << "Enter book name: ";
    cin >> book_name;
    fstream file_names;
    file_names.open(book_name +".txt" , ios :: in);
    if(!file_names.is_open()){
        cout << "No book with these name\n";
    }
    else if (is_it_empty(file_names))
        cout << "No one borrowed these book\n";
    else {
        while (!file_names.eof()) {
            getline(file_names, str);
            cout << str << '\n';
        }
    }
    file_names.close();
}
struct user_info{
    string user_name;
    int user_id;
    vector<int> ids_books;
};
void add_user(fstream &file_users){
    user_info newuser;
    fstream file1;
    cout << "Enter user name & national id:";
    cin >> newuser.user_name >> newuser.user_id;
    file_users.open("users.txt" , ios :: in);
    if(is_it_empty(file_users)){
        file_users.close();
        file_users.open("users.txt" , ios::app);
        file_users << newuser.user_name << ' ' << newuser.user_id;
        file_users.close();
    }
    else{
        file_users.close();
        file_users.open("users.txt" , ios::app);
        file_users << endl << newuser.user_name << ' ' << newuser.user_id;
        file_users.close();
    }
    file1.open(newuser.user_name+".txt" , ios :: app);
    file1.close();
}
void borrow_book(fstream &file_books , fstream &file_users){
    string name , book;
    int qu;
    file_books.open("books.txt", ios :: in);
    file_users.open("users.txt", ios :: in);
    fstream file1;
    fstream file2;
    bool status_name = false , status_book=false;
    cout << "Enter user name and book name:";
    cin >> name >> book;
    while(!file_books.eof()){
        int id;
        string book_name;
        file_books >> book_name >> id >> qu;
        if(book_name == book){
            status_book = true;
            break;
        }
    }
    file_books.close();
    if (!status_book)
        cout << "No book with these name\n";
    while(!file_users.eof()){
        string user_name;
        int user_id;
        file_users >> user_name >> user_id;
        if(user_name== name){
            status_name= true;
            break;
        }
    }
    file_users.close();
    if(!status_name){
        cout << "No users with these name\n";
    }
    fstream file_book;
    file_book.open(book+".txt" , ios :: in);
    if(file_book.is_open()){
        int j = 0;
        while(!file_book.eof()){
            string str;
            file_book >> str;
            j++;
        }
        if(j == qu){
            status_name = false;
            cout << "Not available in library (no copies)\n";
        }
    }
    if (status_name && status_book){
        file1.open(book+".txt" , ios :: in);
        if(is_it_empty(file1)) {
            file1.close();
            file1.open(book+".txt" , ios :: app);
            file1 << name;
            file1.close();
        }
        else{
            file1.close();
            file1.open(book+".txt" , ios :: app);
            file1 << '\n' << name;
            file1.close();
        }
        file2.open(name+".txt", ios :: in);
        if(is_it_empty(file2)) {
            file2.close();
            file2.open(name+".txt" , ios :: app);
            file2 << book;
            file2.close();
        }
        else{
            file2.close();
            file2.open(name+".txt" , ios :: app);
            file2 << '\n' << book;
            file2.close();
        }
    }
}
void return_book() {
    string book, name;
    fstream user_file;
    fstream book_file;
    fstream file1;
    fstream file2;
    bool status_name = true , status_book=true , first = true, exicet = false ,first2 = true;
    cout << "Enter user name and book name:";
    cin >> name >> book;
    user_file.open(name+".txt" , ios :: in);
    book_file.open(book+".txt" , ios :: in);
    if(!book_file.is_open()){
        cout << "No book with these name\n";
        status_book = false;
    }
    if(!user_file.is_open()){
        cout << "No users with these name\n";
        status_name = false;
    }
    user_file.close();
    book_file.close();
    if(status_book && status_name){
        file1.open("newfile.txt", ios :: app);
        file2.open(book+".txt" , ios :: in);
        fstream file_user;
        file_user.open(name+".txt", ios ::in);
        fstream user;
        user.open("new file user.txt" , ios :: app);
        if(is_it_empty(file2)){cout << "user didn't borrow these book\n";
            file1.close();
            file2.close();
            file_user.close();
            user.close();
            remove("newfile.txt");
            remove("new file user.txt");
        }
        else{
            while(!file_user.eof()){
                string str;
                file_user >> str;
                if (str == book){
                    exicet = true;
                    break;
                }
            }
            file_user.clear();
            file_user.seekg(0);
        }
        file2.close();
        if (exicet) {
            file2.open(book+".txt" , ios ::in);
            string str;
            while (!file2.eof()) {
                file2 >> str;
                if(str == name && first2){first2 = false;}
                else{
                    if (first) {
                        file1 << str;
                        first = false;
                    }
                    else
                        file1 << '\n' << str;
                }
            }
            first = true;
            first2 = true;
            while(!file_user.eof()){
                string st;
                file_user >> st;
                if (first2 && st == book){first2 = false;}
                else {
                    if (first) {
                        user << st;
                        first = false;
                    } else {
                        user << '\n' << st;
                    }
                }
            }
            name+= ".txt";
            const char *old = name.c_str();
            file_user.close();
            user.close();
            remove(old);
            rename("new file user.txt" , old);
            file1.close();
            file2.close();
            book += ".txt";
            const char *deap = book.c_str();
            remove(deap);
            rename("newfile.txt", deap);
        }
        else {
            cout << "user didn't borrow these book\n";
            file_user.close();
            user.close();
            remove("new file user.txt");
            file1.close();
            file2.close();
            remove("new file,txt");
        }
    }
}
void print_users(fstream &file_users){
    string name ;
    int id , tall_name = tallest_name_user() , tall_id = tallest_id_user() , tall_book = tallest_name();
    file_users.open("users.txt" , ios :: in);
    fstream file1;
    fstream file2;
    while(!file_users.eof()){
        file_users >> name >> id;
        cout << "user name : " << setw(tall_name) << name << "  id : " << setw(tall_id) << id << "   borrowed books id : ";
        file1.open(name+".txt" , ios :: in);
        while(!file1.eof()){
            string st;
            file1 >> st;
            file2.open("books.txt" , ios :: in);
            while(!file2.eof()){
                string str;
                int book_id , qu;
                file2 >> str >> book_id >> qu;
                if(str == st){
                    cout<< setw (tall_book) << book_id;
                    break;
                }
            }
            file2.close();

        }
        file1.close();
        cout << '\n';
    }
    file_users.close();
}
void delete_user(fstream &file_users){
    string user_name;
    int user_id;
    bool exicet = false , first = true;
    fstream user_file;
    fstream newfile, book_file , nbook_file;
    cout << "Enter user name and id : ";
    cin >> user_name >> user_id;
    user_file.open (user_name+".txt" , ios :: in);
    if(!user_file.is_open()){
        cout << "No user with these name:\n";
        user_file.close();
    }
    else {
        file_users.open("users.txt" , ios :: in);
        newfile.open("newfile.txt" , ios :: app);
        while(!file_users.eof()){
            string st;
            int id;
            file_users >> st >> id;
            if (st == user_name && id == user_id){
                exicet = true;
            }
            else {
                if (first){
                    newfile << st << ' ' << id;
                    first = false;}
                else{newfile << '\n' << st << ' ' << id;}
            }
        }
        if (exicet){
            cout << "when you delete user he should be returned all books\n";
            cout <<" are you sure to delete\""<< user_name << "\" (1 to delete / 2 to ignore) : ";
            int i ;
            cin >> i;
            if (i == 1) {
                while(!user_file.eof()){
                    first = true;
                    string st;
                    user_file >> st;
                    book_file.open(st+".txt" , ios :: in);
                    nbook_file.open("new file for book.txt" , ios :: app);
                    while(!book_file.eof()){
                        string str;
                        book_file >> str;
                        if(str != user_name){
                            if (first){
                                nbook_file << str;
                                first = false;
                            }
                            else
                                nbook_file << endl << str;
                        }
                    }
                    book_file.close();
                    nbook_file.close();
                    st+=".txt";
                    remove(st.c_str());
                    rename("new file for book.txt" , st.c_str());
                }
                user_name += ".txt";
                user_file.close();
                remove(user_name.c_str());
                file_users.close();
                remove("users.txt");
                newfile.close();
                rename("newfile.txt", "users.txt");
            }
            else {
                user_file.close();
                file_users.close();
                newfile.close();
                remove("newfile.txt");
            }
        }
        else{
            cout << "rong id:\n";
            user_file.close();
            file_users.close();
            newfile.close();
            remove("newfile.txt");
        }
    }
}
void delete_book(fstream &file_books){
    string book_name;
    int book_id;
    bool exicet = false , first = true;
    fstream book_file;
    fstream newfile, user_file , nuser_file;
    cout << "Enter book name and id : ";
    cin >> book_name >> book_id;
    book_file.open (book_name+".txt" , ios :: in);
    if(!book_file.is_open()){
        cout << "No book with these name:\n";
        book_file.close();
    }
    else {
        file_books.open("books.txt" , ios :: in);
        newfile.open("newfile.txt" , ios :: app);
        while(!file_books.eof()){
            string st;
            int id , qu;
            file_books >> st >> id >> qu;
            if (st == book_name && id == book_id){
                exicet = true;
            }
            else {
                if (first){
                    newfile << st << ' ' << id << ' ' << qu;
                    first = false;}
                else{newfile << '\n' << st << ' ' << id << ' ' << qu;}
            }
        }
        if (exicet){
            cout << "when you delete book it will be removed from all users\n";
            cout <<" are you sure to delete\""<< book_name << "\" (1 to delete / 2 to ignore) : ";
            int i ;
            cin >> i;
            if (i == 1) {
                while(!book_file.eof()){
                    first = true;
                    string st;
                    book_file >> st;
                    user_file.open(st+".txt" , ios :: in);
                    nuser_file.open("new file for user.txt" , ios :: app);
                    while(!user_file.eof()){
                        string str;
                        user_file >> str;
                        if(str != book_name){
                            if (first){
                                nuser_file << str;
                                first = false;
                            }
                            else
                                nuser_file << '\n' << str;
                        }
                    }
                    user_file.close();
                    nuser_file.close();
                    st+=".txt";
                    remove(st.c_str());
                    rename("new file for user.txt" , st.c_str());
                }
                book_name += ".txt";
                book_file.close();
                remove(book_name.c_str());
                file_books.close();
                remove("books.txt");
                newfile.close();
                rename("newfile.txt", "books.txt");
            }
            else {
                book_file.close();
                user_file.close();
                file_books.close();
                newfile.close();
                remove("newfile.txt");
            }
        }
        else{
            cout << "rong id:\n";
            book_file.close();
            user_file.close();
            file_books.close();
            newfile.close();
            remove("newfile.txt");
        }
    }
}
void clear_library(fstream &file_books , fstream &file_users){
    bool y ;
    cout << "are you sure you need to delete all books and users (0) to ignore / (1) to delete : ";
    cin >> y;
    if (y){
        file_books.open("books.txt" , ios :: in);
        while(!file_books.eof()){
            string str;
            int id ,qu;
            file_books >> str >> id >> qu;
            str+=".txt";
            remove(str.c_str());
        }
        file_books.close();
        file_users.open("users.txt" , ios :: in);
        while(!file_users.eof()){
            string str;
            int id;
            file_users >> str >> id;
            str+=".txt";
            remove(str.c_str());
        }
        file_users.close();
        remove("users.txt");
        remove("books.txt");
    }
}
void show_info(fstream &file_books , fstream &file_users){
    string name;
    int id , tall_name = tallest_name() , tall_id = tallest_id();
    bool execit = false;
    fstream file_user ;
    cout << "Please enter user name and id you need to show his information : ";
    cin >> name >> id;
    file_user.open(name+".txt" , ios :: in);
    if(!file_user.is_open())
        cout << "NO user with these name\n";
    else{
        file_users.open("users.txt" , ios :: in);
        while(!file_users.eof()){
            string st;
            int ide;
            file_users >> st >> ide;
            if(ide == id){
                execit = true;
                break;
            }
        }
        file_users.close();
    }
    if(execit){
        cout << "\nuser name : "<< name << "\nuser id : " << id << endl;
        file_books.open("books.txt"  , ios :: in);
        if(is_it_empty(file_user))
            cout << "user didn't borrowed books\n";
        else
            cout << "borrowed books :\n" << "book name" << setw(15) << "book id\n";
        while(!file_user.eof()){
            string str;
            file_user >> str;
            while(!file_books.eof()){
                string st;
                int ide , qu;
                file_books >> st >> ide >> qu;
                if(st == str){
                    cout << setw(tall_name) << st << setw(15)<< ide << endl;
                    break;
                }
            }
            file_books.clear();
            file_books.seekg(0);

        }
        file_books.close();
        file_user.close();
    }
    else {
        cout << "Wrong user id\n";
        file_user.close();
    }
}
int main() {
    fstream file_books;
    fstream file_users;
    int x;
    bool status = true;
    while (status) {
        do {
            menu();
            cin >> x;
        } while (x > 13 || x < 0);
        if (x == 0)
            status = false;
        else if(x == 1)
            add_book(file_books);
        else if (x == 2)
            search_book(file_books);
        else if (x == 3)
            who_borrowed_by_name();
        else if (x == 4)
            print_by_id(file_books);
        else if (x == 5)
            print_by_name(file_books);
        else if (x == 6)
            add_user(file_users);
        else if (x == 7)
            borrow_book(file_books, file_users);
        else if (x == 8 )
            return_book();
        else if (x == 9)
            print_users(file_users);
        else if (x == 10)
            delete_user(file_users);
        else if (x == 11)
            delete_book(file_books);
        else if(x == 12)
            clear_library(file_books , file_users);
        else if(x == 13)
            show_info(file_books ,file_users);

    }

    return 0;
}