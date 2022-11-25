#pragma once
#include <SFML/Graphics.hpp>
#include "Scene/SceneStateMachine.h"
#include "Scene/Scene.h"

class SceneSplashScreen :
    public Scene
{
public:
    SceneSplashScreen(SceneStateMachine& ssm, Window& window);

    void onCreate() override;
    void onDestroy() override;

   
    void onActivate() override;
    void onDeactivate()override;

    void setSwitchToScene(unsigned int id);

    void processInput() override;
    void update(sf::Time deltaTime) override;
    void draw(Window& window) override;

private:
    sf::Sprite _splashSprite;

    SceneStateMachine& _sceneStateMachine;
    Window& _window;

    float _showForSeconds;
    bool _skip{};
    float _currentSeconds;

    unsigned int _switchToState;
};

