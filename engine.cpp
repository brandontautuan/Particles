#include "Engine.h"
#include <ctime>
#include <cstdlib>

Engine::Engine()
{
    VideoMode vm = VideoMode::getDesktopMode();
    m_Window.create(vm, "Particles", Style::Default);
}

void Engine::run()
{
    srand(static_cast<unsigned int>(time(nullptr)));

    Clock clock;

    cout << "Starting Particle unit tests..." << endl;
    Particle p(m_Window, 4, { static_cast<int>(m_Window.getSize().x) / 2, static_cast<int>(m_Window.getSize().y) / 2 });
    p.unitTests();
    cout << "Unit tests complete.  Starting engine..." << endl;

    while (m_Window.isOpen())
    {
        Time dt = clock.restart();
        float dtAsSeconds = dt.asSeconds();
        input();
        update(dtAsSeconds);
        draw();
    }
}

void Engine::input()
{
    Event event;
    while (m_Window.pollEvent(event))
    {
        if (event.type == Event::Closed)
        {
            m_Window.close();
        }
        else if (event.type == Event::KeyPressed && event.key.code == Keyboard::Escape)
        {
            m_Window.close();
        }
        else if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left)
        {
            Vector2i mousePos(event.mouseButton.x, event.mouseButton.y);
            for (int i = 0; i < 5; ++i)
            {
                int numPoints = 25 + rand() % 26;
                m_particles.emplace_back(m_Window, numPoints, mousePos);
            }
        }
    }
}

void Engine::update(float dtAsSeconds)
{
    auto it = m_particles.begin();
    while (it != m_particles.end())
    {
        if (it->getTTL() > 0.0f)
        {
            it->update(dtAsSeconds);
            ++it;
        }
        else
        {
            it = m_particles.erase(it);
        }
    }
}

void Engine::draw()
{
    m_Window.clear();
    for (auto& particle : m_particles)
    {
        m_Window.draw(particle);
    }
    m_Window.display();
}
