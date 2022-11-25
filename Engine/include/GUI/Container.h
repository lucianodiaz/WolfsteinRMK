#pragma once
#include "Widget.h"

class Layout;

class Container :
    public Widget
{
public:
    Container(const Container&) = delete;
    Container& operator=(const Container&) = delete;

    Container(Widget* parent = nullptr);
    virtual ~Container();

    void setLayout(Layout* layout);
    Layout* getLayout()const;
    virtual sf::Vector2f getSize() const override;

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    virtual bool processEvent(const sf::Event& event, const sf::Vector2f& parent_pos)override;
    virtual void processEvents(const sf::Vector2f& parent_pos)override;

private:
    Layout* _layout;
};

