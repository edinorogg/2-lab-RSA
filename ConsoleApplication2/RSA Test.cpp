#include <iostream>
#include <random>
#include <string>
#include <cmath>
#include <unordered_set>
#include <sstream>
#include <boost/multiprecision/cpp_int.hpp>
#include <boost/random/random_device.hpp>
#include <boost/random.hpp>
#include <fstream>

using namespace boost::multiprecision;
namespace mp = boost::multiprecision;
using std::cout;
using std::cin;
using std::endl;
using std::string;
enum class Test{
    FermaTest,
    MillerRabinTest,
    SoloveiStrassenTest
};


cpp_int eucledian_algorythm(cpp_int a, cpp_int b) {

    while (b != 0) {
        cpp_int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}
cpp_int pow_big_int(cpp_int base, cpp_int exponent) {

    cpp_int result = 1;
    while (exponent > 0) {
        if (exponent & 1) {
            result = result * base;
        }
        base = base * base;
        exponent >>= 1;
    }
    return result;
}
cpp_int mod_inverse(cpp_int a, cpp_int m) {
    cpp_int m0 = m;
    cpp_int x0 = 0, x1 = 1;

    while (a > 1) {
        cpp_int q = a / m;
        cpp_int t = m;
        m = a % m;
        a = t;
        t = x0;
        x0 = x1 - q * x0;
        x1 = t;
    }

    if (x1 < 0) {
        x1 += m0;
    }

    return x1;
}

class SymbolCalculator {
public:
   
    bool check(cpp_int const &a,cpp_int const &p) {
        if ((a < 0) || (a > p))
            throw std::invalid_argument("a должно быть положительным числом и меньше p.");
        else {
            return true;
        }
    }
    cpp_int legendre_symbol(cpp_int a, cpp_int p) {
        cout << "a is " << a << endl;
        cout << "p is " << p << endl;
        check(a, p);
        if (p <= 0 || (p % 2 == 0 && p != 2)) {
            throw std::invalid_argument("p должно быть простым числом или 2");
        }
        a = a % p;
        if (a < 0) {
            a += p; // приводим a к положительному значению в диапазоне [0, p)
        }
        if (a == 0) {
            return 0;
        }
        if (a == 1) {
            return 1;
        }
        if (a % 2 == 0) {
            return legendre_symbol(a / 2, p) * pow_big_int(-1, (p * p - 1) / 8);
        }
        else {
            return legendre_symbol(p % a, a) * pow_big_int(-1, (a - 1) * (p - 1) / 4);
        }
    }

    cpp_int jacobi_symbol(cpp_int a, cpp_int n) {
        if (n <= 0 || n % 2 == 0) {
            throw std::invalid_argument("n должно быть нечетным положительным числом");
        }
        if (n == 1) {
            return 1;
        }
        a = a % n;
        if (a < 0) {
            a += n; // приводим a к положительному значению в диапазоне [0, n)
        }
        if (a == 0) {
            return 0;
        }
        if (a == 1) {
            return 1;
        }
        if (a % 2 == 0) {
            return jacobi_symbol(a / 2, n) * pow_big_int(-1, (n * n - 1) / 8);
        }
        else {
            if (a % 4 == 3 && n % 4 == 3) {
                return -jacobi_symbol(n, a);
            }
            else {
                return jacobi_symbol(n, a);
            }
        }
    }


};
class PrimalityTest {
protected:

    virtual bool customize_test(const cpp_int& test_value) = 0;
    virtual int iterations_counter(const float& is_prime_min_probability) = 0;
    long randomiser() {
        std::random_device random_device; //рандомайзер без параметров
        std::mt19937 generator(random_device());
        std::uniform_int_distribution<> dis(500, 10000);
        return dis(generator);
    }
    void randomiser(cpp_int const& min, cpp_int const& max, cpp_int &a) { //рандомайзер с параметрами

        boost::random::random_device gen;
        boost::random::uniform_int_distribution<cpp_int> dist(min, max);
        a = dist(gen);
    }
    void randomiser_bit_length(int n, cpp_int &test_value) {
        if ((n > 10000) || (n < 1)) {
            throw(std::invalid_argument)"Битовая длина числа не может иметь параметр более 10000 или менее 1";

        }
        cpp_int min = pow_big_int(2, n - 1);
        cpp_int max = pow_big_int(2, n) - 1;
        boost::random::random_device gen;
        boost::random::uniform_int_distribution<cpp_int> ui(min, max);
       
        test_value = ui(gen) | 1;
    }
    bool cheking_if_even(long const& value) {
        if (value && 1 == 1) {
            return true;
        }
        else {
            return false;
        }
    }
    void Progress_bar(int i) {
        if (i % 10 == 0)
        {
            cout << ".";
        }
        if (i % 100 == 0) {
            cout << "\n количество тестов " << i << "\n";
        }
    }
public: cpp_int runTest(float is_prime_min_probability, int key_length) { //сюда ещё нужно будет вписать название теста в качестве принимаемого параметра./////
        bool test_failed = false;
        int iterations_amount = iterations_counter(is_prime_min_probability);
        int succesful_operations = 0;
        int amount_of_tests = 0;
        int i = 0;
        cpp_int test_value = 0;
        while (succesful_operations != iterations_amount) {
            randomiser_bit_length(key_length, test_value);
            i = 0;
            test_failed = false; //обнуляем переменные при выходе из цикла
            succesful_operations = 0;
            for (size_t i = 0; i < iterations_amount; i++)
            {
                try {
                    customize_test(test_value);
                    succesful_operations++;
                }
                catch (std::exception &e) {
                    amount_of_tests++;
                    test_failed = true;
                    Progress_bar(amount_of_tests);
                    break;
                }

            }
        }

        cout << "Количество тестов для поиска: " << amount_of_tests + 1 << endl;
        return test_value;
    }




};

class FermaTest : public PrimalityTest {
protected:
    int iterations_counter(const float& is_prime_min_probability) override;
    bool customize_test(const cpp_int& test_value)  override;
};

int FermaTest::iterations_counter(const float& is_prime_min_probability) {
    if (is_prime_min_probability < 0.5 || is_prime_min_probability >= 1.0) {
        throw(std::exception)"Ошибка: Минимальная вероятность должна быть в диапазоне[0.5, 1).";
    }
    else {
        int k = static_cast<int>(std::ceil(std::log(1.0 / (1.0 - is_prime_min_probability)) / std::log(2.0)));
        return k;
    }

}

bool FermaTest::customize_test(const cpp_int& test_value)
{

    std::unordered_set<int> uniqueNumbers;
    if (test_value < 1) {
        return false;
    }
    else if (test_value <= 3) {
        return true;
    }
    cpp_int a = 0;
    randomiser(2, test_value - 1, a);
    //creating_a(a, uniqueNumbers, test_value);

    if (powm(a, test_value - 1, test_value) == 1) {
        return true;
    }
    else {
        throw(std::exception)"Число не прошло тест";
        return false;
    }


}

class MillerRabinTest : public PrimalityTest {
protected:
    int iterations_counter(const float& is_prime_min_probability) override;
    bool customize_test(const cpp_int& test_value) override;
};
int MillerRabinTest::iterations_counter(const float& is_prime_min_probability) {
    if (is_prime_min_probability < 0.5 || is_prime_min_probability >= 1.0) {
        throw(std::exception)"Ошибка: Минимальная вероятность должна быть в диапазоне[0.5, 1).";
    }
    double q = 1.0 - is_prime_min_probability; // Вероятность ошибки
    int k = std::ceil(std::log(q) / std::log(0.25)); // Вычисление k
    return k;
}

bool MillerRabinTest::customize_test(const cpp_int& test_value) {
    if (test_value < 1) return false;
    if (test_value <= 3) return true;
    cpp_int d = test_value - 1;
    int poweroftwo = 0;
    while (d % 2 == 0) {
        d /= 2;
        poweroftwo++;
    }
    cpp_int a = 0;
    randomiser(2, test_value - 2, a);
    cpp_int x = powm(a, d, test_value); //тут возможно ошибка
    if (x == 1 || x == test_value - 1) {
        return true;
    }
    for (size_t i = 0; i < poweroftwo - 1; i++)
    {
        x = powm(x, 2, test_value);
        if (x == 1) {
            throw(std::exception)"Число не прошло тест";
        }
        else if (x == test_value - 1) {
            return true;
        }
    }
    throw(std::exception)"Число не прошло тест";
}
class SoloveiStrassenTest : public PrimalityTest {
protected:
    bool customize_test(const cpp_int& test_value) override;
    int iterations_counter(const float& is_prime_min_probability) override;
};
int SoloveiStrassenTest::iterations_counter(const float& is_prime_min_probability) {

    if (is_prime_min_probability < 0.5 || is_prime_min_probability >= 1.0) {
        throw(std::exception)"Ошибка: Минимальная вероятность должна быть в диапазоне[0.5, 1).";
    }
    else {
        int k = static_cast<int>(std::ceil(std::log(1.0 / (1.0 - is_prime_min_probability)) / std::log(2.0)));
        return k;
    }
}
bool SoloveiStrassenTest::customize_test(const cpp_int &test_value) {
    cpp_int a = 0;
    randomiser(2, test_value-2, a);
    //cout << "a is " << a << endl;
    //cout << "test value is " << test_value << endl;
    SymbolCalculator symbolCalculator;
    if (eucledian_algorythm(a, test_value) > 1) {
        throw(std::exception)"Число не прошло тест";
    }
    cpp_int jacobisymbol = 0;
    try {
        jacobisymbol = symbolCalculator.jacobi_symbol(a, test_value);
    }
    catch(...){
    };

    cpp_int s = powm(a, (test_value - 1) / 2, test_value);
    if (s == test_value - 1) {
        s = -1;
    }
    cout << "s is " << s << endl;
    if (jacobisymbol != s) {
        throw(std::exception)"Число не прошло тест";
    }
    else {
        return true;
    }
}

class RSA {
public:
    void encryption();
protected:
    void get_key(Test using_test, int n, cpp_int& q, cpp_int& p, double is_prime_min_probability);
    Test choose_test();
    [[nodiscard]] int get_key_length();
    [[nodiscard]] double get_probability();
    void encrypt_file(string name, const cpp_int &e,const cpp_int &d, const cpp_int &n);
    void open_file_in_binary_mode(const string& name, std::vector<unsigned char>& bytes);
    template<typename T>
    void print(const std::vector<T>& test);

};

void RSA::get_key(Test using_test, int n, cpp_int& q, cpp_int& p, double is_prime_min_probability) {
    switch (using_test)
    {
    case Test::FermaTest: {
        FermaTest fermaTest;
        p = fermaTest.runTest(is_prime_min_probability, n);
        q = fermaTest.runTest(is_prime_min_probability, n);
        break;
    }
    case Test::MillerRabinTest: {

        MillerRabinTest MillerRabTest;
        p = MillerRabTest.runTest(is_prime_min_probability, n);
        q = MillerRabTest.runTest(is_prime_min_probability, n);
        break;
    }
    case Test::SoloveiStrassenTest: {
        SoloveiStrassenTest SolovStrTest;
        p = SolovStrTest.runTest(is_prime_min_probability, n);
        q = SolovStrTest.runTest(is_prime_min_probability, n);
        break;
    }
    default:
        //Do nothing
        break;
    }
}

Test RSA::choose_test() {
    string input;
    int c;
    cout << "Выберите каким тестом вы хотите воспользоваться для генерации ключа" << endl;
    cout << "1. Тест Миллера-Рабина" << endl;
    cout << "2. Тест Ферма" << endl;
    cout << "3. Тест Соловея-Штрассена" << endl;
    do {
        cin >> input;

        std::stringstream ss(input);

        if (ss >> c) {
            if (c > 3 || c < 1) {
                cout << "Введённое вами значение должно соответствовать номеру варианта." << std::endl;
                cin.clear();
            }
            else {
                break;
            }
        }
        else {
            cout << "Ошибка: Введенное значение не является числом. Попробуйте снова." << std::endl;
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    } while (c > 3 || c < 1);
    switch (c)
    {
    case 1:
        return Test::MillerRabinTest;
        break;
    case 2:
        return Test::FermaTest;
        break;
    case 3:
        return Test::SoloveiStrassenTest;
        break;
    default:
        throw(std::exception)"Что-то пошло не так при выборе теста";
    }
}
[[nodiscard]] int RSA::get_key_length() {
    cout << "Введите длину ключа в битах. Длина ключа ограничивается 1024 битами" << endl;
string input;
    while (true) {
        int length_value;
        cout << "Введите число: ";
        cin >> input;

       std::stringstream ss(input);

        if (ss >> length_value) {
            if (length_value < 1 || length_value > 1024) {
                cout << "Ошибка: Введенное значение  не должно быть больше 1024 или меньше 0." << endl;
                cin.clear();
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }
            else {
                return length_value;
                break;
            }
        }
        else {
            cout << "Ошибка: Введенное значение не является числом. Попробуйте снова." << endl;
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }
}
[[nodiscard]] double RSA::get_probability() {
    string input;
    double is_prime_min_probablity;
    while(true){
    
    cout << "Пожалуйста, введите значение минимальной вероятности для числа [0.5.. 1) " << endl;
    cin >> input;
    std::stringstream ss(input);
    if (ss >> is_prime_min_probablity) {
        if (is_prime_min_probablity < 0.5 || is_prime_min_probablity >= 1) {
            std::cout << "Ошибка: Введенное значение  не должно быть больше 1 и меньше 0.5" << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        else {
            return is_prime_min_probablity;
            break;
        }
    }
    else {
        std::cout << "Ошибка: Введенное значение не является числом. Попробуйте снова." << std::endl;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    }


}

void RSA::encryption() {
    int key_length = get_key_length();
    double is_prime_min_probability;
    is_prime_min_probability = get_probability();
    Test variant = choose_test();
    cpp_int q, p, d = 0;
    long e = 0;
    int check = 0;
    get_key(variant, key_length, q, p, is_prime_min_probability);
    cout << "p is " << p << endl;
    cout << "q is " << q << endl;
    cpp_int n = p * q;
    cout << "n is " << n << endl;
    cpp_int EilerFunction = (p - 1) * (q - 1);
    check = 0;
    e = 65537;
    //do {
    //    e = randomiser();
    //    check = eucledian_algorythm(e, EilerFunction);
    //} while (check != 1);
    //check = 0;
    d = 0;
    do {
        d = mod_inverse(e, EilerFunction);
    } while (d < (pow(n, 1 / 4) * 1 / 3));
    cout << "your private key is ( " << d << ',' << n << " )" << endl;
    cout << "your public key is ( " << e << ',' << n << " )" << endl;
    try {
     
        encrypt_file("new.txt", e, d, n);
    }
    catch (std::exception& e) {
        cout << e.what();
    }
  
}


string convert_number_to_text(const std::vector<cpp_int> &decrypted_bytes) {
    string output;
    for (size_t i = 0; i < decrypted_bytes.size(); i++)
    {
        output += static_cast<unsigned char>(decrypted_bytes[i]);
    }
    return output;
}
 void RSA::open_file_in_binary_mode(const string& name, std::vector<unsigned char> & bytes ){
    std::ifstream file(name, std::ios::binary);
        if(file.is_open()) {
            char byte;
            while (file.get(byte)) { // читаем файл посимвольно
                bytes.push_back(static_cast<unsigned char>(byte)); // преобразуем символ в беззнаковый байт и добавляем в вектор
            }
            file.close(); // закрываем файл
        }
        else {
            throw(std::exception)"Could not open file";
        };
}
void RSA::encrypt_file(string name, const cpp_int& e, const cpp_int& d, const cpp_int& n) {
    std::vector<unsigned char> bytes;
    std::vector<cpp_int> encrypted_bytes;
    std::vector<cpp_int> decrypted_bytes;
    open_file_in_binary_mode(name, bytes);
    int number = 0;
    if (!bytes.empty()) {
        for (int i = 0; i < bytes.size(); i++) {
            cpp_int number = static_cast<int>(bytes[i]);
            cpp_int C = powm(number, e, n);
            //cout << C << endl;
            encrypted_bytes.push_back(C);
            cpp_int M = powm(C, d, n);
            //cout << M << endl;
            decrypted_bytes.push_back(M);
        }
    }
    cout << convert_number_to_text(encrypted_bytes);
    cout << "\n";
    cout << convert_number_to_text(decrypted_bytes);

}


int main() {
    setlocale(LC_ALL, "Russian");
    clock_t start = clock();
    std::vector<unsigned char> bytes;
    RSA test;
    test.encryption();


    clock_t end = clock();
    double seconds = (double)(end - start) / CLOCKS_PER_SEC;
    cout << "\nTime spent: " << seconds;
  
        return 0;
}

