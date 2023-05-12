enum class Events;
class Entity;
class Observer;
class Subject
{
public:

    void addObserver(Observer* observer);

    void notify(const Entity& entity, Events event);

private:
    Observer* observer;
};
