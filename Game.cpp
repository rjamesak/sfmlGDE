#include "Game.h"
#include <iostream>

void main(int argc, void ** argv[])
{
	//Program Entry Point
	Game game;
	while (!game.getWindow()->isDone()) {
		//Game Loop
		game.handleInput();
		game.update();
		game.render();
		//sf::sleep(sf::seconds(0.5));
		game.restartClock();
	}
}

Game::Game() : m_window("Chapter 2", sf::Vector2u(800, 600))
{
	//m_mushroomTexture.loadFromFile("tinyShroom_red.png");
	m_mushroomTexture.loadFromFile("spritesheet.png");
	m_mushRect.left = 11;
	m_mushRect.top = 108;
	m_mushRect.width = 45;
	m_mushRect.height = 36;
	m_mushroom.setTexture(m_mushroomTexture);
	m_mushroom.setTextureRect(m_mushRect);
	m_increment = sf::Vector2i(400, 400); //400 pixels per second
}

Game::~Game()
{
}

void Game::handleInput()
{
	m_window.update();
}

void Game::update()
{
	m_window.update();
	moveMushroom();
}

void Game::render()
{
	m_window.beginDraw(); //Clear
	m_window.draw(m_mushroom);
	m_window.endDraw(); //Display

}

Window * Game::getWindow()
{
	return &m_window;
}

sf::Time Game::getElapsed()
{
	return m_elapsed;
}

void Game::restartClock()
{
	m_elapsed = m_clock.restart();
}

void Game::moveMushroom()
{
	sf::Vector2u l_windSize = m_window.getWindowSize();
	sf::Vector2u l_textSize (static_cast<unsigned int>(m_mushRect.width), static_cast<unsigned int> (m_mushRect.height));

	if ((m_mushroom.getPosition().x > l_windSize.x - l_textSize.x &&
		m_increment.x > 0) || (m_mushroom.getPosition().x < 0 && m_increment.x < 0)) {
		m_increment.x = -m_increment.x;
	}

	if ((m_mushroom.getPosition().y > l_windSize.y - l_textSize.y && m_increment.y > 0) ||
		(m_mushroom.getPosition().y < 0 && m_increment.y < 0)) {
		m_increment.y = -m_increment.y;
	}

	float fElapsed = m_elapsed.asSeconds();

	//movement is per second
	m_mushroom.setPosition(m_mushroom.getPosition().x + (m_increment.x * fElapsed),
		m_mushroom.getPosition().y + (m_increment.y * fElapsed));
}
