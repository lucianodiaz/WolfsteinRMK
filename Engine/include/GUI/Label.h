#pragma once
#include "Widget.h"
class Label :
    public Widget
{
public:
    Label(const Label&) = delete;
    Label& operator=(const Label&) = delete;

    Label(const std::string& text, Widget* parent = nullptr);

    virtual ~Label();

    void setText(const std::string& text);
    void setCharacterSize(unsigned int size);
    unsigned int getCharacterSize()const;
    void setTextColor(const sf::Color& color);
    const sf::FloatRect& getGlobalBound()const { return _text.getGlobalBounds(); } ;
    virtual sf::Vector2f getSize()const override;
private:
    sf::Text _text{};

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};

