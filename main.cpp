#include <iostream>
#include <sstream>

class HashTable
{
    static const int Size = 26;
    struct Entry
    {
        std::string Data;
        std::string Status = "never used";
    };

    Entry m_Entries[Size];

    int GetIndex(const std::string &arg){
        return arg.back() - 'a';
    }

    bool Find(const std::string &arg, int *outIndex = nullptr){
        int index = GetIndex(arg);


        while (true)
        {
            if(m_Entries[index].Data == arg){
                if(outIndex){
                    *outIndex = index;
                }
                return true;
            }
            if(m_Entries[index].Status == "never used"){
                return false;
            }            

            index = (index + 1) % Size;
        }

        return false;
    }

    int GetInsertIndex(const std::string &arg){
        int index = GetIndex(arg);

        while (true)
        {
            if(m_Entries[index].Status == "never used" || m_Entries[index].Status == "tombstone"){
                return index;
            }

            index = (index + 1) % Size;
        }

        return -1;
    }
public:
    HashTable() = default;

    int GetSize()
    {
        return Size;
    }

    void Print()
    {
        bool first = true;
        for (int i = 0; i < Size; i++)
        {
            if(m_Entries[i].Status == "occupied"){
                if(!first){
                    std::cout << ' ';
                }
                std::cout << m_Entries[i].Data;

                first = false;
            }

        }
        std::cout << std::endl;
    }

    void Add(const std::string &arg)
    {
        int unused;
        bool exists = Find(arg);

        if(!exists){
            int insertIndex = GetInsertIndex(arg);

            m_Entries[insertIndex].Data = arg;
            m_Entries[insertIndex].Status = "occupied";
        }
    }

    void Delete(const std::string &arg)
    {
        int index;
        bool exists = Find(arg, &index);

        if(exists){
            m_Entries[index].Status = "tombstone";
        }
    }

};

int main()
{
    std::string input;

    getline(std::cin, input);

    HashTable hashTable;

    std::stringstream ss(input);

    while (ss.good())
    {
        std::string token;

        ss >> token;

        std::string entryName = token.substr(1);

        if (token[0] == 'A')
        {
            hashTable.Add(entryName);
        }
        else if (token[0] == 'D')
        {
            hashTable.Delete(entryName);
        }
    }

    hashTable.Print();

    return 0;
}