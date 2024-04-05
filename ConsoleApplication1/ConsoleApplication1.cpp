#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

class Object {
public:
    virtual void someMethod() = 0; // Абстрактный метод
    virtual ~Object() {} // Виртуальный деструктор
};

class ConcreteObject1 : public Object {
public:
    void someMethod() override {
        std::cout << "ConcreteObject1::someMethod()" << std::endl;
    }
};

class ConcreteObject2 : public Object {
public:
    void someMethod() override {
        std::cout << "ConcreteObject2::someMethod()" << std::endl;
    }
};

class ConcreteObject3 : public Object {
public:
    void someMethod() override {
        std::cout << "ConcreteObject3::someMethod()" << std::endl;
    }
};

class Storage {
private:
    std::vector<Object*> objects;
public:
    Storage() {}

    ~Storage() {
        for (auto obj : objects) {
            delete obj; // Удаление объектов
        }
    }

    void addObject(Object* obj) {
        objects.push_back(obj); // Добавление объекта в хранилище
    }

    void removeObject(int index) {
        if (index >= 0 && index < objects.size()) {
            delete objects[index]; // Удаление объекта
            objects.erase(objects.begin() + index); // Удаление указателя из вектора
        }
    }

    void callMethod(int index) {
        if (index >= 0 && index < objects.size()) {
            objects[index]->someMethod(); // Вызов метода объекта
        }
    }

    int getCount() const {
        return objects.size(); // Получение количества объектов в хранилище
    }
};

int main() {
    srand(static_cast<unsigned int>(time(nullptr))); // Используем static_cast для приведения типа

    Storage storage;

    const int actions = 10000;

    for (int i = 0; i < actions; ++i) {
        int action = rand() % 3; // Случайное действие

        switch (action) {
        case 0: {
            // Добавление объекта
            int type = rand() % 3; // Случайный тип объекта
            if (type == 0) {
                storage.addObject(new ConcreteObject1());
            }
            else if (type == 1) {
                storage.addObject(new ConcreteObject2());
            }
            else {
                storage.addObject(new ConcreteObject3());
            }
            break;
        }
        case 1: {
            // Использование объекта
            int count = storage.getCount();
            if (count > 0) { // Проверка наличия объектов в хранилище
                int index = rand() % count; // Случайный индекс объекта
                storage.callMethod(index);
            }
            break;
        }
        case 2: {
            // Удаление объекта
            int count = storage.getCount();
            if (count > 0) { // Проверка наличия объектов в хранилище
                int index = rand() % count; // Случайный индекс объекта
                storage.removeObject(index);
            }
            break;
        }
        }
    }

    return 0;
}
