#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include<SFML/Audio.hpp>
using namespace std;
using namespace sf;

const int rows = 10;
const int cols = 16;
const float c_size = 40.0f;

int main()
{

    RenderWindow front(VideoMode(480, 480), "Game Start Interface");

    Vector2f buttonSize(200, 50);
    Vector2f buttonPosition(140, 220);

    Color buttonColor(84, 104, 130);//RGB//44,62,80
    Color hoverColor(0, 0, 230);

    RectangleShape button1(buttonSize);
    RectangleShape button2(buttonSize);
    RectangleShape button3(buttonSize);

    button1.setPosition(buttonPosition);
    button2.setPosition(buttonPosition.x, buttonPosition.y + 70);
    button3.setPosition(buttonPosition.x, buttonPosition.y + 140);
    Texture back;
    back.loadFromFile("back3.png");


    Sprite background;
    background.setTexture(back);
    /*background.setScale(Vector2f(800, 600)); */



    /*Font start;
    start.loadFromFile("freedom.ttf");*/
    Font font;
    font.loadFromFile("arial.ttf");

    /*Text controls("Maze Runner: FAST Escape",font ,36);
    controls.setStyle(Text::Bold);
    controls.setStyle(Text::Underlined);
    controls.setFillColor(Color::Red);
    */



    Text text1("Level 1", font, 24);
    Text text2("Level 2", font, 24);
    Text text3("Bonus Level", font, 24);

    text1.setPosition(button1.getPosition().x + 50, button1.getPosition().y + 10);
    text2.setPosition(button2.getPosition().x + 50, button2.getPosition().y + 10);
    text3.setPosition(button3.getPosition().x + 50, button3.getPosition().y + 10);
    /*controls.setPosition(text2.getPosition().x-175
        , text2.getPosition().y - 170);*/
        /*controls.setFillColor(Color::Red);*/

    int currentLevel = 0;
    bool nextLevel = false, restart = true;
    Music back_m, level;
    level.openFromFile("level.ogg");
    level.setVolume(50);
    back_m.openFromFile("back_m.ogg");
    back_m.setLoop(true);
    back_m.setVolume(10);




    while (front.isOpen()) {
        Event event;
        while (front.pollEvent(event)) {
            if (event.type == Event::Closed)
                front.close();
        }

        Vector2f mousePos = front.mapPixelToCoords(Mouse::getPosition(front));

        button1.setFillColor(button1.getGlobalBounds().contains(mousePos) ? hoverColor : buttonColor);
        button2.setFillColor(button2.getGlobalBounds().contains(mousePos) ? hoverColor : buttonColor);
        button3.setFillColor(button3.getGlobalBounds().contains(mousePos) ? hoverColor : buttonColor);



        currentLevel = 0;
        if (Mouse::isButtonPressed(Mouse::Left)) {
            if (button1.getGlobalBounds().contains(mousePos)) {
                currentLevel = 1;
                nextLevel = true;

                break;
            }
            else if (button2.getGlobalBounds().contains(mousePos)) {
                currentLevel = 2;
                nextLevel = true;

                break;
            }
            else if (button3.getGlobalBounds().contains(mousePos)) {
                currentLevel = 3;
                nextLevel = true;
                break;
            }
            restart = false;
            /* currentState = extra;*/

        }
        /*}*/


        text3.setOrigin((Vector2f(10.0, -1.0)));

        back_m.play();

        front.draw(background);
        front.draw(button1);
        front.draw(button2);
        front.draw(button3);
        front.draw(text1);
        front.draw(text2);
        /*front.draw(controls);*/
        front.draw(text3);
        front.display();
    }

    while (nextLevel && currentLevel > 0 && currentLevel <= 3)//1,1,1
    {
        switch (currentLevel)
        {

        case 1:
        {
            int score = 0;
            RenderWindow window(VideoMode(640, 400), "Maze Runner", Style::Default);

            Texture back;//bacground texture(wood)
            back.loadFromFile("wood.png");

            Sprite background;
            background.setTexture(back);
            background.setScale(
                static_cast<float>(window.getSize().x) / back.getSize().x,
                static_cast<float>(window.getSize().y) / back.getSize().y
            );


            int maze[rows][cols] = {
                {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
                {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
                {1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1},
                {1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1},
                {1, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1},//Easy
                {1, 0, 1, 0, 1, 0, 0, 0, 1, 1, 1, 1, 0, 1, 1, 1},
                {1, 0, 1, 0, 1, 0, 1, 0, 1, 1, 1, 1, 0, 1, 1, 1},
                {1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 1, 1, 1, 1},
                {1, 1, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 1},
                {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}




            };

            RectangleShape cells[rows][cols];
            for (int i = 0; i < rows; ++i) {
                for (int j = 0; j < cols; ++j) {
                    cells[i][j].setSize(Vector2f(c_size - 2, c_size - 2));
                    cells[i][j].setPosition(j * c_size, i * c_size);
                    if (maze[i][j] == 1) {
                        cells[i][j].setFillColor(Color::Black);
                    }
                    else {
                        cells[i][j].setFillColor(Color::White);
                    }
                }
            }
            bool collected1 = false, collected2 = false;

            CircleShape player(15.0f);
            player.setFillColor(Color::Green);
            player.setPosition(c_size + 10, c_size + 10);

            RectangleShape goal(Vector2f(c_size - 10, c_size - 5));//30,35
            goal.setFillColor(Color::Red);

            goal.setPosition(14 * c_size + 5, 8 * c_size + 5);

            CircleShape collectible1(15.0f);
            collectible1.setFillColor(Color::Red);
            collectible1.setPosition(6 * c_size + c_size / 6, 5 * c_size + c_size / 5);//6,5

            CircleShape collectible2(15.0f);
            collectible2.setFillColor(Color::Cyan);
            collectible2.setPosition(12 * c_size + c_size / 6, 6 * c_size + c_size / 5); //12,6
            Font font;
            font.loadFromFile("arial.ttf");
            Text winner, score_d;
            score_d.setFont(font);
            score_d.setFillColor(Color::White);
            score_d.setPosition(Vector2f(10, 10));

            winner.setFont(font);
            winner.setString("Congratulations You Have  Won!");
            winner.setCharacterSize(30);
            winner.setFillColor(Color::Blue);
            winner.setStyle(Text::Bold);
            winner.setPosition(98, 10);
            bool flag = true, win = false;
            Clock clock;
            Text timer;
            timer.setFont(font);
            timer.setCharacterSize(20);
            timer.setFillColor(Color::White);
            timer.setPosition(10, 370);


            float speed = 0.15f;

            while (window.isOpen()) {
                Event evnt;
                while (window.pollEvent(evnt)) {
                    if (evnt.type == Event::Closed)
                    {
                        window.close();
                        return 0;
                    }

                }
                score_d.setString("Score: " + to_string(score));
                float elapsedTime = 30 - clock.getElapsedTime().asSeconds();
                int minutes = elapsedTime / 60;
                int seconds = static_cast<int>(elapsedTime) % 60;
                timer.setString("Time left: " + to_string(minutes) + ":" + (seconds < 10 ? "0" : "") + to_string(seconds));
                if (elapsedTime <= 0) {
                    window.clear();
                    Text gameOverText;
                    gameOverText.setFont(font);
                    gameOverText.setString("Time's up! Game Over!\nStarting the level again");
                    gameOverText.setCharacterSize(30);
                    gameOverText.setFillColor(Color::Red);
                    gameOverText.setPosition(150, 150);
                    window.draw(gameOverText);
                    window.display();
                    sleep(sf::seconds(3));
                    break;
                }
                FloatRect playerBounds = player.getGlobalBounds();

                if (Keyboard::isKeyPressed(Keyboard::Key::Right) && flag) {
                    player.move(speed, 0.0f);
                    FloatRect nextPos = player.getGlobalBounds();
                    for (int i = 0; i < rows; ++i) {
                        for (int j = 0; j < cols; ++j) {
                            if (maze[i][j] == 1 && cells[i][j].getGlobalBounds().intersects(nextPos))
                            {
                                player.move(-speed, 0.0f);
                            }
                        }
                    }
                }
                if (Keyboard::isKeyPressed(Keyboard::Key::Left) && flag) {
                    player.move(-speed, 0.0f);
                    FloatRect nextPos = player.getGlobalBounds();
                    for (int i = 0; i < rows; ++i) {
                        for (int j = 0; j < cols; ++j) {
                            if (maze[i][j] == 1 && cells[i][j].getGlobalBounds().intersects(nextPos)) {
                                player.move(speed, 0.0f);
                            }
                        }
                    }
                }
                if (Keyboard::isKeyPressed(Keyboard::Key::Down) && flag) {
                    player.move(0.0f, speed);
                    FloatRect nextPos = player.getGlobalBounds();
                    for (int i = 0; i < rows; ++i) {
                        for (int j = 0; j < cols; ++j) {
                            if (maze[i][j] == 1 && cells[i][j].getGlobalBounds().intersects(nextPos)) {
                                player.move(0.0f, -speed);
                            }
                        }
                    }
                }
                if (Keyboard::isKeyPressed(Keyboard::Key::Up) && flag) {
                    player.move(0.0f, -speed);
                    FloatRect nextPos = player.getGlobalBounds();
                    for (int i = 0; i < rows; ++i) {
                        for (int j = 0; j < cols; ++j) {
                            if (maze[i][j] == 1 && cells[i][j].getGlobalBounds().intersects(nextPos)) {
                                player.move(0.0f, speed);
                            }
                        }
                    }
                }


                if (player.getGlobalBounds().intersects(goal.getGlobalBounds()) && score == 2) {
                    win = true;
                    window.draw(winner);
                    window.display();
                    flag = false;

                }
                if (!collected1 && player.getGlobalBounds().intersects(collectible1.getGlobalBounds())) {
                    collected1 = true;
                    level.play();
                    score++;

                }


                if (!collected2 && player.getGlobalBounds().intersects(collectible2.getGlobalBounds())) {
                    collected2 = true;
                    level.play();
                    score++;
                }


                window.draw(background);

                for (int i = 0; i < rows; ++i) {
                    for (int j = 0; j < cols; ++j) {
                        window.draw(cells[i][j]);
                    }
                }
                window.draw(player);
                window.draw(goal);

                if (!collected1)
                {
                    window.draw(collectible1);
                }
                if (!collected2)
                {
                    window.draw(collectible2);
                }

                if (!win)
                {
                    window.draw(score_d);
                }

                if (!flag) {
                    window.draw(winner);
                    window.display();
                    sleep(sf::seconds(1));

                    window.close();
                    currentLevel = 2;


                }
                else {
                    window.draw(timer);
                    window.display();
                }

            }
            break;
        }



        case 2:
        {
            int red = 0;
            int score = 0;
            RenderWindow window(VideoMode(640, 400), "Maze Runner", Style::Default);

            Texture back;//bacground texture(wood)
            back.loadFromFile("wood.png");

            Sprite background;
            background.setTexture(back);
            background.setScale(
                static_cast<float>(window.getSize().x) / back.getSize().x,
                static_cast<float>(window.getSize().y) / back.getSize().y
            );


            int maze[rows][cols] = {
                {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
             { 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1 },
             { 1, 0, 1, 1, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 0, 1 },
             { 1, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1 },
             { 1, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 0, 1 },
             { 1, 1, 0, 0, 0, 1, 0, 1, 1, 0, 1, 0, 0, 1, 0, 1 },//med
             { 1, 1, 1, 1, 0, 1, 0, 0, 0, 1, 1, 1, 0, 1, 0, 1 },
             { 1, 1, 1, 1, 0, 0, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1 },
             { 1, 1, 1, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1 },
             { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 }




            };

            RectangleShape cells[rows][cols];
            for (int i = 0; i < rows; ++i) {
                for (int j = 0; j < cols; ++j) {
                    cells[i][j].setSize(Vector2f(c_size - 2, c_size - 2));
                    cells[i][j].setPosition(j * c_size, i * c_size);
                    if (maze[i][j] == 1) {
                        cells[i][j].setFillColor(Color::Black);
                    }
                    else {
                        cells[i][j].setFillColor(Color::White);
                    }
                }
            }

            CircleShape player(15.0f);
            player.setFillColor(Color::Red);
            player.setPosition(c_size + 10, c_size + 10);

            RectangleShape goal(Vector2f(c_size - 10, c_size - 5));
            goal.setFillColor(Color::Green);
            goal.setPosition(14 * c_size + 5, 8 * c_size + 5);
            Font font;
            font.loadFromFile("arial.ttf");
            Text winner, score_d, dif;
            dif.setFont(font);
            dif.setFillColor(Color::White);
            dif.setPosition(Vector2f(130, 360));
            dif.setString("(The collectibles are invisible)");
            score_d.setFont(font);
            score_d.setFillColor(Color::White);
            score_d.setPosition(Vector2f(10, 10));
            winner.setFont(font);
            winner.setString("Congratulations You Have  Won!");
            winner.setCharacterSize(30);
            winner.setFillColor(Color::Magenta);
            winner.setStyle(Text::Bold);
            winner.setPosition(98, 10);
            bool flag = true;
            Clock clock;
            Text timer;
            timer.setFont(font);
            timer.setCharacterSize(20);
            timer.setFillColor(Color::White);
            timer.setPosition(10, window.getSize().y - 30);
            CircleShape collectible1(10.0f);
            collectible1.setFillColor(Color::White);
            collectible1.setPosition(205, 290);
            bool collectible1Visible = true;

            CircleShape collectible2(10.0f);
            collectible2.setFillColor(Color::White);
            collectible2.setPosition(90, 210);
            bool collectible2Visible = true;

            CircleShape collectible3(10.0f);
            collectible3.setFillColor(Color::White);
            collectible3.setPosition(370, 210);
            bool collectible3Visible = true;

            CircleShape collectible4(10.0f);
            collectible4.setFillColor(Color::White);
            collectible4.setPosition(410, 285);
            bool collectible4Visible = true;



            float speed = 0.15f;

            while (window.isOpen()) {
                Event evnt;
                while (window.pollEvent(evnt)) {
                    if (evnt.type == Event::Closed)
                    {
                        window.close();
                        return 0;
                    }
                }
                score_d.setString("Score: " + to_string(score));
                float elapsedTime = 30 - clock.getElapsedTime().asSeconds();
                int minutes = elapsedTime / 60;
                int seconds = static_cast<int>(elapsedTime) % 60;
                timer.setString("Time: " + to_string(minutes) + ":" + (seconds < 10 ? "0" : "") + to_string(seconds));
                if (elapsedTime <= 0) {
                    window.clear();
                    red = red + 10;
                    Text gameOverText;
                    gameOverText.setFont(font);
                    gameOverText.setString("Time's up! Game Over!\nStarting the level again");
                    gameOverText.setCharacterSize(30);
                    gameOverText.setFillColor(Color::Red);
                    gameOverText.setPosition(150, 150);
                    window.draw(gameOverText);
                    window.display();
                    sleep(sf::seconds(3));
                    break;
                }


                FloatRect playerBounds = player.getGlobalBounds();

                if (Keyboard::isKeyPressed(Keyboard::Key::Right) && flag) {
                    player.move(speed, 0.0f);
                    FloatRect nextPos = player.getGlobalBounds();
                    for (int i = 0; i < rows; ++i) {
                        for (int j = 0; j < cols; ++j) {
                            if (maze[i][j] == 1 && cells[i][j].getGlobalBounds().intersects(nextPos)) {
                                player.move(-speed, 0.0f);
                            }
                        }
                    }
                }
                if (Keyboard::isKeyPressed(Keyboard::Key::Left) && flag) {
                    player.move(-speed, 0.0f);
                    FloatRect nextPos = player.getGlobalBounds();
                    for (int i = 0; i < rows; ++i) {
                        for (int j = 0; j < cols; ++j) {
                            if (maze[i][j] == 1 && cells[i][j].getGlobalBounds().intersects(nextPos)) {
                                player.move(speed, 0.0f);
                            }
                        }
                    }
                }
                if (Keyboard::isKeyPressed(Keyboard::Key::Down) && flag) {
                    player.move(0.0f, speed);
                    FloatRect nextPos = player.getGlobalBounds();
                    for (int i = 0; i < rows; ++i) {
                        for (int j = 0; j < cols; ++j) {
                            if (maze[i][j] == 1 && cells[i][j].getGlobalBounds().intersects(nextPos)) {
                                player.move(0.0f, -speed);
                            }
                        }
                    }
                }
                if (Keyboard::isKeyPressed(Keyboard::Key::Up) && flag) {
                    player.move(0.0f, -speed);
                    FloatRect nextPos = player.getGlobalBounds();
                    for (int i = 0; i < rows; ++i) {
                        for (int j = 0; j < cols; ++j) {
                            if (maze[i][j] == 1 && cells[i][j].getGlobalBounds().intersects(nextPos)) {
                                player.move(0.0f, speed);
                            }
                        }
                    }
                }


                if (player.getGlobalBounds().intersects(goal.getGlobalBounds()) && score == 4) {

                    window.draw(winner);
                    window.display();
                    flag = false;

                }
                if (collectible1Visible && player.getGlobalBounds().intersects(collectible1.getGlobalBounds())) {
                    score++;
                    level.play();
                    collectible1Visible = false;
                }

                if (collectible2Visible && player.getGlobalBounds().intersects(collectible2.getGlobalBounds())) {
                    score++;
                    level.play();
                    collectible2Visible = false;
                }

                if (collectible3Visible && player.getGlobalBounds().intersects(collectible3.getGlobalBounds())) {
                    score++;
                    level.play();
                    collectible3Visible = false;
                }

                if (collectible4Visible && player.getGlobalBounds().intersects(collectible4.getGlobalBounds())) {
                    score++;
                    level.play();
                    collectible4Visible = false;
                }


                window.draw(background);

                for (int i = 0; i < rows; ++i) {
                    for (int j = 0; j < cols; ++j) {
                        window.draw(cells[i][j]);
                    }
                }
                window.draw(player);
                window.draw(goal);
                if (collectible1Visible) {
                    window.draw(collectible1);
                }
                if (collectible2Visible) {
                    window.draw(collectible2);
                }
                if (collectible3Visible) {
                    window.draw(collectible3);
                }
                if (collectible4Visible) {
                    window.draw(collectible4);
                }


                if (!flag) {
                    window.draw(winner);
                    window.display();
                    sleep(sf::seconds(1));
                    currentLevel = 0;

                    window.close();
                    /*currentState = reoccur;*/
                    currentLevel = 3;
                    /*front.clear();*/




                }
                else {

                    window.draw(dif);

                    window.draw(timer);
                    window.draw(score_d);
                    window.display();

                }

            }


            break;
        }
        case 3:
        {
            const int rows = 20;
            const int cols = 30;
            const float c_size = 30.0f;
            int score = 0;
            RenderWindow window(VideoMode(900, 600), "Maze Runner", Style::Default);

            Texture back;//bacground texture(wood)
            back.loadFromFile("wood.png");

            Sprite background;
            background.setTexture(back);
            background.setScale(
                static_cast<float>(window.getSize().x) / back.getSize().x,
                static_cast<float>(window.getSize().y) / back.getSize().y
            );


            int maze[rows][cols] = {
                {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
{1, 0, 0, 0, 1, 0, 1, 1, 1, 0, 0, 1, 1, 1, 0, 1, 0, 1, 0, 0, 0, 1, 0, 0, 1, 1, 1, 1, 0, 1},
{1, 1, 1, 0, 1, 0, 0, 0, 1, 0, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 0, 0, 1, 0, 1},
{1, 0, 0, 0, 0, 0, 1, 0, 1, 1, 0, 0, 0, 1, 0, 1, 1, 0, 0, 0, 1, 1, 0, 0, 0, 1, 0, 1, 0, 1},
{1, 1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 0, 1},
{1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
{1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 0, 1},
{1, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 0, 1},
{1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1},
{1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
{1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1},
{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1},
{1, 0, 1, 0, 0, 0, 1, 0, 1, 1, 1, 0, 1, 0, 1, 1, 0, 1, 0, 0, 0, 1, 0, 1, 0, 1, 1, 1, 0, 1},
{1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1},
{1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1},
{1, 0, 1, 0, 1, 0, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 0, 0, 1, 0, 1, 1, 0, 0, 1, 0, 1, 1, 0, 1},
{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1},
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},




            };

            RectangleShape cells[rows][cols];
            for (int i = 0; i < rows; ++i) {
                for (int j = 0; j < cols; ++j) {
                    cells[i][j].setSize(Vector2f(c_size - 2, c_size - 2));
                    cells[i][j].setPosition(j * c_size, i * c_size);
                    if (maze[i][j] == 1) {
                        cells[i][j].setFillColor(Color::Black);
                    }
                    else {
                        cells[i][j].setFillColor(Color::White);
                    }
                }
            }


            CircleShape player(12.0f);
            player.setFillColor(Color::Green);
            player.setPosition(c_size, c_size + 5);

            RectangleShape goal(Vector2f(c_size - 10, c_size - 5));
            goal.setFillColor(Color::Red);
            goal.setPosition(28 * c_size + 5, 18 * c_size + 5);
            CircleShape collectible1(10.0f);
            collectible1.setFillColor(Color::Green);
            collectible1.setPosition(844, 35);
            bool collectible1Visible = true;

            CircleShape collectible2(10.0f);
            collectible2.setFillColor(Color::Red);
            collectible2.setPosition(844, 393);
            bool collectible2Visible = true;

            CircleShape collectible3(10.0f);
            collectible3.setFillColor(Color::Cyan);
            collectible3.setPosition(153, 392);
            bool collectible3Visible = true;

            CircleShape collectible4(10.0f);
            collectible4.setFillColor(Color::Magenta);
            collectible4.setPosition(35, 275);
            bool collectible4Visible = true;
            Font font;
            font.loadFromFile("arial.ttf");
            Text winner, score_d;
            score_d.setFont(font);
            score_d.setFillColor(Color::White);
            score_d.setPosition(Vector2f(10, 0));

            winner.setFont(font);
            winner.setString("Congratulations You Have  Won!");
            winner.setCharacterSize(26);
            winner.setFillColor(Color::Blue);
            winner.setStyle(Text::Bold);
            winner.setPosition(250, 0);
            bool flag = true, win = false;
            Clock clock;
            Text timer;
            timer.setFont(font);
            timer.setCharacterSize(20);
            timer.setFillColor(Color::White);
            timer.setPosition(10, window.getSize().y - 30);


            float speed = 0.3f;

            while (window.isOpen()) {
                Event evnt;
                while (window.pollEvent(evnt)) {
                    if (evnt.type == Event::Closed)
                    {
                        window.close();
                        return 0;
                    }

                }
                score_d.setString("Score: " + to_string(score));
                float elapsedTime = 60.0 - clock.getElapsedTime().asSeconds();
                int minutes = elapsedTime / 60;
                int seconds = static_cast<int>(elapsedTime) % 60;
                timer.setString("Time left: " + to_string(minutes) + ":" + (seconds < 10 ? "0" : "") + to_string(seconds));
                if (elapsedTime <= 0) {
                    window.clear();
                    Text gameOverText;
                    gameOverText.setFont(font);
                    gameOverText.setString("Time's up! Game Over!\nStarting the level again");
                    gameOverText.setCharacterSize(30);
                    gameOverText.setFillColor(Color::Red);
                    gameOverText.setPosition(290, 270);
                    window.draw(gameOverText);
                    window.display();
                    sleep(sf::seconds(3));
                    break;
                }
                FloatRect playerBounds = player.getGlobalBounds();

                if (Keyboard::isKeyPressed(Keyboard::Key::Right) && flag) {
                    player.move(speed, 0.0f);
                    FloatRect nextPos = player.getGlobalBounds();
                    for (int i = 0; i < rows; ++i) {
                        for (int j = 0; j < cols; ++j) {
                            if (maze[i][j] == 1 && cells[i][j].getGlobalBounds().intersects(nextPos)) {
                                player.move(-speed, 0.0f);
                            }
                        }
                    }
                }
                if (Keyboard::isKeyPressed(Keyboard::Key::Left) && flag) {
                    player.move(-speed, 0.0f);
                    FloatRect nextPos = player.getGlobalBounds();
                    for (int i = 0; i < rows; ++i) {
                        for (int j = 0; j < cols; ++j) {
                            if (maze[i][j] == 1 && cells[i][j].getGlobalBounds().intersects(nextPos)) {
                                player.move(speed, 0.0f);
                            }
                        }
                    }
                }
                if (Keyboard::isKeyPressed(Keyboard::Key::Down) && flag) {
                    player.move(0.0f, speed);
                    FloatRect nextPos = player.getGlobalBounds();
                    for (int i = 0; i < rows; ++i) {
                        for (int j = 0; j < cols; ++j) {
                            if (maze[i][j] == 1 && cells[i][j].getGlobalBounds().intersects(nextPos)) {
                                player.move(0.0f, -speed);
                            }
                        }
                    }
                }
                if (Keyboard::isKeyPressed(Keyboard::Key::Up) && flag) {
                    player.move(0.0f, -speed);
                    FloatRect nextPos = player.getGlobalBounds();
                    for (int i = 0; i < rows; ++i) {
                        for (int j = 0; j < cols; ++j) {
                            if (maze[i][j] == 1 && cells[i][j].getGlobalBounds().intersects(nextPos)) {
                                player.move(0.0f, speed);
                            }
                        }
                    }
                }
                if (collectible1Visible && player.getGlobalBounds().intersects(collectible1.getGlobalBounds())) {
                    score++;
                    level.play();
                    collectible1Visible = false;
                }

                if (collectible2Visible && player.getGlobalBounds().intersects(collectible2.getGlobalBounds())) {
                    score++;
                    level.play();
                    collectible2Visible = false;
                }
                if (collectible4Visible && player.getGlobalBounds().intersects(collectible4.getGlobalBounds())) {
                    score++;
                    level.play();
                    collectible4Visible = false;
                }
                if (collectible3Visible && player.getGlobalBounds().intersects(collectible3.getGlobalBounds())) {
                    score++;
                    level.play();
                    collectible3Visible = false;
                }





                if (player.getGlobalBounds().intersects(goal.getGlobalBounds()) && score == 4) {
                    win = true;
                    window.draw(winner);
                    window.display();
                    flag = false;

                }



                window.draw(background);

                for (int i = 0; i < rows; ++i) {
                    for (int j = 0; j < cols; ++j) {
                        window.draw(cells[i][j]);
                    }
                }
                window.draw(player);
                window.draw(goal);
                if (collectible1Visible) {
                    window.draw(collectible1);
                }
                if (collectible2Visible) {
                    window.draw(collectible2);
                }
                if (collectible3Visible) {
                    window.draw(collectible3);
                }
                if (collectible4Visible) {
                    window.draw(collectible4);
                }

                if (!win)
                {
                    window.draw(score_d);
                }

                if (!flag)
                {
                    window.draw(winner);
                    window.display();
                    sleep(sf::seconds(1));

                    window.close();
                    currentLevel = 4;


                }
                else
                {
                    window.draw(timer);
                    window.display();
                }

            }


        }
        break;
        }
    }

}
















