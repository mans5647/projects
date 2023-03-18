#include <iostream>
#include <string>
#include <cstdint>
#include <ctime>
#include <cstring>
#define PLEN 15 // minimum password length = 15 by default

namespace WARNINGS_
{
    std::string RET_SUCCESS = "Password created successfully \n";
    std::string RET_NOTSUCS = "Password has not been created \n";
    std::string NOT_EQUAL_TO_OPT = "Option not recognized \n";
    std::string NEED_OPT = "Option required after `-` \n";
}
// Class::GenStdPassword()
// Class::GenUserlenPass(uint64_t length)
// 
void throw_error(std::string msg)
{
    std::cout<<msg;
    return;
}

int comp(std::string & __String__, std::string __Pattern__)
{
    for (size_t i = 0; i < __String__.length(); ++i)
    {
        if (__String__[i] == __Pattern__[i])
        {
            continue;
        }
    }
}

namespace getPass
{
    class Password
    {
        private:
            void GenStdPassword();
            void GenUserlenPass();
        public:
            const char ** strings;
            Password();
            ~Password();
            
    };
    Password::Password()
    {
        strings = new const char *[2];
        strings[0] = "MMM";
        strings[1] = "NNN";
        GenStdPassword();
    }
    Password::~Password()
    {
        delete[] strings;
    }
    void Password::GenStdPassword()
    {
        
        srand((unsigned int)time(NULL));
        std::string final_password = ""; // by default is ''
        std::string letters = "aqertyuiop[]';lkjhgfdsazxcvbnm,./ABCDFGETQOYPTURBVMCZJS<VMBNFLTORIEJQW!@#$%^&*()_+ `";
        size_t alph_l = letters.length();
        for (auto i = 0; i < PLEN; i++)
        {
            final_password+=letters[rand() % alph_l];
        }
        std::cout<<"Your password: "<<final_password;
    }
}
int main(int argc, char **argv)
{
    std::string options;
    options[0] = '-';
    for (size_t i = 1; i < argc; i++)
    {
        options+=argv[i];
    }

    options+=' ';

}