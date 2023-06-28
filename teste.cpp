#include <iostream>
#include <string>

class Person {
private:
    std::string name;
    int age;

public:
    // Constructor
    Person(const std::string& personName, int personAge) {
        name = personName;
        age = personAge;
    }

    // Getter methods
    std::string getName() const {
        return name;
    }

    int getAge() const {
        return age;
    }

    // Setter methods
    void setName(const std::string& newName) {
        name = newName;
    }

    void setAge(int newAge) {
        age = newAge;
    }

    // Overload the << operator
    friend std::ostream& operator<<(std::ostream& os, const Person& person) {
        os << "Name: " << person.name << ", Age: " << person.age;
        return os;
    }
};

int main() {
    // Create an instance of the Person class
    Person person("John Doe", 30);

    // Display the person object using cout
    std::cout << person << std::endl;

    return 0;
}
