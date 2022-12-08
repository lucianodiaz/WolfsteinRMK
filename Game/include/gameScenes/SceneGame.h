#pragma once
#include <SFML/System/NonCopyable.hpp>
#include <Scene/SceneStateMachine.h>
#include "Scene/Scene.h"
#include "GUI/Gui.h"

class World;
class SceneGame :
    public Scene , private sf::NonCopyable
{
public:
    
    SceneGame(SceneStateMachine& ssm,Window& window, World& world);

    void onCreate() override;
    void onDestroy() override;

    void onActivate() override;
    void onDeactivate() override;
    void setSwitchToScene(unsigned int id);

    void processInput() override;
    void update(sf::Time deltaTime) override;
    void draw(Window& window) override;

    
private:
    void initGUI();
    unsigned int _switchToState;
    Frame _objective1;
    Frame _objective2;
    World& _world;
    Window& _window;
    SceneStateMachine& _sceneStateMachine;
};

