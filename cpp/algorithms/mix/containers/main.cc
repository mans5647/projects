#include <bits/stdc++.h>


struct Book
{
    Book(const char * name, const char * author_name, const char * genre, const uint32_t * year)
    {
        this->name = name;
        this->author_name = author_name;
        this->genre = genre;
        this->year = *year;
    }
    void Print_Info() const
    {
        std::cout<< "Book name: "<<name<<'\n';
        std::cout<< "Book author: "<<author_name<<'\n';
        std::cout<< "Book genre: "<<genre<<'\n';
        std::cout<< "Book year: "<<year<<'\n';
    }

    public:

    std::string name;
    std::string author_name;
    std::string genre;
    uint32_t year;
};

static const std::vector<const char *> book_genres = {"Horror", "Adventure", "Love", "Cartoon", "Cars"};

std::shared_ptr <Book> Add_Book(void)
{
    std::string t_name, t_author_name, t_gname;
    uint32_t genre, year;
    std::cout<<"Enter book name: ";
    std::getline(std::cin, t_name);
    std::cout<<"Enter book author's name: ";
    std::getline(std::cin, t_author_name);
    
    std::cout << "Enter book genre (";
    for (auto i = book_genres.begin(); i != book_genres.end(); i++)
    {
        std::cout << *i <<","; 
    }
    std::cout<<"): ";
    std::cin >> genre;
    switch (genre)
    {
        case 1:
        t_gname = book_genres[0];
        break;
        case 2:
        t_gname = book_genres[1];
        break;
        case 3:
        t_gname = book_genres[2];
        break;
        case 4:
        t_gname = book_genres[3];
        break;
        case 5:
        t_gname = book_genres[4];
        break;
        default:
            throw std::invalid_argument("Book genre id not found");
            break;
    }
    std::cout<<"Enter book year: ";
    std::cin >> year;
    return std::make_shared<Book>(t_name.c_str(), t_author_name.c_str(), t_gname.c_str(), &year);
}


struct Compare
{
    bool operator()(const std::shared_ptr<Book> & lhs, const std::shared_ptr<Book> & rhs)
    {
        return lhs->year > rhs->year;
    }
};

void print_queue(std::vector<std::shared_ptr<Book>> & values)
{
    std::priority_queue<Book, std::vector<std::shared_ptr<Book>>, Compare> p_q;
    for (auto & i : values)
    {
        p_q.push(i);
    }

    while (!p_q.empty()) {
        auto ptr = p_q.top();
        p_q.pop();
        std::cout<<"Name:\t"<<ptr->name<<" Author:\t"<<ptr->author_name<<" Genre:\t"<<ptr->genre<<" Year:\t"<<ptr->year<<'\n';
        std::cout<<'\n';
    }
}


int main()
{
    std::array<std::shared_ptr<Book>, 5> fixed_array;
    std::list<std::shared_ptr<Book>> network;

    std::vector<std::shared_ptr<Book>> values;

    std::forward_list<std::shared_ptr<Book>> f_list_books;

    std::stack<std::shared_ptr<Book>> stack;
    std::queue<std::shared_ptr<Book>> queue;
    std::priority_queue<std::shared_ptr<Book>> p_q;
    
    std::size_t inx = 0;
    
    for (std::size_t i = 0; i < 5; i++)
    {
        auto ptr = Add_Book();
        fixed_array[inx++] = ptr;
        network.push_back(ptr);
        f_list_books.push_front(ptr);
        stack.push(ptr);
        queue.push(ptr);
        values.push_back(ptr);
        std::cin.ignore(1, '\n');
    }

    std::cout<<"Forward list: \n";
    for (auto & i : f_list_books)
    {
        i.get()->Print_Info();
        std::cout<<'\n';
    }  

    std::cout<<"List: \n";

    for (auto & i : network)
    {
        i.get()->Print_Info();
        std::cout<<'\n';
    }


    std::cout<<"Array: \n";

    for (auto i = fixed_array.begin(); i != fixed_array.end(); i++)
    {
        i->get()->Print_Info();
        std::cout<<'\n';
    }


    std::cout<<"Stack (reversed!): \n";


    while (!stack.empty())
    {
        stack.top().get()->Print_Info();
        stack.pop();
        std::cout<<'\n';
    }


    std::cout<<"Queue!: \n";

    while (!queue.empty())
    {
        queue.front().get()->Print_Info();
        queue.pop();
        std::cout<<'\n';
    }

    print_queue(values);
    

    
    return 0;
}

