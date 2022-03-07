#include <vector>
#include <iostream>
#include <math.h>
#include <memory>
#include <map>
#include <string>
#include <string_view>
#include <mutex>

// using namespace std;

class Samochod
{
public:
    Samochod()
    {
        std::cout << "Constructor Samochod" << std::endl;
    }
    virtual float obliczzasieg() const = 0;
    virtual std::string zwrocnazwe() const = 0;
    virtual ~Samochod()
    {
        std::cout << "Destructor virtualny Samochod" << std::endl;
    }
    // ~Samochod()
    // {
    //     std::cout << "Destructor Samochod" << std::endl;
    // }
};

class Spalinowy : public Samochod
{
    float iloscPaliwaWBaku;
    float ZuzycieNa100Km;

public:
    float getiloscPaliwaWBaku() const { return iloscPaliwaWBaku; }
    float &getiloscPaliwaWBaku() { return iloscPaliwaWBaku; }
    float getZuzycieNa100Km() const { return ZuzycieNa100Km; }
    float &getZuzycieNa100Km() { return ZuzycieNa100Km; }
    float obliczzasieg() const { return iloscPaliwaWBaku / ZuzycieNa100Km; }
    std::string zwrocnazwe() const { return "Spalinowy"; }
    Spalinowy()
    {
        std::cout << "Constructor Spalinowy" << std::endl;
        iloscPaliwaWBaku = 0;
        ZuzycieNa100Km = 1;
    }
    Spalinowy(int a, int b)
    {
        std::cout << "Constructor Parametryczny Spalinowy" << std::endl;
        iloscPaliwaWBaku = a;
        ZuzycieNa100Km = b;
    }
    ~Spalinowy()
    {
        std::cout << "Destructor Spalinowy" << std::endl;
    }
};

class Elektyczny : public Samochod
{

    float iloscMpocyWBateriach;
    float ZuzycieMocyNaKm;

public:
    float getiloscMpocyWBateriach() const { return iloscMpocyWBateriach; }
    float &getiloscMpocyWBateriach() { return iloscMpocyWBateriach; }
    float getZuzycieMocyNaKm() const { return ZuzycieMocyNaKm; }
    float &getZuzycieMocyNaKm() { return ZuzycieMocyNaKm; }
    float obliczzasieg() const { return iloscMpocyWBateriach / ZuzycieMocyNaKm; }
    std::string zwrocnazwe() const { return "Elektyczny"; }
    Elektyczny()
    {
        std::cout << "Constructor Elektyczny" << std::endl;
        iloscMpocyWBateriach = 0;
        ZuzycieMocyNaKm = 1;
    }
    Elektyczny(int a, int b)
    {
        std::cout << "Constructor Parametryczny Elektyczny" << std::endl;
        iloscMpocyWBateriach = a;
        ZuzycieMocyNaKm = b;
    }
    ~Elektyczny()
    {
        std::cout << "Destructor Elektyczny" << std::endl;
    }
};

class test
{
    int *ptr;

public:
    test()
    {
        std::cout << "Constructor" << std::endl;
        ptr = new int;
    }
    ~test()
    {
        std::cout << "Destructor" << std::endl;
        delete ptr;
    }

    test(const test &test1)
    {
        std::cout << "Copy Constructor" << std::endl;
        ptr = new int;
        *ptr = *test1.ptr;
    }
    test &operator=(const test &test1)
    {
        std::cout << "Copy Assigment Operator" << std::endl;
        *ptr = *test1.ptr;
        return *this;
    }
    test(test &&test1)
    {
        std::cout << "Move Constructor" << std::endl;
        ptr = new int;
        *ptr = *test1.ptr;
        test1.ptr = nullptr;
    }
    test &operator=(test &&test1)
    {
        std::cout << "Move Assigment Operator" << std::endl;
        *ptr = *test1.ptr;
        test1.ptr = nullptr;
        return *this;
    }
};

class bazowa
{
    int a;

public:
    bazowa(){};
    ~bazowa(){};
    virtual void print(std::string nazwa)
    {
        std::cout << nazwa << " bazowa" << std::endl;
    }
};

class pochodna final : public bazowa
{
public:
    pochodna(){};
    ~pochodna(){};
    void print(std::string nazwa) override
    {
        std::cout << nazwa << " pochodna" << std::endl;
    }
};

// override - widać ze ona jest wirtualna, jeśli nie jest to wyskoczy błąd
// final - ostateczna ostateczność

// enum
int main()
{
    // vector<int> wek1 {1,2,3,4,5};
    // vector<int> wek2;
    // wek2.reserve(wek1.size());

    // for (const auto & i : wek1)
    // {
    //     wek2.emplace_back(i*10);
    //     // i = 3;
    // }
    // for (int i = 0; i < wek2.size(); i++)
    // {
    //     cout << wek2[i] << endl;
    // }

    // auto test1 = std::make_unique<test>();
    // auto test2 = std::move(test1);
    // auto test3 = static_cast<std::unique_ptr<test> &&>(test2);
    // auto test4(std::move(test3));

    // if (test1.release())
    //     std::cout << "test1" << std::endl;
    // if (test2.release())
    //     std::cout << "test2" << std::endl;
    // if (test3.release())
    //     std::cout << "test3" << std::endl;
    // if (test4.release())
    //     std::cout << "test4" << std::endl;

    std::multimap<int, char> dict{
        {1, 'A'},
        {2, 'B'},
        {2, 'C'},
        {2, 'D'},
        {4, 'E'},
        {3, 'F'}};

    auto range = dict.equal_range(2);

    for (auto i = range.first; i != range.second; ++i) //idziemy po adresach
    {
        std::cout << i->first << ": " << i->second << '\n';
    }

    // test A;
    // test B = test();

    // std::mutex to_mutex;
    // lock_guard mutex_lock(to_mutex);

    // test a;
    // test b = a;
    // a = test();
    // test c = test();

    // std::unique_ptr<Samochod> spalinowy = std::make_unique<Spalinowy>();
    // auto elektryczny = std::make_unique<Elektyczny>();

    // std::unique_ptr<bazowa> A = std::make_unique<bazowa>();
    // A->print("A");
    // std::unique_ptr<bazowa> B = std::make_unique<pochodna>();
    // B->print("B");
    // std::unique_ptr<pochodna> C = std::make_unique<pochodna>();
    // C->print("C");

    // vector<unique_ptr<Samochod>> samochody;
    // auto spalinowy = make_unique<Spalinowy>(2, 4);
    // auto elektryczny = make_unique<Elektyczny>(2, 6);

    // samochody.push_back(spalinowy);
    // samochody.push_back(elektryczny);
    // for (int i = 0; i < samochody.size(); i++)
    // {
    //     cout << samochody[i]->zwrocnazwe() << endl;
    //     cout << samochody[i]->obliczzasieg() << endl;
    // }
    // return 0;
}
