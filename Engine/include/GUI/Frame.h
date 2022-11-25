#pragma once
#include "Container.h"
#include "Input/ActionTarget.h"

class Frame :
    public Container, protected ActionTarget<int>
{
public:
    Frame(const Frame&) = delete;
    Frame& operator=(const Frame&) = delete;

    using ActionTarget<int>::FuncType;

    Frame(sf::RenderWindow& window);

    virtual ~Frame();


    void processEvents();
    bool processEvent(const sf::Event& event);

    void bind(int key, const FuncType& callback);
    void unbind(int key);

    void draw();

    virtual sf::Vector2f getSize()const override;

private:
    sf::RenderWindow& _window;


    virtual bool processEvent(const sf::Event& event, const sf::Vector2f& parent_pos)override;
    virtual void processEvents(const sf::Vector2f& parent_pos)override;
};

