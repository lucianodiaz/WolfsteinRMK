#pragma once
#include <World.h>
#include "Scene/Scene.h"
#include <Scene/SceneStateMachine.h>
#include <GUI/Gui.h>


class SceneMainMenu :
    public Scene
{
public:
    SceneMainMenu(SceneStateMachine& ssm, Window& window);

    void onCreate() override;
    void onDestroy() override;

    void onActivate() override;
    void onDeactivate() override;
    void setSwitchToScene(unsigned int id);

    void processInput() override;
    void update(sf::Time deltaTime) override;
    void draw(Window& window) override;

    void initGUI();

private:
    SceneStateMachine& _sceneStateMachine;
    Window& _window;
    unsigned int _switchToState;

    sf::Sprite _menuSprite;

    Frame _mainMenu;

    enum Status
    {
        StatusMainMenu,
        StatusGame,
        StatusConfiguration,
        StatusPaused,
        StatusExit
    } _status;
};

